cmake_minimum_required(VERSION 3.15)

project(image-processer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)
add_subdirectory(src)

option(BUILD_TEST "build test" ON)
if(BUILD_TEST)
    add_subdirectory(test)
endif()