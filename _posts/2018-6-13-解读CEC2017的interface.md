---
published: true
title: CEC2017 benchmark function调用接口
category: Algorithm
tags: 
  - 算法
layout: post
---

CEC2017 benchmark function可以从[这里](http://web.mysites.ntu.edu.sg/epnsugan/PublicSite/Shared%20Documents/Forms/AllItems.aspx?RootFolder=%2Fepnsugan%2FPublicSite%2FShared%20Documents%2FCEC-2017&View=%7bDAF31868-97D8-4779-AE49-9CEC4DC3F310%7d)下载。

导师最近给了个课题让我自己研究，跟智能优化算法相关的，必不可免的要用到最新的CEC2017 benchmark function,然而
笔者着实踩了很多坑，第一步编译都差点跪了。

# 坑一：abs

如果你下载了上面的CEC2017 benchmark function,并试着按照它的指示在matlab窗口运行`mex cec17_func.cpp -DWINDOWS`。

你会发现，编译根本不通过啊摔！！！！！而且错误提醒信息有几页啊摔！(′д｀ )…彡…彡

然后就会各种怀疑人生，是不是我下的matlab有问题啊，官方给的文件应该没问题才对啊，这个`cec17_func.cpp`这么长怎么debug啊？

后面我发现只是里面的一个函数调用出错了！什么鬼，官方文档都这么不正规吗？

解决办法：打开`cec17_func.cpp`，搜索`abs`，将里面的`abs`统统改成`fabs`，对浮点数求绝对值应该用`fabs`！

# 坑二：This function(F2) has been deleted

编译通过了，试着运行main看看？然后就会提示错误信息：`This function(F2) has been deleted.`，这又是什么？
matlab为什么会提示这样的信息？然后发现是`cec17_func.cpp`里把function2注释掉了，输出了这行信息...不知道
为什么要这么做，解决方法就是把那行代码注释掉并且把function2的注释去掉。

# 坑三：接口如何使用

其实只要知道这里的benchmark function就是用来求 fitness value的这一点再去阅读一下代码，就会很熟悉接口了。

让我们先来看看`PSO_func.m`和`main.m`是如何调用`cec17_func.cpp`的。

先看一下`main.m`的这一行：

`fhd=str2func('cec17_func');`

这里用了str2func()函数，fhd成为了`cec17_func`的handle，之后调用fhd的时候就是在调用`cec17_func`。

再来看`PSO_func`.

`e=feval(fhd,pos',varargin{:});`

这里用了一个feval函数，你只需要知道这里返回了当前pos的fitness value就行了，pos'是pos的转置矩阵，
所以pos'是一个D*NP(维度*种群大小)的矩阵，而varargin{:}是具体使用哪个benchmark function。
那么这个cpp和m的交互是如何实现的呢？具体请查阅`mex`命令的相关知识。

总结一下上面那段代码的含义：返回pos'的fitness value给e，varargin=1...29，代表着第varargin个benchmark function。

# 坑四：大规模运算

总算解决了，那么我们可以运行程序了，按照CEC2017的标准，种群大小为100，维度是10，30，100，迭代次数是维度*10000。
在我自己的电脑上跑10维的数据，每个函数跑50遍取均值，我算了一下时间一次实验大概要跑一天一夜...

然后我就去问老师要了一个实验室服务器的账号，远程控制服务器运算，睡觉起来看结果就好了。

