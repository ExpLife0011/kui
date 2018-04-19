#pragma once

#include "kcore.h"

START_NAMESPACE_KCORE

#define MAX_RESTORE_NUM					32		// ���ԭ�����

// �����̨��������
#define COM_SM_HEART					0x0001		// ����̨������������(��)
#define COM_SM_ADDIMAGE					0x0002		// ��Ӿ���(����:name(string) + size(DWORD)<��λ:G> + cachesize(ULONGLONG)<��λ:B>)
#define COM_SM_ADDRESTPOINT				0x0003		// ��ӻ�ԭ��(����:add(bool) + ip(DWORD) + id(DWORD) + name(string))
#define COM_SM_DELIMAGE					0x0004		// ɾ������(����:cout(DWORD) + delete(bool) + array of id(DWORD))
#define COM_SM_DELRESTPOINT				0x0005		// ɾ����ԭ��(����:id(DWORD) + rstid(DWORD) + deletefile(bool))
#define COM_SM_MODIFYIMAGE				0x0006		// �޸ľ�����Ϣ(����:id(DWORD) + cachesize(ULONGLONG)<��λ:B>)
#define COM_SM_SETAPPLYPOINT			0x0007		// ���û�ԭ�㵱ǰӦ��(����:id(DWORD) + rstid(DWORD))
#define COM_SM_MERGERESTPOINT			0x0008		// �ϲ���ԭ��(����:id(DWORD) + rstid(DWORD) + type((DWORD)0:�ϲ� 1:״̬ 2:ȡ���ϲ�)
#define COM_SM_CHECKPASWORD				0x0009		// ����ϴ���������(����:password(string)); ���:count(DWORD) + array of (id(DWORD) + name(string) + port(WORD)
#define COM_SM_GETCLIENTEX				0x000a		// ��ȡ�ͻ���ͳ����Ϣ(���: count(DWORD) + array of stat(tagStatistics)
#define COM_SM_GETGAMEDISKEX			0x000b		// ��ȡ��Ϸ��ͳ����Ϣ(����:ip(DWORD) + driver(TCHAR) + detail(bool)) (���: maxsendspeed(DWORD) + sendspeed(DWORD) + totalsendbytes(ULONGLONG) + count(DWORD) + array of stat(tagStatistics)
#define COM_SM_GETCACHEINFOEX			0x000c		// ��ȡ����ͳ����Ϣ(����:count(DWORD) + array of driver(TCHAR)) (���:count(DWORD) + array of (driver(TCHAR) + start(bool) + hit(double)))
#define COM_SM_GETHOSTMEMORY			0x000d		// ��ȡ�����ڴ���Ϣ(���:total(DWORD) + free(DWOR)
#define COM_SM_NOTIFYCACHE				0x000e		// ˢ�»���(��)
#define COM_SM_SETDHCPANDTFTP			0x000f		// �����Ƿ���DHCP��TFTP����(����:enable(bool))
#define COM_SM_MIRRORREADFILE			0x0010		// ��ȡ�����ļ�����(����:id(DWORD) + restid(DWORD) + offset(LARGE_INTEGER) + size(DWORD) + isdatafile(bool) ���: size(DWORD) + data(char*)
#define COM_SM_GETALLMIRRORINFOEX		0x0011		// ��ȡ������Ϣ(���: count(DWORD) + array of info(MIRRORINFOEX)
#define COM_SM_NOTIFYMIRRORSYNC			0x0012		// ֪ͨ����ͬ��
#define COM_SM_GETSUPERADMINIP			0x0013		// ��ȡ��������Ա��IP(����: id(DWORD) ����: ip(DWORD))
#define COM_SM_GETALLMIRRORINFO			0x0014		// ��ȡ������Ϣ(���: count(DWORD) + array of info(id(DWORD) + restnum(DWORD) + lastrestid(DWORD) + userestid(DWORD))
#define COM_SM_SETMIRRORDELETE			0x0015		// ���þ���ж��ʱ�ļ�ɾ��״̬(����:cout(DWORD) + delete(bool) + array of id(DWORD))
#define COM_SM_CLIENTOPTIONADMIN		0x0016		// �ͻ������ù���Ա(����:mirrorid(DWORD) + machinename(string) + startorstop(bool) + saveorcancel(bool) + rspname(string))
#define COM_SM_CLIENTGETIMAGEINFO		0x0017		// �ͻ�����ȡ������Ϣ(����:password(string)) + machinename(string); ���: supermirrorid(DWORD) + issave(bool) + count(DWORD) + array of (id(DWORD) + name(string))
#define COM_SM_GETALLMIRRORINFOEXEX		0x0018		// ��ȡ������Ϣ(���: flag(DWORD) + count(DWORD) + array of info(MIRRORINFOEX)
#define COM_SM_GETLOCALPNPINFO			0x0019		// ��ȡ����PNP��Ϣ(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string))
													// ���: count(DWORD) + array of info(name(string) + size(LARGE_INTEGER) + time(FILETIME))
#define COM_SM_LOCALPNPREADFILE			0x001a		// ��ȡ�����ļ�����(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string) + name(string) + offset(LARGE_INTEGER) + size(DWORD))
													// ���: size(DWORD) + data(char*)
#define COM_SM_NOTIFYLOCALPNPSYNC		0x001b		// ֪ͨ����PNPͬ��
#define COM_SM_INFTOLOCALPARAM			0x001c		// ����INF������PNP����(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string) + DbOpt(DWORD))
#define COM_SM_REMOVELOCALPNP			0x001d		// ɾ������PNP (����: count(DWORD) + array of info(VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string))
#define COM_SM_MIRROR_READ_DATA			0x001e		// �Ӿ����ȡ����
#define COM_SM_SSD_PNP					0x001f		// ����SSDPNP
#define COM_SM_PNP_FILE_LIST			0x0020		// PNP�ļ��б�
#define COM_SM_GETGAMEDISKNEW			0x0021		// ��ȡ����Ϸ��ͳ����Ϣ(����:ip(DWORD) + driver(TCHAR) + detail(bool)) (���: maxsendspeed(DWORD) + sendspeed(DWORD) + totalsendbytes(ULONGLONG) + maxrecvspeed(DWORD) + recvspeed(DWORD) + totalrecvbytes(ULONGLONG) + count(DWORD) + array of stat(tagStatistics)

//�Կ�pnp
#define COM_SM_USERDISKREADFILE			0x0022		// ��ȡ�Կ������ļ�����(����:id(DWORD) + restid(DWORD) + offset(LARGE_INTEGER) + size(DWORD) + isdatafile(bool) ���: size(DWORD) + data(char*)
#define COM_SM_GETALLUSERDISKINFOEX		0x0023		// ��ȡ�Կ�������Ϣ(���: USERDISKINFOEX

#define COM_SM_INFTOLOCALDPARAM			0x0024		// �����Կ�INF������PNP����(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string) + DbOpt(DWORD))
#define COM_SM_GETLOCALDPNPINFO			0x0025		// ��ȡ����PNP��Ϣ(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string))
													// ���: count(DWORD) + array of info(name(string) + size(LARGE_INTEGER) + time(FILETIME))
#define COM_SM_LOCALDPNPREADFILE		0x0026		// ��ȡ�����ļ�����(����: VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string) + name(string) + offset(LARGE_INTEGER) + size(DWORD))
													// ���: size(DWORD) + data(char*)

#define COM_SM_NOTIFYMAKEDPNP			0x0027      //֪ͨ����dpnp
#define COM_SM_REMOVELOCALDPNP			0x0028		// ɾ������PNP (����: count(DWORD) + array of info(VenorId(WORD) + DeviceId(WORD) + SubSys(DWORD) + Rev(BYTE) + Os(string))
#define COM_SM_NOTIFYREMAKEUSERDISK		0x0029      //֪ͨ��������UserDisk(����:type((DWORD)0:���� 1:״̬ 2:ȡ������)
#define COM_SM_NOTIFYUSERDISKSYNC		0x002A		// ֪ͨ�Կ�����ͬ��

#define COM_SM_NOTIFYDBOPTION			0x002B      //֪ͨ��ȡ���ݿ�ϵͳѡ��
#define COM_SM_REPORTSVRIPINFO			0x002C		//�ϱ�������ip��Ϣ�����룺tstring + count(DWORD) + array of info(SVRIPINFO)
													//�����std::map<tstring, SVRIPINFOVEC>)
// ����״̬
#define STATUS_NOTFINDIMAGEDRIVER		0x0001		// û�з��־�����
#define STATUS_IMAGENAMEEXIST			0x0002		// �����Ѿ�����
#define STATUS_IMAGESTARTFAIL			0x0003		// ��������ʧ��
#define STATUS_UNKOWNERROR				0x0004		// δ֪����
#define STATUS_INSERTDBERROR			0x0005		// �������ݿ�ʧ��
#define STATUS_IMAGENOTEXIST			0x0006		// ���񲻴���
#define STATUS_PASSWORDERROR			0x0007		// �������
#define STATUS_PERMISSIONDENIED			0x0008		// Ȩ�޲�����������ֹ
#define STATUS_GETDBERROR				0x0009		// ��ȡ���ݿ�ʧ��
#define STATUS_RSPOINTNOTEXIST			0x000a		// ��ԭ�㲻����
#define STATUS_RSPOINTSTARTFAIL			0x000b		// ��ԭ������ʧ��
#define STATUS_TOOMORERSPOINT			0x000c		// ̫��Ļ�ԭ��
#define STATUS_CACHESTARTFAIL			0x000d		// ��������ʧ��
#define STATUS_HAVEMERGERSPOINT			0x000e		// ���кϲ�������������
#define STATUS_DELDBERROR				0x000f		// ɾ�����ݿ��¼ʧ��
#define STATUS_PARAMINVALID				0x0010		// ������Ч
#define STATUS_NOTENOUGHFREESPACE		0x0011		// û���㹻��ʣ��ռ�
#define STATUS_SUPERADMINEXIST			0x0012		// ���ڳ�������Ա
#define STATUS_ADMINEXIST				0x0013		// ���ڹ���Ա
#define STATUS_HAVEADMIN				0x0014		// ���ǹ���Ա
#define STATUS_NOTONLINE				0x0015		// �ͻ���������
#define STATUS_OPTFORBID				0x0016		// ��ֹ�ͻ����ϴ��򿪳���
#define STATUS_LOCALPNPNOFILE			0x0017		// ����PNP�ļ�������


// ����ͬ��״̬
#define MIRRORUPDATE_FINISH				0x0001
#define MIRRORUPDATE_ERROR				0x0002
#define MIRRORUPDATE_WAITING			0x0003		// �����Ŷ�
#define MIRRORUPDATE_CHECKSPACE			0x0004		// �����̿ռ�
#define MIRRORUPDATE_CONNECT			0x0005		// ����������ͨѶ
#define MIRRORUPDATE_INDEXUPDATE		0x0006		// �����ļ�ͬ��
#define MIRRORUPDATE_DATAUPDATE			0x0007		// �����ļ�ͬ��

// ����PNPͬ��״̬
#define LOCALPNPUPDATE_FINISH			0x0001
#define LOCALPNPUPDATE_ERROR			0x0002
#define LOCALPNPUPDATE_WAITING			0x0003		// �����Ŷ�
#define LOCALPNPUPDATE_CONNECT			0x0004		// ����������ͨѶ
#define LOCALPNPUPDATE_DATAUPDATE		0x0005		// �����ļ�ͬ��


// �����Կ�ͬ��״̬
#define USERDISKUPDATE_FINISH				0x0001
#define USERDISKUPDATE_ERROR				0x0002
#define USERDISKUPDATE_WAITING				0x0003		// �����Ŷ�
#define USERDISKUPDATE_CHECKSPACE			0x0004		// �����̿ռ�
#define USERDISKUPDATE_CONNECT				0x0005		// ����������ͨѶ
#define USERDISKUPDATE_INDEXUPDATE			0x0006		// �����ļ�ͬ��
#define USERDISKUPDATE_DATAUPDATE			0x0007		// �����ļ�ͬ��

// ���տ��С
#define BLOCK_SIZE						0x100000L
// һ����ռ��С
#define SECTOR_SIZE						512


// ��������
#define CONNECT_TYPE_UNKOWN				0		// δ֪����
#define CONNECT_TYPE_FILEDISK			1		// �ļ��������� (������PNPʹ��)
#define CONNECT_TYPE_USERMAIN			2		// ������������ (�������ʹ��)
#define CONNECT_TYPE_USERREAD			3		// ������Ԥ������ (Ԥ��ʹ��)
#define CONNECT_TYPE_ADMIN				4		// ����Ա����ɾ����ʱ�ļ�(������ԭ��)
#define CONNECT_TYPE_SUPER_ADMIN		5		// ��������Ա��ֱ�Ӳ�������ϵͳ(���������ؼ��ϴ�����ʹ��)

/// ��Ϣ��
#define FRAME_START_FLAG				'.mgs'
#define FRAME_CMD_QUERY					0x01
#define FRAME_CMD_READ					0x02
#define FRAME_CMD_WRITE					0x03
#define FRAME_CMD_INFO					0x04
#define FRAME_CMD_STOP					0x05
#define FRAME_CMD_HEART					0x06
#define FRAME_CMD_WRITEBACK_ACTION		0x07
#define FRAME_CMD_GAMEDISKINFO			0x08
#define FRAME_CMD_READ_EX				0x09
#define FRAME_CMD_WRITE_EX				0x0a
#define FRAME_CMD_READ_NEW				0x0b
#define FRAME_CMD_WRITE_NEW				0x0c
#define FRAME_CMD_QUERY_NEW				0x0d
#define FRAME_CMD_INFO_NEW				0x0e
#define FRAME_CMD_HEART_NEW				0x0f
#define FRAME_CMD_GAMEDISKINFO_NEW		0x10
#define FRAME_CMD_WRITEBACK_ACTION_NEW	0x11

#pragma warning(disable:4200)

#pragma pack(push, 1)

/// ��������ͷ��
typedef struct tagVDiskHeader
{
	ULONG			flag;		// FRAME_START_FLAG
	ULONG			length;		// total length
	ULONG			command;	// �����
	ULONG			status;		// ״̬
} VDISKHEADER, *LPVDISKHEADER;

/// ���̽�������
typedef struct VDiskRequest : public tagVDiskHeader
{
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
			LONGLONG		pkg_id;
		}Read;
		struct
		{
			LARGE_INTEGER	start;
			ULONG			number;
			LONGLONG		pkg_id;
		}Write;
		struct  
		{
			UCHAR			type;		// ��������
			DWORD			rspid;		// ��ԭ��ID
			DWORD			remoteip;	// �ͻ���IP
			UCHAR			isreconnect;// �Ƿ�����
		}ConnectInfo;
	};

	CHAR			data[0];		// ����

} VDISKREQUEST,*LPVDISKREQUEST;

/// ���̽�������
typedef struct VDiskRequestNew : public tagVDiskHeader
{
	union
	{
		struct
		{
			ULONG			resv1[8];
		}Param;
		struct
		{
			LONGLONG		pkg_id;
			LARGE_INTEGER	start;
			ULONG			number;
		}Read;
		struct
		{
			LONGLONG		pkg_id;
			LARGE_INTEGER	start;
			ULONG			number;
		}Write;
		struct
		{
			LONGLONG		pkg_id;
			UCHAR			type;		// ��������
			DWORD			rspid;		// ��ԭ��ID
			DWORD			remoteip;	// �ͻ���IP
			UCHAR			isreconnect;// �Ƿ�����
		}ConnectInfo;
		struct
		{
			LONGLONG		pkg_id;
		}Heart, Query, GameDiskInfo, WritebackAction;
	};

	CHAR			data[0];		// ����

} VDISKREQUESTNEW, *LPVDISKREQUESTNEW;

/// ����Ӧ��
typedef struct VDiskAck : public tagVDiskHeader
{
	CHAR			data[0];		// ����
} VDISKACK, *LPVDISKACK;

typedef struct VDiskAckEx : public tagVDiskHeader
{
	LARGE_INTEGER	sector;		//in sectors
	ULONG			number;		//in sectors
	CHAR			data[0];
} VDISKACKEX, *LPVDISKACKEX;

typedef struct VDiskAckNew : public tagVDiskHeader
{
	union
	{
		struct
		{
			ULONG			resv1[8];
		}Param;
		struct
		{
			LONGLONG		pkg_id;
			LARGE_INTEGER	start;
			ULONG			number;
		}Read;
		struct
		{
			LONGLONG		pkg_id;
			LARGE_INTEGER	start;
			ULONG			number;
		}Write;
		struct
		{
			LONGLONG		pkg_id;
		}ConnectInfo, Heart, Query, GameDiskInfo, WritebackAction;
	};

	CHAR			data[0];		// ����
} VDISKACKNEW, *LPVDISKACKNEW;


typedef struct WriteBackSettings
{
	ULONG			mem_size;		//  ������
	ULONG			file_size;		//  ������
	ULONG			file_drive;		//	�ļ��̷�
	ULONG			use_unrecognized;// ʹ��δʶ���ڴ�
	ULONG			writeback_limit; //��д���� in Mbytes
	ULONG			reserved[2];
}WRITEBACK_SETTINGS, *PWRITEBACK_SETTINGS;

typedef struct PreReadSettings
{
	BYTE	bIsPreRead;
	BYTE	bBlockSize;				// K
	BYTE	bPreReadThread;			// Ԥ���߳�
	WORD	wReadOneCacheSize;		// K
	WORD	wAllReadCacheSize;		// K
}PREREADSETTINGS, *PPREREADSETTINGS;

#pragma pack(pop)

#define SENDREVBUFFER_SIZE	BLOCK_SIZE + sizeof(VDiskRequest)

#define IMAGE_PATH_NAME		TEXT("kimage")
#define WRITEBACK_PATH_NAME	TEXT("kwrite")
#define USERDISK_NAME		TEXT("userdisk")

END_NAMESPACE_KCORE