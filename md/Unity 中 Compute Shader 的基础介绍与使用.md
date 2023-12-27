> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [weibo.com](https://weibo.com/ttarticle/p/show?id=2309404693710318469869)

> ​​前言

​​前言

​

Compute Shader 是如今比较流行的一种技术，例如之前的《天刀手游》，还有最近大火的《永劫无间》，在分享技术的时候都有提到它。

Unity 官方对 Compute Shader 的介绍如下：[https://docs.unity3d.com/Manual/class-ComputeShader.html](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.unity3d.com%2FManual%2Fclass-ComputeShader.html)

Compute Shader 和其他 Shader 一样是运行在 GPU 上的，但是它是**独立于渲染管线之外**的。我们可以利用它实现**大量且并行**的 GPGPU 算法，用来加速我们的游戏。

在 Unity 中，我们在 Project 中右键，即可创建出一个 Compute Shader 文件：  

![](https://wx4.sinaimg.cn/large/006fToqzly4gvj8yu8qqnj60ls05ojrm02.jpg)

生成的文件属于一种 Asset 文件，并且都是以 **.compute** 作为文件后缀的。

我们来看下里面的默认内容：

![](https://wx3.sinaimg.cn/large/006fToqzly1gvj909yzj8j610s0acabd02.jpg)

本文的主要目的就是让和我一样的萌新能够看懂这区区几行代码的含义，学好了基础才能够看更牛的代码。  

​

语言
--

​

Unity 使用的是 DirectX 11 的 HLSL 语言，会被自动编译到所对应的平台。

​

kernel
------

​

然后我们来看看第一行：

![](https://wx4.sinaimg.cn/large/006fToqzly1gvj90tdtinj610u02a3yj02.jpg)

CSMain 其实就是一个函数，在代码后面可以看到，而 kernel 是内核的意思，这一行即把一个名为 CSMain 的函数声明为内核，或者称之为核函数。这个核函数就是最终会在 GPU 中被执行。  

一个 Compute Shader 中**至少要有一个 kernel 才能够被唤起**。声明方法即为：  
#pragma kernel functionName

我们也可用它在一个 Compute Shader 里声明多个内核，此外我们还可以再该指令后面定义一些预处理的宏命令，如下：  
#pragma kernel KernelOne SOME_DEFINE DEFINE_WITH_VALUE=1337  
#pragma kernel KernelTwo OTHER_DEFINE

我们不能把注释写在该命令后面，而应该换行写注释，例如下面写法会造成编译的报错：  
#pragma kernel functionName // 一些注释

​

RWTexture2D
-----------

​

接着我们再来看看第二行：

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj91r1pjmj610o028dfx02.jpg)

看着像是声明了一个和纹理有关的变量，具体来看一下这些关键字的含义。  

RWTexture2D 中，RW 其实是 **Read** 和 **Write** 的意思，Texture2D 就是二维纹理，因此它的意思就是**一个可以被 Compute Shader 读写的二维纹理**。

如果我们只想读不想写，那么可以使用 Texture2D 的类型。

我们知道纹理是由一个个像素组成的，每个像素都有它的下标，因此我们就可以通过像素的下标来访问它们，例如：Result[uint2(0,0)]。

同样的每个像素会有它的一个对应值，也就是我们要读取或者要写入的值。这个值的类型就被写在了 <> 当中，通常对应的是一个 RGBA 的值，因此是 float4 类型。通常情况下，我们会在 Compute Shader 中处理好纹理，然后在 FragmentShader 中来对处理后的纹理进行采样。

这样我们就大致理解这行代码的意思了，声明了一个名为 Result 的可读写二维纹理，其中每个像素的值为 float4。

在 Compute Shader 中可读写的类型除了 **RWTexture** 以外还有 **RWBuffer** 和 **RWStructuredBuffer**，后面会介绍。

[RWTexture2D - Win32 apps](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fdirect3dhlsl%2Fsm5-object-rwtexture2d)

​

numthreads
----------

​

然后是下面一句（很重要！）：

![](https://wx2.sinaimg.cn/large/006fToqzgy1gvj92pkacnj610o028jre02.jpg)

又是 num，又是 thread 的，肯定和线程数量有关。没错，它就是定义**一个线程组（Thread Group）中可以被执行的线程（Thread）总数量**，格式如下：  

numthreads(tX, tY, tZ)  
注：X，Y，Z 前加个 t 方便和后续 Group 的 X，Y，Z 进行区分

其中 tXtYtZ 的值即线程的总数量，例如 numthreads(4, 4, 1) 和 numthreads(16, 1, 1) 都代表着有 16 个线程。那么为什么不直接使用 numthreads(num) 这种形式定义，而非要分成 tX、tY、tZ 这种三维的形式呢？看到后面自然就懂其中的奥秘了。

**每个核函数前面我们都需要定义 numthreads**，否则编译会报错。  

其中 tX，tY，tZ 三个值也并不是可以随便乱填的，比如来一刀 tX=99999 暴击一下，这是不行的。它们在不同的版本里有如下的约束：  

![](https://wx1.sinaimg.cn/large/006fToqzly4gvj8yu8s8ij612o05k74z02.jpg)

在 Direct11 中，可以通过 **ID3D11DeviceContext::Dispatch(gX,gY,gZ)** 方法创建 gXgYgZ 个线程组，一个线程组里又会包含多个线程（数量即 numthreads 定义）。

注意顺序，**先 numthreads 定义好每个核函数对应线程组里线程的数量（tXtYtZ），再用 Dispatch 定义用多少线程组（gXgYgZ）来处理这个核函数**。其中每个线程组内的线程都是并行的，不同线程组的线程可能同时执行，也可能不同时执行。一般一个 GPU 同时执行的线程数，在 1000-10000 之间。

接着我们用一张示意图来看看线程与线程组的结构，如下图：  

![](https://wx3.sinaimg.cn/large/006fToqzly4gvj8yu9r8bj60ii0h3ta202.jpg)

上半部分代表的是线程组结构，下半部分代表的是单个线程组里的线程结构。因为他们都是由（X,Y,Z）来定义数量的，因此就像一个三维数组，下标都是从 0 开始。我们可以把它们看做是表格一样：**有 Z 个一样的表格，每个表格有 X 列和 Y 行**。例如线程组中的（2,1,0），就是第 1 个表格的第 2 行第 3 列对应的线程组，下半部分的线程也是同理。

搞清楚结构，我们就可以很好的理解下面这些与单个线程有关的参数含义：  

![](https://wx4.sinaimg.cn/large/006fToqzly4gvj8yubddsj610o0u0aem02.jpg)

这里需要注意的是，不管是 Group 还是 Thread，它们的**顺序都是先 X 再 Y 最后 Z**，用表格的理解就是先行（X）再列（Y）然后下一个表（Z），例如我们 tX=5，tY=6 那么第 1 个 thread 的 SV_GroupThreadID=(0,0,0)，第 2 个的 SV_GroupThreadID=(1,0,0)，第 6 个的 SV_GroupThreadID=(0,1,0)，第 30 个的 SV_GroupThreadID=(4,5,0)，第 31 个的 SV_GroupThreadID=(0,0,1)。Group 同理，搞清顺序后，SV_GroupIndex 的计算公式就很好理解了。

再举个例子，比如 SV_GroupID 为（0,0,0）和（1,0,0）的两个 Group，它们内部的第 1 个 Thread 的 SV_GroupThreadID 都为（0,0,0）且 SV_GroupIndex 都为 0，但是前者的 SV_DispatchThreadID=(0,0,0) 而后者的 SV_DispatchThreadID=(tX,0,0)。

好好理解下，它们在核函数里非常的重要。  
[numthreads - Win32 apps](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fdirect3dhlsl%2Fsm5-attributes-numthreads)

​

核函数
---

​

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj93wxlqtj610w05adgl02.jpg)

最后就是我们声明的核函数了，其中参数 SV_DispatchThreadID 的含义上面已经介绍过了，除了这个参数以外，我们前面提到的几个参数都可以被传入到核函数当中，根据实际需求做取舍即可，完整如下：  

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj94fextij610y08g3zo02.jpg)

而函数内执行的代码就是为我们 Texture 中下标为 id.xy 的像素赋值一个颜色，这里也就是最牛的地方。  

举个例子，以往我们想要给一个 x*y 分辨率的 Texture 每个像素进行赋值，单线程的情况下，我们的代码往往如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj95h88u5j610w04eaak02.jpg)

两个循环，像素一个个的慢慢赋值。那么如果我们要每帧给很多张 2048*2048 的图片进行操作，可想而知会卡死。  

如果使用多线程，为了避免不同的线程对同一个像素进行操作，我们往往使用分段操作的方法，如下，四个线程进行处理：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj965hfufj610s0scdj402.jpg)

这么写不是很蠢么，如果有更多的线程，分成更多段，不就一堆重复的代码。但是如果我们能知道每个线程的开始和结束下标，不就可以把这些代码统一起来了么，如下：  

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj96ex7x8j610u07ewfb02.jpg)

那我要是可以开出很多很多的线程是不是就可以一个线程处理一个像素了？  

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj96sczrxj610w05eq3c02.jpg)

用 CPU 我们做不到这样，但是用 GPU，用 Compute Shader 我们就可以。实际上，前面默认的 Compute Shader 的代码里，核函数的内容就是这样的。  

接下来我们来看看 Compute Shader 的妙处，看 **id.xy** 的值。id 的类型为 SV_DispatchThreadID，我们先来回忆下 SV_DispatchThreadID 的计算公式：  
假设该线程的 SV_GroupID=(a, b, c)，SV_GroupThreadID=(i, j, k) 那么 SV_DispatchThreadID=(atX+i, btY+j, c*tZ+k)

首先前面我们使用了 [numthreads(8,8,1)]，即 tX=8，tY=8，tZ=1，且 i 和 j 的取值范围为 0 到 7，而 k=0。那么我们线程组（0,0,0）中所有线程的 SV_DispatchThreadID.xy 也就是 id.xy 的取值范围即为（0,0）到（7,7），线程组（1,0,0）中它的取值范围为（8,0）到（15, 7），...，线程（0,1,0）中它的取值范围为（0,8）到（7,15），...，线程组（a,b,0）中它的取值范围为（a8, b8, 0）到（a8+7,b8+7,0）。

我们用示意图来看下，假设下图每个网格里包含了 64 个像素：  

![](https://wx2.sinaimg.cn/large/006fToqzly4gvj8yuazqij60i70h311k02.jpg)

也就是说我们每个线程组会有 64 个线程同步处理 64 个像素，并且不同的线程组里的线程不会重复处理同一个像素，若要处理分辨率为 1024*1024 的图，我们只需要 dispatch(1024/8, 1024/8, 1) 个线程组。

这样就实现了成百上千个线程同时处理一个像素了，若用 CPU 的方式这是不可能的。是不是很妙？

而且我们可以发现 numthreads 中设置的值是很值得推敲的，例如我们有 4*4 的矩阵要处理，设置 numthreads(4,4,1)，那么每个线程的 SV_GroupThreadID.xy 的值不正好可以和矩阵中每项的下标对应上么。

我们在 Unity 中怎么调用核函数，又怎么 dispatch 线程组以及使用的 RWTexture 又怎么来呢？这里就要回到我们 C# 的部分了。

​

C# 部分
-----

​

以往的 vertex&fragment shader，我们都是给它关联到 Material 上来使用的，但是 Compute Shader 不一样，它是由 **C#**来驱动的。

先新建一个 monobehaviour 脚本，Unity 为我们提供了一个 **Compute Shader** 的类型用来引用我们前面生成的 .compute 文件：

![](https://wx2.sinaimg.cn/large/006fToqzgy1gvj97thh3uj610s02caa902.jpg)

![](https://wx3.sinaimg.cn/large/006fToqzly4gvj8yu9432j609l00v74602.jpg)在 Inspector 界面关联. compute 文件

此外我们再关联一个 Material，因为 Compute Shader 处理后的纹理，依旧要经过 Fragment Shader 采样后来显示。  

public Material material;  

这个 Material 我们使用一个 Unlit Shader，并且纹理不用设置，如下：  

![](https://wx1.sinaimg.cn/large/006fToqzly4gvj8yu8h2aj609j06et8w02.jpg)

然后关联到我们的脚本上，并且随便建个 Cube 也关联上这 Material。

接着我们可以将 Unity 中的 **RenderTexture** 赋值到 Compute Shader 中的 RWTexture2D 上，但是需要注意因为我们是多线程处理像素，并且这个处理过程是无序的，因此我们要将 RenderTexture 的 **enableRandomWrite** 属性设置为 true，代码如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj98o5gdqj610w04cwfc02.jpg)

我们创建了一个分辨率为 256*256 的 RenderTexture，首先我们要把它赋值给我们的 Material，这样我们的 Cube 就会显示出它。然后要把它赋值给我们 Compute Shader 中的 Result 变量，代码如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj99f5adhj610u03edgf02.jpg)

这里有一个 kernelIndex 变量，即核函数下标，我们可以利用 FindKernel 来找到我们声明的核函数的下标：  

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj99w33bcj610u02c0t102.jpg)

这样在我们 FragmentShader 采样的时候，采样的就是 Compute Shader 处理过后的纹理：  

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9ab49ofj610u07eaav02.jpg)

最后就是开线程组和调用我们的核函数了，在 Compute Shader 中，Dispatch 方法为我们一步到位：  

![](https://wx4.sinaimg.cn/large/006fToqzly1gvj9bfwz6cj610s02edg502.jpg)

为什么是 256/8，前面已经解释过了。来看看效果：  

![](https://wx1.sinaimg.cn/large/006fToqzly4gvj8yu94z5j60a008ojsf02.jpg)

上图就是我们 Unity 默认生成的 Compute Shader 代码所能带来的效果，我们也可试下用它处理 2048*2048 的 Texture，也是非常快的。

接下来我们再来看看粒子效果的例子：

首先一个粒子通常拥有颜色和位置两个属性，并且我们肯定是要在 Compute Shader 里去处理这两个属性的，那么我们就可以在 Compute Shader 创建一个 struct 来存储：

![](https://wx1.sinaimg.cn/large/006fToqzly1gvj9c2h1ldj610y05eaac02.jpg)

接着，这个粒子肯定是很多很多的，我们就需要一个像 List 一样的东西来存储它们，在 ComputeShader 中为我们提供了 RWStructuredBuffer 类型。  

​

RWStructuredBuffer
------------------

​

它是一个可读写的 Buffer，并且我们可以指定 Buffer 中的数据类型为我们自定义的 struct 类型，不用再局限于 int、float 这类的基本类型。

因此我们可以这么定义我们的粒子数据：

![](https://wx2.sinaimg.cn/large/006fToqzly1gvj9cp2qabj610y02ejro02.jpg)

[RWStructuredBuffer - Win32 apps](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fdirect3dhlsl%2Fsm5-object-rwstructuredbuffer)  

为了有动效，我们可以再添加一个时间相关值，我们可以根据时间来修改粒子的位置和颜色：

![](https://wx1.sinaimg.cn/large/006fToqzly1gvj9d59g3fj610w02eaa202.jpg)

接着就是怎么在核函数里修改我们的粒子信息了，要修改某个粒子，我们肯定要知道粒子在 Buffer 中的下标，并且这个下标在不同的线程中不能重复，否则就可能导致多个线程修改同一个粒子了。  

根据前面的介绍，我们知道一个线程组中 SV_GroupIndex 是唯一的，但是在不同线程组中并不是。例如每个线程组内有 1000 个线程，那么 SV_GroupID 都是 0 到 999。我们可以根据 SV_GroupID 把它叠加上去，例如 SV_GroupID=(0,0,0) 是 0-999，SV_GroupID=(1,0,0) 是 1000-1999 等等，为了方便我们的线程组都可以是（X,1,1）格式。然后我们就可以根据 Time 和 Index 随便的摆布下粒子，Compute Shader 完整代码：

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj9dnfy60j610y0peadm02.jpg)

接下来我们要在 C# 里给粒子初始化并且传递给 Compute Shader。我们要传递粒子数据，也就是说要给前面的 RWStructuredBuffer 赋值，Unity 为我们提供了 **ComputeBuffer 类来与 RWStructuredBuffer 或 StructuredBuffer 相对应。**  

​

ComputeBuffer
-------------

​

在 Compute Shader 中经常需要将我们一些自定义的 Struct 数据读写到内存缓冲区，ComputeBuffer 就是为这种情况而生的。我们可以在 C# 里创建并填充它，然后传递到 Compute Shader 或者其他 Shader 中使用。

通常我们用下面方法来创建它：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9e83m5kj610y02iaad02.jpg)

其中 count 代表我们 buffer 中元素的数量，而 stride 指的是每个元素占用的空间（字节），例如我们传递 10 个 float 的类型，那么 count=10，stride=4。需要注意的是 **ComputeBuffer 中的 stride 大小必须和 RWStructuredBuffer 中每个元素的大小一致**。  

声明完成后我们可以使用 SetData 方法来填充，参数为自定义的 struct 数组：

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj9emjj58j610s02e0ss02.jpg)

最后我们可以使用 Compute Shader 类中的 SetBuffer 方法来把它传递到 Compute Shader 中：  

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj9f0trk6j610w02gt9302.jpg)

记得用完后把它 Release() 掉。  

[https://docs.unity3d.com/ScriptReference/ComputeBuffer.html](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.unity3d.com%2FScriptReference%2FComputeBuffer.html)

在 C# 中我们定义一个一样的 struct，这样才能保证和 Compute Shader 中的大小一致：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9fh484kj610s06e0td02.jpg)

然后我们在 Start 方法中声明我们的 ComputeBuffer，并且找到我们的核函数：  

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj9fvvxvkj610s09e40c02.jpg)

由于我们想要我们的粒子是运动的，即每帧要修改粒子的信息。因此我们在 Update 方法里去传递 Buffer 和 Dispatch：  

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj9gb9htqj610y07k3zs02.jpg)

到这里我们的粒子位置和颜色的操作都已经完成了，但是这些数据并不能在 Unity 里显示出粒子，我们还需要 Vertex&FragmentShader 的帮忙，我们新建一个 UnlitShader，修改下里面的代码如下：  

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj9gz88a2j60tm1100vu02.jpg)

前面我们说了 ComputeBuffer 也可以传递到普通的 Shader 中，因此我们在 Shader 中也创建一个结构一样的 Struct，然后利用 StructuredBuffer 来接收。  

**SV_VertexID：**在 VertexShader 中用它来作为传递进来的参数，代表顶点的下标。我们有多少个粒子即有多少个顶点。顶点数据使用我们在 Compute Shader 中处理过的 Buffer。

最后我们在 C# 中关联一个带有上面 Shader 的 Material，然后将粒子数据传递过去，最终绘制出来。完整代码如下：

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj9ht0xmmj60to0zi0xw02.jpg)

**material.SetBuffer：**传递 ComputeBuffer 到我们的 Shader 当中。  

**OnRenderObject：**该方法里我们可以自定义绘制几何。

**DrawProceduralNow：**我们可以用该方法绘制几何，第一个参数是拓扑结构，第二个参数数顶点数。

[https://docs.unity3d.com/ScriptReference/Graphics.DrawProceduralNow.html](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.unity3d.com%2FScriptReference%2FGraphics.DrawProceduralNow.html)

最终得到的效果如下：  

![](https://wx3.sinaimg.cn/large/006fToqzly4gvj8yuez9ag60nq0bwu0y02.gif)

Demo 链接如下：  
[https://github.com/luckyWjr/ComputeShaderDemo/tree/master/Assets/Particle](https://weibo.cn/sinaurl?u=https%3A%2F%2Fgithub.com%2FluckyWjr%2FComputeShaderDemo%2Ftree%2Fmaster%2FAssets%2FParticle)

​

ComputeBufferType
-----------------

​

在例子中，我们 new 一个 ComputeBuffer 的时候并没有使用到 [ComputeBufferType](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.unity3d.com%2FScriptReference%2FComputeBufferType.html) 的参数，默认使用了 ComputeBufferType.Default。实际上我们的 ComputeBuffer 可以有多种不同的类型对应 [HLSL 中不同的 Buffer](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fdirect3d11%2Fdirect3d-11-advanced-stages-cs-resources)，来在不同的场景下使用，一共有如下几种类型：  

![](https://wx3.sinaimg.cn/large/006fToqzly4gvj8yubp40j60u010pqb102.jpg)

举个例子，在做 GPU 剔除的时候经常会使用到 Append 的 Buffer（例如后面介绍的用 Compute Shader 实现视椎剔除），C# 中的声明如下：

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj9invz24j610w02gwew02.jpg)

注：Default，Append，Counter，Structured 对应的 Buffer 每个元素的大小，也就是 stride 的值应该是 4 的倍数且小于 2048。  

上述 ComputeBuffer 可以对应 Compute Shader 中的 AppendStructuredBuffer，然后我们可以在 Compute Shader 里使用 Append 方法为 Buffer 添加元素，例如：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9j772poj610y09g75f02.jpg)

那么我们的 Buffer 中到底有多少个元素呢？计数器可以帮助我们得到这个结果。  

在 C# 中，我们可以先使用 ComputeBuffer.SetCounterValue 方法来初始化计数器的值，例如：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9jpb6fnj610w02ct8w02.jpg)

随着 AppendStructuredBuffer.Append 方法，我们计数器的值会自动的 ++。当 Compute Shader 处理完成后，我们可以使用 ComputeBuffer.CopyCount 方法来获取计数器的值，如下：  

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9k1vo1sj610u03gjrw02.jpg)

Append、Consume 或者 Counter 的 Buffer 会维护一个计数器来存储 Buffer 中的元素数量，该方法可以把 src 中的计数器的值拷贝到 dst 中，dstOffsetBytes 为在 dst 中的偏移。在 DX11 平台 dst 的类型必须为 Raw 或者 IndirectArguments，而在其他平台可以是任意类型。  

因此获取 buffer 中元素数量的代码如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9ki2fukj610y07gdhk02.jpg)

从上面两个最基础的例子中，我们可以看出，Compute Shader 中的数据都是由 C# 传递过来的，也就是说**数据要从 CPU 传递到 GPU**。并且在 Compute Shader 处理结束后**又要从 GPU 传回 CPU**。这样可能会有点延迟，而且它们之间的传输速率也是一个瓶颈。

但是如果我们有大量的计算需求，不要犹豫，请使用 Compute Shader，对性能能有很大的提升。

​

UAV（Unordered Access view）
--------------------------

​

Unordered 是无序的意思，Access 即访问，view 代表的是 “data in the required format”，应该可以理解为数据所需要的格式吧。

什么意思呢？我们的 Compute Shader 是多线程并行的，因此我们的数据必然需要能够支持被无序的访问。例如，如果纹理只能被（0,0），（1,0），（2,0），...，Buffer 只能被［0］，［1］，［2］，... 这样有序访问，那么想要用多线程来修改它们明显不行，因此提出了一个概念，即 **UAV，可无序访问的数据格式**。

前面我们提到了 RWTexture，RWStructuredBuffer 这些类型都属于 UAV 的数据类型，并且它们**支持在读取的同时写**入。它们只能在 FragmentShader 和 ComputeShader 中被使用（绑定）。

如果我们的 RenderTexture 不设置 enableRandomWrite，或者我们传递一个 Texture 给 RWTexture，那么运行时就会报错：

the texture wasn't created with the UAV usage flag set!

不能被读写的数据类型，例如 Texure2D，我们称之为 **SRV（Shader Resource View）**。

[Direct3D 12 术语表 - Win32 apps](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.microsoft.com%2Fzh-cn%2Fwindows%2Fwin32%2Fdirect3d12%2Fdirectx-12-glossary)

​

Wrap / WaveFront
----------------

​

前面我们说了使用 numthreads 可以定义每个线程组内线程的数量，那么我们使用 numthreads(1,1,1) 真的每个线程组只有一个线程嘛？NO！

这个问题要从硬件说起，我们 GPU 的模式是 **SIMT**（single-instruction multiple-thread，单指令多线程）。在 NVIDIA 的显卡中，一个 **SM（Streaming Multiprocessor）**可调度多个 wrap，而每个 wrap 里会有 32 个线程。我们可以简单的理解为一个指令最少也会调度 32 个并行的线程。而在 AMD 的显卡中这个数量为 64，称之为 Wavefront。

也就是说如果是 NVIDIA 的显卡，如果我们使用 numthreads(1,1,1)，那么线程组依旧会有 32 个线程，但是多出来的 31 个线程完全就处于没有使用的状态，造成浪费。因此我们在使用 numthreads 时，最好将线程组的数量定义为 64 的倍数，这样两种显卡都可以顾及到。

[https://www.cvg.ethz.ch/teaching/2011spring/gpgpu/GPU-Optimization.pdf](https://weibo.cn/sinaurl?u=https%3A%2F%2Fwww.cvg.ethz.ch%2Fteaching%2F2011spring%2Fgpgpu%2FGPU-Optimization.pdf)

​

移动端支持问题
-------

​

我们可以运行时调用 **SystemInfo.supportsComputeShaders** 来判断当前的机型是否支持 Compute Shader。其中 OpenGL ES 从 3.1 版本才开始支持 Compute Shader，而使用 Vulkan 的 Android 平台以及使用 Metal 的 IOS 平台都支持 Compute Shader。

然而有些 Android 手机即使支持 Compute Shader，但是对 RWStructuredBuffer 的支持并不友好。例如在某些 OpenGL ES 3.1 的手机上，只支持 Fragment Shader 内访问 StructuredBuffer。

在普通的 Shader 中要支持 Compute Shader，Shader Model 最低要求为 4.5，即：

![](https://wx3.sinaimg.cn/large/006fToqzgy1gvj9louekej610w02gt8q02.jpg)

**利用 Compute Shader 实现视椎剔除**  
[《Unity 中使用 Compute Shader 做视锥剔除（View Frustum Culling）》](https://weibo.cn/sinaurl?u=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F376801370)

**利用 Compute Shader 实现 Hi-z 遮挡剔除**  
[《Unity 中使用 Compute Shader 实现 Hi-z 遮挡剔除（Occlusion Culling）》](https://weibo.cn/sinaurl?u=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F396979267)

​

Shader.PropertyToID
-------------------

​

在 Compute Shader 中定义的变量依旧可以通过 Shader.PropertyToID("name") 的方式来获得唯一 id。这样当我们要频繁利用 ComputeShader.SetBuffer 对一些相同变量进行赋值的时候，就可以把这些 id 事先缓存起来，避免造成 GC。

![](https://wx4.sinaimg.cn/large/006fToqzgy1gvj9m5r9tuj61120bmjtc02.jpg)

​

全局变量或常量？
--------

​

假如我们要实现一个需求，在 Compute Shader 中判断某个顶点是否在一个固定大小的包围盒内，那么按照以往 C# 的写法，我们可能如下定义包围盒大小：

![](https://wx2.sinaimg.cn/large/006fToqzgy1gvj9mn2u3tj610w0cgabx02.jpg)

经过测试，其中方法 1 和方法 2 的定义，在 CSMain 里读取到的值都为 float3(0.0f,0.0f,0.0f) ，只有方法 3 才是最开始定义的值。  

​

Shader variants and keywords
----------------------------

​

ComputeShader 同样支持 [Shader 变体](https://weibo.cn/sinaurl?u=https%3A%2F%2Fdocs.unity3d.com%2F2020.3%2FDocumentation%2FManual%2FSL-MultipleProgramVariants.html)，用法和普通的 Shader 变体基本相似，示例如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9n35612j610y0hgju302.jpg)

然后我们就可以在 C# 端启用或禁用某个变体了：

*   #pragma multi_compile 声明的全局变体可以使用 Shader.EnableKeyword/Shader.DisableKeyword 或者 ComputeShader.EnableKeyword/ComputeShader.DisableKeyword
*   #pragma multi_compile_local 声明的局部变体可以使用 ComputeShader.EnableKeyword/ComputeShader.DisableKeyword

示例如下：

![](https://wx1.sinaimg.cn/large/006fToqzgy1gvj9nmv54bj610w0agwfi02.jpg)

这是侑虎科技第 1027 篇文章，感谢作者王江荣供稿。欢迎转发分享，未经作者授权请勿转载。如果您有任何独到的见解或者发现也欢迎联系我们，一起探讨。（QQ 群：793972859）

作者主页：[https://www.zhihu.com/people/luckywjr](https://weibo.cn/sinaurl?u=https%3A%2F%2Fwww.zhihu.com%2Fpeople%2Fluckywjr)，再次感谢王江荣的分享，如果您有任何独到的见解或者发现也欢迎联系我们，一起探讨。（QQ 群：793972859）

  
​​​​