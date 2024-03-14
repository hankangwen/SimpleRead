如何将 tolua 框架接入 Unity 项目中，这里假设我们已经有一个项目，并且已经实现了一些基础架构或者项目已经是完整的，此时，如何将 tolua 这个热更新框架接入进来而不影响原项目的结构？

tolua 引入：

1.资源下载：

既然要将 tolua 引入项目，第一步肯定是先到 tolua 的 github 资源库 中下载 tolua 的资源包：tolua-master.zip

2.资源引入：

将下载的资源解压缩，可以看到大致的目录结构如下：


|-- Luajit64

tolua-master

|-- Assets

|-- Luajit

|-- Luajit64

|-- ProjectSettings

|-- Unity5.x
这么多文件夹，那些才是我们真正需要的，将 Assets 文件夹下面的所有文件都复制到我们项目的 Assets 目录中，由于我使用的是 Unity 5.5.1f1 ，所以需要将 Unity5.x/Assets/Plugins 文件夹也复制到我们项目的 Assets 目录中与进行替换合并。

3.其他：

Unity 编辑器导入目录下新增的资源后，会弹出一个窗口提示 “点击确定自动生成常用类型注册文件，也可通过菜单逐步完成此功能” ，这里直接点击 【确定】 即可。

lua 起点 ：

在 ToLuaExamples 目录中提供了很多实用范例，对于刚入门的新手有很大帮助，这里就不一一赘述了，我们直接进入到正式项目的应用实践中。在 ToluaMisc 中提供了一个 LuaClient.cs ，这个就是 tolua 提供给我们一个封装好的启动接口，可以通过继承此类来编写我们项目的 tolua 管理器，这里我创建一个 LuaEngine.cs ，继承自 LuaClient 并重写两个接口：InitLoader 和 LoadLuaFiles ：


修改搜索 lua 文件的目录
    /// &lt;/summary&gt;
    protected override void LoadLuaFiles()
    {

using System.Collections;

using System.Collections.Generic;

using LuaInterface;

using UnityEngine;

/// &lt;summary&gt;

/// tolua 启动入口，将此脚本动态绑定到一个不销毁的 GameObject 上，通常跟游戏的 GameManagr 绑在同物体上

/// &lt;/summary&gt;

public class LuaEngine : LuaClient {

    protected override LuaFileUtils InitLoader()
    
    {
    
        return new LuaResLoader();
    
    }
    
    /// &lt;summary&gt;
    
    /// 可添加或修改搜索 lua 文件的目录
    
    /// &lt;/summary&gt;
    
    protected override void LoadLuaFiles()
    
    {

#if UNITY_EDITOR

        // 添加编辑器环境下获取 lua 脚本的路径（Assets/lua）
    
        luaState.AddSearchPath(Application.dataPath   "/lua");

#endif

        OnLoadFinished();
    
    }

}
在游戏控制中心脚本 GameManager （绑定在游戏起始场景中的一个 GameObject 上面，通常是一个 Empty GameObject）的 Awake 方法中，通过以下方式启动此脚本：



using System.Collections;

using System.Collections.Generic;

using UnityEngine;

public class GameManager : MonoBehaviour {

    private static GameManager _instance = null;
    
    private LuaEngine _luaEngine;
    
    public static GameManager Instance
    
    {
    
        get { return _instance; }
    
    }
    
    void Awake()
    
    {
    
        _instance = this;
    
        // 设置为切换场景不被销毁的属性
    
        GameObject.DontDestroyOnLoad(gameObject);
    
        Init();
    
    }
    
    /// &lt;summary&gt;
    
    /// 游戏管理器的初始化步骤
    
    /// &lt;/summary&gt;
    
    void Init()
    
    {
    
        _luaEngine = gameObject.AddComponent&lt;LuaEngine&gt;();
    
    }

}
执行启动场景，可以看到最后输出：



 [Main.lua:3]:logic start

UnityEngine.Debug:Log(Object)
这是 Assets/Lua/Main.lua 的打印内容，这个脚本也就是所有 lua 逻辑的起始点：



--主入口函数。从这里开始lua逻辑

function Main()                 

    print("logic start")            

end

--场景切换通知

function OnLevelWasLoaded(level)

    collectgarbage("collect")
    
    Time.timeSinceLevelLoad = 0

end
目录结构优化：

导入 tolua 的资源后，Assets 目录下的资源会版的有点乱和杂，所以有必要根据项目原本的结构对 tolua 的一些目录结构进行优化：

1.*Wrap.cs 目录：

Assets/Source/Generate 是用来保存 tolua 生成的可供 lua 调用的 C# 类的绑定类，但是在我的项目中，习惯性把脚本放在 Assets/Scripts 目录中，所以这里我们只需要打开 Assets/Editor/Custom/CustomSettings.cs ，修改一下内容：



public static string saveDir = Application.dataPath   "/Scripts/Generate/";   
然后将 Source/LuaConst.cs 移动到 Assets/Scripts/Framework/tolua 目录中，在 Scripts 中创建一个 Generate 目录，关闭 Unity 在重新启动，会再像刚引入 tolua 那样弹出一个窗口提示 “点击确定自动生成常用类型注册文件，也可通过菜单逐步完成此功能” ，这里也是直接点击 【确定】 即可。此时，在 Assets/Scripts/Generate 会生成一堆 *wrap.cs 的脚本文件，说明目录修改成功。但是此时会有重名文件，必须把整个 Source 目录删掉。

2.ToLua 目录：

Assets/ToLua 目录下是 tolua 框架最为核心的一些库，当然按照我们项目的规则；外部引入的第三方插件资源主要放在 Assets/ThirdParty 目录中，这里我们我们直接将整个 ToLua 目录移动到第三方插件目录，然后需要修改几个地方：

LuaConst.cs 中的 toluaDir ：



public static string toluaDir = Application.dataPath   "/ThirdParty/ToLua/Lua";        //tolua lua文件目录
CustomSettings.cs 中的 toluaBaseType ：



public static string toluaBaseType = Application.dataPath   "/ThirdParty/ToLua/BaseType/"; 
完成上述两项设置及完成了目录的修改。