---
published: true
title: Modern Operating Systems chapter 6 notes Deadlock
category: Operating system
tags: 
  - Operating system
layout: post
---

# Overview

## Definition

>A set of processes is deadlocked if each process in the set is waiting for an event that only another process in the set can cause.

我们可以把resource分成preemtive的和non-preemtive的，如果resource是preemtive的，那么deadlock是不会发生的，只有non-preemtive的资源才可能发生deadlock。

而deadlock也可以分成不同的种类，其中最常见的就是resource deadlock。

## Conditions for resource deadlocks

Coffman等人在1971提出了资源死锁的四种必要条件:
1. Mutual exclusion。资源只能同时被一个process占有而不能被多个processes占有。
2. Hold-and-Wait. 进程正处于一种“已经拥有一定的资源但还在请求其它资源”的状态。
3. No-preemtive. 前面提到的，resource是non-preemtive的。
4. Circular wait. 两个或更多的processes处于某种回路。

## Deadlock Modeling

可以对resource和进程进行建模，如下图所示，可以很清晰的看出来是否有死锁发生（判断是否存在回路）。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/16.png)

正方形表示resource，圆形表示process。图(a)中process A占有R resource,图(b)中process B请求S resource，图(c)中发生了deadlock。

# Deadlock detection and recovery

其实前面还有个鸵鸟算法，英文名叫**ostrich algorithm**，就不提了。

这里要说的是死锁的检测和恢复，这种技术并不是用来避免死锁的发生，而是检测到它的发生之后让它发生然后采取行动恢复。

## Deadlock detection

对于one resource per type来说，检测很简单，判断是否有回路即可，对于multi-resource per type的话就麻烦一点。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/17.png)

左上角的E向量表示系统的全部资源数（包括已经分配的和未分配的），右上角的A向量表示未分配的资源数，左下角的矩阵表示
各个进程已经占有的资源数，右下角的矩阵表示各个进程的请求资源数。

接下来一步步接受资源释放资源即可，很简单。这样就能判断死锁是否会发生了。

## Deadlock recovery

有三种方式recovery：preemption/rollback/killing process

### Recovery through Preemption

这种方法其实就是人为的解除占用：Temporarily take a resource away from its current owner and give it to another process。
缺点是难以实现。

### Recovery through Rollback

**回滚**，系统了解到deadlock有可能发生，于是定期的设置**checkpoint**，process的状态被写进一个新文件里以便在之后发生死锁的时候回滚到之前的状态。

### Recovery through Killing process

通过杀死占有资源的进程来恢复，要么是杀死处于回路的进程，但是杀死回路之外的进程也是有可能的，原因是这样的进程也可能占用资源，一旦将这个资源释放，也有可能recovery。

另外还需要注意的一点是尽量选择那些可以被重新启动的进程，有些进程一旦被杀死就没办法启动了，可能会造成不良后果。

## Deadlock avoidance

前面的deadlock detection是检测到了，在发生之后进行recovery，而deadlock avoidance则是通过判断分配资源给process是否“safe”来避免进入deadlock。

### Resource Trajectories

书本上给出了一种directly、易于理解的图来帮助理解安全状态和不安全状态，如图所示。为了避免进入不安全状态，在t时刻，不能往上走了。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/18.png)

A state is said to be safe if there is some scheduling order in which every process can run to completion even if all of them suddenly request their maximum number of resources immediately.

请注意，不安全状态和死锁状态是有所不同的，处于不安全状态不一定会发生死锁，比如某个进程释放了资源，此时就进入了安全状态，安全状态则是能保证死锁不发生。

### The Banker's Algorithm

其实前面的deadlock detection里判断是否会发生死锁就已经用了银行家算法了，这个算法也挺简单的，就不赘述了。

## Deadlock prevention

虽然deadlock avoidance看起来有效，但实际上它是难以实现的，因为它需要实现知道process需要哪些资源，实际上是不可能的。
我们可以通过攻击deadlock的四种必要条件来prevent deadlock，只要这四个条件的任意之一不满足，死锁就不会发生。

### Attacking the Mutual-Exclusive Condition

让一个资源同时能被两个或多个Processes占用？听起来好像不太可能，但是在某些情况下是可以做到的，比如read data，一个data可以同时被多个Processes读取，但是write就不行。

### Attacking the Hold-and-Wait Condition

攻击持有等待条件，一种做法是：只有当某进程想使用资源并且有足够多的资源让它运行时才分配，否则不分配。有点像mutual exclusion里的atomic operation。但是和deadlock avoidance一样，这也需要事先知道进程所需要的资源
数，实际上是不可能的。并且，对于某些process来说，一次性把资源都给它使用是不现实的。

另一种实现方法是，在process请求资源前，需要把自己已经占有的资源先释放掉。

### Attacking the No-preemtive Condition

这个顾名思义，允许抢占式的资源分配。

### Attacking the Circular Wait Condition

一种实现方法是process只能占用单一的一种资源，如果它想占有第二种资源的话，需要先释放掉第一种资源，这种方法对于某些进程来说适用，有着特殊性。

另一种实现方法是提供一个全局的资源的序号，只能按照序号请求响应的资源，这样就不会Circular Wait了。