#pragma once

#include <memory>
#include <functional>
#include <system_error>
#include <vector>

#ifndef START_LIBNETIO_NAME_SPACE
#define START_LIBNETIO_NAME_SPACE	namespace libnetio {
#endif
#ifndef END_LIBNETIO_NAME_SPACE
#define END_LIBNETIO_NAME_SPACE		}
#endif

START_LIBNETIO_NAME_SPACE

class IoServicePool;

class IoTcpClient
{
public:

	struct tagIoTcpClientImp;
	using IoTcpClientImpPtr = std::unique_ptr<tagIoTcpClientImp>;

public:

	IoTcpClient();

	virtual ~IoTcpClient();

public:

	/// ����������(uiConnectTimeOut:���ӳ�ʱ(��λ������);uiTimeOut:�ǻ�Ծ��ʱ(��λ������))
	virtual int32_t Start(uint32_t uiRemoteIp, uint16_t uiRemotePort, 
		uint32_t uiConnectTimeOut = 0, uint32_t uiTimeOut = 0,
		std::size_t iThreadCount = 0);

	/// ����������
	virtual int32_t Start(std::shared_ptr<IoServicePool> &pIoServicePoolPtr,
		uint32_t uiRemoteIp, uint16_t uiRemotePort,
		uint32_t uiConnectTimeOut = 0, uint32_t uiTimeOut = 0);

	/// ֹͣ������
	virtual void Stop();

	/// �����־
	virtual void WriteLogInfo(const std::error_code &err);

public:

	/// �ͻ���������Ӧ
	virtual void OnConnect() = 0;

	/// ���յ�������Ӧ
	virtual void OnReceive(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size) = 0;

	/// �������ݺ���Ӧ
	virtual void OnSend(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size) = 0;

	/// �ͻ����رպ���Ӧ
	virtual void OnClose() = 0;

public:

	/// ������������(isall:<true:size���뷢�����;false:size����Ҫ�������)
	void SendBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::size_t offset = 0, bool isall = true);

	/// �첽��������(isall:<true:size����������;false:size����Ҫ�������)
	void ReceiveBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::size_t offset = 0, bool isall = true);

	/// �����ر�����
	void Close();

public:

	/// �첽�������¼�
	using AsyncPostHandleFun = std::function<void()>;
	uint32_t AsyncPostHandle(AsyncPostHandleFun handle);

	/// ��ȡSERVICE POOL(�貶��system_error�쳣)
	std::shared_ptr<IoServicePool>& GetIoServicePool();

public: /// ��ȡ�ͻ�������

	/// ��ȡԶ��IP
	uint32_t GetPeerIp();

	/// ��ȡ����IP
	uint32_t GetLocalIp();

	/// ��ȡSOCKET���
	uint64_t GetSocket();

	/// ���ý��ջ�����
	void SetRecvBuffer(const std::shared_ptr<std::vector<char>> &pRecvBufferPtr);

	/// ���÷��ͻ�����
	void SetSendBuffer(const std::shared_ptr<std::vector<char>> &pSendBufferPtr);

	/// ��ȡ���ջ�����
	std::shared_ptr<std::vector<char>> &GetRecvBuffer();

	/// ��ȡ���ͻ�����
	std::shared_ptr<std::vector<char>> &GetSendBuffer();

	/// ���ý��ջ������ɽ��մ�С
	void SetRecvBufferSize(std::size_t size);

	/// ��ȡ���ջ������ɽ��մ�С
	std::size_t GetRecvBufferSize();

public:

	/// ����ͬ����������
	std::size_t SyncSendBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::error_code &err, std::size_t offset = 0);

	/// ����ͬ����������
	std::size_t SyncRecvBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t size, std::error_code &err, std::size_t offset = 0);

private:

	IoTcpClientImpPtr m_pIoClientImpPtr;

	bool m_bStop;
};

END_LIBNETIO_NAME_SPACE