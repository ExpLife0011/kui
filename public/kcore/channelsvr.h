#pragma once
#include "kcore.h"
using namespace kcore;

class Cchannelsvr : public INetCallback
{
public:
	Cchannelsvr(void);
	virtual ~Cchannelsvr(void);
public:
	/// ʵ����ȡ
	static Cchannelsvr& GetInstance();
	/// ��������
	bool StartServer();
	/// ֹͣ����
	void StopServer();
public:
	virtual void Release();
	virtual long OnAccept(INetModule* pNetModule, DWORD_PTR Id);
	virtual long OnSend(INetModule* pNetModule, DWORD_PTR Id);
	virtual long OnReceive(INetModule* pNetModule, DWORD_PTR Id, LPCSTR pRecvBuf, LPSTR pSendBuf);
	virtual void OnClose(INetModule* pNetModule, DWORD_PTR Id);
public:
	void QueryTaskList(CPkgHelper& In, CPkgHelper& Out);
	void QueryReportStyle(CPkgHelper& In, CPkgHelper& Out);
	void DownTaskZip(CPkgHelper& In, CPkgHelper& Out);
private:
	INetModule*	m_pINetModule;
};

#define sChannelSvr		Cchannelsvr::GetInstance()