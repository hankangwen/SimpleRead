> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/cnT2554JyF35usyRAOCrmQ)

**摘要**
------

在 C# 中，特性（Attribute）是一种强大的语言功能，它允许开发者在程序运行时传递元素的行为信息。特性是一种声明性标签，可以放置在类、方法、结构、枚举、组件等元素前面的方括号中，用于描述元素的行为信息。

使用特性，开发者可以为程序添加各种声明性信息，如编译器指令、注释、描述、方法、类等其他信息。这些信息可以帮助其他开发者更好地理解和使用代码。

使用特性，开发者可以轻松地实现一些高级功能，如自动化注释、元数据导入和导出、类型约束等。同时，特性还可以与其他 C# 语言功能一起使用，如注释、成员属性等。

特性是 C# 语言中非常有用的一个功能，可以帮助开发者更好地组织和描述程序元素的行为信息，从而提高代码的可读性和可维护性。

**正文**
------

### 特性的主要应用场景

1.  **声明性编程** - 通过特性，开发者可以在不改变代码逻辑的情况下，为程序元素添加额外的信息。
    
2.  **插桩（Instrumentation）** - 特性可以用于在编译时或运行时插入额外的操作，比如日志记录、性能监控等。
    
3.  **代码验证** - 特性可以用于实现编译时或运行时的代码验证，保证代码满足特定的约束。
    
4.  **设计时支持** - 在设计工具中，特性可以用于控制属性网格中属性的显示或编辑方式。
    
5.  **序列化和反序列化** - 控制对象的序列化行为，如定义序列化的字段、格式和顺序。
    
6.  **依赖注入（DI）和控制反转（IoC）** - 在某些框架中，特性用于标记依赖项，以便自动注入。
    
7.  **单元测试** - 特性用于标记测试方法、设置测试初始化和清理逻辑等。
    

### 特性的特点

*   **声明性** - 特性提供了一种声明元数据的方式，这些元数据与代码的业务逻辑分离。
    
*   **可扩展性** - 开发者可以自定义特性来满足特定的需求。
    
*   **可检索性** - 可以在运行时使用反射来检索和分析特性信息。
    
*   **可选性** - 特性的使用是可选的，不使用不会影响代码的基本功能。
    

#### 预定义特性

.Net 框架提供了三种预定义特性：

*   AttributeUsage
    
*   Conditional
    
*   Obsolete
    

AttributeUsage （重点）

预定义特性 AttributeUsage 描述了如何使用一个自定义特性类。它规定了特性可应用到的项目的类型。规定该特性的语法如下：[AttributeUsage( validon, AllowMultiple=allowmultiple, Inherited=inherited)] 其中：

*   参数 validon 规定特性可被放置的语言元素。它是枚举器 AttributeTargets 的值的组合。默认值是 AttributeTargets.All。
    
*   参数 allowmultiple（可选的）为该特性的 AllowMultiple 属性（property）提供一个布尔值。如果为 true，则该特性是多用的。默认值是 false（单用的）。
    
*   参数 inherited（可选的）为该特性的 Inherited 属性（property）提供一个布尔值。如果为 true，则该特性可被派生类继承。默认值是 false（不被继承）。
    

AttributeUsage，这个例子我们指定到了 Class，也可以是 Method，Property，Filed，Interface，Struct，Enum 都可以附加属性。

```
internal class Program
{
    static void Main(string[] args)
    {
        Person person = new Person();
        //读取额外属性
        Type t = person.GetType();
        var student = t.GetCustomAttributes(typeof(StudentAttribute), false);
        var a = ((StudentAttribute)student.GetValue(0)).ClassName;
        var b = ((StudentAttribute)student.GetValue(0)).No;
        Console.WriteLine(a);
        Console.WriteLine(b);

        //这样也可以
        Person person = new Person();
        //读取额外属性
        Type t = person.GetType();
        var attr =(StudentAttribute) Attribute.GetCustomAttribute(t, typeof(StudentAttribute));
        Console.WriteLine(attr.ClassName);
        Console.WriteLine(attr.No);

    }
}
```

```
//给Person类一个班级与班级号
[Student("IT",100)]
public class Person
{
    public string Name { get; set; }    
    public int Id { get; set; }
}
```

```
/// <summary>
/// 申明一个自定义属性类
/// </summary>
[AttributeUsage(AttributeTargets.Class, AllowMultiple = true, Inherited = true)]
public class StudentAttribute : Attribute
{
    public StudentAttribute(string classname, int no)
    {
        this.ClassName = classname;
        this.No = no;
    }

    public string ClassName { get; set; }
    public int No { get; set; }
}
```

```
private void btnInit_Click(object sender, EventArgs e)
{
    Show();
}

[Conditional("DEBUG")]
private static void Show()
{
    MessageBox.Show("信息");
}
```

```
private void btnInit_Click(object sender, EventArgs e)
{
    Show();
}

[Obsolete("这是一个旧方法，未来会取消的，请用新的ShowMe")]
private static void Show()
{
    MessageBox.Show("Show");
}

private void ShowMe()
{
    MessageBox.Show("ShowMe");
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdmfKCOspGczNpK3JicRGDOeeHAMPib8TvqNM44VA9EOvoNbVZaqKZwFTh0Om4JSAjFxdhlvN50qyyBA/640?wx_fmt=png&from=appmsg)

#### Conditional

这个预定义特性标记了一个条件方法，其执行依赖于指定的预处理标识符。

它会引起方法调用的条件编译，取决于指定的值，比如 **Debug** 或 **Trace**。例如，当调试代码时显示变量的值。

```
private void btnInit_Click(object sender, EventArgs e)
{
    Show();
}
[Conditional("DEBUG")]
private static void Show()
{
    MessageBox.Show("信息");
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdmfKCOspGczNpK3JicRGDOeeS2tvkCmRqlaSWv4gdjDZndJCIk5KHbWsUzK4CLVJqbfLbxJevu8z3w/640?wx_fmt=png&from=appmsg)

在 Release 下，点击是不会调用 Show()，但在 Debug 下会调用

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdmfKCOspGczNpK3JicRGDOeep44tZRaJGEIiansstdiab0L5bfGdX88OtGic18XUVOpmSk9siaSgtkDccw/640?wx_fmt=png&from=appmsg)

#### Obsolete

这个预定义特性标记了不应被使用的程序实体。它可以让您通知编译器丢弃某个特定的目标元素。例如，当一个新方法被用在一个类中，但是您仍然想要保持类中的旧方法，您可以通过显示一个应该使用新方法，而不是旧方法的消息，来把它标记为 obsolete（过时的）。

*   参数 _message_，是一个字符串，描述项目为什么过时的原因以及该替代使用什么。
    
*   参数 _iserror_，是一个布尔值。如果该值为 true，编译器应把该项目的使用当作一个错误。默认值是 false（编译器生成一个警告）。
    

```
private void btnInit_Click(object sender, EventArgs e)
{
    Show();
}
[Obsolete("这是一个旧方法，未来会取消的，请用新的ShowMe")]
private static void Show()
{
    MessageBox.Show("Show");
}
private void ShowMe()
{
    MessageBox.Show("ShowMe");
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/D1DJjmDXQdmfKCOspGczNpK3JicRGDOeeNu3xEzQIt2PpazR2DEhpicL5fdHOwwszR8m6pryDowiah1XhTccKnVJA/640?wx_fmt=png&from=appmsg)