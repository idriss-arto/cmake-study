cmake_minimum_required(VERSION 3.31)
project(OpenCV_Test)
add_executable(OpenCV_Test main.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(OpenCV_Test ${OpenCV_LIBS} ) 

add_custom_command(
    TARGET OpenCV_Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:OpenCV_Test,SOURCE_DIR>/img"
        "$<TARGET_PROPERTY:OpenCV_Test,BINARY_DIR>/img"
)

## 参考B站视频
## https://www.bilibili.com/video/BV1HyoAYfEr9?spm_id_from=333.788.videopod.sections&vd_source=1a39362686408a3efeb7f263c0d8bb42

### 在项目根目录执行"vcpkg new --application"来创建vcpkg的两个文件（默认配置文件和项目清单）
### 在项目根目录执行"vcpkg add port opencv"来在项目清单里添加OpenCV的端口
### 在CMakePresets.json中设置工具链位置
