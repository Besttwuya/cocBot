#pragma once
#include "afxwin.h"


// page2 对话框

class page2 : public CDialog
{
	DECLARE_DYNAMIC(page2)

public:
	page2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox TrainArmyStyle;
	CComboBox IsClearArmy;
	CComboBox IsAddArmy;
	CEdit Barbarin;
	CEdit Archer;
	CEdit Giant;
	CEdit Goblin;
	CEdit WallBreaker;
	CEdit Ballon;
	CEdit Wizard;
	CEdit Healer;
	CEdit Dragon;
	CEdit Peka;
	CEdit BabyDragon;
	CEdit Miner;
	CEdit Minion;
	CEdit HogRider;
	// wushen
	CEdit Valkyrie;
	CEdit Golem;
	CEdit Witch;
	CEdit LavaHound;
	CEdit BowLer;
	CEdit LightingSpell;
	CEdit HealingSpell;
	CEdit RageSpell;
	CEdit JumpSpell;
	CEdit FreezeSpell;
	CEdit CloneSpell;
	CEdit PoisonSpell;
	CEdit EarthquakeSpell;
	CEdit HasteSpell;
	CEdit SkeletonSpell;
	// army train speed up
	CButton IsSpeedUp;
	// SpeedUp train
	CEdit SpeedUpBegin;
	// SpeedUp train
	CEdit SpeedUpEnd;
	CStatic AllCount;
private:
	CString m_strLine;
	CPoint m_ptOrigin;
public:
	afx_msg void OnEnChangeEdit1();
	void TotalInput();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnEnChangeEdit19();
};
