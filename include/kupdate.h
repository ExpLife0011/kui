#pragma once

#ifndef HAVE_NOT_USE_KCORE
#include "kcore.h"
#endif

// �����̨��������
#define COM_SM_HEART							0x0001		// ����̨������������
#define COM_SM_DELETEGAME						0x0002		// ɾ����Ϸ: ����:gid(DWORD) + strServerPath(tstring)
#define COM_SM_ADDMOVEGAME						0x0003		// �����Ϸ���ƶ����У�����:gid(DWORD) + speed(DWORD) + strName(tstring) + strSrcPath(tstring) + strDestPath(tstring)
#define COM_SM_CLEARMOVEGAME					0x0004		// ����ƶ����У�����:gid(DWORD)(0:�����������)
#define COM_SM_GETMOVEGAMESTATUS				0x0005		// ��ȡ�ƶ���������״̬��Ϣ������:gid(DWORD)(0:��ȡ��������״̬��Ϣ) 
															// ���:gid(DWORD) + Status(DWORD) + NeedsUpdateBytes(__int64) + UpdatedBytes(__int64)
															// ���:count(DWORD) + count(DWORD) + count(DWORD) + 3 * array of (gid(DWORD) + Status(DWORD) + NeedsUpdateBytes(__int64) + UpdatedBytes(__int64))

// =================== P2P ����   ===================
#define P2P_STATUS_WAITING						0x00000000L
#define P2P_STATUS_DWNIDX						0x00000001L
#define P2P_STATUS_COMPARE						0x00000002L
#define P2P_STATUS_DOWNING						0x00000003L
#define P2P_STATUS_COMMIT						0x00000004L
#define P2P_STATUS_ACTION						0x00000005L
#define P2P_STATUS_WAITCOMMIT					0x00000006L
#define P2P_STATUS_SUSPEND						0x00000007L
#define P2P_STATUS_WAITCOMPARE					0x00000008L
#define P2P_STATUS_PRECOMPARE					0x00000009L
#define P2P_STATUS_AFTERCOMPARE					0x0000000aL
#define P2P_STATUS_ERROR						0xfe000000L
#define P2P_STATUS_FINISH						0xff000000L

// �����̨��������
#define P2P_SM_ADDTASK							0x1001		//	�����������: ����:count(DWORD) + array of (gid(DWORD) + force(DWORD:1/0��ʾ�Ƿ�ǿ�Ƹ���))
#define P2P_SM_STOPTASK							0x1002		//	ֹͣ��������: ����:count(DWORD) + array of (gid(DWORD)).
#define P2P_SM_SUSPENDTASK						0x1003		//	��ͣ��������: ����:count(DWORD) + array of (gid(DWORD)).
#define P2P_SM_RESUMETASK						0x1004		//	�ָ���������: ����:count(DWORD) + array of (gid(DWORD)).
#define P2P_SM_ADJUSTTASK						0x1005		//	�ö����õ�:   ����:gid(DWORD) + flag(DWORD:1:0)(�ö����õ�)
#define P2P_SM_GETALLTASK						0x1006		//	ȡ�������������״̬:���:xml��string).
#define P2P_SM_GETALLTASKID						0x1007		//	��ȡ������������ID: ���:count(DWORD) + array of (gid(DWORD)).
#define P2P_SM_FORCEUPDATE						0x1008		//  ֪ͨ������ǿ���޸�ĳ��gid����Ϸ: ����:gid(DWORD).
#define P2P_SM_UPDATELICENCE					0x1009		//	�������֤������: ����: flag1(DWORD) + flag2(DWORD) + nid(DWORD) +																  //  lasttime(DWORD) + session(tstring)
#define P2P_SM_CHECKPORTMAP						0x100A		//	�������˿�ӳ���Ƿ���Ч: ����:port(DWORD)�����:result(bool)
#define P2P_SM_START_NOW						0x100B		//	������ʼ��������:count(DWORD) + array of (gid(DWORD)).
// =====================================================


// =================== UPDATE ����  ====================
#define PKG_SUCCESS								0
#define PKG_ERROR								1

// update define.
#define UPDATE_FLAG_FORCE_UPDATE				0x01		//	ǿ�Ƹ���
#define UPDATE_FLAG_QUICK_COMPARE				0x02		//	���ٸ���	//��ǿ�Ƹ���ֻ�ܶ�ѡһ��
#define UPDATE_FLAG_DELETE_MOREFILE				0x04		//	ִ��ɾ�������ļ�
#define UPDATE_FLAG_DELETE_GAME					0x08		//	�ռ䲻��ʱ��ִ��ɾ������ʵ͵���Ϸ��
#define UPDATE_FLAG_NOTIFY_MAKEIDX				0x10		//	�����������ڻ�����������ļ�����ʱ��֪ͨ������������������
#define UPDATE_FLAG_NOTNOTIFY_INXERROR			0x20		//	��֪ͨ�����޸�
#define UPDATE_FLAG_NOFILENOBUFFER				0x40		//	�������ļ�NOBUFFER
#define UPDATE_FLAG_SYNCPKGMODE					0x80		//	С������
#define	UPDATE_FLAG_IS_SSD						0x100		//	��SSD

#define UPDATE_STATUS_FINISH					0x01		//	���³ɹ����(��)
#define UPDATE_STAUTS_COMPARE					0x02		//	�Ա��ļ�
#define UPDATE_STATUS_UPDATE					0x04		//	�����ļ���
#define UPDATE_STATUS_DELETE_MOREFILE			0x08		//	ɾ�������ļ�
#define UPDATE_STATUS_DELETE_GAME				0x010		//	ɾ����Ϸ
#define UPDATE_STATUS_WAITING					0x020		//	�����Ŷ�
#define UPDATE_STATUS_FINISHALL					0x040		//	���³ɹ����
#define UPDATE_STATUS_ERROR						0xffffffff	//	���³���

#define DELETE_STATUS_FINISH					0x01		//	ɾ���ɹ����(��)
#define DELETE_STATUS_PATH						0x02		//	���㱾��·��
#define DELETE_STATUS_DELETE_GAME				0x04		//	ɾ����Ϸ
#define DELETE_STATUS_WAITING					0x08		//	�����Ŷ�
#define DELETE_STATUS_FINISHALL					0x10		//	ɾ���ɹ����
#define DELETE_STATUS_ERROR						0xffffffff	//	ɾ������

// ��������
#define LIBUPDATE_TYPE_PUSH						0
#define LIBUPDATE_TYPE_SYNC						1
#define LIBUPDATE_TYPE_UPDATE					2
#define LIBUPDATE_TYPE_MOVE						3

// ǿ��
#define PUSH_SM_SETGAME							0
#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN							64
#endif


// �����̨��������
#define UPDATE_SM_ADDTASK						0x2001		// ���ͬ������: ����:count(DWORD) + array of (gid(DWORD) + nForce(DWORD:1:0))
#define UPDATE_SM_ALLTASK						0x2002		// ˢ��ͬ������: ����:
#define UPDATE_SM_ALLTASKSTATUS					0x2003		// ȡ����ͬ�������״̬: ����:Detail(DWORD:1:0) ���:count(DWORD) + count(DWORD)  + 2 * array of (gid(DWORD) + Status(DWORD) + NeedsUpdateBytes(__int64) + UpdatedBytes(__int64) + Speed(DWORD)).
#define UPDATE_SM_ADJUSTTASK					0x2004		// �ö����õ�:   ����:gid(DWORD) + flag(DWORD:1:0)(�ö����õ�)
#define UPDATE_SM_FRESH							0x2005		// ˢ�¶���:	 ����:
#define UPDATE_SM_GETUPDATGAME					0x2006		// ��ȡ�������µ�״̬��Ϣ: �����xml�ļ�
#define UPDATE_SM_GETLOCALPATH					0x2007		// ��ȡ��Ϸ����·��������: count(DWORD) + array of gid(DWORD), ���: count(DWORD) + array of (gid(DWORD) + path(tstring))
#define UPDATE_SM_CANCELTASK					0x2008      // ȡ��ͬ����������:count(DWORD) + array of (gid(DWORD)

//	��kapp�ϱ������������ 
#define KUPDATE_APP_IDCUPDATECOUNTS				0x3301		// ���Ľ��ո��������ܺ�:����: �� ���: DWORD(����)
#define KUPDATE_APP_DOWNLIST					0x3303		// ��ȡ������Ϣ����Ϸ���У����������/�������أ�������: �� ���: DWORD(���������) + DWORD(��������)
#define KUPDATE_APP_DOWNSPEED					0x3304		// ��ȡ��ǰ�����ٶȣ�����: �� ���: DWORD(�ٶ� kb/s)
#define KUPDATE_APP_NEEDDOWNCOUNTS				0x3305		// ��ȡ���ذ汾�����İ汾��ƥ���(�Զ�����)ͳ�Ƹ���������: �� ���: DWORD(����)
#define KUPDATE_APP_UPFAILDCOUNTS				0x3306		// ��ȡ����ʧ��ͳ�Ƹ���(��ȡһ�Σ�����ֵ����)������: �� ���: DWORD(����)
#define KUPDATE_APP_SYNCFAILCOUNTS				0x3307		// ��ȡͬ��ʧ��ͳ�Ƹ���(��ȡһ�Σ�����ֵ����)������: �� ���: DWORD(����)
// =====================================================

START_NAMESPACE_KCORE

/// ������Ϸ����
typedef struct tagPushGameinfo
{
	DWORD gid;
	DWORD flag;
	DWORD speed;
	TCHAR Name[MAX_NAME_LEN];
	TCHAR SvrPath[MAX_PATH];
	TCHAR CliPath[MAX_PATH];
}tagPushGameinfo;

// idx file define
typedef enum Idx_UI_Status
{
	IDX_STATUS_CALLBACK			=   0,			//	only for exit,ui not show the status.
	IDX_STATUS_PARSE_OLDIDX		=	1,			//	only for check.wParam = 0, lParam = 0.
	IDX_STATUS_SCAN_DIRECTORY	=	2,			//	wParam = 0, lParam = 0.
	IDX_STATUS_GET_FILESIZE		=	3,			//	wParam = lowsize. lParam = highsize.
	IDX_STATUS_CALCRC			=	4,			//	wParam = progress.(n:0-100).lParam = 0
	IDX_STATUS_CHECK_IDXFILE	=	5,			//	only for check.wParam = progress(n:0-100), lParam = 0.
	IDX_STATUS_NOTIFY			=	6,			//	wParam = LPCTSTR. text tip information.
	IDX_NO_DIRECTORY			=	7,			//	
	IDX_STATUS_INFO				=	8,
	IDX_STATUS_FINISH			=   0xffffffff	//	wParam = erroce code.(0:success.).lParam:0
}Idx_UI_Status;

// ====================== �����ļ���ص������� ===============================

/// �����Ҫ�жϣ��򷵻�false��
typedef bool (__stdcall *IDXUICALLBACK)(void* pcookie, Idx_UI_Status status, DWORD_PTR wParam, DWORD_PTR lPraram);

/// ���������ļ�
DWORD __stdcall Idxfile_Make(DWORD gid, LPCTSTR gamename, LPCTSTR dir, IDXUICALLBACK pCallback = NULL, void* pCookie = NULL);

/// ��������
DWORD __stdcall Idxfile_Check(DWORD gid, LPCTSTR gamename, LPCTSTR dir, IDXUICALLBACK pCallback, void* pCookie);
/// 
DWORD __stdcall Idxfile_DeleteMorefileEx(LPCTSTR dir, char* pidxfile, DWORD length);

/// �õ������ļ��汾��.ʧ�ܷ���-1
DWORD __stdcall Idxfile_GetVersion(LPCTSTR file);

/// �õ��ڴ������ļ��汾��.ʧ�ܷ���-1
DWORD __stdcall Idxfile_GetVersionEx(char* pfile, DWORD length);

/// �������еõ���Ϸ�Ĵ�С.
__int64 __stdcall Idxfile_GetGameSize(LPCTSTR file);

/// �������еõ���Ϸ��gid,gname.
bool __stdcall Idxfile_GetGameInfo(LPCTSTR file, DWORD& gid, LPTSTR gname = NULL);

// =====================================================

// ======================== �ƶ�����״̬ ===============

#define UPDATE_STATUS_CLEAR			0xfffffffd		// �������
#define UPDATE_STATUS_ERRORALL		0xfffffffe		// ������Ϣ

// =====================================================

/// ͬ������
typedef struct tagUpdateParameter
{
	DWORD			cbSize;				//	=sizeof(tagUpdateParameter)
	DWORD			UpdateType;			//	LIBUPDATE_TYPE_*.
	DWORD			UpdateFlag;			//	UPDATE_FLAG_*
	DWORD			speed;				//	limit speed.(k/s).
	DWORD			gid;				//	game id.
	TCHAR			gname[MAX_PATH];	//	game name.
	TCHAR			srcdir[MAX_PATH];	//	server directory of game.
	TCHAR			dstdir[MAX_PATH];	//	client directory of game.
	TCHAR			svrip[MAX_PATH];	//	server ip.
	TCHAR			cliip[MAX_PATH];	//	client ip.
}tagUpdateParameter;

/// ͬ��״̬
typedef struct tagUpdateStatus
{
	DWORD   cbSize;						//	=sizeof(tagUpdateStatus)
	DWORD	Status;						//	����״̬
	__int64	m_qNeedsUpdateBytes;		//	��Ҫ���µ��ֽ���
	__int64	m_qUpdatedBytes;			//	�������µ��ֽ���
	DWORD	m_dwLeftTime;				//	����ʣ��ʱ��
	DWORD	m_dwSpeed;					//	�����ٶ�k/s
	TCHAR	Info[1024];					//	�����Ϣ���ļ������ߴ�����Ϣ
}tagUpdateStatus;

/// ɾ����Ϸ״̬
typedef struct tagDeleteGameStatus
{
	DWORD	Status;						//	ɾ��״̬
	TCHAR	Info[1024];					//	�����Ϣ���ļ������ߴ�����Ϣ
}tagDeleteGameStatus;

// ====================== ͬ����ص������� ===============================

typedef bool(__stdcall *UPDATE_BEFORE)(void * ptr, __int64 need_size);
typedef bool(__stdcall *UPDATE_AFTER)(void * ptr);
/// ��ʼ����
HANDLE __stdcall LibUpdate_StartUpdate(tagUpdateParameter& UpdateParameter);

/// ��ʼ����(���ص�)
HANDLE __stdcall LibUpdate_StartUpdateBeforeAfter(tagUpdateParameter& UpdateParameter, 
	UPDATE_BEFORE pBefore, void *pBeforCont, 
	UPDATE_AFTER pAfter, void *pAfterCont);

/// ֹͣ����
void __stdcall LibUpdate_StopUpdate(HANDLE handle);

/// ��ȡ����״̬
bool __stdcall LibUpdate_GetStatus(HANDLE handle, tagUpdateStatus& UpdateStatus);

// =====================================================

END_NAMESPACE_KCORE