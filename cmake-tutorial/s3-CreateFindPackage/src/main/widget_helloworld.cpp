#include "widget_helloworld.h"

#include <Eigen/Core>
#include <mymath/mymath.h>

WidgetHelloWorld::WidgetHelloWorld(QWidget *parent) : QDialog(parent) {
    setupUi(this);
    adjustSize();

    connect(btn_test, SIGNAL(clicked()), SLOT(clicked_test()));
}

WidgetHelloWorld::~WidgetHelloWorld() {}

void WidgetHelloWorld::clicked_test() {
    Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
    lab_text->setText(QString::number(get_trace(R)));
    adjustSize();
}
