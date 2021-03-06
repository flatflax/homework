# CSRF简介

CSRF全称Cross Site Request Forgery，即跨站请求伪造。也有被缩写为XSRF的情况。CSRF在受害者不知情的情况下，通过伪装来自受信任用户的请求来利用受信任的网站。

完成一次CSRF攻击的过程大概如下：
* 受害者登陆受信任网站A，并在本地生成cookie
* 受害者网站在不登出网站A（登陆未过期）的状态下，访问危险网站B
* 危险网站B中要求访问网站A（隐式访问）

可以使用以下三种方法来防止CSRF攻击：

* 验证http请求中的referer
* 在请求表单中添加token并验证
* 在http中自定义属性验证

## 验证http请求中的Referer字段

Rerferer字段记录了该请求的来源地址。服务器端可以增加一个拦截器，通过判断请求中的referer字段，来判断该请求是否通过受信任网站发送的。假如并非从本站发送的，则拒绝该请求。

验证Referer字段简单易行。但由于该字段是由第三方浏览器生成的，不能保证浏览器完全不存在安全漏洞。例如低版本的ie可以篡改referer字段。

## 验证请求表单中的token

服务器可以通过在(会对服务器的数据进行修改的)请求表单中添加一个不存在于cookies中的参数(例如随机生成的token)，然后在服务器中拦截验证。

该方式的主要理念是在请求中添加一个伪随机数，主要实现的几种方式如下：
* cookie-hashing ： 在所有请求中添加同一个加密信息
* 验证码
* one-time token

由于该随机数在cookie中不存在，所以黑客不能在自己的网站中捏造一个可以通过拦截器的token。但黑客可以通过referer来获取该token值。

## 在http中自定义属性验证

主要的实现方式有XMLHttpRequest等。该操作获取的页面不能被浏览器所记录，因此也不能对该页面进行前进、后退、刷新、收藏等操作。对用户体验有一定的影响。