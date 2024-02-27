> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzg2MjUzMzcyOA==&mid=2247484014&idx=1&sn=d9464b228d84c3d0bfce11cb03528164&chksm=ce072361f970aa77fad2ab3e2afc93ee365fa1d819dba6d923a33af243a817790b4d1d179cd1&scene=21#wechat_redirect)

![](https://mmbiz.qpic.cn/sz_mmbiz_gif/NSzqcbtSiakk2R1OlRqdW1SbE9nGyweDLewpL1tqczMic9pQhK2mAJJJIX9dtXTZ17rpTztNveQgefpfqicFwPtibw/640?wx_fmt=gif&from=appmsg)

**点击蓝字，关注我们**

![](https://mmbiz.qpic.cn/sz_mmbiz_png/NSzqcbtSiakk2R1OlRqdW1SbE9nGyweDLgZ60yGUNcqVViaNkgsz9V6g1Ro8ibddyBEB4tN7G6KR3V5XHXEIwCU2Q/640?wx_fmt=png&from=appmsg)

在 unity 游戏设计中，观察者模式（Observer Pattern）有着重要的作用，它主要用于实现对象之间的一对多的依赖关系，当一个对象的状态发生变化时，所有依赖于它的对象都得到通知并自动更新。

观察者模式在游戏设计中有几个重要的作用：

**松耦合（Loose Coupling）：** 观察者模式帮助实现了对象之间的松耦合关系。主题和观察者之间没有直接的依赖关系，使得它们能够独立地演化。这使得游戏系统更容易扩展和修改，因为一个对象的改变不会直接影响到其他对象。

**事件处理：** 在游戏中，有许多事件（例如玩家输入、游戏状态变化、玩家死亡等）。观察者模式使得不同的游戏元素能够订阅并响应这些事件，从而实现更灵活的事件处理机制。

**实时通知：** 观察者模式允许在主题状态变化时实时通知所有观察者。这对于实时性要求高的游戏系统非常重要，例如当一个敌人被击败时，所有相关的元素都能够及时做出响应。

**解耦主题和观察者：** 主题和观察者之间的解耦使得系统更易于维护。如果需要添加新的观察者或改变观察者的行为，可以做到不影响主题的实现，从而降低了代码的复杂性。

举个例子：

**传统方式：**

当玩家 HP<=0 时，要调用动画、音效、存档，每个系统都要在玩家类里引用，需要调用一系列方法。耦合性高、代码难以维护。

一个代码里耦合了多个系统。

```
//玩家死亡void PlayerDead(){    // 播放死亡动画    AnimationSystem.PlayDeathAnimation();        // 播放死亡音效    SoundSystem.PlayDeathSound();        // 存档系统记录    SaveSystem.SaveGame();}
```

**观察者模式：**

在 unity 中可以通过 c# 委托函数实现观察者模式。

```
// 定义委托public delegate void PlayerDeathEvent();// 被观察者（事件源）public class Observer : MonoBehaviour{    // 委托事件，将需要触发的一系列事件+=进来    public static event PlayerDeathEvent OnPlayerDeath; //点击按钮模拟玩家死亡，玩家死亡就是一个事件    //一个事件会触发多个事件    Button btn;    void Start()    {        btn = GetComponent<Button>();        // 当按钮点击时（玩家死亡），触发委托事件，        //点击后会触发+=进来的一系列事件：动画处理、音效处理、存档处理        btn.onClick.AddListener(() =>        {            if (OnPlayerDeath != null)            {                OnPlayerDeath();            }        });    }}// 具体的观察者类public class AnimationSystem : MonoBehaviour{    void Start()    {        // 注册观察者事件，在PlayerDeathEvent里面加入需要触发的一系列事件        Observer.OnPlayerDeath += PlayDeathAnimation;    }    void PlayDeathAnimation()    {        // 处理动画系统逻辑    }}// 具体的观察者类public class SoundSystem : MonoBehaviour{    void Start()    {        // 注册观察者        Observer.OnPlayerDeath += PlayDeathSound;    }    void PlayDeathSound()    {        // 处理音效系统逻辑    }}// 具体的观察者类public class SaveSystem : MonoBehaviour{    void Start()    {        // 注册观察者        Observer.OnPlayerDeath += SaveGame;    }    void SaveGame()    {        // 处理存档系统逻辑    }}
```

上面的代码的表示是这些相关系统在观察玩家是否死亡，一旦死亡，就会触发注册的事件，跟在玩家死亡后面执行。通过观察者模式，按钮的点击事件（玩家死亡）与其他系统的逻辑彼此解耦，不再需要直接引用对方。这使得系统更加灵活，可以方便地扩展和维护。

通过观察者模式，可以实现游戏中对象之间的松耦合关系，提高代码的可维护性和扩展性。当游戏中的某个模块需要与其他模块进行通信时，可以通过观察者模式实现一种灵活而有效的方式。