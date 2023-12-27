> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/Czhenya/article/details/118172854)

#### 2048 化学元素版？一文教你 Unity 零基础制作 2048！

*   [前言](#_2)
*   [一，游戏介绍和效果展示](#_6)
*   [二，开发前的准备工作](#_16)
*   *   [2.1 创建工程](#21__18)
    *   [2.2 导入素材](#22__26)
*   [三，游戏开发进行中](#_39)
*   *   [3.1 游戏场景搭建](#31__41)
    *   [3.2 核心代码编写](#32__68)
    *   [3.3 游戏音效处理](#33__102)
*   [四，游戏完成源码分享](#_114)
*   *   [4.1 Manager 游戏管理类](#41_Manager_116)
    *   [4.2 Number 数字处理类](#42_Number_414)
*   [结语](#_704)

前言
--

> 玩游戏也能学习知识？还记得高中时的化学元素常见金属活动性属性表吗？一起来复习一下：钾 K，钙 Ca，钠 Na，镁 Mg，铝 Al，锌 Zn，铁 Fe， 锡 Ni，铅 Sn，氢 (H)，铜 Cu，汞 Hg，银 Ag，铂 Pt，金 Au。 一股很熟悉的味道有没有？一起来看看化学元素和游戏之间发生的碰撞吧~

一，游戏介绍和效果展示
-----------

2048 一款益智小游戏，游戏的规则十分简单，简单易上手的数字小游戏，闲来无事，自己制作一个，却怎么也到没有成功到 2048。

老规矩，先看下按照此博文一步步操作完成的效果吧~

![](https://img-blog.csdnimg.cn/img_convert/4afcdc9d6b9a0f7dde4ae2038a8b10ca.gif#pic_center)

二，开发前的准备工作
----------

### 2.1 创建工程

打开 Unity Hub 点击 “新建”，在弹窗中输入 --> “项目名称” --> 选择 "项目位置" --> “项目版本控制系统” 选不选都行，不需要在云端备份的话就不要选（我一般不选）  
，选了没用过的话，会自动帮你安装 PlasticSCM 到本地。最后点击创建即可。

![](https://img-blog.csdnimg.cn/img_convert/ad93ab936b9d8e02847bab7df623757c.png)

### 2.2 导入素材

将提前准备好的素材 (图片和声音) 导入工程。(文末会提供下载地址)

*   方式一: 在 "Project" 面板右键 --> “Improt Package” --> “Custom Package…” --> 选择自己下载下来的 UnityPackage --> 最后点击 "Import" 导入。  
    ![](https://img-blog.csdnimg.cn/img_convert/bff0b558a8897d8039af7999a4ec0906.png)
    
*   方式二: 直接将下载还的 UnityPackage，拖拽到项目中，然后点击 "Import" 导入:![](https://img-blog.csdnimg.cn/img_convert/fb8016eab41a37d016f9c2738b68d872.gif)
    

导入项目后工程目录如下:  
![](https://img-blog.csdnimg.cn/img_convert/bc4ea8f3b7d5bb76b989b7b2eb42d6c6.png)

三，游戏开发进行中
---------

### 3.1 游戏场景搭建

*   设置分辨率：点击 Game 视图分辨率选框，设置为 (1080x1920)，没有的话点击加号自行添加一个，或者使用一个竖屏的就可以。![](https://img-blog.csdnimg.cn/img_convert/49d9e8c44c89e4323045fa59f18f410b.png)
    
*   创建背景: 右键 UI --> Image 创建后，重命名为 BG，将其锚点设置为铺满，源文件指定为素材 "play_bg_forest_dark":  
    ![](https://img-blog.csdnimg.cn/img_convert/4d6ca63ab7fac56c10cedae47ad21b5e.png)
    
*   修改 Canvas: 将自动创建出来的 Canvas 的 Canvas Scaler 属性设置如下:  
    ![](https://img-blog.csdnimg.cn/img_convert/302c790f7f373d06a9103d8a101900d7.png)
    
*   创建格子: 在 “Canvas” 下创建 Image，重命名为“MapBg”，将其宽高设置为(1720,1720)，然后修改其颜色为浅蓝色，透明度相应调低，效果如下:(自己觉得好看就可以了)  
    ![](https://img-blog.csdnimg.cn/img_convert/377677b698933ec0d273d460500d99a5.png)  
    然后在 “MapBg” 下再次创建一个 Image，重命名为“gezi”，将其宽高设置为(400,388)，调整其颜色为(22,0,192,30)，还是一样调整到自己喜欢的颜色即可。然后“Ctrl + D” 复制 15 个格子出来:  
    ![](https://img-blog.csdnimg.cn/img_convert/92ee3d98f0c082fe9a6f4b59e5ca9db4.png)  
    最后在 “MapBg” 上添加 "Grid Layout Group"，属性设置如下图，将格子铺满到地图背景上:  
    ![](https://img-blog.csdnimg.cn/img_convert/5d9605c63d2b13814cabf83967906e5e.png)
    
*   创建数字池: 右键创建一个空物体作为加载数字的父物体，并命名为 “NumPool”，所有属性默认即可。  
    ![](https://img-blog.csdnimg.cn/img_convert/67cc30ce9deeb9dcd8ae51e1072a2736.png)
    
*   创建数字预制体: 右键 Image 重命名为 Num，宽高调整为和格子一样大 (400,380)，然后将其拽到 Resources 文件夹下，作为预制体，然后右键删除场景中 Num 即可:  
    ![](https://img-blog.csdnimg.cn/img_convert/a92caf279b73f7e6e37e3b6da6de2c39.gif)
    
*   游戏结束面板：创建 Image 命名为 “UIFinsh”，铺满背景。在“UIFinsh” 下在创建一个 Text 和一个 Button，作为游戏结束显示文本和重新开始按钮:![](https://img-blog.csdnimg.cn/img_convert/e88273cef89200468f4f82318a5c2fb8.png)
    

### 3.2 核心代码编写

场景终于搭建完了，下面开始编写脚本吧，**完整代码在四中给出**，这里只讲解实现思路，查看核心逻辑。

*   在 Project 下创建 Scripts 文件夹，然后创建 "Manager.cs" 和 “Number.cs” 脚本。
    
*   基础逻辑就是：默认生成两个数字，接收用户输入，管理器触发移动逻辑，数字移动并校验合并，移动后校验是否游戏结束，若结束处理游戏结束摞，若未结束在自动生成一个数字:
    

#mermaid-svg-u6uv8GgEf5ErAH0X .label{font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family);fill:#333;color:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .label text{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .node rect,#mermaid-svg-u6uv8GgEf5ErAH0X .node circle,#mermaid-svg-u6uv8GgEf5ErAH0X .node ellipse,#mermaid-svg-u6uv8GgEf5ErAH0X .node polygon,#mermaid-svg-u6uv8GgEf5ErAH0X .node path{fill:#ECECFF;stroke:#9370db;stroke-width:1px}#mermaid-svg-u6uv8GgEf5ErAH0X .node .label{text-align:center;fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .node.clickable{cursor:pointer}#mermaid-svg-u6uv8GgEf5ErAH0X .arrowheadPath{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .edgePath .path{stroke:#333;stroke-width:1.5px}#mermaid-svg-u6uv8GgEf5ErAH0X .flowchart-link{stroke:#333;fill:none}#mermaid-svg-u6uv8GgEf5ErAH0X .edgeLabel{background-color:#e8e8e8;text-align:center}#mermaid-svg-u6uv8GgEf5ErAH0X .edgeLabel rect{opacity:0.9}#mermaid-svg-u6uv8GgEf5ErAH0X .edgeLabel span{color:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .cluster rect{fill:#ffffde;stroke:#aa3;stroke-width:1px}#mermaid-svg-u6uv8GgEf5ErAH0X .cluster text{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family);font-size:12px;background:#ffffde;border:1px solid #aa3;border-radius:2px;pointer-events:none;z-index:100}#mermaid-svg-u6uv8GgEf5ErAH0X .actor{stroke:#ccf;fill:#ECECFF}#mermaid-svg-u6uv8GgEf5ErAH0X text.actor>tspan{fill:#000;stroke:none}#mermaid-svg-u6uv8GgEf5ErAH0X .actor-line{stroke:grey}#mermaid-svg-u6uv8GgEf5ErAH0X .messageLine0{stroke-width:1.5;stroke-dasharray:none;stroke:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .messageLine1{stroke-width:1.5;stroke-dasharray:2, 2;stroke:#333}#mermaid-svg-u6uv8GgEf5ErAH0X #arrowhead path{fill:#333;stroke:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .sequenceNumber{fill:#fff}#mermaid-svg-u6uv8GgEf5ErAH0X #sequencenumber{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X #crosshead path{fill:#333;stroke:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .messageText{fill:#333;stroke:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .labelBox{stroke:#ccf;fill:#ECECFF}#mermaid-svg-u6uv8GgEf5ErAH0X .labelText,#mermaid-svg-u6uv8GgEf5ErAH0X .labelText>tspan{fill:#000;stroke:none}#mermaid-svg-u6uv8GgEf5ErAH0X .loopText,#mermaid-svg-u6uv8GgEf5ErAH0X .loopText>tspan{fill:#000;stroke:none}#mermaid-svg-u6uv8GgEf5ErAH0X .loopLine{stroke-width:2px;stroke-dasharray:2, 2;stroke:#ccf;fill:#ccf}#mermaid-svg-u6uv8GgEf5ErAH0X .note{stroke:#aa3;fill:#fff5ad}#mermaid-svg-u6uv8GgEf5ErAH0X .noteText,#mermaid-svg-u6uv8GgEf5ErAH0X .noteText>tspan{fill:#000;stroke:none}#mermaid-svg-u6uv8GgEf5ErAH0X .activation0{fill:#f4f4f4;stroke:#666}#mermaid-svg-u6uv8GgEf5ErAH0X .activation1{fill:#f4f4f4;stroke:#666}#mermaid-svg-u6uv8GgEf5ErAH0X .activation2{fill:#f4f4f4;stroke:#666}#mermaid-svg-u6uv8GgEf5ErAH0X .mermaid-main-font{font-family:"trebuchet ms", verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .section{stroke:none;opacity:0.2}#mermaid-svg-u6uv8GgEf5ErAH0X .section0{fill:rgba(102,102,255,0.49)}#mermaid-svg-u6uv8GgEf5ErAH0X .section2{fill:#fff400}#mermaid-svg-u6uv8GgEf5ErAH0X .section1,#mermaid-svg-u6uv8GgEf5ErAH0X .section3{fill:#fff;opacity:0.2}#mermaid-svg-u6uv8GgEf5ErAH0X .sectionTitle0{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .sectionTitle1{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .sectionTitle2{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .sectionTitle3{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .sectionTitle{text-anchor:start;font-size:11px;text-height:14px;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .grid .tick{stroke:#d3d3d3;opacity:0.8;shape-rendering:crispEdges}#mermaid-svg-u6uv8GgEf5ErAH0X .grid .tick text{font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .grid path{stroke-width:0}#mermaid-svg-u6uv8GgEf5ErAH0X .today{fill:none;stroke:red;stroke-width:2px}#mermaid-svg-u6uv8GgEf5ErAH0X .task{stroke-width:2}#mermaid-svg-u6uv8GgEf5ErAH0X .taskText{text-anchor:middle;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .taskText:not([font-size]){font-size:11px}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutsideRight{fill:#000;text-anchor:start;font-size:11px;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutsideLeft{fill:#000;text-anchor:end;font-size:11px}#mermaid-svg-u6uv8GgEf5ErAH0X .task.clickable{cursor:pointer}#mermaid-svg-u6uv8GgEf5ErAH0X .taskText.clickable{cursor:pointer;fill:#003163 !important;font-weight:bold}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutsideLeft.clickable{cursor:pointer;fill:#003163 !important;font-weight:bold}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutsideRight.clickable{cursor:pointer;fill:#003163 !important;font-weight:bold}#mermaid-svg-u6uv8GgEf5ErAH0X .taskText0,#mermaid-svg-u6uv8GgEf5ErAH0X .taskText1,#mermaid-svg-u6uv8GgEf5ErAH0X .taskText2,#mermaid-svg-u6uv8GgEf5ErAH0X .taskText3{fill:#fff}#mermaid-svg-u6uv8GgEf5ErAH0X .task0,#mermaid-svg-u6uv8GgEf5ErAH0X .task1,#mermaid-svg-u6uv8GgEf5ErAH0X .task2,#mermaid-svg-u6uv8GgEf5ErAH0X .task3{fill:#8a90dd;stroke:#534fbc}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutside0,#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutside2{fill:#000}#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutside1,#mermaid-svg-u6uv8GgEf5ErAH0X .taskTextOutside3{fill:#000}#mermaid-svg-u6uv8GgEf5ErAH0X .active0,#mermaid-svg-u6uv8GgEf5ErAH0X .active1,#mermaid-svg-u6uv8GgEf5ErAH0X .active2,#mermaid-svg-u6uv8GgEf5ErAH0X .active3{fill:#bfc7ff;stroke:#534fbc}#mermaid-svg-u6uv8GgEf5ErAH0X .activeText0,#mermaid-svg-u6uv8GgEf5ErAH0X .activeText1,#mermaid-svg-u6uv8GgEf5ErAH0X .activeText2,#mermaid-svg-u6uv8GgEf5ErAH0X .activeText3{fill:#000 !important}#mermaid-svg-u6uv8GgEf5ErAH0X .done0,#mermaid-svg-u6uv8GgEf5ErAH0X .done1,#mermaid-svg-u6uv8GgEf5ErAH0X .done2,#mermaid-svg-u6uv8GgEf5ErAH0X .done3{stroke:grey;fill:#d3d3d3;stroke-width:2}#mermaid-svg-u6uv8GgEf5ErAH0X .doneText0,#mermaid-svg-u6uv8GgEf5ErAH0X .doneText1,#mermaid-svg-u6uv8GgEf5ErAH0X .doneText2,#mermaid-svg-u6uv8GgEf5ErAH0X .doneText3{fill:#000 !important}#mermaid-svg-u6uv8GgEf5ErAH0X .crit0,#mermaid-svg-u6uv8GgEf5ErAH0X .crit1,#mermaid-svg-u6uv8GgEf5ErAH0X .crit2,#mermaid-svg-u6uv8GgEf5ErAH0X .crit3{stroke:#f88;fill:red;stroke-width:2}#mermaid-svg-u6uv8GgEf5ErAH0X .activeCrit0,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCrit1,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCrit2,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCrit3{stroke:#f88;fill:#bfc7ff;stroke-width:2}#mermaid-svg-u6uv8GgEf5ErAH0X .doneCrit0,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCrit1,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCrit2,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCrit3{stroke:#f88;fill:#d3d3d3;stroke-width:2;cursor:pointer;shape-rendering:crispEdges}#mermaid-svg-u6uv8GgEf5ErAH0X .milestone{transform:rotate(45deg) scale(0.8, 0.8)}#mermaid-svg-u6uv8GgEf5ErAH0X .milestoneText{font-style:italic}#mermaid-svg-u6uv8GgEf5ErAH0X .doneCritText0,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCritText1,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCritText2,#mermaid-svg-u6uv8GgEf5ErAH0X .doneCritText3{fill:#000 !important}#mermaid-svg-u6uv8GgEf5ErAH0X .activeCritText0,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCritText1,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCritText2,#mermaid-svg-u6uv8GgEf5ErAH0X .activeCritText3{fill:#000 !important}#mermaid-svg-u6uv8GgEf5ErAH0X .titleText{text-anchor:middle;font-size:18px;fill:#000;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X g.classGroup text{fill:#9370db;stroke:none;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family);font-size:10px}#mermaid-svg-u6uv8GgEf5ErAH0X g.classGroup text .title{font-weight:bolder}#mermaid-svg-u6uv8GgEf5ErAH0X g.clickable{cursor:pointer}#mermaid-svg-u6uv8GgEf5ErAH0X g.classGroup rect{fill:#ECECFF;stroke:#9370db}#mermaid-svg-u6uv8GgEf5ErAH0X g.classGroup line{stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X .classLabel .box{stroke:none;stroke-width:0;fill:#ECECFF;opacity:0.5}#mermaid-svg-u6uv8GgEf5ErAH0X .classLabel .label{fill:#9370db;font-size:10px}#mermaid-svg-u6uv8GgEf5ErAH0X .relation{stroke:#9370db;stroke-width:1;fill:none}#mermaid-svg-u6uv8GgEf5ErAH0X .dashed-line{stroke-dasharray:3}#mermaid-svg-u6uv8GgEf5ErAH0X #compositionStart{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #compositionEnd{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #aggregationStart{fill:#ECECFF;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #aggregationEnd{fill:#ECECFF;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #dependencyStart{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #dependencyEnd{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #extensionStart{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X #extensionEnd{fill:#9370db;stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X .commit-id,#mermaid-svg-u6uv8GgEf5ErAH0X .commit-msg,#mermaid-svg-u6uv8GgEf5ErAH0X .branch-label{fill:lightgrey;color:lightgrey;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .pieTitleText{text-anchor:middle;font-size:25px;fill:#000;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .slice{font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X g.stateGroup text{fill:#9370db;stroke:none;font-size:10px;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X g.stateGroup text{fill:#9370db;fill:#333;stroke:none;font-size:10px}#mermaid-svg-u6uv8GgEf5ErAH0X g.statediagram-cluster .cluster-label text{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X g.stateGroup .state-title{font-weight:bolder;fill:#000}#mermaid-svg-u6uv8GgEf5ErAH0X g.stateGroup rect{fill:#ECECFF;stroke:#9370db}#mermaid-svg-u6uv8GgEf5ErAH0X g.stateGroup line{stroke:#9370db;stroke-width:1}#mermaid-svg-u6uv8GgEf5ErAH0X .transition{stroke:#9370db;stroke-width:1;fill:none}#mermaid-svg-u6uv8GgEf5ErAH0X .stateGroup .composit{fill:white;border-bottom:1px}#mermaid-svg-u6uv8GgEf5ErAH0X .stateGroup .alt-composit{fill:#e0e0e0;border-bottom:1px}#mermaid-svg-u6uv8GgEf5ErAH0X .state-note{stroke:#aa3;fill:#fff5ad}#mermaid-svg-u6uv8GgEf5ErAH0X .state-note text{fill:black;stroke:none;font-size:10px}#mermaid-svg-u6uv8GgEf5ErAH0X .stateLabel .box{stroke:none;stroke-width:0;fill:#ECECFF;opacity:0.7}#mermaid-svg-u6uv8GgEf5ErAH0X .edgeLabel text{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .stateLabel text{fill:#000;font-size:10px;font-weight:bold;font-family:'trebuchet ms', verdana, arial;font-family:var(--mermaid-font-family)}#mermaid-svg-u6uv8GgEf5ErAH0X .node circle.state-start{fill:black;stroke:black}#mermaid-svg-u6uv8GgEf5ErAH0X .node circle.state-end{fill:black;stroke:white;stroke-width:1.5}#mermaid-svg-u6uv8GgEf5ErAH0X #statediagram-barbEnd{fill:#9370db}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-cluster rect{fill:#ECECFF;stroke:#9370db;stroke-width:1px}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-cluster rect.outer{rx:5px;ry:5px}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-state .divider{stroke:#9370db}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-state .title-state{rx:5px;ry:5px}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-cluster.statediagram-cluster .inner{fill:white}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-cluster.statediagram-cluster-alt .inner{fill:#e0e0e0}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-cluster .inner{rx:0;ry:0}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-state rect.basic{rx:5px;ry:5px}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-state rect.divider{stroke-dasharray:10,10;fill:#efefef}#mermaid-svg-u6uv8GgEf5ErAH0X .note-edge{stroke-dasharray:5}#mermaid-svg-u6uv8GgEf5ErAH0X .statediagram-note rect{fill:#fff5ad;stroke:#aa3;stroke-width:1px;rx:0;ry:0}:root{--mermaid-font-family: '"trebuchet ms", verdana, arial';--mermaid-font-family:"Comic Sans MS","Comic Sans", cursive}#mermaid-svg-u6uv8GgEf5ErAH0X .error-icon{fill:#522}#mermaid-svg-u6uv8GgEf5ErAH0X .error-text{fill:#522;stroke:#522}#mermaid-svg-u6uv8GgEf5ErAH0X .edge-thickness-normal{stroke-width:2px}#mermaid-svg-u6uv8GgEf5ErAH0X .edge-thickness-thick{stroke-width:3.5px}#mermaid-svg-u6uv8GgEf5ErAH0X .edge-pattern-solid{stroke-dasharray:0}#mermaid-svg-u6uv8GgEf5ErAH0X .edge-pattern-dashed{stroke-dasharray:3}#mermaid-svg-u6uv8GgEf5ErAH0X .edge-pattern-dotted{stroke-dasharray:2}#mermaid-svg-u6uv8GgEf5ErAH0X .marker{fill:#333}#mermaid-svg-u6uv8GgEf5ErAH0X .marker.cross{stroke:#333} :root { --mermaid-font-family: "trebuchet ms", verdana, arial;} #mermaid-svg-u6uv8GgEf5ErAH0X {color: rgba(0, 0, 0, 0.75); font: ; } 结束 继续 默认生成数字 管理器接收用户输入 管理器触发数字移动逻辑 数字移动并校验合并 移动后校验游戏结束 处理游戏结束逻辑

*   Manager 中接收用户输入的方式一种是在移动端的滑动，一种是在 PC 端的按下剪头或 WASD 上下左右移动:  
    ![](https://img-blog.csdnimg.cn/img_convert/bec11ea11676dca02047a3324f9c70cd.png)  
    ![](https://img-blog.csdnimg.cn/img_convert/348f3e761809c1807af0adcfd86e09c4.png)
    
*   Manager 收到用户输入后的控制游戏数字移动逻辑:  
    ![](https://img-blog.csdnimg.cn/img_convert/b165f39ebb9881552fca426e2e0f8616.png)
    
*   Num 类收到 Manager 的移动，合并逻辑处理:  
    ![](https://img-blog.csdnimg.cn/img_convert/022695b629f87c9f5343225190cf1124.png)
    
*   最后将 Manager 挂载到 “BG”，并对公有变量’PoolManager’和’UIFinsh’赋值，如下图即可:  
    ![](https://img-blog.csdnimg.cn/img_convert/cdf4851447d095a08f9b61cf9c2d51cc.png)
    
*   将 Number 脚本挂载到上面制作的预制体 “Num” 上即可。  
    ![](https://img-blog.csdnimg.cn/img_convert/fcb3bc2fee1e49046baba134a078f5bf.png)  
    **此时所有的游戏逻辑就都完成，运行游戏就可以玩耍了~**
    

### 3.3 游戏音效处理

音效是这一个游戏的很重要的部分，一个好的音效可以让用户得到更好的反馈，所以再简单的游戏也要有背景音和音效给用户一个好的交互体验。

*   背景音乐: 在 “BG” 上，添加组件 “Audio Source”，将音频文件“bg_1” 赋值给 AudioClip 并勾选 Loop，即可完成自动循环播放背景音乐:  
    ![](https://img-blog.csdnimg.cn/img_convert/08b564ef054eaf549bd3535367ad4ec4.png)
    
*   数字音效: 同理在 “Num” 预制体上添加组件 “Audio Source”，将音频文件“num” 赋值给 AudioClip，其他属性默认即可。  
    ![](https://img-blog.csdnimg.cn/img_convert/54491211df4afa2cbc424a2a78e408ca.png)
    

四，游戏完成[源码](https://so.csdn.net/so/search?q=%E6%BA%90%E7%A0%81&spm=1001.2101.3001.7020)分享
----------------------------------------------------------------------------------------

### 4.1 Manager 游戏管理类

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{
    public static Manager _isnstance;  //单例模式的引用

    public Transform poolManager;   //生成数字的池子
    private GameObject numPrefab;   //数字的预制体
    public Number[,] numbers = new Number[4, 4]; //保存方格中的数组
    //正在移动中的Num
    public List<Number> isMovingNum = new List<Number>();  
    public bool hasMove = false;   //是否有数字发生了移动
 
    public GameObject UIFinsh;  //游戏结束页面

    void Awake()
    {
        _isnstance = this;
    }
    
    void Start()
    {
        numPrefab = Resources.Load<GameObject>("Num");
        // 开始游戏
        ReStartBtn();
        // 游戏结束面板按钮监听，重新开始
        UIFinsh.GetComponentInChildren<Button>().onClick.AddListener(ReStartBtn);
    }

    // 重新开始
    void ReStartBtn()
    {
        isMovingNum.Clear();
        numbers = new Number[4, 4];
        for (int i = poolManager.childCount - 1; i >= 0; i--)
        {
            Destroy(poolManager.GetChild(i).gameObject);
        }
        hasMove = false;
        //游戏开始生成两个数字
        CreateNun();
        CreateNun();
        UIFinsh.SetActive(false);
    }

    void CreateNun()
    {
        GameObject go = Instantiate(numPrefab);
        go.transform.parent = poolManager;
        go.transform.localScale = Vector3.one;
    }

    #region 检测键盘和触摸输入
    void Update()
    {
        //--------- 移动端检测逻辑 ---------
        //有触摸点，且滑动
        if (isMovingNum.Count == 0)
        {
            if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Moved)
            {
                int dieX = 0;
                int dieY = 0;
                //获取滑动的距离
                Vector2 touchDelPos = Input.GetTouch(0).deltaPosition;
                if (Mathf.Abs(touchDelPos.x) > Mathf.Abs(touchDelPos.y))
                {
                    //滑动距离
                    if (touchDelPos.x > 10)
                    {
                        dieX = 1;
                    }
                    else
                    if (touchDelPos.x < -10)
                    {
                        dieX = -1;
                    }
                }
                else
                {
                    if (touchDelPos.y > 10)
                    {
                        dieY = 1;
                    }
                    else if (touchDelPos.y < -10)
                    {
                        dieY = -1;
                    }
                }
                MoveNum(dieX, dieY);
            }
        }
        
        //--------- PC端检测逻辑 ---------
        if (isMovingNum.Count == 0)
        {
            int dieX = 0;
            int dieY = 0;
            if (Input.GetKeyDown(KeyCode.A) || Input.GetKeyDown(KeyCode.LeftArrow))
            {
                dieX = -1;
            }
            else
            if (Input.GetKeyDown(KeyCode.D) || Input.GetKeyDown(KeyCode.RightArrow))
            {
                dieX = 1;
            }
            else
            if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow))
            {
                dieY = 1;
            }
            else
            if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.DownArrow))
            {
                dieY = -1;
            }
            MoveNum(dieX, dieY);
        }

        if (hasMove && isMovingNum.Count == 0)   //生成新的数字
        {
            CreateNun();
            hasMove = false;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (numbers[i, j] != null)
                    {
                        numbers[i, j].OneMove = false;
                    }
                }
            }
        }
    }
    #endregion

    #region 游戏逻辑
    /// <summary>
    /// 数字移动方法
    /// </summary>
    /// <param ></param>
    /// <param ></param>
    public void MoveNum(int directionX, int directionY)
    {
        if (directionX == 1)  //向右移动  
        {
            //首先将空格填满   最右侧列不需做判断
            for (int j = 0; j < 4; j++)
            {
                for (int i = 2; i >= 0; i--)
                {
                    if (numbers[i, j] != null)  //格子中有物体（数字），，调用移动方法
                    {
                        numbers[i, j].Move(directionX, directionY);
                    }
                }
            }
        }
        else

        //===========向左移动==================
        if (directionX == -1)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 1; i < 4; i++)
                {   //最左侧的一列 [0,0] [0,1] [0,2] [0,3]
                    if (numbers[i, j] != null)
                    {
                        numbers[i, j].Move(directionX, directionY);
                    }
                }
            }
        }
        else

        //===========向上移动==================
        if (directionY == 1)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 2; j >= 0; j--)
                {
                    if (numbers[i, j] != null)
                    {
                        numbers[i, j].Move(directionX, directionY);
                    }
                }
            }
        }
        else

        //===========向下移动==================
        if (directionY == -1)
        {
            for (int i = 3; i >= 0; i--)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (numbers[i, j] != null)  //有物体（数字）就移动
                    {
                        numbers[i, j].Move(directionX, directionY);
                    }
                }
            }
        }
    }


    /// <summary>
    /// 判断是否是空格的方法
    /// </summary>
    /// <param >数组索引X</param>
    /// <param >数组索引Y</param>
    /// <returns></returns>
    public bool isEmpty(int x, int y)
    {
        if (x < 0 || x > 3 || y < 0 || y > 3)
        {
            return false;
        }
        else if (numbers[x, y] != null)
        {
            return false;
        }
        return true;
    }

    /// <summary>
    /// 判断游戏是否结束
    /// </summary>
    /// <returns>返回true则游戏结束</returns>
    public bool isDead()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (numbers[i, j] == null)
                {
                    return false;
                }
            }
        }

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                if (numbers[i, j].value == numbers[i + 1, j].value)
                {
                    return false;
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (numbers[i, j].value == numbers[i, j + 1].value)
                {
                    return false;
                }
            }
        }
        return true;
    }

    #endregion
    
    /// <summary>
    /// 游戏结束
    /// </summary>
    /// <param >false:输,true:赢</param>
    public void ShowUIFinsh(bool isSuccess)
    {
        UIFinsh.SetActive(true);
        if (isSuccess)
        {
            UIFinsh.GetComponentInChildren<Text>().text = "游戏成功";
        }
        else
        {
            UIFinsh.GetComponentInChildren<Text>().text = "游戏失败";
        }
    }
}
```

### 4.2 Number 数字处理类

```
using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using UnityEngine;
using UnityEngine.UI;
using Vector3 = UnityEngine.Vector3;

public class Number : MonoBehaviour
{
    //在二维数组中的位置X，Y
    public int posX; 
    public int posY;

    private int offsetX = -620;      //显示偏移，Y，，，
    private int offsetY = -620;
    private int space = 420;         // 间距

    private bool isMoving = false;   //动画是否播放过的计数
    public int value;                //产生数字是几
    private bool toDestroy;          //判断数字是否销毁  
    public bool OneMove = false;     //标识数字是否合并过一次
 
    // Use this for initialization
    void Start()
    {
        // 80%成2的概率，更改本身的Sprite名字，以更换图片
        value = Random.value > 0.2f ? 2 : 4;
        this.GetComponent<Image>().sprite = LoadSprite();
        do
        {
            posX = Random.Range(0, 4);
            posY = Random.Range(0, 4);
        } while (Manager._isnstance.numbers[posX, posY] != null);

        transform.localPosition = GetLocalPos();
        // 存放数字本身到数组中，表示此位置有数字不能生成新的数字
        Manager._isnstance.numbers[posX, posY] = this;
        if (Manager._isnstance.isDead())
        {
            // 游戏失败
            Manager._isnstance.ShowUIFinsh(false);
        }
    }

    // Update is called once per frame
    void Update()
    {
        //播放一次动画
        if (!isMoving)
        {
            if (transform.localPosition != GetLocalPos())
            {
                isMoving = true;
                StartCoroutine(MoveAni());
            }
        }
    }

    // 移动动画
    IEnumerator MoveAni()
    {
        Debug.Log("移动动画...");
        float t = 0;
        for (int i = 0; i < 10; i++)
        {
            transform.localPosition = Vector3.Lerp(transform.localPosition, GetLocalPos(), t);
            t += 0.1f;
            yield return new WaitForEndOfFrame();
        }
        // 移动结束的回调
        MoveOver();
    }


    #region 游戏核心移动算法
    /// <summary>
    /// 核心，移动方法（有空格，有物体是否一样）
    /// </summary>
    public void Move(int directionX, int directionY)
    {
        //Debug.Log("测试");
        
        //==========向右移动==================  
        if (directionX == 1) 
        {
            int index = 1;  // 空格标志
            while (Manager._isnstance.isEmpty(posX+index,posY))
            {
                index++;
            }
            // 有空格的移动
            if (index>1)
            {
                
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {   // 保证不会重复添加物体（数字）到列表，
                    Manager._isnstance.isMovingNum.Add(this);
                }
                //移动一次，就生成两个数字的标志符
                Manager._isnstance.hasMove = true;
                //向空格位置移动
                Manager._isnstance.numbers[posX, posY] = null;
                posX = posX + index - 1;
                Manager._isnstance.numbers[posX, posY] = this;
            }
            //有相同数字的移动
            if (posX < 3 && value == Manager._isnstance.numbers[posX+1,posY].value &&
                !Manager._isnstance.numbers[posX+1,posY].OneMove)
            {
                // 只合并一次的标志
                Manager._isnstance.numbers[posX + 1, posY].OneMove = true;
                // 移动的标志，（生成新的物体（数字））
                Manager._isnstance.hasMove = true;
                // 动画播放的限定（有数字在列表中就不会重复播放第二次动画） 
                // 不会重复添加物体（数字）到列表，
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }
                // 碰到一样的数字，讲位置设为空 并销毁本身标识（true），
                // 再将其位置上的值变为2倍，（更换成新的数字）
                toDestroy = true;
                Manager._isnstance.numbers[posX, posY] = null;
                Manager._isnstance.numbers[posX + 1, posY].value *= 2;
                posX += 1;
            }
        }else

        //===========向左移动==================
        if (directionX == -1)
        {
            int index = 1;
            while (Manager._isnstance.isEmpty(posX - index, posY))
            {
                index++;
            }
            //有空格的移动
            if (index > 1)
            {
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                Manager._isnstance.numbers[posX, posY] = null;
                posX = posX - index + 1;
                Manager._isnstance.numbers[posX, posY] = this;
            }

            //碰到相同数字的移动
            if (posX > 0 && value == Manager._isnstance.numbers[posX - 1, posY].value && 
                !Manager._isnstance.numbers[posX - 1, posY].OneMove)
            {
                Manager._isnstance.numbers[posX - 1, posY].OneMove = true;
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                toDestroy = true;
                Manager._isnstance.numbers[posX, posY] = null;
                Manager._isnstance.numbers[posX - 1, posY].value *= 2;
                posX -= 1;
            }

        }else

        //===========向上移动==================
        if (directionY == 1)
        {
            int index = 1;   //空格标志
            while (Manager._isnstance.isEmpty(posX , posY + index))
            {
                index++;
            }
            //有空格的移动
            if (index > 1)
            {
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                Manager._isnstance.numbers[posX, posY] = null;
                posY = posY + index - 1;
                Manager._isnstance.numbers[posX, posY] = this;
            }
            //有相同位置的移动
            if (posY < 3 && value == Manager._isnstance.numbers[posX , posY + 1].value && !Manager._isnstance.numbers[posX, posY + 1].OneMove)
            {
                Manager._isnstance.numbers[posX , posY + 1].OneMove = true;
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                toDestroy = true;
                Manager._isnstance.numbers[posX, posY] = null;
                Manager._isnstance.numbers[posX , posY + 1].value *= 2;
                posY += 1;
            }

        }else

        //===========向下移动==================
        if (directionY == -1)
        {
            int index = 1;  //空格标志位
            while (Manager._isnstance.isEmpty(posX, posY - index))
            {
                index++;
            }
            //有空格的移动
            if (index > 1)
            {
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                Manager._isnstance.numbers[posX, posY] = null;
                posY = posY - index + 1;
                Manager._isnstance.numbers[posX, posY] = this;
            }
            //有相同数字的移动
            if (posY > 0 && value == Manager._isnstance.numbers[posX, posY - 1].value && !Manager._isnstance.numbers[posX, posY - 1].OneMove)
            {
                Manager._isnstance.numbers[posX, posY -1].OneMove = true;
                Manager._isnstance.hasMove = true;
                if (!Manager._isnstance.isMovingNum.Contains(this))
                {
                    Manager._isnstance.isMovingNum.Add(this);
                }

                toDestroy = true;
                Manager._isnstance.numbers[posX, posY] = null;
                Manager._isnstance.numbers[posX, posY - 1].value *= 2;
                posY -= 1;
                }
        }
    }

#endregion

    /// <summary>
    /// 动画结束，标志改为false
    /// </summary>
    public void MoveOver()
    {
        isMoving = false;
        //若碰到了相同的数字  销毁自己，和改变另一个图片（数字）
        if (toDestroy)   
        {
            Destroy(this.gameObject);
            value = Manager._isnstance.numbers[posX, posY].value;
            Manager._isnstance.numbers[posX, posY].GetComponent<Image>().sprite = LoadSprite();
            //游戏成功
            if (value == 4096)
            {
                Manager._isnstance.ShowUIFinsh(true);
            }
        }
        Manager._isnstance.isMovingNum.Remove(this);
    }

    Vector3 GetLocalPos()
    {
       return new Vector3(offsetX + posX * space, offsetY + posY * space, 0);
    }

    /// <summary>
    /// 根据数字加载对应图片
    /// </summary>
    /// <returns></returns>
    Sprite LoadSprite()
    {
        return Resources.Load<Sprite>(value.ToString());
    }
}
```

结语
--

本文从新建项目开始一步一步带你完成所有步骤，还在等什么呢？三连支持一下吧~

需要素材的小伙伴点击[链接下载](https://download.csdn.net/download/Czhenya/19801838)即可。没有积分的同学，关注我的 VX 公众号，回复 “2048” 即可。