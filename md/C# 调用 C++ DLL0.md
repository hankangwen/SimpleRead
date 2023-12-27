> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/m0_37251750/article/details/81280016)

#### C# 调用 C++ 的 dll 总归可以有两种方法：

1、非托管 C++ 创建的 dll 库，需要用静态方法调用；

2、直接使用 CLR，生成托管 C++dll 库。

很多时候在项目中需要通过 C++ 调用 C# 的 dll, 或者反过来调用。首先明白一个前提：C# 是托管型代码。C++ 是非托管型代码。  
托管型代码的对象在托管堆上分配内存，创建的对象由虚拟机托管。（C# ）  
非托管型代码对象有实际的内存地址，创建的对象必须自己来管理和释放。（C++）

##### 托管 C++dll 库方式

**1、打开 VS 创建 C++ 项目 "C++_CScharp_DLL"**

![](https://img-blog.csdnimg.cn/8ebcb30014aa46a589cb4d46a97f0dd8.png)

点击确定之后接着点击下一步：

![](https://img-blog.csdnimg.cn/img_convert/619426585cce1a97cb708758866eaae5.png)

然后选择应用程序和附加选项：  
![](https://img-blog.csdnimg.cn/b4c8fa21d0a24742bc3d3ecbd1a987a6.png)

点击完成，C++ 的项目就新建好了。

**2、添加代码文件**

右键项目，添加类，如下图所示：

![](https://img-blog.csdnimg.cn/img_convert/8699a67c30e0892e77b7ce83165b45ec.png)

添加类之后会打开添加文件对话框，点击添加即可，如下图所示：

![](https://img-blog.csdnimg.cn/26fea93fca5547eb8edb19e0b27a7771.png)

点击确定之后进去下一个对话框，填写文件名 Function, 如下图所示：

![](https://img-blog.csdnimg.cn/0b6d1facdd3846b6ab7e08ab18657528.png)

添加好后会生成 h 文件和 cpp 文件，如下图所示：

![](https://img-blog.csdnimg.cn/img_convert/92686aa418a059aff0f108753c6c2e7e.png)

Function 类文件代码如下：

```
//Function.h

#pragma once
#include <string>
public ref class Function
{
public:
    Function(void);
    ~Function(void);
    int menber;
    int menberFuncAdd(int a,int b);
    System::String^ say(System::String^ str);
};

//.cpp
#include "Function.h"
Function::Function(void)
{
}
Function::~Function(void)
{
}

int Function::menberFuncAdd(int a,int b)
{
   return a+b;
}
System::String^ Function::say(System::String^ str)
{
   return str;
}
```

填写完后 Function.h 文件会报错, 错误类型如下：

![](https://img-blog.csdnimg.cn/img_convert/ba6576e1a017d27704fc0625695a2644.png)

这里需要在 C++ 项目里面设置，让动态库受到公共语言运行时的支持。如下图所示：

打开项目属性  
![](https://img-blog.csdnimg.cn/4ea94b9885884c23a414d2e89c836cbc.png)  
![](https://img-blog.csdnimg.cn/img_convert/6512019b295d3bdd6fb200054b5d656a.png)  
修改完成后点击项目右键生成 DLL，看是否报错，成功结果如下图：  
![](https://img-blog.csdnimg.cn/img_convert/ef61e3acf695da4391b81930d1676ee1.png)

**3、添加测试程序：**

在该解决方案中添加测试程序：  
![](https://img-blog.csdnimg.cn/img_convert/439d2423058b723c19908e96f1df8fc5.png)  
添加一个 C# 控制台测试程序：  
![](https://img-blog.csdnimg.cn/img_convert/67bb233a27c348fd323d39f1718770f5.png)

添加完后设为启动项：  
![](https://img-blog.csdnimg.cn/img_convert/90187913f555196bac2df4a2160eaaa7.png)  
添加引用：  
![](https://img-blog.csdnimg.cn/21b9ef0d6cfd46c4ae9a3110f436c0db.png)

将 C++ 项目添加到 C# 的项目中：  
![](https://img-blog.csdnimg.cn/fd927752219442728cc2e0febf9afee3.png)  
**4、编写测试代码**

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            Function fun = new Function();
            Console.WriteLine(fun.menberFuncAdd(1, 2));
            Console.WriteLine(fun.say("Hello World"));
            Console.ReadKey();
        }
    }
}
```

##### 非托管 C++dll 库

非托管模式从功能上来说，只支持函数调用，直接调用 C++ 类库中的公共方法，在被导出的函数前面一定要添加额 extern “C 来指明导出函数的时候使用 C 语言方式编译和链接的，这样保证函数定义的名字相同，否则如果默认按 C++ 方式导出，那个函数名字就会变得乱七八糟，我们的程序就无法找到入口点了。

"__declspec(dllexport)“意思是将后面修饰的内容定义为 DLL 中要导出的内容。当然你也可以不使用这个宏，可以直接将”__declspec(dllexport)" 写在要导出的函数前面。C++ 中定义如下：  
`extern "C" __declspec(dllexport) int __stdcall Add(int n1, int n2);`  
在 C# 中，调用如下：

[DllImport(“SampleCppWrapper.dll”)]

private static extern int Add(int n1, int n2);

**注意：**

在编译 C++DLL 之前，需要做以下配置，在项目属性对话框中选择 "C/C++“|“Advanced”，将 Compile AS 选项的值改为"C++”。然后确定，并编译。

![](https://img-blog.csdnimg.cn/53811937be98478b8ac2e57752cf0326.png)

以下为摘录例子：

1、 调用 C++ 类库中的类的方法

C# 不能直接调用 C++ 类库中的类，需要一种变通的解决方式，通过再做一个 C++ 类库把要调用的类成员方法暴露出来，比如下面这个 C++ 类：

```
//SampleCppClass.h
#pragma once
class __declspec(dllexport) SampleCppClass
{
public:
    SampleCppClass(void);
    ~SampleCppClass(void);
    
    int Add(int n1, int n2);
    int Sub(int n1, int n2);
};

//SampleCppClass.cpp
#include "SampleCppClass.h"
SampleCppClass::SampleCppClass(void)
{
}
SampleCppClass::~SampleCppClass(void)
{
}
int SampleCppClass::Add(int n1, int n2)
{
    return n1 + n2;
}
int SampleCppClass::Sub(int n1, int n2)
{
    return n1 - n2;
}
```

我们要调用 SampleCppClass 中的 Add 和 Sub 两个方法，所以我们再写一个 C++ 类库，通过公共方法间接调用类成员方法：

```
//SampleCppWrapper.h
#pragma once

#include "..\SampleCppClass\SampleCppClass.h"
namespace SampleCppWrapper
{
    extern "C" __declspec(dllexport) int __stdcall Add(int n1, int n2);
    extern "C" __declspec(dllexport) int __stdcall Sub(int n1, int n2);
}

//SampleCppWrapper.cpp
#include "SampleCppWrapper.h"
namespace SampleCppWrapper
{
    SampleCppClass* g_pObj = new SampleCppClass();
    int __stdcall Add(int n1, int n2)
    {
        return g_pObj->Add(n1, n2);
    }

    int __stdcall Sub(int n1, int n2)
    {
        return g_pObj->Sub(n1, n2);
    }
}
```

在 C# 中，再调用 SampleCppWrapper.dll 中的公共方法：

```
[DllImport("SampleCppWrapper.dll")]
private static extern int Add(int n1, int n2);
[DllImport("SampleCppWrapper.dll")]
private static extern int Sub(int n1, int n2);
```

**3、 使用 C++ 类库中的回调函数**

C++ 的回调函数是一种事件响应机制，和 C# 的委托相似，比如一个 C++ 类中的回调函数：

```
// SampleCppClass.h
#pragma once

typedef void (*LoopCallback)(void* pContext);

class __declspec(dllexport) SampleCppClass
{
public:
    SampleCppClass(void);
    ~SampleCppClass(void);
    
    void SetCallbackFunc(LoopCallback callback);
    void SetCallbackContext(void* pContext);
    void Loop();
private:
    LoopCallback m_callback;
    void* m_pContext;
};

// SampleCppClass.cpp
#include "SampleCppClass.h"

SampleCppClass::SampleCppClass(void)
{
}

SampleCppClass::~SampleCppClass(void)
{
}

void SampleCppClass::SetCallbackFunc(LoopCallback callback)
{
    m_callback = callback;
}

void SampleCppClass::SetCallbackContext(void* pContext)
{
    m_pContext = pContext;
}

void SampleCppClass::Loop()
{
    for (int i=0; i<10; i++)
    {
        if (m_callback != NULL)
        {
            m_callback(m_pContext);
        }
    }
}
```

导出方法文件中添加：

```
//.h
#pragma once
#include "..\SampleCppClass\SampleCppClass.h"
namespace SampleCppWrapper
{
    typedef void (__stdcall *LoopCallbackWrapper)(void* pContext);

    extern "C" __declspec(dllexport) void __stdcall SetCallbackFunc(LoopCallbackWrapper callback);
    extern "C" __declspec(dllexport) void __stdcall SetCallbackContext(void* pContext);
    extern "C" __declspec(dllexport) void __stdcall Loop();
}

// .CPP
#include "SampleCppWrapper.h"
namespace SampleCppWrapper
{
    LoopCallbackWrapper g_callbackWrapper;
    SampleCppClass* g_pObj = new SampleCppClass();

    void LoopCallbackFunc(void* pContext);

    void __stdcall SetCallbackFunc(LoopCallbackWrapper callback)
    {
        g_callbackWrapper = callback;
        g_pObj->SetCallbackFunc(LoopCallbackFunc);
    }

    void __stdcall SetCallbackContext(void* pContext)
    {    
        g_pObj->SetCallbackContext(pContext);
    }

    void __stdcall Loop()
    {
        g_pObj->Loop();
    }

    void LoopCallbackFunc(void* pContext)
    {
        if (g_callbackWrapper != NULL)
        {
            g_callbackWrapper(pContext);
        }
    }
}
```

C# 中调用：

```
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SampleCsTest
{
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential)]
        private class Context
        {
            public Form1 Form { get; set; }
        }

        private delegate void LoopCallbackHandler(IntPtr pContext);
        private static LoopCallbackHandler callback = LoopCallback;

        [DllImport("SampleCppWrapper.dll")]
        private static extern void SetCallbackFunc(LoopCallbackHandler callback);
        [DllImport("SampleCppWrapper.dll")]
        private static extern void SetCallbackContext(IntPtr pContext);
        [DllImport("SampleCppWrapper.dll")]
        private static extern void Loop();

        private Context ctx = new Context();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SetCallbackFunc(callback);
            ctx.Form = this;
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(ctx));
            Marshal.StructureToPtr(ctx, ptr, false);
            SetCallbackContext(ptr);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Loop();
        }

        private static void LoopCallback(IntPtr pContext)
        {
            Context ctx = (Context)Marshal.PtrToStructure(pContext, typeof(Context));
            ctx.Form.textBox1.Text += "callback" + Environment.NewLine;
        }
    }
}
```

以上为非托管方式简单参数的传递，实际使用过程中，可能参数类型会复杂很多，这牵涉到 C# C++ 之间的参数转换及 C# 语法对托管代码的编写，具体做一些项目时，肯定会比例子情况复杂的多，那就需要对各种参数传递及转换好好了解一番，如果解决了各种情况参数传递问题，基本 C# 调用非托管 C++dll 没有其它复杂问题。