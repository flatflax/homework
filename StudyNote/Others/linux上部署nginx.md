linux上部署nginx

##安装编译工具及库文件
	yum -y install make zlib zlib-devel gcc-c++ libtool  openssl openssl-devel
### 离线情况下：

	http://vault.centos.org/7.2.1511/os/x86_64/Packages/ 获取相关的rpm文件
	(gcc-c++)

##安装pcre
	wget http://downloads.sourceforge.net/project/pcre/pcre/8.35/pcre-8.35.tar.gz
	tar zxvf pcre-8.35.tar.gz
	./configure
	make && make install

##安装nginx
	wget http://nginx.org/download/nginx-1.6.2.tar.gz
	tar zxvf nginx-1.6.2.tar.gz
	cd nginx-1.6.2

###离线状态下：
依赖包：
pcre
pcre-devel
libstdc++-devel
gcc-c++
zlib-devel

###编译安装
	./configure
	make
	make install

##安装flask
###离线状态下：
依赖包：
Werkzeug-0.12.1.tar.gz
MarkupSafe-1.0.tar.gz
pytz-2017.2.zip
click-6.7.tar.gz
itsdangerous-0.24.tar.gz
Jinja2-2.9.6.tar.gz
Babel-2.4.0.tar.gz

###[不知道原因]Werkzeug需要解压安装
	tar -xzvf Werkzeug-0.12.1.tar.gz 
	cd Werkzeug-0.12.1/
	python setup.py install

## 安装Flask-SQLAlchemy
###离线情况下：
依赖包：
SQLAlchemy

#安装uWSGI

******************************
##配置uWSGI
uwsgi.ini

	uwsgi /apps/webTest/src/buildconf/uwsgi.ini --daemonize /var/log/uwsgi.log

	--daemonize : 后台运行，记录写到uwsgi.log中
	--enable-threads ： 支持多线程

##配置nginx
/usr/local/nginx/conf

	server {
        listen       80;
        server_name  localhost;

        #charset koi8-r;

        #access_log  logs/host.access.log  main;

        location / {
            # root   html;
            # index  index.html index.htm;
            proxy_pass http://127.0.0.1:8888;
        }
        
        }

	/usr/local/nginx/sbin/nginx -t  测试config文件是否合法
	/usr/local/nginx/sbin/nginx 运行nginx

