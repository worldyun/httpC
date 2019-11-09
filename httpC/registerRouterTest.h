#pragma once
#include "RouterMap.h"
#include "Request.h"
#include "Response.h"
#include <string>
#include <iostream>
#include "json.hpp"
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

	string body = "Hello Router !";
	resp.write(body);

	//cout << req.getData.dump(4);
}

registerRouterTest::registerRouterTest()
{

}

registerRouterTest::~registerRouterTest()
{

}


