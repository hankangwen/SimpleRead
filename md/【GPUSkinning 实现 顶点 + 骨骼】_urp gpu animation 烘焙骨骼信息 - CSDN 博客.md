> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/weixin_43934384/article/details/128952070)

#### GPUSkinning 实现 顶点 + 骨骼

*   [前言](#_2)
*   [什么是模型？](#_6)
*   *   [对于 unity Animation 的优化](#unity_Animation_29)
    *   *   [什么是 unity Animation? 为什么要优化它们?](#unity_Animation_31)
        *   [该如何优化 Animator+SkinnedMeshRenderer?](#AnimatorSkinnedMeshRenderer_34)
        *   *   [1、通过 KkinnedMeshRendere 和 Animator 修改模型并采样（这里暂时以只存在单个 SkinnedMeshRenderer 为例）](#1KkinnedMeshRendereAnimatorSkinnedMeshRenderer_38)
            *   [2、保存动画信息](#2_137)
            *   [3、将动画信息传递给材质](#3_284)
            *   [4、材质读取动画信息](#4_347)
            *   [5、简单写一个烘培的工具](#5_460)
            *   [6、优化](#6_851)
            *   *   [动画的播放的优化](#_855)
                *   [多模型的烘培](#_965)
        *   [基于骨骼的动画贴图](#_1093)

前言
--

不知不觉已经正式工作半年多了，之前的 [UE4](https://so.csdn.net/so/search?q=UE4&spm=1001.2101.3001.7020) 学习记录还没开头就噶了。但是好在游戏方面的学习并没有落下，之后应该会时不时在这里更新，算是给自己一个交代吧。那就不废话了，现在开始吧。

什么是模型？
------

模型，在 [unity](https://so.csdn.net/so/search?q=unity&spm=1001.2101.3001.7020) 运行以名为 “mesh”（网格）的类存储。从本质上来说，模型只是存储了很多点、线、面以及其他信息的一个文件。  
要理解这句话，可以看看接下来的部分，懂得都懂可以直接看下一小节。  
我们在打开 Blender（其他建模工具也可以）并创建一个立方体（Blender 已经帮我们创建好了）

![](https://img-blog.csdnimg.cn/2c8a282de90d485389f614e0a9c990bc.png#pic_center)  
我们先把右上角的渲染模式改成第一个（原本默认是第二个），然后分别按键盘上方数字键的 1、2、3，可以分别进入顶点、线段、面的编辑模式。  
![](https://img-blog.csdnimg.cn/69a1c88a471e48ba91cb74d4883bc488.png)![](https://img-blog.csdnimg.cn/6863d7c22fa14631bbaf1be462cc8ead.png)![](https://img-blog.csdnimg.cn/9ada03e5b08e490fa0ad5b00398bc788.png)

模型其实就是这些点线面组成的数据文件，平常我们见到的模型都是已经被应用程序可视化到屏幕上了。  
我们再在 Blender 中将立方体以 Obj 格式保存，再用记事本打开这个 Obj 文件，就会看到以下的内容  
![](https://img-blog.csdnimg.cn/4f9b41bf471e4c1083bd65c666997403.png#pic_center)  
![](https://img-blog.csdnimg.cn/1566fabe019c4c15b3ba9cd3a6dd3d0a.png)![](https://img-blog.csdnimg.cn/01872a24003d4dd2bf0a34da4b62846a.png)

![](https://img-blog.csdnimg.cn/d2af0d37eb6a455abec8c97768df9012.png)![](https://img-blog.csdnimg.cn/ecd2bb9a7d23424a9f3029c8d5190d39.png)  
![](https://img-blog.csdnimg.cn/99f5cef026664063a4bf2db621faf261.png)![](https://img-blog.csdnimg.cn/39f81a7431c140a0a44e6819d4d17df3.png)

![](https://img-blog.csdnimg.cn/59d3447fee1d45d797ae94d6655944a5.png)![](https://img-blog.csdnimg.cn/806f2a32dc404356bb23571942901d2c.png)  
这里是个人认为模型最重要的地方，就是结合之前的信息所得到的面的信息，比如第一行所代表的面，它由 v1,v5,v7,v3 几个顶点组成，每个顶点用的 uv 坐标分别是 uv1,uv5,uv9,uv3, 且都是用 na 作为法线，左后得到了上面右图中青色的那个面。  
在 Unity 中所有的面都是三角面（一行只有三个顶点信息），即使你建模的时候是四角面，Unity 也会自动帮你切割，上面的一些信息只是举例希望大家能更好理解模型是什么（当然其他格式的模型文件存储格式也不太一样）。

![](https://img-blog.csdnimg.cn/25126b4f9288449a8e98976a7b1802dc.png#pic_center)

### 对于 unity Animation 的优化

在了解了上面的模型的基础知识之后，我们将深入一些，了解一下对 unity Animation 的优化。

#### 什么是 unity Animation? 为什么要优化它们?

其实这个理由很简单，骨骼动画要使用到 SkinnedMeshRenderer，其渲染的模型是不能被合批的，在场景中有许多对象使用 Animator+SkinnedMeshRenderer 的组合的话会导致 DrawCall 次数过多英雄游戏效率。  
![](https://img-blog.csdnimg.cn/d8a148690d9c4f6a95bac3534bbd64ee.png#pic_center)

#### 该如何优化 Animator+SkinnedMeshRenderer?

知道原因后，如何优化它们呢？或者说，有没有什么方法能够替代它们呢？当然是有的，我们可以先结合渲染管线的知识来思考一下，Skinned [Mesh](https://so.csdn.net/so/search?q=Mesh&spm=1001.2101.3001.7020) Render 主要帮助我们做了什么工作呢？能不能通过在管线中的某一步优化它呢？  
如果对于渲染管线有一定了解的同学应该都知道在管线中有那么一个操作，就是将顶点坐标从模型空间转换到裁剪空间，那么我们是不是就可以将一定时间间隔的顶点坐标记录下来用于裁剪空间的坐标转换呢？

##### 1、通过 KkinnedMeshRendere 和 Animator 修改模型并采样（这里暂时以只存在单个 SkinnedMeshRenderer 为例）

我们都知道 Animator 会通过插值修改模型的骨骼信息从而修改顶点的位置信息，接下来的问题就是怎么处理获得采样动画序列后的模型信息。Unity 已经很贴心的为我们在 SkinnedMeshRenderer 组件中准备了 BakeMesh 函数, 它可以将当前蒙皮动画的模型以不带骨骼的 Mesh 存储下来，我们就可以利用这个烘培好的 Mesh 将每个顶点对应帧的位置或者偏移存储下来。  
（以下是一个示例）

```
using UnityEditor.Animations;
using UnityEngine;

public class AnimatorCtrl : MonoBehaviour
{
    public Animator animator;
    public AnimatorController animatorController;
    public AnimationClip animation;
    [Range(0, 1)]
    public float animationSlider;
    private float lastAnimTime = 0;
    public bool DebugOn = false;
    // Start is called before the first frame update
    void Start()
    {
        ///获取Animator组件
        animator = gameObject.GetComponent<Animator>();
        if (animator == null) animator = gameObject.AddComponent<Animator>(); 
        ///确保Animtor组件有AnimatorController
        if(animator.runtimeAnimatorController == null)
        {
            animatorController = new AnimatorController();
            animatorController.name = "Ctrl";
            animatorController.AddLayer("Layer0");
            animator.runtimeAnimatorController = animatorController;
        }
        else
        {
            animatorController = (AnimatorController)animator.runtimeAnimatorController;
            if(animatorController.layers.Length < 1) animatorController.AddLayer("Layer0");
        }
        ///向AnimatorCtroller中加入动画
        if (animation != null)
        {
            AnimatorState state = animatorController.layers[0].stateMachine.AddState(animation.name);
            state.motion = animation;
            animator.speed = .0f;
        }
        //Debug.LogError(animation.length);
        if (DebugOn)
        {
            Invoke("DebugOnMethod", 0.1f);
        }
    }

    // Update is called once per frame
    void Update()
    {
        ///根据animationSlider的值改变模型的信息
        if (animationSlider != lastAnimTime)
        {
            animator.Play(animation.name, 0, animationSlider);
            lastAnimTime = animationSlider;
        }
    }

    void DebugOnMethod()
    {
        ///在开始游戏后在x轴上实例化出这个动画以60帧播放时每一帧的动作
        SkinnedMeshRenderer skinnedMesh = gameObject.GetComponent<SkinnedMeshRenderer>();
        if (skinnedMesh == null) skinnedMesh = gameObject.GetComponentInChildren<SkinnedMeshRenderer>();
        if (skinnedMesh != null)
        {
            int totalFrame = (int)animation.length * 60;
            GameObject goParent = new GameObject("Parent");
            animator.speed = 1.0f;
            animator.Play(animation.name, 0, 0f);
            float deltaTime = animation.length / totalFrame;
            ///这里Animator只能在Update后跟上BakeMesh，不能用Play(name,layer,time)后跟上BakeMesh
            ///原因可能是Play后对于Mesh的采样操作是异步的，导致模型信息并没有变化（具体原因还没找到资料）
            for (int i = 0; i < totalFrame; ++i)
            {
                animator.Update(deltaTime);
                GameObject go = new GameObject();
                Mesh mash = new Mesh();
                MeshFilter mf = go.AddComponent<MeshFilter>();
                ///这里这部我们就已经获取到模型信息了
                skinnedMesh.BakeMesh(mash);
                mf.sharedMesh = mash;
                MeshRenderer mr = go.AddComponent<MeshRenderer>();
                mr.material = skinnedMesh.material;
                go.transform.position = gameObject.transform.position - (i + 1) * 3 * Vector3.right;
                Quaternion eular = new Quaternion();
                eular.eulerAngles = new Vector3(-90, 0, 0);
                go.transform.rotation = eular;
                go.transform.SetParent(goParent.transform);
            }
            animator.speed = .0f;
        }
    }

}
```

![](https://img-blog.csdnimg.cn/f2fd949dd98348208f41d12991f45d55.png#pic_center)

##### 2、保存动画信息

要怎么把每个顶点地位置或偏移 (该片文档中我们以点的位置为例) 保存下来并且供 shader 读取呢？对于我们来说当然是贴图了。可是如果位置或偏移大于贴图存储的范围(0f1.0f) 的话该如何处理呢？那么我们就便利找到模型中每个轴上的的绝对值，把每个点的值映射到 01 的范围的同时，把这每个轴上最大的绝对值也存储下来。同时，我们也需要把动画的时间、每秒帧数给存储下来，用于给 Shader 处理动画信息。（Animator 在处理顶点位置的同时也会处理法线信息，这里我们存储起来先不用）

```
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class GPUSkinningAsset : ScriptableObject
{
    //烘培出来的贴图
    public Texture2D[] textures;
    //烘培贴图的大小
    public Vector2Int textureSize;
    //动画在三个轴上的缩放
    public Vector3 animScalar;
    //动画时长
    public float animTime;
    //动画贴图数
    public int textureCount;
    //顶点数
    public int vertexCount;

#if UNITY_EDITOR
    [System.NonSerialized]
    // 顶点位置数组
    private List<List<Vector3>> frameBakeData;
    // 顶点法线数组
    private List<List<Vector3>> normalBakeData;
    ///这个函数由其他地方调用，调用的地方一会会放在下面
    public void CreateBakedAssets(string path, List<List<Vector3>> framePositions, List<List<Vector3>> frameNormals, float animationClipTime)
    {
        animScalar = Vector3.zero;
        animTime = animationClipTime;
        vertexCount = framePositions[0].Count;
        frameBakeData = framePositions;
        normalBakeData = frameNormals;
        ///这里我们先固定贴图大小为256*256
        int TEX_SIZE = 256;
        int frameVertexCount = vertexCount * frameBakeData.Count * 2;
        textureSize = new Vector2Int(TEX_SIZE, TEX_SIZE);
        if (frameBakeData.Count > 0) vertexCount = frameBakeData[0].Count;
        double[][] offsets = new double[vertexCount * frameBakeData.Count][];
        double[] scaler = new double[3];
        // generate texture
        for (int frameIndex = 0; frameIndex < frameBakeData.Count; frameIndex++)
        {
            List<Vector3> meshFrame = frameBakeData[frameIndex];
            List<Vector3> meshNormal = normalBakeData[frameIndex];
            for (int vert = 0; vert < meshFrame.Count; vert++)
            {
                //Debug.LogError(vert.ToString() + ":" + meshFrame[vert]);
                int arrayPos = (frameIndex * meshFrame.Count) + vert;
                Vector3 framePos = meshFrame[vert];
                Vector3 frameNormal = Vector3.zero;
                if (meshNormal.Count > vert)frameNormal = meshNormal[vert];
                double[] data = new double[6]
                {
                        framePos.x,
                        framePos.y,
                        framePos.z,
                        frameNormal.x,
                        frameNormal.y,
                        frameNormal.z
                };
                offsets[arrayPos] = data;
                ///比较获得XZY轴最大的位置的绝对值
                scaler[0] = Math.Max(scaler[0], System.Math.Abs(data[0]));
                scaler[1] = Math.Max(scaler[1], System.Math.Abs(data[1]));
                scaler[2] = Math.Max(scaler[2], System.Math.Abs(data[2]));
            }
        }
        animScalar = new Vector3((float)scaler[0], (float)scaler[1], (float)scaler[2]);
        List<Texture2D> bakeTextures = new List<Texture2D>();
        int xPos = 0;
        int yPos = 0;
        int textureIndex = 0;
        int frame = 0;
        int pixelsLeft = textureSize.x * textureSize.y;
        int verticesLeftInFrame = vertexCount * 2;
        for (int vert = 0; vert < offsets.Length; vert++)
        {
            double[] data = offsets[vert];
            if (data == null) continue;
            for (int s = 0; s < data.Length; s++)
            {
                data[s] /= s < 3 ? scaler[s] : 1.0f;
                data[s] = data[s] * 0.5d + 0.5d;
            }

            for (int c = 0; c < data.Length; c += 3)
            {
                Color color = new Color((float)data[c + 0], (float)data[c + 1], (float)data[c + 2], 1);
                if (yPos == textureSize.y)
                {
                    xPos++;
                    yPos = 0;
                    if (xPos == textureSize.x)
                    {
                        xPos = 0;
                        textureIndex++;
                        pixelsLeft = textureSize.x * textureSize.y;
                    }
                }
                if (bakeTextures.Count <= textureIndex)
                {
                    ///这里强调一下，如果要使动画更精确，图片的保存格式最好是RGBAHalf往上，否则会有失真导致动画中某些顶点闪现
                    bakeTextures.Add(new Texture2D(textureSize.x, textureSize.y, TextureFormat.RGBAHalf, false, false));
                }
                Texture2D bakeTexture = bakeTextures[textureIndex];
                bakeTexture.SetPixel(xPos, yPos, color);
                yPos++;

                pixelsLeft--;
                verticesLeftInFrame--;
                // 让同一帧的顶点和法线数据在同一张贴图里
                if (verticesLeftInFrame == 0)
                {
                    verticesLeftInFrame = vertexCount * 2;
                    frame++;
                    if (pixelsLeft < vertexCount * 2)
                    {
                        textureIndex++;
                        pixelsLeft = textureSize.x * textureSize.y;
                        xPos = 0;
                        yPos = 0;
                    }
                }
            }
        }
        var existingTextures = UnityEditor.AssetDatabase.LoadAllAssetsAtPath(path).Where(a => a is Texture2D).ToArray();
        for (int t = 0; t < bakeTextures.Count; t++)
        {
            bakeTextures[t].name = string.Format("{0}_{1}", this.name, t);
            foreach (var existing in existingTextures)
                DestroyImmediate(existing, true);
            UnityEditor.AssetDatabase.AddObjectToAsset(bakeTextures[t], this);
        }
        textures = bakeTextures.ToArray();
        textureCount = textures.Length;
    }
#endif
}
```

![](https://img-blog.csdnimg.cn/66d4221ef9cd4a5e8071276eccba21b2.png)

##### 3、将动画信息传递给材质

这里其实没有内容，主要就是数据传递。但是有几点需要注意的地方：

*   由于我们一个贴图的大小有限，不太可能把每一帧都保存在一张贴图中，所以我们向材质发送的不是一张贴图，而是贴图数组 (Texture2DArray)
*   将 Texture 数据保存到 Texture2DArray 中有两种方法，分别是 Texture2DArray 的 SetPixels 和 Graphics.CopyTexture，如果可以的话尽量 Graphics.CopyTexture，它耗时更少。
*   Texture2DArray 的 FilterMode 要设置为 Point，因为对于贴图的采样是用小数的，如果设置为 Bilinear 或者 Trilinear 的话就会因为精度问题导致采样的结果有误。
*   要使用 GPUInstancing，我们要使用 MaterialPropertyBlock，并且如果要确保能够实现 GPUInstancing 优化 DrawCall 的效果，每个播放动画对象的贴图属性不能设置的不一样，否则会生成新的动画实例导致优化失败。所以多个相同材质相同模型的对象要播放不同的动画，需要把多个动画的动画贴图都保存到 texture2DArray 里，且需要用 SkinnedMeshRenderer 的 SharedMaterial(共享材质) 来设置贴图。（这里我们先使用一个动画举例，要多个动画的播放会放在之后）

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public class GPUSkinningSetter : MonoBehaviour
{
    public GPUSkinningAsset Animation;
    private MeshRenderer render;
    private MaterialPropertyBlock matBlock;
    private Material mat;
    private Texture2DArray texArray;
    // Start is called before the first frame update
    void Start()
    {
        SetInfo();
    }

    private void OnEnable()
    {
        SetInfo();
    }

    private void SetInfo()
    {
        if (render == null) render = gameObject.GetComponent<MeshRenderer>();
        if (matBlock == null) matBlock = new MaterialPropertyBlock();
        if (Animation != null)
        {
            //查看是否支持Graphics.CopyTexture,尽量使用Graphics.CopyTexture，因为它比SetPixels耗时更短
            CopyTextureSupport copyTextureSupport = SystemInfo.copyTextureSupport;
            texArray = new Texture2DArray(Animation.textureSize.x, Animation.textureSize.y, Animation.textures.Length, Animation.textures[0].format, false, false);
            texArray.filterMode = FilterMode.Point;
            DontDestroyOnLoad(texArray);
            for (int i = 0; i < Animation.textures.Length; ++i)
            {
                if (copyTextureSupport == UnityEngine.Rendering.CopyTextureSupport.None) texArray.SetPixels(Animation.textures[i].GetPixels(0), i, 0);
                else Graphics.CopyTexture(Animation.textures[i], 0, 0, texArray, i, 0);
            }
            mat = render.sharedMaterial;
            mat.SetTexture("_AnimationTex", texArray);
            //如果使用SetPixels的话需要Apply一下
            if (copyTextureSupport == UnityEngine.Rendering.CopyTextureSupport.None) texArray.Apply();
            render.GetPropertyBlock(matBlock);
            matBlock.SetVector("_Scale", Animation.animScalar);
            matBlock.SetFloat("_AnimationSize", Animation.animTime);
            matBlock.SetInt("_FPS", 60);
            matBlock.SetInt("_VertexNum", Animation.vertexCount);
            matBlock.SetVector("_TextureSize", new Vector4(Animation.textureSize.x, Animation.textureSize.y, 0, 0));
            render.SetPropertyBlock(matBlock);
        }
    }
}
```

##### 4、材质读取动画信息

对于材质部分，其实和生成动画贴图反着来就行了。具体操作就是通过_Time 结构体获取时间、通过顶点序号以及其他传入的数据获得要采样贴图的下表以及采样 UV，再通过三个轴的缩放获得真正的模型坐标。需要注意的一点，就是我们采样贴图获得模型坐标是在顶点着色器中的，在顶点着色器我们是不能使用采样函数 tex2D, 只能使用 tex2Dlod，同理对于 Tex2DArray，我们也只能使用 UNITY_SAMPLE_TEX2DARRAY_LOD。

```
Shader "Unlit/GPUSkinning"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _AnimationTex ("Texture", 2DArray) = ""{}             //动画贴图
        _Scale ("Scale", Vector) = (1, 1, 1, 0)             //x, y, z轴的缩放
        _AnimationSize ("Animation Size", float) = 0        //动画长度
        _FPS("FPS", Int) = 0                                //FPS
        _VertexNum("Vertex Num", Int) = 0                   //顶点数
        _TextureSize("Texture Size", Vector) = (0, 0, 0, 0) //动画贴图大小
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma require 2darray
            #pragma multi_compile_instancing
            #pragma target 3.5

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
                uint vertexId : SV_VertexID;
                UNITY_VERTEX_INPUT_INSTANCE_ID
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
                float4 color : TEXCOORD1;
                UNITY_VERTEX_INPUT_INSTANCE_ID
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;
            UNITY_DECLARE_TEX2DARRAY(_AnimationTex);
            //GPUInstancing属性
            UNITY_INSTANCING_BUFFER_START(Props)
                    UNITY_DEFINE_INSTANCED_PROP(float, _AnimationSize)
                    UNITY_DEFINE_INSTANCED_PROP(float4, _Scale)
                    UNITY_DEFINE_INSTANCED_PROP(uint, _FPS)
                    UNITY_DEFINE_INSTANCED_PROP(uint, _VertexNum)
                    UNITY_DEFINE_INSTANCED_PROP(float4, _TextureSize)
            UNITY_INSTANCING_BUFFER_END(Props)
            float4 SampleAnimationTex(appdata v)
            {
                float animaTime = UNITY_ACCESS_INSTANCED_PROP(Props, _AnimationSize);
                float passedTime = _Time.y;
                float time = passedTime - floor(passedTime / animaTime) * animaTime;
                uint nowFrame = floor(time * (UNITY_ACCESS_INSTANCED_PROP(Props, _FPS) - 1));
                uint vertexNum = UNITY_ACCESS_INSTANCED_PROP(Props, _VertexNum);
                float4 textureSize = UNITY_ACCESS_INSTANCED_PROP(Props, _TextureSize);
                uint framePerTex = floor(textureSize.x * textureSize.y  * 1.0 / (2 * vertexNum));
                //获取当前是第几帧和使用第几个贴图
                uint currentFrame = nowFrame % framePerTex;
                uint currentTextureIndex = floor(nowFrame / framePerTex);
                uint nowVertex = currentFrame * vertexNum * 2 + v.vertexId * 2;
                uint row = floor(nowVertex / textureSize.y);
                //获取采样UV
                float uvX = row * 1.0f / textureSize.x;
                float uvY = (nowVertex % textureSize.y) * 1.0 / textureSize.y;
                float4 sampleResult = UNITY_SAMPLE_TEX2DARRAY_LOD(_AnimationTex, float3(uvX, uvY, currentTextureIndex), 0);
                float4 animScale = UNITY_ACCESS_INSTANCED_PROP(Props, _Scale);
                float4 finalResult = float4(
                                        (sampleResult.x * 2 - 1) * animScale.x,
                                        (sampleResult.y * 2 - 1) * animScale.y,
                                        (sampleResult.z * 2 - 1) * animScale.z,
                                        0);
                return finalResult;
            }

            //之后需要什么效果，再在顶点着色器和片元着色器中添加变量和计算公式即可
            v2f vert (appdata v)
            {
                v2f o;
                                UNITY_SETUP_INSTANCE_ID(v);
                UNITY_TRANSFER_INSTANCE_ID(v, o);
                o.color = SampleAnimationTex(v);
                //o.vertex = UnityObjectToClipPos(v.vertex);
                o.vertex = UnityObjectToClipPos(o.color);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                UNITY_SETUP_INSTANCE_ID(i);
                // sample the texture
                fixed4 col = tex2D(_MainTex, i.uv);
                return col;
            }
            ENDCG
        }
    }
}
```

##### 5、简单写一个烘培的工具

我写的烘培贴图的的工具特别简单，其中最重要的就是通过 Animator 的 Update 和 SkinnedMeshRenderer 的 BakeMesh 函数获得顶点信息。我就在这里不过多讲解了，只是简单的把代码贴上来。

```
#pragma warning disable 0642
#pragma warning disable 0618

using UnityEngine;
using UnityEditor;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using UnityEditor.Animations;

/// <summary>
/// Editor Window for MeshAnimator baking
/// </summary>
public class GPUSkinningGenerator : EditorWindow
{
    [SerializeField]
    private GameObject prefab;
    [SerializeField]
    private GameObject previousPrefab;
    [SerializeField]
    private List<AnimationClip> animClips = new List<AnimationClip>();
    [SerializeField]
    private SkinnedMeshRenderer skinnedRenderer;
    [SerializeField]
    private Object outputFolder;
    [SerializeField]
    private Animator animator;
    [SerializeField]
    private RuntimeAnimatorController animController;
    [SerializeField]
    private Avatar animAvatar;

    private List<AnimationClip> clipsCache = new List<AnimationClip>();

    private static GPUSkinningGenerator window;
    private static GPUSkinningGenerator Instance;

    [MenuItem("Assets/烘培动画贴图")]
    static void MakeWindow()
    {
        window = GetWindow(typeof(GPUSkinningGenerator)) as GPUSkinningGenerator;
        if (window.prefab != Selection.activeGameObject)
        {
            window.prefab = null;
            window.OnEnable();
        }
    }
    private Dictionary<string, bool> bakeAnims = new Dictionary<string, bool>();
    /// Reload the target prefab
    private void OnEnable()
    {
        Instance = this;
        titleContent = new GUIContent("烘培动画贴图");
        if (prefab == null && Selection.activeGameObject)
        {
            prefab = Selection.activeGameObject;
            OnPrefabChanged();
        }
    }
    private void OnDisable()
    {

    }
    #region GUI
    /// 绘制编辑器UI
    private void OnGUI()
    {
        GUI.skin.label.wordWrap = true;
        using (new EditorGUILayout.HorizontalScope())
        {
            prefab = EditorGUILayout.ObjectField("烘培的预制体", prefab, typeof(GameObject), true) as GameObject;
        }

        if (prefab == null) DrawWarning("需要指定烘培的预制体");
        else if (previousPrefab != prefab) OnPrefabChanged();

        if (prefab != null && !string.IsNullOrEmpty(GetPrefabPath()))
        {
            outputFolder = EditorGUILayout.ObjectField("Output Folder", outputFolder, typeof(Object), false);
        }
        GUILayout.Space(1);
        using (new GUILayout.ScrollViewScope(new Vector2()))
        {
            GUILayout.Label("<b>要烘培的动画</b>");
            for (int i = 0; i < animClips.Count; i++)
            {
                GUILayout.BeginHorizontal();
                {
                    var previous = animClips[i];
                    animClips[i] = (AnimationClip)EditorGUILayout.ObjectField(animClips[i], typeof(AnimationClip), false);
                    
                    if (GUILayout.Button("删除", GUILayout.Width(32)))
                    {
                        animClips.RemoveAt(i);
                        GUILayout.EndHorizontal();
                        break;
                    }
                }
                GUILayout.EndHorizontal();
            }
            if (GUILayout.Button("添加动画"))
            {
                animClips.Add(null);
            }
            using (new EditorGUILayout.HorizontalScope())
            {
                if (animAvatar == null)
                    GetAvatar();
                animAvatar = EditorGUILayout.ObjectField("骨骼", animAvatar, typeof(Avatar), true) as Avatar;
            }
        }
        if (prefab != null)
        {
            GUILayout.Space(10);
            int bakeCount = animClips.Count(q => q != null);
            GUI.enabled = bakeCount > 0;
            var c = GUI.color;
            GUI.color = new Color(128 / 255f, 234 / 255f, 255 / 255f, 1);
            if (GUILayout.Button(string.Format("烘培{0}份动画", bakeCount), GUILayout.Height(30)))
                CreateGPUSkinningTexture();
            if (GUILayout.Button(string.Format("Debug"), GUILayout.Height(30)))
                ExportMeshPosition();
            GUI.color = c;
            GUI.enabled = true;
        }
    }
    private void DrawWarning(string text)
    {
        int w = (int)Mathf.Lerp(300, 900, text.Length / 200f);
        using (new EditorGUILayout.HorizontalScope(GUILayout.MinHeight(30)))
        {
            var style = new GUIStyle(GUI.skin.FindStyle("CN EntryWarnIcon"));
            style.margin = new RectOffset();
            style.contentOffset = new Vector2();
            GUILayout.Box("", style, GUILayout.Width(15), GUILayout.Height(15));
            var textStyle = new GUIStyle(GUI.skin.label);
            textStyle.contentOffset = new Vector2(10, Instance.position.width < w ? 0 : 5);
            GUILayout.Label(text, textStyle);
        }
    }
    #endregion

    #region 自定义函数

    /// 选中预制体改变时的回调
    private void OnPrefabChanged()
    {
        if (Application.isPlaying)
        {
            return;
        }
        animator = null;
        animAvatar = null;
        if (prefab != null)
        {
            bakeAnims.Clear();
        }
        previousPrefab = prefab;
    }
    
    /// 返回选中的预制体的路径
    private string GetPrefabPath()
    {
        string assetPath = AssetDatabase.GetAssetPath(prefab);
        if (string.IsNullOrEmpty(assetPath))
        {
            Object parentObject = PrefabUtility.GetCorrespondingObjectFromSource(prefab);
            assetPath = AssetDatabase.GetAssetPath(parentObject);
        }
        return assetPath;
    }
    
    /// 创建烘培贴图时的动画控制器
    private UnityEditor.Animations.AnimatorController CreateBakeController()
    {
        AnimatorController controller = new AnimatorController();
        controller.name = "AnimationCtrl";
        controller.AddLayer("Layer0");
        AnimatorStateMachine baseStateMachine = controller.layers[0].stateMachine;
        foreach (var clip in animClips)
        {
            var state = baseStateMachine.AddState(clip.name);
            state.motion = clip;
        }
        return controller;
    }

    /// 返回预制体的骨骼信息
    private Avatar GetAvatar()
    {
        if (animAvatar) return animAvatar;
        var objs = EditorUtility.CollectDependencies(new Object[] { prefab }).ToList();
        foreach (var obj in objs.ToArray())
            objs.AddRange(AssetDatabase.LoadAllAssetRepresentationsAtPath(AssetDatabase.GetAssetPath(obj)));
        objs.RemoveAll(q => q is Avatar == false || q == null);
        if (objs.Count > 0)
            animAvatar = objs[0] as Avatar;
        return animAvatar;
    }

    /// 设置对象及其子对象的hideFlags
    private void SetChildFlags(Transform t, HideFlags flags)
    {
        Queue<Transform> q = new Queue<Transform>();
        q.Enqueue(t);
        for (int i = 0; i < t.childCount; i++)
        {
            Transform c = t.GetChild(i);
            q.Enqueue(c);
            SetChildFlags(c, flags);
        }
        while (q.Count > 0)
        {
            q.Dequeue().gameObject.hideFlags = flags;
        }
    }

    /// 替换名称中的特殊字符
    private string FormatClipName(string name)
    {
        string badChars = "!@#$%%^&*()=+}{[]'\";:|";
        for (int i = 0; i < badChars.Length; i++)
        {
            name = name.Replace(badChars[i], '_');
        }
        return name;
    }
    #endregion

    #region Baking Methods
    /// 采样动画，烘培贴图
    private void CreateGPUSkinningTexture()
    {
        RuntimeAnimatorController bakeController = null;
        try
        {
            string assetPath = GetPrefabPath();
            if (string.IsNullOrEmpty(assetPath))
            {
                EditorUtility.DisplayDialog("GPUSkinning", string.Format("无法获取{0}的路径", prefab.name), "OK");
                return;
            }
            if (outputFolder == null)
            {
                EditorUtility.DisplayDialog("GPUSkinning", "无法加载导出路径，请确保导出路径正确。", "OK");
                return;
            }
            string assetFolder = AssetDatabase.GetAssetPath(outputFolder);
            if (string.IsNullOrEmpty(assetFolder))
            {
                EditorUtility.DisplayDialog("GPUSkinning", "无法加载导出文件夹", "OK");
                return;
            }

            int animCount = 0;
            GameObject sampleGO = Instantiate(prefab, Vector3.zero, Quaternion.identity);
            skinnedRenderer = sampleGO.GetComponent<SkinnedMeshRenderer>();
            if (skinnedRenderer == null) skinnedRenderer = sampleGO.GetComponentInChildren<SkinnedMeshRenderer>();
            if (skinnedRenderer == null)
            {
                /// 确保烘培动画时有模型信息
                DestroyImmediate(sampleGO);
                throw new System.Exception("预制体没有skinnedMeshRenderer");
            }
            else
            {
                animator = sampleGO.GetComponent<Animator>();
                if (animator == null) animator = sampleGO.GetComponentInChildren<Animator>();
                if (animator == null) animator = sampleGO.AddComponent<Animator>();
                bakeController = CreateBakeController();
                animator.runtimeAnimatorController = bakeController;
                animator.avatar = GetAvatar();
                animator.cullingMode = AnimatorCullingMode.AlwaysAnimate;
                GameObject asset = new GameObject(prefab.name + "_GPUSkinning");
                int vertexCount = 0;
                Transform rootMotionBaker = new GameObject().transform;
                //枚举要渲染的动画
                for(int i = 0; i < animClips.Count; ++i)
                {
                    AnimationClip animClip = animClips[i];
                    //这里我们以60帧为例
                    int bakeFrames = Mathf.CeilToInt(animClip.length * 60);
                    float lastFrameTime = 0;
                    List<List<Vector3>> framePositions = new List<List<Vector3>>();
                    List<List<Vector3>> frameNormals = new List<List<Vector3>>();
                    for (int j = 0; j < bakeFrames; j++)
                    {
                        float bakeDelta = Mathf.Clamp01((float)j / bakeFrames);
                        EditorUtility.DisplayProgressBar("烘培贴图", string.Format("烘培动画:{0} 第{1}帧", animClip.name, j), bakeDelta);
                        float animationTime = bakeDelta * animClip.length;
                        if (animClip.isHumanMotion || !animClip.legacy)
                        {
                            float normalizedTime = animationTime / animClip.length;
                            string stateName = animClip.name;
                            animator.Play(stateName, 0, normalizedTime);
                            if (lastFrameTime == 0)
                            {
                                float nextBakeDelta = Mathf.Clamp01(((float)(j + 1) / bakeFrames));
                                float nextAnimationTime = nextBakeDelta * animClip.length;
                                lastFrameTime = animationTime - nextAnimationTime;
                            }
                            animator.Update(animationTime - lastFrameTime);
                            lastFrameTime = animationTime;
                        }
                        else
                        {
                            GameObject sampleObject = sampleGO;
                            Animation legacyAnimation = sampleObject.GetComponentInChildren<Animation>();
                            if (animator && animator.gameObject != sampleObject)
                                sampleObject = animator.gameObject;
                            else if (legacyAnimation && legacyAnimation.gameObject != sampleObject)
                                sampleObject = legacyAnimation.gameObject;
                            animClip.SampleAnimation(sampleObject, animationTime);
                        }

                        Mesh skinnedMesh = new Mesh();
                        skinnedRenderer.BakeMesh(skinnedMesh);
                        Vector3[] meshesInFrame = skinnedMesh.vertices;
                        Vector3[] normalsInFrame = skinnedMesh.normals;
                        rootMotionBaker.position = animator.rootPosition;
                        rootMotionBaker.rotation = animator.rootRotation;
                        for(int k =0; k < meshesInFrame.Length; ++k)
                        {
                            meshesInFrame[k] = rootMotionBaker.TransformPoint(meshesInFrame[k]);
                        }
                        // debug only
                        //Instantiate(sampleGO, j * Vector3.right, Quaternion.identity);
                        framePositions.Add(meshesInFrame.ToList());
                        frameNormals.Add(normalsInFrame.ToList());
                        vertexCount = meshesInFrame.Length;
                        DestroyImmediate(skinnedMesh);
                    }
                    string name = string.Format("{0}/{1}_GPUSkinningAsset.asset", assetFolder, FormatClipName(animClip.name));
                    GPUSkinningAsset gpuAsset = ScriptableObject.CreateInstance<GPUSkinningAsset>();
                    AssetDatabase.CreateAsset(gpuAsset, name);
                    gpuAsset.CreateBakedAssets(name, framePositions, frameNormals, animClip.length);
                    animCount++;
                }
                DestroyImmediate(rootMotionBaker.gameObject);
                DestroyImmediate(asset);
            }
            DestroyImmediate(sampleGO);
            EditorUtility.ClearProgressBar();
        }
        catch (System.Exception e)
        {
            EditorUtility.ClearProgressBar();
            EditorUtility.DisplayDialog("烘培错误", string.Format("流程有误，详见{0}", e), "OK");
            Debug.LogException(e);
        }
        finally
        {
            if (bakeController)
            {
                //AssetDatabase.DeleteAsset(AssetDatabase.GetAssetPath(bakeController));
            }
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }
    }

    public void ExportMeshPosition()
    {
        GameObject sampleGO = Instantiate(prefab, Vector3.zero, Quaternion.identity);
        skinnedRenderer = sampleGO.GetComponent<SkinnedMeshRenderer>();
        if (skinnedRenderer == null) skinnedRenderer = sampleGO.GetComponentInChildren<SkinnedMeshRenderer>();
        if (skinnedRenderer == null)
        {
            Destroy(sampleGO);
            return;
        }
        Mesh skinnedMesh = skinnedRenderer.sharedMesh;
        List<List<Vector3>> meshes = new List<List<Vector3>>();
        List<List<Vector3>> normals = new List<List<Vector3>>();
        List<Vector3> vertexs = skinnedMesh.vertices.ToList();
        meshes.Add(vertexs);
        normals.Add(skinnedMesh.normals.ToList());
        for(int i = 0; i < skinnedMesh.vertexCount; ++i)
        {
            Debug.LogWarning(i.ToString() + ":" + vertexs[i]);
        }
        DestroyImmediate(sampleGO);
    }

    #endregion
}
```

##### 6、优化

我们之前也提到有些有一些需要优化的点我这里总结一下

*   在 GPUInstancing 实现的情况下使不同的对象播放不同的动画，且播放动画的速率、开始时间等不一样
*   有些对象是由多个 MeshRenderer 和 SkinnedMeshRenderer 组成的，烘培动画贴图时需要一起烘培

###### 动画的播放的优化

这个我们提过了一些了，我们需要把所有动画贴图传给材质，因为有动画长度、FPS 以及顶点位置的缩放，采样动画贴图的是不会越界的，所以在此基础上我们只需要修改属性快的属性为对应动画的信息即可。我们需要的添加的是当前动画的贴图起始下标，动画时间的缩放、动画开始的时间。

```
Shader "Unlit/GPUSkinning"
{
    Properties
    {
       ...
        _AnimationTexIndex ("AnimationTexIndex", Int) = 0       //动画开始下标
        ...
        _AnimationStartTime("Animation Start Time", float) = 0  //动画开始时间
        _AnimationScale("Animation Scale", Range(0.8, 1.3)) = 0 //动画时间缩放
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            ...
            UNITY_INSTANCING_BUFFER_START(Props)
                    //添加对应变量的申明
                    UNITY_DEFINE_INSTANCED_PROP(int, _AnimationTexIndex)
                    ...
                    UNITY_DEFINE_INSTANCED_PROP(float, _AnimationStartTime)
                    UNITY_DEFINE_INSTANCED_PROP(float, _AnimationScale)
            UNITY_INSTANCING_BUFFER_END(Props)
            float4 SampleAnimationTex(appdata v)
            {
                ...
                //计算时间偏移
                float passedTime = UNITY_ACCESS_INSTANCED_PROP(Props, _AnimationStartTime) + _Time.y * UNITY_ACCESS_INSTANCED_PROP(Props, _AnimationScale);
                ...
                //加上贴图下标的偏移
                uint currentTextureIndex = floor(nowFrame / framePerTex) + UNITY_ACCESS_INSTANCED_PROP(Props, _AnimationTexIndex);
                ...
            }

            ...
            ENDCG
        }
    }
}
```

```
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public class GPUSkinningSetter : MonoBehaviour
{
    ...
    //要播放的动画信息
    private List<int> AnimStartMap = new List<int>();
    // Start is called before the first frame update
    void Start()
    {
        SetInfo();
        int playIdx = Random.Range(0, Animations.Length);
        NowPlayIndex = playIdx;
        PlayAnima(playIdx);
    }

    private void SetInfo()
    {
        ...
        int totalTex = 0;
        for (int i = 0; i < Animations.Length; ++i) totalTex += Animations[i].textureCount;
        ...
        //定义对应大小的texture2DArray
        texArray = new Texture2DArray(Animations[0].textureSize.x, Animations[0].textureSize.y, totalTex, Animations[0].textures[0].format, false, false);
        ...
        //复制贴图
        int texCount = 0;
        for(int i = 0; i < Animations.Length; ++i)
        {
            GPUSkinningAsset Animation = Animations[i];
            AnimStartMap.Add(texCount);
            for (int j = 0; j < Animation.textureCount; ++j)
            {
                Texture2D tex = Animation.textures[j];
                if (copyTextureSupport == UnityEngine.Rendering.CopyTextureSupport.None) texArray.SetPixels(tex.GetPixels(0), texCount, 0);
                else Graphics.CopyTexture(tex, 0, 0, texArray, texCount, 0);
                texCount ++;
            }
        }
        ...
    }

    private void PlayAnima(int idx)
    {
        GPUSkinningAsset Animation = Animations[idx];
        if(Animation != null)
        {
            render.GetPropertyBlock(matBlock);
            //其他属性的赋值
            matBlock.SetInt("_AnimationTexIndex", AnimStartMap[idx]);
            ...
            matBlock.SetFloat("_AnimationStartTime", Random.Range(0.0f, Animation.animTime));
            matBlock.SetFloat("_AnimationScale", Random.Range(0.8f, 1.3f));
            render.SetPropertyBlock(matBlock);
        }
    }
}
```

###### 多模型的烘培

这个其实也很简单只需要获取渲染预制体的所有 MeshRenderer 和 SkinnedMeshRenderer，将 MeshRenderer 的 Mesh 和 SkinnedMeshRenderer 烘培出来的 Mesh 进行合并后保存下来即可，这一步操作在 MeshAnimator 如下 (太懒了，懒得手写实现一遍了)

```
private struct CombineInstanceMaterial
{
    public CombineInstance combine;
    public Material material;
    public Mesh sharedMesh;
}
private Mesh GenerateCombinedMesh(List<MeshFilter> filters, List<SkinnedMeshRenderer> renderers, out bool combined)
{
    int totalMeshes = filters.Count + renderers.Count;
    combined = false;
    //如果只有一个Mesh直接返回
    if (totalMeshes == 1 && !shaderGraphSupport)
    {
        foreach (MeshFilter mf in filters)
        {
            return mf.sharedMesh;
        }
        foreach (SkinnedMeshRenderer sr in renderers)
        {
            return sr.sharedMesh;
        }
    }
    List<Mesh> tempMeshes = new List<Mesh>();
    List<CombineInstanceMaterial> combineInstances = new List<CombineInstanceMaterial>();
    //将mesh及其对应的材质缓存下来
    foreach (MeshFilter mf in filters)
    {
        Material[] materials = new Material[0];
        if (mf == null)
            continue;
        Mesh m = mf.sharedMesh;
        if (m == null) m = mf.mesh;
        if (m == null)
            continue;
        var mr = mf.GetComponent<MeshRenderer>();
        if (mr)
        {
            materials = mr.sharedMaterials.Where(q => q != null).ToArray();
        }
        var matrix = mf.transform.localToWorldMatrix;
        if (mr && !mr.enabled)
        {
            matrix = Matrix4x4.zero;
        }
        for (int i = 0; i < m.subMeshCount; i++)
        {
            combineInstances.Add(new CombineInstanceMaterial()
            {
                combine = new CombineInstance()
                {
                    mesh = m,
                    transform = matrix,
                    subMeshIndex = i
                },
                material = materials.Length > i ? materials[i] : null,
                sharedMesh = m,
            });
        }
    }
    foreach (SkinnedMeshRenderer sr in renderers)
    {
        Material[] materials = sr.sharedMaterials.Where(q => q != null).ToArray();

        if (sr == null || sr.sharedMesh == null)
            continue;

        for (int i = 0; i < sr.sharedMesh.subMeshCount; i++)
        {
            Mesh t = new Mesh();
            sr.BakeMesh(t);
            tempMeshes.Add(t);
            var m = sr.transform.localToWorldMatrix;
            Matrix4x4 scaledMatrix = Matrix4x4.TRS(MatrixUtils.GetPosition(m), MatrixUtils.GetRotation(m), sr.enabled ? Vector3.one : Vector3.zero);
            combineInstances.Add(new CombineInstanceMaterial()
            {
                combine = new CombineInstance()
                {
                    mesh = t,
                    transform = scaledMatrix,
                    subMeshIndex = i
                },
                material = materials.Length > i ? materials[i] : null,
                sharedMesh = sr.sharedMesh,
            });
        }
    }
    Dictionary<Material, Mesh> materialMeshes = new Dictionary<Material, Mesh>();
    Mesh mesh = null;
    Material nullMaterial = new Material(Shader.Find("Standard"));
    //根据材质合并Mesh
    while (combineInstances.Count > 0)
    {
        Material cMat = combineInstances[0].material;
        var combines = combineInstances.Where(q => q.material == cMat).Select(q => q.combine).ToArray();
        combineInstances.RemoveAll(q => q.material == cMat);
        mesh = new Mesh();
        mesh.CombineMeshes(combines, true, true);
        if (cMat == null)
            cMat = nullMaterial;
        materialMeshes.Add(cMat, mesh);
        tempMeshes.Add(mesh);
    }
    //将所有Mesh合并
    CombineInstance[] finalCombines = materialMeshes.Select(q => new CombineInstance() { mesh = q.Value }).ToArray();
    mesh = new Mesh();
    mesh.CombineMeshes(finalCombines, false, false);
    mesh.RecalculateBounds();
    combined = true;
    foreach (Mesh m in tempMeshes)
    {
        DestroyImmediate(m);
    }
    if (shaderGraphSupport)
    {
        var vertexIndexUvs = new Vector2[mesh.vertexCount];
        for (int i = 0; i < vertexIndexUvs.Length; i++)
        {
            vertexIndexUvs[i] = new Vector2(i, 0);
        }
        mesh.uv4 = vertexIndexUvs;
    }
    return mesh;
}
```

#### 基于骨骼的动画贴图

还有一种 GpuSkinning 是基于骨骼变换实现的，原理就是将骨骼的变换信息、顶点权重等记录在贴图里，然后在 shader 里进行计算，它比记录顶点的方式比内存占用更小，但是计算量更多，之后有机会的话我也会实现一下，这里先放上相关链接。由于时间有限，我还没有完全实现这个方法，下面先将思路和部分实现说明一下。我只将其简单实现了一下，没有用于 GPUInstancing, 大家感兴趣可以结合这个方法实现一下 GPUInstancing。  
（[这是参考的资料](https://blog.csdn.net/yxriyin/article/details/83018985)）  
首先我们先要知道一点，一个顶点在绑定骨骼后，其在播放动画时唯一不变的是相对于其绑定骨骼的相对位置，这句话也可以理解成，一个顶点对于其绑定骨骼空间坐标是不变的。那么如果我们获得了一个顶点及其绑定骨骼切改骨骼可以追溯到根骨骼的话，那么我们就可以先将这个顶点转换到其绑定骨骼的骨骼空间，然后再播放动画后，将顶点从骨骼空间转换到模型空间。（这段不理解的话可以看看《游戏引擎架构》的 11.5 蒙皮及生成矩阵调色板一节，书的链接我放在下面，大家可以看看，其他的内容也很好，十分推荐）  
而通常我们导入 unity 的带骨骼的模型，它初始的姿势我们称为绑定姿势 (Bind Pose)，通过 MeshRenderer 传入的模型顶点也都是这个姿势对应的顶点坐标。所以对于上面的过程，我们要将顶点先从绑定姿势的模型空间转到骨骼空间，再用播放动画后的骨骼空间转到模型空间。  
如果对于矩阵乘法比较了解的同学应该知道，要进行上述的空间变换的话，需要对应的矩阵：绑定姿势下模型空间到骨骼空间的矩阵、播放动画后骨骼空间到模型空间的矩阵。播放动画后 animationController 会帮我们自动调整骨骼的位置，我们通过骨骼 Transform 获得相应的矩阵即可（Matrix4x4 类有个 TRS 静态方法，可以通过传入坐标、旋转、缩放三个变量获得变换矩阵, 或者直接使用 Transform.worldToLocalMartix），如果一个骨骼有父骨骼的话，我们只需要左乘父骨骼的变换矩阵即可。  
那么接下来的问题就是如何获得绑定姿势下的矩阵了，Unity 已经贴心地帮我们把绑定姿势下各个骨骼的骨骼空间到模型空间的矩阵处理好了，放在 Mesh 类下的 bindposes 变量中（Matrix4x4 类型），正常来说每个顶点先乘 bindposes，然后再乘以播放动画后的骨骼转模型矩阵即可。而我们动画贴图保存的信息不再是顶点坐标，而是每个 bindposes 乘以骨骼转模型矩阵的数据。  
首先是烘培贴图，和之前比没啥要特别注意的点，我就直接上代码了。

```
private void CreateGPUSkinningTexture()
{
    ....
    for (int i = 0; i < animClips.Count; ++i)
    {
        ....
        List<List<Matrix4x4>> boneMatrixsList = new List<List<Matrix4x4>>();
        for (int j = 0; j < bakeFrames; j++)
        {
            ....
            List<Matrix4x4> boneMatrixs1 = new List<Matrix4x4>();
            List<Matrix4x4> boneMatrixs2 = new List<Matrix4x4>();
            for (int k = 0; k < skinnedRenderer.bones.Length; ++k)
            {
                //方法一：通过骨骼树的结构构造骨骼空间转模型空间矩阵
                boneMatrixs1.Add(TransformBone(skinnedRenderer.bones[k], skinnedRenderer.sharedMesh.bindposes[k], false));
                //方法二：通过骨骼的transform内置结构构造骨骼空间转模型空间矩阵
                boneMatrixs2.Add(skinnedRenderer.bones[k].localToWorldMatrix * skinnedRenderer.sharedMesh.bindposes[k]);
            }
            //这里只是用来Debug
            Mesh bakeMesh = new Mesh();
            skinnedRenderer.BakeMesh(bakeMesh);
            BoneWeight bw = skinnedRenderer.sharedMesh.boneWeights[1145];
            Vector3 vertex = skinnedRenderer.sharedMesh.vertices[1145];
            Vector3 finalPos1 = boneMatrixs1[bw.boneIndex0].MultiplyPoint(vertex) * bw.weight0 +
                boneMatrixs1[bw.boneIndex1].MultiplyPoint(vertex) * bw.weight1 +
                boneMatrixs1[bw.boneIndex2].MultiplyPoint(vertex) * bw.weight2 +
                boneMatrixs1[bw.boneIndex3].MultiplyPoint(vertex) * bw.weight3;
            Vector3 finalPos2 = boneMatrixs2[bw.boneIndex0].MultiplyPoint(vertex) * bw.weight0 +
                boneMatrixs2[bw.boneIndex1].MultiplyPoint(vertex) * bw.weight1 +
                boneMatrixs2[bw.boneIndex2].MultiplyPoint(vertex) * bw.weight2 +
                boneMatrixs2[bw.boneIndex3].MultiplyPoint(vertex) * bw.weight3;
            Debug.LogError("realPos: " + skinnedRenderer.gameObject.transform.localToWorldMatrix.MultiplyPoint(bakeMesh.vertices[1145]) +
                            "\ntestpos1: " + finalPos1 +
                            "\ntestpos1: " + finalPos2 +
                            "\nmatrix: " + boneMatrixs2[bw.boneIndex0]);
                            
                            
            boneMatrixsList.Add(boneMatrixs1);
            //boneMatrixsList.Add(boneMatrixs2);
        }
    }
    ....
}

public Matrix4x4 TransformBone(Transform bone, Matrix4x4 mat, bool debugOn)
{
    if(debugOn) Debug.LogError(mat);
    Matrix4x4 mat4x4 = Matrix4x4.TRS(bone.localPosition, bone.localRotation, bone.localScale) * mat;
    if (bone.parent != null) mat4x4 = TransformBone(bone.parent, mat4x4, debugOn);
    return mat4x4;
}
```

由于 Matrix4x4 是 4 行 4 列的矩阵且不是所有值的范围都在 0~1，所以在烘培时也需要进行一下缩放。

```
public void CreateBakedAssets(string path, List<List<Matrix4x4>> BonesMatList, float animationClipTime)
{
    ....
    float[] scaler = new float[3];
    for (int frameIndex = 0; frameIndex < BonesMatList.Count; frameIndex++)
    {
        List<Matrix4x4> BonesMat = BonesMatList[frameIndex];
        for (int boneIdx = 0; boneIdx < BonesMat.Count; boneIdx++)
        {
            //Debug.LogError(vert.ToString() + ":" + meshFrame[vert]);
            int arrayPos = (frameIndex * BonesMat.Count) + boneIdx;
            Matrix4x4 frameBone = BonesMat[boneIdx];

            scaler[0] = Math.Max(scaler[0], System.Math.Abs(frameBone.m03));
            scaler[1] = Math.Max(scaler[1], System.Math.Abs(frameBone.m13));
            scaler[2] = Math.Max(scaler[2], System.Math.Abs(frameBone.m23));
        }
    }
    ....
    bakeTextures.Add(new Texture2D(textureSize.x, textureSize.y, TextureFormat.RGBAHalf, false, false));
    for (int frameIndex = 0; frameIndex < BonesMatList.Count; frameIndex++)
    {
        for (int boneIdx = 0; boneIdx < BonesMatList[frameIndex].Count; boneIdx++)
        {
            Matrix4x4 data = BonesMatList[frameIndex][boneIdx];
            data.m00 = data.m00 * 0.5f + 0.5f;
            data.m01 = data.m01 * 0.5f + 0.5f;
            data.m02 = data.m02 * 0.5f + 0.5f;
            data.m03 = data.m03 / scaler[0] * 0.5f + 0.5f;
            data.m10 = data.m10 * 0.5f + 0.5f;
            data.m11 = data.m11 * 0.5f + 0.5f;
            data.m12 = data.m12 * 0.5f + 0.5f;
            data.m13 = data.m13 / scaler[1] * 0.5f + 0.5f;
            data.m20 = data.m20 * 0.5f + 0.5f;
            data.m21 = data.m21 * 0.5f + 0.5f;
            data.m22 = data.m22 * 0.5f + 0.5f;
            data.m23 = data.m23 / scaler[2] * 0.5f + 0.5f;
            Color[] colors = new Color[]{
                new Color(data.m00, data.m01, data.m02, data.m03),
                new Color(data.m10, data.m11, data.m12, data.m13),
                new Color(data.m20, data.m21, data.m22, data.m23),
                new Color(data.m30, data.m31, data.m32, data.m33)
            };
            if (yPos == textureSize.y)
            {
                xPos++;
                yPos = 0;
                if (xPos == textureSize.x)
                {
                    xPos = 0;
                    textureIndex++;
                    bakeTextures.Add(new Texture2D(textureSize.x, textureSize.y, TextureFormat.RGBAHalf, false, false));
                }
            }
            bakeTextures[textureIndex].SetPixel(xPos, yPos, colors[0]);
            bakeTextures[textureIndex].SetPixel(xPos, yPos + 1, colors[1]);
            bakeTextures[textureIndex].SetPixel(xPos, yPos + 2, colors[2]);
            bakeTextures[textureIndex].SetPixel(xPos, yPos + 3, colors[3]);
            yPos += 4;
        }
    }
    ....
}
```

![](https://img-blog.csdnimg.cn/39dcb716a7a644bf971b5ede15728d7f.png)

其次在 Unity 的 Mesh 类型中，其中有一个 BoneWeight 数据，记录的是每个点在播放动画时跟随移动的最多四个骨骼以及受其影响的权重，我们可以把这些变量存在模型的 uv2-uv5 中，在 shader 的顶点着色器中读取它们。

```
if(mesh.boneWeights.Length > 0)
{
    List<Vector2> uv1 = new List<Vector2>();
    List<Vector2> uv2 = new List<Vector2>();
    List<Vector2> uv3 = new List<Vector2>();
    List<Vector2> uv4 = new List<Vector2>();
    for(int i = 0; i < mesh.vertexCount; ++i)
    {
        int nowIndex = System.Math.Min(i, mesh.boneWeights.Length);
        BoneWeight bw = mesh.boneWeights[nowIndex];
        uv1.Add(new Vector2(bw.boneIndex0, bw.weight0));
        uv2.Add(new Vector2(bw.boneIndex1, bw.weight1));
        uv3.Add(new Vector2(bw.boneIndex2, bw.weight2));
        uv4.Add(new Vector2(bw.boneIndex3, bw.weight3));
    }
    mesh.SetUVs(1, uv1);
    mesh.SetUVs(2, uv2);
    mesh.SetUVs(3, uv3);
    mesh.SetUVs(4, uv4);
    gameObject.GetComponent<MeshFilter>().sharedMesh = mesh;
}
```

```
struct appdata
{
    float4 vertex : POSITION;
    float2 uv : TEXCOORD0;
    float2 bone1 : TEXCOORD1;
    float2 bone2 : TEXCOORD2;
    float2 bone3 : TEXCOORD3;
    float2 bone4 : TEXCOORD4;
};
```

然后在 shader 中我们处理处理每个顶点对应的骨骼即可，这里我没用 GPUInstancing 了，大家可以自己去实现一下。

```
Shader "Unlit/GpuSkinningBone"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _AnimationTex("Texture", 2DArray) = ""{}                //动画贴图
        _Scale("Scale", Vector) = (1, 1, 1, 0)                  //x, y, z轴的缩放
        _AnimationSize("Animation Size", float) = 0             //动画长度
        _FPS("FPS", int) = 0                                    //FPS
        _BoneNum("Bone Num", Int) = 0                           //骨骼数
        _TextureSize("Texture Size", Vector) = (0, 0, 0, 0)     //动画贴图大小
        [IntRange]_Bone("Bone",Range(1,4)) = 1
        _NowFrame("Now Frame",Range(0,1)) = 0
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
                float2 bone1 : TEXCOORD1;
                float2 bone2 : TEXCOORD2;
                float2 bone3 : TEXCOORD3;
                float2 bone4 : TEXCOORD4;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            UNITY_DECLARE_TEX2DARRAY(_AnimationTex);
            sampler2D _MainTex;
            float4 _MainTex_ST;
            float4 _Scale;
            float _AnimationSize;
            int _FPS;
            int _BoneNum;
            float4 _TextureSize;
            float _Bone;
            float _NowFrame;

            //采样骨骼对应贴图
            float4x4 getTransMat(int boneIndex)
            {
                int nowFrame = floor(_FPS * _AnimationSize * _NowFrame);
                int nowBone = nowFrame * _BoneNum + boneIndex;
                int nowBoneIndex = nowBone * 4;
                int nowBoneColumn0 = nowBoneIndex % _TextureSize.y;
                int nowBoneRow0 = floor(nowBoneIndex / _TextureSize.y);
                float u = nowBoneRow0 * 1.0f / _TextureSize.x;
                int nowBoneColumn1 = nowBoneColumn0 + 1;
                int nowBoneColumn2 = nowBoneColumn1 + 1;
                int nowBoneColumn3 = nowBoneColumn2 + 1;
                float4 row0 = UNITY_SAMPLE_TEX2DARRAY_LOD(_AnimationTex, float3(u, nowBoneColumn0 * 1.0f / _TextureSize.y, 0), 0);
                row0.xyz = row0.xyz * 2.0f - 1.0f;
                row0.w = (row0.w* 2.0f - 1.0f) * _Scale.x ;
                float4 row1 = UNITY_SAMPLE_TEX2DARRAY_LOD(_AnimationTex, float3(u, nowBoneColumn1 * 1.0f / _TextureSize.y, 0), 0);
                row1.xyz = row1.xyz * 2.0f - 1.0f;
                row1.w = (row1.w * 2.0f - 1.0f) * _Scale.y;
                float4 row2 = UNITY_SAMPLE_TEX2DARRAY_LOD(_AnimationTex, float3(u, nowBoneColumn2 * 1.0f / _TextureSize.y, 0), 0);
                row2.xyz = row2.xyz * 2.0f - 1.0f;
                row2.w = (row2.w * 2.0f - 1.0f) * _Scale.z;
                float4 row3 = UNITY_SAMPLE_TEX2DARRAY_LOD(_AnimationTex, float3(u, nowBoneColumn3 * 1.0f / _TextureSize.y, 0), 0);
                return float4x4(row0, row1, row2, row3);
                //return tex2Dlod(_AnimationTex, float4(nowBoneRow0 * 1.0f / _TextureSize.x, nowBoneColumn0 * 1.0f / _TextureSize.y, 0, 0));
            }

            v2f vert (appdata v)
            {
                v2f o;
                //采样四根骨骼后加权平均
                o.vertex = UnityObjectToClipPos(
                    mul(getTransMat(v.bone1.x), v.vertex) * v.bone1.y + 
                    mul(getTransMat(v.bone2.x), v.vertex) * v.bone2.y + 
                    mul(getTransMat(v.bone3.x), v.vertex) * v.bone3.y + 
                    mul(getTransMat(v.bone4.x), v.vertex) * v.bone4.y 
                );
                //o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag(v2f i) : SV_Target
            {
                // sample the texture
                fixed4 col = tex2D(_MainTex, i.uv);
                return col;
            }
            ENDCG
        }
    }
}
```

这种方法相比于记录顶点位置的方法，优点是在确保 GPUInstancing 的同时保存的动画贴图更小，但是要计算的消耗更多，在顶点着色器中最少需要 3 次采样，极端情况要 16 次贴图采样。