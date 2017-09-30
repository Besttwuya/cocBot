/*
通过管道操作 一些控制台程序，例如adb,或者一些引擎
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
	//启动 shell，如果成功则进入#状态，可以使用RunCmd执行命令
	/*可在文件后面直接附加命令*/
	BOOL Start(CString cmdStr);
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
