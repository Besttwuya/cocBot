#pragma once

// ConnectServer ÃüÁîÄ¿±ê

class ConnectServer : public CSocket
{
private:
	CString Accept_str;
public:
	ConnectServer();
	virtual ~ConnectServer();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	CString GetAcceptStr();  
};


