# Linux防火墙、iptables

## 关于防火墙的认识

第一代防火墙使用了基于包过滤(Packet filter)的技术，被称为包过滤防火墙。第一代防火墙是静态的数据包过滤，在静态的数据包过滤中只检查数据包的报头.

第二代防火墙主要是基于状态检测（stateful filter）技术，称为stateful inspection firewalls。第二代防火墙服务于 OSI 参考模型的第四层传输层。通过保留足够的数据包来监控 TCP/IP 层次的连接状态并出判断，可以通过一些 session 信息如 IP 地址、端口等来做一些静态数据包过滤所做不了的更严格、更安全的动态数据包过滤。

第三代防火墙基于应用层实现，被称为proxy firewalls。第三代防火墙拦截所有的连接，并执行一个深入的应用层分析。可以在应用层面上监视恶意请求的流量状态。

在Linux中的防火墙主要分为以下三类：
* Netfilter 的数据包过滤机制
* TCP Wrappers 的程序管理
* Proxy 的代理服务器

## TCP Wrapper

TCP Wrapper的功能主要基于静态函数库`libwrap.a`实现。xinetd、sshd 和 portmap 等许多服务编译时则依赖于动态链接库`libwrap.so`。

TCP Wrapper会根据`/etc/hosts.allow`和`/etc/hosts.deny`来判断该客户是否被允许连接某项服务。读取时会先匹配`/etc/hosts.allow`再匹配`/etc/hosts.deny`，按文件内顺序读取。

	<daemon list>: <client list> [: <option>: <option>: ...]

## iptables的结构

iptables是linux内核版本为2.4以上时，内核中的数据包过滤器。iptables由iptables和netfilter两部分组成。

* iptalbes：主要工作于用户空间，为用户提供了一个编辑规则的接口。
* netfilter：主要工作于内核空间，是内核的一部分，由一些过滤表组成。

netfilter是过滤器的底层，其规则存放在内存中，提供接口`ip_tables`给iptalbes进行编辑修改配置表。这个配置表主要由`tables`、`chains`、`target`组成。

其中配置表有四个，分别是filter,NAT,mangle和raw

### filter table

filter表主要功能为数据包的过滤和访问控制。其主要有三个规则链(hook point)：

* INPUT : 从外地生成，目的地是本地的包
* FORWORD : 从外地生成，目的地非本地的包(本机负责转发)
* OUTPUT : 从本地生成的包

我们也可以通过修改源码定制filter
	
	# expample：INPUT hook point
	# from net/ipv4/netfilter/iptable_filter.c -> iptable_filter_init -> Hook point -> nf_register_hooks
	{
        .hook        = ipt_local_in_hook,
        .owner        = THIS_MODULE,
        .pf        = NFPROTO_IPV4,
        .hooknum    = NF_INET_LOCAL_IN,
        .priority    = NF_IP_PRI_FILTER,
    }

### NAT table

NAT（Network Address Translation） 表主要用于修改数据包的报头的 IP 地址、端口号等信息。可以实现数据包伪装、平衡负载、端口转发和透明代理。主要有三个链：

* PREROUTING : 在包刚刚到达本机时，到达路由之前改变它的目的地址
* OUTPUT : 改变本地产生的包的目的地址
* POSTROUTING : 在包就要离开防火墙之前改变其源地址

NAT分为静态NAT、动态NAT和NPAT。在iptables中常用NPAT。NPAT中又分为SNAT和DNAT。
* 源NAT（SNAT，Source NAT）修改数据包的源地址。源NAT改变数据流的第一个数据包的来源地址，数据包伪装就是一具SNAT的例子。
* 目的NAT（DNAT，Destination NAT）修改数据包的目的地址。它是改变第一个数据包的目的地地址，如平衡负载、端口转发和透明代理就是属于DNAT。

若是要做SNAT的数据包需要添加到POSTROUTING链中。要做DNAT的数据包需要添加到PREROUTING链中。直接从本地出站的信息包的规则被添加到OUTPUT链中。

### mangle table

mangele表主要用于修改数据包中的TOS、TTL、Qos，调整以及策略路由等应用。

* TOS ：　Type Of Service，服务类型
* TTL　：　Time To Live，生存周期
* Qos　：　Quality Of Service，服务质量

mangle表根据TOS的不同来决定经过的路由的路径。TTL意味着这个包从发送方到接收方，需要经过多少个路由器，每经过一个路由器，TTL会减1.mangle表通过修改TTL值来修改经过路由器时，TTL被修改的值，使防火墙更隐蔽，不会被trace-routes发现。

mangle表中包含五个规则链：

* PREROUTING
* POSTROUTING
* INPUT
* OUTPUT
* FORWARD

### raw table

raw表主要用于决定数据包是否被状态跟踪机制处理。在匹配数据包时，raw表的规则要优先于其他表。raw表中包含两个规则连：

* PREROUTING
* OUTPUT

### 数据包

在iptables中，数据包被跟踪连接时，有4种不同状态：
* NEW : 数据包需要新建一个连接(重新连接/重定向)
* RELATED : 数据包基于已建立的连接，建立新连接
* ESTABLISHED : NEW状态的数据包发送并接到应答
* INVALID ： 数据包没有被识别出所属连接，或数据包没有状态

数据包的进出流程：

    # 与链相关
    PREROUTING -(ToLocal)-> INPUT --> OUTPUT
    PREROUTING -(NOT-ToLocal)-> FORWARD --> POSTROUTING

    # 与表相关
    # 优先度
    raw > mangle > NAT > fliter

    # 各链中查看的表
    PREROUTING ： raw -> mangle -> NAT
    INPUT : mangle -> fliter
    OUTPUT : raw -> mangle -> NAT -> fliter
    FORWARD :　mangle -> fliter
    POSTROUTING : mangle -> NAT


## iptables的使用

`sudo iptables -nvL --line`查看当前写下的规则

1. num 规则在链中的顺序位置
2. pkts 规则处理的数据包数
3. bytes 规则处理的字节数，
4. target 规则的行为，
5. port 匹配端口
6. opt TCP头部中options的一部分
7. in 网卡进入的限制ip的匹配条件
8. out 网卡出去的限制ip的匹配条件
9. source 数据源地址
10. destination 数据的目的地址

`sudo iptables-save`查看当前生效的规则，`-t`指定需要保存的表。
