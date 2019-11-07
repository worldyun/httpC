#pragma once
#include <string>
#include<map>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Response
{
public:
	string respBody;
	int status;
	Response();
	string getResponse();
	void write(string writeBody);
	void write(json writeBody);
private:
	static void writeHttpStatus(Response * me);
	map<int, string> httpStatus;
	string date;
	string contentType;
	map<string, string> setHeader;
};

