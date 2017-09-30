#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// page1 对话框

class page1 : public CDialogEx
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
	CEdit LoadOutSet;
	
	
	afx_msg void OnBsOrOtherChange();
	afx_msg void OnLoadInConfig();
	afx_msg void OnLoadOutConfig();
	CEdit LoadInSet;
	afx_msg void OnSelectFile();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtQuickset();
	HWND hParent;//父窗口句柄
	CComboBox townLevel;
	CButton check_bs;
	afx_msg void OnBnClickedCheckBs();
	afx_msg void OnBnClickedCheckLd();
	BOOL app_player_type;
	CListBox m_list;
};
