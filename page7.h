#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxvslistbox.h"
#include "afxcmn.h"


// page7 �Ի���

class page7 : public CDialog
{
	DECLARE_DYNAMIC(page7)

public:
	page7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page7();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// screen shoot
	CButton DeBugSearchShoot;
	CButton DebugLocateAD;
	// SetShowErrorMsg
	CButton SetShowErrorMsg;
	// SwitchMode
	CComboBox SwitchModeVersion_1;
	// SwitchMode
	CButton IsSwitchMode;
	// SwitchMode
	// SwitchMode
	afx_msg void OnDisableSetWindowSize();
	// DisableSetWindowSize
	CButton DisableSetWindowSize;
	afx_msg void OnBindWindowSet();
public:
	bool IsShowBindSetWindow;
	afx_msg void OnOpen1();
	CEdit m_edit1;
	CListCtrl m_list1;
	afx_msg void OnAdd();
	CComboBox Clear;
	afx_msg void OnClear();
};
