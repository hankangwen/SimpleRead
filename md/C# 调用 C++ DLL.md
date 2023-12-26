> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/eUos92-heTjMVK7pfX5sNw)

**前言**

很多人说，C# 底层太难了，今天搞个简单点的。看下如何通过最简单的方式 C# 调用 C++ 写的 DLL。以 VS2022 为蓝本。  

**C++**
=======

首先新建一个具有导出项的 C++ DLL 动态链接库项目，用其它的项目新建，比如动态链接库 DLL 项目，或者空项目或有各种问题。打开 VS2022，选择如下图所示：  

![](https://mmbiz.qpic.cn/mmbiz_png/E2GaFRlbWh8iaDtzBgOVanfBcv2S8w7RYxib0WYWTEL438nx4RfL5uJDbrWgU7xLOvH0nibd5VlYqsI8FyTNDNXwQ/640?wx_fmt=png&from=appmsg)

取名叫 Dll1，项目建好了之后，结构如下图：

![](https://mmbiz.qpic.cn/mmbiz_png/E2GaFRlbWh8iaDtzBgOVanfBcv2S8w7RYMWqZ14tDfvDrWYGl4D3s3OoicqCy89L781ibMJA7ib1libQCx0cwdZAX8w/640?wx_fmt=png&from=appmsg)

右击源文件 -》添加 -》新建项 -》文件名: FileName.cpp，源文件文件夹下多了一个 FileName.cpp 的 C++ 文件。其它文件是默认创建的，不用管它。

![](https://mmbiz.qpic.cn/mmbiz_png/E2GaFRlbWh8iaDtzBgOVanfBcv2S8w7RYNRumrelk1rR9G7Kib5lq8n2uHJcbNzqxp8k4UcpYCHgBiax40xhRAxZQ/640?wx_fmt=png&from=appmsg)

FileName.cpp 添加如下代码  

```
#include "pch.h"


extern "C" __declspec(dllexport) int Add(int x, int y)
{
#ifdef _DEBUG
  return x;
#else
  return y;
#endif
}
```

把 Dll1 项目生成下，.../x64/Debug 目录下找到 Dll1.dll。就是生成好的 C++ DLL 了。不需要任何设置。
===================================================================

**C#**
======

新建一个 C# 控制台应用程序，代码如下：

```
namespace ConsoleApp1
{
    public class Test
    {
        [DllImport("E:\\Visual Studio Project\\Test_\\x64\\Debug\\Dll1.dll")]
        public static extern int Add(int a, int b);

        internal class Program
        { 
            static void Main(string[] args)
            {
                Console.WriteLine(Add(33, 2));            
                Console.ReadLine();
            }
        }
    }
}
```

DllImport 里面包含的即是上面 C++ 生成的 Dll1 的路径。

调用结果如下：  

![](https://mmbiz.qpic.cn/mmbiz_png/E2GaFRlbWh8iaDtzBgOVanfBcv2S8w7RYHkULLjyQ9Tc7oczuicouYeeQGqSGibzfxZFS9eUR8iaMicWV0M0CumA1eA/640?wx_fmt=png&from=appmsg)

以上为最简单的 C# 调用 C++ DLL 的过程，全程不需要任何库文件，以及编译方面的设置

**往期精彩回顾**

[.NET8 JIT 核心: 分层编译的原理](http://mp.weixin.qq.com/s?__biz=Mzg5NDYwNjU4MA==&mid=2247485453&idx=1&sn=f7c1a6198b9e24af64a6a88b80230a76&chksm=c01c4596f76bcc80ff69ce39bc691f508a118f679d64c070e12538151dde161c4f80da935724&scene=21#wechat_redirect)
==============================================================================================================================================================================================================================================

[新版. Net 性能有没有达到 C++90%?](http://mp.weixin.qq.com/s?__biz=Mzg5NDYwNjU4MA==&mid=2247485277&idx=1&sn=dfb356778d490c11986e5134d578271a&chksm=c01c4ac6f76bc3d0f1821af547af1bdb67b6a4cff3f7611203ac4690f0f400e322294128d5c6&scene=21#wechat_redirect)  

[面试官问. Net 对象赋值为 null, 就会被 GC 回收吗?](http://mp.weixin.qq.com/s?__biz=Mzg5NDYwNjU4MA==&mid=2247485350&idx=1&sn=6a19a00f7f86bc5802d06c99556d2a19&chksm=c01c4a3df76bc32b63f8d2530a044e8e1fc82ebfd98ddeb5002799e992e3108037ed9ad52db3&scene=21#wechat_redirect)![](https://mmbiz.qpic.cn/mmbiz_jpg/Vtf2wZNabHCNFqhaS3jlRN82iafVavcOpaFn6ZrPpEMEicyZLpYnay0ueGY6j6hRt1rfyKicmDrasw5VwzB7CeEkg/640?wx_fmt=jpeg&wxfrom=5&wx_lazy=1&wx_co=1)
===================================================================================================================================================================================================================================================================================================================================================================================================================================