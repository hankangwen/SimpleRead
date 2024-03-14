> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.jianshu.com](https://www.jianshu.com/p/493b81544f80)

[参考资料](https://link.jianshu.com?t=https%3A%2F%2Fcoding.net%2Fhelp%2Fdoc%2Fgit%2Fgit-lfs.html)

Git LFS 是 Github 开发的一个 Git 的扩展，用于实现 Git 对大文件的支持

![](http://upload-images.jianshu.io/upload_images/1059995-670f795346b86292) git-lfs

### 使用目的

在游戏开发过程中, 设计资源占用了很大一部分空间. 像 png,psd 等文件是二进制 (blob) 的, 体积也很庞大.  
但 git 的 diff/patch 等是基于文件行的. 对于二进制文件来说. git 需要存储每次 commit 的改动.  
每次当二进制文件修改, 发生变化的时候. 都会产生额外的提交量. 导致 clone 和 pull 的数据量大增. 在线仓库的体积也会迅速增长.

![](http://upload-images.jianshu.io/upload_images/1059995-c9ddfd907277e8df.png) git-grow

LFS(Large File Storage) 就是为了解决这一问题而产生的工具.  
它将你所标记的大文件保存至另外的仓库, 而在主仓库仅保留其轻量级指针.  
那么在你检出版本时, 根据指针的变化情况下更新对应的大文件. 而不是在本地保存所有版本的大文件

![](http://upload-images.jianshu.io/upload_images/1059995-7e78b1cc5ceb6c1f.png) store

### 安装

> 注意：安装 Git LFS 需要 Git 的版本不低于 1.8.5

#### _Linux_

1.  `curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash`  
    `
2.  `sudo apt-get install git-lfs`
3.  `git lfs install`

#### _Mac_

1.  安装 HomeBrew `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
2.  `brew install git-lfs`
3.  `git lfs install`

#### _Windows_

1.  下载安装 [windows installer](https://link.jianshu.com?t=https%3A%2F%2Fgithub.com%2Fgithub%2Fgit-lfs%2Freleases)
2.  运行 windows installer
3.  在命令行执行 `git lfs install`

### 使用

1.  执行 `git lfs install` 开启 lfs 功能
2.  使用 `git lfs track` 命令进行大文件追踪 例如`git lfs track "*.png"` 追踪所有后缀为 png 的文件
3.  使用 `git lfs track` 查看现有的文件追踪模式
4.  提交代码需要将`gitattributes`文件提交至仓库. 它保存了文件的追踪记录
5.  提交后运行`git lfs ls-files` 可以显示当前跟踪的文件列表
6.  将代码 push 到远程仓库后，LFS 跟踪的文件会以『Git LFS』的形式显示:
7.  clone 时 使用'git clone' 或 `git lfs clone`均可