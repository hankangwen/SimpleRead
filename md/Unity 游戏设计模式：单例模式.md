> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247483989&idx=1&sn=5570ff817c9090676f0081e82be98dbd&chksm=ce07235af970aa4c21c970091396cd1b12bd6576428f9876d5238615d445597f7dd2723ab386&scene=178&cur_album_id=3218779881132752901#rd)

**单例模式**

在 C# 游戏设计中，单例模式是一种常见的设计模式，它的主要目的是确保一个类只有一个实例，并提供一个全局访问点。单例模式在游戏开发中具有以下几个作用：

1. 全局访问点：单例模式确保只有一个类的实例存在，并提供一个全局的访问点，这样在整个游戏中的任何地方都可以访问该实例。这对于管理全局的游戏状态、资源管理器或其他共享的对象非常有用。

2. 资源共享：在游戏中，可能有一些需要全局访问的资源，例如音频管理器、网络管理器等。使用单例模式可以确保这些资源只有一个实例，避免资源的重复创建和管理。

**2 种类型单例模式**

**1. 饿汉模式**

形容一旦使用就占用内存，吃内存![](https://mmbiz.qpic.cn/mmbiz_gif/QzpHS4dMic6IH8wrCnMicRKjFBIgxZLK6aM9GMicSmptN10FWp8LJMcmbCYFyuuvsxYRorAwogBjicYtRXibXaHhvSQ/640)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakkibNYj9Lfqzf2DbnuYXPjiautNuicRIjiczxRm46PMMibBKMOTLeJ09n6OC7Ox2XxfluEARQfQjERpBdQ/640)

比如使用了类的静态成员，但是静态成员又和实例对象无关，然后就创建了实例对象浪费资源。

创建单例类：

```c#
class Singleton
{
    private static Singleton instance=new Singleton();
    //私有的构造函数，保证在外部不能new
    private Singleton(){}
    //公共静态属性，提供全局访问点
    public static Singleton Instance
    {
        get
        {
            return instance;
        }
    }
    //其他方法
}
```

使用举例：

```c#
//在主函数使用
Singleton singleton1 = Singleton.Instance;
Singleton singleton2 = Singleton.Instance;
//就可以使用singleton这一个单例了
//这样singleton1和singleton2都只保存了同一个对象实例，不会出现其他实例，保证了对象的单一性
```

**2. 饱汉模式（懒汉）**

静态成员会在其所在类首次被使用时才初始化

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakkibNYj9Lfqzf2DbnuYXPjiaukxrDemIAKToE8yAdYLiaHeqgRCHM3ueKswHtQvOPFzjKrgaemUqz6lA/640)

```c#
class Singleton //饱汉懒汉模式
{
    private static Singleton instance;
    private Singleton(){}
    public static Singleton Instance//只有访问了成员属性Instance后，才会创建instance实例
    {
        get
        {
            if (instance == null)
            {
                instance = new Singleton();//创建实例
            }
            return instance;
        }
    }
}
```

上面的属性访问器不是线程安全的，因为没加锁，下面的是线程安全的，但也就仅是创建时安全。

```c#
class Singleton //饱汉懒汉模式，线程安全版
{
    private static Singleton instance;
    private static Object obj=new Object();//用来使用lock
    private Singleton(){}
    public static Singleton Instance//只有访问了成员属性Instance后，才会创建instance实例
    {
        get
        {
            lock(obj){
                if (instance == null)
                {
                    instance = new Singleton();//创建实例
                }
            }

            return instance;
        }
    }
}

```

**3.c# 提供的饱汉模式泛型类**

Lazy<T>

延迟初始化:

Lazy<T> 会保存一个工厂方法，该方法用于创建对象。只有在第一次访问 Lazy<T>.Value 属性时，工厂方法才会被调用，从而创建对象。

线程安全:

Lazy<T> 可以配置为线程安全，这意味着在多线程环境中，只有一个线程可以执行工厂方法创建对象。这确保了对象的单一实例。

缓存:

一旦对象被创建，Lazy<T> 会缓存该对象。后续对 Value 属性的访问将返回相同的对象实例。

使用 Lazy 只能解决单件实例创建时的线程安全问题，不能解决买卖物品的线程安全问题

![](https://mmbiz.qpic.cn/mmbiz_gif/QzpHS4dMic6IH8wrCnMicRKjFBIgxZLK6aM9GMicSmptN10FWp8LJMcmbCYFyuuvsxYRorAwogBjicYtRXibXaHhvSQ/640)

```c#
class Singleton//c#自带的懒汉类
{
    //传入一个回调函数（委托函数）
    private static readonly Lazy<Singleton> instance = new Lazy<Singleton>(() => new Singleton());
    private Singleton() { }
    public static Singleton Instance
    {
        get
        {
            return instance.Value;//调用Lazy类里面的属性访问器Value，然后Value就会调用上面的回调函数（lamda表达式）
        }
    }
}
```

  

总的来说，单例模式在游戏设计中提供了一种有效的方式来管理全局状态和共享资源，使得代码更容易维护和扩展。