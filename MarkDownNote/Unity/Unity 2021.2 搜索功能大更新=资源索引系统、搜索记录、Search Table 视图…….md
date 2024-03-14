> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247537141&idx=1&sn=a6f291cd02bc4d7e5a1791e916ed710b&source=41#wechat_redirect)

过去一年里，Unity 的搜索功能经历了极大的转变。除了能按名称查找对象的 **Quick Search** 包，还有更为精细的**核心搜索功能**，你将能保存搜索结果、查看结果详情，并使用类似 LINQ 的语言来发起复杂的搜索。

自 2021.1 版本首次推出的 Search 已然成为许多 Unity 用户必用的功能，**内置于编辑器内的搜索功能**无须安装额外软件包就能投入使用。

你可以输入字符来搜索对象并进行操作，也能发起更为复杂的搜索，发挥工具的潜力。在 Unity 2021.2 的新版本中，搜索功能迎来了一系列的重大改进，保证用户能维持高生产力。请在下文详细了解本次更新。

* 注意，Quick Search 目前有一版实验性版本可兼容 2020.3，并包含了几乎所有的核心功能。要安装最新的预览包，请打开 Project Settings，找到并启用 Preview Packages 选项。

**改进后的数据排列**

今天的 Asset Indexing System（资源索引系统）要比以往更为强劲。初次排列现在不仅占用更少的时间和空间，而且还支持在 **Index Manager**（Window > Search > IndexManager ）中自定义设置来扩充索引的信息量。

![](https://mmbiz.qpic.cn/mmbiz_jpg/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNQGJm7gcvhxib5Dnr6XpHXC4vI5PhTIHvpm3ys9Z2ricHtEacMbvib1pBw/640?wx_fmt=jpeg)

如果像上方一样启用列表中的 Properties 和 Dependencies，你就可以更充分地利用新的 Search Picker 和 Table。

**搜索记录组织**

另一个重大改进位于超级好用的搜索记录（Save Searches）功能里。我们很清楚重复地搜索是多么可恼，所以我们为搜索记录加了新的组织选项。

![](https://mmbiz.qpic.cn/mmbiz_jpg/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNLoRVG5ibmiaY6hJ5kp089JaMBl7Py1WfXOhOVlseyXs4dbhrLCh9xseg/640?wx_fmt=jpeg)

新选项包括：只显示在用户个人页面的 **User Searches**（保存为偏好设置），及与所有项目参与人共享的 **Project Searches** （保存为项目资源）。你可以为结果设置图标，并在新窗口中打开搜索结果。搜索窗口的状态将被保留，搜索文本、图标大小（特别是 Table 布局）和打开的搜索栏将始终被恢复。

**Search Table 视图**

搜索窗口允许以多种方式可视化对象，包括列表、大图标列表及多种尺寸的块状视图，如下图所示。

![](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNX4FlsZX2p4VXUs8TSz8dYGiajP1YXp0wu3sbVDWcWfMJUuEP9DAYqgQ/640?wx_fmt=gif)

Unity 2021.2 支持在 Table 中可视化查询结果：

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNLmoROtp1XZ6uIEMlxlaBqb3FwB7dz8ACV2z0HLozbfN31vPRY5UNmw/640?wx_fmt=png)

你可以按名称或描述来进行排序，甚至能用 Search Expression（搜索表达式）来提取文件属性，生成类似下方的列表：

_https://github.com/Unity-Technologies/com.unity.search.extensions/wiki/Blog-Search-21.2#search-expressions_

[视频详情](javascript:;)

**Search Picker**

该功能更能满足高级 Unity 用户的需求。Unity 现在支持用搜索窗口代替旧方法来选取资源、对象或其他内容，让选取更加精确。你可以在代码中指明搜索所涉及的脚本属性。

先为任意参考属性加上 **[SearchContextAttribute]** 特性，再指定每次搜索的 **Search Provider**，来发起一次范围更小的初始搜索，或设定 Search View Flags 来更改 Search Picker 的外貌。

[SearchContextAttribute]：

_https://docs.unity3d.com/2021.2/Documentation/ScriptReference/Search.SearchContextAttribute.html_

Search Provider：

_https://docs.unity3d.com/2021.2/Documentation/ScriptReference/Search.SearchProvider.html_

```
public class Weapon : MonoBehaviour
{
    [SearchContext("_t:texture width>=1024 -png -lightmap_",
                                    SearchViewFlags.GridView, "asset")]
    public Texture2D icon;
    public int damage;

```

上方设定看起来会像这样：

![](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNxA1nt2grsvcuXD5Ujm6IcAVYb6KQZZPK1Zyb7whBTxaU1sSfNLibLicQ/640?wx_fmt=gif)

注意，在 Search Picker 视图默认带有一种网格图的搜索设置。

**搜索表达式**

最后，我们加入了搜索表达式的概念。搜索表达式可让搜索字符更为强大、个性化。那它究竟能帮你做些什么呢？

_**01**_  你能用它来发起一次交叉引用多个 Search Provider 的搜索，或同时发起多次搜索。

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xetKrOdgwKnm6kwfxy2FODI8gfeQZyt85JM94Y1nCycRHBdega5z2p1N5MO8ariaZ1QMKVITlR4iaeA/640?wx_fmt=png) 比如说，显示当前场景中所有着色器无法编译的对象。

_**02** _ 在搜索中转换和筛选结果，表达式非常像 LINQ 加上 SQL 加上 Lisp（S-Expression 句法）。

 ![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xetKrOdgwKnm6kwfxy2FODI8gfeQZyt85JM94Y1nCycRHBdega5z2p1N5MO8ariaZ1QMKVITlR4iaeA/640?wx_fmt=png) sort{count{...groupby{a:assets, @type}}, @value, desc}

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xetKrOdgwKnm6kwfxy2FODI8gfeQZyt85JM94Y1nCycRHBdega5z2p1N5MO8ariaZ1QMKVITlR4iaeA/640?wx_fmt=png) select{t:LODGroup, @lodsize}

_**03** _ 如果在 Search Table 中使用，你就能发起复杂的搜索，并将结果列为表格。Search Expression 可用作长期集成或验证系统的基础。

Search Table：

_https://docs.google.com/document/d/1MSCfgioubn6NwWTYZqorVYeF3FfeXYJ0d2AZXepGacE/edit#heading=h.noyflehpbuz9_

当然 Search Expression 的句法非常多，你可能会在搜索时用到以下内容：

查找所有带有 “rock” 纹理的预制件：

**t:prefab ref={t:texture rock}**

搜索系统将根据 **t:texturerock** 开始查找，再到所有纹理上查找 **t:prefabref=**，最后汇总并显示结果。

查找项目中的资源种类数：

**count{t={distinct{select{a:assets, @type}}}}**

求出项目中所有 LODGroup 配置文件的平均 LODSize：

**avg{select{t:LODGroup, @lodsize}}**

通常大括号就代表着搜索表达式。而前缀 **avg、 select、 distinct** 则表明了搜索结果的处理方法。求值过程运行于 Unity 的后台线程中，无论搜索有多复杂、数据有多大，搜索窗口不会出现无响应情况。

搜索功能同样支持保存非常长的搜索表达式，方便下次使用。

[视频详情](javascript:;)

**反馈及更多**

本文介绍的所有功能都在 Unity 编辑器文档中有说明。

并且，我们还制作了多个搜索功能演示和几种基于 Search 功能打造的原型开发工具，并专程上传到公共 GitHub 仓库内供大家下载使用。 

我们的 Wiki 百科还收录了几篇关于非常不错的搜索功能文章，其中有一篇详细解读了更为精密的搜索表达式。

Query Examples 页面还提供了 2022.1 新搜索功能的预览。

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xdqKFEbTMpwu3FLoDugXNicNLLm8Vhg9IJViaQg0GpZUkiashxK8rMLfnT4SuFha4iaTyicBNntRrcPHgg/640?wx_fmt=png)

欢迎大家下载体验。

[1] Unity 编辑器文档：  

_https://docs.unity3d.com/2021.2/Documentation/Manual/search-usage.html_

[2] 搜索功能演示：

_https://github.com/Unity-Technologies/com.unity.search.extensions/wiki/Query-Examples  
_

[3] 原型开发工具：  

_https://github.com/Unity-Technologies/com.unity.search.extensions/wiki/Dependency-Viewer_

[4] 公共 GitHub 仓库：  

_https://github.com/Unity-Technologies/com.unity.search.extensions_

[5] 搜索功能文章：

_https://github.com/Unity-Technologies/com.unity.search.extensions/wiki/Blog-Search-21.2_

[6] 搜索表达式：

_https://github.com/Unity-Technologies/com.unity.search.extensions/wiki/Search-Expressions_

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGia3ibXvfribSG3BEumwiakOoXOmvbw1a7icDGWF8wMoicDZqMko9kichBLEYug/640?wx_fmt=png)

[![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xciaWqWgEUqGBDibuQiaeibfydicvF6x0Ig2Biag9yGR8nbjsHnhoK8zJ66tmI24IJJqbJwPpSYT7R4B8Ig/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzU5MjQ1NTEwOA==&mid=2247537014&idx=1&sn=0598baf23fc426a954701169617d9c60&chksm=fe1d65ddc96aeccb43df468260339c07c1c9aadd7195e7ec7a827ec18da2747d0f48b91f6720&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xfYiaabcPqbbchd6eTuJLicBT2OxWMqiaElqUrwcv6f1ib1vw9oPEcwIr5IuveC1ZcOZogz5MZWSBpRMw/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzU5MjQ1NTEwOA==&mid=2247534995&idx=2&sn=47acf916f4a4691f26c43d3622258f85&chksm=fe1d7d38c96af42eaec10183c9869de236bf78dfe9eb81a82c0f2c36eed79e41c278d0fec271&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xep6bwprVYLicSVI20OASsSB4XribcGb0ia4w08wibr0SUhg3YLNtBDnutJNY3FKMPev1txl4SrIoy5EA/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzU5MjQ1NTEwOA==&mid=2247534998&idx=1&sn=9e5b1c966b62fb3bcc8c007da1868a65&chksm=fe1d7d3dc96af42b75127c5496488b2ff43bfa94533c3567ef549632243fc616372f827bd6b3&scene=21#wechat_redirect)

**长按关注**

**Unity 官方微信**

第一时间了解 Unity 引擎动向，学习最新开发技巧

![](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsun6CMe09NXZkcm0GiaWH5X4CPfZTL3Qr1sx7pQSy6M4wpTibnlGgsZCauTnDicQiaSAsB4RhXza2bw/640?wx_fmt=gif)

 每一个 “在看”，都是我们前进的动力 

![图片](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsOlrhMAcw4vJeMyK5jRwBckKrT4zFgAYY4q4uQvK3PH1NDVxrHF45kMQicj1f33oqSBxfulBounQ/640?wx_fmt=gif)