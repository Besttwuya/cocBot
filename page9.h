#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// page9 �Ի���

class page9 : public CDialogEx
{
	DECLARE_DYNAMIC(page9)

public:
	page9(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page9();

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_RichEdit1;

	CProgressCtrl m_progress;
	afx_msg void OnPaint();
	CButton m_notShowLog;
};
