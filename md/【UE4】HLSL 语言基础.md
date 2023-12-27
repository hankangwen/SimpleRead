> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/139665164?utm_id=0)

【前言】
----

本篇相当基础，肯定有很多未提到的，待添加。

【导图】
----

![](https://pic3.zhimg.com/v2-6af7c3c2c938e7cefa69d398a095592a_r.jpg)![](https://pic3.zhimg.com/v2-ab63fe22a0dbb8be20ef686565d86912_r.jpg)

一、HLSL：High Level Shader Language 简介
------------------------------------

解释——高阶着色器语言

开发商——微软

运行平台——Direct 3D X

诞生由来：

Direct8.x 中，着色器是通过低级着色汇编语言来编写的，这样的程序更像是汇编式的指令集合，由于其效率低、可读性差、版本限制等缺点，迫切要求出现一门更高级的着色语言。到了 Direct3D9，HLSL（High Level Shading Language，高级渲染语言）应运而生了。

HLSL 的语法非常类似于 C 和 C++，学习起来是很方便的。

更多相关内容，请认准 MICROSOFT 官方 HLSL 文档，我只是一个小菜鸡~，本篇的知识点也比较**基础**，不像大佬们搞的那么高大上。（还是后期用到什么就进行添补什么）

虚幻官方只给了一个简单的案例

[Custom Expressions](https://link.zhihu.com/?target=https%3A//docs.unrealengine.com/en-US/Engine/Rendering/Materials/ExpressionReference/Custom/index.html)[HLSL - Win32 apps](https://link.zhihu.com/?target=https%3A//docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl)

### 【一些小建议】

强烈建议虚幻材质节点参考 Blender 的这个数学节点（展开后可用快捷键快速选择，如 a for add,s for subtract)

![](https://pic4.zhimg.com/v2-cc3b6b04da8f5440071418431f6d1997_r.jpg)

都是单个的节点然后选不同的枚举即可，而不是单个的节点就是单个的节点，只能删除，删除地同时线也断了，还需要重新连接。

或者是虚幻官方可以提供两种选择状态：

*   一种是像上图 Blender 当中的那样 ，选择枚举即可。
*   一种就是现在的这种版本

两种方式供开发者选择。

材质节点又没有右键 Replace 的选择选项。要不然删除之后，还得重新连线，非常的麻烦。

![](https://pic3.zhimg.com/v2-eddbce4796660b07bbef71cccb0556f6_r.jpg)![](https://pic3.zhimg.com/v2-0f833d294f203eec4d771668a6e5e4ce_r.jpg)

二、自定义 HLSL 代码 Custom 节点
-----------------------

### 【2.1】节点讲解

1. 分号断句, return 返回值。

2. 代码设置输入值的变量类型：（输入变量类型跟代码中写的不匹配会报错）

![](https://pic4.zhimg.com/v2-f24974bca675763791f53970d916c777_r.jpg)

3. 枚举选择输出值的变量类型：

![](https://pic1.zhimg.com/v2-a21445b17f4b09f717dd4513fc9f7f18_r.jpg)

4.Description 定义节点的名字

### 【2.2】开发环境相关

用 VS Code，新建一个 test.hlsl，后缀为 hlsl 即可，写完后复制粘贴到 Custom 的 Code 处（要不然一直需要 Shift+Enter 换行，能烦死你）

另外，它还提供了很多的插件，自己可以试着使用。

![](https://pic4.zhimg.com/v2-2334a380e8e11c40e056488871878ec7_r.jpg)![](https://pic1.zhimg.com/v2-f3a20cca767f1dd833bf6d5ab67fb438_r.jpg)

三、数学运算相关：
---------

### 【3.1】常用变量类型

*   float 1234

### 【3.2】常用数学符号

另外常用的符号有

*   +
*   *
*   -
*   /
*   ==（判断）
*   ++（本身加一）（B=float2(1,2); C=++B) ，放在变量前面.

### 【3.3】常用数学公式

这里拿 dot 向量点乘来举例，你可以把它换成其他数学公式。参考官方文档。（公式后双括号内加参数）

[Intrinsic Functions - Win32 apps](https://link.zhihu.com/?target=https%3A//docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions)

### 【3.4】举例

```
float A=dot(float3(B),float3(C)); //输出float 1 
return A;
```

![](https://pic3.zhimg.com/v2-4cea826babf598e067bedb09b23b68ba_r.jpg)![](https://pic4.zhimg.com/v2-4ca6f1627dcb4c56df8a21a182d56f1b_r.jpg)

四、变量相关
------

【4.1】注意事项
---------

1.  分号断句（注意中英文分号的区别）
2.  return 返回值
3.  多个参数用逗号，隔开（注意逗号中英文的区别）
4.  定义 float /2/3/4 变量类型 (用括号包住参数的名字）（注意是连在一块儿的，如 float2， 而不是 float 2 带空格这样子）

【4.2】常用变量定义
-----------

*   小括号前也要加上类型
*   大括号直接囊括值

```
float a=10; //Debug ScalarValues
float2 b=float2(1,2);
float3 c={1,2,3};
float4 d={1,2,3,4};
vector a={1,2,3,4};               //而我们直接使用Vector的话，就是表示为一种包含4个float的元素的类型(vector=float4)：
```

**【4.2.1】小括号——前面得加上相应的定义，如 float2、float3 之类的**

【错误做法】直接小括号括值

```
float2 b=(3,2);
return b;  // 取2

float3 c=(4,1,3);
return c; // 取3
```

![](https://pic4.zhimg.com/v2-1ccfb5c3bda4ef4534aa399bdd55d977_r.jpg)

【正确做法】后面加上值的类型

```
float2 b=float2(1,2);
return b;
```

![](https://pic3.zhimg.com/v2-b15d8a87c3cff9ca52c4200d63e0fbd2_r.jpg)

**【4.2.2】大括号——直接囊括定义相应正确的值**

注意后边不用加 float 1234 之类的。

```
float4 A= {1,2,3,4};
return A;
```

![](https://pic1.zhimg.com/v2-15f7c77606f4fe6d129bd5eda96c2c7c_r.jpg)

### 【4.3】Append Vector

当然你可以用 Append 的方式，如下，float4=float3+float1

```
float3 B=float3(1,0,1);
float4 A=float4(B,1);
return A;
```

![](https://pic2.zhimg.com/v2-8cbfc15ff435d2f66cf206d0f1bfd551_r.jpg)

【4.4】如何 Get 和 Set 参数的值
----------------------

相对应于蓝图 Variable 的 Ctrl Get 和 Alt Set。

1.  可以用 x、y、z、w，
2.  也可以用 r、g、b、a
3.  也可以用索引，【0】、【1】、【2】、【3】

```
float4 A={1,2,3,4};
float B=A.x;
float C=A.g;
float D=A[3];
A.a=10;
float E=A.a;
float4 F=float4 (B,C,D,E);
return F;
```

![](https://pic1.zhimg.com/v2-41c1a5d82e5178fdba7fc3df592ec0d4_r.jpg)

【4.5】Swizzle 取特定位的值
-------------------

关于 Set 的话，我们还可以直接编排，相对应于材质节点 Swizzle。

![](https://pic1.zhimg.com/v2-b7b0a9b314288063582db163cdec41bc_b.jpg)

```
float4 A={1,2,3,4};
float3 B=A.xzy;
float3 C=A.rrg;
return B+C;
```

![](https://pic1.zhimg.com/v2-7721db2f0899b2118cc272e5503f5244_r.jpg)![](https://pic4.zhimg.com/v2-0374b7a97fbd034f57ff724062d9c9eb_r.jpg)

五、结构体和数组
--------

【5.1】结构体 Structure
------------------

定义法：struct A{};

实例化：A a；

```
struct A
{
float2 B;
float2 C;
};
A a;
a.B=float2(1,2);
a.C=++a.B;
return a.C;
```

![](https://pic4.zhimg.com/v2-589cb5d4fbae61f334ee4aea8090e60f_r.jpg)

【5.2】数组 Array
-------------

定义法： float t [n];

```
float t[20];
t[1]=1;
t[2]=2;
t[10]=10;
return t[2]+t[10];
```

![](https://pic2.zhimg.com/v2-7a2d9dab26f93915e6ac2d2a723de0fd_r.jpg)![](https://pic1.zhimg.com/v2-6e14b44f78177839ea4c0e3361d6772c_r.jpg)

六、判断语句
------

判断语句：
-----

*   if、else
*   continue
*   break
*   switch

就只拿 if else 举例，其他跟 C/C++ 等编程语言差不多，自己可以直接套用进行测试。

```
float a=A;
if(a==0)
{
float b=1;
return b;
}
else
{
float b=2;
return b;
}
```

![](https://pic2.zhimg.com/v2-e04ebeeeeb81265a7917e3d02011ef55_r.jpg)![](https://pic3.zhimg.com/v2-25a2be5b19b39bd5c2a36f8a05fbdf86_r.jpg)

### 循环语句：

*   while loop
*   for loop

也是差不多，for loop 举例

```
float a=0;
for(i=0;i<10;i++)
{
a+=1;
}
return a ;
```

![](https://pic2.zhimg.com/v2-27c061a3bb326e2158ccb2c3f4b74759_r.jpg)

【其他】
----

还有很多其他像矩阵 matrix、贴图等，以后用到再添加（不用就不添加，皮~）。
----------------------------------------