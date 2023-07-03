cmake_minimum_required(VERSION 3.10)

# set the project name
project(CT VERSION 0.0.1 LANGUAGES CXX)

# 生成compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置c++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置目标文件的目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# 设置编译参数
add_compile_options(-g -Wall)

# 设置头文件路径
include_directories("third")

# 框架源码
add_subdirectory(src)
# 测试代码
add_subdirectory(test)