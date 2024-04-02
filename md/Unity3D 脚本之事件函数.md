> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=MzkxNzU0MTQwNQ==&mid=2247484085&idx=1&sn=f2842a98fba29ccdea352c16478280c9&chksm=c1be45c7f6c9ccd16c6533adadda7d15293d6e10d8b4ca3a48f999ecb751fd4be7a1a2c757e4&cur_album_id=3285227852443090947&scene=189#wechat_redirect)

**加载第一个场景**

场景开始时将调用以下函数（为场景中的每个对象调用一次）。

Awake：始终在任何 Start 函数之前并在实例化预制件之后调用此函数。（如果游戏对象在启动期间处于非活动状态，则在激活之后才会调用 Awake。）

OnEnable：（仅在对象处于激活状态时调用）在启用对象后立即调用此函数。在创建 MonoBehaviour 实例时（例如加载关卡或实例化具有脚本组件的游戏对象时）会执行此调用。

请注意，对于添加到场景中的对象，在为任何对象调用 Start 和 Update 等函数之前，会为_所有_ 脚本调用 Awake 和 OnEnable 函数。当然，在游戏运行过程中实例化对象时，不能强制执行此调用。

**Editor**

Reset：调用 Reset 可以在脚本首次附加到对象时以及使用 Reset 命令时初始化脚本的属性。

OnValidate：每当设置脚本的属性时都会调用 OnValidate，包括反序列化对象时，这可能发生在不同的时间，例如在编辑器中打开场景时和域重新加载后。

**在第一次帧更新之前**

Start：仅当启用脚本实例后，才会在第一次帧更新之前调用 Start。

对于场景资源中的对象，在为任何脚本调用 Update 等函数之前，将在所有脚本上调用 Start 函数。当然，在游戏运行过程中实例化对象时，不能强制执行此调用。

**帧之间**

OnApplicationPause：在帧的结尾处调用此函数（在正常帧更新之间有效检测到暂停）。在调用 OnApplicationPause 之后，将发出一个额外帧，从而允许游戏显示图形来指示暂停状态。

**更新顺序**

跟踪游戏逻辑和交互、动画、摄像机位置等的时候，可以使用一些不同事件。常见方案是在 Update 函数中执行大多数任务，但是也可以使用其他函数。

FixedUpdate：调用 FixedUpdate 的频度常常超过 Update。如果帧率很低，可以每帧调用该函数多次；如果帧率很高，可能在帧之间完全不调用该函数。在 FixedUpdate 之后将立即进行所有物理计算和更新。在 FixedUpdate 内应用运动计算时，无需将值乘以 Time.deltaTime。这是因为 FixedUpdate 的调用基于可靠的计时器（独立于帧率）。

Update：每帧调用一次 Update。这是用于帧更新的主要函数。

LateUpdate：每帧调用一次 LateUpdate__（在 Update__ 完成后）。LateUpdate 开始时，在 Update 中执行的所有计算便已完成。LateUpdate 的常见用途是跟随第三人称摄像机。如果在 Update 内让角色移动和转向，可以在 LateUpdate 中执行所有摄像机移动和旋转计算。这样可以确保角色在摄像机跟踪其位置之前已完全移动。

通常，不应依赖为不同的游戏对象调用相同事件函数的顺序 - 除非顺序明确记录或可设置。（如果需要对播放器循环进行更细粒度的控制，可以使用 PlayerLoop API。）

不能指定为同一 MonoBehaviour 子类的不同实例调用事件函数的顺序。例如，一个 MonoBehaviour 的 Update 函数可能会在另一个游戏对象（包括其父级或子级游戏对象）上的相同 MonoBehaviour 的 Update 函数之前或之后调用。

可以指定一个 MonoBehaviour 子类的事件函数应在不同子类的事件函数之前调用（使用 Project Settings 窗口的 Script Execution Order 面板）。例如，如果有两个脚本，EngineBehaviour 和 SteeringBehaviour，可以设置 Script Execution Order，这样 EngineBehaviours 始终在 SteeringBehaviours 之前更新。

**动画更新循环**

Unity 评估动画系统时，将调用以下函数和 Profiler 标记。

OnStateMachineEnter：在状态机更新 (State Machine Update) 步骤中，当控制器的状态机进行流经 Entry 状态的转换时，将在第一个更新帧上调用此回调。在转换到 StateMachine 子状态时不会调用此回调。仅当动画图中存在控制器组件（例如，AnimatorController、AnimatorOverrideController 或 AnimatorControllerPlayable）时才会发生此回调。注意：将此回调添加到 StateMachineBehaviour 组件会禁用多线程的状态机评估。

OnStateMachineExit：在状态机更新 (State Machine Update) 步骤中，当控制器的状态机进行流经 Exit 状态的转换时，将在最后一个更新帧上调用此回调。在转换到 StateMachine 子状态时不会调用此回调。仅当动画图中存在控制器组件（例如，AnimatorController、AnimatorOverrideController 或 AnimatorControllerPlayable）时才会发生此回调。注意：将此回调添加到 StateMachineBehaviour 组件会禁用多线程的状态机评估。

触发动画事件 (Fire Animation Events)：调用在上次更新时间和当前更新时间之间采样的所有剪辑中的所有动画事件。

StateMachineBehaviour (OnStateEnter/OnStateUpdate/OnStateExit)：一个层最多可以有 3 个活动状态：当前状态、中断状态和下一个状态。使用一个定义 OnStateEnter、OnStateUpdate 或 OnStateExit 回调的 StateMachineBehaviour 组件为每个活动状态调用此函数。依次针对当前状态、中断状态和下一个状态调用此函数。仅当动画图中存在控制器组件（例如，AnimatorController、AnimatorOverrideController 或 AnimatorControllerPlayable）时才会执行此步骤。

OnAnimatorMove：在每个更新帧中为每个 Animator 组件调用一次此函数来修改根运动 (Root Motion)。

StateMachineBehaviour(OnStateMove)：使用定义此回调的 StateMachineBehaviour 在每个活动状态中调用此函数。

OnAnimatorIK：设置动画 IK。为每个启用 IK pass 的 Animator Controller 层进行一次此调用。仅当使用人形骨架时才会执行此事件。

StateMachineBehaviour(OnStateIK)：使用在启用 IK pass 的层上定义此回调的 StateMachineBehaviour 组件在每个活动状态中调用此函数。

WriteProperties：从主线程将所有其他动画属性写入场景。

**有用的性能分析标记**

脚本生命周期流程图中显示的某些动画函数不是可以调用的事件函数；它们是 Unity 处理动画时调用的内部函数。

这些函数具有 Profiler 标记，因此您可以使用 Profiler 查看 Unity 在帧中调用这些函数的时间。知道 Unity 调用这些函数的时间有助于准确了解所调用的事件函数的具体执行时间。

例如，假设在 FireAnimationEvents 回调中调用 Animator.Play。如果知道只有在执行状态机更新 (State Machine Update) 和流程图 (Process Graph) 函数后才会触发 FireAnimationEvents 回调，就可以预期动画剪辑会在下一帧播放，而不是马上播放。

状态机更新 (State Machine Update)：在执行序列的此步骤中评估所有状态机。仅当动画图中存在控制器组件（例如，AnimatorController、AnimatorOverrideController 或 AnimatorControllerPlayable）时才会发生此回调。注意：状态机评估通常是多线程的，但添加某些回调（例如，OnStateMachineEnter 和 OnStateMachineExit）会禁用多线程。请参数上文的动画更新循环以了解详细信息。

ProcessGraph：评估所有动画图。此过程包括对需要评估的所有动画剪辑进行采样以及计算根运动 (Root Motion)。

ProcessAnimation：混合动画图的结果。

WriteTransforms：将所有动画变换从工作线程写入场景。如果一个人形骨架的多个层启用了 IK pass，则该人形骨架可以有多个 WriteTransforms 通道（请参阅脚本生命周期流程图）。

**Rendering**

OnPreCull：在摄像机剔除场景之前调用。剔除操作将确定摄像机可以看到哪些对象。正好在进行剔除之前调用 OnPreCull。

OnBecameVisible/OnBecameInvisible：对象变为对任何摄像机可见 / 不可见时调用。

OnWillRenderObject：如果对象可见，则为每个摄像机调用一次。

OnPreRender：在摄像机开始渲染场景之前调用。

OnRenderObject：所有常规场景渲染完成之后调用。此时，可以使用 GL 类或 Graphics.DrawMeshNow 来绘制自定义几何形状。

OnPostRender：在摄像机完成场景渲染后调用。

OnRenderImage：在场景渲染完成后调用以允许对图像进行后处理，请参阅后期处理效果。

OnGUI：每帧调用多次以响应 GUI 事件。首先处理布局和重新绘制事件，然后为每个输入事件处理布局和键盘 / 鼠标事件。

OnDrawGizmos 用于在场景视图中绘制辅助图标以实现可视化。

Note: These callbacks only work with the Built-in Render Pipeline.

**协程**

Update 函数返回后将运行正常协程更新。协程是一个可暂停执行 (yield) 直到给定的 YieldInstruction 达到完成状态的函数。协程的不同用法：

yield 在下一帧上调用所有 Update 函数后，协程将继续。

yield WaitForSeconds 在为帧调用所有 Update 函数后，在指定的时间延迟后继续。

yield WaitForFixedUpdate 在所有脚本上调用所有 FixedUpdate 后继续。如果协同程序在 FixedUpdate 之前生成，那么它会在当前帧的 FixedUpdate 之后继续运行。

yield WWW 在 WWW 下载完成后继续。

yield StartCoroutine 将协程链接起来，并会等待 MyFunc 协程先完成。

**销毁对象时**

OnDestroy：对象存在的最后一帧完成所有帧更新之后，调用此函数（可能应 Object.Destroy 要求或在场景关闭时销毁该对象）。

**退出时**

在场景中的所有活动对象上调用以下函数：

OnApplicationQuit：在退出应用程序之前在所有游戏对象上调用此函数。在编辑器中，用户停止播放模式时，调用函数。

OnDisable：行为被禁用或处于非活动状态时，调用此函数。

来源 unity 官方文档。