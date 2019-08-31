/*
 * @Author: Han
 * @Date: 2019-08-28 20:47:01
 *
 * Hello World 对话框
 */

#pragma once

#include "ui_widget_hello_world.h"

class WidgetHelloWorld : public QDialog, public Ui::WidgetHelloWorld {
    Q_OBJECT
public:
    WidgetHelloWorld(QDialog *parent);
    ~WidgetHelloWorld();
};