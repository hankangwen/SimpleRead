> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/KB05Gy5HyY3yFhLngBdZ_w)

##   C#面向对象(OOPs)中的多态性类型

**概述**：在编程语言和类型理论中，多态性是为不同类型的实体提供单个接口，或者使用单个符号来表示多个不同的类型。多态对象是能够呈现多种形式的对象。

### 编译时多态性（静态绑定或早期绑定或临时多态性）：

编译时多态性存在两种类型，一种是**运算符重载**，另一种是**方法重载**

#### ** 方法重载： ** 

允许一个类具有多个具有相同名称但参数不同的方法。这里只有参数的区别，不返回方法的类型。

```c#
using System;  
  
public class Calculator  
{  
    public int Add(int a, int b)  
    {  
        return a + b;  
    }  
  
    // Overloaded method with different parameter types  
    public double Add(double a, double b)  
    {  
        return a + b;  
    }  
    // this is not possible can't have same paramter but different return type  
    public int Add(double a, double b)  
    {  
        return (int) a + b;  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        Calculator calc = new Calculator();  
        int result1 = calc.Add(10, 20);  
        double result2 = calc.Add(3.5, 4.5);  
  
        Console.WriteLine("Result 1: " + result1);  
        Console.WriteLine("Result 2: " + result2);  
    }  
}
```

#### ** 运算符重载：** 

允许重新定义运算符以使用用户定义的类型。就像您可以在字符串类型中添加数字一样。

```c#
using System;  
  
public class Complex  
{  
    public int Real { get; set; }  
    public int Imaginary { get; set; }  
  
    public Complex(int real = 0, int imaginary = 0)  
    {  
        Real = real;  
        Imaginary = imaginary;  
    }  
  
    // Overloading the '+' operator for adding two Complex objects  
    public static Complex operator +(Complex c1, Complex c2)  
    {  
        return new Complex(c1.Real + c2.Real, c1.Imaginary + c2.Imaginary);  
    }
    
    // Overloading the '!=' operator for adding two Complex objects  
    public static bool operator !=(Complex first, Complex second)  
    {  
        return !(first.Real == second.Real && first.Imaginary == second.Imaginary);  
    }  
    
    // Overloading the '==' operator for adding two Complex objects  
    public static bool operator ==(Complex first, Complex second)  
    {  
        return first.Real == second.Real && first.Imaginary == second.Imaginary;  
    }

    public override bool Equals(object? obj)
    {
        if(obj == null || GetType() != obj.GetType())
            return false;
        
        Complex other = (Complex)obj;
        return Real == other.Real && Imaginary == other.Imaginary;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Real, Imaginary);
    }
  
    public void Display()  
    {  
        Console.WriteLine($"Real: {Real}, Imaginary: {Imaginary}");  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        Complex c1 = new Complex(3, 4);  
        Complex c2 = new Complex(5, 6);  
        Complex result = c1 + c2; // Using the overloaded '+' operator  
        result.Display();  
    }  
}
```

在上面的例子中，复杂类重载 + 和 ！= 运算符，使用运算符重载，您可以提供自定义的自然运算符重载 -、+、* 或 = 等。你在编译时定义的所有东西，这就是为什么这被称为编译时重载。默认情况下，在 c# 中，整数和字符串之间存在默认的 + 运算符重载。

### 运行时多态性（动态绑定或后期绑定）：

#### ** 方法覆盖：** :

当子类提供已在其超类或父类中定义的方法的特定实现时发生。子类或子类方法重写具有相同签名和相同返回类型的超类方法。

```c#
using System;  
  
// Base class  
class Shape  
{  
    public virtual void Draw()  
    {  
        Console.WriteLine("Drawing a shape");  
    }  
}  
  
// Derived class  
class Circle : Shape  
{  
    public override void Draw()  
    {  
        Console.WriteLine("Drawing a circle");  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        // Runtime binding example  
        Shape shape = new Circle(); // Creating instance of derived class but of base class reference  
        shape.Draw(); // This will call the overridden method in Circle class at runtime  
    }  
}
```

方法覆盖：

*   在此示例中，该类定义了一个虚拟方法 ShapeDraw() 。
    
*   该类继承自该方法，并使用其自己的实现重写该方法 CircleShapeDraw() 。
    
*   当子类提供已在其超类 中定义的方法的特定实现时，将发生方法重写。
    
*   Shape中的方法使用相同的签名和返回类型重写 in 中的方法。Draw()CircleDraw()Shape
    

#### ** 运行时绑定：**

*   在该方法中，创建一个实例 ，并将其分配给 类型的引用。MainCircleShape
    
*   这是多态性 **（子类型多态性）的一个例子，后面的 i 节将对此进行解释 **，其中派生类 （） 对象可以被视为其基类 （） 类型。CircleShape
    
*   在运行时，当调用时，C# 运行时系统将确定对象 （） 的实际类型，并执行 中重写的方法。shape.Draw()CircleCircle
    
*   这称为运行时绑定或后期绑定，其中在运行时根据对象的实际类型决定调用哪个方法。
    

#### ** 参数多态性（泛型编程）：**

** 泛 型：** 允许编写函数或类，这些函数或类可以在编译时对各种数据类型进行操作，而无需知道特定类型。它通过对类型进行抽象来提供灵活性和代码可重用性。

```c#
using System;  
  
public class Stack<T>  
{  
    private T[] elements;  
    private int top;  
  
    public Stack(int size)  
    {  
        elements = new T[size];  
        top = -1;  
    }  
  
    public void Push(T item)  
    {  
        if (top == elements.Length - 1)  
        {  
            Console.WriteLine("Stack overflow!");  
            return;  
        }  
        elements[++top] = item;  
    }  
  
    public T Pop()  
    {  
        if (top == -1)  
        {  
            Console.WriteLine("Stack underflow!");  
            return default(T);  
        }  
        return elements[top--];  
    }  
  
    public void Print()  
    {  
        Console.WriteLine("Stack elements:");  
        for (int i = top; i >= 0; i--)  
        {  
            Console.WriteLine(elements[i]);  
        }  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        Stack<int> intStack = new Stack<int>(5);  
        intStack.Push(1);  
        intStack.Push(2);  
        intStack.Push(3);  
        intStack.Print();  
        Console.WriteLine("Popped item: " + intStack.Pop());  
  
        Stack<string> stringStack = new Stack<string>(3);  
        stringStack.Push("Hello");  
        stringStack.Push("World");  
        stringStack.Print();  
        Console.WriteLine("Popped item: " + stringStack.Pop());  
    }  
}
```

在此示例中：

*   我们定义了一个使用泛型类型参数的类Stack<T>
    
*   该类可以使用创建类实例时指定的任何数据类型。
    
*   我们演示了如何使用 int 和 string 类型来使用类。Stack<int>, Stack<string>
    
*   通过使用泛型，该类允许相同的实现使用不同的数据类型，从而提供灵活性和代码可重用性。
    

#### ** 亚型多态性（Inclusion Polymorphism）：**

方法覆盖： 使派生类的对象能够被视为其基类的对象，从而允许多态行为。当派生类继承自基类并提供其自己的某些方法的实现时，就会发生这种情况，从而重写基类方法的行为。

```c#
using System;  
  
// Interface  
public interface IShape  
{  
    void Draw();  
}  
  
// Class implementing the interface  
public class Circle : IShape  
{  
    public void Draw()  
    {  
        Console.WriteLine("Drawing a circle");  
    }  
}  
  
// Another class implementing the interface  
public class Rectangle : IShape  
{  
    public void Draw()  
    {  
        Console.WriteLine("Drawing a rectangle");  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        IShape shape1 = new Circle();  
        IShape shape2 = new Rectangle();  
  
        shape1.Draw(); // Calls the Draw method of Circle  
        shape2.Draw(); // Calls the Draw method of Rectangle  
    }  
}
```

*   类Circle和类RectangleI都实现接口，并提供自己的ShapeDraw方法实现。 
    
*   在运行时，我们创建 Circle 和 Rectangle 类的对象，并将它们分配给 IShape 类型的变量。
    

大多数设计模式使用子类型多态来实现灵活和鲁棒的类设计，这是一种非常强大的多态行为，如策略设计模式或观察者设计模式或装饰器设计模式等。

#### ** 强制多态性（铸造）：**

强制多态性，也称为隐式转换，是指编译器或运行时环境将一种数据类型自动转换为另一种数据类型。这种转换是在安全且合乎逻辑的情况下进行的，从而允许更灵活和方便的编程。

```c#
using System;  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        int num1 = 10;  
        double num2 = num1; // Implicit conversion from int to double  
  
        Console.WriteLine("num1: " + num1); // Outputs: num1: 10  
        Console.WriteLine("num2: " + num2); // Outputs: num2: 10.0  
    }  
}
```

在此示例中：

*   我们有一个初始化的整数变量num1，值为 10。
    
*   我们将 num1的值赋值给一个双精度变量num2。此赋值将触发从 int到 double的隐式转换。
    
*   编译器会自动将int值转换为double值，因为这样做是安全的，不会损失精度。
    
*   这种隐式转换允许我们将num2视为一个double，即使它最初是一个int，** 表明强制多态性。**
    

总结
--

面向对象编程中的多态性包括**编译时**和**运行时**行为。**编译时多态性涉及方法和运算符重载**，允许基于参数和运算符的多种行为。

通过方法重写实现的运行时多态性使子类能够提供自己的超类方法实现。其他形式包括**具有泛型的参数多态性、通过方法覆盖和接口的子类型多态性，以及用于隐式类型转换的强制多态性**。这些概念有助于提高软件开发中的代码灵活性、可重用性和适应性。