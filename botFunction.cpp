#include "StdAfx.h"
#include<fstream>
#include "global.h"
void CbotFunction::SetPath(CString _in_path)
{
	filePath = _in_path;
}


CString CbotFunction::GetPath()
{
	CString now_path = filePath;
	return now_path;
}
CString CbotFunction::GetExePath()
{
	TCHAR tcExePath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);  // 设置ini路径到exe同一目录下  

	//_tcsrchr() 反向搜索获得最后一个'\\'的位置，并返回该位置的指针  
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');
	if (pFind == NULL)
	{
		return 0;
	}
	*pFind = '\0';
	CString szIniPath = tcExePath;
	szIniPath = szIniPath + _T("\\");
	return szIniPath;
}
unsigned int CbotFunction::WriteFile(CString _in_FileName, CString _in_message)
{
	if (_in_FileName == _T(""))
	{
		return 0;
	}
	CFile file_log(filePath + _in_FileName, CFile::modeCreate | CFile::modeWrite);
	//file_log.SeekToEnd();
	file_log.Write(_in_message, strlen(_in_message));
	file_log.Close();
	return 1;
}
CString CbotFunction::ReadFile(CString _in_FileName)
{
	if (!PathFileExists(filePath + _in_FileName))
	{
		return "";
	}
	CFile File(filePath + _in_FileName, CFile::modeRead);
	File.SeekToBegin();
	unsigned long long length;
	length = File.GetLength();
	char* pbuf = new char[length + 1];
	File.Read(pbuf, length);
	pbuf[length] = '\0';
	CString result(pbuf);
	File.Close();
	delete pbuf;
	return result;
}
CString CbotFunction::ReadFileWithoutPath(CString _in_PathAndFlieName)
{
	if (_in_PathAndFlieName.GetLength() <= 1)
	{
		return "";

	}
	CFileFind finder;

	if (!PathFileExists(_in_PathAndFlieName))
	{
		return "Null!";
	}
	CFile File(_in_PathAndFlieName, CFile::modeRead);

	File.SeekToBegin();
	DWORD length = File.GetLength();
	if (length > 0)
	{
		char* pbuf = new char[length + 1];
		File.Read(pbuf, File.GetLength());
		pbuf[length] = '\0';
		CString  result(pbuf);
		File.Close();
		delete[]pbuf;
		return result;
	}

	return "";
}
CString CbotFunction::getSets(const CString& key)
{
	CString ret;
	ret = m_map[key];
	return ret;
}
int CbotFunction::getSetsInt(const CString& key)
{
	return _ttoi(m_map[key]);
}

void CbotFunction::setSetsStr(const CString& key, const CString& value)
{
	m_map[key] = value;
}

bool CbotFunction::LoadSets(CString file)
{
	using namespace std;
	CFile f;
	if (f.Open(file, CFile::modeRead) == FALSE)
		return false;
	DWORD len = f.GetLength();
	if (len == 0)
		return false;
	char* buff = new char[len + 1];
	f.Read(buff, len);
	buff[len] = '\0';
	vector<string>vstr,vstr2;
	_split(buff, vstr, "\r\n");
	int vsize = vstr.size();
	int i;
	for (i=0;i<vsize;i++)
	{
		_split(vstr[i], vstr2, "=");
		if (vstr2.size() == 2)
			m_map[vstr2[0].c_str()] = vstr2[1].c_str();
		else if(vstr2.size()==1)
			m_map[vstr2[0].c_str()] = "";
	}

	//f.open(file.GetBuffer())
	f.Close();
	delete[]buff;
	return true;
}

bool CbotFunction::SaveSets(CString file)
{
	using namespace std;
	map<CString, CString>::iterator it, end;
	CFile f;
	if (false == f.Open(file, CFile::modeCreate | CFile::modeWrite))
		return false;
	CString temp;
	temp = "";
	for (it=m_map.begin(),end=m_map.end();it!=end;it++)
	{
		temp += it->first;
		temp += "=";
		temp += it->second;
		temp += "\r\n";
	}
	f.Write(temp.GetBuffer(), temp.GetLength());
	f.Close();
	temp.ReleaseBuffer();
	return true;
}

void CbotFunction::setSetsInt(CString key, int value)
{
	CString str;
	str.Format("%d", value);
	m_map[key] = str;
}

unsigned int CbotFunction::Dealy(long DelayCount)
{
	DWORD j = GetTickCount();
	for (;;)
	{
		Sleep(1);
		if (GetTickCount() >= j + DelayCount)
		{
			break;
		}

	}
	return 0;
}

CString CbotFunction::GetNowTime(int type)
{

	CString strTime, keytime, result_str;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%y-%m-%d");
	keytime = tm.Format("%X");
	if (type == 1)
	{
		result_str = strTime + keytime;
	}
	if (type == 2)
	{
		result_str = strTime;
	}
	if (type == 3)
	{
		result_str = keytime.Left(2) + keytime.Mid(3, 2) + keytime.Right(2);
	}

	return result_str;
}
long CbotFunction::Initialize()
{
	tm = CTime::GetCurrentTime();

	StartYear = 0;
	StartMonth = 0;
	StartDay = 0;
	StartHour = 0;
	StartMinute = 0;
	StartSecond = 0;
	return 0;
}

void CbotFunction::ScreenCapture(CString _in_file_name)
{
	_in_file_name = filePath + _in_file_name;//设置截图文件目录+名称
	CDC *pDC;//屏幕DC
	pDC = CDC::FromHandle(GetDC(NULL));//获取当前整个屏幕DC
	int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//获得颜色模式
	int Width = pDC->GetDeviceCaps(HORZRES);
	int Height = pDC->GetDeviceCaps(VERTRES);
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);

	CBitmap memBitmap, *oldmemBitmap;//建立和屏幕兼容的bitmap
	memBitmap.CreateCompatibleBitmap(pDC, Width, Height);

	oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
	memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//复制屏幕图像到内存DC

	//以下代码保存memDC中的位图到文件
	BITMAP bmp;
	memBitmap.GetBitmap(&bmp);//获得位图信息

	FILE *fp = fopen(_in_file_name, "w+b");

	BITMAPINFOHEADER bih = { 0 };//位图信息头
	bih.biBitCount = bmp.bmBitsPixel;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小
	bih.biWidth = bmp.bmWidth;//宽度

	BITMAPFILEHEADER bfh = { 0 };//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//文件总的大小
	bfh.bfType = (WORD)0x4d42;

	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头

	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头

	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//申请内存保存位图数据

	GetDIBits(memDC.m_hDC, (HBITMAP)memBitmap.m_hObject, 0, Height, p,
		(LPBITMAPINFO)&bih, DIB_RGB_COLORS);//获取位图数据

	fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//写入位图数据

	delete[] p;

	fclose(fp);

	memDC.SelectObject(oldmemBitmap);

}
void CbotFunction::SetStartTime()
{

	StartYear = tm.GetYear();
	StartMonth = tm.GetMonth();
	StartDay = tm.GetDay();
	StartHour = tm.GetHour();
	StartMinute = tm.GetMinute();
	StartSecond = tm.GetSecond();
}

bool CbotFunction::KillProcessById(DWORD pID)
{

	HANDLE Hwnd;
	bool ret = FALSE;
	Hwnd = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, 0, pID);
	if (Hwnd)
	{
		if (TerminateProcess(Hwnd, 0))
		{
			ret = true;
		}
	}
	return ret;
}

void CbotFunction::FileSearch(CString root,CString type)
{ // root 为目录名
	CFileFind ff;
	CString FilePath;
	CString FileName;
	root += type;
	OutputDebugStringA(root);
	BOOL res = ff.FindFile(root);
	while (res)
	{
		res = ff.FindNextFile();
		FileName = ff.GetFileName();
		FilePath = ff.GetFilePath();
		if (ff.IsDirectory() && !ff.IsDots())// 找到的是文件夹
		{
			FileSearch(FilePath,type);// 递归
		}
		else if (!ff.IsDirectory() && !ff.IsDots())// 找到的是文件
		{

			if (SearchStr.GetLength()>4)
			{
				SearchStr += "|";
			}
			SearchStr += FileName;
			
		}
	}
}
CString CbotFunction::SelectFile(const char* fileStr)
{
	//TCHAR szFilter[] = _T("配置(*.cbt)|*.cbt||");
	if (strlen(fileStr)<4)
	{
		fileStr = "所有文件(*.*)|*.*||";
	}
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, fileStr);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		return strFilePath;
	}
	else
	{
		return "";
	}
}
bool CbotFunction::compareStr(const char * firstStr, const char * nextStr)
{
	int nLen1 = strlen(firstStr);
	int nLen2 = strlen(nextStr);
	bool ret = false;
	if (nLen1!=nLen2)
	{
		return false;
	}
	for (int i=0;i<nLen1;i++)
	{
		if (firstStr[i]==nextStr[i])
		{
			ret = true;
		}
		else
		{
			ret = false;
			break;
		}
	}
	return ret;
}


//**************** Detail ******************//
CGameInfo::CGameInfo()
{
	IsFirstRecord = true;
	IsRecordSuccess = false;
	StartGold = 0;
	StartElixir = 0;
	StartTroophs = 0;
	StartTime = 0;
	StartDarkElixir = 0;
	ArmyRet = 0;
}
void CGameInfo::InitlizeDetail()
{
	IsFirstRecord = true;
	IsRecordSuccess = false;
	StartGold = 0;
	StartElixir = 0;
	StartTroophs = 0;
	StartTime = 0;
	StartDarkElixir = 0;
	ArmyRet = 0;
}
long CGameInfo::SetStartResource(long _in_StartGold, long _in_StartElixir, long _in_StartDarkElixir, long _in_StartTroophs)
{
	CString strDay, strH;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strDay = tm.Format("%d");
	strH = tm.Format("%X");
	long ntime = 0;
	if (IsFirstRecord == true && IsRecordSuccess == false)
	{
		StartGold = _in_StartGold;
		StartElixir = _in_StartElixir;
		StartDarkElixir = _in_StartDarkElixir;
		StartTroophs = _in_StartTroophs;


		ntime = _ttoi(strDay) * 24 * 60 + _ttoi(strH.Left(2)) * 60 + _ttoi(strH.Mid(3, 2));
		StartTime = ntime;
		if (StartGold*StartElixir != 0)
		{
			IsFirstRecord = false;
			IsRecordSuccess = true;
			return 1;
		}
		else
		{

			IsFirstRecord = true;
			return 0;
		}


	}

	return 1;
}
long CGameInfo::SetNowResource(long _in_NowGold, long _in_NowElixir, long _in_NowDarkElixir, long _in_NowTroophs)
{
	NowGold = _in_NowGold;
	NowElixir = _in_NowElixir;
	NowDarkElixir = _in_NowDarkElixir;
	NowTroophs = _in_NowTroophs;
	LootGold = NowGold - StartGold;
	LootElixir = NowElixir - StartElixir;
	LootDarkElixir = NowDarkElixir - StartDarkElixir;
	LootTroophs = NowTroophs - StartTroophs;
	CString strDay, strH;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strDay = tm.Format("%d");
	strH = tm.Format("%X");
	long ntime = 0;
	ntime = _ttoi(strDay) * 24 * 60 + _ttoi(strH.Left(2)) * 60 + _ttoi(strH.Mid(3, 2));
	NowTime = ntime;
	RunTime = NowTime - StartTime;
	if (NowGold*NowElixir != 0)
	{
		return 1;
	}
	return 0;
}
long CGameInfo::GetLootGold()
{
	return LootGold;
}
long CGameInfo::GetLootElixir()
{
	return LootElixir;
}
long CGameInfo::GetLootDarkElixir()
{
	return LootDarkElixir;
}
long CGameInfo::GetLootTroophs()
{
	return LootTroophs;
}
long CGameInfo::GetRunTime()
{
	return RunTime;
}



