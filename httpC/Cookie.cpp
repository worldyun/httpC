#include "Cookie.h"
#include <string>
using namespace std;

Cookie::Cookie(string _key, string _value)
{
	this->key = _key;
	this->value = _value;
	this->maxAge = -100;
}
void Cookie::setPath(string _path) {
	this->path = _path;
}
void Cookie::setMaxAge(int _maxAge) {
	this->maxAge = _maxAge;
}

