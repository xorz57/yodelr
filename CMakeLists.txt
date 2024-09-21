cmake_minimum_required(VERSION 3.26)

project(Yodelr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Yodelr STATIC src/yodelr_impl.cpp)
add_library(Yodelr::Yodelr ALIAS Yodelr)
target_include_directories(Yodelr PUBLIC include)

add_subdirectory(benchmarks)
add_subdirectory(examples)
add_subdirectory(tests)
