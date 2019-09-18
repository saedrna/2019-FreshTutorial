cmake_minimum_required(VERSION 3.0) #必需，用于规定所需的cmake版本

project(CMakeTutorial LANGUAGES C CXX) #必需，设定项目名称

######################################################################
#
# CMake Project Settings
#
######################################################################
set(CMAKE_CXX_STANDARD 11) #使用的标准版本

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_BugFix "0")
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BugFix})
#上面的四行为具体版本号
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP /wd4996 /wd4819 /wd4251 /wd4267 /wd4244 /wd4275 /wd4005 /wd5033 /wd4018")
    add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES -DWIN32_LEAN_AND_MEAN -DNOMINMAX -D_ENABLE_EXTENDED_ALIGNED_STORAGE) # windows use windows api
endif(MSVC)
#if中是忽略了常见的一些无用警告和bug
######################################################################
#
# Add executibles
#
######################################################################
add_executable(main main.cpp)
#将创建的cpp加入程序中
