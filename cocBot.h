
// newcocbot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcocBotApp:
// �йش����ʵ�֣������ cocBot.cpp
//

class CcocBotApp : public CWinApp
{
public:
	CcocBotApp();

// ��д
public:
	HMODULE m_hRichEdit;
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	int ExitInstance();
	/*ע����*/
	bool RegistryDll(const char* szDllPath);
	/*�ƽ�*/
	int CrackDm(const char* crackDllName);
};

extern CcocBotApp theApp;