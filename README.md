# GUI版checker指南

* 语言：`c++`  with  `Qt`

* git仓库:  https://github.com/fangtiancheng/checker.git

使用指南：

1. **界面**

可执行文件位于`.\release\Checker.exe`

![gui](.\gui.png)

2. **按钮功能**

   2.1 结点数据类型——选择子图结点存储类型：`整形` int或者`字符串` std::string

   2.2 `清空`：           清空log输出；

   2.3 `导入原图`：    选择原图文件路径； **前置按钮**：结点数据类型

   2.4 `生成检查器`：生成检查器对象；     **前置按钮**：`导入原图`

   2.5 `检查`：          检查子图文件；         **前置按钮**：`生成检查器`

3. **输入**

   按下`导入原图`导入格式为

   ```
   <(VerType), (VerType), (double)>
   <(VerType)>
   ```

   的标准输入原图文件；

   按下`导入子图`导入格式为一行一个子图结点的标准待检查文件。

4. **输出与报错**

   ![output](.\output.png)

   2.3前置按钮缺失： Ver Type Unknow!

   2.4前置按钮缺失：open file error 

   2.5前置按钮缺失：Havn\'t New Checker 

   正常输出：

   ```
   total_weight = $total
   loss / total = $loss / $total
   ```

    `$total`表示原图边权和，`$loss`表示原图到子图的分割所损失的边权。

   报错：

   ```c++
   "format error"              // 输入格式错误
   "node $node number error"   // 分割后的图多出原图不存在的结点$node
   "double node '$node'"       // 分割后的图有重复结点$node
   "node don't exist"          // 原图有结点在子图中尚未出现
   ```

   