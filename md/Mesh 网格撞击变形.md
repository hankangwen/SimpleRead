> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/Gnk8n59hVgswX7QAfzCLfA)

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/3x56T6iafMuAKIatAiaABoNeO3mvA2fibB0xibgZO3n9k1mB5ribOAzOiaYw5ydvCdiaAQoesJa8QWb181nOXYaBXdzzg/640?wx_fmt=gif&from=appmsg)

物理碰撞
----

*   两个游戏物体发生碰撞的必要条件：
    

1.  发生碰撞的两个游戏物体有 Collider（碰撞器）组件；
    
2.  其中一个物体有 Rigidbody（刚体）组件。
    

*   MonoBehaviour 中的相关回调函数：
    

<table><thead><tr data-style="border-width: 1px 0px 0px; border-right-style: initial; border-bottom-style: initial; border-left-style: initial; border-right-color: initial; border-bottom-color: initial; border-left-color: initial; border-top-style: solid; border-top-color: rgb(204, 204, 204); background-color: white;"><th data-style="border-top-width: 1px; border-color: rgb(204, 204, 204); text-align: left; background-color: rgb(240, 240, 240); font-size: 14px; min-width: 85px;">回调函数</th><th data-style="border-top-width: 1px; border-color: rgb(204, 204, 204); text-align: left; background-color: rgb(240, 240, 240); font-size: 14px; min-width: 85px;">详解</th></tr></thead><tbody><tr data-style="border-width: 1px 0px 0px; border-right-style: initial; border-bottom-style: initial; border-left-style: initial; border-right-color: initial; border-bottom-color: initial; border-left-color: initial; border-top-style: solid; border-top-color: rgb(204, 204, 204); background-color: white;"><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">OnCollisionEnter (Collision)</td><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">当前碰撞器开始接触另一个碰撞器时被调用。</td></tr><tr data-style="border-width: 1px 0px 0px; border-right-style: initial; border-bottom-style: initial; border-left-style: initial; border-right-color: initial; border-bottom-color: initial; border-left-color: initial; border-top-style: solid; border-top-color: rgb(204, 204, 204); background-color: rgb(248, 248, 248);"><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">OnCollisionStay (Collision)</td><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">当前碰撞器持续接触另一个碰撞器时被调用。</td></tr><tr data-style="border-width: 1px 0px 0px; border-right-style: initial; border-bottom-style: initial; border-left-style: initial; border-right-color: initial; border-bottom-color: initial; border-left-color: initial; border-top-style: solid; border-top-color: rgb(204, 204, 204); background-color: white;"><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">OnCollisionExit (Collision)</td><td data-style="border-color: rgb(204, 204, 204); font-size: 14px; min-width: 85px;">当前碰撞器停止接触另一个碰撞器时被调用。</td></tr></tbody></table>

碰撞数据
----

物体发生碰撞时的碰撞数据存储于 Collision 对象中，相关属性：

*   articulationBody：与当前碰撞器发生碰撞的物体上的 Articulation Body 组件；
    
*   body：与当前碰撞器发生碰撞的物体上的 Rigidbody 或 Articulation Body 组件；
    
*   collider：与当前碰撞器发生碰撞的碰撞器；
    
*   contactCount：碰撞接触点的数量；
    
*   contacts：碰撞接触点数组，碰撞接触点包含位置和法线数据；
    
*   gameObject：与当前碰撞器发生碰撞的物体；
    
*   impulse：碰撞冲量；
    
*   relativeVelocity：两个碰撞对象的相对线性速度；
    
*   rigidbody：与当前碰撞器发生碰撞的物体上的 Rigidbody 组件；
    
*   transform：与当前碰撞器发生碰撞的物体的 Transform 组件。
    

撞击变形
----

*   撞击判定：当 relativeVelocity 的长度大于一定阈值时，可以判定为撞击；
    
*   网格变形：通过调整撞击物体上的网格顶点，使网格发生形变：
    

1.  顶点位移量：计算网格顶点到碰撞接触点的距离，距离越近的变形程度应该越大，顶点位移量也就相应越大。
    
2.  顶点位移方向：通过将 relativeVelocity 从世界空间转换到被撞击物体的局部空间获得顶点位移方向。
    

```
//变形发生的阈值[SerializeField] private float deformationThreshold = 5f;//变形影响的半径[SerializeField] private float deformationRadius = .5f;private void OnCollisionEnter(Collision collision){    //两个碰撞对象的相对线性速度足够大时网格变形    if (collision.relativeVelocity.magnitude > deformationThreshold)    {        //撞击的物体        GameObject collideGameObject = collision.gameObject;        //物体上的网格        Mesh mesh = collideGameObject.GetComponent<MeshFilter>().sharedMesh;        //网格上的顶点数组        Vector3[] vertices = mesh.vertices;        //遍历撞击接触点        for (int i = 0; i < collision.contactCount; i++)        {            ContactPoint contactPoint = collision.GetContact(i);            //全局坐标转撞击物体的局部坐标            Vector3 world2LocalPoint = collideGameObject.transform.InverseTransformPoint(contactPoint.point);            //遍历网格顶点 顶点移位形成变形            for (int j = 0; j < vertices.Length; j++)            {                //网格顶点到撞击接触点的距离                float magnitude = (world2LocalPoint - vertices[j]).magnitude;                //在影响范围内                if (magnitude < deformationRadius)                {                    //位移量                    float delta = (deformationRadius - magnitude) / deformationRadius * .1f;                    //位移                    vertices[j] -= collideGameObject.transform                        .InverseTransformDirection(collision.relativeVelocity) * delta;                }            }        }        //更新网格顶点        mesh.vertices = vertices;        mesh.RecalculateNormals();        mesh.RecalculateBounds();        //重启碰撞        collision.collider.enabled = false;        collision.collider.enabled = true;    }}
```