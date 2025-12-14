#include "executor.h"

Executor::Executor() {
    // 默认初始化位置和朝向为（0,0,N）
    x_ = 0;
    y_ = 0;
    heading_ = 'N';
}

void Executor::initialize(int32_t x, int32_t y, char heading) {
    x_ = x;
    y_ = y;
    heading_ = heading;
}

void Executor::executeCommand(char command) {
    switch (command) {
        case 'M':
            moveForward();
            break;
        case 'L':
            turnLeft();
            break;
        case 'R':
            turnRight();
            break;
        // 其他指令不处理，根据约束，传入的参数都是合法的
    }
}

void Executor::executeBatchCommands(const std::string& commands) {
    for (char command : commands) {
        executeCommand(command);
    }
}

void Executor::getCurrentState(int32_t& x, int32_t& y, char& heading) const {
    x = x_;
    y = y_;
    heading = heading_;
}

void Executor::turnLeft() {
    // 左转90度：N→W→S→E→N
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

void Executor::turnRight() {
    // 右转90度：N→E→S→W→N
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

void Executor::moveForward() {
    // 根据当前朝向前进1格
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
