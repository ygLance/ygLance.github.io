---
published: true
title: Modern Operating Systems chapter 2 notes Scheduling
category: Operating system
tags: 
  - Operating system
layout: post
---

什么是Scheduling? 为什么我们需要Scheduling？

When two or more processes/threads are simultaneously in the ready state, if only one CPU is available, a choice has to be made which process to run next. 
做出这个choice的被称为**Scheduler**，这个过程叫**Scheduling**。Scheduler使用的算法叫**scheduling algorithm**。

随着计算机硬件的飞速发展（摩尔定律），CPU的资源不再是*scarce*的了，scheduling也就显得没那么重要了，举个简单的例子，如果一个计算机的CPU运算速度无限快，根本就没有必要调度，随便运行哪个程序都可以，
因为都是很快就运行完了，还设置复杂的调度算法？何必呢。

但对于networked servers来说，scheduling又显得重要起来，因为servers通常会接收来自不同用户的requests，这时就需要scheduler发挥作用了。

根据使用CPU时间的长短我们可以把process分成两类，一类叫**compute-bound**,或者叫**CPU-bound**,另一类叫**I/O-bound**。如下图所示，CPU-bound的process会经常使用CPU的资源，而I/O-bound的process不经常使用CPU。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/6.png)

随着现在CPU的运算速度越来越快，CPU使用的时间越来越短，很多时候我们都是处于I/O-bound的状态，所以我们更关注IO-bound。


# When to Schedule

1. When a new process is created. 比如Unix系统中使用了`fork()`指令，child process的状态和parent process完全相同，都处于ready的状态，那么先运行child还是parent呢？
2. When a process exits。当一个process运行完之后我们必须决定下一个运行的process。
3. When a process blocks on I/O。当一个process因为I/O阻塞了，我们必须决定下一个运行的process。
4. When an I/O interrupts occurs。一个程序从waiting for the I/O到可以运行了，这时候需要scheduler决定是否运行这个刚准备就绪的process。

# Scheduling Algorithms

## Categories

我们可以以两个标准来对scheduling algorithms进行分类。

### Environments

根据process的运行环境，分成不同的类。

1. Batch。 批处理系统
2. Interactive。交互系统
3. Real time。实时系统

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/7.png)

### preemptive& nonpreemptive

还可以把算法分为抢占式和非抢占式。

>A nonpreemptive scheduling algorithm picks a process to run and then just lets it run until it blocks (either on I/O or
waiting for another process) or voluntarily releases the CPU.
In contrast, a preemptive scheduling algorithm picks a process and lets it run
for a maximum of some fixed time.

简单点说就是，nonpreemptive的算法在某个进程运行完之前是不会进行调度的，而preemtive的算法在某个进程运行完之后可能安排其它进程运行。

## Scheduling in Batch Systems

### First-Come, First-Served

这个算法的另一个名字叫FIFO，也就是队列。
* non-preemptive
* not optimal

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/8.png)

挺简单的，没什么好说的，注意一下waiting time的计算。

优点是非常简单，易于实现。

缺点是：
1. Waiting time depends on arrival order.
2. Potentially long wait for jobs that arrive later.
3. Convoy effect:Short jobs stuck waiting for long jobs.(reduces utilization of I/O devices)

什么是Convoy effect呢？ Convoy effect有两种表现形式：
1. All I/O devices idle even when the system contains lots of I/O jobs.
2. CPU idle when even if system contains CPU bound jobs.

### SJF

Shortest Job First algoirithm has two versions. One version is non-preemtive and one is preemtive.

SJF有一个特殊的地方，它是有前提的，它的requirement是：the elapse time needs to know in advance.

如果所有的jobs都是同时到达的，那么SJF是optimal的，

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/9.png)

Preemtive SJF is also called Shortest Remaining Time Next(SRTN).

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/10.png)

SJF的优点是：
1. Provably optimal for minimizing average wait time。
2. Helps keep I/O devices busy.

缺点：
1. Not pratical:Cannot predict future CPU burst time.
2. Starvation:Long jobs may never be scheduled.

SJF还有一个特点是它不支持优先级调度，因为它自己规定了优先级(时间短的优先)。

## Scheduling in Interactive System

对于Interactive system来说，算法总是preemtive的。

###  Round-Robin Scheduling

RR其实就是preemtive的FCFS，它假设所有processes有着相同的优先级，并且视processes为一个queue。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/11.png)

这里对于time quantum有一个需要注意的地方：time quantum的长短如何选定？

如果time quantum太大的话，虽然减少了context switch的发生次数，但是会让它变成FCFS，有着糟糕的响应时间。
如果太短的话，增加了context switch的发生的次数，并且没有有效利用CPU,花了太多时间在switch上而不是利用CPU。

下面再来整理一下RR的优缺点。
优点：
1. Fair allocation of CPU across jobs,no starvation.
2. Low average waiting time when job lengths vary.
3. Shortest jobs finish relatively quickly.
4. Turnaround time typically larger than SRTF but better response time.

缺点：
1. Poor average waiting time with similar job lengths.
2. performance depends on length of time-slice.
3. Do not consider priority.
4. High overhead due to frequent context switches.

### Priority Scheduling

其实也就是带着优先级的FCFS。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/12.png)

优点：
1. Static priorities work well for real time systems
2. Dynamic priorities work well for general workloads.

缺点：
1. Low priority jobs can starve
2. May not give the best AWT

### Multi-Level Queue

Used in scenarios where the processes can be classified into groups based on property like process type,CPU time,IO access,memory size,etc.
Split the Ready Queue in serveral queues, processes assigned to one queue permanently.

把各种不同优先级的processes分成不同的queue,each queue with its own scheduling algorithm.

### Multi-Level Feedback Queue

将一份job分成不同的level，这个level没运行完就到下个level。和muti-level queue有所不同。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/13.png)
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/14.png)

### Lottery Scheduling

基于概率的调度，Give processes lottery tickets. At scheduling time, a lottery ticket is chosen at random, and the process holding that ticket gets that resource.

意思就是拿到更多票的运行的概率会高。

优点是：
1. simple
2. highly responsive
3. can support cooperation between processes
3. easy to support priority and propotion requirement



