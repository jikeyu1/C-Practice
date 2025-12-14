#pragma once

#include <string>

class Executor {
public:
    // 构造函数，默认初始化位置和朝向为（0,0,N）
    Executor();
    
    // 初始化接口，设置车的位置和朝向
    void initialize(int32_t x, int32_t y, char heading);
    
    // 执行单个指令
    void executeCommand(char command);
    
    // 执行批量指令
    void executeBatchCommands(const std::string& commands);
    
    // 查询当前位置和朝向
    void getCurrentState(int32_t& x, int32_t& y, char& heading) const;
    
private:
    int32_t x_;
    int32_t y_;
    char heading_;
    bool is_accelerated_; // 加速状态标志
    bool is_reversing_;   // 倒车状态标志
    
    // 辅助函数：左转90度
    void turnLeft();
    
    // 辅助函数：右转90度
    void turnRight();
    
    // 辅助函数：前进1格
    void moveForward();
    
    // 辅助函数：后退1格
    void moveBackward();
    
    // 执行掉头指令
    void executeTurnRound();
};
