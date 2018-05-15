# neo4j

需要有相应的JDK版本

## 安装

* Open up your terminal/shell.
* Extract the contents of the archive, using:
	
	tar -xf <filecode>.

For example,
	
	tar -xf neo4j-community-3.3.5-unix.tar.gz

*　Place the extracted files in a permanent home on your server. The top level directory is referred to as NEO4J_HOME.
	*　To run Neo4j as a console application, use:

	<NEO4J_HOME>/bin/neo4j console

To run Neo4j in a background process, use:

	<NEO4J_HOME>/bin/neo4j start

For additional commands see the Unix tarball installation documentation.

* Visit http://localhost:7474 in your web browser. 
* Connect using the username 'neo4j' with default password 'neo4j'. You'll then be prompted to change the password.


* `neo4j stop` 关闭服务
* `neo4j status` 查看状态

## 远程访问
修改 `./conf/neo4j.conf`,实现http下访问

* 远程bolt访问

将`dbms.connectors.default_listen_address=0.0.0.0`注释去掉

将`#dbms.connector.http.listen_address=:7474`的注释去掉，改为`dbms.connector.http.listen_address=0.0.0.0:7474`

重新启动服务后，就可以在别的机器上用浏览器使用7474端口远程访问服务器了。登陆成功后会提示修改密码。

<font color="while">新的密码：1qaz2wsx</font>

* 选择连接数据库

`#dbms.active_database=graph.db`


## 一些概念

### 数据库的基本组成
`nodes`：基本单位

`relationship`：连接`nodes`

`properties`：`nodes`的一些属性

### 其他

`labels`:`nodes`可以使用`labels`分类,一个`nodes`可以拥有0个或者多个`labels`，`labels`不存在`properties`

### Cypher

neo4j通过编写Cypher命令来完成操作

部分参考link

* [Neo4J(Cypher语句)初识](https://blog.csdn.net/free8666/article/details/52909523)
* [w3cschool](https://www.w3cschool.cn/neo4j/)

* delete

需要先删除relationship，然后再删除nodes
	
	match(n:person{name:"Tom"})-[r:KNOWS]->(m:person{name:"Jenny"}) delete r
	match(n:person{name:"Tom"}) delete n