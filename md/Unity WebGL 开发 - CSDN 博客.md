> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_26318597/article/details/106069504)

#### 教程来啦

*   [一. WebGL 不能干的那些事](#WebGL_1)
*   [二. 注意事项](#_9)
*   *   [1. 播放声音](#1_10)
    *   [2. 跨域](#2_12)
    *   [3. 发布 http or https?](#3http_or_https_30)
    *   [4. 包体大小](#4_32)
    *   [5.Odin](#5Odin_40)
    *   [6.T 序列化失败](#6T_45)
*   [三. 参考资料](#_52)
*   [四. Build](#Build_63)
*   *   [主要步骤](#_66)
    *   [web.config](#webconfig_84)
    *   *   [Apache](#Apache_87)
        *   [IIS](#IIS_110)
    *   [手机端去掉提示框](#_137)
    *   [全屏](#_170)
    *   [加载时间过长](#_223)
    *   [页面模板](#_229)
    *   *   [只要进度条不要 Logo](#Logo_232)
        *   [自定义加载背景图](#_259)
    *   [激活嵌入资源](#_268)
*   [五. IIS 部署](#IIS__288)
*   *   [启用 Internet Infomation Services](#Internet_Infomation_Services_289)
    *   [添加程序到 IIS](#IIS_291)
*   [六. 浏览器设置](#_303)
*   [七. UnityScript 与 JavaScript 通信](#UnityScriptJavaScript_314)

一.[WebGL](https://so.csdn.net/so/search?q=WebGL&spm=1001.2101.3001.7020) 不能干的那些事
--------------------------------------------------------------------------------

1. 内置的 video player 无法播放。（可以使用 [AVPro](//download.csdn.net/download/qq_26318597/12584049) 播放）  
2. 多线程  
3.socket(可以用 UnityWebRequest 或 websocket)  
4. 不支持`dynamic`类型，可以使用 object。  
5. 不支持 ComputeShader： SystemInfo.supportsComputeShaders  
![](https://img-blog.csdnimg.cn/be8e5a1af6f140b48e311a6229416a65.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

二. 注意事项
-------

### 1. 播放声音

要去掉 AutoPlay

### 2. 跨域

[参考 1](https://www.cnblogs.com/bossing/p/10943045.html)  
[参考 2](https://blog.csdn.net/beihuanlihe130/article/details/75315204?locationNum=6&fps=1)  
[官网](https://docs.unity3d.com/Manual/webgl-networking.html)  
web.config 添加

```
<httpProtocol>
			<customHeaders>
				<add  />
				<add  />
				<add />
				<add  />
			</customHeaders>
		</httpProtocol>
```

![](https://img-blog.csdnimg.cn/20210112180653124.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

### 3. 发布 http or https?

当发布到`https`上时程序中访问`http`的都会被改成 https, 这时候一般就报错了。。。

### 4. 包体大小

注意工程中尽量不用`Resources`文件夹，不然打包的时候会导致包体过大。因为放在该文件夹下的东西**都会**被打包。

<table><thead><tr><th>是否包含 Resources</th><th>build 包体大小</th></tr></thead><tbody><tr><td>包含 Resources</td><td>14M</td></tr><tr><td>无 Resources</td><td>12.7M</td></tr><tr><td>无 Resource+Assembly Definitions</td><td>8.93M</td></tr></tbody></table>

### 5.Odin

有的类型在 WebGL 平台并**不支持**序列化，如果你使用了 Odin 就需要在打包前生成`AOT`:  
![](https://img-blog.csdnimg.cn/20210127181937173.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)  
![](https://img-blog.csdnimg.cn/20210127182059601.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

### 6.T 序列化失败

```
T序列化失败，System.Reflection.Emit.DynamicMethod::.ctor
```

把序列化工具换成 [Json .Net For Unity](https://assetstore.unity.com/packages/tools/input-management/json-net-for-unity-11347)

三. 参考资料
-------

[hi,WebGL](http://www.hiwebgl.com/?p=628#WebGL-2)  
[Unity 发布 WebGL 注意事项](https://my.oschina.net/u/4305185/blog/3848900)  
[Unity WebGL 官方教程](https://docs.unity3d.com/Manual/webgl.html)  
[Unity WebGL 官方教程翻译](https://blog.csdn.net/u010930289/article/details/55814101)  
[发布后打不开](https://my.oschina.net/xiongjunyu/blog/680015)  
[Unity WebGL 游戏](https://simmer.io/)  
[官方 WebGL Tiny](https://www.unity3d.com/tiny)  
[IIS 的搭建](https://blog.csdn.net/yuanguozhengjust/article/details/25747729)  
[别个的笔记](https://blog.csdn.net/weixin_43996171/article/details/106563458)  
[问题总结](https://blog.csdn.net/qq_41594985/article/details/106718787)

四. Build
--------

空场景 build 耗时~ 142s  
[测试 demo](//download.csdn.net/download/qq_26318597/12569192)

### 主要步骤

Build 后目录配置 配置并 Build web.config 手机端去掉提示框 选择模板 自定义模板 勾选 WebAssembly Streaming

### web.config

需要在 index.html 同级目录下添加`web.config`配置文件。  
需要根据部署的服务器决定：

#### Apache

`web.config`后缀改成`.htaccess`  
`Gzip版本`:

```
<IfModule mod_mime.c>
  AddType application/octet-stream .unityweb
  AddEncoding gzip .unityweb
  AddType application/wasm .wasm
  AddEncoding gzip .wasm
  AddOutputFilterByType DEFLATE application/wasm
</IfModule>
```

`Brotli版本`：

```
<IfModule mod_mime.c>
  AddEncoding br .unityweb
  RemoveType .wasm
  AddType application/wasm .wasm
  RemoveType .unityweb
  AddType application/octet-stream .unityweb
</IfModule>
```

#### IIS

首先安装 [`URL Rewrite`](https://download.csdn.net/download/qq_26318597/14109716)！

```
<?xml version="1.0" encoding="UTF-8"?>
<configuration>
  <system.webServer>
    <staticContent>
      <remove fileExtension=".unityweb" />
      <mimeMap fileExtension=".unityweb" mimeType="application/octet-stream" />
      <remove fileExtension=".wasm" />
      <mimeMap fileExtension=".wasm" mimeType="application/wasm" />
    </staticContent>
    <rewrite>
      <outboundRules>
        <rule >
          <match serverVariable="RESPONSE_Content-Encoding" pattern=".*" />
          <conditions>
            <add input="{REQUEST_FILENAME}" pattern="\.(unityweb|wasm)$" />
          </conditions>
          <action type="Rewrite" value="gzip" />
        </rule>
      </outboundRules>
    </rewrite>
  </system.webServer>
</configuration>
```

### 手机端去掉提示框

在手机端打开 wegl 项目会弹出不支持 webgl 的提示框，不想要的话可以把`UnityLoader.js`文件内的提示框代码改下（line:2041）：  
修改前代码

```
compatibilityCheck: function(e, t, r) {
    UnityLoader.SystemInfo.hasWebGL ? UnityLoader.SystemInfo.mobile ? e.popup("Please note that Unity WebGL is not currently supported on mobiles. Press OK if you wish to continue anyway.", [{
      text: "OK",
      callback: t
    }]) : ["Edge", "Firefox", "Chrome", "Safari"].indexOf(UnityLoader.SystemInfo.browser) == -1 ? e.popup("Please note that your browser is not currently supported for this Unity WebGL content. Press OK if you wish to continue anyway.", [{
      text: "OK",
      callback: t
    }]) : t() : e.popup("Your browser does not support WebGL", [{
      text: "OK",
      callback: r
    }])
  },
```

修改后

```
compatibilityCheck: function(e, t, r) {
    UnityLoader.SystemInfo.hasWebGL ?  ["Edge", "Firefox", "Chrome", "Safari"].indexOf(UnityLoader.SystemInfo.browser) == -1 ? e.popup("Please note that your browser is not currently supported for this Unity WebGL content. Press OK if you wish to continue anyway.", [{
      text: "OK",
      callback: t
    }]) : t() : e.popup("Your browser does not support WebGL", [{
      text: "OK",
      callback: r
    }])
  },
```

### 全屏

`index.html` 修改如下：  
![](https://img-blog.csdnimg.cn/20200706105101427.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

```
<!DOCTYPE html>
<html lang="en-us">

<head>
  <meta charset="utf-8">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <title>Unity WebGL Player | Pudong</title>
  <link rel="shortcut icon" href="TemplateData/favicon.ico">
  <link rel="stylesheet" href="TemplateData/style.css">
  <script src="TemplateData/UnityProgress.js"></script>
  <script src="Build/UnityLoader.js"></script>
  <script>
    var gameInstance = UnityLoader.instantiate("gameContainer", "Build/build.json", {
      onProgress: UnityProgress
    });
  </script>
  <!-- 滚动条隐藏 -->
  <style type="text/css">
    body {
      overflow: scroll;
      overflow-x: hidden;
      overflow-y: hidden;
    }
  </style>

  <!-- 窗口自适应 -->
  <script type="text/javascript">
    function ChangeCanvas() {
      document.getElementById("gameContainer").style.width = window.innerWidth + "px";
      document.getElementById("gameContainer").style.height = window.innerHeight + "px";
      document.getElementById("#canvas").style.width = window.innerWidth + "px";
      document.getElementById("#canvas").style.height = window.innerHeight + "px";
    }
  </script>
</head>

<body onResize="ChangeCanvas()">
  <div class="webgl-content" style="position:absolute;width: 100%; height: 100%;z-index:1" id="gameContainer"></div>
  <div style="position:absolute;z-index:2">

  </div>
</body>

</html>
```

`以上修改只能做到页面最大化，如果要全屏可以手动F11或者添加其他代码`  
![](https://img-blog.csdnimg.cn/20210126143018292.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

### 加载时间过长

1. 使用 Gzip 压缩格式  
![](https://img-blog.csdnimg.cn/20200706105507165.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)  
![](https://img-blog.csdnimg.cn/20200706105600353.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

### 页面模板

[模板 demo](//download.csdn.net/download/qq_26318597/12581762)  
![](https://img-blog.csdnimg.cn/20200706171651321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

#### 只要进度条不要 Logo

用以下内容替换`UnityProgress.js`

```
function UnityProgress(gameInstance, progress) {
  if (!gameInstance.Module)
    return;

  if (!gameInstance.progress) {
    gameInstance.progress = document.createElement("div");
    gameInstance.progress.className = "progress " + gameInstance.Module.splashScreenStyle;
    gameInstance.progress.empty = document.createElement("div");
    gameInstance.progress.empty.className = "empty";
    gameInstance.progress.appendChild(gameInstance.progress.empty);
    gameInstance.progress.full = document.createElement("div");
    gameInstance.progress.full.className = "full";
    gameInstance.progress.appendChild(gameInstance.progress.full);
    gameInstance.container.appendChild(gameInstance.progress);
  }
  gameInstance.progress.full.style.width = (100 * progress) + "%";
  gameInstance.progress.empty.style.width = (100 * (1 - progress)) + "%";
  if (progress == 1)
    gameInstance.progress.style.display = "none";
}
```

[Unity 发布 WebGL 时如何修改、删除默认的载入进度条](https://gameinstitute.qq.com/community/detail/128615)

#### 自定义加载背景图

如下所示把`黑色的背景`换成了图片！！！  
![](https://img-blog.csdnimg.cn/20200717143812458.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)  
方法概况：直接把 Logo 换成想要的背景图，然后在 css 中修改尺寸即可`｛（>A<）｝〃≈≈大罗法咒`  
详细步骤：  
1.`TemplateData/progressLogo.Dark.png` 替换成需要的背景图片。（ps: 进度条是`progressFull.Dark.png`）  
2. 打开`style.css`修改 logo 的宽高`.webgl-content .logo {background: url('progressLogo.Light.png') no-repeat center / contain; width: 100%; height: 100%;}`  
3.(ノ・_・) ノ去！卍卍卍

### 激活嵌入资源

[介绍](https://docs.unity3d.com/Manual/webgl-embeddedresources.html)

```
using UnityEditor;
namespace ZYF
{

    public class ZYF_WebGLEditorScript
    {
        [MenuItem("WebGL/Enable Embedded Resources")]
        [System.Obsolete]
        public static void EnableErrorMessageTesting()
        {
            PlayerSettings.SetPropertyBool("useEmbeddedResources", true, BuildTargetGroup.WebGL);
        }
    }
}
```

五. IIS 部署
---------

### 启用 Internet Infomation Services

![](https://img-blog.csdnimg.cn/20200512113951513.gif)

### 添加程序到 IIS

1.`把build目录添加到IIS`  
![](https://img-blog.csdnimg.cn/20200512115624453.gif)  
2.`通过浏览器打开（http://localhost/webgl/ ）`  
当然也可以用 ip 打开，笔者本地 ip 为：192.168.10.215，所以地址为：http://192.168.10.215:80/webgl/

![](https://img-blog.csdnimg.cn/20200512120054241.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)  
报错了就说明需要添加`web.config`文件！  
`重新打开页面就正常了`

![](https://img-blog.csdnimg.cn/20200512120653513.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI2MzE4NTk3,size_16,color_FFFFFF,t_70)

六. 浏览器设置
--------

Chrome 快捷方式右键属性在目标内添加 `--enable-webgl --ignore-gpu-blacklist --allow-file-access-from-files`即可 (注意第一个的空格)  
示例：“C:\Program Files (x86)\Google\Chrome\Application\chrome.exe” --enable-webgl --ignore-gpu-blacklist --allow-file-access-from-files  
![](https://img-blog.csdnimg.cn/20200512135328871.gif)  
Firefox:

```
地址栏输入：about:config
找webgl.disabled  false
找webgl.force-enabled true
```

七. UnityScript 与 JavaScript 通信
------------------------------

[┏ (゜ω゜)=👉](https://blog.csdn.net/qq_26318597/article/details/113177003)