#include <iostream>
#include "2-需求文档\课后综合作业-支持不同的车辆类型\executor.h"

void testSportsCar() {
    std::cout << "=== 测试跑车功能 ===\n";
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 测试前进指令
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    std::cout << "跑车执行指令 'M' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试左转指令
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    std::cout << "跑车执行指令 'L' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试右转指令
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    std::cout << "跑车执行指令 'R' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    std::cout << std::endl;
}

void testBus() {
    std::cout << "=== 测试公交车功能 ===\n";
    Executor executor(VehicleType::BUS);
    
    // 测试前进指令
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    std::cout << "公交车执行指令 'M' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试左转指令
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    std::cout << "公交车执行指令 'L' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试右转指令
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    std::cout << "公交车执行指令 'R' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    std::cout << std::endl;
}

void testBatchCommands() {
    std::cout << "=== 测试批量指令 ===\n";
    
    // 测试跑车的批量指令
    Executor sportsCarExecutor(VehicleType::SPORTS_CAR);
    sportsCarExecutor.executeBatchCommands("MLR");
    int32_t x, y;
    char heading;
    sportsCarExecutor.getCurrentState(x, y, heading);
    std::cout << "跑车执行批量指令 'MLR' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试公交车的批量指令
    Executor busExecutor(VehicleType::BUS);
    busExecutor.executeBatchCommands("MLR");
    busExecutor.getCurrentState(x, y, heading);
    std::cout << "公交车执行批量指令 'MLR' 后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    std::cout << std::endl;
}

void testVehicleSwitch() {
    std::cout << "=== 测试车辆类型切换 ===\n";
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 初始为跑车，前进1次（2格）
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    std::cout << "跑车前进1次后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 切换为公交车
    executor.setVehicleType(VehicleType::BUS);
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    std::cout << "切换为公交车并前进1次后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    std::cout << std::endl;
}

int main() {
    std::cout << "C++课程实验 - 车辆执行器测试\n";
    std::cout << "================================\n";
    
    testSportsCar();
    testBus();
    testBatchCommands();
    testVehicleSwitch();
    
    std::cout << "所有测试完成！\n";
    
    return 0;
}