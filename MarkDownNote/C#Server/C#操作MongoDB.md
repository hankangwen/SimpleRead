这篇文章将讲解如何使用C#连接MongoDB数据库，并且读取里面的文档。

[toc]

#### 一、新建项目

新建控制台程序，命名为 “MongoDBDemo”

![image-20220711093059945](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_31_0_image-20220711093059945.png)

#### 二、使用 NuGet 添加 MongoDB.Driver

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_32_33_img.png)

安装完成以后，查看项目的引用，发现 MongoDB 使用到的几个 dll 文件都已经添加到引用中。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_32_55_img.png)

#### 三、代码连接

##### 原始数据

![image-20220711094210132](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_42_10_image-20220711094210132.png)

##### 1.连接方式一

```c#
using System;
using System.Threading.Tasks;
using MongoDB.Driver;
using MongoDB.Bson;

namespace MongoDBDemo
{
    class Program
    {
        protected static IMongoClient _client;
        protected static IMongoDatabase _database;
        static void Main(string[] args)
        {
            // 数据库名称
            string strCon = "mongodb://127.0.0.1:27017/bianchengbang";
            var mongoUrl = new MongoUrlBuilder(strCon);          
            string databaseName = mongoUrl.DatabaseName;
            _client = new MongoClient(mongoUrl.ToMongoUrl());
            _database = _client.GetDatabase(databaseName);

            const string collectionName = "user";   // 集合名称
            var collection = _database.GetCollection<BsonDocument>(collectionName);
            var filter = new BsonDocument();
            var list = Task.Run(async () => await collection.Find(filter).ToListAsync()).Result;
            list.ForEach(p =>
            {
                Console.WriteLine("姓名：" + p["name"].ToString() + ",电话:" + p["phone"].ToString());
            });

            Console.ReadKey();
        }
    }
}

```

##### 2.连接方式二

（1）在配置文件中添加 MongoDB 数据库的连接字符串

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_48_46_img.png)

代码：

```c#
using System;
using System.Threading.Tasks;
using MongoDB.Driver;
using MongoDB.Bson;
using System.Configuration;

namespace MongoDBDemo
{
    class Program
    {
        protected static IMongoClient _client;
        protected static IMongoDatabase _database;
        static void Main(string[] args)
        {
            // 数据库名称
            string strCon = ConfigurationManager.ConnectionStrings["mongodbConn"].ConnectionString;
            var mongoUrl = new MongoUrlBuilder(strCon);          
            string databaseName = mongoUrl.DatabaseName;
            _client = new MongoClient(mongoUrl.ToMongoUrl());
            _database = _client.GetDatabase(databaseName);

            const string collectionName = "user";   // 集合名称
            var collection = _database.GetCollection<BsonDocument>(collectionName);
            var filter = new BsonDocument();
            var list = Task.Run(async () => await collection.Find(filter).ToListAsync()).Result;
            list.ForEach(p =>
            {
                Console.WriteLine("姓名：" + p["name"].ToString() + ",电话:" + p["phone"].ToString());
            });

            Console.ReadKey();
        }
    }
}

```

#### 四、结果输出

*![image-20220711094954761](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_9_49_54_image-20220711094954761.png)*

#### 五、拓展知识：连接C#控制台应用的配置文件

##### 1、App.config、**.dll.config 和 vshost.exe.config 作用区别

> vshost.exe.config 是程序运行时的配置文本。
>
> exe.config 是程序运行后会复制到 vshost.exe.config。
>
> app.config 是在 vshost.exe.config 和 exe.config 没有情况起作用，从 app.config 复制到 exe.config 再复制到 vshost.exe.config。
>
> 写配置文件都是写到 exe.config 文件中了，app.config 不会变化。
>
> app.config 只在 exe.config 丢失的情况下在开发环境中重新加载 app.config，vshost.exe.config 和 exe.config 会自动创建内容跟 app.config 一样。
>
> vshost.exe.config 和 app.config 两个文件可不要，但 exe.config 文件不可少。

##### 2、创建配置文件及配置文件数据读取

<img src="https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_0_16_1075697-20200715112717600-1931209378.png" style="zoom:80%;" />

App.config与MongoDBDemo.exe.config内容相同：

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
  <connectionStrings>
    <add name="mongodbConn" connectionString="mongodb://127.0.0.1:27017/bianchengbang"/>
  </connectionStrings>  
    <startup> 
        <supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.7.2" />
    </startup>
  <runtime>
    <assemblyBinding xmlns="urn:schemas-microsoft-com:asm.v1">
      <dependentAssembly>
        <assemblyIdentity name="System.Runtime.CompilerServices.Unsafe" publicKeyToken="b03f5f7f11d50a3a" culture="neutral" />
        <bindingRedirect oldVersion="0.0.0.0-5.0.0.0" newVersion="5.0.0.0" />
      </dependentAssembly>
    </assemblyBinding>
  </runtime>
</configuration>
```

如果带账号密码则为下图所示：

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_2_21_1075697-20200715114214620-31136886.png)

##### 3、读取和修改 appSettings 配置——修改后一定要 Save——修改的是 App.config 编译后的配置文件 dll.config

appSettings：主要存储程序设置，以键值对的形式出现。

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_6_57_1075697-20200715114550923-433931702.png)

修改 appSettings 之前

未 Save，dll.config 配置的 user 是 888

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_7_34_1075697-20200715114704596-94467921.png)

代码中修改 appSettings 之后

没有调用 Save，dll.config 配置中的 user 还是 888。

Save 写之后，dll.config 配置【不是 App.config】的 user 修改为 999。【App.config 并没有改变】

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_8_14_1075697-20200715114654432-1376239694.png)

connectionStrings：由于保存数据连接字符串。

##### 4、读取 connectionStrings 配置

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_9_19_1075697-20200715115042523-313002124.png)

![](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/11_10_9_27_1075697-20200715115052972-1739242973.png)