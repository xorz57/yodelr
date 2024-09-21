cmake_minimum_required(VERSION 3.15...3.30)

project(Yodelr)

option(YODELR_BENCHMARKS "Build Yodelr Benchmarks" ON)
option(YODELR_EXAMPLES "Build Yodelr Examples" ON)
option(YODELR_TESTS "Build Yodelr Tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Yodelr STATIC src/yodelr_impl.cpp)
add_library(Yodelr::Yodelr ALIAS Yodelr)
target_include_directories(Yodelr PUBLIC include)

if(YODELR_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(YODELR_EXAMPLES)
    add_subdirectory(examples)
endif()

if(YODELR_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
