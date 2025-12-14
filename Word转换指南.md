# Word版实验报告转换指南

由于系统环境限制，直接生成的Word文档可能无法正常打开。以下是将Markdown格式的实验报告转换为Word格式的几种方法：

## 方法一：使用在线转换工具
1. 访问在线Markdown转Word工具：
   - https://markdownlivepreview.com/
   - https://pandoc.org/try/
   - https://www.markdowntoword.com/

2. 复制 `车辆执行器实验报告.md` 中的所有内容
3. 粘贴到在线工具中进行转换
4. 下载生成的Word文档

## 方法二：使用Microsoft Word 2016及以上版本
1. 打开Microsoft Word
2. 点击「文件」→「打开」
3. 选择「浏览」并找到 `车辆执行器实验报告.md`
4. Word会自动将Markdown转换为Word格式
5. 保存为.docx文件

## 方法三：使用Visual Studio Code插件
1. 安装VS Code的「Markdown All in One」插件
2. 打开 `车辆执行器实验报告.md` 文件
3. 按下 `Ctrl + Shift + P` 打开命令面板
4. 输入「Markdown: Export to HTML」导出为HTML文件
5. 用Word打开HTML文件并保存为.docx格式

## 方法四：使用Pandoc（需要安装）
1. 下载并安装Pandoc：https://pandoc.org/installing.html
2. 打开命令提示符
3. 执行命令：
   ```
   pandoc 车辆执行器实验报告.md -o 车辆执行器实验报告.docx
   ```

## 注意事项
1. 转换后的Word文档可能需要手动调整格式（如标题、代码块样式等）
2. 代码块在Word中可能需要设置等宽字体（如Consolas或Courier New）
3. 确保转换后的文档包含所有测试结果和代码示例

## 已生成的文件
- `车辆执行器实验报告.md`：完整的实验报告（Markdown格式）
- `googletest测试结果报告.md`：Google Test测试结果报告

您可以根据需要选择合适的方法将Markdown转换为Word格式。