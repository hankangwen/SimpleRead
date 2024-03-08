> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.cnblogs.com](https://www.cnblogs.com/caiger-blog/p/16211519.html)

写在前面
====

*   如果在 Player 运行时突然崩溃，仅靠 Player.log 日志文件不能定位引起崩溃的代码，那么可以尝试利用 dmp（仅限 Windows 平台）文件定位崩溃原因。

正文
==

环境
--

*   Unity 2020.3.21f1 (64-bit)，IL2CPP 后端，Windows 平台。
*   Visual Studio 2019

先让 Unity 崩溃
-----------

*   想要得到 dmp 文件，必须先让 Unity 崩溃。我的测试设计很简单，场景有一个按钮，点了按钮就会让 Unity 崩溃。场景效果如下图：

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430213120496-1553473420.png)

　　按钮的代码 TestCrash.cs 如下（参考链接：“[怎样能够强制 Unity 应用 Crash](https://answer.uwa4d.com/question/5dd5f3337307ec2f0f99a2b2)”），我在 ClickCrash 方法中写了强制崩溃：

[![](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0); "复制代码")

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Diagnostics;

public class TestCrash : MonoBehaviour
{
    
    public void ClickCrash()
    {
        UnityEngine.Debug.LogFormat($"<color=yellow>ForceCrash</color>");
        Utils.ForceCrash(ForcedCrashCategory.FatalError);

    }

}
```

[![](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0); "复制代码")

　　在编辑器上，Unity 的表现是突然卡住，然后弹出向 Unity 官方发送报错的窗口，关闭这个窗口后编辑器也会被关闭。

利用 dmp 文件定位崩溃代码　　
-----------------

*   编辑器上可以成功崩溃后就打 Player，如下图，BuildSetting 窗口务必要勾上 Development Build，再勾上 Deep Profiling Support，不然即使得到 dmp 文件也无法具体定位。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430214237040-1354034266.png)

　　打出的 Player 文件夹内容如下图，这里我的 Player 叫 2019TestMisc.exe。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430221347205-684756075.png)

　　顺便一提，我在 Assembly-CSharp4.cpp 里找到了我写的测试代码。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430221505511-1135701293.png)

　　运行 2019TestMisc.exe，能正常崩溃，这里的表现也是突然卡住，然后弹出向 Unity 官方发送报错的窗口，关闭这个窗口后 2019TestMisc.exe 也会被关闭。

　　UnityManual 有[介绍](https://docs.unity3d.com/2022.2/Documentation/Manual/LogFiles.html)在哪里可以看 Crash 文件，我的 Crash 文件夹路径如下图：

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430221645572-1754770973.png)

　　打开文件夹就能看到 crash.dmp 文件和 Player.log。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430221728383-1240592579.png)

　　UnityManual 有[调试说明](https://docs.unity3d.com/2022.2/Documentation/Manual/WindowsDebugging.html)，这里我用 Vs 打开 crash.dmp 文件，如下图，它长这样：

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430221958394-1753373859.png)

　　我按照[调试说明](https://docs.unity3d.com/2022.2/Documentation/Manual/WindowsDebugging.html)设置了符号路径，如下图，为了能尽快定位崩溃，我在 “自动符号加载首选项” 里选了“加载除排除模块之外的所有模块”。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430223804442-414698947.png)

　　开始调试，调试结果如下图，能看到它会定位到一个 C++ 文件，调用堆栈窗口里能看到引起崩溃的具体脚本 TestCrash 和方法 ClickCrash。

![](https://img2022.cnblogs.com/blog/747596/202204/747596-20220430222600371-319547461.png)