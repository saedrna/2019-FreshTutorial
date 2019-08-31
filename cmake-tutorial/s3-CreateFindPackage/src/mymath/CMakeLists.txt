file(GLOB SOURCES "*.h" "*.cpp")
add_library(mymath ${SOURCES})
target_link_libraries(mymath Eigen3::Eigen3)
