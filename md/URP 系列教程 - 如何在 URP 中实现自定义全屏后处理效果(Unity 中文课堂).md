> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [learn.u3d.cn](https://learn.u3d.cn/tutorial/urp-tutorial-how-to-create-custom-post-processing-in-urp?chapterId=64c9ba806e020b001e56cbb3#64c9ba806e020b001e56cbb2)

> Unity3d 教程《URP 系列教程 - 如何在 URP 中实现自定义全屏后处理效果》, 后处理（Post-processing) 是现代游戏中必不可少的技术之一，是提升最终画面呈现品质的重要渲染技术。

## 摘要

后处理（Post-processing)是现代游戏中必不可少的技术之一，是提升最终画面呈现品质的重要渲染技术。后处理渲染技术的好坏，往往决定了游戏画面是否能够达到令人惊艳的效果。

虽然URP中已经为我们内置了近20种后处理效果，并且URP团队也在继续迭代添加更多的效果。

不过如何在URP中创建自定义的后处理效果并不容易。幸运的是URP团队在URP14.x中为开发者内置了**FullScreen Pass Renderer Feature 与 FullScreen Blit 功能，**  这样可以使我们轻松的在URP中去自定义全屏的后处理效果。

本篇教程就是教大家从易到难使用URP中的Full Screen Pass Renderer Feature去实现两种常用的**全屏后处理效果：**

**1.去饱和度效果**

**2.镜头雨滴效果**

# 章节1 URP中的内置后处理效果

## 摘要

后处理（Post-processing)是指在正常渲染管线结束后，对最终渲染画面进行的后期加工的技术，如滤镜等。以此来模拟物理摄像机和电影特效。

1.URP 中有那些内置的后处理效果
------------------

目前 URP 中有那些内置的后处理效果？在最新的 URP 16.0 中内置 19 种后处理效果， Bloom、Channel Mixer、Chromatic Aberration、Color Adjustments、Color Curves、Depth of Field、Film Grain、Lens Distortion、Lift Gamma Gain、Motion Blur、Panini Projection、Shadows Midtones Highlights、Split Toning、Tonemapping、Vignette、White Balance、Lens Flare；我们可以使用这些后处理效果，显著提高游戏的画面质量![](https://learn-public.cdn.u3d.cn/20230802/learn/images/9e85b9b4-4385-4173-84e4-517a1c393b89_image.png)使用后处理前![](https://learn-public.cdn.u3d.cn/20230802/learn/images/9c022aaa-b0ef-4b55-a391-1be92ff45757_image.png)使用后处理后![](https://learn-public.cdn.u3d.cn/20230802/learn/images/af8cbe11-f269-4892-b573-f16bfb481f9f_image.png)使用后处理前![](https://learn-public.cdn.u3d.cn/20230802/learn/images/b0272737-3b49-4b16-82ae-93d3b1ba07a4_image.png)使用后处理后

## 2.如何在 URP 中使用后处理

-----------------

关于如何使用 URP 中的后处理技术，我已经在之前的 URP 系列教程中，给大家详细讲过，对这部分的内容感兴趣或者还不懂的同学，建议大家可以点击此链接进行查看：https://learn.u3d.cn/tutorial/urp-post-process-volume。![](https://learn-public.cdn.u3d.cn/20230802/learn/images/7200581f-7fa5-41ee-a98c-595e4c6e7961_image.png)

# 章节2 URP自定义后处理效果

## 摘要

虽然URP中已经为我们内置了近20种后处理效果，并且URP团队也在继续迭代添加更多的效果。我们可以调整这些预构建的后处理效果来为你自己的游戏画面创建特定的视觉风格。

但是如何在URP中创建一个自定义的后处理效果并不容易。不过URP团队在Renderer中内置了Full Screen Pass Renderer Feature与 Full Screen Blit 功能，  这样可以使我们更加轻松的在URP中去自定义一些全屏的后处理效果。

所以接下来我会带大家从易到难来使用URP中的Full Screen Pass Renderer Feature去实现两种常用后处理效果：

 Desaturation（画面去饱和效果） 和全屏雨水效果。

## 1. 自定义后处理效果：去饱和效果

Desaturation（去饱和度效果） ：是我们在游戏中经常使用的一种后处理效果；我们多用其来指示角色耗尽生命值时的一种效果 。

![img](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_54_0_cb8023e3-d0b1-4b0d-9207-6cb969b8a4bf_image.png)

去饱和效果前

![img](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_53_59_2030c4ad-c290-437c-aef6-a6357e04b2cd_image.png)

去饱和效果后

## 2. 自定义后处理效果：镜头上的雨水效果

镜头上的雨水后处理效果也是日常以及游戏中常用的画面效果

![img](https://learn-public.cdn.u3d.cn/20230802/learn/images/cad3de92-13c3-4ef6-b24d-62c872233ec2_pexels_kaique_rocha_125510.jpg)

# 章节3 如何在URP中实现去饱和效果

## 摘要

前面我们简单的介绍了这种后处理效果，接下来我们来看下如何在URP中进行实现

## 1.新建 URP 工程

------------

1. 使用的 Unity 版本是 2022.3.x 创建新的 URP 工程（URP 安装包为 URP14.x），这里我选择的是 3D Sample Scene（URP）模版,2. 将工程重新重名（这里我命名为 My Custom PP）；

   ![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_57_43_05c72de4-f163-43bb-bdd2-3668da1e43b0_image.png)

2. 在 Project Settings > Graphics > Scriptable Render Pipeline Settings 下确认正确引用 URP Asset；![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_57_44_542762af-a493-4bcf-b7dc-eb0e729b5bcf_image.png)输入图像描述（可选）  



## 2.创建全屏的 Shader Graph

---------------------

1. 在您的项目中创建一个新的 Shader Graph。在 Project 窗口中右键单击并选择 Create > Shader Graph > URP > Fullscreen Shader Graph；![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_57_44_2455e953-6160-410a-8ce2-0855d1d2c3b7_image.png)输入图像描述（可选）  

2. 添加 URP 样本缓冲区节点（URP Sample Buffer）。在 “Shader Graph” 窗口中右键单击，然后选择 Create Node “创建节点”。然后找到并选择 URP Sample Buffer。

   ![](https://learn-public.cdn.u3d.cn/20230802/learn/images/9a5fde28-0b0e-4cc5-a731-c89ac64e6d41_image.png)  

3. 在 URP Sample Buffer 节点的 Source Buffer 下拉菜单中，选择 BlitSource。

   ![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_57_43_a3c2bb9d-68ea-4f9f-9858-e7e25d4ed6d5_image.png)  

4. 添加 Vector 3 节点；

5. 为 Vector 3 节点分配以下值：X = 0.2126、Y = 0.7152、Z = 0.0722；

6. 添加点积 Dot Product 节点，并按如下方式连结，并保存；![](https://learn-public.cdn.u3d.cn/20230802/learn/images/3d2be78e-a65b-4665-93ef-3571c29f3458_image.png)  

## 3.创建新材质并引用全屏 Shader Graph

--------------------------

1. 在项目窗口中右键单击并选择 Create > Material，新建材质；
1. 在检查器中打开材质并选择 Shader > Shader Graphs，然后选择前面步骤中创建的 Shader Graph，将新建的 Shader Graph 着色器应用到材质； ![](https://learn-public.cdn.u3d.cn/20230802/learn/images/ca21b962-058c-4d82-8b53-4d98e9e3e1b1_image.png) 



## 4.为 URP Renderer 中添加 Full Screen Pass Renderer Feature

-------------------------------------------------------

1. 在 Project 窗口中，选择 URP Renderer 渲染器。2. 在检查器中，单击 Add Renderer Feature （添加渲染器功能）并选择 Full Screen Pass Renderer Feature （全屏通道渲染器功能）。
1. ![](https://learn-public.cdn.u3d.cn/20230802/learn/images/5b2319cf-9d93-4fa7-b087-21edfd6117df_image.png)  



## 5.设置 Full Screen Pass Renderer Feature

---------------------------------------

1. 将后期处理材质设置为您使用 Fullscreen Shader Graph 创建的材质。

2. 将 Injection Point (注入点) 设置为 After Rendering Post Processing (渲染后处理后)。3. 将 Requirements 设置为 Color。

  ![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_10_57_46_db3af0da-4f6d-4ce4-815c-041895096711_image.png)

  3. 设置完成后，我们就会在 Game 视图中看到这样的效果：![](https://learn-public.cdn.u3d.cn/20230802/learn/images/e57e9307-72ee-478a-9797-be6d5f863663_image.png)

# 章节 4. 如何在 URP 中实现镜头上的雨滴效果

## 摘要

上一章节中，我们小试牛刀，教大家如何在URP中实现画面去饱和的后处理效果，

那么本章我们我们将带大家学习一个稍微有难度的全屏后处理效果；镜头上的雨水效果

## 1.观察雨天玻璃上的水滴效果

在开始之前我们先来观察下雨天现实中玻璃窗户上的雨水效果；

![](https://learn-public.cdn.u3d.cn/20230802/learn/images/ec45cc8b-da92-40c2-ae58-8f060703446e_image.png)

为了方便大家理解，我将玻璃窗户上的雨水分为三个部分：

1. 较大的雨滴（雨水直接打到玻璃上留下的较大的雨滴）, 或者说动态的雨滴；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_24_2fa547c9-b0a3-45a2-b683-0e77a16ff8d0_image.png)

## 2.创建 Full Screen Rainy Window Shader Graph

-------------------------------------------

1. 在上章节创建的 URP 工程下，在 Project>Assets 下创建新的文件夹命名为 ShaderGraphs;

2. 在新建的文件夹中创建一个全屏的 Shader Graph ，右键单击并选择 Create > Shader Graph > URP > Fullscreen Shader Graph，并命名为 Full Screen Rainy Window;

![](https://learn-public.cdn.u3d.cn/20230802/learn/images/3829dfc0-207a-4ce5-b163-dbe4e5639def_image.png)

3. 双击 Full Screen Rainy Window 文件进行编辑；

   
## 3.创建新材质并引用 Full Screen Rainy Window

1. 在项目窗口中右键单击并选择 Create > Material，新建材质并命名为 Full Screen Rainy Window Mat；

2. 在检查器中打开材质并选择 Shader > Shader Graphs，然后选择前面步骤中创建的 Full Screen Rainy Window Shader Graph，将该 Shader Graph 着色器应用到材质；

![](https://learn-public.cdn.u3d.cn/20230802/learn/images/c666bb07-fc9e-4fcb-af03-268fcdd2ed0e_image.png)

## 4.为 URP Renderer 中添加并设置 Full Screen Pass Renderer Feature

----------------------------------------------------------

1. 在 Project 窗口中，选择 URP Renderer 渲染器。

2. 在检查器中，单击 Add Renderer Feature （添加渲染器功能）并选择 Full Screen Pass Renderer Feature （全屏通道渲染器功能）。

3. 将其重命名为 FullScreen Rainy Window Renderer Feature

4. 将后期处理材质设置为 Full Screen Rainy Window Mat 。

5. 将 Injection Point (注入点) 设置为 After Rendering Post Processing (渲染后处理后)。

6. 将 Requirements 设置为 Color。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_22_6392003a-4599-4666-bdca-1bbb19541f07_image.png)

## 5.下载雨滴贴图并导入ShaderGraph

1. 首先在 Project>Assets 目录下创建 Textures 文件夹

2. 在本教程附属素材处下载 RainDrops_01 贴图，并导入到 Unity 中来；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_22_002d9e11-f2ae-494c-beef-45befed43407_image.png)

3. 将 RainDrops 贴图直接拖拽到 Shader Graph 编辑界面

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_24_1f63fceb-443e-4be0-84ca-4d29ff216467_image.png)

那么接下来我们就对雨滴贴图进行采样

## 6.设置雨滴贴图采样坐标

1. 首先我们要获取屏幕位置，所以我们创建 Screen Position 节点，

2. 因为我们只需要屏幕坐标的 X,Y 值，所以我们需要创建 Swizzle 节点并与 Screen Position 节点进行连结，并在 Swizzle 节点 Mask 属性处输入 xy, 从而只输出屏幕坐标的 X,Y 值；

3. 接着我们将 Swizzle 节点的 out 端口与 Sample Texture 2D 节点的 UV 输入端口进行连结，使其采样我们的雨滴贴图；

4. 将采样后的结构输出到我们的 Fragment 节点的 Base Color 处；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_23_7687247c-a18e-4233-ba18-0d1baea464ff_image.png)

5. 在 Shader Graph 的左上角点击 Save Asset，返回到 Game 视图我们发现：

![](https://learn-public.cdn.u3d.cn/20230802/learn/images/e0f8a825-2a0d-4764-acaa-8d3fb4a70565_image.png)![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_25_d5d0033f-4b67-4344-92e4-764d2995cc8e_image.png)

如上图所示：我们已经将贴图采样结果应用在了屏幕上，

不过我们发现一个问题是我们雨滴被拉伸了，这是为什么呢？

因为 Game 窗口的视口坐标是竖直方向与水平方向都是从 0 到 1，但很明显我们的 Game 窗口并不是正方形（长宽比为 16:9），所以如果想对纹理进行正确的采样，我们需要对屏幕的位置数据进行调整，使其变为正方形。

1. 所以接下来我们引入 Screen 节点，我们可以从 Screen 这个节点中获取屏幕的宽度和高度；

2. 接下里我们需要创建一个除法 Divide 节点，并将 Screen 节点的 Width 端口、Height 端口分别与 Divide 节点的 A、B 两个节点进行连结，这样我们将得到一个 16:9 的长宽比值；

3. 我们将其应用到水平 X 轴，竖直方向保持不变（也就意味着我们只需要将除后的值乘以 X，而使 1 乘以 Y），所以我们需要引入 Combine 节点，将 Divide 节点的输出与 Combine 节点的 R 端口连结，并将 Combine 节点的输入端口 G 与值 1 进行连结；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_26_8e2250a8-0e2c-4f10-a597-42280088eae5_image.png)

4. 将 Combine 输出后的结果与之前 Swizzle 节点的输出相乘，并将最终结果与贴图采样节点相连：

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_28_7d3d7ddc-eb8b-42b3-b805-d5a55b990405_image.png)

5. 在 Shader Graph 的左上角点击 Save Asset，返回到 Game 视图我们发现：雨滴采样正常，没有拉伸。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_32_6c4895c2-72c5-4af6-8b1e-a8c0b8de2efc_image.png)![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_32_2e5d01c5-9f4b-4558-801b-e21c110b1088_image.png)

## 7.法线向量范围重映射

1.接下来我们需要分离出采样后纹理的不同组成部分，我们创建Combine节点获取到R，G，Alpha值；

![img](https://learn-public.cdn.u3d.cn/20230802/learn/images/9ed38ef5-e6bd-422e-91a6-0f94dc4233de_image.png)

2.为了获得一个正确的法线信息，我们需要将纹理在【0,1】之间的RGB值映射到法线向量的【-1,1】之间，故我们需要将normal *2.0-1.0这样的操作，创建相关节点如下所示；

![img](https://learn-public.cdn.u3d.cn/20230802/learn/images/dea32279-a374-4524-a3b4-bda61ec0216f_image.png)

3.最后我们使用Swizzle节点输出X,Y；

![img](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_24_50_76c1cfc5-ebaa-4f85-90c1-cc11f1e5b3cd_image.png)

## 8.采样场景的Color

1. 紧接上一步骤：我们将重新映射的法线向量信息（x,y）添加到屏幕位置坐标；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_36_e714c2d2-3b36-47b2-afb1-4c9e3b4843b5_image.png)

2. 然后我们使用 Add 的输出结果来采样我们场景的颜色，这里我们创建 URP Sample Buffer 节点，并将 Source Buffer 修改为 Blit Source 获取我们场景的颜色；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_38_6de43dc0-cfca-4cda-8aff-734967367194_image.png)

3. 最后将 URP Sample Buffer 节点的输出与 Fragment 节点的 Base Color 端口链接，

![](https://learn-public.cdn.u3d.cn/20230803/learn/images/da6c8c0b-91fe-4692-9c6c-2c9b30cda600_image.png)

4. 在 Shader Graph 的左上角点击 Save Asset，返回到 Game 视图我们发现： 我们得到一个还不错的水滴效果；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_41_8d143b95-628e-4a93-8029-aa96578b9698_image.png)

5. 不过目前的水滴的扭曲程度大有点太明显，我们需要减弱它的扭曲效果，所以我们在上一节中 Swizzle 节点后乘以一个小于 1 的数（这里我设置为 0.03）；

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_41_182f9dd8-2e25-4d37-8896-5972b20a2a0e_image.png)

6. 在 Shader Graph 的左上角点击 Save Asset，返回到 Game 视图我们发现：现在我们就有了一个相对比较正常的雨滴效果。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_44_93da1850-14af-40b4-a997-5b3407101472_image.png)

## 9.未完待续

那么接下来我会在下一部教程中带大家制作：

1.如何为大水滴动起来，

2.为镜头添加小水滴、

3.为镜头添加滑落的水滴

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2023/10/9_11_19_46_7abc69ed-cfdb-4849-8afa-836a0e82d015_image.png)
