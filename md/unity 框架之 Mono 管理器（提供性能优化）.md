> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/66Gvn_FUeYDRqzzEO1ZMbA)

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/NSzqcbtSiakldVh8ZGApDU6jCHJug5cPMmqLYZIyLboaFwtmUSxiawoXut8UqLAmDrkwyoM6icfIDHr7f8w9Y61wQ/640?wx_fmt=gif&from=appmsg)

**点击蓝字，关注我们**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakldVh8ZGApDU6jCHJug5cPMv4ppbny74VzEibk1hxzRBg18gMGtWr7s1K29uuMfef7kgWCmNZwRbmw/640?wx_fmt=png&from=appmsg)

**Mono 管理器：统一执行游戏对象的全局 Update 方法和协程启动**

接上一篇场景管理器：

[unity 框架之场景管理器框架](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484153&idx=1&sn=b128a3bc8df7bb4577a18ab3db65a1ec&chksm=ce0723f6f970aae0367088ad9f80b6cdf1d06d0b9bfdab7afbfadb6572e47a0e90cbd214fa76&scene=21#wechat_redirect)  

上篇提到了的前置知识 Mono 管理器，这篇就来实现一下。

在 Unity 游戏开发中，频繁的 Update 方法调用和协程管理可能会导致性能下降，为了解决这一问题，可以使用 Mono 管理器来代理执行游戏对象的全局 Update 方法和启动协程。Mono 管理器作为一个单例对象，统一管理游戏对象的 Update 方法和协程启动，从而优化游戏性能。

完整代码：

```
using UnityEngine;using UnityEngine.Events;namespace Core{    /// <summary>    /// 代理执行游戏全局的Update方法，统一调用，目的为了节省性能    /// </summary>    public class MonoProxy : MonoBehaviour    {        private static MonoProxy instance = null;        //给外部调用继承Mono的单例对象：例如开启协程        public static MonoProxy Instance        {            get            {                if (instance == null)                {                    Init();                }                return instance;            }        }        //需要执行的update事件        private UnityEvent fixedUpdateProxy { get; set; } = null;        private UnityEvent updateProxy { get; set; } = null;        private UnityEvent lateUpdateProxy { get; set; } = null;        //初始化，需要外部先调用        public static void Init()        {            if (instance != null)            {                Debug.Log("Mono 已初始化过，无需再初始化");                return;            }            instance = new GameObject(nameof(MonoProxy)).AddComponent<MonoProxy>();            DontDestroyOnLoad(instance.gameObject);            //初始化事件            instance.fixedUpdateProxy = new UnityEvent();            instance.updateProxy = new UnityEvent();            instance.lateUpdateProxy = new UnityEvent();            Debug.Log("Mono 初始化完成...");        }        /// <summary>        /// 注册FixedUpdate的方法        /// </summary>        /// <param >需要添加的方法</param>        public static void AddFixedUpdateListener(UnityAction callback)        {            instance.fixedUpdateProxy.AddListener(callback);        }        /// <summary>        /// 注册Update的方法        /// </summary>        /// <param >需要添加的方法</param>        public static void AddUpdateListener(UnityAction callback)        {            instance.updateProxy.AddListener(callback);        }        /// <summary>        /// 注册LateUpdate的方法        /// </summary>        /// <param >需要添加的方法</param>        public static void AddLateUpdateListener(UnityAction callback)        {            instance.lateUpdateProxy.AddListener(callback);        }        /// <summary>        /// 注销FixedUpdate的方法        /// </summary>        /// <param >需要移除的方法</param>        public static void RemoveFixedUpdateListener(UnityAction callback)        {            instance.fixedUpdateProxy.RemoveListener(callback);        }        /// <summary>        /// 注销Update的方法        /// </summary>        /// <param >需要移除的方法</param>        public static void RemoveUpdateListener(UnityAction callback)        {            instance.updateProxy.RemoveListener(callback);        }        /// <summary>        /// 注销LateUpdate的方法        /// </summary>        /// <param >需要移除的方法</param>        public static void RemoveLateUpdateListener(UnityAction callback)        {            instance.lateUpdateProxy.RemoveListener(callback);        }        //执行生命周期update相关        private void FixedUpdate()        {            instance.fixedUpdateProxy?.Invoke();        }        private void Update()        {            instance.updateProxy?.Invoke();        }        private void LateUpdate()        {            instance.lateUpdateProxy?.Invoke();        }        //物体销毁时移除所有的事件监听        private void OnDestroy()        {            instance.fixedUpdateProxy.RemoveAllListeners();            instance.updateProxy.RemoveAllListeners();            instance.lateUpdateProxy.RemoveAllListeners();        }    }}
```

**使用示例**

下面是 Mono 管理器的使用示例：

```
using UnityEngine;public class ExampleMonoManagerUsage : MonoBehaviour{    void Start()    {        // 初始化Mono管理器        Core.MonoProxy.Init();        // 注册FixedUpdate方法        Core.MonoProxy.AddFixedUpdateListener(OnFixedUpdate);        // 注册Update方法        Core.MonoProxy.AddUpdateListener(OnUpdate);        // 注册LateUpdate方法        Core.MonoProxy.AddLateUpdateListener(OnLateUpdate);        // 启动协程        Core.MonoProxy.Instance.StartCoroutine(ExampleCoroutine());    }    // 在FixedUpdate中执行的逻辑    private void OnFixedUpdate()    {        Debug.Log("FixedUpdate");    }    // 在Update中执行的逻辑    private void OnUpdate()    {        Debug.Log("Update");    }    // 在LateUpdate中执行的逻辑    private void OnLateUpdate()    {        Debug.Log("LateUpdate");    }    // 示例协程    private System.Collections.IEnumerator ExampleCoroutine()    {        yield return new WaitForSeconds(1f);        Debug.Log("Coroutine finished!");    }    // 在MonoBehaviour销毁时，注销所有方法，避免内存泄漏    private void OnDestroy()    {        Core.MonoProxy.RemoveFixedUpdateListener(OnFixedUpdate);        Core.MonoProxy.RemoveUpdateListener(OnUpdate);        Core.MonoProxy.RemoveLateUpdateListener(OnLateUpdate);    }}
```

在这个示例中，我们创建了一个名为 **ExampleMonoManagerUsage** 的 MonoBehaviour 类，并在其 Start 方法中初始化了 Mono 管理器，并注册了 FixedUpdate、Update 和 LateUpdate 方法的回调函数，以及启动了一个协程。

注意：此处利用 Mono 管理器启动协程只是为了演示在不继承 Mono 的脚本中要怎么启动协程。

在回调函数和协程中，我们可以编写对应的逻辑代码。需要注意的是，在 MonoBehaviour 销毁时，我们需要注销这些方法，避免内存泄漏。

通过 Mono 管理器，我们可以更加有效地管理游戏中的 Update 方法和协程，提高游戏的性能表现。

关注我，学习更多游戏开发技巧。