[toc]
#### 1.连接数据库

要连接数据库，首先需要指定要连接的数据库名称，如果数据库不存在的话，MongoDB 则会自动创建它。下面通过简单的代码来演示如何使用C#代码连接 MongoDB 数据库：

```c#
using System;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");

            IMongoDatabase database = mongoClient.GetDatabase("myDB");
            Console.WriteLine("Credentials ::" + credential);

            Console.ReadKey();
        }
    }
}
```

编译并运行上面的程序，即可创建名为“myDb”的数据库，并输出如下所示的内容：

Connected to the database successfully!
Credentials ::myDb@sampleUser

#### 2.创建集合

若要创建集合，您可以使用 com.mongodb.client.MongoDatabase 类的 createCollection() 方法，示例代码如下：

```C#
using System;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");

            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            database.CreateCollection("tutorial");
            Console.WriteLine("Create collection successfully!");

            Console.ReadKey();
        }
    }
}

```

编译并运行上面的程序，运行结果如下所示：

Connected to the database successfully!
Create collection successfully!

#### 3.获取/选择集合

要获取/选择数据库中的集合，您可以使用 com.mongodb.client.MongoDatabase 类的 getCollection() 方法，示例代码如下：

```C#
using System;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");

            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            database.CreateCollection("tutorial2");
            Console.WriteLine("Create collection successfully!");

            const string collectionName = "tutorial2";
            var collection = database.GetCollection<BsonDocument>(collectionName);
            Console.WriteLine("Select collection tutorial2 successfully!");

            Console.ReadKey();
        }
    }
}

```

编译并运行上面的程序，运行结果如下所示：

Connected to the database successfully!
Create collection successfully!
Select collection tutorial2 successfully!

#### 4.插入文档

想要向集合中插入文档，您可以使用 com.mongodb.client.MongoCollection 类的 insert() 方法，示例代码如下：

```c#
using System;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);
            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            const string collectionName = "tutorial3";
            database.CreateCollection(collectionName);
            Console.WriteLine("Create collection successfully!");

            var collection = database.GetCollection<BsonDocument>(collectionName);
            Console.WriteLine("Select collection successfully!");

            BsonDocument document = new BsonDocument("title", "MongoDB")
                .Add("description", "database")
                .Add("likes", 100)
                .Add("url", "www.bianchengbang.net")
                .Add("by", "编程帮");
            collection.InsertOne(document);
            Console.WriteLine("Insert document successfully");

            Console.ReadKey();
        }
    }
}
```

Create collection successfully!
Select collection successfully!
Insert document successfully

#### 5.查询文档

想要查询集合中的文档，您可以使用 com.mongodb.client.MongoCollection 类的 find() 方法，此方法会返回一个游标，因此想要查询集合中的所有文档您只需要不断迭代此游标即可，示例代码如下：

```c#
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");

            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            const string collectionName = "tutorial3";
            var collection = database.GetCollection<BsonDocument>(collectionName);
            Console.WriteLine("Select collection successfully!");

            BsonDocument document1 = new BsonDocument("title", "MongoDB")
                .Add("description", "database")
                .Add("likes", 100)
                .Add("url", "www.bianchengbang.net")
                .Add("by", "编程帮");
            BsonDocument document2 = new BsonDocument("title", "html")
                .Add("description", "database")
                .Add("likes", 200)
                .Add("url", "www.bianchengbang.net/html")
                .Add("by", "编程帮");
            List<BsonDocument> list = new List<BsonDocument>();
            list.Add(document1);
            list.Add(document2);
            collection.InsertMany(list);

            var filter = new BsonDocument();
            var list2 = Task.Run(async () => await collection.Find(filter).ToListAsync()).Result;
            list2.ForEach(p =>
            {
                Console.WriteLine(p);
            });

            Console.ReadKey();
        }
    }
}
```

Connected to the database successfully!
Select collection successfully!
{ "_id" : ObjectId("62cb94d1c6343689168a3979"), "title" : "MongoDB", "description" : "database", "likes" : 100, "url" : "www.bianchengbang.net", "by" : "编程帮" }
{ "_id" : ObjectId("62cbbcc68b693b007da230d9"), "title" : "MongoDB", "description" : "database", "likes" : 100, "url" : "www.bianchengbang.net", "by" : "编程帮" }
{ "_id" : ObjectId("62cbbcc68b693b007da230da"), "title" : "html", "description" : "database", "likes" : 200, "url" : "www.bianchengbang.net/html", "by" : "编程帮" }

#### 6.更新文档

要更新（修改）集合中文档的数据，您可以使用 com.mongodb.client.MongoCollection 类的 updateOne() 方法，示例代码如下：

```c#
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");
            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            const string collectionName = "tutorial3";
            var collection = database.GetCollection<BsonDocument>(collectionName);
            Console.WriteLine("Select collection successfully!");

            var filter = Builders<BsonDocument>.Filter.Eq("title", "html");
            var update = Builders<BsonDocument>.Update
                .Set("likes", 520)
                .CurrentDate("lastModified");
            collection.UpdateOne(filter, update);
            Console.WriteLine("Update document successfully!");

            var filter2 = new BsonDocument();
            var list = Task.Run(async () => await collection.Find(filter2).ToListAsync()).Result;
            list.ForEach(p =>
            {
                Console.WriteLine(p);
            });

            Console.ReadKey();
        }
    }
}
```

Connected to the database successfully!
Select collection successfully!
Update document successfully!
{ "_id" : ObjectId("62cb94d1c6343689168a3979"), "title" : "MongoDB", "description" : "database", "likes" : 100, "url" : "www.bianchengbang.net", "by" : "编程帮" }
{ "_id" : ObjectId("62cbbcc68b693b007da230d9"), "title" : "MongoDB", "description" : "database", "likes" : 100, "url" : "www.bianchengbang.net", "by" : "编程帮" }
{ "_id" : ObjectId("62cbbcc68b693b007da230da"), "title" : "html", "description" : "database", "likes" : 520, "url" : "www.bianchengbang.net/html", "by" : "编程帮", "lastModified" : ISODate("2022-07-11T06:50:03.421Z") }

#### 7.删除文档

想要从集合中删除文档，您可以使用 com.mongodb.client.MongoCollection 类的 deleteOne() 方法，示例代码如下：

```c#
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");
            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            const string collectionName = "tutorial3";
            var collection = database.GetCollection<BsonDocument>(collectionName);
            Console.WriteLine("Select collection successfully!");

            var filter = Builders<BsonDocument>.Filter.Eq("title", "MongoDB");
            collection.DeleteOne(filter);
            Console.WriteLine("Delete document successfully!");

            var filter2 = new BsonDocument();
            var list = Task.Run(async () => await collection.Find(filter2).ToListAsync()).Result;
            list.ForEach(p =>
            {
                Console.WriteLine(p);
            });

            Console.ReadKey();
        }
    }
}
```

Connected to the database successfully!
Select collection successfully!
Delete document successfully!
{ "_id" : ObjectId("62cbbcc68b693b007da230d9"), "title" : "MongoDB", "description" : "database", "likes" : 100, "url" : "www.bianchengbang.net", "by" : "编程帮" }
{ "_id" : ObjectId("62cbbcc68b693b007da230da"), "title" : "html", "description" : "database", "likes" : 520, "url" : "www.bianchengbang.net/html", "by" : "编程帮", "lastModified" : ISODate("2022-07-11T06:50:03.421Z") }

#### 8.删除集合

要从数据库中删除集合，您可以使用 com.mongodb.client.MongoCollection 类中的 drop() 方法，示例代码如下：

```c#
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");
            IMongoDatabase database = mongoClient.GetDatabase("myDB");
            
            const string collectionName = "tutorial";
            Task.Run(async () =>
            {
                await database.DropCollectionAsync(collectionName);
            });
            Console.WriteLine("Drop collection successfully!");

            Console.ReadKey();
        }
    }
}
```

Connected to the database successfully!
Drop collection successfully!

#### 9.列出所有集合

```c#
using System;
using MongoDB.Driver;

namespace MongoDBDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "mongodb://127.0.0.1:27017/bianchengbang";
            MongoClient mongoClient = new MongoClient(connectionString);

            MongoCredential credential;
            credential = MongoCredential.CreateCredential("sampleUser", "myDb", "password");
            Console.WriteLine("Connected to the database successfully!");
            IMongoDatabase database = mongoClient.GetDatabase("myDB");

            var list = database.ListCollectionNames().ToList();
            foreach (var item in list)
            {
                Console.WriteLine(item);
            }

            Console.ReadKey();
        }
    }
}
```

Connected to the database successfully!
tutorial3
tutorial1
tutorial2

