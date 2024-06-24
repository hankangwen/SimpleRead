> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [mp.weixin.qq.com](https://mp.weixin.qq.com/s/CAzN2gAscsBmQ1Cytb2WHw)

**1、简述**

GitLab 是一个功能强大的 Git 仓库管理工具，支持代码审查、持续集成 / 持续部署 (CI/CD) 等多种功能。使用 Docker 安装 GitLab 可以简化部署过程，确保环境一致性。本文将介绍如何在 Docker 中安装和配置 GitLab。

**2、准备环境**

gitlab 要求至少 4G 的内存:

```
[root@localhost ~]# free -m
              total        used        free      shared  buff/cache   available
Mem:           5786        4201         147          29        1438        1265
Swap:             0           0           0

```

准备好 Docker 容器：

> Docker：基本安装和配置
> 
> 拾荒的小海螺，公众号：拾荒的小海螺 [Docker：基本安装和配置](https://mp.weixin.qq.com/s?__biz=Mzk0OTIyOTYwNg==&mid=2247483906&idx=1&sn=9e9171a41980c7c4b5f56a23f85bb1d9&chksm=c35ac34bf42d4a5d7233754846906c97085530c193aaa0d75a8f8ed8c014cd095cc165b9d4fb&token=9567962&lang=zh_CN#rd)

**3、拉取 gitlab 容器**

直接拉取最新的 gitlab 版本

```
docker pull gitlab/gitlab-ce

```

创建一个目录来存放 GitLab 的配置、日志和数据文件。例如：

```
mkdir -p /data/gitlab/config /data/gitlab/logs /data/gitlab/data

```

使用以下命令启动 GitLab 容器：

```
$ sudo docker run -d  -p 8443:443 -p 8090:8090 -p 8022:22 --name gitlab --restart always 
-v /data/gitlab/config:/etc/gitlab 
-v /data/gitlab/logs:/var/log/gitlab 
-v /data/gitlab/data:/var/opt/gitlab gitlab/gitlab-ce

```

-d：后台运行

 -p：将容器内部端口向外映射

 --name：命名容器名称

 -v：将容器内数据文件夹或者日志、配置等文件夹挂载到宿主机指定目录

**4、修改端口映射**  

在 / data/gitlab/config 路径中找到 gitlab.rb

```
[root@localhost config]# ls
gitlab.rb            initial_root_password  ssh_host_ecdsa_key.pub  ssh_host_ed25519_key.pub  ssh_host_rsa_key.pub
gitlab-secrets.json  ssh_host_ecdsa_key     ssh_host_ed25519_key    ssh_host_rsa_key          trusted-certs

```

在 gitlab.rb 配置中添加：

```
# 配置http协议所使用的访问地址,不加端口号默认为80
external_url 'http://192.168.220.144:8090'
# 配置ssh协议所使用的访问地址和端口
gitlab_rails['gitlab_ssh_host'] = '192.168.220.144'
# 此端口是run时22端口映射的222端口
gitlab_rails['gitlab_shell_ssh_port'] = 8022

```

然后重启 gitlab：

```
docker restart gitlab

```

然后在浏览器上访问：http://192.168.220.144:8090

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUEEFsicpxFiahGnUXOyZI2CeibIicN5ND8pPPpHBx4w0SNtMdlTT9rdt9icFiamb2QFzGkNeLTmhEf0iatlw/640?wx_fmt=png&from=appmsg)

出现这个页面不是失败，Gitlab 启动比较慢，要多等一会儿。

**5、修改密码**  

1、root 默认密码放在 initial_root_password 文件底下，通过以下指令查看

```
docker exec -it gitlab grep 'Password:' /etc/gitlab/initial_root_password
find / -name initial_root_password
cat /data/gitlab/config/initial_root_password 

```

2、修改默认的密码

首先进入 gitlab 控制台：

```
docker exec -it gitlab /bin/bash

```

接着进入指定的 gitlab-rails 控制台：

```
gitlab-rails console -e production

```

这一步可能等待比较久，多等一下等进入输入控制台

按步骤一步一步执行：

```
user =User.find(1)                                 //第一步
user.password ='123456?'                  //第二步
user.password_confirmation ='123456?'            //第三步
user.send_only_admin_changed_your_password_notification!  //第四步
user.save!                          //第五步

```

```
[root@localhost config]# docker exec -it gitlab /bin/bash
root@8e97133ab2de:/# gitlab-rails console -e production
--------------------------------------------------------------------------------
 Ruby:         ruby 2.7.5p203 (2021-11-24 revision f69aeb8314) [x86_64-linux]
 GitLab:       14.6.1 (661d663ab2b) FOSS
 GitLab Shell: 13.22.1
 PostgreSQL:   12.7
--------------------------------------------------------------------------------
Loading production environment (Rails 6.1.4.1)
irb(main):001:0> user =User.find(1)
=> #<User id:1 @root>
irb(main):002:0> user.password ='123456?'
=> "123456?"
irb(main):003:0> user.password_confirmation ='123456?'
=> "123456?"
irb(main):004:0> user.send_only_admin_changed_your_password_notification!
=> true
irb(main):005:0> user.save!
=> true

```

然后通过 exit 退出，再重启 gitlab。  

**6、备份和恢复**

GitLab 提供了简单的备份机制。可以通过以下命令创建备份：

```
docker exec -t gitlab gitlab-backup create

```

要恢复 GitLab 实例，请将备份文件复制到 /data/gitlab/data/backups 目录，然后运行以下命令：

```
docker exec -t gitlab gitlab-backup restore BACKUP=your_backup_filename

```

请将 your_backup_filename 替换为实际的备份文件名。

**7、优化启动速度**

因  docker 版本的 gitlab 启动会自动启动 prometheus|grafana|alertmanager 和一系列 exporter， 非常占用资源，且导致启动比较慢，因此我们可以通过修改 /etc/gitlab/gitlab.rb 来关闭该功能。

默认启动包含如下内容：

```
# ps -ef|grep -E 'prome|exporter|alert|graf'
git          280     272  0 10:09 ?        00:00:00 /opt/gitlab/embedded/bin/gitlab-workhorse -listenNetwork unix -listenUmask 0 -listenAddr /var/opt/gitlab/gitlab-workhorse/sockets/socket -authBackend http://localhost:8080 -authSocket /var/opt/gitlab/gitlab-rails/sockets/gitlab.socket -documentRoot /opt/gitlab/embedded/service/gitlab-rails/public -pprofListenAddr  -prometheusListenAddr localhost:9229 -secretPath /opt/gitlab/embedded/service/gitlab-rails/.gitlab_workhorse_secret -logFormat json -config config.toml
root         350      23  0 10:09 ?        00:00:00 runsv redis-exporter
root         351      23  0 10:09 ?        00:00:00 runsv gitlab-exporter
root         352      23  0 10:09 ?        00:00:00 runsv grafana
root         353      23  0 10:09 ?        00:00:00 runsv postgres-exporter
root         355      23  0 10:09 ?        00:00:00 runsv alertmanager
root         356      23  0 10:09 ?        00:00:00 runsv prometheus
root         357     351  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/gitlab-exporter
root         358     350  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/redis-exporter
root         359     352  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/grafana
gitlab-+     360     352  0 10:09 ?        00:00:00 /opt/gitlab/embedded/bin/grafana-server -config /var/opt/gitlab/grafana/grafana.ini
gitlab-+     361     350  0 10:09 ?        00:00:00 /opt/gitlab/embedded/bin/redis_exporter --web.listen-address=localhost:9121 --redis.addr=unix:///var/opt/gitlab/redis/redis.socket
root         362     353  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/postgres-exporter
git          363     351  0 10:09 ?        00:00:07 /opt/gitlab/embedded/bin/ruby /opt/gitlab/embedded/bin/gitlab-exporter web -c /var/opt/gitlab/gitlab-exporter/gitlab-exporter.yml
gitlab-+     365     353  0 10:09 ?        00:00:01 /opt/gitlab/embedded/bin/postgres_exporter --web.listen-address=localhost:9187 --extend.query-path=/var/opt/gitlab/postgres-exporter/queries.yaml
root         366     355  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/alertmanager
root         368     356  0 10:09 ?        00:00:00 svlogd -tt /var/log/gitlab/prometheus
gitlab-+     369     356  1 10:09 ?        00:00:12 /opt/gitlab/embedded/bin/prometheus --web.listen-address=localhost:9090 --storage.tsdb.path=/var/opt/gitlab/prometheus/data --config.file=/var/opt/gitlab/prometheus/prometheus.yml
gitlab-+     370     355  0 10:09 ?        00:00:00 /opt/gitlab/embedded/bin/alertmanager --web.listen-address=localhost:9093 --storage.path=/var/opt/gitlab/alertmanager/data --config.file=/var/opt/gitlab/alertmanager/alertmanager.yml
root         618     615  0 10:11 ?        00:00:00 tail --follow=name --retry /var/log/gitlab/redis-exporter/current /var/log/gitlab/redis-exporter/state /var/log/gitlab/postgresql/current /var/log/gitlab/postgresql/state /var/log/gitlab/sidekiq/current /var/log/gitlab/sidekiq/state /var/log/gitlab/gitlab-exporter/current /var/log/gitlab/gitlab-exporter/state /var/log/gitlab/gitlab-rails/gitlab-rails-db-migrate-2022-02-10-01-12-10.log /var/log/gitlab/gitlab-rails/exceptions_json.log /var/log/gitlab/gitlab-rails/application.log /var/log/gitlab/gitlab-rails/web_exporter.log /var/log/gitlab/gitlab-rails/application_json.log /var/log/gitlab/gitlab-rails/sidekiq_client.log /var/log/gitlab/gitlab-rails/audit_json.log /var/log/gitlab/gitlab-rails/api_json.log /var/log/gitlab/gitlab-rails/auth.log /var/log/gitlab/gitlab-rails/production.log /var/log/gitlab/gitlab-rails/service_measurement.log /var/log/gitlab/gitlab-rails/graphql_json.log /var/log/gitlab/gitlab-rails/production_json.log /var/log/gitlab/gitlab-rails/git_json.log /var/log/gitlab/gitlab-rails/grpc.log /var/log/gitlab/logrotate/current /var/log/gitlab/grafana/current /var/log/gitlab/grafana/state /var/log/gitlab/postgres-exporter/current /var/log/gitlab/postgres-exporter/state /var/log/gitlab/nginx/gitlab_access.log /var/log/gitlab/nginx/gitlab_error.log /var/log/gitlab/nginx/current /var/log/gitlab/nginx/access.log /var/log/gitlab/nginx/error.log /var/log/gitlab/redis/current /var/log/gitlab/redis/state /var/log/gitlab/alertmanager/current /var/log/gitlab/alertmanager/state /var/log/gitlab/gitlab-workhorse/current /var/log/gitlab/gitlab-workhorse/state /var/log/gitlab/prometheus/current /var/log/gitlab/prometheus/state /var/log/gitlab/sshd/current /var/log/gitlab/gitaly/current /var/log/gitlab/gitaly/gitaly_ruby_json.log /var/log/gitlab/gitaly/state /var/log/gitlab/puma/puma_stderr.log /var/log/gitlab/puma/current /var/log/gitlab/puma/puma_stdout.log /var/log/gitlab/puma/state
root        2385    1071  0 10:26 pts/0    00:00:00 grep --color=auto -E prome|exporter|alert|graf

```

通过修改 gitlab.rb 配置文件：  

```
alertmanager['enable'] = false
node_exporter['enable'] = false
redis_exporter['enable'] = false
postgres_exporter['enable'] = false
gitlab_exporter['enable'] = false
prometheus_monitoring['enable'] = false
grafana['enable'] = false

```

然后重启启动 gitlab，再查看

```
[root@localhost config]# ps -ef|grep -E 'prome|exporter|alert|graf'
chrony    96781  96777  0 07:46 ?        00:00:03 /opt/gitlab/embedded/bin/gitlab-workhorse -listenNetwork unix -listenUmask 0 -listenAddr /var/opt/gitlab/gitlab-workhorse/sockets/socket -authBackend http://localhost:8080 -authSocket /var/opt/gitlab/gitlab-rails/sockets/gitlab.socket -documentRoot /opt/gitlab/embedded/service/gitlab-rails/public -pprofListenAddr  -prometheusListenAddr localhost:9229 -secretPath /opt/gitlab/embedded/service/gitlab-rails/.gitlab_workhorse_secret -logFormat json -config config.toml
root      97762  97761  0 07:55 ?        00:00:00 tail --follow=name --retry /var/log/gitlab/sshd/current /var/log/gitlab/gitlab-rails/gitlab-rails-db-migrate-2022-10-28-09-37-05.log /var/log/gitlab/gitlab-rails/production.log /var/log/gitlab/gitlab-rails/application.log /var/log/gitlab/gitlab-rails/application_json.log /var/log/gitlab/gitlab-rails/grpc.log /var/log/gitlab/gitlab-rails/service_measurement.log /var/log/gitlab/gitlab-rails/auth.log /var/log/gitlab/gitlab-rails/sidekiq_client.log /var/log/gitlab/gitlab-rails/production_json.log /var/log/gitlab/gitlab-rails/api_json.log /var/log/gitlab/gitlab-rails/gitlab-rails-db-migrate-2022-10-28-09-47-20.log /var/log/gitlab/gitlab-rails/exceptions_json.log /var/log/gitlab/logrotate/current /var/log/gitlab/redis/current /var/log/gitlab/gitaly/gitaly_ruby_json.log /var/log/gitlab/gitaly/current /var/log/gitlab/postgresql/current /var/log/gitlab/puma/puma_stdout.log /var/log/gitlab/puma/puma_stderr.log /var/log/gitlab/puma/current /var/log/gitlab/sidekiq/current /var/log/gitlab/gitlab-workhorse/current /var/log/gitlab/nginx/current /var/log/gitlab/nginx/error.log /var/log/gitlab/nginx/gitlab_access.log /var/log/gitlab/nginx/gitlab_error.log /var/log/gitlab/nginx/access.log /var/log/gitlab/gitlab-exporter/current /var/log/gitlab/redis-exporter/current /var/log/gitlab/prometheus/current /var/log/gitlab/alertmanager/current /var/log/gitlab/postgres-exporter/current /var/log/gitlab/grafana/current
root      98228  92777  0 07:58 pts/1    00:00:00 grep --color=auto -E prome|exporter|alert|graf

```

重新访问：http://192.168.220.144:8090，出现以下界面代表你安装成功：

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUEEFsicpxFiahGnUXOyZI2CeibHC04RUW2Qne2jS6LMIC5ic89B9tJ4LE2gf14Krjp91atfsuJk6l3XyQ/640?wx_fmt=png&from=appmsg)

**8、配置 ssh keys**

在本地打开 git bash 客户端输入 ssh-keygen 生成公钥和私钥

```
ssh-keygen -t rsa -C 'xxx@xxx.com'

```

```
lsk1@LAPTOP-0SIF32SL MINGW64 /e/Project/Java_Project/eureka
$ ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/c/Users/wlsk1/.ssh/id_rsa):   //首次回车
Enter passphrase (empty for no passphrase):             //可以输入密码
Enter same passphrase again:                    //再次确认密码
Your identification has been saved in /c/Users/wlsk1/.ssh/id_rsa.
Your public key has been saved in /c/Users/wlsk1/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:sGfrvxU09TPXBfyVhMEyN4k/j/a7WSaaPywPSp3gClk wlsk1@LAPTOP-0SIF32SL
The key's randomart image is:
+---[RSA 3072]----+
|            ooBoo|
|           + B.o+|
|      .     B .+=|
|       o   . +  =|
|      . E . . +  |
|       = o o = . |
|      o . o *.o o|
|       o o o.+o+o|
|        o.+.o+o=o|

```

在本地目录 c/Users/wlsk1/.ssh/id_rsa.pub. 下查找 id_rsa.pub 打开并复制到

![](https://mmbiz.qpic.cn/mmbiz_png/1zA0SMrjkUEEFsicpxFiahGnUXOyZI2Ceib0RTJtibdicqibl6ItiaT7u5iann6daROhYI1RfXzlxKZvFdx5wQSko6WpBg/640?wx_fmt=png&from=appmsg)

接着自己通过 Git 客户端直接拉取代码就行。

**9、总结**

通过 Docker 安装 GitLab 不仅简化了部署过程，还提供了灵活性和可移植性。希望本文能帮助你顺利完成 GitLab 的安装和配置。如果有任何问题，欢迎留言讨论！