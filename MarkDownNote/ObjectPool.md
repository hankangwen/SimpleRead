### 对象池的运用

> ObjectPool对象池，减少内存分配和释放所带来的消耗。

#### 1.什么是对象池，为什么要用对象池？

对象池，即对象的池子。对象池里寄存着一些废弃的对象，当计算机程序需要某对象时，可以向对象池申请，让我们对废弃的对象再利用，其实质是内存我们对废弃的内存再利用就能省去了很多内存碎片问题和GC问题，还能节省实例化时CPU的消耗。其中实例化消耗包括模型文件读取、贴图文件读取、GameObject实例化、程序逻辑初始化、内存分配消耗等。



对象池的规则是，需要对象时向对象池申请对象，对象池从池子中拿出以前废弃的对象重新“清洗”后给出去，如果对象池里也没有可用的对象，则新建一个再给出去，在对象用完后，仍把这些废弃的对象放入对象池以便再利用。

对象池的方法本质是重复利用内存，重复利用的好处很多，能减少内存碎片，碎片少了，内存连续的可能性就大，CPU缓存命中的概率也大了，此外，内存的使用量也会减少，因为大块内存不会因为碎片问题而需要重新申请新的内存，同时内存垃圾及触发垃圾回收的次数也少了，我们知道垃圾回收是非常耗时的，GC优化会在后面的章节中详细讲解。提及UI优化，界面中的有些效果需要不断跳出相同的物体。这时实例化和销毁UI物体是逻辑中消耗CPU容量最大的部分，物体被不断新建出来，又不断被销毁。CPU容量大部分被浪费在实例化和销毁上，渲染只占了很小一部分比重。这时运用对象池就能解决大部分浪费的问题，即将要销毁的实例对象，放入对象池并移出屏幕或隐藏，当需要它们时再放出来重新初始化。



对象池是个非常好的优化内存和CPU的方式，不过使用得不恰当也会引起不少内存问题。如果对象池的回收被错误地重复操作，不但会导致新的逻辑错误，还可能导致内存被撑大，因此使用对象池时最好要小心，谨慎地回收，也不要错误地放弃回收。这里总结了几条运用对象池的经验：

1）当程序中有重复实例化并不断销毁的对象时需要使用对象池进行优化。重复实例化和销毁操作会消耗大量CPU，在此类对象上使用对象池优化的效果极佳。

2）每个需要使用对象池的对象都需要继承对象池的基类对象，这样在初始化时可以针对不同的对象重载，区别对待不同类型的对象，让不同对象根据各自的情况分别初始化。

3）销毁操作时使用对象池接口进行回收，切记不要重复回收对象，也不要错误地放弃回收。在销毁物体时要使用对象池提供的回收接口，以便让对象池集中存储对象。

4）场景结束时要及时销毁整个对象池，避免无意义的内存驻留。在场景结束后，对象池内的物体已经不再适合新的场景，或者说面临的环境情况与旧场景已不同，所以需要及时清理对象池，把内存空出来留给新场景使用。

```c#
// ObjectPool.cs
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// ObjectPool.cs - A pool of objects that can be reused.
/// Copy from UnityEngine.UI.ObjectPool.cs
/// </summary>
internal class ObjectPool<T> where T : new()
{
    private readonly Stack<T> m_Stack = new Stack<T>();
    private readonly UnityAction<T> m_ActionOnGet;
    private readonly UnityAction<T> m_ActionOnRelease;

    public int countAll { get; private set; }
    public int countActive { get { return countAll - countInactive; } }
    public int countInactive{ get { return m_Stack.Count; } }
    
    public ObjectPool(){}
    public ObjectPool(UnityAction<T> actionOnGet, UnityAction<T> actionOnRelease)
    {
        m_ActionOnGet = actionOnGet;
        m_ActionOnRelease = actionOnRelease;
    }

    public T Get()
    {
        T element;
        if (m_Stack.Count == 0)
        {
            element = new T();
            countAll++;
        }
        else
        {
            element = m_Stack.Pop();
        }

        if (m_ActionOnGet != null)
            m_ActionOnGet(element);
        return element;
    }

    public void Release(T element)
    {
        if (m_Stack.Count > 0 && ReferenceEquals(m_Stack.Peek(), element))
            Debug.LogError("Internal error. Trying to destroy object that is already released to pool.");
        if (m_ActionOnRelease != null)
            m_ActionOnRelease(element);
        m_Stack.Push(element);
    }
}
```



```c#
//ListPool.cs
using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// ListPool - A generic class for reusing lists.
/// Copy from UnityEngine.UI.ListPool.cs.
/// </summary>
internal static class ListPool<T>
{
    // Object pool to avoid allocations.
    private static readonly ObjectPool<List<T>> s_ListPool = new ObjectPool<List<T>>(null, Clear);
    static void Clear(List<T> l) { l.Clear(); }

    public static List<T> Get()
    {
        return s_ListPool.Get();
    }

    public static void Release(List<T> toRelease)
    {
        s_ListPool.Release(toRelease);
    }
}
```

