// page4.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page4.h"
#include "afxdialogex.h"


// page4 对话框

IMPLEMENT_DYNAMIC(page4, CDialogEx)

page4::page4(CWnd* pParent /*=NULL*/)
	: CDialogEx(page4::IDD, pParent)
{

}

page4::~page4()
{
}

void page4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, AttackDeadbaseStyle);
	DDX_Control(pDX, IDC_COMBO2, AttackActivebaseStyle);
	DDX_Control(pDX, IDC_EDIT5, AttackLingtingMinDarkElixir);
	DDX_Control(pDX, IDC_COMBO3, AttackMinDarkElixirLevel);
	DDX_Control(pDX, IDC_CHECK1, AttackIsExitWithoutResource);
	DDX_Control(pDX, IDC_EDIT1, AttackMinWaitTime);
	DDX_Control(pDX, IDC_CHECK2, AttackIsExitWhenLittleResource);
	DDX_Control(pDX, IDC_EDIT2, AttackExitGold);
	DDX_Control(pDX, IDC_EDIT3, AttackExitElixir);
	DDX_Control(pDX, IDC_EDIT4, AttackExitDarkElixir);
	DDX_Control(pDX, IDC_COMBO4, UseLightingCount);
	DDX_Control(pDX, IDC_COMBO5, AttackSpeed);
}


BEGIN_MESSAGE_MAP(page4, CDialogEx)
END_MESSAGE_MAP()


// page4 消息处理程序



