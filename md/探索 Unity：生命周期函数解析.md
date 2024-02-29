> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247483949&idx=1&sn=c6e403effe6ed01f860e27cc6fed4ab8&chksm=ce072322f970aa34bab2f5b7f5793be98a28450b200c9335a600061dfd21d366bf145d50daff&scene=178&cur_album_id=3218021275236007937#rd)

Unity 生命周期函数是在游戏对象的不同阶段被调用的方法，通过这些函数，我们可以在不同的时刻执行特定的代码。在这篇文章中，我们将一步步解析 Unity 生命周期函数，分为不同阶段来理解它们的作用。

[事件函数的执行顺序 - Unity 手册 (unity3d.com)](https://docs.unity3d.com/cn/2022.3/Manual/ExecutionOrder.html#ScriptLifecycleFlowchart)

#### **1. 初始化阶段 Initialization** 

##### **- Awake（唤醒）**

始终在任何 Start 函数之前并在实例化预制件之后调用此函数。（如果游戏对象在启动期间处于非活动状态，则在激活之后才会调用 Awake。）

##### **- OnEnable（当可用）**

（仅在对象处于激活状态时调用）在启用对象后立即调用此函数。在创建 MonoBehaviour 实例时（例如加载关卡或实例化具有脚本组件的游戏对象时）会执行此调用。

##### **- Reset（重置）（Editor）**

调用 Reset 可以在脚本首次附加到对象时以及使用 *Reset* 命令时初始化脚本的属性。

##### **- Start（开始）**

在对象的第一帧更新前调用，常用于初始化游戏对象之间的引用关系等操作。

仅当启用脚本实例后，才会在第一次帧更新之前调用 Start。

#### **2. 物理阶段Physics** 

##### **- FixedUpdate（固定更新）**

在固定的物理时间间隔内调用，适合处理物理相关的逻辑，如移动、碰撞检测等。调用 **FixedUpdate** 的频度常常超过 **Update**。如果帧率很低，可以每帧调用该函数多次；如果帧率很高，可能在帧之间完全不调用该函数。在 **FixedUpdate** 之后将立即进行所有物理计算和更新。在 **FixedUpdate** 内应用运动计算时，无需将值乘以 **Time.deltaTime**。这是因为 **FixedUpdate** 的调用基于可靠的计时器（独立于帧率）。

##### **- OnTriggerXXX（触发）**

处理触发器事件，例如 OnTriggerEnter、OnTriggerStay、OnTriggerExit 等。

##### **- OnCollisionXXX（碰撞）**

处理碰撞事件，例如 OnCollisionEnter、OnCollisionStay、OnCollisionExit 等。

##### **- yield WaitForFixedUpdate（协程：物理帧结束）**

在协程中使用，等待物理帧结束后继续执行。

#### **3. 输入事件阶段 Input events**

##### **- OnMouseXXX（输入）**

处理用户输入事件，例如鼠标点击、键盘输入等。

#### **4. 游戏逻辑阶段 Game logic**

##### **- Update（更新）**

在每一帧更新时调用，用于处理游戏逻辑。每帧调用一次 **Update**。这是用于帧更新的主要函数。

###### **- 判断多个协程点**

在 Update 中可以判断多个协程的执行点，进行逻辑控制:yield null, yield WaitForSeconds, yield WWW, yield StartCoroutine

###### **- 内部动画更新 Internal animation update**

在 Update 中更新内部动画。

#### **- LateUpdate（延后更新）**

在 Update 之后调用，适合处理与 Update 相关的逻辑。每帧调用一次 **LateUpdate__（在** Update__ 完成后）。**LateUpdate** 开始时，在 **Update** 中执行的所有计算便已完成。**LateUpdate** 的常见用途是跟随第三人称摄像机。如果在 **Update** 内让角色移动和转向，可以在 **LateUpdate** 中执行所有摄像机移动和旋转计算。这样可以确保角色在摄像机跟踪其位置之前已完全移动。

#### **5. 渲染阶段**

渲染阶段包括多个生命周期函数，用于处理与渲染相关的逻辑，例如特效、相机视觉效果等。以下是这些函数的解释：

##### **- OnPreCull**

在摄像机剔除场景之前调用。剔除操作将确定摄像机可以看到哪些对象。正好在进行剔除之前调用 OnPreCull。

**OnPreCull** 在剔除阶段（culling）之前调用，用于在相机剔除不可见物体之前执行逻辑。在这里进行的操作将在剔除阶段考虑，可以用于自定义剔除逻辑或计算视觉效果。

##### **- OnWillRenderObject**

如果对象可见，则为每个摄像机调用**一次**。

**OnWillRenderObject** 在相机渲染之前调用，用于确定是否渲染当前对象。通常在自定义渲染脚本中使用，允许我们在渲染之前执行特定的逻辑，如动态调整材质或更新纹理。

##### **- OnBecameVisible（即将可见）**

对象变为对任何摄像机可见时调用。

**OnBecameVisible** 当对象在相机视野中变得可见时调用。可以用于激活或处理一些与可见性相关的逻辑，例如开始播放特效或启用特殊效果。

##### **- OnBecameInvisible（即将不可见）**

对象变为对任何摄像机不可见时调用。

**OnBecameInvisible** 当对象在相机视野中变得不可见时调用。适用于处理不可见时的逻辑，如停止播放特效或禁用一些效果以提高性能。

##### **- OnPreRender（即将渲染）**

在摄像机开始渲染场景之前调用。

**OnPreRender** 在相机渲染之前调用，用于在渲染之前执行特定逻辑。在这里进行的操作将影响相机渲染的结果，可以用于修改材质、设置全局效果等。

##### **- OnRenderObject**

所有常规场景渲染完成之后调用。此时，可以使用 [GL](https://docs.unity3d.com/cn/2022.3/ScriptReference/GL.html) 类或 [Graphics.DrawMeshNow](https://docs.unity3d.com/cn/2022.3/ScriptReference/Graphics.DrawMeshNow.html) 来绘制自定义几何形状。

**OnRenderObject** 在相机渲染物体时调用，通常用于自定义渲染逻辑。在这里可以执行一些与对象渲染相关的操作，例如绘制辅助几何或实现特殊的渲染效果。

##### **- OnPostRender**

在摄像机完成场景渲染后调用。

**OnPostRender** 在相机完成渲染后调用，用于在渲染之后执行逻辑。适用于处理与整体渲染结果相关的操作，如后期处理效果。

##### **- OnRenderImage**

在场景渲染完成后调用以允许对图像进行后处理，请参阅[后期处理效果](https://docs.unity3d.com/cn/2022.3/Manual/PostProcessingOverview.html)。

**OnRenderImage** 在相机完成渲染后，但在渲染结果被绘制到屏幕之前调用。允许对渲染结果进行后期处理，生成最终的图像效果。

##### **- OnDrawGizmos（Gizmos 渲染）**

用于在场景视图中绘制辅助图标以实现可视化。

**OnDrawGizmos** 用于在 Scene 视图中渲染场景的 Gizmos。适用于在编辑器中可视化调试信息，通常用于显示场景中的边界、路径、碰撞体等信息。

#### **- GUI 渲染**

处理 GUI 渲染的逻辑。

##### OnGUI

每帧调用多次以响应 GUI 事件。首先处理布局和重新绘制事件，然后为每个输入事件处理布局和键盘/鼠标事件。

##### **- yield WaitForEndOfFrame（协程：帧结束）**

在协程中使用，等待帧结束后继续执行。

#### **6. 暂停阶段**

##### **- OnApplicationPause（应用暂停）**

在应用暂停时调用，可用于处理暂停时的逻辑。

#### **7. 退出阶段**

##### **- OnApplicationQuit（应用退出）**

在应用退出时调用，可用于处理退出时的逻辑。

##### **- OnDisable（隐藏）

行为被禁用或处于非活动状态时，调用此函数。

##### **- OnDestroy（销毁）**

在对象被销毁时调用，进行资源释放等清理操作。

通过了解和合理使用这些生命周期函数，我们可以更好地掌握 Unity 中对象的生命周期，实现精确的逻辑控制和资源管理。希望这份解析能够帮助你更好地理解 Unity 生命周期函数的作用和运行顺序。