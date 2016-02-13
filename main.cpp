#include "RequestMessage.h"
#include "ServerTool.h"
#include "ResponseMessage.h"

using namespace std;

string __http_docroot;
string __http_domain;

int main()
{
    parseConfig("/Users/mr_wang/Documents/MiniHttpServer/MiniHttpServer.config");
    RequestMessage requestMessage;
    string response;
    requestMessage.requestMessageParse("GET /test.html HTTP1.1\r\n\Lengh: 8080\r\n\Date: July Mon 2013\r\n\r\n<html>\nhaha\n</html>");
    cout<<requestMessage.getMethod()<<endl;
    cout<<requestMessage.getVersion()<<endl;
    cout<<requestMessage.getRequst_URL()<<endl;
    cout<<requestMessage.isValid()<<endl;
    cout<<requestMessage.getBody()<<endl;
    createResponseMessage(requestMessage,response);
    cout<<response<<endl;
}