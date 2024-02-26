> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484110&idx=1&sn=f4913085287d6f9a2c921e1127575025&chksm=ce0723c1f970aad73a9235043c9c9b2e34600dde6410214200fd9791c809f692cf4577afd8dc&scene=178&cur_album_id=3285418518473310211#rd)

#### **Unity 事件中心框架**

Unity 作为一款强大的游戏开发引擎，提供了丰富的工具和框架，其中事件中心框架是一个备受关注的重要组成部分。本文将深入探讨 Unity 事件中心框架的重要性以及它在游戏开发中的作用。

#### **什么是事件中心框架？**

事件中心框架是一种设计模式，它允许游戏中的不同部分之间进行松耦合的通信。在 Unity 中，这一框架通过使用 C# 的委托和事件机制来实现。通过事件中心，游戏中的各个模块可以订阅和触发事件，实现模块之间的解耦和灵活性。

#### **为什么事件中心框架如此重要？**

##### **1. 解耦性**

在游戏开发中，各个模块之间的紧密耦合可能导致代码难以维护和扩展。事件中心框架通过允许模块之间通过事件进行通信，降低了它们之间的依赖性，使得代码更加清晰、可读和易于维护。

##### **2. 灵活性**

事件中心框架为游戏开发提供了更大的灵活性。模块可以选择订阅感兴趣的事件，而不需要了解其他模块的具体实现细节。这使得在不影响整体结构的情况下进行修改和更新变得更加容易。

##### **3. 模块化**

通过将不同功能的代码封装成模块，并通过事件中心进行通信，游戏开发可以更容易地实现模块化。这种模块化的设计使得团队能够更好地协作，每个成员可以专注于自己负责的部分而无需关心整个项目的细节。

#### **基础的事件中心**

前提技术：需要观察者模式，单例模式，委托，Dictionary

不能传递带参数的方法  

```c#
using System.Collections.Generic;
using UnityEngine.Events;
public class EventCenter : BaseSingleton<EventCenter>
{
    //key:事件的名字（例如：怪物死亡，玩家死亡，通过...）
    //value:监听的事件，对于委托函数们
    private Dictionary<string, UnityAction> eventDic = new Dictionary<string, UnityAction>();

    /// <summary>
    /// 添加事件监听
    /// </summary>
    /// <param name="name">事件的名字</param>
    /// <param name="action">处理此事件的委托函数</param>
    public void AddEventListner(string name,UnityAction action)
    {
        //存在此事件
        if (eventDic.ContainsKey(name))
        {
            eventDic[name] += action;
        }
        //不存在此事件
        else
        {
            eventDic.Add(name, action);
        }
    }
    /// <summary>
    /// 移除某事件监听
    /// </summary>
    /// <param name="name"></param>
    /// <param name="action"></param>
    public void RemoveEventListner(string name,UnityAction action)
    {
        if (eventDic.ContainsKey(name))
            eventDic[name] -= action;
    }
    /// <summary>
    /// 事件触发，触发多播委托
    /// </summary>
    /// <param name="name"></param>
    public void EventTrigger(string name)
    {
        //执行委托
        //eventDic[name]();
        //另外一种写法，效果相同
        eventDic[name].Invoke();
    }
    /// <summary>
    /// 清除所有事件，切换场景时调用
    /// </summary>
    public void Clear()
    {
        eventDic.Clear();
    }
}
```

#### **通用的事件中心**

可以添加带任意参数的方法，参数以 object 的形式传递，涉及装箱拆箱。

```c#
using System.Collections.Generic;
using UnityEngine.Events;
public class EventCenter : BaseSingleton<EventCenter>
{
    //key:事件的名字（例如：怪物死亡，玩家死亡，通过...）
    //value:监听的事件，对于委托函数们
    // UnityAction<object>,委托函数有一个参数，参数类型是object，用来传递信息（单个信息怪物类型，可以是个数组传多个信息）
    private Dictionary<string, UnityAction<object>> eventDic = new Dictionary<string, UnityAction<object>>();

    /// <summary>
    /// 添加事件监听
    /// </summary>
    /// <param name="name">事件的名字</param>
    /// <param name="action">处理此事件的委托函数</param>
    public void AddEventListner(string name,UnityAction<object> action)
    {
        //存在此事件
        if (eventDic.ContainsKey(name))
        {
            eventDic[name] += action;
        }
        //不存在此事件
        else
        {
            eventDic.Add(name, action);
        }
    }
    /// <summary>
    /// 移除某事件监听
    /// </summary>
    /// <param name="name"></param>
    /// <param name="action"></param>
    public void RemoveEventListner(string name,UnityAction<object> action)
    {
        if (eventDic.ContainsKey(name))
            eventDic[name] -= action;
    }
    /// <summary>
    /// 事件触发，触发多播委托
    /// </summary>
    /// <param name="name"></param>
    public void EventTrigger(string name,object info)
    {
        //执行委托
        //eventDic[name]();
        //另外一种写法，效果相同
        eventDic[name].Invoke(info);
    }
    /// <summary>
    /// 清除所有事件，切换场景时调用
    /// </summary>
    public void Clear()
    {
        eventDic.Clear();
    }
}
```

#### **如何在 Unity 中使用事件中心框架？**

在 Unity 中，事件中心框架的使用相对简单。通过定义事件和委托，然后在需要的地方订阅和触发这些事件，就能够实现模块之间的通信。

以下是一个简单的例子：

使用通用的事件中心，可以在不同的类中都调用事件中心，使用事件中心充当沟通桥梁，而不用类与类之间互相调用产生耦合。

##### **Player 类**  

```c#
public class Player : MonoBehaviour
{
    private void Awake()
    {
        //在事件中心添加监听"MonsterDead"，然后就执行MonsterDeadDo方法
        EventCenter.GetInstance.AddEventListner("MonsterDead", MonsterDeadDo);
    }
    public void MonsterDeadDo(object info)
    {
        //通过info获得传入的信息
        print($"玩家获得奖励{(info as Monster).name}死了后触发");
    }
    private void OnDestroy()
    {
        EventCenter.GetInstance.RemoveEventListner("MonsterDead", MonsterDeadDo);
    }

}
```

##### **Other 类**

```c#
public class Other : MonoBehaviour
{
    private void Awake()
    {
        EventCenter.GetInstance.AddEventListner("MonsterDead", DoSomething);
    }
    public void DoSomething(object info)
    {
        print($"其他角色做了某些操作在{(info as Monster).name}死了后触发");
    }
    private void OnDestroy()
    {
        EventCenter.GetInstance.RemoveEventListner("MonsterDead", DoSomething);
    }
}
```

##### **Monster 类**

```c#
public class Monster : MonoBehaviour
{
    int tag = 1;
    string name = "哥斯拉";
    public void Start()
    {
        Dead();
    }
    public void Dead()
    {
        print("敌人死亡");
        //然后触发事件中心的这个事件，让监听的都进行操作，并传入自己(Monster脚本)作为参数
        EventCenter.GetInstance.EventTrigger("MonsterDead", this);
    }
}
```

##### **调用测试结果**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakkKjVJVfbt6icC2rmET65ic6GmXfaBF2elnkRlGNar3DeblxxQyGKb8FzOjQhTqV1kDl3z0u4k0iaz7g/640?wx_fmt=png&from=appmsg)

以上代码使用 EventCenter.GetInstance 获取事件中心单例，调用其中的添加监听的方法实现事件监听。Player 和 Other 都监听了 MonsterDead 这个事件，并加入了这个事件触发时会执行的方法。然后 Monster 类中执行了死亡的事件，结果自动触发了 Player 和 Other 的相应方法。

#### **结论**

Unity 事件中心框架是实现游戏开发中松耦合、灵活和模块化设计的重要工具。通过合理使用事件中心框架，开发者可以更好地组织和管理代码，提高项目的可维护性和可扩展性。在今后的游戏开发中，深入理解并善用事件中心框架将为开发者带来更加高效和愉悦的开发体验。

本文需要一定基础才能理解，理解不了可以收藏关注反复观看

单例模式可以看我之前这篇：

[Unity 重要框架之单例模式框架](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484067&idx=1&sn=c48d8782ec03236fcccc17f00c67bc0a&chksm=ce0723acf970aaba56ea34782f8d8c68f04ca18e045796e4d97724b680272d981d3a0d7f4170&scene=21#wechat_redirect)  

观察者模式可以看这篇：

[unity 游戏设计必备利器：观察者模式](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484014&idx=1&sn=d9464b228d84c3d0bfce11cb03528164&chksm=ce072361f970aa77fad2ab3e2afc93ee365fa1d819dba6d923a33af243a817790b4d1d179cd1&scene=21#wechat_redirect)

如有错误欢迎指出。