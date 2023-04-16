/*
* 基于epoll和线程池的并发webserver
* 主线程负责监听连接和I/O读写
* 工作线程负责业务处理：解析请求，确定应答信息
* 同步I/O的Proactor模式
* 使用了sendfile零拷贝发送文件
*/

#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <sys/socket.h>
#include <assert.h>
#include <iostream>
#include "http/http_conn.h"
#include "threadpool/threadpool.h"

Http_conn* users[65536] = {NULL};
//设置文件描述符为非阻塞模式
int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

//在内核事件表中注册事件
void addfd( int epollfd, int fd, bool one_shot )
{
    epoll_event event;
    event.data.fd = fd;
    // event.events = EPOLLIN | EPOLLRDHUP;//边缘触发模式
    event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;//边缘触发模式  对端正常关闭连接时会触发EPOLLRDHUP|EPOLLIN事件
    if( one_shot )
    {
        event.events |= EPOLLONESHOT;//只触发一次
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

//移除内核事件表中的文件描述符，关闭文件描述符
void removefd( int epollfd, int fd )
{
    epoll_ctl( epollfd, EPOLL_CTL_DEL, fd, 0 );
    close( fd );
}

//修改注册的事件
void modfd( int epollfd, int fd, int ev )
{
    epoll_event event;
    event.data.fd = fd;
    event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;//重置EPOLLONESHOT
    epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &event );
}

int main(int argc, char* argv[])
{
    char* default_ip = NULL;
    char* default_port = NULL;
    if(argc == 3)//指定了ip, port
    {
        default_ip = argv[1];
        default_port = argv[2];
    }
    else
    {
        default_ip = "172.27.93.141";
        default_port = "32769";
        printf("using default ip:%s, port:%s\n", default_ip, default_port);
    }
    const char* ip = default_ip;
    const char* port = default_port;
    //服务器地址
    sockaddr_in host_addr;
    host_addr.sin_family = AF_INET;
    //主机字节序转换为网络字节序
    host_addr.sin_port = htons(atoi(port));
    //地址转换函数，点分十进制转为32位无符号整数，并由主机字节序转换为网络字节序
    inet_pton(AF_INET, ip, &host_addr.sin_addr);

    //创建监听sockfd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    //设置端口复用，使服务端关闭连接而经历TIME_WAIT状态时可以被重新绑定
    int reuse = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));/////////////////
    //绑定本机ip和端口
    int ret = bind(listen_fd, (sockaddr*)&host_addr, sizeof(host_addr));
    std::cout << "errno:" << errno << std::endl;
    assert(ret != -1);
    //设为监听fd  连接队列长度最大设为1024
    ret = listen(listen_fd, 1024);
    std::cout << "listen:" << std::endl;
    //创建epollfd，标记内核时间表
    int epollfd = epoll_create(10);
    //注册listenfd的可读事件，不启用oneshot
    addfd(epollfd, listen_fd, false);
    epoll_event events[1024];//设置最多存放1024个事件

    //创建线程池  线程均已创建，运行着worker函数 
    threadpool<Http_conn> pool;

    while(1)
    {
        // 等待监听的事件发生，返回事件数目
        int number = epoll_wait(epollfd, events, 1024, 0);
        if(number < 0)
        {
            std::cerr << "epoll failure." << std::endl;
            break;
        }
        for(int i=0;i<number;++i)
        {
            int sockfd = events[i].data.fd;
            //有新的连接到来
            if(sockfd == listen_fd)
            {
                while(1)//因为设置为边缘模式，所以要一次性接收完所有的连接
                {
                    sockaddr_in client;
                    socklen_t len = sizeof(client);
                    // 非阻塞调用
                    int connfd = accept(listen_fd, (sockaddr*)&client, &len);
                    if(connfd == -1)
                    {
                        break;
                    }
                    // 注册新的连接文件描述符，启用oneshot
                    addfd(epollfd, connfd, true);
                    //释放已断开连接的httpconn对象
                    if(users[connfd])
                    {
                        delete users[connfd];
                        users[connfd] = NULL;
                    }
                    users[connfd] = new Http_conn(connfd, epollfd, client);
                    char client_ip[16];
                    // 地址转换 无符号整数到点分字符串
                    inet_ntop(AF_INET, &client.sin_addr, client_ip, sizeof(client_ip));
                    printf("A client entered, ip:%s\n", client_ip);
                }
            }
            //对端关闭连接
            else if(events[i].events & EPOLLRDHUP)
            {
                removefd(epollfd, sockfd);
                // delete users[sockfd];
                // users[sockfd] = NULL;
                printf("A client left.\n");
            }
            else if(events[i].events & EPOLLIN)
            {
                users[sockfd]->M_READ = true;
                pool.append(users[sockfd]);
                // // 对端关闭连接/没有数据可读/缓冲区装不下
                // if(!users[sockfd]->read())
                // {
                //     removefd(epollfd, sockfd);
                //     delete users[sockfd];
                //     users[sockfd] = NULL;
                //     printf("A client left.\n");
                // }
                // //如果连接没有关闭
                // if(users[sockfd])
                // {
                //     pool.append(users[sockfd]);//往请求队列加入任务
                // }

            }
            else if(events[i].events & EPOLLOUT)//可写
            {
                // users[sockfd]->write();
                // //不保持连接
                // if(!users[sockfd]->m_linger)
                // {
                //     removefd(epollfd, sockfd);
                //     delete users[sockfd];
                //     users[sockfd] = NULL;
                // }
                // else//保持连接
                // {
                //     users[sockfd]->init();
                //     //注册读事件 重置EPOLLONESHOT
                //     modfd(epollfd, sockfd, EPOLLIN);
                // }
                users[sockfd]->M_WRITE = true;
                pool.append(users[sockfd]);
            }
        }
    }
    close(epollfd);
    close(listen_fd);
    return 0;
}





