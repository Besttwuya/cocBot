#pragma once

#include <fstream>
#include <vector>
#include <string>
// Graphic 对话框

class Graphic : public CDialogEx
{
	DECLARE_DYNAMIC(Graphic)

public:
	Graphic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Graphic();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPHIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	std::vector<int>vpos_x;
	std::vector<int>vpos_y;
	afx_msg void OnBnClickedLoadPos();
	afx_msg void OnPaint();
};
