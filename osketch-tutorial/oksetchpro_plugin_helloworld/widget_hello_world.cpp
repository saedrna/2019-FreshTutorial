/*
 * @Author: Han
 * @Date: 2019-08-28 20:46:50
 *
 * Hello World 对话框
 */

#include "widget_hello_world.h"
#include "osketchpro_plugin_helloworld.h"

#include <QMessageBox>

#include <osketchpro_frame/osketchpro_interface.h>

WidgetHelloWorld::WidgetHelloWorld(QDialog *parent) : QDialog(parent) {
    setupUi(this);

    adjustSize();
//TODO：修改connect下对应部件的名称
    connect(btn_test, &QPushButton::clicked, [this]() {
        QWidget *root = get_osketchpro_interface()->get_widget_root();
        std::string data = OSketchProPluginHelloWorld::get_plugin()->data_;

        QMessageBox::information(root, tr("Information"), QString::fromStdString(data), QMessageBox::Ok);
    });
}

WidgetHelloWorld::~WidgetHelloWorld() {}
