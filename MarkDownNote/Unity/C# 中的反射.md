> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg4MDU1ODI2Mg==&mid=2247483844&idx=1&sn=ca402da910a3e41d996f3c9a096276dc&scene=19#wechat_redirect)

点击上方 “**游戏程序员聚集地**”，进行关注  

更无花态度，全有雪精神。

### 反射（Reflection）的用途

它允许在运行时查看特性（attribute）信息。  
它允许审查集合中的各种类型，以及实例化这些类型。  
它允许延迟绑定的方法和属性（property）。  
它允许在运行时创建新类型，然后使用这些类型执行一些任务。

> 1. 反射指程序可以访问、检测和修改它本身状态或行为的一种能力。  
> 2. 程序集包含模块，而模块包含类型，类型又包含成员。反射则提供了封装程序集、模块和类型的对象。  
> 3. 可以使用反射动态地创建类型的实例，将类型绑定到现有对象，或从现有对象中获取类型。然后，可以调用类型的方法或访问其字段和属性。

反射是一个十分简单而又灵活的东西, 用好了, 它就像一只温驯的猫, 用不好, 它就是被猫玩耍后的毛线团.

优缺点

优点:  
1. 反射提高了程序的灵活性和扩展性。  
2. 降低耦合性，提高自适应能力。  
3. 它允许程序创建和控制任何类的对象，无需提前硬编码目标类。

缺点：  
1. 性能问题：使用反射基本上是一种解释操作，用于字段和方法接入时要远慢于直接代码。因此反射机制主要应用在对灵活性和拓展性要求很高的系统框架上，普通程序不建议使用。  
2. 使用反射会模糊程序内部逻辑；程序员希望在源代码中看到程序的逻辑，反射却绕过了源代码的技术，因而会带来维护的问题，反射代码比相应的直接代码更复杂。

> Show Code

在 unity 中新建一个脚本测试代码

那么这个脚本是需要来被使用的

```
 1public class Drawed
 2{
 3    public int Num1;
 4    public int Num2;
 5    public string Str1;
 6    public Drawed() 
 7    {
 8        Num1 = 1;
 9        Num2 = 1;
10        Str1 = "Hi,I am Jtro !";
11    }
12
13    public int GetNum1()
14    {
15        return Num1;
16    }
17
18    public string GetStr()
19    {
20        return Str1;
21    }
22
23    public string SayHello(string Greeting, string Name)
24    {
25        return Greeting + "," + Name;
26    }
27}


```

然后在新建一个 UseDraw 脚本, 挂在摄像机上

```
 1using System.Collections;
 2using System.Collections.Generic;
 3using System.Reflection;
 4using UnityEngine;
 5
 6public class UseDraw : MonoBehaviour
 7{
 8    public Drawed drawed = new Drawed();
 9
10    string Greeting = "Hello";
11    string Name = "I am Jtro";
12
13    // Start is called before the first frame update
14    void Start()
15    {
16        MethodInfo getnum1 = drawed.GetType().GetMethod("GetNum1");
17        Debug.Log(getnum1.Invoke(drawed, null));
18
19        MethodInfo getstr = drawed.GetType().GetMethod("GetStr");
20        Debug.Log(getstr.Invoke(drawed, null));
21
22        MethodInfo sayHello = drawed.GetType().GetMethod("SayHello");
23        string [] obj = new string[] {Greeting ,Name };//对于反射中传入值的一个封装
24        Debug.Log(sayHello.Invoke(drawed, obj));
25
26    }
27
28    // Update is called once per frame
29    void Update()
30    {
31
32    }
33}


```

其中前两个反射方法很简单, 没有传值, 第三个方法中呢, 是需要传入一些值的,  
在得到了 MethodInfo 之后呢, 用 invoke 就可以执行该方法:  

invoke 原型如下:

```
1object Invoke (object obj,object[] parameters);



```

<table data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)"><thead data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)"><tr data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="font-size: inherit; color: inherit; line-height: inherit; margin: 0px; padding: 0px; border-color: rgb(204, 204, 204) currentcolor currentcolor; border-style: solid none none; border-width: 1px 0px 0px; background-color: white;"><th width="164.33333333333334" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(40, 40, 40)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)|rgb(240, 240, 240)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left; font-weight: bold; background-color: rgb(240, 240, 240);">参数</th><th width="360.3333333333333" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(40, 40, 40)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)|rgb(240, 240, 240)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left; font-weight: bold; background-color: rgb(240, 240, 240);">说明</th></tr></thead><tbody data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)"><tr data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="font-size: inherit; color: inherit; line-height: inherit; margin: 0px; padding: 0px; border-color: rgb(204, 204, 204) currentcolor currentcolor; border-style: solid none none; border-width: 1px 0px 0px; background-color: white;"><td width="136" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left;">obj</td><td width="360.3333333333333" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left;">一个对象引用, 将调用它所指向的对象上的方法</td></tr><tr data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="font-size: inherit; color: inherit; line-height: inherit; margin: 0px; padding: 0px; border-color: rgb(204, 204, 204) currentcolor currentcolor; border-style: solid none none; border-width: 1px 0px 0px; background-color: white;"><td width="136" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left;">parameters</td><td width="360.3333333333333" data-darkmode-color-16594898996061="rgb(163, 163, 163)" data-darkmode-original-color-16594898996061="#fff|rgb(62, 62, 62)" data-darkmode-bgcolor-16594898996061="rgb(25, 25, 25)" data-darkmode-original-bgcolor-16594898996061="#fff|rgb(255,255,255)" data-style="color: inherit; line-height: inherit; margin: 0px; font-size: 1em; border-color: rgb(204, 204, 204); border-style: solid; border-width: 1px; padding: 0.5em 1em; text-align: left;">所有需要传递方法的参数都必须在 parameters 数组中指定, 如果这个方法中没有参数, 那么也要写一个 "null"</td></tr></tbody></table>

运行结果如下:

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aQSLV4maljGpU6kW4GEa8ZGjtBdrHaBiaibarUibLnegQBSbmRZGibIB7gpW7uTS0oN82Bq2bYKFiclMA/640?wx_fmt=png)

到这里多说一句, 在 c# 中使用反射还不如直接使用单利模式 . -_-||  

…END…

![](https://mmbiz.qpic.cn/mmbiz_png/2ibt1icyStlHic7ahCUraibQEGs1UdQEKfvMCQ93Ut3fMg3TUtg7zLmJib2sicDpwH8hsQw5ibbAd7hOYXF0cDkZlfThQ/640?wx_fmt=png)

扫描二维码

获取更多精彩

微信号 : We_Jtro

![](https://mmbiz.qpic.cn/mmbiz_jpg/tXghtxYMW0Y8PFkByNhkzsZmTmGLiaSnDibXiaDfK5QoXworQvwXwnnqfZlkZibzzia6avUWLdIny849UrAgicXGG6aQ/640?wx_fmt=jpeg)

![](https://mmbiz.qpic.cn/mmbiz_gif/hmdGwusCnbUMlfLG96lu1UIzpB0VSugiaeFNwEHtxX2gsXP79Pj7FGSSEaMYHDMXs2K8U7ibdTj12IzlPib7fNiaIg/640?wx_fmt=gif)