#pragma once
#include <string>
#include <vector>
using namespace std;

class StringP
{
public:
	static string strFind(string str, string left, string right);
	static string strFind(string str, string left, int length);
	static string strSplit(string str, vector<string>& rel, string flag, int time = 1);
	static string strFindLeft(string str, string flag);
};


