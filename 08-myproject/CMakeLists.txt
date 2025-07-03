cmake_minimum_required(VERSION 3.31)
project(myProject VERSION 1.2.3 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(DemoAPP main.cpp)

configure_file("config.h.in" "config.h")
target_include_directories(DemoAPP PUBLIC ${PROJECT_BINARY_DIR})

# 添加子目录，并执行子目录中的CMakelists.txt
add_subdirectory(Shape)

target_link_libraries(DemoAPP Shape)