cmake_minimum_required(VERSION 3.15...3.30)

add_executable(example_yodelr example_yodelr.cpp)
target_link_libraries(example_yodelr PRIVATE Yodelr)
