> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484006&idx=1&sn=593d9adba34de8608d9a209bd1e79922&chksm=ce072369f970aa7fe802895ba4d611e7fca2d403fd3d889895764385ffb65a5d6440c813cc96&cur_album_id=3218021275236007937&scene=189#wechat_redirect)

工厂模式是一种创建型设计模式，它提供了一种封装对象实例化过程的方式，使得客户端代码与具体类的实现解耦。

在 C# 的游戏设计中，模式有以下作用：

**对象的创建与使用分离：** 单工厂模式将对象的创建过程放在一个单独的工厂类中，使得客户端代码不直接依赖于具体的类实现。客户端只需要通过工厂类来创建对象，而不需要了解对象的具体实现细节。

**易于扩展：** 如果需要添加新的游戏元素或功能，只需要修改工厂类，而不需要修改客户端代码。这使得系统更加灵活，易于扩展和维护。

**代码复用：** 工厂模式可以在多个地方共享，以确保对象的一致性创建。这有助于减少重复的代码，提高代码的可维护性。

**降低耦合度：** 客户端代码不需要直接知道如何创建对象，只需通过工厂类来获取所需的对象。这降低了系统中各个类之间的耦合度，使得系统更易于理解和维护。

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakmpzteueEzNMu6qoOobpvUNkibZzVh4PPT2WFDoaL9u5fm3PdW1QOlv9Tme3dmNxCQEXsticntjI6Fw/640?wx_fmt=png&from=appmsg)

工厂模式用于创建对象实例，例如创建不同类型的敌人（Enemy）或武器（Weapon）。

分为：简单工厂模式，工厂方法模式，抽象工厂模式

优点：

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/NSzqcbtSiakmpzteueEzNMu6qoOobpvUNcjcRafuBdm6tcgbYEoZLib0GGQqoRkyrFL330wFIkLWkucd7iaQnIKZQ/640?wx_fmt=gif&from=appmsg)![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakmpzteueEzNMu6qoOobpvUN9DLf03nB5ao7WlibfgdAzKNsLxMR0OofrfdicVIUIMrlEB8R0xwfcgpw/640?wx_fmt=png&from=appmsg)

**1. 简单工厂模式**

需要创建的对象类：

```c#
//游戏对象类
interface IGameObject
{
    void LogMe();
}
//让游戏对象继承此接口，这样就可以使用接口装载各种对象
class Enemy : IGameObject
{
    public void LogMe()
    {
        Console.WriteLine("我是敌人");
    }
}
class Player : IGameObject
{
    public void LogMe()
    {
        Console.WriteLine("我是玩家");
    }
}
class Goods : IGameObject
{
    public void LogMe()
    {
        Console.WriteLine("我是商品");
    }
}
```

下面为简单工厂类

```c#
    //创建一个接口表示游戏对象
    //也可以创建一个类，但方法记得要写virtual和override不然表现不了多态

//创建简单工厂类
class GameObjectFactory
{
    //实现在工厂创建对象的方法并返回
    public static IGameObject CreateItem(string name)
    {
        switch (name)
        {
            case "Enemy":
                return new Enemy();
            case "Player":
                return new Player();
            case "Goods":
                return new Goods();
            default:
                throw new ArgumentException($"无效的对象名: {name}");
        }

    }
}
    class Program
    {
        static void Main(string[] args)
        {
            //调用工厂类创建对象
            IGameObject enemy = GameObjectFactory.CreateItem("Enemy");
            IGameObject player = GameObjectFactory.CreateItem("Player");
            IGameObject goods = GameObjectFactory.CreateItem("Goods");
            enemy.LogMe();
            player.LogMe();
            goods.LogMe();
        }
    }
```

**2. 工厂方法模式**

工厂方法模式是对简单工厂模式进一步的解耦，在工厂方法模式中是 “一类产品对应一个工厂类”

而这些工厂类都继承于一个抽象工厂。这相当于是把原本会随着业务扩展而庞大的简单工厂类，拆分成了一个个的具体产品工厂类，这样代码就不会都耦合在同一个类里。

```c#
interface IFactory
{
    IGameObject CreateGameObject();
}
//敌人工厂
class EnmyFactory : IFactory
{
    public IGameObject CreateGameObject()
    {
        return new Enemy();
    }
}
//玩家工厂
class PlayerFactory : IFactory
{
    public IGameObject CreateGameObject()
    {
        return new Player();
    }
}
//使用：
    IFactory enemyFactory = new EnmyFactory();//创建敌人工厂
    IGameObject enemy = enemyFactory.CreateGameObject();//通过敌人工厂创建敌人
    IFactory playerFactory = new PlayerFactory();//创建玩家工厂
    IGameObject player = playerFactory.CreateGameObject();//通过玩家工厂创建玩家
```

**3. 抽象工厂模式**

抽象工厂模式是工厂方法模式的加强版，抽象工厂模式与工厂方法模式最大的区别在于，工厂方法模式针对一个产品对应一个工厂类，而抽象工厂模式面对多个产品对应一个工厂类，一个工厂角色可以负责多个不同产品等级结构中的产品对象的创建 。

```c#
//在上面的游戏对象类在加一些
//不同敌人类
    class BigEnemy : IGameObject
    {
        public void LogMe()
        {
            Console.WriteLine("我是大敌人");
        }
    }
    class SmallEnemy : IGameObject
    {
        public void LogMe()
        {
            Console.WriteLine("我是小敌人");
        }
    }
//不同玩家类
    class BigPlayer : IGameObject
    {
        public void LogMe()
        {
            Console.WriteLine("我是大玩家");
        }
    }
    class SmallPlayer : IGameObject
    {
        public void LogMe()
        {
            Console.WriteLine("我是小玩家");
        }
    }
```

以下为抽象工厂类：

```c#
interface IFactory
{
    IGameObject CreateBigOne();
    IGameObject CreateSmallOne();
}
//创建敌人工厂
class EnemyFactory : IFactory
{
    public IGameObject CreateBigOne()
    {
        return new BigEnemy();
    }

    public IGameObject CreateSmallOne()
    {
        return new SmallEnemy();
    }
}
//创建玩家工厂
class PlayerFactory : IFactory
{
    public IGameObject CreateBigOne()
    {
        return new BigPlayer();
    }

    public IGameObject CreateSmallOne()
    {
        return new SmallPlayer();
    }
}
//使用
    IFactory enemyFactory = new EnemyFactory();//创建敌人工厂
    IGameObject bigEnemy = enemyFactory.CreateBigOne();
    IGameObject smallEnemy = enemyFactory.CreateSmallOne();
    IFactory playerFactory = new PlayerFactory();//创建玩家工厂
    IGameObject bigPlayer = playerFactory.CreateBigOne();
    IGameObject smallPlayer = playerFactory.CreateSmallOne();
```