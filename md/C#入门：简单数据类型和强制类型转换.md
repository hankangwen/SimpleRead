> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247483954&idx=1&sn=051b38248e2828bdba87b36203f53274&chksm=ce07233df970aa2b362fc51885279ec83edc67acbdb3205776b50f1daa88ffaea8d164d5186e&scene=178&cur_album_id=3218779881132752901#rd)

 本期来讲讲 unity 的脚本语言 ---C#，C# 的简单数据类型及范围和强制类型转化的方法。这可是 unity 游戏开发必备技能。

**1. 简单数据类型**

**![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakkZajKribXSibKM2FMoUfVmdsH09E63SbtXYpbDpXByKZlHjf7MSSicxVia3oy953Nfuc7CYgGUalOKng/640)**

各个类型的范围：

> byte -> System.Byte 
> 
> (字节型，占 1 字节，表示 8 位正整数，范围 0 ~ 255)

> ushort -> System.UInt16
> 
>  (无符号短整型，占 2 字节，表示 16 位无符号整数，范围 0 ~ 65,535)

> uint -> System.UInt32 
> 
> (无符号整型，占 4 字节，表示 32 位无符号整数，范围 0 ~ 4,294,967,295)

> ulong -> System.UInt64 
> 
> (无符号长整型，占 8 字节， 表示 64 位无符号整数，范围 0 ~ 大约 10 的 20 次方)

> sbyte -> System.SByte 
> 
> (带符号字节型，占 1 字节，表示 8 位整数，范围 -128 ~ 127)

> short -> System.Int16
> 
>  (短整型，占 2 字节，表示 16 位整数，范围 -32,768 ~ 32,767)

> int -> System.Int32 
> 
> (整型，占 4 字节，表示 32 位整数，范围 -2,147,483,648 到 2,147,483,647)

> long -> System.Int64 
> 
> (长整型，占 8 字节， 表示 64 位有符号整数，范围大约 -(10 的 19) 次方 到 10 的 19 次方)

> float -> System.Single 
> 
> (单精度浮点型，占 4 个字节，范围（-3.40282347E+38F 到 3.40282347E+38F)

> double -> System.Double 
> 
> (双精度浮点型，占 8 个字节，范围（-1.7976931348623157E+308，1.7976931348623157E+308）
> 
> decimal->System.Decimal(表示十进制数，占 16 个字节)

> bool -> System.Boolean 
> 
> (布尔型，其值为 true 或者 false)

> char -> System.Char
> 
>  (字符型，占有两个字节，表示 1 个 Unicode 字符)

> string -> System.String 
> 
> (字符串型，表示一系列 Unicode 字符的不可变序列)

  

**2. 强制转换**

**2.1 括号法**

在变量前加上 (类型)

```c#
int num;
char c='A';
num=(int)c;
```

注意范围，超出范围会异常，正数变负数

bool 和 string 不能和其他类型进行强制转换

**2.2 Parse 法**

把字符串转化为对应的类型

语法：

变量类型. Parse("字符串")；

```c#
int num=int.Parse("123");
```

注意：字符串必须能够转换成对应类型并且范围要符合，否则报错

**2.3 Convert 类法**

更准确的对各个类型进行转换, 会四舍五入

语法：

Convert.To 目标类型 (变量或常量)

```c#
int a =Convert.ToInt32("12");

a=Convert.ToInt32(1.5556f);//a变成2，会四舍五入
a=Convert.ToInt32(true);//a变成1
//以下是其他类型的示例
sbyte sb=Convert.ToSByte("1");
short s=Convert.ToInt16("1");
int i=Convert.ToInt32("1");
long l=Convert.ToInt64("1");

byte b=Convert.ToByte("1");
ushort us=Convert.ToUInt16("1");
uint ui=Convert.ToUInt32("1");
ulong ul=Convert.ToUInt64("1");

float f=Convert.ToSingle("13.4");
double d=COnvert.ToDouble("13.4");
decimal de=Convert.ToDecimal("13.4");

bool bo=Convert.ToBoolean("true");
char c=Convert.ToChar("A");

string str=Convert.ToString(1000);
```

**2.4 其他类型转换为 string**

语法：

变量. ToString();

```c#
string str=1.ToString();
str='A'.ToString();
int a=20;
str=a.ToString();//str为"20"
```

