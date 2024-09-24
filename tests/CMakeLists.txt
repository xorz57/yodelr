cmake_minimum_required(VERSION 3.15...3.30)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
  GIT_SHALLOW ON
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(YodelrTest main.cpp)
target_link_libraries(YodelrTest PRIVATE GTest::gtest_main)
target_link_libraries(YodelrTest PRIVATE Yodelr::Yodelr)

include(GoogleTest)

gtest_discover_tests(YodelrTest)
