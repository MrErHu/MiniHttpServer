/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */

#ifndef MINIHTTPSERVER_RESPONSEMESSAGE_H
#define MINIHTTPSERVER_RESPONSEMESSAGE_H

#include <iostream>
#include <map>

using namespace std;

//MIME节点类型
struct MIMENode
{
    const string type;
    const string value;
};
//支持的MIME集合
MIMENode mimeSet[] =
        {
                {".html", "text/html"},
                {".xml", "text/xml"},
                {".xhtml", "application/xhtml+xml"},
                {".txt", "text/plain"},
                {".rtf", "application/rtf"},
                {".pdf", "application/pdf"},
                {".word", "application/msword"},
                {".png", "image/png"},
                {".gif", "image/gif"},
                {".jpg", "image/jpeg"},
                {".jpeg", "image/jpeg"},
                {".au", "audio/basic"},
                {".mpeg", "video/mpeg"},
                {".mpg", "video/mpeg"},
                {".avi", "video/x-msvideo"},
                {".gz", "application/x-gzip"},
                {".tar", "application/x-tar"},
                {NULL ,NULL}
        };
//HTTP状态码
#define HTTP_CONTINUE 		    100	//收到了请求的起始部分，客户端应该继续请求

#define HTTP_OK				    200	//服务器已经成功处理请求
#define HTTP_ACCEPTED		    202	//请求已接受，服务器尚未处理

#define HTTP_MOVED			    301	//请求的URL已移走，响应应该包含Location URL
#define	HTTP_FOUND			    302	//请求的URL临时移走，响应应该包含Location URL
#define HTTP_SEEOTHER		    303	//告诉客户端应该用另一个URL获取资源，响应应该包含Location URL
#define HTTP_NOTMODIFIED	    304	//资源未发生变化

#define HTTP_BADREQUEST		    400	//客户端发送了一条异常请求
#define HTTP_FORBIDDEN		    403	//服务器拒绝请求
#define HTTP_NOTFOUND		    404	//URL未找到

#define HTTP_ERROR			    500	//服务器出错
#define HTTP_NOIMPLEMENTED	    501 //服务器不支持当前请求所需要的某个功能
#define HTTP_BADGATEWAY		    502	//作为代理或网关使用的服务器遇到了来自响应链中上游的无效响应
#define HTTP_SRVUNAVAILABLE	    503 //服务器目前无法提供请求服务，过一段时间后可以恢复

//友好语句
string http_ok = 			    "OK";
string http_badrequest = 	    "Bad Request";
string http_forbidden =		    "Forbidden";
string http_notfound = 		    "Not Found";
string http_noimplemented = 	"No Implemented";

//HTTP响应首部
#define HTTP_ACCEPTRANGE_HEAD			"Accpet-Range"
#define	HTTP_AGE_HEAD 					"Age"
#define	HTTP_ALLOW_HEAD					"Allow"
#define	HTTP_CONTENTBASE_HEAD			"Content-Base"
#define	HTTP_CONTENTLENGTH_HEAD			"Content-Length"
#define	HTTP_CONTENTLOCATION_HEAD		"Content-Location"
#define	HTTP_CONTENTRANGE_HEAD			"Content-Range"
#define	HTTP_CONTENTTYPE_HEAD			"Content-Type"
#define	HTTP_DATE_HEAD					"Date"
#define	HTTP_EXPIRES_HEAD				"Expires"
#define	HTTP_LAST_MODIFIED_HEAD			"Last-Modified"
#define	HTTP_LOCATION_HEAD 				"Location"
#define	HTTP_PUBLIC_HEAD				"Public"
#define HTTP_RANGE_HEAD 				"Range"
#define	HTTP_SERVER_HEAD				"Server"



/*
 *作用：将MIME的type转换为相应的value
 *参数：type
 *返回: NULL表示type在MIME中不存在，否则返回相应value的指针
 */
string parseMIMEValue(const string key);
/*
 *作用：通过HTTP状态码返回友好语句
 *参数：HTTP状态码
 *返回: 相应的语句
*/
string getStateByCodes(int http_codes);


#endif //MINIHTTPSERVER_RESPONSEMESSAGE_H
