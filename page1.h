#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// page1 �Ի���

class page1 : public CDialog
{
	DECLARE_DYNAMIC(page1)

public:
	page1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// xuke
	CEdit license;
	// ģ����
	CComboBox BluestacksOrOthers;
	// ��Ϸ����
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
