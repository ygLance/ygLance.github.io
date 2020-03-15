---
published: true
title: Modern Operating System semaphore专题
category: Operating system
tags: 
  - Operating system
layout: post
---

弄个semaphores相关的专题吧。通过各种案例解析。

# The Readers and Writers Problem

读者写者问题翻译过来是这样的：对于某个数据库来说，读者可以同时多人读，但是读和写不能同时进行。

对于这个问题如何分析？既然读和写要分开，那么我们肯定需要一个semaphores来控制互斥，读者可以同时多人读，那么我们需要一个整数来控制读者的人数，
为了对这个整数进行保护，那么我们需要一个semaphores来控制对整数的互斥。
于是，程序就变成了这样。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/os/15.png)

# Exercise1

有一个阅览室，共有100个座位，读者进入时必须先在一张登记表上登记，该表为每一座位列一表目，包括座号和读者姓名等，读者离开时要消掉登记的信息，试用PV操作描述读者进程之间的同步关系。 

PV操作和信号量其实是一个东西，这里就用down和up来做了。

对问题分析，登记表需要控制互斥，设置semaphores mutex。
一共有一百个座位，设置一个semaphore empty=100控制人数，并且设置一个full=0控制同步。

	typedef int semaphore;
	semaphore mutex=1;
	semaphore empty=100;
	semaphore full=0;

	void in(){
		while(true){
			down(&empty);
			down(&mutex);
			blankIn();
			up(&mutex);
			up(&full);
		}
	}

	void out(){
		while(true){
			down(&full);
			down(&mutex);
			blankOut();
			up(&mutex);
			up(&empty);
		}
	}
	
# bathroom problem

Suppose that a university wants to show off how politically correct it is by applying the
U.S. Supreme Court’s ‘‘Separate but equal is inherently unequal’’ doctrine to gender as
well as race, ending its long-standing practice of gender-segregated bathrooms on campus. However, as a concession to tradition, it decrees that when a woman is in a bathroom, other women may enter, but no men, and vice versa. A sign with a sliding
marker on the door of each bathroom indicates which of three possible states it is currently in:  
* Empty
* Women present
* Men present
In some programming language you like, write the following procedures:
woman wants to enter, man wants to enter, woman leaves, man leaves. You
may use whatever counters and synchronization techniques you like.

分析：这里对男生的人数和女生人数都有要求，所以要设置两个整数mn和wn,紧接着要设置保护这两个数的mutex:mn_mutex,wn_mutex，最后要设置对bathroom的mutex。一共五个信号量。

	Solution: 
	typedef int semaphore;
	semaphore mn=0;//number of men
	semaphore wn=0;//number of women
	semaphore mn_mutex=1;//protect mn
	semaphore wn_mutex=1;//protect wn
	semaphore br=1;//control access to bathroom

	void woman_wants_to_enter(){
	while(1){
		down(&wn_mutex);
		wn=wn+1;
		if(wn==1) down(&br);
		up(&wn_mutex);
		}
	}
	void man_wants_to_enter(){
		while(1){
			down(&mn_mutex);
			mn=mn+1;
			if(mn==1) down(&br);
			up(&mn_mutex);
		}
	}
	void woman_leaves(){
		down(&wn_mutex);
		wn_mutex=wn_mutex-1;
		if(wn_mutex==0) up(&br);
		up(&wn_mutex);
	}
	void man_leaves(){
		down(&mn_mutex);
		mn_mutex=mn_mutex-1;
		if(mn_mutex==0) up(&br);
		up(&mn_mutex);
	}

	
	