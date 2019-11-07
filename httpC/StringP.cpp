#include "StringP.h"
#include <string>
using namespace std;

string StringP::strFind(string str, string left, string right) {
	int strStart = -1, strEnd = -1;
	string rel = "";
	strStart = str.find(left) + left.length();
	if (strStart >= left.length())
	{
		strEnd = str.find(right, strStart);
		if (strEnd > strStart)
		{
			rel.assign(str, strStart, strEnd - strStart);
		}
	}
	return rel;
}

string StringP::strFind(string str, string left, int length) {
	int strStart = -1;
	string rel = "";
	strStart = str.find(left) + left.length();
	if (strStart >= left.length())
	{
		length = length < (str.length() - strStart) ? length : (str.length() - strStart);
		rel.assign(str, strStart, length);
	}
	return rel;
}

string StringP::strFindLeft(string str, string flag) {
	int strStart = -1;
	string rel = "";
	strStart = str.find(flag);
	if (strStart > 0)
	{
		rel.assign(str, 0, strStart);
	}
	return rel;
}



string StringP::strSplit(string str, vector<string>& rel, string flag, int time) {
	time = time == 1 ? 1 : 99999999;
	string temp = "";
	int start = -1;
	start = str.find(flag);
	while (start >= 0 && time >=1)
	{
		temp.assign(str, 0 , start);
		str.assign(str, start + flag.length(), str.length() - (start + flag.length()));
		if (temp.length() > 0)
		{
			rel.push_back(temp);
		}
		start = str.find(flag);
		time--;
	}
	if (str.length() > 0)
	{
		rel.push_back(str);
	}
	if (rel.size() > 0)
	{
		return rel.at(0);
	}
	return "";
}