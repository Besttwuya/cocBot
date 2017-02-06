#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// BindSet 对话框

class BindSet : public CDialogEx
{
	DECLARE_DYNAMIC(BindSet)

public:
	BindSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BindSet();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnClose();
public:
	bool IsShow;
	CComboBox display;
	CComboBox mouse;
	CComboBox keypad;
	CComboBox mode;
	CComboBox public_;
	CButton IsBindWindowEx;
	CButton IsUserBind;
	afx_msg void OnOpen();
	CEdit AdbPath;
};
