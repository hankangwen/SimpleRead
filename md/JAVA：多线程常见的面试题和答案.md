> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/_rh2h4xzU21uYs9Sjz9qbQ)

**1、并发编程三要素？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 原 子 性

原子性指的是一个或者多个操作，要么全部执行并且在执行的过程中不被其他操作打断，要么就全部都不执行。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 可 见 性

可见性指多个线程操作一个共享变量时，其中一个线程对变量进行修改后，其他线程可以立即看到修改的结果。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 有 序 性

有序性，即程序的执行顺序按照代码的先后顺序来执行。

**1、Java 中的 volatile 关键字有什么作用？**

答：volatile 关键字在 Java 中主要用于变量的同步，其核心作用可以概括为两点：

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 保证内存可见性：当一个变量定义为 volatile 之后，它会保证对所有线程的可见性。这意味着当一个线程修改了一个 volatile 变量的值，新值对于其他线程来说是立即可见的。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 禁止指令重排序：volatile 还可以防止指令重排序优化。在没有 volatile 修饰的多线程程序中，为了提高性能，编译器和处理器可能会对指令进行重排序，但是一旦变量被 volatile 修饰，就会禁止这种重排序，以确保程序的执行顺序与代码的顺序相同。

虽然 volatile 可以保证单次读 / 写的原子性，但它无法保证整个操作的原子性。例如，volatile 变量的 i++ 操作无法保证原子性。

**2、创建线程的方式有哪些？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 通过继承 Thread 类创建线程类

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 实现 Runnable 接口创建线程类

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 通过 Callable 和 Future 接口创建线

**3、Java 如何保证线程安全？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 使用同步代码块

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 使用同步方法

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 使用 Lock 锁机制， 通过创建 Lock 对象，采用 lock() 加锁，unlock() 解锁，来保护指

定的代码块。

**4、描述 Synchronized、ReentrantLock 的区别 ？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) synchronized 是关键字，ReentrantLock 是 API 接口

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) Lock 需要手动加锁，手动释放锁

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) synchronized 不可中断，ReentrantLock 可中断、可超时

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) synchronized 是非公平锁，ReentrantLock 公平、非公平皆可

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) ReentrantLock 支持 Condition，多条

**5、在 Java 中 wait 和 sleep 方法的不同？**

答：通常会在电话面试中经常被问到的 Java 线程面试问题。最大的不同是在等待时 wait 会释放锁，而 sleep 一直持有锁。Wait 通常被用于线程间交互，sleep 通常被用于暂停执行。

**6、为什么我们调用 start() 方法时会执行 run() 方法，为什么我们不能直接调用 run() 方法？**

答：当你调用 start() 方法时你将创建新的线程，并且执行在 run() 方法里的代码 。但是如果你直接调用 run() 方法，它不会创建新的线程也不会执行调用线程的代码 ，只会把 run 方法当作普通方法去执行。

**7、Java 中用到的线程调度算法是什么？**

答：计算机通常只有一个 CPU, 在任意时刻只 能执行一条机器指令, 每个线程只有获得 CPU 的使用权才能 执行指令 . 所谓多线程的并发运行, 其实是指从宏观上看, 各个线程轮流获得 CPU 的使用权, 分别执行 各自的任务. 在运行池中, 会有多个处于就绪状态的线程在等待 CPU,JAVA 虚拟机的 一项任务就是负责线程 的调度 , 线程调度是指按照特定机制为多个线程分配 CPU 的使用权。

**有两种调度模型：分时调度模型和抢占式调度模型。**

分时调度模型是指让所有的线程轮流获得 cpu 的使 用权, 并且平均分配每个线程占用的 CPU 的时间片这个也比较好理解。

java 虚拟机采用抢占式调度模型，是指优先让可运行池中优先级高的线程占用 CPU，如果可运行池中 的线程优 先级相同，那么就随机 选择一个线程，使其占用 CPU。处于运行状态的 线程会一 直运行，直至它不得不 放弃 CPU。

**8、什么是 Daemon 线程？它有什么意义？**

答：所谓后台 (daemon) 线程，是指在程序运行的时候在后台提供一种通用服务的线程，并且这个线程并不属于程序中不可或缺的部分。因此，当所有的非后台线程结束时，程序也就终止了，同时会杀死进程中的所有后台线程。反过来说，只要有任何非后台线程还在运行，程序就不会终止。必须在线程启动之前调用 setDaemon()方法，才能把它设置为后台线程。

**注意：后台进程在不执行 finally 子句的情况下就会终止其 run() 方法。**

比如：JVM 的垃圾回收线程就是 Daemon 线程 ，Finalizer 也是守护线程。

**9、CyclicBarrier 和 CountDownLatch 的区别**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CountDownLatch 简单的说就是一个线程等待，直到他所等待的其他线程都执行完成并且调用 countDown() 方法发出通知后，当前线程才可以继续执行。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) cyclicBarrier 是所有线程都进行等待，直到所有线程都准备好进入 await() 方法之后，所有线程同时开始执行！

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CountDownLatch 的计数器只能 使用一次。而 CyclicBarrier 的计数器可以使用 reset() 方法重置。所以 CyclicBarrier 能处理更为复杂的业务场景，比如如果计算发生错误，可以重置计数器，并让线程们重新执行一次。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CyclicBarrier 还提供其他有用的方法，比如 getNumberWaiting 方法可以获得 CyclicBarrier 阻塞的线程数量。isBroken 方法用来知道阻塞的线程是否被中断 。如果被中断返回 true，否则返回 false。

**10、什么是 CAS 与其 常见的问题？**

答：CAS 是一种基于锁的操作，而且是乐观锁。在 java 中锁分为乐观锁和悲观锁。悲观锁是将资源锁住，等一个之前获得锁的线程释放锁之后，下一个线程才可以访问。而乐观锁采取了一种宽泛的态度，通过某种方式不加锁来处理资源，比如通过给记录加 version 来获取数据，性能较悲观锁有很大的提高。

CAS 常见的问题：

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CAS 容 易 造 成 ABA 问 题

一个线程 a 将数值改成了 b，接着又改成了 a，此时 CAS 认为是没有变化，其实是已经变化过了，而这个问题的解决方案可以使用版本号标识，每操作一次 version 加 1。在 java5 中，已经提供了 AtomicStampedReference 来解决问题。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)  不 能 保 证 代 码 块 的 原 子 性

CAS 机制所保证的知识一个变量的原子性操作 ，而不能保证整个代码块的原子性。比如需要保证 3 个变量共同进行原子性的更新，就不得不使用 synchronized 了。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CAS 造 成 CPU 利 用 率增 加

之前说过了 CAS 里面是一个循环判断的过程，如果线程一直没有获取到状态，cpu 资源会一直被占用

**11、线程池的优点？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 重用存在的线程，减少对象创建销毁的开销。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 可有效的控制最大并发线程数，提高系统资源的使用率，同时避免过多资源竞争，避免堵塞。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 提供定时执行、定期执行、单线程、并发数控制 等功能。

**12、常用的并发工具类有哪些？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CountDownLatch

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CyclicBarrier

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) Semaphore

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) Exchanger

**13、Java 线程具有五中基本状态**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 新 建 状 态（New）：当线程对象对创建后，即进入了新建状态，如：Thread t = new MyThread()；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)  就 绪 状 态 （ Runnable） ：当 调用线程对象的 start() 方法（t.start();），线程即进入就绪状态。处于就绪状态的线程，只是说明此线程已经做好了准备，随时等待 CPU 调度执行，并不是说执行了 t.start() 此线程立即就会执行；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 运 行 状 态 （ Running）：当 CPU 开始调度处于就绪状态的线程时，此时线程才得以真 正执行，即进入到 运行状态 。注：就 绪状 态是进入到运 行状态的 唯一入口，也就是说，线程要想进入运行状态执行，首先必须处于就绪状态中；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 阻 塞 状 态（Blocked）：处于运行状态中的线程由于某种原因，暂时放弃对 CPU 的使用权 ，停止执行 ，此时进入阻塞 状态，直到其进 入到就绪状态 ，才 有机 会再次被 CPU 调用以进入到运行状态。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 死 亡 状 态（Dead）：线程执行完了或者因异常退出了 run() 方法，该线程结束生命周期

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUE1sEWxHZApV2A5rN9ceV2H5Uf1sgRH4NXzfOBNHIkaibvR9mgOr2DNf3LLnUwBwLJeGa1HovrHcwQ/640?wx_fmt=png&from=appmsg)

**14、线程池的创建方式有哪些**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newSingleThreadExecutor() 创建一个单线程化的线程池；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newFixedThreadPool() 创建固定线程数量的线程池；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newCachedThreadPool() 创建一个可缓存的线程池，若线程数超过处理所需，缓存一段时间后会回收，若线程数不够，则新建线程。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newScheduledThreadPool() 创建一个可以延迟或定期执行任务的线程池；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newSingleThreadScheduledExecutor() 创建一个单线程执行器，该执行器可以安排命令在给定延迟后运行，或定期执行；

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) newWorkStealingPool() 使用可用处理器数量作为其目标并行度级别创建工作窃取线程池 [ JDK1.8 新增]。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 创建 ThreadPoolExecutor 对象来实现自定义线程池创建

FixedThreadPool 和 SingleThreadExecutor 传入的最后一个参数阻塞队列 ”workQueue“，默认的长度 INTEGER.MAX_VALUE，而它们允许的最大线程数量又是有限的，所以当请求线程的任务过多线程不够用时，它们会在队列中等待，又因为队列的长度特别长，所以可能会堆积大量的请求，导致 OOM。

CachedThreadPool 和 ScheduledThreadPool 它们的阻塞队列长度有限，但是传入的第二个参数 maximumPoolSize 为 Integer.MAX_VALUE，这就意味着当请求线程的任务过多线程不够而且队列也满了的时候，线程池就会创建新的线程，因为它允许的最大线程数量是相当大的，所以可能会创建大量线程，导致 OOM。

**15、synchronized 的作用？**

答：在 Java 中，synchronized 关键字是用来控制线程同步的，就是在多线程的环境下，控制 synchronized 代码段不被多个线程同时执行。synchronized 既可以加在一段代码上，也可以加在方法上。

**16、什么是 AQS**

答：AQS 是 AbustactQueuedSynchronizer 的简称， 它是一个 Java 提高的底层同步工具类，用一个 int 类型的变量表示同步状态，并提供了一系列的 CAS 操作来管理这个同步状态。

AQS 是一个用来构建锁和同步器的框架，使用 AQS 能简单且高效地构造出应用广泛的大量的同步器，比如我们提到的 ReentrantLock，Semaphore，其他的诸如 ReentrantReadWriteLock，SynchronousQueue，FutureTask 等等皆是基于 AQS 的。

AQS 支持两种同步方式：

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 独占式

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 共享式

**17、sleep 方法和 wait 方法有什么区别?**

答：这个问题常问，sleep 方法和 wait 方法都可以用来放弃 CPU 一定的时间，不同点在于如果线程持有某个对象的监视器，sleep 方法 不会放弃这个对象的监 视器，wait 方法会放弃这个对象的监视器。

**18、ThreadLocal 是什么？有什么用？**

答：ThreadLocal 是一个本地线程副本变量工 具类。主要用于将私有线程和该 线程存放的副本对象做一个映射，各个线程之间的变量互不干扰，在高并发场景下，可以实现无状态的调用，特别适用于各个线程依赖不通的变量值完成操作的场景。简单说 ThreadLocal 就是一种以空间换 时间的做法，在每个 Thread 里面维护了一个以开地址法实现的 ThreadLocal.ThreadLocalMap，把数据进行隔离，数据不共享，自然就没有线程安全方面的问题了。

**19、ConcurrentHashMap 的并发度是什么**

答：ConcurrentHashMap 的并 发度 就是 segment 的大 小， 默认 为 16，这 意味 着最多同 时可 以有 16 条线 程操 作 ConcurrentHashMap，这 也是 ConcurrentHashMap 对 Hashtable 的最 大优 势， 任何 情 况下 ，Hashtable 能同时有 两条 线程 获取 Hashtable 中的 数据 吗？

**20、什么是多线程的上下文切换**

答：多线程的上下文切换是指 CPU 控制权由 一个已经正在运行的线程切换到另外一个就绪并等待获取 CPU 执行权的线程的过程。

**21、什么是线程调度器 (Thread Scheduler) 和时间分片(TimeSlicing)？**

答：线程调度器是一个操作系统服务，它负责为 Runnable 状态的线程分配 CPU 时间。一旦我们创建一个线程并启动它，它的执行便依赖于线程调度器的实现。

时间分片是指将可用的 CPU 时间分配给可用的 Runnable 线程的过程。分配 CPU 时间可以基于线程优先级或者线程等待的时间。线程 调度并不受到 Java 虚拟机控制，所以由应用程序来控制它是更好的选择（也就是说不要让你的程序依赖于线程的优先级）。

**22、Java 线程数过多会造成什么异常？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)  线 程 的 生 命 周 期 开 销 非 常 高

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 消 耗 过 多 的 CPU 资源

如果可运行的线程数量多于可用处理器的数量，那么有线程将会被闲置。大量空闲的线程会占用许多内存，给垃圾回收器带来压力，而且大量的线程在竞争 CPU 资源时还将产生其他性能的开销。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 降 低 稳 定 性

JVM 在可创建线程的数 量上存在一个限制 ，这个限制值将随着平台的不同而不同，并且承受着多个因素制约，包括 JVM 的启动参数、Thread 构造函数中请求栈的大小，以及底层操作系统对线程的限制等。如果破坏了这些限制，那么可能抛出 OutOfMemoryError 异常。

**23、线程池中核心线程数量大小怎么设置？**

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) CPU 密集型任务：

比如像加解密，压缩、计算等一系列需要大量耗费 CPU 资源的任务，大部分场景下都是纯 CPU 计算。尽量使用较小的线程池，一般为 CPU 核心数 + 1。因为 CPU 密集型任务使得 CPU 使用率很高，若开过多的线程数，会造成 CPU 过度切换。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) IO 密集型任务：

比如像 MySQL 数据库、文件的读写、网络通信等任务，这类任务不会特别消耗 CPU 资源，但是 IO 操作比较耗时，会占用比较多时间。可以使用稍大的线程池，一般为 2*CPU 核心数。IO 密集型任务 CPU 使用率并不高，因此可以让 CPU 在等待 IO 的时候有其他线程去处理别的任务，充分利用 CPU 时间。

另外：线程的平均工作时间所占比例越高，就需要越少的线程；线程的平均等待时间所占比例越高，就需要越多的线程；

以上只是理论值，实际项目中建议在本地或者测试环境进行多次调优，找到相对理想的值大小。

**24、说说 submit(和 execute 两个方法有什么区别？**

答：submit() 和 execute() 都是用来执行线程池的，只不过使用 execute() 执行线程池不能有返回方法，而使用 submit() 可以使用 Future 接收线程池执行的返回值。

**25、volatile 如何保证可见性？**

答：Volatile 是通过 MESI 缓存一致性协议和总线嗅探机制来保证可见性的

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)   什么是 MESI 协议？

MESI 协议其实是一个变量在内存中的不同状态！MESI 是指 4 种状态的首字

```
M 修改 (Modified) 当一个线程要修改便令
E 独享、互斥 (Exclusive) 当一个线程拿到了共享变量，此时为独享状态！
S 共享 (Shared) 当多个线程都拿到了共享变量，此时为共享状态！
I 无效 (Invalid) 线程丢弃了自己工作内存中的变量，为无效状态！
```

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) MESI 协议如何保证可见性？

首先 cpu 会根据共享变量是否带有 Volatile 字段，来决定是否使用 MESI 协议保证缓存一致性。如果有 Volatile，汇编层面会对变量加上 Lock 前缀，当一个线程修改变量的值后，会马上经过 store、write 等原子操作修改主内存的值（如果不加 Lock 前缀不会马上同步），为什么监听到修改会马上同步呢？就是为了触发 cpu 的嗅探机制，及时失效其他线程变量副本。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) cpu 总线嗅探机制

cpu 总线嗅探机制监听到这个变量被修改，就会把其他线程的变量副本由共享 S 置为无效 I，当其他线程在使用变量副本时，发现其已经无效，就回去主内存中拿一个最新的值。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) 在写入主内存时为什么要加锁？在哪里加锁？

变量被修改后同步到主内存的过程中会在 store 之前加锁，写完后解锁，这个锁只有在修改的时候才会加，锁粒度非常小。因为在 store 时可能已经经过了总线，但此时还没有 write 进主内存，总线却触发了嗅探机制，其他线程的变量已失效，当其他线程去主内存读最新数据时，新数据还未 write 进来，产生脏数据！

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGOfFHtGoZE2JavBvCqgfIbJV2fUjf67YaSTcajIHwBzNaqZvWBgx9TkiaO159L7LkQE4m8B8BGGCw/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp) Lock 前缀的作用

使 CPU 缓存数据立即写会主内存（Volatile 修饰的变量会带 lock 前缀）触发总线嗅探机制和缓存一致性协议 MESI 来失效其他线程的变量

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUE1sEWxHZApV2A5rN9ceV2H1zzEwT0rDC21DbANpCkRxOTDImD2mkDFibxuaa2iczsgWB1G1KaPDCMg/640?wx_fmt=png&from=appmsg)