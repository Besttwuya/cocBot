#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// page1 对话框

class page1 : public CDialog
{
	DECLARE_DYNAMIC(page1)

public:
	page1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// xuke
	CEdit license;
	// 模拟器
	CComboBox BluestacksOrOthers;
	// 游戏区服
	CComboBox GameVersion;
	CButton OffLine;
	CButton RequestArmy;
	CButton Attack;
	CButton DonateArmy;
	CButton UpgradeWall;
	CButton UpgradeHeros;
	CButton ControlTroophs;
	CButton LightingDarkElixir;
	CButton RemoveTree;
	CButton RearmAll;
	CComboBox QuickSet;
	CEdit QuickSetShow;
	CEdit LoadOutSet;
	
	CComboBox ServerPort;
	afx_msg void OnBsOrOtherChange();
	CEdit BsOrOtherWindowText;
	CComboBox BsOrOtherNo;
	afx_msg void OnLoadInConfig();
	bool IsLoadInConfig;
	bool IsLoadOutConfig;
	afx_msg void OnLoadOutConfig();
	CEdit LoadInSet;
	afx_msg void OnSelectFile();
};
