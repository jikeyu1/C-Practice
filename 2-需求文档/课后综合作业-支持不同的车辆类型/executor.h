#pragma once

#include "vehicle.h"
#include <string>
#include <memory>

class Executor {
public:
    // 构造函数，默认创建跑车类型
    Executor(VehicleType type = VehicleType::SPORTS_CAR);
    
    // 初始化接口，设置车的位置和朝向
    void initialize(int32_t x, int32_t y, char heading);
    
    // 执行单个指令
    void executeCommand(char command);
    
    // 执行批量指令
    void executeBatchCommands(const std::string& commands);
    
    // 查询当前位置和朝向
    void getCurrentState(int32_t& x, int32_t& y, char& heading) const;
    
    // 切换车辆类型
    void setVehicleType(VehicleType type);
    
private:
    // 创建车辆对象
    void createVehicle(VehicleType type);
    
    std::unique_ptr<Vehicle> vehicle_; // 车辆对象指针
    VehicleType current_type_;         // 当前车辆类型
};
