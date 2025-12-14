#pragma once

#include <string>

// 车辆类型枚举
enum class VehicleType {
    SPORTS_CAR,
    BUS
};

// 车辆基类
class Vehicle {
public:
    virtual ~Vehicle() = default;
    
    // 设置位置和朝向
    void setPosition(int32_t x, int32_t y, char heading) {
        x_ = x;
        y_ = y;
        heading_ = heading;
    }
    
    // 获取当前位置和朝向
    void getPosition(int32_t& x, int32_t& y, char& heading) const {
        x = x_;
        y = y_;
        heading = heading_;
    }
    
    // 执行前进指令 - 纯虚函数，由子类实现
    virtual void moveForward() = 0;
    
    // 执行左转指令 - 纯虚函数，由子类实现
    virtual void turnLeft() = 0;
    
    // 执行右转指令 - 纯虚函数，由子类实现
    virtual void turnRight() = 0;
    
protected:
    int32_t x_ = 0;
    int32_t y_ = 0;
    char heading_ = 'N';
    
    // 辅助方法：实际的前进1格操作
    void actualMoveForward() {
        switch (heading_) {
            case 'N':
                y_ += 1;
                break;
            case 'E':
                x_ += 1;
                break;
            case 'S':
                y_ -= 1;
                break;
            case 'W':
                x_ -= 1;
                break;
        }
    }
    
    // 辅助方法：实际的左转90度操作
    void actualTurnLeft() {
        switch (heading_) {
            case 'N':
                heading_ = 'W';
                break;
            case 'W':
                heading_ = 'S';
                break;
            case 'S':
                heading_ = 'E';
                break;
            case 'E':
                heading_ = 'N';
                break;
        }
    }
    
    // 辅助方法：实际的右转90度操作
    void actualTurnRight() {
        switch (heading_) {
            case 'N':
                heading_ = 'E';
                break;
            case 'E':
                heading_ = 'S';
                break;
            case 'S':
                heading_ = 'W';
                break;
            case 'W':
                heading_ = 'N';
                break;
        }
    }
};

// 跑车类
class SportsCar : public Vehicle {
public:
    // 跑车的前进：1次移动2格
    void moveForward() override {
        actualMoveForward();
        actualMoveForward();
    }
    
    // 跑车的左转：先左转90度，再前进1格
    void turnLeft() override {
        actualTurnLeft();
        actualMoveForward();
    }
    
    // 跑车的右转：先右转90度，再前进1格
    void turnRight() override {
        actualTurnRight();
        actualMoveForward();
    }
};

// Bus类
class Bus : public Vehicle {
public:
    // Bus的前进：1次移动1格
    void moveForward() override {
        actualMoveForward();
    }
    
    // Bus的左转：先前进1格，再左转90度
    void turnLeft() override {
        actualMoveForward();
        actualTurnLeft();
    }
    
    // Bus的右转：先前进1格，再右转90度
    void turnRight() override {
        actualMoveForward();
        actualTurnRight();
    }
};
