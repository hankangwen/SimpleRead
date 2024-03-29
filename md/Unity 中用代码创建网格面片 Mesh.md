> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/mp8LTscbwKjaEsnCOn3yDA)

### Unity 中用代码创建网格面片 Mesh

今天我们来实现用代码去创建一个可以挂材质球的网格面片物体。

如果我们在场景中新建一个 3D Object/Quad 面片,

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_35_43_640.png)

我们会发现它上面挂载了这些组件

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_35_52_640.png)

让此面片显示在场景中的主要组件是 MeshFilter  和 Mesh Renderer, 前者是从模型中读取模型顶点，UV 坐标等数据，后者则是通过这些数据把面片渲染出来。  

老规矩，搭建场景:  创建一个空物体 CreateMesh 并且挂载上我们的脚本

CreateMesh 脚本如下：  

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateMesh : MonoBehaviour
{
    // Start is called before the first frame update
    public Material material;
    private void Start()
    {
        Vector3[] vertices = new Vector3[4];
        Vector2[] uv = new Vector2[4];
        int[] triangles = new int[6];

        vertices[0] = new Vector3(0, 1);
        vertices[1] = new Vector3(1, 1);
        vertices[2] = new Vector3(0, 0);
        vertices[3] = new Vector3(1, 0);

        uv[0] = new Vector2(0, 1);
        uv[1] = new Vector2(1, 1);
        uv[2] = new Vector2(0, 0);
        uv[3] = new Vector2(1, 0);

        triangles[0] = 0;
        triangles[1] = 1;
        triangles[2] = 2;
        triangles[3] = 2;
        triangles[4] = 1;
        triangles[5] = 3;

        Mesh mesh = new Mesh();

        mesh.vertices = vertices;
        mesh.uv = uv;
        mesh.triangles = triangles;

        GameObject gameObject = new GameObject("Mesh", typeof(MeshFilter), typeof(MeshRenderer));
        gameObject.transform.localScale = new Vector3(30, 30, 1);

        gameObject.GetComponent<MeshFilter>().mesh = mesh;

        gameObject.GetComponent<MeshRenderer>().material = material;
    }
}
```

我们先创建一个面片的顶点数组（4 个）  

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_2_640.png)

其次通过顺时针的顺序将顶点位置添加到数组中  

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_6_640.png)

triangles  是三角面，一个面片有两个三角面，一个三角面有三个顶点数据，我们把顶点的下标分别填到三角面数组中，部分定点可以复用，顶点下标填入的顺序会影响三角面是向前渲染还是向后渲染。最后给物体上的 MeshRenderer 里的材质球赋上我们创建的材质。这里我新建一个材质，选择了 Unlit/Transparent, 挂上一张图片

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_11_640.png)

运行程序，我们会发现场景中生成了一个 Mesh 面片，

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_14_640.png)

因为 00 点在左下角，所以面片原点在左下角，如果我们想让它在中心位置，则把顶点坐标修改一下

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_19_640.png)

![](https://gitcode.net/hankangwen/blog-image/raw/master/pictures/2024/02/19_9_36_24_640.png)