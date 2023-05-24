# MyWebserver
* 基于epoll和线程池的并发webserver；
* Reactor模式，主线程只负责监听连接和读写事件，工作线程负责I/O读写和业务处理(解析请求，确定应答信息等)；
* 使用sendfile零拷贝发送文件。

# 使用方法
1. 克隆仓库
```
git clone git@github.com:QMJ602/MyWebserver.git
```
2. 生成
```shell
rm -r build
mkdir build
cd build
cmake ..
make
```
3. 运行
```shell
./webserver [本机ip] [端口号]
```

# TCP服务器编程基本流程
1. 创建socket

```c++
int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
```
2. 绑定本机ip和端口号

```c++
int ret = bind(listen_fd, (sockaddr*)&host_addr, sizeof(host_addr));
```
3. 设置套接字为监听状态
   监听套接字会维护两个队列：
*  `SYN_RCVD`，半连接队列，收到了客户端的连接请求，发出`SYN+ACK`包，等待客户端的`ACK`;
*  `SYN_ESTABLISHED`，全连接队列，已经建立连接。

```c++
 ret = listen(listen_fd, 1024); //连接队列的最大长度设为1024
 ```
 4. 接通连接，从 `SYN_ESTABLISHED`队列头部取出一个连接，若队列为空，将阻塞
```c++
int connfd = accept(listen_fd, (sockaddr*)&client, &len);
```
5. 接收消息,可以使用`recv()`或`read()`系统调用

返回值：
* 小于`0`：出错
* `0`：对端关闭了连接
* 大于`0`：接收到的数据长度大小
```c++
int read_byte = recv(m_sockfd, m_readbuf, READ_BUFFER_SIZE, 0);
```
6. 回复消息
```c++
int ret = send(m_sockfd, m_sendbuf, strlen(m_sendbuf), 0);
```
7. 关闭连接
```c++
close( fd );
```


# 关于线程池
线程池包含哪些成员？
* 存放线程的线程数组；
* 任务队列；
* 工作函数；
* 互斥锁+信号量。

没有任务时工作线程处于什么状态？
阻塞等待信号量。











# 关于errno
* Linux中系统调用的错误都存储于errno中，errno由操作系统维护，存储就近发生的错误，即下一次的错误码会覆盖上一次的错误。
* errno是线程局部变量，每个线程都有自己的errno，因此是线程安全的。


# 数据库操作
https://blog.csdn.net/weixin_49730048/article/details/124353156

