#pragma once
#include <string>

using namespace std;

class Cookie
{
public:
	string key;
	string value;
	string path;
	int maxAge;
	Cookie(string _key, string _value);
	void setPath(string _path);
	void setMaxAge(int _maxAge);

private:

};
