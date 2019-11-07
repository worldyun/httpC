#include "Response.h"
#include <iostream> 
#include <time.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

Response::Response() {
	this->status = 200;
	this->respBody = "<html><head></head><body><h1>Hello Http !</h1></br><h2>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -- Powered By C++ Http Server<h2></body></html>";
	time_t rawtime;
	struct tm* info;
	char nowTime[80];
	time(&rawtime);
	rawtime = rawtime - 3600 * 8;
	info = localtime(&rawtime);
	strftime(nowTime, 80, "%a, %d %b %Y %H:%M:%S GMT", info);
	nowTime[29] = '\0';
	this->date = nowTime;
	this->contentType = "text/html; charset=UTF-8";
	Response::writeHttpStatus(this);
}

string Response::getResponse() {
	string rel = "";
	rel += "HTTP/1.1 ";
	rel += to_string(this->status);
	rel += " ";
	map<int, string>::iterator strmapIter;
	strmapIter = this->httpStatus.find(this->status);
	if (strmapIter != this->httpStatus.end())
	{
		rel += strmapIter->second;
	}
	rel += "\rContent-Type: ";
	rel += this->contentType;
	rel += "\rdate: ";
	rel += this->date;
	rel += "\rContent-Length: ";
	rel += to_string(this->respBody.length());
	rel += "\r\n\r\n";
	rel += this->respBody;
	return rel;
}

void Response::write(json writeBody) {
	this->respBody = writeBody.dump();
	this->contentType = "text/json; charset=UTF-8";
}

void Response::write(string writeBody) {
	this->respBody = writeBody;
	this->contentType = "text/html; charset=UTF-8";
}

void Response::writeHttpStatus(Response* me) {
	me->httpStatus[100] = "Continue";
	me->httpStatus[101] = "Switching Protocols";
	me->httpStatus[200] = "OK";
	me->httpStatus[201] = "Created";
	me->httpStatus[202] = "Accepted";
	me->httpStatus[203] = "Non-Authoritative Information";
	me->httpStatus[204] = "No Content";
	me->httpStatus[205] = "Reset Content";
	me->httpStatus[206] = "Partial Content";
	me->httpStatus[300] = "Multiple Choices";
	me->httpStatus[301] = "Moved Permanently";
	me->httpStatus[302] = "Found";
	me->httpStatus[303] = "See Other";
	me->httpStatus[304] = "Not Modified";
	me->httpStatus[305] = "Use Proxy";
	me->httpStatus[306] = "Unused";
	me->httpStatus[307] = "Temporary Redirect";
	me->httpStatus[400] = "Bad Request";
	me->httpStatus[401] = "Unauthorized";
	me->httpStatus[402] = "Payment Required";
	me->httpStatus[403] = "Forbidden";
	me->httpStatus[404] = "Not Found";
	me->httpStatus[405] = "Method Not Allowed";
	me->httpStatus[406] = "Not Acceptable";
	me->httpStatus[407] = "Proxy Authentication Required";
	me->httpStatus[408] = "Request Time-out";
	me->httpStatus[409] = "Conflict";
	me->httpStatus[410] = "Gone";
	me->httpStatus[411] = "Length Required";
	me->httpStatus[412] = "Precondition Failed";
	me->httpStatus[413] = "Request Entity Too Large";
	me->httpStatus[414] = "Request-URI Too Large";
	me->httpStatus[415] = "	Unsupported Media Type";
	me->httpStatus[416] = "Requested range not satisfiable";
	me->httpStatus[417] = "Expectation Failed";
	me->httpStatus[500] = "Internal Server Error";
	me->httpStatus[501] = "Not Implemented";
	me->httpStatus[502] = "Bad Gateway";
	me->httpStatus[503] = "Service Unavailable";
	me->httpStatus[504] = "Gateway Time-out";
	me->httpStatus[505] = "HTTP Version not supported";
}