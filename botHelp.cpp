
#include "stdafx.h"
#include "botHelp.h"



void _split(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	int cout = 0;
	std::string::size_type pos1, pos2;
	//先确定大小
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		//v.push_back(s.substr(pos1, pos2 - pos1));
		cout++;
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		//v.push_back(s.substr(pos1));
		cout++;
	//*加进去
	pos2 = s.find(c);
	pos1 = 0;
	v.resize(cout);
	int index = 0;
	while (std::string::npos != pos2)
	{
		v[index] = s.substr(pos1, pos2 - pos1);
		index++;
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v[index] = s.substr(pos1, pos2 - pos1);
	index++;
}
void Split(const CString& s, vector<CString>&v, const CString& c)
{
	int cout = 0;
	int pos1, pos2;
	//先确定大小
	int clen = c.GetLength();
	pos2 = s.Find(c);
	pos1 = 0;
	while (-1 != pos2)
	{
		//v.push_back(s.substr(pos1, pos2 - pos1));
		cout++;
		pos1 = pos2 + clen;
		pos2 = s.Find(c, pos1);
	}
	if (pos1 != s.GetLength())
		//v.push_back(s.substr(pos1));
		cout++;
	//*加进去
	pos2 = s.Find(c);
	pos1 = 0;
	v.resize(cout);
	int index = 0;
	while (-1 != pos2)
	{
		v[index] = s.Mid(pos1, pos2 - pos1);
		index++;
		pos1 = pos2 + clen;
		pos2 = s.Find(c, pos1);
	}
	if (pos1 != s.GetLength())
		v[index] = s.Mid(pos1, pos2 - pos1);
	index++;
}

 int GetNetTime(char*res,unsigned int nLen)
{
	CString modePath;
	::AfxGetModuleFileName(NULL, modePath);
	modePath = modePath.Left(modePath.ReverseFind(_T('\\')));
	HINSTANCE hIns = LoadLibrary(modePath + "\\botHelp.dll");
	if (!hIns) return 0;
	typedef int(*OPEN_URL)(const char*, char*, unsigned int);
	OPEN_URL open_url = (OPEN_URL)GetProcAddress(hIns, "open_url");
	if (NULL == open_url) return 0;
	open_url("http://www.1pluscad.com/gettime.php", res, nLen);
	FreeLibrary(hIns);
	//OutputDebugString(buffer);
	TRACE("%d\n",strlen(res));
	if (strlen(res) != 20) return 0;
	int y, month, d, h, minutes,seconds;
	if (!sscanf_s(res, "%d-%d-%d %d:%d:%d", &y, &month, &d, &h, &minutes,&seconds)) return 0;

	return (y % 100) * 100000000 + month * 1000000 + d * 10000 + h * 100 + minutes;
	
}
