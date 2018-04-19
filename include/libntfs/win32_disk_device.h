#pragma once

#include "ntfsimp.h"

START_NAMESPACE_NTFS

#pragma pack(push, 1)
struct tagNtfsDiskParam
{
	unsigned long SectorSize;
	unsigned char szDiskBootInfo[SECTOR_SIZE];
	unsigned __int64 TotalReadSize;
	unsigned __int64 TotalWriteSize;
	unsigned __int64 ullOffSet;
	int iVolumeIndex;
	tagNtfsDiskParam()
		: SectorSize(SECTOR_SIZE)
		, TotalReadSize(0)
		, TotalWriteSize(0)
		, ullOffSet(0)
		, iVolumeIndex(-1)
	{
		::memset(szDiskBootInfo, 0, sizeof(szDiskBootInfo));
	}
};
#pragma pack(pop)


class NtfsDiskDevice : public NtfsImp
{
public:

	NtfsDiskDevice();

	virtual ~NtfsDiskDevice();

public:

	/// ��ʼ��
	virtual DWORD Init(void *pParam = NULL, unsigned long flags = NTFS_IMP_NONE, const char *name  = NULL);

	/// �ͷ�
	virtual void Release();

public:

	/// �������Ƿ���Ч
	virtual bool CheckParamInfo(void *pParam) = 0;

	/// ������
	virtual unsigned long on_device_readdataformdisk(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize) = 0;

	/// д����
	virtual unsigned long on_device_writedatatodisk(void *pParam, unsigned __int64  ullOffSet, const void *pBuffer, unsigned long dwSize) = 0;

public:

	/// ��ʼ��
	virtual signed long on_device_init(void *pParam);

	/// �ͷ�
	virtual signed long on_device_release(void *pParam);

	/// ���õ���������С
	virtual signed long on_device_setsectorsize(void *pParam, unsigned short bytespersector);

	/// ������
	virtual signed long on_device_readdata(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize);

	/// д����
	virtual signed long on_device_writedata(void *pParam, unsigned __int64 ullOffSet, const void *pBuffer, unsigned long dwSize);

	/// ������
	virtual signed long on_device_readsector(void *pParam, unsigned __int64 ullStartSector,  unsigned long dwNumber, void *pBuffer);

	/// д����
	virtual signed long on_device_writesector(void *pParam, unsigned __int64  ullStartSector, unsigned long dwNumber, const void *pBuffer);

	/// ˢ�´���
	virtual signed long on_device_sync(void *pParam);

	/// ��Ե�ַ����Ե�ַת��
	virtual signed long on_device_daddresstofaddress(void *pParam, unsigned __int64  ullOffSet,
		unsigned __int64*  pullOffSet);

public:

	/// �ж��Ƿ�EFI����(pMbrBuffer:��һ���������ݣ�pGptBuffer:�ڶ�����������)
	static signed long checkefiboot(const void *pMbrBuffer, const void *pGptBuffer);
};

END_NAMESPACE_NTFS
