
// cocbotDlg.h : ͷ�ļ�
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
// CcocBotDlg �Ի���
class CcocBotDlg : public CDialogEx
{
// ����
public:
	CcocBotDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CcocBotDlg();                       // ��׼��������
// �Ի�������
	enum { IDD = IDD_NEWCOCBOT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	SOCKET m_socket;
	CTabCtrl main_tab;
	CListCtrl m_list;
	CButton m_StartStopButton;
	CString app_player_bs_install_dir, app_player_ld_install_dir;//bs,�׵�ģ������װ·��/��Ŀ¼
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
// ʵ��
protected:
	HICON m_hIcon; //ͼƬ
	HICON m_IconStart;
	HICON m_IconStop;
	CRect rect_max;
	CMenu menu;
	//�� ��
	int row = 0, col = 0;
	// ���ɵ���Ϣӳ�亯��
	//��ʼ������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	//��ť�¼�
	afx_msg void OnBnClickedShowHideAppPlayer();
	afx_msg void OnBnClickedStartStopBot();
	afx_msg void OnBnClickedPausebot();
	afx_msg void OnScreenCapture();
	//��ʱ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//���ڹر�
	afx_msg void OnClose();
	//�Զ�����Ϣ
	afx_msg LRESULT oneKeySet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SetLog(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Statistics(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpDataAppPlayerInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SelectAppPlayer(WPARAM wParam, LPARAM lParam);
	//����
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
	//���ô��ڴ�С
	afx_msg void OnBnClickedResetSize();
	// �һ��б�
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//�˵�-����ģ����
	afx_msg void OnLaunch();
	//�˵�-�ر�ģ����
	afx_msg void OnQuit();
	//�˵�-��ʼһ���ű�
	afx_msg void OnStartOneScript();
	//�˵�����ͣһ���ű�
	afx_msg void OnPauseOneScript();
	//�˵�-ֹͣһ���ű�
	afx_msg void OnStopOneScript();
	//ˢ���б�
	afx_msg void OnBnClickedUpdataList();
	afx_msg void OnSetConfig();
};




//����ȫ�ֺ���

 CString GetExePath();
