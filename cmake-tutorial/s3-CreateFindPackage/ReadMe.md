- 本示例中实现的功能为：调用 Eigen3 函数库，在 mymath 中实现计算矩阵对角线上的和的功能。
  - 创建一个文件夹。命名为 s3-CreateFindPackage ，内部文件组织形式于上一示例相同，可以复制过来。在cmake 文件夹下添加一个文件 FindEigen3.cmake ，内容及注释点[这里](cmake-tutorial/s3-CreateFindPackage/cmake/FindEigen3.cmake).
  - 在 s3-CreateFindPackage 下的 cmakelists中，添加如下内容：
   ```cmake
    set(Eigen3_INCLUDE_DIR ${CMAKE_PREFIX_PATH}/include/eigen3)
    find_package(Eigen3 REQUIRED)
    ```
  - 在 mymath 的 cmakelists 文件中添加如下内容：
  ```cmake
    target_link_libraries(mymath Eigen3::Eigen3)
    ```
  - 在 mymath.cpp 中添加一个求矩阵对角线和的函数：
   ```c++
    double get_trace(const Eigen::Matrix3d& v)
    {
        return v.diagonal().sum();
    }
    ```
  - 在 widget_helloworld.cpp 下修改 click 函数：
   ```c++
    void WidgetHelloWorld::clicked_test() {
        Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
        lab_text->setText(QString::number(get_trace(R)));
        adjustSize();
      }

    ```
  - 运行 build.bat ,对项目进行编译，得到对应的 sln 。生成并添加缺少的插件后，即可成功运行。至此查找第三方库完成。