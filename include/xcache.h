#pragma once

#ifndef LIBXCACHE_EXPORTS
#ifdef _WIN64
#pragma comment(lib, "kcache64")
#else
#pragma comment(lib, "kcache")
#endif 
#endif

#define FUN_DEVICE_NAME			L"\\Device\\xcache"
#define FUN_DOS_NAME			L"\\DosDevices\\xcache"
#define FUN_APP_NAME			L"\\\\.\\xcache"
#define SERVICE_NAME			L"kcache"

#define IOCTL_START_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x901, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ��������
#define IOCTL_STOP_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ֹͣ����
#define IOCTL_QUERY_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x903, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ��ѯ����
#define IOCTL_SETADD_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x904, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ������Ҫ���ݵ�����
#define IOCTL_CHECK_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x905, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ����Ƿ��ⲿ����
#define IOCTL_UPDATE_XCACHE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x906, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ���»���
#define IOCTL_GETBLOCKNUM_XCACHE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x907, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ��ȡ�������������
#define IOCTL_GETBLOCKNUMX_XCACHE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x908, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ��ȡ�������������
#define IOCTL_GETBLOCKLIST_XCACHE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x909, METHOD_BUFFERED, FILE_ANY_ACCESS)	// ��ȡ�������������

// ===================================== old device ===============================================
#define FUN_DEVICE_OLDNAME		L"\\Device\\KCache"
#define FUN_DOS_OLDNAME			L"\\DosDevices\\KCache"
#define FUN_APP_OLDNAME			L"\\\\.\\KCache"

#define FILE_DEVICE_YCACHE		0x7676
// =================================================================================================

#pragma pack(push, 1)

typedef struct tagDriverLetterInfo
{
	WCHAR wDriverLetter;			// �̷�
	ULONGLONG ullDriverSize;		// ��С(������)
	BOOLEAN bEnable;				// ��������
} DRIVERLETTERINFO, *PDRIVERLETTERINFO;
typedef struct tagStartCacheParam
{
	ULONG ulIndexCacheInfoId;		// ����ID
	ULONG ulCacheSize;				// �ܴ�С(MB)
	ULONG ulBlockSize;				// �����С(KB)
	WCHAR wSSDDriverLetter;			// �̷�
	ULONG ulSSDCacheSize;			// �ܴ�С(MB)
	ULONG ulCount;					// �̷�����
	DRIVERLETTERINFO wDriverInfo[1];// �̷���Ϣ
} STARTCACHEPARAM, *PSTARTCACHEPARAM;

typedef struct  tagDiskStatistics
{
	WCHAR		wDriverLetter;		// �̷�(��д)
	ULONG		ulUserCount;		// ��ʹ�ø���
	ULONGLONG	ullAllReadSize;		// �ܶ�ȡ
	ULONGLONG	ullCacheReadSize;	// �����ȡ
	ULONGLONG	ullAllWriteSize;	// ��д��
	ULONGLONG	ullCacheWriteSize;	// ����д��
} DISKSTATISTICS, *PDISKSTATISTICS;
typedef struct tagCacheStatistics
{
	ULONG		ulIndexCacheInfoId;
	ULONG 		ulSetCacheSize;		// �ܴ�С(MB)
	ULONG 		ulSetBlockSize;		// �����С(KB)
	WCHAR 		wSetSSDDriverLetter;// �̷�
	ULONG 		ulSetSSDCacheSize;	// �ܴ�С(MB)

	ULONG		ulCacheSize;		// �ܴ�С(������)
	ULONG		ulBlockSize;		// �����С(������)
	ULONG		ulUserCount;		// ��ʹ�ø���
	ULONGLONG	ullAllReadSize;		// �ܶ�ȡ
	ULONGLONG	ullCacheReadSize;	// �����ȡ
	ULONGLONG	ullAllWriteSize;	// ��д��
	ULONGLONG	ullCacheWriteSize;	// ����д��
	ULONG		ulDiskNumber;
} CACHESTATISTICS, *PCACHESTATISTICS;

typedef struct tagSetAddCacheParam
{
	WCHAR wDriverLetter;			// �̷�
	ULONGLONG ullStartSector;		// ��ʼ����
	ULONG ulNumberSector;			// ��������
} SETADDCACHEPARAM, *PSETADDCACHEPARAM;

typedef struct tagBlockNumberInfo
{
	ULONG ulCurPrvNumber;
	ULONG ulCurNexNumber;
	ULONG ulNumber;
	ULONGLONG ullDLinkSize;
} BLOCKNUMBERINFO, *PBLOCKNUMBERINFO;

typedef struct tagBlockNumberInfox
{
	ULONG ulCurPrvNumber0;
	ULONG ulCurNexNumber0;
	ULONG ulNumber0;
	ULONG ulNumberUsed0;
	ULONG ulCurPrvNumber1;
	ULONG ulCurNexNumber1;
	ULONG ulNumber1;
	ULONG ulNumberUsed1;
	ULONG ulCurPrvNumber2;
	ULONG ulCurNexNumber2;
	ULONG ulNumber2;
	ULONG ulNumberUsed2;
	ULONG ulCurPrvNumber3;
	ULONG ulCurNexNumber3;
	ULONG ulNumber3;
	ULONG ulNumberUsed3;
	ULONGLONG ullDLinkSize;
	ULONGLONG ullAllUseCount;		// �ܷ��ʼ���
	ULONGLONG ullAllNoUseCount;		// ��ɾ������
	ULONGLONG ullAllRemoveCount;	// ����̭����
	ULONGLONG ullAllMoveCount;		// ���ƶ�����
	ULONGLONG ullAllLoopCount;		// ��ѭ������
	ULONG ulAccessCountB0;		// ����ʴ���
	ULONG ulAccessTimeB0;		// �����ʱ��
	ULONG ulAccessCountE0;		// ����ʴ���
	ULONG ulAccessTimeE0;		// �����ʱ��
	ULONG ulAccessCountB1;		// ����ʴ���
	ULONG ulAccessTimeB1;		// �����ʱ��
	ULONG ulAccessCountE1;		// ����ʴ���
	ULONG ulAccessTimeE1;		// �����ʱ��
	ULONG ulMaxAccessCount;		// �滻����ʴ���
	ULONG ulCount[15];
} BLOCKNUMBERINFOX, *PBLOCKNUMBERINFOX;

typedef struct tagBlockListItem
{
	ULONGLONG ullStartSector;
	ULONG     ulAccessCount;
} BLOCKLISTITEM, *PBLOCKLISTITEM;

#pragma pack(pop)

/// ����NT����
DWORD StartNTDriver(LPCTSTR lpDriverName = SERVICE_NAME);

/// �ر�NT����
DWORD StopNTDriver(LPCTSTR lpDriverName = SERVICE_NAME);

/// ��װNT����
DWORD InstallNTDriver(LPCTSTR lpDriverName = SERVICE_NAME);

/// ж��NT����
DWORD UnInstallNTDriver(LPCTSTR lpDriverName = SERVICE_NAME);

/// ��������
DWORD StartCache(PSTARTCACHEPARAM pStartCacheParam, DWORD dwSize);

/// ֹͣ����
DWORD StopCache(ULONG ulIndexCacheInfoId);

/// ���»���
DWORD UpdateCache(DWORD dwIndexCacheInfoId, PDRIVERLETTERINFO pDriverLetterInfo, DWORD dwCount);

/// ��ȡ������Ϣ
DWORD GetCacheInfo(void *pBuffer, DWORD dwSize);

/// ��ȡ������Ϣ
DWORD CheckCacheInfo(PBOOLEAN pbEnable, WCHAR wDriverLetter = 0);

/// �������CACHE
DWORD IoSetAddCache(WCHAR wDriverLetter, ULONGLONG ullStartSector, ULONG ulNumberSector, PHANDLE m_phCacheHandle = NULL);

/// ��ȡ�����������Ϣ
DWORD GetBlockNumberInfo(ULONG ulIndexCacheInfoId, PBLOCKNUMBERINFO pBlockNumberInfo);

DWORD GetBlockNumberInfoX(ULONG ulIndexCacheInfoId, PBLOCKNUMBERINFOX pBlockNumberInfo);
DWORD GetBlockListInfo(ULONG ulIndexCacheInfoId, PBLOCKLISTITEM pBlockInfo, PULONG pCount);