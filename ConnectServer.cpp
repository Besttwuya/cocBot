// ConnectServer.cpp : ʵ���ļ�
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


// ConnectServer ��Ա����


void ConnectServer::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnAccept(nErrorCode);
}


void ConnectServer::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CSocket::OnClose(nErrorCode);
}


void ConnectServer::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnConnect(nErrorCode);
}


void ConnectServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnSend(nErrorCode);
}


int ConnectServer::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}


int ConnectServer::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: �ڴ����ר�ô����/����û���

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