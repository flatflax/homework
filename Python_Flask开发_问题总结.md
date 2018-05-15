# Flask开发中的一些问题

### 修改model数据时报错

报错信息：`InvalidRequestError: Object '<User at 0x423b550>' is already attached to session '1' (this is '12')`

原因：SQLAlchemy的对象db已经被初始化使用，不能提交两个`db.session`。在对model数据进行修改的时候，可以使用`from models import db`，然后再使用`db.session.add()`或者`db.session.delete()`等操作。

### 表单需要传递PUT(修改)和DELETE(删除)请求

解决方法：

* 在表单中添加`<input type="hidden" name="_method" value="DELETE">`，在修饰函数中通过判断`request.form["_method"]`来确定增/删/改。
* 传json

### 部署

* uWSGI+NGINX
* Gunion

### 应用上下文，请求上下文
上下文(Contex)：保存所需资源（变量、函数）的位置

<table>
	<tr>
		<th>变量名</th>
		<th>上下文</th>
		<th>说明</th>
	</tr>
	<tr>
		<th>g</th>
		<th>应用上下文</th>
		<th>当前激活程序的程序实例</th>
	</tr>
	<tr>
		<th>current_app</th>
		<th>应用上下文</th>
		<th>处理请求时用作临时存储的对象。每次请求都会重设这个变量</th>
	</tr>
	<tr>
		<th>request</th>
		<th>请求上下文</th>
		<th>请求对象，封装了客户端发出的HTTP请求中的内容</th>
	</tr>
	<tr>
		<th>session</th>
		<th>请求上下文</th>
		<th>用户会话，用于存储请求之间需要“记住”的值的词典</th>
	</tr>
</table>

应用上下文和请求上下文的区别在于它们的生命周期。

请求上下文RequestContex的生命周期是一次请求。请求上下文中保存了`app`、`request`、`url_adapter`、`flashes`、`session`。其中`app`和应用上下文中的app含义相同。

应用上下文AppContex是0.9版本新增的，生命周期不确定。应用上下文众保存了三个变量`app`、`url_adapter`、`g`。其中`app`是对当前web应用对象的引用；`g`是保存请求中，需要用到的请求内的全局变量。

上下文对象的作用域：

线程中有一个`ThreadLocal`类，实现线程隔离。Werkzeug中实现了他的线程隔离类`werkzeug.local.Local`。
在`flask.globals`中定义了两个`LocalStack`，分别为`_request_ctx_stack`和`_app_ctx_stack`。`LocalStack`是Flask定义的线程隔离的栈存储对象，分别用来存储应用上下文和请求上下文。线程隔离意味着，不同的线程拥有不同的pid，不同的请求都在不同的线程中被处理，在同一个时期内该线程内只处理一个请求。

上下文的推送：

Flask 在分发请求之前激活（或推送）程序和请求上下文，请求处理完成后再将其删除。程序上下文被推送后，就可以在线程中使用`current_app` 和`g` 变量。类似地，请求上下文被推送后，就可以使用`request` 和`session` 变量。如果使用这些变量时我们没有激活程序上下文或请求上下文，就会导致错误。

例子：

	app_ctx = self.app.app_context()
	app_ctx.push()
	
上面两句是调用应用上下文中的push方法，推送应用上下文。应用上下文推送之后，我们就可以访问g变量了。

### 密码

Werkzeug（使用的是PBKDF2算法）

使用上面的包，计算加盐哈希密码及验证。

在验证时，为了安全原因，在验证密码时应该固定时间返回结果。可以使用异或的方式验证。

### 记录用户操作

signals

logger

before_request(f)