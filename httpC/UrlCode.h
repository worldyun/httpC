#pragma once

#include<iostream>  
#include<stdio.h>   

/*
using namespace std;
static unsigned char char_to_hex(unsigned char x)
{
	return (unsigned char)(x > 9 ? x + 55: x + 48);
}

static int is_alpha_number_char(unsigned char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

//url编码实现   

void urlencode(unsigned char* src, int  src_len, unsigned char* dest, int  dest_len)
{
	unsigned char ch;
	int  len = 0;

	while (len < (dest_len - 4) && *src)
	{
		ch = (unsigned char)*src;
		if (*src == ' ')
		{
			*dest++ = '+';
		}
		else if (is_alpha_number_char(ch) || strchr("=!~*'()", ch))
		{
			*dest++ = *src;
		}
		else
		{
			*dest++ = '%';
			*dest++ = char_to_hex((unsigned char)(ch >> 4));
			*dest++ = char_to_hex((unsigned char)(ch % 16));
		}
		++src;
		++len;
	}
	*dest = 0;
	return;
}



//解url编码实现   

unsigned char* urldecode(unsigned char* encd, unsigned char* decd)
{
	int j, i;
	char* cd = (char*)encd;
	char p[2];
	unsigned int num;
	j = 0;

	for (i = 0; i < strlen(cd); i++)
	{
		memset(p, '/0', 2);
		if (cd[i] != '%')
		{
			decd[j++] = cd[i];
			continue;
		}

		p[0] = cd[++i];
		p[1] = cd[++i];

		p[0] = p[0] - 48 - ((p[0] >= 'A') ? 7 : 0) - ((p[0] >= 'a') ? 32 : 0);
		p[1] = p[1] - 48 - ((p[1] >= 'A') ? 7 : 0) - ((p[1] >= 'a') ? 32 : 0);
		decd[j++] = (unsigned char)(p[0] * 16 + p[1]);

	}
	decd[j] = '/0';

	return decd;
}
*/

static int php_htoi(char* s)
{
	int value;
	int c;

	c = ((unsigned char*)s)[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = ((unsigned char*)s)[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
}
/* }}} */

/* {{{ URL解码，提取自PHP 5.2.17
   用法：string urldecode(string str_source)
   时间：2012-8-14 By Dewei
*/
string urldecode(string& str_source)
{
	char const* in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	char* str;

	str = _strdup(in_str);
	char* dest = str;
	char* data = str;

	while (in_str_len--) {
		if (*data == '+') {
			*dest = ' ';
		}
		else if (*data == '%' && in_str_len >= 2 && isxdigit((int) * (data + 1))
			&& isxdigit((int) * (data + 2))) {
			*dest = (char)php_htoi(data + 1);
			data += 2;
			in_str_len -= 2;
		}
		else {
			*dest = *data;
		}
		data++;
		dest++;
	}
	*dest = '\0';
	out_str_len = dest - str;
	out_str = str;
	free(str);
	return out_str;
}







string urlencode(string& str_source)
{
	char const* in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	string out_str;
	register unsigned char c;
	unsigned char* to, * start;
	unsigned char const* from, * end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char*)in_str;
	end = (unsigned char*)in_str + in_str_len;
	start = to = (unsigned char*)malloc(3 * in_str_len + 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;

	out_str_len = to - start;
	out_str = (char*)start;
	free(start);
	return out_str;
}
/* }}} */

/* {{{ URL编码CString版，提取自PHP 5.2.17
   用法：CString urlencode(CString str_source)
   说明：仅不编码 -_. 其余全部编码，空格会被编码为 +
   时间：2012-8-13 By Dewei
*/
/*CString urlencode(CString& str_source)
{
	char const* in_str = str_source;
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	CString out_str = '\0';
	register unsigned char c;
	unsigned char* to, * start;
	unsigned char const* from, * end;
	unsigned char hexchars[] = "0123456789ABCDEF";

	from = (unsigned char*)in_str;
	end = (unsigned char*)in_str + in_str_len;
	start = to = (unsigned char*)malloc(3 * in_str_len + 1);

	while (from < end) {
		c = *from++;

		if (c == ' ') {
			*to++ = '+';
		}
		else if ((c < '0' && c != '-' && c != '.') ||
			(c < 'A' && c > '9') ||
			(c > 'Z' && c < 'a' && c != '_') ||
			(c > 'z')) {
			to[0] = '%';
			to[1] = hexchars[c >> 4];
			to[2] = hexchars[c & 15];
			to += 3;
		}
		else {
			*to++ = c;
		}
	}
	*to = 0;

	out_str_len = to - start;
	out_str = (char*)start;
	free(start);
	return out_str;
}
*/









std::string UrlDecode(const std::string& szToDecode)

{

	std::string result;

	int hex = 0;

	for (size_t i = 0; i < szToDecode.length(); ++i)

	{

		switch (szToDecode[i])

		{

		case '+':

			result += ' ';

			break;

		case '%':

			if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))

			{

				std::string hexStr = szToDecode.substr(i + 1, 2);

				hex = strtol(hexStr.c_str(), 0, 16);

				//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]  

				  //可以不经过编码直接用于URL  

				if (!((hex >= 48 && hex <= 57) || //0-9  

					(hex >= 97 && hex <= 122) ||   //a-z  

					(hex >= 65 && hex <= 90) ||    //A-Z  

					//一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]  

					hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29

					|| hex == 0x2a || hex == 0x2b || hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f

					|| hex == 0x3A || hex == 0x3B || hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f

					))

				{

					result += char(hex);

					i += 2;

				}

				else result += '%';

			}
			else {

				result += '%';

			}

			break;

		default:

			result += szToDecode[i];

			break;

		}

	}

	return result;

}