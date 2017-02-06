#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// page4 对话框

class page4 : public CDialogEx
{
	DECLARE_DYNAMIC(page4)

public:
	page4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~page4();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox AttackDeadbaseStyle;
	CComboBox AttackActivebaseStyle;
	CEdit AttackLingtingMinDarkElixir;
	CComboBox AttackMinDarkElixirLevel;
	CButton AttackIsExitWithoutResource;
	CEdit AttackMinWaitTime;
	CButton AttackIsExitWhenLittleResource;
	CEdit AttackExitGold;
	CEdit AttackExitElixir;
	CEdit AttackExitDarkElixir;
	
	// attack dark elixir
	CComboBox UseLightingCount;
	//**************** list ********************//
	CComboBox AttackSpeed;
};
