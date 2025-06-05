# 最小版本号要求
cmake_minimum_required(VERSION 3.31)

# 禁用编译器检测输出
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# 项目名称
project(VariableLesson)

# 参数设置
# set(myVar1 "hello  world")
# set(myVar2 hello  world)
# message("myVar1 = ${myVar1}")
# message("myVar2 = " ${myVar2})

# 变量带换行的情况，以及 "打印内容" 和 [[打印内容]] 的区别
# set(myVar3 secondLine)
# set(multiLine1 "
# firstLine,
# ${myVar3}
# ")
# set(multiLine2 [[
# firstLine,
# ${myVar3}
# ]])
# message("multiLine1 = ${multiLine1}")
# message("multiLine2 = ${multiLine2}")

# 环境变量设置，只是临时添加
# set(ENV(PATH) "$ENV{PATH}:/mydir")

# 普通变量 vs 缓存变量，
# 有同名的普通变量和缓存变量时，用变量名引用的是普通变量
set(myVar4 "normal variable")
set(myVar4 "cache variable" CACHE STRING "备注" FORCE)
message(STATUS "myVar4 = " ${myVar4})
unset(myVar4)
message(STATUS "myVar4 = " ${myVar4})

# 缓存变量是否应用强制更新的区别
set(myVar4 "new cache variable" CACHE STRING "备注")
message(STATUS "without FORCE, new myVar4 = " ${myVar4})
set(myVar4 "new cache variable" CACHE STRING "备注" FORCE)
message(STATUS "with FORCE, new myVar4 = " ${myVar4})

# 变量作用域
# set(myVar5 cat)
# block()
#   set(myVar5 dog)
#   message(STATUS "inblock myVar5 = ${myVar5}")
# endblock()
# message(STATUS "outblock myVar5 = ${myVar5}")

# set(myVar6 cat)
# block()
#   set(myVar6 dog PARENT_SCOPE)
#   message(STATUS "inblock myVar6 = ${myVar6}")
# endblock()
# message(STATUS "outblock myVar6 = ${myVar6}")

# set(myVar7 cat)
# block(SCOPE_FOR VARIABLES PROPAGATE myVar7)
#   set(myVar7 dog)
#   message(STATUS "inblock myVar7 = ${myVar7}")
# endblock()
# message(STATUS "outblock myVar7 = ${myVar7}")

