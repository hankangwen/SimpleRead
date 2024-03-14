> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_42316280/article/details/122942774)



 **前言：**在商业的项目中，许多公司会使用`SVN`或`GIT`等版本控制系统来协作开发，可是在`Unity`编辑器中并没有集成`SVN`的相关功能，每当我们需要提交或者更新代码时，需要在项目的文件夹中去进行操作，所以写了一个工具来实现在`Unity`编辑器中可以直接使用`SVN`。

**核心原理：**  
 在`Windows`中，我们可以通过`cmd`启动各种其他应用程序，`SVN`也不例外，我们在`cmd`中执行这行命令，便可以进行`SVN`操作：

```
TortoiseProc.exe /command:xxxxxxx  /path:xxxxxxxxx /closeonend:0
```

 其中，`/command:`后为操作的类型（即`update`、`commit`、`revert`）；`/path:`后为项目的路径。

根据以上原理，我们的工具代码如下：

```c#
using System;
using System.Threading;
using System.Diagnostics;
using UnityEngine;
using UnityEditor;

/// <summary>
/// Unity SVN工具
/// </summary>
public class SVNTool
{
    /// <summary>
    /// svn的GUI程序名
    /// </summary>
    private static readonly string SVN_APP_NAME = "TortoiseProc.exe";

    /// <summary>
    /// 项目路径，即Assets文件夹
    /// </summary>
    private static string projectPath = Application.dataPath;

    /// <summary>
    /// cmd命令模板
    /// </summary>
    private static string cmdCommandModule = SVN_APP_NAME + " " + "/command:{0} /path:{1} /closeonend:0";

    /// <summary>
    /// svn update assets
    /// </summary>
    /// update整个Assets文件夹
    [MenuItem("Tools/SVN Tool/SVN Update All")]
    public static void UpdateAll()
    {
        string cmdCommand = string.Format(cmdCommandModule, "update", projectPath);
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn commit assets
    /// </summary>
    /// commit整个Assets文件夹
    [MenuItem("Tools/SVN Tool/SVN Commit All")]
    public static void CommitAll()
    {
        string cmdCommand = string.Format(cmdCommandModule, "commit", projectPath);
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn revert assets
    /// </summary>
    /// revert整个Assets文件夹
    [MenuItem("Tools/SVN Tool/SVN Revert All")]
    public static void RevertAll()
    {
        string cmdCommand = string.Format(cmdCommandModule, "revert", projectPath);
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn showlog assets
    /// </summary>
    /// showLog整个Assets文件夹
    [MenuItem("Tools/SVN Tool/SVN ShowLog All")]
    public static void ShowLogAll()
    {
        string cmdCommand = string.Format(cmdCommandModule, "log", projectPath);
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn update select
    /// </summary>
    /// update在Assets界面选中的资源
    [MenuItem("Assets/SVN Tool/SVN Update")]
    public static void UpdateSelect()
    {
        string cmdCommand = string.Format(cmdCommandModule, "update", GetSVNCommand());
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn commit select
    /// </summary>
    /// commit在Assets界面选中的资源
    [MenuItem("Assets/SVN Tool/SVN Commit")]
    public static void CommitSelect()
    {
        string cmdCommand = string.Format(cmdCommandModule, "commit", GetSVNCommand());
        InvokeCmd(cmdCommand);
    }

    /// <summary>
    /// svn revert select
    /// </summary>
    /// revert在Assets界面选中的资源
    [MenuItem("Assets/SVN Tool/SVN Revert")]
    public static void RevertSelect()
    {
        string cmdCommand = string.Format(cmdCommandModule, "revert", GetSVNCommand());
        InvokeCmd(cmdCommand);
    }

    public static string GetSVNCommand()
    {
        string[] selectFilePath = GetSelectFilePath();
        string temp = string.Empty;
        for(int i = 0; i < selectFilePath.Length; i++)
        {
            temp += selectFilePath[i];
            temp += "*";
        }
        return temp;
    }

    /// <summary>
    /// 获取选中的资源的路径
    /// </summary>
    /// <returns>选中资源的路径 string[]</returns>
    public static string[] GetSelectFilePath()
    {
        string[] guidArray = Selection.assetGUIDs;
        string[] selectFilePath = new string[guidArray.Length];
        for(int i = 0; i < guidArray.Length; i++)
        {
            selectFilePath[i] = AssetDatabase.GUIDToAssetPath(guidArray[i]);
        }
        return selectFilePath;
    }

    /// <summary>
    /// 调用cmd
    /// </summary>
    /// <param >cmd命令</param>
    private static void InvokeCmd(string cmdCommand)
    {
        new Thread(new ThreadStart(() => //新建线程，ThreadStart表示在Thread上执行的方法
        {
            try
            {
                Process p = new Process(); //新建系统进程

                //Process中的StartInfo为要传递给Process.Start()方法的属性

                //设置p.StartInfo属性
                p.StartInfo.FileName = "cmd.exe"; //要启动的应用程序
                p.StartInfo.Arguments = "/c " + cmdCommand + "&exit"; //启动应用程序时要使用的一组命令行参数
                p.StartInfo.UseShellExecute = false; //是否使用操作系统shell启动进程(如果是从可执行文件创建进程，应设置为false)
                p.StartInfo.RedirectStandardInput = true; //指示应用程序的输入是否从StandardInput流中读取的值(StandardInput)
                p.StartInfo.RedirectStandardOutput = true;
                p.StartInfo.RedirectStandardError = true;
                p.StartInfo.CreateNoWindow = true; //不显示程序窗口

                p.Start(); //启动进程
                p.WaitForExit(); //等待程序执行完退出进程
                p.Close(); //关闭进程
            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
        })).Start();
    }
}

```

 该工具实现了`SVN`的`update`、`commit`、`revert`、`showlog`这四个最常用的功能。

**补充：**  
 1、除了以上工具中的`SVN`命令外，`SVN`还有其他几种`cmd`命令：`checkout`、`diff`、`add`  
 2、在`Visual Studio`中，可直接在拓展中安装`VisualSVN for Visual Studio`插件实现`SVN`操作。