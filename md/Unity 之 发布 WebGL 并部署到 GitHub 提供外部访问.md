> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/a0GP6uzm4vOik4LM0HK8VA)

**不用服务器也能发布页游？那还不赶紧来试试**

**(Unity | WebGL | GitHub | 游戏内嵌网页）**

前言

> 自己发布游戏到网页是什么体验？本文教你发布自己的网页游戏，还不赶紧试试，让好友也能在浏览器上玩到自己的游戏

点击试玩：2048 化学元素版

效果展示： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyrbWKibS9IyezzYycBDUuPicUVkRSFakaBZ9UNRibl14debfO79WR5dj6w/640?wx_fmt=png)

PS：分辨率是可以自定义的 ，我这个为什么做这么小，后面会说~

一，准备工作
======

1.1 Unity 环境配置
==============

打开 “Unity Hub”，左侧安装目录，找到需要打 WebGL 包的已安装版本 Unity，点击三个点 “...”，选择添加模块：

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELy4T5wbHtRSAxGdgSN4ZACdLcaUia5c4dB86LHrybOLUYPichib4HloEFcw/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELylRGDQIJLLUPXUHH7rw3CVY3yMqhicSWKIRjKCia5glptLMRHRywAa7VQ/640?wx_fmt=png)

选择 “WebGL Build Support”，点击完成，等待安装完成即可。

1.2 GitHub 相关操作
===============

1.  在 GitHub 上创建远程仓库
    
    登陆 GitHub 官网（打不开的话需要 Fan 墙），点击右上角 “+”，选择 “New repository” 然后弹出如下界面，进行创建项目配置，图中红框分别表示：项目名称，设置为共开（这样别人才能访问到），带描述文件，最后点击下面的创建按钮：
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyXIr2mwTBF5F3picmX1kIaXQRVHXFZsZLGoYxE08YZ6Yj34VoHq03mjQ/640?wx_fmt=png)

2.  将远程仓库克隆到本地
    
    这就不多说了，使用你的习惯的任何方式都可以，我用的是 “Source Tree“，操作如下：在网页中复制 1 中创建好的 URL，“Source Tree“中点击” 新建“ 弹窗如下图，按图填写完成，点击克隆即可：
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyxs4BqQJpVtFzEybJlAPzVgNHQVf4dAc0OXUs07Bjg72HY2xV8bEsSg/640?wx_fmt=png)

3.  克隆成功
    
    克隆成功后会在你填写的目录中看到有一个”README.md“的文件，若你的电脑设置开启了” 显示隐藏文件 “，应该还有”.git“这样的文件。
    

二，发布 WebGL
==========

2.1 切换目标平台
----------

两种方式：1 是打开时切换平台，2 是打开后在工程中切换

PS: 若你还没有预发布项目，只想测试发布 WebGl 功能，那么就新建工程然后跟着操作即可。

1.  打开时切换目标平台
    
    若你已经有了预发布的项目那么就直接把目标平台修改为”WebGL“ 然后打开项目即可;
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyNHuibEulibeufw2ghSDObn5uQdzU7fjrbzMGWaspaZuIQibXictKyCXYibg/640?wx_fmt=png)

2.  打开后切换目标平台
    
    若你的项目没有按照第一步的方式使用”WebGL” 平台打开，那么需要在工程中 “Build Settings...” --> 弹出面板选择 “WebGL” --> 点击 “Switch Platform” 等待切换平台完成即可：
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyambvMER4Ay88ZUNDqbGf2H87ic9V4lm2D23PLwf6Sn7903M3L0sWmEg/640?wx_fmt=png)

2.2 发布配置
--------

打开 "Project Settings" 面板 --> 左侧选项栏选择”Player“：

1.  基础信息配置
    
    公司名，项目名，版本号。（没有特殊需求的话默认也行）
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELynZMFZoKicmyRTicU2aESHjc935Nt4JgdicrzvJMH7JmMFE8NsibXnyNe5A/640?wx_fmt=png)

2.  分辨率和显示
    
    找到下面”Resolution and Presentation“面板，设置分辨率。若在不想再后台运行，取消勾选”Run in Background“
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyW15AvW5mPM6ficxibTASibnx8SQVtbHNKzLANeCbtPXUKUck3EwdmRqeQ/640?wx_fmt=png)

PS：其他配置和发布其他平台基本一致，没特殊需求也不需要修改。

2.3 打包 WebGL
------------

打开 “Build Settings...” 面板，点击”Build“，选择打包路径，然后等待打包完成即可：  
![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyRwzrjnvEI8DibUZunXTtnGSU8ReOSVtOvlSfT8VG9xBy2fzQqbdiapag/640?wx_fmt=png)

打包成功后，会在刚刚指定的目录下得到两个文件： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELySXXhicxib5maGC5J6PqH7c96SnD7JIJtEUefTwAsJL1l5wOrDtaVqiaiag/640?wx_fmt=png)

此时双击”index.html“就可以在浏览器中玩耍了。

2.4 打开本地文件问题
------------

打开提示：

> 看起来你的浏览器不支持运行 Unity WebGL 内容从文件:// url。请将它上传到 http 服务器，或尝试不同的浏览器。

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyXmHKFgwgD2vSH8ZFWmZZppQuEMSC4JxMdqPbc04p1BMROErJXUzDUw/640?wx_fmt=png)

若你的浏览器可以打开”index.html“这个本地网页，那么可以忽略这个问题，若不能打开，推荐使用” 火狐浏览器 “试试，不过即使打不开也没有关系，反正我们后面要传到 GitHub 上面。

三，设置静态网页
========

3.1 上传 GitHub
=============

还是和 1.2 一样，使用你习惯的方式进行推送即可

将 Unity 打包出来 WebGL 文件放到本地仓库 (1.2 克隆的那个文件夹) 中，然后推送到远程仓库即可：

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyWAVbOpcHyTN5m0PlfuUx1iciaVnSZmbyJ4vtLialKnvdwPxgTwu5vOkUw/640?wx_fmt=png)

推送成功后，在网站上可以看到如下目录： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyiaUDWkjzdx1GDA33zZeia2J3ybvf1x5uiakZ437WHRKw0V1dDDCa7cwfg/640?wx_fmt=png)

3.2 设置 Pages
============

在 GitHub 上选择 “Settings” --> 左侧标签栏选择“Pages” --> 然后将 "Source" 设置为“master” --> 最后点击右侧“Save” 保存，等网页刷新完成，即可看到下图带颜色背景框部分的 URL，点击此 URL，即可访问。 ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELyzyImpruAmasRPSkyZTHgycOPL6cnxb7Du0nphHW48KFzNEnB13QKtg/640?wx_fmt=png)

3.3 成功访问
========

本文示例的 URL：https://czhenya.github.io/2048.github.io/ 点击即可在线玩耍「2048 化学元素版」

相关拓展：内嵌到网站
==========

先说说在 “前言” 留下的问题，做所以做这么下，是为了... 看下图吧，一图胜千言

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icKfG1xcMzck9EsTLnkxELykBfawRC1RC2QDfw4yjwl2NNmhXBYWHicKbwJrKc92aMlv3tUuOsweEQ/640?wx_fmt=png)

没错，是为了在这自定义区域可以玩耍。

不过好像官方并不允许这么做（第二天自定义模块被清空了），所以我现在的主页上也就没有这个效果了，不过知识还是要学习的，有个人网站的小伙伴，可以尝试下，将小游戏嵌入到自己的网站。

代码如下：

```
<div align="center"><iframe id="game" width="286" height="446" src="https://czhenya.github.io/2048.github.io/"></iframe></div>
```

上面代码的 “width” 和“height”都可以根据游戏的宽高进行修改，而“src” 你可以在各种小游戏网站上找到后缀名是`.html`都可以。

相关推荐： 一文零基础教你制作 Unity 2048 ！【文末源码】