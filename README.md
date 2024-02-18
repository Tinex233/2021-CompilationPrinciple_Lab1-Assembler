# SCNU 2021 Compilation Principle Lab1: Assembler
***This is a converter that allows for converting NFA to DFA, minimizing DFA, and so on.***  

---
## Requirements
Qt 5.9.9   
c++11

   
## Usages
The three buttons on the top left side are used to respectively import a .txt file, analyze the content, and clear the text content. The two buttons on the top right side can be used to save the analysis results and clear the result content.
Enter C++ statements in the left text editor, click the analyze button, and the results will be displayed in the right text editor.

---
# 华南师范大学编译原理实验1——单词拼装器

## 一、必做内容

1. 把C++源代码中的各类单词（记号）进行拼装分类。   
C++语言包含了几种类型的单词（记号）：标识符，关键字，数（包括整数、浮点数），字符串、注释、特殊符号（分界符）和运算符号等【详细的单词类别及拼装规则见另外的文件说明】。   
2. 要求应用程序应为Windows界面。   
3. 打开一个C++源文件，列出所有可以拼装的单词（记号）。   
4. 应该书写完善的软件设计文档。   
 

## 二、选做内容

预编译系统的实现----打造具有个人风格的XC++语言（单词替换）   
   
1. 描述具有风格的XC++的单词有哪些，分别对应原C++的是哪些单词。   
2. 实现这个单词替换方案。   
3. 需要按上述1,2的内容书写相应的设计文档。   


## 三、完成时间
4周

## 四、上交方法
通过砺儒云课堂提交

## 五、完成方式
每个学生自行独立完成。

## 六、实验实现的编程语言
C++程序设计语言

## 七、运行效果样本

### C++源程序：   

Test.cpp   
```cpp
#include<iostream.h>   
main()   
{   
   int i;   
   cin>>i;   
   if (i>3) cout<<"ok";   
}   
```

### 扫描结果：   
\#     特殊符号   
Include    关键字   
<iostream. h>    特殊符号   
main    关键字   
(        特殊符号   
)        特殊符号   
{      特殊符号   
int    关键字   
 i      标识符   
;       特殊符号   
cin   关键字   
\>>    特殊符号   
i       标识符   
;       特殊符号   
if      关键字     
(       特殊符号   
i       标识符   
\>      特殊符号   
3       数   
)        特殊符号   
cout   关键字   
<<     特殊符号   
“ok”   串   
;        特殊符号   
}        特殊符号   

目前如“123L”等部分数字上或进制上的分析尚待解决。   
界面示例：
![image](https://github.com/Tinex233/2021-CompilationPrinciple_Lab1-Assembler/assets/128806135/54954780-0550-4a00-8798-e922b39c08d6)


