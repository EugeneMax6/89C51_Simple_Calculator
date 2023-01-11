# 89C51_Simple_Calculator

## 简易计算器

简易的计算器应能够显示按键所对应运算数，具有加、减、乘、除四则运算功能，并对所计算的结果进行显示。 因此，该计算器应至少具有LED/LCD显示屏、4×4的矩阵键盘，以实现数字的输入和输出。此外，应具有开关以控制其运行状态和显示其运行状态的LED灯。

使用Proteus、Keil程序编写，基于51单片机，大学单片机课程的一个普通大作业，功能不多但是基本功能都差不多完善了。

可能有少许bug，有空再来改改吧。

使用Proteus选择89C51，画好电路然后用Keil编写程序并导出HEX文件，再将HEX文件导入Proteus的MCU里即可。

需要相关ppt的也可以给我发邮件，拯救一下大家的期末大作业。(前提是我没删掉哈哈)

E-Mail：eugenemax6@outlook.com

## **A simple caculator based on 89C51**

Using Proteus and Keil for coding, the simple calculator is based on 89C51 MCU.

It is one of my homeworks of MCU course.

It is a simple project but it is instructive, especially the LCD1602's drivers.

**Function:** add / subtract / multiply / divide

There may be some bugs which I have neglected.

## 电路图片 / The Picture of the Circuit

The file of Protues project is 计算器.pdsprj

Main components: LCD1602 / KEYPAD_SMALLCACL / LED

![计算器](https://raw.githubusercontent.com/EugeneMax6/89C51_Simple_Calculator/124017de445cd57565c9cfd3637db0b2c43eed16/%E8%AE%A1%E7%AE%97%E5%99%A8.SVG)

## 功能展示 / Function Display （With GIF Picture)

![display](https://raw.githubusercontent.com/EugeneMax6/89C51_Simple_Calculator/main/display.gif)

## 其他 / Something more

这个小程序是在学习单片机的初期做的，由于缺乏汇编语言的知识，因此只能用C语言编写程序然后用Keil编译，总的来说程序写的很简单，也有很多写的不好的地方，比如解决一些异常直接用了穷举法，但是对于一些初学者，尤其是对于C语言都不太熟悉的来说，这种方式上手较快。

深入地学习了汇编语言以及编译原理后，我对于这些程序有了更深刻的认识，不过也懒得改啦。

MCU、嵌入式之类的对于我来说还挺难的，主要是我硬件知识的水平不够高，有些东西认知不足，因此做起来往往会遇到很多困难。



This program was made at the beginning of learning MCU. At first, due to the lack of knowledge of assembly language, I could only use C.

There are a lot of things that are not concise in the program, which I feel more than sorry.

