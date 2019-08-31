#pragma once

#include "ui_widget_helloworld.h"

class WidgetHelloWorld : public QDialog, public Ui::WidgetHelloWorld {
    Q_OBJECT
public:
    WidgetHelloWorld(QWidget *parent = nullptr);
    ~WidgetHelloWorld();

public slots:
    void clicked_test();
};
