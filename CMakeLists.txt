cmake_minimum_required(VERSION 3.15...3.30)

project(Yodelr LANGUAGES CXX)

option(YODELR_EXAMPLES "Build Yodelr Examples" ON)
option(YODELR_TESTS "Build Yodelr Tests" ON)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Yodelr STATIC src/Yodelr.cpp)
target_include_directories(Yodelr PUBLIC include)

add_library(YodelrMock INTERFACE)
target_include_directories(YodelrMock INTERFACE ${CMAKE_SOURCE_DIR}/mocks)
target_link_libraries(YodelrMock INTERFACE Yodelr)
target_link_libraries(YodelrMock INTERFACE GTest::gmock)

if(YODELR_EXAMPLES)
    add_subdirectory(examples)
endif()

if(YODELR_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
