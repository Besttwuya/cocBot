#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// page4 �Ի���

class page4 : public CDialogEx
{
	DECLARE_DYNAMIC(page4)

public:
	page4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page4();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
