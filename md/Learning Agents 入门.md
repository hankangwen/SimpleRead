> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/-qh69C7WWfHA7LTWe_O7Bw)

**![](https://mmbiz.qpic.cn/mmbiz_jpg/s2uc3bvmFVCUOYtc43hqj5OlLs1INNkFAMlbo6pSKa1WPhVwUL6twoveF9w1fUNlmk7ahiaRUbcbFRkIyNHU1TA/640?wx_fmt=jpeg)**

了解 Learning Agents：一款用于 AI 机器人的机器学习插件。Learning Agents 可以帮助你通过强化学习和模仿学习训练 NPC，可以用来创建游戏玩法代理、基于物理的动画和自动化 QA 机器人等等！

我们先通过一个简单的例子来看一下 Learning Agents 各个部分的实际工作方式。在这个教程中，我们将训练一个神经网络，让它在赛道上驾驶跑车。

我们先通过一个简单的例子来看一下 Learning Agents 各个部分的实际工作方式。在这个教程中，我们将训练一个神经网络，让它在赛道上驾驶跑车。我们的目标是训练一个代理，确保它能够在不偏离赛道的情况下，尽可能快地跑完赛道。首先，我们将使用强化学习来训练网络，在之后的教程中，我们还会展示如何使用模仿学习来加速这个过程。我们将使用虚幻引擎 5.3 提供的车辆模板，这可以帮助我们节省大量设置时间。这个教程只涉及蓝图，不需要掌握 C++ 方面的知识。

完成本教程的学习后，你将拥有一个经过完全训练的模型，效果如下所示：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5srdZvRxh1lubZ5Es5KoqZfKGQp79q4ung8xmeSCS30OcGIAcolE8RA/640?wx_fmt=png)

**问题 - 2023 年 9 月 11 日**
========================

*   **Mac 问题**：本教程目前仅适用于 **Windows** 系统。在明确针对 Mac 的调整措施后，我们将在可能的情况下增加额外的步骤。
    
*   **超时**：在收集体验的过程中，有部分用户反馈称存在超时问题。请参阅相关论坛帖了解补救措施。
    

**初始设置**

1. 通过 Epic Games 启动程序安装虚幻引擎 5.3.0（或更高版本）。

2. 点击 “启动”，打开虚幻项目浏览器：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5BICa51jHqjSVKfRLPmg9gzm2AVm3Fia1LmGMPvO7skk46o7ibufUEJNw/640?wx_fmt=png)

_虚幻引擎 5.3 中的新项目菜单_

  1. 点击左侧列表中的**游戏**。

  2. 点击**载具**。

 3. 设置合理的项目位置和名称。例如 “LearningAgentsDrive”。

  4. 点击**创建**。

3. 如果一切顺利，就能打开新项目，界面如下所示：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5hyywR3wqrRPUU6FF4z86t73x8hKDG5yexuQRhfKvmwwrZia36HqlnLg/640?wx_fmt=png)

_这是利用载具模板创建新项目时显示的编辑器界面。_

**测试**

如果想快速检查完整性，可以点击绿色的运行按钮，驾驶车辆，感受一下车辆的操控性。

控制：

*   W - 加速
    
*   S - 刹车
    
*   A - 左转
    
*   D - 右转
    
*   空格键 - 手刹
    
*   鼠标 - 四处浏览
    
*   Tab 键 - 切换第一人称视角和第三人称视角
    
*   退格键 - 重置车辆（比如车辆翻转时）
    

**清理地图**
========

为了尽量避免训练时出现问题，我们需要删除地图中可能妨碍训练的对象，比如这些护柱、坡道和道路减速带。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC50NCBicf28kcNjk1DCRJmjSkeqvfHxdrTiaJA9VruFEPhC9p9iaxAV6Gzg/640?wx_fmt=png)

_删除大纲面板中高亮显示的项目。_

在大纲面板中，你可以单击最上面的护柱，然后按住 shift 键，单击最后一个圆柱体，然后按删除键将它们全部删除。接下来，你可以一一删除剩余的障碍物、护柱、坡道和道路减速带文件夹。

**启用 Learning Agents 插件**
=========================

最后，我们需要启用 Learning Agents 插件。在顶部的导航菜单中，单击 “编辑”，选择 “插件”。搜索 “Learning Agents”，勾选插件旁边的方框，启用插件。
===========================================================================================

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5qHrruHYEGEEtMJcFkJEd8UNXicIpbP4eMHobEtYR1Nq9TkvfYZCFG6A/640?wx_fmt=png)

_编辑器插件窗口显示的 Learning Agents 插件_

这时会弹出一个窗口，表明 Learning Agents 是一个实验性插件。点击 “确定” 继续。窗口底部会出现一个 “立即重启” 按钮。单击这个按钮重新启动编辑器。编辑器会自动重新打开。

完成初始设置后，就可以开始使用 Learning Agents 插件！

**Learning Agents 管理器**
=======================

我们要熟悉的第一个类是 Learning Agents 管理器。管理器是一种 Actor，Learning Agents 的剩余部分都将围绕这个 Actor 构建。它既是一种数据结构，存储着各种代理的引用，也将用来设置学习逻辑。代理以批量方式进行处理，旨在提高工作效率。代理可以是任意 UObject，也就是说，你可以将任何对象设为代理。在这个例子中，我们将使用 SportsCar_Pawn 作为代理。管理器类通过一系列管理器组件进行扩展，这些组件可以增强管理器的功能，包括交互器、训练器、录制器等等。在这个教程中，我们会详细介绍这些组件。
===============================================================================================================================================================================================================================================================================

**创建管理器蓝图**

在内容侧滑菜单的 “内容” 文件夹中创建一个新的文件夹，命名为“Learning”：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5noDjIJ64MTRYGqWOlTYzfo5XASWlpHSjicZY5JpD9Z52rQYxpVfgggA/640?wx_fmt=png)

_编辑器内容浏览器中显示新建的 Learning 文件夹。_

在 Learning 文件夹中单击鼠标右键，创建一个新的蓝图类。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5x9VojRk640tVKGzLu7NqTd2MlXRmj4ECJDjtsLXShW77McpbuiaOibww/640?wx_fmt=png)

_蓝图类按钮在右键单击列表中。_

在 “选择父类” 窗口中，展开“所有类”，搜索“LearningAgentsManager”。选择

“LearningAgentsManager（LearningAgents 管理器）”，点击 “选择” 按钮。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5ehXrBxbq6bDrEKfQpEsIqX2EyGo9CjERpbcQM4ycdOcf99iatcZzg2w/640?wx_fmt=png)

_选择父类窗口中显示 LearningAgentsManager。_

创建好之后，我们要为新的资产设置一个合理的名称。这个管理器将用于强化学习训练，我们可以把它命名为 “BP_RLTrainingManager”。你可以先打开蓝图图表，稍后我们再继续构建这个蓝图。

最后，在 “VehicleExampleMap” 中放置一个管理器实例。在这个教程中，管理器的位置不重要。

**使用管理器注册代理**

要成为代理，跑车的每个实例都要通过管理器进行注册。一种方法是让 Pawn 在**开始运行（BeginPlay）**期间找到管理器并调用**添加代理（AddAgent）**。打开 SportsCar_Pawn 蓝图（按 Alt+Shift+O 并搜索 “SportsCar_Pawn”）。在蓝图中添加一个注释框，说明 Pawn 需要找到管理器并注册，具体如下所示：

_![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5xafwONPmAzicRF5AZib4vvHgyjARsHaXiaqLqegpttLhAHIbIsHOniaIvA/640?wx_fmt=png)_

_* 点击 “阅读原文” 查看完整蓝图_  

首先，我们要找到管理器。我们可以使用**获取类的 Actor（Get Actor Of Class）**，将 **Actor 类****（ActorClass）**设为

“LearningAgentsManager”。后面我们将会看到，定义多个不同的管理器很正常，例如一个训练管理器和一个单独的推断管理器。通过让 Pawn 寻找基类，而不是特定的

“BP_RLTrainingManager” 类，Pawn 可以更轻松地和我们定义的任意管理器协同工作。

找到并验证管理器之后，我们可以调用**添加代理（AddAgent）**。**添加代理**将获取一个 UObject 引用，这个对象就是代理本身。因为我们现在在跑车的蓝图中，我们可以使用**自身（Self）**节点来注册 Pawn。添加代理返回唯一的一个整数，作为这辆车的**代理 ID（AgentId）**。涉及代理管理器的大多数方法都接受**代理 ID**（比如获取代理（GetAgent）、移除代理（RemoveAgent）等），因此你可以把它提升为变量，以便之后使用。

通过调用添加代理，管理器的**代理**数组属性中会增加一个指向车辆的指针。如你所见，Learning Agents 的其余部分将接收这组代理，以便执行与学习相关的各种任务，例如收集观察和采取行动。

现在我们要快速测试一下，确保已将车辆正确添加到管理器中。

**日志**

每当在管理器中添加或删除一个代理，就会向 “日志学习（LogLearning）” 发送一条消息。在玩游戏的时候，我们可以在输出日志中看到类似的信息：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5UjJicqibpuqyseUWrwu9y4hWYAic4VmeJgEHicWru3UNro0FrvDtXR4gjg/640?wx_fmt=png)

_添加代理时显示的日志消息示例。_

如果你没看到这条消息，就要检查一下是否将 **BP_RLTrainingManager** 放在了关卡中的某个位置，再返回上一步检查一下 Pawn 的蓝图代码是否正确。

**日志学习（LogLearning）**将用于 Learning Agents 发出的各种有用信息和消息，包括警告和错误。如果你的游戏看起来存在学习问题，最好检查一下输出日志，看一下有没有警告或错误提示。

**Learning Agents 管理器组件**
=========================

现在，我们已经将管理器放到关卡中，车辆也已经注册为代理。接下来，我们要让管理器利用这些代理做一些有用的事情。管理器的大部分功能都来自于**管理器组件**。这些组件可以扩展管理器，使管理器能够执行各种任务，比如收集观察、采取行动、执行训练和将数据记录到文件中等等。在下一节中，我们将介绍三种组件：交互器、策略和训练器。

**Learning Agents 交互器**

交互器组件负责定义管理器的代理如何通过观察和行动与世界交互。指定管理器的所有代理共享一组相同的观察和行动。我们要在游戏中实现交互器的四个主要功能：SetupObservations（观察设置）、SetObservations（设置观察）、SetupActions（行动设置）和 GetActions（获取行动）。我们来创建交互器蓝图，然后为车辆实现这些事件。

在内容侧滑菜单中，右键单击并创建一个新的蓝图类。选择 **LearningAgents 交互器**

**（LearningAgentsInteractor）**作为父类，将它命名为 “BP_DrivingInteractor”。打开蓝图并点击“事件图表（Event Graph）” 选项卡（如果没有打开的话）。

**观察**

Learning Agents 包含很多预定义观察对象，我们可以添加强类型数据，这些数据将被用作神经网络的输入。添加观察的位置、速度和各种其他游戏状态很简单。除了被观察的原始数据，观察对象通常还会接收额外的可选参数，用于将原始观察转化为以自我为中心的参照系。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5icM6X4tUnvAWtX8JRqe1ChR7iaxyCz7lfKloZU5MRH6pkyushFq9CX0Q/640?wx_fmt=png)

_图：世界坐标系和自我中心参考系的区别。_

自我中心参考系通常用于帮助代理更好地泛化。假设你想让代理从它当前所在的位置移动到已知的目标位置（见上图）。如果以世界坐标的形式给代理提供目标位置，代理的策略可能会记住特定于该位置的导航路径。如果位置被移到地图的其他地方，就必须再次训练代理，让它学习如何完成看似相同的任务。但是如果给代理提供一个相对位置，比如目标偏离机器人当前所在位置，旋转到机器人前向的参考系中，那么策略更有可能泛化到地图的任何部分。

这是上述示例在交互器蓝图图表中的大致逻辑：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5z6SHeRC9dfzReJ7o7jaDXuWSJVj8UBU01TtBXehOU661K2kamlDriaw/640?wx_fmt=png)

_上述示例在蓝图事件图表中的代码。_

_* 点击 “阅读原文” 查看完整蓝图_

首先，在 **Setup Observations** 事件期间，我们通过调用观察对象的添加观察函数并将它们提升为变量来声明观察对象。虽然只是个简单的例子，但在这个事件期间需要添加你的所有观察。这个事件将在初始设置期间被管理器调用一次（稍后会详细说明）。所有观察都有一个名称和一个缩放变量。目前，名称仅用于警告 / 错误消息中的调试目的，或者用于可视化记录器，但设置合理的名称以表明观察意图仍然很重要。缩放用于在输入神经网络前将数据规范化。虚幻引擎的坐标系以厘米为单位，因此通常清楚情况下，你需要增加缩放值，确保输入符合（-1,1）的大致范围。

接下来，我们要定义如何在**设置观察（Set observations）**事件期间从游戏状态中收集每个观察。对于位置观察来说，我们需要调用它的成员函数**设置位置观察**

**（SetPositionObservation）**。这个函数需要下列参数：

*   目标（必需） - 这是我们要设置的观察。
    
*   代理 ID（必需） - 正在设置观察值的代理的 ID。
    
*   位置（必需） - 将被转换并用作输入的原始数据。
    
*   相对位置（可选） - 将位置表示为一个偏移向量。
    
*   相对旋转（可选） - 将位置从全局坐标系转换为旋转后的参考系。
    

对于每个代理来说，我们可以通过将它的 ID 提供给**获取代理（GetAgent）**函数来获取代理对象。如果提供适当的**代理类（AgentClass）**，输出会自动转换为适当的类型。虽然这个示例只展示了位置观察的工作原理，但其他观察对象遵循类似的模式。在图表中添加**设置观察**节点后，你可以将鼠标悬停在节点的各个引脚上，了解每个参数的意图。

**驾驶示例观察**

为了让车辆成功在赛道上行驶，我们需要给它提供车辆相对于赛道的位置和其他状态信息（例如当前车速）。赛道用样条表示，Learning Agents 提供了一个样条辅助组件，可以轻松沿着样条观察位置。遗憾的是，当前这个赛道是用地形样条表示的，我们需要一个常规的样条组件。要解决这个问题，我们可以在地图上放置常规样条，让它匹配赛道的形状。

在内容侧滑菜单中创建一个新的蓝图类：

选择 **Actor** 作为父类。将它命名为 “BP_SportCarTrackSpline”。在这个蓝图中，使用组件面板上的添加按钮添加一个样条组件：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC580Eb5peNsereurNRibz4O2JEbRngp6GWK9wpHtKziaZmItN5vHe35SbQ/640?wx_fmt=png)

_添加组件面板显示如何添加样条_

然后，把这个 Actor 放到关卡中。如果在大纲面板中选中 Actor，可以选中它的样条组件，编辑样条。确保样条 Actor 位于（0,0,0）。将样条点放在地形样条点上。为了便于放置样条，你可以尝试将视口切换成**俯视图**，而不是**透视图**。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC55iageN1m9gIh8rDXTqMz3bYOGLg23Tb13xLkHpIFicshX1NQGM1lnKxA/640?wx_fmt=png)

_细的白色曲线为样条放置完成后的俯视效果。_

放置好样条之后，我们可以从交互器访问样条。接下来，请将以下蓝图复制粘贴到交互器中：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5yiaEdnOahgIp7ibwIRJ4YMkgw5IIno6jIYCCoZo2wQLyTWCKvqqdh71Q/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

对于每个**设置**节点来说，左键单击节点可以选中这个节点，右键单击节点会弹出一个上下文菜单，菜单中有一个**创建变量（Create variable）**按钮。创建六个变量，具体如下所示：

_![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5zibELsqJJwrq3VgeGviaTKPJGQf93gmQgrWJAdnahM8ErOicyzqtibqb1w/640?wx_fmt=png)_

_添加到观察中的六个变量。_

在 “获取类的 Actor” 节点中，将 Actor 类引脚设为“BP_SportCarTrackSpline”。

设置好之后，我们来创建**设置观察**的代码。复制粘贴以下蓝图代码：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5as4OXVv26LFOjY6vFYDrwnFOy6TfoB75K5EgvWmWYBvwG7fCCOxKfA/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

复制代码后，浏览一下图表，看看有没有节点断开。如果名称不一致，可能需要替换一些变量。

完成设置和设置观察后，代理就能感知自己在赛道上的位置。你可以将鼠标放在这个图表中的每个节点上，查看每个节点的作用。

**行动**

Learning Agents 中的行动遵循和观察同样的模式。我们要实现一个行动设置（SetupAction）事件，声明代理可以执行的行动，还要实现一个**获取行动（GetActions）**事件，从神经网络中获取行动值，再把它们应用到代理上。

为了简单起见，我们将为车辆设置两个行动：油门 / 制动和转向。将以下代码复制到交互器图表中：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC52vzZOLVIEqVkgdFOJR5HJSIoIxyTbdUEK7ZMDxqvBzNbRv6tzfsmcw/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

在**获取行动**的过程中，我们需要从神经网络中获取值，然后把它们应用到车辆上。为此，我们在每个 **LearningAgents 行动**

**（LearningAgentsAction）**对象上调用了相应的**获取行动**函数，然后以某种方式来使用这些值。跑车 Pawn 有一个 Chaos 载具移动组件（ChaosVehicleMovementComponent），我们可以通过它来应用油门、刹车和转向输入。复制下面的图表：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5M4DOsa4WKs0tY8Q90CwS5xibfoItAJzd03AMm11VTswhciaHNVtwuwsg/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

完成这个图表的创建后，保存并编译交互器蓝图。如果没有问题，你将可以看到一个绿色的校验标记，表示蓝图 “可以运行”。如果没有看到这个标记，请检查错误和相应代码，找出问题根源。

交互器已设置完成！下面我们来创建策略蓝图。

**Learning Agents 策略**

策略是负责将代理的观察转化为行动的组件。方法是将观察输入神经网络，输出行动值。

在内容侧滑菜单的 ML 文件夹中创建一个新的蓝图类，选择 **LearningAgents 策略**

**（LearningAgentsPolicy）**作为父类。设置合理的名称，比如 “BP_DrivingPolicy”。打开蓝图后，你只需要保存蓝图，然后我们来看下个部分。有关策略的相应功能，我们将在编写管理器蓝图的时候介绍。

**Learning Agents 训练器**

我们要创建的最后一个组件是 **LearningAgents 训练器（LearningAgentsTrainer）**。顾名思义，训练器负责训练代理根据它们观察到的结果，在游戏中执行正确的行动。在这个例子中，我们将实现一个强化学习训练器。Learning Agents 还可以实现其他形式的训练，比如模仿学习，本教程不涉及这方面内容。对于强化学习来说，我们需要完成两件事：**奖励**和**完成**。

我们来创建训练器蓝图和实现相关事件。返回内容侧滑菜单，像之前一样创建一个蓝图类，选择 **LearningAgents 训练器**作为父类。将这个蓝图命名为 “BP_DrivingRLTrainer”。打开训练器的蓝图图表，你可以在这个图表中看到我们要实现的一些空事件。

**奖励**

奖励是一种反馈机制，可以告知代理行动是好是坏。获得积极的奖励时，代理很有可能在未来采取这种行动；获得消极的奖励（即惩罚）时，代理可能不会在未来采取这种行动。通过调整行动的概率，驾驶代理可以学习在赛道的每个位置上采取正确的行动。奖励的设置方法与观察和行动相似。

首先，我们要找到样条组件，以便在接下来的逻辑中引用样条。我们可以在组件的**开始运行**事件中找到它，如下所示：

将**获取类的 Actor** 节点的 **Actor 类**引脚设为 “BP_SportCarTrackSpline”，然后从**设置 Track Spline（Set Track Spline）**节点创建一个变量。

在**奖励设置（SetupRewards）**期间，我们定义了代理可以在游戏过程中获得的奖励。对于驾驶车辆这个例子来说，我们要实现两种行为：让车辆以最快的速度行驶和确保车辆永远不会偏离赛道。这可以通过为车辆在样条上的速度提供奖励和在偏离赛道的情况下施加惩罚来实现。添加设置奖励的的代码，具体如下：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5vXzaF5Uicj1Nx30oNFDcmrMT8AK1n44rZNxiajlMolp1PRkH8cvTsadw/640?wx_fmt=png)

 _* 点击 “阅读原文” 查看完整蓝图_

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5ABCrNBNtSCHhgycYgHzDHjNHFHAWpN85bcQQVYicQCx5w2d2icdgbyyw/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

确保为所有三个**设置**节点创建变量。

声明奖励后，我们可以通过代码来填充它们的值。在 Learning Agents 中，奖励将在回合的每一步通过 “设置奖励（SetRewards）” 事件赋予。下列代码可以收集车辆在样条上的速度和偏离赛道的惩罚：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5dhKrfgVu8gyicOAvicl0ET9FfZrEUjjApPnibscmz8X5B5wC5Wr5ibibdmQ/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

**完成**

在强化学习中，训练将在多个回合中进行。一个回合是从游戏开始到游戏结束的一系列观察、行动和奖励过程。除了正常的游戏结束条件外（比如：完成比赛），如果代理的状态很糟糕，无法进行有意义的学习，或者状态良好，无法获得进一步奖励，在这些情况下，通常会添加额外的逻辑，尽早结束训练，加快训练过程。对于这个驾驶示例来说，我们要添加可以检测车辆是否偏离赛道的逻辑，尽早结束一个回合。完成分两种类型：**终止**和**截断**。终止用于不可能进一步获得积极奖励的情况——假设代理在未来所有步骤中获得的奖励为零。截断用于想尽早结束回合的情况，代理还有可能继续获得更多奖励，无论是积极的还是消极的。发生截断时，代理将使用其内部对预期奖励的估计来预测最终的总奖励（即回报）。

检测到车辆偏离赛道时，我们将使用终止，因此代理不会再尝试预估未来的奖励。这么做的原因是车辆可能会回到赛道上，开始从速度奖励中获得积极的奖励。这些积极的奖励将抵消并可能超过因车辆偏离赛道而施加的消极惩罚。这就意味着如果使用截断，代理可能无法学习正确的行为。将以下代码添加到训练器中，其中包含设置完成的逻辑，然后在**设置完成（SetCompletions）**期间填充相应的值：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5b6kCwfhVKx4TWwqfNLTC7iaHW3z9jMuen54ApnfNYqiaTFmbW4cFHrhg/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

**重置回合**

最后，训练器还有一项额外任务是在触发代理的完成或达到回合的最长时间时，将代理及其环境重置为初始训练条件。这可以让每个代理重新开始一个训练回合，继续收集训练数据。

在这个例子中，我们不用考虑环境中的任何物体，但我们想把赛车随机传送到赛道上的任意一个位置，然后从这个位置开始练习驾驶。为此，我们将在 Pawn 上实现一个函数，然后从训练器的**重置回合（ResetEpisodes）**事件调用这个函数。

打开 **SportsCar_Pawn** 蓝图。在左侧添加一个新的函数，命名为

“ResetToRandomPointOnSpline”：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5KpMWt2HQXrTs3RgPanW5JuPMWqy583HlwpnqImjagC6m4jDBSXhddA/640?wx_fmt=png)

_如何使用编辑器中的函数面板添加 ResetToRandomPointOnSpline。_

使用下列代码填充函数：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5CVLDBZwSXuX5VJoffMnFjkTfvn7rp5Tl7jNsOILv1jajyU3h60W2WQ/640?wx_fmt=png)

__* 点击 “阅读原文” 查看完整蓝图__

设置好这个函数后，返回

“BP_DrivingRLTrainer”，将以下代码添加到**重置回合**事件中：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5lM4jrukaUlnGYDJyr1MUBiaw6ffFOia4nydJyOWr9OOGz1zSoVXewibGA/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

粘贴代码时可能会丢失 “Reset to Random Point…” 节点，请重新在图表中添加这个节点，并按图中所示将它连接起来。

训练器设置完成！现在，它可以就每个代理的行为提供反馈，在代理偏离赛道时结束 / 重置它们的训练。

**Learning Agents 管理器：设置和 Tick**

前面，我们创建了 **LearningAgentsManager**，了解了它在 LearningAgents 中的作用。现在，我们继续来构建管理器的蓝图图表。管理器将利用我们刚刚创建的各种组件来构建实际的训练逻辑。

**开始运行：组件设置**

打开 **BP_RLTrainingManager** 的蓝图图表。在组件面板中添加三个管理器组件：**BP_DrivingInteractor**、**BP_DrivingPolicy** 和 **BP_DrivingRLTrainer**：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5RTbmSBk87XcrmGpL2yyTeaaSPxHAn1CaZN033elxekv6rQCDLxRa0w/640?wx_fmt=png)

_三个学习管理器组件：策略、训练器、交互器_

在开始运行期间，管理器需要调用每个组件的设置（setup）函数。这些函数将在内部调用我们刚才创建的设置事件。将以下代码添加到管理器中：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5u8QRzL7EJGPmTibz1ibhaiaBImAA5MKAGyhlxZ5lic7sWVPKGibLNcNmicbg/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

注意，**策略设置（SetupPolicy）**函数需要一个神经网络资产。这个资产将存储待训练的实际权重。如果不输入一个资产，这些权重只会存储在内存中，训练完成后就会丢失。我们来创建一个资产，将这些权重存储到磁盘上。在内容侧滑菜单中，右键单击并选择 “其他”->“数据资产”。在选择器窗口选择 **LearningAgents 神经网络（LearningAgentsNeuralNetwork）**，将它命名为 “DA_DrivingNetwork”。保存这个资产，返回管理器。通过下拉菜单，用我们刚刚创建的资产填充“神经网络资产（NeuralNetworkAsset）” 引脚：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5PYa61gBEa6N5zKVLoibgGKOrsBpvbLkxCehKYFbiblNBYsRTthJvfFWg/640?wx_fmt=png)

_神经网络资产引脚被设为我们刚刚创建的数据资产。_

至此，初始设置就完成了。策略和训练设置对象中还有很多设置可以调整，但是我们可以保留默认值，因为默认值就足够了。

**Tick：学习步骤**

创建好所有组件后，我们需要运行实际的训练步骤。对于这个驾驶示例来说，可以在管理器的 Tick 事件中实现：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5sicZgwsiaVdzbJNXbTicEJC3xvpEUib2zGiaVduicK2Ywusc5dK4afXNmstA/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

复制代码并创建缺失的变量。同样，使用默认值就行。

深入了解各种组件 API 之后，你会发现 Learning Agents 具有很大的灵活性，但是在这个教程中，我们可以使用**运行训练（RunTraining）**功能。这个函数会在后台调用我们之前编写的所有必要的数据操作代码：**设置观察**、**获取行动**、**设置奖励**和**设置完成**。每次调用**运行训练**，观察和行动都会被缓存，直到收集完整的回合。一个回合完成后，它的数据将与一个基于 python 的训练过程共享，虚幻引擎会在后台预热。随着训练开始，最新的网络权重将被同步，以便使用最新版本的策略收集更多经验。

**结尾工作**

现在，强化学习需要的组件已经全部到位，但是我们还需要做一些调整，以确保训练成功。由于行动是使用模拟物理实时发生的，我们需要留出一些时间，以便行动有时间影响游戏状态。这很容易实现，只需要降低管理器的 Tick 速率——这可以有效控制代理做决定的频率。在管理器的蓝图中，单击窗口顶部的类默认值按钮，将 **Actor->Tick 间隔（秒）**设为 **0.1**。这样就可以留出足够的时间，让油门、刹车和转向行动对游戏状态产生有意义的影响。同样，在管理器的蓝图中，将**代理最大数量（MaxAgentNum）**属性设为 **32**，这样就可以使用多个代理进行训练：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC59QVFQCjEgy1ekklNw5lxoEDtPqnHakXib13KZLteGwyI0mYWI4BWjQg/640?wx_fmt=png)

_Learning Agents 管理器的 Actor Tick 面板显示不同的 Tick 速率和代理最大数量。_

接下来，从环境中收集数据的速度将成为训练的瓶颈。提升数据收集速度最简单的方法是从更多的代理中收集数据。由于我们已经增加**代理最大数量**，我们只需要在地图上放置更多的驾驶代理。找到 **SportsCar_Pawn**，在地图上放置更多的代理。32 个应该不错。在地图上放置 31 个代理，最后的代理将由虚幻引擎的游戏开始逻辑生成。最后生成的代理就是你在编辑器中运行期间，在视口中看到的车辆。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5FGgE1m6GM0GWnoLcyjaEol9sNN7cP0DI5aENPJhYUjv5rfcM47CVkQ/640?wx_fmt=png)

_添加到赛道上的 31 辆车都将作为代理。_

默认情况下，车辆之间会相互碰撞。为了简单起见，我们要禁用这种碰撞。打开 **SportsCar_Pawn** 蓝图，在类默认的碰撞部分，将**碰撞预设**改为**自定义**，然后单击复选框，忽略车辆碰撞：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5Z5xzAEUXXsdWZ8FgyqZiclOHOH7tLulIL29MJAsiaSFYHQLZyI6nZGicg/640?wx_fmt=png)

_跑车 Pawn 的碰撞面板显示车辆碰撞已关闭。_

**训练**

至此，设置工作已全部完成。保存所有内容，以免丢失。训练大约需要 **15 分钟**才能看到明显的进步，大约 **2 小时**后，车辆就可以完成训练。为了继续使用你的工作站，你应该让编辑器全速工作，即便它没有聚焦。打开编辑器偏好设置，关闭**处于背景中时占用较少 CPU**：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5Ap8ChB55iasJeDFmXwyjL9Q4Iric8tSuW2V9T6YDERR1HQPYjhekYdzA/640?wx_fmt=png)

_编辑器偏好设置显示 “处于背景中时占用较少 CPU” 已被禁用。_

更改这项设置后，点击运行按钮开始训练。获得满意的训练结果后，就可以停止运行。经过训练的权重将保存在我们创建的 **DA_NeuralNetwork** 资产中。编辑器会将这个资产标记为脏，保存这个资产，从而将权重保存到磁盘上。

如果想停止训练，然后从之前训练过的权重开始恢复训练，需要在管理器中中关闭**运行训练**节点上的**重新初始化策略网络（Reinitialize Policy Network）**引脚：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5097J6XG27icS958lf7xKj0dDCKTGkhadfDUFicLLkvjfzdaec17wLJbg/640?wx_fmt=png)

_运行训练节点显示 “重新初始化策略网络” 已被禁用。_

__* 点击 “阅读原文” 查看完整蓝图__

如果**神经网络资产**中存储了预训练权重，然后在**重新初始化策略网络为 True** 的情况下重新启动关卡，现有的权重将会被覆盖，因此在修改这项设置时要小心。如果这种情况是不小心导致的，并且想恢复以前的权重，你可以关闭并重新打开编辑器，**不要保存**神经网络数据资产。

开始训练后，最好检查一下输出日志，看看有没有警告或错误。如果一切正常，每隔一段时间你可能会看到类似的日志消息：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5FV1PcORcxrLmFnIS1dzAC9QicugycwN01JnVnkaThhmcFn4umLMH4VA/640?wx_fmt=png)

_日志示例：显示训练过程中的通知。_

随着时间的推移，平均奖励和平均回报值会增加，行为会逐渐改善。

**推断**

获得完全训练好的模型后，你可以在推断模式下运行这个模型，使用训练好的行为。这就是运行模型的方式，然后你就可以把它应用到你的游戏中。推断时不使用 Python，所有神经网络代码完全在虚幻引擎游戏进程中运行。以**发行**模式打包和构建游戏时，应用程序中不包含任何训练代码。

运行推断的一种简单方法是创建第二个管理器。在内容侧滑菜单中，复制现有的管理器（只需复制 / 粘贴），重新命名为

“BP_InferenceManager”。删除高亮显示的部分：训练组件、设置和**运行训练**。

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5fHb0HPlVscicNfjkicOQZZbjmszW3BrbtibD7bSSOl5Zliaz5ApTx8dKVQ/640?wx_fmt=png)

_红色高亮部分待删除的 Learning Agents 管理器。_

_* 点击 “阅读原文” 查看完整蓝图_

完全移除训练器后，我们可以在 Tick 事件期间从策略中调用**运行推断（RunInference）**函数：

![](https://mmbiz.qpic.cn/mmbiz_png/s2uc3bvmFVDypEu9qscLrJnTAs6ZPhC5bwE6iaZeWlfStFDddicjf9Pz2v2HBM648xFJc5YicJXAxoP2XpkxaMNSA/640?wx_fmt=png)

_* 点击 “阅读原文” 查看完整蓝图_

将训练管理器从关卡中移除，将推断管理器放到关卡中。点击运行按钮后，你就看到所有车辆沿着赛道移动到随机位置并开始行驶。

**下一步**
=======

完成本教程的学习后，你将可以训练自己的强化学习代理。在这个教程中，我们介绍了 Learning Agents 蓝图 API 的大部分内容，这些内容都可以在 **C++** 中访问。建议大家自己去了解一下我们没有讲到的很多其他观察、行动和奖励。

在训练足够长的时间后，你可能会发现，车辆无法学习逼真的赛车路线。再回来看一下我们的奖励函数，车辆会试图在样条上最大限度地提高速度，但这并不能 100% 转化为在赛道上以最快的速度前进。你可以挑战一下是否能提高奖励，更准确地反映出预期效果并分享你的结果！

![](https://mmbiz.qpic.cn/mmbiz_jpg/s2uc3bvmFVCUOYtc43hqj5OlLs1INNkFAMlbo6pSKa1WPhVwUL6twoveF9w1fUNlmk7ahiaRUbcbFRkIyNHU1TA/640?wx_fmt=jpeg)  

> **近期焦点**

[虚幻引擎 5.3 现已发布！](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650673488&idx=1&sn=f096a5307224ce9c578060c85d806a0c&chksm=83edb617b49a3f010cf59205e7aba1cb5cc9ff65f29811b341e3c4c15a27325cdba310527997&scene=21#wechat_redirect)

[虚幻引擎 5.2 现已发布！](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650669967&idx=1&sn=d9ac536182889706734ce10f5f2bd2ab&chksm=83eda4c8b49a2dde4e138d2ef8a0273b5597cc26ba712868fe371c9a1801f227fc8098f6179f&scene=21#wechat_redirect)

[MetaHuman  Animator 现已开放下载](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650671035&idx=1&sn=3f931afdf56a5a3d26eb2100a913fc28&chksm=83eda0fcb49a29ea71393e244ecf538ad6e9170c04ff4bf433f42db5113dc9ffa201e0542efa&scene=21#wechat_redirect)

[GDC 2023](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650668167&idx=1&sn=b38929ca9af0c26b950832e6c1541172&chksm=83ee5bc0b499d2d60908985a552b8c8d6d91278bf614dc62010629d49b7d6670d606c28897e3&scene=21#wechat_redirect)

[深入了解 Epic 在 GDC 2023 上发布的公告](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650668900&idx=1&sn=7a79db905b2d826dd4ae3d342c436587&chksm=83ee5823b499d135996d9d76cd27ebe019804a0ccd251963dc5c5c7d62193b99e0d864cf3313&scene=21#wechat_redirect)

[Epic MegaGrants：2022 年更新](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650667214&idx=1&sn=c4fb32343cf0f0ca1b00f0fcb6772fd8&chksm=83ee5f89b499d69f902d3470ce61c0140323fe64e47dc7d1b3ffadf06817347fc6ce8c172cbd&scene=21#wechat_redirect)  

[虚幻开发者闪耀 TGA 2022](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650667435&idx=1&sn=8804532c14d1d11ee4cacdecebae975a&chksm=83ee5eecb499d7facd085ba87650043eae7d0e3b92b023e7e4a4f8e3829cece55fd43b2a6511&scene=21#wechat_redirect)  

[技术赋能各行业！Unreal Open Day 2022 圆满落幕](http://mp.weixin.qq.com/s?__biz=MzAxNzMzODkyMA==&mid=2650666517&idx=1&sn=2a90b96e54239be575d8344b00a3bbec&chksm=83ee5152b499d844a6f255345a64773cccb29806e3345cd294493b481ff7f37bfd1aaad18d86&scene=21#wechat_redirect)

![](https://mmbiz.qpic.cn/mmbiz_jpg/s2uc3bvmFVCUOYtc43hqj5OlLs1INNkFAMlbo6pSKa1WPhVwUL6twoveF9w1fUNlmk7ahiaRUbcbFRkIyNHU1TA/640?wx_fmt=jpeg)

扫描下方二维码，关注后点击菜单栏按钮 “更多内容” 并选择 “联系我们” 获得更多虚幻引擎的授权合作方式和技术支持。

![](https://mmbiz.qpic.cn/mmbiz_jpg/s2uc3bvmFVCUOYtc43hqj5OlLs1INNkFILNR8BezN3ftOFZhocGvQkWhjBY2RNpXDOLty50KicIyVUN7KW8fXEQ/640?wx_fmt=jpeg)

**长按屏幕选择 “识别二维码”** **关注虚幻引擎**

**“虚幻引擎” 微信公众账号是 Epic Games 旗下 Unreal Engine 的中文官方微信频道，在这里我们与大家一起分享关于虚幻引擎的开发经验与最新活动。**