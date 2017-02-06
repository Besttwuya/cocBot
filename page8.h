#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// page8 对话框

class page8 : public CDialog
{
	DECLARE_DYNAMIC(page8)

public:
	page8(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page8();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl1;
	CStatic RunTime;
	CStatic AttackCount;
	CStatic SearchCount;
	// NowLog
	CStatic NowLog;
	CStatic m_ThreadCount;
};
