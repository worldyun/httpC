#pragma once
#include "RouterMap.h"
#include "Request.h"
#include "Response.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "Cookie.h"
using namespace std;


class registerRouterTest : public RouterBaseClass
{
public:
	registerRouterTest();
	~registerRouterTest();
	void doServer(Request& req, Response& resp);

private:

};



RegisterRouter( "/test", registerRouterTest);

void registerRouterTest::doServer(Request& req, Response& resp) {


	Cookie cookie("Test123", "1234563789");
	cookie.setPath("/test");
	cookie.setMaxAge(60*60*24);
	resp.setCookie(cookie);
	resp.delCookie("Test123", "/test");
	cout << req.cookies.dump(4);



	string body = "Hello Router !";
	resp.write(body);

	
}

registerRouterTest::registerRouterTest()
{

}

registerRouterTest::~registerRouterTest()
{

}


