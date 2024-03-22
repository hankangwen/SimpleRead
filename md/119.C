> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/cDfrNknVafaPQgnLLTdDOA)

**摘要**
------

在计算机程序的开发过程中，C# 中断模式是一个非常重要的概念。中断模式指的是我们可以暂停程序的执行，然后查看程序中的状态，也可以让程序继续行。这个功能非常有用，可以帮助程序员调试代码，发现和修复程序中的错误。

**正文**
------

断点

断点是源代码中自动进入中断模式的一个标记，当遇到析点的时候，程序会进入中断模式。

*   右击代码行，选择 breakpoint(断点)>insert breakpoint（插入断点)
    
*   光标定位到代码行，选择菜单上的 Debug(调试)->Toggle Breakpoint(切换断点)
    
*   光标定位到代码行，按下 F9 键，在比按下 F9 是取消断点
    
*   在需要添加晰点的行首位置，直接单击，再次单击取消断点
    

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdnp05ZdLicO8m6fdZW5NzHywSPr7GY9xO5FGVKVd9dyFTiaCXibcKTmuFjLgDJf1FibNrRHBot24Ucasg/640?wx_fmt=png&from=appmsg)

打开断点窗口

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdnp05ZdLicO8m6fdZW5NzHywm19Nuhs8peLlVuaW3xZusuka800oneZ4H760P0z4XI9KCib7QkyZR6A/640?wx_fmt=png&from=appmsg)

监视变量

在中断模下查看变量值最简单的方式，就是把鼠标指向源代码中的变量名，此时会出现一个工具提示，显示该变量的信息。

中断模式下的窗口（左下角），有三个选项卡

*   错误列表 - 程序运行中发生的所有错误的列表
    
*   局部变量 - 当前运行环境中所有的局部变量的值
    
*   监视 - 监视某个变量的值的变化
    

在上面的几个窗口中不但可以观视察变量值的变化，还可以直接去修改变量中存储的值

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdnp05ZdLicO8m6fdZW5NzHywvQL9MzZHQAAOZrnLZ3S6EX0MrU9EAhkUCHibNS5rAiaS76mrlTmztcEg/640?wx_fmt=png&from=appmsg)

监视窗口

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdnp05ZdLicO8m6fdZW5NzHyw2DQX4BCDEWKvtTQvibKibYhR54WvK4buczspqiaBT3xIib88H3mib54DC6A/640?wx_fmt=png&from=appmsg)

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdnp05ZdLicO8m6fdZW5NzHywqdJkYhMdaGOlMleJepjnI5JKp74WAfuAAicbwjvJXhZHdVkVIyyIHHQ/640?wx_fmt=png&from=appmsg)

单步执行代码

*   逐语句运行 F11 ，会进调用的过程
    
*   逐过程运行 F10，不会进调用的过程