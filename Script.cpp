#include "stdafx.h"
#include "Script.h"
#include "lua_func.h"
#include "botLib.h"
#define AVOID_ZERO(x) ((x)==0?1:(x))
CScript::CScript()
	
{
	scriptVer = cocBotVer;
	scriptInfo = 0;
	attackArmy.archer = 0;
	attackArmy.babarin = 0;
	attackArmy.giant = 0;
	attackArmy.goblin = 0;
	attackArmy.wallbreaker = 0;
	attackArmy.wizard = 0;
	SwitchNo = 0;
	bindHwnd = 0;
	AppCocID = 0;
	AppPlayerType = 0;
	IsSwitch = false;
}


CScript::~CScript()
{

}


long CScript::GetScriptState()
{
	return scriptInfo;
}


CString CScript::GetExePath()
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
	return szIniPath;
}


bool CScript::CreateDm(int type)
{

	::CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);

	if (dm.CreateDispatch(clsid) == TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CScript::Dealy(unsigned long mSeconds)
{
	DWORD t1 = GetTickCount();
	t1 += mSeconds;
	for (; GetTickCount() < t1;)
	{
		if (false == IsThreadRun) break;
		Sleep(1);
	}
}


void CScript::DealyRandTime(unsigned long minDeaySeconds, unsigned long maxDealySeconds)
{
	CString str;
	DWORD s = GetTickCount() / 2555;
	srand(s);
	if (minDeaySeconds >= maxDealySeconds)
	{
		maxDealySeconds = minDeaySeconds + 10;
	}
	long resultRand = minDeaySeconds + (rand() % (maxDealySeconds - minDeaySeconds));
	str.Format("随机延迟:%ld s", resultRand);
	SetLog(str, true, BLUECOLOR, false);
	resultRand *= 1000;
	Dealy(resultRand);
}


void CScript::LeftClick(long x, long y)
{
	dm.MoveTo(x, y);
	Dealy(10);
	dm.LeftClick();
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
	str = dm.EnumProcess("HD-Adb.exe");
	if (str.GetLength() > 0)
	{
		coc.KillProcessById(_ttoi(str));
		ret += 1;
	}
	return ret;
}


int CScript::SelectSolider(int type)
{
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	//dm.SetPath("\Pic\\attack\\solider");
	CString base_path = GetExePath() + "Pic\\attack\\solider\\";
	str.Format("%ssolider_%d.bmp|%ssolider_%d_2.bmp", base_path,type,base_path,type);

	int loc_ret=ImageLoc(25, 570, 833, 650,str,0.95, x, y);
	long x1 = 0, x2 = 0;
	CString armyNum;
	int solider_num = 0;
	if (loc_ret==1)
	{
		dm.UseDict(DICT_COC_ATTACKARMY);
		MakeRect(x, &x1, &x2);
		armyNum = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
		str.Format("%s\t%s", ARMYNAME[type - 1], armyNum);
		SetLog(str);
		if (armyNum.GetLength() > 0)
		{
			if (armyNum.Left(1) == "x")
			{
				armyNum = armyNum.Right(armyNum.GetLength() - 1);
			}
		}
		dm.MoveTo(x, 608);
		Dealy(20);
		dm.LeftClick();
		solider_num = _ttoi(armyNum);
		if (solider_num == 0)solider_num = 1;
	}
	else
	{
		solider_num = 0;
	}
	return solider_num;
}


int CScript::SelectSpell(int type)
{
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	CString base_path = GetExePath() + "Pic\\attack\\spell\\";
	str.Format("%sspell_%d.bmp",base_path, type);
	ImageLoc(25, 570, 833, 650, str, 0.95, x, y);
	long x1 = 0, x2 = 0;
	int solider_num = 0;
	CString armyNum;
	if (x > 0)
	{
		dm.UseDict(DICT_COC_ATTACKARMY);
		MakeRect(x, &x1, &x2);
		armyNum = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);
		str.Format("%d\t%s", type, armyNum);
		SetLog(str);
		//SetLog(armyNum);
		if (armyNum.GetLength() > 0)
		{
			if (armyNum.Left(1) == "x")
			{
				armyNum = armyNum.Right(armyNum.GetLength() - 1);
			}
		}
		dm.MoveTo(x, 608);
		Dealy(20);
		dm.LeftClick();
		solider_num = _ttoi(armyNum);
		if (solider_num == 0)solider_num = 1;
	}
	else
	{
		solider_num = 0;
	}
	return solider_num;
}


int CScript::SelectHero(int type)
{
	const int minY = 572;
	const int maxY = 597;
	int x, y;
	CString str;
	CString base_path = GetExePath() + "Pic\\attack\\king\\";
	str.Format("%sking_%d.bmp", base_path, type);
	ImageLoc(25, 570, 833, 650, str, 0.95, x, y);
	if (x > 0)
	{
		LeftClick(x, y);
		return 1;
	}
	else
	{
		return 0;
	}
}

int CScript::ImageLoc(long x1, long y1, long x2, long y2, const char* file, double sim, int&ret_x, int&ret_y)
{
	void* p = (void*)dm.GetScreenData(x1, y1, x2, y2);
	int retx, rety;
	int ret = ::ImageLoc(x2 - x1, y2 - y1, p, file, sim, &retx, &rety);
	ret_x = ret_y = -1;
	if (ret == 1)
	{
		retx += x1;
		rety += y1;
		ret_x = retx;
		ret_y = rety;
	}
	return ret;
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
			//SetLog("发现广告，尝试清除", true, RGB(0xff, 0x00, 0x00), false);
			return 1;
		}


	}
	return 0;
}


int CScript::WaitForMainScreen()
{
	//if (lua_call_script("test.lua") == 0)
		//return 1;
	dm.SetPath(_T("\Pic\\others\\checkMainScreen"));
	int waitTime = 0;
	VARIANT x, y;
	CString showStr;
	CString PicName, result;
	PicName = dm.MatchPicName("main_screen*.bmp");
	do
	{
		if (_ttoi(coc.getSets("DebugLocateAD")) == 1)
		{
			ClearAdvirtisment();
		}

		dm.SetPath(_T("\Pic\\others\\checkMainScreen"));
		dm.FindMultiColor(12, 5, 837, 51, "3abded-0f0f0f", "30|-1|37bfed-0f0f0f,786|7|fff655-0f0f0f,796|9|ffec22-0f0f0f", 1.0, 0, &x, &y);
		//成功
		if (x.lVal > 0)
		{
			return 1;
		}

		showStr.Format("加载村庄中,请等待：%ds", 60 - waitTime);
		if (waitTime % 5 == 0)
		{
			checkScreenError();
			SetLog(showStr, true, BLUECOLOR, false);
		}
		else
		{
			SetLog(showStr, false, BLUECOLOR, false);
		}
		if (waitTime >= 60)
		{
			scriptInfo = ShouldRestart;
			SetLog(_T("未发现村庄，尝试重启"), true, REDCOLOR, true);
			return -1;
		}
		waitTime++;

		Dealy(1000);
	} while (IsThreadRun);
	return -1;
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
		Dealy(1500);
		dm.FindMultiColor(357, 133, 509, 173, "ffffff-0f0f0f", "63|6|ffffff-0f0f0f", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
			LeftClick(x.lVal, y.lVal);
			Dealy(1000);
			if (_ttoi(coc.getSets("IsChangeWords")) == 1)
			{
				dm.SendString(bindHwnd, coc.getSets("requestWords"));
			}
			Dealy(1000);
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


int CScript::CheckArmyNum(int* trainT)
{


	if (checkMainScreen() != 1)
	{
		return -1;
	}
	VARIANT x, y;
	dm.SetPath("\Pic\\others");
	dm.MoveTo(34, 519);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	CString armyStr, M_time, time_str, spells_str, clancastle_str, clan_spell, ret_str;
	float ret = 0, NowCount = 0, AllCount = 1;
	dm.UseDict(0);
	Dealy(200);
	armyStr = dm.Ocr(75, 134, 155, 157, "ffffff-050505", 0.85);
	if (armyStr.GetLength() <= 0) armyStr = "0/240";
	using namespace std;
	vector<string> vstr;
	_split(armyStr.GetBuffer(), vstr, "/");
	armyStr.ReleaseBuffer();
	vstr.size() == 2 ? AllCount = _ttoi(vstr[1].c_str()) : AllCount = 240;
	NowCount = _ttoi(vstr[0].c_str());
	AllCount > 0 ? ret = ((float)NowCount * 100) / (float)AllCount : ret = 0.0;

	LootRecord[SwitchNo].ArmyRet = ret;
	int pos = 0;
	pos = (int)ret;
	if (pos > 100)
	{
		pos = 0;
	}
	if (pProgress) pProgress->SetPos(pos);
	M_time = dm.Ocr(730, 137, 831, 153, "ffffff-050505", 0.85);
	spells_str = dm.Ocr(75, 283, 125, 302, "ffffff-050505", 0.85);
	clancastle_str = dm.Ocr(184, 436, 238, 456, "ffffff-050505", 0.85);
	clan_spell = dm.Ocr(522, 433, 560, 452, "ffffff-050505", 0.85);
	dm.FindPic(730, 137, 831, 153, "minutes_1.bmp|minutes_1.bmp", "0f0f0f", 0.9, 0, &x, &y);
	if (M_time.GetLength() <= 0)
	{
		time_str = "0";
	}

	x.lVal > 0 ? M_time += _T("分钟") : M_time += "秒";

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
	*trainT = _ttoi(time_str);
	ret_str.Format("%f", ret);
	ret_str += "%";
	SetLog(_T("[兵营人口]" + armyStr + "(" + ret_str + ")[造兵时间]" + M_time), true, RGB(0x00, 0x00, 0xff), false);
	SetLog("[法术] " + spells_str + " [部落援军] " + clancastle_str + " [部落法术] " + clan_spell, true, RGB(0x00, 0x00, 0xff), false);
	if (_ttoi(coc.getSets("RequestArmy")) == 1)
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

	if (ret >= _ttoi(coc.getSets("MinTroopRet")))
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
			Dealy(500);
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
	str_begin = coc.getSets("SpeedUpBegin");
	str_end = coc.getSets("str_end");
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
	if (checkMainScreen() != 1)
	{
		checkScreenError();
		Dealy(2000);
	}
	if (checkMainScreen() != 1) return-1;
	dm.MoveTo(34, 519);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	unsigned int army_num[30] = { 0 };/*士兵数量*/

	army_num[1] = _ttoi(coc.getSets("Barbarin"));
	army_num[2] = _ttoi(coc.getSets("Archer"));
	army_num[3] = _ttoi(coc.getSets("Giant"));
	army_num[4] = _ttoi(coc.getSets("Goblin"));
	army_num[5] = _ttoi(coc.getSets("WallBreaker"));
	army_num[6] = _ttoi(coc.getSets("Ballon"));
	army_num[7] = _ttoi(coc.getSets("Wizard"));
	army_num[8] = _ttoi(coc.getSets("Healer"));
	army_num[9] = _ttoi(coc.getSets("Dragon"));
	army_num[10] = _ttoi(coc.getSets("Peka"));
	army_num[11] = _ttoi(coc.getSets("BabyDragon"));
	army_num[12] = _ttoi(coc.getSets("Miner"));
	army_num[13] = _ttoi(coc.getSets("Minion"));//dark
	army_num[14] = _ttoi(coc.getSets("HogRider"));
	army_num[15] = _ttoi(coc.getSets("Valkyrie"));
	army_num[16] = _ttoi(coc.getSets("Golem"));
	army_num[17] = _ttoi(coc.getSets("Witch"));
	army_num[18] = _ttoi(coc.getSets("LavaHound"));
	army_num[19] = _ttoi(coc.getSets("BowLer"));
	army_num[20] = _ttoi(coc.getSets("LightingSpell"));//spell
	army_num[21] = _ttoi(coc.getSets("HealingSpell"));
	army_num[22] = _ttoi(coc.getSets("RageSpell"));
	army_num[23] = _ttoi(coc.getSets("JumpSpell"));
	army_num[24] = _ttoi(coc.getSets("FreezeSpell"));
	army_num[25] = _ttoi(coc.getSets("CloneSpell"));
	army_num[26] = _ttoi(coc.getSets("PoisonSpell"));
	army_num[27] = _ttoi(coc.getSets("EarthquakeSpell"));
	army_num[28] = _ttoi(coc.getSets("HasteSpell"));
	army_num[29] = _ttoi(coc.getSets("SkeletonSpell"));
	//**************造兵***************//
	attackArmy.babarin = army_num[1];
	attackArmy.archer = army_num[2];
	attackArmy.giant = army_num[3];
	attackArmy.goblin = army_num[4];
	attackArmy.wallbreaker = army_num[5];
	//
	int retx, rety;
	dm.SetPath("\Pic\\others");
	dm.MoveTo(34, 519);
	Dealy(200);
	dm.LeftClick();
	long ex = 0, ey = 0;
	if (WaitPic(25, 63, 211, 134, "\Pic\\others", "trainView1.bmp", 50, false) != 1)
	{
		SetLog("WaitPic false", true, REDCOLOR, false);
		return 0;
	}
	dm.MoveTo(295, 96);
	Dealy(20);
	dm.LeftClick();
	Dealy(1000);
	dm.UseDict(0);
	CString str, now, right;
	float NowCount = 0, AllCount = 1;
	int IsClear = 0;
	IsClear = _ttoi(coc.getSets("IsClearArmy"));
	str = dm.Ocr(43, 125, 128, 152, "ffffff-050505", 0.85);

	now = str.Left(str.Find("/"));
	right = str.Right(str.GetLength() - str.Find("/") - 1);
	NowCount = _ttoi(now);
	AllCount = _ttoi(right);
	if (AllCount == 0)
	{
		AllCount = 1;
	}
	if (NowCount * 100 / AllCount >= _ttoi(coc.getSets("MinTroopRet")))
	{
		dm.MoveTo(814, 53);
		Dealy(20);
		dm.LeftClick();
		checkScreenError();
		return 1;
	}
	ClearArmy();


	CString pic_name, base_path;
	int TrainArmyStyle = 0;
	TrainArmyStyle = _ttoi(coc.getSets("TrainArmyStyle"));
	if (TrainArmyStyle == 0)/*自定义造兵*/
	{
		dm.SetPath("\Pic\\others\\solider");
		base_path = GetExePath() + "Pic\\others\\solider\\";
		for (int i = 1; i <= 12; i++)
		{
			if (army_num[i] == 0)/*无需此造兵*/
			{
				continue;
			}
			pic_name.Format("%ssolider_%d.bmp",base_path, i);
			//dm.FindPic(21, 335, 839, 548, pic_name, "0f0f0f", 0.85, 0, &x, &y);
			ImageLoc(21, 335, 839, 548, pic_name, 0.95, retx, rety);
			if (retx > 0)
			{
				dm.MoveTo(retx,rety);
				for (int j = 1; j <= army_num[i]; j++)
				{

					Dealy(50);
					dm.LeftClick();
				}
			}
			else
			{
				SetLog("Not Find  " + pic_name, true, REDCOLOR, false);
			}
		}
		//adbCmd("input swipe 798 499 50 467");
		adbSwipe(798, 499, 50, 467);
		Dealy(1000);
		for (int i = 13; i <= 19; i++)/*黑水兵*/
		{
			if (army_num[i] == 0)
			{
				continue;
			}
			pic_name.Format("%ssolider_%d.bmp", base_path, i);
			//dm.FindPic(21, 335, 839, 548, pic_name, "0f0f0f", 0.85, 0, &x, &y);
			ImageLoc(21, 335, 839, 548, pic_name, 0.95, retx, rety);
			if (retx > 0)
			{
				dm.MoveTo(retx, rety);
				for (int j = 1; j <= army_num[i]; j++)
				{

					Dealy(50);
					dm.LeftClick();
				}
			}
			else
			{
				SetLog("Not Find  " + pic_name, true, REDCOLOR, false);
			}
	
			Dealy(200);
		}
	}
	if (_ttoi(coc.getSets("IsSpeedUp")) == 1)
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
			SetLog("error:bad one key train!", false, REDCOLOR, false);
		}
	}

	Dealy(1000);
	dm.MoveTo(493, 94);
	Dealy(20);
	dm.LeftClick();
	Dealy(1500);
	dm.SetPath("\Pic\\others\\solider");
	for (int i = 20; i <= 29; i++)/*make spell*/
	{
		if (army_num[i] == 0)
		{
			continue;
		}
		pic_name.Format("spell_%d.bmp", i - 19);
		dm.FindPic(21, 335, 839, 548, pic_name, "0f0f0f", 0.85, 0, &x, &y);
		if (army_num[i] != 0 && x.lVal > 0)
		{
			dm.MoveToEx(x.lVal, y.lVal, 5, 5);
			for (int j = 1; j <= army_num[i]; j++)
			{

				Dealy(50);
				dm.LeftClick();
			}
		}
		else
		{
			//SetLog("[r]Not Find  " + str);
		}
	}

	dm.MoveTo(812, 94);
	Dealy(20);
	dm.LeftClick();
	Dealy(1000);



	return 0;
}


int CScript::adbCmd(CString strCmd)
{

	CString   strOut;
	const int max_size = 512;
	char buffer[max_size] = { 0 };

	using namespace std;
	vector<string> vstr;
	//这里确定模拟器种类，并获得对应参数
	if (AppPlayerType == APP_PLAYER_LIGHTING)
	{
		//::SendMessage(hParennt, TH_UPDATA_APP_PLAYER_INFO, 0, 0);
		//Dealy(1000);
		//雷电专用
		adbCmd(AppPlayerIndex, strCmd);
		return 0;
	}
	//先adb device
	adb.Start(appPlayerInstallDir+"\\HD-Adb.exe devices");
	adb.Stop();
	SetLog(adb.GetOutput());
	//2.选择对应的端口进行连接

	adb.Start(appPlayerInstallDir + "\\HD-Adb.exe shell");
	adb.RunCmd(strCmd);
	adb.Stop();
	CString adb_error = adb.GetOutput();
	SetLog(adb_error, false, REDCOLOR, true);
	if (adb_error.Find("error: device not found") >= 0)
	{
		SetLog(_T("error: device not found,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), true);
		}
		adb.Start(appPlayerInstallDir + "\\HD_Adb.exe shell");
		adb.RunCmd(strCmd);
		adb.Stop();
		SetLog(adb.GetOutput(), false, REDCOLOR, true);

	}
	else if (adb_error.Find("device offline") >= 0)
	{
		SetLog(_T("error: device offline,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), true);
		}
		adb.Start(appPlayerInstallDir + "\\HD_Adb.exe shell");
		adb.RunCmd(strCmd);
		adb.Stop();
		SetLog(adb.GetOutput(), false, REDCOLOR, true);

	}

	return 0;
}


int CScript::adbCmd(int index, CString cmd)
{
	CString str, out;
	str.Format(" adb --index %d --command ", index);
	str += "\"shell ";
	str += cmd;
	str += "\"";
	adb.Start(appPlayerInstallDir+"\\dnconsole.exe"+str);
	adb.Stop();
	out = adb.GetOutput();
	if (out.Find("error: device not found") >= 0)
	{
		SetLog(_T("error: device not found,try to kill adb.exe!"), true, RGB(0xff, 0x00, 0x00), true);
		if (KillAdb())
		{
			SetLog(_T("kill adb.exe is ok, try to restart adb server"), true, RGB(0xff, 0x00, 0x00), true);
		}
		else
		{
			SetLog(_T("error:kill adb.exe 失败 请检查Adb 路径！ "), true, RGB(0xff, 0x00, 0x00), true);
		}
		adb.Start(appPlayerInstallDir + "\\dnconsole.exe" + str);
		adb.Stop();
		out = adb.GetOutput();
		SetLog(out);

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
	long AttackLingtingMinDarkElixir = _ttoi(coc.getSets("AttackLingtingMinDarkElixir"));
	int UseLightingCount = _ttoi(coc.getSets("UseLightingCount"));
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
		//SetLog(ResultPos);
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
	int AttackMinWaitTime = _ttoi(coc.getSets("AttackMinWaitTime"));
	VARIANT x, y;
	SetLog("下兵完成，等待战斗结束", true, RGB(0x00, 0x00, 0xff), false);
	//识别的资源（当前）
	long ntGold = 0, ntElixir = 0, ntDark = 0;
	//之前的资源（1s前）
	long nbGold = 0, nbElixir = 0, nbDark = 0;
	//最少资源
	long minGold, minElixir, minDark;
	minGold = _ttoi(coc.getSets("AttackExitGold"));
	minElixir = _ttoi(coc.getSets("AttackExitElixir"));
	minDark = _ttoi(coc.getSets("AttackExitDarkElixir"));
	//是否资源较少时推出
	int isExit = _ttoi(coc.getSets("AttackIsExitWhenLittleResource"));
	//资源无变化时间（s)
	int  nTime = 0;
	//识别的资源
	CString strGold, strElixir, strDark;
	//设置字库
	dm.UseDict(DICT_COC_FISH);
	CString str_t;
	do
	{
		dm.SetPath(_T("\Pic\\attack"));
		if (false == IsThreadRun) return -1;
		dm.FindPic(392, 520, 462, 562, "return.bmp", "141414", 0.9, 0, &x, &y);
		Dealy(100);

		strGold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		strElixir = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		strDark = dm.Ocr(46, 121, 108, 143, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.85);
		ntGold = _ttoi(strGold), ntElixir = _ttoi(strElixir), ntDark = _ttoi(strDark);

		if (ntGold == nbGold&&ntElixir == nbElixir&&ntDark == nbDark)
		{
			nTime++;
			if (nTime % 2 == 0)
			{
				str_t.Format("%d", AttackMinWaitTime - nTime);
				SetLog("战斗将在" + str_t + "秒后结束", true, RGB(0x00, 0x00, 0xff), false);
			}

		}
		else
		{
			nTime = 0;
		}
		nbGold = ntGold, nbElixir = ntElixir, nbDark = ntDark;
		if (isExit == 1)
		{
			if ((ntGold <= minGold) && (ntElixir <= minElixir) && (ntDark <= minDark))
			{
				break;
			}
		}
		if (false == IsThreadRun) return -1;
		if (x.lVal > 0 || nTime > AttackMinWaitTime)
		{
			if (send_LightngSpell() == 1)
			{
				if (LightingAttack(ntDark))
				{
					Dealy(2000);
				}
			}

			break;
		}
		Dealy(1000);
	} while (nTime <= 255);
	SetLog("返回村庄", true, RGB(0xff, 0x00, 0xff), true);
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
	return 0;
}


int CScript::Attack_Intel()
{

	Dealy(1000);
	if (false == IsThreadRun) return -1;
	long AttackSpeed = 10, AttackChangeDealy = 10;
	AttackSpeed = _ttoi(coc.getSets("AttackSpeed"))/2;
	AttackSpeed = (AttackSpeed + 1) * 10;
	AttackChangeDealy = _ttoi(coc.getSets("AttackGird"));
	AttackChangeDealy = (AttackChangeDealy + 1) * 10;
	dm.SetPath(_T("\Pic\\attack"));
	SetLog(_T("定位下兵位置"));
	//寻找所有下兵色块
	//全部
	CString res,str;

	res = dm.FindColorBlockEx(35, 27, 794, 567, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 70, 10, 10);
	if (res.GetLength() <= 0) return -1;
	//所有坐标
	int nPos = dm.GetResultCount(res);
	long* allx = new long[nPos];
	long* ally = new long[nPos];
	/*初始化*/
	VARIANT tempx, tempy;
	/*获取所有坐标*/
	for (int i=0;i<nPos;i++)
	{
		dm.GetResultPos(res, i, &tempx, &tempy);
		allx[i] = tempx.lVal;
		ally[i] = tempy.lVal;
	}

	//下兵坐标
	long x[MAX_ARMY_COUNT], y[MAX_ARMY_COUNT];
	/*寻求最优坐标*/
	int bestIndex = 0;

	for (int i = 0; i < MAX_ARMY_COUNT; i++)
	{
		bestIndex = Array::FindNearestPos<long>(allx, ally, nPos, ATTACK_CIRCLE_X[i], ATTACK_CIRCLE_Y[i]);
		x[i] = allx[bestIndex];
		y[i] = ally[bestIndex];
	}
	
	/*到这里，之前的大量坐标已经不需要了，删除*/
	delete[]allx, delete[]ally;
	SetLog(_T("定位完成"));
	//识别兵种数量
	float solider_num;
	GetArmyMsg();
	//下兵间距
	float distance = 1;
	/*巨人*/
	solider_num = SelectSolider(GIANT);
	if (solider_num > 0.0001)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
		}
	}
	Dealy(AttackChangeDealy);
	/*野蛮人*/
	solider_num = SelectSolider(BARBARIN);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*炸弹人*/
	solider_num = SelectSolider(WALLBREAKER);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*弓箭手*/
	solider_num = SelectSolider(ARCHER);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*哥布林*/
	solider_num = SelectSolider(GOBLIN);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	/*释放 援军双王*/
	VARIANT vx, vy;
	dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &vx, &vy);//释放 援军
	if (vx.lVal > 0)
	{
		SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(vx.lVal, vy.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0], y[0]); Dealy(20); dm.LeftClick();
	}
	dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &vx, &vy);//bar barin king
	if (vx.lVal > 0)
	{
		SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(vx.lVal, vy.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0], y[0]); Dealy(20); dm.LeftClick();
	}

	dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &vx, &vy);//archer king
	if (vx.lVal> 0)
	{
		SetLog("释放女王", true, BLUECOLOR, false);
		dm.MoveTo(vx.lVal, vy.lVal);
		Dealy(20);
		dm.LeftClick();
		Dealy(200);
		dm.MoveTo(x[120],y[120]);
		Dealy(20);
		dm.LeftClick();
	}
	dm.FindMultiColor(18, 568, 834, 617, GRAND_WARDEN_COLOR1, GRAND_WARDEN_COLOR2, 0.9, 0, &vx, &vy);
	if (vx.lVal > 0)
	{
		SetLog("守护者", true, BLUECOLOR, false);
		dm.MoveTo(vx.llVal,vy.lVal);
		Dealy(20);
		dm.LeftClick();
		Dealy(200);
		dm.MoveTo(x[180],y[180]);
		Dealy(20);
		dm.LeftClick();
	}
	/************************* 再检查一下哪些还没下完 ***********************************/
	/*巨人*/
	solider_num = SelectSolider(GIANT);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
		}
	}
	Dealy(AttackChangeDealy);
	/*野蛮人*/
	solider_num = SelectSolider(BARBARIN);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*炸弹人*/
	solider_num = SelectSolider(WALLBREAKER);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*弓箭手*/
	solider_num = SelectSolider(ARCHER);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	Dealy(AttackChangeDealy);
	/*哥布林*/
	solider_num = SelectSolider(GOBLIN);
	if (solider_num > 0)
	{
		distance = MAX_ARMY_COUNT / solider_num;
		if (distance <= 0.0001)distance = 1;
		for (int i = 0; i < MAX_ARMY_COUNT; i += distance)
		{
			LeftClick(x[i], y[i]);
			Dealy(AttackSpeed);
		}
	}
	/*释放 援军双王*/
	dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &vx, &vy);//释放 援军
	if (vx.lVal > 0)
	{
		SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(vx.lVal, vy.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0], y[0]); Dealy(20); dm.LeftClick();
	}
	dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &vx, &vy);//bar barin king
	if (vx.lVal > 0)
	{
		SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(vx.lVal, vy.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0], y[0]); Dealy(20); dm.LeftClick();
	}

	dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &vx, &vy);//archer king
	if (vx.lVal > 0)
	{
		SetLog("释放女王", true, BLUECOLOR, false);
		dm.MoveTo(vx.lVal, vy.lVal);
		Dealy(20);
		dm.LeftClick();
		Dealy(200);
		dm.MoveTo(x[120], y[120]);
		Dealy(20);
		dm.LeftClick();
	}
	dm.FindMultiColor(18, 568, 834, 617, GRAND_WARDEN_COLOR1, GRAND_WARDEN_COLOR2, 0.9, 0, &vx, &vy);
	if (vx.lVal > 0)
	{
		SetLog("守护者", true, BLUECOLOR, false);
		dm.MoveTo(vx.llVal, vy.lVal);
		Dealy(20);
		dm.LeftClick();
		Dealy(200);
		dm.MoveTo(x[180], y[180]);
		Dealy(20);
		dm.LeftClick();
	}
	Dealy(2000);
	return 0;
}


int CScript::Attack_Equal()
{
	Dealy(2000);
	if (false == IsThreadRun) return -1;
	CString xyStr, usestr;
	long AttackSpeed = 10, AttackChangeDealy = 10;
	AttackSpeed = _ttoi(coc.getSets("AttackSpeed"));
	AttackSpeed = (AttackSpeed + 1) * 10;
	AttackChangeDealy = _ttoi(coc.getSets("AttackGird"));
	AttackChangeDealy = (AttackChangeDealy + 1) * 10;
	dm.SetPath(_T("\Pic\\attack"));
	SetLog(_T("定位下兵位置"), true, BLUECOLOR, false);
	//VARIANT x1, y1;
	int solider_num = 0; //
	float distance = 1.0;
	int attackcount = 0;
	CString attack_xy;
	CString result_posx[4] = {};
	//寻找所有下兵色块
	result_posx[0] = dm.FindColorBlockEx(44, 55, 445, 379, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[1] = dm.FindColorBlockEx(32, 349, 447, 630, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[2] = dm.FindColorBlockEx(426, 305, 768, 506, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	result_posx[3] = dm.FindColorBlockEx(428, 113, 707, 298, "a7b052-050f0f|9cb24a-0f0f0f|bad058-050f0f", 0.99, 56, 8, 8);
	//下兵位置
	long x[4][61] = { 0 }, y[4][61] = { 0 };
	x[0][0] = 465, y[0][0] = 149;
	x[1][0] = 159, y[1][0] = 337;
	x[2][0] = 443, y[2][0] = 530;
	x[3][0] = 604, y[3][0] = 311;
	for (int i = 0; i < MAXATTACKCOUNT; i++)
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
		for (int i = 0; i < MAXATTACKCOUNT; i++)
		{
			attack_xy = dm.FindNearestPos(result_posx[j], 1, x[j][i], y[j][i]);
			x[j][i] = _ttoi(attack_xy.Left(3));
			y[j][i] = _ttoi(attack_xy.Right(3));
			if (false == IsThreadRun) return -1;
		}
		if (false == IsThreadRun) return -1;
	}
	SetLog(_T("定位完成"), true, BLUECOLOR, false);
	Dealy(200);
	GetArmyMsg();
	VARIANT xg, yg;
	for (int j = 0; j <= 3; j++)
	{
		if (false == IsThreadRun) return -1;

		//giant
		solider_num = SelectSolider(GIANT);

		if (solider_num > 0)
		{
			//distance = MAXATTACKCOUNT / (solider_num / (4 - j) + 1);
			// distance*count=ldis
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = distance; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SelectSolider(BARBARIN);
		if (solider_num > 0)
		{
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SelectSolider(WALLBREAKER);
		if (solider_num > 0)
		{
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
			}
		}
		Dealy(AttackChangeDealy);
		//goblin
		solider_num = SelectSolider(GOBLIN);
		if (solider_num > 0)
		{
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SelectSolider(ARCHER);
		if (solider_num > 0)
		{
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		solider_num = SelectSolider(WIZARD);
		if (solider_num > 0)
		{
			distance = army_camp / 4 / AVOID_ZERO(solider_num / (4 - j));
			Dealy(100);
			for (int i = 1; i < MAXATTACKCOUNT; i += distance)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		if (scriptInfo <= 0)
		{

			return 0;
		}
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			SetLog("释放女王", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, GRAND_WARDEN_COLOR1, GRAND_WARDEN_COLOR2, 0.9, 0, &xg, &yg);
		if (xg.lVal > 0)
		{
			SetLog("守护者", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackChangeDealy);
	}
	SetLog("释放剩余兵种", true, BLUECOLOR, false);
	for (int j = 0; j <= 3; j++)
	{
		if (false == IsThreadRun) return -1;
		//giant
		solider_num = SelectSolider(GIANT);
		if (solider_num > 0)
		{
			Dealy(100);
			for (int i = 0; i < solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SelectSolider(BARBARIN);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= 20; i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		solider_num = SelectSolider(WALLBREAKER);
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
		solider_num = SelectSolider(GOBLIN);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		Dealy(AttackChangeDealy);
		//archer
		solider_num = SelectSolider(2);
		if (solider_num > 0)
		{
			Dealy(50);
			for (int i = 0; i <= solider_num / (4 - j); i++)
			{
				dm.MoveTo(x[j][i], y[j][i]);
				Dealy(AttackSpeed);
				dm.LeftClick();
				if (false == IsThreadRun) return -1;
			}
		}
		if (false == IsThreadRun) return -1;
		dm.FindMultiColor(25, 570, 827, 652, "84bce0-0f0f0f", "-26|22|5f97ce-0f0f0f,27|24|6297cc-0f0f0f,-11|45|4b6e8f-0f0f0f,17|42|4a6f95-0f0f0f", 0.9, 1, &xg, &yg);//释放 援军
		if (xg.lVal > 0)
		{
			SetLog("释放援军", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}
		dm.FindMultiColor(18, 568, 834, 617, "e7b463-0f0f0f", "21|13|e8a540-0f0f0f,-7|13|e0bf76-0f0f0f,4|9|e89268-0f0f0f,8|10|ea946e-0f0f0f", 0.9, 1, &xg, &yg);//bar barin king
		if (xg.lVal > 0)
		{
			SetLog("释放蛮王", true, BLUECOLOR, false); dm.MoveTo(xg.lVal, yg.lVal); Dealy(20); dm.LeftClick(); Dealy(200); dm.MoveTo(x[0][1], y[0][1]); Dealy(20); dm.LeftClick();
		}

		dm.FindMultiColor(18, 568, 834, 617, "6C4CB4-040404", "0|0|6C4CB4-040404,4|-1|7253BC-060704,-8|16|D59486-0B1012,7|15|E48A61-040202,8|12|F39A6E-030503,11|12|F4A074-040404,23|13|6C44B6-040202,26|21|6840B0,31|21|6C48BB-040303", 0.9, 1, &xg, &yg);//archer king
		if (xg.lVal > 0)
		{
			SetLog("释放女王", true, BLUECOLOR, false);
			dm.MoveTo(xg.lVal, yg.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
			dm.MoveTo(x[0][1], y[0][1]);
			Dealy(20);
			dm.LeftClick();
		}
		Dealy(AttackChangeDealy);
	}

	Dealy(2000);
	
	return 0;
}


int CScript::SetLog(CString logStr, bool IsShow, COLORREF color, bool IsSave)
{
	//如果父窗口句柄为空，则不发送
	if (hParennt == NULL) return -1;
	//消息结构体
	SEND_INFO info = { logStr,IsShow,color,IsSave };
	//向主窗口发送日志消息
	::SendMessage(hParennt, TH_SETLOG, AppPlayerIndex, (LPARAM)&info);
	return 0;
}


int CScript::Attack_lua()
{
	/*调用lua脚本*/
	lua_call_script(coc.getSets("AttackLuaName"));
	return 0;
}


int CScript::CheckDeadbase()
{
	VARIANT x, y;
	int ElixirType = 0;
	ElixirType = _ttoi(coc.getSets("SearchDeadbaseElixir"));
	int result=-1;
	CString str_i, deadbase_pic;
	if (townLevel >= 7)
	{
		dm.SetPath(_T("\Pic\\normal\\deadbase"));
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
		dm.FindPic(30, 30, 800, 620, deadbase_pic, "0f0f0f", 0.89, 0, &x, &y);
		if (x.lVal > 0)
			result = 1;


	}
	else
	{
		dm.SetPath(_T("\Pic\\weak\\deadbase"));
		
		str_i = "d_*.bmp";
		deadbase_pic = dm.MatchPicName(str_i);

		dm.FindPic(30, 30, 800, 620, deadbase_pic, "0f0f0f", 0.85, 0, &x, &y);
		if (x.lVal > 0)
		{
			result = 1;
		}


	}
	if (result == 1)
	{
		if (townLevel >= 10)
		{
			str_i=dm.FindColorBlockEx(30, 30, 800, 620, "a7b052-050f0f|9cb24a-050f0f|bad058-050f0f|adbc52-050f0f", 1, 30, 6, 6);
			int count = dm.GetResultCount(str_i);
			str_i.Format("attack count:%d", count);
			SetLog(str_i);
			result = count < 100 ? 0 : 1;
		}
	}
	return result;
}


int CScript::CheckDefends()
{
	dm.SetPath(_T("\Pic\\normal\\defends"));
	int IsTooHigh = 0;
	CString str;
	CString match_str, leftStr;
	int defendType[10] = { 0 };
	defendType[0] = _ttoi(coc.getSets("ArcherTower"));
	defendType[1] = _ttoi(coc.getSets("Mortar"));
	defendType[2] = _ttoi(coc.getSets("WizardTower"));
	defendType[3] = _ttoi(coc.getSets("AirDefense"));
	defendType[4] = _ttoi(coc.getSets("XBow"));
	defendType[5] = _ttoi(coc.getSets("Inferno"));
	defendType[6] = _ttoi(coc.getSets("EagleArtillery"));
	int defendLevel[10] = { 0 };
	defendLevel[0] = _ttoi(coc.getSets("ArcherTowerLevel")) + 1;
	defendLevel[1] = _ttoi(coc.getSets("MortarLevel")) + 1;
	defendLevel[2] = _ttoi(coc.getSets("WizardTowerLevel")) + 1;
	defendLevel[3] = _ttoi(coc.getSets("AirDefenseLevel")) + 1;
	defendLevel[4] = _ttoi(coc.getSets("XBowLevel")) + 1;
	defendLevel[5] = _ttoi(coc.getSets("InfernoLevel")) + 1;
	defendLevel[6] = _ttoi(coc.getSets("EagleArtilleryLevel")) + 1;
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
	SetLog(_T("搜鱼"), true, BLUECOLOR, false);
	//进攻按钮
	VARIANT x, y;
	dm.MoveTo(59, 601);
	Dealy(200);
	dm.LeftClick();
	Dealy(2000);
	//搜索按钮
	dm.FindMultiColor(128, 476, 326, 563, "e85d0d-0a0800", "44|1|e75d0d-0a0800,105|-3|e55d0d-0a0800,-11|12|dd590d-0a0800,120|14|dd590d-0a0800", 0.95, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(200);
		dm.LeftClick();
	}
	else
	{
		SetLog("error,can't find search button!", true, REDCOLOR, false);
		return -1;
	}
	Dealy(200);
	const int maxStrLen = 7;
	int search_i = 0;
	int type = 0;
	int fight_value = 0;
	long SearchCount = 0;
	long SearchMaxCount = 0;
	int DeBugSearchShoot = 0;
	CString str1, str2, str3, G_gold, G_water, G_oil, SearchCount_str;
	CString showStr;
	str1 = coc.getSets("SearchMinGold");
	str2 = coc.getSets("SearchMinElixir");
	str3 = coc.getSets("SearchMinDarkElixir");
	SearchMaxCount = _ttoi(coc.getSets("SearchMaxCount"));
	DeBugSearchShoot = _ttoi(coc.getSets("DeBugSearchShoot"));
	type = _ttoi(coc.getSets("SearchType"));
	long SearchDealy = _ttoi(coc.getSets("SearchDealy")) * 1000;
	long SearchWait = _ttoi(coc.getSets("SearchWait")) * 5;
	if (SearchWait / 5 < 20)
	{
		SearchWait = 20 * 5;
	}
	long T_gold = _ttoi(str1), T_water = _ttoi(str2), T_oil = _ttoi(str3);

	do
	{
		SearchCount++;
		search_i = 0;
		do
		{
			if (scriptInfo <= 0)
			{
				return 0;
			}
			dm.FindMultiColor(702, 481, 840, 544, "f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f", 0.9, 0, &x, &y);
			if (search_i >= SearchWait)
			{
				SetLog(_T("卡白云时间过长！尝试重新启动"), true, REDCOLOR, false);
				scriptInfo = -2;
				//IsThreadRun = false;
				return 0;
			}
			search_i = search_i + 1;
			Dealy(200);
		} while (x.lVal < 0);
		Dealy(100);
		SearchCount_str.Format("%ld", SearchCount);
		dm.UseDict(1);
		Dealy(SearchDealy);
		G_gold = dm.Ocr(46, 65, 121, 84, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_water = dm.Ocr(44, 96, 121, 114, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		G_oil = dm.Ocr(44, 117, 113, 145, "fffbcc-030303|ffe8fd-030303|f3f3f3-030303", 0.8);
		showStr = SearchCount_str + " [G] " + G_gold + "[W]" + G_water + "[D]" + G_oil;
		showStr.Format("[S] %3ld [G] %8ld [W] %8ld [D] %8ld", SearchCount, _ttoi(G_gold), _ttoi(G_water), _ttoi(G_oil));
		SetLog(showStr, true, BLUECOLOR, false);
		if (SearchResult(T_gold, T_water, _ttoi(G_gold), _ttoi(G_water), type) > 0 && _ttoi(G_oil) >= T_oil)
		{
			if (CheckDeadbase() == 1)
			{
				fight_value = 1;
				if (CheckDefends() >= 1)
				{
					fight_value = 0;
					dm.MoveTo(767, 517);
					Dealy(200);
					dm.LeftClick();
					SetLog(_T("防御过高"), true, BLUECOLOR, false);
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
				SetLog(_T("不是死鱼"), true, BLUECOLOR, false);
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
		return 0;
	}
	return 1;
}


void CScript::CollectResource()
{
	SetLog("收集资源", true, BLUECOLOR, false);
	VARIANT x, y;

	for (int s = 1; s < 3; s++)
	{
		dm.FindMultiColor(74, 51, 734, 603, "d8dcb8-050808", "15|1|d8dcb8-050808, 5|10|403048, 8|11|4b3854-050808, -3|13|b8c088,16|13|b8c088-050505", 0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(100);
		}
		Dealy(60);
	}
	Dealy(500);
	for (int s = 1; s < 3; s++)
	{
		//dm.FindPic(75, 41, 680, 528, "gold.bmp", "0f0f0f", 0.9, 0, &x, &y);
		dm.FindMultiColor(74, 51, 734, 603, "d6dcb8-050808", "16|2|d0dbb8-050808,6|4|f031d8-080808,9|4|ef35df-090909,5|9|d653c8-090909,7|10|df58d0-090909", 0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(100);
		}
		Dealy(60);
	}
	Dealy(500);
	for (int s = 1; s < 3; s++)
	{
		//dm.FindPic(75, 41, 680, 528, "darkelixir.bmp", "0f0f0f", 0.9, 0, &x, &y);
		dm.FindMultiColor(74, 51, 734, 603, "d3dcb8-090909", "15|0|d4dcb8-090909,5|5|ffe848-090909,6|5|ffed48-090909,9|5|ffe418-090909", 0.9, 0, &x, &y);
		if (x.lVal > 0)
		{
			dm.MoveTo(x.lVal, y.lVal);
			Dealy(20);
			dm.LeftClick();
			Dealy(200);
		}
	}
	Dealy(1000);
}


int CScript::DonateArmy()
{
	if (_ttoi(coc.getSets("DonateArmy")) != 1) return -1;
	SetLog("捐兵", true, BLUECOLOR, false);
	int DonateType = 0;
	int ret = 0;
	DonateType = _ttoi(coc.getSets("DonateType"));
	int should_donate = 0;
	long FindY = 0;
	//1.设置字库
	dm.SetPath("\Pic\\others\\DonateArmy");
	dm.UseDict(DICT_COC_DONATE);
	VARIANT x, y;
	long fx = 0, fy = 0;
	//2.>> button
	dm.FindMultiColor(3, 297, 40, 393, "f09c11-0f0f0f", "11|14|e8882a-0f0f0f,5|26|ffffff-0f0f0f,3|50|bb4808-0f0f0f", 1.0, 1, &x, &y);//>> button
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	else
	{
		SetLog("not find >> button");
		return -1;
	}
	//3.需要设置的

	int IsArmy[21] = { 1 };
	IsArmy[0] = _ttoi(coc.getSets("IsBarbarin"));
	IsArmy[1] = _ttoi(coc.getSets("IsArcher"));
	IsArmy[2] = _ttoi(coc.getSets("IsGiant"));
	IsArmy[3] = _ttoi(coc.getSets("IsGoblin"));
	IsArmy[4] = _ttoi(coc.getSets("IsWallBreaker"));
	IsArmy[5] = _ttoi(coc.getSets("IsBallon"));
	IsArmy[6] = _ttoi(coc.getSets("IsWizard"));
	IsArmy[7] = _ttoi(coc.getSets("IsHealer"));
	IsArmy[8] = _ttoi(coc.getSets("IsDragon"));
	IsArmy[9] = _ttoi(coc.getSets("IsPeka"));
	IsArmy[10] = _ttoi(coc.getSets("IsBabyDragon"));
	IsArmy[11] = _ttoi(coc.getSets("IsMiner"));
	IsArmy[12] = _ttoi(coc.getSets("IsMinion"));
	IsArmy[13] = _ttoi(coc.getSets("IsHogRider"));
	IsArmy[14] = _ttoi(coc.getSets("IsValkyrie"));
	IsArmy[15] = _ttoi(coc.getSets("IsGolem"));
	IsArmy[16] = _ttoi(coc.getSets("IsWitch"));
	IsArmy[17] = _ttoi(coc.getSets("IsLavaHound"));
	IsArmy[18] = _ttoi(coc.getSets("IsBower"));
	IsArmy[19] = 1;
	IsArmy[20] = 1;
	//这里设置两个矩阵
	//意愿矩阵和识别矩阵

	int WantDonate[21] = { 1 };
	int NeedDonate[21] = { -1 };
	CString donateStr;//捐兵的字符串
	CString donateX, donateY;
	VARIANT xs, ys;
	CString str;
	char buffer[512] = { 0 };
	using namespace std;
	vector<string> vstr1, vstr2;
	long lastY = 84;
	long y1, y2;
	y1 = y2 = 0;
	Dealy(2000);
	//4.寻找“增援”按钮
	//捐助按钮
	for (lastY = 84; lastY < 660; )
	{
		dm.FindMultiColor(189, lastY, 306, 660, "cced74-090509", "33|-4|d5f27d-090509,62|-3|d5f17d-090509,1|15|75bf2d-080804,32|17|6db72d-080804,57|16|6ebc2d-080804", 1.0, 0, &x, &y);
		//6.ocr
		fx = x.lVal;
		fy = y.lVal;
		if (fx <= 0)
		{
			lastY += 60;
			continue;
		}
		else
		{
			lastY = fy;
		}
		y1 = fy - 40, y2 = fy + 30;
		donateStr = dm.Ocr(9, y1, 283, y2, "bfc1bf-0f0f0f|f5f5f5-0f0f0f|d7d7d7-0f0f0f|9b9d9b-0f0f0f", 0.85);
		if (donateStr.GetLength() > 0)
		{
			SetLog(_T("需要:") + donateStr, true, BLUECOLOR, false);
		}
		else
		{
			continue;
		}
		//7.查找,并赋值给需求矩阵
		if (DonateType != 2)
		{
			for (int j = 0; j < 21; j++)
			{
				NeedDonate[j] = donateStr.Find(ARMYNAME[j]) + 1;
			}
		}




		//8.点击 “增援”
		dm.MoveTo(fx, fy);
		Dealy(20);
		dm.LeftClick();
		Dealy(2000);
		//find small red x
		dm.FindMultiColor(716, 3, 760, 663, "ffffff", "19|1|cd151d-050505,35|4|ffffff", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{
		}
		else
		{
			SetLog("not find small red x");
			continue;
		}
		int y0 = y.lVal + 10;
		int n = 0;
		//9.寻找兵图标 并点击

		switch (DonateType)
		{
		case 0:
			for (n = 0; n < 21; n++)
			{
				if (WantDonate[n] * NeedDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}
			break;
		case 1:
			for (n = 0; n < 21; n++)
			{
				if (WantDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}
			break;
		case 2:
			for (n = 0; n < 21; n++)
			{

				str.Format("UserWant %d", n);
				GetPrivateProfileString("捐兵/请求", str, "", buffer, 512, coc.GetPath());
				if (strlen(buffer) == 0) continue;
				_split(buffer, vstr1, "|");
				if (vstr1.size() < 2) continue;
				WantDonate[n] = _ttoi(vstr1[0].c_str());
				if (WantDonate[n] != 1) continue;
				if (vstr1[1].length() == 0) continue;
				_split(vstr1[1], vstr2, ",");
				for (int index = 0; index < vstr2.size(); index++)
				{
					NeedDonate[index] = donateStr.Find(vstr2[index].c_str()) + 1;
				}
				if (WantDonate[n] * NeedDonate[n] <= 0) continue;
				if (DonateClick(n, 8, y0) == 1) break;
			}


			break;
		}



		if (false == IsThreadRun)	return 1;

		//10.close .find small red x
		dm.FindMultiColor(716, 3, 760, 663, "ffffff", "19|1|cd151d-050505,35|4|ffffff", 1.0, 1, &x, &y);
		if (x.lVal > 0)
		{

			LeftClick(735, y.lVal);
		}
		Dealy(1500);
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


int CScript::IdentifyIsDonate(int* array, int type /* = 2 */)
{
	return -1;
}

int CScript::UpGradeWall()
{
	if (_ttoi(coc.getSets("UpgradeWall")) != 1) return-1;
	dm.SetPath(_T("\Pic\\normal\\wall"));
	long UpgradeWallMinGold = _ttoi(coc.getSets("UpgradeWallMinGold"));
	long UpgradeWallMinElixir = _ttoi(coc.getSets("UpgradeWallMinElixir"));
	int UpgradeWallUseType = _ttoi(coc.getSets("UpgradeWallUseType"));
	int UpgradeWallLevel = _ttoi(coc.getSets("UpgradeWallLevel"));
	bool IsUpGrade = false;
	VARIANT x, y;
	CString wallPicName;
	CString str, buttonStr, wallPoint;
	switch (UpgradeWallUseType)
	{
	case 0:
		if (LootRecord[SwitchNo].NowGold >= UpgradeWallMinGold)
		{
			buttonStr.Format("upgrade_%d*.bmp", 1);
			IsUpGrade = true;
		}
		break;
	case 1:
		if (LootRecord[SwitchNo].NowElixir >= UpgradeWallMinElixir)
		{
			buttonStr.Format("upgrade_%d*.bmp", 2);
			IsUpGrade = true;
		}
		break;
	case 2:
		if (LootRecord[SwitchNo].NowDarkElixir >= UpgradeWallMinElixir || LootRecord[SwitchNo].NowGold >= UpgradeWallMinGold)
		{
			buttonStr = "upgrade*.bmp";
			IsUpGrade = true;
		}
		break;
	default:
		break;
	}
	if (false == IsUpGrade)
	{
		return 0;
	}


	if (UpgradeWallLevel == 0)
	{
		str = "wall_*.bmp";
	}
	else
	{
		str.Format("wall_%d*.bmp", UpgradeWallLevel);
	}
	wallPicName = dm.MatchPicName(str);//获取城墙图片
	using std::vector;
	using std::string;
	vector<string> help, strHelp;
	wallPoint = dm.FindPicExS(30, 30, 830, 640, wallPicName, "0f0f0f", 0.9, 2);
	if (wallPoint.GetLength() <= 0)
	{
		return 0;
	}
	_split(wallPoint.GetBuffer(), help, "|");
	wallPoint.ReleaseBuffer();
	for (int i = 0; i < help.size(); i++)
	{
		str = help[i].c_str();
		SetLog(str);
		_split(help[i], strHelp, ",");
		dm.MoveTo(_ttoi(strHelp[1].c_str()), _ttoi(strHelp[2].c_str()));
		Dealy(20);
		dm.LeftClick();
		Dealy(500);
		for (int j = 0; j < 10; j++)
		{
			dm.FindMultiColor(357, 523, 432, 552, "ffffb7-050f0f", "0|2|ffffb7-05090f,-1|3|f9f9b4-05090f,0|3|ffffb7-05090f,1|3|faf9b6-05090f,0|7|ffffb7-05090f,4|2|ffffb7-05090f,4|6|fefeb8-05090f,6|1|eae59b-05090f", 0.9, 0, &x, &y);
			if (x.lVal > 0)
			{
				SetLog("find wall");
				dm.FindPic(391, 550, 624, 577, dm.MatchPicName(buttonStr), "0f0f0f", 0.85, 0, &x, &y);
				if (x.lVal > 0)
				{
					dm.MoveTo(x.lVal, y.lVal);
					Dealy(20);
					dm.LeftClick();
					Dealy(1000);
					dm.FindPic(352, 474, 537, 507, dm.MatchPicName(buttonStr), "0f0f0f", 0.85, 0, &x, &y);
					if (x.lVal > 0)
					{
						dm.MoveTo(x.lVal, y.lVal);
						Dealy(20);
						dm.LeftClick();
						return 1;
						break;
					}
				}
			}
			else
			{
				Dealy(100);
			}
		}

		if (i > 5)
		{
			break;
		}
	}
	return 0;


}


int CScript::ConnectAppPlayer()
{
	int BindInfo = 0;
	long IsBind = 0;

	CString str;
	
	CString bindstr[5] = { "" };
	//****************** check and bind ****************//
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:
		//window_hwnd = dm.FindWindow("", "BlueStacks App Player");
		bindstr[0] = "gdi2";
		bindstr[1] = "windows";
		bindstr[2] = "windows";
		bindstr[3] = "";
		bindstr[4] = "0";

		break;
	case APP_PLAYER_LIGHTING:


		SetLog(str);
		bindstr[0] = "dx.graphic.opengl";
		bindstr[1] = "windows";
		bindstr[2] = "windows";
		bindstr[3] = "";
		bindstr[4] = "4";




		break;
	default:
		BindInfo = -2;
		break;
	}
	if (bindHwnd > 0)
	{

		IsBind = dm.BindWindowEx(bindHwnd, bindstr[0], bindstr[1], bindstr[2], bindstr[3], _ttoi(bindstr[4]));
		str.Format("BindWindowEx=%ld", IsBind);
		if (IsBind == 1)
		{
			BindInfo = 1;

		}
		else
		{
			str.Format("GetLastError=%ld", dm.GetLastError());
			SetLog(str);
			BindInfo = -1;
		}


	}
	else
	{

		BindInfo = -2;//no hwnd
	}


	return BindInfo;//-1:Bind False ,-2,No Hwnd
}


int CScript::SetClientWindowSize(int x, int y)
{
	//
	CString path;
	path = coc.GetExePath();
	path += "Config.ini";
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	VARIANT xw, yw;
	CString str;
	CRegKey key;
	DWORD w = x;
	DWORD h = y;
	dm.GetClientSize(bindHwnd, &xw, &yw);
	if ((xw.lVal != 850) || (yw.lVal != 667))
	{

		str.Format("错误的分辨率：%ld,%ld", xw.lVal, yw.lVal);
		SetLog(str, true, BLUECOLOR, false);
	}
	else
	{
		return 0;//normal
	}
	switch (AppPlayerType)
	{
	case APP_PLAYER_BLUESTACKS:

		key.Create(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\BlueStacks\\Guests\\Android\\FrameBuffer\\0"));

		key.SetDWORDValue(_T("Width"), w);
		key.SetDWORDValue(_T("Height"), h);
		key.SetDWORDValue(_T("GuestWidth"), w);
		key.SetDWORDValue(_T("GuestHeight"), h);
		key.SetDWORDValue(_T("WindowWidth"), w);
		key.SetDWORDValue(_T("WindowHeight"), h);
		key.Close();


		break;
	case APP_PLAYER_LIGHTING:
		adb.Start(appPlayerInstallDir+"\\dnconsole.exe modify --index %d --resolution 850,667,160 --cpu 1 --memory 1024");
		adb.Stop();
		break;

	default:
		break;
	}
	return 1;//set
}


int CScript::StartCoc()
{
	CString cocVer, str;
	str.Format("%d", AppCocID);
	char buffer[128] = { 0 };
	GetPrivateProfileString("version", str, "", buffer, 128, coc.GetExePath() + "CocVersion.ini");

	adbRunApp(buffer);
	SetLog("启动部落冲突", true, BLUECOLOR, false);
	return 0;
}


int CScript::StopCoc()
{
	CString cocVer, str;
	str.Format("%d", AppCocID);
	char buffer[128] = { 0 };
	GetPrivateProfileString("Version", str, "", buffer, 128, coc.GetExePath() + "CocVersion.ini");
	cocVer = buffer;
	using namespace std;
	vector<string> vstr;
	_split(cocVer.GetBuffer(), vstr, "/");
	cocVer.ReleaseBuffer();
	adbCloseApp(vstr[0].c_str());
	SetLog("停止部落冲突", true, BLUECOLOR, false);
	return 0;
}


int CScript::ControlTroophs()
{
	if (_ttoi(coc.getSets("ControlTroophs")) == 0 || LootRecord[SwitchNo].NowTroophs <= _ttoi(coc.getSets("MaxTroophs"))) return 0;


	SetLog(_T("降杯"), true, REDCOLOR, false);
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

	long SearchWait = _ttoi(coc.getSets("SearchWait")) * 5;

	SearchCount++;
	search_i = 0;
	do
	{
		if (scriptInfo <= 0)
		{
			return 0;
		}
		dm.FindMultiColor(702, 481, 840, 544, "f0b028-0f0f0f", "71|-4|f0b028-0f0f0f,3|31|d84d00-0f0f0f,87|34|d84800-0f0f0f", 0.9, 0, &x, &y);
		if (search_i >= SearchWait)
		{
			SetLog(_T("卡白云时间过长！尝试重新启动"), true, REDCOLOR, false);
			StopCoc();
			scriptInfo = ShouldRestart;
			//IsThreadRun = false;
			return 0;
		}
		search_i = search_i + 1;
		Dealy(200);
	} while (x.lVal < 0);
	Dealy(100);

	for (int i = 1; i <= 17; i++)
	{
		if (SelectSolider(i) != 0)
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


int CScript::ZoomOut()
{
	const int Ctrl = 17;
	int n = 0;
	AppPlayerType == APP_PLAYER_LIGHTING ? n = 3 : n = 10;
	for (int i = 1; i <= n; i++)
	{
		if (IsThreadRun == false)
		{

			return 0;
		}
		dm.KeyPress(40);
		Dealy(100);

	}
	adbSwipe(400, 100, 400, 600);
	return 1;
}


bool CScript::HideKey()
{
	return false;
}


int CScript::AddDict()
{
	long ret = 0;
	dm.SetPath("\Dict");
	ret += dm.SetDict(DICT_COC_ARMY, "coc_army.bak"); //设置字库 0
	ret += dm.SetDict(DICT_COC_FISH, "cocfish.txt");      //设置字库 1
	ret += dm.SetDict(DICT_COC_RESOURCE, "cocresource.bak");  //设置字库 2
	ret += dm.SetDict(DICT_COC_TROOPTH, "cocbein.bak");      //设置字库 3
									   //dm.SetDict(4, "OnlineTime.txt");   //设置字库 4
	ret += dm.SetDict(DICT_COC_DONATE, "coc_donate.txt");   //设置字库 5
	ret += dm.SetDict(DICT_COC_ATTACKARMY, "AttackArmy.txt");
	return ret;
}


int CScript::RepairAttackArmy(int oldArmyCount, int &distance)
{


	if (oldArmyCount == 0)
	{
		distance = MAXATTACKCOUNT;
	}
	else
	{
		distance = MAXATTACKCOUNT / (oldArmyCount + 2);
	}

	if (distance < 1)
	{
		distance = 1;
	}
	else if (distance > MAXATTACKCOUNT)
	{
		distance = MAXATTACKCOUNT - 2;
	}
	return 0;
}


int CScript::GetArmyMsg()
{

	int type = _ttoi(coc.getSets("attackCount"));
	if (type == 0)//进行识别
	{

		const int minY = 572;
		const int maxY = 597;
		SetLog("识别军队信息：", true, BLUECOLOR, false);
		dm.UseDict(6);
		VARIANT x, y;
		CString str;
		CString result, first, next, sim;
		CString army_num_str;
		for (int i = 1; i <= 12; i++)
		{
			str.Format("solider_%d.bmp", i);
			dm.SetPath("\Pic\\attack\\solider");
			dm.FindPic(25, 570, 833, 644, str, "0f0f0f", 0.9, 0, &x, &y);
			long x1 = 0, x2 = 0;
			if (x.lVal > 0)
			{
				MakeRect(x.lVal, &x1, &x2);
				army_num_str = dm.Ocr(x1, minY, x2, maxY, "ffffff-0f0f0f", 0.85);

				if (army_num_str.GetLength() > 0)
				{
					str = ARMYNAME[i];
					str += ":";
					str += army_num_str;
					SetLog(str, true, BLUECOLOR, false);
					if (army_num_str.Left(1) == "x")
					{
						army_num_str = army_num_str.Right(army_num_str.GetLength() - 1);
					}
					switch (i)
					{
					case BARBARIN:
						attackArmy.babarin = _ttoi(army_num_str);
						break;
					case ARCHER:
						attackArmy.archer = _ttoi(army_num_str);
						break;
					case GIANT:
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

		}


	}
	if (type == 1)//固定为造兵的数量
	{
		return 1;
	}
	return 1;
}


int CScript::MakeRect(long srcX, long* x1, long* x2)
{
	const int minX = 26;
	const int dX = 66;
	const int sX = 4;
	for (int i = minX; i < 850; i = i + dX + sX)
	{
		if ((i <= srcX) && (srcX <= i + dX))
		{
			*x1 = i + 10;
			*x2 = i + dX;
			return 1;
		}
	}
	*x1 = srcX - 30;
	*x2 = srcX + 30;
	return 0;
}


long CScript::WaitPic(long x1, long y1, long x2, long y2, LPCTSTR path, LPCTSTR picName, int timesOut, bool Isclick)
{
	VARIANT x, y;
	int index = 0;
	long result = 0;
	dm.SetPath(path);
	do
	{
		index++;
		timesOut--;
		dm.FindPic(x1, y1, x2, y2, picName, "0f0f0f", 0.9, 0, &x, &y);
		if (index > MAX_FIND_PIC_TIME || timesOut < 0)
		{
			break;
		}
		else
		{
			Dealy(30);
		}

	} while (x.lVal <= 0);
	if (x.lVal&&y.lVal > 0)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	if (Isclick == true && result == 1)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}

	return result;
}


int CScript::adbClick(int x, int y)
{
	CString str;
	str.Format("input tap %d %d", x, y);
	adbCmd(str);
	return 0;
}


int CScript::adbSwipe(int x1, int y1, int x2, int y2)
{
	CString str;
	str.Format("input swipe %d %d %d %d", x1, y1, x2, y2);
	adbCmd(str);
	return 0;
}


int CScript::adbKeyEvent(int keyCode)
{
	CString str;
	str.Format("input keyevent %d", keyCode);
	adbCmd(str);
	return 0;
}


int CScript::adbInputText(CString text)
{
	CString buffer = "input text ";
	buffer += text;
	adbCmd(text);
	return 0;
}


int CScript::adbRunApp(CString bagNameAndClassName)
{

	CString str = "am start -n ";
	str += bagNameAndClassName;
	adbCmd(str);
	return 0;
}


int CScript::adbCloseApp(CString packageName)
{
	CString buffer = "am force-stop ";
	buffer += packageName;
	adbCmd(buffer);
	return 0;
}


int CScript::Statistics()
{
	GetResource();
	if (hParennt == NULL) return -1;
	::SendMessage(hParennt, TH_STASTICS, (WPARAM)&LootRecord[SwitchNo], AppPlayerIndex * 3 + SwitchNo);
	return 0;
}


int CScript::DonateClick(int type, int count, int y0)
{
	const long x1 = 322;
	const long x2 = 757;
	CString str;
	dm.SetPath("\Pic\\others\\DonateArmy");

	str.Format("d%d.bmp", type + 1);
	if (type >= 19)
	{
		str = dm.MatchPicName("d*.bmp");
	}
	VARIANT x, y;
	dm.FindPic(x1, y0, x2, y0 + 210, str, "0f0f0f", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		for (int j = 1; j <= count; j++)
		{
			dm.LeftClick();
			Dealy(100);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


int CScript::checkMainScreen()
{
	checkScreenError();
	Dealy(1000);
	int ret = 0;
	VARIANT x, y;
	
	for (int i = 0; i < 5; i++)
	{
		dm.FindMultiColor(12, 5, 837, 51, "3abded-0f0f0f", "30|-1|37bfed-0f0f0f,786|7|fff655-0f0f0f,796|9|ffec22-0f0f0f", 1.0, 0, &x, &y);
		if (x.lVal > 0)
		{
			ret = 1;
			break;
		}
		if (IsThreadRun == false)
		{
			ret = -1;
		}
		else
		{
			Dealy(500);
		}

	}
	return ret;
}


int CScript::checkScreenError()
{
	dm.SetPath(_T("\Pic\\others\\checkMainScreen"));
	VARIANT x, y;
	CString str;
	//close
	str = dm.MatchPicName("buttonClose*.bmp");
	dm.FindPic(400, 846, 8, 350, str, "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	//<<
	str = dm.MatchPicName("buttonRequest*.bmp");
	dm.FindPic(309, 285, 356, 406, str, "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	//ok
	dm.FindPic(250, 300, 700, 600, "okButton.bmp", "0f0f0f", 0.90, 1, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	//close red x
	const int x1 = 563, y1 = 3, x2 = 846, y2 = 301;
	dm.FindMultiColor(x1, y1, x2, y2, "ff8d95-050505", "12|1|ff8d95-050505,21|1|ff8d95-050505,11|11|ffffff-050505,12|11|ffffff-050505,-1|21|ed1115-050505,24|20|eb1115-050505", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	//船
	dm.FindMultiColor(490, 3, 802, 222, "612028-080808", "0|1|602028-080808,-1|3|5d1e26-080808,-1|5|5c1c24-080808,-1|6|5b1c24-080808", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	//回营
	dm.FindMultiColor(12, 560, 112, 650, "eeebd6-030706", "67|-2|f1f2d9-030706,17|2|832b18-030706,56|8|c44e2d-030706,31|24|ffad8f-051312,48|22|ffc0a1-051312", 0.9, 0, &x, &y);
	if (x.lVal > 0)
	{
		dm.MoveTo(x.lVal, y.lVal);
		Dealy(20);
		dm.LeftClick();
	}
	return 0;
}


int CScript::LaunchAppPlayer(int wParam)
{
	CString str;

	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:
		if (PathFileExists(appPlayerInstallDir))
		{
			ShellExecute(NULL, "open", appPlayerInstallDir+"\\HD-StartLauncher.exe", NULL, NULL, SW_NORMAL);
		}
		else
		{
			AfxMessageBox("PathFile not Exists");
			IsThreadRun = false;
		}


		break;
	case APP_PLAYER_LIGHTING:
		if (PathFileExists(appPlayerInstallDir))
		{
		
			str.Format(" launch --index %d", wParam);
			adb.Start(appPlayerInstallDir+"\\dnconsole.exe"+str);
			adb.Stop();
		}
		else
		{
			AfxMessageBox("PathFile not Exists");
			IsThreadRun = false;
		}

	
		break;
	default:
		break;
	}

	SetLog("打开模拟器", true, RGB(0xff, 0x00, 0x00), false);
	return 1;
}


int CScript::QuitAppPlayer(int wParam)
{
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	CString path, str;
	path = coc.GetExePath();
	path += "Config.ini";
	int ret = 0;
	CString process_name[8] = {};
	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:

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

		break;
	case APP_PLAYER_LIGHTING:
		if (PathFileExists(appPlayerInstallDir))
		{

			str.Format(" quit --index %d", wParam);
			adb.Start(appPlayerInstallDir+"\\dnconsole.exe" + str);
			adb.Stop();
		}
		else
		{
			AfxMessageBox("PathFile not Exists");
			IsThreadRun = false;
		}
		str = adb.GetOutput();
		if (str.GetLength() <= 4) return 0;
		break;

	default:
		break;
	}

	SetLog("关闭模拟器", true, RGB(0xff, 0x00, 0x00), false);
	return ret;
}

int CScript::RestartScript()
{
	int ret = 0;
	SetLog("掉线");
	//1.
	StopCoc();
	//2.
	scriptInfo = SCRIPT_STATE_IN_RUN;
	//3.先解绑窗口，再把之前创建的对象释放了
	TRACE("3.先解绑窗口，再把之前创建的对象释放了");
	dm.UnBindWindow();
	dm.ReleaseDispatch();
	dm = NULL;
	//4.重新创建一个
	TRACE("4.创建大漠对象");
	if (false == CreateDm())
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
	}
	//5..检测插件版本
	TRACE("5..检测插件版本");
	if (dm.Ver() != DM_VER_5)
	{

		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，插件版本不正确，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	//6..设置错误提示
	TRACE("6..设置错误提示");
	dm.SetShowErrorMsg(_ttoi(coc.getSets("SetShowErrorMsg")));
	Dealy(500);

	//7..绑定模拟器
	TRACE("7..绑定模拟器");
	ret = SetBindHwnd();
	if (ret <= 0)
	{
		AfxMessageBox("未发现模拟器，请重启模拟器和辅助");
		IsThreadRun = false;
		return 0;
	}
	ret = ConnectAppPlayer();
	if (ret == -1)
	{
		SetLog("链接模拟器失败!", true, RGB(0xff, 0x00, 0xff), true);

		IsThreadRun = false;
		return 0;
	}
	if (ret == -2)
	{
		SetLog("请检查模拟器是否打开!", true, RGB(0xff, 0x00, 0xff), true);

		IsThreadRun = false;
		return 0;
	}
	Dealy(5000);
	TRACE("8..添加字库");
	//8..添加字库
	AddDict();
	//9.
	StartCoc();

	return 1;
}

int CScript::WaitForTrainArmy()
{
	StopCoc();
	SetLog("等待造兵");
	CString str;
	long st = trainTime * 60;
	do
	{
		str.Format("剩余时间：%dm %ds.", st / 60, st % 60);
		SetLog(str, false, BLUECOLOR, false);
		if (false == IsThreadRun) return-1;
		Dealy(1000);
		st--;
	} while (st > 0);
	scriptInfo = SCRIPT_STATE_IN_RUN;
	StartCoc();
	return 0;
}

int CScript::SwitchCoc()
{

	//1.关闭coc
	StopCoc();
	do
	{
		//由于最先运行的是主账号，编号为零，故每次切换，编号增加 1
		SwitchNo += 1;
		//如果超出最大编号，设置成零
		if (SwitchNo >= MAX_SWITCH_COUNT) SwitchNo = 0;
		//如果需切换，则确定为新编号，开始切换
		if (cocInfo[SwitchNo].IsSwitch == true) break;
	} while (IsThreadRun);

	//2.改变配置文件
	coc.SetPath(cocInfo[SwitchNo].configName);
	//3.改变coc 版本编号
	AppCocID = cocInfo[SwitchNo].AppID;
	//4.等等一会 30s
	Dealy(30000);
	//5.启动 coc
	StartCoc();
	//6.设置脚本信息为正常
	scriptInfo = SCRIPT_STATE_IN_RUN;
	//结束
	return 0;
}

int CScript::Attack()
{
	int Ret = 0;
	if (_ttoi(coc.getSets("Attack")) != 1) return 0;
	SetLog("Attack");
	MakeArmy();
	Dealy(3000);
	if (IsThreadRun == false)  return 0;
	Ret = SearchFish();
	if (Ret == 1)/*搜索成功*/
	{
		int AttackType = _ttoi(coc.getSets("AttackDeadbaseStyle"));
		switch (AttackType)
		{
		case 0:
			SetLog(_T("智能攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_Intel(); //下兵

			break;
		case 1:
			SetLog(_T("均分式攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_Equal();

			break;
		case 2:/*lua 脚本攻击*/
			SetLog(_T("lua 脚本攻击"), true, RGB(0xff, 0x00, 0x00), true);
			Ret = Attack_lua(); //下兵
			break;

		}
		/*等待返回*/
		Ret= WaitForReturnHome();
		return Ret;
	}
	else/*搜索失败*/
	{
		return -1;
	}

}

int CScript::script_init()
{
	CString str;
	int ret = 0,temp;
	//1.变量初始化
	SetLog("初始化...", true, BLACKCOLOR, true);
	coc.Initialize();
	townLevel = _ttoi(coc.getSets("townLevel"))+2;
	//这是切换信息初始化
	//a.主账号
	cocInfo[0].IsSwitch = true;
	cocInfo[0].configName = coc.GetPath();
	cocInfo[0].AppID = _ttoi(coc.getSets("GameVersion"));
	//b.子账号
	for (int i = 1; i < MAX_SWITCH_COUNT; i++)
	{
		str.Format("IsSwitch --Index %d", i);
		cocInfo[i].IsSwitch = _ttoi(coc.getSets(str));
		str.Format("ConfigPath --Index %d", i);
		cocInfo[i].configName = coc.getSets(str);
		str.Format("CocVersion --Index %d", i);
		cocInfo[i].AppID = _ttoi(coc.getSets(str));
		LootRecord[i].InitlizeDetail();
	}
	SwitchNo = 0;
	//coc 编号
	AppCocID = _ttoi(coc.getSets("GameVersion"));
	//是否下线
	IsOffLine = _ttoi(coc.getSets("OffLine"));
	//是否切换
	IsSwitch = _ttoi(coc.getSets("IsSwitchMode"));
	switch (townLevel)/*初始化总人口*/
	{
	case 2:
		army_camp = 40;
		break;
	case 3:
		army_camp = 60;
		break;
	case 4:
		army_camp = 80;
		break;
	case 5:
		army_camp = 120;
		break;
	case 6:
		army_camp = 150;
		break;
	case 7:
		army_camp = 200;
		break;
	case 8:
		army_camp = 200;
		break;
	case 9:
		army_camp = 220;
		break;
	case 10:
		army_camp = 240;
		break;
	case 11:
		army_camp = 220;
		break;
	default:
		army_camp = 200;
		break;
	}
	//2.创建大漠对象

	if (false == CreateDm())
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
	}


	//3.检测插件版本

	if (dm.Ver() != DM_VER_5&&dm.Ver() != DM_VER_6)
	{

		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，插件版本不正确，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	//4.设置错误提示

	dm.SetShowErrorMsg(_ttoi(coc.getSets("SetShowErrorMsg")));
	Dealy(500);

	//5.检查adb路径是否正确
	if (!PathFileExists(appPlayerInstallDir))
	{
		AfxMessageBox("模拟器路径错误，请重新设置！");
		IsThreadRun = false;
		return 0;
	}
	//检测句柄
	ret = SetBindHwnd();
	temp = 120;
	if (ret<=0) /*模拟器未打开，自动打开并等待，最长120s*/
	{
		LaunchAppPlayer(AppPlayerIndex);
		while (_ttoi(getList2(AppPlayerIndex,4))==0&&IsThreadRun&&temp>0)//等待模拟器启动完成
		{
			Dealy(1000);
			temp--;
		}
		ret = SetBindHwnd();
		if (temp==0)/*超时*/
		{
			SetLog("time out!", true, REDCOLOR, false);
			IsThreadRun = false;
			return -1;
		}
	}
	//6.设置分辨率
	ret = SetClientWindowSize(850, 667);

	if (ret == 0)
	{
		//分辨率正常
	}
	else if (ret == 1)
	{
		//设置好了分辨率，现在需要关闭模拟器
		SetLog("设置好了分辨率，现在需要关闭模拟器");
		QuitAppPlayer(AppPlayerIndex);
		//等待5秒m
		Dealy(5000);
		//打开模拟器
		LaunchAppPlayer(AppPlayerIndex);
		//等等30s
		SetLog("打开模拟器,等等30s");
		Dealy(3000);
		temp = 120;
		while (_ttoi(getList2(AppPlayerIndex, 4)) == 0 && IsThreadRun&&temp > 0)//等待模拟器启动完成
		{
			Dealy(1000);
			temp--;
		}
		ret = SetBindHwnd();
		if (temp == 0)/*超时*/
		{
			SetLog("time out!", true, REDCOLOR, false);
			IsThreadRun = false;
			return -1;
		}
	}
	//7.绑定模拟器

	ret = ConnectAppPlayer();
	if (ret == -1)
	{
		SetLog("链接模拟器失败!", true, RGB(0xff, 0x00, 0xff), true);

		IsThreadRun = false;
		return 0;
	}
	if (ret == -2)
	{
		SetLog("请检查模拟器是否打开!", true, RGB(0xff, 0x00, 0xff), true);

		IsThreadRun = false;
		return 0;
	}




	//8.添加字库
	AddDict();

	//9.再打开coc
	StartCoc();
	//10.到这里初始化工作已经结束，接下是主线任务
	return 1;
}

int CScript::script_main()
{

	int Ret = -1;
	//检测插件版本
	if (dm.Ver() != DM_VER_5&&dm.Ver() != DM_VER_6)
	{
		IsThreadRun = false;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;
	if (false == IsThreadRun) return 0;
	//缩放主屏幕
	Ret = ZoomOut();
	if (false == IsThreadRun) return 0;
	Dealy(1000);
	if (false == IsThreadRun) return 0;
	//资源统计
	Statistics();
	if (false == IsThreadRun) return 0;
	//资源搜集
	CollectResource();
	if (false == IsThreadRun) return 0;
	//杯段调整
	ControlTroophs();
	if (scriptInfo == ShouldRestart) return -1;
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;
	//检测士兵数量
	if (false == IsThreadRun) return 0;
	Ret = CheckArmyNum(&trainTime);
	if (false == IsThreadRun) return 0;
	//攻击
	if (Ret == 1)  Ret = Attack();
	//卡白云返回
	if (scriptInfo == ShouldRestart) return -1;
	if (false == IsThreadRun) return 0;
	//检测主屏幕
	if (WaitForMainScreen() < 0) return -1;

	//造兵
	if (trainTime == 0 && LootRecord[SwitchNo].ArmyRet <= 95)
	{
		SetLog("补兵", true, BLUECOLOR, false);
		MakeArmy();
	}


	if (false == IsThreadRun) return 0;
	//随机延迟
	DealyRandTime(15, 60);
	if (false == IsThreadRun) return 0;
	//捐兵
	DonateArmy();
	if (false == IsThreadRun) return 0;
	//升级城墙
	UpGradeWall();
	if (trainTime > 2)
	{
		if (IsOffLine) scriptInfo = ShouldWaitForArmy;
		if (IsSwitch) scriptInfo = ShouldSwitch;
	}
	return 0;
}

static unsigned  EntryScript(LPVOID pParam)
{
	CScript *script_info = (CScript *)pParam;


	//脚本初始化
	script_info->script_init();

	// 开始脚本循环
	do
	{
		if (false == script_info->IsThreadRun) return 0;
		//主线功能
		script_info->script_main();
		//中途停止了
		if (false == script_info->IsThreadRun) return 0;
		//掉线,重启脚本
		if (script_info->scriptInfo == ShouldRestart)
		{
			script_info->RestartScript();
			//由于掉线原因，脚本到这里必须重启，故到此结束
			continue;//进入下一轮循环
		}
		if (false == script_info->IsThreadRun) return 0;
		//等待造兵
		if (script_info->scriptInfo == ShouldWaitForArmy)
		{
			script_info->WaitForTrainArmy();
		}
		if (false == script_info->IsThreadRun) return 0;
		//切换配置
		if (script_info->scriptInfo == ShouldSwitch)
		{
			script_info->SwitchCoc();
		}
		//判断脚本是否需要停止，如果不需要，则进入下一轮循环
	} while (script_info->IsThreadRun);

	return 1;

}

CScript*  StartOneScript(CScript *script_info, int index, const char* configFile)
{
	if (script_info == NULL)
		return NULL;
	//1.序号
	if (index >= 0) script_info->AppPlayerIndex = index;
	//2.设置配置路径
	if (configFile) script_info->coc.SetPath(configFile);
	//3.设置窗口句柄
	//if (appHwnd > 0) script_info->bindHwnd = appHwnd;
	//4.线程标志
	script_info->IsThreadRun = true;
	script_info->IsThreadRun = true;
	script_info->scriptInfo = 1;
	// 5.创建线程
	script_info->pThread = AfxBeginThread(EntryScript, (void*)script_info, 0, 0);
	if (script_info->pThread->m_hThread == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	return script_info;
}

BOOL         StopOneScript(CScript  *script_info)
{
	if (script_info == NULL) return FALSE;

	// 设置标志位
	script_info->IsThreadRun = false;
	//script_info->scriptInfo = -10;
	script_info->IsThreadRun = false;
	// 等待最多3秒,如果超时,就强制结束线程.危险.(有资源泄漏)
	if (script_info->pThread == NULL) return TRUE;
	if (WAIT_OBJECT_0 != WaitForSingleObject(script_info->pThread->m_hThread, 0xfff))
	{
		// 先解绑窗口. 避免窗口崩溃
		script_info->dm.UnBindWindow();
		TerminateThread(script_info->pThread->m_hThread, 0);
		//CloseHandle(script_info->pThread->m_hThread);
	}
	//释放大漠对象
	script_info->dm = NULL;


	return TRUE;
}

BOOL         SuspendOneScript(CScript* script_info)
{
	if (script_info == NULL) return FALSE;
	script_info->pThread->SuspendThread();

	return TRUE;
}

BOOL         ResumOneScript(CScript* script_info)
{
	if (script_info == NULL) return FALSE;
	script_info->pThread->ResumeThread();

	return TRUE;
}

BOOL         SuspendAllScript(CScript* script_info[])
{
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		if (script_info == NULL) continue;;
		script_info[i]->pThread->SuspendThread();
	}


	return TRUE;
}

BOOL         ResumAllScript(CScript* script_info[])
{
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		if (script_info == NULL) continue;
		script_info[i]->pThread->ResumeThread();
	}


	return TRUE;
}

BOOL          StopAllScript(CScript * all_script_info[])
{
	// 先把所有标志位置0
	int i;
	for (i = 0; i < MAX_THREAD_COUNT; ++i)
	{

		if (all_script_info[i] == NULL) continue;
		all_script_info[i]->IsThreadRun = 0;
	}

	// 等待所有
	for (i = 0; i < MAX_THREAD_COUNT; ++i)
	{
		if (all_script_info[i] == NULL) continue;
		// 等待最多3秒,如果超时,就强制结束线程.危险.(有资源泄漏)
		if (WAIT_OBJECT_0 != WaitForSingleObject(all_script_info[i]->pThread->m_hThread, 3000))
		{
			// 先解绑窗口. 避免窗口崩溃
			all_script_info[i]->dm.UnBindWindow();
			TerminateThread(all_script_info[i]->pThread->m_hThread, 0);
		}
		all_script_info[i]->dm = NULL;
		//释放内存
		//消去地址
		all_script_info[i] = NULL;
	}

	return TRUE;
}


int CScript::SetBindHwnd()
{

	long nHwnd = 0;
	switch (AppPlayerType)
	{
	case  APP_PLAYER_BLUESTACKS:
		nHwnd = (long) ::FindWindow(nullptr, "BlueStacks App Player");
		break;
	case APP_PLAYER_LIGHTING:
		nHwnd = _ttoi(getList2(AppPlayerIndex,3));
		break;
	default:
		break;
	}
	if (nHwnd > 0)
	{
		bindHwnd = nHwnd;
		return 1;
	}
	else
	{
		bindHwnd = 0;
		return 0;
	}
}

CString CScript::getList2(int x, int y)
{
	CString str;
	using namespace std;
	vector<string> vstr1, vstr2;
	if (AppPlayerType==APP_PLAYER_LIGHTING)
	{
		adb.Start(appPlayerInstallDir + "\\dnconsole.exe list2");
		adb.Stop();
		str = adb.GetOutput();
		if (str.GetLength() <= 4) return "";
		_split(str.GetBuffer(), vstr1, "\n");
		str.ReleaseBuffer();
		if (vstr1.size() <= x) return "";
		if (vstr1[x].length() <= 1) return "";
		_split(vstr1[x], vstr2, ",");
		if (vstr2.size() <= y) return "";
		return CString(vstr2[y].c_str());
	}
	return "";
}
