> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.jianshu.com](https://www.jianshu.com/p/f8faa62213f7) ![](http://upload-images.jianshu.io/upload_images/16535515-21d910de2d84fbc0.png) image.png

🔥

[mongodb 云数据库](https://links.jianshu.com/go?to=https%3A%2F%2Fcloud.mongodb.com%2F)

🌟

[点击这里查看 mongodb 本地数据库安装](https://www.jianshu.com/p/93835487fd2f)

#### 使用步骤：

`小白一枚，正在学习egg和mongoose，希望有大佬指点迷津🙏 ～`

👌 **1. 首先你要先注册一个账号**；  
🏠 **2. 建立你的数据库（这里也有收费的，当然比免费的好）**

*   然后选择最后一个免费的  
    
    ![](http://upload-images.jianshu.io/upload_images/16535515-3e5c137f06a62904.png) image.png ![](http://upload-images.jianshu.io/upload_images/16535515-aeacfdc31f399b25.png) image.png 🇨🇳 **3. 选择服务地区，这里很多都是国外的，随便找个免费的就行了（只是针对初学者，个人感觉速度还行。如果想要更好的建议花钱或者使用 [阿里云 -- 云数据库 MongoDB 版](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.aliyun.com%2Fproduct%2Fmongodb%3Fspm%3D5176.21213303.778269.3.47f43edakSZGUG%26scm%3D20140722.S_card%40%40%25E5%258D%25A1%25E7%2589%2587%40%40125._.ID_card%40%40%25E5%258D%25A1%25E7%2589%2587%40%40125-RL_mongodb-OR_ser-V_2-P0_0) ）**  
    ![](http://upload-images.jianshu.io/upload_images/16535515-580adc3abc0edd5e.png) image.png 🚶 **4. 添加数据库用户，用来确定数据库的访问权限**
    
*   设置用户名和密码，然后添加用户  
    
    ![](http://upload-images.jianshu.io/upload_images/16535515-91ef89cd379f0177.png) image.png ![](http://upload-images.jianshu.io/upload_images/16535515-ec75a373d7bd15dc.png) image.png 👉 **5. 添加 IP 地址，用来确定都哪些 IP 可以访问到你的数据库（毕竟一个用户也能多端连接，因此又加了一层 IP 条件的限制）**
    
*   选择允许任意 IP 访问（0.0.0.0/0）  
    
    ![](http://upload-images.jianshu.io/upload_images/16535515-7f24f9e3d8c3a5d0.png) image.png ![](http://upload-images.jianshu.io/upload_images/16535515-49481dc4d1d464a5.png) image.png 🔗 **6. 连接你的 [集群](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.zhihu.com%2Fquestion%2F20004877%2Fanswer%2F393868688)**
    
*   选择你要连接的方式，并通过此连接方式对数据库进行修改（这里推荐大家用 [MongoDB Compass 可视化工具](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.mongodb.com%2Ftry%2Fdownload%2Fcompass)，方便你查看和管理数据）
    
*   复制生成的连接地址，并把 `<password>` 替换成你创建用户的那个密码
    
*   打开你下载的 [MongoDB Compass 可视化工具](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.mongodb.com%2Ftry%2Fdownload%2Fcompass)，然后把刚才复制的，粘贴上去，点击连接
    
*   连接成功，默认会有 `admin和local`目录（接下来你的项目创建表，以及添加删除数据，都可以在这个工具中看到）
    

![](http://upload-images.jianshu.io/upload_images/16535515-d97614b8bbeed1a5.png) image.png

![](http://upload-images.jianshu.io/upload_images/16535515-1e13c35ed1867df5.png) image.png

![](http://upload-images.jianshu.io/upload_images/16535515-2a04809aff50400a.png) image.png

![](http://upload-images.jianshu.io/upload_images/16535515-7c805f1cc4765a92.png) image.png

![](http://upload-images.jianshu.io/upload_images/16535515-ef8dd8f6bbb72681.png) image.png

![](http://upload-images.jianshu.io/upload_images/16535515-63b5d46e57d604df.png) image.png