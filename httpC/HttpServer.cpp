#include "HttpServer.h"
#include <iostream> 
#include <string>
#include "Request.h"
#include "Response.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


char* HttpServer::processData(string reqHeader, string reqBody) {
	
	Request req;
	req.requestPaser(reqHeader, reqBody);
	Response resp;

	//cout << req.getPostData("txtPWD");
	
	auto resBody = R"(
		{
			"Hello": "Http !",
			"Powered": "By",
			"C++": "Http Server",
			"Other": {
					"Author": "WorldYun",
					"Time": 20191107,
					"测试": "中文"
			}
		}
	)"_json;
	

	resp.write(resBody);
	resp.status = 301;

	string resData = resp.getResponse();
	//cout << resData;
	char* data = new char[resData.length()];
	resData.copy(data, string::npos, 0);
	return data;
}

int HttpServer::listen(int port) {
	if(this->startListen(port) == 200)
		std::cout << "Massage: Http Server has started on " << port << " !" << std::endl;
	return 0;
}