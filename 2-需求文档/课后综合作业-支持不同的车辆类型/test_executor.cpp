#include <gtest/gtest.h>
#include "executor.h"

// 测试跑车的前进指令
TEST(SportsCarTest, MoveForward) {
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 跑车前进：1次移动2格
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 2); // 跑车前进2格
    EXPECT_EQ(heading, 'N');
}

// 测试跑车的左转指令
TEST(SportsCarTest, TurnLeft) {
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 跑车左转：先左转90度，再前进1格
    executor.executeCommand('L');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 左转90度 → (0,0,W)
    // 前进1格 → (-1,0,W)
    EXPECT_EQ(x, -1);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'W');
}

// 测试跑车的右转指令
TEST(SportsCarTest, TurnRight) {
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 跑车右转：先右转90度，再前进1格
    executor.executeCommand('R');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 右转90度 → (0,0,E)
    // 前进1格 → (1,0,E)
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'E');
}

// 测试Bus的前进指令
TEST(BusTest, MoveForward) {
    Executor executor(VehicleType::BUS);
    
    // Bus前进：1次移动1格
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1); // Bus前进1格
    EXPECT_EQ(heading, 'N');
}

// 测试Bus的左转指令
TEST(BusTest, TurnLeft) {
    Executor executor(VehicleType::BUS);
    
    // Bus左转：先前进1格，再左转90度
    executor.executeCommand('L');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 前进1格 → (0,1,N)
    // 左转90度 → (0,1,W)
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'W');
}

// 测试Bus的右转指令
TEST(BusTest, TurnRight) {
    Executor executor(VehicleType::BUS);
    
    // Bus右转：先前进1格，再右转90度
    executor.executeCommand('R');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 前进1格 → (0,1,N)
    // 右转90度 → (0,1,E)
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'E');
}

// 测试批量指令执行
TEST(VehicleTest, BatchCommands) {
    // 测试跑车的批量指令
    Executor sportsCarExecutor(VehicleType::SPORTS_CAR);
    sportsCarExecutor.executeBatchCommands("MLR");
    int32_t x, y;
    char heading;
    sportsCarExecutor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // M → (0,2,N)
    // L → 左转90度 → (0,2,W)，前进1格 → (-1,2,W)
    // R → 右转90度 → (-1,2,N)，前进1格 → (-1,3,N)
    EXPECT_EQ(x, -1);
    EXPECT_EQ(y, 3);
    EXPECT_EQ(heading, 'N');
    
    // 测试Bus的批量指令
    Executor busExecutor(VehicleType::BUS);
    busExecutor.executeBatchCommands("MLR");
    busExecutor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // M → (0,1,N)
    // L → 前进1格 → (0,2,N)，左转90度 → (0,2,W)
    // R → 前进1格 → (-1,2,W)，右转90度 → (-1,2,N)
    EXPECT_EQ(x, -1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(heading, 'N');
}

// 测试车辆类型切换
TEST(VehicleTest, SwitchVehicleType) {
    Executor executor(VehicleType::SPORTS_CAR);
    
    // 初始为跑车，前进2格
    executor.executeCommand('M');
    
    // 切换为Bus
    executor.setVehicleType(VehicleType::BUS);
    
    // Bus前进1格
    executor.executeCommand('M');
    
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 跑车前进2格 → (0,2,N)
    // 切换为Bus后位置不变 → (0,2,N)
    // Bus前进1格 → (0,3,N)
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 3);
    EXPECT_EQ(heading, 'N');
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
