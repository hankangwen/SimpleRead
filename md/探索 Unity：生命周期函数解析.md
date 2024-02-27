> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247483949&idx=1&sn=c6e403effe6ed01f860e27cc6fed4ab8&chksm=ce072322f970aa34bab2f5b7f5793be98a28450b200c9335a600061dfd21d366bf145d50daff&scene=178&cur_album_id=3218021275236007937#rd)

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/NSzqcbtSiaklV4sicChzIaIOZeJrmZfmh3K8WhVUiaASFABW4Z9MISTgoXBsShaeVqJBWpgvgViaQ9icxMk2EPCMmKg/640)

**点击蓝字，关注我们**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/JzT3Hy1ZmiaSLzNsD4vMIGbWoNTich9qKSRSLNA8ZMBAuaIqgnG6bCW0KNfO1h1V8wbkCJPsvbGj9hKh6Igd1kbQ/640)

Unity 生命周期函数是在游戏对象的不同阶段被调用的方法，通过这些函数，我们可以在不同的时刻执行特定的代码。在这篇文章中，我们将一步步解析 Unity 生命周期函数，分为不同阶段来理解它们的作用。

**1. 初始化阶段**

**- Awake（唤醒）**

在对象被实例化时调用，适合进行初始化操作，但是不能保证其他对象都已经唤醒。

**- OnEnable（当可用）**

在对象被激活时调用，用于启用与对象相关的组件和资源。

**- Reset（重置）（Editor）**

在 Unity 编辑器中，当脚本被 Reset 按钮重置时调用，通常用于初始化编辑器状态。

**- Start（开始）**

在对象的第一帧更新前调用，常用于初始化游戏对象之间的引用关系等操作。

**2. 物理阶段**

**- FixedUpdate（固定更新）**

在固定的物理时间间隔内调用，适合处理物理相关的逻辑，如移动、碰撞检测等。

**- OnTriggerXXX（触发）**

处理触发器事件，例如 OnTriggerEnter、OnTriggerStay、OnTriggerExit 等。

**- OnCollisionXXX（碰撞）**

处理碰撞事件，例如 OnCollisionEnter、OnCollisionStay、OnCollisionExit 等。

**- yield WaitForFixedUpdate（协程：物理帧结束）**

在协程中使用，等待物理帧结束后继续执行。

**3. 输入事件阶段**

处理用户输入事件，例如鼠标点击、键盘输入等。

**4. 游戏逻辑阶段**

**- Update（更新）**

在每一帧更新时调用，用于处理游戏逻辑。

**- 判断多个协程点**

在 Update 中可以判断多个协程的执行点，进行逻辑控制。

**- 内部动画更新**

在 Update 中更新内部动画。

**- LateUpdate（延后更新）**

在 Update 之后调用，适合处理与 Update 相关的逻辑。

**5. 渲染阶段**

渲染阶段包括多个生命周期函数，用于处理与渲染相关的逻辑，例如特效、相机视觉效果等。以下是这些函数的解释：

**- OnWillRenderObject**

**OnWillRenderObject** 在相机渲染之前调用，用于确定是否渲染当前对象。通常在自定义渲染脚本中使用，允许我们在渲染之前执行特定的逻辑，如动态调整材质或更新纹理。

**- OnPreCull**

**OnPreCull** 在剔除阶段（culling）之前调用，用于在相机剔除不可见物体之前执行逻辑。在这里进行的操作将在剔除阶段考虑，可以用于自定义剔除逻辑或计算视觉效果。

**- OnBecameVisible（即将可见）**

**OnBecameVisible** 当对象在相机视野中变得可见时调用。可以用于激活或处理一些与可见性相关的逻辑，例如开始播放特效或启用特殊效果。

**- OnBecameInvisible（即将不可见）**

**OnBecameInvisible** 当对象在相机视野中变得不可见时调用。适用于处理不可见时的逻辑，如停止播放特效或禁用一些效果以提高性能。

**- OnPreRender（即将渲染）**

**OnPreRender** 在相机渲染之前调用，用于在渲染之前执行特定逻辑。在这里进行的操作将影响相机渲染的结果，可以用于修改材质、设置全局效果等。

**- OnRenderObject**

**OnRenderObject** 在相机渲染物体时调用，通常用于自定义渲染逻辑。在这里可以执行一些与对象渲染相关的操作，例如绘制辅助几何或实现特殊的渲染效果。

**- OnPostRender**

**OnPostRender** 在相机完成渲染后调用，用于在渲染之后执行逻辑。适用于处理与整体渲染结果相关的操作，如后期处理效果。

**- OnRenderImage**

**OnRenderImage** 在相机完成渲染后，但在渲染结果被绘制到屏幕之前调用。允许对渲染结果进行后期处理，生成最终的图像效果。

**- OnDrawGizmos（Gizmos 渲染）**

**OnDrawGizmos** 用于在 Scene 视图中渲染场景的 Gizmos。适用于在编辑器中可视化调试信息，通常用于显示场景中的边界、路径、碰撞体等信息。

**- GUI 渲染**

处理 GUI 渲染的逻辑。

**- yield WaitForEndOfFrame（协程：帧结束）**

在协程中使用，等待帧结束后继续执行。

**6. 暂停阶段**

**- OnApplicationPause（应用暂停）**

在应用暂停时调用，可用于处理暂停时的逻辑。

**7. 退出阶段**

**- OnDestroy（销毁）**

在对象被销毁时调用，进行资源释放等清理操作。

**- OnApplicationQuit（应用退出）**

在应用退出时调用，可用于处理退出时的逻辑。

通过了解和合理使用这些生命周期函数，我们可以更好地掌握 Unity 中对象的生命周期，实现精确的逻辑控制和资源管理。希望这份解析能够帮助你更好地理解 Unity 生命周期函数的作用和运行顺序。