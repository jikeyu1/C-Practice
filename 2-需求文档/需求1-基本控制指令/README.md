# Executor组件 - 需求1实现

## 项目结构
```
需求1-基本控制指令/
├── executor.h          # Executor类头文件，定义接口
├── executor.cpp        # Executor类实现文件
├── test_executor.cpp   # 单元测试用例
├── CMakeLists.txt      # CMake构建脚本
└── README.md           # 项目说明文档
```

## 功能实现

Executor组件实现了智能车的基本控制指令，包括：

1. **初始化功能**：设置车的位置(x, y)和朝向(heading)
2. **移动指令**：
   - M：前进1格
   - L：左转90度
   - R：右转90度
3. **批量指令执行**：支持连续执行多个指令
4. **状态查询**：获取车当前的位置和朝向

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
g++ -std=c++11 -o test_executor test_executor.cpp executor.cpp -lgtest -lpthread
./test_executor
```

## 测试用例

测试用例覆盖了以下场景：

1. 默认构造函数
2. 初始化功能
3. 前进指令（四个方向）
4. 左转指令（连续左转）
5. 右转指令（连续右转）
6. 批量指令执行
7. 复杂批量指令执行

## 设计说明

1. **接口设计**：提供了简洁明了的对外接口，便于使用
2. **封装性**：将内部实现细节隐藏，只暴露必要的接口
3. **可扩展性**：便于后续添加更多功能，如加速、倒车、掉头等
4. **测试驱动开发**：先设计测试用例，再实现功能，确保代码质量
