#include "Request.h"
#include <string>
#include <map>
#include <iostream>
#include "UrlCode.h"
#include "StringP.h"
#include <vector>
#include "json.hpp"
#include <sstream>
using json = nlohmann::json;
using namespace std;

void Request::requestPaser(string reqHeader, string reqBody) {
	//cout << reqHeader;
	vector<string> tempHeader;
	StringP::strSplit(reqHeader, tempHeader, "\r\n", 2);
	if (tempHeader.size() > 1)
	{
		string firstLine = tempHeader.at(0);
		vector<string> firstLineData;
		StringP::strSplit(firstLine, firstLineData, " ", 2);
		if (firstLineData.size() == 3)
		{
			this->reqHeaderData["httpMethod"] = firstLineData.at(0);
			this->reqHeaderData["url"] = firstLineData.at(1);
			this->url = firstLineData.at(1);
			this->host = StringP::strFindLeft(this->url, ":");
			vector<string> urlData;
			StringP::strSplit(this->url, urlData, "?");
			if (urlData.size() > 1)
			{
				this->dataPaser(urlData.at(1), this->getData);
			}
			this->router = urlData.at(0);
			this->reqHeaderData["versions"] = firstLineData.at(2);
			vector<string>::iterator oneLine;
			for (oneLine = tempHeader.begin() + 1; oneLine != tempHeader.end(); oneLine++)
			{
				vector<string> oneLineDatas;
				StringP::strSplit(*oneLine, oneLineDatas, ": ", 2);
				if (oneLineDatas.size() == 2)
				{
					this->reqHeaderData[oneLineDatas.at(0)] = oneLineDatas.at(1);
				}
			}
		}
	}
	//cout << this->reqHeaderData.dump(4);

	if (reqBody.length() > 0)
	{
		this->dataPaser(reqBody, this->postData);
	}
}

void Request::dataPaser(string strData , json& data) {
	strData = urldecode(strData);
	if (strData[0] != '{')
	{
		vector<string> datas;
		StringP::strSplit(strData, datas, "&", 2);
		vector<string>::iterator index;
		for (index = datas.begin(); index != datas.end(); index++)
		{
			vector<string> keyValue;
			StringP::strSplit(*index, keyValue, "=");
			if (keyValue.size() == 2)
			{
				data[keyValue.at(0)] = keyValue.at(1);
			}
		}
	}
	else
	{
		try
		{
			data = json::parse(strData);
		}
		catch (const std::exception&)
		{
			// 计划：写入日志文件
		}
	}

	//cout << data.dump(4) << endl;

}

string Request::getGetData(string key) {
	json::iterator strmapIter;
	strmapIter = this->getData.find(key);
	if (strmapIter != getData.end())
	{
		return strmapIter.value();
	}
	return "";
}
string Request::getPostData(string key) {
	json::iterator strmapIter;
	strmapIter = this->postData.find(key);
	if (strmapIter != postData.end())
	{
		return strmapIter.value();
	}
	return "";
}