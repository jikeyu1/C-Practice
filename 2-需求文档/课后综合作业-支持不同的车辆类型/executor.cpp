#include "executor.h"

Executor::Executor(VehicleType type) {
    current_type_ = type;
    createVehicle(type);
}

void Executor::createVehicle(VehicleType type) {
    switch (type) {
        case VehicleType::SPORTS_CAR:
            vehicle_ = std::make_unique<SportsCar>();
            break;
        case VehicleType::BUS:
            vehicle_ = std::make_unique<Bus>();
            break;
        // 可以扩展更多车辆类型
    }
}

void Executor::initialize(int32_t x, int32_t y, char heading) {
    vehicle_->setPosition(x, y, heading);
}

void Executor::executeCommand(char command) {
    switch (command) {
        case 'M':
            vehicle_->moveForward();
            break;
        case 'L':
            vehicle_->turnLeft();
            break;
        case 'R':
            vehicle_->turnRight();
            break;
        // 其他指令可以在这里扩展
    }
}

void Executor::executeBatchCommands(const std::string& commands) {
    for (char command : commands) {
        executeCommand(command);
    }
}

void Executor::getCurrentState(int32_t& x, int32_t& y, char& heading) const {
    vehicle_->getPosition(x, y, heading);
}

void Executor::setVehicleType(VehicleType type) {
    if (current_type_ != type) {
        // 保存当前位置和朝向
        int32_t x, y;
        char heading;
        vehicle_->getPosition(x, y, heading);
        
        // 创建新类型的车辆
        createVehicle(type);
        current_type_ = type;
        
        // 恢复位置和朝向
        vehicle_->setPosition(x, y, heading);
    }
}
