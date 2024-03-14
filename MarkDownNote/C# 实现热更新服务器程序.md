> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/su_xf/article/details/118570719)

        很早就想写一篇关于热更服务器的文章，这两天有功夫就来写一下，正巧前两天也花时间把自己写了一段时间的 C#[框架](https://so.csdn.net/so/search?q=%E6%A1%86%E6%9E%B6&spm=1001.2101.3001.7020)给整理开源了。

        其实首先探讨的一个问题就是，热更服务器程序到底有没有必要出现，或者说有没有适用场景，我个人觉得吧还是有的。比如如果真的可以在不重启应用的情况下实现逻辑的更新，这未尝对于一些紧急的情况不是一个好消息，尤其是一些小团队、小创业公司刚起步的时候，技术测试流程和人力不会像成规模的企业那样完善，那么带来的问题就是上线后的应用、游戏可能会存在一些 Bug，如果不严重还好，可以留到下一个迭代更新统一修复，但是如果严重了，又考虑如果此刻关服修复会导致用户流失，那么这时候不停服[热更新](https://so.csdn.net/so/search?q=%E7%83%AD%E6%9B%B4%E6%96%B0&spm=1001.2101.3001.7020)就有了应用场景，可以在用户无感知的情况下进行逻辑的修复工作。这也是热更功能主要的适用场景，至于增加新功能或者删除一些功能也可以通过不停服的方式来操作。

        那么说完这个需求后，接下就是怎么才能实现这个功能。其实这个功能主要还是利用了 C# 自带的反射，在新的 Dotnet 框架中. net core3.0 以后和. net5.0 以后，微软对 Assembly 加载做了进一步整理，虽然以前也有类似功能，但是众所周知的原因，以前的. net 版本混乱，现在微软既开源也统一化版本，可以说在未来时间里，.Net 的潜力不可估量，那么我所讲的，也是基于较新的框架版本实现的。

        AssemblyLoadContext 这个类就是今天的主角，它的主要功能就是隔离式的程序上下文，什么意思，就是它具备一定保护，可以使动态加载的程序集不和静态加载的程序集混合在一起，而是独立运行在类似沙盒的空间里，但是又具备相互访问的权限。这就很厉害了，这样一来，我们可以加载自己的程序集，然后供本来应用调用，在需要更新的时候，把新的程序集加载进来，并且替换旧的程序，释放旧的程序集，这样就可以无缝衔接的执行新的逻辑了。

        下面我就借用我自己写的框架来实现这个热更的过程，如果对热更原理本身感兴趣的，也可以去看看我写的热更源码，我会在文章最下面贴上我的开源项目地址，源码里面基本上都是有注释的，所以看起来也不会很难。

一、首先我们创建一个. Net5.0 或者. Netcore3.1 的项目，取名 Abc：

![](https://img-blog.csdnimg.cn/20210708122236204.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)![](https://img-blog.csdnimg.cn/20210708122347504.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)![](https://img-blog.csdnimg.cn/20210708122401903.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)

二、创建成功，我们找到依懒项，右击管理 Nuget 程序包，选择浏览标签搜索：EasySharpFrame，然后选中后点击下载按钮进行安装。

![](https://img-blog.csdnimg.cn/20210708122909140.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)

三、安装完成后，框架就算成功安装好了，接下来，我们再从解决方案右击新建一个新的项目，这个项目就是用于热更逻辑实现的动态库，名字就叫 Hotfix，创建之后，在解决方案资源管理器一栏中就会看到这个项目已经成功添加进去了，之后我们右击这个 Hotfix 项目的依赖项，找到添加项目引用，直接把 Abc 勾选确定，至此项目的添加创建步骤就完成了。

![](https://img-blog.csdnimg.cn/20210708123208971.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)![](https://img-blog.csdnimg.cn/202107081233159.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)![](https://img-blog.csdnimg.cn/20210708123358222.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)![](https://img-blog.csdnimg.cn/20210708123617155.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N1X3hm,size_16,color_FFFFFF,t_70)

四、接下来就是开始写代码实际应用了，首先在 Abc 主项目中的 Program.cs 入口中，调用框架中热更管理单例。因为我们没有更改 Hotfix 项目的默认配置，所以生成出来的 Dll 文件名就是 Hotfix，然后我们在 Hotfix 项目里添加一个 Main.cs 的入口文件，这里通过热更管理器就完成了初始化，后面每次重载也只需要重复这个步骤就可以了。

```
class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Hello World!");
 
        // 确保进行不会自动结束
        while (true)
        {
            // 调用热更模块加载Hotfix
            HotfixMgr.Instance.Load("Hotfix", "Hotfix.Main");
            // 回车继续，否则阻塞
            Console.ReadLine();
        }
    }
}
```

五、接下来，我们在 Hotfix 项目里 Main.cs 中加点测试内容。

```
public class Main
{
    public void Hello()
    {
        Console.WriteLine("Hello World");
    }
}
```

并且在刚刚主工程代码里加点东西。 

```
// 调用热更模块加载Hotfix
HotfixMgr.Instance.Load("Hotfix", "Hotfix.Main");
// 这里可以通过Agent调用测试入口的函数
HotfixMgr.Instance.Agent.Hello();
// 回车继续，否则阻塞
Console.ReadLine();
```

六、这样一个简单的热更事例就完成了，接下来生成解决方案。然后找到 Hotfix 项目生成路径，把关于 Hotfix.dll 和 Hotfix.pdb 两个文件复制粘贴到 Abc 的生成路径下。双击 Abc.exe，启动事例查看结果。注：pdb 是用于给运行时提供出错时准确提示错误的解释文件，实际运行只需要 dll，如果不需要查看问题出处，可以只复制 dll 即可。

![](https://img-blog.csdnimg.cn/20210708135203103.png)

此时不要关闭控制台，继续回到 VS 中，修改一下 Main.cs 的内容，并且这次只生成 Hotfix 项目，把生成好的 dll 和 pdb 复制到 Abc 中。

```
public class Main
{
    public void Hello()
    {
        // 修改前
        // Console.WriteLine("Hello World");
        // 修改后
        Console.WriteLine("Hello New World");
    }
}
```

替换完成后，在控制台回车一下，结果显示：

![](https://img-blog.csdnimg.cn/20210708135147615.png)

新的逻辑已经更新至程序中。

        以上就是一个简单的热更流程展示，框架提供的热更功能还有更多功能，这里只是简单介绍一下热更的原理与实现。如果对框架感兴趣的朋友可以到 github 上去了解。

        项目地址：[EasySharpFrame](https://github.com/suxf/EasySharpFrame)

        如果觉得可以的话，可以在 Github 项目给颗星支持一下，非常感谢~