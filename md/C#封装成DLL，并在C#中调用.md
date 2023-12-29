> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/Pei_hua100/article/details/108239225?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170372686516800211578659%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170372686516800211578659&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-108239225-null-null.142^v99^control&utm_term=C%23%E8%B0%83%E7%94%A8C%23%E7%9A%84DLL&spm=1018.2226.3001.4187)

## C#封装成DLL，并在C#中调用

**一、C# 封装成 DLL**

1、在 VS 中创建项目选择类库，命名 myDll

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODEzNTE0MzQ1MS0xMTU2NjY2MzQzLnBuZw?x-oss-process=image/format,png)

2、建立好项目后自动生成的代码如下：

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODEzNTI1MTk0My0zMTY0MzI1NjMucG5n?x-oss-process=image/format,png)

　　代码修改如下，添加自己要封装的 C# 代码，注意修饰符必须为 public

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace myDLL
{
    public class Class1
    {
        //封装的DLL函数
        public int add(int x, int y)
        {
            return x + y;
        }
    }
}
```

3、点击项目生成解决方案，然后在项目目录的 bin/debug 下即可发现封装好的 dll 文件

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODEzNTg1MjkxMS0xMjUyMTI5MjU2LnBuZw?x-oss-process=image/format,png)

注意：封装成 DLL 时程序集名字要跟程序里的 namespace 命名一致，如下图，否则应用 DLL 时无法引用成功。

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDIvMTQzMzc3MS0yMDE5MDIxMzExNTIwMDA5Mi0xNjI0NTM0ODk1LnBuZw?x-oss-process=image/format,png)

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDIvMTQzMzc3MS0yMDE5MDIxMzExNTI0NjY3Ny0yMDQ4MzQ0NDQ4LnBuZw?x-oss-process=image/format,png)

**二、C# 中调用该 DLL**

1、新建 WPF 项目 testUseMyDll, 在引用里添加 testMyDll 项目封装好的类库。

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MDIyNTE3MS00ODA3MzAzNDcucG5n?x-oss-process=image/format,png)

2、把 DLL 放在项目文件夹的 bin 目录的 Debug 目录下

3、点击项目里的引用添加 DLL

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MDYyNzIwMC0xNzY0MzEyMjgyLnBuZw?x-oss-process=image/format,png)

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MDkwOTI2NC0xNjQzOTgwOTQucG5n?x-oss-process=image/format,png)

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MDk0MzIwNy0xMzc2ODIwMDczLnBuZw?x-oss-process=image/format,png)

　　添加完后可以在应用里看到 DLL

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MTEzNDE5MS0xMDc2NTg4Mzg1LnBuZw?x-oss-process=image/format,png)

4、使用 using 包含进去

```
using myDLL;
```

5、添加一个测试按钮，按下就调用该 DLL 的函数

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MDQxMzU2Mi0xNTUwNTA4MzM1LnBuZw?x-oss-process=image/format,png)

　　跳转到按钮程序部分添加调用代码

```
Class1 test = new Class1(); //新建类
            int a = test.add(1,2); //调用DLL的函数
            Console.WriteLine(" a = " + a);//查看调用结果
```

6、运行结果如下

　　 ![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MTgzMjExOC0yMDQ2ODQ2NDE5LnBuZw?x-oss-process=image/format,png)

7、最后附上完成的测试代码图

　　![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWcyMDE4LmNuYmxvZ3MuY29tL2Jsb2cvMTQzMzc3MS8yMDE5MDEvMTQzMzc3MS0yMDE5MDExODE0MTk0OTkxMi0xOTA1MjQ3ODMxLnBuZw?x-oss-process=image/format,png)

说明：C# 封装的 DLL 是非标准的 DLL（托管类），不可以用 DllImport 调用，DllImport 是用来调用标准类（非托管类）的，这类 DLL 一般是用 C++ 写的