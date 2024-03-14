> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/LLLLL__/article/details/112860102?ops_request_misc=&request_id=&biz_id=102&utm_term=Unity%E4%BD%BF%E7%94%A8RSA%E9%9D%9E%E5%AF%B9%E7%A7%B0%E5%8A%A0%E5%AF%86&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-112860102.142^v40^pc_rank_34_1,185^v2^control&spm=1018.2226.3001.4187)

### 一：前言

常用的文件[加密算法](https://so.csdn.net/so/search?q=%E5%8A%A0%E5%AF%86%E7%AE%97%E6%B3%95&spm=1001.2101.3001.7020)有：DES、AES、RSA、SHA-1、MD5.....  
.Net 自带了安全类库，在 System.Security.Cryptography 下有一些常用的加密算法  
其中 MD5 属于摘要算法，多用于检查文件是否有修改

### 二：加密算法介绍

——对称[加密](https://so.csdn.net/so/search?q=%E5%8A%A0%E5%AF%86&spm=1001.2101.3001.7020)  
对称加密算法有 AES、DES、3DES 等  
在对称加密算法中，密钥只有一个，加密和解密都使用相同的密钥

——非对称加密  
非对称加密算法有 [RSA](https://so.csdn.net/so/search?q=RSA&spm=1001.2101.3001.7020)、DSA、ECC 等  
在非对称加密算法中，需要两个密钥，一个公钥一个私钥  
如果使用公钥对数据进行加密，只有使用对应的私钥才能进行解密，如果使用私钥对数据进行加密，只有使用对应的公钥才能进行解密

——签名加密算法 (散列算法)  
签名加密算法有 SHA1、[MD5](https://so.csdn.net/so/search?q=MD5&spm=1001.2101.3001.7020)、HMAC 等  
签名加密算法不需要密钥，一般不可逆

### 三：AES 算法

需要注意的是加密后获得的 bytes 千万别用 UTF8 去获取字符串，不然会有信息损失，导致后面解密失败

```
using System;
using System.Security.Cryptography;
using System.Text;
 
/// <summary>
/// AES工具
/// </summary>
public class AESUtils
{
    const string AES_KEY = "dhjkfhskajflwoxj";
 
    /// <summary>
    /// AES加密
    /// </summary>
    /// <param >明文</param>
    public static string Encrypt(string content)
    {
        if (string.IsNullOrEmpty(content))
        {
            return null;
        }
        byte[] contentBytes = Encoding.UTF8.GetBytes(content);
        byte[] keyBytes = Encoding.UTF8.GetBytes(AES_KEY);
        RijndaelManaged rm = new RijndaelManaged();
        rm.Key = keyBytes;
        rm.Mode = CipherMode.ECB;
        rm.Padding = PaddingMode.PKCS7;
        ICryptoTransform ict = rm.CreateEncryptor();
        byte[] resultBytes = ict.TransformFinalBlock(contentBytes, 0, contentBytes.Length);
        return Convert.ToBase64String(resultBytes, 0, resultBytes.Length);
    }
 
    /// <summary>
    /// AES解密
    /// </summary>
    /// <param >密文</param>
    public static string Decrypt(string content)
    {
        if (string.IsNullOrEmpty(content))
        {
            return null;
        }
        byte[] contentBytes = Convert.FromBase64String(content);
        byte[] keyBytes = Encoding.UTF8.GetBytes(AES_KEY);
        RijndaelManaged rm = new RijndaelManaged();
        rm.Key = keyBytes;
        rm.Mode = CipherMode.ECB;
        rm.Padding = PaddingMode.PKCS7;
        ICryptoTransform ict = rm.CreateDecryptor();
        byte[] resultBytes = ict.TransformFinalBlock(contentBytes, 0, contentBytes.Length);
        return Encoding.UTF8.GetString(resultBytes);
    }
}
```

### 四：DES 算法

需要注意的是加密后获得的 bytes 千万别用 UTF8 去获取字符串，不然会有信息损失，导致后面解密失败

```
using System;
using System.Security.Cryptography;
using System.Text;
using System.IO;
using UnityEngine;
 
/// <summary>
/// DES工具
/// </summary>
public class DESUtils
{
    public const string DES_KEY = "lhwyjlyy";
 
    /// <summary>
    /// DES加密
    /// </summary>
    /// <param >明文</param>
    public static string Encrypt(string content)
    {
        if (string.IsNullOrEmpty(content))
        {
            return null;
        }
        byte[] contentBytes = Encoding.UTF8.GetBytes(content);
        byte[] keyBytes = Encoding.UTF8.GetBytes(DES_KEY);
        DESCryptoServiceProvider provider = new DESCryptoServiceProvider();
        provider.Key = keyBytes;
        provider.IV = keyBytes;
        MemoryStream ms = new MemoryStream();
        CryptoStream cs = new CryptoStream(ms, provider.CreateEncryptor(), CryptoStreamMode.Write);
        cs.Write(contentBytes, 0, contentBytes.Length);
        cs.FlushFinalBlock();
        return Convert.ToBase64String(ms.ToArray());
    }
 
    /// <summary>
    /// DES解密
    /// </summary>
    /// <param >密文</param>
    public static string Decrypt(string content)
    {
        if (string.IsNullOrEmpty(content))
        {
            return null;
        }
        byte[] contentBytes = Convert.FromBase64String(content);
        byte[] keyBytes = Encoding.UTF8.GetBytes(DES_KEY);
        DESCryptoServiceProvider provider = new DESCryptoServiceProvider();
        provider.Key = keyBytes;
        provider.IV = keyBytes;
        MemoryStream ms = new MemoryStream();
        CryptoStream cs = new CryptoStream(ms, provider.CreateDecryptor(), CryptoStreamMode.Write);
        cs.Write(contentBytes, 0, contentBytes.Length);
        cs.FlushFinalBlock();
        return Encoding.UTF8.GetString(ms.ToArray());
    }
}
```