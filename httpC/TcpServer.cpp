#include "TcpServer.h"
#include <iostream>
#include <winsock2.h>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib") 

/*
*
*	emmmmm,这写的什么玩意儿。。。。
*
*	以后改，先留个标记
*
*/

int TcpServer::recvHttp(TcpServer* const me, SOCKET sClient, sockaddr_in remoteAddr) {

	
	if (sClient == INVALID_SOCKET)
	{
		std::cout << "ERROR: accept error !" << std::endl;
		return 0;
	}
	while (true)
	{
		string revData = "", revHeader = "", revBody = "";
		int httpHeadLenth = 0;
		while (true)
		{
			//cout << "111";
			char data[1500];
			int ret = recv(sClient, data, 1400, 0);
			if (ret >= 0)
			{
				data[ret] = 0x00;
				char *nedata = new char[ret+1];
				strncpy(nedata, data, ret+1);
				revData += nedata;
				delete []nedata;
			}
			httpHeadLenth = revData.find("\r\n\r\n");
			if (httpHeadLenth > 0)
			{
				revHeader.assign(revData, 0, httpHeadLenth);
				revData.assign(revData, httpHeadLenth+4, revData.length() - (httpHeadLenth + 4));
				break;
			}
		}
		int connection = revHeader.find("Connection: keep-alive");
		int transferEncoding = revHeader.find("Transfer-Encoding: chunked");
		int contentLength = revHeader.find("Content-Length");
		
		
		if (contentLength >= 0)
		{
			int contentLengthAt = revHeader.find("Content-Length");
			string contentLength;
			contentLength.assign(revHeader, contentLengthAt + 16 , (revHeader.find('\r', contentLengthAt) - contentLengthAt - 16));
			if (contentLength.length() > 0)
			{
				int bodyLength = 0;
				stringstream ssTemp; //仅作类型转换的临时变量，无他用
				ssTemp << contentLength;
				ssTemp >> bodyLength;
				while (true)
				{
					//cout << 222;
					if (revData.length() >= bodyLength)
					{
						revBody.assign(revData, 0, bodyLength);
						break;
					}
					char data[1500];
					int ret = recv(sClient, data, 1500, 0);
					if (ret >= 0)
					{
						data[ret] = 0x00;
						char* nedata = new char[ret + 1];
						strncpy(nedata, data, ret + 1);
						revData += nedata;
						delete[]nedata;
					}
				}
			}
			const char* sendData = me->processData(revHeader, revBody);
			send(sClient, sendData, strlen(sendData), 0);
			closesocket(sClient);
			delete[]sendData;
			break;
		}
		else if (connection >= 0 || transferEncoding >= 0)
		{
			if (revData.length()>0)
			{
				
				while (true)
				{
					//cout << 333;
					int httpBodyLenth = revData.find("\r\n0\r\n");
					if (httpBodyLenth > 0)
					{
						revBody.assign(revData, 0, httpBodyLenth);
						break;
					}
					char data[1500];
					int ret = recv(sClient, data, 1500, 0);
					if (ret >= 0)
					{
						data[ret] = 0x00;
						char* nedata = new char[ret + 1];
						strncpy(nedata, data, ret + 1);
						revData += nedata;
						delete[]nedata;
					}
					else
					{
						revBody = revData;
						break;
					}
					httpBodyLenth = revData.find("\r\n0\r\n");
					if (httpBodyLenth > 0 )
					{
						revBody.assign(revData, 0, httpBodyLenth);
						break;
					}
				}
			}
			const char* sendData = me->processData(revHeader, revBody);
			send(sClient, sendData, strlen(sendData), 0);
			closesocket(sClient);
			delete[]sendData;
			break;
		}
		else 
		{
			
			if (revData.length() > 0)
			{
				while (true)
				{
					//cout << 444;
					int httpBodyLenth = revData.find("\r\n0\r\n");
					if (httpBodyLenth > 0)
					{
						revBody.assign(revData, 0, httpBodyLenth);
						break;
					}
					char data[1500];
					int ret = recv(sClient, data, 1500, 0);
					if (ret >= 0)
					{
						data[ret] = 0x00;
						char* nedata = new char[ret + 1];
						strncpy(nedata, data, ret + 1);
						revData += nedata;
					}
					else
					{
						revBody = revData;
						break;
					}
					httpBodyLenth = revData.find("\r\n0\r\n");
					if (httpBodyLenth > 0 )
					{
						revBody.assign(revData, 0, httpBodyLenth);
						break;
					}
				}
			}
			const char* sendData = me->processData(revHeader, revBody);
			send(sClient, sendData, strlen(sendData), 0);
			closesocket(sClient);
			break;
			
			/*
			const char* sendData = me->processData(revHeader, revBody);
			send(sClient, sendData, strlen(sendData), 0);
			closesocket(sClient);
			delete sendData;
			break;
			*/
		}
	}
	return 200;
}


void TcpServer::waitConn(TcpServer * const me) {
	//vector<SOCKET> sClient;
	//SOCKET sClient;
	while (true)
	{
		//sClient = new SOCKET;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		SOCKET sClient = accept(me->slisten, (SOCKADDR*)& remoteAddr, &nAddrlen);
		std::thread(&TcpServer::recvHttp, me, sClient, remoteAddr).detach();
		//sClient.push_back(accept(me->slisten, (SOCKADDR*)& remoteAddr, &nAddrlen));
		//std::thread(&TcpServer::doServer, me, sClient.back(), remoteAddr).detach();
		//thread(doServer, i, numOfThreads, ref(frame), ref(outBinaryImage), ref(fps), ref(isPlay)).detach();
	}
}

int TcpServer::startListen(int port) {
	this->listenPort = port;
	sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字  
	slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		std::cout << "ERROR: create socket error !" << std::endl;
		return 1;
	}

	//绑定IP和端口  
	sin.sin_family = AF_INET;
	sin.sin_port = htons(listenPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)& sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::cout << "ERROR: bind error !" << std::endl;
		return 2;
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		std::cout << "ERROR: listen error !" << std::endl;
		return 3;
	}
	std::cout << "Massage: TCP Server has started on " << this->listenPort << " !" << std::endl;
	std::thread(&TcpServer::waitConn,this).detach();
	return 200;
}