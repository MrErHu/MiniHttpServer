/*
* Author:MrErHu
* Email:wanglei_cs@163.com
* Date:2016/2/11
*/

#ifndef MINIHTTPSERVER_REQUESTMESSAGE_H
#define MINIHTTPSERVER_REQUESTMESSAGE_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

typedef map<string, string> httpHeaders;    //http首部重定义
/*
 *请求报文类
 */
class RequestMessage{
private:
    string method;  //请求方法
    string request_URL; //请求URL
    string version; //  版本
    httpHeaders requsetHeaders; //请求报文首部
    string body; //请求首部

    //作用:去除string类型的首位空格
    std::string& trim(std::string &s);
public:
    /*
     * 作用:请求报文解析方法
     * 参数:string类型待解析报文
     * 返回:true:解析成功;false:解析失败
     */
    bool requestMessageParse(const string& http_requst);
    /*
     * 作用:根据KEY返回RequstMessage中httpHeaders相对应的值
     * 参数:string类型的KEY值
     * 返回:string类型的对应值
     */
    string getRequestHeadersValue(const string& KEY);
    /*
     * 下列成员函数用来返回RequestMessage成员变量
     */
    string getMethod(){return this->method;}
    string getRequst_URL(){return this->request_URL;}
    string getVersion(){return this->version;}
    string getBody(){return this->body;}
    httpHeaders& getRequsetHeaders(){return this->requsetHeaders;}
};
#endif //MINIHTTPSERVER_REQUESTMESSAGE_H * Author:MrErHu