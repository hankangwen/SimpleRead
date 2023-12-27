> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/JavaD0g/article/details/131269392?spm=1001.2014.3001.5502)

#### [Unity](https://so.csdn.net/so/search?q=Unity&spm=1001.2101.3001.7020) Remote 实操教程

*   [1. 插件安装](#1_1)
*   *   [1-1. 编辑器 Unity Remote 插件安装](#11Unity_Remote_2)
    *   [1-2. 移动设备安装 Unity Remote](#12Unity_Remote_8)
*   [2. 配置调整](#2_17)
*   [3. 总结](#3_28)
*   *   [3-1.IOS 流程](#31IOS__29)
    *   [3-2.Android 流程](#32Android__37)

1. 插件安装
-------

### 1-1. 编辑器 Unity Remote 插件安装

我们需要先安装 InputSystem 插件  
我们打开 PackageManager 视窗（不知道怎么打开的看回上一篇文章如何安装 InputSystem 有详细讲解）选择 InputSystem，点击右边属性面板中的 Samples  
![](https://img-blog.csdnimg.cn/bacc0c2ff8524a6a9824a68382e6cbba.png)  
找到 Unity Remote 点击 Import 导入（导入成功后 Import 按钮就会显示为 Reimport）  
![](https://img-blog.csdnimg.cn/153e6fc268ea4e2592f6b50da3dd31bb.png)

### 1-2. 移动设备安装 Unity Remote

IOS 端的话直接在 App Store 里面搜索 Unity Remote 下载就可以  
![](https://img-blog.csdnimg.cn/15dca3b3afac449d8662a846c9650d12.jpeg)  
Android 端的话并不能直接下载需要在 Google 商店搜索 Unity Remote 下载（需要科技和魔法）  
或者自行百度搜索一下 Unity remote 5 对应的 apk 也可以（网上百度网盘等资源很容易找到）  
Android 端的使用需要打开开发者模式后（注：**每个型号系统打开开发者模式的方法不同，大家可以上网查看一下自己手机型号是如何打开的**）  
点击 USB 调试或者 USB 链接（注：**每个不同 UI 的叫法不一样，反正就是要打开 USB 连接的权限**）  
移动端设备 Unity Remote 下载好之后使用数据线将移动设备和 PC 链接

2. 配置调整
-------

此时回到编辑器这打开 File => Build Settings 选择对应的平台端（与将要链接的移动设备相同）  
![](https://img-blog.csdnimg.cn/565f7f529fe741dea748a435a8f22787.png)  
之后在打开 Editor => Project Settings 找到 Editor（1-2. 编辑器中 Unity Remote Sample 安装成功才会显示）  
![](https://img-blog.csdnimg.cn/bf8543f1bacb44f7be88c31bb204ae52.png)  
我们将 Device 选择到 Android 设备上（如果没有出现 IOS 或者 Android 的选项是因为 Unity 编辑器没有安装对应平台的模块，需要安装并选择后才会显示 参照配置调整的第一点，**如果选择对应平台后还没出现就把数据线拔了重新插**）  
![](https://img-blog.csdnimg.cn/32ee66c41c4d485cb11698859c347bef.png)  
下面参数根据自己的需求调整（有的人反应连接到移动设备的画面很模糊是因为 Resolution 选择了低分辨率）  
[Unity Remote 参数对应的解释](https://img-blog.csdnimg.cn/a23fa4e16faf402ba9e9e31185163c9a.png)

最后我们点击开始，就可以在我们的移动设备上同步并操作我们编辑器中正在运行的场景了。

3. 总结
-----

### 3-1.IOS 流程

1.  Unity 编辑器中安装 Unity Remote 插件 Sample
2.  IOS 端在 App Store 下载 Unity Remote 5
3.  数据线连接移动设备和 PC
4.  Unity 编辑器中安装并选择 IOS 开发平台
5.  Unity Remote 中 Device 选择 IOS
6.  点击开始运行即可同步移动设备和 PC 端画面

### 3-2.Android 流程

1.  Unity 编辑器中安装 Unity Remote 插件 Sample
2.  Android 端在 Google Store 下载 Unity Remote 5
3.  打开 Android 系统的开发者模式并开启 USE 连接选项
4.  数据线连接移动设备和 PC
5.  Unity 编辑器中安装并选择 Android 开发平台
6.  Unity Remote 中 Device 选择 Android
7.  点击开始运行即可同步移动设备和 PC 端画面