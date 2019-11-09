
// httpServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "RegisterRouter.h"
#include "HttpServer.h"

using namespace std;


int main(int argc, char* argv[])
{
	system("chcp 65001");
	system("cls");
	HttpServer server;
	server.listen(8888);
	getchar();
	return 0;
}



