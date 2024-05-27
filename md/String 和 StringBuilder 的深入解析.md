> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/nl96YjCeQoWpXW4sonCmvw)

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/zrjP7da7BLZ9oRibkJyc5ZXCyz1icViaK699JoenSqEXsC9R5dsjEhJFYkJ17ibPRMLVJ0OOwhM5eO8tyib87N1tbSA/640?wx_fmt=jpeg&from=appmsg)

**前言**

本文出发点是我们开发的过程中是否真正的理解 stringbuilder 的使用，string 字符串操作的是如何实现（哈希表），stringbuilder 是否设置默认值容量，什么时候才用 stringbuilder。

**一、概念**

**String** **和** **stringbulider** **的理解**

**string** 是我们用的最多的类型之一，是一个特殊的引用类型，直接派生于 Object，因此它的值储存在托管堆上。构造一个新字符串的时候，不需要用 new。它是” 不可变的 “。初始化字符串对象后，该字符串对象的长度、内容都是确定不变的了。可以思考这个时候，我们需要更改或者添加字符串，会做一个怎样的动作呢？

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9l2qhOxBcB4qnu3EXowM4kurgHibdW0LwToOMLMhseeyct1aiaJmeKgeLw/640?wx_fmt=png&from=appmsg)![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lUhzkOLL7GRacZ5EBlOY1iaGMj3edA5KSYbo2tsUKmDicW8PbQLZ6PyTQ/640?wx_fmt=png&from=appmsg)

**StringBulider** 因为 string 的” 不可变 “，导致多次修改字符串的时候会损耗性能，.net 为了解决这个问题，提供了动态创建 string 的方法，以克服 string 不可变带来的性能损耗。StringBuilder 和 String 比起来，功能较少，只有基本的属性和增删改的方法。但是你知道 stringbuilder 也有一个固定的容量值吗**？？**，**注意：****StringBulider** **容量** **（默认是** **16****）**虽然   StringBuilder   对象是动态对象，允许扩充它所封装的字符串中字符的数量，但是您可以为它可容纳的最大字符数指定一个值。此值称为该对象的容量，不应将它与当前   StringBuilder   对象容纳的字符串长度混淆在一起。例如，可以创建   StringBuilder   类的带有字符串 “Hello”（长度为   5）的一个新实例，同时可以指定该对象的最大容量为   25。当修改   StringBuilder   时，在达到容量之前，它不会为其自己重新分配空间。当达到容量时，将自动分配新的空间且容量翻倍。可以使用**重载的构造函数之一来指定** **StringBuilder** 类的容量。以下代码示例指定可以将   MyStringBuilder 对象扩充到最大 25 个空白。StringBuilder MyStringBuilder  =  new   StringBuilder("Hello   World!",   25);   另外，可以**使用读** **/** **写   Capacity** **属性来设置对象的最大长度**。以下代码示例使用   Capacity   属性来定义对象的最大长度。  MyStringBuilder.Capacity   =   25;   EnsureCapacity   方法可用来检查当前   StringBuilder   的容量。如果容量大于传递的值，则不进行任何更改；但是，如果容量小于传递的值，则会更改当前的容量以使其与传递的值匹配。也可以查看或设置   Length   属性。如果将   Length   属性设置为大于   Capacity   属性的值，则自动将   Capacity   属性更改为与   Length   属性相同的值。如果将   Length   属性设置为小于当前   StringBuilder   对象内的字符串长度的值，则会缩短该字符串。

**二****、为什么说变动影响性能****。（****string** **和** **StringBuilder****）**

```
private void button1_Click(object sender, EventArgs e)

        {

 

            int number =int.Parse( textBox1.Text.ToString());

 

            GetStringTime(number);

            GetStringBulider(number);

 

            GetStringTime1(number);

            GetStringBulider1(number);

        }

 

        /// <summary>

        ///  测试string 性能时间

        /// </summary>

        private void GetStringTime(int number)

        {

            Stopwatch watch = new Stopwatch();

            List< String> li = new List< string>();

            watch.Start();

            string str = "select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";

            for (int i = 0; i < number; i++)

            {

                li.Add(str);    

            }

            watch.Stop();

            label1.Text = watch.ElapsedMilliseconds.ToString();

 

        }

 

 

        private void GetStringBulider(int number)

        {

            Stopwatch watch = new Stopwatch();

            List<String> li = new List<string>();

            watch.Start();

            StringBuilder strb = new StringBuilder();

            strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");

            for (int i = 0; i < number; i++)

            {

                li.Add(strb.ToString());   

            }

            watch.Stop();

            label2.Text = watch.ElapsedMilliseconds.ToString();

       

        }

 

 

        /// <summary>

        ///  测试string 性能时间变化

        /// </summary>

        private void GetStringTime1(int number)

        {

            Stopwatch watch = new Stopwatch();

            List<String> li = new List<string>();

            watch.Start();

            string str = "select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";

            for (int i = 0; i < number; i++)

            {

                str = str+"select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";

          

            }

            watch.Stop();

            label1.Text =label1.Text+"不变，变化"+  watch.ElapsedMilliseconds.ToString();

 

        }

 

 

        /// <summary>

        ///  测试stringBulider  变化的性能

        /// </summary>

        /// <param ></param>

        private void GetStringBulider1(int number)

        {

            Stopwatch watch = new Stopwatch();

            List<String> li = new List<string>();

            watch.Start();

            StringBuilder strb = new StringBuilder();

            strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");

            for (int i = 0; i < number; i++)

            {

                strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");

   

            }

            watch.Stop();

            label2.Text =label2.Text+"不变，变化"+ watch.ElapsedMilliseconds.ToString();

 

        }
```

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lj5u4FdGyzibMgHibt4U0xmKkfzYjNctIRhCfiaPpsH9Ku2ZRkq895icITg/640?wx_fmt=png&from=appmsg)

  备注：如果每次都这样重新分配真实疯了，.net 肯定没有那么傻了，最起码要避免下如果两个 string 的字符串一模一样，我是不是不需要分配新的堆，只需要制定同样的引用就好了呢？下面就出现了一个名词：**字符串留用**，CLR 初始化的时候会创建哈希表，每构建一个新字符串都会与哈希表匹配，查找是否有相同的字符串，如果匹配，就会返回这个已存在的旧对象，由新变量进行引用。否则，就会创建一个字符串副本添加到哈希表里，Key 就是字符串，Value 就是 string 对象在堆上的地址。

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9l2iaf4EBqIzLucU1eJHFUJLKtNuIiaibqibwUicTLXzCB3rxydarbxFsJg3Q/640?wx_fmt=png&from=appmsg)

**是不是所有的都是这样呢，有什么特殊情况吗？**

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lZkWibFv3BPkvmAyrUIFibLVJn06U9As5Eu7qib9S05ftpf2OOBnibr7REg/640?wx_fmt=png&from=appmsg)

**总结** **New** **出来的对象是不会记录在哈希表。**

**tringBuilder** 对象维护一个缓冲区，以便容纳新数据的串联。如果有足够的空间，新数据将被追加到缓冲区的末尾；否则，将分配一个新的、更大的缓冲区，原始缓冲区中的数据被复制到新的缓冲区，然后将新数据追加到新的缓冲区。

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lbmvuIicN736bQ9PbNVQiapI0fU5UVfr2tEwoKWaBtmia2yzmzDn3s3D3g/640?wx_fmt=png&from=appmsg)

**内部实现原理**

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lVC16OvykUR7sqTL6Enbn40SqlaiaExoJkAEicMRdwPHQ1t1hpicAN8C7g/640?wx_fmt=png&from=appmsg)

**总结：**StringBuffer 是可变类，和线程安全的字符串操作类，任何对它指向的字符串的操作都不会产生新的对象。每个 StringBuffer 对象都有一定的缓冲区容量，当字符串大小没有超过容量时，不会分配新的容量，当字符串大小超过容量时，会自动增加容量。事实是，StringBuilder 比 string 快的原因是 string 拼接时产生了中间对象，最终是垃圾。如：string str = "a";str += "b";str += "c"; 那么，最终结果是 "abc"，但第二行产生了 "ab" 只是一个中间对象，是个垃圾。用 StringBuilder 会避免这种中间对象的产生。那如果我这么写呢？string str ="a"+"b"+ "c"; 这会比 StringBuilder 慢吗？不会。

**中间对象的产生才是影响性能的主要原因。**

**三、测试案例****：**

```
private void button1_Click(object sender, EventArgs e)
        {
            int number =int.Parse( textBox1.Text.ToString());
            GetStringTime(number);
            GetStringBulider(number);
            GetStringTime1(number);
            GetStringBulider1(number);
        }
        /// <summary>
        ///  测试string 性能时间
        /// </summary>
        private void GetStringTime(int number)
        {
            Stopwatch watch = new Stopwatch();
            List< String> li = new List< string>();
            watch.Start();
            string str = "select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";
            for (int i = 0; i < number; i++)
            {
                li.Add(str);    
            }
            watch.Stop();
            label1.Text = watch.ElapsedMilliseconds.ToString();
        }
        private void GetStringBulider(int number)
        {
            Stopwatch watch = new Stopwatch();
            List<String> li = new List<string>();
            watch.Start();
            StringBuilder strb = new StringBuilder();
            strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");
            for (int i = 0; i < number; i++)
            {
                li.Add(strb.ToString());   
            }
            watch.Stop();
            label2.Text = watch.ElapsedMilliseconds.ToString();
        }
        /// <summary>
        ///  测试string 性能时间变化
        /// </summary>
        private void GetStringTime1(int number)
        {
            Stopwatch watch = new Stopwatch();
            List<String> li = new List<string>();
            watch.Start();
            string str = "select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";
            for (int i = 0; i < number; i++)
            {
                str = str+"select * from testa inner join 快速排序耗费时间 快速排序耗费时间 快速排序耗费时间";
            }
            watch.Stop();
            label1.Text =label1.Text+"不变，变化"+  watch.ElapsedMilliseconds.ToString();
        }
        /// <summary>
        ///  测试stringBulider  变化的性能
        /// </summary>
        /// <param ></param>
        private void GetStringBulider1(int number)
        {
            Stopwatch watch = new Stopwatch();
            List<String> li = new List<string>();
            watch.Start();
            StringBuilder strb = new StringBuilder();
            strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");
            for (int i = 0; i < number; i++)
            {
                strb.Append("select * from testa inner join dsadfasfsadfa快速排序耗费时间快速排序耗费时间");
            }
            watch.Stop();
            label2.Text =label2.Text+"不变，变化"+ watch.ElapsedMilliseconds.ToString();
        }
```

效果图如下：

![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lIYmbKPSZYhnzWJCf38ibRDqxIRv1biaVLY9SnLIjjWTkjBFwKG59cjCQ/640?wx_fmt=png&from=appmsg) ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lwrj0Q3zeibgxGkF2PeGjuu4VOKakkLREmAsXGuSXI7yngZjvjnG0ibXA/640?wx_fmt=png&from=appmsg)![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lRRkX0s5yFwSRTENV3qtibtjPibPRZ2Jo9sEhvQvbbH5vA6CCPRpcxnoQ/640?wx_fmt=png&from=appmsg)![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lRbgOMOscKkWYFqbho3esTOqtTmqPwEjxHaLIb8A9GEq0Zd4JUAcmyw/640?wx_fmt=png&from=appmsg)

 ![](https://mmbiz.qpic.cn/sz_mmbiz_png/zrjP7da7BLYVdn9qPIdMN7ffLLOZnf9lCicgEnycuRxZjrSEmJialsricYzgXMWeDkcCN6NmYDAn1mnprPRbgkOLA/640?wx_fmt=png&from=appmsg)

备注：每图第一行表示 string，第二行表示 stringbulider，变化表示 str++ 的意思或 append。

**四：总结：****String** **和** **stringbulider** **的整体汇总****。**

1. Sting 是恒定的，string 部里的人是可变化的。

2. 对于简单的字符串连接操作，在性能上 stringbuilder 不一定总是优于 string。因为 stringbulider 对象的创建也消耗大量的性能，在字符串连接比较少的情况下，过度滥用 stringbuilder 会导致性能的浪费而非节约，只有大量无法预知次数的字符串操作才考虑 stringbuilder 的使用。从最后分析可以看出如果是 100 行以内根本看不出太大差别。

3. Stringbulider 的使用，最好制定合适的容量值，否则优于默认值容量不足而频繁的进行内存分配操作，是不妥的实现方法。

可以深思，第一我们对适合的容量值处理了吗？第二，我们是不是一再提要使用 stringbuilder 说性能好，但是在 100 行内的字符操作有分别吗。

简单的字符串连接操作可以适度思考下 string.Concat 和 string.join 的使用。（string.concat 的装箱操作）。

- ![](https://mmbiz.qpic.cn/mmbiz_gif/Ljib4So7yuWhV286BqNMwDMKWbMic75en4IFH3HQqFtoiau9PLcbwvKEBlkUJqs3k2WCCm7Vbv39dcUDNN1dPy7hA/640?wx_fmt=gif&wxfrom=5&wx_lazy=1&tp=webp) -

看完本文有收获？请转发分享给更多人

推荐关注「CSharp 精选营」，提升编程技能

推荐阅读  点击标题可跳转

*   [Git 详细使用教程（新手必看）！](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486032&idx=1&sn=5c78194b36802bb4bd71bbdf868b1f02&chksm=ce2ac51ef95d4c0836f9dbaeb93efaea13741cc8c383fd9f8123a28e663c7456a7e9affd75b3&scene=21#wechat_redirect)
    
*   [C# 读取 Excel 文件的几种方法【总结整理】](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486062&idx=1&sn=b1332ac25a764e21c9cee17672c2bb41&chksm=ce2ac520f95d4c366806457f376d88d4befa760b441c57ef83b7e22a3ffe8c55b710aa839653&scene=21#wechat_redirect)
    
*   [浅谈 sqlserver2008 和 sqlserver2014 的区别](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486269&idx=1&sn=580614420c444d6ba6d49e22df3f2ff3&chksm=ce2ac473f95d4d650256ef82b0054aa594bbabe5e74bc4df71732562ccc74d26f62eedd9ccf2&scene=21#wechat_redirect)
    
*   [C# 多种实现异步编程的方式及优缺点](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486304&idx=1&sn=8a83a1cf68a19ccb8e4637b10b0ad9f9&chksm=ce2ac42ef95d4d385b89090effe3576cb1d2ce7da5ddd54da03a278ab7672c4906eceafd003b&scene=21#wechat_redirect)
    
*   [使用 C# 实现 23 种常见的设计模式](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486311&idx=1&sn=2d5590408f03bc6e8cb294fcf78ee341&chksm=ce2ac429f95d4d3f020d4fcf227807bdda58c4dbfca6b3fa6475a8ad4667fc3ed613888fb73e&scene=21#wechat_redirect)
    
*   [C# 每年发布一个新版本，你焦虑吗？](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486406&idx=1&sn=0c651d1d856e8520b2dd9aca05b74702&chksm=ce2ac488f95d4d9eab2afb235e88c5dc492b9c37ad7217424cda729aa477cea4912a18086a94&scene=21#wechat_redirect)
    
*   [.NET 进阶书籍推荐](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486445&idx=1&sn=d01e41ad2052d571e8bc16f2ce107f58&chksm=ce2ac4a3f95d4db5a823a85a87edf9614e8bcea085e5742a9857c8232fe3298c03eb9a08c2a6&scene=21#wechat_redirect)
    
*   [Combres - 提高 Web 应用程序性能的 ASP.NET 资源管理库](http://mp.weixin.qq.com/s?__biz=Mzg2MDEwMTE1Mw==&mid=2247486677&idx=1&sn=cb0fcc78c7f6479bc9345a24eea13675&chksm=ce2ac39bf95d4a8d8d078b6e3361b5f46c491b83e832eaed42799e3a2f58fc65b8e2d98c98d8&scene=21#wechat_redirect)
    

**建群声明：**本着技术在于分享，方便大家交流学习的初心，特此建立**【CSharp 技术交流群】**，热烈欢迎各位进群交流学习编程心得，也希望进群的大佬能不吝分享自己遇到的技术问题和经验。

扫码入群

长按识别二维码

添加微信好友备注 “入群”

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/zrjP7da7BLYNQbGtY4nttt6Aq3QugPP4lNRP59icYzdvnqPVN7kKGGrUYbXiaOxSQNfJJWSYb1EDksEh1ibzsBV8g/640?wx_fmt=other&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)

![](https://mmbiz.qpic.cn/mmbiz_jpg/Vtf2wZNabHCNFqhaS3jlRN82iafVavcOpaFn6ZrPpEMEicyZLpYnay0ueGY6j6hRt1rfyKicmDrasw5VwzB7CeEkg/640?wx_fmt=other&wxfrom=5&wx_lazy=1&wx_co=1&tp=webp)  

点赞和在看就是最大的支持❤️