- 先创建一个文件夹，命名为 s0-CreateAnExecutible 。在该文件夹下添加一个源文件命名为main.cpp，再添加一个 CMakeLists.txt。

- CMakeLists.txt文件中，第一行为：
  ```cmake
  cmake_minimum_required(VERSION 3.0) #必需：用于规定需要使用 的 cmake 版本。
  ```
  第二行为：
  ```cmake
  project(CMakeTutorial LANGUAGES C CXX) #必需：定义所创建项目的名称。
  ```
  接下来的内容为工程所需配置信息。
  ```cmake
  set(CMAKE_CXX_STANDARD 11) #使用的标准版本
  set(VERSION_MAJOR "0")
  set(VERSION_MINOR "1")
  set(VERSION_BugFix "0")
  set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BugFix})
  #上面的四行为具体版本号
  if(MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP /wd4996 /wd4819 /wd4251 /wd4267 /wd4244 /wd4275 /4005 /wd5033 /wd4018")
      add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES -DWIN32_LEAN_AND_MEAN -DNOMINMAX _ENABLE_EXTENDED_ALIGNED_STORAGE) # windows use windows api
  endif(MSVC)
  #if中是忽略了常见的一些无用警告和bug
    ```
  
  最后添加一行：
  
  ```cmake
    add_executable(main main.cpp)  #将创建的cpp加入程序中
  ```
- 在 s0-CreateAnExecutible 文件夹下添加一个 build.bat 文件，文件中添加如下代码：

   ```cmake
      mkdir build
      cd build
      cmake -G "Visual Studio 15 2017" -A "x64" -T "host=x64" ^
          -DCMAKE_TOOLCHAIN_FILE=%CONDA_PREFIX%/h2o.cmake ^
          -DCMAKE_BUILD_TYPE=Release ^
          ../
  ```

- 接下来需要在配置好的anaconda环境下对其进行编译（环境配置方法点[这里](../../3rdparty/ReadMe.md)）。
![build](../../images/build.PNG)

- 若编译成功，s0-CreateAnExecutible 文件夹下会出现一个名为 build 的文件夹。打开其中的 CMakeTutorial.sln 即可看到好的解决方案。此时就可以进行进一步的功能添加等操作了。此处以控制台输出 ``` Hello World``` 为例。在 main.cpp 下如下代码：
  ```c++
    #include <iostream>
    int main(int argc, char** argv){
        std::cout << "Hello World!" << std::endl;
        return 0;
    }
  ```

- 在 ```RelWithDebInfo``` 模式下进行调试（请务必使用该模式调试），将 main 设为启动项目，即可得到以下输出：
  ![result](../../images/s0result.PNG)