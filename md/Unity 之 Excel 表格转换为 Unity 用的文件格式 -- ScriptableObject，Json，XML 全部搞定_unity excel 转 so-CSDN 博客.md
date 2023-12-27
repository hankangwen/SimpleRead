> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/Czhenya/article/details/119449823)

#### Unity 之 Excel 表格转换为 Unity 用的文件格式 -- ScriptableObject，Json，[XML](https://so.csdn.net/so/search?q=XML&spm=1001.2101.3001.7020) 全部搞定

*   [前言](#_2)
*   [一，准备工作](#_6)
*   *   [1.1 确认表格表头](#11__8)
    *   [1.2 读取 Excel](#12_Excel_28)
    *   [1.3 存储数据](#13__69)
    *   [1.4 配置文件类](#14__145)
*   [二，转换为 ScriptableObject](#ScriptableObject_176)
*   [三，转换为 Json](#Json_226)
*   [四，转换为 XML](#XML_285)
*   [五，使用小结](#_359)

前言
--

最近工作中遇到的一个问题，其他同事在网上抓来的数据保存为 Excel 表格，需要在 Unity 中进行使用其中的数据进行开发。有些经验的同学都知道 Unity 是可以对 Excel 进行操作的，由于我 Excel 并不是 Unity 中常用的数据格式，并且相同数量级的情况下其他数据格式会比 Excel 更节省内存空间，于是有了这篇文章 – Excel 表格转换为 Unity 用的文件格式。由于需求和个人习惯的不同，我这里为大家提供了转换为三种格式的方法 – ScriptableObject，Json，XML。

一，准备工作
------

### 1.1 确认表格表头

既然是 Excel 进行格式转换，首先要有一个 Excel 表格吧，所以新建一个 Excel：（注意：后缀是. xlsx）

![](https://img-blog.csdnimg.cn/img_convert/1118c2343f3ccd1910609da8442f332d.png)

模拟数据编写如下：

![](https://img-blog.csdnimg.cn/img_convert/17c7459708fd5cd3c0924c2d39a21781.png)

这时表头就确定好了：

<table><thead><tr><th>任务 ID</th><th>任务描述</th><th>任务奖励</th></tr></thead><tbody><tr><td>task_id</td><td>task_describe</td><td>task_reward</td></tr></tbody></table>

### 1.2 读取 Excel

*   导入用到的 dll 库

没有的童鞋文末获取：  
![](https://img-blog.csdnimg.cn/img_convert/76e90a0cb819f90c15b6058e6c71c7d4.png)

*   引用命名空间：

```
using Excel;
```

*   编写读取方法：

```
/// <summary>
/// 处理Excel工具类
/// </summary>
public class ExcelTool
{
    /// <summary>
    /// 读取excel文件内容
    /// </summary>
    /// <param >文件路径</param>
    /// <param >行数</param>
    /// <param >列数</param>
    /// <returns></returns>
    static DataRowCollection ReadExcelContext(string filePath, ref int columnNum, ref int rowNum)
    {
        FileStream stream = File.Open(filePath, FileMode.Open, FileAccess.Read, FileShare.Read);
        // Debug.Log(stream == null);
        IExcelDataReader excelReader = ExcelReaderFactory.CreateBinaryReader(stream);
        DataSet result = excelReader.AsDataSet();
        // Tables[0] 下标0表示excel文件中第一张表的数据
        columnNum = result.Tables[0].Columns.Count;
        rowNum = result.Tables[0].Rows.Count;
        return result.Tables[0].Rows;
    }
}
```

### 1.3 存储数据

按照 1.1 确认的表头，写一个数据类：

```
/// <summary>
/// 数据序列化类 -- 和Excel列一一对应
/// </summary>
[System.Serializable]
public class ExcelItem
{
    public int task_id;
    public string task_describe;
    public string task_reward;
}
```

再添加一个数据管理类，作为读出来的所有数据的和，最后也是将它转换为我们要存储的格式。

一开始使我是这样写的：

```
public class ExcelManager
{
    public static ExcelItem[] dataArray;
}
```

不过后来为了兼容转换为 ScriptableObject 格式改成了如下写法：

```
public class ExcelManager : ScriptableObject
{
    public ExcelItem[] dataArray;
}
```

最后转化格式的原理是一样的，只是在调用上略有不同。

有了上面两个类之后，我们将在 Excel 中读出来的数据存储起来，在`ExcelTool`类中编写方法：

```
/// <summary>
/// 读取表数据，生成对应的数组
/// </summary>
/// <param >excel文件全路径</param>
/// <returns>Item数组</returns>
public static ExcelItem[] CreateItemArrayWithExcel(string filePath)
{
    //获得表数据
    int columnNum = 0, rowNum = 0;
    Debug.Log(filePath);
    DataRowCollection collect = ReadExcelContext(filePath, ref columnNum, ref rowNum);
    Debug.Log("读取到数据表 列数 columnNum ： " + columnNum + " ，行数 rowNum： " + rowNum);
    // 第一行是标题（头）
    //for (int i = 0; i < columnNum; i++)
    //{ 
    //    rowTitleList.Add(collect[0][i].ToString());
    //}
    //第二行开始才是数据
    ExcelItem[] array = new ExcelItem[rowNum - 1];
    for (int i = 1; i < rowNum; i++)
    {
        ExcelItem item = new ExcelItem();
        //解析每列的数据
        item.task_id = int.Parse(collect[i][0].ToString());
        item.task_describe = collect[i][1].ToString();
        item.task_reward = collect[i][2].ToString();
        array[i - 1] = item;
    }
    return array;
}
```

至此在 Excel 中的所有数据，都被保存到`ExcelManager` 中 `ExcelItem[]` 类型的数组`dataArray` 中了。

### 1.4 配置文件类

为了方便后续使用，我定义了一个配置文件类，用来存储读取 Excel 文件路径，文件名 和保存其他格式文件的路径和文件名称，这样以后有路径更改的时候，只需要在这个类中进行修改就可以了。

```
public class ExcelConfig
{
    /// <summary>
    /// 存放excel表文件夹的的路径，本例Excel表放在了"Assets/Excels/"当中
    /// </summary>
    public static readonly string excelsFolderPath = Application.dataPath + "/ReadExcel/";

    /// <summary>
    /// 要读取的Excel文件名称 -- 后缀为xlsx
    /// </summary>
    public static readonly string excelName = "TaskConfig.xlsx";

    /// <summary>
    /// 存放Excel转化后文件的文件夹路径
    /// </summary>
    public static readonly string assetPath = "Assets/ReadExcel/";

    /// <summary>
    /// 保存处理后数据文件名称
    /// </summary>
    public static readonly string saveName = "TaskConfig";
}
```

二，转换为 ScriptableObject
----------------------

在编辑器拓展中处理格式转换，这样有数据更新，就只需要替换 Excel 文件，然后点点按钮就可以更新文件了。

创建 "Editor" 文件夹，在其下创建 “ExcelBuild” 脚本，编写拓展方法代码如下:

```
using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Xml;
using UnityEditor;
using UnityEngine;

// <summary>
/// 编辑器扩展 将xlsx文件转换为其他格式
/// </summary>
public class ExcelBuild : Editor
{
    /// <summary>
    /// 转换为 ScriptableObject
    /// </summary>
    [MenuItem("CustomEditor/CreateExcelAsset")]
    public static void CreateItemAsset() {
        ExcelManager excelManager = CreateInstance<ExcelManager>();
        //赋值
        excelManager.dataArray = ExcelTool.CreateItemArrayWithExcel(ExcelConfig.excelsFolderPath + ExcelConfig.excelName);

        // 确保文件夹存在
        if(!Directory.Exists(ExcelConfig.assetPath)) {
            Directory.CreateDirectory(ExcelConfig.assetPath);
        }
 
        // asset文件的路径 要以"Assets/..."开始，否则CreateAsset会报错
        string assetPath = string.Format("{0}{1}.asset", ExcelConfig.assetPath, ExcelConfig.saveName);
        // 生成一个Asset文件
        AssetDatabase.CreateAsset(excelManager, assetPath);
        AssetDatabase.SaveAssets();
        
        AssetDatabase.Refresh();
    }
}
```

最后点击 “CustomEditor” --> “CreateExcelAsset” 既可以得到. asset 格式的文件了：  
![](https://img-blog.csdnimg.cn/img_convert/6f095bb91106ee77480d89504118aa32.png)

三，转换为 Json
----------

若你跳过了 2 步骤，则需要创建 "Editor" 文件夹，在其下创建 “ExcelBuild” 脚本，若为跳过，则直接“ExcelBuild”，添加方法即可

编写拓展方法代码如下:

```
using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Xml;
using UnityEditor;
using UnityEngine;

// <summary>
/// 编辑器扩展 将xlsx文件转换为其他格式
/// </summary>
public class ExcelBuild : Editor
{
    /// <summary>
    /// 转换为 JSON
    /// </summary>
    [MenuItem("CustomEditor/CreateExcelJson")]
    public static void CreateExcelJson()
    {
        ExcelManager excelManager = CreateInstance<ExcelManager>();
        //赋值
        excelManager.dataArray = ExcelTool.CreateItemArrayWithExcel(ExcelConfig.excelsFolderPath + ExcelConfig.excelName);

        // 文件保存路径
        string filePath = ExcelConfig.assetPath + ExcelConfig.saveName + ".json";

        // 找到当前路径
        FileInfo file = new FileInfo(filePath);
        // 判断有没有文件，有则打开文件，没有创建后打开文件
        StreamWriter sw = file.CreateText();
        // ToJson接口将你的列表类传进去，并自动转换为string类型
        string json = JsonUtility.ToJson(excelManager);
        // 转码
        Regex reg = new Regex(@"(?i)\\[uU]([0-9a-f]{4})");
        json = reg.Replace(json, delegate (Match m) { return ((char)Convert.ToInt32(m.Groups[1].Value, 16)).ToString(); });

        // 将转换好的字符串存进文件，
        sw.WriteLine(json);

        // 注意释放资源
        sw.Close(); 
        sw.Dispose();

        AssetDatabase.Refresh();
    }
}
```

最后点击 “CustomEditor” --> “CreateExcelJson” 既可以得到. json 格式的文件了：  
![](https://img-blog.csdnimg.cn/img_convert/9ccb0eba0db8b382240b1ece21b47189.png)

四，转换为 XML
---------

若你跳过了 2 步骤，则需要创建 "Editor" 文件夹，在其下创建 “ExcelBuild” 脚本，若为跳过，则直接“ExcelBuild”，添加方法即可

编写拓展方法代码如下:

```
using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Xml;
using UnityEditor;
using UnityEngine;

// <summary>
/// 编辑器扩展 将xlsx文件转换为其他格式
/// </summary>
public class ExcelBuild : Editor
{
    /// <summary>
    /// 转换为 XML
    /// </summary>
    [MenuItem("CustomEditor/CreateExcelXML")]
    public static void CreateExcelXML()
    { 
        ExcelManager excelManager = CreateInstance<ExcelManager>();
        //赋值
        excelManager.dataArray = ExcelTool.CreateItemArrayWithExcel(ExcelConfig.excelsFolderPath + ExcelConfig.excelName);
     
        // 文件保存路径
        string filePath = ExcelConfig.assetPath + ExcelConfig.saveName + ".XML";
        
        XmlDocument doc = new XmlDocument();
        //创建根节点
        XmlElement root =  doc.CreateElement("root"); 
        // 设置根节点
        doc.AppendChild(root);

        for (int i = 0; i < excelManager.dataArray.Length; i++)
        {
            // 一级子节点
            XmlElement data = doc.CreateElement("Data");
            // 设置和根节点的关系
            root.AppendChild(data);

            //创建数据子节点   
            XmlElement itemId = doc.CreateElement("task_id");
            XmlElement itemDescribe = doc.CreateElement("task_describe");
            XmlElement itemReward = doc.CreateElement("task_reward");

            // 设置节点间关系
            data.AppendChild(itemId); 
            data.AppendChild(itemDescribe);
            data.AppendChild(itemReward);

            // 数据负值
            itemId.InnerText = excelManager.dataArray[i].task_id.ToString();
            itemDescribe.InnerText = excelManager.dataArray[i].task_describe;
            itemReward.InnerText = excelManager.dataArray[i].task_reward;
        }

        // 保存到本地
        doc.Save(filePath);
        
        AssetDatabase.Refresh();
    }
}
```

最后点击 “CustomEditor” --> “CreateExcelXML” 既可以得到. XML 格式的文件了：  
![](https://img-blog.csdnimg.cn/img_convert/f466977d36b454a6b6ff1f871d9b7ac1.png)

五，使用小结
------

1.  Excel 转换为上面三种格式的准备工作是一致的  
    都需要对 Excel 进行读取存储，若表头有改动则需要更改`ExcelItem`类的对应数据  
    ![](https://img-blog.csdnimg.cn/img_convert/f400dfa68cd1e367a5006eb6ec011f9b.png)  
    还需要修改`ExcelTool.CreateItemArrayWithExcel`存储方法：  
    ![](https://img-blog.csdnimg.cn/img_convert/6fded9eb786a57f4702c5954d88848d6.png)
    
2.  在编写转换 XML 格式的文件时的拓展方法写的具体，若有大量的改动会很麻烦，建议使用转换为 JSON 格式的拓展方法，然后通过工具进行 JSON 到 XML 格式的转换，比如：  
    ![](https://img-blog.csdnimg.cn/img_convert/fcfd78949f5ae877ed46560e11bedf29.png)
    

**工具目录：**  
![](https://img-blog.csdnimg.cn/32c69e790fee40e58b5b8601c1f1e85d.png)

> Excel 的动态链接库：[获取链接](https://download.csdn.net/download/Czhenya/20895169)  
> 转换工具源码分享：[获取链接](https://download.csdn.net/download/Czhenya/20895159)  
> 积分不足的小伙伴，关注文末公众号，回复”Excel“自助获取哦~