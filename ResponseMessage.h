/*
 * Author:MrErHu
 * Email:wanglei_cs@163.com
 * Date:2016/2/11
 */

#ifndef MINIHTTPSERVER_RESPONSEMESSAGE_H
#define MINIHTTPSERVER_RESPONSEMESSAGE_H

#include <iostream>
#include <string>
#include <vector>

#include "RequestMessage.h"
#include "ServerTool.h"

using namespace std;

//HTTP状态码
#define HTTP_CONTINUE 		100	//收到了请求的起始部分，客户端应该继续请求

#define HTTP_OK				200	//服务器已经成功处理请求
#define HTTP_ACCEPTED		202	//请求已接受，服务器尚未处理

#define HTTP_MOVED			301	//请求的URL已移走，响应应该包含Location URL
#define	HTTP_FOUND			302	//请求的URL临时移走，响应应该包含Location URL
#define HTTP_SEEOTHER		303	//告诉客户端应该用另一个URL获取资源，响应应该包含Location URL
#define HTTP_NOTMODIFIED	304	//资源未发生变化

#define HTTP_BADREQUEST		400	//客户端发送了一条异常请求
#define HTTP_FORBIDDEN		403	//服务器拒绝请求
#define HTTP_NOTFOUND		404	//URL未找到


#define HTTP_ERROR			500	//服务器出错
#define HTTP_NOIMPLEMENTED	501 //服务器不支持当前请求所需要的某个功能
#define HTTP_BADGATEWAY		502	//作为代理或网关使用的服务器遇到了来自响应链中上游的无效响应
#define HTTP_SRVUNAVAILABLE	503 //服务器目前无法提供请求服务，过一段时间后可以恢复

//HTTP友好语句
string http_ok = 			    "OK";
string http_badrequest = 	    "Bad Request";
string http_forbidden =		    "Forbidden";
string http_notfound = 		    "Not Found";
string http_noimplemented = 	"No Implemented";

//HTTP响应首部
#define TYHP_ACCEPTRANGE_HEAD			"Accpet-Range"
#define	TYHP_AGE_HEAD 					"Age"
#define	TYHP_ALLOW_HEAD					"Allow"
#define	TYHP_CONTENTBASE_HEAD			"Content-Base"
#define	TYHP_CONTENTLENGTH_HEAD			"Content-Length"
#define	TYHP_CONTENTLOCATION_HEAD		"Content-Location"
#define	TYHP_CONTENTRANGE_HEAD			"Content-Range"
#define	TYHP_CONTENTTYPE_HEAD			"Content-Type"
#define	TYHP_DATE_HEAD					"Date"
#define	TYHP_EXPIRES_HEAD				"Expires"
#define	TYHP_LAST_MODIFIED_HEAD			"Last-Modified"
#define	TYHP_LOCATION_HEAD 				"Location"
#define	TYHP_PUBLIC_HEAD				"Public"
#define TYHP_RANGE_HEAD 				"Range"
#define	TYHP_SERVER_HEAD				"Server"

/*
 *函数作用：通过HTTP状态码返回友好语句
 *函数参数：int:HTTP状态码
 *函数返回值:string:友好语句
 */
string parseCodeToStatement(int HTTPcode);
/*
 *作用：根据解析下来的RequestMessage来处理客户的请求
 *参数: RequestMessage:解析出来的请求requestMessage;string:生成的responseMessage
 *返回值: HTTP状态码
 *目前支持的请求首部：GET HEAD
 *目前支持的响应首部：Date，Content-Base，Content-Length，Content-Location,Last-Modified，Public，Server
 */
int  createResponseMessage(RequestMessage requestMessage,string responseMessage);

#endif //MINIHTTPSERVER_RESPONSEMESSAGE_H
