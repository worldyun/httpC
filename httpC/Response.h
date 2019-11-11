#pragma once
#include <string>
#include <map>
#include <vector>
#include "json.hpp"
#include "Cookie.h"
using json = nlohmann::json;
using namespace std;




class Response
{
public:
	string respBody;
	int status;
	string router;

	Response();
	string getResponse();
	void write(string writeBody);
	void write(json writeBody);
	void setCookie(string key, string value);
	void setCookie(Cookie cookie);
	void delCookie(string key, string path);

private:
	map<int, string> httpStatus;
	string date;
	string contentType;
	map<string, string> setHeader;
	vector<Cookie> cookies;

	string getCookies();
	static void writeHttpStatus(Response * me);

};


