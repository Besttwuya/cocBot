
// newcocbot.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "cocBot.h"
#include "cocBotDlg.h"
#include "Login.h"
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

	//
	AfxInitRichEdit2();

	//
	m_hRichEdit=LoadLibrary(_T("RICHED20.DLL"));
	
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//Ƥ��
	//skinppLoadSkin(_T("blue.ssk"));//blue.sskΪ��Ŀ�µ�Ƥ���ļ�

	// ����1 ����COM����߳�ģ��Ϊsta
	CoInitialize(NULL);
	 
	//2.ȷ��·��
	CString modePath;
	::AfxGetModuleFileName(NULL, modePath);
	
	modePath = modePath.Left(modePath.ReverseFind(_T('\\')));

	//3.���￪ʼע���Į

	if (false == RegistryDll(modePath + "\\Function\\dm.dll"))
	{
		::MessageBox(NULL, "ע����ʧ�ܣ�", "��ʾ", MB_OK | MB_ICONERROR);
		return FALSE;

	}

	//4.���濪ʼ�ƽ��Į
	
	if (CrackDm("dm.dll")<=0)
	{
		::MessageBox(NULL, "�ƽ���ʧ�ܣ�", "��ʾ", MB_OK | MB_ICONERROR);
	}
	
	//5.���汾��
	Cdmsoft dm;
	if (dm.CreateDispatch("dm.dmsoft")==FALSE)
	{
		MessageBox(NULL, "��������ʧ��,����Ƿ�����ע��", "����", MB_OK);
		dm = NULL;
		return FALSE;
	}
	if (dm.Ver()!=DM_VER_5&&dm.Ver()!=DM_VER_6)
	{
		CString tmp;
		tmp = "�汾���󣬵�ǰ�汾����:" + dm.Ver();
		MessageBox(NULL, tmp, "����", MB_OK);
		dm = NULL;
		return FALSE;
	}
	dm = NULL;
	if (!AfxSocketInit())
	{
		::MessageBox(NULL,"�����׽��ֿ�ʧ�ܣ�","��ʾ",0);
		return FALSE;
	}

	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//��¼�Ի���
	CLogin login;
	//���Ի���
	CcocBotDlg dlg; 

	//����Ϊ���Ի���
	m_pMainWnd = &dlg;

	
	INT_PTR nResponse = 0;
	//��½
	//***************************************************************
	
	/*do 
	{
		nResponse = login.DoModal();
		if (IDOK != nResponse) return FALSE;
		if (!login.strAccount.GetLength())
		{
			MessageBox(NULL, "�������˺ţ�", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (!login.strPassWord.GetLength())
		{
			MessageBox(NULL, "���������룡", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (login.strAccount!=DEFAULT_ACCOUNT)
		{
			MessageBox(NULL, "�˺Ų����ڣ�", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (login.strPassWord != DEFAULT_PASSWORD)
		{
			MessageBox(NULL, "���벻��ȷ��", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
	
		break;
	

	} while (true);
	
	*/
	//***************************************************************
	nResponse = dlg.DoModal();
	//��ʾģ̬�Ի���


	//�Ի���ر���
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

	//�ͷ�һЩDLL
	FreeLibrary(m_hRichEdit);

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
		
	}
	
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CcocBotApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	//skinppExitSkin();
	return 0;
}


bool CcocBotApp::RegistryDll(const char* szDllPath)
{
	HMODULE hLib = LoadLibrary(szDllPath);
	if (hLib < (HMODULE)HINSTANCE_ERROR)
	{
		return FALSE;
	}
	HRESULT hResult = ::OleInitialize(NULL);
	if (hResult != S_OK)
	{
		FreeLibrary(hLib);
		return FALSE;
	}
	FARPROC lpDllEntryPoint = GetProcAddress(hLib, "DllRegisterServer");
	if (lpDllEntryPoint == NULL)
	{
		FreeLibrary(hLib);
		::OleUninitialize();
		return FALSE;
	}
	if (FAILED((*lpDllEntryPoint)()))
	{
		FreeLibrary(hLib);
		::OleUninitialize();
		return FALSE;

	};
	::OleUninitialize();
	FreeLibrary(hLib);
	return TRUE;
}


int CcocBotApp::CrackDm(const char* crackDllName)
{
	Cdmsoft dm;
	CLSID clsid;
	CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (FALSE==dm.CreateDispatch(clsid))
	{
		dm = NULL;
		return false;
	}
	dm.RegEx("11111111111111111111", "", "127.0.0.1");
	int ret = 0;
	int writeValue = 1;
	HANDLE hWnd = GetModuleHandleA(crackDllName);
	char msg[100] = { 0 };
	int n = 0;
	if (hWnd)
	{
		//for 5.1423
		if (dm.Ver() == "5.1423")
		{
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1063d0 + (long)hWnd), &writeValue, 1, 0);
			/*n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1063d4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x106614 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x106618 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x106ca4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1065e4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x115b60 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x10f7bc + (long)::GetModuleHandleA("ntdll.dll")), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x10fc84 + (long)::GetModuleHandleA("ntdll.dll")), &writeValue, 1, 0);
			*/
			//_asm mov [0x1063d0+hWnd],1
			//*(int*)(0x1063d0 + (long)hWnd) = 1;
		}else if (dm.Ver()=="6.1538")
		{
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1073e0 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1073e4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x1075f4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x107624 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x107628 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x107cb4 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x116bb8 + (long)hWnd), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x10f7bc + (long)::GetModuleHandleA("ntdll.dll")), &writeValue, 1, 0);
			n = ::WriteProcessMemory(INVALID_HANDLE_VALUE, LPVOID(0x10fc84 + (long)::GetModuleHandleA("ntdll.dll")), &writeValue, 1, 0);

		}
	}
	if (n>0)
	{
		ret = 1;
	}
	else
	{
		ret = ::GetLastError();
		ret *= -1;
	}
	dm = NULL;
	return ret;
}
