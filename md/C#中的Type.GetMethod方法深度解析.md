> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/AqNOYCPLmWHK6Ns6gnfyIw)

在 C# 编程中，`Type`类是一个非常重要的类，它提供了对类型元数据（如属性、方法、事件等）的访问。其中，`GetMethod`方法是`Type`类中的一个重要成员，它允许我们根据指定的名称和参数类型来获取类型中的方法信息。

本文将详细介绍`GetMethod`方法的使用方式、参数含义以及在实际开发中的应用场景。

一、GetMethod 方法概述

`GetMethod`方法是`System.Type`类的一个成员，用于获取当前`Type`对象表示的类型中定义的方法信息。该方法有多个重载版本，可以根据不同的参数来获取不同的方法信息。

二、GetMethod 方法参数详解

`GetMethod`方法的主要参数包括方法名称、参数类型数组、绑定标志等。下面是一些常见的重载版本及其参数说明：

1.  `public MethodInfo GetMethod(string name);`
    

*   `name`：要获取的方法的名称。此方法将返回与指定名称匹配的第一个公共方法。
    

3.  `public MethodInfo GetMethod(string name, BindingFlags bindingAttr);`
    

*   `name`：要获取的方法的名称。
    
*   `bindingAttr`：一个位掩码，用于指定应如何绑定到方法。这可以包括如公共方法、非公共方法、实例方法等不同的绑定选项。
    

5.  `public MethodInfo GetMethod(string name, Type[] types);`
    

*   `name`：要获取的方法的名称。
    
*   `types`：一个`Type`对象数组，它表示方法的参数类型。此方法将返回与指定名称和参数类型匹配的第一个公共方法。
    

7.  `public MethodInfo GetMethod(string name, BindingFlags bindingAttr, Binder binder, Type[] types, ParameterModifier[] modifiers);`
    

*   `name`：要获取的方法的名称。
    
*   `bindingAttr`：一个位掩码，用于指定应如何绑定到方法。
    
*   `binder`：一个对象，用于将参数类型绑定到方法。如果此参数为`null`，则使用默认的`Binder`。
    
*   `types`：一个`Type`对象数组，它表示方法的参数类型。
    
*   `modifiers`：一个`ParameterModifier`对象数组，用于修改参数传递方式。如果此参数为`null`，则使用默认的调用约定。
    

三、GetMethod 方法的应用场景

`GetMethod`方法在实际开发中有着广泛的应用场景，以下是一些常见的使用场景：

1.  **反射调用**：通过`GetMethod`获取方法信息后，可以使用`MethodInfo`对象的`Invoke`方法来动态调用该方法。这在实现插件式架构、框架开发或动态代理等场景中非常有用。
    
2.  **API 自动化测试**：在自动化测试框架中，可以使用`GetMethod`来获取待测试 API 的方法信息，并构建相应的测试用例和测试数据。
    
3.  **动态构建表达式树**：在构建动态 LINQ 查询或表达式树时，可以使用`GetMethod`来获取类型中的方法，并将其作为表达式树的一部分。
    
4.  **元数据分析和处理**：在需要对类型进行元数据分析或处理的场景中，如代码生成、序列化 / 反序列化等，可以使用`GetMethod`来获取类型中的方法信息，并进行相应的处理。
    

四、使用示例

下面是一个简单的示例，演示如何使用`GetMethod`方法来获取并调用一个类的方法：

```
using System;
using System.Reflection;

public class MyClass
{
    public void MyMethod(int a, string b)
    {
        Console.WriteLine("MyMethod called with a = " + a + ", b = " + b);
    }
}

class Program
{
    static void Main()
    {
        Type type = typeof(MyClass);
        MethodInfo methodInfo = type.GetMethod("MyMethod", new Type[] { typeof(int), typeof(string) });
        
        if (methodInfo != null)
        {
            MyClass myClassInstance = new MyClass();
            methodInfo.Invoke(myClassInstance, new object[] { 123, "Hello" });
        }
        else
        {
            Console.WriteLine("Method not found.");
        }
    }
}
```

在上面的示例中，我们首先通过`typeof`操作符获取`MyClass`类型的`Type`对象，然后使用`GetMethod`方法根据方法名称和参数类型获取`MyMethod`方法的`MethodInfo`对象。最后，我们创建了一个`MyClass`的实例，并使用`MethodInfo`对象的`Invoke`方法调用了该方法。

五、总结

`Type.GetMethod`方法是 C# 反射机制中的重要组成部分，它允许我们在运行时动态地获取类型中的方法信息。通过灵活使用`GetMethod`