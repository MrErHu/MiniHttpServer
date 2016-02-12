/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */

#ifndef MINIHTTPSERVER_SERVERTOOL_H
#define MINIHTTPSERVER_SERVERTOOL_H

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <time.h>
#include <sys/stat.h>


using namespace std;

extern string __http_docroot;
extern string __http_domain;

/*
 * 作用:获得系统时间
 * 参数:无
 * 返回:string类型的当前时间
 */
string getTime();
/*
 * 作用:根据http请求中URL和配置文件中的docroot构造真正的URL
 * 参数:string类型的URL
 * 返回:string类型的真实URL
 */
string makeRealURL(const string& url);
/*
 * 作用:测试是否存在文件
 * 参数:string类型的绝对文件路径
 * 返回:bool类型:true:文件存在;false:文件不存在
 */
bool fileIsExisted(const string& path);
/*
 * 作用:获得文件的长度
 * 参数:string类型的绝对文件路径
 * 返回:int类型的文件长度,-1表示文件不存在
 */
int fileLength(const string& path);
/*
 * 作用:获得文件的最后修改时间
 * 参数:string类型的绝对文件路径
 * 返回:string类型的文件最后修改时间
 */
string fileModifiedTime(const string& path);
/*
 * 作用:配置文件解析
 * 参数:配置文件地址
 * 返回:bool类型 true:成功;false:失败
 */
bool parseConfig(const string& path);
/*
    * 作用:设置文件标识符为非阻塞形式
    * 参数:int文件标识符
    * 返回:bool标识设置成功与否
    */
bool setFileNonBloking(int fd);
/*
*函数作用：设置套接字SO_REUSEADDR选项
*函数参数：要设置的套接字
*函数返回值: 无
*/
bool setSocketREUSEADDR(int socketfd);
/*
*函数作用：关闭套接字TCP_NODELAY选项，开启nagle算法
*函数参数：要设置的套接字
*函数返回值: 无
*/
bool setOnTcpNagle(int socketfd);
/*
 *函数作用：设置套接字SO_RCVTIMEO选项，接收超时
 *函数参数：sockfd要设置的套接字, sec秒, usec毫秒
 *函数返回值: bool
 */
bool setSocketrecv_timeo(int sockfd, int sec, int usec);
/*
 *函数作用：设置套接字SO_SNDTIMEO选项，发送超时
 *函数参数：sockfd要设置的套接字, sec秒, usec毫秒
 *函数返回值:bool
 */
bool setSO_SNDTIMEO(int sockfd, int sec, int usec);
/*
 * 作用:创建套接字
 * 参数:无
 * 返回:生成的套接字fd
 */
int createSocket();
/*
 * 作用:封装系统调用的监听
 * 参数:套接字描述符sockfd和最大可排队序列blacklog
 * 返回:无
 */
void socketListen(int sockfd, int backlog);
/*
 * 作用:封装系统调用的bind操作
 * 参数sockfd：是由socket()调用返回的并且未作连接的套接字描述符(套接字号)。
 * 参数addr： 是赋给套接字s的本地地址（名字），其长度可变，结构随通信域的不同而不同。
 * 参数addlen：表明了name的长度。
 * 返回:无
 */
void socketBind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
/*
 * 作用:封装系统调用:accept()用于面向连接服务器。
 * 参数:addr和addrlen存放客户方的地址信息
 * 返回:ret_fd有相同特性的新套接字号。新的套接字可用于处理服务器并发请求。
 */
int socketAccept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
/*
 * 作用:封装系统调用:getservbyname()返回与给定服务名对应的包含名字和服务号信息的servent结构指针。
 * 参数:name:一个指向服务名的指针 proto:指向协议名的指针
 * 返回:servent结构指针。
 */
struct servent* Getservbyname(const char *name, const char *proto);

#endif //MINIHTTPSERVER_SERVERTOOL_H
