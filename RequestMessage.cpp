/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */
#include "RequestMessage.h"

    /*
     *作用:去除string类型的首位空格
     */
    string& RequestMessage::trim(std::string &s)
    {
        if (s.empty())
        {
            return s;
        }
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        return s;
    }
/*
     * 作用:请求报文解析方法
     * 参数:string类型待解析报文
     * 返回:true:解析成功;false:解析失败
     */
bool RequestMessage::requestMessageParse(const string& http_request)
{
    if(http_request.empty())
    {
        return false;
    }
    string crlf="\r\n";
    string crlfcrlf="\r\n\r\n";
    int pre=0,next=0;
    next=http_request.find(crlf,pre);
    if(next!=string::npos)
    {
        string requestLine=http_request.substr(pre,next-pre);
        stringstream sstream(requestLine);
        sstream>>this->method;
        sstream>>this->request_URL;
        sstream>>this->version;
        pre=next;
    }else
    {//没有查找到\r\n
        return false;
    }
    int pos_crlfcrlf=http_request.find(crlfcrlf,pre);
    if(pos_crlfcrlf==string::npos)
    {//不存在crlfcrlf
        return false;
    }
    string headBuff,key,value;
    while(true)
    {
        next=http_request.find(crlf,pre+2);
        if(next<=pos_crlfcrlf)
        {
            headBuff=http_request.substr(pre+2,next-pre-2);
            pre=next;
            int pos_devision=headBuff.find(":",0);
            if(pos_devision==string::npos)
                continue;
            key=headBuff.substr(0,pos_devision);
            value=headBuff.substr(pos_devision+1,headBuff.size()-pos_devision-1);
            this->trim(key);
            this->trim(value);
            this->requsetHeaders.insert(make_pair(key,value));
        }else//首部扫描完毕
        {
            break;
        }
    }
    //请求主体
    this->body=http_request.substr(pos_crlfcrlf+4,http_request.size()-pos_crlfcrlf-4);
}
/*
 * 作用:根据KEY返回RequstMessage中httpHeaders相对应的值
 * 参数:string类型的KEY值
 * 返回:string类型的对应值
 */
string RequestMessage::getRequestHeadersValue(const string& KEY)
{
    auto values=this->requsetHeaders.find(KEY);
    if(values!=this->requsetHeaders.end())//存在首部
    {
        return (*values).second;
    }
    else{//不存在首部
        return "";
    }
}