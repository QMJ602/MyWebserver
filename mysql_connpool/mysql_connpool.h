#include <mysql/mysql.h>
#include <string>
#include <list>
#include "../locker/locker.h"

class mysql_connpool{
public:
    static mysql_connpool* getInstance();                           // 获取连接池实例
    ~mysql_connpool();
public:
    void init(std::string ip, unsigned int port, std::string user, std::string password, std::string databaseName, int maxConn);
    MYSQL* getConnection();                                         // 获取一个数据库连接
    bool releaseConnection(MYSQL* conn);                            // 释放一个数据库连接
    int getFreeConnCount();                                         // 获取空闲数目连接
    void destroyPool();                                             // 销毁连接池
private:
    mysql_connpool();                                               // 构造函数设为私有
    mysql_connpool(const mysql_connpool&) = delete;                 // 禁用拷贝构造
    mysql_connpool& operator = (const mysql_connpool&) = delete;    // 禁用赋值运算符
private:
    int m_maxConn;                                                  // 最大连接数
    std::list<MYSQL*> m_connList;                                   // 连接池
    locker m_locker;                                                // 互斥锁
    sem m_sem;                                                      // 信号量
public:
    std::string m_ip;                                               // 数据库ip
    unsigned int m_port;                                            // 数据库端口号
    std::string m_user;                                             // 登录数据库地用户名
    std::string m_password;                                         // 密码
    std::string m_databaseName;                                     // 数据库名称
};