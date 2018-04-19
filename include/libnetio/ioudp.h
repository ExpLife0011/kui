#pragma once

#include <memory>
#include <stdint.h>
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

enum eIoUdpOptType
{
	IoUdpOptTypeStart = 0,
	IoUdpOptTypeStop,
	IoUdpOptTypeSend,
	IoUdpOptTypeRecv,
	IoUdpOptTypePostSend,
	IoUdpOptTypePostRecv,
	IoUdpOptTypeHandle,
};

#pragma pack(push, 1)
struct tagIoUdpSendParamInfo
{
	uint32_t ui32RemotelIp;
	uint16_t ui16Port;
	uint32_t ui32SendSize;
};
#pragma pack(pop)

class IoServicePool;
class IoUdp
{
public:

 	struct tagIoUdpImp;
	using IoUdpImpPtr = std::unique_ptr<tagIoUdpImp>;

public:

	IoUdp();

	virtual ~IoUdp();

public:

	/// ����������
	virtual int32_t Start(uint16_t ui16Port, uint32_t ui32LocalIp = 0,
		std::size_t iThreadCount = 0, bool bReuseAddr = false, bool bBroadcast = false);

	/// ����������
	virtual int32_t Start(uint16_t ui16Port, std::shared_ptr<IoServicePool> &pIoServicePoolPtr,
		uint32_t ui32LocalIp = 0, bool bReuseAddr = false, bool bBroadcast = false);

	/// ֹͣ������
	virtual void Stop();

	/// �����־
	virtual void WriteLogInfo(eIoUdpOptType type, const std::error_code &err, 
		uint32_t ui32RemotelIp = 0, uint16_t ui16Port = 0);

public:

	/// ���յ�������Ӧ
	virtual void OnReceive(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size, uint32_t ui32RemotelIp, uint16_t ui16Port) = 0;

	/// �������ݺ���Ӧ
	virtual void OnSend(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t offset, std::size_t size, uint32_t ui32RemotelIp, uint16_t ui16Port) = 0;

public:

	/// ��ȡUDP���ض˿�
	inline uint16_t GetPort() { return m_ui16Port; }

	/// ��ȡUDP���ذ󶨵�IP
	inline uint32_t GetIp() { return m_ui32LocalIp; }

public:

	/// �첽�������¼�
	using AsyncPostHandleFun = std::function<void()>;
	uint32_t AsyncPostHandle(AsyncPostHandleFun handle);

	/// ��ȡSERVICE POOL(�貶��system_error�쳣)
	std::shared_ptr<IoServicePool>& GetIoServicePool();

	/// ��ȡSOCKET���
	uint64_t GetSocket();

public:

	/// �����첽��������
	void SendBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr,	std::size_t size, 
		uint32_t ui32RemotelIp, uint16_t ui16Port, std::size_t offset = 0);

	/// �첽��������
	void ReceiveBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr, std::size_t size,
		std::size_t offset = 0);

public:

	/// �����첽��������(�����Ͷ���, sendparamsize: sizeof(tagIoUdpSendParamInfo))
	void SendBufferEx(std::shared_ptr<std::vector<char>>& pBufferPtr, std::size_t size,
		uint32_t ui32RemotelIp, uint16_t ui16Port, std::size_t sendparamsize);

	/// �첽��������(�����Ͷ���, sendparamsize: sizeof(tagIoUdpSendParamInfo))
	void ReceiveBufferEx(std::shared_ptr<std::vector<char>>& pBufferPtr, std::size_t size,
		std::size_t sendparamsize);

public:

	/// ������������(��������)
	void SyncSendBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr, std::size_t size,
		uint32_t ui32RemotelIp, uint16_t ui16Port,
		std::size_t offset = 0);

	/// ������������(��������)
	void SyncRecvBuffer(std::shared_ptr<std::vector<char>>& pBufferPtr, std::size_t size,
		uint32_t &ui32RemotelIp, uint16_t &ui16Port,
		std::size_t offset = 0);

private:

	IoUdpImpPtr m_pIoUdpImp;
	uint32_t m_ui32LocalIp;
	uint16_t m_ui16Port;
	bool m_bStop;
};

END_LIBNETIO_NAME_SPACE