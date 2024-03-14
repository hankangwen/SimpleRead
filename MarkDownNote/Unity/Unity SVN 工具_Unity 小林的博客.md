> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/weixin_43839583/article/details/117701015)

可在 Unity 上直接进行提交、更新、查看 log、clear up 等操作。

代码如下：

```
/********************************************************************
	文件：UnityToSVN.cs
	功能：整合SVN命令到Unity编辑器
*********************************************************************/

using UnityEditor;
using UnityEngine;
using System.Diagnostics;

public class UnityToSVN {
    private const string Menu_Commit = "SVN/Commit Selected";
    private const string Menu_Commit_All = "SVN/Commit All";
    private const string Menu_Update = "SVN/Update Selected";
    private const string Menu_Update_All = "SVN/Update All";
    private const string Menu_Log = "SVN/Log Selected";
    private const string Menu_Log_All = "SVN/Log All";
    private const string Menu_Cleanup = "SVN/Cleanup";

    #region MenuItem
    [MenuItem(Menu_Commit)]
    public static void SVNCommit() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("commit", path);
        }
        else {
            SVNCommitAll();
        }
    }

    [MenuItem(Menu_Commit_All)]
    public static void SVNCommitAll() {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("commit", path);
    }

    [MenuItem(Menu_Update)]
    public static void SVNUpdate() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("update", path);
        }
        else {
            SVNUpdateAll();
        }
    }

    [MenuItem(Menu_Update_All)]
    public static void SVNUpdateAll() {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("update", path);
    }

    [MenuItem(Menu_Log)]
    public static void SVNLog() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("log", GetSelObjPath(true));
        }
        else {
            SVNLogAll();
        }
    }

    [MenuItem(Menu_Log_All)]
    public static void SVNLogAll() {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("log", path);
    }

    [MenuItem(Menu_Cleanup)]
    public static void SVNCleanup() {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("cleanup", path);
    }
    #endregion

    public static void SVNCmd(string command, string path) {
        string cmd = "/c tortoiseproc.exe /command:{0} /path:\"{1}\" /closeonend 2";
        cmd = string.Format(cmd, command, path);
        ProcessStartInfo proc = new ProcessStartInfo("cmd.exe", cmd);
        proc.WindowStyle = ProcessWindowStyle.Hidden;
        Process.Start(proc);
    }

    private static string GetSelObjPath(bool firstOne = false) {
        string path = string.Empty;
        for (int i = 0; i < Selection.objects.Length; i++) {
            path += ConvertToFilePath(AssetDatabase.GetAssetPath(Selection.objects[i]));
            if (firstOne) break;
            path += "*";
            path += ConvertToFilePath(AssetDatabase.GetAssetPath(Selection.objects[i])) + ".meta";
            path += "*";
        }
        return path;
    }

    public static string ConvertToFilePath(string path) {
        string m_path = Application.dataPath;
        m_path = m_path.Substring(0, m_path.Length - 6);
        m_path += path;
        return m_path;
    }
}

```

这个在以前的项目组确实可以使用，但是在另一个项目组中，这个却不太能够使用了，由于一个工程一个地区，China 是工程的主目录，但同级目录下还有韩国台湾越南之类的工程，那些工程很多都是通过软链实现的，只有带_Localization 文件夹的才是那个地区的特有的差异化的文件，所以当你打开一个韩国的工程的时候，要提交东西的时候其实是提交到 China 中的，只有带_Localization 的才是提交到它原本的那里，所以以上的 [svn](https://so.csdn.net/so/search?q=svn&spm=1001.2101.3001.7020) 操作显然就有些不适用了，然后就相应的进行了更改。

以下为通过软链的工程所使用的，代码如下：

```
/********************************************************************
    xiaolin
	文件：UnityToSVN.cs
	功能：整合SVN命令到Unity编辑器
*********************************************************************/

using UnityEditor;
using UnityEngine;
using System.Diagnostics;

public class UnityToSVN {
    private const string China = "China";
    private const string Localization = "_Localization";

    private const string Menu_Commit = "SVN/Commit Selected";
    private const string Menu_Commit_All_In_This_Project = "SVN/Commit All In This Project";
    private const string Menu_Commit_All_In_China_Project = "SVN/Commit All In China Project";
    private const string Menu_Commit_All = "SVN/Commit All In Root Project";
    private const string Menu_Update = "SVN/Update Selected";
    private const string Menu_Update_All_In_This_Project = "SVN/Update All In This Project";
    private const string Menu_Update_All_In_China_Project = "SVN/Update All In China Project";
    private const string Menu_Update_All = "SVN/Update All In Root Project";
    private const string Menu_Log = "SVN/Log Selected";
    private const string Menu_Log_All_In_This_Project = "SVN/Log All In This Project";
    private const string Menu_Log_All_In_China_Project = "SVN/Log All In China Project";
    private const string Menu_Log_All = "SVN/Log All In Root Project";
    private const string Menu_Cleanup = "SVN/Cleanup";

    #region MenuItem
    [MenuItem(Menu_Commit,false,1)]
    public static void SVNCommit() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("commit", path);
        }
        else {
            SVNCommitAll();
        }
    }

    [MenuItem(Menu_Commit_All_In_This_Project, false, 2)]
    public static void SVNCommitAllInThisProject()
    {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("commit", path);
    }

    [MenuItem(Menu_Commit_All_In_China_Project, false, 3)]
    public static void SVNCommitAllInChinaProject()
    {
        string path = Application.dataPath;
        string areaPath = GetCurrentAreaName();
        path = path.Replace(areaPath, China);
        path = path.Substring(0, path.Length - 7);
        SVNCmd("commit", path);
    }

    [MenuItem(Menu_Commit_All, false, 4)]
    public static void SVNCommitAll() {
        //string path = Application.dataPath;
        //path = path.Substring(0, path.Length - 7);
        string path = GetRootPath();
        SVNCmd("commit", path);
    }


    [MenuItem(Menu_Update, false, 100)]
    public static void SVNUpdate() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("update", path);
        }
        else {
            SVNUpdateAll();
        }
    }
    

    [MenuItem(Menu_Update_All_In_This_Project, false, 101)]
    public static void SVNUpdateAllInThisProject()
    {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("update", path);
    }

    [MenuItem(Menu_Update_All_In_China_Project, false, 102)]
    public static void SVNUpdateAllInChinaProject()
    {
        string path = Application.dataPath;
        string areaPath = GetCurrentAreaName();
        path = path.Replace(areaPath, China);
        path = path.Substring(0, path.Length - 7);
        SVNCmd("update", path);
    }

    [MenuItem(Menu_Update_All, false, 103)]
    public static void SVNUpdateAll() {
        //string path = Application.dataPath;
        //path = path.Substring(0, path.Length - 7);
        string path = GetRootPath();
        SVNCmd("update", path);
    }

    [MenuItem(Menu_Log, false, 200)]
    public static void SVNLog() {
        string path = GetSelObjPath(true);
        if (path != "") {
            SVNCmd("log", GetSelObjPath(true));
        }
        else {
            SVNLogAll();
        }
    }

    [MenuItem(Menu_Log_All_In_This_Project, false, 201)]
    public static void SVNLogAllInThisProject()
    {
        string path = Application.dataPath;
        path = path.Substring(0, path.Length - 7);
        SVNCmd("log", path);
    }

    [MenuItem(Menu_Log_All_In_China_Project, false, 202)]
    public static void SVNLogAllInChinaProject()
    {
        string path = Application.dataPath;
        string areaPath = GetCurrentAreaName();
        path = path.Replace(areaPath, China);
        path = path.Substring(0, path.Length - 7);
        SVNCmd("log", path);
    }

    [MenuItem(Menu_Log_All, false, 203)]
    public static void SVNLogAll() {
        //string path = Application.dataPath;
        //path = path.Substring(0, path.Length - 7);
        string path = GetRootPath();
        SVNCmd("log", path);
    }

    [MenuItem(Menu_Cleanup, false, 300)]
    public static void SVNCleanup() {
        //string path = Application.dataPath;
        //path = path.Substring(0, path.Length - 7);
        string path = GetRootPath();
        SVNCmd("cleanup", path);
    }
    #endregion

    public static void SVNCmd(string command, string path) {
        string cmd = "/c tortoiseproc.exe /command:{0} /path:\"{1}\" /closeonend 2";
        cmd = string.Format(cmd, command, path);
        ProcessStartInfo proc = new ProcessStartInfo("cmd.exe", cmd);
        proc.WindowStyle = ProcessWindowStyle.Hidden;
        Process.Start(proc);
    }

    private static string GetSelObjPath(bool firstOne = false) {
        string path = string.Empty;
        for (int i = 0; i < Selection.objects.Length; i++) {
            path += ConvertToFilePath(AssetDatabase.GetAssetPath(Selection.objects[i]));
            if (firstOne) break;
            path += "*";
            path += ConvertToFilePath(AssetDatabase.GetAssetPath(Selection.objects[i])) + ".meta";
            path += "*";
        }
        return path;
    }

    public static string ConvertToFilePath(string path) {
        string m_path = Application.dataPath;
        m_path = m_path.Substring(0, m_path.Length - 6);
        m_path += path;
        if (m_path.IndexOf(Localization) > -1)
            return m_path;
        string areaName = GetCurrentAreaName();
        //UnityEngine.Debug.Log("区域名为:" + areaName);
        m_path = m_path.Replace(areaName, China);
        return m_path;
    }

    

    /// <summary>
    /// 获取当前工程的区域名，如：TaiWan
    /// </summary>
    /// <returns></returns>
    public static string GetCurrentAreaName()
    {
        string path = Application.dataPath;
        string[] splitPath = path.Split("/".ToCharArray());
        //UnityEngine.Debug.Log("Area Name:" + splitPath[splitPath.Length - 2]);
        return splitPath[splitPath.Length - 2];
    }

    /// <summary>
    /// 获取所有工程的根路径，如：.../20200724_best2_client_ope
    /// </summary>
    /// <returns></returns>
    public static string GetRootPath()
    {
        string path = Application.dataPath;
        string[] splitPath = path.Split("/".ToCharArray());
        string backPath = "/" + splitPath[splitPath.Length - 2] + "/" + splitPath[splitPath.Length - 1];
        path = path.Replace(backPath, "");
        return path;
    }
}

```

![](https://img-blog.csdnimg.cn/20210608142749675.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzgzOTU4Mw==,size_16,color_FFFFFF,t_70#pic_center)  
假如我现在打开的是 E:\B2Project\20200724_best2_client_ope\TaiWan 的工程, 以下都以该工程路径为例。

**Commit Selected:**  
在 Activitys 文件夹所在的路径下假如包含_Localization 文件夹的，视为这是该地区特有的文件，则在当前文件夹下打开 svn 提交页面，但假如 Activitys 文件夹所在的路径下不包含_Localization 文件夹的，则打开的是 China 中的 Activitys 文件夹的 svn 提交界面。

**Commit All In this Project:**  
该命令在 E:\B2Project\20200724_best2_client_ope\TaiWan 的目录下进行提交。

**Commit All In China Project:**  
该命令在 E:\B2Project\20200724_best2_client_ope\China 的目录下进行提交。

**Commit All In Root Project:**  
该命令在 E:\B2Project\20200724_best2_client_ope 的目录下进行提交。

**Update 命令和 Log 命令同上。**  
Cleanup 在最外层进行操作的，一个命令就够了。

![](https://img-blog.csdnimg.cn/20210608142929673.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzgzOTU4Mw==,size_16,color_FFFFFF,t_70#pic_center)  
带 All 的 svn 命令要操作的文件太多，等一会可能会变成图中的这样，此时不用关闭该界面，再等久一点就出来内容了。操作完之后，svn 的相关界面会自动关闭，假如是 Update 的操作，在 unity 中还会自动导入。