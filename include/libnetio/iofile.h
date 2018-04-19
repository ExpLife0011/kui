#pragma once

#ifdef WIN32

#include <memory>
#include <system_error>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <vector>
#include <functional>
#include <mutex>

#ifndef START_LIBNETIO_NAME_SPACE
#define START_LIBNETIO_NAME_SPACE	namespace libnetio {
#endif
#ifndef END_LIBNETIO_NAME_SPACE
#define END_LIBNETIO_NAME_SPACE		}
#endif

START_LIBNETIO_NAME_SPACE

struct TcpSession;
class IoServicePool;

typedef struct tagTcpSessionFileParam
{
	std::shared_ptr<TcpSession> pSessionPtr;		// TCP�ͻ���
	std::size_t iTotalTrascationLen;				// �ܴ�С
	std::size_t iTrascationLen;						// ��ִ�С
	std::mutex lockTrascationLen;					// ��ִ�С��
} TCPSESSIONFILEPARAM, *PTCPSESSIONFILEPARAM;

class IoFile
{
public:

	struct tagIoFileImp;
	using IoFileImpPtr = std::unique_ptr<tagIoFileImp>;

public:

	IoFile();

	virtual ~IoFile();

public:

	/// ����������
	/// (dwDesiredAccess:GENERIC_ALL etc.)
	/// (dwDesiredAccess:OPEN_ALWAYS etc.)
	/// (dwFlagsAndAttributes:FILE_ATTRIBUTE_NORMAL etc.)
	virtual int32_t Start(std::wstring &strFilePath, DWORD dwDesiredAccess,
		DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, std::size_t iThreadCount = 0);

	/// ����������
	virtual int32_t Start(std::wstring &strFilePath,
		std::shared_ptr<IoServicePool> &pIoServicePoolPtr, DWORD dwDesiredAccess,
		DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes);

	/// ����������(hFile must be set FILE_FLAG_OVERLAPPED)
	virtual int32_t Start(HANDLE hFile, std::size_t iThreadCount = 0);

	/// ����������(hFile must be set FILE_FLAG_OVERLAPPED)
	virtual int32_t Start(HANDLE hFile, std::shared_ptr<IoServicePool> &pIoServicePoolPtr);

	/// ֹͣ������
	virtual void Stop();

	/// �����־
	virtual void WriteLogInfo(const std::error_code &err);

public:

	/// ��ȡ���ݺ���Ӧ(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	virtual void OnRead(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t bptoffset, uint64_t offset, std::size_t needsize,
		const std::error_code &err, std::size_t size) = 0;

	/// д�����ݺ���Ӧ(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	virtual void OnWrite(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t bptoffset, uint64_t offset, std::size_t needsize,
		const std::error_code &err, std::size_t size) = 0;

public: /// TCP�ͻ���ʹ��

	/// ��ȡ���ݺ���Ӧ(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	virtual void OnTcpSessionRead(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t bptoffset, uint64_t offset, std::size_t needsize,
		std::shared_ptr<tagTcpSessionFileParam> &pTcpSessionFileParamPtr,
		const std::error_code &err, std::size_t size) = 0;

	/// д�����ݺ���Ӧ(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	virtual void OnTcpSessionWrite(std::shared_ptr<std::vector<char>>& pBufferPtr,
		std::size_t bptoffset, uint64_t offset, std::size_t needsize,
		std::shared_ptr<tagTcpSessionFileParam> &pTcpSessionFileParamPtr,
		const std::error_code &err, std::size_t size) = 0;

public:

	/// ��ȡ�ļ�����(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	int32_t ReadFile(uint64_t offset, std::shared_ptr<std::vector<char>> &pBufferPtr, 
		std::size_t size, std::size_t bptoffset = 0);

	/// д���ļ�����(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	int32_t WriteFile(uint64_t offset, std::shared_ptr<std::vector<char>> &pBufferPtr,
		std::size_t size, std::size_t bptoffset = 0);

public: /// TCP�ͻ���ʹ��

	/// ��ȡ�ļ�����(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	int32_t TcpSessionReadFile(uint64_t offset, 
		std::shared_ptr<std::vector<char>> &pBufferPtr,	std::size_t size, 
		std::shared_ptr<tagTcpSessionFileParam> &pTcpSessionFileParamPtr, 
		std::size_t bptoffset = 0);

	/// д���ļ�����(offset:�ļ�ƫ��;bptoffset:pBufferPtrƫ��)
	int32_t TcpSessionWriteFile(uint64_t offset,
		std::shared_ptr<std::vector<char>> &pBufferPtr,	std::size_t size,
		std::shared_ptr<tagTcpSessionFileParam> &pTcpSessionFileParamPtr, 
		std::size_t bptoffset = 0);

public:

	/// ͬ����ȡ����
	std::size_t SyncReadFile(uint64_t offset, std::shared_ptr<std::vector<char>> &pBufferPtr,
		std::size_t size, std::error_code& err, std::size_t bptoffset = 0);

	/// ͬ��д������
	std::size_t SyncWriteFile(uint64_t offset, std::shared_ptr<std::vector<char>> &pBufferPtr,
		std::size_t size, std::error_code& err, std::size_t bptoffset = 0);

public:

	/// �첽�������¼�
	using AsyncPostHandleFun = std::function<void()>;
	uint32_t AsyncPostHandle(AsyncPostHandleFun handle);

	/// ��ȡSERVICE POOL(�貶��system_error�쳣)
	std::shared_ptr<IoServicePool>& IoFile::GetIoServicePool();

public:

	/// ��ȡ�ļ���С
	int64_t GetFileSize() { return m_nFileSize.QuadPart; }

	/// ��ȡ�ļ����
	HANDLE GetFileHandle() { return m_hFile; }

private:

	IoFileImpPtr m_pIoFileImpPtr;

	HANDLE m_hFile;

	LARGE_INTEGER m_nFileSize;			// �ļ���С(��λ���ֽ�)

	bool m_bStop;
};

END_LIBNETIO_NAME_SPACE

#endif

