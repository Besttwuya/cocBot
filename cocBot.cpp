
// newcocbot.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "cocBot.h"
#include "cocBotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnewcocbotApp

BEGIN_MESSAGE_MAP(CcocBotApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CnewcocbotApp ����

CcocBotApp::CcocBotApp()
{
	EnableHtmlHelp();

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CnewcocbotApp ����

CcocBotApp theApp;


// CnewcocbotApp ��ʼ��

BOOL CcocBotApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		AfxMessageBox("error bad InitInstance",MB_OK);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;
	AfxInitRichEdit2();
	m_hRichEdit=LoadLibrary(_T("RICHED20.DLL"));
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	if (!AfxSocketInit())
	{
		::MessageBox(NULL,"�����׽��ֿ�ʧ�ܣ�","char",0);
		return FALSE;
	}
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	
	CcocBotDlg dlg;
	
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
		
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	FreeLibrary(m_hRichEdit);
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CcocBotApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	return 0;
}
