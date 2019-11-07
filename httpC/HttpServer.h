#pragma once
#include "TcpServer.h"
#include <iostream>

using namespace std;

class HttpServer : public TcpServer
{

public:
	virtual char* processData(string reqHeader, string reqBody);
	int listen(int port = 8888);
};

