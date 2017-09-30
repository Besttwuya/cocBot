#pragma once
#ifndef BOTHELP_H__
#define BOTHELP_H__
#include <string.h>
#include <vector>

using std::vector;
using std::string;
/*字符串分割函数*/
void _split(const std::string& s, vector<string>& v, const std::string& c);
/*分割*/
//void Split(const CString& s, vector<CString>&v, const CString& c);
/*获取网络时间，格式：20|17 07 03 20 04 */
int GetNetTime(char* res,unsigned int nLen);
/**/
#endif