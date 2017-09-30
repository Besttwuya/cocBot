
// cocbotDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
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
#include "Graphic.h"
#include "Script.h" 
// CcocBotDlg 对话框
class CcocBotDlg : public CDialogEx
{
// 构造
public:
	CcocBotDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CcocBotDlg();                       // 标准析构函数
// 对话框数据
	enum { IDD = IDD_NEWCOCBOT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	SOCKET m_socket;
	CTabCtrl main_tab;
	CListCtrl m_list;
	CButton m_StartStopButton;
	CString app_player_bs_install_dir, app_player_ld_install_dir;//bs,雷电模拟器安装路径/根目录
	page1 pag1;//page class
	page2 pag2;
	page3 pag3;
	page4 pag4;
	page5 pag5;
	page6 pag6;
	page7 pag7;
	page8 pag8;
	page9 pag9;
	page10 pag10;
	Graphic m_graphic;
	bool IsInit;
	
	SCRIPT_STATE contorl_script = SCRIPT_STATE::NOTSTART;
// 实现
protected:
	HICON m_hIcon; //图片
	HICON m_IconStart;
	HICON m_IconStop;
	CRect rect_max;
	CMenu menu;
	//行 列
	int row = 0, col = 0;
	// 生成的消息映射函数
	//初始化函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	//按钮事件
	afx_msg void OnBnClickedShowHideAppPlayer();
	afx_msg void OnBnClickedStartStopBot();
	afx_msg void OnBnClickedPausebot();
	afx_msg void OnScreenCapture();
	//定时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//窗口关闭
	afx_msg void OnClose();
	//自定义消息
	afx_msg LRESULT oneKeySet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SetLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Statistics(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpDataAppPlayerInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SelectAppPlayer(WPARAM wParam, LPARAM lParam);
	//配置
	afx_msg LRESULT SaveConfigInFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoadOutConfig(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoadInConfig(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowGraphic(WPARAM wParam, LPARAM lParam);
public:
	
	
	
	CbotFunction fbot;
	
	
private:
	BOOL InitSocket();
	void InitlizeList(void);
public:

	
	void SaveConfig(CString fileName="");
	void UpdateWindowSet();
	BOOL IsFirstUsePrograme();
	//设置窗口大小
	afx_msg void OnBnClickedResetSize();
	// 右击列表
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//菜单-启动模拟器
	afx_msg void OnLaunch();
	//菜单-关闭模拟器
	afx_msg void OnQuit();
	//菜单-开始一个脚本
	afx_msg void OnStartOneScript();
	//菜单，暂停一个脚本
	afx_msg void OnPauseOneScript();
	//菜单-停止一个脚本
	afx_msg void OnStopOneScript();
	//刷新列表
	afx_msg void OnBnClickedUpdataList();
	afx_msg void OnSetConfig();
};




//其它全局函数

 CString GetExePath();
