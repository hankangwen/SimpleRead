> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/YEs0Bx0rRpwTEZCJprpZ9Q)

在 C# 中，线程优先级是指操作系统调度线程执行的顺序。每个线程都有一个优先级，这决定了它与其他线程相比获取 CPU 时间的优先权。C# 利用`System.Threading.ThreadPriority`枚举来设置线程的优先级。

**ThreadPriority 枚举**
---------------------

`ThreadPriority`枚举包含以下值：

*   `Lowest`：最低优先级。
    
*   `BelowNormal`：低于正常优先级。
    
*   `Normal`：正常优先级。
    
*   `AboveNormal`：高于正常优先级。
    
*   `Highest`：最高优先级。
    

**示例**
------

### 示例 1：设置线程优先级

下面的示例演示了如何创建两个线程，并为它们设置不同的优先级。

```
using System;
using System.Threading;

class Program
{
    static void Main()
    {
        Thread thread1 = new Thread(Thread1Function);
        Thread thread2 = new Thread(Thread2Function);

        // 设置线程优先级
        thread1.Priority = ThreadPriority.Lowest;
        thread2.Priority = ThreadPriority.Highest;

        thread1.Start();
        thread2.Start();

        thread1.Join();
        thread2.Join();

        Console.WriteLine("主线程结束。");
    }

    static void Thread1Function()
    {
        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine("Thread1正在执行...");
            Thread.Sleep(1000);
        }
    }

    static void Thread2Function()
    {
        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine("Thread2正在执行...");
            Thread.Sleep(1000);
        }
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdkIzXQqrSrlRyFNtibPgyibVyLnDptFjhQgYwXdNQKSpnicH6kqnZddxOrywNGTpcofPiau5WMMiaG0vjg/640?wx_fmt=png&from=appmsg)

在这个示例中，`thread1`被设置为最低优先级`Lowest`，而`thread2`被设置为最高优先级`Highest`。这意味着在 CPU 资源有限的情况下，`thread2`将比`thread1`获得更多的执行时间。

### 示例 2：理解优先级的影响

让我们通过一个计数器示例来更深入地理解线程优先级的影响。

```
using System;
using System.Threading;

class Program
{
    static void Main()
    {
        Thread lowPriorityThread = new Thread(Counting);
        Thread highPriorityThread = new Thread(Counting);

        lowPriorityThread.Priority = ThreadPriority.Lowest;
        highPriorityThread.Priority = ThreadPriority.Highest;

        lowPriorityThread.Start(1);
        highPriorityThread.Start(2);

        lowPriorityThread.Join();
        highPriorityThread.Join();

        Console.WriteLine("主线程结束。");
    }

    static void Counting(object id)
    {
        for (int i = 0; i < 10; i++)
        {
            Console.WriteLine($"线程{id}: {i}");
            Thread.Sleep(500);
        }
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdkIzXQqrSrlRyFNtibPgyibVybl1avSXSSPSmVtcSpn6SSW09zZAdym2rKytc7RcO8k5ytZ63aPttZQ/640?wx_fmt=png&from=appmsg)

在这个示例中，我们有两个执行相同任务的线程，但它们的优先级不同。尽管它们的工作完全相同，但高优先级的线程（`highPriorityThread`）在资源竞争时，将更有可能先完成任务。

注意事项
----

*   在设置线程优先级时应谨慎，因为不恰当的优先级设置可能会导致低优先级线程饿死（即几乎永远不获得 CPU 时间）。
    
*   线程优先级应该根据线程的重要性和需求来合理设置。
    
*   在多核处理器系统中，线程优先级的影响可能不如单核处理器系统明显，因为有更多的 CPU 资源可供线程使用。
    

通过上述示例和解释，我们可以看到 C# 中线程优先级的设置和应用是相对直接的。合理地使用线程优先级可以帮助我们更好地控制和管理线程之间的执行顺序和资源分配。