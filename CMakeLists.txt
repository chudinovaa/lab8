set(CMAKE_VER 3.14)
cmake_minimum_required(VERSION ${CMAKE_VER})
project(lab8)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR})

find_package(OpenMP REQUIRED)

add_subdirectory(src)

enable_testing()
find_package(Git REQUIRED)
include(cmake_macros/load_gtest.cmake)
find_package(Threads REQUIRED)
add_subdirectory(test)