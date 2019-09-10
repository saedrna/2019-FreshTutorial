cmake_minimum_required(VERSION 3.0)

project(CMakeTutorial LANGUAGES C CXX)

######################################################################
#
# CMake Project Settings
#
######################################################################
set(CMAKE_CXX_STANDARD 11)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_BugFix "0")
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BugFix})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP /wd4996 /wd4819 /wd4251 /wd4267 /wd4244 /wd4275 /wd4005 /wd5033 /wd4018")
    add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES -DWIN32_LEAN_AND_MEAN -DNOMINMAX -D_ENABLE_EXTENDED_ALIGNED_STORAGE) # windows use windows api
endif(MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(BUILD_SHARED_LIBS "Build Dynamic Libs" ON)

######################################################################
#
# Find Package
#
######################################################################
# https://blog.kitware.com/cmake-finding-qt5-the-right-way/
# https://doc.qt.io/qt-5/cmake-manual.html
find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)
include(Qt5LinguistToolsMacrosNoInclude)

######################################################################
#
# Add executibles
#
######################################################################

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)   
add_subdirectory(src)
#连接到src文件夹下，通过src下的cmakelists文件进行进一步处理