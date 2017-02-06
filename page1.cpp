// page1.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"

#include "page1.h"

#include "afxdialogex.h"


// page1 对话框

IMPLEMENT_DYNAMIC(page1, CDialog)

page1::page1(CWnd* pParent /*=NULL*/)
	: CDialog(page1::IDD, pParent)
{

}

page1::~page1()
{
}

void page1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, license);
	DDX_Control(pDX, IDC_COMBO1, BluestacksOrOthers);
	DDX_Control(pDX, IDC_COMBO2, GameVersion);
	DDX_Control(pDX, IDC_CHECK1, OffLine);
	DDX_Control(pDX, IDC_CHECK2, RequestArmy);
	DDX_Control(pDX, IDC_CHECK3, Attack);
	DDX_Control(pDX, IDC_CHECK4, DonateArmy);
	DDX_Control(pDX, IDC_CHECK5, UpgradeWall);
	DDX_Control(pDX, IDC_CHECK6, UpgradeHeros);
	DDX_Control(pDX, IDC_CHECK7, ControlTroophs);
	DDX_Control(pDX, IDC_CHECK8, LightingDarkElixir);
	DDX_Control(pDX, IDC_CHECK9, RemoveTree);
	DDX_Control(pDX, IDC_CHECK10, RearmAll);
	DDX_Control(pDX, IDC_COMBO3, QuickSet);
	DDX_Control(pDX, IDC_EDIT2, QuickSetShow);
	DDX_Control(pDX, IDC_EDIT3, LoadOutSet);
	DDX_Control(pDX, IDC_COMBO4, ServerPort);
	DDX_Control(pDX, IDC_EDIT4, BsOrOtherWindowText);
	DDX_Control(pDX, IDC_COMBO5, BsOrOtherNo);

	DDX_Control(pDX, IDC_EDIT5, LoadInSet);
}


BEGIN_MESSAGE_MAP(page1, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO1, &page1::OnBsOrOtherChange)
	ON_BN_CLICKED(IDC_BUTTON10, &page1::OnLoadInConfig)
	ON_BN_CLICKED(IDC_BUTTON11, &page1::OnLoadOutConfig)
	ON_BN_CLICKED(IDC_BUTTON2, &page1::OnSelectFile)
END_MESSAGE_MAP()


// page1 消息处理程序


void page1::OnBsOrOtherChange()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (BluestacksOrOthers.GetCurSel())
	{
	case 0:
		BsOrOtherWindowText.EnableWindow(FALSE);
		break;
	case 1:
		BsOrOtherWindowText.EnableWindow(TRUE);
		break;
	case 2:
		BsOrOtherWindowText.EnableWindow(TRUE);
		break;
	default:
		//BsOrOtherWindowText.EnableWindow(FALSE);
		break;
	}
	
}


void page1::OnLoadInConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	IsLoadInConfig = true;
}


void page1::OnLoadOutConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	IsLoadOutConfig = true;
}


void page1::OnSelectFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CbotFunction* bot = new CbotFunction;
	CString filename;
	filename= bot->SelectFile("配置文件(*.cbt)|*.cbt||");
	delete bot;
	LoadInSet.SetWindowTextA(filename);
	
}
