> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_42345116/article/details/122055201?ops_request_misc=&request_id=&biz_id=102&utm_term=unity%E5%A4%9A%E7%BA%BF%E7%A8%8B&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-2-122055201.nonecase&spm=1018.2226.3001.4187)

### 一、什么是线程？

> 线程是操作系统能够进行运算调度的最小单位，被包含在进程之中，是进程中的实际运作单位。一条线程指的是进程中一个单一顺序的控制流，一个进程中可以并发多个线程，每条线程并行执行不同的任务。

简单理解： 

我们首先了解一下什么是进程。我们电脑开启的每个软件其实就是一个进程。Ctrl+alt+delete 选择任务管理器可以查看

 ![](https://img-blog.csdnimg.cn/223ede431b2749f3a430360f05e4d241.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6KKr5Luj56CB5oqY56Oo55qE54uX5a2Q,size_20,color_FFFFFF,t_70,g_se,x_16)

为什么要先了解进程呢？因为进程和线程是包含关系，一个进程（软件）中是包含多个线程的。并且一个进程至少要有一个线程。

好接下来我们举例说明一下，QQ 这个进程（软件），我们把进程和线程的关系当成脚本中我们写的类和函数的关系，要知道我们的类其实就是一个大功能（软件），类中的方法函数就是为了帮助实现这个类的某个功能（软件的某个功能）。他们之间的关系 就是 一个类中包含多个方法函数并且类中至少有一个方法（一个类中一个方法都没有，没有操作计算没有意义，这里举例参数类不算.....）。

二、为什么要使用线程？
-----------

线程其实是同时（并行）执行的，要知道在 Unity 中虽然有协程可以协助主线程进行计算，但是协程的计算还是在主线程中的，如果协程要计算的数据过大，需要等待，这时候就会影响主线程的其他方法执行，比如我们在 UpDate 中实现鼠标控制相机旋转移动，这时候协程计算某个数据等待了 2 秒，你就明显发现屏幕卡顿了（因为主线程在计算东西，相机旋转在后面等着呢）。

所以这时候就用到线程了。有了线程 我不管你计算的数据多么庞大，我主线程根本不怕（两者各干各的 互不影响）。

### 三、Unity 可以使用[多线程](https://so.csdn.net/so/search?q=%E5%A4%9A%E7%BA%BF%E7%A8%8B&spm=1001.2101.3001.7020)，但却要避免使用线程

Unity 自己本身 UnityEngine 所使用的 API 是不能被多线程调用的，所以 Unity 是不能使用多线程的，但是 C# 中可以使用多线程，Unity 使用 C# 进行脚本编辑，故而 Unity 也可以通过 C# 来调用多线程。

> Unity 使用多线程时要注意几点：
> 
> 1.  变量都是共享的 (都能指向相同的内存地址)
> 2.  UnityEngine 的 API 不能在分线程运行
> 3.  UnityEngine 定义的基本结构 (int, float, struct 定义的数据类型) 可以在分线程计算，如 Vector3(struct)可以, 但 Texture2d(class, 根父类为 Object) 不可以。
> 4.  UnityEngine 定义的基本类型的函数可以在分线程运行

详细信息： 

[Unity 之可以使用多线程，但为何要避免使用。_被代码折磨的狗子的博客 - CSDN 博客](https://blog.csdn.net/qq_42345116/article/details/122054926 "Unity之可以使用多线程，但为何要避免使用。_被代码折磨的狗子的博客-CSDN博客")

四、线程的生命周期
---------

![](https://img-blog.csdnimg.cn/940285bcfc994e8eb81facbd3b4d760e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6KKr5Luj56CB5oqY56Oo55qE54uX5a2Q,size_20,color_FFFFFF,t_70,g_se,x_16)

> 线程的生命周期包含 5 个阶段，包括：新建、就绪、运行、阻塞、销毁。
> 
> *   新建：就是刚使用 new 方法，new 出来的线程；
>     
> *   就绪：就是调用的线程的 start() 方法后，这时候线程处于等待 CPU 分配资源阶段，谁先抢的 CPU 资源，谁开始执行;
>     
> *   运行：当就绪的线程被调度并获得 CPU 资源时，便进入运行状态，run 方法定义了线程的操作和功能;
>     
> *   阻塞：在运行状态的时候，可能因为某些原因导致运行状态的线程变成了阻塞状态，比如 sleep()、wait() 之后线程就处于了阻塞状态，这个时候需要其他机制将处于阻塞状态的线程唤醒，比如调用 notify 或者 notifyAll() 方法。唤醒的线程不会立刻执行 run 方法，它们要再次等待 CPU 分配资源进入运行状态;
>     
> *   销毁：如果线程正常执行完毕后或线程被提前强制性的终止或出现异常导致结束，那么线程就要被销毁，释放资源;
>     

五、线程基础方法使用 
-----------

> new Thread()：创建一个线程
> 
> start()：开启创建的线程
> 
> join()：当前线程等待另一个线程结束后，在执行
> 
> Sleep(); 等待 N 毫秒后继续执行
> 
> Suspend()：该方法并不终止未完成的线程，它仅仅挂起当前线程，以后还可恢复；
> 
> Resume()：恢复被 Suspend() 方法挂起的线程的执行。
> 
> Abort()：结束线程

其中 Suspend()，Resume() 已经过时，因为它们是不安全的，为什么呢？这涉及到 CPU 的调度问题，人们为了将 CPU 充分的利用起来，在数据处理时，CPU 的调度是不确定，举个例子，我们在生活中给别人打电话的时候左手执行接听电话这个任务，这时候电话那头人说了一个号码，你需要用右手来记录，虽然在同一时间执行了这两个任务，但是当你用左手接听电话那边说的数字的时候，右手是不可能同时写的（除非你有预言功能，在他说之前就已经知道号码了），这时候的处理方式就是当他说出一部分号码时，右手趁着他喘口气的时间，在本子上记下来。CPU 的处理方式也是如此。如果我们在左手接电话的任务中调用 Suspend() 方法，这时候右手任务趁虚而入，那么我们会发现我们想挂起的左手任务还在执行，不想挂起的任务却被暂停了，这样在数据处理中是一个很严重的事情。

接下来教大家上面方法如何使用

### 1. 线程调用有参无参的方法函数

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
 
public class ThreadTest : MonoBehaviour
{
    Thread threadA;
    Thread threadB;
    void Start()
    {
        threadA = new Thread(AA);
        threadB = new Thread(new ParameterizedThreadStart(BB));
        threadA.Start();
        threadB.Start("B线程： ");
    }
 
    //无参 
    void AA()
    {
        for (int i = 0; i < 5; i++)
        {
            Debug.Log("A线程： " + i);
        }
    }
 
    //有参 注意有参函数类型必须是object类型
    void BB(object a) 
    {
        for (int i = 0; i < 5; i++)
        {
            Debug.Log(a.ToString() + i);
        }
    }
 
}
```

运行结果：

![](https://img-blog.csdnimg.cn/d19f37871c8741f2b0340662a0360280.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6KKr5Luj56CB5oqY56Oo55qE54uX5a2Q,size_11,color_FFFFFF,t_70,g_se,x_16)

 我们可以看出打印结果是无序的（虽然是交错打印的，实际他们的运行方式是，A 线程在打印的时候 CPU 有空余时间，这时候 B 线程直接顶上，这么做能充分的利用 CPU）

### 2.Join() 方法使用 

我们接下来让 A 线程循环打印完毕后在执行 B 线程循环，这就用到我们的 Join 方法了

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
 
public class ThreadTest : MonoBehaviour
{
    Thread threadA;
    Thread threadB;
    void Start()
    {
        threadA = new Thread(AA);
        threadB = new Thread(new ParameterizedThreadStart(BB));
        threadA.Start();
        threadA.Join();//在CPU加入threadA的结束判断当threadA线程结束后 在执行后面的线程方法
        threadB.Start("A线程： ");
    }
 
    //无参
    void AA()
    {
        for (int i = 0; i < 5; i++)
        {
            Debug.Log("B线程： " + i);
        }
    }
 
    //有参
    void BB(object a) 
    {
        for (int i = 0; i < 5; i++)
        {
            Debug.Log(a.ToString() + i);
        }
    }
 
}
```

结果：

![](https://img-blog.csdnimg.cn/e9a83342dc8b433990280b92ca0a2f30.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6KKr5Luj56CB5oqY56Oo55qE54uX5a2Q,size_11,color_FFFFFF,t_70,g_se,x_16)

 看结果就知道变成顺序打印了，但是要注意一点 Join 这个方法会占用很多 CPU 资源，要小心利用，Join 在线程执行完之前分配大量的时间片给该线程，直到线程结束后。所以使用的时候要注意

### 3.Sleep() 等待睡眠结束

这个很简单 就是执行到该语句时等待一段时间继续往下执行

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
 
public class ThreadTest : MonoBehaviour
{
    Thread threadA;
    Thread threadB;
    void Start()
    {
        threadA = new Thread(AA);
        threadB = new Thread(new ParameterizedThreadStart(BB));
        threadA.Start();
        threadB.Start("B线程： ");
    }
 
    //无参
    void AA()
    {
        Debug.Log("A线程开启");
        Thread.Sleep(3000); //3000毫秒 等待3秒钟
        Debug.Log("A线程等待了3秒");
 
    }
 
    //有参
    void BB(object a) 
    {
        for (int i = 0; i < 3; i++)
        {
            Thread.Sleep(1000); //1000毫秒 等待1秒钟
            Debug.Log(a.ToString() + i);
        }
    }
}
```

结果：

![](https://img-blog.csdnimg.cn/3d64e33a69ea4a338275eacc37bced05.gif)

 结果很直观吧 就不多解释了。

4.Abort() 停止线程
--------------

其实也叫 "杀死" 线程，执行这个方法后线程就被摧毁了，从线程生命周期来看他是自动执行的，这里举一个使用他的例子

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
 
public class ThreadTest : MonoBehaviour
{
    Thread threadA;
    void Start()
    {
        threadA = new Thread(AA);
        threadA.Start();
    }
 
    //无参
    void AA()
    {
        //死循环 每过1秒执行一次
        while (true)
        {
            Thread.Sleep(1000); //3000毫秒 等待3秒钟
            Debug.Log("A线程执行");
        }
    }
 
    
    void OnApplicationQuit()
    {
        //结束线程必须关闭 否则下次开启会出现错误 （如果出现的话 只能重启unity了）
        threadA.Abort();
    }
 
}
```

结果：

![](https://img-blog.csdnimg.cn/e6eac48bd4de480482422080c72919ea.gif)

 这里打印结果没啥作用，其实你们可以试一下，在 OnApplicationQuit() 不加 threadA.Abort() 方法的时候，Unity 结束运行时你会发现还是会有打印效果。

### 5. 做一个按钮控制开关线程

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System.Threading;
 
public class ThreadTest : MonoBehaviour
{
    [SerializeField] Button btn;
    Thread threadA;
    void Start()
    {
        threadA = new Thread(AA);
        threadA.Start();
 
        btn.onClick.AddListener(delegate {
            btn.transform.GetChild(0).GetComponent<Text>().text = isStart ? "开启" : "暂停";
            isStart = !isStart; 
        });
    }
 
    bool isStart = false;
    //无参
    void AA()
    {
        //死循环 每过1秒执行一次
        while (true)
        {
            if (isStart)
            {
                Debug.Log("A线程执行");
                Thread.Sleep(1000); //1000毫秒 等待1秒钟
            }
        }
    }
    
    void OnApplicationQuit()
    {
        //结束线程必须关闭 否则下次开启会出现错误 （如果出现的话 只能重启unity了）
        threadA.Abort();
    }
 
}
```

结果： 

![](https://img-blog.csdnimg.cn/892b3b6a7fa34048b8fbbab49c4c69b8.gif)

###  6. 使用协程控制线程一秒打印一次

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System.Threading;
using System.IO;
 
public class ThreadTest : MonoBehaviour
{
    Thread threadA;
    void Start()
    {
        threadA = new Thread(AA);
        threadA.Start();
        StartCoroutine(Test());
    }
 
    IEnumerator Test()
    {
        while (true)
        {
            isEnd = true;
            yield return new WaitForSeconds(1f);
        }
    }
 
    bool isEnd = false;
    //无参
    void AA()
    {
        while (true)
        {
            if (isEnd)
            {
                isEnd = false;
                Debug.Log("A线程执行");
            }
        }
 
    }
 
    void OnApplicationQuit()
    {
        //结束线程必须关闭 否则下次开启会出现错误 （如果出现的话 只能重启unity了）
        threadA.Abort();
    }
 
}
```

### 六、线程池的使用

>  .NET Framework 的 ThreadPool 类提供一个线程池，该线程池可用于执行任务、发送工作项、处理异步 I/O、代表其他线程等待以及处理计时器。那么什么是线程池？线程池其实就是一个存放线程对象的 “池子 (pool)”，他提供了一些基本方法，如：设置 pool 中最小 / 最大线程数量、把要执行的方法排入队列等等。ThreadPool 是一个静态类，因此可以直接使用，不用创建对象。

有点类似 Unity 中的对象池，当要使用线程的时候我们线程池查找是否有空闲的线程，有就使用，没有就创建生成。

微软官网说法如下：

> 许多应用程序创建大量处于睡眠状态，等待事件发生的线程。还有许多线程可能会进入休眠状态，这些线程只是为了定期唤醒以轮询更改或更新的状态信息。 线程池，使您可以通过由系统管理的工作线程池来更有效地使用线程。 

所以线程池一般是在需要大量线程，并且线程的数据处理都很小的情况下使用

使用方法很简单：

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System.Threading;
using System.IO;
 
public class ThreadTest : MonoBehaviour
{
    void Start()
    {
        ThreadPool.QueueUserWorkItem(new WaitCallback(AA), null);
    }
 
    //无参
    void AA(object a)
    {
        Debug.Log("A线程执行");
    }
 
}
```

这里要注意几点：

> 1. 线程池的方法必须是有参方法，而且传参不能超过 2 个
> 
> 2. 如果方法使用死循环，Unity 结束运行后，还是会执行线程方法。