# Executor组件支持不同的车辆类型 - 课后综合作业

## 设计思路

本作业采用面向对象的设计模式，通过继承和多态实现了支持不同车辆类型的Executor组件。主要设计思路如下：

1. **抽象基类设计**：定义`Vehicle`基类，包含通用的位置和朝向管理，以及纯虚函数接口
2. **多态实现**：不同车辆类型（跑车、Bus）继承自`Vehicle`基类，重写指令处理方法
3. **工厂模式**：Executor根据车辆类型创建相应的车辆对象
4. **封装性**：Executor组件对外提供统一的接口，隐藏内部车辆类型的实现细节

## 代码结构

```
课后综合作业-支持不同的车辆类型/
├── vehicle.h          # 车辆基类和具体车辆类型实现
├── executor.h         # Executor组件接口
├── executor.cpp       # Executor组件实现
├── test_executor.cpp  # 单元测试用例
├── CMakeLists.txt     # CMake构建脚本
└── README.md          # 项目说明文档
```

## 功能实现

### 车辆类型

1. **跑车（SportsCar）**
   - M指令：前进2格
   - L指令：先左转90度，再前进1格
   - R指令：先右转90度，再前进1格

2. **Bus**
   - M指令：前进1格
   - L指令：先前进1格，再左转90度
   - R指令：先前进1格，再右转90度

### Executor组件

- **初始化功能**：设置车辆的位置和朝向
- **指令执行**：支持单指令和批量指令执行
- **状态查询**：获取当前位置和朝向
- **车辆类型切换**：支持在运行时切换不同的车辆类型

## 构建和运行测试

### 使用CMake构建

1. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```

2. 运行CMake生成构建文件：
   ```bash
   cmake ..
   ```

3. 编译项目：
   ```bash
   make
   ```

4. 运行测试：
   ```bash
   ./test_executor
   ```

### 使用g++直接编译

```bash
g++ -std=c++14 -o test_executor test_executor.cpp executor.cpp -lgtest -lpthread
./test_executor
```

## 测试用例

测试用例覆盖了以下场景：

1. 跑车的前进、左转、右转指令
2. Bus的前进、左转、右转指令
3. 批量指令执行
4. 车辆类型切换

## 设计优点

1. **可扩展性**：新的车辆类型可以通过继承`Vehicle`基类轻松添加
2. **灵活性**：支持在运行时切换车辆类型
3. **封装性**：Executor对外提供统一接口，隐藏内部实现细节
4. **可测试性**：每个车辆类型可以独立测试
5. **代码复用**：通用功能在基类中实现，避免代码重复

## 示例代码

```cpp
// 创建Executor，初始为跑车类型
Executor executor(VehicleType::SPORTS_CAR);

// 执行指令
executor.executeCommand('M'); // 跑车前进2格

// 切换为Bus类型
executor.setVehicleType(VehicleType::BUS);

// 执行指令
executor.executeCommand('M'); // Bus前进1格

// 获取当前状态
int32_t x, y;
char heading;
executor.getCurrentState(x, y, heading);
```
