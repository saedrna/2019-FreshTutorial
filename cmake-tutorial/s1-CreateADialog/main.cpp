#include "widget_helloworld.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFontDatabase>
#include <QTextStream>
#include <QTranslator>

void load_style() {
    QFile f(":qdarkstyle/style.qss");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());

    int fontid = QFontDatabase::addApplicationFont(QStringLiteral(":/fonts/wqy-microhei.ttc"));
    QString wqy = QFontDatabase::applicationFontFamilies(fontid).at(0);
    QFont font(wqy);
#if _WIN32
    font.setPointSizeF(9.0);
#else
    font.setPointSizeF(12.0);
#endif
    QApplication::setFont(font);
}

void load_translator() {
    QLocale locale;
    if (locale.country() == QLocale::China) {
        QString appfile = QApplication::applicationDirPath();
        QString qmdir = QDir(appfile).absoluteFilePath("resources");
        QString qmpath = QDir(qmdir).absoluteFilePath("widget_helloworld_" + QLocale::system().name());
        QTranslator *translator = new QTranslator();
        bool loaded = translator->load(qmpath);
        loaded = QApplication::installTranslator(translator);
    }
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    load_style();
    load_translator();

    WidgetHelloWorld dialog;
    dialog.show();

    return app.exec();
}