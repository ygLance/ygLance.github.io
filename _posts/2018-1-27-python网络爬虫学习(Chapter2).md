---
published: true
title: Web Scraping With Python Chapter 2 Learning notes
category: Python
tags: 
  - Web Scraping
layout: post
---

>《Web Scraping With Python》Chapter 2的学习笔记

# You Don't Always Need a Hammer

>When Michelangelo was asked how he could sculpt a work of art as masterful as his David, he is famously reported to have said: “It is easy. You just chip away the stone that doesn’t look like David.”

这里将Web Scraping比作雕刻，即“用锤子去掉那些不像‘David’的部分”，在解析难题(Gordian Knot)的时候(即此网站很难去爬),我们不总是需要“锤子”(即我们不要一开始就dive),我们需要做的更聪明点：

* 查看此网页有无 `print this page`，或者移动端版本的html(通常来说移动端的html格式和架构会更好些)
* 查看JavaScript File有无自己想要的信息
* 也许URL就有你想要的信息
* 有无其它比较好爬的网页同样能得到你的信息

# Another Serving of BeautifulSoup

几乎每个网站都会有层叠样式表（Cascading Style Sheet， CSS）。CSS 可以让 HTML 元素呈现出差异化，使那些具有完全相同修饰的元素呈现出不同的样式。
比如一些标签看起来是这样：
	<span class="green"></span>
	<span class="red"></span>

我们可以通过创建一个这样的网络爬虫来爬取网页中的所有人物名称（此网页中人物名字都是绿色的）：

	from urllib.request import urlopen
	from bs4 import BeautifulSoup
	html = urlopen("http://www.pythonscraping.com/pages/warandpeace.html")
	bsObj = BeautifulSoup(html)
	nameList = bsObj.findAll("span", {"class":"green"})
	for name in nameList:
		print(name.get_text())
		
## 关于get_text()函数  

>get_text() 会把你正在处理的 HTML 文档中所有的标签都清除，然后返回一个只包含文字的字符串。 假如你正在处理一个包含许多超链接、段落和标签的大段源代码， 那么 .get_text() 会把这些超链接、段落和标签都清除掉，
只剩下一串不带标签的文字。

例如，上面的代码的结果是(只保留了前五行)：

	Anna
	Pavlovna Scherer
	Empress Marya
	Fedorovna
	Prince Vasili Kuragin

如果`print(name.get_text())`换成 `print(name)`，运行结果就会变成：

	<span class="green">Anna
	Pavlovna Scherer</span>
	<span class="green">Empress Marya
	Fedorovna</span>
	<span class="green">Prince Vasili Kuragin</span>
	
## 关于BeautifulSoup中的findAll函数和find函数

BeatifulSoup文档中两者的定义是：

	findAll(tag, attributes, recursive, text, limit, keywords)
	find(tag, attributes, recursive, text, keywords)

find 其实等价于findAll的limit等于1时的情形。如果你只对网页中获取的前 x 项结果感兴趣，就可以设置它。

>find和findAll函数中关键词参数的注意事项  
虽然`bsObj.findAll(id="text")`和`bsObj.findAll("", {"id":"text"})`是完全一样的，但是偶尔会出现问题，比如我们用class属性查找标签，如果这样写代码：`bsObj.findAll(class="green")`，就会
因为class是python中的保留字而产生一个语法错误。一个比较臃肿的解决方案是在class后增加一个下划线：`bsObj.findAll(class_="green")`,或者：`bsObj.findAll("", {"class":"green"})`

## Other BeautifulSoup Objects

### NavigableString Object

用来表示标签里的文字，不是标签。

### Comment Object

>Used to find HTML comments in comment tags, <!--like this one-->

再加上我们之前学习的**Tag Object**和**BeautifulSoup**对象，这四个对象就是我们用BeautifulSoup库时能遇到的所有对象了，

## Navigating Trees

一个html页面可以被映射成一棵树，以http://www.pythonscraping.com/pages/page3.html 为例，Navigating Tree是：

	html
	— body
	— div.wrapper
	— h1
	— div.content
	— table#giftList
	— tr
	— th
	— th
	— th
	— th
	— tr.gift#gift1
	— td
	— td
	— span.excitingNote
	— td
	— td
	— img
	— ……其他表格行省略了……
	— div.footer
	
### children和descendants

我们在处理标签时，可以选择处理它的children或是descendants,但这里有一个极其容易混淆的地方，以以下代码为例：

	from urllib.request import urlopen
	from bs4 import BeautifulSoup
	html = urlopen("http://www.pythonscraping.com/pages/page3.html")
	bsObj = BeautifulSoup(html)
	for child in bsObj.find("table",{"id":"giftList"}):
	print(child)

上面的代码打印了bsObj的后代中所有符合条件的标签。在上面代码的第5行加上`.children()`和不加上是一样的，即`for child in bsObj.find("table",{"id":"giftList"}):`和
`for child in bsObj.find("table",{"id":"giftList"}).children:`等价。

而处理descenents，是处理完后代之后继续遍历一遍它的后代标签并得到标签的**text**,例如上面(children)代码得到的结果（一部分）是：

	<tr><th>
	Item Title
	</th><th>
	Description
	</th><th>
	Cost
	</th><th>
	Image
	</th></tr>

如果将代码的`for child in bsObj.find("table",{"id":"giftList"}):`换成`for child in bsObj.find("table",{"id":"giftList"}).descendants:`，结果（一部分）会变成：

	<tr><th>
	Item Title
	</th><th>
	Description
	</th><th>
	Cost
	</th><th>
	Image
	</th></tr>
	<th>
	Item Title
	</th>

	Item Title

	<th>
	Description
	</th>

	Description

	<th>
	Cost
	</th>

	Cost

	<th>
	Image
	</th>

	Image

通过上面结果我们可以得知，descendant在访问后代标签之后，又循环遍历了一遍后代标签，并且输出了text信息。

### siblings

	from urllib.request import urlopen
	from bs4 import BeautifulSoup
	html = urlopen("http://www.pythonscraping.com/pages/page3.html")
	bsObj = BeautifulSoup(html)
	for sibling in bsObj.find("table",{"id":"giftList"}).tr.next_siblings:
	print(sibling)
	
这行代码会打印产品列表的所有行的产品，但是不会打印标题，原因是自己不能被视为自己的兄弟。

#### Make Selections Specifc

切记不要直接使用标签来得到你想要的信息，比如：`bsObj.table.tr`虽然和`bsObj.find("table",{"id":"giftList"}).tr`得到的结果一样，但是后者更稳定。

### parents

	from urllib.request import urlopen
	from bs4 import BeautifulSoup
	html = urlopen("http://www.pythonscraping.com/pages/page3.html")
	bsObj = BeautifulSoup(html)
	print(bsObj.find("img",{"src":"../img/gifts/img1.jpg"
	}).parent.previous_sibling.get_text())
	
原标签结构为：
	<tr>
	— <td>
	— <td>
	— <td>(3)
	— “$15.00” (4)
	— s<td> (2)
	— <img src=”../img/gifts/img1.jpg">(1)

结果为：`$15.00`

# Regular Expressions

正则表达式，简称为regex，大二《编译原理》课有很详细的学过这方面的知识，就不再赘述了。

# Regular Expressions and BeautifulSoup

同时运用两方面的知识来构建一个爬虫，regex可以让我们得到的信息更具体，在一些需要对信息进行限制的情况下我们需要用到regex。

# Accessing Attributes

用`myTag.attrs`这样的格式可以获取标签的所有属性。

# Lambda Expressions

Lambda表达式，或许可以用来替代regex，不展开说。

# Beyond BeautifulSoup

介绍了除BeautifulSoup之外可以用到的库，但目前我打算专注BeautifulSoup，就不去了解了。

* lxml

* HTML Parser


