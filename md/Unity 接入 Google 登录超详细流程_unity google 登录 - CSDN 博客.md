> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_39940718/article/details/130029503?spm=1001.2100.3001.7377&utm_medium=distribute.pc_feed_blog_category.none-task-blog-classify_tag-18-130029503-null-null.nonecase&depth_1-utm_source=distribute.pc_feed_blog_category.none-task-blog-classify_tag-18-130029503-null-null.nonecase)

接入环境
----

1、unity 版本：2021.3.21f1  
特别说明：通过 Unityhub 安装的 Unity，需要安装对应版本所需的 JDK、SDK、NDK，我们默认使用 Unity 自带的，不需要使用自己下载的，否则可能会导致打包失败的问题。![](https://img-blog.csdnimg.cn/26853fd3bbf64b70b55861206b4c3be5.png#pic_center)  
![](https://img-blog.csdnimg.cn/02d94ba453b744b489d7a57d47ad6dbb.png#pic_center)

2、google 登录 sdk 版本：GoogleSignIn_v1.0.4.1  
特别说明：  
(1)GoogleSignIn 官方插件地址是：[GoogleSignIn](https://github.com/googlesamples/google-signin-unity)，但是这个版本目前有些问题，IOS 打包报错，因为 IOS 部分代码没有更新。  
(2) 所以我们使用别人解决完了的版本：[无 bug 版 GoogleSignIn_v1.0.4.1](https://github.com/CodeMasterYi/google-signin-unity)，这里面有文档可以看  
(3) 可以直接通过这个地址下载 unitypackage 包导入自己项目：[GoogleSignIn_v1.0.4.1.unitypackage](https://github.com/CodeMasterYi/google-signin-unity/releases/tag/v1.0.4.1)，这个文件需要下载。**GoogleSignIn_v1.0.4.1.unitypackage 需要导入自己项目。**  
3、安卓依赖管理插件 EDM4U:[EDM4U 下载地址](https://github.com/googlesamples/unity-jar-resolver)，这个插件需要下载，**external-dependency-manager-1.2.175.unitypackage 需要导入自己项目。**

开始接入
----

### 创建工程

1、新建 Unity 工程  
2、导入前面提到的两个 unitypackage 包  
3、创建 UI，一个登录按钮，一个显示用文本，一个挂载脚本的空物体。![](https://img-blog.csdnimg.cn/3eebb9b473fe4f67a252fd0f3c4e5420.png#pic_center)  
4、新建脚本，脚本里的代码可以直接从 https://github.com/CodeMasterYi/google-signin-unity 这个示例代码里面复制进来。然后把脚本拖到 GoogleSdkObj 上，statusText 拖过去进行赋值，webclientid 下面再详细说。  
![](https://img-blog.csdnimg.cn/cfe947bcc3f24b60bd8a902762aa9c0c.png#pic_center)

5、给按钮添加点击事件，如图所示。  
![](https://img-blog.csdnimg.cn/1154590dae6e4bebb8a6bd04f4c6872d.png#pic_center)  
6、接下来就是这个 WebClientId 了。

### WebClientId 获取

1、进入这个地址：[谷歌 API 控制台](https://console.cloud.google.com/?hl=zh-cn)，如果没有 cloud 项目的话需要新建 cloud 项目，如果已有直接选择项目进入。  
2、创建 OAuth 同意屏幕，如果已有可以忽略。  
![](https://img-blog.csdnimg.cn/055173907820463ab7f5db4be6b438c9.png#pic_center)  
这 4 个步骤完成就可以了。  
3、在 “凭据” 页面上，创建两个 Android 类型的客户端 ID

![](https://img-blog.csdnimg.cn/e40145b8ec514a839e33fc077c614e96.png#pic_center)  
![](https://img-blog.csdnimg.cn/52a45ebc4aae41d6ab693630693c4e64.png#pic_center)  
![](https://img-blog.csdnimg.cn/a274524f01054edebf844dd9fe812839.png#pic_center)**–这是借某位大佬的一张图–**

4、在 “凭据” 页面上，创建一个 Web 类型的客户端 ID  
![](https://img-blog.csdnimg.cn/d83f036442594cd59409b2e8f30e43af.png#pic_center)  
5、找到创建完成的凭据，复制出 WebClientId  
![](https://img-blog.csdnimg.cn/6718ac65706947fd9d56b2b0ed9a925d.png#pic_center)  
6、把这个 WebClientId 赋值到代码，或者直接在 inspector 界面赋值。

```
using System;
    using System.Collections.Generic;
    using System.Threading.Tasks;
    using Google;
    using UnityEngine;
    using UnityEngine.UI;

    public class SigninSampleScript : MonoBehaviour
    {

        public Text statusText;

        public string webClientId = "131761931994-ljnoj13a9gfhruftaqv2a5iicr0i30ub.apps.googleusercontent.com";

        private GoogleSignInConfiguration configuration;

        // Defer the configuration creation until Awake so the web Client ID
        // Can be set via the property inspector in the Editor.
        void Awake()
        {
            configuration = new GoogleSignInConfiguration
            {
                WebClientId = webClientId,
                RequestIdToken = true
            };
            GameObject.DontDestroyOnLoad(this);
        }

        public void OnSignIn()
        {
            GoogleSignIn.Configuration = configuration;
            GoogleSignIn.Configuration.UseGameSignIn = false;
            GoogleSignIn.Configuration.RequestIdToken = true;
            AddStatusText("Calling SignIn");

            GoogleSignIn.DefaultInstance.SignIn().ContinueWith(
              OnAuthenticationFinished);
        }

        public void OnSignOut()
        {
            AddStatusText("Calling SignOut");
            GoogleSignIn.DefaultInstance.SignOut();
        }

        public void OnDisconnect()
        {
            AddStatusText("Calling Disconnect");
            GoogleSignIn.DefaultInstance.Disconnect();
        }

        internal void OnAuthenticationFinished(Task<GoogleSignInUser> task)
        {
            if (task.IsFaulted)
            {
                using (IEnumerator<System.Exception> enumerator =
                        task.Exception.InnerExceptions.GetEnumerator())
                {
                    if (enumerator.MoveNext())
                    {
                        GoogleSignIn.SignInException error =
                                (GoogleSignIn.SignInException)enumerator.Current;
                        AddStatusText("Got Error: " + error.Status + " " + error.Message);
                    }
                    else
                    {
                        AddStatusText("Got Unexpected Exception?!?" + task.Exception);
                    }
                }
            }
            else if (task.IsCanceled)
            {
                AddStatusText("Canceled");
            }
            else
            {
                AddStatusText("Welcome: " + task.Result.DisplayName + "!");
            }
        }

        public void OnSignInSilently()
        {
            GoogleSignIn.Configuration = configuration;
            GoogleSignIn.Configuration.UseGameSignIn = false;
            GoogleSignIn.Configuration.RequestIdToken = true;
            AddStatusText("Calling SignIn Silently");

            GoogleSignIn.DefaultInstance.SignInSilently()
                  .ContinueWith(OnAuthenticationFinished);
        }


        public void OnGamesSignIn()
        {
            GoogleSignIn.Configuration = configuration;
            GoogleSignIn.Configuration.UseGameSignIn = true;
            GoogleSignIn.Configuration.RequestIdToken = false;

            AddStatusText("Calling Games SignIn");

            GoogleSignIn.DefaultInstance.SignIn().ContinueWith(
              OnAuthenticationFinished);
        }

        private List<string> messages = new List<string>();
        void AddStatusText(string text)
        {
            if (messages.Count == 5)
            {
                messages.RemoveAt(0);
            }
            messages.Add(text);
            string txt = "";
            foreach (string s in messages)
            {
                txt += "\n" + s;
            }
            statusText.text = txt;
        }
    }
```

打包测试
----

1、设置一下 unityplayersetting，圈起来的地方要注意，  
(1) 包名要和 google 上架的一致，  
(2) 打包方式 il2cpp，  
(3)keystore 要填好，  
(4)custom main gradle Template 要勾上，然后 google 地址换成阿里云的

```
maven {
            // url "https://maven.google.com"
            url "https://maven.aliyun.com/nexus/content/groups/public"
        }
```

![](https://img-blog.csdnimg.cn/893240c904504e29b15d33fd6323d94c.png#pic_center)  
![](https://img-blog.csdnimg.cn/3133dd3b0bf14201a498bab29613ffba.png#pic_center)

(5)custo gradle properties Template 要勾上, 然后 gradleTemplate.properties 脚本里需要加上这两句

```
android.useAndroidX=true
android.enableJetifier=true
```

![](https://img-blog.csdnimg.cn/b255307fe5574f75b4e66825989fda42.png#pic_center)

2、切换到安卓平台  
3、注册安卓依赖到 mainTemplate.gradle 文件  
(1)  
![](https://img-blog.csdnimg.cn/7dc6735634db4712bbcac8c66fc52e06.png#pic_center)

(2)resolve 之后修改 maven 地址  
![](https://img-blog.csdnimg.cn/ad22b4a31e034650b2806ff8a002e3b9.png#pic_center)  
4、打包测试

**整个工程已上传，点击下面的链接可免费下载**  
[1、测试工程下载](https://download.csdn.net/download/qq_39940718/87667105)  
[2、GoogleSignIn_v1.0.4.1.unitypackage 下载](https://github.com/CodeMasterYi/google-signin-unity/releases/tag/v1.0.4.1)  
[3、安卓依赖管理插件 EDM4U 下载](https://download.csdn.net/download/qq_39940718/87901349)