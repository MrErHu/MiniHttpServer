C++实现的小型HTTP服务器</br>
开发IDE:Clion</br>
操作系统:OS X EI Capitan</br>
代码结构说明：</br>
RequestMessage.h/cpp定义了RequestMessage类：用于对于http请求报文的解析</br>
ResponseMessage.h/cpp：用于对于特定的请求报文生成响应报文</br>
ServerTool.h/cpp：http相应的服务工具</br>
main.cpp:主函数。控制socket通信</br>
说明：该http服务器实现了http服务的基本流程，暂时只支持文本格式的请求，请求方式支持HEAD和GET。需要开始在main函数里面定义配置文件的路径。</br>
运行情况：
![Image text](https://raw.githubusercontent.com/MrErHu/MiniHttpServer/master/picture/p2.png)
![Image text](https://raw.githubusercontent.com/MrErHu/MiniHttpServer/master/picture/p1.png）

              
