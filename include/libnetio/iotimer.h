#pragma once

#include <memory>
#include <functional>
#include <system_error>
#include <chrono>

#ifndef START_LIBNETIO_NAME_SPACE
#define START_LIBNETIO_NAME_SPACE	namespace libnetio {
#endif
#ifndef END_LIBNETIO_NAME_SPACE
#define END_LIBNETIO_NAME_SPACE		}
#endif

START_LIBNETIO_NAME_SPACE

class IoServicePool;

class IoTimer
{
public:

	struct tagIoTimerImp;
	using IoTimerImpPtr = std::unique_ptr<tagIoTimerImp>;
	using AsyncTimeOutFun = std::function<void()>;

public:

	IoTimer();

	virtual ~IoTimer();

public:

	/// ����������(iDelayExcuteTime:��λ:����)
	virtual int32_t Start(AsyncTimeOutFun pAsyncTimeOutFun, 
		AsyncTimeOutFun pAsyncCancelFun, int32_t iDelayExcuteTime = 0,
		std::size_t iThreadCount = 0);

	/// ����������(iDelayExcuteTime:��λ:����)
	virtual int32_t Start(std::shared_ptr<IoServicePool> &pIoServicePoolPtr, 
		AsyncTimeOutFun pAsyncTimeOutFun, AsyncTimeOutFun pAsyncCancelFun, 
		int32_t iDelayExcuteTime = 0);

	/// ����������
	virtual int32_t Start(AsyncTimeOutFun pAsyncTimeOutFun,
		AsyncTimeOutFun pAsyncCancelFun, const std::chrono::steady_clock::time_point &tTimePoint,
		std::size_t iThreadCount = 0);

	/// ����������
	virtual int32_t Start(std::shared_ptr<IoServicePool> &pIoServicePoolPtr,
		AsyncTimeOutFun pAsyncTimeOutFun, AsyncTimeOutFun pAsyncCancelFun,
		const std::chrono::steady_clock::time_point &tTimePoint);

	/// ֹͣ������
	virtual void Stop();

	/// �����־
	virtual void WriteLogInfo(const std::error_code &err);

public:

	/// �첽�������¼�
	using AsyncPostHandleFun = std::function<void()>;
	uint32_t AsyncPostHandle(AsyncPostHandleFun handle);

	/// ��ȡSERVICE POOL(�貶��system_error�쳣)
	std::shared_ptr<IoServicePool>& GetIoServicePool();

public:

	/// ȡ��ʱ��
	void CancelTimer();

	/// ����ʱ��(iDelayExcuteTime:��λ:����)
	void ResetTimer(AsyncTimeOutFun pAsyncTimeOutFun,
		AsyncTimeOutFun pAsyncCancelFun, int32_t iDelayExcuteTime = 0);

private:

	IoTimerImpPtr m_pIoTimerImpPtr;
	bool m_bStop;

};

END_LIBNETIO_NAME_SPACE