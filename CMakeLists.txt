cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Fzolv INTERFACE)
target_include_directories(Fzolv INTERFACE include)

add_executable(Fzolv_Exec src/main.cpp)
target_link_libraries(Fzolv_Exec Fzolv)

enable_testing()
add_executable(Fzolv_Test src/test.cpp)
target_link_libraries(Fzolv_Test Fzolv GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Fzolv_Test)