> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/wzRk6r1pg4x9xX2ZH973Qg)

前言
--

在. NET 应用程序开发中，_JSON_ 序列化和反序列化在对处理数据交换至关重要，也是一项常见任务。如_处理 Web API、配置文件和系统之间的数据交换等场景_。在**.NET** 生态中 _Newtonsoft.Json_ 与 _System.Text.Json_ 是两个用于 _JSON_ 处理的两个重要库。_Newtonsoft.Json_ 多年来一直是标准，而 _System.Text.Json_ 是微软引入作为 _Newtonsoft.Json_ 的高性能替代方案。本文探讨它们的区别、功能、优缺点，希望能帮助您为项目选择最佳选项。

Newtonsoft.Json  牛顿软件. Json
---------------------------

Newtonsoft.Json 由 James Newton-King 开发，多年来一直是 .NET 生态系统中 JSON 序列化和反序列化的首选库。它提供了广泛的功能，并在开发人员中获得了广泛的采用。

_**1、特点**_

*   支持. NET 2.0 及以上版本；
    

*   灵活性高：支持多种数据类型，包括私有字段、只读属性；
    

*   使用广泛且文档也相对丰富；
    

*   编写缩进且易于阅读；
    

_**2、示例**_

```
using Newtonsoft.Json;
// 序列化
string userJson = JsonConvert.SerializeObject(userEntityObject);
// 反序列化
UserEntityObject userEntityObject = JsonConvert.DeserializeObject<UserEntityObject>(userJson);

```

_**3、优点**_

*   丰富的功能集和广泛的自定义选项。
    

*   被广泛采用。
    

*   成熟且久经考验的库。
    

_**4、缺点**_

*   与 System.Text.Json 相比，大型数据集的性能可能会降低。
    

System.Text.Json  System.Text.Json 系统
-------------------------------------

System.Text.Json 在 .NET Core 3.0 及更高版本中引入，是微软内置 JSON 处理库，旨在作为 _Newtonsoft.Json_ 的现代、高性能替代方案。它专注于性能和与 .NET 生态系统的无缝集成，而无法与 Newtonsoft.Json 相同级别的功能和灵活性相比。

_**1、特点**_

*   在. NET Core 3.0 及更高版本上可用；
    

*   默认是强类型转换；
    

*   适用于简单场景；
    

*   有较好的性能与内存利用率；
    

*   内置支持，它与其他 .NET 功能（如 async/await、流和内存管理）无缝集成。
    

_**2、示例**_

```
using System.Text.Json;
// 序列化
string userJson = JsonSerializer.Serialize(userEntityObject);
// 反序列化
UserEntityObject userEntityObject = JsonSerializer.Deserialize<UserEntityObject>(userJson);

```

_**3、优点**_

*   针对性能进行了优化，尤其是在具有大型数据集的场景中。
    

*   .NET Core 和 .NET 5+ 中的内置支持，无需额外的依赖项。
    

*   与其他 .NET 功能无缝集成。
    

_**4、缺点**_

*   与 Newtonsoft.Json 相比，功能不那么丰富，缺少一些高级自定义选项。
    
*   与 Newtonsoft.Json 相比，社区支持有限，资源更少。
    

功能比较
----

System.Text.Json 提供了速度和效率，但它缺少 Newtonsoft.Json 提供的一些高级功能。如果您需要动态 JSON 处理或自定义序列化规则，Newtonsoft.Json 更灵活。

<table data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><thead data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><th data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"></th><th data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">System.Text.Json&nbsp;&nbsp;System.Text.Json 系统</th><th data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">Newtonsoft.Json&nbsp;&nbsp;牛顿软件. Json</th></tr></thead><tbody data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">内置支持</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">是. NET 的一部分</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">需要 NuGet 包引用</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">LINQ to JSON （JObject）&nbsp;&nbsp;LINQ 到 JSON （JObject）</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">不可用</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">完全支持</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">&nbsp;动态 JSON （JToken）</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">不支持</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">完全支持</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">自定义转换器</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">&nbsp;有限</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">更强大</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">参考处理</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">有限</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">支持循环引用</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">JSON 注释</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">&nbsp;不支持</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">完全支持</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="250" width="250" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">序列化格式</td><td data-colwidth="198" width="198" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">WriteIndented =true&nbsp;&nbsp;WriteIndented = 真</td><td data-colwidth="200" width="200" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">Formatting.Indented&nbsp;&nbsp;格式. 缩进</td></tr></tbody></table>

性能比较
----

性能是微软引入 System.Text.Json 的主要原因之一。它专为高速序列化 / 反序列化和降低内存开销而设计。

<table data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><thead data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><th data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><br data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"></th><th data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">System.Text.Json&nbsp;&nbsp;System.Text.Json 系统</th><th data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">Newtonsoft.Json&nbsp;&nbsp;牛顿软件. Json</th></tr></thead><tbody data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">序列化速度</td><td data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">针对 .NET 进行了优化，更快</td><td data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">由于附加功能而变慢</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">内存使用情况</td><td data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">较低</td><td data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">较高</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">反序列化速度</td><td data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">更快</td><td data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">稍慢</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">区分大小写</td><td data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">默认区分大小写</td><td data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">不区分大小写</td></tr><tr data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0"><td data-colwidth="164" width="164" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">CamelCase 支持</td><td data-colwidth="273" width="273" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">需要 JsonSerializerOptions</td><td data-colwidth="203" width="203" valign="top" data-immersive-translate-walked="2d885904-863a-4875-b508-ec5f8df1f2b0">默认启用</td></tr></tbody></table>

使用选择
----

_**1、选择 System.Text.Json 的情况**_

*   需要高性能和低内存使用率；
    

*   使用 ASP.NET Core 或 Blazor，它是默认的 JSON 库；
    

*   不需要 JObject 的高级功能；
    

*   需要没有额外依赖项的内置支持；
    

_**2、 选择 Newtonsoft.Json 的情况**_

*   需要动态 JSON 处理（JObject、JToken）；
    

*   需使用复杂或深度嵌套的 JSON 结构；
    

*   需要自定义转换器、引用处理或高级设置；
    

*   需要支持旧版 .NET Framework 版本；
    

小结
--

_Newtonsoft.Json_ 和 _System.Text.Json_ 都是 .NET 生态中功能强大的 _JSON_ 处理库，每个库都有自己的一组功能、优点和缺点。可根据项目要求、性能注意事项和所需功能集等因素选择。希望本文对您有所收获，如有不到之处, 请多多包涵。