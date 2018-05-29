## WinSCP

用`ifconfig`获取虚拟机的ip就口以了

## Centos下用neo4j需要JDK环境

* [官网](http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)获取相应版本的rpm
* 安装
* 
		sudo rpm -ivh jdk-8u151-linux-x64.rpm


## Python环境安装

CentOS内置Python2.7，迫于懒，就找了个3里面最新的稳定版装了

* 安装可能用到的依赖包
	
    	yum install openssl-devel bzip2-devel expat-devel gdbm-devel readline-devel sqlite-devel

* wget下载

		wget https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tgz

* `tar -zxvf Python-3.6.5.tgz`解压
* `mv Python-3.6.5 /usr/local`移到后面的目录里
* 删除旧版本的Python

		ll /usr/bin | grep python

		rm -rf /usr/bin/python
* 进入Python目录里

		./configure 	# 配置
		make			# 编译
		make install 	# 安装
* 删除旧的软连接，创建新的软连接
		rm -rf /usr/bin/python

		ln -s /usr/local/bin/python3.6 /usr/bin/python
		ln -s /usr/local/bin/pip3 /usr/bin/pip

* Centos部分命令默认使用`/usr/bin/python`执行，所以报错时需要修改相关命令使用`/usr/bin/python2.7`执行

## 安装docker

因为是CentOS7,所以内置了……

	yum -y install docker-io

	service docker start	# 启动后台服务

### 创建Nginx镜像
* 在Docker Hub上查找nginx镜像

		docker search nginx
* 拉取相关镜像

		docker pull nginx

* 运行容器

		docker run -p 80:80 --name mynginx -v $PWD/www:/www -v $PWD/conf/nginx.conf:/etc/nginx/nginx.conf -v $PWD/logs:/wwwlogs  -d nginx

## SSH连接

确保已经安装openssh

	yum list installed | grep openssh-server

加入没有安装的话，输入`yum install openssh-server`进行安装

修改`/etc/ssh/sshd_config`,开启监听、远程登陆和密码验证

	# If you want to change the port on a SELinux system, you have to tell
	# SELinux about this change.
	# semanage port -a -t ssh_port_t -p tcp #PORTNUMBER
	#
	Port 22
	#AddressFamily any
	ListenAddress 0.0.0.0
	ListenAddress ::

	# Authentication:
	#LoginGraceTime 2m
	PermitRootLogin yes
	#StrictModes yes
	#MaxAuthTries 6
	#MaxSessions 10

	# To disable tunneled clear text passwords, change to no here!
	PasswordAuthentication yes
	#PermitEmptyPasswords no
	PasswordAuthentication yes

运行指令开启服务`sudo service sshd start`

使用指令`ps -e | grep sshd`检查服务是否开启，或使用指令`netstat -an | grep 22`检查端口是否被监听

#### 虚拟机
在win端`ipconfig`获取虚拟机ip，在centos端`ifconfig`获取自身网络连接ip。进行互ping尝试。

`ssh-keygen`创建公钥

#### cmd连接

`ssh username@host:port` 详情自己看手册吧

## mongodb

官网下载`mongodb-linux-x86_64-3.6.5`

	tar zxvf mongodb-linux-x86_64-2.4.9.tgz
	mv mongodb-linux-x86_64-2.4.9 mongodb
	cd mongodb
	mkdir db
	mkdir logs
	cd bin
	vi mongodb.conf

在配置文件中添加

	dbpath=/usr/local/mongodb/db
	logpath=/usr/local/mongodb/logs/mongodb.log
	port=27017
	fork=true
	bind_ip=0.0.0.0

执行`/usr/local/mongodb/bin/mongod -f /usr/local/mongodb/bin/mongodb.config`

可以设置开机自启动

	vi /etc/rc.d/rc.local
	/usr/local/mongodb/bin/mongod --config /usr/local/mongodb/bin/mongodb.conf
