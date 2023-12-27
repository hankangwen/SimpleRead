> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [learn.u3d.cn](https://learn.u3d.cn/tutorial/urp-tutorials-urp-decal-system?chapterId=63562b27edca72001f21d0a2#620cf1abeb46bf001f5666b3)

> Unity3d 教程《URP 系列教程 - URP Decal System 贴花系统的介绍与应用》, 贴花 Decals 是现代游戏中非常常见的功能，很多用户会因为 URP 中缺失贴花系统而放弃使用 URP。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/f6ac0b31-7c16-44e9-81b7-f905892c798d_11111111.png)

URP 系列教程 - URP Decal System 贴花系统的介绍与应用

< 返回：URP 系列教程 - URP Decal System 贴花系统的介绍与应用

> 章节 1. URP 新功能系列教程 - URP Decal System 贴花系统的介绍与应用

![](https://learn-public.cdn.u3d.cn/cdn-origin/assets/styles/i/cnLearn/chapter-bk.e9f9a004fb5fe9daa25ffe5e0ce0e48e.png)![](https://learn-public.cdn.u3d.cn/20220216/learn/images/f6ac0b31-7c16-44e9-81b7-f905892c798d_11111111.png)

教程

URP 系列教程 - URP Decal System 贴花系统的介绍与应用

贴花 Decals，顾名思义，允许在物体表面上添加图案（贴花），包括基于物理的照明。如果你想向物体表面添加任何细节，那么贴画系统是一个非常强大的解决方案。贴花 Decal 在游戏中是一种非常常见的效果，举几个常见的用例是：比如在游戏中墙壁上的涂鸦、地毯上的花纹或者在射击游戏中的血迹、弹孔等等效果。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/abc43f67-f2d3-4bf2-81f7-b6364e59960a_image.png)![](https://learn-public.cdn.u3d.cn/20220216/learn/images/ee618ea0-6931-4ba7-9656-2d00095d31d3_image.png)![](https://learn-public.cdn.u3d.cn/20220216/learn/images/649d546d-c3a8-41c0-879a-5a01bfdb098c_image.png)

正因为贴花 Decals 是现代游戏中非常常见的功能，很多用户会因为 URP 中缺失贴花系统而放弃使用 URP。虽然也有些用户会为管线缺少的功能编写自己的解决方案。但是创造一个高质量的贴花系统并非易事，因为贴花系统最佳解决方案与渲染逻辑是密切相关。所以 URP 拥有其内置的贴花解决方案变得非常重要。Unity 在 URP 12.0 及以上版本中将贴花 Decals 在 Renderer Feature 中完全模块化；并且实现了贴花投影（Decals Projector ）、贴花网格以及贴花着色器（Decal Shader Graph）。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/7062967b-c23d-4dca-afc4-6d980beb16b4_image.png)

由于 URP 涵盖平台广泛，所以 Unity 推出几种不同的解决方案：使用户可以根据平台的不同选择不同质量与性能的贴花解决方案。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/c2d98f0b-b208-449b-9e36-049f8e9c98ea_image.png)

第一种 Screen space decals（屏幕空间贴花）

Screen space decals（屏幕空间贴花）通过在不透明对象之后渲染贴花作为额外的渲染通道来工作，并且根据渲染目标（如 forward/deferred）会有轻微的变化。屏幕空间贴花解决方案虽然在视觉上非常有限，但它不需要深度预通（depth prepass），这使屏幕空间贴花解决方案非常适合基于 tile 的渲染设备（移动设备）。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/9b6e9a71-8a37-4070-81f7-966038603c8b_image.png)

其中 Normal Blend 属性中的选项（Low、Medium 和 High）确定 Unity 在从深度纹理重建法线向量时所采用的深度纹理的样本数。质量越高，重建的法线越准确，性能影响越大。（Low 表示 Unity 在重建法线时采用一个深度样本、Medium 表示 Unity 在重建法线时采用三个深度样本、High 表示 Unity 在重建法线时采用七个深度样本）

其中 Use GBuffer 属性 : 在延迟渲染路径中使用此选项。在延迟渲染路径中，贴花影响基础颜色、自发光颜色和法线。

贴花缓冲区 DBuffer 解决方案与 GBuffer 贴花非常相似，Unity 将贴花渲染到贴花缓冲区 (DBuffer)。然后然后 Unity 在渲染不透明对象期间将 DBuffer 的内容覆盖在不透明对象之上。

如下图所示：首先我们先在 depth prepass 渲染深度图，然后将贴花（Decal）渲染到类似 GBuffer 的 DBuffer 上，然后再渲染 GBuffer 的时候，直接应用同样的位置对 DBuffer 进行采样，融合到 GBuffer 中。之后根据渲染路径的不同：

● 前向 - 在渲染不透明对象期间，每个对象将 _DBufferTexture0-3 应用于其表面数据 Surface Data

● 延迟 - 在渲染 GBuffer 期间，每个对象都将 _DBufferTexture0-3 应用于其表面数据 Surface Data。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/8b7e6a04-1167-4305-af66-61b7f166740f_image.png)

当我们选择 DBuffer 这个解决方案时，会在 Technique 属性下显示 Surface Data 属性。Surface Data 属性允许我们指定贴花的哪些 Surface Data 表面属性与底层网格混合。为了更好地控制性能我们通过 Surface Data 属性来进行控制。

Albedo：贴花影响基础颜色 base color 和自发光颜色 emission color

Albedo Normal：贴花影响基础颜色、自发光颜色和法线。

Albedo Normal MAOS：贴花影响基础颜色、自发光颜色、法线、金属值、平滑度值和环境光遮挡值。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/11c13cf9-fb99-41eb-9285-1ea22fb5fd49_image.png)

DBuffer 贴花技术需要 Depth Normal Prepass，这使得此技术在实现基于 tile 的渲染的 GPU 上效率较低。所以它不适合移动平台，比较适合 PC 和 Console 平台。(高清渲染管线 HDRP 目前在采用这种贴花方案)

3. 案例 - 如何使用 URP Decal System 创建 FPS 游戏中的弹孔效果
---------------------------------------------

那么接下来，我们就是通过一个实战的案例来教大家如何使用 URP Decal System。

首先我们新创建一个 URP 的工程，我将项目命名为 BulletDecals，然后在 Edit>Project settings 中找到 URPAsset。

接着点击 URPAsset_Renderer，在 Inspector 面板中添加 Decal Renderer Feature 到 URPAsset_Renderer 当中。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/9ed87cbb-7a53-49e1-a3ff-4354bca29712_image.png)

添加完成 Decal Renderer Feature 之后，将 Technique 设置为 Automaic；这样的话 Unity 会自动根据所构建的平台和系统的兼容性选择最合适的 Decal 渲染技术；Max Draw Distance 设置为 100，代表 Unity 渲染贴花时距相机得到最大距离为 100，大于这个距离，Unity 将不渲染对应的贴花（如下图举例所示）

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/efc8dfbb-66ed-4511-bb19-e9f71f62c570_image.png)

接着我们创建一个材质，将其命名为 MetalBulletHole；然后的话为其指定 Shader Graphs/Decal 着色器。这里我将着色器也命名为了 MetalBulletHole；

双击 Edit..., 打开 Shader Graphs，为了能够控制贴图的颜色与法线强度，这里我们在内置的 Decal Shader Graph 上增加了两个节点 Multiplay 与 Normal Strength ；并在 Shader Graph 中添加两个属性 Color 和 Normal Strength, 这样我们就可以在编辑器的 Inspector 界面对其进行修改。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/92087501-4b20-4f56-9d76-5dbe18bd5e3f_image.png)

在材质的 Inputs 属性中选择添加对应的 Albedo 贴图和 Normal 贴图。选择 Color 为白色，并将 NormalStrength 的强度调节为 0.547；

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/560972e2-1a42-4a49-a5e0-61caa9752abf_image.png)

创建一个空的 GameObject，将其命名为 MetalBulletHole，将 URP Decal Projector 组件添加到 MetalBulletHole 身上。调整大小与深度值使其显示在金属板面上，将我们之前创建的 MetalBulletHole 材质添加到 Material 属性上。当选择 Decal Projector 时，Unity 会显示其边界和投影方向。Decal Projector 在边界框内的每个 Mesh 上绘制贴花材质。其中白色箭头表示投影方向。箭头的底部是坐标轴点。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/697e7f3e-c61d-4cf5-bf86-4edf44a0e93d_image.png)

最后，为了使我们的效果更加逼真，我们在 MetalBulletHole 加上子弹与金属碰撞产生的火花 Sparks 与烟尘 Dust 的粒子效果。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/bfc0edc3-2294-425d-a219-141025563de8_image.png)

按照上面的方式，我们接着实现与子弹与墙面的贴花效果和子弹与木材的贴花效果；最终的效果如下：

URP 支持材质的 GPU 实例化。如果场景中的贴花使用相同的材​​质，并且材质启用了启用 GPU Instancing 实例化属性，则 URP 会实例化材质并减少对性能的影响。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/79d39156-1643-41b6-9166-cb5d6400975a_image.png)

我们尝试在该项目中开启所有的贴花材质的 GPU Instancing，通过对比统计窗口的合批数和渲染线程的节省的时间都有了明显的提升。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/320f9d27-aeb0-4cb3-aa85-45fbb26be2a2_image.png)![](https://learn-public.cdn.u3d.cn/20220216/learn/images/9e3705bf-d299-4fb3-b4aa-76dc332bd010_image.png)

另外由于 URP Decal System 采用了类似 ECS 的实现方法，所以在使用 URP 贴花系统的时候如果和 jobify 和 burst 一起使用效果会更好。

我们来做一个简单性能测试，我们在场景中创建了 10000 个 Decal, 对比使用 Burst 前后性能的对比：通过 Profiler 中的数据我们也可以明显的看到使用 Burst 后，帧率得到了提升并且更加稳定。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/e58584ad-0a59-48fa-9986-28c3af233094_image.png)![](https://learn-public.cdn.u3d.cn/20220216/learn/images/1c5a1070-a427-4172-a626-2b034fa8e4d9_image.png)

最后 URP Decal System 目前还不能在透明表面上起作用。但是这个功能已经在 HDRP 中已经使用 Cluster decal 解决方案进行实现了。所以我们的计划目标是将 HDRP 贴花解决方案移植到 URP，以致于使它满足 URP 对移动设备友好性。

![](https://learn-public.cdn.u3d.cn/20220216/learn/images/dc1e8020-4da3-4029-906a-cf7d0f955bc9_image.png)![](https://learn-public.cdn.u3d.cn/20221018/learn/images/c2653bd4-91db-4137-a857-ab27153b1372_image.png)
