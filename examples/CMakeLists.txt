cmake_minimum_required(VERSION 3.26)

add_executable(YodelrExample main.cpp)
target_link_libraries(YodelrExample PRIVATE Yodelr::Yodelr)
