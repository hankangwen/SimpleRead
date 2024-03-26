> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/_pOnfUc5o-3uhtzfLOsawg)

在数字世界中，文件的完整性验证是一项至关重要的任务。MD5（Message-Digest Algorithm 5）是一种广泛使用的密码散列函数，它可以将任意长度的 “字节串” 映射为一个固定长度的 “大整数”。这个“大整数” 通常被表示为一个 32 位的十六进制数，也就是一个 MD5 值。通过比较文件的 MD5 值，我们可以确定文件是否在传输或存储过程中被篡改。

在 C# 中，我们可以使用 System.Security.Cryptography 命名空间下的 MD5CryptoServiceProvider 类来计算文件的 MD5 值。下面是一个简单的示例，演示了如何使用 C# 获取文件的 MD5 值。

首先，我们需要引入必要的命名空间：

```
using System;using System.IO;using System.Security.Cryptography;using System.Text;
```

然后，我们可以创建一个方法，用于计算文件的 MD5 值：

```
public static string GetFileMD5Hash(string filePath){    try    {        using (FileStream stream = File.OpenRead(filePath))        {            MD5 md5 = MD5.Create();            byte[] hashValue = md5.ComputeHash(stream);            // 将字节数组转换为十六进制字符串            StringBuilder hex = new StringBuilder(hashValue.Length * 2);            foreach (byte b in hashValue)            {                hex.AppendFormat("{0:x2}", b);            }            return hex.ToString();        }    }    catch (Exception ex)    {        throw new Exception("Error computing MD5 hash for file " + filePath, ex);    }}
```

在这个方法中，我们首先使用`File.OpenRead`方法打开文件，并创建一个`MD5`的实例。然后，我们调用`ComputeHash`方法计算文件的散列值，得到一个字节数组。最后，我们将这个字节数组转换为一个十六进制字符串，这就是文件的 MD5 值。

现在，你可以调用这个方法并传入文件的路径来获取文件的 MD5 值：

```
string filePath = @"C:\path\to\your\file.txt";string md5Hash = GetFileMD5Hash(filePath);Console.WriteLine("The MD5 hash of the file is: " + md5Hash);
```

请注意，虽然 MD5 在过去被广泛使用，但由于存在碰撞问题（即两个不同的输入可能产生相同的 MD5 值），现在对于安全性要求较高的场景，更推荐使用 SHA-256 或其他更安全的哈希算法。但是，对于一般的文件完整性校验，MD5 仍然是一个简单且有效的选择。

此外，处理文件时要确保文件路径正确，并且文件在读取过程中不会被其他程序修改，否则计算出的 MD5 值可能会不准确。同时，处理异常也很重要，以确保在文件不存在、无法访问或其他错误情况下能够优雅地处理。

通过上述方法，你可以轻松地在 C# 中获取文件的 MD5 值，从而验证文件的完整性。