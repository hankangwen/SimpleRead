> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/CXNQ0F7jD3Ctivwb7tIA8g)

前言

> 若你的工程还没有进行基础配置，请查看我的博文 Unity 之 ShaderGraph 入门使用详解，按照步骤操作完成配置即可，还能顺便学习一下基础操作流程哦

> 本文手把手教你制作自发光和能量护盾效果，入门级教程，还不快动手试试？有经验的童鞋可以直接跳到最后一步，按照图示搭建即可。

一，效果展示
======

老规矩，直接上效果图：（实际效果要比这个好看） ![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTenGTAgpfKCz48MMaOANiczME0xfMbSNMdystFBxHJ6HHrp0VmhxNJPg/640?wx_fmt=gif)

这个动图看起来怪怪的，为展示实际效果，再补发一张，动图中间部分是录屏的原因，不会影响最终制作效果： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTLDicSBfEWHCpomX08xYlqs4O10GXoe3Dc9iatm5CxQlAOphviaxFnDbxQ/640?wx_fmt=png)

没学习 Shader Graph 之前：我靠😱 ！这效果有点牛啊，那个大佬写的？学习了 Shader Graph 之后：我去😒 ！就这？岂不是有手就行？

二，原理介绍
======

两种效果都是通过`Fresnel Effect`菲涅耳节点的菲涅耳效应来实现的。

菲涅耳效应：简单的说，物体在不同角度观察下，表面的反射率是不一样的。菲涅耳效应模拟的就是物体材质反射率随角度改变的效果。这种效果经常被用来实现边缘照明，这在很多艺术风格中都很常见。

Shader Graph 中的`Fresnel Effect`菲涅耳节点： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTlsNe4VgH9NFrLQwXQqHfthU7gSyibtLm2YRFmB1YZnc0WSq1HWIsgsg/640?wx_fmt=png)

三，发光效果
======

3.1 准备工作
--------

在 Project 面板右键 --> Create --> Shader --> PBRGraph（我这里命名为 “OuterGlowPBRGraph”），然后双击打开编辑器面板： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolT6l4JHdDNjicERIa1vibqpFibXoIx13zeKzphfo7FIK0gEfxKeb1kzfZpA/640?wx_fmt=png)

3.2 开始制作
--------

1.  实现自发光
    

创建`Fresnel Effect`菲涅耳节点，因为是自发光效果所以还需要创建一个`Time`节点，然后在创建一个`Multiply`乘法节点将其连接如下： ![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTZ76Eg1oA18VnWKLT5C8krGvI4MeyhwLz9z0eibzEhVGOvPRwdg8X21w/640?wx_fmt=gif)

2.  优化显示
    

由上图可以看出当`Time`节点输出小于 0 时，材质完全显示为黑色。这样的效果可不行，所以我们需要限制一下`Time`节点的输出，所以添加一个`Remap`重新映射节点，这个节点我们可以根据输入值，在输入限定的最大最小值之间的差值，返回在输出的限定范围重新映射值。(比如：输入 In:0，输入 Min:-1,Max:1; 输出 Min:0,Max:10; 则此时返回值是 5)。将此节点插入到`Time`和`Multiply`中间，并将其 Out Min Maxx 修改为 (0.2，1)： ![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolT08wQ8SfOGbZfKxKic2qxlBJchO6wbUYEFicOBK2ch3HxDAPpZwcZRaUg/640?wx_fmt=gif)

3.  添加颜色
    

其实上面两步就实现了一个基本的自发光的效果，因为通常情况下使用都需要修改颜色，所以我们也添加一个`Color`颜色节点，并将其制作为外部可修改的属性。制作步骤：创建`Color`颜色节点并将其设置为公开属性（选中节点右键选择 “Convert To Property”），然后再创建一个`Multiply`乘法节点，节点连接如下： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTE5lzH882uu5AU3XqLHRqYB8rtfoFhbKnGFwb0Q0UIiafmBia1YFVyGNg/640?wx_fmt=png)

最后记得点击左上角的 "Save Asset" 保存一下哦~

3.3 实际使用
--------

1.  创建材质球并使用刚制作的 Shader
    

这里提供一个快捷创建材质球的方法，鼠标选中我们保存的 “OuterGlowPBRGraph” 文件，然后右键创建材质球，这样我们创建出来的材质球，就自动使用这个 Shader 了。 ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTAjM2T6TVgVr2nNibbC3PmIzKvTavQQRJuMmd33qYMlsukU7oalshUxA/640?wx_fmt=png)

2.  在 “Hierarchy” 面板创建 Sphere，并将刚刚创建的材质球赋值给它，得到结果如下：
    

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTk8LLdK9917lpTaYMudMmXTa3BibEtOLQYueUh2YR4oBXgb4ic51I31Qg/640?wx_fmt=png)

3.  为材质球的公开属性赋值，调试效果：
    

![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTNiaAx1HOgEicq68C8FzoN5KjvCECPBLAOFySqKooT1xcDe6RayAjXh6Q/640?wx_fmt=gif)

四，护盾效果
======

2.1 准备工作
--------

在 Project 面板右键 --> Create --> Shader --> UnlitGraph（我这里命名为 “ShieldUnlitGraph”），然后双击打开编辑器面板： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTXVhRzdn7HnsM9EIFJTX8ngY2g8NHTNicnJKkgFH7lEutTNsNH97J4Ew/640?wx_fmt=png)

2.2 开始制作
--------

1.  创建菲涅尔节点和颜色节点
    

创建`Fresnel Effect`菲涅耳节点和`Color`颜色节点，然后在创建一个`Multiply`乘法节点将其连接如下：为了后续方便调整效果直接将`Color`颜色节点声明为公开属性（选中节点右键选择 “Convert To Property”） ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolT8Is0ibtjvLRiayRKNuwlq5kM7iaXsKsfibTTgEYfACRfiaQibgq5IxrFNbgw/640?wx_fmt=png)

2.  添加控制时间节点
    

动态实现：还是通过最常见的时间节点和常量做乘机的方式实现，创建`Time`，`Vector1`，`Multiply`三个节点，并将`Vector1`节点设置为公开，连接如下： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTjmZYUG9iaZ6Oxe2VNPO72yicelngwbVF4AmcHlkzxcyjnvBLbuDibrAdQ/640?wx_fmt=png)

3.  添加贴图和偏移节点
    

创建`Sample Texture 2D`和`Texture 2D Asset`节点用来控制贴图显示（Texture 2D Asset 节点设置为公开），添加`Tilling And Offset`节点用来控制贴图偏移，从而达到移动的效果，节点连接关系如下： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTClibiaNvTw8J4J83aDSmzauGrPxgpknBF21CjqL8Z8UIibG2ogWoicFHXg/640?wx_fmt=png)

4.  让贴图动起来
    

将 2 步骤中的`Multiply`乘法节点的输出连接到 3 步骤`Tilling And Offset`的 Offset 输入上，即可看到移动效果： ![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTYnDkicnvfDrNicibPslOSgQAy2IDTHcNa8znzRDFnDf2hL2K0fYaSM7Lw/640?wx_fmt=gif)

5.  连接剩下节点
    

在添加`Multiply`乘法节点将贴图节点和菲涅尔节点输出连接起来，然后将其输出连接到主节点`Alpha`透明度通道；最后将主节点的 “Surface” 属性设置为 “Transparent” 透明的： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTpNA9oqX5ChKwthYWBsicOmZoicpeQ3pERxmquBw1YGMXicgW4Pq8ibRA9w/640?wx_fmt=png)

记得点击左上角的 "Save Asset" 保存一下哦~

2.3 多种护盾
--------

使用和上面自发光的使用方式一样：

1.  创建材质球并使用刚制作的 Shader；
    
2.  在 “Hierarchy” 面板创建 Sphere，并将刚刚创建的材质球赋值给它；
    
3.  赋值预留的公开属性，查看效果即可。
    

多种形态的护盾，可以通过颜色的变化，贴图的变换来进行区分。

实现不同形状的护盾，也只需要将其应用到不同的模型网格上即可，这里我创建 Capsule 和 Sphere 就得到了两种不同形状的护盾： ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTJicfTqCTNsqeesDaaqa3zliaSZ2HzMVNpicJO3r2BegTBibRt1A0VQm0lQ/640?wx_fmt=png)

五，完整图示
======

5.1 自发光效果
---------

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTFI8VHiaSkdzTdIV5fTAgpffe3CxzTYjqLs7VbLjJwnAebsZfNicPAZnw/640?wx_fmt=png)

5.2 能量护盾效果
----------

能量效果用的的贴图是随便在网上找的就不贴出来了（直接搜索网格随便照一张都可以用） ![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ00icHyN3Gql4bONP8iaR4YibolTLk1JIEjL8by4SLkhK9zl9GBjq7zyIX3K2mumg3kutxwRjqN3MdrX4g/640?wx_fmt=png)