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

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


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
file(GLOB SOURCES *.cpp *.h)
file(GLOB SOURCES_QT *.ui *.qrc *.ts)

file(GLOB TS_FILES "widget_helloworld_zh_CN.ts")
file(GLOB TS_SRC_FILES
          "*.h"
          "*.cpp"
          "*.hpp"
          "*.ui"
          "*.qrc")
qt5_create_translation_no_include(QM_FILES
                                  "${TS_SRC_FILES}"
                                  ${TS_FILES}
                                  OPTIONS
                                  -locations
                                  relative)

add_executable(main ${SOURCES} ${SOURCES_QT} ${QM_FILES} ${TS_FILES})

target_link_libraries(main Qt5::Core Qt5::Widgets Qt5::Gui)

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
          "$<TARGET_FILE_DIR:main>/resources/"
  COMMAND ${CMAKE_COMMAND} -E copy ${QM_FILES}
          "$<TARGET_FILE_DIR:main>/resources/"
  COMMENT "Copying translation files to $<TARGET_FILE_DIR:main>/resources/"
)