#pragma once

#include <stdint.h>
#include <memory>
#include <system_error>
#include <vector>
#include <functional>

#ifndef START_LIBNETIO_NAME_SPACE
#define START_LIBNETIO_NAME_SPACE	namespace libnetio {
#endif
#ifndef END_LIBNETIO_NAME_SPACE
#define END_LIBNETIO_NAME_SPACE		}
#endif

START_LIBNETIO_NAME_SPACE

// =======================================================
class IoServicePool;
struct TcpSession;
class IoTcpServer
{
public:

	struct tagIoServerImp;
	using IoServerImpPtr = std::unique_ptr<tagIoServerImp>;

public:

	IoTcpServer();

	virtual ~IoTcpServer();

public:

	/// ����������
	virtual int32_t Start(uint16_t ui16Port, uint32_t ui32LocalIp = 0,
		uint32_t uiTimeOut = 0, std::size_t iThreadCount = 0, bool bReuseAddr = false);

	/// ����������
	virtual int32_t Start(uint16_t ui16Port, std::shared_ptr<IoServicePool> &pIoServicePoolPtr,
		uint32_t uiTimeOut = 0, uint32_t ui32LocalIp = 0, bool bReuseAddr = false);

	/// ֹͣ������
	virtual void Stop();

	/// �����־
	virtual void WriteLogInfo(const std::error_code &err);

public:

	/// ��ȡTCP�����˿�
	inline uint16_t GetPort() { return m_ui16Port; }

	/// ��ȡTCP�����󶨵�IP
	inline uint32_t GetIp() { return m_ui32LocalIp; }

	/// ��ȡTCP�����󶨵��߳�����
	inline std::size_t GetThreadCount() { return m_iThreadCount; }

public:

	/// ���տͻ���������Ӧ
	virtual void OnAccept(const std::shared_ptr<TcpSession> &pSessionPtr) = 0;

	/// ���յ�������Ӧ
	virtual void OnReceive(const std::shared_ptr<TcpSession> &pSessionPtr,
		std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size) = 0;

	/// �������ݺ���Ӧ
	virtual void OnSend(const std::shared_ptr<TcpSession> &pSessionPtr, 
		std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size) = 0;

	/// �ͻ����رպ���Ӧ
	virtual void OnClose(const std::shared_ptr<TcpSession> &pSessionPtr) = 0;

public:

	/// ������������(isall:<true:size���뷢�����;false:size����Ҫ�������)
	void SendBuffer(const std::shared_ptr<TcpSession> &pSessionPtr, 
		std::shared_ptr<std::vector<char>>& pBufferPtr, 
		std::size_t size, std::size_t offset = 0, bool isall = true);

	/// �첽��������(isall:<true:size����������;false:size����Ҫ�������)
	void ReceiveBuffer(const std::shared_ptr<TcpSession> &pSessionPtr,
		std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::size_t offset = 0, bool isall = true);

	/// �����ر�����
	void Close(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// �����ر���������
	void CloseAll();

public:

	/// ����ͬ����������
	std::size_t SyncSendBuffer(const std::shared_ptr<TcpSession> &pSessionPtr,
		std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::error_code &err, std::size_t offset = 0);

	/// ����ͬ����������
	std::size_t SyncRecvBuffer(const std::shared_ptr<TcpSession> &pSessionPtr,
		std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::error_code &err, std::size_t offset = 0);

public:

	/// �첽������ͻ����¼�
	using AsyncPostHandleTcpSessionFun = std::function<void()>;
	uint32_t AsyncPostHandle(const std::shared_ptr<TcpSession> &pSessionPtr, 
		AsyncPostHandleTcpSessionFun handle);

public:

	/// �첽�������¼�
	using AsyncPostHandleFun = std::function<void()>;
	uint32_t AsyncPostHandle(AsyncPostHandleFun handle);

	/// ��ȡSERVICE POOL(�貶��system_error�쳣)
	std::shared_ptr<IoServicePool>& GetIoServicePool();

public: /// ��ȡ�ͻ�������

	/// ��ȡsession id
	uint64_t GetSessionId(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ��ȡԶ��IP
	uint32_t GetPeerIp(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ��ȡ����IP
	uint32_t GetLocalIp(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ��ȡSOCKET���
	uint64_t GetSocket(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ���ý��ջ�����
	void SetRecvBuffer(const std::shared_ptr<TcpSession> &pSessionPtr,
		const std::shared_ptr<std::vector<char>> &pRecvBufferPtr);

	/// ���÷��ͻ�����
	void SetSendBuffer(const std::shared_ptr<TcpSession> &pSessionPtr,
		const std::shared_ptr<std::vector<char>> &pSendBufferPtr);

	/// ��ȡ���ջ�����
	std::shared_ptr<std::vector<char>> &GetRecvBuffer(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ��ȡ���ͻ�����
	std::shared_ptr<std::vector<char>> &GetSendBuffer(const std::shared_ptr<TcpSession> &pSessionPtr);

	/// ���ý��ջ������ɽ��մ�С
	void SetRecvBufferSize(const std::shared_ptr<TcpSession> &pSessionPtr, std::size_t size);

	/// ��ȡ���ջ������ɽ��մ�С
	std::size_t GetRecvBufferSize(const std::shared_ptr<TcpSession> &pSessionPtr);

private:

	uint16_t m_ui16Port;
	uint32_t m_ui32LocalIp;
	std::size_t m_iThreadCount;
	IoServerImpPtr m_pIoServerImpPtr;
	bool m_bStop;
};

END_LIBNETIO_NAME_SPACE