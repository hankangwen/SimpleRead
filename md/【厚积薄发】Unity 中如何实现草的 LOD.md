> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/IpuUTobHNhlILSp7ILMSZQ)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/ALp6MpyX3HB2tL5Co7Hre0bjXJaxlarjYU1Qpm66AKXQZCQnxdIPicwicvicjvBCmBMGzNQiavcP0XKugelpZQO86Q/640?wx_fmt=png&from=appmsg)

这是第 379 篇 UWA 技术知识分享的推送，精选了 UWA 社区的热门话题，涵盖了 UWA 问答、社区帖子等技术知识点，助力大家更全面地掌握和学习。

UWA 社区主页：community.uwa4d.com

UWA QQ 群：465082844

**本期目录：**

*   Unity 中如何实现草的 LOD  
    
    --------------------
    
*   用 Compute Shader 处理图像数据后在安卓机上不能正常显示渲染纹理
    ---------------------------------------
    
*   关于进游戏程序集加载的问题
    -------------
    
*   预制件编辑模式一直在触发自动保存
    ----------------
    

**Terrain**

**Q：****Unity 自带的 Terrain 中草作为 Detail，无法设置 LOD Group。感觉草的 LOD 应该是一个非常基础的功能，Unity 选择不支持这个功能的原因是什么？要想实现草的 LOD，我想到的几种方式：**

**1. 手动放置。**

**2. 自己写 Procedural 工具批量生成。**

**3. 使用 Terrain 的 Paint Trees 功能变通实现。即把草当作一种 Tree，增大种植密度。不知道这种实现会不会有副作用。**

**或者有没有更好的实现方式？**

******针对以上问题，有经验的朋友欢迎转至社区交流分享：******

https://answer.uwa4d.com/question/65fe527f5c7f5d2c5805d354

**Shader**

**Q：****我用 Compute Shader 来做 2D 游戏图像数据的处理工作。**

**这是一款老 2D 游戏，客户端资源中大量图像都是以 UShort[] 数组存储的。读取后数组中的一个 UShort 值对应一个像素颜色值，通过写一个 Compute Shader，将这些像素颜色值写到 RenderTexture 上，然后用 Canvas+RawImage 显示在主摄像机中。**

**在编辑器中已经正常运行了，每帧渲染耗时 8-10ms（因为换装游戏的关系，需要对颜色值做很多叠加计算等处理）。**

**我打包出 APK 包，在安卓手机真机上却无法像在编辑器里一样显示图像。**

**在安卓手机运行时，打 Log 检测：**

```
SystemInfo.supportsComputeShaders
```

**安卓真机系统是支持这个 Compute Shader 的。**  

**用 FrameDebugger 查看时，在编辑器里：**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/ALp6MpyX3HCZVibvD6EE1OXfdQC7ib2eK1iaNBz4yIoo5aDsGDhNn8mzOicibdDL9tjrI4PtzqiaYhTkdK9JmJ0RlFkw/640?wx_fmt=png&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1)

**可以看到运行了 Compute Shader，而且显示了这个 Compute Shader 的名称：XImageComputeShader。**  

**上图第二红框中就是渲染出的 RenderTexture 图像内容。通过绑定 RawImage，在游戏画面中可以正常显示。**

**但在安卓机里，看不到运行 Compute Shader 的地方，而 RenderTexture 的图像内容全部为空。**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/ALp6MpyX3HCZVibvD6EE1OXfdQC7ib2eK1GuMfMmPBHESQwnj3TsMfYsbHYNkouN2JibQpxIKYntiaiacy9otbqial9Q/640?wx_fmt=png&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1)

**而游戏画面中，也是空白内容，没有图像。****请教各位大佬，问题可能出在哪里？**

**另外，我用了华佗热更，再用 IL2CPP，是否会因为某些原因被裁剪掉？如何验证修复呢？**

A：已解决：

1. 屏幕实际分辨率和手机品牌标志分辨率的差别导致我传入的图像数组尺寸不对。

2. 华佗热更 “可能” 裁剪掉了某些关键部分，我把 Compute Shader 在游戏初始化时做了个调用就解决了。

********************感谢题主浪里个狼 @UWA 问答社区提供了回答，********************欢迎大家转至社区交流：************************

https://answer.uwa4d.com/question/65f5759f3625c22cffcb1eba

**Script**

**Q：对于非程序人员他们不会修改代码，每次进游戏都要 Reload 一遍程序集，感觉没什么必要，然后就把 Reload Domain 关掉了。后续要处理静态数据有什么好办法吗？一个一个手动改吗？**

A：Mono 的脚本在 OnDestroy 里面对静态数据置空和取消静态事件。

非 Mono 的脚本自己封装一个带 [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.SubsystemRegistration)] 的方法对静态数据清空。

然后还需要对有些插件进行修改，因为有些插件没有对 EditorSettings.enterPlayModeOptionsEnabled 进行判断可能在 Editor 模式下有问题。

********************感谢菜鸟 @UWA 问答社区提供了回答，********************欢迎大家转至社区交流：************************

https://answer.uwa4d.com/question/65f931a79ff41504a764ab1a

**Prefab**

**Q：****在打开预制体编辑模式的时候，勾选 Auto Save 会一直触发这个自动保存功能，****不勾选则会一直显示已修改，若手动点击 Save，还是会触发已修改，不知道怎么回事？**

A：我已经解决了。原来是 QHierarchy 这个插件出现了问题，具体原因没找到，但是删掉重新导入就好了。

**************************感谢题主花小邪 @UWA 问答社区提供了回答，********************欢迎大家转至社区交流：******************************  

https://answer.uwa4d.com/question/65fe89f35c7f5d2c5805d355

封面图来源于网络

* * *

今天的分享就到这里。生有涯而知无涯，在漫漫的开发周期中，我们遇到的问题只是冰山一角，UWA 社区愿伴你同行，一起探索分享。欢迎更多的开发者加入 UWA 社区。

UWA 官网：www.uwa4d.com  

UWA 社区：community.uwa4d.com

UWA 学堂：edu.uwa4d.com

官方技术 QQ 群：465082844

![](https://mmbiz.qpic.cn/mmbiz_png/ALp6MpyX3HDae00jn6Gib7zYgLkZDIQlqZBY5wricwesNPRbZItT8zIdnDogVE8FicXfdBibjUo8dkRgtdZohtUtVQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1&retryload=1)

（长按识别二维码进入 UWA 问答）

点击下方名片关注我们，将我设为星标，及时接收小编每日推送哦，性能优化不迷路～

[**UWA Pipeline 2.6.0 版本更新**](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936519&idx=1&sn=08daa11831fa22d80b372f6fb822509e&chksm=f1c91135c6be9823ce988a46182c7a32d5adfac1ab9ff4e450e993b72e9b7d5e8a7e41cb47dd&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/ALp6MpyX3HDPbJocuz3oB53yUib3KQTmhczlScgWQzXFVWMFeF0EBEDLibRShKMuS5VvU9At2ibTIXRhHoa4JeVoA/640?wx_fmt=png&from=appmsg&wxfrom=5&wx_lazy=1&wx_co=1)](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936519&idx=1&sn=08daa11831fa22d80b372f6fb822509e&chksm=f1c91135c6be9823ce988a46182c7a32d5adfac1ab9ff4e450e993b72e9b7d5e8a7e41cb47dd&scene=21#wechat_redirect)

**近期精彩回顾**

> [******【厚积薄发************】大地形的一种简化 RVT******](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936790&idx=1&sn=6b5b52352a71f4892616af26795f06af&chksm=f1c91224c6be9b32cc6263f4fd11be051d320ce946bb3d280941e66ef0bc2c023b5566cc56bc&scene=21#wechat_redirect)  
> 
> [******【学堂上新】******【传送篇】MMORPG 全栈式网络游戏开发之旅************](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936814&idx=1&sn=4d65acbfed08bec81f928d0131b77728&chksm=f1c9121cc6be9b0aba5f5dca5287fd10ddfb199db9141c8fe8a940fc7ae07685b40a2a2dd759&scene=21#wechat_redirect)  
> 
> [******【万象更新】************UWA Pipeline 2.6.0 版本更新******************](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936519&idx=1&sn=08daa11831fa22d80b372f6fb822509e&chksm=f1c91135c6be9823ce988a46182c7a32d5adfac1ab9ff4e450e993b72e9b7d5e8a7e41cb47dd&scene=21#wechat_redirect)
> 
> [******【学堂上新】******************从 0 到 1 开发管理后台************************](http://mp.weixin.qq.com/s?__biz=MzI3MzA2MzE5Nw==&mid=2668936742&idx=1&sn=439673fb6f12e4f480cf957b5802d7ea&chksm=f1c91254c6be9b423d7c16961f61e2b8d8c5b9b781016f1b034e798ddf04b7b5577c18988a6c&scene=21#wechat_redirect)

![](https://mmbiz.qpic.cn/mmbiz_png/ALp6MpyX3HBwPy7V6xFBRqWr7eWDgQnCnYoC3wn5celiaqB2dfl2jZXKpAVnYrAqvQYYd9UvXNgeejzckxzPqxA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)