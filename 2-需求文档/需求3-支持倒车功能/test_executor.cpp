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

// 测试加速功能 - F指令切换加速状态
TEST(ExecutorTest, AccelerateCommand) {
    Executor executor;
    
    // 初始状态应为未加速
    // 执行F指令后进入加速状态
    executor.executeCommand('F');
    
    // 加速状态下前进，应前进2格
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 2); // 加速状态下前进2格
    EXPECT_EQ(heading, 'N');
    
    // 再次执行F指令，退出加速状态
    executor.executeCommand('F');
    
    // 正常状态下前进，应前进1格
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 3); // 正常状态下前进1格
    EXPECT_EQ(heading, 'N');
}

// 测试加速状态下的左转指令
TEST(ExecutorTest, AcceleratedTurnLeft) {
    Executor executor;
    executor.executeCommand('F'); // 进入加速状态
    
    // 加速状态下左转：先前进1格，然后左转90度
    executor.executeCommand('L');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 加速状态下L指令：前进1格 → (0,1,N)，然后左转 → (0,1,W)
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'W');
}

// 测试加速状态下的右转指令
TEST(ExecutorTest, AcceleratedTurnRight) {
    Executor executor;
    executor.executeCommand('F'); // 进入加速状态
    
    // 加速状态下右转：先前进1格，然后右转90度
    executor.executeCommand('R');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // 加速状态下R指令：前进1格 → (0,1,N)，然后右转 → (0,1,E)
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'E');
}

// 测试包含加速指令的批量指令
TEST(ExecutorTest, BatchCommandsWithAcceleration) {
    Executor executor;
    
    // 测试指令序列：F（加速）、M（前进2格）、L（前进1格+左转）、F（取消加速）、M（前进1格）
    executor.executeBatchCommands("FMLFM");
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // F → 进入加速状态
    // M → 前进2格 → (0,2,N)
    // L → 前进1格 → (0,3,N)，左转 → (0,3,W)
    // F → 取消加速状态
    // M → 前进1格 → (-1,3,W)
    EXPECT_EQ(x, -1);
    EXPECT_EQ(y, 3);
    EXPECT_EQ(heading, 'W');
}

// 测试多次切换加速状态
TEST(ExecutorTest, MultipleAccelerationToggle) {
    Executor executor;
    
    // F → 加速
    // F → 取消加速
    // F → 加速
    // F → 取消加速
    executor.executeBatchCommands("FFFF");
    
    // 最终应处于未加速状态
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 正常状态下前进1格
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'N');
}

// 测试倒车功能 - B指令切换倒车状态
TEST(ExecutorTest, ReverseCommand) {
    Executor executor;
    
    // 执行B指令后进入倒车状态
    executor.executeCommand('B');
    
    // 倒车状态下前进，应后退1格
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, -1); // 倒车状态下后退1格
    EXPECT_EQ(heading, 'N');
    
    // 再次执行B指令，退出倒车状态
    executor.executeCommand('B');
    
    // 正常状态下前进，应前进1格
    executor.executeCommand('M');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0); // 正常状态下前进1格，回到原点
    EXPECT_EQ(heading, 'N');
}

// 测试倒车状态下的转向指令
TEST(ExecutorTest, ReversedTurns) {
    Executor executor;
    executor.executeCommand('B'); // 进入倒车状态
    
    // 倒车状态下左转：应右转90度
    executor.executeCommand('L');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'E'); // 倒车状态下L指令：右转90度
    
    // 倒车状态下右转：应左转90度
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);
    EXPECT_EQ(heading, 'N'); // 倒车状态下R指令：左转90度，回到初始朝向
}

// 测试倒车+加速叠加状态
TEST(ExecutorTest, ReverseAccelerateCombined) {
    Executor executor;
    executor.executeCommand('B'); // 进入倒车状态
    executor.executeCommand('F'); // 进入加速状态
    
    // 倒车+加速状态下前进，应后退2格
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, -2); // 倒车+加速状态下后退2格
    EXPECT_EQ(heading, 'N');
    
    // 倒车+加速状态下左转：先后退1格，然后右转90度
    executor.executeCommand('L');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, -3); // 后退1格
    EXPECT_EQ(heading, 'E'); // 右转90度
    
    // 倒车+加速状态下右转：先后退1格，然后左转90度
    executor.executeCommand('R');
    executor.getCurrentState(x, y, heading);
    EXPECT_EQ(x, -1); // 后退1格（当前朝向E，后退即x减1）
    EXPECT_EQ(y, -3);
    EXPECT_EQ(heading, 'N'); // 左转90度
}

// 测试包含倒车指令的批量指令
TEST(ExecutorTest, BatchCommandsWithReverse) {
    Executor executor;
    
    // 测试指令序列：B（倒车）、M（后退1格）、L（右转90度）、F（加速）、M（后退2格）
    executor.executeBatchCommands("BMLFM");
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 预期结果：
    // 初始状态：(0,0,N)
    // B → 进入倒车状态
    // M → 后退1格 → (0,-1,N)
    // L → 右转90度 → (0,-1,E)
    // F → 进入加速状态（现在是倒车+加速）
    // M → 后退2格 → (-2,-1,E)（朝向E，后退即x减2）
    EXPECT_EQ(x, -2);
    EXPECT_EQ(y, -1);
    EXPECT_EQ(heading, 'E');
}

// 测试多次切换倒车状态
TEST(ExecutorTest, MultipleReverseToggle) {
    Executor executor;
    
    // B → 倒车
    // B → 取消倒车
    // B → 倒车
    // B → 取消倒车
    executor.executeBatchCommands("BBBB");
    
    // 最终应处于未倒车状态
    executor.executeCommand('M');
    int32_t x, y;
    char heading;
    executor.getCurrentState(x, y, heading);
    
    // 正常状态下前进1格
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
    EXPECT_EQ(heading, 'N');
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
