#include "ResponseMessage.h"
#include "RequestMessage.h"
#include "ServerTool.h"

#define MAX_BACKLOG 100 //最大排队数量
#define BUFF_SIZE 1024*1024
#define SOCKET_PORT 8080

using namespace std;

string __http_docroot;
string __http_domain;

//服务器
int main()
{
    //监听socketfd
    int listenfd;
    //新的客户端sockfd
    int connfd;
    struct sockaddr_in ser_addr,cli_addr;
    socklen_t cli_len;
    int len = 0;
    //接受缓冲区:BUFF_SIZE大小
    char recv_buf[BUFF_SIZE];
    //解析配置文件
    //路径填入自定义的配置文件路径
    parseConfig("/Users/mr_wang/Documents/MiniHttpServer/MiniHttpServer.config");

    //调用自定义的函数创建socketfd
    listenfd=createSocket();
    if(-1 == listenfd)
    {
        cout<<"Failed to socket"<<endl;
        return -1;
    }
    //socket相关设置
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SOCKET_PORT);  //这里输入服务器端口号
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY表示本机IP
    //调用封装的系统调用进行bind
    socketBind(listenfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
    cout<<"Now listen..."<<endl;
    if(-1 == listen(listenfd,MAX_BACKLOG))
    {
        cout<<"Failed to listen"<<endl;
        return -2;
    }
    while(true)
    {
        memset(&cli_addr,0,sizeof(cli_addr));
        cli_len = sizeof(cli_addr);
        printf("Now accept...\n");
        connfd = socketAccept(listenfd,(struct sockaddr *)&cli_addr,&cli_len);
        if(-1 == connfd)
        {
            cout<<"Failed to accept"<<endl;
            break;
        }
        memset(recv_buf,0,sizeof(recv_buf));
        len = recv(connfd,recv_buf,sizeof(recv_buf),0);
        if(-1 == len)
        {
            perror("Failed to recv");
            return -1;
        }
        //http请求报文处理
        string receiveString(recv_buf);
        string responseString;
        RequestMessage requestMessage;
        requestMessage.requestMessageParse(receiveString);
        createResponseMessage(requestMessage,responseString);

        cout<<"Recv from client is "<<endl;
        cout<<recv_buf<<endl;
        cout<<responseString<<endl;
        const char *sendbuf = responseString.c_str();
        len=strlen(sendbuf);
        //http响应报文发送
        send(connfd,sendbuf,len,0);
        close(connfd);
    }
    close(listenfd);
    return 0;
}