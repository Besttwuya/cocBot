#pragma once
#include "afxwin.h"


// page10 对话框

class page10 : public CDialog
{
	DECLARE_DYNAMIC(page10)

public:
	page10(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page10();

// 对话框数据
	enum { IDD = IDD_DIALOG10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// page10 updaterecord
	
	CStatic Instruction;
	afx_msg void OnDownload();
};
