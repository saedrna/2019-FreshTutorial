/*
 * @Author: Han
 * @Date: 2019-08-28 20:41:27
 *
 * 插件入口
 */

#pragma once

#include <QObject>
#include <QtPlugin>

#include <osketchpro_frame/osketchpro_interface.h>

#include "widget_hello_world.h"

// TODO: change plugin name
class OSketchProPluginHelloWorld : public QObject, public OSketchProPluginInterface {
    Q_OBJECT

    // TODO: change plugin metadata

    Q_PLUGIN_METADATA(IID "org.vrlab.osketchpro.plugin.helloworld" FILE "osketchpro_plugin_helloworld.json")
    Q_INTERFACES(OSketchProPluginInterface)

public:
    // TODO: 最好加入一个静态函数，可以返回当前插件实例
    // 每个插件会维护一个这个实例，可以在这里加入一些在工程周期内的全局参数
    static OSketchProPluginHelloWorld *get_plugin();

    // TODO: 最好加入一个静态函数，可以返回插件的一些数据，也可以通过程序 interface 获取，比较麻烦
    static WidgetHelloWorld *get_widget();

public:
    // TODO: 每个插件必须重载初始化函数
    // 加载插件后，进行初始化，在里面创建需要的内容
    virtual bool init();

    // TODO: 每个插件必须返回特征 ID 和 名字
    virtual std::tuple<int, std::string> get_dog_feature();

public:
    // TODO: 插件实例可能需要维护一些插件内部共有的数据源
    std::string data_;
};