// page9.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page9.h"
#include "afxdialogex.h"


// page9 对话框

IMPLEMENT_DYNAMIC(page9, CDialogEx)

page9::page9(CWnd* pParent /*=NULL*/)
	: CDialogEx(page9::IDD, pParent)
{

}

page9::~page9()
{
}

void page9::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEdit1);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_NOTSHOWLOG, m_notShowLog);
}


BEGIN_MESSAGE_MAP(page9, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page9 消息处理程序


void page9::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}
