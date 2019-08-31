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

######################################################################
#
# Add executibles
#
######################################################################
add_executable(main main.cpp)
