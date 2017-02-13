
// cocbotDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ConnectServer.h"
#include "afxwin.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "page5.h"
#include "page6.h"
#include "page7.h"
#include "page8.h"
#include "page9.h"
#include "page10.h"
#include "BindSet.h"
#include "Script.h"
#define POINT_COUNT 100 
// CnewcocbotDlg 对话框
class CcocBotDlg : public CDialogEx
{
// 构造
public:
	CcocBotDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CcocBotDlg();                       // 标准析构函数
	
	//global
	CString bot_version;
	int   m_nzValues[POINT_COUNT];  
// 对话框数据
	enum { IDD = IDD_NEWCOCBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	SOCKET m_socket;
	BOOL InitSocket();
	struct RECVPARAM
	{
		SOCKET sock;	//已创建的套接字
		HWND hwnd;		//对话框句柄
	};
	static DWORD WINAPI RecvProc(LPVOID lpParameter);


// 实现
protected:
	HICON m_hIcon;
	HICON m_Button1;
	HICON m_Button2;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CMyTabCtrl main_tab;
	CTabCtrl main_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStart();
	afx_msg void OnEndBot();
	afx_msg void OnHideWindow();
	afx_msg void OnShowWindow();
	afx_msg void OnClose();
	CStatic State;
	void OnLoadOutConfig();
	void OnLoadInConfig();
	// OnInitlizeList
	void InitlizeList(void);
	// Variables
	void InitilzieColor(void);
	// CButton
	CButton m_Start;
	// CButton
	CButton m_Stop;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnScreenCapture();
	bool RegDm(void);
	void DrawWave(CDC* pDC,CRect &rectPicture);
	afx_msg void OnSetSize();
private:
	bool IsInit;
public:
private:
	CString m_OldState;
public:
	CStatic m_Show;
	void gameShow();
};
