> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [learn.u3d.cn](https://learn.u3d.cn/tutorial/urp-post-process-volume?chapterId=63562b2aedca72001f21d321#608a5fd53ed70d00215006fb)

> Unity3d 教程《URP 系列教程 | 如何使用 URP 中内置的后处理效果提升画面质量》, 本篇教程将教大家使用 URP Post-processing 中的 Global Volume 与 Local Volume，会主要介绍后期处理的一些效果调节如 Bloom、Vignette、Channel Mixer、Color Adjustments 等等。

章节1	URP系列教程 | 如何使用URP Post-processing中的Global Volume 与Local Volume

## 摘要

本篇教程将教大家使用URP Post-processing中的Global Volume 与Local Volume，会主要介绍后期处理的一些效果调节如 Bloom、Vignette、Channel Mixer、Color Adjustments 等等。我们来一起看下吧!!!

欢迎大家点击上方的收藏，您的收藏是我创作最大的动力~

*若对本课程有任何疑问、建议或反馈，欢迎加入微社区与作者本人交流：https://fanbook.mobi/W897PFJd

## 1.前言

URP 使用 Volume 框架进行后期处理效果。这种框架很简单，新建一个 Volume，在上面加挂常用后处理，例如 Bloom、Tonemapping 等，调节相应参数；勾选主相机上的 PostProcessing，这样就能得到后处理功能。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_33_79af231b-d145-40a7-a400-6b15328f45d2_image.png)![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_23_717f4d56-2177-4aef-bce4-0ba87d064459_image.png)

今天带大家一起了解下 URP PostProcessing 中的 Volume 的属性参数介绍，后面也会带大家手把手使用 PostProcessing 中的 Global Volume 与 Local Volume 做一个上图中场景中的后处理效果。

## 2.什么是 Global Volume 与 Local Volume

-----------------------------------

URP 为 Volume 实现了专用的 GameObject，Volume 分为两类，一类是 Global Volume（全局 Volume），另一类是 Local Volume 如 Box Volume, Sphere Volume, Convex Mesh Volume（盒子 Volume，球体 Volume，网格 Volume）。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_24_38f1514a-bde5-49c4-be8e-9556d8d22afe_image.png)

另外 Volume 组件中的 Mode 属性定义了这个 Volume 的类别是 Global Volume 还是 Local Volume。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_27_5628bcbe-22d3-4d76-8b1c-708fa3f3a09c_image.png)

我们可以新建一个 Local Volume，这里我们选择 Box Volume，这样我们的 Inspector 面板会多出两个组件一个 Volume，一个是 Box Collider；当然也可以将已经创建好的 Global Volume 的 Mode 属性改为 Local，只需要手动再添加一个 Collider 即可。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_34_fb407440-5137-47e3-8b48-4a24b68bdca6_image.png)

将 “Mode” 设置为 “Global” 时，Volume 会在场景中的所有位置影响相机。在 “Mode” 设置为 “Local” 的情况下，如果摄影机位于 Collider 的范围内，则 Volume 会影响摄影机。我下面也会结合案例来给大家进行介绍。我们可以将 Volume 组件添加到任何 GameObject。一个场景可以包含多个带有 Volume 组件的 GameObject。我们也可以将多个 Volume 组件添加到一个 GameObject 上。

“Volume”组件引用一个 “Volume Profile”，其中包含“场景” 属性。Volume Profile 包含每个属性的默认值，并且默认情况下将其隐藏。使用 “Volume Overrides”，可以更改或扩展“Volume Profile” 中的默认属性。在运行时，URP 会遍历附加到场景中已激活的 Game Object 的所有 enabled 的 Volume 组件， URP 使用 “Camera position” 和“Volume”组件属性来计算贡献，从而来确定每个 Volume 对最终 Scene 设置的贡献。

## 3.Volume组件的属性

接下来我们来看下 “Volume” 组件属性，“Volume”组件属性包含控制组件如何影响相机以及如何与其他 Volume 交互的属性。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/e1eaa5f0-0844-485c-b97c-ade946156542_image.png)

Mode：是用来计算此 Volume 是否会影响摄像机：Mode 分类两类，一个是 Global，一个是 Local。

•Global：会使 Volume 的作用范围无边无界，并影响场景中的每个相机。

•Local：允许我们为 Volume 指定边界，以便 Volume 仅影响边界内的摄像机。这里我们需要将碰撞器添加到 Volume 的 GameObject 从而设置他的边界。

Blend Distance: 仅当我们从 “Mode” 下拉列表中选择 “Local” 时，此属性才会显示。该属性表示 URP 与 Volume 碰撞器开始进行混合的最远距离；值为 0 表示 URP 在进入 Collider 后立即应用这个 Volume 的替代值。

Weight：Volume 对场景的影响程度。URP 将此乘数应用于它使用 “Camera Position” 和“Blend Distance”计算出的值。

Priority：URP 使用此值来确定在 “Volume” 对场景具有相同影响量时使用的 Volume。 URP 首先使用优先级更高的 Volume。

Profile：Volume 配置文件资产，其中包含存储 URP 用于处理该 Volume 的属性的 Volume 组件。

到这里的话，关于 Volume 组件的属性就已经介绍完成了。现在我们一起来使用 URP PostProcessing 中 Global Volume 与 Local Volume 结合来做个案例。

## 4.如何使用 Global Volume 的 Bloom 效果

--------------------------------

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_41_518ca534-0fff-43c4-b8e7-867b1c70be8b_image.png)

该场景的后期效果用到了 Bloom、Vignette、Channel Mixer、Color Adjustments 首先我们在 Hierarchy 面板中创建 Global Volume, 在 Inspector 中 Volume 中点击新建 Profile，然后点击 Add Override，添加 Bloom，接着我们点击 Bloom 中 All，这样可以一键勾选 Bloom 下的属性。在这里我们调节其中的 Intensity 参数，Intensity：设置 Bloom 滤镜的强度，默认值为 0，这表示 Bloom 效果被禁用。我们设置其值为 4.45，之后我们勾选上 High Quality Filtering 参数，High Quality Filtering：勾选上它能够使用高质量的采样。这样可以减少闪烁并提高整体平滑度。其他的参数我们暂时不做调整。 如图下操作所示。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_45_5411c006-ef40-4539-89b7-15c6e1e0e93a_image.png)

## 5.如何使用 Global Volume 的 Vignette 效果

-----------------------------------

接着我们添加 Vignette，也就是我们常说的晕光，在摄影中，晕光是指图像边缘相对于中心的变暗和 / 或去饱和度。在现实生活中，过多的滤镜、副镜头和不合适的镜头罩通常是造成这种效果的原因。这里我们可以使用 Vignette 绘制焦点到图像的中心。我们来看下具体的设置。

首先我们设置 Vignette 的强度也就是 Intensity 参数，这里我们将其值修改为 0.41; 接着我们调节 Smoothness：使用 slider 设置晕光边缘的平滑度。值的范围在 0.01 和 1 之间。值越高，晕光边界越平滑。默认值是 0.2，这里我们修改它的值为 0.34；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_48_2d54cb25-7721-4bf9-bb08-43e6df78f7d2_image.png)

我们来看下前后添加 Vignette 效果前后的对比。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_59_c3f050e3-7f84-4ed0-adf0-0e6f6b51880a_image.png)![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_9_53_53_ecee605e-1781-4fbe-bfa6-06aacb3ff0cc_image.png)

## 6.如何使用 Global Volume 的 Channel Mixer 效果

----------------------------------------

调节完成晕光效果之后，我们添加 Channel Mixer，Channel Mixer（通道混频器）效果修改每个输入颜色通道对输出通道的总体混合的影响。例如，如果你增加绿色通道受到红色通道的整体混合的影响，最终图像的所有区域的绿色 (包括中性 / 单色) 色调会变成更红的色调。

因为我们具体是想调节出一个傍晚夕阳的效果，所以我们需要修改绿色通道受到红色通道对整个输出通道的影响值为 40，这样的话我们就收到了一个偏红色的色调效果。接着我们降低红色通道受到绿色通道的整体混合影响值为 - 4。最后修改红色通道受到蓝色通道的整体混合影响以及绿色通道受到蓝色通道的整体混合影响，值分别为 - 16 与 30，如图下所示

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/580d685f-5531-4f79-ae37-1d8f21abe669_image.png)![](https://learn-public.cdn.u3d.cn/20210429/learn/images/cfeaeaab-0abb-4d3c-92b9-6438b254aebe_image.png)![](https://learn-public.cdn.u3d.cn/20210429/learn/images/9cf446c8-ee0a-4538-982c-0e8071b2ccf6_image.png)

## 7.如何使用 Global Volume 的 Color Adjustments 效果

--------------------------------------------

这里的话我们需要添加 Color Adjustments，使用这个效果来调整最终渲染图像的整体色调、亮度和对比度。

Contrast：使用滑块扩展或缩小色调值的整体范围。较大的正值将扩展色调范围，较低的负值将缩小色调范围，这里我们修改其值为 1.7；

Hue Shift ：这里的使用滑块来改变所有颜色的色调。这里的值我们增加为 4.5；

Saturation：使用滑块来改变所有颜色的强度，这里的值我们修改为 54；

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/1180c847-d409-4367-9103-d40ac561235f_image.png)

我们来看下调整完 Color Adjustments 后的效果：

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/83f37d89-3d42-4a07-9fe2-df86b7ca8fb6_image.png)

## 8.添加Fog雾效

还没有结束我们需要为场景添加上雾效 Fog; 这里的话我们点击 Window 的 Rendering 下的 Lighting Settings

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/e98e9c68-f84a-43e2-aaf7-aa2f1b515d7d_image.png)

然后勾线其中的 Other Settings 中的 Fog, 然后修改气度为 0.01。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/f2e6a5cd-3b60-4f26-8605-3601066d2efb_image.png)![](https://learn-public.cdn.u3d.cn/20210429/learn/images/5d32d5df-24c0-4841-bbff-83823516a1b8_image.png)

## 9.如何使用Local Volume组件

首先我们在 Hierarchy 面板中创建 Local Volume, 这里我们选择 Box Volume, 我们会在 Inspector 面板发现相比于 Global Volume 多出了一个 Box Collider。这里我们修改 Volume 下的 Blend Distance 为 1，这样的话当我们摄像机靠近这个 Collider 的时候会有一个颜色渐变的效果。另外我们需要设置这里得到 Priority 为 1。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/1ac824dc-0d33-49c8-9c0f-8b06816c5ee2_image.png)

在 Inspector 下 Volume 中点击新建 Profile。接着点击 Add Override，这里我们添加一种后效 Color Adjustments 调节它的 Saturation 饱和度为最低，这样我们就会得到类似于灰度图的一个效果。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/8adb2ad9-efef-4202-880c-c0774727df12_image.png)

我们调节 Collider 的大小，勾选上 Collider 的 Is Trigger, 这样的话当我们的摄像机进入到 Collider 的范围内的话，就会激活我们的 Local Volume 所设置的后处理效果。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/d1c4926e-ced7-4bde-9309-0fd3e254a978_image.png)

好的，我们来看下相机进入 Box Collider 后，Local Volume 设置被启用之后，我们的场景后效的变化。

![](https://learn-public.cdn.u3d.cn/20210429/learn/images/c9916d9c-d281-48aa-a59e-95f34b7821df_image.png)

好的，到这里的话关于如何使用 URP PostProcessing 中的 Global Volume 与 Local Volume，就已经介绍到这里了。

## 10.如何自定义后处理效果？？？

虽然 URP 中已经为我们内置了近 20 种后处理效果，并且 URP 团队也在继续迭代添加更多的效果。

不过如何在 URP 中创建自定义的后处理效果并不容易。幸运的是 URP 团队在 URP14.x 中为开发者内置了 FullScreen Pass Renderer Feature 与 FullScreen Blit 功能， 这样可以使我们轻松的在 URP 中去自定义全屏的后处理效果。

对这部分感兴趣的同学，可以阅读我的另一份 URP 系列教程：如何自定义后处理效果

https://learn.u3d.cn/tutorial/urp-tutorial-how-to-create-custom-post-processing-in-urp
