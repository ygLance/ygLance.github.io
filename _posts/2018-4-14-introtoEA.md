---
published: true
title: 《Evolutionary Computation》读书笔记（二）
category: Algorithm
tags: 
  - 算法
  - Evolutionary Algorithm
layout: post
---

当fitness landscape不再是单峰的，而是“四峰”的，结果又会如何呢？  f(x)=50-x1^2-x2^2。
书上给出了4种方案猜想：
>1. EV will converge to a homogeneous fixed point as before. However, there are now four peaks of attraction. Which one it converges near will depend on the randomly
generated initial conditions.
2. EV will converge to a stable fixed point in which the population is made up of subpopulations (species), each clustered around one of the peaks.
3. EV will not converge as before, but will oscillate indefinitely among the peaks.
4. The symmetry of the fitness landscape induces equal but opposing pressures to increment and decrement both feature values. This results in a dynamic equilibrium in which the average fitness of the population changes very little from its initial value.

我自己写的代码是这样的：

	#EV3.py
	import random
	from config import *

	pop = []  # 种群
	for cnt in range(0, population):
		ind= [random.uniform(zone[0], zone[1]),random.uniform(zone[0], zone[1])]
		pop.append(ind)

	#for i in pop:
		#print(str(i[0])+" "+str(i[1])+'\n')

	birthdate = []  # birthdate
	for cnt in range(0, population):
		birthdate.append(cnt + 1)

	fitness = []  # fitness
	for cnt in range(0, population):
		fitness.append(fitness_landscape(pop[cnt]))

	birthcount=11#用来记录birthdate信息

	ave=open("D:\\Evolutionary Computation\\EV one\\ave.txt",'w')
	ave.truncate()
	while birthcount <= times:
		print("Indiv birthdate fitness gene values")
		for i in range(0, 10):
			print(str(i+1) + "  " + str(birthdate[i]) + "  " + str(fitness[i]) + " " + str(pop[i]) + "  ")
		print('\n')
		parent = pop[random.randint(0, population - 1)]  # 从亲代随机选择一个
		child=mutation(parent)
		fitness_child = fitness_landscape(child)# 子代变异

		race=pop[random.randint(0, population - 1)]#子代与这个个体竞争
		fitness_race=fitness_landscape(race)
		index = pop.index(race)
		print("child_choose="+str(child)+" fitness="+str(fitness_child))
		print("parent_index="+str(pop.index(parent)+1))
		print("race_choose="+str(race)+" fitness="+str(fitness_race))
		print("race_index="+str(index+1))
		if (fitness_child > fitness_race)&(child[0]<5.0)&(child[0]>-5.0)&(child[1]<5.0)&(child[1]>-5.0):
			birthdate[index] = birthcount
			pop[index] = child
			fitness[index] = fitness_child
		sum = 0.0
		for i in fitness:
			sum += i

		ave.write(str(sum*1.0/population) + ' ')


		birthcount += 1

	ave.close()

	#此文件用于设置基本配置
	import random
	import numpy

	times=10000#进化代数

	population=10#种群大小
	zone=[-5,5]#初始值区间

	def fitness_landscape(a):
		return (a[0]*1.0*a[0])+(a[1]*1.0*a[1])

	def mutation(parent):#mutation
		a=parent[0]+numpy.random.randn()
		b=parent[1]+numpy.random.randn()
		return [a,b]


	
		
跑的结果是这样的：
![0](https://raw.githubusercontent.com/Logos23333/Logos23333.github.io/master/_posts/image/EV/2.png)

实际的gene values每次跑的结果都不一样，也就是随着初始值变化而变化，但fitness最后基本都收敛到了50左右。