// page10.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page10.h"
#include "afxdialogex.h"


// page10 对话框

IMPLEMENT_DYNAMIC(page10, CDialog)

page10::page10(CWnd* pParent /*=NULL*/)
	: CDialog(page10::IDD, pParent)

{

}

page10::~page10()
{
}

void page10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_State, Instruction);
	
}


BEGIN_MESSAGE_MAP(page10, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &page10::OnDownload)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page10 消息处理程序





void page10::OnDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	//MFC    
	//用默认浏览器打开网页  
	//如果找不到默认浏览器，则默认用IE打开  
	ShellExecute(NULL, _T("open"), _T("https://pan.baidu.com/s/1i5bmWXf"), NULL, NULL, SW_SHOWNORMAL);//
}


void page10::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}
