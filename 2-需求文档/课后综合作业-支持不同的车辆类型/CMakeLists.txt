cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(VehicleExecutorTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Google Test库
find_package(GTest REQUIRED)

# 添加头文件目录
include_directories(${GTEST_INCLUDE_DIRS})

# 创建Vehicle库
add_library(vehicle vehicle.h)
set_target_properties(vehicle PROPERTIES LINKER_LANGUAGE CXX)

# 创建Executor库
add_library(executor executor.cpp)
target_link_libraries(executor vehicle)

# 创建测试可执行文件
add_executable(test_executor test_executor.cpp)
target_link_libraries(test_executor executor ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

# 添加测试
enable_testing()
add_test(NAME VehicleExecutorTest COMMAND test_executor)
