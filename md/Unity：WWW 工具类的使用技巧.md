> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/ivLhLhpW5qAYg9SSX2eQJw)

**1、简述**

Unity 的 WWW 类是一种用于发送 HTTP 请求和接收 HTTP 响应的类。它可以用来访问网络上的资源，如文本、图像、音频和视频等。本文将介绍如何使用 Unity 的 WWW 类来访问网络资源。

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUFQmY1ib7Iak3r8ZujqejCt3ZPG75s4qLtsM4qMzLej7FON1fwBrQlE0xPqViahyp7MKBpobAad7oibg/640?wx_fmt=png&from=appmsg)

**2、创建一个简单的 HTTP 请求**

首先，我们需要创建一个 WWW 对象来发送 HTTP 请求。以下是一个简单的示例代码，用来发送一个 GET 请求：

```
using UnityEngine;
using System.Collections;

public class SimpleHTTP : MonoBehaviour
{
    IEnumerator Start()
    {
        WWW www = new WWW("http://www.example.com");
        yield return www;
        
        if (www.error != null)
        {
            Debug.Log(www.error);
        }
        else
        {
            Debug.Log(www.text);
        }
    }
}
```

**3、发送 POST 请求**

如果要发送一个 POST 请求，我们需要使用 WWWForm 类来创建一个表单对象。以下是一个简单的示例代码，用来发送一个 POST 请求：

```
using UnityEngine;
using System.Collections;

public class SimpleHTTP : MonoBehaviour
{
    IEnumerator Start()
    {
        WWWForm form = new WWWForm();
        form.AddField("username", "user");
        form.AddField("password", "password");

        WWW www = new WWW("http://www.example.com/login", form);
        yield return www;

        if (www.error != null)
        {
            Debug.Log(www.error);
        }
        else
        {
            Debug.Log(www.text);
        }
    }
}
```

**4、发送带有请求头的请求**

如果要发送一个带有请求头的请求，我们需要使用 WWW 类的 SetRequestHeader 方法。以下是一个简单的示例代码，用来发送一个带有请求头的 GET 请求：

```
using UnityEngine;
using System.Collections;

public class SimpleHTTP : MonoBehaviour
{
    IEnumerator Start()
    {
        WWW www = new WWW("http://www.example.com");
        www.SetRequestHeader("Authorization", "Bearer token");
        yield return www;

        if (www.error != null)
        {
            Debug.Log(www.error);
        }
        else
        {
            Debug.Log(www.text);
        }
    }
}
```

**5、加载本地贴图**

如果要加载本地的图片转成 Texture2D，我们可以通过在文件路径前面添加 fille 标签，来实现将当前图片转成 texture：

```
public static IEnumerator LoadTexture(string filePath, Action<bool, Texture2D> callback)
{
    if (IsWindows && !filePath.StartsWith("file://"))
    {
        filePath = "file://" + filePath;
    }
    WWW www = new WWW(filePath);
    yield return www;
    if (string.IsNullOrEmpty(www.error))
    {
        callback.Invoke(true, www.texture);
    }
    else
    {
        Debug.LogError("WWW load Texture2D file Error: " + www.error + "   " + filePath);
        if (callback != null)
        {
            callback(false, null);
        }
    }
}
```

**6、异步加载本地贴图**

如果要加载本地的图片转成 Texture2D，我们可以通过在文件路径前面添加 fille 标签，并且通过 MoveNext 来实现异步加载图片转成 texture：

```
public static Texture2D LoadTextureSync(string filePath)
{
   if (IsWindows && !filePath.StartsWith("file://"))
   {
       filePath = "file://" + filePath;
   }
   using (WWW www = new WWW(filePath))
   {
       while (www.MoveNext()) { }

       if (string.IsNullOrEmpty(www.error))
       {
           return www.texture;
       }
       else
       {
           Debug.LogError("WWW load Texture2D file Error: " + www.error + "   " + filePath);
       }
   }
   return null;
}
```

**7、总结**

Unity 的 WWW 类是一个非常强大的类，可以用来发送 HTTP 请求和接收 HTTP 响应。本文介绍了如何使用 WWW 类来发送 GET 和 POST 请求，以及如何发送带有请求头的请求。希望这些示例代码能够帮助你更好地理解 Unity 的 WWW 类的使用方法。