#pragma once
#include "afxwin.h"


// page6 对话框

class page6 : public CDialogEx
{
	DECLARE_DYNAMIC(page6)

public:
	page6(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page6();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit UpgradeWallMinGold;
	CEdit UpgradeWallMinElixir;
	CComboBox UpgradeWallUseType;
	CComboBox UpgradeWallLevel;
	CEdit UpgradeHeroMinDarkElixir;
	CComboBox UpgradeHeroType;
	afx_msg void OnPaint();
};
