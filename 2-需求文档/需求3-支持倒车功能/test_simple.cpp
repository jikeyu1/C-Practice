#include <iostream>
#include "executor.h"

int main() {
    // 创建Executor实例
    Executor executor;
    int32_t x, y;
    char heading;
    
    // 测试1: 基本前进功能
    std::cout << "测试1: 基本前进功能\n";
    executor.getCurrentState(x, y, heading);
    std::cout << "初始状态: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行M指令后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试2: 倒车功能
    std::cout << "\n测试2: 倒车功能\n";
    executor.executeCommand('B');
    std::cout << "执行B指令后进入倒车状态\n";
    
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行M指令后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试3: 倒车状态下的转向
    std::cout << "\n测试3: 倒车状态下的转向\n";
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行L指令后(应右转): x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行R指令后(应左转): x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试4: 倒车+加速叠加状态
    std::cout << "\n测试4: 倒车+加速叠加状态\n";
    executor.executeCommand('F');
    std::cout << "执行F指令后进入倒车+加速状态\n";
    
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行M指令后(应后退2格): x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    // 测试5: 状态取消
    std::cout << "\n测试5: 状态取消\n";
    executor.executeCommand('B');
    executor.executeCommand('F');
    std::cout << "执行B和F指令后取消所有状态\n";
    
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    std::cout << "执行M指令后: x=" << x << ", y=" << y << ", heading=" << heading << std::endl;
    
    return 0;
}
