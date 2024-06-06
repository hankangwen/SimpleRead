> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/s2q9H2diAkQmtzG8zczXKw)

本文转载自 Unity 社区，作者：Mark

注意：新的输入法系统需要 Unity 2019.4+ 和 .NET 4 运行时。它不适用于 .NET 3.5 的项目。

教程版本：Unity 2021.3.26

大家好，我是 Mark 。Unity 新版输入系统一直没时间学，最近闲下来了抽空研究了一下和旧版相比在可配置性、多设备支持、性能等方面都有明显的优势。我也是参考官方的教程边学边记录的有啥问题可以在评论区留言，后期我也会抽空继续补充更加进阶的教程。如果该教程对你有帮助请点赞＋收藏。

官方教程：

https://docs.unity.cn/Packages/com.unity.inputsystem@1.1/manual/QuickStartGuide.html

**安装**

 **打开 Package Manager**

**导航栏 -> Window -> Package Manager**

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHhs0wFDvBLAApqJlMEzKfQJqZJRpLd8HlItQKcCuQdWXrQQmAHlm2Aw/640?wx_fmt=png&from=appmsg)

 **安装 Input System**

选择 **Unity Registry** 在列表中找到 Input System 点击 Install 安装。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHTGiayywdh3HuuIPZ6ibHO6XKob2KsUUfLvWZPfCaldZOr1YPUaq7cicpw/640?wx_fmt=png&from=appmsg)

点击 Yes 启用新版 Input System 等待 Unity 重新启动。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHjkrQ8Z7vCIh0jOX260Hu2cHPH3uH8z8LkACt33cob9gJpBicj1p4mWg/640?wx_fmt=png&from=appmsg)

Unity 默认会同时启用旧版和新版输入系统，你可以在 **Player settings** 中 (Edit -> Project Settings -> Player ->Active Input Handling) 找到相应的设置。可以随时修改这里的设置，这样做依然会重启编辑器。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHQrqlehvhPZEl4ogLcgoovE5gyiaTCpq6rMFB8QAqo3w7QGPiaDyuGqDA/640?wx_fmt=png&from=appmsg)

**入门指南**

 **快速监听某个按键按下抬起操作**

```
void Update()  
{  
    // 检查空格键是否在这个帧被按下  
    if (Keyboard.current.spaceKey.wasPressedThisFrame)  
    {        
        Debug.Log("Space key was pressed");  
    }   
    // 检查空格键是否在这个帧被释放  
    if (Keyboard.current.spaceKey.wasReleasedThisFrame)  
    {        
        Debug.Log("Space key was released");  
    }   
    // 检查左鼠标键是否在这个帧被按下  
    if (Mouse.current.leftButton.wasPressedThisFrame)  
    {        
        Debug.Log("Left mouse button was pressed");  
    }  
    // 检查左鼠标键是否在这个帧被释放  
    if (Mouse.current.leftButton.wasReleasedThisFrame)  
    {        
        Debug.Log("Left mouse button was released");  
    }
}

```

 **使用可视化编辑器来建立映射**

**Project -> Create -> Input Actions**

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHnfpmib3DPYe6HrDB7ibMS8icCAZcY7MopgcvYzJcRDstmc2bYibKnQkTIQ/640?wx_fmt=png&from=appmsg)

新建 Input Actions 给其命名（名称无所谓），笔者命名为 Test Input Controls 完成后，选中该文件勾选 **Generate C# Class 点击 Apply** 后 Unity 会为我们生成一个 Action 的包装类，方便后续在代码中引用。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHo139XwtG5gD6LCCr4tVucSBQ3onSHbicmiaxEMOLFxqZx3HicvFxjICEQ/640?wx_fmt=png&from=appmsg)

**Action Map**

可以理解为一个组织和管理输入动作的一种方式。通过将相关的输入动作放在同一个 Action Map 中，可以更好地管理输入逻辑。例如，可以将所有与玩家移动相关的输入动作放在一个叫做 "Movement" 的 Action Map 中。

**Action**

一个具体的输入动作，比如按键按下、摇杆移动等。

生成结束点击 Edit asset 创建第一个 Action Map 并将其命名为 Player 并将 Actions 列表生成的 Action 重命名为 Fire 。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHWS0eaw4GA9ORwXpY53hewicaCPxGbHAp7sDSny1hm6Dkd2NL4zOicZGA/640?wx_fmt=png&from=appmsg)

选中 **<No Binding>** 给 Fire Action 映射对应的按键（按键可以自定义，笔者映射的按键为键盘的 K 键）

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHsSyL4rmKDh42SFcXKHdjiat3Y2FEIRpoSKTAR4P5TPwrIyuPLwJATEw/640?wx_fmt=png&from=appmsg)

也可以绑定多个按键对应不同的操作设备，笔者映射的第二个按键为鼠标左键

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHdpM3s29J35BsyKkU1lxauTpc0ntELibpQWD5eprYiaibwdoN41ZN1G7uA/640?wx_fmt=png&from=appmsg)

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDH8jNPHDNdibeI8Tm1szws1N8ySrxuZy5DEUZhaMPwdjZGgMibwibT3rUBw/640?wx_fmt=png&from=appmsg)

完成上述操作后点击 **Save Asset** 保存当前映射表，这样做可以绑定多个物理输入得到的输入值也只会影响同引用的 Action 对象。

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHMozTOicdFZnqROWia5ZhpqvmNtOibozic4Q3aZG6ickChJCwwJlicGRibGM8A/640?wx_fmt=png&from=appmsg)

 **通过代码监听映射表中的按键**  

创建测试脚本 **TestInputSystem** （命名可随意），我们需要使用之前的 TestInputControls ，通过监听 started 和 canceled 实现按键按下抬起操作。具体可参考下述代码

```
// 输入控制类的实例  
private TestInputControls InputControls;  
void OnEnable()  
{  
    InputControls = new TestInputControls(); // 创建输入控制实例  
    InputControls.Player.Fire.started += OnFireDown; // 注册开火开始动作的回调  
    InputControls.Player.Fire.canceled += OnFireUp; // 注册开火结束动作的回调  
    InputControls.Enable(); // 启用输入控制  
}  
//当开火动作被触发时调用此方法。
private void OnFireDown(InputAction.CallbackContext Obj)  
{  
    Debug.Log($"Fire Down | KeyName:{Obj.control.name}"); // 输出"Fire Down"到控制台 
}
//当开火动作释放时调用此方法。
private void OnFireUp(InputAction.CallbackContext Obj)  
{  
    Debug.Log($"Fire Up | KeyName:{Obj.control.name}"); // 输出"Fire Up"到控制台 
}
//主要用于移除输入动作的回调函数，并禁用输入控制。
private void OnDisable()  
{  
    InputControls.Player.Fire.started -= OnFireDown; // 移除开火开始事件的监听  
    InputControls.Player.Fire.canceled -= OnFireUp; // 移除开火结束事件的监听 
    InputControls.Disable(); // 禁用输入控制  
}

```

**测试效果**

可以看到，我们使用一套代码就可以同时监听键盘和鼠标的输入

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHUUZbf0GmQ5L7aKHciazpsnU3pjNHl3D8aYvzTkAWiaY3g7nxxRF5q8eg/640?wx_fmt=png&from=appmsg)

按下抬起有了，要想实现长按也很简单。选中 **TestInputControls** 点击 Edit asset 在 Action Properties 一栏点击 Interactions 后方的 ＋ 号添加 Hold

  

> Hold：按下并按住至少设定的持续时间（默认为 defaultHoldTime），则执行动作。（长按执行操作） MultiTap：需要多次轻击（在 tapTime 内按下并释放），每次轻击之间的间隔不超过 tapDelay 秒（双击或多击）

> Press：根据按钮的按下和释放顺序来触发特定的操作（例如：在按下按钮后执行某个动作或在释放按钮时执行某个操作）

> SlowTap：按下并按住控件一段时间后释放时执行操作（长按释放后执行操作） Tap：按下并按住小段时间内释放执行操作（点击）

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDHoZUtkQCZcHUOtGvtpS6vEKzS5gxuDDWVzF7AGBxLCfib8Uzo4fK93hw/640?wx_fmt=png&from=appmsg)

添加完 Hold 后，看一下它的两个变量。**如果默认值不能满足你的需求**，取消勾选 Default 可自定义变量值。修改 Hold Time 变量一般即可满足需求

> Press Point：按下按键这个阈值才能被认为是按下（笔者理解的是按压力度）

> Hold Time：按下并按住按键保持的时间 (以秒为单位)

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYGRguAXEnNGY76g0iaUtXTDH8qFVEMyuXrdD14rZbVmwAdvthyqPKMfYCA0b0Tu6HTTBOSeI0Aembw/640?wx_fmt=png&from=appmsg)

还是之前的代码在此基础上增加了长按监听的代码，具体参考下述代码

  

```
// 输入控制类的实例  
private TestInputControls InputControls;  
void OnEnable()  
{  
    InputControls = new TestInputControls(); // 创建输入控制实例  
    InputControls.Player.Fire.started += OnFireDown; // 注册开火开始动作的回调  
    InputControls.Player.Fire.performed  += OnLongPress; // 注册长按动作的回调  
    InputControls.Player.Fire.canceled += OnFireUp; // 注册开火结束动作的回调  
    InputControls.Enable(); // 启用输入控制  
}  
//当开火动作被触发时调用此方法。
private void OnFireDown(InputAction.CallbackContext Obj)  
{  
    Debug.Log($"Fire Down | KeyName:{Obj.control.name}"); // 输出"Fire Down"到控制台 
}  
//当开火动作持续时调用的方法。
private void OnLongPress(InputAction.CallbackContext Obj)  
{  
    Debug.Log($"Fire Long Press | KeyName:{Obj.control.name},持续时间{Obj.duration}"); // 输出动作持续时间  
}  
//当开火动作释放时调用此方法。
private void OnFireUp(InputAction.CallbackContext Obj)  
{  
    Debug.Log($"Fire Up | KeyName:{Obj.control.name}"); // 输出"Fire Up"到控制台  
}  
//主要用于移除输入动作的回调函数，并禁用输入控制。
private void OnDisable()  
{  
    InputControls.Player.Fire.started -= OnFireDown; // 移除开火开始事件的监听  
    InputControls.Player.Fire.performed  -= OnLongPress; // 移除长按事件的监听 
    InputControls.Player.Fire.canceled -= OnFireUp; // 移除开火结束事件的监听 
    InputControls.Disable(); // 禁用输入控制  
}

```

经过上述步骤，我们学习到了新版 InputSystem 中的三个最基本的按键触发（按下、抬起、长按）。

  

![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYEKoH22pA8qvtLR6sibsQ1T3uER5D68NCtia160eD4ycdibcicDEwHkfDiaSkKqCcROxBDctbS2mgZkmZA/640?wx_fmt=other&from=appmsg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

想要学习更多干货，[**Unite 全球开发者大会**](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247556292&idx=1&sn=fac1e534f3291c81d76f0d4f90047269&chksm=c1861f40f6f19656a06b85001bbc68b204afde61fa33abed9edc38af66b2939c808701d3f882&scene=21#wechat_redirect)等你来！  

**7 月 23 日 - 25 日**，Unite 将于上海隆重开启。1 场 Keynote 和多个专场，涵盖**团结引擎、游戏生态、数字孪生、智能座舱**等多重赛道，我们还准备了小而美的工作坊，覆盖**小游戏、开源鸿蒙、Vision Pro** 三大主题。

走过路过别错过。  

![图片](https://mmbiz.qpic.cn/sz_mmbiz_jpg/NYLZoOxGjYHwet5teZ2jxMtYAL6ia1fW1D2zmialVIPXc7kI3YcfdYLcqqhbN5P0KibiaDXxQOVGs1vP4eXQjOvZ1w/640?wx_fmt=other&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)

扫码购票处

  

  

![图片](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGia3ibXvfribSG3BEumwiakOoXOmvbw1a7icDGWF8wMoicDZqMko9kichBLEYug/640?wx_fmt=png)

[![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYE0pXoibgZdG402gsj2GEkeK632mNhkOAhQrAF5ulpjiaIklswNGlfBjP9YSwvFcr4QRKcY3JnDh2jA/640?wx_fmt=png&from=appmsg)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247556292&idx=1&sn=fac1e534f3291c81d76f0d4f90047269&chksm=c1861f40f6f19656a06b85001bbc68b204afde61fa33abed9edc38af66b2939c808701d3f882&scene=21#wechat_redirect)

[![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYEqXHeRtyzJvT56ibf00TSHFlABcj2BeP47P6Zv8RJIMiblzibV7AYmobkIRgnOj0sXtI2Ghtfm522Mg/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247554960&idx=1&sn=baaa3c68685a06d7fda1981b3a6d1cfc&chksm=c1861414f6f19d029a720f793f5e7743efa6bcc19ed86b9d9db8ec89cd039a427d5f386c7517&scene=21#wechat_redirect)

[![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFlmXNbMs1FdxC7KPpvg2EIq8dyKvEgibJtQpwToGrSB8bzw7YYjXl7icibt3S7A2qZU7NO0KJO9aEpQ/640?wx_fmt=png&from=appmsg)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247555484&idx=2&sn=b7c1242601dcf66ad5c5e4c0eaa17a6b&chksm=c1861a18f6f1930e1c5bd3a78b90ba094e3c0e7d271d2a77addb248a3ffac404ee9f3946cece&scene=21#wechat_redirect)

[![图片](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFhicnUTmPvVTnuSk3RX0WO8h4q4GuKCTMLTp9EzCCsrQ6s6ibLdyQaAXIkootlEiaLe6jlWCBjvoLfQ/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247539782&idx=1&sn=8fb062017695d7063dcb50ad3dfb9134&chksm=c1865fc2f6f1d6d4e99fc3529b8d9097400a4489ad38c0c4d0ddcf3c62b1ba9186fd1d455d12&scene=21#wechat_redirect)

**长按关注**

**Unity 官方微信**

第一时间了解 Unity 引擎动向，学习进阶开发技能

![图片](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsun6CMe09NXZkcm0GiaWH5X4CPfZTL3Qr1sx7pQSy6M4wpTibnlGgsZCauTnDicQiaSAsB4RhXza2bw/640?wx_fmt=gif)

 点击 “阅读原文”，跳转 Unite 2024 官网 

![图片](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGiak1T8bOLMtfRms9jViblv5tWzrm1ndtPKsj9A6fzH8G5p3gg9helEc1g/640?wx_fmt=gif)