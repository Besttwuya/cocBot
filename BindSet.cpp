// BindSet.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "BindSet.h"
#include "afxdialogex.h"


// BindSet 对话框

IMPLEMENT_DYNAMIC(BindSet, CDialogEx)

BindSet::BindSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG11, pParent)
{

	EnableAutomation();

}

BindSet::~BindSet()
{
}

void BindSet::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void BindSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, display);
	DDX_Control(pDX, IDC_COMBO2, mouse);
	DDX_Control(pDX, IDC_COMBO3, keypad);
	DDX_Control(pDX, IDC_COMBO4, mode);
	DDX_Control(pDX, IDC_COMBO5, public_);
	DDX_Control(pDX, IDC_CHECK1, IsBindWindowEx);
	DDX_Control(pDX, IDC_CHECK2, IsUserBind);
	DDX_Control(pDX, IDC_EDIT1, AdbPath);
}


BEGIN_MESSAGE_MAP(BindSet, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &BindSet::OnOpen)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(BindSet, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IBindSet 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {6ED328B8-41A0-47CD-80BE-3FFFBA82EA9C}
static const IID IID_IBindSet =
{ 0x6ED328B8, 0x41A0, 0x47CD, { 0x80, 0xBE, 0x3F, 0xFF, 0xBA, 0x82, 0xEA, 0x9C } };

BEGIN_INTERFACE_MAP(BindSet, CDialogEx)
	INTERFACE_PART(BindSet, IID_IBindSet, Dispatch)
END_INTERFACE_MAP()


// BindSet 消息处理程序


void BindSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void BindSet::OnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("应用程序(*.exe)|*.exe||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK  == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath  = fileDlg.GetPathName();
		AdbPath.SetWindowTextA(strFilePath);
	}
	
}
