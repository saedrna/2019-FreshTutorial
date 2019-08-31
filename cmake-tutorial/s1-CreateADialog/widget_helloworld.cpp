#include "widget_helloworld.h"

WidgetHelloWorld::WidgetHelloWorld(QWidget *parent) : QDialog(parent) {
    setupUi(this);
    adjustSize();

    connect(btn_test, SIGNAL(clicked()), SLOT(clicked_test()));
}

WidgetHelloWorld::~WidgetHelloWorld() {}

void WidgetHelloWorld::clicked_test() {
    lab_text->setText(tr("HelloWorld"));
    adjustSize();
}
