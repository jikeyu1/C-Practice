#include "executor.h"

Executor::Executor() {
    // 默认初始化位置和朝向为（0,0,N）
    x_ = 0;
    y_ = 0;
    heading_ = 'N';
    is_accelerated_ = false; // 默认未加速
    is_reversing_ = false;   // 默认未倒车
}

void Executor::initialize(int32_t x, int32_t y, char heading) {
    x_ = x;
    y_ = y;
    heading_ = heading;
    is_accelerated_ = false; // 初始化时重置加速状态
    is_reversing_ = false;   // 初始化时重置倒车状态
}

void Executor::executeCommand(char command) {
    switch (command) {
        case 'F':
            // 切换加速状态
            is_accelerated_ = !is_accelerated_;
            break;
        case 'B':
            // 切换倒车状态
            is_reversing_ = !is_reversing_;
            break;
        case 'M':
            if (is_reversing_) {
                if (is_accelerated_) {
                    // 倒车+加速状态下，后退2格
                    moveBackward();
                    moveBackward();
                } else {
                    // 仅倒车状态下，后退1格
                    moveBackward();
                }
            } else {
                if (is_accelerated_) {
                    // 仅加速状态下，前进2格
                    moveForward();
                    moveForward();
                } else {
                    // 正常状态下，前进1格
                    moveForward();
                }
            }
            break;
        case 'L':
            if (is_reversing_) {
                if (is_accelerated_) {
                    // 倒车+加速状态下，先后退1格，然后右转90度
                    moveBackward();
                    turnRight();
                } else {
                    // 仅倒车状态下，右转90度
                    turnRight();
                }
            } else {
                if (is_accelerated_) {
                    // 仅加速状态下，先前进1格，然后左转90度
                    moveForward();
                    turnLeft();
                } else {
                    // 正常状态下，左转90度
                    turnLeft();
                }
            }
            break;
        case 'R':
            if (is_reversing_) {
                if (is_accelerated_) {
                    // 倒车+加速状态下，先后退1格，然后左转90度
                    moveBackward();
                    turnLeft();
                } else {
                    // 仅倒车状态下，左转90度
                    turnLeft();
                }
            } else {
                if (is_accelerated_) {
                    // 仅加速状态下，先前进1格，然后右转90度
                    moveForward();
                    turnRight();
                } else {
                    // 正常状态下，右转90度
                    turnRight();
                }
            }
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

void Executor::moveBackward() {
    // 根据当前朝向后退1格
    switch (heading_) {
        case 'N':
            y_ -= 1;
            break;
        case 'E':
            x_ -= 1;
            break;
        case 'S':
            y_ += 1;
            break;
        case 'W':
            x_ += 1;
            break;
    }
}
