#include <iostream>
#include "mysql_connpool.h"

mysql_connpool::mysql_connpool()
{

}

mysql_connpool::~mysql_connpool()
{
    destroyPool();
}

// 懒汉模式，第一次获取时创建
mysql_connpool& mysql_connpool::getInstance()
{
    // 局部静态变量实现单例模式  c++11规定在初始化变量时其它线程必须等待，因此是线程安全的
    static mysql_connpool connpool;
    return connpool;
}

void mysql_connpool::init(std::string ip, unsigned int port, std::string user, std::string password, std::string databaseName, int maxConn)
{
    this->m_ip = ip;
    this->m_port = port;
    this->m_user = user;
    this->m_password = password;
    this->m_databaseName = databaseName;
    this->m_maxConn = maxConn;

    // 创建maxConn个连接
    for(int i = 0; i < m_maxConn; ++i)
    {
        MYSQL* conn = NULL;
        conn = mysql_init(conn);
        if(conn == NULL)
        {
            std::cerr << "init sql failure." << std::endl;
            return;
        }
        conn = mysql_real_connect(conn, m_ip.c_str(), m_user.c_str(), m_password.c_str(), m_databaseName.c_str(), m_port, NULL, 0);
        if(conn == NULL)
        {
            std::cerr << "connect sql failure." << std::endl;
            return;
        }
        m_connList.push_back(conn);
    }
    //初始化信号量
    m_sem = sem(maxConn);
}

int mysql_connpool::getFreeConnCount()
{
    return m_connList.size();
}

MYSQL* mysql_connpool::getConnection()
{
    m_sem.wait();
    m_locker.lock();
    MYSQL* conn = m_connList.front();
    m_connList.pop_front();
    m_locker.unlock();
    return conn;
}

bool mysql_connpool::releaseConnection(MYSQL* conn)
{
    if(conn == NULL)
        return false;
    m_locker.lock();
    m_connList.push_back(conn);
    m_locker.unlock();
    m_sem.post();
    return true;
}

void mysql_connpool::destroyPool()
{
    m_locker.lock();
    // 遍历连接池，关闭sql实例
    for(auto it = m_connList.begin(); it != m_connList.end(); ++it)
    {
        mysql_close(*it);
    }
    m_connList.clear();
    m_locker.unlock();
}



