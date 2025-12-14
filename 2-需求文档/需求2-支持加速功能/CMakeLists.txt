cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(ExecutorTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Google Test库
find_package(GTest REQUIRED)

# 添加头文件目录
include_directories(${GTEST_INCLUDE_DIRS})

# 创建Executor库
add_library(executor executor.cpp)

# 创建测试可执行文件
add_executable(test_executor test_executor.cpp)

# 链接库
target_link_libraries(test_executor executor ${GTEST_LIBRARIES} pthread)

# 添加测试
enable_testing()
add_test(NAME ExecutorTest COMMAND test_executor)
