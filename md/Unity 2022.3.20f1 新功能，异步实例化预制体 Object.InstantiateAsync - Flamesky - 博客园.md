> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.cnblogs.com](https://www.cnblogs.com/flamesky/p/18019553)

> 今天查看 Unity 2022.3.20f1 更新日志，发现新增了个异步实例化的功能，这个功能解决了 Unity 历史上实例化预制体卡顿的痛点，简直不要太爽。

今天查看 [Unity 2022.3.20f1 更新日志](https://unity.com/releases/editor/whats-new/2022.3.20#release-notes)，发现新增了个异步实例化的功能，这个功能解决了 Unity 历史上实例化预制体卡顿的痛点，简直不要太爽。

![](https://img2024.cnblogs.com/blog/510084/202402/510084-20240218163932632-1033809008.png)

具体的 [API 文档](https://docs.unity3d.com/2022.3/Documentation/ScriptReference/Object.InstantiateAsync.html)请点击跳转。

做了个简单的实例化测试，实例化 500*500 个 Cube，耗时 9.2s。实例化过程之间不会卡顿，可以做其他事情，即便是在重度游戏加载场景过程中也不需要担心卡顿掉帧影响操作了。测试代码如下：

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjTest : MonoBehaviour
{
    public GameObject obj;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(Test());
        Debug.LogError($"test InstantiateAsync");
    }

    IEnumerator Test()
    {
        float startTime = Time.realtimeSinceStartup;
        for (int i = 0; i < 500; i++)
        {
            AsyncInstantiateOperation<GameObject> instantiateOperation = Object.InstantiateAsync(obj, 500);
            yield return instantiateOperation;
            if (instantiateOperation.isDone)
            {
                // Debug.Log($"{instantiateOperation.Result.Length}");
                for (int j = 0; j < instantiateOperation.Result.Length; j++)
                {
                    GameObject go = instantiateOperation.Result[j];
                    go.name = $"cube{i}-{j}";
                }
            }
        }
        Debug.LogError($"spend time:{Time.realtimeSinceStartup - startTime} seconds");
    }

}
```

创建一个 cube 拖成预制体，拖拽到脚本上，运行游戏，可以看到 cube 一个个在 Hierachy 视图逐个创建出来，期间可以拖动滚动条查看，不会卡。

可惜当前项目没能用这个版本，不过后续新项目能用上新版本，用异步实例化绝对是爽翻天。