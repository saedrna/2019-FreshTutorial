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

target_link_libraries(main mymath Qt5::Core Qt5::Widgets Qt5::Gui)

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
          "$<TARGET_FILE_DIR:main>/resources/"
  COMMAND ${CMAKE_COMMAND} -E copy ${QM_FILES}
          "$<TARGET_FILE_DIR:main>/resources/"
  COMMENT "Copying translation files to $<TARGET_FILE_DIR:main>/resources/"
)