/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */
#include "ResponseMessage.h"
/*
 *函数作用：通过HTTP状态码返回友好语句
 *函数参数：int:HTTP状态码
 *函数返回值:string:友好语句
 */
string parseCodeToStatement(int HTTPcode)
{
    switch (HTTPcode)
    {
        case HTTP_OK:
            return http_ok;
        case HTTP_BADREQUEST:
            return http_badrequest;
        case HTTP_FORBIDDEN:
            return http_forbidden;
        case HTTP_NOTFOUND:
            return http_notfound;
        case HTTP_NOIMPLEMENTED:
            return http_noimplemented;
        default:
            break;
    }
    return "";
}
/*
 *作用：根据解析下来的RequestMessage来处理客户的请求
 *参数: RequestMessage:解析出来的请求requestMessage;string:生成的responseMessage
 *返回值: HTTP状态码
 *目前支持的请求首部：GET HEAD
 *目前支持的响应首部：Date，Content-Base，Content-Length，Content-Location,Last-Modified，Public，Server
 */
int  createResponseMessage(RequestMessage &requestMessage,string& responseMessage)
{
    if(!requestMessage.isValid())
    {//请求RequestMessage无效
        return HTTP_BADREQUEST;
    }
    if(!responseMessage.empty())
    {//如果生成报文不为空,则清空
     responseMessage.clear();
    }
    //通用
    string crlf="\r\n";
    string statusLine=requestMessage.getVersion()+" ";
    string server= "Server: MiniHTTPServer";
    string content_base= "Content-Base: "+__http_domain;
    string date= "Date: "+getTime();
    //文件相关
    string contentLength="Content-Length: ";
    string contentLocation="Content-Location: ";
    string contentLastModified="Last-Modified: ";
    //请求方法
    string method= requestMessage.getMethod();
    string realURL= makeRealURL(requestMessage.getRequst_URL());
    string version= requestMessage.getVersion();
    //
    if(method == "GET")
    {//GET首部
        if(!fileIsExisted(realURL))
        {//不存在请求的文件
            statusLine+=to_string(HTTP_NOTFOUND)+" ";
            statusLine+=parseCodeToStatement(HTTP_NOTFOUND);
            responseMessage=statusLine+crlf;
            responseMessage+=server+crlf;
            responseMessage+=date+crlf;
            return HTTP_NOTFOUND;
        }
        else
        {//存在请求的文件
            statusLine+=to_string(HTTP_OK)+" ";
            statusLine+=parseCodeToStatement(HTTP_OK);
            responseMessage=statusLine+crlf;
            responseMessage+=contentLength+to_string(fileLength(realURL))+crlf;
            responseMessage+=server+crlf;
            responseMessage+=content_base+crlf;
            responseMessage+=date+crlf;
            responseMessage+=contentLastModified+fileModifiedTime(realURL)+crlf;
            responseMessage+=crlf;
            //读取body
            fstream infile;
            string fileLine;
            infile.open(realURL);
            while(getline(infile,fileLine))
                responseMessage+=fileLine+crlf;
        }
    }
    else if( method=="HEAD")
    {//HEAD首部
        if(!fileIsExisted(realURL))
        {//不存在请求的文件
            statusLine+=to_string(HTTP_NOTFOUND)+" ";
            statusLine+=parseCodeToStatement(HTTP_NOTFOUND);
            responseMessage=statusLine+crlf;
            responseMessage+=server+crlf;
            responseMessage+=date+crlf;
            return HTTP_NOTFOUND;
        }
        else
        {//存在请求的文件
            statusLine+=to_string(HTTP_OK)+" ";
            statusLine+=parseCodeToStatement(HTTP_OK);
            responseMessage=statusLine+crlf;
            responseMessage+=contentLength+to_string(fileLength(realURL))+crlf;
            responseMessage+=server+crlf;
            responseMessage+=content_base+crlf;
            responseMessage+=date+crlf;
            responseMessage+=contentLastModified+fileModifiedTime(realURL)+crlf;
            responseMessage+=crlf;
            return HTTP_OK;
        }
    }
    else if(method == "PUT" || method =="DELETE" || method=="POST")
    {//暂时不支持的首部
        statusLine+=to_string(HTTP_NOIMPLEMENTED)+" ";
        statusLine+=parseCodeToStatement(HTTP_NOIMPLEMENTED);
        responseMessage=statusLine+crlf;
        responseMessage+=server+crlf;
        responseMessage+=date+crlf;
        return HTTP_NOIMPLEMENTED;
    }
    else
    {//错误请求
        statusLine+=to_string(HTTP_BADREQUEST)+" ";
        statusLine+=parseCodeToStatement(HTTP_BADREQUEST);
        responseMessage=statusLine+crlf;
        return HTTP_BADREQUEST;
    }
}