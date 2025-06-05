cmake_minimum_required(VERSION 3.31)

# 禁用编译器检测输出
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# 项目名称
project(Function_TEST VERSION 0.1.0 LANGUAGES CXX)

# 命名参数和未命名参数，以及ARGC、ARGV、ARGN
# 定义函数
function(my_funtion a b)
    message("=========================MyFunction=========================")
    message("a:${a}, b:${b}")
    message("argc:${ARGC}")
    message("argv:${ARGV}")
    message("argv0:${ARGV0}, argv1:${ARGV1}, argv2:${ARGV2}")
    message("argn:${ARGN}")
    message("argn0:${ARGN0}, argn1:${ARGN1}")
endfunction(my_funtion)

# 使用函数
my_funtion(命名参数一 命名参数二 未命名参数一 未命名参数二 未命名参数三)

# 关键字参数
# 定义函数
# function(my_funtion2 targetName)
#     message("=========================MyFunction2=========================")
#     message("targetName:${targetName}")
#     message("argc:${ARGC}")
#     message("argv:${ARGV}")
# endfunction(my_funtion2)

function(my_funtion2 targetName)
    set(options USE_MYLIB)
    set(oneValueArgs MYLIB_PATH)
    set(multiValueArgs SOURCES INCLUDES)
    cmake_parse_arguments(arg_myfunction2 "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    message("
    =========================MyFunction2=========================
    USE_MYLIB:${arg_myfunction2_USE_MYLIB}
    MYLIB_PATH:${arg_myfunction2_MYLIB_PATH}
    SOURCES:${arg_myfunction2_SOURCES}
    INCLUDES:${arg_myfunction2_INCLUDES}
    targetName:${targetName}
    ")
endfunction(my_funtion2)

# 使用函数
my_funtion2(mytarget
    USE_MYLIB
    MYLIB_PATH "/usr/local/lib"
    SOURCES "main.cpp"
    INCLUDES "include" "include2"
)

# 函数返回值
# 定义函数
function(my_funtion3 returnValue)
    set(returnValue "hello world" PARENT_SCOPE)
    # set(${returnValue} "hello world" PARENT_SCOPE)
endfunction(my_funtion3)

# 使用函数
my_funtion3(result)
message("returnValue:${returnValue}")
message("result:${result}")

# 宏和函数的区别
# 定义函数和宏
function(my_funtion4 a)
    message("=========================MyFunction4=========================")
    if(a)
        message("a is true")
    else()
        message("a is false")
    endif()
endfunction(my_funtion4)

macro(my_macro a)
    message("=========================MyMacro=========================")
    if(a)
        message("a is true")
    else()
        message("a is false")
    endif()
endmacro(my_macro)

# 使用函数和函数
my_funtion4(hello)
my_macro(hello)