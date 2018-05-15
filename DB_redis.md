# Redis相关

## 安装

下载，解压，编译

	wget http://download.redis.os/release/redis-4.0.9.tar.gz
	tar xzf redis-4.0.9.tar.gz
	cd redis-4.0.9
	make

二进制文件放置在编译完成后的src目录下

	src/redis-server	# 启动redis服务
	redis-cli shutdown 	# 关闭服务

`redis.config`里说明了相关配置信息

* `daemonize`设定是否后台执行，后台执行时会在`/var/run/redis/pid`写入一个pid文件

## 远程访问

修改`redis.config`注释掉`bind localhost`和修改`protected-mode`为no

或者重启redis，关闭保护模式

	redis-server --protected-mode no

用`ps -ef | grep redis`查询可知

	root     14776 14701  0 09:38 pts/0    00:00:00 /home/database/redis-4.0.9/src/redis-server *:6379

当前所有host下的6379都可以访问redis

## Python Redis

	pip install redis

	import redis
	r = redis.StrictRedis(host='localhost', port=6379, db=0)
	r.set('foo', 'bar')		# 或者r['foo']='bar'
	r.get('foo', 'bar')
