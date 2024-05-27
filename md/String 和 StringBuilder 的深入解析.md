> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/nl96YjCeQoWpXW4sonCmvw)

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
    Stopwatch watch = new Stopwatch()
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

StringBuilder 对象维护一个缓冲区，以便容纳新数据的串联。如果有足够的空间，新数据将被追加到缓冲区的末尾；否则，将分配一个新的、更大的缓冲区，原始缓冲区中的数据被复制到新的缓冲区，然后将新数据追加到新的缓冲区。

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
