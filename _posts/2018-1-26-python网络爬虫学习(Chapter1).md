---
published: true
title: Web Scraping With Python Chapter 1 Learning notes
category: Python
tags: 
  - Web Scraping
layout: post
---

>《Web Scraping With Python》Chapter 1的学习笔记

# urllib
urllib是python library自带的库,可以直接用。

## urlopen

	from urllib.request import urlopen
	html = urlopen("http://pythonscraping.com/pages/page1.html")
	read= html.read()
	print(type(html))
	print(type(read))
	
运行结果为：	
	<class 'http.client.HTTPResponse'>
    <class 'bytes'>

urlopen(url)打开一个网页并读取相关内容，html.read()返回的是网页的html code。

关于urllib和urllib2

>urllib or urllib2?  
If you’ve used the urllib2 library in Python 2.x, you might have
noticed that things have changed somewhat between urllib2 and
urllib. In Python 3.x, urllib2 was renamed urllib and was split into
several submodules: urllib.request, urllib.parse, and url
lib.error. Although function names mostly remain the same, you
might want to note which functions have moved to submodules
when using the new urllib.

# BeautifulSoup

>“Beautiful Soup, so rich and green,  
Waiting in a hot tureen!  
Who for such dainties would not stoop?  
Soup of the evening, beautiful Soup!”  

很有趣的一个名字，BeautifulSoup取名于*爱丽丝梦游仙境*的同名诗歌。

在windows上为python3安装BeautifulSoup十分简单，不再赘述。

BeautifulSoup其实就是一个类，这个类会把html的内容组织成一个特定的结构，如：

>html → <html><head>...</head><body>...</body></html>  
>— head → <head><title>A Useful Page<title></head>  
>— title → <title>A Useful Page</title>  
>— body → <body><h1>An Int...</h1><div>Lorem ip...</div></body>  
>— h1 → <h1>An Interesting Title</h1>  
>— div → <div>Lorem Ipsum dolor...</div>  

下面看一段代码：

	from urllib.request import urlopen
	from bs4 import BeautifulSoup
	html = urlopen("http://www.pythonscraping.com/pages/page1.html")
	bsObj = BeautifulSoup(html.read())
	print(bsObj.h1)

结合上文，它的输出结果应该是：
`<h1>An Interesting Title</h1>`
	
# ExceptionHandling

先简单理解一下URL的组成。

protocol://serverIP/path

我们通常用的是http协议，所以大多数网站都是以http开头的，接下来的serverIP就是主机或者叫服务器的ip地址，path是具体路径，可以省略。

## HTTPError

>The page is not found on the server (or there was some error in retrieving it)

简单的来说，当一个特定服务器没有你想要的相关网页时(也可以理解为服务器没有你要的那个文件)，HTTPError就会被抛出。

	try:
	html = urlopen("http://www.pythonscraping.com/pages/page1.html")
	except HTTPError as e:
	print(e)
	#return null, break, or do some other "Plan B"
	else:
	#program continues. Note: If you return or break in the
	#exception catch, you do not need to use the "else" statement

## URLError

>The server is not found

简单的来说，如果服务器宕机了或者是根本就没有这个服务器，那么URLError就会被抛出。

书上其实没有提到URLError，它说的是如果找不到服务器，那么html会是一个None值，接着用if语句判断html是否为None，当我在运行书上的程序时发现如果找不到服务器，直接就会抛出
URLError，if语句是不会执行的。

## AttributeError

如果我们在网页找不到具体的tag时，AttributeError就会被抛出。
例如`print(bsObj.nonExistentTag.someTag)`中的someTag不存在，此时会抛出AttributeError。


