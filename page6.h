#pragma once
#include "afxwin.h"


// page6 �Ի���

class page6 : public CDialogEx
{
	DECLARE_DYNAMIC(page6)

public:
	page6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page6();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
