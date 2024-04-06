> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/__soXTCZeY88N8h8NJXzlg)

**摘要**

近日，西山居亮相游戏开发者大会（GDC）并发表演讲。西山居引擎平台技术总监黄锦寿在会上分享《解限机》产品如何运用 VG 提高渲染效率。这是西山居一次重要的尝试，展现当前中国游戏研发的成果与进展。  

西山居作为国内优秀的头部游戏厂商，凭借多年持续创新的产品研运能力，一直致力于打造能够触动人心的游戏作品，带给玩家们最好的游戏体验。《解限机》作为西山居开启科幻赛道的第一个作品，正显示出了西山居在破局创新，全球化战略上的决心。

随着科技的飞速发展和游戏产业的不断壮大，用户们对于游戏体验的需求也在逐渐提高。玩家越来越专业，越来越 “挑剔”，他们不再满足于简单的消遣和娱乐，而更追求在**精品游戏中实现沉浸式体验和精神满足。**

为了紧跟玩家们的变化，满足玩家们的期望，在现阶段，游戏制作者们纷纷将目光投向了画面制作，致力于提供更精美、更震撼的游戏视觉体验。

✦✦✦

然而，这就让游戏厂商们都共同面临一个难题：随着游戏规模的扩大和场景复杂度，以及模型精度的提高，制作过程需要采用多级的 LOD，这使得美术资源制作的**工作量大幅增加**，需要大量美术劳动力。同时，**游戏开发的周期也相应延长**。  

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EobYPrVZPziaXsJYmcFEmTEFyy5zp9Dl731frI1Ywo97VUILe20fj8lg/640?wx_fmt=jpeg)

西山居作为国内**优秀的头部游戏厂商**凭借多年**持续创新的产品研运能力**亮相本次游戏开发者大会（GDC）并发表演讲。

在大会 Unity 演讲专场上西山居引擎平台技术总监黄锦寿介绍了**《解限机》**产品如何运用 VG（Virtual Geometry）**提高渲染效率**，高效完成游戏中的高精度模型和庞大地图制作，使游戏在视觉呈现上实现了质的飞跃，为玩家提供优质的游戏体验，以解决游戏行业中长期存在的难题，展现了中国游戏研发在硬表面渲染技术上取得的成果与进展，也象征着我们在中国科幻与机甲题材作品上作出的重要尝试。

     ✦✦✦

该游戏于 2023 年年底 TGA（The Game Award）首曝，颁奖期间的首曝播放量仅次于《黑神话：悟空》，超过了《漫威蜘蛛侠 2》在内的一众 3A 游戏，收获了玩家们大量关注，其中**丰富的对战模式、独特个性的机甲、实时弹道演算与丰富的场景建筑破环效果**，都让玩家们对这款游戏充满了期待。

![图片](https://mmbiz.qpic.cn/mmbiz_jpg/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EZAylI25h24NN3hiaBkRb8oWmqL8KsmibO0gDlwicDckibzDXG05Vg34IXQ/640?wx_fmt=jpeg)

**✦✦✦**

**✦美术制作周期长？**

**VG 助力高效高精度渲染** **✦**

在 VG 技术的强大加持下，游戏团队只需要制作高精度模型，美术人员无需再为制作 LOD 资源而投入额外的时间和精力，程序生成的 LOD 模型，其效率和效果均优于手工制作。

同时，在 GDC 上，黄锦寿还介绍了**一套完整的 GPU 高效率渲染方案**。把原本由 CPU 来做的裁剪、LOD 计算、排序等操作交给 GPU 来负责计算，从而降低渲染对 CPU 的能耗，让 CPU 更专注与游戏逻辑计算，这样就充分利用了 GPU 和 CPU 的时间，减少相互等待而造成的算力浪费。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EicKxxeubcQjiazbfG8eJy4XL5tUAWlLK9Z1ibApvDDeQqkBhVJicydkReg/640?wx_fmt=png)

（完整的渲染管线流程都在 GPU 中完成）

        ✦✦✦

在分享中，黄锦寿还提到，游戏的植被系统是为项目专门定制化开发，让植被系统支持 VG，通过 VG 渲染游戏里所有的树和草，并且还支持交互。  

并且，植被系统支持 Imposter, 从近处看是实体模型的树，远处看是简单几个面片的 Imposter, 这些植被也支持可破环、交互，这些碰撞检测都通过 GPU 来计算。在游戏实际应用中，是允许多名玩家同时发射子弹并破坏场景中的植被。由于子弹数量庞大，计算碰撞检测的处理量非常高。

为了解决这个问题，制作团队充分利用了 GPU 的并行计算能力来进行**高效的碰撞检测**，使能够支持大量子弹同时进行精确的碰撞检测。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EPM7kfeBrsxdLcA3LXnuue2qSJcDn1R2UWC0oEibGIkmaN88L4FsSwnw/640?wx_fmt=png)

（基于 VG 可实现的交互植被）

   ✦✦✦      

并且，VG 使单场景的 triangle 数量大幅提高，可以突破以前的数量限制，常规的模型三角面数量不再是渲染效率的瓶。

在 GDC 上，黄锦寿进行场景演示，展示了 VG 的渲染性能。在一个十分复杂的场景中，植被加上建筑总面数可能超过了惊人的 10 亿个三角形面片，甚至有可能达到数十亿之多。

但是由于有 VG 的技术，团队只需制作出高精度的模型，就可以在面数上稍微放松一点，使美术可以有更大的发挥空间。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EhlDdccDKHNdPu8j8fjZO0pUauJnFzGW8SdjhhZiaTh7czGPn3mTLrLA/640?wx_fmt=png)

（VG 使单场景承受面数变高）

       ✦✦✦

此外，黄锦寿还在 GDC 上演示了 VG 在《解限机》的具体运用。传统的 GPU Skinning，需要把动作烘培到贴图上，但是这样操作，动作融合、IK、RIG 动作融合，都没有办法使用。《解限机》对动作的表现力要求比较高，所以使用了 IK Rig 动作融合这些功能。

为了解决此问题，制作团队决定在这些动作系统完成骨骼矩阵运算后，再把数据上传到 GPU 显存中，在 GPU 里面做蒙皮动画计算。最后通过 VG 一次 DrawCall 就可以全部渲染到屏幕上，实现不同种类不同动作的机甲单个 Drawcall **一次完成渲染**。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EJ3f4o3hS5rN6zef7bOvbtmP3v9sCDWZ21bDlbibJOznIqQ7HhrfHdibA/640?wx_fmt=png)

（合批渲染，FPS 大幅提升）

         ✦✦✦       

同时，VG 的运用可以大大减少内存使用，无需再次加载先前的 MESH 数据，在内存中，我们不需要存储任何关于模型的数据。因为 VG 的数据可以直接储存在显存中，这样一来，可以节省不少的内存空间。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69EC9WIhQzgZZVuMfWbicttexf4DWkAfGeftUkDnY52872kYRVkaQ6aG2Q/640?wx_fmt=png)

（原始 Mesh 与 VG Meshi 所占内存对比）

         ✦✦✦       

此项 VG 技术不仅兼容 Unity 的高清晰渲染管线（HDRP）和通用渲染管线（URP），还支持多平台部署，包括 PC、Android、iOS、Xbox 和 PS5 等。这意味着 VG 可以在这些主机平台上顺畅运行，为用户提供一致的高质量体验。

在最后，黄锦寿对比了 VG 场景与普通场景的性能。在这段场景性能对比中，可以看到在采用 VG 之后，游戏性能得到了显著的提升。在换成 VG 后，FPS 分别提升 43% 和 31%。

同时，CPU 的耗时也明显降低，这一提升主要归功于将裁剪、LOD 计算等任务从 CPU 迁移到了 GPU 上，GPU 利用率从 70% 上升到了 97%，使得开发者可以将这部分释放出来的 CPU 计算能力用于游戏逻辑等其他方面，而不再让渲染占据这部分宝贵的 CPU 资源。

总的来说，VG 技术的应用有效地提升了游戏性能，并为开发者提供了更多的资源分配灵活性。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69Ef4MuCcCto00WkOcn53Ds4mWP0WAaicttY7dxXQ1VEmKdj8RqgmbdTfQ/640?wx_fmt=png)

（VG 场景与普通场景性能数据对比）

         ✦✦✦       

VG 是**新引擎的全新特性**，可以媲美目前最先进的商业引擎的虚拟多边形效果。这场关于西山居《解限机》VG 应用的分享引起了在场国外开发者的浓厚兴趣。

他们在提问环节纷纷举手发言，就自己关心的问题向专家请教，他们的踊跃提问不仅促进了**行业内的交流与进步**，也为 VG 技术应用于游戏，以解决行业难题提供了宝贵的启示和动力。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PCFic9M7XLdOCGTECuuCk1tV6RSzAz69ET6I0oANnzLDrnibnqTFicrsB5y5pUym7L90BV5Vw72ITPYgThtqb3Yeg/640?wx_fmt=png)

游戏不仅仅是一种娱乐方式，更是一种情感的寄托。因此，西山居一直致力于打造能够**触动人心的游戏作品**，带给玩家们最好的游戏体验。

而 VG 在《解限机》中的应用，能够将游戏中的世界呈现得更加真实、生动，更具表现力，让玩家仿佛置身于一个引人入胜的全新世界，沉浸其中，**畅享独特非凡的游戏体验**。

✦✦✦

作为国内最早的游戏研发厂商，西山居至今已研发运营超过数十款网络游戏，游戏产品类型从当初的单机游戏发展到现在涉及客户端网游、移动端游戏等多个领域。

纵观全球游戏行业，很多公司往往会选择在一个品类下做横向精细化发展，《解限机》作为西山居开启科幻赛道的第一个作品，显示出了**西山居在破局创新，全球化战略上的决心**，代表着西山居多元化布局的步伐从未停歇。

通过对**游戏 + 文化**创新模式进行持续探索与耕耘、坚持游戏质量与底蕴并重的理念，持续引领玩家一起探索对未来无限的可能，共创更多优秀作品。  

![](https://mmbiz.qpic.cn/mmbiz_gif/PCFic9M7XLdMLl2ZNnslgeH9Q6eK5VibI9mWensUe9d34icV75Q8nV4POpzaDsBX6Ke3HfvNichtnWSPcd7D4K2icCg/640?wx_fmt=gif)