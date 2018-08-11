# CGI & FastCGI

## CGI

CGI(Common Gateway Interface,通用网关接口)是Web 服务器运行时外部程序的规范。

![CGI构架图](../pics/Cgi01.png)

CGI脚本被运行在Web服务器上，由浏览器的输入启发。客户端可以通过CGI来让Web 服务器运行外部程序并返回结果。CGI 也会从Web 服务器获取用户输入的参数并传给外部程序。然而，对于每个用户请求都需要运行一次程序，这样很难扩大用户规模，因为即使程序很小，启动时还是会有明显的等待时间。

这个“每个请求都运行新程序”的模型使得CGI程序实现起来非常简单，但是限制了CGI的效率和可伸缩性。在高负载时，操作系统进程的创建和处理开销变得非常重要。此外，CGI流程模型限制了资源重用(例如重用数据库连接、内存缓存等)。

为了避免启动延迟，人们开始把语言解释器合并到Web 服务器中。Apache 可以通过mod_php 模块来运行PHP，通过mod_perl 模块来运行Perl，通过mod_python 来运行Python。这样，动态语言的代码就可以直接在持续运行的Apache 进程中执行，不用再调用外部程序。

另一种方式是在一个独立的持续运行的程序中运行动态语言，并让它和Web 服务器进行通
信，例如FastCGI 和SCGI。

## FastCGI

FastCGI(Fast Common Gateway Interface)也是协议和规范，最大的特点是对CGI进行性能优化。和CGI中对每个请求都需要初始化环境不同，FastCGI在一个进程中依次处理多次请求，从而提高效率，降低开销。这些进程属于FastCGI服务器，而不是Web服务器。

由于FastCGI服务器和Web服务器独立，因此在繁忙的时候，服务器和应用程序可以独立运行、独立重启。

## 两者和WSGI的关系

CGI和FastCGI规定的是Server和Application底层的通信协议的规范，简明的说是规定了如何传输数据。

WSGI是Server和Application/Web框架之间的接口规范。

