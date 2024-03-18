> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.cnblogs.com](https://www.cnblogs.com/flamesky/p/17923139.html)

因为老的 API  Properties.DeleteArrayElementAtIndex(propertyIndex); 提示没权限修改，

而 unity 提供了新的 API  GameObjectUtility.RemoveMonoBehavioursWithMissingScript(go); 更方便移除丢失的组件，需要遍历物体下面所有子节点，否则无法移除子节点的丢失组件。

于是重新整理了下清理的编辑器代码，直接贴上：

[![](http://assets.cnblogs.com/images/copycode.gif)](javascript:void(0); "复制代码")

```
1 using System;
 2 using UnityEngine;
 3 using UnityEditor;
 5 public class ResTool : Editor
 6 {
 7     [MenuItem("Tools/清理prefab中所有Missing的脚本")]
 8     public static void ClearAllPrefabMissingComponents()
 9     {
10         EditorUtility.DisplayProgressBar("Modify Prefab", "Please wait...", 0);
11         string[] assetGUIDs = AssetDatabase.FindAssets("t:Prefab", new string[] { "Assets/Res/Prefab" });
12         try
13         {
14             for (int i = 0; i < assetGUIDs.Length; i++)
15             {
16                 string path = AssetDatabase.GUIDToAssetPath(assetGUIDs[i]);
17                 // Debug.Log($"path:{path}");
18                 GameObject pre = PrefabUtility.LoadPrefabContents(path);
20                 DeleteRecursive(pre, (go) =>
21                 {
22                     GameObjectUtility.RemoveMonoBehavioursWithMissingScript(go);
23                 });
24                 PrefabUtility.SaveAsPrefabAssetAndConnect(pre, path, InteractionMode.AutomatedAction);
26                 EditorUtility.DisplayProgressBar($"清理Prefab丢失组件", $"当前{pre}, {i}/{assetGUIDs.Length}", i / (float)assetGUIDs.Length);
27             }
28         }
29         catch (Exception e)
30         {
31             Debug.LogError($"{e}");
32         }
34         AssetDatabase.SaveAssets();
35         EditorUtility.ClearProgressBar();
36         AssetDatabase.Refresh();
37     }
39     /// <summary>
40     /// 遍历所有子节点
41     /// </summary>
42     /// <param ></param>
43     /// <param ></param>
44     static void DeleteRecursive(GameObject obj, Action<GameObject> action)
45     {
46         action(obj);
48         for (int i = 0; i < obj.transform.childCount; i++)
49         {
50             DeleteRecursive(obj.transform.GetChild(i).gameObject, action);
51         }
53     }
55 }
```

[![](http://assets.cnblogs.com/images/copycode.gif)](javascript:void(0); "复制代码")