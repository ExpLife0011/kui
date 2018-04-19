#ifndef __KDisk_inc_h__
#define __KDisk_inc_h__

#pragma once

#define KDISK_NTDEVICE_NAME		L"\\Device\\KDiskVol%c"
#define KDISK_DOSDEVICE_NAME	L"\\DosDevices\\KDiskVol%c"

#define KDISK_WIN32_NAME		TEXT("\\\\.\\KDiskVol%c")
#define KDISK_DRIVER_NAME_X86	TEXT("kdisk.sys")
#define KDISK_DRIVER_NAME_X64	TEXT("kdisk64.sys")
#define KDISK_SERVICE_NAME		TEXT("kdisk")

#define IOCTL_KDISK_MOUNT		CTL_CODE(0x8000, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS|FILE_WRITE_ACCESS)
#define IOCTL_KDISK_UNMOUNT		CTL_CODE(0x8000, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS|FILE_WRITE_ACCESS)

typedef struct MOUNTINFO
{
	ULONG   DiskType;
	ULONG	Ip;
	USHORT	Port;
	WCHAR	UserId[64];
}MOUNTINFO, *PMOUNTINFO;

#define CONNECT_TYPE_UNKOWN				0		// δ֪����
#define CONNECT_TYPE_FILEDISK			1		// �ļ��������� (������PNPʹ��)
#define CONNECT_TYPE_USERMAIN			2		// ������������ (�������ʹ��)
#define CONNECT_TYPE_USERREAD			3		// ������Ԥ������ (Ԥ��ʹ��)
#define CONNECT_TYPE_ADMIN				4		// ����Ա����ɾ����ʱ�ļ�(������ԭ��)
#define CONNECT_TYPE_SUPER_ADMIN		5		// ��������Ա��ֱ�Ӳ�������ϵͳ(���������ؼ��ϴ�����ʹ��)

#define FRAME_START_FLAG			'.mgs'
#define FRAME_CMD_QUERY				0x01
#define FRAME_CMD_READ				0x02
#define FRAME_CMD_WRITE				0x03
#define FRAME_CMD_INFO				0x04

#pragma warning(disable:4200)

#pragma pack(push, 1)

typedef struct VDiskRequest
{
	ULONG			flag;		// FRAME_START_FLAG
	ULONG			length;		// total length.
	ULONG			command;	// �����
	ULONG			status;		// ״̬

	union
	{
		struct
		{
			ULONG			resv1[8];
		}Param;
		struct
		{
			LARGE_INTEGER	start;
			ULONG			number;
		}Read;
		struct
		{
			LARGE_INTEGER	start;
			ULONG			number;
		}Write;
		struct  
		{
			UCHAR			type;	// ��������
		}ConnectInfo;
	};
	CHAR			data[0];		// ����
}VDISKREQUEST,*LPVDISKREQUEST;

typedef struct VDiskAck
{
	ULONG			flag;			// FRAME_START_FLAG
	ULONG			length;			// total length.
	ULONG			command;		// �����
	ULONG			status;			// ״̬
	CHAR			data[0];		// ����
}VDISKACK, *LPVDISKACK;

typedef struct WriteBackSettings
{
	ULONG			mem_size;		//  ������
	ULONG			file_size;		//  ������
	ULONG			file_drive;
	ULONG			reserved[4];
}WRITEBACK_SETTINGS, *PWRITEBACK_SETTINGS;

typedef struct PreReadSettings
{
	UCHAR	bIsPreRead;
	UCHAR	bBlockSize;				// K
	UCHAR	bPreReadThread;			// Ԥ���߳�
	USHORT	wReadOneCacheSize;		// K
	USHORT	wAllReadCacheSize;		// K
}PREREADSETTINGS, *PPREREADSETTINGS;

typedef struct tPtItem
{
	UCHAR	bState;
	UCHAR	bStartHead;
	UCHAR	bStartSec;
	UCHAR	bStartCyl;
	UCHAR	bType;
	UCHAR	bEndHead;
	UCHAR	bEndSec;
	UCHAR	bEndCyl;
	ULONG	dwStartSec;
	ULONG	dwTotalSecs;
}PTITEM, *LPPTITEM;

#pragma pack(pop)

#endif