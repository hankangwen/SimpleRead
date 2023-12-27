> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_34035956/article/details/134268540?spm=1001.2014.3001.5502)

#### Unity 如何查看编译的耗时？

关键词:  
编译、脚本、编辑器、静态类、程序集、函数、命名空间、构造函数、回调方法、注册时间、注册方法

#### 文字记录:

hello，大家好，今天和大家分享一下 Unity 项目如何查看编译的时间，或者说是编译的耗时。这里我提前准备了一个空的项目工程，因为接下来我们要写的脚本，它仅在编程器的环境中被使用，所以我提前创建好了一个 Editor 文件夹。  
我们在文件夹里面新建一个 C# 脚本，就取名为 CompileTimer。等待编译一下，双击打开这个脚本。这个类它是不需要 start 和 update 两个方法的，它也不需要继承值目录 behavior。  
我们首先将 Unity Editor 命名空间给引入进来，然后我们将这个类修改为静态类，写一个静态的构造函数。

在构造函数里面，我们需要先注册两个事件，一个为编译开始的事件，另一个即为编译结束的事件。  
注册时间相关的代码我们暂时先不写，我们先为这个静态类加上一个标签，也就是属性，我们加上 InitializeOnLoad 这个属性之后，这也就表示当 Unity 编辑器运行时，该类的静态构造函数会自动被调用。  
接下来我们再引入 UnityEditor.Compilation 这个命名空间，它提供了访问和操作 Unity 编辑器中脚本编译流程的功能和事件。

回到静态构成函数里面，当编译开始的时候，我们注册一下 compilationStarted 方法，这里我们可以看到这个方法，它需要一个 object 类型的参数，这里我就不使用快捷键来创建这个方法了。  
回到静态构的函数下面，我们手动把这个方法给补上，就将其命名为 OnCompilationStarted。不要忘记它的参数，上面我们已经提到了它的类型为 object。

到这里，编译开始时注册方法相关的代码，我们就写完复制一下这行代码。紧接着我们来注册一下编译结束时的方法。我们将方法命名为 OnCompilationFinished，它的参数和上面的方法是一致的。

在编译开始的回调方法里面，我们需要先记录一下编译开始的时间，所以我们先在上面声明一个时间戳，它的类型为 double，将其命名为 start time。  
回到方法里面，我们使用编辑器启动到当前时刻所经过的时间来对这个编译开始的时间进行赋值，它的单位为秒。  
在编译结束的回调方法里面，我们首先计算一下编译结束的时间，将其命名为 end time。然后我们再计算下时差，也就是编译说花费的时间。

最后我们再把计算出来的时间输出到控制台上面，也就是打印条 log。

在这里将 duration 只保留两位小数。

okay，至此脚本我们算是写完了。接下来我们把多余的命名空间给删了，回到 Unity 里面去测试一下。

```
using UnityEditor;
using UnityEditor.Compilation;
using UnityEngine;

namespace Editor
{
    [InitializeOnLoad]
    public static class CompileTimer
    {
        private static double _startTime;
        
        static CompileTimer()
        {
            CompilationPipeline.compilationStarted += OnCompilationStarted;
            CompilationPipeline.compilationFinished += OnCompilationFinished;
        }

        private static void OnCompilationStarted(object obj)
        {
            _startTime = EditorApplication.timeSinceStartup;
        }

        private static void OnCompilationFinished(object obj)
        {
            double endTime = EditorApplication.timeSinceStartup;
            double duration = endTime - _startTime;
            Debug.Log($"编译耗时：{duration:F2} 秒");
        }
    }
}
```

我们随便新建个脚本，那就写个 test 吧，非常的 nice。在这里我们已经可以看到本次编译所耗费的时间了。到这里有的小可爱肯定有疑问了，我们查看这个项目的编译时间具体有什么用，那它的用途或者说好处可就多了去了。  
我给大家举几个简单的例子。首先就是在性能方面，随着我们的项目开发周期变长，也就是说随着项目的增长，编译的时间可能会逐渐的增加。  
我们有了这个工具之后，我们可以实时了解项目编译时间的变化，如果突然发现编译的时间显著的增加了，这可能是一个不好的迹象，那表明我们在项目中加入了一些影响性能的东西。

另外一点可能说的比较现实，过长的编译时间会影响开发者的心情，也会影响我们的效率。尤其在大型团队中，不同的团队成员可能会影响整体的编译时间。  
有了具体的编译时间的数据，我们可以更有针对性的讨论哪些项目的变动导致了编译时间的变化，从而采取相应的优化策略。

最后我们再和前面几集视频做一个简单的互动。在前面的视频里面，我们聊到了 Unity 的程序集。我们今天写的这个工具类，它对于我们合并程序集来说特别的有帮助。  
这个类其实还有一些不完美的地方，比如我们可以使用更加详细的日志输出，例如当别人的时间超过 5 秒钟之后，我们可以打印一条警告的日志。  
再比如，我们还可以为编译时间添加上平均值和最大值。实际上要不要加上这些功能取决于项目的具体需求与项目的规模。我们目前这个脚本已经完成了它最主要的功能。  
![](https://img-blog.csdnimg.cn/4d200d70a0a24f328481130ad2dba246.png)