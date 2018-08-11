# Selenium WebDriver用于爬虫

## 简介

Selenium是一款用于Web应用的开源自动化测试工具，由ThoughtWorks公司制作。该产品由Selenium IDE、Selenium Remote Control(RC)和Selenium GRID组成，分别完成测试过程中的录制、编写和运行，已经并行处理的功能。该工具核心Selenium RC基于JsUnit，使用JavaScript编写，因而可以运行于支持JavaScript的浏览器上。Selenium支持使用包括C、Java、Python等多种语言进行开发。

网络爬虫（Web Crawler or Spider）指编写程序以自动爬取指定互联网网页的指定信息，采集互联网信息。不同计算机语言可以借助不同的库以实现与网页的互动。当使用Python进行爬虫时，常使用的库有Scrapy、Requests、Beautiful Soup等。

当需要爬取异步加载的动态页面、又暂时无心研究Ajax异步加载等原理时，可以考虑使用Selenium系列工具。当考虑使用Selenium实现爬虫功能时，可以选择WebDriver或Selenium Grid实现。本文主要介绍选择WebDriver实现的情况。

## WebDriver对浏览器的支持

Selenium WebDriver是Selenium RC的继任者，因而也能运行于任何支持JavaScript的浏览器上，如桌面端的Chrome、Edge、Firefox、Safari等，服务器端可以考虑使用PhantomJS。在使用Selenium WebDriver前，需要先安装对应浏览器的驱动并将该驱动文件放置在环境路径中。

以Firefox为例，在完成Selenium库的安装和Firefox驱动的下载后，键入以下内容，声明并调用Firefox，新建窗口打开<http://www.python.org>网页：

	from selenium import webdriver  
	 
	driver = webdriver.Firefox()  
	driver.get("http://www.python.org") # get方法打开网页  
	  
	driver.close() # 关闭WebDriver  

## 选择器

当WebDriver正确打开所需爬取的网页后，如同使用其他方式实现爬虫一样，我们需要先对网页代码进行解析，考虑如何让WebDriver过滤掉大部分的内容，找到存储着所需信息的单个元素或多个元素。

	find_element_by_id()
	find_element_by_name()  
	find_element_by_xpath() 
	find_element_by_link_text()  
	find_element_by_partial_link_text()  
	find_element_by_tag_name()  
	find_element_by_class_name()  
	find_element_by_css_selector()  
	
	# 选择多个elements  
	find_elements_by_name  
	# 下略

上述列举的方法为Selenium WebDriver提供的选择器方法，其中1-8行返回单个元素。当需要选择多个元素时，可以使用以10为例的方法，该方法返回一个列表。我们可以根据自己熟悉的筛选方式选择所需元素。以下列HTML为例：

	<html>  
		<body>  
			<form id="loginForm">  
				<input name="username" type="text" />  
				<input name="password" type="password" />  
				<input name="continue" type="submit" value="Login" />  
				<input name="continue" type="button" value="Clear" />  
			</form>  
		</body>  
	<html>

当使用Xpath选择 `<input name="username" type="text" />` 的内容时，我们可以使用下面两种（或组合）方式实现。其中`/html/body`是寻找html元素下的body子节点，`form/input[1]`是寻找form元素下的第一个input子节点，`//input[@name='username']`是在所有内容中寻找名字属性为username的input节点。

	login_form = driver.find_element_by_xpath("/html/body/form/input[1]")  
	login_form = driver.find_element_by_xpath("//input[@name='username']")

在找到所需元素之后，可以调用`element.get_attribute(<attribute_name>)`方法获取所需的元素属性， 然后进行存储或其他处理。

## 控件操作

在实现爬虫过程中，我们往往不仅是在某一个类型的页面中一直爬取信息，更多的是通过与页面的交互，跳转到不同类型的网页中爬取多种信息。因此我们也需要Selenium WebDriver实现与网页的交互。

其中较为常用的是keys。可以实现对所选元素键入回车、点击和输入文字等操作。

	from selenium.webdriver.common.keys import Keys  
	  
	# 省略driver和定位elem的部分  
	elem.send_keys("some text")  
	elem.send_keys(Keys.RETURN)  
	elem.clear() 

除此之外还能实现填充表单、对不同Frame的切入和切出以及调用js方法，详细可以参考文档。

## 其他

通常在使用Selenium WebDriver访问网页时，Selenium会等待页面加载完成再进行下一步操作，但是对于Ajax异步加载实现的网站，WebDriver会不知道何时网页才能加载完成。在这个时候需要对其设置等待时间。等待的实现可以通过显式等待和隐式等待两种方式实现。

除此之外，为了让selenium表现得更像一个自然人，避免被网站判定为爬虫机器人，在调用PhantomJS时可以修改请求头的User-Agent，也可以考虑对cookie进行一定的处理，或在条件允许下添加一些等待。

当有一个新的爬虫想法出现时，可以借助Selenium WebDriver快速地验证其可行性。但是当需要提高其工作效率，实现高并发和分布式时却比较困难。此时可以考虑使用其他的工具组合，例如Scrapy+chromedriver或Selenium Grid等。

## 参考

Selenium with Python文档：<http://selenium-python.readthedocs.io/>
