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