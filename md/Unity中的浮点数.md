> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/hjVNVJwXBLgzD1M-9rO2uw)

Unity   float f =0.1f 为什么 $"{f}" 输出的时候会是 0.100000001
```c#
C# 中的 $"{}" 是一个字符串插补（String Interpolation）的语法糖，用于方便地创建和修改字符串。
```

    在 $"{}" 的 {} 里面，我们可以直接放入变量，或者一些表达式。编译器会自动将其替换为相应的字符串。

    这是一个非常有用的特性，它使得拼接和格式化字符串更加简单直观。例如，我们可以非常方便地在字符串中插入变量的值：

```c#
int age = 20;
string name = "John";
string result = $"Hello, my name is {name} and I am {age} years old.";
```

    你可以在 {} 中放入变量, 编译器会将其替换成变量的值。但是，如果你在这个过程中遇到精度丢失，那可能是浮点数的精度问题。在 C#中，float 是 32 位的，能够精确到 7 位，而 double 是 64 位的，能精确到 15 位。这些都是不完全准确的，因为这些类型在内部是以二进制的形式存储的，只有某些十进制小数可以精确地转换为二进制小数。因此，在存储或转换时，可能会有一些轻微的舍入错误。

```c#
float f = 0.1f;
Console.WriteLine($"{f}");//0.100000001
```

    _**尽管你可能期望输出 0.1，但实际输出可能是 0.100000001 或类似的，这是因为 0.1 不能精确地表示为二进制小数。**_

    在数字系统中，某些十进制数无法精确地表示为二进制数。例如，十进制的 0.1 或 0.2 就不能被精确地表示为一个二进制的浮点数。

    让我们以 0.1 为例来说明一下：十进制下的 0.1 转换为二进制数是一个无限循环小数，

> 将十进制数 0.1 转换为二进制可以通过以下步骤进行近似计算：
>
> 1. 将小数部分乘以2，并取整数部分作为二进制的一位。重复这一步骤直到小数部分为0或者达到所需的精度。
>
> 具体步骤如下：
>
> - 0.1 * 2 = 0.2，整数部分为 0
> - 取小数部分 0.2，继续乘以2
> - 0.2 * 2 = 0.4，整数部分为 0
> - 取小数部分 0.4，继续乘以2
> - 0.4 * 2 = 0.8，整数部分为 0
> - 取小数部分 0.8，继续乘以2
> - 0.8 * 2 = 1.6，整数部分为 1
> - 取小数部分 0.6，继续乘以2
> - 0.6 * 2 = 1.2，整数部分为 1
> - 取小数部分 0.2，继续乘以2
> - 0.2 * 2 = 0.4，整数部分为 0
> - ...
>
> 这个过程会一直重复下去，因为 0.1 在二进制中是一个无限循环小数。因此，无法用有限位数的二进制小数来精确表示 0.1。

即 0.0001100110011001100110011...，对于这样的无限小数，计算机无法精确存储，会在一定的位数后进行截断或者四舍五入，这样就会产生精度误差，这是由浮点数的表示方法决定的。

    然而，某些十进制数是可以精准的被转换为二进制数的。比如，0.5、0.25、0.75 等。这是因为他们在二进制中为有限的小数。例如，0.5 在二进制中是 0.1，0.25 在二进制中是 0.01。这些小数在计算机中可以被精确表示。

    因此，在计算机编程中，一般不建议直接比较两个浮点数是否完全相等，因为可能会因为这些精度问题导致比较结果不准确。如果要比较两个浮点数是否相等，通常的做法是检查它们是否 “足够接近”，也就是它们之间的差的绝对值是否小于一个很小的正数。

    在涉及到需要高精度的计算或表示时你应该用 decimal 类型。另外，如果只是在输出的时候遇到了这种情况，你可以考虑格式化输出，比如用 "F2" 保留两位小数：

```c#
float f = 0.1f;
Console.WriteLine($"{f:F2}");
```

    但是请注意，这只会影响输出的显示，不会解决浮点数精度的根本问题。
