> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=Mzk0OTIyOTYwNg==&mid=2247483906&idx=1&sn=9e9171a41980c7c4b5f56a23f85bb1d9&chksm=c35ac34bf42d4a5d7233754846906c97085530c193aaa0d75a8f8ed8c014cd095cc165b9d4fb&token=9567962&lang=zh_CN#rd)

#### **1、概述**

**Docker** 是一个开源的应用容器引擎，让开发者可以打包他们的应用以及依赖包到一个可移植的容器中, 然后发布到任何流行的 Linux 机器或 Windows 机器上, 也可以实现虚拟化, 容器是完全使用沙箱机制, 相互之间不会有任何接口

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUGW8MdicGrlj1NlMx10MN77htibv2hGzNQYNWQkRZu6dgxgyLIRCekBSQz0qibQMLNntHKfTvOPB6BsA/640?wx_fmt=png)

docker 容器的优势：更高效的利用系统资源；更快速的启动时间；一致的运行环境；持续支付和部署；更轻松的迁移。

文档链接：https://docs.docker.com/engine/install/centos/

镜像链接：https://hub.docker.com/

**2、网络拓扑**

Docker 可以为在容器创建隔离的网络环境，在隔离的网络环境下，容器具有完全独立的网络栈，与宿主机隔离，也可以使容器共享主机或者其他容器的网络命名空间，基本可以满足开发者在各种场景下的需要。

按 docker 官方的说法，docker 容器的网络有五种模式：

- bridge：docker 默认的网络模式，为容器创建独立的网络命名空间，容器具有独立的网卡等所有单独的网络栈，是最常用的使用方式。

- host：直接使用容器宿主机的网络命名空间。

- none：为容器创建独立网络命名空间，但不为它做任何网络配置，容器中只有 lo，用户可以在此基础上，对容器网络做任意定制。

- 其他容器：与 host 模式类似，只是容器将与指定的容器共享网络命名空间。

- 用户自定义：docker 1.9 版本以后新增的特性，允许容器使用第三方的网络实现或者创建单独的 bridge 网络，提供网络隔离能力，可以用于集成 calico、weave、openvswitch 等第三方厂商的网络实现。

这些网络模式在相互网络通信方面的对比如下所：

<table><tbody><tr><td width="123" valign="top">模式&nbsp;</td><td width="123" valign="top">是否支持多主机</td><td width="123" valign="top">南北通信机制</td><td width="123" valign="top">东西通信机制</td></tr><tr><td width="123" valign="top">bridge&nbsp;</td><td width="123" valign="top">否</td><td width="123" valign="top">宿主主机端口绑定</td><td width="123" valign="top">通过 Linux bridge</td></tr><tr><td width="123" valign="top">host&nbsp;</td><td width="123" valign="top">是</td><td width="123" valign="top">按宿主网络通信</td><td width="123" valign="top">按宿主网络通信</td></tr><tr><td width="123" valign="top">none&nbsp;</td><td width="123" valign="top">否</td><td width="123" valign="top">无法通信</td><td width="123" valign="top">只能用 link 通信</td></tr><tr><td width="123" valign="top">其他容器</td><td width="123" valign="top">否</td><td width="123" valign="top">宿主主机端口绑定</td><td width="123" valign="top">通过 link 通信</td></tr><tr><td width="123" valign="top">用户自定义</td><td width="123" valign="top">按网络实现走</td><td width="123" valign="top">按网络实现走</td><td width="123" valign="top">按网络实现走</td></tr></tbody></table>

**3、卸载**  

Docker 的旧版本被称为 Docker 或 Docker -engine。如果已经安装了它们，请卸载它们以及相关的依赖项。

```
$ sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine

```

**4、安装依赖插件**

在新主机上第一次安装 Docker Engine 之前，需要设置 Docker 存储库。之后，你可以从存储库中安装和更新 Docker。

设置存储库，安装 yum-utils 包 (它提供 yum-config-manager 实用程序) 并设置稳定存储库。

```
$ sudo yum install -y yum-utils
$ sudo yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo

```

**5、Docker 镜像安装**

安装最新版本的 Docker Engine 和 containerd，或者进入下一步安装特定版本:

```
$ sudo yum install docker-ce docker-ce-cli containerd.io

```

启动：

```
$ sudo systemctl start docker

```

查看版本：

```
$ docker -v

```

查看安装镜像：

```
$ docker images

```

查看所有的容器：  

```
$ docker ps -a

```

随机启动：

```
$ systemctl enable docker

```

**6、镜像加速**

因大多镜像是国外的，顾可以添加阿里云镜像加速，可以快点下载对应的镜像。Linux 针对 Docker 客户端版本大于 1.10.0 的用户, 您可以通过修改 daemon 配置文件 / etc/docker/daemon.json 来使用加速器

```
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://29ojwllp.mirror.aliyuncs.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker

```

**7、新版 Docker 安装**

Docker 目前支持的 64 位 CentOS 版本：CentOS 7，CentOS 8

使用官方安装脚本自动安装方法，安装命令如下：

```
curl -fsSL https://get.docker.com | bash -s docker mirror Aliyun

```

或者也可以使用国内 daocloud 一键安装命令：

```
curl -sSL https://get.daocloud.io/docker | s

```

然后启动 docker：

```
$ sudo systemctl start docker

```