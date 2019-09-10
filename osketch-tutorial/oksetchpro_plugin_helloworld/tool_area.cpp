/*
 * @Author: Han Hu
 * @Date: 2019-03-19 17:50:42
 * 纹理清理工具，会高亮待清理的纹理，并且鼠标移动上取会显示纹理大小
 */

#include <osketchpro_frame/osketchpro_interface.h>
#include <sketchup/sketchup.h>

#include "tool_area.h"

namespace h2o {

ToolArea::ToolArea(QObject *parent) : ToolBase(parent) {}

ToolArea::~ToolArea() {}

VALUE ToolArea::activate() {
    // 创建一个 pick helper
    VALUE view = rb_funcall(su_model(), rb_intern("active_view"), 0);
    VALUE ph = rb_funcall(view, rb_intern("pick_helper"), 0);
    rb_iv_set(rtool_, "@pick_helper", ph);

    create_geometry();

    return Qnil;
}

VALUE ToolArea::deactivate(VALUE view) {
    rb_funcall(view, rb_intern("invalidate"), 0);
    su_choose_selection_tool();

    return Qnil;
}

VALUE ToolArea::draw(VALUE view) {
    VALUE face_color = su_color(Vector4d(0.0, 1.0, 1.0, 1.0));
    VALUE line_color = su_color(Vector4d(1.0, 0.7, 0.0, 1.0));

    // 绘制面

    VALUE V = rb_iv_get(rtool_, "@V");
    if (V != Qnil) {
        rb_funcall(view, rb_intern("drawing_color="), 1, face_color);
        rb_funcall(view, rb_intern("draw"), 2, rb_eval_string("GL_TRIANGLES"), V);
    }

    // 绘制边界
    VALUE E = rb_iv_get(rtool_, "@E");
    if (E != Qnil) {
        rb_funcall(view, rb_intern("line_stipple="), 1, su_string(""));
        rb_funcall(view, rb_intern("drawing_color="), 1, line_color);
        rb_funcall(view, rb_intern("line_width="), 1, INT2NUM(5));
        rb_funcall(view, rb_intern("draw"), 2, rb_eval_string("GL_LINES"), E);
    }

    VALUE face = rb_iv_get(rtool_, "@face");
    if (face != Qnil) {
        VALUE point = rb_iv_get(rtool_, "@point");
        VALUE options = rb_eval_string(R"(
{
  :size => 14,
  :bold => true,
  :color => "DeepPink",
  :align => TextAlignRight
})");
        //通过下面这行获取到的平面面积值格式为ruby下的Value类型。直接转为double进行输出，会出现乱码和
        //数值异常的情况，需要进行转化
        //double area = rb_funcall(face, rb_intern("area"), 0);
        value rb_area = rb_funcall(face, rb_intern("area"), 0);
        double area=NUM2DBL(rb_area)* INCH_2_METER * INCH_2_METER;
        //NUM2DBL可将value形式的变量转换为double。sketchup默认单位为英寸，需进行单位转化，1英寸=0.0254米
        VALUE text = su_string(QObject::tr("Face Area [%1]").arg(QString::number(area)).toStdString());
        rb_funcall(view, rb_intern("draw_text"), 3, point, text, options);
        return Qnil;
    }

    return Qnil;
}

VALUE ToolArea::onMouseMove(VALUE flags, VALUE x, VALUE y, VALUE view) {
    VALUE ph = rb_iv_get(rtool_, "@pick_helper");
    VALUE rnum = rb_funcall(ph, rb_intern("do_pick"), 2, x, y);

    if (NUM2INT(rnum) == 0) {
        rb_iv_set(rtool_, "@face", Qnil);
        return Qnil;
    }

    VALUE face = rb_funcall(ph, rb_intern("picked_face"), 0);
    if (face == Qnil) {
        rb_iv_set(rtool_, "@face", Qnil);
        rb_funcall(view, rb_intern("invalidate"), 0);
        return Qnil;
    }

    Vector3d point = Vector3d(NUM2DBL(x), NUM2DBL(y), 0.0);

    rb_iv_set(rtool_, "@face", face);
    rb_iv_set(rtool_, "@point", su_point3d(point));
    rb_funcall(view, rb_intern("invalidate"), 0);
    return Qnil;
}

VALUE ToolArea::resume(VALUE view) {
    rb_funcall(view, rb_intern("invalidate"), 0);
    return Qnil;
}

void ToolArea::create_geometry() {
    // 只要这个工具启动，肯定是有平面有问题
    // 判断是否有选择平面
    VALUE sel = rb_funcall(su_model(), rb_intern("selection"), 0);
    std::vector<VALUE> faces = su_enumerable_faces_nocomponent(sel);

    // 对每个 平面，首先绘制一个 原始顶点和当前顶点的连接线
    std::vector<Vector3d> triangles;
    std::vector<Vector3d> boundaries;

    for (VALUE face : faces) {
        // 统一 face normal 和 entity 的坐标系，目前 face normal 是局部的
        // 每个顶点沿着法向量偏移 offset
        Vector3d normal = su_face_normal(face);

        // 只需要顶点和三角形信息
        std::vector<Vector3d> points = su_face_loop_vertices(face);

        for (int i = 0; i < points.size(); ++i) {
            Vector3d point = points[i];
            Vector3d point2 = points[(i + 1) % points.size()];

            // LINE 中添加两个顶点
            boundaries.push_back(point);
            boundaries.push_back(point2);
        }

        //
        MatrixXd vertices;
        MatrixXu indices;
        std::tie(vertices, indices) = su_face_mesh(face);

        for (int f = 0; f < indices.cols(); ++f) {
            triangles.push_back(Vector3d(vertices.col(indices(0, f))));
            triangles.push_back(Vector3d(vertices.col(indices(1, f))));
            triangles.push_back(Vector3d(vertices.col(indices(2, f))));
        }
    }

    // 转换为
    if (triangles.empty() || boundaries.empty()) {
        rb_iv_set(rtool_, "@E", Qnil);
        rb_iv_set(rtool_, "@V", Qnil);
        return;
    }

    // 生成 @V, @E, @L
    VALUE E = rb_ary_new2(boundaries.size());
    for (const Vector3d &point : boundaries) {
        rb_ary_push(E, su_point3d(point));
    }
    rb_iv_set(rtool_, "@E", E);

    VALUE V = rb_ary_new2(triangles.size());
    for (const Vector3d &point : triangles) {
        rb_ary_push(V, su_point3d(point));
    }
    rb_iv_set(rtool_, "@V", V);

    su_view_invalidate(su_model());
}

} // namespace h2o