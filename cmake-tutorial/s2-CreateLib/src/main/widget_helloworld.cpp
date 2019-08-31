#include "widget_helloworld.h"

#include <mymath/mymath.h>

WidgetHelloWorld::WidgetHelloWorld(QWidget *parent) : QDialog(parent) {
    setupUi(this);
    adjustSize();

    connect(btn_test, SIGNAL(clicked()), SLOT(clicked_test()));
}

WidgetHelloWorld::~WidgetHelloWorld() {}

void WidgetHelloWorld::clicked_test() {
    int c = myadd(1, 2);
    lab_text->setText(QString::number(c));
    adjustSize();
}
