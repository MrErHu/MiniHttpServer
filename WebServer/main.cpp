#include "RequestMessage.h"
#include "ServerTool.h"
#include "ResponseMessage.h"

#define MAX_BACKLOG 100 //最大排队数量
#define BUFF_SIZE 1024*1024

using namespace std;

string __http_docroot;
string __http_domain;

int main()
{
    int listen_fd;
    int conn_sock;
    uint16_t listen_port;
    struct servent 		*pservent;
    struct sockaddr_in 	server_addr;
    struct sockaddr_in	client_addr;
    socklen_t 			addrlen;
    char rev[BUFF_SIZE];

    //创建监听套接字
    listen_fd = createSocket();
    //设置监听套接字为非阻塞模式
    setSocketNonBloking(listen_fd);
    //对监听套接字设置SO_REUSEADDR选项
    setSocketREUSEADDR(listen_fd);
    //通过服务名和协议名获得相应的知名端口
    pservent = Getservbyname("http", "tcp");
    //实际上设置了为80端口
    listen_port = pservent->s_port;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = (8090);//设置端口
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //将服务器sockaddr_in与监听套接字绑定
    socketBind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    //开始监听
    socketListen(listen_fd, MAX_BACKLOG);
    cout<<"Server Start......"<<endl;
    while(true)
    {
        conn_sock = socketAccept(listen_fd, (struct sockaddr*)&client_addr, &addrlen);
        if(conn_sock>=0)
        {
            cout<<"连接成功，开始通信"<<endl;
        }
        else
        {
            cout<<"连接失败"<<endl;\
            exit(-1);
        }
        //设置新链接上的套接字为非阻塞模式
        setSocketNonBloking(conn_sock);
        if(recv(conn_sock,rev,BUFF_SIZE,0)==-1)
        {
            break;
        }
        string requeststring(rev);
        string sendstring;
        RequestMessage requestMessage;
        requestMessage.requestMessageParse(requeststring);
        createResponseMessage(requestMessage,sendstring);
        const char *sed=sendstring.c_str();
        if(send(conn_sock, sed, strlen(sed) + 1, 0)==-1)
        {
            break;
        }
        close(conn_sock);
        continue;
    }
    close(listen_fd);
    return 0;
}