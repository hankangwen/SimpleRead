> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/yao_hou/article/details/134471487)

#### 文章目录

*   [一、创建 C++ dll 项目](#C_dll_4)
*   [二、C# 程序员调用 C++ dll](#CC_dll_104)
*   [三、C++ 与 C# 数据类型对应](#CC_196)
*   *   [基本数据类型对应表](#_199)
    *   [C++ 指针类型与 C# 类型](#CC_263)

在使用 [C# 开发](https://so.csdn.net/so/search?q=C%23%E5%BC%80%E5%8F%91&spm=1001.2101.3001.7020)客户端时，有时需要调用 C++ dll，本篇博客来介绍 C# 程序如何调用 C++ dll。

一、创建 C++ dll 项目
---------------

首先使用 [VS2022](https://so.csdn.net/so/search?q=VS2022&spm=1001.2101.3001.7020) 创建 C++ dll 项目，具体步骤如下：

（1）选择 Windows 桌面向导，点击下一步, 取项目名，例如我的 dll 项目名是 libMath  
![](https://img-blog.csdnimg.cn/8bbacd0bf25e40dda4ca3af01bcc4440.png)

（2）选择动态项目，勾选导出符号

![](https://img-blog.csdnimg.cn/9768ddc4569141d5a2aec055cc9b9280.png)

（3）编写动态代码，代码如下：

libMath.h

```
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBMATH_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBMATH_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LIBMATH_EXPORTS
#define LIBMATH_API __declspec(dllexport)
#else
#define LIBMATH_API __declspec(dllimport)
#endif

// 此类是从 dll 导出的
class LIBMATH_API ClibMath {
public:
	ClibMath();
	int Add(int a, int b);
	int Sub(int a, int b);
};

// 由于需要给C#调用，为了方便导出类，添加了函数进行导出，并且需要加extern "C"
extern "C" {
    LIBMATH_API ClibMath* CreateMyClass();

    LIBMATH_API void DeleteMyClass(ClibMath* obj);

    LIBMATH_API int CallAdd(ClibMath* obj, int num1, int num2);

    LIBMATH_API int CallSub(ClibMath* obj, int num1, int num2);
}
```

注意: 如果想导出 C++ 类在 C# 中使用，由于语言语法差异，C++ 类在 C# 中无法使用，因为 C++ 类通常包含成员函数、构造函数、析构函数等，而 C# 与 C++ 在处理这些方面存在差异。一种可行的方法是在 C++ 类中添加一些导出函数，这样它们可以通过 C# 调用。这些函数可以执行类的实例化、调用成员函数等操作。确保使用 extern “C” 以避免名称修饰, 因为 C++ 函数在编译时，会在原有的函数名前后添加一些符号，例如 add 函数在编译后可能变成了 @xxasd_sfdf_add_xxx 之类的，但是使用`extern "C"` 后就是按照 C 语言的方式导出，函数名不变，例如我添加的一些类导出方法：

```
// 由于需要给C#调用，为了方便导出类，添加了函数进行导出，并且需要加extern "C"
extern "C" {
    LIBMATH_API ClibMath* CreateMyClass();

    LIBMATH_API void DeleteMyClass(ClibMath* obj);

    LIBMATH_API int CallAdd(ClibMath* obj, int num1, int num2);

    LIBMATH_API int CallSub(ClibMath* obj, int num1, int num2);
}
```

libMath.cpp

```
// libMath.cpp : 定义 DLL 的导出函数。
//

#include "framework.h"
#include "libMath.h"

// 这是已导出类的构造函数。
ClibMath::ClibMath()
{
    return;
}

int ClibMath::Add(int a, int b)
{
    return a + b;
}

int ClibMath::Sub(int a, int b)
{
    return a - b;
}

LIBMATH_API ClibMath* CreateMyClass() {
    return new ClibMath();
}

LIBMATH_API void DeleteMyClass(ClibMath* obj) {
    delete obj;
}

LIBMATH_API int CallAdd(ClibMath* obj, int num1, int num2) {
    return obj->Add(num1, num2);
}

LIBMATH_API int CallSub(ClibMath* obj, int num1, int num2) {
    return obj->Sub(num1, num2);
}
```

二、C# 程序员调用 C++ dll
------------------

生成 dll 后可以用命令拷贝到 C# 项目的 exe 目录，或者手动拷贝，然后在 C# 代码中使用`import`导入即可，如下图：  
![](https://img-blog.csdnimg.cn/5284880b015f446cb67e73575d5aab14.png)

代码如下：

```
/*

C# 调用 C++ dll 

将libMath.dll放到CSharpCallCppDLL/bin/Debug目录下

*/
 


using System.Runtime.InteropServices;

namespace CSharpCallCppDLL
{
    internal class Program
    {
        private static IntPtr myClassInstance;  // 定义C++类的实例，用于后面的调用

        [DllImport("libMath.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateMyClass();

        [DllImport("libMath.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DeleteMyClass(IntPtr obj);

        [DllImport("libMath.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int CallAdd(IntPtr obj, int num1, int num2);

        [DllImport("libMath.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int CallSub(IntPtr obj, int num1, int num2);

        static void Main(string[] args)
        {
            Console.WriteLine("测试C#调用C++");

            myClassInstance = CreateMyClass();
            int nRet = CallAdd(myClassInstance, 1, 2);
            Console.WriteLine($"1 + 2 = {nRet}");

            // 清理C++内存
            DeleteMyClass(myClassInstance);
        }
    }
}
```

注意：由于 C++ 的编译特点，C++ 项目有 Debug、Release、x86、x64 之分，特别需要注意 dll 的放置位置，放错了可能就链接失败了，以及 C++ 在 x64 于 x86 下的指针 4 字节与 8 字节的区分，这些都会导致在 C# 调用 C++ dll 代码失败或者 crash。**此外，确保你的应用程序具有访问和加载 DLL 所需的适当权限。**

运行结果如下：  
![](https://img-blog.csdnimg.cn/0cbf908f25004a2ebf04c40f6fdffd5d.png)  
在 C# 中可以创建一个对应 C++ 类的 C# 包装类，使用 DllImport 属性声明导出函数，例如下面的代码：

```
public class MyClassWrapper {
    private IntPtr myClassInstance;

    [DllImport("YourCppLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr CreateMyClass();

    [DllImport("YourCppLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void DeleteMyClass(IntPtr obj);

    [DllImport("YourCppLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void CallMyMethod(IntPtr obj);

    public MyClassWrapper() {
        myClassInstance = CreateMyClass();
    }

    ~MyClassWrapper() {
        DeleteMyClass(myClassInstance);
    }

    public void MyMethod() {
        CallMyMethod(myClassInstance);
    }
}
```

使用 C# 包装类：

在 C# 中，可以实例化 MyClassWrapper 类，并调用其中的方法，这将转发调用到 C++ 类的实例。

```
MyClassWrapper myInstance = new MyClassWrapper();
myInstance.MyMethod();
```

这是一个简单的例子，实际情况可能更为复杂，特别是在处理类的继承、虚函数等方面。确保在进行实际应用时进行充分的测试，以确保互操作性正常运作。

三、C++ 与 C# 数据类型对应
-----------------

C# 在调用 C++ DLL 时，需要通过 P/Invoke 技术来完成。P/Invoke 是. NET Framework 用于调用非托管代码库的一种方式。在这个过程中，我们需要处理两种语言之间的数据类型转换，因为它们的数据类型不完全一致。

### 基本数据类型对应表

以下是 C++ 和 C# 之间的一些常见数据类型的对应表（请注意，这并不是一个完全的列表，只是一些常见类型的示例）：

<table><thead><tr><th>C++</th><th>C#</th></tr></thead><tbody><tr><td><code>bool</code></td><td><code>bool</code></td></tr><tr><td><code>char</code> / <code>BYTE</code></td><td><code>byte</code></td></tr><tr><td><code>short</code></td><td><code>short</code></td></tr><tr><td><code>int</code></td><td><code>int</code></td></tr><tr><td><code>long</code></td><td><code>int</code></td></tr><tr><td><code>float</code></td><td><code>float</code></td></tr><tr><td><code>double</code></td><td><code>double</code></td></tr><tr><td><code>char*</code> (C-style string)</td><td><code>string</code></td></tr><tr><td><code>wchar_t*</code> (Unicode string)</td><td><code>string</code></td></tr></tbody></table>

在 C# 中，我们使用`DllImport`特性来声明对 C++ DLL 的函数调用。例如，如果我们有一个 C++ 函数如下：

```
extern "C" __declspec(dllexport) int Add(int a, int b);
```

在 C# 中，我们可以这样声明和使用它：

```
[DllImport("MyLibrary.dll")]
public static extern int Add(int a, int b);

public void Main()
{
    int result = Add(2, 3);
}
```

对于更复杂的数据类型，如结构体和类，我们需要在 C# 中创建对应的类或结构体来匹配。例如，如果我们有一个 C++ 结构体：

```
struct Person
{
    char* name;
    int age;
};
```

我们可以在 C# 中创建一个类来匹配它：

```
[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
public class Person
{
    public string name;
    public int age;
}
```

注意我们使用了`StructLayout`特性并设置`CharSet`为`CharSet.Ansi`，因为 C++ 中的`char*`类型对应于 ANSI 字符串。

在处理 C++ DLL 中的函数时，也需要注意函数调用的约定（`cdecl`，`stdcall`等）。默认情况下，C# 假定被调用的函数使用`stdcall`调用约定。如果函数使用不同的调用约定，你需要在`DllImport`特性中指定它，例如：

```
[DllImport("MyLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
```

在处理更复杂的情况，如回调函数，复杂的数据结构，和 C++ 类时，可能需要更多的处理。处理这些情况通常需要对两种语言都有深入的理解，并且可能需要手动管理内存。

### C++ 指针类型与 C# 类型

C++ 指针在 C# 中的相应类型取决于指针指向的数据类型和你如何打算使用它。这里有几种常见的情况：

1.  **指向简单类型的指针**：如果指针指向一个简单的数值类型（如`int*`、`float*`等），你可以在 C# 中使用`IntPtr`类型来表示它。你可以使用`Marshal`类中的方法（如 `Marshal.ReadInt32`、`Marshal.WriteInt32`等）来读取或写入指针指向的数据。
    
2.  **指向字符串的指针**：如果指针指向一个字符串（如`char*`或`wchar_t*`），你可以在 C# 中使用`string`类型来表示它。在`DllImport`特性中，你可以使用`MarshalAs`特性来指定字符串的编码方式。
    
3.  **指向结构体的指针**：如果指针指向一个结构体，你可以在 C# 中创建一个对应的类或结构体，并使用`ref`关键字或者`IntPtr`类型来表示指针。使用`ref`关键字时，.NET 运行时会自动处理内存管理。使用`IntPtr`时，你需要手动管理内存。
    

例如，假设你有一个 C++ 函数如下：

```
extern "C" __declspec(dllexport) void ModifyPerson(Person* person);
```

在 C# 中，你可以这样使用它：

```
[DllImport("MyLibrary.dll")]
public static extern void ModifyPerson(ref Person person);

// 或者
[DllImport("MyLibrary.dll")]
public static extern void ModifyPerson(IntPtr personPtr);
```

4.  **指向数组的指针**：如果指针指向一个数组，你可以在 C# 中使用数组类型来表示它。你也可以使用`MarshalAs`特性来指定数组的大小。

对于更复杂的情况，例如指向函数的指针（函数指针），你可能需要使用`Marshal.GetDelegateForFunctionPointer`方法将其转换为 C# 委托。

需要注意的是，当你使用`IntPtr`来管理指针时，你需要自己负责内存的分配和释放。你可以使用`Marshal.AllocHGlobal`和`Marshal.FreeHGlobal`方法来分配和释放非托管内存。