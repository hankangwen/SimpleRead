> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/C3S03IOHZ0qIyRTG3lIO0Q)

随着经济全球化的趋势，游戏也逐渐变得不分国界。在进行游戏内文本的国际化 / 本土化多语言切换时往往需要制作组耗费大量精力。

**Unity 中文课堂 Jay 老师**带来了免费教程《「Unity 插件教程」国际化插件 Localization 小白也能简单实现多语言切换》，带大家利用插件进行多语言文本的全局管理，达到快速切换文本语言的效果。

[视频详情](javascript:;)

点击**阅读原文**，即可免费学习完整视频版教程！

**课代表笔记**  

**插件安装**

1. 打开 Unity 上方工具栏中的 Window =>Package Manager 打开 Unity 插件包管理界面  

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P47917w24CNhRLXL7g7JsQRYQZlia7v5EGJRQJsheZTnibdVJmtoAM6ThnDkQ/640?wx_fmt=png)

2. 点击右上角 Package 选项中 Unity Registry，然后在右侧搜索栏中搜索 Localization

3. 选择 Localization 插件并点击安装

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791ibm0l6lBYXEAW9qHKcYr99E9sEEVzooonjPsdXsB80e0sDhAXwLgmtw/640?wx_fmt=png)

**创建 Localization Settings**

1. 在 Unity 编辑器的顶部栏找到并点击 Edit => Project Settings

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791Tctned93jN4EBXoGXIZHQjyjaFwTVRpLpBTArqMibcETicibzqo3D7ic7g/640?wx_fmt=png)

2. 打开 Project Settings 页面之后选择到 Localization (如果 Localization 插件安装好了就会显示，反之没有安装好就不会显示该选项页面)

3. 点击创建按钮后，选择好 Localization Settings 的路径保存即可（如果之前已经创建直接选择已有 Settings 配置即可）

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791Ns89z1Wb8LhJbel9fjiaAvd4nZz2PzictJOejnrnSOiaLJnfVnfibBzgibw/640?wx_fmt=png)

4. 创建成功之后点击 Locale Generator 按钮生成

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791z4oD0sJfDr0zqaiaF1OQS3X63tbyj7doKOZehzLrjOqBNz7R1r6BibZQ/640?wx_fmt=png)

5. 勾选需要本地化的语言，选择好对应路径保存即可

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791BMSXlUEdfWCsZBsQefLYqEyHH8jdEvH5R2ePeMPXbVprcWWb5r8yrg/640?wx_fmt=png)

6. 是否需要更换默认语言

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791bueWibbOgGh2icsag74uOfsZRfzKhUkw7wU4nnuLIibvwl7BVGl8pm2Eg/640?wx_fmt=png)

**创建 Localization Tables**

1. 找到并点击 Window => Asset Management => Localization Tables

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791EQpCd9XRvSTAANAicVOUGhibFOK219q2Jollu4ygRjDRvjpzovcZ3rzA/640?wx_fmt=png)

2. 点击 New Table Collection 按钮创建新的本地化文本对应表

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791Gh40kJ2JaY0y59jIJk8ia0fiagBUMcmPa3bhuHGS6XNagUIe9T7DK1Rg/640?wx_fmt=png)

3. 选择 String Table Collection 类型  
4. 命名好 Table 的名称，点击 Create 选择对应路径创建即可

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791Zy5vlBib2k7vzv8jDsiar03I5m0Ie7BQtiaFsjkaty8MSttekkbf73cWQ/640?wx_fmt=png)

5. 创建好 Table 后，我们可以直接创建对应的文本实体 (也可以在绑定 Localization string event 到对应文本时创建)

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791MCLdntjOnbmEzHy40A2t5SWKkeeHQQTELVib2DPt1vYg4plZxcxvanw/640?wx_fmt=png)

**绑定 Localization string event 到对应文本**

1. 在场景中找需要多语言化的文本组对象

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791IVnibbdRibgVFf0pVMZk2sMCziaySfGlqiarE1ia9hnXmqtzI7qzx9liawPA/640?wx_fmt=png)

2. 在该文本对象中添加 Localize String Event 组件

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P47911XricWW4XVU22JtoDtcm79g2fgOmkSciaeZmlFylVEqLamfob7826n7Q/640?wx_fmt=png)

3. 点击 String Reference 将创建好的 Localize Entry 关联到该文本（如果没有提前创建好 Entry 则点击下方的 Add Table Entry 进行新建即可）

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791iaYT5foTUsajYZpz1S8Puhq2fE7OquJjpr0BiaKeejrJPDN4p9rh7XOA/640?wx_fmt=png)

4. 在关联 Entry 界面搜索 Key 并选择对应 Entry 进行绑定

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791hWPoTy6omiaMKT6ne0m9WDzIEX504tCcria0J6GbaMX5ETewTEUibZBNA/640?wx_fmt=png)

5. 此时点击开始项目，已经可以通过选择右上角的下拉框来切换对应文本的语言了

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791zWhqXibVh8e7B9awxibqIkB6AyJD8YasfJ0GEhmne5ef7wjJdWJqXQpw/640?wx_fmt=png)

**编辑 Localization 切换语言脚本**

在上述步骤完成后，已经可以在项目测试时使用编辑器内置的 Localization 下拉框中进行文本语言切换。接下来需要编写 Localization 切换语言脚本来完成在游戏进行时使用 settings 的语言选择下拉框进行文本语言切换。

1. 先写一段下拉框语言切换方法

```
using UnityEngine;
using UnityEngine.UI;
using System;
using UnityEngine.Localization.Settings;

public class UIScripts : MonoBehaviour
{
    public Dropdown languageDropdown;
    public void selectLanguage(){
        StartCoroutine(changeLocales(languageDropdown.value));
    }
    public void selectLanguage(){
        //将下拉框当前选中选项的下标作为参数设置到LocalizationSettings的SelectedLocale达到实现语言切换的效果
        LocalizationSettings.SelectedLocale = LocalizationSettings.AvailableLocales.Locales[languageDropdown.value];
    }
}
```

2. 将写好的 selectLanguage 方法挂载到 Language 下拉框的 OnChange 事件上

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791N0HN0hFeEdHAnc91ZRzrbzFCuKdK6iaBSzVQA38EicxRKIn6STBWsO5g/640?wx_fmt=png)

3. 编写并挂载完脚本后便可以实现项目进行时实现语言切换功能。

**全局化控制文本多语言内容**

当项目体量过大时候，难免会遇到海量的文本需要进行多语言化，此时直接在 Localization Table 里面是难以管理的，因此需要将 Table 以 CSV 的格式导出在外部与项目分离使用 Excel 进行管理。

1. 以 CSV 格式导出 Localization Table  

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791mUsV2jrQZnpoCfQIWBicInhQicbUHRvFJkmqac4x3mX0hZnSbZWoNlfA/640?wx_fmt=png)

2. 在导出 CSV 文件后，可以使用 Excel 工具直接进行文本的全局管理

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791gAfD772ZY1sox7PF2jRS51FYp0cAOXfiaPQdwpJicZpWniamIGpgN30cQ/640?wx_fmt=png)

3. 在 CSV 文件管理编辑后需要使用 UTF-8 的编码格式进行保存，否则在 CSV 再次导入回项目是中文字符会显示为乱码

![](https://mmbiz.qpic.cn/sz_mmbiz_png/wqMMAm9XjfOHOvlXzFpxeQH1Fp7P4791gNiaEudmk7tyAon7J0cOgf1KnDqCChsKbMOAa8a8zmIge7hac6CwoiaQ/640?wx_fmt=png)

4. 最后以相同的方式再次将 CSV 格式的文件导入回 Localization Table 就可以正常使用了。

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xep6bwprVYLicSVI20OASsSBUAteKA1pjOt7XebPFGH0pKllY1sKbxyBfnWDPTbu26VusPwkeRcLcw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

以上就是教程《「Unity 插件教程」国际化插件 Localization 小白也能简单实现多语言切换》的部分内容分享，完整内容请直接点击**阅读原文**到 **Unity 中文课堂**观看。

![](https://mmbiz.qpic.cn/mmbiz_png/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGia3ibXvfribSG3BEumwiakOoXOmvbw1a7icDGWF8wMoicDZqMko9kichBLEYug/640?wx_fmt=png)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYEqXHeRtyzJvT56ibf00TSHFlABcj2BeP47P6Zv8RJIMiblzibV7AYmobkIRgnOj0sXtI2Ghtfm522Mg/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247551389&idx=1&sn=af01cb627f4ccb13819f3e647b4764ce&chksm=c1860a19f6f1830f23c7e5ca0a5d679a4acb3e4f5e934789b593f433a38360588454306cb85c&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFhicnUTmPvVTnuSk3RX0WO8rRC09HiaDjNgDDOiaWF5Xicj9VNEjYmRvFY9gaAXYmVGXdR5wMyicibKN2w/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247547473&idx=1&sn=b2a1cf21323497825bc52a73deda633c&chksm=c18639d5f6f1b0c3ee538da0a5fbb48716478ea807da448e00df080b41fd71d00216930189fe&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFhicnUTmPvVTnuSk3RX0WO81J2nFn1wT01Se1llQQrPpDqw5DlP7PPr00oPB1xWfNKSNOmDHTicJfQ/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247548526&idx=1&sn=3ea688bbb03a1d1d5326182127faf271&chksm=c1863deaf6f1b4fcab36ab81ffbd2e0a6c3f99f121f50258e93c94b22bf7b914f2b983fcc917&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYHvITEfU45s2QOToV65ygiatAx2O90rk2qy430vFDwTeA2nzYHeaNTrBMtRRyibSHNgYvouQCC7UHyg/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247551758&idx=1&sn=36d8999840bcf6d4c2bbce399ec72359&chksm=c186088af6f1819cd7ed87591c7532654d472e0fb14357c6ec85c91be7f2a008df2e2e9bea08&scene=21#wechat_redirect)

[![](https://mmbiz.qpic.cn/sz_mmbiz_png/NYLZoOxGjYFhicnUTmPvVTnuSk3RX0WO8h4q4GuKCTMLTp9EzCCsrQ6s6ibLdyQaAXIkootlEiaLe6jlWCBjvoLfQ/640?wx_fmt=png)](http://mp.weixin.qq.com/s?__biz=MzkyMTM5Mjg3NQ==&mid=2247539782&idx=1&sn=8fb062017695d7063dcb50ad3dfb9134&chksm=c1865fc2f6f1d6d4e99fc3529b8d9097400a4489ad38c0c4d0ddcf3c62b1ba9186fd1d455d12&scene=21#wechat_redirect)

**长按关注**

**Unity 官方微信**

第一时间了解 Unity 引擎动向，学习进阶开发技能

![](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xfsun6CMe09NXZkcm0GiaWH5X4CPfZTL3Qr1sx7pQSy6M4wpTibnlGgsZCauTnDicQiaSAsB4RhXza2bw/640?wx_fmt=gif)

 点击 “阅读原文”，前往课程主页 

![图片](https://mmbiz.qpic.cn/mmbiz_gif/YIXoZTpc5xd9brdr3oibU9ib5GvKQ3NyGiak1T8bOLMtfRms9jViblv5tWzrm1ndtPKsj9A6fzH8G5p3gg9helEc1g/640?wx_fmt=gif)