
// newcocbot.cpp : 定义应用程序的类行为。
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


// CnewcocbotApp 构造

CcocBotApp::CcocBotApp()
{
	EnableHtmlHelp();

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CnewcocbotApp 对象

CcocBotApp theApp;


// CnewcocbotApp 初始化

BOOL CcocBotApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
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

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	//
	AfxInitRichEdit2();

	//
	m_hRichEdit=LoadLibrary(_T("RICHED20.DLL"));
	
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//皮肤
	//skinppLoadSkin(_T("blue.ssk"));//blue.ssk为项目下的皮肤文件

	// 步骤1 设置COM组件线程模型为sta
	CoInitialize(NULL);
	 
	//2.确定路径
	CString modePath;
	::AfxGetModuleFileName(NULL, modePath);
	
	modePath = modePath.Left(modePath.ReverseFind(_T('\\')));

	//3.这里开始注册大漠

	if (false == RegistryDll(modePath + "\\Function\\dm.dll"))
	{
		::MessageBox(NULL, "注册插件失败！", "提示", MB_OK | MB_ICONERROR);
		return FALSE;

	}

	//4.下面开始破解大漠
	
	if (CrackDm("dm.dll")<=0)
	{
		::MessageBox(NULL, "破解插件失败！", "提示", MB_OK | MB_ICONERROR);
	}
	
	//5.检查版本号
	Cdmsoft dm;
	if (dm.CreateDispatch("dm.dmsoft")==FALSE)
	{
		MessageBox(NULL, "创建对象失败,检查是否正常注册", "错误", MB_OK);
		dm = NULL;
		return FALSE;
	}
	if (dm.Ver()!=DM_VER_5&&dm.Ver()!=DM_VER_6)
	{
		CString tmp;
		tmp = "版本错误，当前版本号是:" + dm.Ver();
		MessageBox(NULL, tmp, "错误", MB_OK);
		dm = NULL;
		return FALSE;
	}
	dm = NULL;
	if (!AfxSocketInit())
	{
		::MessageBox(NULL,"加载套接字库失败！","提示",0);
		return FALSE;
	}

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//登录对话框
	CLogin login;
	//主对话框
	CcocBotDlg dlg; 

	//设置为主对话框
	m_pMainWnd = &dlg;

	
	INT_PTR nResponse = 0;
	//登陆
	//***************************************************************
	
	/*do 
	{
		nResponse = login.DoModal();
		if (IDOK != nResponse) return FALSE;
		if (!login.strAccount.GetLength())
		{
			MessageBox(NULL, "请输入账号！", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (!login.strPassWord.GetLength())
		{
			MessageBox(NULL, "请输入密码！", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (login.strAccount!=DEFAULT_ACCOUNT)
		{
			MessageBox(NULL, "账号不存在！", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
		if (login.strPassWord != DEFAULT_PASSWORD)
		{
			MessageBox(NULL, "密码不正确！", "", MB_OK | MB_ICONINFORMATION);
			continue;
		}
	
		break;
	

	} while (true);
	
	*/
	//***************************************************************
	nResponse = dlg.DoModal();
	//显示模态对话框


	//对话框关闭了
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	//释放一些DLL
	FreeLibrary(m_hRichEdit);

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
		
	}
	
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
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
