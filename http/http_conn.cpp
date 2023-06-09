#include "http_conn.h"

const char* ok_200_title = "OK";
const char* error_400_title = "Bad Request";
const char* error_400_form = "Your request has bad syntax or is inherently impossible to satisfy.\n";
const char* error_403_title = "Forbidden";
const char* error_403_form = "You do not have permission to get file from this server.\n";
const char* error_404_title = "Not Found";
const char* error_404_form = "The requested file was not found on this server.\n";
const char* error_500_title = "Internal Error";
const char* error_500_form = "There was an unusual problem serving the requested file.\n";
const char* doc_root = "../Resource";//服务器根目录
// const char* homepage = "/home/qmj/linux_net/homepage.jpg";
// const char* doc_root = "/home/qmj/blog/public";
// const char* homepage = "/home/qmj/blog/public/index.html";
const char* homepage = "../Resource/login1.html";
std::string sql_ip = "127.0.0.1";
std::string sql_user = "root";
std::string sql_passwd = "123456";
std::string sql_database = "registeration";
int sql_port = 3306;
int sql_maxconn = 10;

void Http_conn::sql_connpool_init()
{
    m_connpool = mysql_connpool::getInstance();
    m_connpool->init(sql_ip, sql_port, sql_user, sql_passwd, sql_database, sql_maxconn);
}
Http_conn::Http_conn(int sockfd, int epollfd, sockaddr_in client_address)
{
    m_sockfd = sockfd;
    m_epollfd = epollfd;
    m_client_address = client_address;
    init();
}
Http_conn::~Http_conn()
{
    free(m_target_file);
}
void Http_conn::init()
{
    memset(m_readbuf, 0, READ_BUFFER_SIZE);
    memset(m_sendbuf, 0, WRITE_BUFFER_SIZE);
    m_check_index = 0;
    m_read_index = 0;
    m_startline = 0;
    m_check_state = CHECK_STATE_REQUEST_LINE;
    m_linger = false;
    m_version = NULL;
    m_host = NULL;
    m_file_fd = -1;
    m_target_file = (char*)malloc(100);
    m_url = NULL;
    m_method = GET;
    m_content_length = 0;
    m_content = NULL;
    M_READ = false;
    M_WRITE = false;
    m_connpool = NULL;
    sql_connpool_init();
}

//读取socket上的数据
bool Http_conn::read()
{
    if(m_read_index >= READ_BUFFER_SIZE)//读缓冲区装不下
    {
        return false;
    }
    while(1)
    {
        int read_byte = recv(m_sockfd, m_readbuf+m_read_index, READ_BUFFER_SIZE-m_read_index, 0);
        if(read_byte > 0)
        {
            m_read_index += read_byte;
        }
        else if(read_byte == 0)//对端关闭连接
        {
            return false;
        }
        else
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK)//没有数据可读
            {
                break;
            }
            return false;//出错
        }
    }
    return true;
}

//往socket上写入数据
bool Http_conn::write()
{
    //发送应答行，应答头
    int ret = send(m_sockfd, m_sendbuf, strlen(m_sendbuf), 0);
    //有文件要发送
    if(m_file_fd != -1)
    {
        off_t bytes_have_send = 0;//已发送的字节数，作为每次sendfile的偏移
        ssize_t bytes_to_send = m_file_stat.st_size;//要发送的字节数
        //printf("file size:%ld\n", bytes_to_send);
        while(bytes_to_send > 0)//循环发送，直至文件发送完成
        {
            int count = sendfile(m_sockfd, m_file_fd, &bytes_have_send, bytes_to_send);//bytes_have_send会随着sendfile的调用自动更新
            if(count < 0 && errno == EAGAIN)
            {
                //写缓冲区满
                continue;
            }
            else if(count < 0 && errno == EPIPE)
            {
                printf("broken pipe\n");
                break;
            }
            else if(count == 0)
            {
                break;
            }
            bytes_to_send -= count;
            printf("%d字节已发送, 剩余%d字节.\n", bytes_have_send, bytes_to_send);
        }
        close(m_file_fd);
    }
}

/**************************************************************
 * 功能：每调用一次，解析出一个完整行
 * buffer：接收缓冲区
 * check_index：目前正在分析的字节
 * read_index：缓冲区中的数据的最后一个字节的下一字节
 * 返回值：行的状态
 * 判断完整行的标志：遇到回车符+换行符 "\r\n"  如果单独遇到\r或\n则说明请求语法错误
 * ***********************************************************/
Http_conn::LINE_STATUS Http_conn::parse_line()
{
    char cur_byte;
    for(; m_check_index < m_read_index; ++m_check_index)
    {
        cur_byte = m_readbuf[m_check_index];
        //遇到回车符
        if(cur_byte == '\r')
        {
            if(m_check_index + 1 == m_read_index)              //如果当前字节已经是收到的最后一个字节，则行不完整
            {
                return LINE_OPEN;
            }
            else
            {
                if(m_readbuf[m_check_index+1] == '\n')          //下一个是回车，则读到完整行
                {
                    //用结束符'\0'替换回车和换行符，相当于截断字符串
                    m_readbuf[m_check_index++] = '\0';
                    m_readbuf[m_check_index++] = '\0';
                    return LINE_OK;
                }
                else                                       //请求语法错误
                {
                    return LINE_BAD;
                }
            }
        }
        //遇到换行符
        if(cur_byte == '\n')
        {
            if(m_check_index == 0)                          //当前字符是第一个字符，说明语法错误
            {
                return LINE_BAD;
            }
            else
            {
                if(m_readbuf[m_check_index-1] == '\r')         //上个字符是换行符，读到完整行
                {
                    m_readbuf[m_check_index-1] = '\0';
                    m_readbuf[m_check_index++] = '\0';
                    return LINE_OK;
                }
                else
                {
                    return LINE_BAD;
                }
            }
        }
    }
    return LINE_OPEN;
}

/**************************************************************
 * 功能：解析请求行
 * temp：当前完整行头部指针
 * check_state：当前的主状态机状态
 * 返回值：http请求处理结果
 * ***********************************************************/
Http_conn::HTTP_CODE Http_conn::parse_request_line(char* temp)
{
    printf("line:%s\n", temp);
    char* meth_url = strpbrk(temp, " ");           //返回第一次出现空格的指针  method和url的分割点
    if(!meth_url)                                  //不合法
        return BAD_REQUEST;
    *meth_url = '\0';                              //在cut处加结束符——把method分割了出来
    char* method = temp;
    if(strcasecmp(method, "GET") == 0)             //字符串比较
    {
        m_method = GET;
    }
    else if(strcasecmp(method, "POST") == 0)
    {
        m_method = POST;
    }
    printf("method:%s\n", method);

    meth_url++;
    meth_url += strspn(meth_url, " ");             //返回不是空格的第一个字符下标
    char* url_version = strpbrk(meth_url, " ");    //第二次出现空格的指针 url和version的分割点
    if(!url_version)
        return BAD_REQUEST;
    *url_version = '\0';
    m_url = meth_url;                          //获得url

    printf("url:%s\n", m_url);
    if(strncasecmp(m_url, "http://", 7) == 0)    //字符串比较
    {
        m_url += 7;                                 //跳过http://
        m_url = strchr(m_url, '/');              //返回第一次出现/的位置.跳过网址
    }
    if(!m_url || m_url[0] != '/')
    {
        return BAD_REQUEST;
    }
    url_version++;
    url_version += strspn(meth_url, " ");
    m_version = url_version;                   //获得版本信息
    printf("version:%s\n", m_version);

    m_check_state = CHECK_STATE_REQUEST_HEAD;        //解析完毕，切换到解析请求头状态
    return NO_REQUEST;
}

/**************************************************************
 * 功能：解析请求头
 * temp：当前完整行头部指针，每次传入一行
 * check_state：当前的主状态机状态
 * 返回值：http请求处理结果
 * ***********************************************************/
Http_conn::HTTP_CODE Http_conn::parse_request_head(char* temp)
{
    if(temp[0] == '\0')                                //遇到空行，说明head部分结束
    {
        if(m_content_length != 0)                        //如果有请求正文
        {
            m_check_state = CHECK_STATE_REQUEST_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;                            //否则，返回获得一个完整http请求
    }
    char* colon = strpbrk(temp, ":");                  //获取冒号位置指针
    if(!colon)
        return BAD_REQUEST;
    *colon = '\0';
    if(strcasecmp(temp, "Host") == 0)                  //头部字段为HOST
    {
        m_host = colon + 1;
        m_host += strspn(m_host, " ");                      //从第一个非空格字符开始
        printf("host:%s\n", m_host);
    }
    else if(strcasecmp(temp, "Connection") == 0)       //头部字段为Connection
    {
        char* conn = colon + 1;
        conn += strspn(conn, " ");
        if(strcasecmp(conn, "keep-alive") == 0)        //是否保持连接
        {
            m_linger = true;
            printf("Connection:keep-alive\n\n");
        }
        else
            printf("Connection:close\n");
    }
    else if(strcasecmp(temp, "Content-Length") == 0)   //头部字段为Content-Length
    {
        char* num = colon+1;
        num += strspn(num, " ");
        m_content_length = atoi(num);
        printf("Content-Length:%d\n", m_content_length);
    }
    else if(strcasecmp(temp, "action") == 0)                                              //其他头部字段
    {
        char* act = colon + 1;
        act += strspn(act, " ");
        if(strcasecmp(act, "register") == 0)        //登录还是注册
        {
            m_action = REGISTER;
        }
        else
            m_action = LOGIN;
    }
    return NO_REQUEST;
}

/**************************************************************
 * 功能：解析请求正文
 * temp：当前完整行头部指针
 * 返回值：http请求处理结果
 * ***********************************************************/
Http_conn::HTTP_CODE Http_conn::parse_request_content(char* temp)
{
    m_content = temp;
    printf("content:%s\n", m_content);
    return GET_REQUEST;
}

/**************************************************************
 * 功能：主状态机，解析出一个完整的请求信息
 * buffer：接收缓冲区指针
 * check_index：目前正在分析的字节
 * read_index：缓冲区中的数据的最后一个字节的下一字节
 * startline：当前要分析的行头部指针，随着parse_line更新
 * 返回值：http请求处理结果
 * ***********************************************************/
Http_conn::HTTP_CODE Http_conn::process_read()
{
    LINE_STATUS line_status = LINE_OK;
    HTTP_CODE ret_code = NO_REQUEST;
    while((line_status = parse_line()) == LINE_OK)
    {
        char* temp = m_readbuf + m_startline;    //当前行位置
        m_startline = m_check_index;            //更新当前行为下一行开始位置
        switch (m_check_state)
        {
            //分析请求行
        case CHECK_STATE_REQUEST_LINE:
            ret_code = parse_request_line(temp);
            if(ret_code == BAD_REQUEST)//出错
                return BAD_REQUEST;
            break;
            //分析请求头
        case CHECK_STATE_REQUEST_HEAD:
            ret_code = parse_request_head(temp);
            if(ret_code == BAD_REQUEST)
            {
                //printf("00000000\n");
                return BAD_REQUEST;
            }
            if(ret_code == GET_REQUEST)
            {
                // printf("111111111\n");
                return do_request();
            }
            break;
            //分析请求体
        case CHECK_STATE_REQUEST_CONTENT:
            //printf("2222222222\n");
            ret_code = parse_request_content(temp);
            if(ret_code == GET_REQUEST)
            {
                printf("2222222222\n");
                return do_request();
            }
            break;
        default:
            return INTERNAL_ERROR;//服务器内部错误
            break;
        }
    }
    //还未解析出完整行
    if(line_status == LINE_OPEN)
    {
        return NO_REQUEST;
    }
    //解析出出错行
    else
    {
        return BAD_REQUEST;
    }
}


/**************************************************************
 * 功能：分析处理请求，在获得一个完整请求时调用
 * 返回值：http请求处理结果
 * ***********************************************************/
Http_conn::HTTP_CODE Http_conn::do_request()
{
    if(m_method == GET)
    {
        
        //请求网站首页  /
        if(strlen(m_url) == 1)
        {
            strcpy(m_target_file, homepage);
        }
        else
        {//获得资源路径
            strcpy(m_target_file, doc_root);
            int len = strlen(doc_root);
            strcpy(m_target_file + len, m_url);
        }
        //资源不存在
        if(stat(m_target_file, &m_file_stat) < 0)//获取文件状态信息，保存在m_file_stat结构体中
        {
            return NO_RESOURCE;
        }
        //如果其他用户没有读权限
        if(!(m_file_stat.st_mode & S_IROTH))
        {
            return FORBIDDEN_REQUEST;
        }
        //如果目标资源是一个目录
        if(S_ISDIR(m_file_stat.st_mode))
        {
            return BAD_REQUEST;
        }
        //否则，是一个文件请求
        return FILE_REQUEST;
    }
    else if(m_method == POST)
    {
        if(m_content == NULL)
            return BAD_REQUEST;
        //解析用户名密码
        char* delimiter = strchr(m_content, '&');
        char* username = strchr(m_content, '=') + 1;
        char* passwd = strchr(delimiter, '=') + 1;
        *delimiter = '\0';
        MYSQL* sql = m_connpool->getConnection();
        if(m_action == REGISTER)
        {
            char query[100];
            char format[] = "SELECT 1 FROM user WHERE username='%s' LIMIT 1";
            snprintf(query, 100, format, username);
            if(0 == mysql_query(sql, query))
            {
                MYSQL_RES* result = mysql_store_result(sql);
                if (mysql_num_rows(result) == 0)
                {
                    char insert[100];
                    char fmt[] = "INSERT INTO user(username, passwd) VALUES('%s', '%s')";
                    snprintf(insert, 100, fmt, username, passwd);
                    if(0 == mysql_query(sql, insert))
                    {
                        printf("插入成功\n");
                    }
                }
                mysql_free_result(result);
            }
        }
        else if(m_action == LOGIN)
        {
            char query[100];
            char format[] = "SELECT * FROM user WHERE username='%s'";
            snprintf(query, 100, format, username);
            if(0 == mysql_query(sql, query))
            {
                MYSQL_RES* result = mysql_store_result(sql);
                if(mysql_num_rows(result) == 0)
                {
                    printf("用户不存在！\n");
                    return BAD_REQUEST;
                }
                MYSQL_ROW row = mysql_fetch_row(result);
                unsigned int num_fields = mysql_num_fields(result);
                for (unsigned int i = 0; i < num_fields; i++) {
                    printf("%s ", row[i] ? row[i] : "NULL");
                        }
                if(strcmp(row[1], passwd) == 0)
                {
                    printf("登录成功！\n");
                }
                else
                {
                    printf("密码错误\n");
                    printf("%s\n", passwd);
                    printf("%s\n",row[1]);
                }
                mysql_free_result(result);
            }
        }
        return FILE_REQUEST;
    }
    
}
/**************************************************************
 * 功能：向发送缓冲区添加内容
 * ***********************************************************/
bool Http_conn::add_response(std::string text)
{
    std::string send_string = std::string(m_sendbuf);
    send_string += text;
    strcpy(m_sendbuf, send_string.c_str());
    return true;
}
/**************************************************************
 * 功能：添加应答状态行
 * ***********************************************************/
bool Http_conn::add_status_line(int status, const char* title)
{
    std::string status_line = "HTTP/1.1 " + std::to_string(status) + " " + std::string(title) + "\r\n";
    return add_response(status_line);
}
/**************************************************************
 * 功能：添加状态头->Content-Length:
 * ***********************************************************/
bool Http_conn::add_content_length(int content_lenth)
{
    std::string content_lenth_text = "Content-Length: " + std::to_string(content_lenth) + "\r\n";
    return add_response(content_lenth_text);
}
/**************************************************************
 * 功能：添加状态头->Connection: 
 * ***********************************************************/
bool Http_conn::add_linger()
{
    std::string linger_text;
    linger_text += "Connection: ";
    linger_text += (m_linger == true) ? "keep-alive" : "close";
    linger_text += "\r\n";
    return add_response(linger_text);
}
/**************************************************************
 * 功能：添加状态头->空行
 * ***********************************************************/
bool Http_conn::add_blankline()
{
    return add_response("\r\n");
}
/**************************************************************
 * 功能：添加完整状态头
 * ***********************************************************/
bool Http_conn::add_headers(int content_lenth)
{
    add_content_length(content_lenth);
    add_linger();
    add_blankline();
}
/**************************************************************
 * 功能：添加应答体
 * ***********************************************************/
bool Http_conn::add_content(const char* content)
{
    return add_response(std::string(content));
}
/**************************************************************
 * 功能：根据解析请求的结果决定发送什么响应
 * read_ret：请求解析的结果
 * ***********************************************************/
bool Http_conn::process_write(HTTP_CODE read_ret)
{
    switch(read_ret)
    {
        case INTERNAL_ERROR:
            add_status_line(500, error_500_title);
            add_headers(strlen(error_500_form));
            add_content(error_500_form);
            break;
        case BAD_REQUEST:
            add_status_line(400, error_400_title);
            add_headers(strlen(error_400_form));
            add_content(error_400_form);
            break;
        case NO_RESOURCE:
            add_status_line(404, error_404_title);
            add_headers(strlen(error_404_form));
            add_content(error_404_form);
            break;
        case FORBIDDEN_REQUEST:
            add_status_line(403, error_403_title);
            add_headers(strlen(error_403_form));
            add_content(error_403_form);
            break;
        case FILE_REQUEST:
            add_status_line(200, ok_200_title);
            add_headers(m_file_stat.st_size);
            //打开待发送文件的文件描述符
            m_file_fd = open(m_target_file, O_RDONLY);
        default:
            return false;
    }
    return true;
}

// void Http_conn::process()
// {
//     HTTP_CODE read_ret = NO_REQUEST;
//     //解析请求
//     while(read_ret == NO_REQUEST)
//     {
//         read_ret = process_read();
//     }
//     //得到请求，确定应答内容,填充发送缓冲区
//     process_write(read_ret);
//     //填充完成后，可以发送了，注册写事件 重置EPOLLONESHOT
//     modfd(m_epollfd, m_sockfd, EPOLLOUT);
// }
void Http_conn::process()
{
    if(M_READ) // 读任务
    {
        if(this->read())
        {
            HTTP_CODE read_ret = NO_REQUEST;
            //解析请求
            while(read_ret == NO_REQUEST)
            {
                read_ret = process_read();
            }
            //得到请求，确定应答内容,填充发送缓冲区
            process_write(read_ret);
            // 注册写事件
            modfd(m_epollfd, m_sockfd, EPOLLOUT);
        }
        M_READ = false;
    }
    if(M_WRITE) // 写任务
    {
        this->write();
        if(m_linger)//保持连接
        {
            this->init();
            //注册读事件
            modfd(m_epollfd, m_sockfd, EPOLLIN);
        }
        else
        {
            removefd(m_epollfd, m_sockfd);
        }
    }
}

//修改注册的事件
// void modfd( int epollfd, int fd, int ev )
// {
//     epoll_event event;
//     event.data.fd = fd;
//     event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;//重置EPOLLONESHOT
//     epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &event );
// }