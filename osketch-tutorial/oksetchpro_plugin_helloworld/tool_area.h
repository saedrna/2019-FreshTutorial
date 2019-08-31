/*
 * @Author: Han Hu
 * @Date: 2019-03-19 17:51:29
 * 纹理清理工具，会高亮待清理的纹理，并且鼠标移动上取会显示纹理大小
 */

#pragma once

#include <osketchpro_frame/tool.h>

#include <ruby.h>

namespace h2o {
class ToolArea : public ToolBase {
    Q_OBJECT
public:
    ToolArea(QObject *parent);
    ~ToolArea();

    VALUE activate() override;
    VALUE deactivate(VALUE view) override;
    VALUE draw(VALUE view) override;
    VALUE onCancel(VALUE reason, VALUE view) override { return Qnil; }
    VALUE onKeyDown(VALUE key, VALUE repeat, VALUE flags, VALUE view) override { return Qnil; }
    VALUE onKeyUp(VALUE key, VALUE repeat, VALUE flags, VALUE view) override { return Qnil; }
    VALUE onLButtonDoubleClick(VALUE flags, VALUE x, VALUE y, VALUE view) override { return Qnil; }
    VALUE onLButtonDown(VALUE flags, VALUE x, VALUE y, VALUE view) override { return Qnil; }
    VALUE onLButtonUp(VALUE flags, VALUE x, VALUE y, VALUE view) override { return Qnil; }
    VALUE onMouseEnter(VALUE view) override { return Qnil; }
    VALUE onMouseLeave(VALUE view) override { return Qnil; }

    VALUE onMouseMove(VALUE flags, VALUE x, VALUE y, VALUE view) override;
    VALUE onReturn(VALUE view) override { return Qnil; }
    VALUE resume(VALUE view) override;
    VALUE suspend(VALUE view) override { return Qnil; }
    VALUE onSetCursor() override { return Qnil; }

    static std::string toolname() { return "ToolArea"; }

protected:
    // 高亮
    void create_geometry();

    // 选择平面的纹理大小
    Vector2i size_texture_;
};
} // namespace h2o
