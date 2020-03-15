---
published: true
title: 《Evolutionary Computation》读书笔记（一）
category: Algorithm
tags: 
  - 算法
  - Evolutionary Algorithm
layout: post
---

从最简单的进化系统开始研究：EV。

对于一个进化系统来说，它的初始条件有哪些？这些初始条件怎样的影响了结果？这就是我们需要考虑的问题。那么，影响一个系统的因素有哪些呢？
1. 种群初始值。是随机初始值吗？初始种群时给定的种子（seed）大小？种群数量？
2. 选择的parents数量m。如何选择parents?
3. 选择的children数量n。如何选择children?
4. mutation function。高斯分布？
5. 子代间竞争？子代和父母竞争？全体一起竞争？
6. fitness landscape。变量的数量？线性？非线性？
7. exploitation和exploration的权衡。 2018/4/12
8. 基因的多少（也就是目标函数的维度）。

上面是我自己总结的影响一个系统的因素，也许未来还会继续添加，要想研究一个系统，我们就必须先解决上面的问题。

对于EV来说，它是一个非常简单的进化系统，

	EV：
	1. 均匀的随机生成m个初始个体。
	2. 每次**均匀随机**选择**一个**parent。
	3. 每次生成一个子代。
	4. 随机选择原先种群的一个个体与offspring做比较，fitness大的留下。

# EV1

更具体的EV：

	EV：（on a simple fitness landscape）
	1. 种群初始大小为10，并且保持10不变。gene values从[-100,100]间随机选择。种子大小为12345。
	2. fitness landscape:f(x)=50-x^2。
	3. mutation delta=1.0。
	
下面给出书中这个模型跑的结果：

	Simulation time limit (# births): 1000
	Random number seed (positive integer): 12345
	Using an inverted parabolic landscape defined on 1 parameter(s) with
	offset 50.0, with parameter initialization bounds of:
	1: -100.0 100.0 and with hard parameter bounds of:
	1: -Infinity Infinity
	Using a genome with 1 real-valued gene(s).
	Using delta mutation with step size 1.0
	Population size: 10
	Population data after 10 births (generation 1):
	Global fitness: max = 43.02033, ave = -4599.12864, min = -8586.50977
	Local fitness: max = 43.02033, ave = -4599.12793, min = -8586.50977
	Indiv birthdate fitness gene values
	1 1 -713.93585 -27.63939
	2 2 43.02033 2.64191
	3 3 -7449.33398 86.59869
	4 4 -6909.38477 83.42293
	5 5 -4387.99414 66.61827
	6 6 -8499.85352 -92.46542
	7 7 -1154.42651 -34.70485
	8 8 -5584.96094 -75.06638
	9 9 -2747.90723 -52.89525
	10 10 -8586.50977 -92.93282
	
	Population data after 20 births (generation 2):
	Global fitness: max = 43.02033, ave = -5350.27546, min = -8586.50977
	Local fitness: max = 43.02033, ave = -3689.70459, min = -8499.85352
	Indiv birthdate fitness gene values
	1 1 -713.93585 -27.63939
	2 2 43.02033 2.64191
	3 18 -659.65704 -26.63939
	4 4 -6909.38477 83.42293
	5 5 -4387.99414 66.61827
	6 6 -8499.85352 -92.46542
	7 7 -1154.42651 -34.70485
	8 8 -5584.96094 -75.06638
	9 20 -713.93585 -27.63939
	10 15 -8315.92188 -91.46542

	Population data after 1000 births (generation 100):
	Global fitness: max = 49.87177, ave = -104.82450, min = -8586.50977
	Local fitness: max = 49.87177, ave = 49.87177, min = 49.87177
	Indiv birthdate fitness gene values
	1 62 49.87177 -0.35809
	2 89 49.87177 -0.35809
	3 248 49.87177 -0.35809
	4 65 49.87177 -0.35809
	5 109 49.87177 -0.35809
	6 72 49.87177 -0.35809
	7 96 49.87177 -0.35809
	8 108 49.87177 -0.35809
	9 77 49.87177 -0.35809
	10 100 49.87177 -0.35809

我自己在电脑上跑的结果是这样的：
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/EV/0.png)

	#EV.py
	#author:logos
	import random
	from config import *

	pop = []  # 种群
	for cnt in range(0, population):
		pop.append(random.uniform(zone[0], zone[1]))

	birthdate = []  # birthdate
	for cnt in range(0, population):
		birthdate.append(cnt + 1)

	fitness = []  # fitness
	for cnt in range(0, population):
		fitness.append(fitness_landscape(pop[cnt]))

	birthcount=10#用来记录birthdate信息

	ave=open("D:\\Evolutionary Computation\\EV one\\ave.txt",'w')
	ave.truncate()
	while birthcount <= times:
		parent = pop[random.randint(0, population - 1)]  # 从亲代随机选择一个
		child=mutation(parent)  # 子代变异
		fitness_child = fitness_landscape(child)

		race=pop[random.randint(0, population - 1)]#子代与这个个体竞争
		fitness_race=fitness_landscape(race)
		index = pop.index(race)
		if fitness_child > fitness_race:
			birthdate[index] = birthcount
			pop[index] = child
			fitness[index] = fitness_child
		sum = 0.0
		for i in fitness:
			sum += i

		ave.write(str(sum*1.0/population) + ' ')
		print("Indiv birthdate fitness gene values")
		for i in range(0, 10):
			print(str(i+1) + "  " + str(birthdate[i]) + "  " + str(fitness[i]) + " " + str(pop[i]) + "  ")
		print('\n')
		birthcount += 1

	ave.close()

	
和书本相差不大。对于这个简单的模型来说，需要考虑的问题其实也有不少。
1. 为什么gene values和fitness总会收敛到同一点？
2. gene values和fitness一定会收敛吗？
3. mutation delta的大小对最后的结果有什么影响？

对于第一个问题，其实可以发现`gene values`的值必定是在`[-0.5,0.5`]之间的，因为此时的mutation delta的值是1，若最后的值不在`[-0.5,0.5]`区间内，那么一定会有变异存在使得此值的fitness landscape更大，则会代替原本
的个体，那么为什么会收敛到同一点呢？还是因为mutation delta，考虑这样一个情况，某个gene values进入了`[-0.5,0.5]`区间，另一个数也进入了，在generation趋近于无穷的情况下，大的fitness landscape一定会取胜的，
那么，无论对于什么样的mutation function，最后都会收敛到同一点吗？不是，后面会用正态分布作为mutation function，迭代无数代后gene values不同，这里会收敛到同一点完全就是因为mutation delta=1太特殊了。

# EV2
	
这次的mutation function变得复杂了，不再是delta=1，而是采用正态分布（高斯分布）。

![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/EV/0.png)

可以看到，用正态分布(step size=1)作为mutation function效果比delta=1好。

	#此文件用于设置基本配置
	#config.py
	import random
	import numpy

	times=1000#进化代数

	population=10#种群大小
	zone=[-100,100]#初始值区间

	def fitness_landscape(a):
		return 50.0-(a*1.0)*a

	def mutation(parent):#mutation
		number=numpy.random.randn()
		return parent+number
		
1. 为什么正态分布效果就会好？一定会更好吗？

