> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/Ofa4yng2r7FFWQ6Wkm-U6Q)

不点蓝字，我们哪来故事？

  

  

  

Unity 之 三种抽奖示例（跑马灯，转盘，老虎机实例 文中源码）  

====================================

**一，跑马灯抽奖**

效果图：

![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibroasZEdicL6EqWEettrHsdOOzRjRIqO9KNEE44VRPgSbicBWUCht4DibuQ/640?wx_fmt=gif)

**设计思路：**

点击按钮 ，根据需求 (概率) 计算本次抽奖获得物品

模拟转动 (先加速后减速)， 一段时间后停止

场景搭建：

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibrPlCZ7SAUhknvl7328CSPjDc7uZicx30JgrDickdpVtYxdsu7Uiat6Hib6g/640?wx_fmt=png)

一个按钮，一个组奖品（放到一个父物体上），一个光环（当前选中的那个奖品）

**实现代码：**

```
using System.Collections;
using UnityEngine;
using UnityEngine.UI;


public class RotaryTablePanel : MonoBehaviour
{
    // 抽奖按钮，
    public Button drawBtn;
    // 抽奖图片父物体
    public Transform rewardImgTran;
    // 光环
    public Transform HaloImgTransform;
    // 抽奖图片
    private Transform[] rewardTransArr;


    // 默认展示状态
    private bool isInitState;
    // 抽奖结束 -- 结束状态，光环不转
    private bool drawEnd;
    // 中奖
    private bool drawWinning;
    
    // 展示状态时间 --> 控制光环转动速度
    private float rewardTime = 0.8f;
    private float rewardTiming = 0;


    // 当前光环所在奖励的索引
    private int haloIndex = 0;
    // 本次中奖ID
    private int rewardIndex = 0;
    
    // 点了抽奖按钮正在抽奖
    private bool isOnClickPlaying;
    
    void Start()
    {
        drawBtn.onClick.AddListener(OnClickDrawFun);
        rewardTransArr = new Transform[rewardImgTran.childCount];
        for (int i = 0; i < rewardImgTran.childCount; i++)
        {
            rewardTransArr[i] = rewardImgTran.GetChild(i);
        }
        
        // 默认展示时间
        rewardTime = 0.6f;
        rewardTiming = 0;
        
        drawEnd = false;
        drawWinning = false;
        isOnClickPlaying = false;
    }


    
    void Update()
    {
        if (drawEnd) return;
        
        // 抽奖展示
        rewardTiming += Time.deltaTime;
        if (rewardTiming >= rewardTime)
        {
            rewardTiming = 0;
            haloIndex++;
            if (haloIndex >= rewardTransArr.Length)
            {
                haloIndex = 0;
            }
            SetHaloPos(haloIndex);
        }
    }
    
    // 设置光环显示位置
    void SetHaloPos(int index)
    {
        HaloImgTransform.position = rewardTransArr[index].position;


        // 中奖 && 此ID == 中奖ID
        if (drawWinning && index == rewardIndex)
        {
            isOnClickPlaying = false;
            drawEnd = true;
            //todo...展示中奖物品，维护数据 --> 注意: index是索引
            Debug.Log("恭喜您中奖，中奖物品索引是：" + index + "号");
        }
    }


    // 点击抽奖按钮
    void OnClickDrawFun()
    {
        if (!isOnClickPlaying)
        {
            // 随机抽中ID
            rewardIndex =  Random.Range(0, rewardTransArr.Length);
            Debug.Log("开始抽奖，本次抽奖随机到的ID是：" + rewardIndex);
            isOnClickPlaying = true;
            drawEnd = false;
            drawWinning = false;
            StartCoroutine(StartDrawAni());
        }
    }


    /// <summary>
    /// 开始抽奖动画
    /// 先快后慢 -- 根据需求调整时间
    /// </summary>
    /// <returns></returns>
    IEnumerator StartDrawAni()
    {
        rewardTime = 0.8f;
        // 加速
        for (int i = 0; i < 7; i++)
        {
            yield return new WaitForSeconds(0.1f);
            rewardTime -= 0.1f;
        }
        yield return new WaitForSeconds(2f);
        // 减速
        for (int i = 0; i < 5; i++)
        {
            yield return new WaitForSeconds(0.1f);
            rewardTime += 0.1f;
        }        
        yield return new WaitForSeconds(1f);
        drawWinning = true;
    }
    
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/pvb9xD2icalR48l1bYUE1KtCMOsm0DxCzjb9TYxEhyjzxXU6AQo9Inzibrwv8ZGsga4KmrEJakauYZ7N6C8Sia7UA/640?wx_fmt=png)

**二，转盘抽奖**

**效果图：**

![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibrcMSaT1lEVHXLcXCwlhz7LWGFsLxgKicaN1HMGibU3L4biaxALWRhH8icyQ/640?wx_fmt=gif)

**设计思路：**（和上面差不多）

点击按钮 ，根据需求 (概率) 计算本次抽奖获得物品索引

根据随机到的索引，计算需要旋转的角度

模拟转动 ， 一段时间后停止到计算的角度上

场景搭建：

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibrpoIFXK96mgf7yo6KQnphOVIAlUIbFD34BZib3Jr1bKMH5WBpVRvSjsQ/640?wx_fmt=png)

一个按钮，一个转盘，一个指针；

**实现代码：**

```
using UnityEngine;
using UnityEngine.UI;


public class RotaryDrawDemo : MonoBehaviour
{
    // 转盘
    public Transform RotateTableTrans;
    // 抽奖按钮
    public Button DrawBtn;
    // 转盘区域数 -- （Demo中图片是10份）
    private int rotateTableNumber = 10;
    
    // 旋转动画时间      
    private float rotateTime = 3f;
    private float rotateTiming = 0f;
    /// <summary>
    /// 需要转动到的目标位置
    /// </summary>
    private Quaternion targetAngels = Quaternion.identity;
    // 转动的速度 
    private float rotateSpeed = 20;
    // 模拟抽奖的选择时间 
    private float RotateTime = 3f;
    /// <summary>
    /// 是否开始抽奖转动
    /// </summary>
    private bool isStartRotate = false;
    // 本次中奖ID
    private int rewardIndex = 0;

    void Start()
    {
        DrawBtn.onClick.AddListener(OnClickDrawFun);
    }
    void Update()
    {
        if (!isStartRotate) return;
        
        rotateTiming += Time.deltaTime;
        // 过了动画时间
        if (rotateTiming >= RotateTime)
        {
            RotateTableTrans.Rotate(Vector3.back * 2);
            // 计算当前正在旋转的角度和目标角度的夹角
            if (Quaternion.Angle(RotateTableTrans.rotation, targetAngels) <= 2)
            {
                // 设置目标夹角
                RotateTableTrans.rotation = targetAngels;
                // 转动停止
                isStartRotate = false;


                // todo... 奖品展示，数据维护
                Debug.Log("***** 恭喜或的奖品，奖品索引：" + rewardIndex + " ，转盘角度是：" 
                          + RotateTableTrans.localEulerAngles.z + "*****");
            }
        }
        else
        {
            // 转动转盘(back为顺时针, forward为逆时针)
            RotateTableTrans.Rotate(Vector3.back * 10);
        }
    }


    // 点击抽奖按钮
    void OnClickDrawFun()
    {
        if (!isStartRotate)
        {
            //开始旋转
            isStartRotate = true;
            rotateTiming = 0;
            // 随机到转盘第几块区域
            rewardIndex = Random.Range(0, rotateTableNumber);
            // 根据区域计算角度 --> 36 = 360 / rotateTableNumber;
            float targetRot = rewardIndex * 36; 
            //设置目标位置
            targetAngels = Quaternion.Euler(0, 0, targetRot);
            
            Debug.Log("----- 开始抽奖 随机到的区域，索引是:" + rewardIndex + "，角度是：" + targetRot + "-----");
        }
    }
}
```

![](https://mmbiz.qpic.cn/mmbiz_png/pvb9xD2icalR48l1bYUE1KtCMOsm0DxCzjb9TYxEhyjzxXU6AQo9Inzibrwv8ZGsga4KmrEJakauYZ7N6C8Sia7UA/640?wx_fmt=png)

**三，老虎机抽奖**

效果图：

![](https://mmbiz.qpic.cn/mmbiz_gif/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibrXia38nw57eEnSHvRiafsB3ZW6SZtxM6QRIUZFyt9P0bybQwuibckic2McQ/640?wx_fmt=gif)

场景搭建：

1. 创建 Image 命名为 Bg 作为电视框背景；

2. 创建 Image 命名 Mask 并添加 Mask 组件作为电视框内容显示遮罩框；

3. 创建四个 Image 作为滚动图片；

4. 创建开始抽奖按钮；

![](https://mmbiz.qpic.cn/mmbiz_png/MIOAFJuZ009DQO4g4fnNlOgbYspiboXibrH9G6ZicZ3U6LeYzE55jxM95Tkwfd1uOicuQqCGgRHdkMCzOWny4g1GEQ/640?wx_fmt=png)

PS：实际项目中可以根据需求来动态修改图片显示，以达到的控制每次抽奖奖品内容。

```
using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class ScollToDraw : MonoBehaviour
{
      // 抽奖按钮
      public Button DrowBtn;
      
      // 奖励图片
      public Image[] ArardImgArr;

      // 转盘速度
      public float AniMoveSpeed = 3f;

      // 进度
      private float[] progress = new[] {0f, 1f, 2f, 3f, 4f};

      // 转动动画位置
      private Vector3[] AniPosV3 = new[]
            {Vector3.up * 240, Vector3.up * 120, Vector3.zero, Vector3.down * 120, Vector3.down * 240};

      // 自动暂停标识
      private bool isAutoStop;
      // 抽奖结束 停止刷新界面UI
      private bool isStopUpdatePos;
      
      void Start()
      {
            DrowBtn.onClick.AddListener(DrawFun);
            isAutoStop = false;
            isStopUpdatePos = false;
      }

      void Update()
      {
            if (isStopUpdatePos) return;
            
            float t = Time.deltaTime * AniMoveSpeed;
            for (int i = 0; i < ArardImgArr.Length; i++)
            {
                  progress[i] += t;
                  ArardImgArr[i].transform.localPosition = MovePosition(i);
            }
      }
      
      // 获取下一个移动到的位置
      Vector3 MovePosition(int i)
      {
            int index = Mathf.FloorToInt(progress[i]);
            if (index > AniPosV3.Length - 2)
            {
                  //保留其小数部分，不能直接赋值为0
                  progress[i] -= index; 
                  index = 0;
                  // 索引为2的到底了，索引为0的就在正中心
                  if (i == 2 && isAutoStop)
                  {
                        isStopUpdatePos = true;
                        Debug.Log("展示奖励界面...");
                        // todo...获取奖励数据维护
                  }
                  return AniPosV3[index];
            }
            else
            {
                  return Vector3.Lerp(AniPosV3[index], AniPosV3[index + 1], progress[i] - index);
            }
      }
      
      /// <summary>
      /// 点击抽奖
      /// </summary>
      void DrawFun()
      {
            isAutoStop = false;
            isStopUpdatePos = false;
            StartCoroutine(SetMoveSpeed(2));
            // DoTween 按钮下拉动画
            // Transform tran = DrowBtn.transform;
            //tran.DOLocalMoveY(-60, 0.2f).OnComplete(() =>
            //{
            //      tran.DOLocalMoveY(50, 0.2f);
            //
            //});
      }
      
      // 抽奖动画速度控制
      IEnumerator SetMoveSpeed(int time)
      {
            AniMoveSpeed = 10;
            yield return new WaitForSeconds(time);
            AniMoveSpeed = 1;
            yield return new WaitForSeconds(time);
            isAutoStop = true;
      }
}
```

**V 信搜 "开发同学留步"，回复 “Unity 抽奖” 获得一，二项目源码。**

**V 信搜 "开发同学留步"，回复 “老虎机” 获得第三个项目源码。**

好看的人才能点

![](https://mmbiz.qpic.cn/mmbiz_gif/b96CibCt70iaaBAicDNCSs6H0O0SBGSALfnHVryZWUNXAT7Luaia7E90nBw8hhXic1BChibrWdYMCL7RxhPMX0pafichQ/640?wx_fmt=gif)