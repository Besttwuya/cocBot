#pragma once
#include "afxwin.h"


// page10 �Ի���

class page10 : public CDialog
{
	DECLARE_DYNAMIC(page10)

public:
	page10(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~page10();

// �Ի�������
	enum { IDD = IDD_DIALOG10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// page10 updaterecord
	
	CStatic Instruction;
	afx_msg void OnDownload();
};
