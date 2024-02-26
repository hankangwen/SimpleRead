> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484153&idx=1&sn=b128a3bc8df7bb4577a18ab3db65a1ec&chksm=ce0723f6f970aae0367088ad9f80b6cdf1d06d0b9bfdab7afbfadb6572e47a0e90cbd214fa76&scene=21#wechat_redirect)

#### **场景管理中心：Unity 中的基本框架之一**

在游戏开发中，场景管理是至关重要的一环。它直接影响着游戏的流畅性和用户体验。在 Unity 中，我们可以通过创建一个简单而有效的场景管理器框架来实现这一功能。

前置知识点：单例设计模式，Mono 管理器（负责代理需要在继承 Mono 环境下的脚本执行），委托函数。

下面是一个基本的场景管理器框架示例：

```c#
using System.Collections;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;

namespace Core
{
    public class SceneManager
    {
        // 初始化场景管理器
        public static void Init()
        {
            Debug.Log("场景管理器初始化完成...");
        }

        /// <summary>
        /// 同步加载场景
        /// </summary>
        /// <param name="sceneName">场景名称</param>
        /// <param name="onSceneLoaded">场景加载完成后的回调</param>
        public static void LoadScene(string sceneName, UnityAction onSceneLoaded = null)
        {
            UnityEngine.SceneManagement.SceneManager.LoadScene(sceneName);
            onSceneLoaded?.Invoke();
        }

        /// <summary>
        /// 异步加载场景
        /// </summary>
        /// <param name="sceneName">场景名称</param>
        /// <param name="onProgress">加载进度更新回调</param>
        /// <param name="onSceneLoaded">场景加载完成后的回调</param>
        public static void LoadSceneAsync(string sceneName, UnityAction<float> onProgress = null, UnityAction onSceneLoaded = null)
        {
            MonoProxy.Instance.StartCoroutine(LoadSceneAsyncCoroutine(sceneName, onProgress, onSceneLoaded));
        }

        private static IEnumerator LoadSceneAsyncCoroutine(string sceneName, UnityAction<float> onProgress, UnityAction onSceneLoaded)
        {
            AsyncOperation asyncOperation = UnityEngine.SceneManagement.SceneManager.LoadSceneAsync(sceneName);

            while (!asyncOperation.isDone)
            {
                // 如果需要，可以通过回调函数返回加载进度
                onProgress?.Invoke(asyncOperation.progress);
                yield return null;
            }

            // 场景加载完成后执行回调
            onSceneLoaded?.Invoke();
        }
    }
}
```

以上代码实现了一个基本的场景管理器框架，直接使用声明为静态方法来让场景管理器实现单例设计模式（也可以继承单例框架，具体可以看我主页的单例模式框架），具备同步和异步加载场景的功能。因为此场景管理器并未继承 Mono，所以需要使用 Mono 管理器（继承 Mono 的 Mono 管理器）的实例来启动协程。下面是对代码的简要解释：

*   **Init()** 方法用于初始化场景管理器，这里只是简单地打印一条日志。
    
*   **LoadScene(string sceneName, UnityAction onSceneLoaded = null)** 方法用于同步加载场景，加载完成后会调用传入的回调函数。
    
*   **LoadSceneAsync(string sceneName, UnityAction<float> onProgress = null, UnityAction onSceneLoaded = null)** 方法用于异步加载场景，通过协程实现，可以传入加载进度更新回调和场景加载完成后的回调函数。
    
*   在异步加载的协程中，通过 **asyncOperation.progress** 获取加载进度，同时在加载完成后执行回调函数。
    

这个简单的框架可以作为一个基础，根据具体项目的需求进行扩展和定制，以实现更复杂的场景管理功能。

以下为场景管理器的使用示例：

```c#
using UnityEngine;

public class ExampleSceneLoader : MonoBehaviour
{
    void Start()
    {
        // 初始化场景管理器
        Core.SceneManager.Init();

        // 同步加载场景
        Core.SceneManager.LoadScene("YourSceneName", OnSceneLoaded);

        // 异步加载场景
        Core.SceneManager.LoadSceneAsync("YourSceneName", OnProgressUpdate, OnSceneLoaded);
    }

    // 场景加载完成后的回调
    private void OnSceneLoaded()
    {
        Debug.Log("场景加载完成！");
        // 在这里可以执行场景加载完成后的逻辑
    }

    // 场景加载进度更新回调
    private void OnProgressUpdate(float progress)
    {
        Debug.Log("加载进度：" + (int)(progress * 100) + "%");
        // 在这里可以更新加载进度条等UI
    }
}
```

*   在 **Start()** 方法中，首先初始化了场景管理器 **Core.SceneManager.Init()**。
    
*   然后通过 **Core.SceneManager.LoadScene()** 同步加载了一个场景，并传入了加载完成后的回调函数 **OnSceneLoaded()**。
    
*   接着通过 **Core.SceneManager.LoadSceneAsync()** 异步加载了另一个场景，同时传入了加载进度更新回调函数 **OnProgressUpdate()** 和加载完成后的回调函数 **OnSceneLoaded()**。
    

通过这样的方式，我们可以简单而有效地使用场景管理器框架，实现对场景的加载控制，并根据需求进行相应的处理。

本文需要一定基础才能理解，理解不了可以收藏关注反复观看。

单例模式可以看我之前这篇：

[Unity 重要框架之单例模式框架](http://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484067&idx=1&sn=c48d8782ec03236fcccc17f00c67bc0a&chksm=ce0723acf970aaba56ea34782f8d8c68f04ca18e045796e4d97724b680272d981d3a0d7f4170&scene=21#wechat_redirect)