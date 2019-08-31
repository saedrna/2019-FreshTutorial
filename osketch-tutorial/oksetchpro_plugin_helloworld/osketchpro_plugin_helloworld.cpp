/*
 * @Author: Han
 * @Date: 2019-08-28 20:41:18
 *
 * 插件入口
 */

#include "osketchpro_plugin_helloworld.h"
#include "widget_hello_world.h"

#include <QTranslator>

#include <base/base.h>
#include <osketchpro_frame/osketchpro_interface.h>

OSketchProPluginHelloWorld *OSketchProPluginHelloWorld::get_plugin() {
    // 这个 plugins 返回的就是插件名称和插件实例的一个 map
    auto plugins = get_osketchpro_interface()->get_plugins();
    return (OSketchProPluginHelloWorld *)plugins.at("org.vrlab.osketchpro.plugin.helloworld");
}

WidgetHelloWorld *OSketchProPluginHelloWorld::get_widget() {
    // 每个窗口在接口中注册后，都可以通过他的名称获取到，接口内部也是维护的一个和名称对应的 map
    return (WidgetHelloWorld *)get_osketchpro_interface()->get_widget("HelloWorld");
}

bool OSketchProPluginHelloWorld::init() {
    // 加载翻译文件
    {
        // 获取插件的相对路径，资源文件会安装在此目录
        std::string dir;
        {
            auto handle = GetModuleHandle("osketchpro.so");
            char path[1024];
            GetModuleFileNameA(handle, path, 1024);
            dir = std::string(path);
            dir = get_directory(dir);
        }

        QLocale locale;
        if (locale.country() == QLocale::China) {

            // TODO: 修改翻译资源名称
            QString name = "OSketchProPluginHelloWorld_" + QLocale::system().name();

            QTranslator *translator = new QTranslator();
            bool loaded = translator->load(name, QString::fromStdString(join_paths(dir, "Resources")));
            loaded = QApplication::installTranslator(translator);

            CHECK(loaded);
        }
    }

    OSketchProInterface *interface = get_osketchpro_interface();

    // 创建 UI 信息
    //创建该插件的按钮，图标为Building.png
    QPushButton *button = new QPushButton(QIcon(":/images/Building.png"), "", interface->get_toolbar());
    button->setIconSize({32, 32});
    // 这里父节点给 nullptr，在加入到主程序后，会修改父节点
    WidgetHelloWorld *widget_helloworld = new WidgetHelloWorld(nullptr);

    // TODO: 第一个参数就是 UI 的名称，用于后续获取 UI
    interface->add_widget("HelloWorld", button, widget_helloworld);

    data_ = "Hello World!";

    return true;
}

std::tuple<int, std::string> OSketchProPluginHelloWorld::get_dog_feature() {
    // make_tuple 第一个参数为该插件 ID ，该ID若为-1，认为这个插件不需要狗也可以访问，否则必须要有特定 id 的狗
    return std::make_tuple(-1, std::string("org.vrlab.osketchpro.plugin.helloworld"));
}
