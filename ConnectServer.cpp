// ConnectServer.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "ConnectServer.h"


// ConnectServer

ConnectServer::ConnectServer()
{
}

ConnectServer::~ConnectServer()
{
}


// ConnectServer 成员函数


void ConnectServer::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnAccept(nErrorCode);
}


void ConnectServer::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnClose(nErrorCode);
}


void ConnectServer::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnConnect(nErrorCode);
}


void ConnectServer::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	leng = Receive(pData, 1024, 0);
	str = pData;
	Accept_str=str;
	delete pData;
	pData = NULL;
	CSocket::OnReceive(nErrorCode);
}


void ConnectServer::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnSend(nErrorCode);
}


int ConnectServer::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}


int ConnectServer::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CSocket::Send(lpBuf, nBufLen, nFlags);
}
CString ConnectServer::GetAcceptStr()
{
	CString str=Accept_str;
	if (str.GetLength()<3)
	{
		str=_T("");
	}
	return str;
}