/*
ͨ���ܵ����� һЩ����̨��������adb,����һЩ����
*/

#pragma once
#include <WinDef.h>
#include <atlstr.h>

class CPipeShell
{
public:
	CPipeShell(void);
	~CPipeShell(void);
public:
	//���� shell������ɹ������#״̬������ʹ��RunCmdִ������
	/*�����ļ�����ֱ�Ӹ�������*/
	BOOL Start(CString cmdStr);
	//�������������adb shell״̬�µ��������������ж�������\n�ָ�
	BOOL RunCmd(const CString&strCmdline);

	//�˳�shell����״̬���رս���
	BOOL Stop();

	//��ȡ������,����ǰ����ص���Stop�Ƚ���
	CString GetOutput();

public:
	BOOL Loop();

private:
	HANDLE	hThread;
	CString m_strOutput;
	//HANDLE	m_hProcess;

	//ָʾ�߳�׼���ã����Խ�������������ź���
	HANDLE	m_hEvent;

	HANDLE	m_hReadPipe;
	HANDLE	m_hReadPipe2;
	HANDLE	m_hWritePipe;
	HANDLE	m_hWritePipe2;
};
