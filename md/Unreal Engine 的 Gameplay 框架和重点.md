> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/44FwITlLCCYALQS78vmePA)

点击上方 “放牛的星星” 关注后了解更多精彩内容

上一篇我们聊的是 Unreal 引擎的启动和初始化过程。

[Unreal 引擎 ，启动！](http://mp.weixin.qq.com/s?__biz=MzA4NTg1Mzk0OQ==&mid=2649902588&idx=1&sn=4cb36041a83b855d72793b0baa5d9b9d&chksm=87d77e6eb0a0f778dbd446cc7434aa791606f8e7f9828700e14d0750f3ec8656fd889d8132e1&scene=21#wechat_redirect)  

也大概讲了 Unreal 引擎和编辑器 (EditorEngine)、运行时(GameEngine) 的关系。接下来我们就会走到 GameEngine 更深一点的层次，了解一下它的运行时框架, 以及开发者接触最多的 Gameplay 框架。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh495ObZWOibAiahUgauna48hLchLWWpnGs3gbLkCLqbMbsNQib6ic5MiboWw/640?wx_fmt=png)

****1 理解 Gameplay****

Gameplay 是最近几年才广为流传的一个名词（不是说以前没有），我没有做过具体考证，但应该是从 Unreal 广泛流传开来的，伴生的一个概念还有 3C。

最近的面试中（Unity 和 Unreal 的都有），我也会适当的问一些候选人类似的问题，比如你所理解的 Gameplay 和 3C 是什么？大多数学习过 Unreal 会说 3C 就是指 Character，Control 和 Camera，不过也就仅此而已；而对 Gameplay 的表述则会混乱一些，大致会把 Unreal 的流程讲一遍。而只有 Untiy 经验的有很大一部分是表述不出来这些概念的。这也会让我进行一些思考，为什么不同的引擎开发人员对游戏开发概念会出现这么大的偏差呢？

在过去很长一段时间里，Unity 占据了手游甚至是游戏开发的 “大半壁江山”。最开始只有一个统一的称谓叫“客户端”，之后逐渐从客户端开发上分化出了 TA（技术美术）和引擎，甚至于现在比较热门的 TD（技术策划）。我们会说 Unity 开发，Unity 客户端，Unity 前端，却很少听到 Unity 的 Gameplay。归其原因还是因为 Unity 的闭源，以及源码付费让绝大多数的游戏公司在做项目的时候，不会把引擎开发和“客户端” 开发进行概念上的并列。默认招聘和谈论的就是使用 Unity 引擎进行项目的内容开发，所以 Unity 的开发者之间除非特指引擎组和引擎源码，不然大家都是 “客户端” 开发。

随着 Unreal 引擎的逐渐普及，Gameplay 的概念也得到了广泛的传播。因为开源的关系，Unreal 在招聘的时候会刻意区分是引擎岗位还是 “客户端开发” 岗位，而这个 “客户端开发” 在广义上就是指 Unreal 的 Gameplay。那么为什么我要区分 “广义” 和“狭义”呢？因为划分的标准不一样。

广义的 Gameplay。以引擎源码为界限，需要改动引擎源码才能实现的会被划归为引擎开发。而基于引擎开发游戏或者玩法的称之为 Gameplay。所以若以广义的划分标准来看，绝大多数的 Unity 开发都是 “Gameplay” 开发。而绝大大多数的 Unreal 开发，多多少少都会改动到引擎，是不是就是 “引擎开发” 了呢？

狭义上的 Gameplay。以 Unreal 4.27 提供的 Gameplay 框架作为参考，它其实包含的就是游戏的规则和状态，3C 和用户界面，也就是表达一个游戏玩法的最基础元素（但实际上一个复杂的游戏考虑的远远不止这么些）。那么问题来了，比如我们所说的战斗，剧情，AI，载具这些就不属于游戏玩法了吗？就不是 Gameplay 了吗？

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhTzcicYicDuk23icFLtxU3QmFsvm7bkBambcZRaMzdmle7vCx3ZZ7uJUrg/640?wx_fmt=png)

注：UE5 的 Gameplay 扩展了 Actors，移动组件，游戏功能和模块化，定时器等内容，但对于理解 Unreal 的 Gameplay 上没有什么大的概念上的变化。Unreal 5.1 的 Gameplay 框架 。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh0jbIvLon6Qd2b2MGwPv3N7icoBZp8OsM2ZUWggKWBoyPBTsicTSXSOqg/640?wx_fmt=png)

综上所述，无论是从广义上还是狭义上的 Gameplay 划分都是不太科学合理的。

对于 Unity 项目而言，它的 AssetBundle 机制很不好用，某同学研发了一套自己的资源组织规则；又或者某位 TA 同学基于 URP，重写了一套延迟渲染的流程，这些在我看来都属于引擎开发的范畴。

对于 Unreal 项目而言，某位同学没有动到引擎代码，从业务层设计了一套更高效的动画存储和加载框架，那么它是属于引擎开发的，而某位同学为了更方便的进行业务开发，从引擎层开放了一个面板参数进行数据配置，虽然改动了引擎源码但也不算是引擎开发。

所以我认为，如果某位同学的职能更多的是基于框架和系统来做玩法内容和乐趣体验的会被归为 Gameplay；如果他的职能更多的是为游戏开发提供底层的扩展能力、优化框架和系统，增加游戏开发的技术边界等部分的内容可以算作引擎开发（如果只分引擎和 Gameplay 类别的话），当然如果愿意的话，也可以分更多的细类比如性能优化，工具开发，系统管线等。简单来说，提供能力的是引擎，提供内容的是 Gameplay。

****2 Unreal Gameplay 框架介绍****

关于框架的理解，必然每个人还是有自己的看法。这里我们先就只讨论一下 Unreal 在文档中标记的 GamePlay 框架的内容，即：

*   游戏规则
*   角色
*   控制
*   相机
*   用户界面和 HUD

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhPudYM2bCYibBrlARpxutG8FzuFibG02qXSpQQszw3jznqeRAw6AEia0hQ/640?wx_fmt=png)

拿官方的一个示例举例来说明 Gameplay 的工作方式：

> 兔子与蜗牛赛跑。游戏框架的基础是 GameMode。GameMode 设置的是游戏规则，如首个跨过终点线的玩家即是冠军。其同时可生成玩家。在 PlayerController 中设置一名玩家，其同时会产生一个 Pawn。Pawn 是玩家在游戏中的物理代表，控制器则拥有 Pawn 并设置其行为规则。本范例中共有 2 个 Pawn，一个用于蜗牛而另一个用于兔子。兔子实际为 角色（Character），是 pawn 的一个特殊子类，拥有跑跳等内置移动功能。另一方面，蜗牛拥有不同的移动风格，可从 Pawn 类处直接延展。Pawn 可包含自身的移动规则和其他游戏逻辑，但控制器也可拥有该功能。控制器可以是获取真人玩家输入的 PlayerController 或是电脑自动控制的 AIController。在本范例中，玩家控制的是蜗牛，因此 PlayerController 拥有的是蜗牛 Pawn。而 AI 则控制兔子，AIController 则拥有兔子角色，其中已设有停止、冲刺或打盹等行为。相机（Camera）提供的视角仅对真人玩家有效，因此 PlayerCamera 仅会使用蜗牛 Pawn 的其中一个 CameraComponent。进行游戏时，玩家的输出将使蜗牛在地图中四处移动，同时 HUD 将覆盖在相机提供的视角上，显示目前游戏中的第一名和已进行的游戏时间。

****2.1 GameMode****

在上面这个例子中，GameMode 决定的是游戏规则，即拥有两个角色，先跨过终点线的玩家为冠军。衍生的部分还有比如是否允许观战以及观战的人数最多为多少？玩家如何进入游戏，以及使用哪张比赛地图？游戏是否可以暂停，以及暂停之后如何恢复？游戏是否允许使用道具，又或者是否可以在游戏中作弊等，这些规则都是跑在服务器上的，确保规则的权威性和安全性。GameMode 在 Unreal 里的实现是 AGameModeBase 类（用 A 开头是因为它继承于 Unreal 的 AActor，这是 Unreal 的类命名规则，可以查看代码规范），它是 AGameMode 的基类。一个项目可以拥有任意多的 GameMode 来设置各种各样的玩法，但同一时刻只能使用一个 GameMode。AGameModeBase 提供若干基础的、可被 override 的接口：

*   InitGame。在这里做所有游戏规则的初始化工作。
*   PreLogin 。登录前的预处理。由于 GameMode 只会跑在服务器上，可以在这里检查玩家的合法性，判定是否允许玩家登录服务器。
*   PostLogin。登录后的后处理。玩家成功登录服务器之后的调用。
*   HandleStartingNewPlayer。一般登录成功之后就会创建玩家在服务器上的对象，对象创建成功之后会调用该函数，可以在这里对玩家进行初始化，比如获取玩家的 PlayerState。
*   RestartPlayer。创建玩家的实体对象（可操控的，场景上可见的 Pawn 对象）。
*   Logout。玩家退出或者服务器被销毁时调用。

其他的还有很多，这里只列举了一部分。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh092D2c6TXPkuNnzLLFv4uA0OY1H62FErR58WR2P3qgqSJTbY3ibNAaA/640?wx_fmt=png)

再次强调，这些逻辑都是存在服务器上的，客户端是没有办法访问的。如果确实需要访问一些 GameMode 相关的信息，那可以通过创建一个 Actor，把相关属性和数据赋值给 Actor，之后由 replication 机制覆盖到远程客户端上。

上面说到的是 AGameModeBase 类。其实在 4.14 版本之前，通用的是 AGameMode，该类现在仍然保留，它提供一些扩展类的接口。新建工程默认都是从 AGameModeBase 类继承，当然开发者可以手动从 AGameMode 继承以获取以下接口：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhgky4pvKXdSfxNEsw2iaJmA3iaxLSSZAvoViatibzwsy5uAeINPTkibcibJ6g/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmht21HIZBxUdV9D3iaEZbLyOVsicPfCzbpLcahs8TAzwB5LLYdAbffDqbQ/640?wx_fmt=png)

GameMode 作为 Unreal 项目的开始入口，是需要在最开始进行初始化的。那么它的设置方式也有很多种：

在工程的 Project Setting 下进行设置。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhuOpxLqZAcouvJ5p4W3WxfnVAbvaqTubz9C2UnW9RdrZOgTfr04cOaw/640?wx_fmt=png)

在 DefaultEngine.ini 的文件里进行设置

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhicrzZhh7PBptnChb8SPcojzLVCdFeckY5uf6vIQYUC7ofwdqbcWLQ7Q/640?wx_fmt=png)

其实第一种的设置方式也是修改了这个配置文件而已。更多的操作方法可以查看 设置游戏模式 。

****2.2 Game State****

字面意思，Game State 就是指游戏状态。它管理了所有已连接的客户端，并且实时追踪游戏层面的属性并把它们分发给远程客户端。有别于 Play State，GS（GameState）主要是负责游戏全局属性，比如 5V5Moba 游戏中的红蓝双方防御塔的剩余数量，游戏当前进行的时间，大小龙击杀的情况，红蓝阵营野怪刷新情况等等。而 PS（Player State）则是记录单个玩家的属性和状态，比如补了多少刀，出了什么状态，身上有多少钱，技能冷却时间等等。

归纳一下就是，GS 应该追踪游戏进程中变化的属性，这些属性与所有人皆相关，且所有人可见。它存在于服务器上，但会被复制到所有的客户端上。

和 GameMode 一样，Game State 也是在 AGameStateBase 中实现基础接口，并且在 Project Setting 中进行配置。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhhQXGeM2IZ9D6XqsKRIuYEiaiaPww3gO0UPsVDuox2yicicdqsQw2uBoV2Q/640?wx_fmt=png)

几个比较重要的函数：

*   GetServerWorldTimeSeconds 服务器版本的游戏时间，权威可靠的，会被同步在客户端。
*   PlayerArray。所有 APlayerState 的列表，对游戏中玩家执行操作和逻辑时候非常有用。
*   BeginPlay。

还有一些其他的接口，如下。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh52wdxiaxMKdnxKmzb9R0DjVn9QDNCweITjlyLe8NWTZ1hfSBkws6HxA/640?wx_fmt=png)

需要注意的是，这仅仅是 Unreal 从引擎侧实现的最小版本，在项目开发的时候，你可以使用它来扩展任意的 Game State 数据，并进行远程客户端的数据推送。  

****2.3 Camera****

接下来是大名鼎鼎的 “3C” 之一的 Camera（相机）。在面试的时候，对于中初级的开发同学我一般都会跟他探讨一个话题：“你怎么理解 3C？”

而得到的回答很多都是字面意思，相机，控制，和角色。如果健谈一点的同学可能还会补充一下，代表一个游戏的基础体验。但我其实更希望能听到他们举一些例子（无论是自己做过的还是别的游戏的），来说明如何通过这些模块来提高玩家的基础体验甚至变成游戏玩法的一部分。

相机在游戏中其实是代表了玩家的视角，以及玩家如何去观察这个 “世界”。它不但会关联渲染，给管线提供必要的渲染内容可视性和遮挡剔除，同时也承载这渲染完成之后的后处理效果后期处理效果。但更多的是，如何使用相机的组件模块来完成更好的游戏体验和沉浸感。比如以下列举一些相机组件完成的游戏体验：

*   《英雄联盟》中，盖伦使用 R 斩杀了敌人之后，画面会表现出气浪冲击波的效果。
*   《尘埃》赛车游戏中，通过切换不同视角来完成第一人称和第三人称的驾驶体验。同时可以通过额外的摄像机渲染来完成后视镜的效果。
*   《黎明杀机》中，屠夫（第一视角）和逃生者（第三视角）的游玩视角不一样。屠夫可以通过佩戴 “鹰眼” 的技能来让视野变成类似于水滴透镜的效果，从而得到更开阔的视野。
*   《鬼泣》中，通过切换固定摄像机视角来完成走廊到房间的视角切换。或者模拟一个虚拟演唱会上的导播相机调度。
*   飞行游戏中可以通过设置轻微的动画来模拟穿过气流的颠簸感。航海游戏可以通过设置轻微的动画来表达海浪对船造成的轻微摇摆。常规的 3D 游戏可以使用弹簧臂的形式，让玩家躲在墙角或者被建筑遮挡的时候，相机不会穿模。
*   射击游戏中，通过改变相机的 FOV 参数完成狙击枪的模拟。格斗或者动作游戏中可以通过调用相机震动来调优 “打击感”。

关于相机提升基础体验，总结为两点：

*   如何正确使用 UE 提供的相机和相机组件 使用摄像机
*   如何通过配置 / 开发相机动画完成 摄像机动画

****2.4 Character****

提到角色，就需要先提一下他的父类 Pawn（棋子）《InsideUE4》GamePlay 架构（四）Pawn。UE 中，把所有可以在游戏中视觉看到的东西都称之为 Pawn。比如一张桌子，一块石头，一个池塘等。Pawn 继承自 Actor，并且一个 Pawn 需要很多个组件和它一起作用，比如场景上有一个金矿石：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhPRfHEjI0NqYhg2CgASt84em57Zj6uOAHD4nPa4ISaznT9esCg7ibMibg/640?wx_fmt=png)

它的位置、旋转和缩放由 SceneComponent 中定义的 Transform 信息所决定。

它的可视化样子由 StaticMeshComponent 决定。

它如果发光就需要绑定一个粒子组件 ParticleSystemComponent 。

它如果需要和周围环境进行交互，有实际的物理体积就需要绑定一个碰撞盒组件 BoxComponent 。回到角色上来，一个 Character 就是一个特殊的，可以行走的 Pawn，一般代表垂直站立的玩家。也就是说它比 Pawn 多了

CharacterMovementComponent，同时，因为一个可行走的模型需要提供一些行走动画，所以还需要 SkeletalMeshComponent 组件来提供骨骼框架，由于人的形状和盒子差别很大，所以在物理碰撞上用胶囊体 CapsuleComponent 来替换碰撞盒。角色组件是一个 Avatar，代表玩家在和游戏场景交互。并且可以在场景中行走、跑动、跳跃、飞行和游泳等，同样作为一个 Actor，它也包含基础的网络功能，并接受玩家的输入控制。当然可以可以任意扩展和使用 Character。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhick08Ciago9tic3WBs4C8rQkTib7m8ZxtLiax1zPdkI77cGhFJrRNFWlcdw/640?wx_fmt=png)

关于角色的拓展可以做的非常非常的深，包含动画，场景交互，物理等维度都是可以的。比如不使用刚体物理即可行走、跑动、跳跃、飞行、坠落、摔倒、游泳和攀爬等，比如在空气、水、沼泽，沙漠、雪地、太空等场景下中行进的速度、浮力、重力值，以及角色能对物理对象施加的物理作用力（魔法，科技等）等。再比如一些动画相关的表现：RootMotion，MotionMatching 新一代动画技术：Motion Matching，IK/FK 等。其他关于 Character 的基础介绍可以查阅：Setting Up a Character 。

****2.5 Controller****

过去我们在谈论 UI 框架的时候，一个被提及的最多的模式就是 MVC。它把一个系统结构分为数据 - 视图 - 控制三个不同的关系层。目的是为了减少逻辑耦合，并让每个层的职能更加的专一化。相同的概念我们也可以引入到一些战斗的设计中，比如逻辑 - 表现分离，用事件或者协议来传递数据并驱动逻辑执行。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhT3bbAMchDFiczYAxCB31FrLkdKYXSSEwUzsBtIMGtD4VrBnFkwfRNBA/640?wx_fmt=png)

那么到 Gameplay 框架中，我们仍然能找到一个比较合适的部分来套用这套模式。比如我们现在的 M 就是 Player State，我们的 V 就是 Character，那么 C 自然就是马上要介绍的 Controller 了（如果要看系统性的介绍请看这篇 《InsideUE4》GamePlay 架构（五）Controller）。AController 继承自 AActor，也就是说它并没有场景实体，是一个场景不可见的对象。它拥有一个 PlayerState，一个 Pawn，如果这个 Pawn 同样是 Character 的话，那么它还有一个不为空的 Character 对象。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhlpPzPAaoHuHOj1x965sBLibPWw1IGnDtnbsIf9Zr5LCfJXRd1psjib8Q/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhiaLrJ94IpMttia6DjS04UiaC7U3V6JicXVq0eo7TNAdVl60GmSnTewdnIw/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhDvhJJvo4VXahPFIykm0sS0HUe123N8oWSs41IM2zeqYcaFeyXficibCQ/640?wx_fmt=png)

默认情况下，一个控制器只对应一个 Pawn，二者之间也非强绑定关系而是组合关系。如果需要更改默认的控制器逻辑，可以自定义继承实现。

控制器会接收其控制的 Pawn 所发生诸多事件的通知。因此控制器可借机实现响应该事件的行为，拦截事件并接替 Pawn 的默认行为。控制器又分为两种不同的类型《InsideUE4》GamePlay 架构（六）PlayerController 和 AIController：

*   Player Controller 。代表玩家的输入和控制。
*   AI Controller 。代表 AI 或者远程玩家在本地的镜像。

其中 Player Controller 是玩家直接操控角色的逻辑类，因此非常复杂。大体可以分为 Camera 管理，Input 响应，UPlayer 关联和操控，HUD 显示，关卡切换的逻辑处理，音效部分等等。而 AI Controller 因为不需要接受玩家操控，因此对 Camera、Input、UPlayer 关联，HUD 显示，Voice、Level 切换等部分都不是必须的，但对应的它增加了一些额外的模块，比如 Navigation（导航）, 行为树, Task 系统等实现。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhALn4D3nqDMX74q1eSeMibOYV3jkz1drZo7fnH6jjLqrFn7Zbem8AX4A/640?wx_fmt=png)

****2.6 HUD 和 UI****

HUD 可以理解为对部分 Player State 的场景可视化。比如怪物或者人物头顶的血条，名字等等。而 UI 则是覆盖在场景渲染之上，提供更多玩家交互和查看的信息。二者的主要区别是在交互上，HUD 一般来说是不能交互的，简略的信息；而 UI 则指的是菜单和其他互动元素。这部分不展开细说，可以参考 Slate UI 编程

****2.7 其他****

以上是 Unreal 4.x 时代的 Gameplay 框架所包含的内容，到了 5.1 之后，又新增了一些内容，我们也顺带提一下。

Actors。不得不再次搬出大钊的文章《InsideUE4》GamePlay 架构（一）Actor 和 Component，强烈建议大家系统性的学习他的 “GamePlay 架构” 系列。因为文章视角不一样，我这里基本不会展开讨论细节。Actor 除了继承自 UObject 的序列化、反射、内存管理等能力之外，额外实现的是组件的组合能力，Tick 能力，网络复制能力和对生命周期的管控 Actor 生命周期。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhXkZp9a3K28xN2SYrfcttcK8uBRfa2ZicXgpPhkjT0BVTWc6GHaPakfw/640?wx_fmt=png)

简单介绍一下上面这张图，它展示了 Actor 的三种实例化方式，但无论它是怎么 “来” 的，它 “走” 的流程是一样的。三种模式是：

*   从磁盘加载
*   Play in Editor
*   Spawn

其中 1 和 2 十分相似，1 是从磁盘里加载，2 是从编辑器中复制。当实例化之后都会执行 Post（Load || Duplicate）逻辑, InitializeActorsForPlay（UWorld 调用），再到 RouteActorInitialize（Actor 自己的组件初始化），再到关卡开始的逻辑调用 BeginPlay。

3 的逻辑不同，它是通过运行时生成的，所以执行的是 PostCreate，然后需要执行对应的构造逻辑 ExecuteConstruction 来创建蓝图变量，然后用 PostActorConstruction 来执行 Actor 自身的组件初始化（其实和 RouteActorInitialize 的主要一样），然后就是一样的 BeginPlay。

虽然创建逻辑有差异，但销毁逻辑一致，执行了 EndPlay 之后，Actor 就会被标记为 RF_PendingKill, 并在下个垃圾回收周期中被解除分配，然后有垃圾回收器将其回收。

Timer 。不是很明白，为什么要把定时器单独归类到 Gameplay 框架中来。可能是因为 AActor 中提供了 GetWorldTimerManager 函数来获取 FTimerManager 的实例？定时器可以设置使用指定时间，或者指定帧来作为触发器。

UCharacterMovementComponent 的移动逻辑。除了人物移动之外，还有表示发射物 / 子弹移动的组件 ProjectileMovementComponent，以及一些特定的运动组件，比如 RotatingMovementComponent 用来展示飞机螺旋桨，风车或者任何可以旋转的东西。

****3 Unreal Gameplay 框架 Runtime 流程****

在上一篇 Unreal Engine 的启动流程中，我们留了一个大坑。引擎的 Init 和 Tick 我们就只介绍了一点皮毛，也就是 EngineLoop 自身阶段的逻辑情况，那么真正跟开发者相关的部分还是 EngineLoop 调用了 EditorEngine 或者是 GameEngine 之后的 Gameplay 部分。因为整个逻辑引擎的 tick 太多了，我们只聊一下跟 Gameplay 初始化相关的部分。先翻出这张包浆图：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhZswglPNZApqNuHKhs60xhRLugzVj1l9GuBaBsnbWxsHYuBxZvpUDrg/640?wx_fmt=png)

这张图主要展示了编辑器环境下和 Runtime 环境下 Gameplay 的初始化顺序。而编辑器又比较特殊，它既要处理 Editor 编辑器本身的初始化，又要解决 PIE（Play in Editor 也就是编辑器中点击 Play 按钮）和 SIE（Simulate in Editor 编辑器中点击模拟）情况下的初始化情况。

求同存异，我们从共同的部分开始整（图上蓝色部分）。看一下 UWorld::BeginPlay 这个函数的介绍：Gameplay（梦）开始的地方，开始 GameMode 逻辑并且调用所有 Actors 的 BeginPlay 函数。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhXiaaP3viaVPDrWLgpY1stE3XiaqQicGq88TsGgz1yF4xO5iaCdFkkVCicU3Q/640?wx_fmt=png)

逻辑实现如下：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhOn8SzGXCcQk2yOzKJia55Q80lL2r6w0UicG0HNico3eIkHS4O1eAmPDIg/640?wx_fmt=png)

初始化所有 World 类型的 Subsystem 并调用它们的 OnWorldBeginPlay 函数。

*   根据服务器类型生成服务器的 Actors
    
*   调用 GameMode 的 StartPlay
    
*   如果有 AISystem，那么 StartPlay
    
*   进行 WorldBeginPlay 事件广播
    
*   初始化物理系统
    

到这里，我们的第一个 Gameplay 的元素 GameMode 已经开始工作了。那么接下来往下就是 GameMode 的 StartPlay 逻辑了。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhjdx8yV8ff43aUoLutl71RurDzVKPQpzNwicToOZTCxGupVGpJjsWvDQ/640?wx_fmt=png)

这里第二个元素 GameState 也上场了。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhAediaW8Y7t4yEZjozPk6Z5eMvu7UOpAicibViaPUW05QGXrZl1yD2TKicIA/640?wx_fmt=png)

GameState 对所有 Actors 派发了 BeginPlay 事件，并广播了 OnWorldMatchStarting 事件。那么其余的部分是在哪里初始化的呢？答案是在 BeginPlay 之前。

上面的提到了 GameMode 的 StartPlay 流程，但它必须先初始化才能够执行 StartPlay。它的初始化逻辑就写在 StartPlayInEditorGameInstance 函数中，也就是当我们在编辑器里按下 Play 按钮之后。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhHqPSMIdQRSxz9lr3gejykjPhMhVFxQezdlOtC7VfJEYz52fRBhurZQ/640?wx_fmt=png)

在进行了一系列的参数组装之后，它会开始调用 GameMode 的初始化。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhcdiabLyD9fJTUT8NicfibMibMoFkLo9Kw15QhYf9LoiaQrJ8LASzXr5GvoQ/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhx1zuVIKicmunXgcSp7S4GLyGpu95KAOibD4hQjIKFZVNKPUcbF3VJpuA/640?wx_fmt=png)

再往后执行一系列其他初始化工作之后，开始为 LocalPlayer 本地玩家创建 Actor。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh2Q1iay8ibAL48FSgRSsOuXCjJa9V5VwYTrJrfx8jlmpc4hreFh3hKNQA/640?wx_fmt=png)

本地玩家先要完成登录验证，然后会返回一个 PlayerController，这个对象在 Login 逻辑中生成。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhUc6PtHFbmLyiaMxJkmQOcpZXLozwEcwFl1jiaRHqx7YFuFK7Lqiaicv9GQ/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhgJ18Y2Y4OI6YtiaUpwFHTWhHibeI4tAJXmrS8tbgZDrcYqVTp7ibx6CpQ/640?wx_fmt=png)

然后来到了 PostLogin 逻辑，当玩家成功登录之后，就会调用 HandleStartingNewPlayer 函数并开始一场比赛。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhEYIFI0dFBerbkrEqSQKzOIuHUgNWoD1zJR87oYBQeEk7BFQld6K01g/640?wx_fmt=png)

在 Handle 的字调用栈里就会去创建一个 Pawn（Character）来跟 Controller 进行绑定。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhB1zOYf7LQbNY4BusLggr45UdwIY24qOugBmyGd44LYM6lSjKlnzgTA/640?wx_fmt=png)

然后创建 HUD（事实上 HUD 的调用逻辑比 Pawn 早一点点，都是在 AGameModeBase::PostLogin 里做的）。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhuNDpeWYkO6YRvial3NXZmMkfPt61mFrHzF8iaIwR9tKicFjtIculwhDiaA/640?wx_fmt=png)

到这里，Controller，Character，HUD 都已经出现了，加上之前提到的 GameMode 和 GameState，狭义上的 Gameplay 就只剩下 Camera 了。

Camera 因为关联着渲染，本身逻辑会复杂很多，并且初始化的时机也要提前很多，大部分时候和跟随场景一起加载了。但 Camera 并没有那么多花样，它就是视口和 transform 的信息，再加上渲染好的 renderTexture 用作后处理。Gameplay 向的相机玩法更多的是做相机的动画和功能用途，比如跟随，切换视角，平滑轨迹或者用小型的摄像机动画模拟各种显示场景来达到沉浸感。

除了前面在框架介绍里提到的一些 Camera 的用法之外，还可以看一下这个了解一下 Camera 系统 UE4 里的 Camera 系统 ，代码里直接差 APlayerCameraManager 类就好。

另外，Controller 是持有 Camera 对象并且可以操作 Camera 对象的。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhhfBic1u4ODfClRFR5p7zEuYYWibPxogDibBCbRVVl9Z8hkqV0PEXPJR6Q/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhxOy6FM819XqrzlVNLe2FrCfZe3zPBbY0B5OrUemut0zibEibKLDO23lA/640?wx_fmt=png)

架构图我也不想画了，怎么画都不会有 @大钊 画的好，大家直接看他的就好了《InsideUE4》GamePlay 架构（十）总结。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhia7RuLpSBRl9aMVHUQINyzfFALnl75aW0XlsK9ustW0hQtQ1DTmnicXw/640?wx_fmt=png)

****4 Lyra 工程中的 Gameplay 部分****

Lyra 是 Epic 提供的基于 Unreal5 的初学者示例项目，但如果你真信了它是初学者项目的话，只能说会很惨。。。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmh5BmicL5vlicaXZdy1ZXSr0t8A8ZkUdZxPRqurXBVTFMrOOmHl46luO0Q/640?wx_fmt=png)

严格来说它一点都不初级，甚至非常高级，说是当前 Unreal 5 的最佳实践也不过分。它向开发者展示了如何去重写一个项目的 Gameplay，展示了最新的 Unreal 5 的特性和使用方式，甚至写了一些完全可以独立复用的 Plugin 插件。本篇的重点还是 Gameplay 部分，所以我们着重聊一下 ModularGameplayActors 这个自定义的 Gameplay 扩展插件和 Lyra 基于它的业务逻辑。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhSJ4n9Z0ebNX4ib2l5UBsKWp6c7mpnevrnu30wsTdXp0fLjH8cnZUPtw/640?wx_fmt=png)

其实这个思想很好，它用一套自己的 Modular 来隔离引擎和项目层，我自己的开发理念也是相似的，能不动引擎的尽量不动，自己写一些继承和扩展，既有自由度，又不会在未来引擎升级或者业务修改的时候造成兼容性的麻烦。这个 Plugin 其实没有任何实质的内容，就是对所有涉及到的引擎原有模块做出继承，也就是充当了项目和引擎之间的缓冲带。比如 AModularGameModeBase，AModularGameStateBase 等分别如下：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhaC2xznfw0A4opHickxPGMeK6WRW1oqlGbIZjo2Qnq0wTLnL3CXQpWUQ/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhGbQ54roFdQ4O7v79CibxIUOSBrDlEN4IgibSiar3ltzjFTRY2N01Y5RKg/640?wx_fmt=png)

他们都只做了最基本的继承而已。那么重要的其实是在 Lyra 下的实现，我们一一来看。最开始的自然是 GameMode 了，由于所有的基础模块都重写了，所以在构造函数里，需要将它们一一重新指定初始化。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhTMPSpaJhI9B8ibW0UPxt3dniaosDnDFiaxicCTRgqFsawPLccTxtdvcZxA/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A73YgeD1XwpNN05EUVrdzmhmRJwMCjQtuzOCFmeaA6vibWRf2pN3Y3XAQwwuOLZk5vjpwBO8xVCT5g/640?wx_fmt=png)

额 好像不能这么写，不然又变成讲细节了。但找了一圈又没找到专项介绍这部分内容的其他文章（如果大家看到的话，欢迎私聊我，我把链接贴上来）。如果全部展开来说的话，这篇文章的的长度要爆炸了（已经 1 万字了）。那就放到下一篇吧，写个详细一点的流程剖析。

预告：下篇：**Unreal 5 新项目 Gameplay 框架重构（以 Lyra 为例）**

[

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/z6LMx9vQ9A5H1QK575yCG30XIYrSSGlYtcz597u2dWAA5fo44Vzbf1JtcGYyu6LIibfnHmOpUx003VQpzzIzDkg/640?wx_fmt=jpeg)

Unreal 引擎 ，启动！







](https://mp.weixin.qq.com/s?__biz=MzA4NTg1Mzk0OQ==&mid=2649902588&idx=1&sn=4cb36041a83b855d72793b0baa5d9b9d&chksm=87d77e6eb0a0f778dbd446cc7434aa791606f8e7f9828700e14d0750f3ec8656fd889d8132e1&scene=21#wechat_redirect)

  

[

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/z6LMx9vQ9A4gpDzmtvAJNibRk1ib8FDzXLlWs9Vv7ciaKeaTfsibltHh0IeiabccfoboslxtETHlXibEvnUWVgWzOvWQ/640?wx_fmt=jpeg)

写给 Unity 开发者的 Unreal Engine 开发指南 （扫盲）







](https://mp.weixin.qq.com/s?__biz=MzA4NTg1Mzk0OQ==&mid=2649902281&idx=1&sn=8f774023fb6522037af77485abdfc1af&chksm=87d77f5bb0a0f64df6d6fb5db20ff9fb66aa6b7899b8689d0618c7a9da2748a95bc25d6fee39&scene=21#wechat_redirect)

  

**关注我，不迷路~**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/z6LMx9vQ9A5H1QK575yCG30XIYrSSGlY4mw7PliaGIialRFBA2aycOEtwL4wUaxcc3aAnzSric16ibu8FlRIonTxicg/640)  

点击下方名片，将公众号**设为星标****（流程如上图）**

可第一时间收到推送和完整封面！

  
  

个人观点，仅供参考