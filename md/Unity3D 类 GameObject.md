> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=MzkxNzU0MTQwNQ==&mid=2247484094&idx=1&sn=3b3514f32a18202f05d7124fe4ec0315&chksm=c1be45ccf6c9ccda34ff5b57b8b9b2bbf688d53a5a00ecf18c4ebcdbaf467feeded92f8b28d4&scene=178&cur_album_id=3285227852443090947#rd)

        GameObject 是 Unity 中场景的构建块，可充当用于确定 GameObject 外观以及 GameObject 作用的功能组件的容器。

在脚本编写中，GameObject 类提供了允许在代码中使用的方法的集合，包括查找、建立连接和在 GameObject 之间发送消息，以及添加或移除附加到 GameObject 的组件和设置与其在场景中的状态相关的值。

### 物体在场景中的状态

当我们在场景中添加一个空物体时，它仅包含物体的_状态信息_和_空间信息_两个部分

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/QTo0hNVPAwXeUYIichd3vEeicCNsUMwZp2DAuicKiaZuzKmiayXXcib7liaekm7DQsyGJbb6v46x3VhaycxIWuiaIbicThQ/640?wx_fmt=other&from=appmsg)

一个空物体的基本信息

活动状态

*   左上角的对勾，表示物体的 “激活状态”。
    
*   对于挂载了渲染器的物体，处于非激活状态后会变为不可见。
    
*   处于非激活状态的物体不会接收任何正常的回调或事件，例如 Update,FixedUpdate 等。
    
*   如果场景中的物体一开始就处于非激活状态，它的 Awake 也不会在进入场景后执行，而是会在物体被激活时执行。
    
*   非活跃状态的物体被销毁时也不会调用 OnDestroy。
    
*   如果物体启用了协程，物体进入非激活状态后协程也会停止。
    

静态状态

*   右上角的对勾，表示物体是否是静态的。
    
*   某些系统会对静态物体进行预处理，例如大多数地图由于需要烘焙寻路网格和烘焙灯光一般都会设置为静态。
    

![](https://mmbiz.qpic.cn/sz_mmbiz_jpg/QTo0hNVPAwXeUYIichd3vEeicCNsUMwZp25YPApCFckBbQBPxILfCHQDZQTCDhT9OO7orME9APAqibs09SP3iaco4w/640?wx_fmt=other&from=appmsg)

静态选项

*   Nothing 不为任何系统静态
    
*   Everything 为所有系统静态
    
*   ContributeGI 全局光照系统
    
*   OccluderStatic 遮挡剔除系统中的遮挡物
    
*   BatchingStatic 合并物体网格
    
*   NavigationStatic 寻路系统
    
*   OccludeeStatic 遮挡剔除系统中的被遮挡物
    
*   OffMeshLinkGeneration 寻路系统不连续的网格
    
*   ReflectionProbeStatic 反射探针系统
    

使用代码设置静态状态

```
[MenuItem("GameObject/StaticObj")]    private static void CreateStaticGameObject()    {        GameObject go = new GameObject("staticObj");        //设置物体为寻路系统静态，注意工具类在UnityEditor命名空间下        GameObjectUtility.SetStaticEditorFlags(go,StaticEditorFlags.NavigationStatic);    }
```

### 添加，访问和移除组件

*   通过添加组件可以在运行是给物体添加行为，注意组件类需要继承自 MonoBehaviour。
    
*   同理移除组件就是移除物体的某些行为，但实际开发中一般使用 component.enable = false 禁用组件。
    

```
/// <summary>    /// 组件操作    /// </summary>    private void ComponentOperation()    {        //添加"AddComponent"组件        gameObject.AddComponent<AddComponent>();        //访问需要移除的组件        var needRemove = gameObject.GetComponent<RemoveComponent>();        //禁用组件        needRemove.enabled = false;        //移除"RemoveComponent"组件        Destroy(needRemove);    }
```

想要访问其他物体上的组件可以通过其他物体的引用调用 GetComponent<T>() 方法。

### 查找子物体

有时，游戏场景会使用许多相同类型的 GameObject，例如可收集对象、路径点和障碍物。这些游戏对象可能需要由监督或响应它们的特定脚本来跟踪（例如，寻路脚本可能需要使用所有路径点）。可以使用变量来链接这些游戏对象，但是如果必须将每个新路标拖动到脚本中的变量，会使设计过程变得繁琐。同样，如果删除一个路标，则必须删除对丢失游戏对象的变量引用，这很麻烦。此类情况下，可使一组游戏对象成为一个父游戏对象的所有子对象，这种管理多个游戏对象的方式通常会更好。可以使用父游戏对象的变换组件来检索子游戏对象（因为所有游戏对象都具有隐式变换）：

```
using UnityEngine;

public class WaypointManager : MonoBehaviour {
    public Transform[] waypoints;

    void Start()
    {
        waypoints = new Transform[transform.childCount];
        int i = 0;

        foreach (Transform t in transform)
        {
            waypoints[i++] = t;
        }
    }
}
```

### 发送和广播消息

向物体发送消息相当于直接通过方法名调用物体身上的方法，而不需要知道方法所在的类，共用三种发消息的方式

*   向物体及其所有子物体发送消息 BroadcastMessage
    
*   向物体自身发送消息 SendMessage
    
*   向物体及其所有父物体发送消息 SendMessageUpwards
    

```
public class MessageSender : MonoBehaviour{    public GameObject receiver;    public GameObject receiver2;    public GameObject receiver3;    private void Start()    {        SendMessage();    }    /// <summary>    /// 发送消息    /// </summary>    private void SendMessage()    {        //向物体及其所有子物体发送消息，将自己名字作为参数发送，不必要有接收者        receiver.BroadcastMessage("ReceiveMessage",transform.name            ,SendMessageOptions.DontRequireReceiver);        //向物体自身发送消息，将自己名字作为参数，如果没有接收者会报错        //如果物体身上有多个脚本都有这个名字的方法，则都会被调用        receiver2.SendMessage("ReceiveMessage",transform.name            ,SendMessageOptions.RequireReceiver);        //向物体及其所有父物体物体发送消息，将自己名字作为参数，如果没有接收者会报错        receiver3.SendMessageUpwards("ReceiveMessage", transform.name            , SendMessageOptions.RequireReceiver);    }}public class MessageReceiver : MonoBehaviour{    public void ReceiveMessage(string from)    {        Debug.Log(transform.name + "receive message from " + from);    }}
```

### 按名称或标签查找 gameobject

```
/// <summary>    /// 查找物体    /// </summary>    private void FindGameObject()    {        //Hierarchy从上到下查找第一个名字为"Test1"的物体        GameObject go = GameObject.Find("Test1");        Debug.Log(go.transform.position);        //Hierarchy从上到下查找第一个标签为"Club"的物体        GameObject club = GameObject.FindGameObjectWithTag("Club");        Debug.Log(club.name);        //查找所有标签为"Ball"的物体        GameObject[] balls = GameObject.FindGameObjectsWithTag("Ball");        Debug.Log(balls.Length);    }
```

### 创建和销毁 gameobject

创建 gameobject

物体创建可以分为两种，一种是使用_构造方法创建空物体_，或_根据预制体创建副本。_

```
/// <summary>    /// 创建物体    /// </summary>    private void CreateGameObject()    {        //创建一个名字为“emptyObj”的空物体        GameObject emptyObj = new GameObject("emptyObj");        //使用预制体创建一个副本        GameObject prefabInstance1 = Instantiate(prefab);        prefabInstance1.name = "1";        //副本作为当前物体的子物体        GameObject prefabInstance2 = Instantiate(prefab, transform);        prefabInstance2.name = "2";        //副本作为当前物体的子物体，且不保持副本在世界坐标中的位置，旋转缩放        GameObject prefabInstance3 = Instantiate(prefab, transform, false);        prefabInstance3.name = "3";        //副本作为当前物体的子物体，且保持副本在世界坐标中的位置，旋转缩放        GameObject prefabInstance4 = Instantiate(prefab, transform, true);        prefabInstance4.name = "4";        //创建副本时直接赋值物体的位置和旋转        GameObject prefabInstance5 = Instantiate(prefab,Vector3.zero,Quaternion.identity);        prefabInstance5.name = "5";        //副本作为当前物体的子物体，并直接赋值物体的位置和旋转（世界坐标系下）        GameObject prefabInstance6 = Instantiate(prefab, Vector3.zero, Quaternion.identity,transform);        prefabInstance6.name = "6";    }
```

销毁 gameobject

物体的销毁可以使用 Destroy(gameobject)API。

```
/// <summary>    /// 销毁物体    /// </summary>    private void DestroyGameObject()    {        //移除当前脚本,并不会销毁物体        //Destroy(this);        //销毁当前物体        Destroy(gameObject);        Debug.Log(gameObject.name);        //当前帧立即销毁当前物体        DestroyImmediate(gameObject);        Debug.Log(gameObject.name);    }
```

从上图我们可以看到 Destroy 销毁物体后当前帧仍然可以获得物体的名字，而使用 DestroyImmediate 销毁物体，物体会立即被销毁，再次打印名字时就会空引用报错。

### 创建原始对象

可以使用 Unity 的 API 直接创建基础物体，如胶囊体，立方体，球体等。

```
/// <summary>    /// 创建基础物体    /// </summary>    private void CreatePrimitive()    {        //胶囊体        GameObject Capsule = GameObject.CreatePrimitive(PrimitiveType.Capsule);        Capsule.transform.position = new Vector3(0, 0, 0);        //立方体        GameObject Cube = GameObject.CreatePrimitive(PrimitiveType.Cube);        Cube.transform.position = new Vector3(1, 0, 0);        //圆柱        GameObject Cylinder = GameObject.CreatePrimitive(PrimitiveType.Cylinder);        Cylinder.transform.position = new Vector3(2, 0, 0);        //平面        GameObject Plane = GameObject.CreatePrimitive(PrimitiveType.Plane);        Plane.transform.position = new Vector3(3, 0, 0);        //面片        GameObject Quad = GameObject.CreatePrimitive(PrimitiveType.Quad);        Quad.transform.position = new Vector3(4, 0, 0);        //球体        GameObject Sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);        Sphere.transform.position = new Vector3(5, 0, 0);    }
```