> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [cloud.tencent.com](https://cloud.tencent.com/developer/article/1747925)

[toc]

将excel表格文件转换生成unity可识别的asset文件unity_Excel-asset--master

项目开源地址:[https://github.com/641273917/unity_Excel-asset-](https://github.com/641273917/unity_Excel-asset-) 

许多时候, 我们需要通过 excel 表格来生成我们要读取的文件, 之前我倒是试过小型的 cvs 表格, 但是感觉不是很方便, 这里就用了直接读取 excel 表格的方式来生成 asset 了. 比如, 我们现在有这样的一个表格:

![](https://ask.qcloudimg.com/http-save/yehe-2277581/799647leu4.png?imageView2/2/w/1620)

表格文件

最后我们会转换成这样的文件

![](https://ask.qcloudimg.com/http-save/yehe-2277581/0l1y5kwp7h.png?imageView2/2/w/1620)

asset 文件

我们为什么要这么做呢? 因为 unity 不识别 excel, 如果在游戏开发中有一些数值变化, 只需要修改 excel 表格, 重新生成 asset 就好. 下面是实现代码:

#### 一 配置代码:

```c#
using UnityEngine;
public class ExcelConfig 
{
    public static readonly string excelsFolderPath = Application.dataPath + "/Excel/";
    public static readonly string assetPath = "Assets/Resources/Release/";
}

```

#### 二 表数据信息 这里记录所有表格中的文件, 这与之前的文章 "解析 json 文件" 比较类似

```C#
using UnityEngine;
public class ExcelLineManage:ScriptableObject  
{
    public Item[] dataArray;
}

[System.Serializable]
public class Item
{
    public string ID;
    public string ChinaName;
    public string EnglishName;
    public string Age;
    public string height;
    public string weight;
    public string address;
    public string zipcode;
    public string hobbit;
    public string Contact;
    public string emergencycontact;
}
```

#### 三 读取表格工具脚本 这里需要引用文件

```c#
using System.IO;
using System.Data;
using Excel;
using UnityEngine;
public class ExcelTool  
{
    public static Item[] CreatItemArrayWithExcel(string filePath)
    {
        
        int columnNum = 0, rowNum = 0;
        DataRowCollection collection = ReadExcel(filePath, ref columnNum, ref rowNum);
        
        Item[] array = new Item[rowNum - 2];
        for (int i = 2; i < rowNum; i++)
        {
            Item item = new Item
            {
                ID = collection[i][0].ToString(),
                ChinaName = collection[i][1].ToString(),
                EnglishName = collection[i][2].ToString(),
                Age = collection[i][3].ToString(),
                height = collection[i][4].ToString(),
                weight = collection[i][5].ToString(),
                address = collection[i][6].ToString(),
                zipcode = collection[i][7].ToString(),
                hobbit = collection[i][8].ToString(),
                Contact = collection[i][9].ToString(),
                emergencycontact = collection[i][10].ToString(),
            };
            array[i - 2] = item;
        }
        return array;
    }
    
    static DataRowCollection ReadExcel(string filePath, ref int columnnum, ref int rownum)
    {
        FileStream stream = File.Open(filePath, FileMode.Open, FileAccess.Read, FileShare.Read);
        IExcelDataReader excelReader = ExcelReaderFactory.CreateOpenXmlReader(stream);
        DataSet result = excelReader.AsDataSet(); 
        
        columnnum = result.Tables[0].Columns.Count;
        rownum = result.Tables[0].Rows.Count;
        stream.Close();
        return result.Tables[0].Rows; 
    }
}
```

#### 四 生成 asset 文件的编辑器类

```c#
using System.IO;
using UnityEditor;
using UnityEngine;

public class CreatAssetWithExcel : Editor
{
    [MenuItem("Tools/生成asset文件")]
    private static void CreatExcel()
    {
            ExcelLineManage manager = ScriptableObject.CreateInstance<ExcelLineManage>();
            
            manager.dataArray = ExcelTool.CreatItemArrayWithExcel(ExcelConfig.excelsFolderPath + "TESTEXCEL.xlsx");
            
            if (!Directory.Exists(ExcelConfig.assetPath))
            {
                Directory.CreateDirectory(ExcelConfig.assetPath);
            }
 
            string assetPath = string.Format("{0}{1}.asset", ExcelConfig.assetPath, "TESTEXCEL");
            
            AssetDatabase.CreateAsset(manager, assetPath);
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh(); 
    }
}

```

编译完成之后点击 tools / 生成 asset 文件, 即可在配置的路径中看到生成的 asset 文件, 那么如何使用呢?

#### 五 解析 asset 文件

```c#
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReadAsset : MonoBehaviour
{ 
    
    void Start()
    {
        ExcelLineManage LineManage = Resources.Load<ExcelLineManage>("Release/TESTEXCEL");
        foreach (var item in LineManage.dataArray)
        {
            Debug.Log(item.ID + "---" + item.ChinaName + "---" + item.EnglishName + "---" + item.Age + "---" + item.height + "---" + item.weight + "---" + item.address + "---" + item.zipcode + "---" + item.hobbit + "---" + item.Contact + "---" + item.emergencycontact);
        }
    }
}
```

解析就完成了.
