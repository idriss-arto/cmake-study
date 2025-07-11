
cmake_minimum_required(VERSION 3.31)
project(MyDemo VERSION 0.1.0)

add_library(DemoLib INTERFACE)

# 实现跨平台标准化安装路径的关键模块，用于设置自制库安装路径和目录变量。
include(GNUInstallDirs)


#          变量	                              指向路径	                      是否随当前cmake文件所在位置变化
#   PROJECT_SOURCE_DIR	      				顶层项目目录	            				否
# CMAKE_CURRENT_SOURCE_DIR	     当前处理的 CMakeLists.txt 所在目录	                   	 是
target_include_directories(
	DemoLib 
	INTERFACE 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
) 


# find_package
## find_package 适用于CMake支持的第三方库
## 因为纯CMake实现，所以可以跨平台使用
## 底层会先找到库的查找模块，如这里是 FindOpenSSL.cmake
## 然后定义导入目标，如这里的 OpenSSL::SSL 和 OpenSSL::Crypto
## 最后将导入目标链接到 DemoLib 库上
## find_package还有另一种实现机制，通过配置文件来查找库。
## 这种方式适用于使用自制库，或者库作者提供了配置文件的情况。
## 具体使用例子可见详见simple中的cmake文件
## 使用配置文件查找库需要在find_package中指定CONFIG选项
## 安装自制库步骤如下：
### 1.生成配置文件
### 2.导出目标
### 3.安装复制文件

# pkg_check_modules
## pkg_check_modules适用于没有CMake支持的第三方库
## 需要安装pkg-config工具
## 但在windows中需要额外配置
## 使用示例见分布式kv项目的顶层cmake文件

# 依赖
find_package(OpenSSL REQUIRED)
if(NOT OPENSSL_FOUND)
    message(SEND_ERROR  "OpenSSL not found") 
endif()

target_link_libraries(DemoLib INTERFACE OpenSSL::SSL OpenSSL::Crypto OpenSSL::applink)
if(WIN32)
    target_link_libraries(DemoLib INTERFACE wsock32 ws2_32 crypt32)
endif()



# 测试
enable_testing()
## EXCLUDE_FROM_ALL使得test目录不会被包含在默认构建
## 只有显式请求时（如 make test_target 或 ctest）才会构建
add_subdirectory(test EXCLUDE_FROM_ALL)






# 以下为导出和安装自制库的步骤
## 一、生成配置文件
### 1. 版本文件生成
### 功能：生成一个版本文件，用于支持 CMake 的 find_package 命令检查版本兼容性。
### 参数：
### VERSION ${PROJECT_VERSION}：使用项目版本号（如 1.2.3）。
### COMPATIBILITY SameMajorVersion：声明兼容性规则为 “主版本相同即兼容”（如 1.2.3 和 1.5.0 兼容，但 2.0.0 不兼容）。
### 输出文件：${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake。
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

###        变量	                       指向路径	                   是否可变	                   典型用途
### PROJECT_SOURCE_DIR	  项目源代码的根目录（如 myproject/）	    固定不变	     引用源码文件（如头文件、配置模板）
### PROJECT_BINARY_DIR	构建产物的根目录（如 myproject/build/）	 取决于构建目录	 存放编译生成的文件（如可执行文件、中间文件）

### 2. 配置文件模板处理
### 功能：将模板文件 Config.cmake.in 处理为实际的配置文件，替换其中的变量引用。
### 参数：
### 源模板：${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in（源码中的模板文件）。
### 输出路径：${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake（构建目录中的临时文件）。
### 安装路径：${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake（默认对应 /usr/local/share/项目名/cmake）。
configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION
	${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)



## 二、导出目标 
### 3. 导出目标（Export Targets）
### 功能：将 DemoLib 库添加到导出列表，以便其他项目通过 CMake 引用。
### 参数：
### TARGETS DemoLib：指定要导出的目标（库或可执行文件）。
### EXPORT ${PROJECT_NAME}_Targets：指定导出集的名称（如 MyProject_Targets）。
### install(TARGETS DemoLib EXPORT ${PROJECT_NAME}_Targets)
install(TARGETS DemoLib EXPORT ${PROJECT_NAME}_Targets)

### 4. 安装导出文件
### 功能：生成并安装一个 CMake 文件，用于描述导出的目标（如库的位置、依赖等）。
### 参数：
### EXPORT ${PROJECT_NAME}_Targets：导出之前通过 install(TARGETS ...) 注册的目标。
### FILE ${PROJECT_NAME}Targets.cmake：输出文件名（如 MyProjectTargets.cmake）。
### NAMESPACE ${PROJECT_NAME}::：为目标添加命名空间（如 MyProject::DemoLib）。
### DESTINATION ...：安装路径（同上，默认 /usr/local/share/项目名/cmake）。
install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


## 三、安装复制文件
### 5. 安装头文件
### 功能：将头文件安装到系统 include 目录。
### 参数：
### FILES ...：指定要安装的文件（如 httplib.h）。
### TYPE INCLUDE：等效于 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}（默认 /usr/local/include）。
### install(FILES "${PROJECT_SOURCE_DIR}/include/httplib.h" TYPE INCLUDE)

### 6. 安装配置文件
### 功能：安装之前生成的配置文件和版本文件。
### 参数：
### FILES ...：指定要安装的文件（Config.cmake 和 ConfigVersion.cmake）。
### DESTINATION ...：安装路径（默认 /usr/local/share/项目名/cmake）。
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)








