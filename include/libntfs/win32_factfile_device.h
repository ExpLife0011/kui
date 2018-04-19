#pragma once

#include "win32_disk_device.h"

START_NAMESPACE_NTFS

#pragma pack(push, 1)
struct tagNtfsFactFileParam : tagNtfsDiskParam
{
	TCHAR szDiskFile[MAX_PATH];
	HANDLE hFile;				// ���
	HANDLE hReadWriteEvent;		// ��д���
	NtfsLock lockReadWrite;
	unsigned char* pDataAlignedBuf;
	unsigned long DataAlignedSize;
	bool FileFlagNoBuffering;
	tagNtfsFactFileParam()
		: hFile(INVALID_HANDLE_VALUE)
		, hReadWriteEvent(NULL)
		, pDataAlignedBuf(NULL)
		, DataAlignedSize(SECTOR_SIZE) // 512B
		, FileFlagNoBuffering(false)
	{
		::memset(szDiskFile, 0, sizeof(szDiskFile));
	}
};

#pragma pack(pop)


class NtfsFactFileDevice : public NtfsDiskDevice
{
public:

	NtfsFactFileDevice();

	virtual ~NtfsFactFileDevice();

public:

	/// ��ʼ��
	virtual DWORD Init(void *pParam = NULL, unsigned long flags = NTFS_IMP_NONE, const char *name  = NULL);

	/// �ͷ�
	virtual void Release();

public:

	/// �������Ƿ���Ч
	virtual bool CheckParamInfo(void *pParam);

	/// ������
	virtual unsigned long on_device_readdataformdisk(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize);

	/// д����
	virtual unsigned long on_device_writedatatodisk(void *pParam, unsigned __int64  ullOffSet, const void *pBuffer, unsigned long dwSize);

public:

	/// ��ʼ��
	virtual signed long on_device_init(void *pParam);

	/// �ͷ�
	virtual signed long on_device_release(void *pParam);

	/// ˢ�´���
	virtual signed long on_device_sync(void *pParam);

private:

	/// ������
	signed long on_device_readdataex(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize);

	/// д����
	signed long on_device_writedataex(void *pParam, unsigned __int64  ullOffSet, const void *pBuffer, unsigned long dwSize);

};

END_NAMESPACE_NTFS
