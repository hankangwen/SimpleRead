> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/2QoVJXmyUp9hMNDlnsdF0Q)

往往基础的东西反而暗藏玄机。  

今天我们来讲一下 Unity 基础组件之一的 Transform。前面介绍的可能大家都知道，但是后面介绍的大家不一定清楚，但是十分实用的方法；

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGib3NUOSCjxBSic6gVXj8hKmePGC3n5MlYBq3iaHrtekTiaKvNgepOBKbWrLX5aFuTb5ic4WHDLjJLAjw/640?wx_fmt=png&from=appmsg)

面板上的东西不多，分别是位置，旋转，缩放。当物体没有父物体时或父物体的属性都是默认值时，物体的三个属性和世界空间坐标系下相同，当物体有父物体时，则是相对于父物体的局部坐标，局部旋转，局部缩放。缩放坐标有一个**椭圆圈加斜杠的标志，**点击它后，设置 X 的缩放值，会同步到 Y 和 Z 值，也就是同等缩放。

下面主要介绍一下 Transform 类中一些我们经常使用的方法和变量。以及一些比较特殊但是好用的方法。  

进入 Transform 类，我们会发现它继承自 Component, 所有组件都继承自这个类.  

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGib3NUOSCjxBSic6gVXj8hKmojUmtyoXYb4diccf3DZQEjjte5TAUjHafx4ESg5UwwxUKMy6YAVP5Kw/640?wx_fmt=png&from=appmsg)

我们自己写的脚本能挂载在物体上也是因为简介继承了这个 Component 类，我们自己写的脚本继承自 MonoBehaviour 类，MonoBehaviour 的爷爷辈就是 Component

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGib3NUOSCjxBSic6gVXj8hKmFeEK46auvKImA6IzTyMibliaYdsuQwBtIpoX15WZqWa5WqYnRlC22cVg/640?wx_fmt=png&from=appmsg)

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGib3NUOSCjxBSic6gVXj8hKmMOLGnA4j0gNf7vgUIHLrV8VIfoPHPiaFK7IyzJ2vey00WPKHicrVwwkg/640?wx_fmt=png&from=appmsg)

从上面那张图中我们可以看出 Transform 还继承了 IEnumerable 接口，这就意味着物体是可以通过 foreach 遍历下面带有 Transform 组件的子物体。

```
public Transform targetParent;
    // Start is called before the first frame update
  void Start()
  {
      foreach (Transform child in targetParent)
      {
          Debug.Log(child.name);
      }
  }
```

**变量部分:**  

```
//世界空间下的坐标
transform.position
//相对于父物体的坐标(局部空间)
transform.localPosition
//世界空间下的旋转角度
Debug.Log(transform.eulerAngles);
//相对于父物体的旋转角度(局部空间)
Debug.Log(transform.localEulerAngles);
```

这里要注意一下欧拉角的数值问题，无论我们在面板上设置多大的角度，变量存储的值都是在 0~360 的范围，超出 360 部分取余数  

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGib3NUOSCjxBSic6gVXj8hKmAVe6chsOzianllsMmZFyicZyXyWRzspUn4eRYObOSMg9Tg4Ir5XW9jPA/640?wx_fmt=png&from=appmsg)

```
//物体的正右方，也就是局部坐标系的X轴(红轴)
Debug.Log(transform.right);
//官方描述
//     The red axis of the transform in world space.
public Vector3 right
{
    get
    {
        return rotation * Vector3.right;
    }
    set
    {
        rotation = Quaternion.FromToRotation(Vector3.right, value);
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGz6m7j9Bduo9PD7ojoJP6ZAWWkcvwiceppvxvTTMRrrMbibDLs6TXicpQuJXfCrtaJIAVicuY0cMtAdQ/640?wx_fmt=png&from=appmsg)

上图我们是以 - Y 方向看向世界坐标系和物体自身坐标系，物体沿着自身 Y 轴旋转 45° 后，我们可以把 X(local) 红色的轴看成一个向量，这个向量相对于世界坐标系（右上角）而言，它的方向是向着世界坐标系 X 和  -Z 方向的中间，这里也可以理解为啥位置坐标 X 是正数，Z 是负数 (前提是物体没有父物体存在，它的坐标就是世界坐标系下的坐标)。最后得出 Transform.Right 的单位向量值为。通过勾股定理也能算出来

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGz6m7j9Bduo9PD7ojoJP6ZERnDZBlNR5n9rrFFaWLNmdxkXIOULaXgd1p4du8DCiaNYibpXJzH1AMg/640?wx_fmt=png&from=appmsg)

我们还可以设置 transform.right 的值，

```
transform.right = new Vector3(0,1,0);
```

**设置前：**

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLoQtDrXrkkP5SbVFwnSL2FmWc8qEj6UxARrRg3kHFbU4lPzcibIoCxxw/640?wx_fmt=png&from=appmsg)

**设置后**：  

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLHHP5NJZkiafPqRk0Pw5EdA9kEN3Um1QYX6Ko1nz676j9y82kGibjianbA/640?wx_fmt=png&from=appmsg)

设置后 X 轴往上，因为 X 轴的 Y 值要为 1，而如何能让 X 轴往上，我们只有让 Z 轴旋转正 90° 才行。  

```
//物体的正上方，也就是局部坐标系的Y轴(绿轴)
 Debug.Log(transform.up);
 // 摘要:
//     The green axis of the transform in world space.
public Vector3 up
{
    get
    {
        return rotation * Vector3.up;
    }
    set
    {
        rotation = Quaternion.FromToRotation(Vector3.up, value);
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGz6m7j9Bduo9PD7ojoJP6ZtGXAqyQJ4RdZYcPMHTSicw6Kz1Nx8zOjZU45X196juhJwxarSe6iazibw/640?wx_fmt=png&from=appmsg)

```
//物体的正前方，也就是局部坐标系的Z轴(蓝轴)
 Debug.Log(transform.forward);
 // Returns a normalized vector representing the blue axis of the transform in world
//     space.
public Vector3 forward
{
    get
    {
        return rotation * Vector3.forward;
    }
    set
    {
        rotation = Quaternion.LookRotation(value);
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGz6m7j9Bduo9PD7ojoJP6ZATjQt4xgrsLvMagUxFXJVa7XwLdyU2ibrknyyMSOBv3VQMILym9CGzA/640?wx_fmt=png&from=appmsg)

```
//四元数，用来描述物体的在世界空间下的旋转
Debug.Log(transform.forward);    
```

这里要小心的是，物体绕 Y 轴旋转 60 度得到的四元数和绕 Y 轴旋转 420 度得到的四元数并不相同，  

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxGz6m7j9Bduo9PD7ojoJP6ZOMicpJLHa5BkJdmd70YOFroSWtuZ3eBE76eD7u8jD58NUo4OdHvXBmA/640?wx_fmt=png&from=appmsg)

```
//四元数，用来描述物体的在局部坐标下的旋转
Debug.Log(transform.localRotation);
```

```
//用来描述物体的缩放，我们会发现它没有Scale，只有一个localScale
 Debug.Log(transform.localScale);
```

```
//用来描述物体的父物体，也可以把其设置到某个物体下作为子物体
transform.parent = targetParent;
```

```
//将物体上的某个点从世界坐标系下的位置转换到相对于物体的局部坐标位置的变换矩阵
Vector3 localposition = transform.worldToLocalMatrix * transform.position;
Debug.Log(transform.worldToLocalMatrix);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLL2qpJMIorKQv9Mv0drO4Zjy0ooibqBUDREjERPrpwSXMoGfjEwIMR2WQ/640?wx_fmt=png&from=appmsg)

```
//将某个点的位置从局部坐标系下转换到世界坐标的变换矩阵(只读)
Vector3 worldPosition = transform.localToWorldMatrix * transform.localPosition;
Debug.Log(transform.localToWorldMatrix);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLdGicEiatNWN4OnnibU0iawV8tRF7wdNPDPKVuZsyTDYjbks91me6jicWKhw/640?wx_fmt=png&from=appmsg)

```
//获取物体挂载的最顶端的那个父物体(只读)
 Debug.Log(transform.root);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLqJwmboXzJ4eu2gDPvfn1OKcH1oa5xOtznibRws3GiczVHx6aWv5XwOZg/640?wx_fmt=png&from=appmsg)

```
//获取子物体个数，并不包括子物体的子物体
Debug.Log(transform.childCount);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLEpCyu3Nv8suB4AU3HcwAZiaZruhDPgBS6y8pAynCmN9orIJrFmJ2VJg/640?wx_fmt=png&from=appmsg)

```
//世界空间下的缩放系数
Debug.Log(transform.lossyScale);
```

这里我们把球体放到 Cube 下面, Cube 的 ScaleY 值设为 2，然后球体的 ScaleY 值设为 2，所以最终球体在世界空间下的缩放系数为 4

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLJRDicwB9Rqy0EPuuxKicOy2mibJKiaNq1iaag1BIT891wsXGrxHfKbaIjSw/640?wx_fmt=png&from=appmsg)

```
void Start()
{   
    //先把这个变量设为false,如果后续transform出现变化则这个值会变成true,不设置的默认情况下返回true
    transform.hasChanged = false;
}
void Update()
{
    Debug.Log(transform.hasChanged);
}
```

这里我们先设置 transform.hasChanged 为 false，然后转动球体会发现这个值变成了 true  

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLL4yq8lzAFTmUrfjp3zbobcZsZYSGDyl1p1rl3254qKYrlhP1ORP9z4Q/640?wx_fmt=png&from=appmsg)

```
//Unity 内部使用自己的打包数据结构表示每个变换的层级视图，
//即一个根及其所有深层子项。当其中的变换数量超过其容量时，将调整该数据结构的大小。
Debug.Log(transform.hierarchyCapacity);
//变换的层级视图数据结构中变换的数量。
Debug.Log(transform.hierarchyCount);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLdcpYicf5cb02ozaAkGD7LP4XDezSm14t34IxO1FgZe40pvoXQuFOTyg/640?wx_fmt=png&from=appmsg)

可以理解为获取当前挂载脚本的物体的根物体（Root）下的所有带 Transform 的物体数量。目前来看，容量和数量是一致的

**方法部分：**  

```
//设置自己的父物体
  transform.SetParent(targetParent);
  //设置自己的父物体,
  //但是依旧保持自己之前在世界空间下的的位置，旋转和缩放。（如果父物体放大，则自己的数值会缩小）
  transform.SetParent(targetParent ,false);
```

这里父物体的 ScaleY 值为 2 ，则设置父物体以后，球体的 ScaleY 为 0.5，保持和原来一致大小。  

```
//设置物体世界坐标和旋转角度
  transform.SetPositionAndRotation(Vector3.zero, Quaternion.identity);
  //设置物体局部坐标和旋转角度
  transform.SetLocalPositionAndRotation(Vector3.zero, Quaternion.identity);
  //获取物体世界坐标和旋转角度
  transform.GetPositionAndRotation(out Vector3 position, out Quaternion rotation);
  //获取物体局部坐标和旋转角度
  transform.GetLocalPositionAndRotation(out Vector3 localPosition, out Quaternion localRotation);
```

```
//transform.right 会随着物体的旋转而改变值
//沿着transform.right方向运动，如果将物体旋转90°，
//则会在原先运动方向的基础上乘以两倍，变成180°往原先相反的位置运动
//Space.Self是以自身为坐标系，对于物体旋转X度，
//我们先把坐标系旋转X度，然后以新坐标系为基准再将运动角度旋转X度，所以会出现双倍的情况
transform.Translate(transform.right * Time.deltaTime, Space.Self);
//无论物体怎么旋转，我都是按照物体的transform.right方向运动
transform.Translate(transform.right * Time.deltaTime, Space.World);
//按照targetParent的transform.right方向运动,
//如果物体自身有旋转，则在这个transform.right的方向上加上这个角度去运动
transform.Translate(transform.right * Time.deltaTime, targetParent);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxFVgIOwCKbVibZVc6bZp3OLLYsQ8khIgCoDxbAwR6UIpJiarn3fh3Y2tskDZ8zjf0VYwqIwdfHWqEbg/640?wx_fmt=png&from=appmsg)

```
//自身旋转为0时，物体根据参数的三维数值旋转，也就是各个轴旋转多少度,如果不设置Space参数，默认是Self
//旋转方向会受到自身旋转的角度而变化
transform.Rotate(Vector3.one ,Space.Self);
//物体根据参数的三维数值旋转,旋转方向不会受到自身旋转的角度而变化双倍
transform.Rotate(Vector3.one, Space.World);
//物体沿着X轴旋转50°，因为当自身旋转角度为0 或者50后面再加一个Space.World参数时，transform.right == Vector3(1,0,0)
transform.Rotate(transform.right , 50);
//物体沿着世界坐标下值为(0，1，0)的向量，但是这个向量可以在任意位置，
//我们确定这个向量经过点(1,1,1)，他就变成了唯一的向量，然后物体沿着这个向量旋转50°
transform.RotateAround(new Vector3(1,1,1), new Vector3(0,1,0), 50f);
```

```
//使自己的Z轴正前方（transform.forward）指向目标物体,并且默认物体的Y轴和世界空间下的Y轴一致方向
 transform.LookAt(targetParent);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwKXk69zGJzpPL36GeIr3Oqow53zkOBzl3uhIpUZa1LMJNKVdRuvUsQA/640?wx_fmt=png&from=appmsg)

```
//上面我们默认Y轴一致，但是现在我们指定X轴正右边和世界坐标下一致
transform.LookAt(targetParent , Vector3.right);
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwh4XFVkAhC0Ceia8Dw9N55Du8tgnSiaoyiarbJIFtlvlyW9unIrtTibpFdw/640?wx_fmt=png&from=appmsg)

```
//看向一个点，等于看向一个Transform的位置是一样的,后面的参数轴和上面的一样的效果
 transform.LookAt(Vector3.one,Vector3.right);
```

```
//把之前以物体自身坐标系的向量，转换到世界空间下的向量的值，但是长度要和原向量一致
Debug.Log(transform.TransformDirection(Vector3.one));
//就是把之前世界空间下的向量转换成以物体自身坐标系的向量的值，但是长度要和原向量一致
Debug.Log(transform.InverseTransformDirection(transform.TransformDirection(Vector3.one))); 
```

```
 //把之前以物体自身坐标系的Vector3的值，转换到世界空间下的值
 Debug.Log(transform.TransformVector(Vector3.one));
 //把之前世界空间下的Vector3的转换成以物体自身坐标系的值
 Debug.Log(transform.InverseTransformVector(transform.TransformDirection(Vector3.one)));
```

```
//把之前以物体自身坐标系的点，转换到世界空间下的点的值
Debug.Log(transform.TransformPoint(Vector3.one));
//把之前世界空间下的点转换成以物体自身坐标系的点的值
Debug.Log(transform.InverseTransformPoint(transform.TransformDirection(Vector3.one)));
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwSZhecfUb3LdsqMaB4icERwjQGTv5H7BibPMhn5YeibEcxqbwshlbngTng/640?wx_fmt=png&from=appmsg)

**无论是 TransformDirection ，TransformVector ，TransformPoint，他们的参数都是 Vector3 的**

```
//使子物体不再以作为自己的子物体
transform.DetachChildren();
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwdmEO2O2vic9tokJmBrJHicllhjSQsicic78huYM8eOfVORW1tDz28pHycg/640?wx_fmt=png&from=appmsg)

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwTsVZKWhY32FZrBqo4IkoxdzC5ibnwDJOkc89vbjPniax8OEH4AZ1ibKVA/640?wx_fmt=png&from=appmsg)

```
//将物体移到Hierarchy面板的第一位
 transform.SetAsFirstSibling();
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwlM6ZPsaUtHacF02Zed2kjlojc0srmUyFd8y4yPLOPIwGJk4X4BrFOg/640?wx_fmt=png&from=appmsg)

```
//将物体移到Hierarchy面板的最后一位
transform.SetAsLastSibling();
```

```
//将物体设置到指定数字的位置,0是第一位等同于transform.SetAsFirstSibling()
//数字不合规会报错，但不影响正常执行排序
transform.SetSiblingIndex(0);
//获取当前物体排在Hierarchy面板第几位
transform.GetSiblingIndex();
//查找下面的子物体，可以填写路径，子物体隐藏的时候也能查到
transform.Find("cube/cube");
//判断自己是不是目标物体的子物体
transform.IsChildOf(targetParent);
//获取迭代器
Debug.Log(transform.GetEnumerator());
//获取对应下标的子物体
transform.GetChild(0);
```

**接下来是继承父类得到的成员变量**  

```
//当前游戏物体
Debug.Log(transform.gameObject);
//当前游戏物体的标签
Debug.Log(transform.tag);
//物体的名字
transform.name = "名字";
//套娃
Debug.Log(transform.transform);
//用来控制对象的销毁，保存和是否在inspector界面中可见,HideFlags有多个枚举对象
transform.hideFlags= HideFlags.HideInHierarchy; //在Hierarchy下不显示自己
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwDwKX8LXGZAIWsCmJacn9OwCMf0x1DicLBzBY8QSoUe3gunrTe4pUzIA/640?wx_fmt=png&from=appmsg)

**接下来是继承父类得到的公共函数**

```
//调用此游戏对象或其任何子项中的每个 MonoBehaviour 上名为 methodName 的方法。
transform.BroadcastMessage("methodName");
//判断物体标签是不是Player
transform.CompareTag("Player");
//获取物体下的Rigidbody组件，也可以自定义挂载的脚本组件
transform.GetComponent<Rigidbody>();
//获取子物体下的Rigidbody组件，也可以自定义挂载的脚本组件
transform.GetComponentInChildren<Rigidbody>();
//获取父物体下的Rigidbody组件，也可以自定义挂载的脚本组件
transform.GetComponentInParent<Rigidbody>();
//获取物体身上挂载的名为TransformUse 或继承了TransformUse 的组件列表
transform.GetComponents<MonoBehaviour>();
Debug.Log(transform.GetComponents<MonoBehaviour>().Length) ;
//获取子物体身上挂载的名为TransformUse 或继承了TransformUse 的组件列表
transform.GetComponentsInChildren<MonoBehaviour>();
//获取父物体身上挂载的名为TransformUse 或继承了TransformUse 的组件列表
transform.GetComponentsInParent<MonoBehaviour>();
```

![](https://mmbiz.qpic.cn/mmbiz_png/GicdfssnUFxEHGu5LS3F4KIOaGc1ibibSYwQwUreI4iathpZePGpppLicicO04EtLdiavmZTuib6vFAUVsgNacyppNqTyQ/640?wx_fmt=png&from=appmsg)

```
//调用此游戏对象中的每个 MonoBehaviour 上名为 methodName 的方法。
transform.SendMessage("methodName");
//调用此游戏对象中的每个 MonoBehaviour 上或每个父级上名为 methodName 的方法。
transform.SendMessageUpwards("methodName");
//试图获取物体身上挂载的组件,并输出
transform.TryGetComponent<TransformUse>(out TransformUse transformUse);
//获取物体的ID,这个在当前场景的meta文件中能看到
transform.GetInstanceID();
//返回对象的名称
transform.ToString();
```

接下来介绍一些静态函数，也就是类直接调用的，也是继承而来的  

```
//移除GameObject，组件，资源。
Transform.Destroy(transform);
//立即销毁自己
Transform.DestroyImmediate(transform);
//在切换场景时，不销毁自己，但是这里有个重点，物体依然属于这个场景，如果场景在内存中被回收了，这个子资源依旧会销毁
Transform.DontDestroyOnLoad(transform);
//查找场景中第一个带有此组件的物体
Transform.FindFirstObjectByType<TransformUse>();
//查找场景中带有此组件的物体
Transform.FindAnyObjectByType<TransformUse>();
//查找场景中所有带有此组件物体列表,后面参数是根据物体ID来排序这个列表
Transform.FindObjectsByType<TransformUse>(FindObjectsSortMode.InstanceID);
//克隆一个物体到场景中,这里克隆自己，可以传入别的Object对象
Transform.Instantiate(gameObject);
```

最后还有一些操作符号，我们 Transform 组件和类的介绍就完了，确实筹备了很久和花了很多时间  

```
//判断物体对象是否存在
Debug.Log(transform == true);
//判断两个物体对象是否不同
Debug.Log(transform != targetParent);
//判断两个物体对象是否相同
Debug.Log(transform == targetParent);
```

OK，结束，后续还有很多组件消息非常非常详细的介绍，下一个应该是 Button 或 Rectransform![](https://res.wx.qq.com/t/wx_fed/we-emoji/res/v1.3.10/assets/newemoji/Social.png)