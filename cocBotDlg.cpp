
// newcocbotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "cocBotDlg.h"
#include "afxdialogex.h"

#include "ConnectServer.h"
page1 pag1;//page class
page2 pag2;
page3 pag3;
page4 pag4;
page5 pag5;
page6 pag6;
page7 pag7;
page8 pag8;
page9 pag9;
page10 pag10;
BindSet bindset;

class ConnectServer;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*************** Global Ver ***************//

ConnectServer* BotServer;//Bot Server
CAdbshell adb; // Adb;
long exit_all = 1;//exit code
HANDLE hThread_ID1;//Main_Thread
HANDLE hThread_ID2;//Main_Game
HANDLE hThread_ID3;//Other_Thread
int ThreadCount = 0; //Main_Game Thread Counts
bool IsConnect = false;
bool IsFisrstRecord = true;
//int train_time = 1;
//int script->SwitchNo = 0;
//Detail  script->LootRecord[15];
int Exit_State = 0;
CScript* script = new CScript;
//*********** Struct ****************//
//***** Global Functoin ***********//
CString GetExePath()
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
int StopThread()
{
	script->dm = NULL;
	WaitForSingleObject(hThread_ID2, 3000);
	TerminateThread(hThread_ID2, 3000);
	return 1;
}
CString log_file(CString file)
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
	szIniPath = szIniPath + _T("\\Log");
	szIniPath = szIniPath + _T("\\");
	szIniPath = szIniPath + file + _T(".log");
	return szIniPath;

}
void  WriteLog(CString logStr)
{
	CString strTime, keytime, WriteStr;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%y-%m-%d");
	keytime = tm.Format("%X");
	WriteStr = _T("[") + keytime + _T("]") + logStr + _T("\r\n");
	if (logStr.Left(3) != "[h]")
	{
		//***********RICH EDIT********************//
		CHARFORMAT cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE;
		cf.dwEffects = CFM_UNDERLINE;

		int x = pag9.m_RichEdit1.GetLineCount() - 1;
		if (logStr.Left(3) == "[r]")
		{
			logStr = logStr.Right(logStr.GetLength() - 3);
			cf.yHeight = 13 * 13;
			cf.crTextColor = RGB(0XFF, 0X0, 0X0);
		}
		else
		{
			cf.yHeight = 13 * 13;
			cf.crTextColor = RGB(0X00, 0X00, 0X00);
		}
		strcpy_s(cf.szFaceName,32, _T("宋体"));
		//cf.szFaceName=_T("隶书");
		WriteStr = _T("[") + keytime + _T("]") + logStr + _T("\r\n");
		if (WriteStr.GetLength() > 100)
		{
			WriteStr = "too long !";
		}
		script->coc.State_str = logStr;
		if (pag9.m_RichEdit1.GetLineCount() >= 1000)
		{
			pag9.m_RichEdit1.SetWindowText(_T(""));
		}
		pag9.m_RichEdit1.SetSel(-1, -1);
		pag9.m_RichEdit1.ReplaceSel(WriteStr, 0);
		int lineStart = pag9.m_RichEdit1.LineIndex(x);//取第x行的第一个字符的索引
		int lineEnd = pag9.m_RichEdit1.LineIndex(x + 1) - 1;//取第x行的最后一个字符的索引——用第x+1行的第一个索引减1来实现
		pag9.m_RichEdit1.SetSel(lineStart, lineEnd);//选取第一行字符
		pag9.m_RichEdit1.SetSelectionCharFormat(cf);//设置颜色
		pag9.m_RichEdit1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}


	CFile file_log(log_file(strTime), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	file_log.SeekToEnd();
	file_log.Write(WriteStr, strlen(WriteStr));
	file_log.Close();
}
void WriteLog(CString logStr, bool IsShow, COLORREF color, bool IsSave)
{
	CString strTime, keytime, WriteStr;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%y-%m-%d");
	keytime = tm.Format("%X");
	WriteStr = _T("[") + keytime + _T("]") + logStr + _T("\r\n");
	//***********RICH EDIT********************//
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE;
	cf.dwEffects = CFM_UNDERLINE;
	int x = pag9.m_RichEdit1.GetLineCount() - 1;
	cf.yHeight = 13 * 13;
	cf.crTextColor = color;
	strcpy(cf.szFaceName, _T("宋体"));
	WriteStr = _T("[") + keytime + _T("]") + logStr + _T("\r\n");
	if (IsShow)
	{
		if (pag9.m_RichEdit1.GetLineCount() >= 1000)
		{
			pag9.m_RichEdit1.SetWindowText(_T(""));
		}
		pag9.m_RichEdit1.SetSel(-1, -1);
		pag9.m_RichEdit1.ReplaceSel(WriteStr, 0);
		int lineStart = pag9.m_RichEdit1.LineIndex(x);//取第x行的第一个字符的索引
		int lineEnd = pag9.m_RichEdit1.LineIndex(x + 1) - 1;//取第x行的最后一个字符的索引——用第x+1行的第一个索引减1来实现
		pag9.m_RichEdit1.SetSel(lineStart, lineEnd);//选取第一行字符
		pag9.m_RichEdit1.SetSelectionCharFormat(cf);//设置颜色
		pag9.m_RichEdit1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	script->coc.State_str = logStr;


	if (IsSave)
	{
		CFile file_log(log_file(strTime), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		file_log.SeekToEnd();
		file_log.Write(WriteStr, strlen(WriteStr));
		file_log.Close();
	}

}
int SendMsgToServer(CString str);

CString GetAllSetting()
{
	CString str_set;
	CString winText;
	CString midStr;
	winText = "";
	pag1.license.GetWindowTextA(midStr);
	winText = "[license=" + midStr + "]";
	str_set += winText; winText = "";
	pag1.BsOrOtherWindowText.GetWindowTextA(midStr);
	winText = "[BsOrOtherWindowText=" + midStr + "]";
	str_set += winText; winText = "";
	winText.Format("[ServerPort=%d]", pag1.ServerPort.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[BluestacksOrOthers=%d]", pag1.BluestacksOrOthers.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[BsOrOtherNo=%d]", pag1.BsOrOtherNo.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[GameVersion=%d]", pag1.GameVersion.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[OffLine=%d]", pag1.OffLine.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[RequestArmy=%d]", pag1.RequestArmy.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[Attack=%d]", pag1.Attack.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[DonateArmy=%d]", pag1.DonateArmy.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[UpgradeWall=%d]", pag1.UpgradeWall.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[UpgradeHeros=%d]", pag1.UpgradeHeros.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[ControlTroophs=%d]", pag1.ControlTroophs.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[LightingDarkElixir=%d]", pag1.LightingDarkElixir.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[RemoveTree=%d]", pag1.RemoveTree.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[RearmAll=%d]", pag1.RearmAll.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[QuickSet=%d]", pag1.QuickSet.GetCurSel());
	str_set += winText; winText = "";;
	pag1.QuickSetShow.GetWindowTextA(midStr);
	winText = "[QuickSetShow=" + midStr + "]";
	str_set += winText; winText = "";;
	pag1.LoadInSet.GetWindowTextA(midStr);
	winText = "[LoadInSet=" + midStr + "]";
	str_set += winText; winText = "";;
	pag1.LoadOutSet.GetWindowTextA(midStr);
	winText = "[LoadOutSet=" + midStr + "]";
	str_set += winText; winText = "";;
	winText.Format("[TrainArmyStyle=%d]", pag2.TrainArmyStyle.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[IsClearArmy=%d]", pag2.IsClearArmy.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[IsAddArmy=%d]", pag2.IsAddArmy.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[IsSpeedUp=%d]", pag2.IsSpeedUp.GetCheck());
	str_set += winText; winText = "";;
	pag2.SpeedUpBegin.GetWindowTextA(midStr);
	winText = "[SpeedUpBegin=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.SpeedUpEnd.GetWindowTextA(midStr);
	winText = "[SpeedUpEnd=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Barbarin.GetWindowTextA(midStr);
	winText = "[Barbarin=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Archer.GetWindowTextA(midStr);
	winText = "[Archer=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Giant.GetWindowTextA(midStr);
	winText = "[Giant=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Goblin.GetWindowTextA(midStr);
	winText = "[Goblin=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.WallBreaker.GetWindowTextA(midStr);
	winText = "[WallBreaker=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Ballon.GetWindowTextA(midStr);
	winText = "[Ballon=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Wizard.GetWindowTextA(midStr);
	winText = "[Wizard=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Healer.GetWindowTextA(midStr);
	winText = "[Healer=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Dragon.GetWindowTextA(midStr);
	winText = "[Dragon=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Peka.GetWindowTextA(midStr);
	winText = "[Peka=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.BabyDragon.GetWindowTextA(midStr);
	winText = "[BabyDragon=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Miner.GetWindowTextA(midStr);
	winText = "[Miner=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Minion.GetWindowTextA(midStr);
	winText = "[Minion=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.HogRider.GetWindowTextA(midStr);
	winText = "[HogRider=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Valkyrie.GetWindowTextA(midStr);
	winText = "[Valkyrie=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Golem.GetWindowTextA(midStr);
	winText = "[Golem=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.Witch.GetWindowTextA(midStr);
	winText = "[Witch=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.LavaHound.GetWindowTextA(midStr);
	winText = "[LavaHound=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.BowLer.GetWindowTextA(midStr);
	winText = "[BowLer=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.LightingSpell.GetWindowTextA(midStr);
	winText = "[LightingSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.HealingSpell.GetWindowTextA(midStr);
	winText = "[HealingSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.RageSpell.GetWindowTextA(midStr);
	winText = "[RageSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.JumpSpell.GetWindowTextA(midStr);
	winText = "[JumpSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.FreezeSpell.GetWindowTextA(midStr);
	winText = "[FreezeSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.CloneSpell.GetWindowTextA(midStr);
	winText = "[CloneSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.PoisonSpell.GetWindowTextA(midStr);
	winText = "[PoisonSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.EarthquakeSpell.GetWindowTextA(midStr);
	winText = "[EarthquakeSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.HasteSpell.GetWindowTextA(midStr);
	winText = "[HasteSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag2.SkeletonSpell.GetWindowTextA(midStr);
	winText = "[SkeletonSpell=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.MinTroopRet.GetWindowTextA(midStr);
	winText = "[MinTroopRet=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchMinGold.GetWindowTextA(midStr);
	winText = "[SearchMinGold=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchMinElixir.GetWindowTextA(midStr);
	winText = "[SearchMinElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchMinDarkElixir.GetWindowTextA(midStr);
	winText = "[SearchMinDarkElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchDealy.GetWindowTextA(midStr);
	winText = "[SearchDealy=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchWait.GetWindowTextA(midStr);
	winText = "[SearchWait=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.SearchMaxCount.GetWindowTextA(midStr);
	winText = "[SearchMaxCount=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.MinTroophs.GetWindowTextA(midStr);
	winText = "[MinTroophs=" + midStr + "]";
	str_set += winText; winText = "";;
	pag3.MaxTroophs.GetWindowTextA(midStr);
	winText = "[MaxTroophs=" + midStr + "]";
	str_set += winText; winText = "";;
	winText.Format("[IsWaitBarbarinKing=%d]", pag3.IsWaitBarbarinKing.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWaitArcherKing=%d]", pag3.IsWaitArcherKing.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWaitGrandKing=%d]", pag3.IsWaitGrandKing.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWaitClanCastleTroopsAndSpells=%d]", pag3.IsWaitClanCastleTroopsAndSpells.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWaitSpell=%d]", pag3.IsWaitSpell.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[ArcherTower=%d]", pag3.ArcherTower.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[Mortar=%d]", pag3.Mortar.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[WizardTower=%d]", pag3.WizardTower.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[AirDefense=%d]", pag3.AirDefense.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[XBow=%d]", pag3.XBow.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[Inferno=%d]", pag3.Inferno.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[EagleArtillery=%d]", pag3.EagleArtillery.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[SearchType=%d]", pag3.SearchType.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[SearchDeadbaseGoldCollector=%d]", pag3.SearchDeadbaseGoldCollector.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[SearchDeadbaseElixir=%d]", pag3.SearchDeadbaseElixir.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[ArcherTowerLevel=%d]", pag3.ArcherTowerLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[MortarLevel=%d]", pag3.MortarLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[WizardTowerLevel=%d]", pag3.WizardTowerLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[AirDefenseLevel=%d]", pag3.AirDefenseLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[XBowLevel=%d]", pag3.XBowLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[InfernoLevel=%d]", pag3.InfernoLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[EagleArtilleryLevel=%d]", pag3.EagleArtilleryLevel.GetCurSel());
	str_set += winText;
	winText.Format("[AttackSpeed=%d]", pag4.AttackSpeed.GetCurSel());
	str_set += winText;
	winText.Format("[AttackGird=%d]", pag4.AttackGird.GetCurSel());
	str_set += winText;
	winText.Format("[attackCount=%d]", pag4.attackCount.GetCurSel());
	str_set += winText;
	winText.Format("[AttackDeadbaseStyle=%d]", pag4.AttackDeadbaseStyle.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[AttackActivebaseStyle=%d]", pag4.AttackActivebaseStyle.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[AttackMinDarkElixirLevel=%d]", pag4.AttackMinDarkElixirLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[UseLightingCount=%d]", pag4.UseLightingCount.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[AttackIsExitWithoutResource=%d]", pag4.AttackIsExitWithoutResource.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[AttackIsExitWhenLittleResource=%d]", pag4.AttackIsExitWhenLittleResource.GetCheck());
	str_set += winText; winText = "";;
	pag4.AttackMinWaitTime.GetWindowTextA(midStr);
	winText = "[AttackMinWaitTime=" + midStr + "]";
	str_set += winText; winText = "";;
	pag4.AttackExitGold.GetWindowTextA(midStr);
	winText = "[AttackExitGold=" + midStr + "]";
	str_set += winText; winText = "";;
	pag4.AttackExitElixir.GetWindowTextA(midStr);
	winText = "[AttackExitElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	pag4.AttackExitDarkElixir.GetWindowTextA(midStr);
	winText = "[AttackExitDarkElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	pag4.AttackLingtingMinDarkElixir.GetWindowTextA(midStr);
	winText = "[AttackLingtingMinDarkElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	winText.Format("[DonateType=%d]", pag5.DonateType.GetCurSel());
	str_set += winText; winText = "";;
	pag5.DonateMinSendGetRet.GetWindowTextA(midStr);
	winText = "[DonateMinSendGetRet=" + midStr + "]";
	str_set += winText; winText = "";;
	pag5.DonateCount.GetWindowTextA(midStr);
	winText = "[DonateCount=" + midStr + "]";
	str_set += winText; winText = "";;
	pag5.DonateDealy.GetWindowTextA(midStr);
	winText = "[DonateDealy=" + midStr + "]";
	str_set += winText; winText = "";;
	winText.Format("[IsDonateSendGetRet=%d]", pag5.IsDonateSendGetRet.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsDonateNotFull=%d]", pag5.IsDonateNotFull.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsBarbarin=%d]", pag5.IsBarbarin.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsArcher=%d]", pag5.IsArcher.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsGiant=%d]", pag5.IsGiant.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsGoblin=%d]", pag5.IsGoblin.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWallBreaker=%d]", pag5.IsWallBreaker.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsBallon=%d]", pag5.IsBallon.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWizard=%d]", pag5.IsWizard.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsHealer=%d]", pag5.IsHealer.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsDragon=%d]", pag5.IsDragon.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsPeka=%d]", pag5.IsPeka.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsBabyDragon=%d]", pag5.IsBabyDragon.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsMiner=%d]", pag5.IsMiner.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsMinion=%d]", pag5.IsMinion.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsHogRider=%d]", pag5.IsHogRider.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsValkyrie=%d]", pag5.IsValkyrie.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsGolem=%d]", pag5.IsGolem.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsWitch=%d]", pag5.IsWitch.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsLavaHound=%d]", pag5.IsLavaHound.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsBower=%d]", pag5.IsBower.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsPoison=%d]", pag5.IsPoison.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsEarthquake=%d]", pag5.IsEarthquake.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsHaste=%d]", pag5.IsHaste.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsSkeleton=%d]", pag5.IsSkeleton.GetCheck());
	str_set += winText; winText = "";;
	pag6.UpgradeWallMinGold.GetWindowTextA(midStr);
	winText = "[UpgradeWallMinGold=" + midStr + "]";
	str_set += winText; winText = "";;
	pag6.UpgradeWallMinElixir.GetWindowTextA(midStr);
	winText = "[UpgradeWallMinElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	pag6.UpgradeHeroMinDarkElixir.GetWindowTextA(midStr);
	winText = "[UpgradeHeroMinDarkElixir=" + midStr + "]";
	str_set += winText; winText = "";;
	winText.Format("[IsSkeleton=%d]", pag6.UpgradeWallUseType.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[UpgradeWallLevel=%d]", pag6.UpgradeWallLevel.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[UpgradeHeroType=%d]", pag6.UpgradeHeroType.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[DeBugSearchShoot=%d]", pag7.DeBugSearchShoot.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[DebugLocateAD=%d]", pag7.DebugLocateAD.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[SetShowErrorMsg=%d]", pag7.SetShowErrorMsg.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsSwitchMode=%d]", pag7.IsSwitchMode.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[DisableSetWindowSize=%d]", pag7.DisableSetWindowSize.GetCheck());
	str_set += winText; winText = "";
	winText.Format("[SwitchModeVersion_1=%d]", pag7.SwitchModeVersion_1.GetCurSel());
	str_set += winText; winText = "";;
	//bind set
	winText.Format("[IsUserBind=%d]", bindset.IsUserBind.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[IsBindWindowEx=%d]", bindset.IsBindWindowEx.GetCheck());
	str_set += winText; winText = "";;
	winText.Format("[display=%d]", bindset.display.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[mouse=%d]", bindset.mouse.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[keypad=%d]", bindset.keypad.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[public_=%d]", bindset.public_.GetCurSel());
	str_set += winText; winText = "";;
	winText.Format("[mode=%d]", bindset.mode.GetCurSel());
	str_set += winText;
	bindset.AdbPath.GetWindowText(midStr);
	winText = "[AdbPath=" + midStr + "]";
	str_set += winText;
	CString str = "0";
	winText = "";
	for (int i = 0; i < 15; i++)
	{
		str.Format("[IsSwitchX%d=%d]", i, pag7.m_list1.GetCheck(i));
		str_set += str;

	}
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			str = pag7.m_list1.GetItemText(i, j);
			if (j == 1)
			{
				midStr.Format("[VersionNameX%d=", i);
			}
			if (j == 2)
			{
				midStr.Format("[ConfigPathX%d=", i);
			}
			if (j == 3)
			{
				midStr.Format("[VersionNoX%d=", i);
			}
			winText = midStr + str + "]";
			str_set += winText;
		}
	}
	return str_set;
}
void UpdateWindowSet(CString result_str)
{
	CbotFunction bot;

	bot.SetAllSetting(result_str);
	pag1.license.SetWindowText(bot.GetSingleSetting("license"));
	pag1.ServerPort.SetCurSel(_ttoi(bot.GetSingleSetting("ServerPort")));
	pag1.BluestacksOrOthers.SetCurSel(_ttoi(bot.GetSingleSetting("BluestacksOrOthers")));
	pag1.BsOrOtherNo.SetCurSel(_ttoi(bot.GetSingleSetting("BsOrOtherNo")));
	pag1.BsOrOtherWindowText.SetWindowTextA(bot.GetSingleSetting("BsOrOtherWindowText"));
	pag1.GameVersion.SetCurSel(_ttoi(bot.GetSingleSetting("GameVersion")));
	pag1.OffLine.SetCheck(_ttoi(bot.GetSingleSetting("OffLine")));
	pag1.RequestArmy.SetCheck(_ttoi(bot.GetSingleSetting("license")));
	pag1.RequestArmy.SetCheck(_ttoi(bot.GetSingleSetting("RequestArmy")));
	pag1.Attack.SetCheck(_ttoi(bot.GetSingleSetting("Attack")));
	pag1.DonateArmy.SetCheck(_ttoi(bot.GetSingleSetting("DonateArmy")));
	pag1.UpgradeWall.SetCheck(_ttoi(bot.GetSingleSetting("UpgradeWall")));
	pag1.UpgradeHeros.SetCheck(_ttoi(bot.GetSingleSetting("UpgradeHeros")));
	pag1.ControlTroophs.SetCheck(_ttoi(bot.GetSingleSetting("ControlTroophs")));
	pag1.LightingDarkElixir.SetCheck(_ttoi(bot.GetSingleSetting("LightingDarkElixir")));
	pag1.RemoveTree.SetCheck(_ttoi(bot.GetSingleSetting("RemoveTree")));
	pag1.RearmAll.SetCheck(_ttoi(bot.GetSingleSetting("RearmAll")));
	pag1.QuickSet.SetCurSel(_ttoi(bot.GetSingleSetting("QuickSet")));
	pag1.QuickSetShow.SetWindowText(bot.GetSingleSetting("QuickSetShow"));
	pag1.LoadInSet.SetWindowText(bot.GetSingleSetting("LoadInSet"));
	pag1.LoadOutSet.SetWindowText(bot.GetSingleSetting("LoadOutSet"));
	pag2.TrainArmyStyle.SetCurSel(_ttoi(bot.GetSingleSetting("TrainArmyStyle")));
	pag2.IsClearArmy.SetCurSel(_ttoi(bot.GetSingleSetting("IsClearArmy")));
	pag2.IsAddArmy.SetCurSel(_ttoi(bot.GetSingleSetting("IsAddArmy")));
	pag2.IsSpeedUp.SetCheck(_ttoi(bot.GetSingleSetting("IsSpeedUp")));
	pag2.SpeedUpBegin.SetWindowText(bot.GetSingleSetting("SpeedUpBegin"));
	pag2.SpeedUpEnd.SetWindowText(bot.GetSingleSetting("SpeedUpEnd"));
	pag2.Barbarin.SetWindowText(bot.GetSingleSetting("Barbarin"));
	pag2.Archer.SetWindowText(bot.GetSingleSetting("Archer"));
	pag2.Giant.SetWindowText(bot.GetSingleSetting("Giant"));
	pag2.Goblin.SetWindowText(bot.GetSingleSetting("Goblin"));
	pag2.WallBreaker.SetWindowText(bot.GetSingleSetting("WallBreaker"));
	pag2.Ballon.SetWindowText(bot.GetSingleSetting("Ballon"));
	pag2.Wizard.SetWindowText(bot.GetSingleSetting("Wizard"));
	pag2.Healer.SetWindowText(bot.GetSingleSetting("Healer"));
	pag2.Dragon.SetWindowText(bot.GetSingleSetting("Dragon"));
	pag2.Peka.SetWindowText(bot.GetSingleSetting("Peka"));
	pag2.BabyDragon.SetWindowText(bot.GetSingleSetting("BabyDragon"));
	pag2.Miner.SetWindowText(bot.GetSingleSetting("Miner"));
	pag2.Minion.SetWindowText(bot.GetSingleSetting("Minion"));
	pag2.HogRider.SetWindowText(bot.GetSingleSetting("HogRider"));
	pag2.Valkyrie.SetWindowText(bot.GetSingleSetting("Valkyrie"));
	pag2.Golem.SetWindowText(bot.GetSingleSetting("Golem"));
	pag2.Witch.SetWindowText(bot.GetSingleSetting("Witch"));
	pag2.LavaHound.SetWindowText(bot.GetSingleSetting("LavaHound"));
	pag2.BowLer.SetWindowText(bot.GetSingleSetting("BowLer"));
	pag2.LightingSpell.SetWindowText(bot.GetSingleSetting("LightingSpell"));
	pag2.HealingSpell.SetWindowText(bot.GetSingleSetting("HealingSpell"));
	pag2.RageSpell.SetWindowText(bot.GetSingleSetting("RageSpell"));
	pag2.JumpSpell.SetWindowText(bot.GetSingleSetting("JumpSpell"));
	pag2.FreezeSpell.SetWindowText(bot.GetSingleSetting("FreezeSpell"));
	pag2.CloneSpell.SetWindowText(bot.GetSingleSetting("CloneSpell"));
	pag2.PoisonSpell.SetWindowText(bot.GetSingleSetting("PoisonSpell"));
	pag2.EarthquakeSpell.SetWindowText(bot.GetSingleSetting("EarthquakeSpell"));
	pag2.HasteSpell.SetWindowText(bot.GetSingleSetting("HasteSpell"));
	pag2.SkeletonSpell.SetWindowText(bot.GetSingleSetting("SkeletonSpell"));
	pag3.MinTroopRet.SetWindowText(bot.GetSingleSetting("MinTroopRet"));
	pag3.SearchMinGold.SetWindowText(bot.GetSingleSetting("SearchMinGold"));
	pag3.SearchMinElixir.SetWindowText(bot.GetSingleSetting("SearchMinElixir"));
	pag3.SearchMinDarkElixir.SetWindowText(bot.GetSingleSetting("SearchMinDarkElixir"));
	pag3.SearchDealy.SetWindowText(bot.GetSingleSetting("SearchDealy"));
	pag3.SearchWait.SetWindowText(bot.GetSingleSetting("SearchWait"));
	pag3.SearchMaxCount.SetWindowText(bot.GetSingleSetting("SearchMaxCount"));
	pag3.MinTroophs.SetWindowText(bot.GetSingleSetting("MinTroophs"));
	pag3.MaxTroophs.SetWindowText(bot.GetSingleSetting("MaxTroophs"));
	pag3.IsWaitBarbarinKing.SetCheck(_ttoi(bot.GetSingleSetting("IsWaitBarbarinKing")));
	pag3.IsWaitArcherKing.SetCheck(_ttoi(bot.GetSingleSetting("IsWaitArcherKing")));
	pag3.IsWaitGrandKing.SetCheck(_ttoi(bot.GetSingleSetting("IsWaitGrandKing")));
	pag3.IsWaitClanCastleTroopsAndSpells.SetCheck(_ttoi(bot.GetSingleSetting("IsWaitClanCastleTroopsAndSpells")));
	pag3.IsWaitSpell.SetCheck(_ttoi(bot.GetSingleSetting("IsWaitSpell")));
	pag3.ArcherTower.SetCheck(_ttoi(bot.GetSingleSetting("ArcherTower")));
	pag3.Mortar.SetCheck(_ttoi(bot.GetSingleSetting("Mortar")));
	pag3.WizardTower.SetCheck(_ttoi(bot.GetSingleSetting("WizardTower")));
	pag3.AirDefense.SetCheck(_ttoi(bot.GetSingleSetting("AirDefense")));
	pag3.XBow.SetCheck(_ttoi(bot.GetSingleSetting("XBow")));
	pag3.Inferno.SetCheck(_ttoi(bot.GetSingleSetting("Inferno")));
	pag3.EagleArtillery.SetCheck(_ttoi(bot.GetSingleSetting("EagleArtillery")));
	pag3.SearchType.SetCurSel(_ttoi(bot.GetSingleSetting("SearchType")));
	pag3.SearchDeadbaseGoldCollector.SetCurSel(_ttoi(bot.GetSingleSetting("SearchDeadbaseGoldCollector")));
	pag3.SearchDeadbaseElixir.SetCurSel(_ttoi(bot.GetSingleSetting("SearchDeadbaseElixir")));
	pag3.ArcherTowerLevel.SetCurSel(_ttoi(bot.GetSingleSetting("ArcherTowerLevel")));
	pag3.MortarLevel.SetCurSel(_ttoi(bot.GetSingleSetting("MortarLevel")));
	pag3.WizardTowerLevel.SetCurSel(_ttoi(bot.GetSingleSetting("WizardTowerLevel")));
	pag3.AirDefenseLevel.SetCurSel(_ttoi(bot.GetSingleSetting("AirDefenseLevel")));
	pag3.XBowLevel.SetCurSel(_ttoi(bot.GetSingleSetting("XBowLevel")));
	pag3.InfernoLevel.SetCurSel(_ttoi(bot.GetSingleSetting("InfernoLevel")));
	pag3.EagleArtilleryLevel.SetCurSel(_ttoi(bot.GetSingleSetting("EagleArtilleryLevel")));
	pag4.AttackSpeed.SetCurSel(_ttoi(bot.GetSingleSetting("AttackSpeed")));//attackCount
	pag4.attackCount.SetCurSel(_ttoi(bot.GetSingleSetting("attackCount")));//AttackGird
	pag4.AttackGird.SetCurSel(_ttoi(bot.GetSingleSetting("AttackGird")));
	pag4.AttackDeadbaseStyle.SetCurSel(_ttoi(bot.GetSingleSetting("AttackDeadbaseStyle")));
	pag4.AttackActivebaseStyle.SetCurSel(_ttoi(bot.GetSingleSetting("AttackActivebaseStyle")));
	pag4.AttackMinDarkElixirLevel.SetCurSel(_ttoi(bot.GetSingleSetting("AttackMinDarkElixirLevel")));
	pag4.AttackIsExitWithoutResource.SetCheck(_ttoi(bot.GetSingleSetting("AttackIsExitWithoutResource")));
	pag4.AttackIsExitWhenLittleResource.SetCheck(_ttoi(bot.GetSingleSetting("AttackIsExitWhenLittleResource")));
	pag4.AttackMinWaitTime.SetWindowText(bot.GetSingleSetting("AttackMinWaitTime"));
	pag4.AttackExitGold.SetWindowText(bot.GetSingleSetting("AttackExitGold"));
	pag4.AttackExitElixir.SetWindowText(bot.GetSingleSetting("AttackExitElixir"));
	pag4.AttackExitDarkElixir.SetWindowText(bot.GetSingleSetting("AttackExitDarkElixir"));
	pag4.AttackLingtingMinDarkElixir.SetWindowText(bot.GetSingleSetting("AttackLingtingMinDarkElixir"));
	pag4.UseLightingCount.SetCurSel(_ttoi(bot.GetSingleSetting("UseLightingCount")));
	pag5.DonateType.SetCurSel(_ttoi(bot.GetSingleSetting("DonateType")));
	pag5.DonateMinSendGetRet.SetWindowText(bot.GetSingleSetting("DonateMinSendGetRet"));
	pag5.DonateCount.SetWindowText(bot.GetSingleSetting("DonateCount"));
	pag5.DonateDealy.SetWindowText(bot.GetSingleSetting("DonateDealy"));
	pag5.IsDonateSendGetRet.SetCheck(_ttoi(bot.GetSingleSetting("IsDonateSendGetRet")));
	pag5.IsDonateNotFull.SetCheck(_ttoi(bot.GetSingleSetting("IsDonateNotFull")));
	pag5.IsBarbarin.SetCheck(_ttoi(bot.GetSingleSetting("IsBarbarin")));
	pag5.IsArcher.SetCheck(_ttoi(bot.GetSingleSetting("IsArcher")));
	pag5.IsGiant.SetCheck(_ttoi(bot.GetSingleSetting("IsGiant")));
	pag5.IsGoblin.SetCheck(_ttoi(bot.GetSingleSetting("IsGoblin")));
	pag5.IsWallBreaker.SetCheck(_ttoi(bot.GetSingleSetting("IsWallBreaker")));
	pag5.IsBallon.SetCheck(_ttoi(bot.GetSingleSetting("IsBallon")));
	pag5.IsWizard.SetCheck(_ttoi(bot.GetSingleSetting("IsWizard")));
	pag5.IsHealer.SetCheck(_ttoi(bot.GetSingleSetting("IsHealer")));
	pag5.IsDragon.SetCheck(_ttoi(bot.GetSingleSetting("IsDragon")));
	pag5.IsPeka.SetCheck(_ttoi(bot.GetSingleSetting("IsPeka")));
	pag5.IsBabyDragon.SetCheck(_ttoi(bot.GetSingleSetting("IsBabyDragon")));
	pag5.IsMiner.SetCheck(_ttoi(bot.GetSingleSetting("IsMiner")));
	pag5.IsMinion.SetCheck(_ttoi(bot.GetSingleSetting("IsMinion")));
	pag5.IsHogRider.SetCheck(_ttoi(bot.GetSingleSetting("IsHogRider")));
	pag5.IsValkyrie.SetCheck(_ttoi(bot.GetSingleSetting("IsValkyrie")));
	pag5.IsGolem.SetCheck(_ttoi(bot.GetSingleSetting("IsGolem")));
	pag5.IsWitch.SetCheck(_ttoi(bot.GetSingleSetting("IsWitch")));
	pag5.IsLavaHound.SetCheck(_ttoi(bot.GetSingleSetting("IsLavaHound")));
	pag5.IsBower.SetCheck(_ttoi(bot.GetSingleSetting("IsBower")));
	pag5.IsPoison.SetCheck(_ttoi(bot.GetSingleSetting("IsPoison")));
	pag5.IsEarthquake.SetCheck(_ttoi(bot.GetSingleSetting("IsEarthquake")));
	pag5.IsHaste.SetCheck(_ttoi(bot.GetSingleSetting("IsHaste")));
	pag5.IsSkeleton.SetCheck(_ttoi(bot.GetSingleSetting("IsSkeleton")));
	pag6.UpgradeWallMinGold.SetWindowText(bot.GetSingleSetting("UpgradeWallMinGold"));
	pag6.UpgradeWallMinElixir.SetWindowText(bot.GetSingleSetting("UpgradeWallMinElixir"));
	pag6.UpgradeHeroMinDarkElixir.SetWindowText(bot.GetSingleSetting("UpgradeHeroMinDarkElixir"));
	pag6.UpgradeWallUseType.SetCurSel(_ttoi(bot.GetSingleSetting("UpgradeWallUseType")));
	pag6.UpgradeWallLevel.SetCurSel(_ttoi(bot.GetSingleSetting("UpgradeWallLevel")));
	pag6.UpgradeHeroType.SetCurSel(_ttoi(bot.GetSingleSetting("UpgradeHeroType")));
	pag7.SetShowErrorMsg.SetCheck(_ttoi(bot.GetSingleSetting("SetShowErrorMsg")));
	pag7.DebugLocateAD.SetCheck(_ttoi(bot.GetSingleSetting("DebugLocateAD")));
	pag7.IsSwitchMode.SetCheck(_ttoi(bot.GetSingleSetting("IsSwitchMode")));
	pag7.DeBugSearchShoot.SetCheck(_ttoi(bot.GetSingleSetting("DeBugSearchShoot")));
	pag7.DisableSetWindowSize.SetCheck(_ttoi(bot.GetSingleSetting("DisableSetWindowSize")));
	pag7.SwitchModeVersion_1.SetCurSel(_ttoi(bot.GetSingleSetting("SwitchModeVersion_1")));
	bindset.IsUserBind.SetCheck(_ttoi(bot.GetSingleSetting("IsUserBind")));
	bindset.IsBindWindowEx.SetCheck(_ttoi(bot.GetSingleSetting("IsBindWindowEx")));
	bindset.display.SetCurSel(_ttoi(bot.GetSingleSetting("display")));
	bindset.mouse.SetCurSel(_ttoi(bot.GetSingleSetting("mouse")));
	bindset.keypad.SetCurSel(_ttoi(bot.GetSingleSetting("keypad")));
	bindset.public_.SetCurSel(_ttoi(bot.GetSingleSetting("public_")));
	bindset.mode.SetCurSel(_ttoi(bot.GetSingleSetting("mode")));
	bindset.AdbPath.SetWindowText(bot.GetSingleSetting("AdbPath"));
	CString list_str = "0", usestr = "";
	list_str = script->coc.GetSingleSetting("DeadBaseAttackList");
	CString findStr = "";
	for (int i = 0; i < 15; i++)
	{
		findStr.Format("IsSwitchX%d", i);
		pag7.m_list1.SetCheck(i, _ttoi(bot.GetSingleSetting(findStr)));
	}
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			if (j == 1)
			{
				findStr.Format("VersionNameX%d", i);
			}
			if (j == 2)
			{
				findStr.Format("ConfigPathX%d", i);
			}
			if (j == 3)
			{
				findStr.Format("VersionNoX%d", i);
			}
			usestr = bot.GetSingleSetting(findStr);
			pag7.m_list1.SetItemText(i, j, usestr);

		}

	}
}
unsigned int Dealy(long DelayCount)
{
	DWORD j = GetTickCount();
	for (;;)
	{

		if (GetTickCount() >= j + DelayCount)
		{
			break;
		}
		if (exit_all == 1)
		{
			break;
		}
		Sleep(1);
	}
	return 0;
}
int ConnectBotServer()
{
	UINT port = 0;
	switch (pag1.ServerPort.GetCurSel())
	{
	case -1:
		port = 4444;
		break;
	case 0:
		port = 5555;
		break;
	case 1:
		port = 6666;
		break;
	case 2:
		port = 7777;
		break;
	case 3:
		port = 8888;
		break;
	}
	if (IsConnect)                             // 如果已经连接，则断开服务器
	{
		IsConnect = false;
		BotServer->Close();
		//delete BotServer;
		BotServer = NULL;
		return 1;
	}
	else                                                // 未连接，则连接服务器
	{
		BotServer = new ConnectServer();
		if (!BotServer->Create())         //创建套接字
		{
			AfxMessageBox(_T("创建套接字失败！"));
			return 0;
		}
	}
	if (!BotServer->Connect(IPADRESS, port))    //连接服务器
	{
		WriteLog("连接服务器失败!", true, RGB(0xff, 0x00, 0x00), false);

		return 0;
	}
	else
	{
		IsConnect = true;
		WriteLog("成功连接服务器", true, RGB(0x00, 0x00, 0xff), false);

	}
	return 0;
}
int SendMsgToServer(CString str)
{
	BotServer->Send(str, strlen(str), 0);
	return 0;
}
BOOL IsFirstUsePrograme()
{
	BOOL IsFirst = FALSE;
	CRegKey myKey;
	CString pbuf;
	const int maxLen = 255;
	ULONG nchars = 0;
	myKey.Create(HKEY_CURRENT_USER, "SOFTWARE\\CocBot\\Config\\0");
	myKey.QueryMultiStringValue("version", pbuf.GetBuffer(maxLen), &nchars);
	pbuf.ReleaseBuffer();
	CString str = cocBotVer;
	if (pbuf != str)
	{
		IsFirst = TRUE;
		myKey.SetMultiStringValue("version", cocBotVer);
		myKey.SetMultiStringValue("Talking", QQGROUPNAME);
	}

	myKey.Close();
	return IsFirst;
}
void InitlizeVariables(void)
{
	WriteLog("初始化...");
	script->coc.Initialize();
	script->coc.SetVersion("5.1423");
	script->SwitchNo = 0;
	Sleep(3500);
	script->IsThreadRun = true;
	for (int i = 0; i < 15; i++)
	{
		script->LootRecord[i].InitlizeDetail();
	}

	WriteLog("初始化完成");
}

//界面相关函数 ，保留
int Statistics()
{
	long LootGold = 0, LootElixir = 0, LootDarkElixir = 0, LootTroophs = 0;
	long RunTime = 0;
	int py = 0;
	py = script->SwitchNo * 5;
	script->GetResource();

	Dealy(300);
	LootGold = script->LootRecord[script->SwitchNo].GetLootGold();
	LootElixir = script->LootRecord[script->SwitchNo].GetLootElixir();
	LootDarkElixir = script->LootRecord[script->SwitchNo].GetLootDarkElixir();
	LootTroophs = script->LootRecord[script->SwitchNo].GetLootTroophs();
	RunTime = script->LootRecord[script->SwitchNo].GetRunTime();
	if (RunTime == 0)
	{
		RunTime = 1;
	}
	CString str[5] = {};
	str[0].Format("%ld", script->LootRecord[script->SwitchNo].StartGold);
	str[1].Format("%ld", script->LootRecord[script->SwitchNo].StartElixir);
	str[2].Format("%ld", script->LootRecord[script->SwitchNo].StartDarkElixir);
	str[3].Format("%ld", script->LootRecord[script->SwitchNo].StartTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 1, str[i]);
	}
	str[0].Format("%ld", script->LootRecord[script->SwitchNo].NowGold);
	str[1].Format("%ld", script->LootRecord[script->SwitchNo].NowElixir);
	str[2].Format("%ld", script->LootRecord[script->SwitchNo].NowDarkElixir);
	str[3].Format("%ld", script->LootRecord[script->SwitchNo].NowTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 2, str[i]);
	}
	str[0].Format("%ld", LootGold);
	str[1].Format("%ld", LootElixir);
	str[2].Format("%ld", LootDarkElixir);
	str[3].Format("%ld", LootTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 3, str[i]);
	}
	str[0].Format("%ld", LootGold * 60 / RunTime);
	str[1].Format("%ld", LootElixir * 60 / RunTime);
	str[2].Format("%ld", LootDarkElixir * 60 / RunTime);
	str[3].Format("%ld", LootTroophs * 60 / RunTime);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 4, str[i]);
	}

	str[0].Format("%ld", (LootGold * 24 / RunTime) * 60);
	str[1].Format("%ld", (LootElixir * 24 / RunTime) * 60);
	str[2].Format("%ld", (LootDarkElixir * 24 / RunTime) * 60);
	str[3].Format("%ld", (LootTroophs * 24 / RunTime) * 60);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 5, str[i]);
	}
	CString tstr;
	tstr = "";
	tstr.Format("运行时间：%ld day %ld h %ld minutes.", RunTime / 1440, (RunTime % 1440) / 60, RunTime % 60);
	//pag8.RunTime.SetWindowTextA(tstr);
	tstr.Format("攻击次数：%ld", script->coc.GetSomeCount(1));
	pag8.AttackCount.SetWindowTextA(tstr);
	tstr.Format("搜索次数：%ld", script->coc.GetSomeCount(0));
	pag8.SearchCount.SetWindowTextA(tstr);
	tstr.Format("当前账号：%d", script->SwitchNo);
	pag8.NowLog.SetWindowText(tstr);
	return 0;
}
BOOL HideKey()
{
	return TRUE;
}
//************* Important Thread Function **************//
UINT  Main_Game(LPVOID lpParamter)
{
	if (script->IsThreadRun == false)
	{
		script->dm = NULL;
		return 0;
	}
	ThreadCount++;
	CString count_str;
	count_str.Format("重启次数： %d", ThreadCount);
	WriteLog(count_str);
	if (script->coc.GetVersion() != script->dm.Ver())
	{

		script->IsThreadRun = false;
		exit_all = 1;
		AfxMessageBox(_T("启动失败，请检查插件是否注册！"), MB_OK);
		return 0;
	}
	script->dm.SetShowErrorMsg(_ttoi(script->coc.GetSingleSetting("SetShowErrorMsg")));
	CString windowtext;
	Dealy(500);
	int connect = 0;
	connect = script->ConnectBsOrOthers();
	count_str.Format("connect=%d", connect);
	WriteLog(count_str, true, RGB(0xff, 0x00, 0xff), true);
	int Ret = 0;
	if (connect == -1)
	{
		WriteLog("链接模拟器失败!", true, RGB(0xff, 0x00, 0xff), true);
		script->dm = NULL;
		script->IsThreadRun = false;
		exit_all = 1;
		return 0;
	}
	if (connect == -2)
	{
		WriteLog("请检查模拟器是否打开!", true, RGB(0xff, 0x00, 0xff), true);
		script->dm = NULL;
		script->IsThreadRun = false;
		exit_all = 1;
		return 0;
	}
	if (_ttoi(script->coc.GetSingleSetting("DisableSetWindowSize")) != 1)
	{
		if (script->SetClientWindowSize() != 1)
		{
			WriteLog("SetClientWindowSize FALSE", true, RGB(0xff, 0x00, 0x00), true);
			//IsRestart = true;
			//script->scriptStateCode = ShouldRestart;
			script->dm = NULL;
			return 0;
		}

	}

	Dealy(200);

	//hThread_ID2 = AfxBeginThread(Identify_OffLine,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
	if (script->IsThreadRun == false)
	{
		script->dm = NULL;
		return 0;
	}
	script->AddDict();
	script->StartCoc(script->coc.GetCocVer());
	script->Dealy(2000);
	script->checkMainScreen();
	if (script->IsThreadRun == false)
	{
		script->dm = NULL;
		return 0;
	}
	script->ZoomOut();

	script->Dealy(1000);
	if (script->IsThreadRun == false)
	{
		script->dm = NULL;
		return 0;
	}
	do
	{
		script->ZoomOut();
		script->Dealy(1000);
		for (int r = 0; r <= 10; r++)
		{
			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			Statistics();
			if (_ttoi(script->coc.GetSingleSetting("ControlTroophs")) == 1 && script->LootRecord[script->SwitchNo].NowTroophs > _ttoi(script->coc.GetSingleSetting("MaxTroophs")))
			{

				script->DownTroophs();
				if (script->IsThreadRun == false)
				{
					return 0;
				}
				script->checkMainScreen();
			}
			else
			{
				break;
			}

		}
		if (script->IsThreadRun == false || script->scriptStateCode <= 0)
		{
			script->dm = NULL;
			return 0;
		}
		if (script->CheckArmyNum(&script->train_time) && _ttoi(script->coc.GetSingleSetting("Attack")) == 1)
		{
			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}

			if (_ttoi(script->coc.GetSingleSetting("Attack")) == 1)
			{
				script->MakeArmy();
				Dealy(2000);
				if (script->IsThreadRun == false)
				{
					script->dm = NULL;
					return 0;
				}
				Ret = script->SearchFish();
				if (Ret == 1)
				{
					int AttackType = _ttoi(script->coc.GetSingleSetting("AttackDeadbaseStyle"));
					switch (AttackType)
					{
					case 0:
						WriteLog(_T("智能攻击"), 1, RGB(0xff, 0x00, 0x00), true);
						script->Main_Attack(); //下兵
						script->coc.AddSomeCount(1, 1);
						break;
					case 1:
						WriteLog(_T("均分式攻击"), 1, RGB(0xff, 0x00, 0x00), true);
						script->EqualAttack();
						script->coc.AddSomeCount(1, 1);
						break;
					default:
						WriteLog(_T("智能攻击"), 1, RGB(0xff, 0x00, 0x00), true);
						script->Main_Attack(); //下兵
						script->coc.AddSomeCount(1, 1);
					}
				}
			}
			else
			{
				WriteLog("not allowed attack", true, RGB(0xff, 0x00, 0x00), true);
			}

			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			script->checkMainScreen();

			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
		}
		else
		{

			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			if (script->train_time == 0 && script->LootRecord[script->SwitchNo].ArmyRet <= 95)
			{
				WriteLog("add / train necessary army");
				script->MakeArmy();
			}
			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			Statistics();

			script->CollectResource();
			if (script->train_time > 2)
			{
				if (_ttoi(script->coc.GetSingleSetting("OffLine")) == 1 && pag7.IsSwitchMode.GetCheck() != 1)
				{
					script->scriptStateCode = ShouldWaitForArmy;
					return 0;
				}
			}
			if (script->train_time >= 5 && pag7.IsSwitchMode.GetCheck() == 1)
			{
				script->scriptStateCode = ShouldSwitch;
				return 0;
			}
			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			if (script->scriptStateCode > 0)
			{
				script->DealyRandTime(15, 60);
			}

			script->Dealy(300);
			if (_ttoi(script->coc.GetSingleSetting("DonateArmy")) == 1)
			{
				script->Donate();
			}
			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}
			script->checkMainScreen();
			Statistics();
			//UpDate_Wall();

			if (script->IsThreadRun == false)
			{
				script->dm = NULL;
				return 0;
			}

		}
	} while (script->IsThreadRun == true || script->scriptStateCode > 0);
	return 0;
}
UINT  Main_Thread(LPVOID lpParamter)
{
	WriteLog(_T("启动 coc bot 普通模式"));
	script->scriptStateCode = NormalRun;
	script->IsThreadRun = true;
	int coc_ver_choose = 0;
	CString coc_ver, str_i;
	coc_ver_choose = _ttoi(script->coc.GetSingleSetting("GameVersion"));
	str_i.Format("%d", coc_ver_choose);
	CString path = script->coc.GetExePath();
	path += "Config.ini";
	GetPrivateProfileString(TEXT("version"), str_i, "", coc_ver.GetBuffer(250), 250, path);
	coc_ver.ReleaseBuffer();
	script->coc.SetCocVer(coc_ver);
	hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	while (exit_all != 1)
	{
		//************掉线检测，是则重启**********//
		if (script->GetScriptState() == ShouldRestart)
		{
			script->IsThreadRun = false;
			Dealy(3000);
			StopThread();
			script->StopCoc(script->coc.GetCocVer());
			Dealy(5000);
			script->CreateDm();
			script->IsThreadRun = true;
			script->scriptStateCode = NormalRun;
			hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

		}
		//*************** Check Should OffLine ***********//
		if (script->scriptStateCode == ShouldWaitForArmy)
		{

			script->StopCoc(script->coc.GetCocVer());
			script->IsThreadRun = false;
			StopThread();
			WriteLog("Wait for army");
			CString str;
			str.Format("wait time=%d minutes", script->train_time - 1);
			WriteLog(str);
			for (int i = 1; i <= script->train_time - 1; i++)
			{
				if (exit_all == 1)
				{
					script->scriptStateCode = NormalNoRun;
					break;
				}
				for (int j = 0; j < 60; j++)
				{
					str.Format("剩余时间 = %d分 %d秒", (script->train_time - 1 - i), 59 - j);
					WriteLog(str, false, RGB(0, 0, 0), false);
					Dealy(999);
				}

			}
			Dealy(5000);
			script->train_time = 0;
			script->scriptStateCode = NormalRun;
			script->CreateDm();
			script->IsThreadRun = true;
			hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

		}
		if (0)
		{
			script->IsThreadRun = false;
			Dealy(5000);
			WinExec("C:\\Program Files (x86)\\BlueStacks\\HD-StartLauncher.exe", SW_NORMAL);
			Dealy(10000);
			if (exit_all != 1)
			{
				script->CreateDm();
				//IsRestart = false;
				script->IsThreadRun = true;
				hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

			}

		}
		if (exit_all == 1)
		{
			script->IsThreadRun = false;
			script->scriptStateCode = NormalNoRun;
			script->IsThreadRun = false;
			return 0;
		}
		Dealy(1000);

	}
	return 0;
}
UINT SwitchMode_Thread(LPVOID lpParamter)
{
	exit_all = 0;
	CString ver[16] = {};
	int ver_count = 0, n = 0, sn = 0, change_d[10] = { 0 };
	ver[0] = "com.supercell.clashofclans/com.supercell.clashofclans.GameApp";
	ver[1] = "com.supercell.clashofclans.qihoo/com.supercell.clashofclans.GameAppKunlun";
	ver[2] = "com.supercell.clashofclans.kunlun/com.supercell.clashofclans.GameAppKunlun";
	ver[3] = "com.supercell.clashofclans.wdj/com.supercell.clashofclans.GameAppKunlun";
	ver[4] = "com.supercell.clashofclans.baidu/com.supercell.clashofclans.GameAppKunlun";
	ver[5] = "com.supercell.clashofclans.uc/com.supercell.clashofclans.uc.GameApp";
	ver[6] = "com.supercell.clashofclans.huawei/com.supercell.clashofclans.GameAppKunlun";
	ver[7] = "com.supercell.clashofclans.nearme.gamecenter/com.supercell.clashofclans.GameAppKunlun";
	ver[8] = "com.supercell.clashofclans.vivo/com.supercell.clashofclans.GameAppKunlun";
	ver[9] = "com.supercell.clashofclans.anzhi/com.supercell.clashofclans.GameAppKunlun";
	ver[10] = "com.supercell.clashofclans.ewan.kaopu/com.supercell.clashofclans.GameAppKunlun";
	ver[11] = "com.supercell.clashofclans.lenovo/com.supercell.clashofclans.GameAppKunlun";
	ver[12] = "com.supercell.clashofclans.wdj/com.flamingo.sdk.view.WDJSplashActivity";
	ver[13] = "com.supercell.clashofclans.mi/com.supercell.clashofclans.mi.GameAppXiaomi";
	ver[14] = "com.supercell.clashofclans.ewan.hm/cn.ewan.supersdk.activity.SplashActivity";
	ver[15] = "com.supercell.clashofclans.ewan.leshi/cn.ewan.supersdk.activity.SplashActivity";
	CString coc_ver, str_i;
	int coc_ver_choose = 0;
	CString switchmode_config[15] = {};
	CString ResultStr;
	int SwitchMax = 0;
	for (int i = 0; i < 15; i++)
	{
		if (pag7.m_list1.GetCheck(i) == TRUE)
		{
			++ver_count;
		}

	}
	CString ver_check[16] = { 0 };
	for (int i = 0; i <= 5; i++) { ver_check[i] = ""; } //set null
	for (int i = 0; i < 15; i++)
	{
		if (pag7.m_list1.GetCheck(i) == 1)
		{
			str_i = pag7.m_list1.GetItemText(i, 3);//版本编号
			ver_check[n] = ver[_ttoi(str_i)];
			switchmode_config[n] = pag7.m_list1.GetItemText(i, 2);//配置路径+文件名
			++n;
		}
	}
	//**************** Initilaze Mode End ************************//
	coc_ver = ver_check[0];
	script->coc.SetCocVer(coc_ver);
	ResultStr = script->coc.ReadFileWithoutPath(switchmode_config[0]);
	if (ResultStr.GetLength() < 255)
	{
		WriteLog("错误的配置文件", true, RGB(0xff, 0x00, 0x00), false);
		exit_all = 1;
		script->IsThreadRun = false;
		script->scriptStateCode = NormalNoRun;
		AfxMessageBox("错误的配置文件", MB_OK);
		return 0;

	}
	script->coc.SetAllSetting(ResultStr);//设置全局配置 （切换的设置不在此范围）
	//**************** Initilaze First Switch *****************//
	//***********switch mode ********************//
	WriteLog(_T("启动 coc bot :切换模式"));
	script->scriptStateCode = SwitchRun;
	hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	script->SwitchNo = 0;
	sn += 1;
	while (exit_all != 1)
	{
		//************掉线检测，是则重启**********//
		if (script->scriptStateCode == ShouldRestart)
		{
			script->IsThreadRun = false;
			script->StopCoc(script->coc.GetCocVer());
			Dealy(3000);
			StopThread();
			Dealy(5000);
			script->CreateDm();
			script->IsThreadRun = true;
			script->scriptStateCode = SwitchRun;
			hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

		}
		//**************** SwitchMode *****************//
		if (script->scriptStateCode == ShouldSwitch)
		{
			script->IsThreadRun = false;
			script->StopCoc(script->coc.GetCocVer());
			Dealy(5000);
			StopThread();
			WriteLog("等待切换", true, RGB(0x00, 0xff, 0xff), false);
			Dealy(35000);
			coc_ver = ver_check[sn];
			script->coc.SetCocVer(coc_ver);
			ResultStr = script->coc.ReadFileWithoutPath(switchmode_config[sn]);
			if (ResultStr.GetLength() < 255)
			{
				WriteLog("错误的配置文件", true, RGB(0xff, 0x00, 0x00), false);
				exit_all = 1;
				script->IsThreadRun = false;
				script->scriptStateCode = NormalNoRun;
				AfxMessageBox("错误的配置文件", MB_OK);
				return 0;

			}
			script->coc.SetAllSetting(ResultStr);
			sn = sn + 1;
			script->SwitchNo += 1;
			if (sn > ver_count - 1)
			{
				sn = 0;
			}
			if (script->SwitchNo > ver_count - 1)
			{
				script->SwitchNo = 0;
			}
			coc_ver = ver_check[sn];
			WriteLog("[h]" + coc_ver);

			if (coc_ver == "")
			{
				sn = 0;
				coc_ver = ver_check[sn];
				script->coc.SetCocVer(coc_ver);
				ResultStr = script->coc.ReadFileWithoutPath(switchmode_config[sn]);
				script->coc.SetAllSetting(ResultStr);
			}
			else
			{
				if (exit_all == 1)
				{
					return 0;
				}
				script->IsThreadRun = true;
				script->scriptStateCode = SwitchRun;
				script->CreateDm();
				hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

			}
		}
		if (0)
		{
			script->IsThreadRun = false;
			StopThread();
			Dealy(5000);
			WinExec("C:\\Program Files (x86)\\BlueStacks\\HD-StartLauncher.exe", SW_NORMAL);
			Dealy(10000);
			if (exit_all != 1)
			{
				script->IsThreadRun = true;
				script->CreateDm();
				script->scriptStateCode = SwitchRun;
				hThread_ID2 = AfxBeginThread(Main_Game, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

			}

		}
		if (exit_all == 1)
		{
			script->scriptStateCode = NormalNoRun;
			script->IsThreadRun = false;
			StopThread();
			return 0x4;
		}
		Dealy(200);

	}
	return 0;
}
//******************************************************//
// 用于应用程序“关于”
//菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CnewcocbotDlg 对话框




CcocBotDlg::CcocBotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcocBotDlg::IDD, pParent)
	, IsInit(false)
	, m_OldState(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	bot_version = cocBotVer;
	// 将数组m_nzValues的元素都初始化为0   
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);
	//初始化richedit
	BotServer = NULL;
	script->pRichEditCtrl = &(pag9.m_RichEdit1);


}
CcocBotDlg::~CcocBotDlg()
{
	if (BotServer != NULL)
	{
		delete BotServer;
	}
	delete script;
}
void CcocBotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, main_tab);
	DDX_Control(pDX, IDC_State, State);
	DDX_Control(pDX, IDC_BUTTON1, m_Start);
	DDX_Control(pDX, IDC_BUTTON2, m_Stop);
	DDX_Control(pDX, IDC_SHOW, m_Show);
}

BEGIN_MESSAGE_MAP(CcocBotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CcocBotDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CcocBotDlg::OnStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CcocBotDlg::OnEndBot)
	ON_BN_CLICKED(IDC_BUTTON3, &CcocBotDlg::OnHideWindow)
	ON_BN_CLICKED(IDC_BUTTON4, &CcocBotDlg::OnShowWindow)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CcocBotDlg::OnScreenCapture)
	ON_BN_CLICKED(IDC_SETSIZE, &CcocBotDlg::OnSetSize)
END_MESSAGE_MAP()


// CnewcocbotDlg 消息处理程序

BOOL CcocBotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString title;
	GetWindowText(title);
	title += "  当前版本号<<";
	title += cocBotVer;
	title += ">>";
	title += " qq群：584618461";
	SetWindowText(title);
	main_tab.InsertItem(0, TEXT("快速设置"));
	main_tab.InsertItem(1, TEXT("训练设置"));
	main_tab.InsertItem(2, TEXT("搜索设置"));
	main_tab.InsertItem(3, TEXT("攻击设置"));
	main_tab.InsertItem(4, TEXT("捐兵/请求"));
	main_tab.InsertItem(5, TEXT("升级设置"));
	main_tab.InsertItem(6, TEXT("高级设置"));
	main_tab.InsertItem(7, TEXT("统计"));
	main_tab.InsertItem(8, TEXT("实时日志"));
	main_tab.InsertItem(9, TEXT("关于"));
	pag1.Create(IDD_DIALOG1, GetDlgItem(IDC_TAB1));
	pag2.Create(IDD_DIALOG2, GetDlgItem(IDC_TAB1));
	pag3.Create(IDD_DIALOG3, GetDlgItem(IDC_TAB1));
	pag4.Create(IDD_DIALOG4, GetDlgItem(IDC_TAB1));
	pag5.Create(IDD_DIALOG5, GetDlgItem(IDC_TAB1));
	pag6.Create(IDD_DIALOG6, GetDlgItem(IDC_TAB1));
	pag7.Create(IDD_DIALOG7, GetDlgItem(IDC_TAB1));
	pag8.Create(IDD_DIALOG8, GetDlgItem(IDC_TAB1));
	pag9.Create(IDD_DIALOG9, GetDlgItem(IDC_TAB1));
	pag10.Create(IDD_DIALOG10, GetDlgItem(IDC_TAB1));
	bindset.Create(IDD_DIALOG11, GetDlgItem(IDD_NEWCOCBOT_DIALOG));
	//获得IDC_TABTEST客户区大小
	CRect rc;
	main_tab.GetClientRect(&rc);
	//调整子对话框在父窗口中的位置
	rc.top += 30;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;

	//设置子对话框尺寸并移动到指定位置
	pag1.MoveWindow(&rc);
	pag2.MoveWindow(&rc);
	pag3.MoveWindow(&rc);
	pag4.MoveWindow(&rc);
	pag5.MoveWindow(&rc);
	pag6.MoveWindow(&rc);
	pag7.MoveWindow(&rc);
	pag8.MoveWindow(&rc);
	pag9.MoveWindow(&rc);
	pag10.MoveWindow(&rc);
	pag1.ShowWindow(true);
	pag2.ShowWindow(FALSE);
	pag3.ShowWindow(FALSE);
	pag4.ShowWindow(FALSE);
	pag5.ShowWindow(FALSE);
	pag6.ShowWindow(FALSE);
	pag7.ShowWindow(FALSE);
	pag8.ShowWindow(FALSE);
	pag9.ShowWindow(FALSE);
	pag10.ShowWindow(FALSE);
	bindset.ShowWindow(FALSE);
	//********************* attack ************************//
	InitlizeList();
	//***************** update window set ****************//
	CbotFunction bot;
	CString basepath = bot.GetExePath();
	bot.SetPath(basepath);
	CString result_str = bot.ReadFile("BotSet.cbt");
	UpdateWindowSet(result_str);
	CString str_show, path;
	CbotFunction record;
	path = record.GetExePath();
	record.SetPath(path);
	str_show = record.ReadFile("Instruction.txt");
	pag10.Instruction.SetWindowTextA(str_show);
	int count = 0;
	ConnectBotServer();
	if (IsConnect == true)
	{
		WriteLog("当前版本：" + bot_version, 1, RGB(0x00, 0x00, 0xff), false);
		CString send_str;
		SendMsgToServer(send_str);
	}
	WriteLog("交流群：584618461", true, RGB(0x00, 0x00, 0xff), false);
	SetBackgroundColor(RGB(0Xc0, 0xc0, 0xc0));
	InitilzieColor();
	m_Button1 = AfxGetApp()->LoadIcon(IDI_ICON4);
	m_Button2 = AfxGetApp()->LoadIcon(IDI_ICON5);
	m_Start.SetIcon(m_Button1);
	m_Stop.SetIcon(m_Button2);
	// 启动定时器，ID为1，定时时间为200ms   
	if (IsFirstUsePrograme()==TRUE)
	{
		WriteLog("欢迎首次使用cocBot,使用前务必阅读相关说明文档！", true, REDCOLOR, false);

	}
	if (!RegDm())
	{
		WriteLog("插件功能异常!", 1, RGB(0xff, 0x00, 0x00), false);

	}
	else
	{
		if (script->dm.Ver() != "5.1423")
		{
			str_show = " 错误版本 =";
			str_show += script->dm.Ver();
			WriteLog(str_show, 0, RGB(0xff, 0x00, 0x00), false);
			str_show = "插件路径 = ";
			str_show += script->dm.GetBasePath();
			WriteLog("两个可能:", true, RGB(0xff, 0x00, 0x00), false);
			WriteLog("1.插件被释放到了Plugin目录", true, RGB(0xff, 0x00, 0x00), false);
			WriteLog("2.插件被释放到了系统目录", true, RGB(0xff, 0x00, 0x00), false);
			WriteLog(str_show, 0, RGB(0xff, 0x00, 0x00), false);
			WriteLog("解决办法是删除" + str_show + "目录下的script->dm.dll插件", true, RGB(0xff, 0x00, 0x00), false);
		}
		else
		{
			str_show = "插件版本 ：";
			str_show += script->dm.Ver();
			str_show += " 当前插件路径：";
			str_show += script->dm.GetBasePath();
			WriteLog(str_show, 1, RGB(0x00, 0x00, 0xff), false);
		}
		script->dm = NULL;
	}
	//IsFIRST RUN
	if (pag1.BluestacksOrOthers.GetCurSel() == 0)
	{
		pag1.BsOrOtherWindowText.SetWindowTextA("BlueStacks App Player");
		pag1.BsOrOtherWindowText.EnableWindow(FALSE);
	}
	pag9.m_progress.SetRange(0, 100);
	SetTimer(1, 1000, NULL);
	SetTimer(2, 500, NULL);
	IsInit = true;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcocBotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcocBotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CRect rect;
		CDC* pdc=m_Show.GetDC();
		m_Show.GetClientRect(&rect);
		pdc->FillSolidRect(rect,RGB(0X00,0X00,0XFF));
		pdc->FillPath();
		pdc->TextOutA(rect.Width() / 2, rect.Height() / 2, "测试中...");
		
		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcocBotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CcocBotDlg::InitSocket()
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		::MessageBox(NULL, "套接字创建失败！", "char", 0);
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;//指定地址族，对于IP地址，此变量一直是AF_INET
	addrSock.sin_port = htons(6000);	//指定端口号，本例使用6000
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//指定IP地址，本例让其接收任意发送到本地的任意IP地址的数据

	int retval;
	//绑定套接字
	retval = bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == retval)
	{
		closesocket(m_socket);
		::MessageBox(NULL, "绑定失败！", "char", 0);
		return FALSE;
	}
	return FALSE;
}

DWORD WINAPI CcocBotDlg::RecvProc(LPVOID lpParameter)
{
	//获取主线程传递的套接字和窗口句柄
	SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	delete lpParameter;

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);

	char recvBuf[200];
	char tempBuf[200];
	int retval;
	while (TRUE)
	{
		//接收数据
		retval = recvfrom(sock, recvBuf, 200, 0, (SOCKADDR*)&addrFrom, &len);
		if (SOCKET_ERROR == retval)
		{
			break;
		}
		sprintf(tempBuf, "%s说：%s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		WriteLog(tempBuf);
		//::PostMessage(hwnd,WM_RECVDATA, 0,(LPARAM)tempBuf);
	}

	return 0;
}
void CcocBotDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch (main_tab.GetCurSel())
	{
	case 0:

		pag1.ShowWindow(true);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;

	case 1:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(true);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 2:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(true);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 3:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(true);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 4:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(true);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 5:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(true);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 6:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(true);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 7:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(true);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(FALSE);
		break;
	case 8:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(true);
		pag10.ShowWindow(FALSE);
		break;
	case 9:
		pag1.ShowWindow(FALSE);
		pag2.ShowWindow(FALSE);
		pag3.ShowWindow(FALSE);
		pag4.ShowWindow(FALSE);
		pag5.ShowWindow(FALSE);
		pag6.ShowWindow(FALSE);
		pag7.ShowWindow(FALSE);
		pag8.ShowWindow(FALSE);
		pag9.ShowWindow(FALSE);
		pag10.ShowWindow(true);
		break;
	}

	*pResult = 0;
}
void CcocBotDlg::OnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Start.EnableWindow(FALSE);
	m_Stop.EnableWindow(TRUE);
	CString path;
	path = script->coc.GetExePath();
	path += "Import\\";
	script->coc.SetPath(path);
	CString result;
	result = script->coc.ReadFile("AttackSoliderInfo.txt");
	if (result.GetLength() < 10)
	{
		return;
	}
	script->coc.ConfigInfo = result;
	script->coc.SetVersion("5.1423");
	script->coc.SetPath(GetExePath());
	CString save_str = GetAllSetting();
	script->coc.SetAllSetting(save_str);
	script->CreateDm();
	script->IsThreadRun = true;
	exit_all = 0;
	InitlizeVariables();
	if (pag7.IsSwitchMode.GetCheck() != 1)
	{

		hThread_ID1 = AfxBeginThread(Main_Thread, 0, 0, NULL);
	}
	else
	{
		hThread_ID1 = AfxBeginThread(SwitchMode_Thread, 0, 0, NULL);
	}


}

void CcocBotDlg::OnEndBot()
{
	// TODO: 在此添加控件通知处理程序代码
	script->IsThreadRun = false;
	script->scriptStateCode = 0;
	exit_all = 1;
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	Sleep(5015);
	script->dm.UnBindWindow();
	script->dm = NULL;

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);



}
void CcocBotDlg::OnHideWindow()
{
	// TODO: 在此添加控件通知处理程序代码
	CLSID clsid;
	CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	Cdmsoft dmx;
	dmx.CreateDispatch(clsid);
	CString winText, str;
	long window_hwnd = dmx.FindWindow("", "BlueStacks App Player");
	if (window_hwnd > 0)
	{
		dmx.MoveWindow(window_hwnd, 0, 0);
		dmx.SetWindowTransparent(window_hwnd, 0);
	}
	pag1.BsOrOtherWindowText.GetWindowTextA(winText);
	if (winText.GetLength() > 0)
	{
		window_hwnd = dmx.FindWindow("Qt5QWindowIcon", winText);
		str.Format("window_hwnd =%ld", window_hwnd);
		if (window_hwnd > 0)
		{
			dmx.MoveWindow(window_hwnd, 0, 0);
			dmx.SetWindowTransparent(window_hwnd, 0);
		}

	}

	//func_adb("input text 233");
	//CString str= coc.ReadFileWithoutPath("F:\\Programe\\Nox\\bin\\BignoxVMS\\nox\\nox.vbox-prev");
	//CString result=coc.GetConfig(str, "Forwarding name=\"port2\" proto=\"1\" hostip", "<", ">");
	//AfxMessageBox(result, MB_OK);
	dmx = NULL;
}
void CcocBotDlg::OnShowWindow()
{
	// TODO: 在此添加控件通知处理程序代码

	CLSID clsid;
	CString str;
	CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	Cdmsoft dmx;
	dmx.CreateDispatch(clsid);
	long window_hwnd = dmx.FindWindow("", "BlueStacks App Player");
	if (window_hwnd > 0)
	{
		dmx.MoveWindow(window_hwnd, 0, 0);
		dmx.SetWindowTransparent(window_hwnd, 255);
	}
	CString winText;
	pag1.BsOrOtherWindowText.GetWindowTextA(winText);
	if (winText.GetLength() > 0)
	{
		window_hwnd = dmx.FindWindow("Qt5QWindowIcon", winText);
		str.Format("window_hwnd =%ld", window_hwnd);
		if (window_hwnd > 0)
		{
			dmx.SetWindowTransparent(window_hwnd, 255);
		}

	}

	gameShow();
	dmx = NULL;

}
void CcocBotDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CbotFunction bot;
	bot.SetPath(GetExePath());
	CString save_str = GetAllSetting();
	bot.WriteFile(_T("BotSet.cbt"), save_str);
	if (exit_all != 1 && script->dm.Ver().GetLength() > 0)
	{
		exit_all = 1;
		Sleep(4015);
		script->dm.UnBindWindow();
		script->dm = NULL;

	}

	KillTimer(1);
	KillTimer(2);
	CDialogEx::OnClose();

}
void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
void CcocBotDlg::OnLoadOutConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	CbotFunction* bot = new CbotFunction;
	path = GetExePath();
	bot->SetPath(path);
	CString save_str = GetAllSetting();
	CString filename;
	pag1.LoadOutSet.GetWindowTextA(filename);
	if (filename.GetLength() < 1)
	{
		filename = "导出";
		filename += bot->GetNowTime(3);
	}

	filename += ".cbt";
	bot->WriteFile(filename, save_str);
	delete bot;
	path += filename;
	MessageBox("导出成功，路径是：" + path, "提示", MB_OK);

}
void CcocBotDlg::OnLoadInConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_config, file_path;
	CbotFunction* bot = new CbotFunction;
	pag1.LoadInSet.GetWindowTextA(file_path);
	if (file_path.GetLength() > 3)
	{
		if (file_path.Right(4) != ".cbt")
		{
			MessageBox("错误的文件" + file_path, "提示", MB_OK);
		}
		else
		{
			str_config = bot->ReadFileWithoutPath(file_path);
			UpdateWindowSet(str_config);
			AfxMessageBox("导入配置成功！");
		}
	}
	delete bot;

	Sleep(1000);
}
// OnInitlizeList
void CcocBotDlg::InitlizeList(void)
{
	CString str;
	//****************** donate keyword list **************//
	pag5.ListKeyWord.SetExtendedStyle(LVS_ICON | LVS_REPORT | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	pag5.ListKeyWord.InsertColumn(0, "选择", LVCFMT_CENTER, 50);
	pag5.ListKeyWord.InsertColumn(1, "关键词", LVCFMT_CENTER, 150);
	pag5.ListKeyWord.InsertColumn(2, "捐赠", LVCFMT_CENTER, 50);

	for (int i = 0; i <= 30; i++)
	{
		str.Format("%d", i);
		pag5.ListKeyWord.InsertItem(i, str);
	}
	//************** loot **************//
	pag8.m_ListCtrl1.SetExtendedStyle(LVS_ICON | LVS_REPORT);
	pag8.m_ListCtrl1.InsertColumn(0, _T(""), LVCFMT_CENTER, 60);
	pag8.m_ListCtrl1.InsertColumn(1, _T("开始资源"), LVCFMT_CENTER, 100);
	pag8.m_ListCtrl1.InsertColumn(2, _T("当前资源"), LVCFMT_CENTER, 100);
	pag8.m_ListCtrl1.InsertColumn(3, _T("掠夺资源"), LVCFMT_CENTER, 100);
	pag8.m_ListCtrl1.InsertColumn(4, _T("时均效率"), LVCFMT_CENTER, 100);
	pag8.m_ListCtrl1.InsertColumn(5, _T("天均效率"), LVCFMT_CENTER, 100);
	pag8.m_ListCtrl1.SetTextBkColor(RGB(0XC0, 0XC0, 0XC0));
	for (int i = 0; i < 15; i++)
	{
		str.Format("账号:%d", i);
		i *= 5;
		pag8.m_ListCtrl1.InsertItem(0 + i, str);
		pag8.m_ListCtrl1.InsertItem(1 + i, "金币");
		pag8.m_ListCtrl1.InsertItem(2 + i, "圣水");
		pag8.m_ListCtrl1.InsertItem(3 + i, "黑油");
		pag8.m_ListCtrl1.InsertItem(4 + i, "奖杯");
		i = i / 5;
	}


	for (int i = 0; i < 121; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			if (i % 5 == 0)
			{
				pag8.m_ListCtrl1.SetItemText(i, j, "--------------------");

			}
			else
			{

				pag8.m_ListCtrl1.SetItemText(i, j, "0");
			}

		}
	}
	//MutliLog
	pag7.m_list1.SetExtendedStyle(LVS_ICON | LVS_REPORT | LVS_EX_CHECKBOXES);
	pag7.m_list1.InsertColumn(0, _T("选定"), LVCFMT_CENTER, 50);
	pag7.m_list1.InsertColumn(1, _T("版本"), LVCFMT_LEFT, 100);
	pag7.m_list1.InsertColumn(2, _T("配置路径"), LVCFMT_CENTER, 200);
	pag7.m_list1.InsertColumn(3, _T("序号"), LVCFMT_CENTER, 50);
	for (int i = 0; i < 15; i++)
	{
		str.Format("%d", i);
		pag7.m_list1.InsertItem(i, str);
	}
	pag7.Clear.AddString("重置所有");
	for (int i = 0; i < 15; i++)
	{
		str.Format("第 %d行", i);
		pag7.Clear.AddString(str);
	}
}
// Variables


void CcocBotDlg::InitilzieColor(void)
{


	pag9.m_RichEdit1.SetBackgroundColor(false, RGB(0Xff, 0Xff, 0Xff));

}
void CcocBotDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str, WinText;
	str.Format("thread count:%ld", ThreadCount);
	pag8.m_ThreadCount.SetWindowText(str);
	str = "状态：";
	str += script->coc.State_str;

	if (m_OldState != script->coc.State_str)
	{
		State.SetWindowText(str);
		m_OldState = script->coc.State_str;
	}
	CTime tm;
	DWORD bigTime = 0;
	tm = CTime::GetCurrentTime();
	CRect rectPicture;
	switch (nIDEvent)
	{
	case 1:
		if (exit_all == 0)
		{
			str = BotServer->GetAcceptStr();
			if (str.GetLength() > 1 && IsFisrstRecord == true)
			{
				IsFisrstRecord = false;
				WriteLog(str, true, RGB(0x00, 0x00, 0xff), false);
			}
			bigTime = (tm.GetDay() - script->coc.tm.GetDay()) * 86400 + (tm.GetHour() - script->coc.tm.GetHour()) * 3600
				+ (tm.GetMinute() - script->coc.tm.GetMinute()) * 60 + tm.GetSecond() - script->coc.tm.GetSecond();
			str.Format("运行时间：%d 天 %d 小时 %d 分 %d 秒 ", bigTime / 86400, (bigTime % 86400) / 3600, (bigTime % 3600) / 60, bigTime % 60);
			pag8.RunTime.SetWindowTextA(str);
			pag8.NowLog.GetWindowText(str);
			WinText = "CocBot 当前版本:<<";
			WinText += cocBotVer;
			WinText += ">>";
			WinText += str;
			WinText += " (正在运行)";
			SetWindowText(WinText);
		}
		else
		{
			str = "(未运行) ";
			WinText = "CocBot 当前版本:<<";
			WinText += cocBotVer;
			WinText += ">>";
			WinText += str;
			SetWindowText(WinText);
		}
		if (exit_all == 1)
		{
			Exit_State++;
		}
		else
		{
			Exit_State = 0;
		}
		if (Exit_State == 20)
		{
			GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			script->IsThreadRun = false;
			Exit_State = 0;
		}
		break;
	case 2:
		//*********** paint *****************//
		if (pag7.IsShowBindSetWindow == true)
		{
			pag7.IsShowBindSetWindow = false;
			bindset.ShowWindow(TRUE);

		}
		if (pag1.IsLoadInConfig)
		{
			pag1.IsLoadInConfig = false;
			OnLoadInConfig();
		}
		if (pag1.IsLoadOutConfig)
		{
			pag1.IsLoadOutConfig = false;
			OnLoadOutConfig();
		}
		if (true == IsInit)
		{
			OnSetSize();
			IsInit = false;

		}
		// 将数组中的所有元素前移一个单位，第一个元素丢弃   
		for (int i = 0; i < POINT_COUNT - 1; i++)
		{
			m_nzValues[i] = m_nzValues[i + 1];
		}
		// 为最后一个元素赋一个80以内的随机数值（整型）   
		m_nzValues[POINT_COUNT - 1] = rand() % 80;

		// 获取绘图控件的客户区坐标   
		// （客户区坐标以窗口的左上角为原点，这区别于以屏幕左上角为原点的屏幕坐标）   
		//pag9.resource.GetClientRect(&rectPicture);
		// 绘制波形图   
		//DrawWave(pag9.resource.GetDC(), rectPicture);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CcocBotDlg::OnScreenCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	long ret = 1;
	script->coc.SetPath(GetExePath());
	script->coc.ScreenCapture("screen.bmp");
	if (ret)
	{
		WriteLog("截图成功，路径是：" + script->coc.GetPath(), 1, RGB(0x00, 0x00, 0xff), false);
	}


}
bool CcocBotDlg::RegDm(void)
{
	CString path, cmdline;
	path = GetExePath();
	CString cmd_line;
	cmd_line = "regsvr32";
	
	cmd_line += " ";
	cmd_line += path;
	cmd_line += "dm.dll /s";
	WinExec(cmd_line, SW_NORMAL);
	path += "Function\\";
	cmdline = path;
	cmdline += "podm.dll";
	if (!script->CreateDm())
	{

		return false;
	}
	HINSTANCE hInst = LoadLibrary(cmdline); // 加载DLL
	if (hInst)
	{
		// 加载成功
		// 定义待访问函数原型 
		typedef BOOL(WINAPI *MYFUNC)(LPCTSTR);
		MYFUNC fun = NULL;
		// 获取函数地址
		fun = (MYFUNC)GetProcAddress(hInst, "破解大漠");
		if (fun)
		{
			// 成功
			fun("dm.dll");
		}
		FreeLibrary(hInst); //释放 DLL
	}
	else
	{
		return false;
	}
	return true;
}
void CcocBotDlg::DrawWave(CDC* pDC, CRect &rectPicture)
{
	float fDeltaX;     // x轴相邻两个绘图点的坐标距离   
	float fDeltaY;     // y轴每个逻辑单位对应的坐标值   
	int nX;      // 在连线时用于存储绘图点的横坐标   
	int nY;      // 在连线时用于存储绘图点的纵坐标   
	CPen newPen;       // 用于创建新画笔   
	CPen *pOldPen;     // 用于存放旧画笔   
	CBrush newBrush;   // 用于创建新画刷   
	CBrush *pOldBrush; // 用于存放旧画刷   

	// 计算fDeltaX和fDeltaY   
	fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);
	fDeltaY = (float)rectPicture.Height() / 80;

	// 创建黑色新画刷   
	newBrush.CreateSolidBrush(RGB(0XFF, 0XFF, 0XFF));
	// 选择新画刷，并将旧画刷的指针保存到pOldBrush   
	pOldBrush = pDC->SelectObject(&newBrush);
	// 以黑色画刷为绘图控件填充黑色，形成黑色背景   
	pDC->Rectangle(rectPicture);
	// 恢复旧画刷   
	pDC->SelectObject(pOldBrush);
	// 删除新画刷   
	newBrush.DeleteObject();

	// 创建实心画笔，粗度为1，颜色为绿色   
	newPen.CreatePen(PS_SOLID, 1, RGB(0xff, 0x00, 0));
	// 选择新画笔，并将旧画笔的指针保存到pOldPen   
	pOldPen = pDC->SelectObject(&newPen);

	// 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点   
	pDC->MoveTo(rectPicture.left + rectPicture.Width() / 2, rectPicture.top);
	// 计算m_nzValues数组中每个点对应的坐标位置，并依次连接，最终形成曲线  
	pDC->LineTo(rectPicture.left + rectPicture.Width() / 2, rectPicture.bottom - 3);
	pDC->MoveTo(rectPicture.left + 3, rectPicture.bottom - rectPicture.Height() / 2);
	pDC->LineTo(rectPicture.right - 3, rectPicture.bottom - rectPicture.Height() / 2);
	for (int i = 3; i < rectPicture.Width(); i += rectPicture.Width() / 24)
	{
		nX = rectPicture.left + i;
		nY = rectPicture.bottom - rectPicture.Height() / 2;
		pDC->MoveTo(nX, nY);
	}
	for (int i = 3; i < rectPicture.Height(); i += rectPicture.Height() / 24)
	{
		nX = rectPicture.left + 3;
		nY = rectPicture.bottom - i;
		pDC->MoveTo(nX, nY);

	}
	nX = rectPicture.left + script->LootRecord[script->SwitchNo].GetRunTime() / 60;
	nY = rectPicture.bottom - script->LootRecord[script->SwitchNo].GetLootGold() / 10000;
	//pDC->LineTo(nX,nY);
	int Ox = rectPicture.left + rectPicture.Width() / 2;
	int Oy = rectPicture.bottom - rectPicture.Height() / 2;
	pDC->MoveTo(Ox, Oy);
	float fx = 0, fy = 0;
	for (float i = 0; i <= 6.3; i += 0.1)
	{
		fx = cos(i);
		fy = sin(i);
		nX = (int)(fx * 100) + Ox;
		nY = (int)(fy * 100) + Oy;
		pDC->LineTo(nX, nY);
	}
	pDC->SelectObject(pOldPen);
	// 删除新画笔   
	newPen.DeleteObject();
	ReleaseDC(pDC);
}
void CcocBotDlg::OnSetSize()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (GetDlgItemText(IDC_SETSIZE, str), str == ">>")
	{
		SetDlgItemText(IDC_SETSIZE, "<<");
	}
	else
	{
		SetDlgItemText(IDC_SETSIZE, ">>");
	}
	static CRect rectLarge;
	static CRect rectSmall;
	if (rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SIZELINE)->GetWindowRect(rectSeparator);
		rectSmall.left = rectLarge.left;
		rectSmall.top = rectLarge.top;
		rectSmall.right = rectSeparator.right;
		rectSmall.bottom = rectLarge.bottom;
	}
	if (str == "<<")
	{
		SetWindowPos(NULL, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL, 0, 0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}



void CcocBotDlg::gameShow()
{
	
}
