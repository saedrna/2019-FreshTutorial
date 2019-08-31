file(GLOB SOURCES
          "*.h"
          "*.cpp"
          "*.ui"
          "*.qrc")

file(GLOB WIDGET_SRC "widget_*")
file(GLOB TOOL_SRC "tool*")
file(GLOB OBS_SRC "obs*")
file(GLOB PROJECT_SRC "osketch*")
file(GLOB UI_SRC "*.ui" "*.qrc")

source_group("Widget Files" FILES ${WIDGET_SRC})
source_group("Tool Files" FILES ${TOOL_SRC})
source_group("Obs Files" FILES ${OBS_SRC})
source_group("OSketch Files" FILES ${PROJECT_SRC})

# TODO 修改翻译文件路径
file(GLOB TS_FILES "OSketchProPluginHelloWorld_zh_CN.ts")

file(GLOB TS_SRC_FILES
          "*.h"
          "*.cpp"
          "*.hpp"
          "*.ui"
          "*.qrc")
qt5_create_translation_no_include(QM_FILES
                                  "${TS_SRC_FILES};${OTHER_SRC_FILES}"
                                  ${TS_FILES}
                                  OPTIONS
                                  -locations
                                  relative)

# TODO 修改这些 target 的名称，和后面所有对应的名字
h2o_add_library(osketchpro_plugin_helloworld
                ${CMAKE_INSTALL_PREFIX}/ruby/h2o_osketchpro
                ${SOURCES}
                ${QM_FILES}
                ${TS_FILES})
target_link_libraries(osketchpro_plugin_helloworld
                      PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui)
target_link_libraries(osketchpro_plugin_helloworld
                      PRIVATE H2O::h2o_sketchup
                              H2O::osketchpro_frame
                              ruby
                              qtwinmigrate)
add_custom_command(
  TARGET osketchpro_plugin_helloworld POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${QM_FILES}
          "${CMAKE_INSTALL_PREFIX}/ruby/h2o_osketchpro/Resources"
  COMMENT "Copying files")

install(FILES ${QM_FILES} DESTINATION Resources)
