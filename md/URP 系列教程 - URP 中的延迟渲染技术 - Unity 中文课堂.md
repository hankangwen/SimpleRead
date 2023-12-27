> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [learn.u3d.cn](https://learn.u3d.cn/tutorial/urp-tutorials-deferred-shading-techniques?chapterId=63562b27edca72001f21d087#623824ca766ee2002054ee77)

> Unity3d 教程《URP 系列教程 - URP 中的延迟渲染技术》, 延迟渲染技术其本质是通过将几何通道与光照通道分离，能够以比标准多通道前向渲染器更低的成本渲染更多的灯光。

我在 2021 年 Unity 深圳 Openday 的 URP 演讲中，提到过延迟渲染是海量灯光的解决方案，会后就收到许多小伙伴私信希望可以详细讲解下，所以本期教程的内容就是关于 URP 延迟渲染的。

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/f2ad497f-dda6-4d5d-bfd4-029a758d6191_image.png)

延迟着色是三十多年前发明的一种渲染技术。其本质是通过将几何通道与光照通道分离，能够以比标准多通道前向渲染器更低的成本渲染更多的灯光。延迟着色已经广泛用于大量灯光的游戏场景中，尤其是在一些主机游戏，比如深受海内外玩家青睐的 Made With Unity 作品原神中就采用了延迟渲染技术。

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/b0453402-e8e2-419c-b882-e517a864b0a1_image.png)

Universal Render Pipeline 作为 Unity 重点推广的渲染管线，其在功能上正逐步与内置渲染管线靠近，并在未来会的替换掉内置渲染管线。这就需要增添一些内置渲染管线支持但是 URP 还没有支持的功能。延迟渲染功能就是其中比较重要的一个。

另一方面 URP 旨在为游戏开发人员提供兼容 Unity 所支持的所有平台的渲染管线，所以该管线可在从低端移动设备到高端台式 PC 的大量平台上运行。所以将延迟着色添加到 URP 中意味着需要探索各种实现来解决目标平台的差异。所以这项工作繁重而紧迫。

一则喜大普奔的消息是：Unity 在 URP 12.0 以及以上版本中添加了对延迟渲染路径的支持。我们目前可以在 Unity 2021.2 及以上版本中进行体验这个功能。

虽然我们能够很简单的在 URP 中切换前向和延迟渲染路径（关于如何切换会在下文进行介绍）。但是对于刚入门 Unity 的新手来说，如何在前向和延迟渲染路径这两种渲染方法之间进行选择？则需要更好地理解为什么 Unity 会有多个渲染路径，以及了解两种渲染方法背后的动机。那么接下来我就带大家来一起探讨下。

一切都与照明有关，我们总是说灯光很昂贵，主要是因为当物体处于灯光范围内时，必须进行大量计算才能找出像素的有效颜色。在 Unity 中，可以按顶点、按像素或按球谐函数（本篇教程中不做讨论）评估灯光。

![](https://learn-public.cdn.u3d.cn/20220316/learn/images/005c1867-c9d8-4a95-a541-b38463459bf8_image.png)

在逐像素光照中，每个像素的颜色都是单独计算的（如左图）。您可以看到，即使我在此示例中使用低多边形球体，但是光照仍然使它看起来是圆形的效果。如果不是看低多边形的边缘，真的很难发现顶点的位置。

然后是逐顶点光照。它对每个顶点进行一次光照计算。顶点之间的所有其他像素使用常规颜色混合算法评估颜色（无需进一步的光计算。）这是最便宜的照明方法。那么我们如何在 Unity 中打开像素和顶点照明开关，在 Light 组件中 Render Mode（渲染模式）属性选项下（如下图所示）进行选择，其中 Important 选项是强制灯光为像素光，Not Important 是顶点光，Auto 是使最强的光成为像素光。

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/251356d3-89c6-48d3-b3c2-ac93d889fb55_image.png)

从画面对比效果来看，游戏开发者更加青睐逐像素光照而不是逐顶点光照（URP 不支持逐顶点光照）。但是逐像素光照有一个明显的缺点。那就是每盏灯光都会导致光照范围内的每个对象增加额外的渲染通道。可以影响对象的灯光数量是有限的，在最新的 Unity 的版本中我们已经提升了 URP 中的光源限制上限，从每个对象可以受 4 个光源影响增加到了可以受 8 个光源的影响。

然而有一种技术可以让您在场景中使用尽可能多的灯光，同时将性能保持在合理的水平。如果场景对象在光照范围内（投射阴影的对象除外），它不会限制阴影的数量，也不会导致额外的绘制通道。它被称之为延迟渲染路径。

多灯光、高性能的原因主要是大多数模型是在没有光照计算的情况下渲染的，当场景渲染接近完成时，光照会应用于渲染的 2D 图像。在这个阶段进行更改通常称为在屏幕空间中进行操作。知道了这一点，我们可以说延迟渲染中的光照是屏幕空间进行的。为了更好地理解延迟渲染过程，让我们看一下 Frame Debugger。

![](https://learn-public.cdn.u3d.cn/20220328/learn/images/7a98f219-dc3c-4e16-85fd-5a780b2575cb_4dc707502bb258ea17107e692e70d7e.png)

上面这幅图是一个平面图像，那么显卡如何知道给其应用光影信息呢？这里就需要感谢深度缓冲区（depth buffer）！深度缓冲区存储有关每个像素位于相机距离远近的信息。当深度缓冲区被表示为图像时，它可能如下所示：

![](https://learn-public.cdn.u3d.cn/20220328/learn/images/d1f374a6-297f-4b37-af24-7170b7e7266d_725973ada9968fb41cd699af53cacc1.png)

但是仅靠深度信息不足以确定应如何在表面上应用光。我们至少还需要方向！3D 空间中的方向通常由法线表示。正好，除了颜色缓冲区和深度缓冲区之外，我们还有一个带法线的缓冲区！如下图所示：

![](https://learn-public.cdn.u3d.cn/20220328/learn/images/b7455cb0-5490-408e-80c8-1a1ee17ee965_23833491f2ed0738f2a8c427800389f.png)

基于这些信息，我们就可以渲染灯光和阴影。场景中有多少物体并不重要。因为一切都只在最后图像上完成。最后将光照通道的反转版本（1–color）与第一张不透明图像进行混合以获得最终结果（如下图所示）。

![](https://learn-public.cdn.u3d.cn/20220328/learn/images/bec2c6bf-27a3-499d-ab14-71ae624fbfa5_image.png)

4.URP 中使用延迟渲染路径与 Accurate G-buffer normals 属性
---------------------------------------------

首先在你的 URP 工程中在 Project Settings>Graphics 下找到 Scriptable Render Pipeline Settings 中的 URP 资产配置文件 URP Asset,

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/ed692a95-a62c-4971-b2e9-728472896bd8_image.png)

然后找到对应的 URP 渲染器资产 Universal Renderer Data, 在 Renderering > Rendering Path。选择 Rendering Path 为 Deferred，这样我们就开启了延迟渲染路径。

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/35c07881-cf34-453f-81fa-c4420de8ef3d_image.png)

值得注意的是选择 Deferred Rendering Path 后，Unity 会显示 Accurate G-buffer normals 属性。

通过 Accurate G-buffer normals 属性，可以配置 Unity 在将法线存储在几何缓冲区（Gbuffer）中时如何对法线进行编码。那么 Accurate G-buffer normals 属性有什么作用呢，我们来看下：

Accurate G-buffer normals 关闭：关闭这个选项可提高性能，尤其是在移动端 GPU 上，但可能会导致光滑表面上出现色带瑕疵。

Accurate G-buffer normals 开启：Unity 使用八面体编码将法线矢量的值存储在法线纹理的 RGB 通道中。通过这种编码，法线矢量的值更加准确，但编码和解码操作会给 GPU 带来额外的负担。对于面向 desktop 和 consoles 平台的开发人员，启用 “Accurate G-buffer normals” 应该是默认设置。

我们在场景中创建一个球体 Sphere，调节球体的光滑度，我们来观察下打开 Accurate G-buffer normals 属性前后，球体表面效果对比。如下图所示：

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/ceb0a6de-b91b-4c36-91e3-b47da1751c62_image.png)

5.URP 中两种延迟渲染解决方案与内置管线延迟渲染解决方案性能对比
----------------------------------

目前没有一种完美的延迟算法可以完全适配 URP 的多平台性。所以为了适应目标平台的多样化以及不断变化的 GPU 硬件的限制和特殊性，URP 中的延迟渲染算法有两种实现方式。分别是经典的 Stencil-based 延迟渲染算法和目前在台式机 GPU 上比较流行的 Tiled-based 延迟渲染算法（其中基于 Stencil-based 解决方案在所有平台上成熟稳定，基于 Tiled-based 的延迟解决方案目前还在更多平台上进行测试）。

关于这两种算法的具体内容不是我们本教程所讲的重点，我们来看一组实验数据：同场景下基于 URP 的两种延迟解决方案与内置渲染管线下的延迟解决方案在不同平台上的性能对比。

我们创建了一个有着 1 个主 directional light, 64 point lights, 灯光模式为 baked lighting 的测试场景。

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/a555b025-39f3-4ae4-a46e-a27d1f06c8bd_image.png)

在 Nvidia Gfx Geforce 1050 上与 iPhone 8 A11 Bionic 性能对比

![](https://learn-public.cdn.u3d.cn/20220321/learn/images/e9d3630c-958d-4688-8b5f-89c98dd0e414_image.png)

从数据表中我们不难发现首先：URP 中延迟渲染技术性能要优于内置渲染管线，其次，在 URP 中的两种延迟渲染解决方案性能在不同平台上性能各有优势。

6. 延迟渲染管线的限制与下一代多光照渲染技术 Forward+
--------------------------------

说到这里，大家是不是对使用新的延迟渲染路径充满热情，保持冷静！延迟渲染并不是万能的。它还存在一些限制。都有哪些限制呢？我们来看下：

首先，延迟渲染不允许我们渲染半透明对象。这是因为如果场景中存在半透明的东西，则无法记录通过半透明对象可见的对象和当前对象本身的深度和法线。但是在前向渲染路径没有渲染半透明对象的限制。

第二个限制是缺乏抗锯齿支持。原因类似于半透明对象的问题。但您可以使用屏幕空间 AA 算法，只是效果可能不太好看。

还有一个就是 URP 中的相机堆叠 Camera Stack 使用也是有限制的，Unity 使用延迟渲染路径仅渲染 Base Camera。Unity 使用前向渲染路径渲染所有 Overlay Camera。也就是说只允许 Base Camera 相机使用延迟渲染模式。Overlay Camera 叠加相机将恢复到正向渲染模式。

那么有没有一种解决方案可以克服前向渲染与延迟渲染的限制还能够有延迟渲染处理多光照的优点。这就是下一代多光照渲染技术 Forward+，也称为基于 Tile 的前向渲染，是结合了前向渲染和基于 Tile 灯光剔除来减少着色过程中灯光数量的一种渲染技术。这将显著改善 URP 中的前向渲染器对着色时使用的灯光数量有总体限制，增加可用于渲染帧的灯光总数。借助 URP 中 Forward+ 的可用性，我们可以在场景中合并比当前前向渲染中每个对象 8 个灯光的限制更多的灯光。 同时，随着灯光和对象数量的增加，我们的项目中的渲染性能将得到更好的扩展。

目前 URP 团队也在 URP 紧锣密鼓中实现 Forward + 技术，应该很快大家就能体验的到。到时候我们将能够选择 Forward+ 作为选择的渲染器，就像在当前的 Forward 和 Deferred 渲染器之间切换一样。关于 Forward+ 我们会在后续的教程中给大家进行介绍。

最后给大家安利一个自己的微信公众号，会定期给大家分享 URP+XR + 多人联机相关的内容，感兴趣的同学扫码关注哦！

![](https://learn-public.cdn.u3d.cn/20220328/learn/images/95cc3b51-51e0-4724-99fc-782752ded6a2_image.png)
