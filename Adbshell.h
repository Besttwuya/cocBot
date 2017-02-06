/*
通过管道操作adb shell	--by sing
*/

#pragma once
#include <WinDef.h>
#include <atlstr.h>

class CAdbshell
{
public:
	CAdbshell(void);
	~CAdbshell(void);
public:
	//启动adb shell，如果成功则进入#状态，可以使用RunCmd执行命令
	//BOOL Start(CString strFileName );
	BOOL Start(CString strFileName, CString IpAdress, int type);
	//这里输入的是在adb shell状态下的批处理命令，如果有多条请以\n分隔
	BOOL RunCmd(const CString&strCmdline);

	//退出shell命令状态，关闭进程
	BOOL Stop();

	//读取输出结果,调用前请务必调用Stop先结束
	CString GetOutput();

public:
	BOOL Loop();

private:
	HANDLE	hThread;
	CString m_strOutput;
	//HANDLE	m_hProcess;

	//指示线程准备好，可以进行命令输入的信号量
	HANDLE	m_hEvent;

	HANDLE	m_hReadPipe;
	HANDLE	m_hReadPipe2;
	HANDLE	m_hWritePipe;
	HANDLE	m_hWritePipe2;
};
