# DDOS攻击：SYN攻击和CC攻击

## DDOS攻击

DOS攻击中的DOS全称是denail-of-service,拒绝服务。DOS攻击通过消耗目标机器或网络的资源，例如暂时地或者无期限地暂停该服务的主机与互联网的连接，导致该服务无法顺利地向用户提供正常服务。DOS攻击通常通过flood攻击，有针对性地尝试对目标机器或资源进行多余请求，使机器过载。

DDoS(distributed denial-of-service)攻击又称分布式拒绝服务攻击。攻击源往往不止一个，又往往成千上万个，并且都是真实唯一的IP地址。

常见的DDoS攻击体现的症状：
* 网络堵塞，打开网站的速度异常的缓慢
* 服务器的 CPU 长期处于满负荷
* 服务器的频繁死机，重启

常见的DDOS攻击有以下几种：

* Ping flood : 发送大量ping包
* Ping of Death : 发送修改后的ping数据包，如添加分包使前后的逻辑不正确，或者加长数据包使其超过IP报文的限制
*　Teardrop attacks　：　发送损坏的IP包，诸如重叠的包或过大的包载荷。
* UDP flood ： 发送大量UDP小包
* SYN flood ： 利用TCP的连接过程，来消耗系统资源
* CC(challenge Collapsar) ： 构造有针对性的、对最为消耗服务器端资源的业务请求

## SYN攻击

SYN攻击是最常见又最容易被利用的一种攻击手法。而SYN攻击依靠的是TCP三次握手过程。攻击方客户端发送SYN的请求连接的信号，在服务器从关闭状态变为监听状态后，客户端不对服务端发来的SYN+ACK作出响应，使得服务器一直等待直到过时。大量的连接等待非常耗费资源。

我们可以使用linux中的iptables，限制每个ip发出的连接次数。

	# 使用 limt 对 syn的每秒钟最多允许3个新链接
	sudo iptables -A INPUT -p tcp --syn -m limit --limit 1/s  --limit-burst 3 -j ACCEPT

	# 或者针对每个客户端作出限制，每个客户端限制并发数为10个
	sudo iptables -I INPUT -p tcp --syn --dport 80 -m connlimit --connlimit-above 10 -j REJECT

## CC攻击

相对于SYN攻击，CC攻击就是对服务器做一次完整的请求，属于TCP全连接攻击。攻击者使用“合法”的源IP与访问请求，由于Collapsar无法判断请求的真假，该请求不会被拦截。但是整个请求非常的消耗资源，例如对数据库进行大数据量的查询等，一次的连接很长，消耗很多的资源的。大量的CC攻击会导致服务器的连接数超过上限，使得网页出现service unavailable提示，服务器CPU占用率很高。

假如我们使用`netstat –na`查看网络连接状态，观察到大量的状态为`ESTABLISHED`的连接，每个IP重复创建数十甚至上百条，外部无法打开软件，软硬重启后短期内恢复正常，几分钟后又无法使用，我们则可以判断服务器遭到了CC攻击。

对于CC攻击，不仅可以使用iptables来防范，还可以通过修改TCP配置，例如：

	sudo vim /etc/sysctl.conf

	#表示开启SYN Cookies。当出现SYN等待队列溢出时，启用cookies来处理，可防范少量SYN攻击，默认为0，表示关闭；
	net.ipv4.tcp_syncookies = 1 

	#表示开启重用。允许将TIME-WAIT sockets重新用于新的TCP连接，默认为0，表示关闭；
	net.ipv4.tcp_tw_reuse = 1 

	#表示开启TCP连接中TIME-WAIT sockets的快速回收，默认为0，表示关闭。
	net.ipv4.tcp_tw_recycle = 1 

	#表示开启TCP连接的最大数量的限制
	net.ipv4.tcp_max_tw_buckets = 5000