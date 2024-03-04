> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/JC3NSUZh7qZ9n1DAaaTJPg)

**Unity 框架之资源管理器**

在 Unity 游戏开发中，资源管理是一个至关重要的环节。良好的资源管理可以提高游戏性能、降低内存占用，并且有助于开发过程的整体效率。在本文中，我将介绍如何使用 Unity 框架中的资源管理器进行资源加载，并提供使用代码示例。

**资源管理器介绍**

Unity 框架提供了许多不同的方式来加载和管理游戏资源。其中之一是使用 **Resources** 文件夹。**Resources** 文件夹是一个特殊的文件夹，其下的资源可以通过 **Resources.Load** 方法进行同步或异步加载。尽管 Unity 官方不再推荐使用 **Resources** 文件夹进行资源管理，因为它会导致整个资源被打包到游戏中，增加了游戏的内存占用和加载时间，但对于小型项目而言，这仍然是一个简单有效的方法。

**前提知识：单例模式、Resources 使用、委托、泛型**

单例模式我之前文章有介绍过 [Unity 重要框架之单例模式框架](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484067&idx=1&sn=c48d8782ec03236fcccc17f00c67bc0a&chksm=ce0723acf970aaba56ea34782f8d8c68f04ca18e045796e4d97724b680272d981d3a0d7f4170&scene=21#wechat_redirect)  

**ResMgr 代码介绍**

下面是我编写的一个简单的资源管理器类 **ResMgr**，其中包含了同步和异步加载资源的方法。这个类是一个单例类，继承自 **BaseSingleton**，确保在整个游戏中只有一个实例。

```c#
using System.Collections;
using UnityEngine;
using UnityEngine.Events;

public class ResMgr : BaseSingleton<ResMgr>
{
    //同步加载资源
    public T Load<T>(string name) where T : Object
    {
        T res = Resources.Load<T>(name);
        //如果对象是一个GameObject类型的，实例化后再返回出去 外部可以直接使用
        if(res is GameObject)
        {
            return GameObject.Instantiate(res);
        }
        else
        {
            return res;
        }
    }
    //异步加载资源
    public void LoadAsync<T>(string name, UnityAction<T> callback) where T : Object
    {

        //开启异步加载协程
        //由于没有继承Mono，只能使用外部的Mono脚本开启协程
        MonoMgr.Instance.StartCoroutine(ReallyLoadAsync(name,callback));

    }
    /// <summary>
    /// 异步加载协程函数
    /// </summary>
    /// <typeparam name="T">加载的类型</typeparam>
    /// <param name="name">resources下的路径（文件名）</param>
    /// <param name="callback">回调函数，在外部定义,利用回调函数来传递加载的资源</param>
    /// <returns></returns>
    private IEnumerator ReallyLoadAsync<T>(string name,UnityAction<T> callback) where T : Object
    {
        //异步加载资源
        ResourceRequest request= Resources.LoadAsync<T>(name);
        //等待请求加载完成，才继续执行下面的步骤
        yield return request;
        //用这个获取加载的资源request.asset
        if(request.asset is GameObject)
        {
            callback(GameObject.Instantiate(request.asset) as T);
        }
        else
        {
            callback(request.asset as T);
        }
    }

}
```

**使用代码示例**

以下使用代码示例，展示了如何调用 **ResMgr** 中的方法来加载资源，包括同步加载和异步加载。

```c#
// 同步加载资源示例
GameObject obj = ResMgr.Instance.Load<GameObject>("Prefab/ExamplePrefab");
// 异步加载资源示例
ResMgr.Instance.LoadAsync<GameObject>("Prefab/ExamplePrefab", (result) =>
{
    // 在回调中使用加载的资源
    GameObject instantiatedObj = result;
    // 这里可以进行资源加载完成后的操作
});
```

**注意事项**

在使用资源管理器时，我给出一些建议：

*   **避免过度依赖 Resources 目录**：尽管 **Resources** 目录在小型项目中可能是一个方便的选择，但是对于大型项目而言，最好避免过度依赖它，因为这会导致游戏的内存占用增加，加载时间变长。官方给出的建议是不要使用 **Resources****。**
    
*   **小项目仍可使用**：尽管如此，对于小型项目而言，使用 **Resources** 目录管理资源仍然是一个简单有效的方法，因为其操作简单、方便快捷。
    
*   **AB 包资源管理**：在下一期，我将讨论更为高效的资源管理方式，即 AssetBundle（AB 包）资源管理，它可以更好地管理大型项目的资源加载和优化。
    

通过以上的文字介绍、代码示例和注意事项，相信你能够更好地理解和使用 Unity 框架中的资源管理器。
