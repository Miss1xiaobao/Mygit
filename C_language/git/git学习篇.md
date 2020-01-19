### git学习篇

<span  style="color: #ff3d00; ">参考资源：</span> 
    
[廖雪峰官网](https://www.liaoxuefeng.com/wiki/896043488029600/898732864121440)
>https://www.liaoxuefeng.com/wiki/896043488029600/898732864121440

[书](https://git-scm.com/book/zh/v2)
>https://git-scm.com/book/zh/v2


####  一、git命令

```c
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@example.com

git init    初始化git仓库
git clone git@github.com:Miss1xiaobao/Mygit.git   克隆一个本地库(自动设置本地 master 分支跟踪克隆的远程仓库的 master 分支)
git remote add origin git@github.com:Miss1xiaobao/Mygit.git    添加远程仓库

git add readme    开始跟踪readme文件（本地git）、将文件放在暂存区
git commit -m "1"   提交（本地git）到仓库

git fetch origin develop  从远程仓库origin中拉取到本地仓库（不合并）
git pull                  (有一个分支设置为跟踪一个远程分支)抓取 + 尝试合并 
git push origin develop   推送到远程仓库（名为origin， develop分支下的）

git branch develop       创建一个分支
git checkout develop     分支切换（切换到develop分支）
git checkout -b develop  新建分支develop并且切换到develop分支
git merge develop       （此时处于master分支）将develop分支合并到master分支
git branch -d work2      删除work2分支
git checkout -b develop origin/develop  新建一个develop分支，切换到该分支，上游分支是origin下的develop分支
git branch -u origin/master   设置当前本地分支跟踪远程master分支


git reset HEAD readme      取消暂存
git checkout -- readme     撤销之前到修改
git commit --amend         提交完了才发现漏掉了几个文件没有添加，或者提交信息写错了


git log                    查看提交历史
git status                 检查工作空间文件状态、分支状态、
git remote -v              远程仓库简写、对应的URL
git remote show origin     查看远程仓库
git show                   标签信息与对应的提交信息
git branch --merged        查看其他分支已经合并到当前分支
git branch --no-merged     查看所有包含未合并工作的分支
git branch -vv             列出本地分支更多的信息



git rm     删除文件
git remote rename origin new_origin    远程仓库重命名为new_origin
git remote rm origin                   移除origin的远程仓库


```
#### 二、
1、版本控制？ 分布式版本控制？ 集中式版本控制？   
2、Linux内核维护  ；Linus Torvalds     
3、文件3种状态：已提交（committed）、已修改（modified）和已暂存（staged）、未跟踪  
4、Git 项目的三个工作区域的概念：Git 仓库、工作目录以及暂存区域。   
5、git config  ---- Git配置
> 1、/etc/gitconfig如果使用带有--system选项的git config时，它会从此文件读取配置变量。

>2、~/.gitconfig或~/.config/git/config文件：只针对当前用户。可以传递--global选项让Git读取此文件。

>3、当前使用仓库的Git目录中的config文件（就是.git/config）：针对该仓库。

6、基于 master 分支的紧急问题分支 work1 work2 
> master----------master---------work1      
>                   |      
>                   |-----------work2------work2
      
>**一次典型合并中所用到的三个快照**：
    
> git merge work2 将work2分支合并到master分支（或work1分支）    
> 解决冲突（如果有冲突）    
> 删除work2分支 

7、遇到冲突时的分支合并
>如果你在两个不同的分支中，对同一个文件的同一个部分进行了不同的修改，Git 就没法干净的合并它们。
>
>git status ----查看那些因包含合并冲突而处于未合并（unmerged）状态的文件。    
>

8、快进（fast-forward）
> 由于当前 master 分支所指向的提交是你当前提交（有关 hotfix 的提交）的直接上游，所以 Git 只是简单的将指针向前移动。 换句话说，当你试图合并两个分支时，如果顺着一个分支走下去能够到达另一个分支，那么 Git 在合并两者的时候，只会简单的将指针向前推进（指针右移），因为这种情况下的合并操作没有需要解决的分歧——这就叫做 “快进（fast-forward）”。

9、跟踪分支、上游分支。
>跟踪分支，本地


#### debug

Git 用以计算校验和的机制叫做 SHA-1 散列（hash，哈希）