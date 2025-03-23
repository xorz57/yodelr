cmake_minimum_required(VERSION 3.15...3.30)

add_executable(YodelrExample Main.cpp)
target_link_libraries(YodelrExample PRIVATE Yodelr::Yodelr)
