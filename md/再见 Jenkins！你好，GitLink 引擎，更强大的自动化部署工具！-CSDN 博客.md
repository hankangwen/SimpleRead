> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/FloraCHY/article/details/119926726)

#### 文章目录

*   [写在前面](#_1)
*   [一、准备工作](#_11)
*   *   [1.1 注册 GitLink 账号](#11_GitLink_12)
    *   [1.2 托管项目](#12__16)
    *   [1.3 新建项目管理引擎流水线](#13__23)
*   [二、开始构建流水线](#_32)
*   *   [2.1 进入图形流水线编辑页](#21__36)
    *   [2.2 添加 git clone 节点](#22_git_clone_46)
    *   [2.3 添加 shell 节点](#23_shell_55)
    *   [2.4 添加 allure html 节点](#24_allure_html_101)
    *   [2.5 添加新建 GitLink 疑修节点](#25_GitLink_109)
    *   [2.6 添加钉钉通知节点](#26__125)
    *   [2.7 设置任务触发器](#27__142)
    *   *   [2.7.1 第一类触发器 cron](#271_cron_151)
        *   [2.7.2 第二类触发器 GitLink](#272__GitLink_154)
*   [三、流水线示例](#_159)

写在前面
----

想要运行自动化测试，但是对于服务器知识了解过少，不足以支撑构建自动化测试项目怎么办？

想要运行自动化测试，但是没有可以服务器怎么办？

GitLink 引擎来帮你解决这些问题！

今天给大家推荐一款好用的 CI/CD 工具：GitLink 引擎，可以轻松实现一键构建自动化测试项目，让你的自动化测试运行无忧！

一、准备工作
------

### 1.1 注册 GitLink 账号

要使用 GitLink 引擎，我们需要注册一个 GitLink 账号，注册地址：https://gitlink.org.cn/register

### 1.2 托管项目

首先，我们需要准备一个自动化测试项目，将自动化测试项目上传到 [GitLink](https://www.gitlink.org.cn/) 或者 [Gitee](https://gitee.com/) 或者 [Github](https://github.com/) 上进行托管。

建议使用 GitLink 进行托管哦~

### 1.3 新建项目管理引擎流水线

GitLink 账号新建成功后，我们可以在 GitLink 新建一个项目，用来管理我们的流水线。

注意：假如是在 GitLink 托管自动化测试项目，如果需要直接使用该项目的引擎，需要将流水线保存在其他分支中，因为流水线的保存会更新代码库文件，以免影响自动化测试代码；

新建项目地址：https://www.gitlink.org.cn/projects/deposit/new （登录后可正常访问）

二、开始构建流水线
---------

引擎内部有很多官方节点以及社区节点，可以先了解一下各个节点的功能以及怎么使用。后续如果引擎这一套路程熟悉了，还可以自定义节点。

下面我简单介绍一下我使用过的节点。

### 2.1 进入图形流水线编辑页

1.  进入项目详情页，点击 “引擎”，进入引擎页面，点击 “图形流水线”  
    ![](https://img-blog.csdnimg.cn/af0e4a75ccd04586b35b54820e74fce7.png)
    
2.  选择流水线代码保存的分支（一般默认 master 分支）后，添加所需要的节点。  
    注意：必须有开始和结束节点。
    

### 2.2 添加 git clone 节点

需要注意如下几个参数：

*   用户名： 访问自动化测试私有仓库的用户名，仓库是公开的可以不填
*   密码： 访问自动化测试私有仓库的用密码，仓库是公开的可以不填
*   git 地址：自动化测试项目的 git 地址
*   标签、分支或 pr/mr：自动化测试项目的所在分支，一般都是默认 master  
    ![](https://img-blog.csdnimg.cn/5eac807250f74637ba887cba0cd33f5b.png)

### 2.3 添加 shell 节点

需要注意几个参数：

*   docker 镜像  
    可以手动输入所需的镜像，我这里用过 2 个镜像：
    
    *   mcr.microsoft.com/playwright/python:v1.38.0-focal：有 playwright 环境
    *   python:3.9-slim-buster：python 3.9 环境  
        ![](https://img-blog.csdnimg.cn/a72c3000ecef4979b26e9248547f6b78.png)
*   环境变量  
    我们需要将 git clone 节点，clone 下来的自动化测试项目路径，保存为环境变量，参考如下：  
    ![](https://img-blog.csdnimg.cn/880c5f41ea31429cbd4ba1fd058114e0.png)
    
*   脚本  
    这里需要输入运行自动化测试项目的命令。
    

可以参考我输入的命令：

```
# 这里是因为我当前使用的镜像没有安装jdk，所以我手动安装了一下
apt update
apt install -y openjdk-8-jdk-headless
# 由于我是自动化测试项目保存了allure的代码，需要给allure执行文件赋予执行权限。
cd $PROJECT/lib/allure-2.22.0/bin
chmod +x allure
# 切换当前目录到自动化测试项目所在目录
cd $PROJECT
# 我是使用pipenv管理依赖环境，所以需要安装pipenv
pip install pipenv
# 使用pipenv安装项目所需依赖，正常命令是pipenv install; 由于镜像使用的3.8，我使用的3.9，因此我需要使用如下命令
pipenv install --python 3.8 --skip-lock
# 在虚拟环境中安装playwright浏览器驱动
pipenv run playwright install
# 在虚拟环境中运行测试
pipenv run python run.py
```

假如你的自动化测试代码，没有封装单独的`run.py`文件，是通过 pytest 去运行测试的，那么命令参考如下：

```
# 一键安装项目所需依赖，项目所需依赖都保存在requirements.txt中
# 或者也可以pip单独一个个安装依赖包
pip install requirements.txt -r
pytest --alluredir=allure-results
```

### 2.4 添加 allure html 节点

注意：如果你的自动化测试代码运行完成后，已经生成了 allure html 测试报告，可以跳过这个节点；

注意：这里 “allure-results 路径” 需要输入自动化测试项目生成的 allure results 测试结果集的目录。git clone 节点会返回自动化测试项目的根路径，我们只需要拼接具体的 allure-results 所在路径即可。例如：`git_clone_0.git_path + "/outputs/report/allure_results"`。

这个节点会自动调用 allure 生成 allure html 测试报告，并将报告压缩成. zip 文件，返回. zip 文件路径（.zip 文件中含有一个. bat 文件，在 windows 环境下，可以不安装 allure，直接双击打开查看报告）。  
![](https://img-blog.csdnimg.cn/dbb337d602374563865803c24ce0afe5.png)

### 2.5 添加新建 GitLink 疑修节点

这里，我需要该节点的作用在于，将 allure html 报告的压缩包上传到仓库的疑修，获取疑修的链接，作为测试运行结果发送到钉钉。  
因为钉钉机器人不能直接发送压缩包文件，所以曲线救国，发送疑修链接，如果需要查看测试报告，可以点击疑修链接后，下载测试报告查看。

该节点有以下参数：

*   GitLink 平台域名：一般为：`https://gitlink.org.cn/`；
*   GitLink 仓库拥有者标识 / 仓库标识：可以在 GitLink 访问某个需要新增疑修的项目 > 代码库页面，参考格式：`floraachy/gitlink_test`；
*   GitLink 平台账号：登录 GitLink 平台的账号，需要通过密钥管理进行管理，防止暴露；
*   GitLink 平台密码：登录 GitLink 平台的密码，需要通过密钥管理进行管理，防止暴露；
*   疑修指派负责人 id: Gitlink 项目成员的 user_id， 不需要指派的情况下可以留空：`"[]"`；
*   疑修（Issue）标题：疑修的标题，例如：allure html 报告生成啦！/ 自动化测试完成了！可自定义；
*   疑修（Issue）内容：疑修内容，可自定义；
*   疑修（Issue）附件：这里可以上传 allure html 报告的压缩包，点击右侧参数 > allure_html 报告生成 > allure-report 压缩的 zip 包路径即可，一般情况下是这样的格式：`allure_html_report_0.allure_report_path` （不需要引号）；

![](https://img-blog.csdnimg.cn/6ea41edf72204589a8314e2d79a5ee2e.png)

### 2.6 添加钉钉通知节点

前提：首先我们需要在钉钉上配置一个钉钉机器人， 获取钉钉机器人的 webhook 地址，具体配置参考：[使用钉钉机器人发送消息至钉钉](https://blog.csdn.net/FloraCHY/article/details/130618777?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169761576816800182130645%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=169761576816800182130645&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-1-130618777-null-null.nonecase&utm_term=%E9%92%89%E9%92%89&spm=1018.2226.3001.4450)

我这里添加的钉钉节点，是发送 markdown 格式的钉钉消息。

需要注意几个参数：

*   展示内容：收到钉钉消息，首屏会话会透出的内容；
*   markdown 消息内容：消息的具体内容，markdown 格式；
*   提醒列表：需要艾特的用户 id 或者手机号；
*   是否艾特所有人；  
    ![](https://img-blog.csdnimg.cn/c71ba9c296384271969fca19be6b44f9.png)

最后，我们添加一个结束节点，整个流程就串起来了。

![](https://img-blog.csdnimg.cn/59e2521c8ce548c3b434eaf60a5e2ba5.png)

### 2.7 设置任务触发器

我们知道 jenkins 里面也是有触发器的，可以设置每周或者每天什么时间点，自动运行流水线。  
或者检测到当前代码仓库有指定事件就自动触发流水线运行。

GitLink 引擎也有这个功能， 提供了 2 类触发器：cron, GitLink。

注意：任务触发器需要添加在开始节点之前。  
![](https://img-blog.csdnimg.cn/03bdec75b9e143c8afd632112042eba5.png)

#### 2.7.1 第一类触发器 cron

这个添加完成后，看具体的说明就可以了，挺简单的。  
![](https://img-blog.csdnimg.cn/25ae29799a944196bd176f6f6018def0.png)

#### 2.7.2 第二类触发器 GitLink

这个触发器是检测当前仓库是否有这三类事件触发：推送代码 / 合并请求 / 创建标签，一旦这 3 类事件发生，就会自动触发流水线的运行。

三、流水线示例
-------

注意：我这个流水线跟上述讲解的有细微差别。因为有些我是已经在自动化测试代码里面实现了，所以对应节点我就忽略了。  
![](https://img-blog.csdnimg.cn/20df5672e0db476e9c29d1a3bd4d8c5f.png)

代码流水线参考：

```
version: 2
name: UI_playwright_图形流水线
description: ""
global:
  concurrent: 1
  cache: path
trigger:
  type: cron
  schedule: 0 0 1 ? * FRI
workflow:
  - ref: git_clone_0
    name: git clone
    task: git_clone@1.2.9
    input:
      remote_url: '"https://gitlink.org.cn/floraachy/uiautotest_playwright.git"'
      ref: '"refs/heads/master"'
      commit_id: '""'
      depth: 1
    needs:
      - start
  - ref: shell_0
    name: shell
    image: mcr.microsoft.com/playwright/python:v1.38.0-focal
    env:
      PROJECT: git_clone_0.git_path
    script:
      - apt update
      - apt install -y openjdk-8-jdk-headless
      - apt install -y unzip
      - cd $PROJECT/lib/allure-2.22.0/bin
      - chmod +x allure
      - ls -l
      - cd $PROJECT
      - pip install pipenv
      - pipenv install --python 3.8 --skip-lock
      - pipenv run playwright install
      - pipenv run python run.py
    needs:
      - git_clone_0
  - ref: end
    name: 结束
    task: end
    needs:
      - dingtalk_notice_markdown_0
  - ref: start
    name: 开始
    task: start
  - ref: dingtalk_notice_markdown_0
    name: 钉钉通知-markdown
    task: dingtalk_notice_markdown@1.0.2
    input:
      boot_webhook_url: ((dingbot.webhook_url))
      secret: ((dingbot.secret))
      msg_title: '"UI自动化测试已完成!"'
      msg_text: extract_txt_0.result + "\n复制链接打开查看详细测试报告：" +
        new_gitlink_issue_0.issue_link
      at_user_ids: '"[]"'
      at_mobiles: '"[]"'
    needs:
      - new_gitlink_issue_0
  - ref: extract_txt_0
    name: 文本内容提取
    task: floraachy/extract_txt@2.0
    input:
      file: git_clone_0.git_path + "/outputs/report/test_result.txt"
    needs:
      - shell_0
  - ref: new_gitlink_issue_0
    name: 新建GitLink疑修Issue
    task: floraachy/new_gitlink_issue@1.0.1
    input:
      host: '"https://gitlink.org.cn"'
      project_url: '"floraachy/uiautotest_playwright"'
      username: ((gitlink.username))
      password: ((gitlink.password))
      issue_assign: '"[87611]"'
      issue_title: '"UI自动化测试报告"'
      issue_content: '""'
      issue_attach: git_clone_0.git_path + "/outputs/report/autotest_report.zip"
    needs:
      - extract_txt_0
```