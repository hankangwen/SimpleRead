> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_45894840/article/details/130004631?spm=1001.2100.3001.7377&utm_medium=distribute.pc_feed_blog_category.none-task-blog-classify_tag-14-130004631-null-null.nonecase&depth_1-utm_source=distribute.pc_feed_blog_category.none-task-blog-classify_tag-14-130004631-null-null.nonecase)

![](https://img-blog.csdnimg.cn/02e68bfd48fe49a7a951013dabe8f556.png)

题目连接：

```
https://play.picoctf.org/practice/challenge/361?originalEvent=72&page=3
```

我们是 windows 系统，所以点击 windows game 下载游戏

![](https://img-blog.csdnimg.cn/8098350dd9c845adaf779e3b7cf5dca5.png)

双击运行 pico.exe

![](https://img-blog.csdnimg.cn/f293a12178944ba9a3f5c4431d249a21.png)

屏幕上方的一串英文是叫我们找 flag，我在这个小地图里走来走去也没 flag，我上梯子后才发现突破点

![](https://img-blog.csdnimg.cn/9d0fa7f38eb54fab95e66bb484a18e21.png)

墙外有一个旗帜，但是我们无法出去，有空气墙，我们碰到旗帜就应该能拿到 flag 了

目前能拿到 flag 的思路：

```
使用Cheat Engine控制人物的坐标，直接修改坐标值，强制出去
使用DnSpy修改程序代码，使一开始运行游戏的时候就显示flag
```

这两个方式我都会演示

Cheat Engine
------------

Cheat Engine 是一款用于修改计算机游戏运行时内存中数值的开源工具。它可以搜索和修改游戏中的各种数值，如生命值、金钱、经验值等等  
下载地址：

```
https://www.cheatengine.org/
```

使用 ctrl+alt+tab 使游戏在后台运行，安装好 Cheat Engine 后双击运行

![](https://img-blog.csdnimg.cn/eec36f94135e45888fbad9f2463d424e.png)

点击左上角的图标，导入我们的游戏进程

![](https://img-blog.csdnimg.cn/14ebff1dc1b44015baf67dd7c93c6952.png)

导入之后就要搜索我们要修改的值了，在 unity 中，玩家的坐标是浮点数，我们可以一直移动来找到坐标值

![](https://img-blog.csdnimg.cn/1dbfded61baf4afcab72fb90e4163761.png)

由于我们不知道坐标，scantype 选择未知的值，valuetype 选择浮点数，然后点击 firstscan

![](https://img-blog.csdnimg.cn/c97700b822174a8abcd72310c092d016.png)

可以看到，他扫描到了 215168000 个值，太多了，现在来慢慢筛选，点击 scantype，选择增加值

![](https://img-blog.csdnimg.cn/a45ef4c3c87047b48e3ec5c157118630.png)

然后回到游戏，我们向前走几步

![](https://img-blog.csdnimg.cn/903bfbd0174f4d3d9121d978c2de5c44.png)

然后回到 Cheat Engine，点击 nextscan

![](https://img-blog.csdnimg.cn/90b1683ec04a4617b35565fea82ae134.png)

可以看到，值减少了很多，现在我们回到游戏，后退几步，回到 Cheat Engine，选择减少值

![](https://img-blog.csdnimg.cn/01f19bf0db764e1a8ac4a3d0d0702e04.png)

点击扫描后又少了一些值，一直重复这几个动作

![](https://img-blog.csdnimg.cn/f6449e8cdbdd4a758d1d89a4d2c8af56.png)

![](https://img-blog.csdnimg.cn/9e7717b18ec940259a19128d5a80750f.png)

现在值减少到了 6 千多个，然后选择不变的值，点击 repeat

![](https://img-blog.csdnimg.cn/e3a20ca2f71d484ab1c48d5ce74f9a4f.png)

点击 nestscan

![](https://img-blog.csdnimg.cn/7a06a875dc5b4d71afa0652b2f645aaa.png)

现在有 400 多个值，取消 repeat，回到游戏，继续重复上面的动作

![](https://img-blog.csdnimg.cn/d2a4334f50324a08bb6bb244028eef17.png)

现在只剩下 60 多个值了，我们点击 address 然后右下角的图标

![](https://img-blog.csdnimg.cn/cf1d9ec730934efb89214f9e8b212174.png)

在最下面我们随便勾选几个值，代表着冻结，然后回到游戏看能不能移动，如果不能就慢慢筛选，直到找到坐标的值

经过一段时间的筛选后，发现这个值就是坐标值，一旦我冻结了他，回到游戏就无法移动

![](https://img-blog.csdnimg.cn/24837c5396644896a8d68ba7561d10f9.png)

首先我们冻结这个值，然后双击，随便改一个值

![](https://img-blog.csdnimg.cn/9b1d7455fcf344c1a2c5ebb4b9c3a7ae.png)

注意别改太大了，大概这个值就能出去

![](https://img-blog.csdnimg.cn/a5753cfe52bc4c2db5fee19779c59491.png)

现在解禁函数，我们走到旗帜前

![](https://img-blog.csdnimg.cn/0808ec461c2e4f7ebd338b49c496e75a.png)

出现了 falg

```
picoCTF{WELCOME_TO_UNITY!!}
```

![](https://img-blog.csdnimg.cn/7d61617bfcb14ab59b488027ff7739d8.png)

DnSpy
-----

DnSpy 是一款开源的. NET 程序集反编译工具，它可以将. NET 程序集反编译成可读性较高的 C# 代码或者 IL 代码。DnSpy 不仅可以查看反编译后的代码，还可以编辑和调试. NET 程序集，包括修改程序集中的变量值、方法等等

下载地址：

```
https://github.com/dnSpy/dnSpy/releases/tag/v6.1.8
```

Assembly-CSharp.dll 是 unity 的程序集，所以我们反汇编这个文件就好了

![](https://img-blog.csdnimg.cn/f817205f0508473dae15f6c845e2b420.png)

双击打开 DnSpy，将 Assembly-CSharp.dll 拖入

![](https://img-blog.csdnimg.cn/3becefe4c28740df94eb2bed2722a186.png)

![](https://img-blog.csdnimg.cn/76722a0a13424041adac48c98c67a575.png)

在 APTX 里找到了一些有趣的函数

![](https://img-blog.csdnimg.cn/9b69684c32614bb480fed16bd761497d.png)

```
private void OnTriggerEnter(Collider collision)
{
	if (collision.gameObject == this.player)
	{
		this.Mysterious.SetActive(true);
	}
}
```

如果玩家碰撞了这个对象，就会输出一些东西，这应该就是 flag 的触发方式了

![](https://img-blog.csdnimg.cn/2ef8868a0f2b4685822a259bf2e9438b.png)

在下面，可以看到游戏启动的函数名次 Start

首先我们复制 this.Mysterious.SetActive(true); 这一行代码，然后右击 APTX

![](https://img-blog.csdnimg.cn/98401e1e927f4a1583135efdbb3adab8.png)

![](https://img-blog.csdnimg.cn/0b7dd1d279234ff9be7f6c2a47a8f009.png)

然后右击我们创建的 Start，选择编辑方法

![](https://img-blog.csdnimg.cn/fc4ea1fe2d7e43008eeb72a652a27221.png)

然后进行修改，使一进入游戏就输出 flag

![](https://img-blog.csdnimg.cn/0648f56906ac436086b2a8480af2736b.png)

![](https://img-blog.csdnimg.cn/52cc341640974dd0887f1bdc61d09bb6.png)

ctrl+shift+s 保存所有，双击打开游戏

![](https://img-blog.csdnimg.cn/a27cf7e26da94b2ca035145bb28e7ede.png)

一进去就能看见 flag 了