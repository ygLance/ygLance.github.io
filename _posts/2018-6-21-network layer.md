---
published: true
title: 计算机网络Chapter 4 network layer
category: computer networking
tags: 
  - computer networking
layout: post
---

进入network layer的学习。

# Overview

network layer主要干了一个什么工作？说起来很简单，就是将分组从发送主机到接收主机，为此，需要两种重要的网络层功能：
1. Forwarding。所谓的forwarding也就是转发，就是指当一个分组到达路由器的一条输出链路时，路由器必须将该分组移动到适当的输出链路，转发是一个本地**动作**。
2. Routing。Routing也就是路由选择，是指采用一定的**routing algorithm**，决定分组采取的路径。

而每台路由器都有一张forwarding table，这个forwarding table是由routing algorithm决定的。

网络层提供的服务被称为**best-effort service**，尽力而为服务，也就是它是unreliable的，

# VC和datagram network

Internet其实是一个**datagram network**，与datagram network相对应的还有另一种计算机网络叫**virtual-circuit**，虚电路提供连接服务，而datagram network提供无连接服务。

在虚电路网络中，该网络的路由器必须为进行中的连接维持和**connection state information**，而数据报网络则无需建立任何虚电路，路由器也不维护任何虚电路的状态信息。

在虚电路中有3个明显不同的阶段：VC setup,data transfer,VC teardown.

在datagram network里，路由器使用longest prefix matching rule最长前缀匹配原则。

# Forwarding

我们现在来关注网络层的转发功能，分组到达一台路由器后如何进行传输？经历了一个怎样的过程？

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/20.png)

如图所示，这是路由器的体系结构，它包含了四个部分：
1. 输入端口。
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/21.png)
输入端口由三部分组成，从左到右依次分别代表了物理层，链路层，网络层。
其中网络层的部分完成了查找功能，在这里就决定了分组的输出端口。

2. 交换结构。将输入端口和输出端口相连接。它有三种实现方式：
经内存交换、经总线交换、经互连网络交换。

3. 输出端口。

4. 路由选择处理器。路由器选择处理器执行路由选择协议，维护路由选择表并为路由器计算转发表。

这些转发功能有时总称为**router forwarding plane**。

# Datagram

现在我们来谈谈Internet中的datagram和编址。

## 数据报格式

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/22.png)

如图是IPv4的数据报格式，它的首部长度为20bytes.
值得一提的是TTL字段，一旦TTL字段减为0，该数据包必须丢弃。
协议字段指示了数据应该交给哪个特定的运输层协议，例如值为6表明数据部分要交给TCP，为17则交给UDP。

## IP datagram fragmentation

IP数据报分片，为什么IP数据报需要分片呢？因为一个链路层frame能承载的最大数据量有限，叫MTU（Maximum Transmission Unit),所以我们需要把数据报分成片。
datagram里提供了三个field来支持分片服务：ID,flag,offset。 ID用来标识这些分片是否属于同一片，即属于同一片的分片ID应该一样，offset用来确定分片是否丢失，flag用来确定是否为最后一个片，如果是最后一个片,flag=0。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/23.png)
其中offset应该是字节数/8.

## Subnet

有时候哦我们会看到ip地址这样写：a.b.c.0/24，这是什么意思呢？这其实是一个network mask，最右边的24定义了子网的地址，也就是说a.b.c.0定义了一个子网，而子网内部用最后的8 bits来标识内部的hosts。

因特网的地址分配策略被称为Classless Interdomain Routing,CIDR,无类别域间路由选择，与之相对的是classful addressing。classful addressing的网络部分被限制为8、16、24.而CIDR的x是无限制的。
一个子网能用的IP地址是2^(32-x)-2.这里减去的包括0.0.0.0和255.255.255.255两个，0.0.0.0是本主机源地址，255.255.255.255是IP的广播地址。

## DHCP

DHCP是**动态主机配置协议**，允许主机自动获取一个IP地址。它也是一个plug-and-play protocol即插即用协议。
用DHCP分配IP地址的过程是：
1. DHCP discover.需要分配IP地址的主机通过广播地址发送DHCP发送discover报文。
2. DHCP offer. DHCP服务器收到一个discover报文后仍然是应用IP广播地址255.255.255.255向客户作作出响应。
3. DHCP request。新到达的客户从一个或多个服务器提供中选择一个并发送一个request message进行响应。
4. DHCP ACK。最后服务器用DHCP ACK报文进行响应。
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/24.png)

## NAT

NAT全称是**Network Address Translation**，NAT能够使一台路由器对于外部世界来说像一个具有单一IP地址的单一设备，NAT使路由器对外界隐藏了家庭网络的细节。
如下图是一个IP地址转换过程，10.0.0.1和10.0.0.2对外界来说都是128.119.40.186主机。
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/25.png)

## Protocol

UPnp是一种允许主机发现并配置邻近NAT的协议。

ICMP被用来沟通主机和路由器，最典型的用途是差错报告。

# Routing Algorithm

## Link State 算法

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/26.png)
很简单的算法。

## Distance-Vector 算法

注意一下这个动态规划递推公式：
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/27.png)

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/computernetworking/28.png)

## Hierarchical Routing

层次路由选择，为什么需要层次路由选择？基于两个原因：
1. Scale。随着路由器数据变得很大，路由选择信息的计算通信等开销将变得不可实现。
2. Autonomous。有些公司要求按照自己的意愿运行路由器。






