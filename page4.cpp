// page4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "page4.h"
#include "afxdialogex.h"


// page4 �Ի���

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
	DDX_Control(pDX, IDC_COMBO6, attackCount);
	DDX_Control(pDX, IDC_ATTACKGRAD, AttackGird);
	DDX_Control(pDX, IDC_LUA_LIST, m_lua_list);
}


BEGIN_MESSAGE_MAP(page4, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page4 ��Ϣ�������





void page4::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}
