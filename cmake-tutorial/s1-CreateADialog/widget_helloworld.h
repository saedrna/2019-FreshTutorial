#pragma once    //会让所在的文件在一个单独的编译中只被包含一次

#include "ui_widget_helloworld.h"

class WidgetHelloWorld : public QDialog, public Ui::WidgetHelloWorld {
    Q_OBJECT
public:
    WidgetHelloWorld(QWidget *parent = nullptr);
    ~WidgetHelloWorld();

public slots:
    void clicked_test();
};
