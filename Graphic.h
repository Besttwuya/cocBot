#pragma once

#include <fstream>
#include <vector>
#include <string>
// Graphic �Ի���

class Graphic : public CDialogEx
{
	DECLARE_DYNAMIC(Graphic)

public:
	Graphic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Graphic();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPHIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	std::vector<int>vpos_x;
	std::vector<int>vpos_y;
	afx_msg void OnBnClickedLoadPos();
	afx_msg void OnPaint();
};
