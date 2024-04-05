> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/IV5UrmOeMNKUeMX529tXQg)

本文作者：U 家工业侠

在从实向虚发展的大浪潮下，为工业的复杂系统，做彻底的、全方位的、系统的数字孪生，使整个工业实现完全的数字化、智能化和可视化，对现代工业有重要的意义。事实上在复杂的数字空间中重建现实世界，要面临众多数据转换、模型优化等难题。

团结引擎是 Unity 中国的引擎研发团队基于 Unity 2022 LTS 版本为中国开发者定制的实时 3D 引擎。**团结引擎同时也为工业软件提****供完备的接口和数据支持**，针对多源异构数据融合难等问题提供了完整而有效的轻量化方案，该方案分为工业模型轻量化和工业场景轻量化两部分。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37JpBq1bllibE1XwOZkv7YZxqicK0ALl6EQY2bL9e5aNl8gXbz8a40gmLQ/640?wx_fmt=png&from=appmsg)

https://unity.cn/tuanjie/tuanjieyinqing

 **工业模型轻量化**

为满足工业模型数据无损导入、精度按需优化等需求，团结引擎提供的数字孪生工具包搭建了一套快速而有效的数据通路。工具包目前支持 **40 多种工业文件格式**的导入及优化，包括建筑行业的 BIM 数据：Revit、Navisworks、Rhino3D、IFC 等，机械制造行业的 CAD 数据：CATIA 、SolidWorks、JT、STEP 等；通用三维数据：USD、FBX、glTF 等。

与之配套的团结引擎数据处理插件能够帮助用户一键导入工业模型，自动完成格式转换、网格减面、破面修复、法线修复等一系列优化工作。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37ZzyzzflbDa4ibQS04KD3cSQgZCrQmI3st8ab9zFqxBjqZ9JQX5KXK0Q/640?wx_fmt=png&from=appmsg)

 **工业场景轻量化**

在完成工业模型的轻量化工作之后，由于工业场景规模大多非常宏大，在实际应用中即便通过模型轻量化、LOD Chain、3DTiles 加载等技术来减轻 CPU、GPU 的实时计算压力，在面对动辄数亿面的高密度场景时，仍然束手无策。为应对此类问题，**团结引擎基于 GPU Driven Pipeline 开发了一套虚拟几何体系统**，用户可以轻松导入高精度模型，无需担心超高面数模型所带来的渲染和显存压力。

借助于虚拟几何体系统，团结引擎对三维场景中的多边形进行了精细的剔除和组织，降低了渲染系统对 CPU 的消耗，同时提升 GPU 的吞吐量，以及运行时的渲染效果和性能；大大满足场景对海量（数以亿计）多边形的渲染需求。接下来，我们将为您简单介绍虚拟几何体的实现原理。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37VQObTMzSvCI5mfM7pXzVQ2hzGAyOib2oxUzrxup6ibbMLibxGFG8HboLQ/640?wx_fmt=png&from=appmsg)https://docs.unity.cn/cn/tuanjiemanual/Manual/VirtualGeometry.html

**虚拟几何体实现原理**

在面对数字孪生场景复杂度、工业模型精度都很高的情况下，传统的 Render Pipeline 存在以下缺陷：

1. CPU 驱动。CPU 需要耗费大量的算力资源来处理 mesh 及状态变化，导致负担过重。

2. 与 GPU 的通信过于频繁。每次状态改变都需要通知 CPU 和 GPU 进行相应操作，导致通信开销过大。

3. CPU 剔除效率低，有大量的 overdraw。

团结引擎通过改进 GPU Driven Render Pipeline，以 GPU 为主要计算资源，通过优化渲染流程，**最大程度地利用 GPU 的并行计算能力**，减少 CPU 和 GPU 的数据交互，以达到更高效、更快速的渲染图像的目的。

其中的虚拟几何体技术通过一套内置处理算法，**将场景中的 mesh 分割成更小的在空间中紧密相关的 cluster**，每个生成的 cluster 会记录相关数据，包括包围盒、材质、纹理等。最终这些生成的 cluster 集合会打包处理成单一的资源文件，引擎直接渲染 mesh，而不需要读取缓冲区里的数据。

由于 mesh 被分割成无数个 cluster，引擎在 cluster 的裁切阶段会**计算出每个 cluster 的显示层级**，这些计算过程都交由 GPU 完成，最大程度地利用了 GPU 的并行计算能力，释放 CPU 算力，以更精细的方式控制场景中 mesh 的 LOD。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37WyRziamhLCRBem0kbMu7mcJsznULBqqHPu4JoM7Ug4l5TQc20lB1rMw/640?wx_fmt=png&from=appmsg)

引擎根据计算结果**以 Streaming 方式动态加载视野内需要渲染的 Cluster**，大大降低了显存占用，减少不必要的细节渲染。当视野内的 Cluster 在屏幕上的大小小于阈值或者远离相机时，可以剔除而不用担心 LOD 过渡带来的效果损失问题。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37wbW7yUA4phBb7EbDQL2phW8TibVcb7pOQPU4hgnGabiccIEZsr7eB2IQ/640?wx_fmt=png&from=appmsg)

Cluster 根据距离视角远近自动 LOD

虚拟几何体的优势：

**1. GPU 驱动。**GPU 决定当前帧应该渲染哪些物体，以及在 GPU 上进行状态改变等操作。减轻了 CPU 的负担，提高了 GPU 的渲染效率。

**2. 流式加载。**由于是虚拟的，所有的几何体数据都可以流式加载。

**3. 更精细的剔除。**GPU 能够使用更加复杂的剔除算法用来剔除不可见的物体和面，减少 overdraw 现象。

**4. 相比于传统的 LOD，其有自适应 LOD 算法并有自然的过度。**

下图为 10 亿三角形级别的 HDRP 场景下，开启 / 关闭虚拟几何体的帧率对比。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY373r1gWDIVDo6eAdNSFNUmP4ibD5LiaES9cNbISic8XVsP1m7mmraHb7fkw/640?wx_fmt=png&from=appmsg)

左：虚拟几何体关闭 - 5 FPS；右：虚拟几何体开启 - 60 FPS

**如何使用虚拟几何体**

  **下载团结 Hub，安装团结引擎**

团结引擎自带虚拟几何体功能。

 **创建或打开 HDRP 项目**

通过选择 Edit->Project Settings…->Graphics 打开 Graphics Settings，找到并开启 Virtual Geometry (Experimental) 选项。在编辑器重启后，虚拟几何体功能被开启。

*   虚拟几何体功能开启后，项目中的所有模型都会被重新导入，以构建虚拟几何体所需的数据，这可能会增加首次导入项目的时间。
    

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37mSJ1GKHyEZHiaibcjFLWPktN1pQiakNleDd6tjZdO2CIupdFv1SFJzic1A/640?wx_fmt=png&from=appmsg)

*   开启虚拟几何体功能后，导入新模型会默认构建虚拟几何体数据，除非此模型使用半透明或 alpha clip 材质。您可以通过 model impoter 来设置您的虚拟几何体的配置。  
    

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37798kpVia3AMCHMEXITtOVlic6Yn0tvSaITDdUUccfMx1ib7mQpAv5lWaQ/640?wx_fmt=png&from=appmsg)

*   虚拟几何体数据不支持在 CPU 端修改。当 Virtual Geometry 打开后，Read/Write 选项会失效；反之，当 Read/Write 选项选中后，Virtual Geometry 会失效。因此如果您想在运行时脚本中修改模型的顶点信息的话，请确保打开 Read/Write， 并关闭 Virtual Geometry 选项。同时，虚拟几何体也不支持勾选 Keep Quads。
    
*   注意：在运行时，手动创建的模型（非复制）是不支持虚拟几何体的。
    

 **在 MeshRenderer 上启用虚拟几何体功能**

MeshRenderer 中有独立的开关让您选择是否在当前物体上开启虚拟几何体，以及虚拟几何体阴影。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37icKBA1td1hDDF4zffmoKZKZPLic4OhXRCb5jstc5fk7F8ZezgC0Ap5UA/640?wx_fmt=png&from=appmsg)

虚拟几何体阴影可以使用虚拟几何体技术来实时的渲染您的级联阴影。

*   虚拟几何体启用后，MeshRenderer 将会以集群的方式渲染，而不再以 Instance 为单位渲染。
    

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY379GXsojpXS8Hm0z4WIX8UmbEdzmlXoGLmmbYZlawq9iaDuKq5jp2lriag/640?wx_fmt=png&from=appmsg)

*   虚拟几何体关闭状态下，MeshRendereer 会以传统方式进行渲染。  
    
*   某些情况下，其所使用的材质不支持虚拟几何体，比如 alpha clip 材质，则您有必要关闭 Virtual Geometry 选项以正确的渲染对象。
    

 **支持平台**

*   Windows (DX11, DX12, Vulkan)
    
*   Linux (Vulkan)
    

 **性能以及内容相关的问题**

虚拟几何体在一定程度上解决了屏幕像素和场景中多边形数目不匹配的问题，通过细节剔除等技术可以根据屏幕分辨率自动适配，因此无论场景中三维模型有多精细，实际试图绘制在屏幕上的三角形数量会始终与像素的数量成正比。

但需要注意的是，以下几种情况虚拟几何体暂时不支持：

*   HDRP 使用前向渲染管线  
    
*   物体使用了半透明材质
    
*   物体使用了 alpha clip 材质
    
*   使用了 LOD Group 组件
    

**下一步开发计划，你来决定**

为更好地为开发者提供虚拟几何体特性，我们列举出后续计划的开发内容，欢迎大家投票参与，以助于我们更准确地评估未来的开发重点。

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/NYLZoOxGjYFnp8oTia0BpC3HvVrrjicY37oHdxceI0pEBhKEyyicIpx8aWWrdCT0QEbunLib56BBbj0AIgRpibQomjQ/640?wx_fmt=jpeg)

扫描上方二维码进行投票

团结引擎作为专为中国开发者定制的实时 3D 引擎，针对各行业定制了不同的技术和功能，例如在数字孪生领域，除了刚刚介绍的 pixyz 和虚拟几何体，还针对工业用户常用的 Arm linux 做了适配，并且把这些功能和产品集成到了**团结引擎 Industry 版**中。后续我们也将带领大家继续剖析团结引擎 Industry 中的其他功能。

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGia3ibXvfribSG3BEumwiakOoXOmvbw1a7icDGWF8wMoicDZqMko9kichBLEYug/640?wx_fmt=png)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYE0pXoibgZdG402gsj2GEkeK632mNhkOAhQrAF5ulpjiaIklswNGlfBjP9YSwvFcr4QRKcY3JnDh2jA/640?wx_fmt=png&from=appmsg)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247556292&idx=1&sn=fac1e534f3291c81d76f0d4f90047269&chksm=c1861f40f6f19656a06b85001bbc68b204afde61fa33abed9edc38af66b2939c808701d3f882&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYEqXHeRtyzJvT56ibf00TSHFlABcj2BeP47P6Zv8RJIMiblzibV7AYmobkIRgnOj0sXtI2Ghtfm522Mg/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247554960&idx=1&sn=baaa3c68685a06d7fda1981b3a6d1cfc&chksm=c1861414f6f19d029a720f793f5e7743efa6bcc19ed86b9d9db8ec89cd039a427d5f386c7517&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFlmXNbMs1FdxC7KPpvg2EIq8dyKvEgibJtQpwToGrSB8bzw7YYjXl7icibt3S7A2qZU7NO0KJO9aEpQ/640?wx_fmt=png&from=appmsg)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247555484&idx=2&sn=b7c1242601dcf66ad5c5e4c0eaa17a6b&chksm=c1861a18f6f1930e1c5bd3a78b90ba094e3c0e7d271d2a77addb248a3ffac404ee9f3946cece&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFhicnUTmPvVTnuSk3RX0WO8h4q4GuKCTMLTp9EzCCsrQ6s6ibLdyQaAXIkootlEiaLe6jlWCBjvoLfQ/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247539782&idx=1&sn=8fb062017695d7063dcb50ad3dfb9134&chksm=c1865fc2f6f1d6d4e99fc3529b8d9097400a4489ad38c0c4d0ddcf3c62b1ba9186fd1d455d12&scene=21#wechat_redirect)

**长按关注**

**Unity 官方微信**

第一时间了解 Unity 引擎动向，学习进阶开发技能

![](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsun6CMe09NXZkcm0GiaWH5X4CPfZTL3Qr1sx7pQSy6M4wpTibnlGgsZCauTnDicQiaSAsB4RhXza2bw/640?wx_fmt=gif)

 每一个 “在看”，都是我们前进的动力 

![图片](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsOlrhMAcw4vJeMyK5jRwBckKrT4zFgAYY4q4uQvK3PH1NDVxrHF45kMQicj1f33oqSBxfulBounQ/640?wx_fmt=gif)