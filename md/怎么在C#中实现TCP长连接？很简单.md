> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/o45shnJzNECviQflq_HmGw)

有群友问怎么在 C# 中实现 TCP 长连接？本文将浅析这个话题。在 C# 中实现 TCP 长连接通常涉及使用 Socket 编程。在网络编程中，TCP 长连接是一种重要的通信方式，特别是在需要实时数据传输或保持持续连接的应用中。本文将介绍如何在 C# 中实现 TCP 长连接，并提供一个简单而完整的示例，以便读者了解其基本原理和实现方法。

### 什么是 TCP 长连接？

TCP（传输控制协议）长连接是指在客户端和服务器之间建立的持久性连接，可以在多个请求和响应之间保持打开状态。与短连接相比，长连接可以减少连接建立和断开的开销，并提高数据传输的效率。长连接通常用于需要频繁通信或实时数据传输的场景，如在线游戏、聊天应用、实时监控系统等。

### 实现 TCP 长连接的基本步骤

要在 C# 中实现 TCP 长连接，通常需要执行以下步骤：

1.  创建服务器端（Server）：在服务器端监听指定的 IP 地址和端口，接受客户端的连接请求。
    
2.  创建客户端（Client）：在客户端建立与服务器的连接，并进行数据交换。
    
3.  保持连接：在服务器和客户端之间保持持久性连接，以便可以随时进行数据传输。
    
4.  数据交换：在连接建立后，通过网络流（NetworkStream）进行数据的发送和接收。
    

### 示例：C# 中实现 TCP 长连接

以下是一个简单的示例，演示了如何在 C# 中创建一个 TCP 服务器端和客户端，并建立长连接进行通信。

#### 服务器端（Server）

```
using System;using System.Net;using System.Net.Sockets;using System.Text;class TCPServer{    static void Main(string[] args)    {        TcpListener listener = null;        try        {            // 指定服务器IP和端口            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");            int port = 8080;            // 创建TcpListener对象            listener = new TcpListener(ipAddress, port);            // 开始监听            listener.Start();            Console.WriteLine("Server is listening on " + ipAddress + ":" + port);            while (true)            {                Console.WriteLine("Waiting for client connection...");                                // 接受客户端连接                TcpClient client = listener.AcceptTcpClient();                Console.WriteLine("Client connected!");                // 处理连接                HandleClient(client);            }        }        catch (Exception e)        {            Console.WriteLine("Error: " + e.ToString());        }        finally        {            if (listener != null)                listener.Stop();        }    }    static void HandleClient(TcpClient client)    {        NetworkStream stream = client.GetStream();        byte[] buffer = new byte[1024];        int bytesRead;        while ((bytesRead = stream.Read(buffer, 0, buffer.Length)) != 0)        {            string dataReceived = Encoding.ASCII.GetString(buffer, 0, bytesRead);            Console.WriteLine("Received: " + dataReceived);            // 处理客户端发送的数据，这里简单地将收到的数据原样发送回去            byte[] responseData = Encoding.ASCII.GetBytes(dataReceived);            stream.Write(responseData, 0, responseData.Length);        }        // 关闭连接        client.Close();    }}
```

#### 客户端（Client）

```
using System;using System.Net.Sockets;using System.Text;class TCPClient{    static void Main(string[] args)    {        try        {            // 指定服务器IP和端口            string serverIP = "127.0.0.1";            int port = 8080;            // 创建TcpClient对象，并连接服务器            TcpClient client = new TcpClient(serverIP, port);            Console.WriteLine("Connected to server.");            // 获取网络流            NetworkStream stream = client.GetStream();            // 发送数据            string message = "Hello, server!";            byte[] data = Encoding.ASCII.GetBytes(message);            stream.Write(data, 0, data.Length);            Console.WriteLine("Sent: " + message);            // 接收数据            data = new byte[1024];            int bytesRead = stream.Read(data, 0, data.Length);            string responseData = Encoding.ASCII.GetString(data, 0, bytesRead);            Console.WriteLine("Received: " + responseData);            // 关闭连接            client.Close();        }        catch (Exception e)        {            Console.WriteLine("Error: " + e.ToString());        }    }}
```

### 总结

通过本文的介绍，大家应该对在 C# 中实现 TCP 长连接有了基本的了解。要注意的是，实际应用中可能需要更复杂的逻辑来处理连接的错误、断开和重连，以及更多的安全性和性能考虑。因此，在开发实际项目时，建议仔细设计和测试长连接的实现，以上代码仅供参考。

通过使用 TCP 长连接，可以实现高效的数据传输和实时通信，为各种类型的应用提供了稳定可靠的网络连接方式。

![](https://mmbiz.qpic.cn/mmbiz_gif/Ljib4So7yuWgtu32lo8txTia7urcjBx8VnHePPpZ8xSbEdsS8Hou17v7epnoibWWkIuHjVEd19ZWn0SibXEfvPPIxA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

*   [免费开源的程序员简历模板](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247497295&idx=1&sn=c0497b6bb472ecadbdeea68735562275&chksm=97516ad4a026e3c27f4fc0f5bd2a7e29f3e8c8be44bb770ab10f210ffa732486ee80f9c2bc2f&scene=21#wechat_redirect)  
    
    ========================================================================================================================================================================================================================================
    
*   [了解作者 & 获取更多学习资料](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247485948&idx=1&sn=afa4d107bb5b102d5d29054216b14af8&chksm=97529567a0251c71db5395776cbb942570b306e77d6c7de009390aece8739fe64f220dae8300&scene=21#wechat_redirect)
    ========================================================================================================================================================================================================================================
    
*   [程序员常用的开发工具软件推荐](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247487776&idx=1&sn=f3a8ba9d8e293312bce8bbf9eeca3983&chksm=97528dbba02504ad612f40cbad3c3296c1ad9b91c014875068cb9f197b05765406bf3bd16cde&scene=21#wechat_redirect)
    =======================================================================================================================================================================================================================================
    
*   [加入 DotNetGuide 技术社区交流群](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247497757&idx=2&sn=bec6d99f1d3d5d64f60250be2fd3c516&chksm=97516486a026ed90927c66b8c7c646b7b90600bac644a26af2df1d3d85b50ef0dee83ddebcf6&scene=21#wechat_redirect)
    ===============================================================================================================================================================================================================================================
    
*   [C#/.NET/.NET Core 推荐学习书籍](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247494103&idx=1&sn=322cbe4a48cf3f7054b4122c04af91e4&chksm=9751754ca026fc5ac0b5a1e37a8cdfdeb59a1952af4190e48edca120f90ede763f389180c520&scene=21#wechat_redirect)  
    
*   [C#/.NET/.NET Core 学习视频汇总](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247487746&idx=1&sn=d2d5d8b309cef1ba72026d502cc71c4a&chksm=97528d99a025048f7c4ef3421478e186728284f03f8c755d8a851472dbf1c319e75babd356a9&scene=21#wechat_redirect)
    
*   [.NET/.NET Core ORM 框架资源汇总](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247493672&idx=1&sn=5105ef0a229e3fbc9caf0f8fae0d99bb&chksm=975174b3a026fda53788936eb6ce130d4f689e1f6f02da98f5349c91ee11c66a5430e4488646&scene=21#wechat_redirect)
    ==================================================================================================================================================================================================================================================
    
*   [](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247486354&idx=1&sn=d636dfbef5faea3821c095e0d7640f64&chksm=97529709a0251e1f9eaf86e2248015460de260700d74ff6923fc2e656f70db728a878f1b9599&scene=21#wechat_redirect)[ASP.NET Core 开发者学习指南路线图](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247487740&idx=1&sn=11e5387dca381b2597be348279ebd626&chksm=97528c67a02505712f0f180ffd4af0971fe74ab37f88df44018c9a3ad4f814770877a002a634&scene=21#wechat_redirect)
    =========================================================================================================================================================================================================================================================================================================================================================================================================================================================================
    
*   [C#/.NET/.NET Core 面试宝典（基础版）](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247490975&idx=1&sn=c1e47f1c253a60c67984d6ee01a49803&chksm=97528104a0250812edeccf2ceaaa6fdbddd04f98ed46d8a826f4e77a6ca5e631356b6bfe04c8&scene=21#wechat_redirect)
    
*   [C#/.NET/.NET Core 优秀项目和框架推荐](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247485418&idx=1&sn=408a44210c21d0ab739ba3108a3f635c&chksm=97529b71a02512679710c370ac85d2deb8b8b5f9298208c69358336445f29a520350b4057c0e&scene=21#wechat_redirect)
    
*   [C#/.NET/.NET Core 学习、工作、面试指南](http://mp.weixin.qq.com/s?__biz=MzIxMTUzNzM5Ng==&mid=2247496760&idx=1&sn=7d3cfef5455980a88667a6d2d607647c&chksm=975168a3a026e1b511c87862eb1efe76cb46f1a503ecba0c5f7989f485481c6d8a7d4af6385f&scene=21#wechat_redirect)
    

![](https://mmbiz.qpic.cn/mmbiz_gif/Ljib4So7yuWhV286BqNMwDMKWbMic75en4IFH3HQqFtoiau9PLcbwvKEBlkUJqs3k2WCCm7Vbv39dcUDNN1dPy7hA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

![](https://mmbiz.qpic.cn/mmbiz_jpg/Vtf2wZNabHCNFqhaS3jlRN82iafVavcOpaFn6ZrPpEMEicyZLpYnay0ueGY6j6hRt1rfyKicmDrasw5VwzB7CeEkg/640?wx_fmt=other&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

* * *

**学习是一个永无止境的过程，你知道的越多，你不知道的也会越多，在有限的时间内坚持每天多学一点，你一定能成为你想要成为的那个人。不积跬步无以至千里，不积小流无以成江河！！！**

![](https://mmbiz.qpic.cn/mmbiz_gif/Vtf2wZNabHCNFqhaS3jlRN82iafVavcOpouj5Bn4jfabZAxkXchh1U6MNAl4Io7efJiaRxzIJSuqQvhwUV3l8ABg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)

**See you next good day**

![](https://mmbiz.qpic.cn/mmbiz_gif/Zxmz2vibxicFJUs3WfYfk2eDHlllAEfaZBSDYcJhf1SCovVSvfPV7awNknJRG5WKq52FGibPicU7CokA8ASoicAYchQ/640?wx_fmt=gif&wxfrom=5&wx_lazy=1&tp=webp)