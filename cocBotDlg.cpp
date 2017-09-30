
// newcocbotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "cocBotDlg.h"
#include "afxdialogex.h"
#include "lua_func.h"
#include "botLib.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define SetConfig1(a,b,c,d) script[0].coc.setSetsStr((b),(c))
#define SetConfig2(a,b,c,d) script[0].coc.setSetsInt((b),(c))
//*****  全局函数 ***********//


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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	//初始化
	script[MAX_THREAD_COUNT].pProgress = &(pag9.m_progress);




}


CcocBotDlg::~CcocBotDlg()
{




}


void CcocBotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, main_tab);
	DDX_Control(pDX, IDC_START_STOP_BOT, m_StartStopButton);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CcocBotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CcocBotDlg::OnTcnSelchangeTab1)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CcocBotDlg::OnScreenCapture)
	ON_BN_CLICKED(IDC_SHOW_HIDE_WINDOW, &CcocBotDlg::OnBnClickedShowHideAppPlayer)
	ON_BN_CLICKED(IDC_START_STOP_BOT, &CcocBotDlg::OnBnClickedStartStopBot)
	ON_BN_CLICKED(IDC_PAUSEBOT, &CcocBotDlg::OnBnClickedPausebot)
	ON_MESSAGE(WM_PAGE_1_TEST_MESSAGE, oneKeySet)
	ON_MESSAGE(WM_BINDSET_SAVE_CONFIG, SaveConfigInFile)
	ON_MESSAGE(WM_SELECT_APP_PLAYER, SelectAppPlayer)
	ON_MESSAGE(TH_SETLOG, SetLog)
	ON_MESSAGE(TH_STASTICS, Statistics)
	ON_MESSAGE(TH_UPDATA_APP_PLAYER_INFO, UpDataAppPlayerInfo)
	ON_MESSAGE(WM_LOAD_IN_CONFIG, OnLoadInConfig)
	ON_MESSAGE(WM_LOAD_OUT_CONFIG, OnLoadOutConfig)
	ON_MESSAGE(WM_SHOW_GRAHIC,OnShowGraphic)
	ON_BN_CLICKED(IDC_RESET_SIZE, &CcocBotDlg::OnBnClickedResetSize)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CcocBotDlg::OnNMRClickList1)
	ON_COMMAND(IDM_LAUNCH, &CcocBotDlg::OnLaunch)
	ON_COMMAND(IDM_QUIT, &CcocBotDlg::OnQuit)
	ON_COMMAND(IDM_START_ONE_SCRIPT, &CcocBotDlg::OnPauseOneScript)
	ON_COMMAND(IDM_PAUSE_ONE_SCRIPT, &CcocBotDlg::OnPauseOneScript)
	ON_COMMAND(IDM_STOP_ONE_SCRIPT, &CcocBotDlg::OnStopOneScript)
	ON_BN_CLICKED(IDC_UPDATA_LIST, &CcocBotDlg::OnBnClickedUpdataList)
	ON_COMMAND(IDM_SET_CONFIG, &CcocBotDlg::OnSetConfig)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL
};
// CnewcocbotDlg 消息处理程序




void CcocBotDlg::SaveConfig(CString fileName)
{
	CString winText, str;
	if (fileName.GetLength() <= 4)
	{
		fileName = GetExePath() + "Config.ini";
	}

	winText = "";
	//1.快速设置
	//WritePrivateProfileINT("快速设置", "townLevel", pag1.townLevel.GetCurSel(), fileName);
	SetConfig2("快速设置", "townLevel", pag1.townLevel.GetCurSel(), fileName);
	SetConfig2("快速设置", "GameVersion", pag1.GameVersion.GetCurSel(), fileName);
	SetConfig2("快速设置", "OffLine", pag1.OffLine.GetCheck(), fileName);
	SetConfig2("快速设置", "DonateArmy", pag1.DonateArmy.GetCheck(), fileName);
	SetConfig2("快速设置", "Attack", pag1.Attack.GetCheck(), fileName);
	SetConfig2("快速设置", "RequestArmy", pag1.RequestArmy.GetCheck(), fileName);
	SetConfig2("快速设置", "UpgradeWall", pag1.UpgradeWall.GetCheck(), fileName);
	SetConfig2("快速设置", "UpgradeHeros", pag1.UpgradeHeros.GetCheck(), fileName);
	SetConfig2("快速设置", "ControlTroophs", pag1.ControlTroophs.GetCheck(), fileName);
	SetConfig2("快速设置", "LightingDarkElixir", pag1.LightingDarkElixir.GetCheck(), fileName);
	SetConfig2("快速设置", "RemoveTree", pag1.RemoveTree.GetCheck(), fileName);
	SetConfig2("快速设置", "RearmAll", pag1.RearmAll.GetCheck(), fileName);
	SetConfig1("快速设置", "QuickSetShow", winText, fileName);
	pag1.LoadOutSet.GetWindowText(winText);
	SetConfig1("快速设置", "LoadOutSet", winText, fileName);
	//2.训练设置
	SetConfig2("训练设置", "TrainArmyStyle", pag2.TrainArmyStyle.GetCurSel(), fileName);
	SetConfig2("训练设置", "IsClearArmy", pag2.IsClearArmy.GetCurSel(), fileName);
	SetConfig2("训练设置", "IsAddArmy", pag2.IsAddArmy.GetCurSel(), fileName);
	pag2.Barbarin.GetWindowText(winText);
	SetConfig1("训练设置", "Barbarin", winText, fileName);
	pag2.Archer.GetWindowText(winText);
	SetConfig1("训练设置", "Archer", winText, fileName);
	pag2.Giant.GetWindowText(winText);
	SetConfig1("训练设置", "Giant", winText, fileName);
	pag2.Goblin.GetWindowText(winText);
	SetConfig1("训练设置", "Goblin", winText, fileName);
	pag2.WallBreaker.GetWindowText(winText);
	SetConfig1("训练设置", "WallBreaker", winText, fileName);
	pag2.Ballon.GetWindowText(winText);
	SetConfig1("训练设置", "Ballon", winText, fileName);
	pag2.Wizard.GetWindowText(winText);
	SetConfig1("训练设置", "Wizard", winText, fileName);
	pag2.Healer.GetWindowText(winText);
	SetConfig1("训练设置", "Healer", winText, fileName);
	pag2.Dragon.GetWindowText(winText);
	SetConfig1("训练设置", "Dragon", winText, fileName);
	pag2.Peka.GetWindowText(winText);
	SetConfig1("训练设置", "Peka", winText, fileName);
	pag2.BabyDragon.GetWindowText(winText);
	SetConfig1("训练设置", "BabyDragon", winText, fileName);
	pag2.Miner.GetWindowText(winText);
	SetConfig1("训练设置", "Miner", winText, fileName);
	pag2.Minion.GetWindowText(winText);
	SetConfig1("训练设置", "Minion", winText, fileName);
	pag2.HogRider.GetWindowText(winText);
	SetConfig1("训练设置", "HogRider", winText, fileName);
	pag2.Valkyrie.GetWindowText(winText);
	SetConfig1("训练设置", "Valkyrie", winText, fileName);
	pag2.Golem.GetWindowText(winText);
	SetConfig1("训练设置", "Golem", winText, fileName);
	pag2.Witch.GetWindowText(winText);
	SetConfig1("训练设置", "Witch", winText, fileName);
	pag2.LavaHound.GetWindowText(winText);
	SetConfig1("训练设置", "LavaHound", winText, fileName);
	pag2.BowLer.GetWindowText(winText);
	SetConfig1("训练设置", "BowLer", winText, fileName);
	pag2.LightingSpell.GetWindowText(winText);
	SetConfig1("训练设置", "LightingSpell", winText, fileName);
	pag2.HealingSpell.GetWindowText(winText);
	SetConfig1("训练设置", "HealingSpell", winText, fileName);
	pag2.RageSpell.GetWindowText(winText);
	SetConfig1("训练设置", "RageSpell", winText, fileName);
	pag2.JumpSpell.GetWindowText(winText);
	SetConfig1("训练设置", "JumpSpell", winText, fileName);
	pag2.FreezeSpell.GetWindowText(winText);
	SetConfig1("训练设置", "FreezeSpell", winText, fileName);
	pag2.CloneSpell.GetWindowText(winText);
	SetConfig1("训练设置", "CloneSpell", winText, fileName);
	pag2.PoisonSpell.GetWindowText(winText);
	SetConfig1("训练设置", "PoisonSpell", winText, fileName);
	pag2.EarthquakeSpell.GetWindowText(winText);
	SetConfig1("训练设置", "EarthquakeSpell", winText, fileName);
	pag2.HasteSpell.GetWindowText(winText);
	SetConfig1("训练设置", "HasteSpell", winText, fileName);
	pag2.SkeletonSpell.GetWindowText(winText);
	SetConfig1("训练设置", "SkeletonSpell", winText, fileName);
	SetConfig2("训练设置", "IsSpeedUp", pag2.IsSpeedUp.GetCheck(), fileName);
	pag2.SpeedUpBegin.GetWindowText(winText);
	SetConfig1("训练设置", "SpeedUpBegin", winText, fileName);
	pag2.SpeedUpEnd.GetWindowText(winText);
	SetConfig1("训练设置", "SpeedUpEnd", winText, fileName);
	//3.搜索设置
	pag3.MinTroopRet.GetWindowTextA(winText);
	SetConfig1("搜索设置", "MinTroopRet", winText, fileName);
	pag3.SearchMinGold.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchMinGold", winText, fileName);
	pag3.SearchMinElixir.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchMinElixir", winText, fileName);
	pag3.SearchMinDarkElixir.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchMinDarkElixir", winText, fileName);
	pag3.SearchDealy.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchDealy", winText, fileName);
	pag3.SearchWait.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchWait", winText, fileName);
	pag3.SearchMaxCount.GetWindowTextA(winText);
	SetConfig1("搜索设置", "SearchMaxCount", winText, fileName);
	pag3.MinTroophs.GetWindowTextA(winText);
	SetConfig1("搜索设置", "MinTroophs", winText, fileName);
	pag3.MaxTroophs.GetWindowTextA(winText);
	SetConfig1("搜索设置", "MaxTroophs", winText, fileName);
	SetConfig2("搜索设置", "IsWaitBarbarinKing", pag3.IsWaitBarbarinKing.GetCheck(), fileName);
	SetConfig2("搜索设置", "IsWaitGrandKing", pag3.IsWaitGrandKing.GetCheck(), fileName);
	SetConfig2("搜索设置", "IsWaitArcherKing", pag3.IsWaitArcherKing.GetCheck(), fileName);
	SetConfig2("搜索设置", "IsWaitClanCastleTroopsAndSpells", pag3.IsWaitClanCastleTroopsAndSpells.GetCheck(), fileName);
	SetConfig2("搜索设置", "IsWaitSpell", pag3.IsWaitSpell.GetCheck(), fileName);
	SetConfig2("搜索设置", "ArcherTower", pag3.ArcherTower.GetCheck(), fileName);
	SetConfig2("搜索设置", "Mortar", pag3.Mortar.GetCheck(), fileName);
	SetConfig2("搜索设置", "WizardTower", pag3.WizardTower.GetCheck(), fileName);
	SetConfig2("搜索设置", "AirDefense", pag3.AirDefense.GetCheck(), fileName);
	SetConfig2("搜索设置", "XBow", pag3.XBow.GetCheck(), fileName);
	SetConfig2("搜索设置", "Inferno", pag3.Inferno.GetCheck(), fileName);
	SetConfig2("搜索设置", "EagleArtillery", pag3.EagleArtillery.GetCheck(), fileName);
	SetConfig2("搜索设置", "SearchType", pag3.SearchType.GetCurSel(), fileName);
	SetConfig2("搜索设置", "SearchDeadbaseGoldCollector", pag3.SearchDeadbaseGoldCollector.GetCurSel(), fileName);
	SetConfig2("搜索设置", "SearchDeadbaseElixir", pag3.SearchDeadbaseElixir.GetCurSel(), fileName);
	SetConfig2("搜索设置", "SearchType", pag3.SearchType.GetCurSel(), fileName);
	SetConfig2("搜索设置", "ArcherTowerLevel", pag3.ArcherTowerLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "MortarLevel", pag3.MortarLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "WizardTowerLevel", pag3.WizardTowerLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "AirDefenseLevel", pag3.AirDefenseLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "XBowLevel", pag3.XBowLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "InfernoLevel", pag3.InfernoLevel.GetCurSel(), fileName);
	SetConfig2("搜索设置", "EagleArtilleryLevel", pag3.EagleArtilleryLevel.GetCurSel(), fileName);
	//4.攻击设置
	SetConfig2("攻击设置", "AttackSpeed", pag4.AttackSpeed.GetCurSel(), fileName);
	SetConfig2("攻击设置", "AttackGird", pag4.AttackGird.GetCurSel(), fileName);
	SetConfig2("攻击设置", "attackCount", pag4.attackCount.GetCurSel(), fileName);
	SetConfig2("攻击设置", "AttackDeadbaseStyle", pag4.AttackDeadbaseStyle.GetCurSel(), fileName);
	SetConfig2("攻击设置", "AttackActivebaseStyle", pag4.AttackActivebaseStyle.GetCurSel(), fileName);
	SetConfig2("攻击设置", "AttackMinDarkElixirLevel", pag4.AttackMinDarkElixirLevel.GetCurSel(), fileName);
	SetConfig2("攻击设置", "UseLightingCount", pag4.UseLightingCount.GetCurSel(), fileName);
	SetConfig2("攻击设置", "AttackIsExitWithoutResource", pag4.AttackIsExitWithoutResource.GetCheck(), fileName);
	SetConfig2("攻击设置", "AttackIsExitWhenLittleResource", pag4.AttackIsExitWhenLittleResource.GetCheck(), fileName);
    int index = pag4.m_lua_list.GetCurSel();
	if (index < 0)index = 0;
	SetConfig2("", "AttackLuaIndex", index, fileName);
	pag4.m_lua_list.GetText(index, winText);
	SetConfig1("攻击设置", "AttackLuaName", winText, fileName);
	pag4.AttackMinWaitTime.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackMinWaitTime", winText, fileName);
	pag4.AttackExitGold.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackExitGold", winText, fileName);
	pag4.AttackExitElixir.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackExitElixir", winText, fileName);
	pag4.AttackExitDarkElixir.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackExitDarkElixir", winText, fileName);
	pag4.AttackLingtingMinDarkElixir.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackLingtingMinDarkElixir", winText, fileName);
	pag4.AttackMinWaitTime.GetWindowTextA(winText);
	SetConfig1("攻击设置", "AttackMinWaitTime", winText, fileName);
	//5.捐兵/请求
	pag5.DonateMinSendGetRet.GetWindowTextA(winText);
	SetConfig1("捐兵/请求", "DonateMinSendGetRet", winText, fileName);
	pag5.DonateCount.GetWindowTextA(winText);
	SetConfig1("捐兵/请求", "DonateCount", winText, fileName);
	pag5.DonateDealy.GetWindowTextA(winText);
	SetConfig1("捐兵/请求", "DonateDealy", winText, fileName);
	pag5.requestWords.GetWindowTextA(winText);
	SetConfig1("捐兵/请求", "requestWords", winText, fileName);
	SetConfig2("捐兵/请求", "IsChangeWords", pag5.IsChangeWords.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "DonateType", pag5.DonateType.GetCurSel(), fileName);
	SetConfig2("捐兵/请求", "IsDonateSendGetRet", pag5.IsDonateSendGetRet.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsDonateNotFull", pag5.IsDonateNotFull.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsBarbarin", pag5.IsBarbarin.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsGiant", pag5.IsArcher.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsBarbarin", pag5.IsGiant.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsGoblin", pag5.IsGoblin.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsWallBreaker", pag5.IsWallBreaker.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsBallon", pag5.IsBallon.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsWizard", pag5.IsWizard.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsHealer", pag5.IsHealer.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsDragon", pag5.IsDragon.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsPeka", pag5.IsPeka.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsBabyDragon", pag5.IsBabyDragon.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsMiner", pag5.IsMiner.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsMinion", pag5.IsMinion.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsHogRider", pag5.IsHogRider.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsValkyrie", pag5.IsValkyrie.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsGolem", pag5.IsGolem.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsWitch", pag5.IsWitch.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsLavaHound", pag5.IsLavaHound.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsBower", pag5.IsBower.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsPoison", pag5.IsPoison.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsEarthquake", pag5.IsEarthquake.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsHaste", pag5.IsHaste.GetCheck(), fileName);
	SetConfig2("捐兵/请求", "IsSkeleton", pag5.IsSkeleton.GetCheck(), fileName);
	for (int i = 0; i < 21; i++)
	{
		str.Format("UserWant %d", i);
		winText.Format("%d", pag5.ListKeyWord.GetCheck(i));
		winText += "|";
		winText += pag5.ListKeyWord.GetItemText(i, 1);
		SetConfig1("捐兵/请求", str, winText, fileName);

	}
	//6.升级设置
	pag6.UpgradeWallMinGold.GetWindowTextA(winText);
	SetConfig1("升级设置", "UpgradeWallMinGold", winText, fileName);
	pag6.UpgradeWallMinElixir.GetWindowTextA(winText);
	SetConfig1("升级设置", "UpgradeWallMinElixir", winText, fileName);
	pag6.UpgradeHeroMinDarkElixir.GetWindowTextA(winText);
	SetConfig1("升级设置", "UpgradeHeroMinDarkElixir", winText, fileName);
	SetConfig2("升级设置", "UpgradeWallUseType", pag6.UpgradeWallUseType.GetCurSel(), fileName);
	SetConfig2("升级设置", "UpgradeWallLevel", pag6.UpgradeWallLevel.GetCurSel(), fileName);
	SetConfig2("升级设置", "UpgradeHeroType", pag6.UpgradeHeroType.GetCurSel(), fileName);
	//7.高级设置
	SetConfig2("高级设置", "DeBugSearchShoot", pag7.DeBugSearchShoot.GetCheck(), fileName);
	SetConfig2("高级设置", "DebugLocateAD", pag7.DebugLocateAD.GetCheck(), fileName);
	SetConfig2("高级设置", "SetShowErrorMsg", pag7.SetShowErrorMsg.GetCheck(), fileName);
	SetConfig2("高级设置", "IsSwitchMode", pag7.IsSwitchMode.GetCheck(), fileName);
	for (int i = 0; i < MAX_SWITCH_COUNT - 1; i++)
	{
		winText.Format("IsSwitch --Index %d", i + 1);
		SetConfig2("高级设置", winText, pag7.m_list1.GetCheck(i), fileName);
		winText.Format("CocName --Index %d", i + 1);
		SetConfig1("高级设置", winText, pag7.m_list1.GetItemText(i, 1), fileName);
		winText.Format("ConfigPath --Index %d", i + 1);
		SetConfig1("高级设置", winText, pag7.m_list1.GetItemText(i, 2), fileName);
		winText.Format("CocVersion --Index %d", i + 1);
		SetConfig1("高级设置", winText, pag7.m_list1.GetItemText(i, 3), fileName);
	}

	//8.多开控制
	//bindset.AppPlayerInstallDir.GetWindowTextA(winText);
	SetConfig1("多开控制", "AppPlayerInstallDir", winText, fileName);
	script[0].coc.SaveSets(fileName);
}


void CcocBotDlg::UpdateWindowSet()
{
	
	pag1.townLevel.SetCurSel(_ttoi(script[0].coc.getSets("townLevel")));
	pag1.GameVersion.SetCurSel(_ttoi(script[0].coc.getSets("GameVersion")));
	pag1.OffLine.SetCheck(_ttoi(script[0].coc.getSets("OffLine")));
	pag1.RequestArmy.SetCheck(_ttoi(script[0].coc.getSets("license")));
	pag1.RequestArmy.SetCheck(_ttoi(script[0].coc.getSets("RequestArmy")));
	pag1.Attack.SetCheck(_ttoi(script[0].coc.getSets("Attack")));
	pag1.DonateArmy.SetCheck(_ttoi(script[0].coc.getSets("DonateArmy")));
	pag1.UpgradeWall.SetCheck(_ttoi(script[0].coc.getSets("UpgradeWall")));
	pag1.UpgradeHeros.SetCheck(_ttoi(script[0].coc.getSets("UpgradeHeros")));
	pag1.ControlTroophs.SetCheck(_ttoi(script[0].coc.getSets("ControlTroophs")));
	pag1.LightingDarkElixir.SetCheck(_ttoi(script[0].coc.getSets("LightingDarkElixir")));
	pag1.RemoveTree.SetCheck(_ttoi(script[0].coc.getSets("RemoveTree")));
	pag1.RearmAll.SetCheck(_ttoi(script[0].coc.getSets("RearmAll")));
	pag1.LoadInSet.SetWindowText(script[0].coc.getSets("LoadInSet"));
	pag1.LoadOutSet.SetWindowText(script[0].coc.getSets("LoadOutSet"));
	pag2.TrainArmyStyle.SetCurSel(_ttoi(script[0].coc.getSets("TrainArmyStyle")));
	pag2.IsClearArmy.SetCurSel(_ttoi(script[0].coc.getSets("IsClearArmy")));
	pag2.IsAddArmy.SetCurSel(_ttoi(script[0].coc.getSets("IsAddArmy")));
	pag2.IsSpeedUp.SetCheck(_ttoi(script[0].coc.getSets("IsSpeedUp")));
	pag2.SpeedUpBegin.SetWindowText(script[0].coc.getSets("SpeedUpBegin"));
	pag2.SpeedUpEnd.SetWindowText(script[0].coc.getSets("SpeedUpEnd"));
	pag2.Barbarin.SetWindowText(script[0].coc.getSets("Barbarin"));
	pag2.Archer.SetWindowText(script[0].coc.getSets("Archer"));
	pag2.Giant.SetWindowText(script[0].coc.getSets("Giant"));
	pag2.Goblin.SetWindowText(script[0].coc.getSets("Goblin"));
	pag2.WallBreaker.SetWindowText(script[0].coc.getSets("WallBreaker"));
	pag2.Ballon.SetWindowText(script[0].coc.getSets("Ballon"));
	pag2.Wizard.SetWindowText(script[0].coc.getSets("Wizard"));
	pag2.Healer.SetWindowText(script[0].coc.getSets("Healer"));
	pag2.Dragon.SetWindowText(script[0].coc.getSets("Dragon"));
	pag2.Peka.SetWindowText(script[0].coc.getSets("Peka"));
	pag2.BabyDragon.SetWindowText(script[0].coc.getSets("BabyDragon"));
	pag2.Miner.SetWindowText(script[0].coc.getSets("Miner"));
	pag2.Minion.SetWindowText(script[0].coc.getSets("Minion"));
	pag2.HogRider.SetWindowText(script[0].coc.getSets("HogRider"));
	pag2.Valkyrie.SetWindowText(script[0].coc.getSets("Valkyrie"));
	pag2.Golem.SetWindowText(script[0].coc.getSets("Golem"));
	pag2.Witch.SetWindowText(script[0].coc.getSets("Witch"));
	pag2.LavaHound.SetWindowText(script[0].coc.getSets("LavaHound"));
	pag2.BowLer.SetWindowText(script[0].coc.getSets("BowLer"));
	pag2.LightingSpell.SetWindowText(script[0].coc.getSets("LightingSpell"));
	pag2.HealingSpell.SetWindowText(script[0].coc.getSets("HealingSpell"));
	pag2.RageSpell.SetWindowText(script[0].coc.getSets("RageSpell"));
	pag2.JumpSpell.SetWindowText(script[0].coc.getSets("JumpSpell"));
	pag2.FreezeSpell.SetWindowText(script[0].coc.getSets("FreezeSpell"));
	pag2.CloneSpell.SetWindowText(script[0].coc.getSets("CloneSpell"));
	pag2.PoisonSpell.SetWindowText(script[0].coc.getSets("PoisonSpell"));
	pag2.EarthquakeSpell.SetWindowText(script[0].coc.getSets("EarthquakeSpell"));
	pag2.HasteSpell.SetWindowText(script[0].coc.getSets("HasteSpell"));
	pag2.SkeletonSpell.SetWindowText(script[0].coc.getSets("SkeletonSpell"));
	pag3.MinTroopRet.SetWindowText(script[0].coc.getSets("MinTroopRet"));
	pag3.SearchMinGold.SetWindowText(script[0].coc.getSets("SearchMinGold"));
	pag3.SearchMinElixir.SetWindowText(script[0].coc.getSets("SearchMinElixir"));
	pag3.SearchMinDarkElixir.SetWindowText(script[0].coc.getSets("SearchMinDarkElixir"));
	pag3.SearchDealy.SetWindowText(script[0].coc.getSets("SearchDealy"));
	pag3.SearchWait.SetWindowText(script[0].coc.getSets("SearchWait"));
	pag3.SearchMaxCount.SetWindowText(script[0].coc.getSets("SearchMaxCount"));
	pag3.MinTroophs.SetWindowText(script[0].coc.getSets("MinTroophs"));
	pag3.MaxTroophs.SetWindowText(script[0].coc.getSets("MaxTroophs"));
	pag3.IsWaitBarbarinKing.SetCheck(_ttoi(script[0].coc.getSets("IsWaitBarbarinKing")));
	pag3.IsWaitArcherKing.SetCheck(_ttoi(script[0].coc.getSets("IsWaitArcherKing")));
	pag3.IsWaitGrandKing.SetCheck(_ttoi(script[0].coc.getSets("IsWaitGrandKing")));
	pag3.IsWaitClanCastleTroopsAndSpells.SetCheck(_ttoi(script[0].coc.getSets("IsWaitClanCastleTroopsAndSpells")));
	pag3.IsWaitSpell.SetCheck(_ttoi(script[0].coc.getSets("IsWaitSpell")));
	pag3.ArcherTower.SetCheck(_ttoi(script[0].coc.getSets("ArcherTower")));
	pag3.Mortar.SetCheck(_ttoi(script[0].coc.getSets("Mortar")));
	pag3.WizardTower.SetCheck(_ttoi(script[0].coc.getSets("WizardTower")));
	pag3.AirDefense.SetCheck(_ttoi(script[0].coc.getSets("AirDefense")));
	pag3.XBow.SetCheck(_ttoi(script[0].coc.getSets("XBow")));
	pag3.Inferno.SetCheck(_ttoi(script[0].coc.getSets("Inferno")));
	pag3.EagleArtillery.SetCheck(_ttoi(script[0].coc.getSets("EagleArtillery")));
	pag3.SearchType.SetCurSel(_ttoi(script[0].coc.getSets("SearchType")));
	pag3.SearchDeadbaseGoldCollector.SetCurSel(_ttoi(script[0].coc.getSets("SearchDeadbaseGoldCollector")));
	pag3.SearchDeadbaseElixir.SetCurSel(_ttoi(script[0].coc.getSets("SearchDeadbaseElixir")));
	pag3.ArcherTowerLevel.SetCurSel(_ttoi(script[0].coc.getSets("ArcherTowerLevel")));
	pag3.MortarLevel.SetCurSel(_ttoi(script[0].coc.getSets("MortarLevel")));
	pag3.WizardTowerLevel.SetCurSel(_ttoi(script[0].coc.getSets("WizardTowerLevel")));
	pag3.AirDefenseLevel.SetCurSel(_ttoi(script[0].coc.getSets("AirDefenseLevel")));
	pag3.XBowLevel.SetCurSel(_ttoi(script[0].coc.getSets("XBowLevel")));
	pag3.InfernoLevel.SetCurSel(_ttoi(script[0].coc.getSets("InfernoLevel")));
	pag3.EagleArtilleryLevel.SetCurSel(_ttoi(script[0].coc.getSets("EagleArtilleryLevel")));
	pag4.AttackSpeed.SetCurSel(_ttoi(script[0].coc.getSets("AttackSpeed")));//attackCount
	pag4.attackCount.SetCurSel(_ttoi(script[0].coc.getSets("attackCount")));//AttackGird
	pag4.AttackGird.SetCurSel(_ttoi(script[0].coc.getSets("AttackGird")));
	pag4.m_lua_list.SetCurSel(script[0].coc.getSetsInt("AttackLuaIndex"));
	pag4.AttackDeadbaseStyle.SetCurSel(_ttoi(script[0].coc.getSets("AttackDeadbaseStyle")));
	pag4.AttackActivebaseStyle.SetCurSel(_ttoi(script[0].coc.getSets("AttackActivebaseStyle")));
	pag4.AttackMinDarkElixirLevel.SetCurSel(_ttoi(script[0].coc.getSets("AttackMinDarkElixirLevel")));
	pag4.AttackIsExitWithoutResource.SetCheck(_ttoi(script[0].coc.getSets("AttackIsExitWithoutResource")));
	pag4.AttackIsExitWhenLittleResource.SetCheck(_ttoi(script[0].coc.getSets("AttackIsExitWhenLittleResource")));
	pag4.AttackMinWaitTime.SetWindowText(script[0].coc.getSets("AttackMinWaitTime"));
	pag4.AttackExitGold.SetWindowText(script[0].coc.getSets("AttackExitGold"));
	pag4.AttackExitElixir.SetWindowText(script[0].coc.getSets("AttackExitElixir"));
	pag4.AttackExitDarkElixir.SetWindowText(script[0].coc.getSets("AttackExitDarkElixir"));
	pag4.AttackLingtingMinDarkElixir.SetWindowText(script[0].coc.getSets("AttackLingtingMinDarkElixir"));
	pag4.UseLightingCount.SetCurSel(_ttoi(script[0].coc.getSets("UseLightingCount")));
	pag5.DonateType.SetCurSel(_ttoi(script[0].coc.getSets("DonateType")));
	pag5.DonateMinSendGetRet.SetWindowText(script[0].coc.getSets("DonateMinSendGetRet"));
	pag5.DonateCount.SetWindowText(script[0].coc.getSets("DonateCount"));
	pag5.DonateDealy.SetWindowText(script[0].coc.getSets("DonateDealy"));
	pag5.IsDonateSendGetRet.SetCheck(_ttoi(script[0].coc.getSets("IsDonateSendGetRet")));
	pag5.IsDonateNotFull.SetCheck(_ttoi(script[0].coc.getSets("IsDonateNotFull")));
	pag5.requestWords.SetWindowText(script[0].coc.getSets("requestWords"));
	pag5.IsChangeWords.SetCheck(_ttoi(script[0].coc.getSets("IsChangeWords")));
	pag5.IsBarbarin.SetCheck(_ttoi(script[0].coc.getSets("IsBarbarin")));
	pag5.IsArcher.SetCheck(_ttoi(script[0].coc.getSets("IsArcher")));
	pag5.IsGiant.SetCheck(_ttoi(script[0].coc.getSets("IsGiant")));
	pag5.IsGoblin.SetCheck(_ttoi(script[0].coc.getSets("IsGoblin")));
	pag5.IsWallBreaker.SetCheck(_ttoi(script[0].coc.getSets("IsWallBreaker")));
	pag5.IsBallon.SetCheck(_ttoi(script[0].coc.getSets("IsBallon")));
	pag5.IsWizard.SetCheck(_ttoi(script[0].coc.getSets("IsWizard")));
	pag5.IsHealer.SetCheck(_ttoi(script[0].coc.getSets("IsHealer")));
	pag5.IsDragon.SetCheck(_ttoi(script[0].coc.getSets("IsDragon")));
	pag5.IsPeka.SetCheck(_ttoi(script[0].coc.getSets("IsPeka")));
	pag5.IsBabyDragon.SetCheck(_ttoi(script[0].coc.getSets("IsBabyDragon")));
	pag5.IsMiner.SetCheck(_ttoi(script[0].coc.getSets("IsMiner")));
	pag5.IsMinion.SetCheck(_ttoi(script[0].coc.getSets("IsMinion")));
	pag5.IsHogRider.SetCheck(_ttoi(script[0].coc.getSets("IsHogRider")));
	pag5.IsValkyrie.SetCheck(_ttoi(script[0].coc.getSets("IsValkyrie")));
	pag5.IsGolem.SetCheck(_ttoi(script[0].coc.getSets("IsGolem")));
	pag5.IsWitch.SetCheck(_ttoi(script[0].coc.getSets("IsWitch")));
	pag5.IsLavaHound.SetCheck(_ttoi(script[0].coc.getSets("IsLavaHound")));
	pag5.IsBower.SetCheck(_ttoi(script[0].coc.getSets("IsBower")));
	pag5.IsPoison.SetCheck(_ttoi(script[0].coc.getSets("IsPoison")));
	pag5.IsEarthquake.SetCheck(_ttoi(script[0].coc.getSets("IsEarthquake")));
	pag5.IsHaste.SetCheck(_ttoi(script[0].coc.getSets("IsHaste")));
	pag5.IsSkeleton.SetCheck(_ttoi(script[0].coc.getSets("IsSkeleton")));
	CString winText, str;
	char buffer[512] = { 0 };
	using namespace std;
	vector<string>vstr;
	for (int i = 0; i < 21; i++)
	{
		str.Format("UserWant %d", i);
		GetPrivateProfileString("捐兵/请求", str, "", buffer, 512, script[0].coc.GetPath());
		if (strlen(buffer) == 0) continue;
		_split(buffer, vstr, "|");
		if (vstr.size() == 0) continue;
		pag5.ListKeyWord.SetCheck(i, _ttoi(vstr[0].c_str()));
		pag5.ListKeyWord.SetItemText(i, 1, vstr[1].c_str());

	}

	pag6.UpgradeWallMinGold.SetWindowText(script[0].coc.getSets("UpgradeWallMinGold"));
	pag6.UpgradeWallMinElixir.SetWindowText(script[0].coc.getSets("UpgradeWallMinElixir"));
	pag6.UpgradeHeroMinDarkElixir.SetWindowText(script[0].coc.getSets("UpgradeHeroMinDarkElixir"));
	pag6.UpgradeWallUseType.SetCurSel(_ttoi(script[0].coc.getSets("UpgradeWallUseType")));
	pag6.UpgradeWallLevel.SetCurSel(_ttoi(script[0].coc.getSets("UpgradeWallLevel")));
	pag6.UpgradeHeroType.SetCurSel(_ttoi(script[0].coc.getSets("UpgradeHeroType")));
	//7.高级设置
	pag7.SetShowErrorMsg.SetCheck(_ttoi(script[0].coc.getSets("SetShowErrorMsg")));
	pag7.DebugLocateAD.SetCheck(_ttoi(script[0].coc.getSets("DebugLocateAD")));
	pag7.IsSwitchMode.SetCheck(_ttoi(script[0].coc.getSets("IsSwitchMode")));
	pag7.DeBugSearchShoot.SetCheck(_ttoi(script[0].coc.getSets("DeBugSearchShoot")));
	pag7.SwitchModeVersion_1.SetCurSel(_ttoi(script[0].coc.getSets("SwitchModeVersion_1")));

	for (int i = 0; i < MAX_SWITCH_COUNT - 1; i++)
	{
		winText.Format("IsSwitch --Index %d", i + 1);
		pag7.m_list1.SetCheck(i, _ttoi(script[0].coc.getSets(winText)));
		winText.Format("CocName --Index %d", i + 1);
		pag7.m_list1.SetItemText(i, 1, script[0].coc.getSets(winText));
		winText.Format("ConfigPath --Index %d", i + 1);
		pag7.m_list1.SetItemText(i, 2, script[0].coc.getSets(winText));
		winText.Format("CocVersion --Index %d", i + 1);
		pag7.m_list1.SetItemText(i, 3, script[0].coc.getSets(winText));
	}

	//8.
//	bindset.AppPlayerInstallDir.SetWindowText(script[0].coc.getSets("AppPlayerInstallDir"));

}


BOOL CcocBotDlg::IsFirstUsePrograme()
{
	BOOL IsFirst = FALSE;
	CRegKey myKey;
	const int maxLen = 255;
	ULONG nchars = 255;
	myKey.Create(HKEY_CURRENT_USER, "SOFTWARE\\CocBot\\Config\\0");
	char msg[maxLen] = { 0 };
	myKey.QueryMultiStringValue("version", msg, &nchars);

	if (fbot.compareStr(msg, cocBotVer) == false)
	{
		IsFirst = TRUE;
		myKey.SetMultiStringValue("version", cocBotVer);
		myKey.SetMultiStringValue("Talking", QQGROUPNAME);
	}

	myKey.Close();
	return IsFirst;
}




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
	pag1.Create(IDD_DIALOG1, this);
	pag2.Create(IDD_DIALOG2, this);
	pag3.Create(IDD_DIALOG3, this);
	pag4.Create(IDD_DIALOG4, this);
	pag5.Create(IDD_DIALOG5, this);
	pag6.Create(IDD_DIALOG6, this);
	pag7.Create(IDD_DIALOG7, this);
	pag8.Create(IDD_DIALOG8, this);
	pag9.Create(IDD_DIALOG9, this);
	pag10.Create(IDD_DIALOG10, this);
	if (m_graphic.Create(IDD_DIALOG_GRAPHIC, this) == FALSE) exit(-2);
	//m_graphic.ShowWindow(TRUE);
	//获得IDC_TABTEST客户区大小
	CRect rc;
	main_tab.GetClientRect(&rc);
	//调整子对话框在父窗口中的位置
	rc.top += 40;
	
	//获取窗口最大
	GetWindowRect(&rect_max);
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
	//父窗口句柄
	script[MAX_THREAD_COUNT].hParennt = GetSafeHwnd();
	script[MAX_THREAD_COUNT].AppPlayerIndex = 0;
	for (int index = 0; index < MAX_THREAD_COUNT; index++)
	{
		script[index].hParennt = GetSafeHwnd();
	}
	pag1.hParent = GetSafeHwnd();
	menu.LoadMenu(IDR_MENU1);

	//================检测模拟器=====================
	CRegKey key;
	ULONG nchars = 255;
	char buf[0xff] = { 0 };
	if (ERROR_SUCCESS == key.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\BlueStacks"))
	{
		/*成功*/
		if (ERROR_SUCCESS == key.QueryStringValue("InstallDir", buf, &nchars))
		{
			title = buf;
			/*写进配置文件*/
			if (title.Right(1) == "\\")title.Delete(title.GetLength() - 1, 1);
			//将模拟器路径载入内存
			app_player_bs_install_dir = title;
			SetConfig1("多开控制", "AppPlayerInstallDir", title, GetExePath() + "Config.ini");
			title = "检测到BlueStacks App Player path:";
			title += buf;
			title += "\nversion:";
			key.QueryStringValue("Version", buf, &nchars);
			title += buf;
			script[MAX_THREAD_COUNT].SetLog(title, true, BLUECOLOR);
		}
		else
		{
			script[MAX_THREAD_COUNT].SetLog("无法读取值");
		}




		key.Close();
	}
	nchars = 255;
	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, "Software\\ChangZhi2\\dnplayer"))
	{
		/*成功*/

		key.QueryStringValue("InstallDir", buf, &nchars);
		title = buf;
		/*写进配置文件*/
		if (title.Right(1) == "\\")title.Delete(title.GetLength() - 1, 1);
		//将模拟器路径载入内存
		app_player_ld_install_dir = title;
		SetConfig1("多开控制", "AppPlayerInstallDir", title, GetExePath() + "Config.ini");
		if (title.GetLength() > 0)
		{
			title = "检测到雷电模拟器 path:";
			title += buf;
			title += "\nversion:";
			key.QueryStringValue("Version", buf, &nchars);
			title += buf;
			script[MAX_THREAD_COUNT].SetLog(title, true, BLUECOLOR);
		}
		key.Close();
	}


	//********************* 初始化列表************************//
	InitlizeList();
	//***************** 从配置中读取所需配置 ****************//
	CString str_show, path;
	
	/******************************/
	
	path = GetExePath();
	script[0].coc.SetPath(path);
	str_show = script[0].coc.ReadFile("Instruction.txt");
	pag10.Instruction.SetWindowTextA(str_show);
	script[MAX_THREAD_COUNT].SetLog("当前版本：" + script[MAX_THREAD_COUNT].scriptVer, 1, RGB(0x00, 0x00, 0xff), false);
	script[MAX_THREAD_COUNT].SetLog("交流群：584618461", true, RGB(0x00, 0x00, 0xff), false);
	//SetBackgroundColor(RGB(0Xc0, 0xc0, 0xc0));
	m_IconStart = AfxGetApp()->LoadIcon(IDI_ICON4);
	m_IconStop = AfxGetApp()->LoadIcon(IDI_ICON5);
	m_StartStopButton.SetIcon(m_IconStart);
	// 启动定时器，ID为1，定时时间为200ms   
	if (IsFirstUsePrograme() == TRUE)
	{
		MessageBox("欢迎首次使用cocBot,使用前务必阅读使用教程！", "提示", MB_ICONINFORMATION);
	}


	pag9.m_progress.SetRange(0, 100);
	//对下拉框进行初始化
	using std::vector;
	using std::string;
	vector <string> vstr1, vstr2;
	//加载常用配置
	script[MAX_THREAD_COUNT].SetLog("加载常用配置", true, BLACKCOLOR, true);
	path =GetExePath();
	path += "常用配置";
	path += "\\";
	script[0].coc.FileSearch(path,"*.ini");
	str_show = script[0].coc.SearchStr;
	_split(str_show.GetBuffer(), vstr1, "|");
	str_show.ReleaseBuffer();
	if (vstr1.size() > 0)
	{
		for (int i = 0; i < vstr1.size(); i++)
		{
			pag1.m_list.AddString(vstr1[i].c_str());
		}
		script[MAX_THREAD_COUNT].SetLog("加载完成", true, BLACKCOLOR, true);
	}
	else
	{
		script[MAX_THREAD_COUNT].SetLog("加载失败", true, REDCOLOR, true);
	}


	//加载捐兵字库
	script[MAX_THREAD_COUNT].SetLog("加载捐兵字库", true, BLACKCOLOR, true);

	path =GetExePath();
	path += "Dict";
	path += "\\coc_donate.txt";
	string result = script[0].coc.ReadFileWithoutPath(path);
	_split(result, vstr1, "\r\n");
	for (int i = 0; i < vstr1.size(); i++)
	{
		str_show = vstr1[i].c_str();
		_split(vstr1[i], vstr2, "$");
		pag5.InputKeyWord.AddString(vstr2[1].c_str());
	}
	
	script[MAX_THREAD_COUNT].SetLog("加载完成", true, BLACKCOLOR, true);
	/*lua*/
	lua_init(0);
	/*设置全局路径*/
	gcurrent_path = GetExePath();

	/*加载lua攻击脚本*/
	path = GetExePath();
	path += "Function\\Lua";
	path += "\\";
	script[0].coc.SearchStr.Empty();
	script[0].coc.FileSearch(path, "*Attack.lua");
	str_show = script[0].coc.SearchStr;
	_split(str_show.GetBuffer(), vstr1, "|");
	str_show.ReleaseBuffer();
	if (vstr1.size() > 0)
	{
		for (int i = 0; i < vstr1.size(); i++)
		{
			pag4.m_lua_list.AddString(vstr1[i].c_str());
		}
	}
	SetTimer(1, 1000, NULL);
	SetTimer(2, 500, NULL);
	IsInit = true;
	OnBnClickedResetSize();
	/*加载配置文件，刷新设置*/
	path = GetExePath() + "Config.ini";
	script[0].coc.LoadSets(path);
	UpdateWindowSet();
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
		pag9.ShowWindow(false);
		pag10.ShowWindow(true);

		break;

	}

	*pResult = 0;
}


void CcocBotDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (glua) { lua_close(glua); glua = NULL; }
	CbotFunction bot;
	bot.SetPath(GetExePath());
	SaveConfig();
	//bot.WriteFile(_T("BotSet.cbt"), save_str);

	if (pag1.app_player_type == APP_PLAYER_BLUESTACKS)
	{
		StopOneScript(&script[0]);
	}
	else
	{
		for (int index = 0; index < MAX_THREAD_COUNT; index++)
		{
			if (m_list.GetCheck(index) == 0) continue;
			StopOneScript(&script[index]);
		}
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


LRESULT CcocBotDlg::OnLoadOutConfig(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	CbotFunction* bot = new CbotFunction;
	path = GetExePath();
	bot->SetPath(path);
	SaveConfig();
	CString filename;
	pag1.LoadOutSet.GetWindowTextA(filename);
	if (filename.GetLength() < 1)
	{
		filename = "导出";
		filename += bot->GetNowTime(3);
	}

	filename += ".ini";
	SaveConfig(path + filename);
	delete bot;
	path += filename;
	MessageBox("导出成功，路径是：" + path, "提示", MB_OK);
	return NULL;

}


LRESULT CcocBotDlg::OnLoadInConfig(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_config, file_path;
	pag1.LoadInSet.GetWindowTextA(file_path);
	if (file_path.GetLength() > 3)
	{
		if (file_path.Right(4) != ".ini")
		{
			MessageBox("错误的文件" + file_path, "提示", MB_OK);
		}
		else
		{
			script[0].coc.LoadSets(file_path);
			UpdateWindowSet();
			AfxMessageBox("导入配置成功！");
		}
	}

	return NULL;
}


void CcocBotDlg::InitlizeList(void)
{
	CString str;
	//****************** donate keyword list **************//
	pag5.ListKeyWord.SetExtendedStyle(LVS_ICON | LVS_REPORT | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	pag5.ListKeyWord.InsertColumn(0, "选择", LVCFMT_CENTER, 50);
	pag5.ListKeyWord.InsertColumn(1, "关键词", LVCFMT_LEFT, 150);
	pag5.ListKeyWord.InsertColumn(2, "捐赠", LVCFMT_LEFT, 50);

	for (int i = 0; i < 21; i++)
	{
		str.Format("%d", i);
		pag5.ListKeyWord.InsertItem(i, str);
		pag5.ListKeyWord.SetItemText(i, 2, ARMYNAME[i]);
	}
	//************** loot **************//
	pag8.m_ListCtrl1.SetExtendedStyle(LVS_ICON | LVS_REPORT);
	pag8.m_ListCtrl1.InsertColumn(0, _T(""), LVCFMT_CENTER, 60);
	pag8.m_ListCtrl1.InsertColumn(1, _T("开始资源"), LVCFMT_RIGHT, 100);
	pag8.m_ListCtrl1.InsertColumn(2, _T("当前资源"), LVCFMT_RIGHT, 100);
	pag8.m_ListCtrl1.InsertColumn(3, _T("掠夺资源"), LVCFMT_RIGHT, 100);
	pag8.m_ListCtrl1.InsertColumn(4, _T("时均效率"), LVCFMT_RIGHT, 100);
	pag8.m_ListCtrl1.InsertColumn(5, _T("天均效率"), LVCFMT_RIGHT, 100);
	for (int i = 0; i < MAX_THREAD_COUNT * 3; i++)
	{
		i % 3 == 0 ? str.Format("主账号:%d", i / 3) : str.Format("子账号:%d", i % 3);
		i *= 5;
		pag8.m_ListCtrl1.InsertItem(0 + i, str);
		pag8.m_ListCtrl1.InsertItem(1 + i, "金币");
		pag8.m_ListCtrl1.InsertItem(2 + i, "圣水");
		pag8.m_ListCtrl1.InsertItem(3 + i, "黑油");
		pag8.m_ListCtrl1.InsertItem(4 + i, "奖杯");
		i = i / 5;
	}

	//MutliLog
	pag7.m_list1.SetExtendedStyle(LVS_ICON | LVS_REPORT | LVS_EX_CHECKBOXES);
	pag7.m_list1.InsertColumn(0, _T("选定"), LVCFMT_CENTER, 50);
	pag7.m_list1.InsertColumn(1, _T("版本"), LVCFMT_LEFT, 100);
	pag7.m_list1.InsertColumn(2, _T("配置路径"), LVCFMT_CENTER, 200);
	pag7.m_list1.InsertColumn(3, _T("序号"), LVCFMT_CENTER, 50);
	for (int i = 0; i < MAX_SWITCH_COUNT - 1; i++)
	{
		str.Format("%d", i + 1);
		pag7.m_list1.InsertItem(i, str);
	}
	pag7.Clear.AddString("重置所有");
	for (int i = 0; i < MAX_SWITCH_COUNT; i++)
	{
		str.Format("第 %d行", i);
		pag7.Clear.AddString(str);
	}
	//================list=============
	m_list.SetExtendedStyle(LVS_ICON | LVS_REPORT | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, "索引", LVCFMT_LEFT, 40);
	m_list.InsertColumn(1, "标题", LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, "配置文件", LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, "状态", LVCFMT_LEFT, 200);
	m_list.InsertColumn(4, "hParent", LVCFMT_LEFT, 100);
	for (int i = 0; i < MAX_THREAD_COUNT; i++)
	{
		str.Format("%d", i);
		m_list.InsertItem(i, str);
	}
	OnBnClickedUpdataList();
	m_list.SetCheck(0, 1);
}


void CcocBotDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str, WinText;

	CTime tm;
	DWORD bigTime = 0;
	tm = CTime::GetCurrentTime();
	CRect rectPicture;
	switch (nIDEvent)
	{
	case 1:
		if (script[0].IsThreadRun == true)
		{
			bigTime = (tm.GetDay() - script[0].coc.tm.GetDay()) * 86400 + (tm.GetHour() - script[0].coc.tm.GetHour()) * 3600
				+ (tm.GetMinute() - script[0].coc.tm.GetMinute()) * 60 + tm.GetSecond() - script[0].coc.tm.GetSecond();
			str.Format("运行时间：%d d %d h %d m %d s ", bigTime / 86400, (bigTime % 86400) / 3600, (bigTime % 3600) / 60, bigTime % 60);
			pag8.RunTime.SetWindowTextA(str);
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

		break;
	case 2:
		//*********** message call back *****************//
		if (true == IsInit)
		{
			IsInit = false;

		}

		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CcocBotDlg::OnScreenCapture()
{
	// TODO: 在此添加控件通知处理程序代码


	
}


void CcocBotDlg::OnBnClickedShowHideAppPlayer()
{
	// TODO: 在此添加控件通知处理程序代码
	CLSID clsid;
	CString str;
	bool hide = false;
	long x = -900, y = 0;;
	if (GetDlgItemText(IDC_SHOW_HIDE_WINDOW, str), str == "隐藏模拟器")
	{
		SetDlgItemText(IDC_SHOW_HIDE_WINDOW, "显示模拟器");
		hide = true;
	}
	else
	{
		SetDlgItemText(IDC_SHOW_HIDE_WINDOW, "隐藏模拟器");
		hide = false;
	}
	//MessageBox(str);
	CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	Cdmsoft dmx;
	dmx.CreateDispatch(clsid);
	CString winText;
	long window_hwnd = 0;
	int index = 0;
	switch (pag1.app_player_type)
	{
	case APP_PLAYER_BLUESTACKS:
		window_hwnd = dmx.FindWindow("", "BlueStacks App Player");
		if (window_hwnd > 0)
		{
			hide == true ? x = -900 : x = 0;
			dmx.MoveWindow(window_hwnd, x, 0);
		}
		break;
	case APP_PLAYER_LIGHTING:
		for (index = 0; index < MAX_THREAD_COUNT; index++)
		{
			if (m_list.GetItemText(index, 1).GetLength() < 1) continue;
			str = m_list.GetItemText(index, 4);
			window_hwnd = _ttoi(str);
			if (window_hwnd > 0)
			{
				hide == true ? x = -900 : x = index % 3 * 850, y = index / 3 * 667;
				dmx.MoveWindow(window_hwnd, x, 0);
			}
		}


		break;
	default:
		return;
		break;
	}

	dmx = NULL;
}


void CcocBotDlg::OnBnClickedStartStopBot()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (contorl_script == NOTSTART)
	{
		m_StartStopButton.EnableWindow(FALSE);
		script[0].scriptInfo = SCRIPT_STATE_IN_RUN;
		CString path;
		path = fbot.GetExePath();

		script[0].coc.SetPath(GetExePath() + "Config.ini");
		SaveConfig();//界面配
		if (pag1.app_player_type == APP_PLAYER_BLUESTACKS)
		{
			script[0].AppPlayerType = pag1.app_player_type;
			script[0].appPlayerInstallDir = app_player_bs_install_dir;
			StartOneScript(&script[0], 0);
		}
		else
		{
			for (int index = 0; index < MAX_THREAD_COUNT; index++)
			{
				if (m_list.GetCheck(index) == 0) continue;
				if (m_list.GetItemText(index, 1).GetLength() <= 0) continue; //模拟器未创建
				script[index].AppPlayerType = pag1.app_player_type;
				script[index].appPlayerInstallDir = app_player_ld_install_dir;
				str = m_list.GetItemText(index, 2);
				if (str.GetLength() < 4)
				{
					script[index].coc.SetPath(GetExePath() + "Config.ini");
				}
				else
				{
					script[index].coc.SetPath(str);
				}
				StartOneScript(&script[index], index);

			}
		}


		contorl_script = INRUN;
		m_StartStopButton.SetIcon(m_IconStop);
		m_StartStopButton.EnableWindow(TRUE);
		pag1.check_bs.EnableWindow(FALSE);
	}
	else
	{
		m_StartStopButton.EnableWindow(FALSE);
		contorl_script = STOP;
		if (pag1.app_player_type == APP_PLAYER_BLUESTACKS)
		{
			StopOneScript(&script[0]);
		}
		else
		{
			for (int index = 0; index < MAX_THREAD_COUNT; index++)
			{
				if (m_list.GetCheck(index) == 0) continue;
				StopOneScript(&script[index]);
			}
		}


		contorl_script = NOTSTART;
		m_StartStopButton.SetIcon(m_IconStart);
		m_StartStopButton.EnableWindow(TRUE);
	}
}


void CcocBotDlg::OnBnClickedPausebot()
{
	// TODO: 在此添加控件通知处理程序代码
	if (contorl_script == INRUN)
	{
		//pManageThread->SuspendThread();
		//pGameThread->SuspendThread();
		SuspendOneScript(&script[0]);
		contorl_script = PAUSE;
		SetDlgItemText(IDC_PAUSEBOT, "继续");
	}
	else if (contorl_script == PAUSE)
	{
		//pManageThread->ResumeThread();
		//pGameThread->ResumeThread();
		ResumOneScript(&script[0]);
		contorl_script = INRUN;
		SetDlgItemText(IDC_PAUSEBOT, "暂停");
	}
}


LRESULT CcocBotDlg::oneKeySet(WPARAM wParam, LPARAM lParam)
{
	CString str, winText;

	str = GetExePath();
	str += "常用配置\\";
	pag1.m_list.GetText(pag1.m_list.GetCurSel(), winText);
	str += winText;
	if (str.Find(".ini") <= 0)
	{
		AfxMessageBox("一键配置失败，请检查文件名是否正确");
	}
	else
	{
		script[0].coc.LoadSets(str);
		UpdateWindowSet();
		MessageBox("一键配置成功");
	}


	return 0;
}


LRESULT CcocBotDlg::SaveConfigInFile(WPARAM wParam, LPARAM lParam)
{
	SaveConfig();
	return NULL;
}


LRESULT CcocBotDlg::SetLog(WPARAM wParam, LPARAM lParam)
{
	if (pag9.m_notShowLog.GetCheck() == 1) return NULL;
	SEND_INFO* info = (SEND_INFO*)lParam;
	//coc.State_str = logStr;
	m_list.SetItemText(wParam, 3, info->logStr);
	if (wParam != 0) return NULL;
	CString strTime, keytime, WriteStr;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%y-%m-%d");
	keytime = tm.Format("%X");
	WriteStr = _T("[") + keytime + _T("]") + info->logStr + _T("\r\n");
	if (info->IsShow == true)
	{
		//***********RICH EDIT********************//
		CHARFORMAT cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE;
		cf.dwEffects = CFM_UNDERLINE;
		int nLineCounts = pag9.m_RichEdit1.GetLineCount() - 1;
		cf.crTextColor = info->color;
		cf.yHeight = 12 * 12;
		strcpy_s(cf.szFaceName, 32, _T("宋体"));
		WriteStr = _T("[") + keytime + _T("]") + info->logStr + _T("\r\n");
		if (nLineCounts >= 1000)
		{
			pag9.m_RichEdit1.SetWindowText("");
		}
		pag9.m_RichEdit1.SetSel(-1, -1);
		pag9.m_RichEdit1.ReplaceSel(WriteStr, 0);
		int lineStart = pag9.m_RichEdit1.LineIndex(nLineCounts);//取第x行的第一个字符的索引
		int lineEnd = pag9.m_RichEdit1.LineIndex(nLineCounts + 1) - 1;//取第x行的最后一个字符的索引——用第x+1行的第一个索引减1来实现
		pag9.m_RichEdit1.SetSel(lineStart, lineEnd);//选取第一行字符
		pag9.m_RichEdit1.SetSelectionCharFormat(cf);//设置颜色
		pag9.m_RichEdit1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	if (info->IsSave == true)
	{
		CString path;
		path = GetExePath();
		path += "Log\\";
		path += strTime;
		path += ".log";
		CFile file_log(path, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		file_log.SeekToEnd();
		file_log.Write(WriteStr, strlen(WriteStr));
		file_log.Close();
	}

	return NULL;
}


LRESULT CcocBotDlg::Statistics(WPARAM wParam, LPARAM lParam)
{
	long LootGold = 0, LootElixir = 0, LootDarkElixir = 0, LootTroophs = 0;
	long RunTime = 0;
	int py = 0;
	CGameInfo* LootRecord = (CGameInfo*)wParam;
	int index = lParam;
	py = index * 5;
	index = index % 3;
	LootGold = LootRecord->GetLootGold();
	LootElixir = LootRecord->GetLootElixir();
	LootDarkElixir = LootRecord->GetLootDarkElixir();
	LootTroophs = LootRecord->GetLootTroophs();
	RunTime = LootRecord->GetRunTime();
	if (RunTime == 0) RunTime = 1;
	CString str[5] = {};
	//开始
	str[0].Format("%ld", LootRecord->StartGold);
	str[1].Format("%ld", LootRecord->StartElixir);
	str[2].Format("%ld", LootRecord->StartDarkElixir);
	str[3].Format("%ld", LootRecord->StartTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 1, str[i]);
	}
	//当前
	str[0].Format("%ld", LootRecord->NowGold);
	str[1].Format("%ld", LootRecord->NowElixir);
	str[2].Format("%ld", LootRecord->NowDarkElixir);
	str[3].Format("%ld", LootRecord->NowTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 2, str[i]);
	}
	//获取
	str[0].Format("%ld", LootGold);
	str[1].Format("%ld", LootElixir);
	str[2].Format("%ld", LootDarkElixir);
	str[3].Format("%ld", LootTroophs);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 3, str[i]);
	}
	//时均
	str[0].Format("%ld", LootGold * 60 / RunTime);
	str[1].Format("%ld", LootElixir * 60 / RunTime);
	str[2].Format("%ld", LootDarkElixir * 60 / RunTime);
	str[3].Format("%ld", LootTroophs * 60 / RunTime);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 4, str[i]);
	}
	//天均
	str[0].Format("%ld", (LootGold * 24 / RunTime) * 60);
	str[1].Format("%ld", (LootElixir * 24 / RunTime) * 60);
	str[2].Format("%ld", (LootDarkElixir * 24 / RunTime) * 60);
	str[3].Format("%ld", (LootTroophs * 24 / RunTime) * 60);
	for (int i = 0; i <= 3; i++)
	{
		pag8.m_ListCtrl1.SetItemText(i + 1 + py, 5, str[i]);
	}
	return 0;
}


LRESULT CcocBotDlg::UpDataAppPlayerInfo(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedUpdataList();
	return NULL;
}


LRESULT CcocBotDlg::SelectAppPlayer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0:
		if (app_player_bs_install_dir.GetLength() < 5)
		{
			MessageBox("你的电脑未安装BS模拟器.请先安装！", "错误", MB_ICONERROR);
		}
		else if (PathFileExists(app_player_bs_install_dir) == FALSE)
		{
			MessageBox("BS模拟器路径错误！", "错误", MB_ICONERROR);
		}
		else
		{
			MessageBox("你的电脑已安装BS模拟器.此模拟器仅支持单开！", "提示", MB_ICONINFORMATION);
		}

		break;
	case 1:
		if (app_player_ld_install_dir.GetLength() < 5)
		{
			MessageBox("你的电脑未安装雷电模拟器.请先安装！", "错误", MB_ICONERROR);
		}
		else if (PathFileExists(app_player_ld_install_dir) == FALSE)
		{
			MessageBox("雷电模拟器路径错误！", "错误", MB_ICONERROR);
		}
		else
		{
			MessageBox("你的电脑已安装雷电模拟器.此模拟器支持多开！", "提示", MB_ICONINFORMATION);
		}
		break;
	default:
		break;
	}
	return NULL;
}


LRESULT CcocBotDlg::OnShowGraphic(WPARAM wParam, LPARAM lParam)
{
	m_graphic.ShowWindow(TRUE);
	return NULL;
}


void CcocBotDlg::OnBnClickedResetSize()
{
	// TODO: 在此添加控件通知处理程序代码

	CString btn_title;
	GetDlgItemText(IDC_RESET_SIZE, btn_title);
	CRect tmp;
	GetDlgItem(IDC_LIST1)->GetClientRect(tmp);
	if (btn_title == "我要多开")
	{
		SetDlgItemText(IDC_RESET_SIZE, "折叠");
		SetWindowPos(NULL, 0, 0, rect_max.Width(), rect_max.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetDlgItemText(IDC_RESET_SIZE, "我要多开");
		SetWindowPos(NULL, 0, 0, rect_max.Width(), rect_max.Height() - tmp.Height() - 20, SWP_NOMOVE | SWP_NOZORDER);
	}
}


void CcocBotDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pMListView = (NM_LISTVIEW*)pNMHDR;
	row = pMListView->iItem;
	col = pMListView->iSubItem;
	CMenu  *pContextMenu = menu.GetSubMenu(0); //获取第一个弹出菜单，所以第一个菜单必须有子菜单 
	CPoint point1;//定义一个用于确定光标位置的位置  
	GetCursorPos(&point1);//获取当前光标的位置，以便使得菜单可以跟随光标  
	if (row >= MAX_THREAD_COUNT)
	{
		return;
	}

	long appHwnd = 0;
	appHwnd = _ttoi(m_list.GetItemText(row, 3));

	if (script[row].IsThreadRun == false)
	{
		menu.EnableMenuItem(IDM_START, MF_GRAYED);
		menu.EnableMenuItem(IDM_STOP, MF_ENABLED);
		menu.EnableMenuItem(IDM_PAUSE, MF_ENABLED);
	}
	else
	{
		menu.EnableMenuItem(IDM_START, MF_ENABLED);
		menu.EnableMenuItem(IDM_STOP, MF_GRAYED);
		menu.EnableMenuItem(IDM_PAUSE, MF_GRAYED);
	}
	::SendMessage(GetSafeHwnd(), WM_BINDSET_SAVE_CONFIG, 0, 0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this); //在指定位置显示弹出菜单
	*pResult = 0;

	*pResult = 0;
}


void CcocBotDlg::OnLaunch()
{
	// TODO: 在此添加命令处理程序代码
	script[MAX_THREAD_COUNT].LaunchAppPlayer(row);
}


void CcocBotDlg::OnQuit()
{
	// TODO: 在此添加命令处理程序代码
	script[MAX_THREAD_COUNT].QuitAppPlayer(row);
}


void CcocBotDlg::OnStartOneScript()
{
	// TODO: 在此添加命令处理程序代码
	if (true == script[row].IsThreadRun)
	{
		MessageBox("已运行");
		return;
	}
	CString str_cfg;
	str_cfg = m_list.GetItemText(row, 2);
	if (PathFileExists(str_cfg) == false)
	{
		//配置文件不存在，请重新设置！
		MessageBox("配置文件不存在，请重新设置！");
		return;
	}
	StartOneScript(&script[row], row, str_cfg);
}


void CcocBotDlg::OnPauseOneScript()
{
	// TODO: 在此添加命令处理程序代码
	CString str;
	menu.GetMenuString(row, str, MF_BYCOMMAND);
	AfxMessageBox(str);

}


void CcocBotDlg::OnStopOneScript()
{
	// TODO: 在此添加命令处理程序代码
	if (true == script[row].IsThreadRun)
		StopOneScript(&script[row]);
}


void CcocBotDlg::OnBnClickedUpdataList()
{
	// TODO: 在此添加控件通知处理程序代码
	//首次加载包含的模拟器
	CString path, str;
	path = GetExePath();
	path += "Config.ini";
	const int max_size = 512;
	char buffer[max_size] = { 0 };
	using namespace std;
	vector<string> vstr1, vstr2;
	if (pag1.app_player_type == APP_PLAYER_LIGHTING)
	{
		if (app_player_ld_install_dir.GetLength() < 5) return;
		script[MAX_THREAD_COUNT].adb.Start(app_player_ld_install_dir + "\\dnconsole.exe list2");
		script[MAX_THREAD_COUNT].adb.Stop();
		str = script[MAX_THREAD_COUNT].adb.GetOutput();
		if (str.GetLength() <= 4) return;
		_split(str.GetBuffer(), vstr1, "\n");
		str.ReleaseBuffer();
		int n = 0;
		for (int i = 0; i < vstr1.size(); i++)
		{
			if (vstr1[i].length() <= 1) break;
			_split(vstr1[i], vstr2, ",");
			n = _ttoi(vstr2[0].c_str());
			/*for (int j = 1; j < vstr2.Size(); j++)
			{
			m_list.SetItemText(n, j, vstr2[j]);
			}*/
			m_list.SetItemText(n, 0, vstr2[0].c_str());/* index */
			m_list.SetItemText(n, 1, vstr2[1].c_str());/* title */
			m_list.SetItemText(n, 4, vstr2[2].c_str());/* title */
		}
	}
}


void CcocBotDlg::OnSetConfig()
{
	// TODO: 在此添加命令处理程序代码
	CbotFunction bot;
	CString  ret;
	ret = bot.SelectFile("");
	m_list.SetItemText(row, 2, ret);
}
