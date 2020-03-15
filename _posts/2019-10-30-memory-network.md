---
published: true
title: 对话系统论文笔记三：memory network
category: Dialogue System
tags: 
  - DL
  - DS
  - paper reading
layout: post
---

2019.10.29 更新 Memory Networks

2019.10.31 更新 End-To-End Memory Networks

# Memory Networks

## 总结

更详细的总结可以看[这一篇](http://www.shuang0420.com/2017/12/04/%E8%AE%BA%E6%96%87%E7%AC%94%E8%AE%B0%20-%20Memory%20Networks/)，这里只做简单的概括以便回忆。

作者认为RNN网络不能很好的保存长期记忆，所以提出了memory network，memory network是一个框架，包含了4个重要的组件： **I** **G** **O** **R** 

- **I** :input feature map,将输入映射为一个特征向量
- **G** :根据新的输入更新memories，举个例子，最简单的**G**可以定义成只存放当前的memory，完全不更新以前的memories
- **O** :给定输入和memory,在特征空间里产生输出
- **R** :将输出转化为自然语言

这里的memory network并不是`end-to-end`的，而是`pipeline`式的，即先得到特征向量，再得到与其最相关的$k$个memories，再得到其特征向量，最后得到自然语言。在中间求其最相关的$k$个memories时，用的是$arg max$，其梯度是断掉的，文章用了`margin ranking loss`来得到整个模型的loss，进而用`SGD`优化模型。

# End-To-End Memory Networks

## 总结

上一篇总结有提到，最初的memory network并不是`end-to-end`的，而是`pipeline`式的，原因就在于其模型在得到与`query`最相关的$k$个memories时，用的是$argmax$，所以整个模型的参数并不能一次性的反向传播及更新，而是分成一个一个module,先更新一个module的参数再更新下一个module的参数。而这篇文章就利用了`attention`，将`query`和memories做`attention`直接得到输出的特征向量。值得一提的是，这里的memory network可以是`multi-layers`式的，文章介绍了两种方式实现多层memory network，详情见文章。

# Task-Oriented Conversation Generation Using Heterogeneous Memory Networks

## 总结