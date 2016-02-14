/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */

#include "ServerTool.h"

/*
 * 作用:获得系统时间
 * 参数:无
 * 返回:string类型的当前时间
 */
string getTime()
{
    time_t nowtime;
    nowtime = time(NULL); //获取日历时间
    return ctime(&nowtime) ;
}
/*
 * 作用:根据http请求中URL和配置文件中的docroot构造真正的URL
 * 参数:string类型的URL
 * 返回:string类型的真实URL
 */
string makeRealURL(const string& url)
{
    string tempURL,realURL;
    int pos=url.find(__http_domain);
    if(pos!=-1)
    {//存在域名将其删去
        tempURL=url.substr(__http_domain.size(),url.size()-__http_domain.size());
    }
    else
    {//否则保持不变
        tempURL=url;
    }
    cout<<tempURL<<endl;
    if(__http_docroot[__http_docroot.size()-1] == '/')//配置项docroot末尾有'/'
    {
        if(tempURL[0] == '/')
            realURL = __http_docroot + tempURL.erase(0, 1);
        else
            realURL = __http_docroot + tempURL;
    }
    else//配置项docroot末尾没有'\'
    {
        if(tempURL[0] == '/')
            realURL = __http_docroot +tempURL;
        else
            realURL = __http_docroot + '/' + tempURL;
    }
    return realURL;
}
/*
 * 作用:测试是否存在文件
 * 参数:string类型的绝对文件路径
 * 返回:bool类型:true:文件存在;false:文件不存在
 */
bool fileIsExisted(const string& path)
{
    ifstream filein;
    filein.open(path);
    bool result=false;
    if(filein)
        result=true;
    filein.close();
    return result;
}
/*
 * 作用:获得文件的长度
 * 参数:string类型的绝对文件路径
 * 返回:int类型的文件长度,-1表示文件不存在
 */
int fileLength(const string& path)
{
    struct stat buf;
    const char *realPath=path.c_str();
    int ret= stat(realPath,&buf);
    if(ret==-1)
    {
        return -1;
    }
    return buf.st_size;
}
/*
 * 作用:获得文件的最后修改时间
 * 参数:string类型的绝对文件路径
 * 返回:string类型的文件最后修改时间
 */
string fileModifiedTime(const string& path)
{
    struct stat buf;
    const char *realPath=path.c_str();
    int ret= stat(realPath,&buf);
    if(ret==-1)
        return "";
    return ctime(&buf.st_mtime);
}
/*
 * 作用:配置文件解析
 * 参数:配置文件地址
 * 返回:bool类型 true:成功;false:失败
 */
bool parseConfig(const string& path)
{
    if(path.empty())//路径为空
        return false;
    ifstream infile;
    infile.open(path);
    if(!infile)//无法打开配置未见
        return false;
    string line,key,value;
    while(getline(infile,line))
    {
        stringstream sstream(line);
        sstream>> key;
        if(key=="docroot")
        {
            sstream>>__http_docroot;
        }
        if(key=="domain")
        {
            sstream>>__http_domain;
        }
    }
    infile.close();
    return true;
}
/*
    * 作用:设置文件标识符为非阻塞形式
    * 参数:int文件标识符
    * 返回:bool标识设置成功与否
    */
bool setSocketNonBloking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        return false;
    flags |= O_NONBLOCK;
    int ret = fcntl(fd, F_SETFL, flags);
    if (ret < 0)
        return false;
    return true;
}
/*
*函数作用：设置套接字SO_REUSEADDR选项
*函数参数：要设置的套接字
*函数返回值: 无
*/
bool setSocketREUSEADDR(int socketfd)
{
    int on = 1;
    int ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret == -1)
        return false;
    return true;
}
/*
*函数作用：开启套接字TCP_NODELAY选项，关闭nagle算法
*函数参数：要设置的套接字
*函数返回值: 无
*/
bool setOffTcpNagle(int socketfd)
{
    int on = 1;
    int ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
    if(ret == -1)
        return false;
    return true;
}
/*
*函数作用：关闭套接字TCP_NODELAY选项，开启nagle算法
*函数参数：要设置的套接字
*函数返回值: bool
*/
bool setOnTcpNagle(int socketfd)
{
    int off = 0;
    int ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, &off, sizeof(off));
    if(ret == -1)
        return false;
    return true;
}
/*
 *函数作用：设置套接字SO_RCVTIMEO选项，接收超时
 *函数参数：sockfd要设置的套接字, sec秒, usec毫秒
 *函数返回值: bool
 */
bool setSocketrecv_timeo(int sockfd, int sec, int usec)
{
    struct timeval time= {sec, usec};
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &time, sizeof(time));
    if(ret == -1)
        return false;
    return true;
}
/*
 *函数作用：设置套接字SO_SNDTIMEO选项，发送超时
 *函数参数：sockfd要设置的套接字, sec秒, usec毫秒
 *函数返回值:bool
 */
bool setSO_SNDTIMEO(int sockfd, int sec, int usec)
{
    struct timeval time= {sec, usec};
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &time, sizeof(time));
    if(ret == -1)
        return false;
    return true;

}
/*
 * 作用:创建套接字
 * 参数:无
 * 返回:生成的套接字fd
 */
int createSocket()
{
    int listen_fd;
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        exit(-1);
    }
    return listen_fd;
}
/*
 * 作用:封装系统调用的监听
 * 参数:套接字描述符sockfd和最大可排队序列blacklog
 * 返回:无
 */
void socketListen(int sockfd, int backlog)
{
    if(listen(sockfd, backlog) == -1)
    {
        exit(-1);
    }
}
/*
 * 作用:封装系统调用的bind操作
 * 参数sockfd：是由socket()调用返回的并且未作连接的套接字描述符(套接字号)。
 * 参数addr： 是赋给套接字s的本地地址（名字），其长度可变，结构随通信域的不同而不同。
 * 参数addlen：表明了name的长度。
 * 返回:无
 */
void socketBind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if(bind(sockfd, addr, addrlen) == -1)
    {
        exit(-1);
    }
    else
    {
        cout<<"bind success..."<<endl;
    }
}
/*
 * 作用:封装系统调用:accept()用于面向连接服务器。
 * 参数:addr和addrlen存放客户方的地址信息
 * 返回:ret_fd有相同特性的新套接字号。新的套接字可用于处理服务器并发请求。
 */
int socketAccept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret_fd = 0;
    for(;;)
    {
        ret_fd = accept(sockfd, addr, addrlen);
        if(ret_fd > 0)
            break;
        else if(ret_fd == -1)
        {
            //由于我们把监听套接字设置为了非阻塞模式
            if(errno != EAGAIN && errno != EPROTO &&
               errno != EINTR && errno != ECONNABORTED)
            {
                perror("accept");
                exit(-1);
            }
        }
        else
            continue;
    }
    return ret_fd;
}
/*
 * 作用:封装系统调用:getservbyname()返回与给定服务名对应的包含名字和服务号信息的servent结构指针。
 * 参数:name:一个指向服务名的指针 proto:指向协议名的指针
 * 返回:servent结构指针。
 */
struct servent* Getservbyname(const char *name, const char *proto)
{
    struct servent 	*pservent;
    if((pservent = getservbyname(name, proto)) == NULL)
    {
        perror("getservbyname");
        exit(-1);
    }
    return pservent;
}


