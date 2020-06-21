- 创建一个文件夹，命名为 s2-CreateLib 。本示例实现的功能为：在上一个实例的基础上，点击按钮，输出两个数字的和。该文件夹包括：src文件夹、cmake文件夹、build.bat、CMakeLists文件。接着上一个实例中的创建的CMakeLists文件，添加如下内容：
    ```cmake

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
     #将所有dll和exe放入bin目录下，将所有lib放入lib目录下。


    include_directories(${CMAKE_CURRENT_LIST_DIR}/src)   
    add_subdirectory(src)
    #连接到src文件夹下，通过src下的cmakelists文件进行进一步处理
    ```
    
    - 对应的，我们看一下src文件夹：包括一个main文件夹、一个mymath文件夹（mymath 下的源文件和头文件实现了简单的加法，此处不做赘述）以及一个 cmakelists 文件。该 cmakelists文件内容为：
    ```cmake
    add_subdirectory(mymath)

    add_subdirectory(main)
    ```
    意为分别加载这两个文件夹中的内容。
   - 这两个文件夹下又分别有cmakelists 文件。mymath文件夹下的cmakelists内容为：
   ```cmake
    file(GLOB SOURCES "*.h" "*.cpp")
    add_library(mymath ${SOURCES})
    #注意此处为library，这样就添加了一个库
    ```
    - 相对于上一个项目，main下的cmakelists文件修改了如下内容：
  ```cmake
    target_link_libraries(main mymath Qt5::Core Qt5::Widgets Qt5::Gui)
    #添加了对mymath 的引用
    void WidgetHelloWorld::clicked_test() {
    int c = myadd(1, 2);
    lab_text->setText(QString::number(c));
    adjustSize();
    //使点击按钮后输出1+2的值
    ```
  - 在 widget_helloworld.cpp 下引用 mymath 中的 myadd 函数。
  ```c++
    void WidgetHelloWorld::clicked_test() {
    int c = myadd(1, 2);
    lab_text->setText(QString::number(c));
    adjustSize();
    //使点击按钮后输出1+2的值
    ```
  - 将缺少的platform插件放入对应位置后即可调试得到正确结果。至此，创建库文件完成。<br>
![libresult](../../images/libresult.PNG)