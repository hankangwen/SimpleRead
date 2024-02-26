> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484078&idx=1&sn=68d39fce76e4497757f11bcf95883f6e&chksm=ce0723a1f970aab7153cee4440218358b80f8af1447aca68372f53592358c04c98e151c9b52d&scene=178&cur_album_id=3285418518473310211#rd)

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/NSzqcbtSiakm0piagdNg5rH7MddNXmIKlXmEFhRdmRUybrj9FUfVcdgQR38oOjfE1PKWUuazVvW8pFgh2euwVXtg/640?wx_fmt=gif&from=appmsg)

**点击蓝字，关注我们**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakm0piagdNg5rH7MddNXmIKlX7iaCSkTMo8lezuUKOpKBLrXvNibhxOvU1PgO1VC4U5ic73z3ATolfPeXg/640?wx_fmt=png&from=appmsg)

Unity 作为一款强大的游戏引擎，提供了丰富的框架和工具，其中对象池框架是开发中不可或缺的重要组成部分。对象池的概念在游戏开发中被广泛应用，其主要目的是提高性能和优化内存管理。本文将深入探讨 Unity 中的对象池框架，解释其重要性以及如何有效地使用它。

**什么是对象池框架？**

对象池是一种用于重复利用游戏对象的机制，而对象池框架则是在 Unity 中实现和管理这种机制的工具。在游戏中，特别是在需要频繁创建和销毁对象的情况下，使用对象池能够显著减轻垃圾回收的压力，提高游戏的性能。

**对象池的工作原理**

对象池框架的基本原理是在游戏启动时创建一定数量的对象实例并保存在池中。当需要使用对象时，不再重新创建新的对象，而是从池中取出一个空闲的对象并重置其状态，然后将其投放到场景中。完成使用后，对象并不被销毁，而是被重新放回对象池，等待下次使用。

**为什么使用对象池框架？**

> **性能优化：** 避免频繁的对象创建和销毁，减少了垃圾回收的频率，提高了游戏的性能。
> 
> **内存管理：** 对象池有效地管理了对象的内存，避免了不必要的内存分配和释放操作。
> 
> **减少资源消耗：** 对象池框架可以降低游戏的资源消耗，使游戏更加流畅。
> 
> **提高对象复用率：** 通过对象池，可以更高效地重用已有的对象，减少了对象的创建成本。

知识前提，单例模式基类 BaseSingleton<T>，详情可以看我的这篇

[Unity 重要框架之单例模式框架](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484067&idx=1&sn=c48d8782ec03236fcccc17f00c67bc0a&chksm=ce0723acf970aaba56ea34782f8d8c68f04ca18e045796e4d97724b680272d981d3a0d7f4170&scene=21#wechat_redirect)  

以下是一个基本的代码，演示如何在 Unity 中实现对象池的基本功能：

```
using System.Collections.Generic;using UnityEngine;public class PoolManager : BaseSingleton<PoolManager>{    //对象池，key为对象在资源文件夹的路径（名字），表示这种类的小池子的名字，value为小池子    private Dictionary<string, List<GameObject>> poolDic=new Dictionary<string, List<GameObject>>();    /// <summary>    /// 取出对象    /// </summary>    /// <param >需要拿的小池子的名字</param>    /// <returns></returns>    public GameObject GetObj(string name)    {        GameObject obj = null;                //有小池子 并且小池子有东西        if (poolDic.ContainsKey(name) && poolDic[name].Count > 0)        {            //取出来            obj = poolDic[name][0];            poolDic[name].RemoveAt(0);            obj.SetActive(true);        }        else        {            //创建一个            obj = GameObject.Instantiate(Resources.Load<GameObject>(name));            obj.name = name;//把对象名改成池子名，方便管理        }        return obj;    }    /// <summary>    /// 放入对象    /// </summary>    /// <param >存储的对象</param>    public void PushObj(string name,GameObject obj)    {        obj.SetActive(false);        //如果有这个池子        if (poolDic.ContainsKey(name))        {            poolDic[name].Add(obj);        }        else//没有池子        {            //加入一个小池子，并初始化小池子个传入的对象            poolDic.Add(name,new List<GameObject>() { obj });        }    }}
```

**代码功能解释：**

> **poolDic**: 一个字典，用于存储多个对象池。每个对象池以资源文件路径（或自定义名字）作为键，对应一个包含多个对象实例的列表。由于我 GetObj 方法当对象池中没有可用对象时，是从资源文件夹中读取并创建，所以我把 key 用资源文件路径来定义。
> 
> **GetObj(string name)**: 从对象池中获取对象的方法。首先检查指定小池子是否存在并且有可用对象，如果有，则从小池子中取出一个对象并激活，否则创建一个新对象，根据你定义的方法创建，此处为从 Resources 文件夹读取。
> 
> **PushObj(string name, GameObject obj)**: 将对象放回对象池的方法。将对象禁用，并根据小池子名字存入相应的小池子中。如果小池子不存在，则创建一个新的小池子。

**代码设计思路：**

> **对象池管理：** 使用字典 **poolDic** 管理多个对象池，每个对象池以资源路径为键，对应一个对象列表。
> 
> **对象获取：****GetObj** 方法用于从指定对象池中获取对象。如果对象池存在且有可用对象，则从池中取出，否则创建新对象。
> 
> **对象放回：****PushObj** 方法用于将对象放回对象池。将对象禁用后，存入对应的对象池。如果对象池不存在，则创建一个新的对象池。

**如何使用对象池框架？**

在 Unity 中，可以通过以下步骤来使用对象池框架：

> **创建对象池：** 在游戏启动时，创建一个对象池并初始化一定数量的对象实例。
> 
> **从对象池中获取对象：** 当需要使用对象时，从对象池中获取一个对象实例。
> 
> **重置对象状态：** 在使用对象前，确保对象的状态已被重置为初始状态。
> 
> **使用对象：** 将对象投放到场景中，完成所需的操作。
> 
> **将对象放回池中：** 在使用完成后，将对象重新放回对象池，等待下次使用。

使用举例：  

Resources 文件夹  

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakm0piagdNg5rH7MddNXmIKlXTagpibtian8GKfFNOaqEm4joiaA9fgKeF7KMBgcJk1wNRvapdC9CBOgHg/640?wx_fmt=png&from=appmsg)

```
using UnityEngine;public class Test : MonoBehaviour{    private void Start()    {        //拿出对象        GameObject obj= PoolManager.Instance.GetObj("MyTest/Cube");        //对对象进行操作        //放回对象        PoolManager.Instance.PushObj("MyTest/Cube", obj);    }}
```

**总结**

本示例只是一个基础的对象池框架，还可以继续扩展和修改。对象池框架是 Unity 中非常重要的一部分，对于提高游戏性能和优化内存管理至关重要。通过合理使用对象池，开发者能够更好地应对游戏中频繁创建和销毁对象的需求，使游戏更加流畅和稳定。希望本文能够帮助你更深入地理解 Unity 中对象池框架的重要性以及如何有效地应用它。

关注我，一起学更多技术。