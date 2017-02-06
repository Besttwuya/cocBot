#pragma once
#include "afxwin.h"


// page3 对话框

class page3 : public CDialog
{
	DECLARE_DYNAMIC(page3)

public:
	page3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page3();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit MinTroopRet;
	CButton IsWaitBarbarinKing;
	CButton IsWaitArcherKing;
	// yongwang
	CButton IsWaitGrandKing;
	CButton IsWaitClanCastleTroopsAndSpells;
	CEdit MinTroophs;
	CEdit MaxTroophs;
	CEdit SearchMinGold;
	CEdit SearchMinElixir;
	CEdit SearchMinDarkElixir;
	CComboBox SearchType;
	CComboBox SearchDeadbaseGoldCollector;
	CComboBox SearchDeadbaseElixir;
	CButton ArcherTower;
	CComboBox ArcherTowerLevel;
	CButton Mortar;
	CComboBox MortarLevel;
	CButton WizardTower;
	CComboBox WizardTowerLevel;
	CButton AirDefense;
	CComboBox AirDefenseLevel;
	CButton XBow;
	CComboBox XBowLevel;
	CButton Inferno;
	CComboBox InfernoLevel;
	CButton EagleArtillery;
	CComboBox EagleArtilleryLevel;
	CEdit SearchDealy;
	CEdit SearchWait;
	CEdit SearchMaxCount;
	CButton IsWaitSpell;
};
