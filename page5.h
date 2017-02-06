#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// page5 对话框

class page5 : public CDialogEx
{
	DECLARE_DYNAMIC(page5)

public:
	page5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page5();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton IsDonateSendGetRet;
	CButton IsDonateNotFull;
	CEdit DonateMinSendGetRet;
	CComboBox DonateType;
	CEdit DonateCount;
	CEdit DonateDealy;
	CButton IsBarbarin;
	CButton IsArcher;
	CButton IsGiant;
	CButton IsGoblin;
	CButton IsWallBreaker;
	CButton IsBallon;
	CButton IsWizard;
	CButton IsHealer;
	CButton IsDragon;
	CButton IsPeka;
	CButton IsBabyDragon;
	CButton IsMiner;
	CButton IsMinion;
	CButton IsHogRider;
	// donate
	CButton IsValkyrie;
	CButton IsGolem;
	CButton IsWitch;
	CButton IsLavaHound;
	CButton IsBower;
	CButton IsPoison;
	CButton IsEarthquake;
	CButton IsHaste;
	CButton IsSkeleton;
	afx_msg void OnAddKeyWord();
	afx_msg void OnClearKeyWord();
	// KeyWord
	// KeyWord
	CListCtrl ListKeyWord;
	// KeyWordToDonate
	CComboBox KeyWordToDonate;
	CComboBox InputKeyWord;
};
