#pragma once
#include <string>
#include<map>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Request
{
private:
	
	json reqHeaderData;
	void dataPaser(string strData, json &data);
	
public:
	json postData;
	json getData;
	json cookies;
	int status;
	string url;
	string router;
	string host;
	void requestPaser(string reqHeader, string reqBody);
	string getGetData(string key);
	string getPostData(string key);
};

