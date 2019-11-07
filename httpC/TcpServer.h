#pragma once

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") 
#include <iostream>
using namespace std;
class TcpServer
{
private:
	WORD sockVersion;
	WSADATA wsaData;
	SOCKET slisten;
	int listenPort;
	sockaddr_in sin;
	static void waitConn(TcpServer* const me);
	static int recvHttp(TcpServer* const me, SOCKET sClient, sockaddr_in remoteAddr);
	/*~TcpServer() {
		closesocket(slisten);
		WSACleanup();
	}*/
	

public:
	int startListen(int port = 8888);
	virtual char* processData(string reqHeader, string reqBody)=0;
};


