> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg5NzUzNTQwNA==&mid=2247486794&idx=1&sn=04c357342969f01911c19832159be9be&source=41#wechat_redirect)

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6e87aPUbsD0BNg7P8U4XSicyRxoMJ0EfyW7AicHA01D0KBbzQj8icqRjnxkJeUPjSgGUszelErFoMJJg/640?wx_fmt=png)

Roslyn 是微软推出的. net 编译器，Unity 现在也逐渐转向了 Roslyn 编译器。由于 Unity 的封装，大家可能并没有注意到这一更改。也觉得这样的更改似乎对大家的日常工作没有太大的影响。那么今天我们就来聊聊 Roslyn 编译器为我们带来的新玩具之一。看看它是如何帮助我们更加便利，优雅的应对一些工作场景。

我们先来看几个有趣的例子。

**第一个例子**

我们建立了如下基类：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjUkIKpIcUiaOfvOxgPGibfYk5YiaPw1z4QQXvHgVkcBhtgNfEPAtj1N4dg/640?wx_fmt=png)

在这个基类中我们定义了一个空的虚函数 LogInfo。

然后我们继承这个基类，实现了如下类：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjAtckczNcec6KDgF6WExhLQ9s05b5KfjciamyCFv3CiahfJloe09dmxzg/640?wx_fmt=png)

显然，这个类在 Unity 中运行的时候，是不会输出任何信息的。我们的测试结果也是如此：  

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjZboA7zzMnEia6BUrTzWD4mdOhzHSRN9YIzufbVYkIV3ZaIoOlldOHPg/640?wx_fmt=png)

接下来，我们对子类（LogMono）做一点点改动：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjm7oRvg20QJnbViawJKVtTCvGhwczDBWgKF6F857ibY9z2yLVawbEwcxQ/640?wx_fmt=png)

我们增加了一个自定义属性 - Logger。这个属性本身是空的：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjgcFZZPvmxIVQKPorQQNrmrF8ydnP7CSXubw1mupsjuEZia8JTNe8lwQ/640?wx_fmt=png)

接下来我们再次运行 Unity 测试一下，神奇的事情发生了：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjI1764GOIbuOukAfD0zScUfxkrQw8I7uPTIjWKRaib3sBHg6ybK8KgMQ/640?wx_fmt=png)

**第二个例子**

接下来我们看第二个例子，众所周知，在 Unity 中，如果需要把一个类作为 Component 挂到 GameObject 上，那么这个类必须继承自 MonoBehavior 类。

比如我们刚才例子中的 LogMonoBase。如果不是 MonoBehavior 的子类，则会收到一个报错信息。比如，我们创建如下类：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjcjgt4QCPIbeOibibejC3wJXFKQbRyBl1VoibAJuadibfzXVTKDpDiceJbqw/640?wx_fmt=png)

当我们试图挂载的时候会出现报错信息：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjOFsh1q09RqYwE86w6WDeljsSTAZVwDJbgTmsVcw8xiam6iayTFTqFKiag/640?wx_fmt=png)

但如果我创建了一个这样的类，结果就不一样了：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjpFibKwfwS094tBmG409JxHDoBkW9oxpibKyOjae9f6bpEhFQufF4wr9Q/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjMmOyta6n3CNS5eg3qMAQo3QQnZo0YcibOh1rOXjBnRBftVgsJq2sXibQ/640?wx_fmt=png)

就加上了我的名字（ChuanBehavior），然后脚本就神奇的挂上了！难道是内部员工福利吗？

当然不是。

以上两个例子所实现的神奇功能，其实都来自于我们今天的主句，Roslyn 编译器所提供的玩具之一，**Code Generator**。

简单的说，Code Generator 允许用户参与代码的编译期，进行诸如代码动态生成，代码动态修改之类的功能。

我们以上的两个例子，就是通过 Code Generator 实现的，其代码如下：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjpDOlDwB6meOm8HD3iagmLPMCicRwwLgic2RuaHxO8PKCG6TPLlGq3Idmg/640?wx_fmt=png)

第一个生成器中，我们找到所有带有 Logger 属性的类，并且生成了一段代码，用来重载了基类的 LogInfo 函数。

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjDbrpzu6qTGECiaOdht5znTp5dMibef45aHzQKPfksia2vV5oN26SuUZOw/640?wx_fmt=png)

在第二个生成器中，我们找到了所有名字含有 **“ChuanBehavior” 字符**的类，并且动态生成了一段代码，完成了该类与 MonoBehavior 的继承关系。

在 Visual Studio 中将以上代码编译为 dll，并且放到 Unity 的 Asset 目录下。按如下设置进行配置：

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjBicwUFztZapIbHlMsoibLIU994GmM9Z4Oiar5Kl99Q7TlHoibwxFE4hw8w/640?wx_fmt=png)

同时给 dll 加上一个特殊的标签（RoslynAnalyzer）

![](https://mmbiz.qpic.cn/mmbiz_png/mToLbH2dg6cCrsw4icibMHYRjFZz0ZYVcjfAu0LOLwAxoZY4zkQgT6fFuEUiaMODfr3aFPpnw9lCc12ap4qfPthbw/640?wx_fmt=png)

Unity 就会在编译代码的时候，使用这个 dll 参与编译行为。

**Code Generator 带给我们非常强大的代码管理能力**。在进行框架设计的时候，我们可以把一些与业务无关的复杂代码，通过 Code Generator 在编译期动态生成，从而简化业务逻辑的代码书写复杂度。

我们也可以通过 Code Generator 实现一些 AOP 的概念，比如装饰器，使我们的代码更加灵活和优雅易读。

关于 Code Generator 更多详细内容，有兴趣的同学可以参阅微软的官方文档和 Unity 手册的相关内容，进一步学习。祝大家开卷有益！

可以找到 Unity 的方式：  

Unity 社区首页：developer.unity.cn  

Unity 问答专区：unity.cn/ask

Unity 中文课堂：learn.u3d.cn

Unity 技术专栏：unity.cn/articles

**长按关注**

**Unity 官方开发者社区**

第一时间了解技术干货文章和海外热点技术文章

![](https://mmbiz.qpic.cn/mmbiz_jpg/mToLbH2dg6f6KldicYekyLnxib3tjn6vyQOA0cAoWzUicYxjsSTTqcibbkh5mLh2RC2IRx7bicOJaGTrkmGv4F8LIUQ/640?wx_fmt=jpeg)

**往期文章**

[![](https://mmbiz.qpic.cn/mmbiz_jpg/mToLbH2dg6e87aPUbsD0BNg7P8U4XSicy3rmXicONbhYWRLGyE8vtB9MfXvy1iakicwwBKMWibzGg3Yd0pBAI1att8Q/640?wx_fmt=jpeg)](http://mp.weixin.qq.com/s?__biz=MzUxOTAwNzA0MQ==&mid=2247486384&idx=1&sn=b4de94304f042b567e6e6b920089c43a&chksm=f981759ecef6fc887c18f7b665719ee0fc2196387331d4285e1a3b442a89a716c6f0e93d030c&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_jpg/mToLbH2dg6dIfmo6E17Fa4uNqH7hWQ5abzSbIfuna1Whw0JvVFmaibPicECXOuyAia0bWOwUxjWVgf9X043oGz1IQ/640?wx_fmt=jpeg)](http://mp.weixin.qq.com/s?__biz=MzUxOTAwNzA0MQ==&mid=2247486506&idx=1&sn=2f40c4f3031821dd61b5bb0e519d3f3d&chksm=f9817204cef6fb12d61e5fa438f4ba7c9390f003588c7f433da6ee2a675dd79b52b0b7574759&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_jpg/mToLbH2dg6e87aPUbsD0BNg7P8U4XSicyxpNYgO4NDvsDa7oClUng1eoCzTaico13N9HpXG2JS2U6jB4hqmlbn4w/640?wx_fmt=jpeg)](http://mp.weixin.qq.com/s?__biz=MzUxOTAwNzA0MQ==&mid=2247486569&idx=1&sn=89ad29f1ee4d5318059aa1386e95fca2&chksm=f9817247cef6fb51b8c386b1f71cb115c3314e777382575c983c7fb48662cf867e8bfd71631b&scene=21#wechat_redirect)