> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/125109062)

一、资源路径
------

Unity 中的资源路径在 Window 平台下打印出来如下图：

![](https://pic2.zhimg.com/v2-69dada2d0b0eb9371abe3fbe2a605dd9_r.jpg)![](https://pic1.zhimg.com/v2-7c7fa71ddb45ef9d2c751b073fa4455c_r.jpg)

**Android 平台**

![](https://pic3.zhimg.com/v2-c550a826d664b7e095b7d8f00e9d4bfe_r.jpg)

**iOS 平台**

![](https://pic3.zhimg.com/v2-631756754f7ec2de42b23d211254c5e2_r.jpg)

二、Unity3D 中的资源访问介绍
------------------

**1、Resources** 是 Unity3D 系统指定文件夹，如果你新建的文件夹的名字叫 Resources，那么里面的内容在打包时都会被打到发布包中。文件夹特点：

1.  只读，即不能动态修改。所以想要动态更新的资源不要放在这里。
2.  会将文件夹内的资源打包集成到. asset 文件里面。
3.  主线程加载。
4.  资源读取使用 **Resources.Load()**。

**2、StreamingAssets** 也是 Unity3D 系统指定文件夹 ，和 Resources 文件的区别就是 Resources 文件夹中的内容在打包时会被压缩和加密。而 StreamingAsset 文件夹中的内容则会原封不动的打入包中，因此 StreamingAssets 主要用来存放存放打包的 AB 资源，然后用户安装包之后把这些 AB 资源是放到手机内。文件夹特点：

1.  只读，可以放一些压缩的 AB 资源。
2.  只能用过 WWW 类来读取。

**3、PersistentDataPath** 是可读写路径。在 iOS 上就是应用程序的沙盒，但是在 Android 可以是程序的沙盒，也可以是 sdcard。并且在 Android 打包的时候，ProjectSetting 页面有一个选项 Write Access，可以设置它的路径是沙盒还是 sdcard。文件夹特点：

1.  内容可读写**。**
2.  无内容限制。一般是从 **StreamingAsset** 中读取二进制文件或者从 **AssetBundle** 读取文件来写入 **PersistentDataPath** 中。
3.  一般游戏活动通过 WWW 动态下载的图片也可以缓存到此目录，方便下次快速打开。

三、编辑器 Log 路径
------------

**1、编辑器 crash.dmp 目录**

C:\Users\\AppData\Local\Temp\Crashes\Crash_xxxxx\xxxxxcrash.dmp

**2、编辑器 log**

C:\Users\Users\AppData\Local\Unity\Editor\Editor.log

C:\Users\Users\AppData\Local\Unity\Editor\Editor-prev.log

**3、项目 log**

C:\Users\Users\AppData\LocalLow \ 公司名字 xxx \ 项目名字 xxx

![](https://pic3.zhimg.com/v2-5a6a7ddfb8b3fd47903f01ad4cf75596_r.jpg)