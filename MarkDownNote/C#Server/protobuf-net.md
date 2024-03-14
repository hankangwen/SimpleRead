> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/30tnwaj4zv739ufFt_4ueQ)

**“** **protobuf 是 google 的一个开源项目，简单的来说，它比 Json，Xml 产生的数据更小，更快速，缺点就是可读可写性差。游戏开发的话一般在网络通讯中会使用。****”**

**以下来自官网的介绍：  
**

> protocol buffers 是一种语言无关、平台无关、可扩展的序列化结构数据的方法，它可用于（数据）通信协议、数据存储等。
> 
>   
> Protocol Buffers 是一种灵活，高效，自动化机制的结构数据序列化方法－可类比 XML，但是比 XML 更小（3 ~ 10 倍）、更快（20 ~ 100 倍）、更为简单。
> 
>   
> 你可以定义数据的结构，然后使用特殊生成的源代码轻松的在各种数据流中使用各种语言进行编写和读取结构数据。你甚至可以更新数据结构，而不破坏由旧数据结构编译的已部署程序。

01

—

Visusl Studio

首先，我们新建一个控制台项目，下载 protobuf-net 的 Nuget 包，下载的方法依次点击工具 ->Nuget 包管理器 -> 管理解决方案的 Nuget 程序包：

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwM0HxPyMeGlX87NoblzQ56bdG3kJvj0QiaFmaqfPKS7C7icsHzpDe8fIaQ/640?wx_fmt=png)

并在搜索框中搜索：“protobuf-net” . 选择好之后，目光转到右边的选项那：  

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwMEea39QZZibTsWKian02iaicicfPSYKjvHiajIPH1KXaeqJh2cKR5YbyVDzVQ/640?wx_fmt=png)

选择你的项目，然后点击安装，等待一会即可安装完成。然后打开 program.cs 文件，开始我们的编写：

引入一个头文件：system.IO;  

```c#
 static void Main(string[] args)
        {
            Hero hero = new Hero
            {
                data = new info
                {
                    age = 27,
                    name = "Vincent",
                    Sex = "男"
                }
            };
            using (var memory = new MemoryStream())
            {
                ProtoBuf.Serializer.Serialize(memory, hero);
                byte[] bytes = memory.ToArray();
                string s = System.BitConverter.ToString(bytes);
                Console.WriteLine(s);
                 s = System.Text.Encoding.UTF8.GetString(bytes);
                Console.WriteLine(s);
                Console.ReadKey();
            }
        }
    }

    [ProtoBuf.ProtoContract]
    public class Hero
    {
        [ProtoBuf.ProtoMember(1)]
        public info data { get; set; }
    }

    [ProtoBuf.ProtoContract]
    public class info
    {
        [ProtoBuf.ProtoMember(1)]
        public int age { get; set; }
        [ProtoBuf.ProtoMember(2)]
        public string name { get; set; }
        [ProtoBuf.ProtoMember(3)]
        public string Sex { get; set; }
    }


```

我们直接运行，即可发现数据转换成 byte[] 的具体信息，以及转换成字符串的效果：

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwMshVACYmfQXfFSVs4w4Oxz0RuRBoSJwl8mQbqpjlb9gNPond4TfMnfQ/640?wx_fmt=png)

那我们就有必要来讲讲这个简单的使用方法了：

首先，类名前必须要加的： [ProtoBuf.ProtoContract]  

类里面成员要加的： [ProtoBuf.ProtoMember(int)]// 这里面数字从 1 开始往后排即可。

在说几个比较常用的元素：enum,List:

```c#
 static void Main(string[] args)
        {
            Hero hero = new Hero
            {
                data = new info
                {
                   ...
                },

                job = Hero.Job.Magister,
                equip = new List<string> { "1", "2", "3" }
            };
            using (var memory = new MemoryStream())
            {
               ...
            }
        }
    }

    [ProtoBuf.ProtoContract]
    public class Hero
    {
        [ProtoBuf.ProtoMember(1)]
        public info data { get; set; }

        [ProtoBuf.ProtoMember(2)]
        public Job job;
        public enum Job
        {
            Magister,
            Swords
        }
        [ProtoBuf.ProtoMember(3)]
        public List<string> equip;

    }

    [ProtoBuf.ProtoContract]
    public class info
    {
       ...
    }


```

打印测试就各位自己测试一下吧。这个没什么技术难度~

02

—  

Unity 

unity 当中的使用方法是要引入 Protobuf-net.dll，接着编写. proto 文件。你可以使用 notepad++，然后使用工具生成. cs 文件。一般会写 bat 文件自动调用生成。好的，接下来我们一步一步看：

首先引入 dll 文件，那么这个文件可以在哪里下载呢？可以去 github 上搜索：“Protobuf-net” ，也可以在此公众号回复： 服务器开发   
里面的第（七） 里面的 protobufTool 就是：

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwMhVulfSXrbMXjfYIZgiapO6mAtJib8Ym9MnicOfh6FhDodSuGVRaWgp3hQ/640?wx_fmt=png)

将 dll 放入 unity 中，你可以新建一个 Plugins 文件夹专门放引入的文件：  

![图片](https://gitcode.net/hankangwen/blog-image/-/raw/master/pictures/2022/07/12_9_59_24_640.png)

然后，我们打开 notepad++, 写入我们的 proto 代码：

```protobuf
message MsgMove{
    optional int32 x = 1;
    optional int32 y = 2;
    optional int32 z = 3;
}

message LoginMsg{
    optional string userName = 1 [default = "vincent"];
    optional string userPsw = 2 [default = "123456"];
}


```

然后文件另存为：LoginMsg.proto 文件，当然，这个名字不是特别的重要。但是我们怎么把它变成 cs 文件到 unity 使用呢？

答案是我们需要自己编写 bat 文件  

```bash
protogen.exe -i:proto\LoginMsg.proto -o:cs\LoginMsg.cs
pause
```

其中 protogen.exe  代表我们要启用的转换程序，-i 代表 “in”，也就是输入的意思。后面的 proto 不是文件，而是文件夹的名字，LoginMsg.proto 放在了这个文件夹中了。-o 代表 “out”, 输出的意思，然后程序暂停，等待用户输入。我们运行一下：  

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwMd5hCrVaprL1u6sx36xg2mSl31xRaZ1IfTgDwBaIRSJy1R9faBVic0gA/640?wx_fmt=png)

生成成功！  

你会在 cs 文件夹中看到一个名为 LoginMsg.cs 的文件，把这个文件原封不动的复制到 unity 中。  

如果你尝试着打开这个文件，你会发现它特别长，而且不好阅读。但这个没关系，我们不用阅读它。直接使用就可以了。  

新建一个 test.cs 脚本，引入头文件：using proto.LoginMsg; 

是的，LoginMsg。  

接下来使用这种结构，和 json 文件类似，生成和解析：

```c#
  private void Start()
    {
        LoginMsg loginMsg = new LoginMsg
        {
            userName = "Jtro",
            userPsw = "99999"
        };

        byte[] bs_proto = Encode_Proto(loginMsg);

        Debug.Log(System.BitConverter.ToString(bs_proto));

        //获取协议名 
        string protoName = loginMsg.ToString();
        //解码
        ProtoBuf.IExtensible m;
        m = Decode_Proto(protoName, bs_proto, 0, bs_proto.Length);
        LoginMsg m2 = m as LoginMsg;
        Debug.Log(m2.userName);
        Debug.Log(m2.userPsw);
    }
    //生成
    public static byte[] Encode_Proto(ProtoBuf.IExtensible msgBase)
    {
        using (var memory = new System.IO.MemoryStream())
        {
            ProtoBuf.Serializer.Serialize(memory, msgBase );
            return memory.ToArray();
        }
    }
    //解析
    public static ProtoBuf.IExtensible Decode_Proto(string protoName, byte[] bytes, int offset, int count)
    {
        using (var memory = new System.IO.MemoryStream(bytes, offset, count))
        {
            System.Type t = System.Type.GetType(protoName);
            return (ProtoBuf.IExtensible)ProtoBuf.Serializer.NonGeneric.Deserialize(t, memory);
        }
    }


```

运行之后，可以在控制台看到效果：

![图片](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aWMliaB8qtsia4I7hxia3jnwMUF7d28Eb7kNbP4F7ytkoTHIqILgunUjGdSq7AQE0fDXTIXeHKZibRbw/640?wx_fmt=png)

上面是加密，下面是解析出来的数据。  
