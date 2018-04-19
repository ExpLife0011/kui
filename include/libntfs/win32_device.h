#pragma once

#include "ntfsimp.h"

START_NAMESPACE_NTFS

struct tagNtfsDriverParam
{
	TCHAR szDriver;
	HANDLE hDriver;				// ����
	HANDLE hReadWriteEvent;		// ��д���
	unsigned char  *pUnalignedBuf;
	NtfsLock lockReadWrite;
	tagNtfsDriverParam()
		: szDriver(L'\0')
		, hDriver(INVALID_HANDLE_VALUE)
		, hReadWriteEvent(NULL)
		, pUnalignedBuf(NULL)
	{
	}
};

class NtfsDriver : public NtfsImp
{
public:

	NtfsDriver();

	virtual ~NtfsDriver();

public:

	/// ��ʼ��
	virtual DWORD Init(void *pParam = NULL, unsigned long flags = NTFS_IMP_RDONLY, const char *name  = NULL);

	/// �ͷ�
	virtual void Release();

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

private:

	/// ������
	signed long on_device_readdataex(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize);

	/// д����
	signed long on_device_writedataex(void *pParam, unsigned __int64  ullOffSet, const void *pBuffer, unsigned long dwSize);

};

END_NAMESPACE_NTFS
