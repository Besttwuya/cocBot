// page8.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "page8.h"
#include "afxdialogex.h"


// page8 �Ի���

IMPLEMENT_DYNAMIC(page8, CDialog)

page8::page8(CWnd* pParent /*=NULL*/)
	: CDialog(page8::IDD, pParent)
{

}

page8::~page8()
{
}

void page8::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl1);
	DDX_Control(pDX, IDC_RunTime, RunTime);
	DDX_Control(pDX, IDC_AttackCount, AttackCount);
	DDX_Control(pDX, IDC_SearchCount, SearchCount);
	DDX_Control(pDX, IDC_THREADCOUNT, m_ThreadCount);
}


BEGIN_MESSAGE_MAP(page8, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page8 ��Ϣ�������


void page8::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}
