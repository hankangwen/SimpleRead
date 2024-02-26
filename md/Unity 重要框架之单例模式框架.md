> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484067&idx=1&sn=c48d8782ec03236fcccc17f00c67bc0a&chksm=ce0723acf970aaba56ea34782f8d8c68f04ca18e045796e4d97724b680272d981d3a0d7f4170&scene=178&cur_album_id=3285418518473310211#rd)

Unity 作为一款强大的游戏开发引擎，其基础框架的设计对于项目的结构和性能有着重要的影响。其中，单例模式是一种常用的设计模式，用于确保一个类只有一个实例，并提供一个全局访问点。

#### **什么是单例模式？**

单例模式是一种创建型设计模式，其目的是确保一个类只有一个实例，并提供一个全局访问点。在 Unity 中，单例模式常用于管理全局数据、游戏状态或者资源管理。通过单例模式，我们可以在整个应用程序中方便地访问特定的对象。



#### **Unity 中的单例模式实现（不继承 Mono 的）**

##### **1. 创建 Singleton 类**

首先，我们需要创建一个 BaseSingleton 类，该类负责管理单例实例的创建和访问。以下是一个简单的 BaseSingleton 类示例：

```c#
//单例模式基类,泛型约束为：存在无参构造函数，非抽象类
//为什么约束，因为使用了instance = new T();
public class BaseSingleton<T> where T:new()
{
    private static T instance;
    //保护构造函数，保证单例只能在内部创建
    protected BaseSingleton() { }
    public static T Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new T();
            }
            return instance;
        }
    }
}
```

##### **2. 应用到 Unity 中的管理器**

假设我们要创建一个 GameManager 作为全局的游戏管理器。我们可以通过继承 BaseSingleton 类来实现 GameManager 的单例模式：

```c#
public class GameManager : BaseSingleton<GameManager>
{
    // 在这里定义GameManager的其他属性和方法

    private GameManager()
    {
        // 私有构造函数，确保只能通过Singleton.Instance访问实例
    }
}
```

##### **3. 在其他类中访问单例**

现在，我们可以在其他类中轻松地访问 GameManager 的单例实例：

```c#
public class PlayerController : MonoBehaviour
{
    void Start()
    {
        // 通过GameManager.Instance访问GameManager的单例实例
        GameManager.Instance.StartGame();
        //StartGame()是在GameManager类里定义的一个方法
    }
}
```

通过这种方式，我们可以方便地管理全局的游戏状态，而无需担心多个实例的创建。



#### **Unity 中的单例模式实现（继承 Mono 的）**

在 Unity 中，经常会使用 MonoBehaviour 作为游戏对象的脚本组件，会需要使用 MonoBehaviour 的相关方法。因此将单例模式与 MonoBehaviour 结合可以更好地适应游戏开发的需求。

##### **1. 创建 Singleton 类**

以下是一个继承 MonoBehaviour 的单例模式基类的实现：

```c#
using UnityEngine;
public class SingletonMono<T> : MonoBehaviour where T : MonoBehaviour
{
    private static T instance;
    public static T Instance
    {
        get
        {
            if (instance == null)
            {
                // 在场景中查找是否已存在该类型的实例
                instance = FindObjectOfType<T>();
                // 如果场景中不存在该类型的实例，则创建一个新的GameObject并添加该组件
                if (instance == null)
                {
                    GameObject singletonObject = new GameObject(typeof(T).Name + "_Singleton");
                    instance = singletonObject.AddComponent<T>();
                    DontDestroyOnLoad(singletonObject); // 保留在场景切换时不被销毁
                }
            }
            return instance;
        }
    }
 //使用virtual虚函数，子类继承可能还需要用Awake()
    protected virtual void Awake()
    {
        // 确保在场景切换时不会销毁该实例
        DontDestroyOnLoad(gameObject);
        // 检查是否存在重复的实例
        if (instance == null)
        {
            instance = this as T;
        }
        else
        {
            Debug.LogWarning("存在重复的单例" + typeof(T).Name + "删除");
            Destroy(gameObject);
        }
    }
}
```

这个基类通过继承 MonoBehaviour，确保了单例实例在场景切换时不会被销毁，并在 Awake 方法中进行了重复实例的检查。

##### **2. 应用到 Unity 中的管理器**

我们可以使用这个基类来创建具体的单例类，例如 GameManager：

```c#
public class GameManager : SingletonMono<GameManager>
{
    // 在这里定义GameManager的其他属性和方法

    private void Start()
    {
        // 在这里可以进行初始化操作
    }
}
```

其他的使用和上面相同。



#### **总结**

单例模式是 Unity 中常用的设计模式之一，特别适用于需要全局访问点的情况。通过创建一个 Singleton 类，我们可以轻松地将其应用到不同的管理器或者全局性的对象中，提高代码的可维护性和灵活性。在实际项目中，根据具体需求可以对单例模式进行扩展和优化。
