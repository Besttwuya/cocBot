#pragma once
#ifndef BOTHELP_H__
#define BOTHELP_H__
#include <string.h>
#include <vector>

using std::vector;
using std::string;
/*�ַ����ָ��*/
void _split(const std::string& s, vector<string>& v, const std::string& c);
/*�ָ�*/
//void Split(const CString& s, vector<CString>&v, const CString& c);
/*��ȡ����ʱ�䣬��ʽ��20|17 07 03 20 04 */
int GetNetTime(char* res,unsigned int nLen);
/**/
#endif