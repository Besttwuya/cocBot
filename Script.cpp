#include "stdafx.h"
#include "Script.h"


CScript::CScript()
	: scriptStateCode(0)
	, IsThreadRun(true)
	, train_time(0)
{
	scriptVer = "5.17.0204";
	scriptStateCode = 0;
	attackArmy.archer = 0;
	attackArmy.babarin = 0;
	attackArmy.giant = 0;
	attackArmy.goblin = 0;
	attackArmy.wallbreaker = 0;
	attackArmy.wizard = 0;
	SwitchNo = 0;
}


CScript::~CScript()
{
	dm = NULL;
}


long CScript::GetScriptState()
{
	return scriptStateCode;
}


LPCTSTR CScript::GetExePath()
{
	TCHAR tcExePath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');
	if (pFind == NULL)
	{
		return 0;
	}
	*pFind = '\0';
	CString szIniPath = tcExePath;
	szIniPath = szIniPath + _T("\\");
	return LPCTSTR(szIniPath);
}


bool CScript::CreateDm(int type)
{
	int ret = 0;
	::CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (dm.CreateDispatch(clsid) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


bool CScript::StopThread(HANDLE hThread)
{
	if (0 == hThread)
	{
		return false;
	}
	else
	{
		dm.UnBindWindow();
		dm = NULL;
		WaitForSingleObject(hThread, 3000);
		TerminateThread(hThread, 3000);
		return true;
	}

}


void CScript::Dealy(unsigned long mSeconds)
{
	DWORD j = GetTickCount();
	for (;;)
	{

		if (GetTickCount() >= j + mSeconds)
		{
			break;
		}
		if (scriptStateCode <= 0)
		{
			break;
		}
		Sleep(1);
	}
}


void CScript::DealyRandTime(unsigned long minDeaySeconds = 0, unsigned long maxDealySeconds = 10)
{
	srand((unsigned)time(NULL));
	CString str;
	if (minDeaySeconds <= maxDealySeconds)
	{
		maxDealySeconds = minDeaySeconds + 10;
	}
	long resultRand = minDeaySeconds + (rand() % (maxDealySeconds - minDeaySeconds));
	str.Format("Rand Dealy=%ld second", resultRand);
	resultRand *= 1000;
	Dealy(resultRand);
}


int CScript::ExcludeTooNearPos(CString allpos, long minDistance, int type, CString& result)
{
	long strLength = 0;
	minDistance = minDistance*minDistance;//平方最小距离
	long dx2 = 0;
	VARIANT x, y;
	CString leftStr, rightStr, str;
	str = allpos;
	strLength = allpos.GetLength();
	if (strLength <= 0)
	{
		result = _T("NULL");
		return 0;
	}
	long maxCount = 0;//start count
	long realCount = 0;//result count
	int IsSave = 0;
	int maxSave = 0;
	if (type == 0)
	{
		maxCount = coc.SpiltStr(allpos.GetBuffer(strLength), "|", str);
		allpos.ReleaseBuffer();
	}
	else
	{
		maxCount = dm.GetResultCount(allpos);
	}


	long* NumberX = new long[maxCount];
	long* NumberY = new long[maxCount];
	long* SaveNumberX = new long[maxCount];
	long* SaveNumberY = new long[maxCount];
	int IsBreak = 0;
	if (type == 0)
	{
		char* strToken = allpos.GetBuffer(strLength);
		allpos.ReleaseBuffer();
		const char* strDelimit = "|";
		char* p;
		char* pNext = NULL;
		p = strtok_s(strToken, strDelimit, &pNext);
		CString* midStr = new CString[maxCount];
		int r = 0;
		while (p != NULL)
		{
			midStr[r] = p;
			r++;
			p = strtok_s(NULL, strDelimit, &pNext);
		}
		for (r = 0; r < maxCount; r++)
		{
			int j = 0;
			strToken = midStr[r].GetBuffer();
			p = strtok_s(strToken, ",", &pNext);
			midStr[r].ReleaseBuffer();
			while (p != NULL)
			{
				str = p;
				if (j == 1)
				{
					NumberX[r] = _ttoi(str);
				}
				if (j == 2)
				{
					NumberY[r] = _ttoi(str);
				}
				j++;
				p = strtok_s(NULL, strDelimit, &pNext);
			}
		}
	}
	else
	{
		dm.GetResultPos(allpos, 0, &x, &y);
		SaveNumberX[0] = x.lVal;
		SaveNumberY[0] = y.lVal;
		for (int i = 0; i < maxCount; i++)
		{
			dm.GetResultPos(allpos, i, &x, &y);
			NumberX[i] = x.lVal;
			NumberY[i] = y.lVal;
		}
	}

	do
	{

		for (int j = 0; j < maxCount; j++)//遍历所有数据
		{
			IsSave = 0;
			for (int i = 0; i <= maxSave; i++)//和已经保存的数据进行对比
			{
				dx2 = (SaveNumberX[i] - NumberX[j])*(SaveNumberX[i] - NumberX[j]) + (SaveNumberY[i] - NumberY[j])*(SaveNumberY[i] - NumberY[j]);//距离的平方

				if (dx2 > minDistance)//距离的平方大于设定距离的平方
				{
					IsSave = 1;
				}
				else
				{
					IsSave = 0;

					break;
				}
			}

			if (IsSave == 1)//如果当前数据满足要求，就存下它
			{
				maxSave++;//记录保存数据的个数

				SaveNumberX[maxSave] = NumberX[j];
				SaveNumberY[maxSave] = NumberY[j];
				str.Format("%ld,", SaveNumberX[maxSave]);
				leftStr += str;
				str.Format("%ld,", SaveNumberY[maxSave]);
				rightStr += str;
				IsBreak = 0;
				break;


			}
			else//否则记录不符合要求的数据个数
			{

				IsBreak++;
			}


		}

	} while (IsBreak < maxCount);//最外层循环，直到所有数据都不行才停止

	leftStr = leftStr.Left(leftStr.GetLength() - 1);
	rightStr = rightStr.Left(rightStr.GetLength() - 1);
	result = leftStr + "|" + rightStr;
	delete[]NumberX;
	delete[]NumberY;
	delete[]SaveNumberX;
	delete[]SaveNumberY;//free memory
	return maxSave;
}


int CScript::KillAdb()
{
	CString str;
	int ret = 0;
	str = dm.EnumProcess("adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	str = dm.EnumProcess("nox_adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	return ret;
}


int CScript::SendXSolider(int type)
{
	const int minY = 577;
	const int maxY = 597;
	dm.SetPath("\Pic\\attack\\Solider");
	int find_n = 0;
	find_n = type - 1;
	if (find_n >= 20 || find_n < 0)
	{
		find_n = 0;
	}
	VARIANT x, y;
	CString str;
	CString result, first, next, sim;
	int z = 0;

	str.Format("%d", type);
	str = coc.GetConfig(str, "[", "]");
	if (str.GetLength() <= 2)
	{
		return 0;
	}
	z = str.Find(",");
	first = str.Left(z);
	next = str.Right(str.GetLength() - z - 1);
	sim = next.Right(2);
	next = next.Left(next.GetLength() - 5);
	dm.FindMultiColor(36, 593, 821, 622, first, next, 0.9, 0, &x, &y);
	
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, 608);
		Dealy(20);
		dm.LeftClick();
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::RepairPos(long x, long y, int type, long* resultX, long* resultY)
{
	switch (type)
	{
	case 0:
		*resultX = x - 10;
		*resultY = y - 10;
		break;
	case 1:
		*resultX = x - 10;
		*resultY = y + 10;
		break;
	case 2:
		*resultX = x + 10;
		*resultY = y + 10;
		break;
	case 3:
		*resultX = x + 10;
		*resultY = y - 10;
		break;
	}

	return 0;
}


int CScript::AttackArea(long x1, long y1, long x2, long y2, long type, long* result_x, long* result_y)
{
	*result_x = 0;
	*result_y = 0;
	dm.SetPath(_T("\Pic\\attack\\normal"));
	CString PicName;
	CString result;
	PicName = dm.MatchPicName("d_*.bmp");
	VARIANT x, y;
	dm.FindPic(x1, y1, x2, y2, PicName, "0f0f0f", 0.95, type, &x, &y);
	result = dm.FindPicEx(x1, y1, x2, y2, PicName, "0f0f0f", 0.95, type);
	if (x.lVal > 0)
	{
		*result_x = x.lVal;
		*result_y = y.lVal;
		return 1;
	}
	else
	{
		*result_x = 425;
		*result_y = 333;
	}


	return 0;
}


int CScript::ClearAdvirtisment()
{

	dm.SetPath("\Advirtisment");
	CString pic_name;
	VARIANT x, y;
	pic_name = dm.MatchPicName("*.bmp");
	if (pic_name.GetLength() > 4)
	{
		if (dm.FindPic(0, 0, 850, 667, pic_name, "0f0f0f", 0.85, 0, &x, &y))
		{
			dm.MoveTo(x.lVal + 5, y.lVal + 5);
			Dealy(20);
			dm.LeftClick();
			//WriteLog("发现广告，尝试清除", true, RGB(0xff, 0x00, 0x00), false);
			return 1;
		}


	}
	return 0;
}


int CScript::TownJudge()
{
	dm.SetPath(_T("\Pic\\others"));
	//WriteLog(_T("等待村庄界面"), true, RGB(0xff, 0x00, 0xff), false);
	int TownJudge_i = 0;
	VARIANT x, y;
	int ae_ret;
	CString tji;
	CString PicName, result;
	PicName = dm.MatchPicName("main_screen*.bmp");
	do
	{
		if (_ttoi(coc.GetSingleSetting("DebugLocateAD")) == 1)
		{
			ClearAdvirtisment();
		}
		if (dm.FindMultiColor(352, 420, 507, 493, "C9E76A-05040F", "29|-4|D0EA73-02080F,66|-1|CAE86C-04020F,-9|25|60AE10-02080F,30|31|5EAC10-080202,67|30|5DAC10-080202", 0.99, 1, &x, &y))
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
		}
		dm.SetPath(_T("\Pic\\others"));
		dm.FindPic(753, 36, 842, 156, "Esc_Army.bmp", "0f0f0f", 0.90, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
		}
		dm.FindPic(256, 1, 324, 62, PicName, "0f0f0f", 0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			break;
		}

		tji.Format("%d", 60 - TownJudge_i);
		if (TownJudge_i % 5 == 0)
		{
			WriteLog(_T("加载村庄中,请等待：") + tji + _T("s"));
		}
		else
		{
			WriteLog(_T("加载村庄中,请等待："));
		}
		if (TownJudge_i >= 60)
		{
			scriptStateCode = ShouldRestart;
			WriteLog(_T("未发现村庄，尝试重启"));
			return 0;
		}
		if (scriptStateCode <= 0)
		{
			break;
			return 0;
		}
		TownJudge_i = TownJudge_i + 1;

		Dealy(1000);
		//******************* Here DEbug place *****************//
		//AttackArea();
		//******************* Debug End ************************//
		//GetArmyMsg();
	} while (TownJudge_i <= 60);
	return 0;
}


int CScript::RequestHelp()
{
	VARIANT x, y;
	dm.SetPath("\Pic\\others\\RequestHelp");
	dm.FindPic(638, 495, 796, 572, "RequestHelp.bmp", "0f0f0f", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
		Dealy(2000);
		dm.FindMultiColor(357, 133, 509, 173, "ffffff-0f0f0f", "63|6|ffffff-0f0f0f", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
			Dealy(2000);
		}
		dm.FindMultiColor(442, 194, 596, 262, "c9e870-0f0f0f", "68|0|c8e870-0f0f0f,2|30|5dac10-0f0f0f,73|30|5cac10-0f0f0f", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20); dm.LeftClick();
		}
		else
		{
			dm.MoveTo(811, 92);
			Dealy(20);
			dm.LeftClick();
		}
	}
	return 0;
}


int CScript::CheckArmyNum(int* Ma_time)
{

	VARIANT x, y;
	dm.SetPath("\Pic\\others");
	CString PicName;
	PicName = dm.MatchPicName("main_screen*.bmp");
	if (dm.FindPic(256, 1, 324, 62, PicName, "0f0f0f", 0.9, 0, &x, &y) <= 0)
	{
		return 0;
	}
	dm.MoveTo(34, 519);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	CString s, sl, Army_str, M_time, time_str, spells_str, clancastle_str, clan_spell, ret_str;
	float ret = 0, NowCount = 0, AllCount = 1;
	dm.UseDict(0);
	Dealy(200);
	s = dm.Ocr(75, 134, 155, 157, "ffffff-050505", 0.85);
	sl = s.Left(s.Find("/"));
	Army_str = s.Right(s.GetLength() - s.Find("/") - 1);
	NowCount = _ttoi(sl);
	AllCount = _ttoi(Army_str);
	if (AllCount > 0)
	{
		ret = (NowCount * 100) / AllCount;

	}
	else
	{

		ret = 0;
	}
	LootRecord[SwitchNo].ArmyRet = ret;
	int pos = 0;
	pos = (int)ret;
	if (pos > 100)
	{
		pos = 0;
	}
	//pag9.m_progress.SetPos(pos);
	M_time = dm.Ocr(730, 137, 831, 153, "ffffff-050505", 0.85);
	spells_str = dm.Ocr(75, 283, 125, 302, "ffffff-050505", 0.85);
	clancastle_str = dm.Ocr(184, 436, 238, 456, "ffffff-050505", 0.85);
	clan_spell = dm.Ocr(522, 433, 560, 452, "ffffff-050505", 0.85);
	dm.FindPic(730, 137, 831, 153, "minutes_1.bmp|minutes_1.bmp", "0f0f0f", 0.9, 0, &x, &y);
	if (M_time.GetLength() <= 0)
	{
		time_str = "0";
	}

	if (x.lVal > 0)
	{
		M_time += _T("分钟");
	}
	else
	{
		M_time += "秒";
	}
	if (M_time.Find(_T("分钟")) != -1)
	{
		time_str = M_time.Left(M_time.Find(_T("分钟")));
	}
	else
	{
		if (time_str != "0"&&M_time.Find("秒") != -1)
		{
			time_str = "1";
		}
	}
	*Ma_time = _ttoi(time_str);
	ret_str.Format("%f", ret);
	ret_str += "%";
	//WriteLog(_T("[兵营人口]" + s + "(" + ret_str + ")[造兵时间]" + M_time), true, RGB(0x00, 0x00, 0xff), false);
	//WriteLog("[法术] " + spells_str + " [部落援军] " + clancastle_str + " [部落法术] " + clan_spell, true, RGB(0x00, 0x00, 0xff), false);
	if (_ttoi(coc.GetSingleSetting("RequestArmy")) == 1)
	{
		RequestHelp();
		Dealy(100);

	}
	dm.SetPath("\Pic\\others");
	VARIANT ex, ey;
	for (int i = 0; i <= 10; i++)
	{
		if (dm.FindPic(753, 36, 842, 156, "Esc_Army.bmp", "0f0f0f", 0.90, 1, &ex, &ey) > 0)
		{

			dm.MoveTo(ex.lVal, ey.lVal);
			Dealy(20);
			dm.LeftClick();
			break;
		}
		Dealy(200);
		if (i >= 10)
		{
			dm.MoveTo(812, 94);
			Dealy(20);
			dm.LeftClick();
			Dealy(1000);
		}
	}

	if (ret >= _ttoi(coc.GetSingleSetting("MinTroopRet")))
	{
		return 1;
	}
	else
	{
		return 0;

	}
}


void CScript::ClearArmy()
{
	VARIANT x, y;
	do
	{
		dm.FindColor(18, 150, 833, 185, "de0306-0f0f0f", 1.0, 0, &x, &y);
		if (x.lVal < 0)
		{
			Dealy(1000);
		}
		dm.FindColor(18, 150, 833, 185, "de0306-0f0f0f", 1.0, 0, &x, &y);
		if (x.lVal < 0)
		{
			break;
		}
		else
		{
			dm.FindColor(18, 150, 833, 185, "de0306-0f0f0f", 1.0, 0, &x, &y);
			dm.MoveTo(x.lVal, y.lVal);
			for (int i = 0; i <= 10; i++)
			{
				Dealy(25);
				dm.LeftClick();
			}
		}


	} while (x.lVal > 0);
}


int CScript::SpeedTrain()
{
	CString str_begin, str_end;
	//pag2.SpeedUpBegin.GetWindowText(str_begin);
	//pag2.SpeedUpEnd.GetWindowText(str_end);
	int nowh = _ttoi(coc.GetNowTime(3).Left(2));
	if (nowh >= _ttoi(str_begin) && nowh <= _ttoi(str_end))
	{
		VARIANT x, y;
		dm.SetPath("\Pic\\others");
		dm.FindPic(695, 262, 831, 328, "speed_1.bmp", "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(2500);
		}
		dm.FindPic(347, 372, 514, 454, "speed_2.bmp", "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(2500);
			return 1;
		}
	}

	return 0;
}


int CScript::MakeArmy()
{
	VARIANT x, y;
	dm.SetPath("\Pic\\others");
	CString PicName;
	PicName = dm.MatchPicName("main_screen*.bmp");
	if (dm.FindPic(256, 1, 324, 62, PicName, "0f0f0f", 0.9, 0, &x, &y) <= 0)
	{
		return 0;
	}
	dm.MoveTo(34, 519);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	unsigned int armytype[30];
	for (int i = 0; i <= 29; i++)
	{
		armytype[i] = 0;

	}
	armytype[1] = _ttoi(coc.GetSingleSetting("Barbarin"));
	armytype[2] = _ttoi(coc.GetSingleSetting("Archer"));
	armytype[3] = _ttoi(coc.GetSingleSetting("Giant"));
	armytype[4] = _ttoi(coc.GetSingleSetting("Goblin"));
	armytype[5] = _ttoi(coc.GetSingleSetting("WallBreaker"));
	armytype[6] = _ttoi(coc.GetSingleSetting("Ballon"));
	armytype[7] = _ttoi(coc.GetSingleSetting("Wizard"));
	armytype[8] = _ttoi(coc.GetSingleSetting("Healer"));
	armytype[9] = _ttoi(coc.GetSingleSetting("Dragon"));
	armytype[10] = _ttoi(coc.GetSingleSetting("Peka"));
	armytype[11] = _ttoi(coc.GetSingleSetting("BabyDragon"));
	armytype[12] = _ttoi(coc.GetSingleSetting("Miner"));
	armytype[13] = _ttoi(coc.GetSingleSetting("Minion"));//dark
	armytype[14] = _ttoi(coc.GetSingleSetting("HogRider"));
	armytype[15] = _ttoi(coc.GetSingleSetting("Valkyrie"));
	armytype[16] = _ttoi(coc.GetSingleSetting("Golem"));
	armytype[17] = _ttoi(coc.GetSingleSetting("Witch"));
	armytype[18] = _ttoi(coc.GetSingleSetting("LavaHound"));
	armytype[19] = _ttoi(coc.GetSingleSetting("BowLer"));
	armytype[20] = _ttoi(coc.GetSingleSetting("LightingSpell"));//spell
	armytype[21] = _ttoi(coc.GetSingleSetting("HealingSpell"));
	armytype[22] = _ttoi(coc.GetSingleSetting("RageSpell"));
	armytype[23] = _ttoi(coc.GetSingleSetting("JumpSpell"));
	armytype[24] = _ttoi(coc.GetSingleSetting("FreezeSpell"));
	armytype[25] = _ttoi(coc.GetSingleSetting("CloneSpell"));
	armytype[26] = _ttoi(coc.GetSingleSetting("PoisonSpell"));
	armytype[27] = _ttoi(coc.GetSingleSetting("EarthquakeSpell"));
	armytype[28] = _ttoi(coc.GetSingleSetting("HasteSpell"));
	armytype[29] = _ttoi(coc.GetSingleSetting("SkeletonSpell"));
	//**************造兵***************//
	attackArmy.babarin = armytype[1];
	attackArmy.archer = armytype[2];
	attackArmy.giant = armytype[3];
	attackArmy.goblin = armytype[4];
	attackArmy.wallbreaker = armytype[5];
	dm.SetPath("\Pic\\others");
	dm.MoveTo(34, 519);
	Dealy(200);
	dm.LeftClick();
	long ex = 0, ey = 0;
	for (int i = 0; i <= 10; i++)
	{
		dm.FindPic(33, 73, 794, 127, "army_view_1.bmp", "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			break;
		}
		if (i >= 10)
		{
			return 0;
		}
	}


	dm.MoveTo(295, 96);
	Dealy(20);
	dm.LeftClick();
	Dealy(1000);
	dm.UseDict(0);
	CString str, now, right;
	int NowCount = 0, AllCount = 1;
	int IsClear = 0;
	IsClear = _ttoi(coc.GetSingleSetting("IsClearArmy"));
	str = dm.Ocr(43, 125, 128, 152, "ffffff-050505", 0.85);
	now = str.Left(str.Find("/"));
	right = str.Right(str.GetLength() - str.Find("/") - 1);
	NowCount = _ttoi(now);
	AllCount = _ttoi(right);
	if (AllCount == 0)
	{
		AllCount = 1;
	}
	if (NowCount / AllCount != 2 || IsClear == 1)
	{
		ClearArmy();

	}

	CString str_i, pic;
	int TrainArmyStyle = 0;
	TrainArmyStyle = _ttoi(coc.GetSingleSetting("TrainArmyStyle"));
	if (TrainArmyStyle == 0)
	{
		dm.SetPath("\Pic\\others\\solider");
		pic = "*.bmp";
		for (int i = 1; i <= 12; i++)
		{
			if (armytype[i] == 0)
			{
				continue;
			}
			str_i.Format("solider_%d.bmp", i);
			dm.FindPic(21, 335, 839, 548, str_i, "0f0f0f", 0.85, 0, &x, &y);
			if (armytype[i] != 0 && x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				for (int j = 1; j <= armytype[i]; j++)
				{

					Dealy(50);
					dm.LeftClick();
				}
			}
			else
			{
				//WriteLog("[r]Not Find  " + str_i);
			}
		}
		func_adb("input swipe 798 499 50 467");
		Dealy(1000);
		for (int i = 13; i <= 19; i++)
		{
			if (armytype[i] == 0)
			{
				continue;
			}
			str_i.Format("solider_%d.bmp", i);
			dm.FindPic(21, 335, 839, 548, str_i, "0f0f0f", 0.85, 0, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveToEx(x.lVal, y.lVal, 5, 5);
				for (int j = 1; j <= armytype[i]; j++)
				{

					Dealy(50);
					dm.LeftClick();
				}
			}
			else
			{
				//WriteLog("[r]Not Find solider " + str_i);
			}
			Dealy(200);
		}
	}
	if (/*pag2.IsSpeedUp.GetCheck() == 1*/0)
	{
		SpeedTrain();
	}
	if (TrainArmyStyle >= 1)
	{
		dm.SetPath("\Pic\\others");
		dm.MoveTo(697, 96);
		Dealy(20);
		dm.LeftClick();
		Dealy(1500);
		switch (TrainArmyStyle)
		{
		case 1:
			dm.FindPic(719, 304, 829, 346, "onekey_train_2.bmp", "0f0f0f", 0.85, 0, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				Dealy(20);
				dm.LeftClick();
			}
			break;
		case 2:
			dm.FindPic(719, 420, 828, 466, "onekey_train_2.bmp", "0f0f0f", 0.85, 0, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				Dealy(20);
				dm.LeftClick();
			}
			break;
		case 3:
			dm.FindPic(718, 538, 827, 577, "onekey_train_2.bmp", "0f0f0f", 0.85, 0, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				Dealy(20);
				dm.LeftClick();
			}
			break;
		}
		if (x.lVal <= 0)
		{
			//WriteLog("[r]error:bad one key train!");
		}
	}

	Dealy(1000);
	dm.MoveTo(493, 94);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	dm.SetPath("\Pic\\others\\solider");
	for (int i = 20; i <= 29; i++)
	{
		if (armytype[i] == 0)
		{
			continue;
		}
		str_i.Format("spell_%d.bmp", i - 19);
		dm.FindPic(21, 335, 839, 548, str_i, "0f0f0f", 0.85, 0, &x, &y);
		if (armytype[i] != 0 && x.lVal > 0)
		{
			dm.MoveToEx(x.lVal, y.lVal, 5, 5);
			for (int j = 1; j <= armytype[i]; j++)
			{

				Dealy(50);
				dm.LeftClick();
			}
		}
		else
		{
			//WriteLog("[r]Not Find  " + str_i);
		}
	}
	dm.SetPath("\Pic\\others");
	for (int i = 0; i <= 10; i++)
	{
		if (dm.FindPic(775, 60, 844, 149, "Esc_Army.bmp", "0f0f0f", 0.9, 0, &x, &y) == 1)
		{
			dm.MoveTo(ex, ey);
			Dealy(20);
			dm.LeftClick();
			Dealy(500);

		}
		if (i >= 10)
		{
			dm.MoveTo(812, 94);
			Dealy(20);
			dm.LeftClick();
			Dealy(1000);
		}
	}

	return 0;
}


int CScript::func_adb(CString f_input)
{

	CString path, strIp, strOut;
	strIp = "127.0.0.1:62001";
	int connectType = 0;
	connectType = _ttoi(coc.GetSingleSetting("BluestacksOrOthers"));
	switch (_ttoi(coc.GetSingleSetting("BsOrOtherNo")))
	{
	case 0:
		strIp = "127.0.0.1:62001";
		break;
	case 1:
		strIp = "127.0.0.1:62025";
		break;
	case 2:
		strIp = "127.0.0.1:62026";
		break;
	case 3:
		strIp = "127.0.0.1:62027";
		break;
	default:
		break;
	}
	if (connectType == 0)
	{
		strIp = "emulator-5554";
		path = "adb.exe";
	}
	else
	{
		path = coc.GetSingleSetting("AdbPath");
	}

	//WriteLog("adb path=" + path, true, RGB(0x00, 0x00, 0xff), false);
	//WriteLog(f_input + "\r\n" + strIp, true, RGB(0x00, 0x00, 0xff), false);
	adb.Start(path, strIp, 1);
	adb.RunCmd(f_input);
	adb.Stop();
	//WriteLog(adb.GetOutput(), true, RGB(0x00, 0x00, 0xff), false);
	CString adb_error = adb.GetOutput();
	if (adb_error.Find("error: device not found") >= 0)
	{
		//WriteLog(_T("error: device not found,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), false);
		if (KillAdb())
		{
			//WriteLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), false);
		}
		else
		{
			//WriteLog(_T("error:kill adb.exe False 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), false);
		}
		adb.Start(path, strIp, 1);
		adb.RunCmd(f_input);
		adb.Stop();

	}
	return 0;
}


int CScript::AddArmy()
{
	return 0;
}


int CScript::GetResource()
{
	CString gold, water, oil, troophs;
	dm.UseDict(2);
	Dealy(20);
	gold = dm.Ocr(652, 19, 811, 45, "ffffff-030303", 0.8);
	water = dm.Ocr(655, 69, 806, 91, "ffffff-030303", 0.8);
	oil = dm.Ocr(702, 120, 800, 140, "ffffff-030303", 0.8);
	troophs = dm.Ocr(61, 78, 125, 104, "ffffff-030303", 0.8);
	if (LootRecord[SwitchNo].IsFirstRecord == true)
	{

		LootRecord[SwitchNo].SetStartResource(_ttoi(gold), _ttoi(water), _ttoi(oil), _ttoi(troophs));

		LootRecord[SwitchNo].SetNowResource(_ttoi(gold), _ttoi(water), _ttoi(oil), _ttoi(troophs));

	}
	else
	{
		LootRecord[SwitchNo].SetNowResource(_ttoi(gold), _ttoi(water), _ttoi(oil), _ttoi(troophs));
	}

	return 0;
}


int CScript::send_LightngSpell()
{
	VARIANT x, y;
	dm.FindMultiColor(36, 593, 821, 638, "082cda-0f0f0f", "5|-1|104be2-0f0f0f,-2|2|0720de-0f0f0f,4|2|0e45de-0f0f0f", 0.9, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal - 30);
		Dealy(100);
		dm.LeftClick();
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::LightingAttack(long darkelixir)
{
	long AttackLingtingMinDarkElixir = _ttoi(coc.GetSingleSetting("AttackLingtingMinDarkElixir"));
	int UseLightingCount = _ttoi(coc.GetSingleSetting("UseLightingCount"));
	long dx, dy;
	if (darkelixir < AttackLingtingMinDarkElixir)
	{
		return 0;
	}
	VARIANT dx1, dy1;
	Dealy(200);
	dm.SetPath("\Pic\\attack\\DarkElixir");
	CString dark_pic;
	dark_pic = dm.MatchPicName("*.bmp");
	if (dark_pic.GetLength() >= 3)
	{
		CString ResultPos = dm.FindPicEx(30, 30, 840, 650, dark_pic, "0f0f0f", 0.8, 0);
		//WriteLog(ResultPos);
		for (int j = 0; j <= ResultPos.GetLength(); j += 7)
		{
			dm.FindPic(30, 30, 840, 650, dark_pic, "0f0f0f", 0.8, 0, &dx1, &dy1);
			if (dx1.lVal)
			{


				dx = dx1.lVal + 15, dy = dy1.lVal + 30;
				if (8 <= dx&&dx <= 132 && 132 <= dy&&dy <= 554)
				{
					dx = 0;
					dy = 0;
				}
				dm.MoveTo(dx, dy);

				for (int k = 0; k <= UseLightingCount; k++)
				{
					Dealy(20);
					dm.LeftClick();
				}
				Dealy(3000);
			}
		}

	}

	return 1;
}


int CScript::WaitForReturnHome()
{
	int AttackMinWaitTime = _ttoi(coc.GetSingleSetting("AttackMinWaitTime"));
	VARIANT x, y;
	//WriteLog("下兵完成，等待战斗结束", true, RGB(0x00, 0x00, 0xff), false);
	long gt = 0, wt = 0, ot = 0;
	long g = 0, w = 0, o = 0;
	int  time1 = 0;
	CString R_gold, R_water, R_oil;
	dm.UseDict(1);
	do
	{
		dm.SetPath(_T("\Pic\\attack"));
		if (scriptStateCode <= 0)
		{
			dm = NULL; return 0;
		}
		dm.FindPic(392, 520, 462, 562, "return.bmp", "141414", 0.9, 0, &x, &y);
		Dealy(100);

		R_gold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		R_water = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		R_oil = dm.Ocr(46, 121, 108, 143, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		gt = _ttoi(R_gold), wt = _ttoi(R_water), ot = _ttoi(R_oil);
		CString str_t;
		if (gt == g&&wt == w&&ot == o)
		{
			time1++;
			if (time1 % 2 == 0)
			{
				str_t.Format("%d", AttackMinWaitTime - time1);
				//WriteLog("战斗将在" + str_t + "秒后结束", true, RGB(0x00, 0x00, 0xff), false);
			}

		}
		else
		{
			time1 = 0;
		}
		g = gt, w = wt, o = ot;

		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
		if (x.lVal > 0 || time1 > AttackMinWaitTime)
		{
			if (send_LightngSpell() == 1)
			{
				if (LightingAttack(ot))
				{
					Dealy(2000);
				}
			}
			//WriteLog("返回村庄", true, RGB(0xff, 0x00, 0xff), true);
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			dm.MoveTo(66, 530);
			Dealy(20);
			dm.LeftClick();
			Dealy(2000);
			dm.MoveTo(500, 396);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(427, 540);
			Dealy(2000);
			dm.LeftClick();
			break;
		}
		Dealy(1000);
	} while (time1 <= 255);
	return 0;
}


int CScript::Main_Attack()
{

	Dealy(2000);
	if (scriptStateCode <= 0)
	{
		return 0;
	}
	long AttackSpeed = 10, AttackChangeDealy = 10, AttackNextDealy = 50;
	int AttackSpeedType = _ttoi(coc.GetSingleSetting("AttackSpeed"));
	switch (AttackSpeedType)
	{
	case 0:
		AttackSpeed = 10;
		break;
	case 1:
		AttackSpeed = 20;
		break;
	case 2:
		AttackSpeed = 30;
		break;
	case 3:
		AttackSpeed = 50;
		break;
	case 4:
		AttackSpeed = 100;
		break;
	case 5:
		AttackSpeed = 200;
		break;
	case 6:
		AttackSpeed = 500;
		break;
	default:
		AttackSpeed = 50;
	}
	AttackChangeDealy = 200;
	AttackNextDealy = 2000;
	dm.SetPath(_T("\Pic\\attack"));
	//WriteLog(_T("定位下兵位置"));
	CString RedLineColor = "d45c21-0f900f";
	CString show_str;
	long ResourceX[4] = { 0 }, ResourceY[4] = { 0 };
	long now_x = 0, now_y = 0;
	AttackArea(134, 81, 426, 314, 2, &now_x, &now_y);
	ResourceX[0] = now_x, ResourceY[0] = now_y;
	AttackArea(140, 330, 471, 540, 3, &now_x, &now_y);
	ResourceX[1] = now_x, ResourceY[1] = now_y;
	AttackArea(426, 305, 768, 506, 1, &now_x, &now_y);
	if (now_x > 600 || now_y <= 300)
	{
		now_x = 500;
		now_y = 425;
	}
	ResourceX[2] = now_x, ResourceY[2] = now_y;
	AttackArea(428, 113, 707, 298, 0, &now_x, &now_y);
	ResourceX[3] = now_x, ResourceY[3] = now_y;
	CString result_pos[4];
	CString result_posx[4];
	long StrLength = 0, MaxLength = 0;
	for (int i = 0; i < 15; i++)
	{

		result_posx[0] = dm.FindMultiColorEx(44, 55, 445, 379, RedLineColor, "-1|1|d45c21-0f900f,-2|2|d45c21-0f900f,-3|3|d45c21-0f900f,-4|4|d45c21-0f900f", 1, 0);
		result_posx[1] = dm.FindMultiColorEx(57, 331, 474, 569, RedLineColor, "1|1|d45c21-0f900f,2|2|d45c21-0f900f,3|3|d45c21-0f900f,4|4|d45c21-0f900f", 1, 0);
		result_posx[2] = dm.FindMultiColorEx(420, 330, 811, 570, RedLineColor, "-1|1|d45c21-0f900f,-2|2|d45c21-0f900f,-3|3|d45c21-0f900f,-4|4|d45c21-0f900f", 1, 1);
		result_posx[3] = dm.FindMultiColorEx(411, 51, 799, 403, RedLineColor, "1|1|d45c21-0f900f,2|2|d45c21-0f900f,3|3|d45c21-0f900f,4|4|d45c21-0f900f", 1, 1);
		StrLength = result_posx[0].GetLength() + result_posx[1].GetLength() + result_posx[2].GetLength() + result_posx[3].GetLength();
		if (MaxLength < StrLength)
		{
			MaxLength = StrLength;
			result_pos[0] = result_posx[0];
			result_pos[1] = result_posx[1];
			result_pos[2] = result_posx[2];
			result_pos[3] = result_posx[3];
			show_str.Format("MaxLength=%ld", MaxLength);
			//WriteLog(show_str, true, RGB(0xff, 0x00, 0xff), false);

		}
		Dealy(200);
		if (scriptStateCode <= 0)
		{
			return 0;
		}
	}
	result_posx[0] = result_pos[0];
	result_posx[1] = result_pos[1];
	result_posx[2] = result_pos[2];
	result_posx[3] = result_pos[3];

	int x[4][61] = { 0 }, y[4][61] = { 0 };
	for (int i = 0; i <= 3; i++)
	{

		result_pos[i] = dm.FindNearestPos(result_posx[i], 1, ResourceX[i], ResourceY[i]);
	}
	//WriteLog(result_pos[0] + "|" + result_pos[1] + "|" + result_pos[2] + "|" + result_pos[3]);

	for (int i = 0; i <= 3; i++)
	{
		x[i][0] = _ttoi(result_pos[i].Left(3));
		y[i][0] = _ttoi(result_pos[i].Right(3));
	}
	MaxLength = 0;

	result_posx[0] = dm.FindColorBlockEx(44, 55, 445, 379, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 55, 8, 8);
	result_posx[1] = dm.FindColorBlockEx(32, 349, 447, 630, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 55, 8, 8);
	result_posx[2] = dm.FindColorBlockEx(426, 305, 768, 506, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 55, 8, 8);
	result_posx[3] = dm.FindColorBlockEx(428, 113, 707, 298, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 55, 8, 8);

	for (int i = 0; i <= 59; i++)
	{
		x[0][i + 1] = x[0][i] - 8;
		y[0][i + 1] = y[0][i] + 6;
		x[1][i + 1] = x[1][i] - 8;
		y[1][i + 1] = y[1][i] - 6;
		x[2][i + 1] = x[2][i] + 8;
		y[2][i + 1] = y[2][i] - 6;
		x[3][i + 1] = x[3][i] + 8;
		y[3][i + 1] = y[3][i] + 6;
	}
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 0; i <= 40; i++)
		{
			result_pos[j] = dm.FindNearestPos(result_posx[j], 1, x[j][i], y[j][i]);
			x[j][i] = _ttoi(result_pos[j].Left(3));
			y[j][i] = _ttoi(result_pos[j].Right(3));
			RepairPos(x[j][i], y[j][i], j, &now_x, &now_y);
			x[j][i] = now_x;
			y[j][i] = now_y;
			if (scriptStateCode <= 0)
			{
				return 0;
			}
		}
		if (scriptStateCode <= 0)
		{
			return 0;
		}
	}
	//红线坐标寻找完成
	//WriteLog(_T("定位完成"));
	Dealy(200);
	VARIANT xg, yg;
	int solider_num = 0;
	for (int j = 0; j <= 3; j++)
	{
		if (scriptStateCode <= 0)
		{
			return 0;
		}
		//giant
		solider_num = SendXSolider(3);
		if (solider_num > 0)
		{
			//WriteLog(_T("giant"));
			Dealy(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		if (solider_num > 0)
		{
			//WriteLog(_T("hog rider"));
			Dealy(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(1);
		if (solider_num > 0)
		{
			//WriteLog(_T("barbarin"));
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(4);
		if (solider_num > 0)
		{
			//WriteLog(_T("wallbreaker"));
			Dealy(100);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
			}
		}
		Dealy(AttackChangeDealy);
		//goblin
		solider_num = SendXSolider(5);
		if (solider_num > 0)
		{
			//WriteLog(_T("哥布林"));
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SendXSolider(2);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		solider_num = SendXSolider(6);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		if (scriptStateCode <= 0)
		{
			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			//WriteLog("释放援军"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			//WriteLog("释放蛮王"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			//WriteLog("释放女王");
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackNextDealy);
	}
	//WriteLog("释放剩余兵种");
	for (int j = 0; j <= 3; j++)
	{
		if (scriptStateCode <= 0)
		{
			return 0;
		}
		//giant
		solider_num = SendXSolider(3);
		if (solider_num > 0)
		{
			//WriteLog(_T("giant"));
			Dealy(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(1);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= 20; i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(4);
		if (solider_num > 0)
		{
			//WriteLog(_T("wallbreaker"));
			Dealy(100);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
			}
		}
		Dealy(AttackChangeDealy);
		//goblin
		solider_num = SendXSolider(5);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SendXSolider(2);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		if (scriptStateCode <= 0)
		{
			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			//WriteLog("释放援军"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			//WriteLog("释放蛮王"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			//WriteLog("释放女王");
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackNextDealy);
	}

	Dealy(2000);
	WaitForReturnHome();
	return 0;
}


int CScript::EqualAttack()
{
	Dealy(2000);
	if (scriptStateCode <= 0 || IsThreadRun == false)
	{
		dm = NULL;
		return 0;
	}
	long AttackSpeed = 10, AttackChangeDealy = 10, AttackNextDealy = 50;
	CString xyStr, usestr;
	AttackSpeed = _ttoi(coc.GetSingleSetting("AttackSpeed"));
	AttackChangeDealy = _ttoi(coc.GetSingleSetting("AttackChangeDealy"));
	AttackNextDealy = _ttoi(coc.GetSingleSetting("AttackNextDealy"));
	AttackSpeed = 20;
	AttackChangeDealy = 500;
	AttackNextDealy = 1000;
	dm.SetPath(_T("\Pic\\attack"));
	WriteLog(_T("定位下兵位置"));
	VARIANT x1, y1;
	long now_x = 0, now_y = 0;
	int solider_num = 0; //
	int distance = 1;
	int attackcount = 0;
	CString attack_xy;
	CString result_posx[4] = {};
	result_posx[0] = dm.FindColorBlockEx(44, 55, 445, 379, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[1] = dm.FindColorBlockEx(32, 349, 447, 630, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[2] = dm.FindColorBlockEx(426, 305, 768, 506, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[3] = dm.FindColorBlockEx(428, 113, 707, 298, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	long x[4][61] = { 0 }, y[4][61] = { 0 };
	x[0][0] = 465, y[0][0] = 149;
	x[1][0] = 159, y[1][0] = 337;
	x[2][0] = 443, y[2][0] = 530;
	x[3][0] = 604, y[3][0] = 311;
	for (int i = 0; i <= 59; i++)
	{
		x[0][i + 1] = x[0][i] - 9;
		y[0][i + 1] = y[0][i] + 7;
		x[1][i + 1] = x[1][i] + 9;
		y[1][i + 1] = y[1][i] + 7;
		x[2][i + 1] = x[2][i] + 9;
		y[2][i + 1] = y[2][i] - 7;
		x[3][i + 1] = x[3][i] - 9;
		y[3][i + 1] = y[3][i] - 7;
	}
	for (int j = 0; j <= 3; j++)
	{
		for (int i = 0; i <= 50; i++)
		{
			attack_xy = dm.FindNearestPos(result_posx[j], 1, x[j][i], y[j][i]);
			x[j][i] = _ttoi(attack_xy.Left(3));
			y[j][i] = _ttoi(attack_xy.Right(3));
			if (scriptStateCode <= 0)
			{
				dm = NULL;
				return 0;
			}
		}
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
	}
	WriteLog(_T("定位完成"));
	Dealy(200);
	GetArmyMsg();
	VARIANT xg, yg;
	for (int j = 0; j <= 3; j++)
	{
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}

		//giant
		solider_num = SendXSolider(GIANT);

		if (solider_num > 0)
		{
			solider_num = attackArmy.giant;
			attackcount = RepairAttackArmy(solider_num, 0, distance);

			Dealy(100);
			for (int i = 0; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(BARBARIN);
		if (solider_num > 0)
		{
			solider_num = attackArmy.babarin;
			attackcount = RepairAttackArmy(solider_num, 0, distance);
			Dealy(50);
			for (int i = 0; i <= attackcount; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(WALLBREAKER);
		if (solider_num > 0)
		{
			solider_num = attackArmy.wallbreaker;
			attackcount = RepairAttackArmy(solider_num, 0, distance);
			Dealy(100);
			for (int i = 0; i <= attackcount; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
			}
		}
		Dealy(AttackChangeDealy);
		//goblin
		solider_num = SendXSolider(GOBLIN);
		if (solider_num > 0)
		{
			solider_num = attackArmy.goblin;
			attackcount = RepairAttackArmy(solider_num, 0, distance);
			Dealy(50);
			for (int i = 0; i <= attackcount; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SendXSolider(ARCHER);
		if (solider_num > 0)
		{
			solider_num = attackArmy.archer;
			attackcount = RepairAttackArmy(solider_num, 0, distance);
			Dealy(50);
			for (int i = 0; i <= attackcount; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		solider_num = SendXSolider(WIZARD);
		if (solider_num > 0)
		{
			solider_num = attackArmy.wizard;
			attackcount = RepairAttackArmy(solider_num, 0, distance);
			Dealy(50);
			for (int i = 0; i <= attackcount; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			WriteLog("释放援军"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			WriteLog("释放蛮王"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			WriteLog("释放女王");
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackNextDealy);
	}
	WriteLog("释放剩余兵种");
	for (int j = 0; j <= 3; j++)
	{
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
		//giant
		solider_num = SendXSolider(3);
		if (solider_num > 0)
		{
			WriteLog(_T("giant"));
			Dealy(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(1);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= 20; i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SendXSolider(WALLBREAKER);
		if (solider_num > 0)
		{
			Dealy(100);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
			}
		}
		Dealy(AttackChangeDealy);
		//goblin
		solider_num = SendXSolider(GOBLIN);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SendXSolider(2);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (scriptStateCode <= 0)
				{
					dm = NULL;
					return 0;
				}
			}
		}
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			WriteLog("释放援军"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			WriteLog("释放蛮王"); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			WriteLog("释放女王");
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackNextDealy);
	}

	Dealy(2000);
	// *********************** End ***********************//

	WaitForReturnHome();
	return 0;
}


int CScript::WriteLog(CString logStr)
{
	coc.State_str = logStr;
	logStr += "\r\n";
	CFile file_log("record.log", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	file_log.SeekToEnd();
	file_log.Write((logStr), strlen(logStr));
	file_log.Close();
	return 0;
}


int CScript::User_Attack()
{
	Dealy(2000);
	if (scriptStateCode <= 0 || IsThreadRun == false)
	{
		dm = NULL;
		return 0;
	}
	long AttackSpeed = 10, AttackChangeDealy = 10, AttackNextDealy = 50;
	long str_count = 0;
	long index = 0;
	long ArmyXcount = 0;
	CString list, usestr;
	AttackSpeed = _ttoi(coc.GetSingleSetting("AttackDeadSpeed"));
	AttackChangeDealy = _ttoi(coc.GetSingleSetting("AttackChangeDealy"));
	AttackNextDealy = _ttoi(coc.GetSingleSetting("AttackNextDealy"));
	AttackSpeed = 20;
	AttackChangeDealy = 500;
	AttackNextDealy = 1000;
	dm.SetPath(_T("\Pic\\attack"));
	WriteLog(_T("定位下兵位置"));
	long ResourceX[4] = { 0 }, ResourceY[4] = { 0 };
	VARIANT x1, y1;
	long now_x = 0, now_y = 0;

	CString attack_xy[4] = {};
	CString attack_sort_xy[4] = {};
	attack_xy[0] = dm.FindColorBlockEx(134, 81, 426, 314, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 1, 88, 10, 10);
	attack_xy[1] = dm.FindColorBlockEx(140, 330, 471, 540, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 1, 88, 10, 10);
	attack_xy[2] = dm.FindColorBlockEx(426, 305, 768, 506, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 1, 88, 10, 10);
	attack_xy[3] = dm.FindColorBlockEx(428, 113, 707, 298, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 1, 88, 10, 10);
	int ArmySort[18] = { 3,1,5,4,2,16,7,6,15,10,11,12,13,14,15,16,17,18 };
	WriteLog(_T("定位完成"));
	// *********************** End ***********************//
	for (int Rattack = 0; Rattack <= 1; Rattack++)
	{
		AttackArea(134, 81, 426, 314, 0, &now_x, &now_y);
		ResourceX[0] = now_x, ResourceY[0] = now_y;
		AttackArea(140, 330, 471, 540, 0, &now_x, &now_y);
		ResourceX[1] = now_x, ResourceY[1] = now_y;
		AttackArea(426, 305, 768, 506, 1, &now_x, &now_y);
		ResourceX[2] = now_x, ResourceY[2] = now_y;
		AttackArea(428, 113, 707, 298, 0, &now_x, &now_y);
		ResourceX[3] = now_x, ResourceY[3] = now_y;

		for (int AttackCount = 0; AttackCount <= 3; AttackCount++)
		{
			if (scriptStateCode <= 0)
			{
				dm = NULL;
				return 0;
			}

			attack_sort_xy[AttackCount] = dm.SortPosDistance(attack_xy[AttackCount], 1, ResourceX[AttackCount], ResourceY[AttackCount]);
			str_count = dm.GetResultCount(attack_sort_xy[AttackCount]);
			for (int i = 0; i <= 17; i++)
			{
				ArmyXcount = SendXSolider(ArmySort[i]);
				if (ArmyXcount > 0)
				{
					for (index = 0; index < str_count&&index + 1 <= (ArmyXcount * 2 / (4 - AttackCount)); index += 2)
					{
						dm.GetResultPos(attack_sort_xy[AttackCount], index, &x1, &y1);
						dm.MoveTo(x1.lVal, y1.lVal);
						Dealy(20);
						dm.LeftClick();
						Dealy(20);
						if (scriptStateCode <= 0)
						{
							dm = NULL;
							return 0;
						}
					}
				}
				Dealy(500);
			}
			Dealy(1000);
		}
		if (scriptStateCode <= 0)
		{
			dm = NULL;
			return 0;
		}
		Dealy(2000);
	}

	WaitForReturnHome();
	return 0;
}


int CScript::check_deadbase()
{
	int ElixirType = 0;
	ElixirType = _ttoi(coc.GetSingleSetting("SearchDeadbaseElixir"));
	int dead0 = 0, dead1 = 0, town_level = 9;
	if (town_level >= 7)
	{
		dm.SetPath(_T("\Pic\\normal\\deadbase"));
		//WriteLog(dm.GetPath());
		VARIANT x, y;
		CString str_i, deadbase_pic;
		str_i = "d_*.bmp";
		switch (ElixirType)
		{
		case 0:
			str_i = "d_*.bmp";
			break;
		case 1:
			str_i = "*75*.bmp|*100*.bmp";
			break;
		case 2:
			str_i = "*100*.bmp";
			break;
		default:
			str_i = "d_*.bmp";

		}
		deadbase_pic = dm.MatchPicName(str_i);


		dm.FindPic(0, 0, 840, 650, deadbase_pic, "0f0f0f", 0.89, 0, &x, &y);

		if (x.lVal > 0)
		{
			dead0 = 1;
		}


	}
	else
	{
		dm.SetPath(_T("\Pic\\weak\\deadbase"));
		CString str_i, deadbase_pic;
		str_i = "d_*.bmp";
		deadbase_pic = dm.MatchPicName(str_i);
		VARIANT x, y;

		dm.FindPic(0, 0, 840, 650, deadbase_pic, "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0) { dead0 = 1; }


	}

	return (dead0 + dead1);
}


int CScript::check_defends()
{
	dm.SetPath(_T("\Pic\\normal\\defends"));
	int IsTooHigh = 0;
	CString str;
	CString match_str, leftStr;
	int* defendType = new int[10];
	defendType[0] = _ttoi(coc.GetSingleSetting("ArcherTower"));
	defendType[1] = _ttoi(coc.GetSingleSetting("Mortar"));
	defendType[2] = _ttoi(coc.GetSingleSetting("WizardTower"));
	defendType[3] = _ttoi(coc.GetSingleSetting("AirDefense"));
	defendType[4] = _ttoi(coc.GetSingleSetting("XBow"));
	defendType[5] = _ttoi(coc.GetSingleSetting("Inferno"));
	defendType[6] = _ttoi(coc.GetSingleSetting("EagleArtillery"));
	int *defendLevel = new int[10];
	defendLevel[0] = _ttoi(coc.GetSingleSetting("ArcherTowerLevel")) + 1;
	defendLevel[1] = _ttoi(coc.GetSingleSetting("MortarLevel")) + 1;
	defendLevel[2] = _ttoi(coc.GetSingleSetting("WizardTowerLevel")) + 1;
	defendLevel[3] = _ttoi(coc.GetSingleSetting("AirDefenseLevel")) + 1;
	defendLevel[4] = _ttoi(coc.GetSingleSetting("XBowLevel")) + 1;
	defendLevel[5] = _ttoi(coc.GetSingleSetting("InfernoLevel")) + 1;
	defendLevel[6] = _ttoi(coc.GetSingleSetting("EagleArtilleryLevel")) + 1;
	CString strDefendName[8] = {};
	CString PicName;
	strDefendName[0] = "ArcherTower";
	strDefendName[1] = "Mortar";
	strDefendName[2] = "WizardTower";
	strDefendName[3] = "AirDefense";
	strDefendName[4] = "XBow";
	strDefendName[5] = "Inferno";
	strDefendName[6] = "EagleArtillery";

	PicName = dm.MatchPicName("*.bmp");

	match_str = dm.FindPicExS(0, 0, 840, 650, PicName, "0f0f0f", 0.9, 0);
	if (match_str.GetLength() > 3)
	{
		for (int i = 0; i < 7; i++)
		{
			if (defendType[i] == 1)
			{
				for (int j = defendLevel[i]; j < 15; j++)
				{
					str.Format("_lv%d", j);
					str = strDefendName[i] + str;
					if (match_str.Find(str) >= 0)
					{
						IsTooHigh = 1;
						break;
					}
				}
				if (IsTooHigh)
				{
					break;
				}

			}
		}


	}

	delete[]defendType;
	delete[]defendLevel;
	return IsTooHigh;
}


int CScript::SearchResult(long InputGold, long IputElixir, long gold, long Elixir, int type)
{
	switch (type)
	{
	case 0:
		if ((gold + Elixir) >= (InputGold + IputElixir))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 1:
		if (gold >= InputGold&&Elixir >= IputElixir)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 2:
		if (gold >= InputGold || Elixir >= IputElixir)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	return 0;
}


int CScript::SearchFish()
{
	WriteLog(_T("搜鱼"));
	dm.MoveTo(59, 601);
	Dealy(200);
	dm.LeftClick();
	Dealy(2000);
	dm.MoveTo(218, 515);
	Dealy(200);
	dm.LeftClick();
	Dealy(200);
	VARIANT x, y;
	int search_i = 0;
	int type = 0;
	int fight_value = 0;
	long SearchCount = 0;
	long SearchMaxCount = 0;
	int DeBugSearchShoot = 0;
	CString str1, str2, str3, G_gold, G_water, G_oil, SearchCount_str;
	str1 = coc.GetSingleSetting("SearchMinGold");
	str2 = coc.GetSingleSetting("SearchMinElixir");
	str3 = coc.GetSingleSetting("SearchMinDarkElixir");
	SearchMaxCount = _ttoi(coc.GetSingleSetting("SearchMaxCount"));
	DeBugSearchShoot = _ttoi(coc.GetSingleSetting("DeBugSearchShoot"));
	type = _ttoi(coc.GetSingleSetting("SearchType"));
	long SearchDealy = _ttoi(coc.GetSingleSetting("SearchDealy")) * 1000;
	long SearchWait = _ttoi(coc.GetSingleSetting("SearchWait")) * 5;

	long T_gold = _ttoi(str1), T_water = _ttoi(str2), T_oil = _ttoi(str3);

	do
	{
		SearchCount++;
		search_i = 0;
		do
		{
			if (scriptStateCode <= 0)
			{
				dm = NULL; return 0;
			}
			dm.FindMultiColor(702, 481, 840, 544, "f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f", 0.9, 0, &x, &y);
			if (search_i >= SearchWait)
			{
				WriteLog(_T("卡白云时间过长！尝试重新启动"));
				scriptStateCode = -2;
				IsThreadRun = false;
				return 0;
			}
			search_i = search_i + 1;
			Dealy(200);
		} while (x.lVal < 0);
		Dealy(100);
		SearchCount_str.Format("SearchCount=%ld", SearchCount);
		dm.UseDict(1);
		Dealy(SearchDealy);
		G_gold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_water = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_oil = dm.Ocr(44, 117, 113, 145, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		WriteLog(SearchCount_str + " [金] " + G_gold + " [水] " + G_water + " [油] " + G_oil);
		if (SearchResult(T_gold, T_water, _ttoi(G_gold), _ttoi(G_water), type) > 0 && _ttoi(G_oil) >= T_oil)
		{
			if (check_deadbase() >= 1)
			{
				fight_value = 1;
				if (check_defends() >= 1)
				{
					fight_value = 0;
					dm.MoveTo(767, 517);
					Dealy(200);
					dm.LeftClick();
					WriteLog(_T("防御过高"));
					Dealy(1000);
				}
			}
			else
			{
				if (DeBugSearchShoot == 1)
				{
					dm.SetPath("\Debug\\Search");
					SearchCount_str.Format("%ld", SearchCount);
					dm.Capture(0, 0, 840, 650, SearchCount_str + ".bmp");
				}
				fight_value = 0;
				dm.MoveTo(767, 517);
				Dealy(200);
				dm.LeftClick();
				WriteLog(_T("不是死鱼"));
				Dealy(1000);
			}
		}
		else
		{
			fight_value = 0;
			dm.MoveTo(767, 517);
			Dealy(200);
			dm.LeftClick();
			Dealy(1000);
		}
		if (false == IsThreadRun)
		{
			return 0;
		}
	} while (fight_value != 1);
	if (false == IsThreadRun)
	{
		dm = NULL; return 0;
	}
	coc.AddSomeCount(0, SearchCount);
	return 1;
}


void CScript::CollectResource()
{
	WriteLog("收集资源");
	VARIANT x, y;
	for (int s = 1; s <= 10; s++)
	{
		dm.FindMultiColor(75, 41, 680, 528, "d7dcb8-0f0f0f", "9|0|d3dcb8-0f0f0f,0|9|b4c080-0f0f0f,4|4|e847d0-0f0f0f", 0.9, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(100);
		}
		Dealy(60);
	}
	Dealy(800);
	for (int s = 1; s <= 10; s++)
	{
		dm.FindMultiColor(75, 41, 680, 528, "d4dab7-0f0f0f", "10|0|d5dab6-0f0f0f,0|8|b7bf82-0f0f0f,5|4|e4c234-0f0f0f", 0.9, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(100);
		}
		Dealy(60);
	}
	Dealy(800);
	for (int s = 1; s <= 5; s++)
	{
		dm.FindMultiColor(75, 41, 680, 528, "d5dcb8-0f0f0f", "9|0|d8dcb8-0f0f0f,0|9|b4bc7d-0f0f0f,9|9|b1bc79-0f0f0f,5|2|2e233d-0f0f0f", 0.9, 1, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
		}
	}
}


int CScript::Donate()
{
	WriteLog("捐兵");
	Dealy(3000);
	int DonateN = 5, DonateType = 0;
	CString colorStr, result, first, next, path;;
	path = coc.GetExePath();
	path += "Import\\DonateSoliderInfo.txt";

	result = coc.ReadFileWithoutPath(path);
	DonateN = _ttoi(coc.GetSingleSetting("DonateCount"));//DonateN
	DonateType = _ttoi(coc.GetSingleSetting("DonateType"));
	int should_donate = 0;
	long FindY = 0;
	dm.SetPath("\Pic\\others\\Donate");
	dm.UseDict(5);
	VARIANT x, y;
	dm.FindMultiColor(3, 297, 40, 393, "f09c11-0f0f0f", "11|14|e8882a-0f0f0f,5|26|ffffff-0f0f0f,3|50|bb4808-0f0f0f", 1.0, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	int IdentifyD[21] = { 0 }, IsArmy[21] = { 0 };
	IsArmy[0] = _ttoi(coc.GetSingleSetting("IsBarbarin"));
	IsArmy[1] = _ttoi(coc.GetSingleSetting("IsArcher"));
	IsArmy[2] = _ttoi(coc.GetSingleSetting("IsGiant"));
	IsArmy[3] = _ttoi(coc.GetSingleSetting("IsGoblin"));
	IsArmy[4] = _ttoi(coc.GetSingleSetting("IsWallBreaker"));
	IsArmy[5] = _ttoi(coc.GetSingleSetting("IsBallon"));
	IsArmy[6] = _ttoi(coc.GetSingleSetting("IsWizard"));
	IsArmy[7] = _ttoi(coc.GetSingleSetting("IsHealer"));
	IsArmy[8] = _ttoi(coc.GetSingleSetting("IsDragon"));
	IsArmy[9] = _ttoi(coc.GetSingleSetting("IsPeka"));
	IsArmy[10] = _ttoi(coc.GetSingleSetting("IsBabyDragon"));
	IsArmy[11] = _ttoi(coc.GetSingleSetting("IsMiner"));
	IsArmy[12] = _ttoi(coc.GetSingleSetting("IsMinion"));
	IsArmy[13] = _ttoi(coc.GetSingleSetting("IsHogRider"));
	IsArmy[14] = _ttoi(coc.GetSingleSetting("IsValkyrie"));
	IsArmy[15] = _ttoi(coc.GetSingleSetting("IsGolem"));
	IsArmy[16] = _ttoi(coc.GetSingleSetting("IsWitch"));
	IsArmy[17] = _ttoi(coc.GetSingleSetting("IsLavaHound"));
	IsArmy[18] = _ttoi(coc.GetSingleSetting("IsBower"));
	CString s;
	CString army[21] = {};
	army[1] = "随意", army[2] = "弓|随|意|", army[3] = "巨人|黑胖|胖子", army[4] = "哥|小偷", army[5] = "炸", army[6] = "黑球", army[7] = "法", army[8] = "天使", army[9] = "龙", army[10] = "皮卡";
	army[11] = "龙宝宝", army[12] = "矿工", army[13] = "亡灵", army[14] = "野猪|猪", army[15] = "武神", army[16] = "石头", army[17] = "女巫", army[18] = "天狗", army[19] = "蓝胖|投手", army[20] = "";
	int ExtraClick = 0;
	for (long donate_y = 89; donate_y < 666; donate_y += 50)
	{
		VARIANT xs, ys;
		dm.FindMultiColor(179, donate_y, 305, donate_y + 60, "c8e470-0F0F0F", "44|-2|cbe873-0F0F0F,-4|7|acd854-0F0F0F,56|7|acd854-0F0F0F", 0.9, 0, &xs, &ys);

		if (xs.lVal > 0)
		{
			Dealy(200);
			long y1, y2;
			y1 = ys.lVal - 50, y2 = ys.lVal + 50;

			s = dm.Ocr(9, y1, 283, y2, "bfc1bf-0f0f0f|f5f5f5-0f0f0f|d7d7d7-0f0f0f|9b9d9b-0f0f0f", 0.85);
			if (s != "")
			{
				WriteLog(_T("[need]:") + s);
			}
			else
			{
				continue;
			}
			for (int j = 0; j <= 19; j++)
			{
				dm.FindStrFast(9, y1, 283, y2, army[j], "bfc1bf-0f0f0f|f5f5f5-0f0f0f|d7d7d7-0f0f0f|9b9d9b-0f0f0f", 0.85, &x, &y);
				if (x.lVal > 0)
				{
					IdentifyD[j] = 1;
				}
				else
				{
					IdentifyD[j] = 0;
				}
			}
			dm.FindMultiColor(179, donate_y, 305, donate_y + 50, "c8e470-0F0F0F", "44|-2|cbe873-0F0F0F,-4|7|acd854-0F0F0F,56|7|acd854-0F0F0F", 0.9, 1, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				Dealy(20);
				dm.LeftClick();
				Dealy(2000);
			}
			dm.FindMultiColor(714, 1, 764, 537, "ffffff-0f0f0f", "-6|-1|f88088-0f0f0f,1|17|ffffff-0f0f0f", 1.0, 1, &x, &y);
			if (x.lVal > 0)
			{

			}
			int y0 = y.lVal + 10;
			CString str_i;

			for (int i = 0; i <= 17; i++)
			{
				switch (DonateType)
				{
				case 0:
					should_donate = IdentifyD[i] * IsArmy[i + 1];
					break;
				case 1:
					should_donate = IsArmy[i + 1];
					break;
				case 2:
					should_donate = 0;
					break;
				default:
					should_donate = 0;
					break;
				}
				if (should_donate > 0)
				{
					int z = 0;

					str_i.Format("%d", i + 1);
					str_i = coc.GetConfig(result, str_i, "[", "]");
					if (str_i.GetLength() <= 2)
					{
						continue;
					}
					z = str_i.Find(",");
					first = str_i.Left(z);
					next = str_i.Right(str_i.GetLength() - z - 1);
					next = next.Left(next.GetLength() - 5);
					dm.FindMultiColor(329, y0, 762, y0 + 210, first, next, 0.9, 0, &x, &y);
					if (x.lVal > 0)
					{
						dm.MoveTo(x.lVal, y.lVal);
						Dealy(20);
						for (int j = 1; j <= DonateN; j++)
						{
							dm.LeftClick();
							Dealy(100);
						}
						break;
					}

				}

			}
			if (false == IsThreadRun)
			{
				return 1;
			}
			Dealy(800);
			dm.FindMultiColor(714, 1, 764, 537, "ffffff-0f0f0f", "-6|-1|f88088-0f0f0f,1|17|ffffff-0f0f0f", 0.9, 1, &x, &y);
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(1500);
		}
		else
		{
			if (ExtraClick < 5)
			{
				FindY = 85;
			}
			else
			{
				FindY = 549;
			}
			dm.FindMultiColor(270, FindY, 312, FindY + 200, "8FC600-040805", "4|0|FFFFFF-050505,10|2|89C100-060301,-1|11|509808-0f0f0f,10|11|509808-0f0f0f", 0.9, 0, &xs, &ys);
			if (xs.lVal > 0 && ExtraClick < 10)
			{
				donate_y = 89;
				dm.MoveTo(xs.lVal, ys.lVal);
				Dealy(20);
				dm.LeftClick();
				ExtraClick += 1;
				Dealy(2000);
			}

		}
		Dealy(100);


	}
	dm.FindMultiColor(714, 1, 764, 537, "ffffff-0f0f0f", "-6|-1|f88088-0f0f0f,1|17|ffffff-0f0f0f", 0.9, 1, &x, &y);
	dm.MoveTo(x.lVal, y.lVal);
	Dealy(20);
	dm.LeftClick();
	Dealy(2000);

	dm.MoveTo(333, 346);
	Dealy(20);
	dm.LeftClick();
	return 0;
}


int CScript::UpGrade_Wall()
{
	dm.SetPath(_T("\Pic\\normal\\update"));
	CString str_i, wall_pic, update_gold, update_water;
	VARIANT x, y;
	str_i = "wall_*.bmp";
	wall_pic = dm.MatchPicName(str_i);
	update_gold = "update_gold.bmp|update_gold_sure.bmp";
	update_water = "update_water.bmp|update_water_sure.bmp";
	WriteLog(wall_pic);
	dm.FindPic(10, 100, 800, 620, wall_pic, "141414", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
		for (int i = 0; i <= 5; i++)
		{
			dm.FindPic(206, 538, 642, 598, update_gold, "141414", 0.9, 0, &x, &y);
			if (x.lVal > 0)
			{
				dm.MoveTo(x.lVal, y.lVal);
				Dealy(20);
				dm.LeftClick();
				for (int j = 0; j <= 5; j++)
				{
					dm.FindPic(338, 448, 549, 538, update_gold, "141414", 0.9, 0, &x, &y);
					if (x.lVal > 0)
					{
						dm.MoveTo(x.lVal, y.lVal);
						Dealy(20);
						dm.LeftClick();
						break;
					}
					Dealy(500);
				}
				Dealy(500);
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::ConnectBsOrOthers()
{
	long window_hwnd = 0;
	int connectType = 0;
	int BindInfo = 0;
	long IsBind = 0;
	CString winText;
	winText = coc.GetSingleSetting("BsOrOtherWindowText");
	CString str;
	connectType = _ttoi(coc.GetSingleSetting("BluestacksOrOthers"));
	CString bindstr[5] = {};
	bindstr[0] = coc.GetSingleSetting("display");
	bindstr[1] = coc.GetSingleSetting("mouse");
	bindstr[2] = coc.GetSingleSetting("keypad");
	bindstr[3] = coc.GetSingleSetting("public_");
	bindstr[4] = coc.GetSingleSetting("mode");
	//****************** check and bind ****************//
	switch (connectType)
	{
	case 0:
		window_hwnd = dm.FindWindow("", "BlueStacks App Player");
		if (window_hwnd <= 0)
		{
			BindInfo = -2;
		}
		else
		{
			IsBind = dm.BindWindow(window_hwnd, _T("gdi2"), _T("windows"), _T("windows"), 0);
			if (IsBind == 1)
			{
				BindInfo = 1;
				return BindInfo;
			}
			else
			{
				BindInfo = 0;
			}
		}
		break;
	case 1:
		if (winText.GetLength() < 1)
		{
			AfxMessageBox("请输入模拟器标题！", MB_OK);
		}
		window_hwnd = dm.FindWindowA("Qt5QWindowIcon", winText);
		coc.parenthwnd = window_hwnd;
		str.Format("window_hwnd=%ld", window_hwnd);
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		str = dm.EnumWindow(window_hwnd, "", "Qt5QWindowIcon", 1);//查找子窗口
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		str = str.Right(str.GetLength() - str.Find(",") - 1);
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		window_hwnd = _ttoi(str);
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);

		if (_ttoi(coc.GetSingleSetting("IsUserBind")) != 1)
		{
			bindstr[0] = "gdi2";
			bindstr[1] = "windows";
			bindstr[2] = "windows";
			bindstr[3] = "";
			bindstr[4] = "0";
		}



		break;
	case 2:
		if (winText.GetLength() < 1)
		{
			AfxMessageBox("请输入模拟器标题！", MB_OK);
		}
		window_hwnd = dm.FindWindowA("Qt5QWindowIcon", winText);
		str.Format("window_hwnd=%ld", window_hwnd);
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		str = dm.EnumWindow(window_hwnd, "QWidgetClassWindow", "Qt5QWindowIcon", 1 + 2);//查找子窗口

		if (str.Find(",") > 0)
		{
			str = str.Right(str.GetLength() - str.Find(",") - 1);
		}
		window_hwnd = _ttoi(str);
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		if (bindstr[3] == "null")
		{
			bindstr[3] = "";
		}
		if (_ttoi(coc.GetSingleSetting("IsUserBind")) != 1)
		{
			bindstr[0] = "dx2";
			bindstr[1] = "windows";
			bindstr[2] = "windows";
			bindstr[3] = "";
			bindstr[4] = "0";
		}


		break;

	default:
		BindInfo = -2;
		break;
	}
	if (window_hwnd)
	{
		coc.BindHwnd = window_hwnd;
		if (_ttoi(coc.GetSingleSetting("IsBindWindowEx")))
		{
			IsBind = dm.BindWindowEx(window_hwnd, bindstr[0], bindstr[1], bindstr[2], bindstr[3], _ttoi(bindstr[4]));
			str.Format("BindWindowEx=%ld", IsBind);
		}
		else
		{
			IsBind = dm.BindWindow(window_hwnd, bindstr[0], bindstr[1], bindstr[2], _ttoi(bindstr[4]));
			str.Format("BindWindow=%ld", IsBind);
		}
		//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
		if (IsBind == 1)
		{
			BindInfo = 1;

		}
		else
		{
			str.Format("GetLastError=%ld", dm.GetLastError());
			//WriteLog(str, true, RGB(0xff, 0x00, 0xff), false);
			BindInfo = -1;
		}


	}
	else
	{

		BindInfo = -2;//no hwnd
	}


	return BindInfo;//-1:Bind False ,-2,No Hwnd
}


int CScript::CloseBS()
{
	int ret = 0;
	CString str;
	CString process_name[8] = {};
	process_name[0] = "HD-Agent.exe";
	process_name[1] = "HD-BlockDevice.exe";
	process_name[2] = "HD-Frontend.exe";
	process_name[3] = "HD-LogRotatorService.exe";
	process_name[4] = "HD-Network.exe";
	process_name[5] = "HD-Service.exe";
	process_name[6] = "HD-SharedFolder.exe";
	process_name[7] = "HD-UpdaterService.exe";
	for (int i = 0; i < 8; i++)
	{
		str = dm.EnumProcess(process_name[i]);
		if (coc.KillProcessById(_ttoi(str)))
		{
			ret += 1;
		}

	}
	//WriteLog("关闭模拟器", true, RGB(0xff, 0x00, 0x00), false);
	return ret;
}


int CScript::SetClientWindowSize()
{
	VARIANT xw, yw;
	long window_hwnd = dm.FindWindow("", "BlueStacks App Player");
	dm.GetClientSize(window_hwnd, &xw, &yw);
	if ((xw.lVal != 850) || (yw.lVal != 667))
	{
		CString str;
		str.Format("错误的分辨率：%ldx%ld", xw.lVal,yw.lVal); 
		WriteLog("错误的分辨率：" + str);
		//WriteLog(_T("设置分辨率"), true, RGB(0xff, 0x00, 0x00), false);
		CRegKey key;
		key.Create(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\BlueStacks\\Guests\\Android\\FrameBuffer\\0"));
		CString strUser = "SOFTWARE\BlueStacks\\Guests\Android\\FrameBuffer";//要写入的键名称
		DWORD strUserValuew = 850;
		DWORD strUserValueh = 667;
		key.SetDWORDValue(_T("Width"), strUserValuew);
		key.SetDWORDValue(_T("Height"), strUserValueh);
		key.SetDWORDValue(_T("GuestWidth"), strUserValuew);
		key.SetDWORDValue(_T("GuestHeight"), strUserValueh);
		key.SetDWORDValue(_T("WindowWidth"), strUserValuew);
		key.SetDWORDValue(_T("WindowHeight"), strUserValueh);
		key.Close();
		CloseBS();
		return 0;
	}
	else
	{
		return 1;
	}
}


int CScript::StartCoc(CString _in_coc_ver)
{
	func_adb("am start -n " + _in_coc_ver);
	WriteLog("启动部落冲突");
	return 0;
}


int CScript::StopCoc(CString _in_coc_ver)
{
	CString close_ver = "";
	close_ver = _in_coc_ver.Left(_in_coc_ver.Find(_T("/")));
	func_adb(_T("am force-stop " + close_ver));
	WriteLog("停止部落冲突");
	return 0;
}


int CScript::DownTroophs()
{
	WriteLog(_T("降杯"));
	dm.MoveTo(59, 601);
	Dealy(200);
	dm.LeftClick();
	Dealy(2000);
	dm.MoveTo(218, 515);
	Dealy(200);

	dm.LeftClick();
	Dealy(200);
	VARIANT x, y;
	int search_i = 0;
	long SearchCount = 0;
	CString str1, str2, str3, G_gold, G_water, G_oil, SearchCount_str;

	long SearchWait = _ttoi(coc.GetSingleSetting("SearchWait")) * 5;

	SearchCount++;
	search_i = 0;
	do
	{
		if (scriptStateCode <= 0)
		{
			dm = NULL; return 0;
		}
		dm.FindMultiColor(702, 481, 840, 544, "f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f", 0.9, 0, &x, &y);
		if (search_i >= SearchWait)
		{
			WriteLog(_T("卡白云时间过长！尝试重新启动"));
			scriptStateCode = -3;
			IsThreadRun = false;
			return 0;
		}
		search_i = search_i + 1;
		Dealy(200);
	} while (x.lVal < 0);
	Dealy(100);

	for (int i = 1; i <= 17; i++)
	{
		if (SendXSolider(i) != 0)
		{
			dm.MoveTo(80, 338);
			Dealy(20);
			dm.LeftClick();
			break;
		}
	}
	Dealy(1000);
	dm.MoveTo(66, 530);
	Dealy(20);
	dm.LeftClick();
	Dealy(2000);
	dm.MoveTo(500, 396);
	Dealy(20);
	dm.LeftClick();
	Dealy(200);
	dm.MoveTo(427, 540);
	Dealy(2000);
	dm.LeftClick();
	return 0;
}


int CScript::SmallScreen()
{
	for (int i = 1; i <= 10; i++)
	{
		if (IsThreadRun == false)
		{

			return 0;
		}
		dm.KeyPress(40);
		Dealy(100);

	}
	func_adb("input swipe 400 100 400 600");
	return 1;
}


int CScript::Statistics()
{
	long LootGold = 0, LootElixir = 0, LootDarkElixir = 0, LootTroophs = 0;
	long RunTime = 0;
	int py = 0;
	py = SwitchNo * 5;
	GetResource();

	Dealy(300);
	LootGold = LootRecord[SwitchNo].GetLootGold();
	LootElixir = LootRecord[SwitchNo].GetLootElixir();
	LootDarkElixir = LootRecord[SwitchNo].GetLootDarkElixir();
	LootTroophs = LootRecord[SwitchNo].GetLootTroophs();
	RunTime = LootRecord[SwitchNo].GetRunTime();
	if (RunTime == 0)
	{
		RunTime = 1;
	}
	CString str[5] = {};
	str[0].Format("%ld", LootRecord[SwitchNo].StartGold);
	str[1].Format("%ld", LootRecord[SwitchNo].StartElixir);
	str[2].Format("%ld", LootRecord[SwitchNo].StartDarkElixir);
	str[3].Format("%ld", LootRecord[SwitchNo].StartTroophs);
	for (int i = 0; i <= 3; i++)
	{
		//pag8.m_ListCtrl1.SetItemText(i + 1 + py, 1, str[i]);
	}
	str[0].Format("%ld", LootRecord[SwitchNo].NowGold);
	str[1].Format("%ld", LootRecord[SwitchNo].NowElixir);
	str[2].Format("%ld", LootRecord[SwitchNo].NowDarkElixir);
	str[3].Format("%ld", LootRecord[SwitchNo].NowTroophs);
	for (int i = 0; i <= 3; i++)
	{
		//pag8.m_ListCtrl1.SetItemText(i + 1 + py, 2, str[i]);
	}
	str[0].Format("%ld", LootGold);
	str[1].Format("%ld", LootElixir);
	str[2].Format("%ld", LootDarkElixir);
	str[3].Format("%ld", LootTroophs);
	for (int i = 0; i <= 3; i++)
	{
		//pag8.m_ListCtrl1.SetItemText(i + 1 + py, 3, str[i]);
	}
	str[0].Format("%ld", LootGold * 60 / RunTime);
	str[1].Format("%ld", LootElixir * 60 / RunTime);
	str[2].Format("%ld", LootDarkElixir * 60 / RunTime);
	str[3].Format("%ld", LootTroophs * 60 / RunTime);
	for (int i = 0; i <= 3; i++)
	{
		//pag8.m_ListCtrl1.SetItemText(i + 1 + py, 4, str[i]);
	}

	str[0].Format("%ld", (LootGold * 24 / RunTime) * 60);
	str[1].Format("%ld", (LootElixir * 24 / RunTime) * 60);
	str[2].Format("%ld", (LootDarkElixir * 24 / RunTime) * 60);
	str[3].Format("%ld", (LootTroophs * 24 / RunTime) * 60);
	for (int i = 0; i <= 3; i++)
	{
		//pag8.m_ListCtrl1.SetItemText(i + 1 + py, 5, str[i]);
	}
	CString tstr;
	tstr = "";
	tstr.Format("运行时间：%ld day %ld h %ld minutes.", RunTime / 1440, (RunTime % 1440) / 60, RunTime % 60);
	//pag8.RunTime.SetWindowTextA(tstr);
	tstr.Format("攻击次数：%ld", coc.GetSomeCount(1));
	//pag8.AttackCount.SetWindowTextA(tstr);
	tstr.Format("搜索次数：%ld", coc.GetSomeCount(0));
	//pag8.SearchCount.SetWindowTextA(tstr);
	tstr.Format("当前账号：%d", SwitchNo);
	//pag8.NowLog.SetWindowText(tstr);
	return 0;
}


bool CScript::HideKey()
{
	return false;
}


int CScript::AddDict()
{
	long ret = 0;
	dm.SetPath("\Dict");
	ret += dm.SetDict(0, "coc_army.bak"); //设置字库 0
	ret += dm.SetDict(1, "cocfish.txt");      //设置字库 1
	ret += dm.SetDict(2, "cocresource.bak");  //设置字库 2
	ret += dm.SetDict(3, "cocbein.bak");      //设置字库 3
									   //dm.SetDict(4, "OnlineTime.txt");   //设置字库 4
	ret += dm.SetDict(5, "coc_donate.txt");   //设置字库 5
	ret += dm.SetDict(6, "AttackArmy.txt");
	return ret;
}


int CScript::RepairAttackArmy(int oldArmyCount, int type, int &distance)
{
	if (type == 4)
	{
		type = 3;
	}
	int attackcount = oldArmyCount / (4 - type);

	if (attackcount == 0)
	{
		distance = MAXATTACKCOUNT;
	}
	else
	{
		distance = MAXATTACKCOUNT / attackcount;
	}

	if (distance < 1)
	{
		distance = 1;
	}
	else if (distance > MAXATTACKCOUNT)
	{
		distance = MAXATTACKCOUNT;
	}
	attackcount *= distance;
	if (attackcount > MAXATTACKCOUNT)
	{
		attackcount = MAXATTACKCOUNT;
	}
	return attackcount;
}


int CScript::GetArmyMsg()
{
	dm.EnableDisplayDebug(1);
	int type = _ttoi(coc.GetSingleSetting("attackCount"));
	if (type == 0)//进行识别
	{

		const int minY = 572;
		const int maxY = 597;
		WriteLog("进行识别");
		WriteLog(dm.GetPath());
		dm.UseDict(6);
		VARIANT x, y;
		CString str;
		CString result, first, next, sim;
		CString army_num_str;
		for (int i = 1; i <=5; i++)
		{
			str.Format("solider_%d.bmp", i);
			WriteLog(str);
			dm.SetPath("\Pic\\attack\\solider");
			dm.FindPic(25, 570, 833, 644, str, "0f0f0f", 0.9,0, &x, &y);
			long x1 = 0, x2 = 0;
			if (x.lVal > 0)
			{
				WriteLog(ARMYNAME[i]);
				WriteLog("find!");
				MakeRect(x.lVal, &x1, &x2);
				army_num_str = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
				dm.SetPath("\Debug");
				dm.CapturePre(str);

				if (army_num_str.GetLength() > 0)
				{
					WriteLog(ARMYNAME[i]);
					WriteLog(army_num_str);
					if (army_num_str.Left(1)=="x")
					{
						army_num_str = army_num_str.Right(army_num_str.GetLength() - 1);
					}
					switch (i)
					{
					case 1:
						attackArmy.babarin = _ttoi(army_num_str);
						break;
					case 2:
						attackArmy.archer = _ttoi(army_num_str);
						break;
					case 3:
						attackArmy.giant = _ttoi(army_num_str);
						break;
					case 4:
						attackArmy.goblin = _ttoi(army_num_str);
						break;
					case 5:
						attackArmy.wallbreaker = _ttoi(army_num_str);
						break;
					default:
						break;
					}
				}

			}
			return 1;

		}
		if (type == 1)//固定为造兵的数量
		{
			return 1;
		}
		return 0;
	}
}

int CScript::MakeRect(long srcX,long* x1,long* x2)
{
	const int minX = 26;
	const int dX = 66;
	const int sX = 3;
	for (int i=minX;i<850;i=i+dX+sX)
	{
		if ((i<=srcX)&&(srcX<=i+dX))
		{
			*x1 = i+10;
			*x2 = i + dX;
			return 1;
		}
	}
	*x1 = srcX - 30;
	*x2 = srcX + 30;
	return 0;
}
