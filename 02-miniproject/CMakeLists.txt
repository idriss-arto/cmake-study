cmake_minimum_required(VERSION 3.31)

# 项目名称
project(MiniProject VERSION 0.1.0 DESCRIPTION "DEMO of Complex Number" LANGUAGES CXX)

# 添加可执行程序
# add_executable(demo main.cpp complex.cpp complex.h)
add_executable(demo)

target_sources(demo
    PRIVATE
        main.cpp
        complex.cpp
        complex.h
)