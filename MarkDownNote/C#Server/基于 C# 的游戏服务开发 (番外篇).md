> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg4MDU1ODI2Mg==&mid=2247485301&idx=1&sn=8af112876c56aaa03bdff7aac1b6619a&chksm=cf722eacf805a7ba4232c96a920ac5d97c6b49ca2c6199295279d8ef5bf52eead7dc9477f819&scene=126&&sessionid=1665201161#rd)

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aVnAhURoJcLfzJmw6zKeicKWh6INBPoOz4qIZA6lLDKpeXZiaia1oicomu4t79KPkSIWXXmKTnUHxsDQ/640?wx_fmt=png)

  

点击蓝字关注我哦

  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aVnAhURoJcLfzJmw6zKeicKWh6INBPoOz4qIZA6lLDKpeXZiaia1oicomu4t79KPkSIWXXmKTnUHxsDQ/640?wx_fmt=png)

![](https://mmbiz.qpic.cn/mmbiz_jpg/tXghtxYMW0aVnAhURoJcLfzJmw6zKeicKQq6cbSX5edjrnf8A9XbiaPib5osIq08g7OYPkKiaygF1eXZE5aHmVxG4w/640?wx_fmt=jpeg)

![](https://mmbiz.qpic.cn/mmbiz_gif/tXghtxYMW0beiaZZhkKogvqxK9WJTpGPW5RJ2MklvWWibRmia7Ecsic50FH04cesAwkONqrpTqWibvk9cLF5mrdqdHw/640?wx_fmt=gif)

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0beiaZZhkKogvqxK9WJTpGPW88gYQjzeASOA5f9QHCgia7H4Fc0ARZkFmzUBZrS0pUMA7JibOYiaujtkw/640?wx_fmt=png)

实战: 用户的登录注册

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0beiaZZhkKogvqxK9WJTpGPWaiaDKcrayibbHzu75VOMythszBJFYNr7j8aaYia9UzmFacZZCkX9dT4GQ/640?wx_fmt=png)

到目前为止, 已经完成了服务端框架的底层功能, 那么现在测试的方法仅仅是通过在 main 函数中写一些测试的一些代码, 并没有和 Unity 真正的结合起来, 那么接下来就和 Unity 结合一下, 真正的去做一个完整的登陆注册流程.

  

既然是登录和注册, 那么肯定有登录和注册这 2 个协议:

  

我们新建一个 LoginMsg 的脚本:

  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8Ve0LnOicNkhgaxibG5vrb9uibOniaTibYYEOPBz7011Qe3PRWZI8pwQWJt4A/640?wx_fmt=png)

  

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class MsgRegister : MsgBase
{
    public MsgRegister()
    {
        protoName = "MsgRegister";
    }
    //客户端
    public string id = "";
    public string pw = "";

    //服务器返回 -0成功 -1失败
    public int result = 0;

}


public class MsgLogin : MsgBase
{
    public MsgLogin()
    {
        protoName = "MsgLogin";
    }
    //客户端
    public string id = "";
    public string pw = "";

    //服务器返回 -0成功 -1失败
    public int result = 0;
}

public class MsgKick : MsgBase
{
    public MsgKick()
    {
        protoName = "MsgKick";
    }
    //下线原因
    public int reason = 0;
}


```

  

接下来要对协议进行处理:  

  

我们起个名字: LoginMsgHandle, 注意虽然这个脚本的名字叫这个, 但是他也是算一个 EventHandler 的一个组合类. 不要被 Unity 开发中创建脚本的形式给迷惑了.

  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VEmS0PWCYx48UlAfEcIlficibFPMTRqPf6yAagHero8j3eiaHRyTYCm8Rg/640?wx_fmt=png)

  

登录注册以及下线, 下线是用来在 2 个客户端同时登录一个账号的时候需要:

  

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public partial class MsgHandler
{
    //注册协议处理
    public static void MsgRegister(ClientState c, MsgBase msgBase)
    {
        MsgRegister msg = (MsgRegister)msgBase;
        //执行数据库语法尝试注册
        if (DbManager.Register(msg.id, msg.pw))
        {
            DbManager.CreatPlayer(msg.id);
            msg.result = 0;
        }
        else
        {
            msg.result = 1;
        }
        //将结果返回给客户端
        NetManager.Send(c, msg);
    }

    //登录协议处理
    public static void MsgLogin(ClientState c, MsgBase msgBase)
    {
        MsgLogin msg = (MsgLogin)msgBase;
        //密码校验
        if (!DbManager.CheckPassword(msg.id, msg.pw))
        {
            msg.result = 1;
            NetManager.Send(c, msgBase);
            return;
        }
        //如果已经在线,并在此客户端上又尝试登录
        if (c.player != null)
        {
            msg.result = 1;
            NetManager.Send(c, msgBase);
            return;
        }
        //如果其他客户端登录,踢下线
        if (PlayerManager.isOnline(msg.id))
        {
            //发送踢下线协议
            Player other = PlayerManager.GetPlayer(msg.id);
            MsgKick msgKick = new MsgKick();
            msgKick.reason = 0; 
            other.Send(msgKick);//协议发送
            //断开连接
            NetManager.Close(other.state);
        }
        //获取玩家数据
        PlayerData playerData = DbManager.GetPlayerData(msg.id);
        if (playerData == null)
        {
            msg.result = 1;
            NetManager.Send(c, msg);
            return;
        }
        //构建player
        Player player = new Player(c);
        player.id = msg.id;
        player.data = playerData;
        PlayerManager.AddPlayer(msg.id, player);
        c.player = player;
        //返回协议
        msg.result = 0;
        player.Send(msg); 
    }

    public static void OnDisconnect(ClientState c)
    {
        Console.WriteLine("Close");
        //Player 下线
        if (c.player != null)
        {
            //保存数据
            DbManager.UpdatePlayerData(c.player.id, c.player.data);
            //移除
            PlayerManager.RemovePlayer(c.player.id);
        }
    }
}


```

  

到目前为止服务端的功能基本写完, 接下来要到 Unity 中,, 写客户端的功能, 首先要搭建一个场景, 场景布置如下:

  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VOmzibhhQy43jdLXr4qkFwtxoeyMU3YOU1B3m2iapnUz6Ql8fTeY1Dt8w/640?wx_fmt=png)

  

2 个输入框以及登录注册按钮.  

  

新建一个 test 脚本文件:  

  

流程同样是先连接服务器然后监听一些回调方法. 首先是连接服务器以及数据处理的一些方法, 这些方法都是之前章节中所写过的, 所以这次我们直接复制过来:  

  

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using TMPro;

public class test : MonoBehaviour
{ 

    private void Start()
    {
        NetManager.Connect("127.0.0.1", 8888); 

    }


    private void Update()
    {
        NetManager.Update();
    }

}


```

  

还有就是把登录注册的协议也要复制过来:  

  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8V6eUQFJJSBAkfV5yqR3g2UmjmGPeP9Ygk9zv1bRkmA395pI11rXlJxw/640?wx_fmt=png)

  

服务器开始的同时运行此脚本, 发现连接没有任何问题, 接下来就是要做的就是把我们的登录注册协议写进去:  

  

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using TMPro;

public class test : MonoBehaviour
{
    public TMP_InputField idInput;
    public TMP_InputField pwInput;

    private void Start()
    {
        NetManager.Connect("127.0.0.1", 8888);
        NetManager.AddMsgListener("MsgMove", OnMsgMove);
        NetManager.AddEventListener(NetManager.NetEvent.ConnectSucc, OnConnectSucc);
        NetManager.AddEventListener(NetManager.NetEvent.ConnectFail, OnConnectFail);
        NetManager.AddEventListener(NetManager.NetEvent.Close, OnConnectClose);
    }



    void OnConnectSucc(string err)
    {
        Debug.Log("连接成功...");
    }

    void OnConnectFail(string err)
    {
        Debug.Log("连接失败...");
    }

    void OnConnectClose(string err)
    {
        Debug.Log("连接关闭...");
    }

    //发送注册协议
    public void OnRegister()
    {
        MsgRegister msg = new MsgRegister();
        msg.id = idInput.text;
        msg.pw = pwInput.text;
        NetManager.Send(msg);
        Debug.Log(msg.protoName);
        Debug.Log(msg.id);
        Debug.Log(msg.pw);
    }
    //收到注册协议
    public void OnMsgRegister(MsgBase msgBase)
    {
         MsgRegister msg = msgBase as MsgRegister;        if (msg.result == 0)
        {
            Debug.Log("注册成功");
        }
        else
        {
            Debug.Log("注册失败!");
        }
    }

    //发送登录协议
    public void OnLoginClick()
    {
        MsgLogin msg = new MsgLogin();
        msg.id = idInput.text;
        msg.pw = pwInput.text;
        NetManager.Send(msg);
    }

    //收到登录协议
    public void OnMsgLogin(MsgBase msgBase)
    {
        MsgLogin msg = msgBase as MsgLogin;        if (msg.result == 1)
        {
            Debug.Log("登录成功");
        }
        else
        {
            Debug.Log("登录失败");
        }
    }

    //踢下线
    void OnMsgKick(MsgBase msgBase)
    {
        Debug.Log("被踢下线");
    }


    private void Update()
    {
        NetManager.Update();
    }



```

然后把输入框赋值一下:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VLzQlY7c8HrQJ6Ftj6IIicZ8ceiczcc3po61tjNqGvNVPn0Ey2zbEE0tQ/640?wx_fmt=png)

我们先尝试运行一下, 先输入一个错误的用户名和密码按登录键:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VBw77lI8OjbIyHcleOibiaRuyX4zhn9yU1xpCO33KanJnzcvDiaIu7O15Q/640?wx_fmt=png)

发现服务器已经调用成功, 接下来我们用正确的账户名和密码登录一下:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VpaQtzEwhGopHma6T8zbmHEicfbywnLkD63w8EfUczICZIFZmCn5RVCA/640?wx_fmt=png)

那么再试试注册的方法:

如果是写一个已经存在的账号:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VicR9mFNiaMrOlb1icSRE8tBbWjnIELoeuADoH7slNpnXqqwEQAKWgYyHw/640?wx_fmt=png)

相反, 写一个没有注册过的账号:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VvjRibopibiaDM0xk5Utz5ibHaNXWSe4862IKepqxu1wtO596YaQTnDdujQ/640?wx_fmt=png)

那么再看看数据库中的内容:  

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8VCdUeWVbfTX35lyIZIO5Dh4bg4SXVUcPtZvnsZuvUXAVyZcVkyLA6zg/640?wx_fmt=png)

发现了一个 bug, 客户端没有打印出状态信息, 经检查, 是协议名字写错了:

修改一下:

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using TMPro;

public class test : MonoBehaviour
{
    public TMP_InputField idInput;
    public TMP_InputField pwInput;

    private void Start()
    {
        NetManager.Connect("127.0.0.1", 8888);
        NetManager.AddMsgListener("MsgMove", OnMsgMove);
        NetManager.AddMsgListener("MsgLogin", OnMsgLogin);
        NetManager.AddMsgListener("MsgRegister", OnMsgRegister);
        NetManager.AddEventListener(NetManager.NetEvent.ConnectSucc, OnConnectSucc);
        NetManager.AddEventListener(NetManager.NetEvent.ConnectFail, OnConnectFail);
        NetManager.AddEventListener(NetManager.NetEvent.Close, OnConnectClose);

    }

    public void Send()
    {
        MsgMove msgMove = new MsgMove
        {
            x = 10,
            y = 2,
            z = -110
        };
        NetManager.Send(msgMove);
    }

    public void OnMsgMove(MsgBase msgBase)
    {
        MsgMove msg = msgBase as MsgMove;
        Debug.Log(msg.protoName);
        Debug.Log(msg.x);
        Debug.Log(msg.y);
        Debug.Log(msg.z);
    }


    void OnConnectSucc(string err)
    {
        Debug.Log("连接成功...");
    }

    void OnConnectFail(string err)
    {
        Debug.Log("连接失败...");
    }

    void OnConnectClose(string err)
    {
        Debug.Log("连接关闭...");
    }

    //发送注册协议
    public void OnRegister()
    {
        MsgRegister msg = new MsgRegister();
        msg.id = idInput.text;
        msg.pw = pwInput.text;
        NetManager.Send(msg);

    }
    //收到注册协议
    public void OnMsgRegister(MsgBase msgBase)
    {
        MsgRegister msg = msgBase as MsgRegister;
        if (msg.result == 0)
        {
            Debug.Log("注册成功");
        }
        else
        {
            Debug.Log("注册失败!");
        }
    }

    //发送登录协议
    public void OnLoginClick()
    {
        MsgLogin msg = new MsgLogin();
        msg.id = idInput.text;
        msg.pw = pwInput.text;
        NetManager.Send(msg); 
    }

    //收到登录协议
    public void OnMsgLogin(MsgBase msgBase)
    {
        MsgLogin msg = msgBase as MsgLogin;
        Debug.Log(msg.result);
        if (msg.result == 1)
        {
            Debug.Log("登录成功");
        }
        else
        {
            Debug.Log("登录失败");
        }
    }

    //踢下线
    void OnMsgKick(MsgBase msgBase)
    {
        Debug.Log("被踢下线");
    }


    private void Update()
    {
        NetManager.Update();
        if (Input.GetKeyDown(KeyCode.A))
        {
            Send();
        }
    }


```

结果如下:

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0bDMq9NwVmibbickDqm3t8ib8Vnts27jSg5Xujialy95M0IMwicDeias4n0dYibSdQXcVNp3b4HpicXl2bHcQ/640?wx_fmt=png)

enjoy it !!!

  

本案例的客户端与服务器源码下载方法: 公众号回复 服务器开发 即可.

…END…

![](https://mmbiz.qpic.cn/mmbiz_png/2ibt1icyStlHic7ahCUraibQEGs1UdQEKfvMCQ93Ut3fMg3TUtg7zLmJib2sicDpwH8hsQw5ibbAd7hOYXF0cDkZlfThQ/640?wx_fmt=png)

扫描二维码

获取更多精彩

微信号 : untiy-plane

![](https://mmbiz.qpic.cn/mmbiz_jpg/tXghtxYMW0Y8PFkByNhkzsZmTmGLiaSnDibXiaDfK5QoXworQvwXwnnqfZlkZibzzia6avUWLdIny849UrAgicXGG6aQ/640?wx_fmt=jpeg)  

你都这么好看了，不给我个好看么~

![](https://mmbiz.qpic.cn/mmbiz_png/tXghtxYMW0aVnAhURoJcLfzJmw6zKeicKs7WatXaDnYsL3RzX8vicezeiaib9l1VgvPaD7CeQ9afI36YcFvlu1KEng/640?wx_fmt=png)