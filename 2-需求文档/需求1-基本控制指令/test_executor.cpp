#include <gtest/gtest.h>
#include "executor.h"

// 测试默认构造函数
TEST(ExecutorTest, DefaultConstructor) {
    Executor executor;
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'N');
}

// 测试初始化功能
TEST(ExecutorTest, Initialize) {
    Executor executor;
    executor.initialize(10, 20, 'E');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 10);
    EXPECT_EQ(y, 20);
    EXPECT_EQ(heading, 'E');
}

// 测试前进指令
TEST(ExecutorTest, MoveForward) {
    Executor executor;
    
    // 向北前进
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'N');
    
    // 向东前进
    executor.initialize(0, 0, 'E');
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'E');
    
    // 向南前进
    executor.initialize(0, 0, 'S');
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, -1);
    EXPECT_EQ(heading, 'S');
    
    // 向西前进
    executor.initialize(0, 0, 'W');
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, -1);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'W');
}

// 测试左转指令
TEST(ExecutorTest, TurnLeft) {
    Executor executor;
    
    // 北左转到西
    executor.executeCommand('L');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'W');
    
    // 西左转到南
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'S');
    
    // 南左转到东
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'E');
    
    // 东左转到北
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'N');
}

// 测试右转指令
TEST(ExecutorTest, TurnRight) {
    Executor executor;
    
    // 北右转到东
    executor.executeCommand('R');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'E');
    
    // 东右转到南
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'S');
    
    // 南右转到西
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'W');
    
    // 西右转到北
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(heading, 'N');
}

// 测试批量指令执行
TEST(ExecutorTest, BatchCommands) {
    Executor executor;
    
    // 测试指令序列：前进、右转、前进、左转、前进
    executor.executeBatchCommands("MRMLM");
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // M → (0,1,N)
    // R → (0,1,E)
    // M → (1,1,E)
    // L → (1,1,N)
    // M → (1,2,N)
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(heading, 'N');
}

// 测试更复杂的批量指令
TEST(ExecutorTest, ComplexBatchCommands) {
    Executor executor;
    executor.initialize(5, 5, 'E');
    
    // 测试指令序列：前进3次，左转，前进2次，右转，前进1次
    executor.executeBatchCommands("MMMLLMMR");
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(5,5,E)
    // MMM → (8,5,E)
    // LL → (8,5,W) (左转两次相当于右转两次)
    // MM → (6,5,W)
    // R → (6,5,N)
    EXPECT_EQ(x, 6);
    EXPECT_EQ(y, 5);
    EXPECT_EQ(heading, 'N');
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
