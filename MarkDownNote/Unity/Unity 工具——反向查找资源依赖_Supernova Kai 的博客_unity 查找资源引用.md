> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_42316280/article/details/123090361)

**前言：**  
 在项目开发过程中，有时候需要查找一个某个美术资源被那些其他资源使用了，可是`Unity`只提供给了以我们正向查找的接口 (`AssetDatabase.GetDependencies()`)，并没有提供给我们反向查找依赖的接口，本文就来介绍如何进行反向查找资源依赖。

**基本原理：**  
 在`Unity`中，任何项目中的文件，都会被分配一个唯一的`guid`，这个`guid`会保存在这个文件的`.meta`文件中；而`Unity`的其他美术文件，例如：预制体、场景、材质等，本身是以`YAML`的格式进行保存的，在这个`YAML`格式文件中，便会记录下它所依赖的其它资源的`guid`。

**验证一下我们的原理：**  
 首先，我创建了一个绿色的材质，然后创建了一个`Cube`，将前面那个材质赋给`Cube`，并把这个`Cube`做成一个预制体。  
![](https://img-blog.csdnimg.cn/ea289fa85a144659aca89d484277b097.png#pic_center)  
 我们用记事本打开这个材质的`.meta`文件，看看它的`guid`是多少

![](https://img-blog.csdnimg.cn/5aced78909bd46b6b859c1ba30173a37.png#pic_center)  
 我们再打开`Cube.prefab`，在这个`YAML`格式的文件中便会记录下这个依赖信息。  
![](https://img-blog.csdnimg.cn/467b376aaa324285bc704c8dff479c3f.png#pic_center)

**代码如下：**

```
using UnityEngine;
using UnityEditor;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

public class FindReferences
{
    [MenuItem("Assets/Find References")]
    private static void Find()
    {
        EditorSettings.serializationMode = SerializationMode.ForceText;
        Object selectObject = Selection.activeObject; //当前选择对象
        string filePath = AssetDatabase.GetAssetPath(selectObject); //当前选择对象的路径
        string fileName = selectObject.name; //当前选择对象的名字
        if(!string.IsNullOrEmpty(filePath))
        {
            string guid = AssetDatabase.AssetPathToGUID(path); //将路径转换为guid
            List<string> includeExtensions = new List<string>() { ".prefab", ".unity", ".mat", ".asset" }; //需要搜索的资源文件（预制体 场景 材质）,可以自己根据情况自定义
            string[] files = Directory.GetFiles(Application.dataPath, "*", SearchOption.AllDirectories).Where(s => includeExtensions.Contains(Path.GetExtension(s).ToLower())).ToArray();

            int index = 0;
            int count = 0;
			//EditorApplication.update，通用更新的委托，将我们的函数添加到此委托以获取更新。
            EditorApplication.update = delegate ()
            {
                string file = Path.GetFullPath(files[index]);
                float percent = (float)(System.Convert.ToDouble(index) / System.Convert.ToDouble(files.Length)); //进度百分比
                EditorUtility.DisplayProgressBar($"正在查找中... ({index}/{files.Length})", file, percent); //进度条
                if(Regex.IsMatch(File.ReadAllText(file), guid)) //读取文件内容，是否包含guid
                {
                	count++;
                    Debug.Log($"第{count}个文件：<color=yellow>{Path.GetFileName(file)}</color>------路径为:<color=yellow>{file}</color>");
                }
                index++;
                if(index >= files.Length)
                {
                    EditorUtility.ClearProgressBar();
                    EditorApplication.update = null;
                    index = 0;
                    Debug.Log("搜索结束");
                }
            };
        }
    }
}

```