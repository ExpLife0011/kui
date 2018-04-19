#include "stdafx.h"
#include "hy.h"
#include "comutil.h"
#include <Shlwapi.h>
#include <WinIoCtl.h>
#pragma comment(lib, "Shlwapi")

#define PROT_PASSWORD	"1A8F33CFA9FC"

#pragma pack(1)
typedef struct tag_MOUNT_PACK
{
	LONGLONG qwStartSec;
	LONGLONG qwSecs;
	DWORD    dwDiskNumber;
	char     szDosDevice[MAX_PATH];
}MOUNTPACK, *LPMOUNTPACK;

typedef struct tag_ProtectArea_Info
{
	BYTE	bState;
	BYTE	bCmd;
	BYTE	bCmdAtOnce;
	BYTE	bModifyOutside;
	DWORD	dwStartSec;
	DWORD	dwSecs;
	DWORD	dwDiskNumber;

	DWORD	dwBitmapNotUsedBits;
	DWORD	dwBitmapOldUsedBits;
	DWORD	dwBitmapNewUsedBits;
	DWORD	dwBitmapTmpUsedBits;
}PROTECTAREA_INFO, *LPPROTECTAREA_INFO;

#define MAX_PROTECTAREA_NUMS	100
typedef struct tag_PROTECTAREA_PACK
{
	DWORD	dwInOrOut;
	DWORD	dwNums;
	DWORD	dwReseave[2];
	char	szPassword[256];
	PROTECTAREA_INFO	Area[MAX_PROTECTAREA_NUMS];
}PROTECTAREA_PACK, *LPPROTECTAREA_PACK;

typedef struct tag_PtInfo
{
	DWORD	dwStartSec;			//�˷����ľ��Կ�ʼ����
	DWORD	dwSecs;				//�˷����Ĵ�С��������
	DWORD	dwUsedSecs;			//�˷����Ѿ���ʹ�õ�������
	BYTE	bFsType;			//�˷����ķ�������
	BYTE	bIsMaster;			//�˷��Ƿ�Ϊ��������1��ʾ��������0��ʾ��������
	BYTE	bIsActive;			//�˷����Ƿ�Ϊ�������1��ʾ�������0��ʾΪ�ǻ����
	BYTE	bDosChar;			//�˷������̷���Ϊ�̷���ASCIIֵ���磬C��ASCIIֵΪ67
	char	szVolume[256];		//�˷����ľ��
}PTINFO, *LPPTINFO;	

#define MAX_PTS	 100
typedef struct tag_HDInfo
{
	DWORD	dwHdNumber;			//��Ӳ����ϵͳ�е��豸˳���
	DWORD	dwSecs;				//��Ӳ�̵Ĵ�С��������
	DWORD	dwReseave;			//����
	DWORD	dwPtNums;			//��Ӳ�̵ķ�������
	PTINFO	pt[MAX_PTS];		//������Ϣ����
}HD, *LPHD;

#pragma pack()

//ע�����з����ַ������Ǵ�д�����ݷ��أ���ʾ�ɹ���������������ʾ����������롣

//��һ��������ʾ��װʱҪ�����ķ����б��ڶ��������õĻ�ԭ���롣������������룬����""���ַ�����
//���أ���ʾ�ɹ����ǣ��Ǵ�����롣


//��װ����������ָ���̷�:
typedef int (WINAPI *PFNINSTALL4DOSCHAR)(LPCSTR szProtectList, LPCSTR szPassword );

//�õ�����״̬�����أ���ʾ��������װ��������ʾû�а�װ������
typedef int (WINAPI *PFNGETDRIVESTATE)();

//ж������
typedef int (WINAPI *PFNUNINSTALLDRIVER)();

//�������Ƿ񱻱�������������̣��������"C"��ע�ⲻ��"C:"����"C:\"
//����ʾ����������ʾû�б���
typedef int (WINAPI *PFNDRIVERISPROTECTED)(LPCSTR pBuffer);

//�������룺���������Ϊ�գ���""�սڷ��������أ���ʾ������ȷ�����������벻��ȷ
typedef int (WINAPI *PFNCHECKPASSWORD)(LPCSTR szPassWord );

//�������룺�������������룬�����롣
typedef int (WINAPI *PFNCHANGEPASSWORD)(LPCSTR szOldPassWord, LPCSTR szNewPassword );

//������дһ����Ҫ��������ݣ� ��С0x100 BYTE��������ݱ����ǣ������ֽڵĻ���ռ䣬
//��Ӧ�ó������д˽�����ݵ��������棬Ҳ���Զ�������
typedef int (WINAPI *PFNRWAPDATA)(BYTE *lpBuf, BYTE isWrite );//1��ʾд������ʾ��

//���ñ�����������Ҫ���̷��б�:���أ���ʾ�ɹ���������ʾ������롣
#define PROT_DRIVER		1
#define UNPROT_DRIVER	3
#define FLAG_REBOOT		0
#define FLAG_IMME		1
typedef int (WINAPI *PFNSETPROTECTAREAFORDOSCHAR)(
	LPCSTR szDosCharList, 
	int iState /*1:��ʾ����������3��ʾȡ����������*/,
	int iCmd, //д0
	LPCSTR szPassword, //��������
	int iIsOnTime /*����ʾ������Ч������ʾ��������Ч����ϵͳ���Լ�ҳ���ļ����ڸ÷����Ļ�������Ҫ���������Ч����Щ����0)*/
	);


//�õ������ķ����б������Ǵ�����ݵĻ��������Լ��������Ĵ�С��һ��ʹ�ã������ֽڼ��ɡ���Ϊ�����ǣ����ڡ�
//���������Уã��ģ��ţ��ƣ��ǣ����ҵ�ǰ�����ˣģ��ơ��򷵻��ڻ�������д"DF".
typedef int (WINAPI *PFNGETPROTECTEDDRIVES)(LPSTR pBuffer, int cxBuffer);

//���������������ڴ�͸��ԭ����͸��ԭ��ԭ���ǣ������͸���̣���͸ǰ�ѣ�����һ�������豸��Ȼ����������д���ݣ��ʹ�͸�ˡ�������󣬰�������ɾ����
//�õ������̵���Ϣ��
typedef int (WINAPI *PFNGETMOUNTINFO)( MOUNTPACK *lpMountPack, LPCSTR szPassword );

//ɾ�������豸��
typedef int (WINAPI *PFNUMOUNTPTDOSCHAR)(LPCSTR szdevicePath,   LPCSTR szPassword);

//��������̡���һ�������Ƿ�����ĸ������"D".�ڶ��������������������Լ�ȡ�ģ�
//�������ǵ�������Ҫʹ�÷�����ĸ�����������ȡ���������֡���PKG,����ȡ
//D:�������������ʾ����Դ�������У����������������롣
typedef int (WINAPI *PFNMOUNTPTDOSCHAR)(LPCSTR szDosChar, LPCSTR szdevicePath, LPCSTR szPassword);

//���ӣ���͸���̡�
//��͸ǰ���ȵ���MoutPtDosChar��"D", "PKG","password");����һ���豸������

//�������豸д�ļ��ͻ�ֱ�Ӵ�͸��\\\\.\\������豸����\�ļ�·����
//CopyFile(��F:\\boot.ini��, ��\\\\.\\PKG\\boot.ini, 0 ).���ѣ��̵�����ļ�д�������																				 
//�������ɾ�������豸��
//UMoutPtDosChar("PKG", "password");

typedef int (WINAPI * PFNGETPROTECTAREA)(PROTECTAREA_PACK *lpProtect);

typedef int (WINAPI * PFNGETHDINFO)( LPHD lphd );

typedef int (WINAPI * PFNUPDATEDIR)( wchar_t *lpPath );

typedef int (WINAPI * PFNSETPROTECTAREA)(PROTECTAREA_PACK *lpProtect, int isOnTime);

static HMODULE _hModule = NULL;
static PFNINSTALL4DOSCHAR 			pfnInstall4DosChar		= NULL;
static PFNGETDRIVESTATE				pfnGetDriveState		= NULL;
static PFNUNINSTALLDRIVER			pfnUnInstallDriver		= NULL;
static PFNDRIVERISPROTECTED			pfnDriverIsProtected	= NULL;
static PFNCHECKPASSWORD				pfnCheckPassword		= NULL;
static PFNCHANGEPASSWORD			pfnChangePassword		= NULL;
static PFNRWAPDATA					pfnRWAPData				= NULL;
static PFNSETPROTECTAREAFORDOSCHAR	pfnProtArea				= NULL;
static PFNGETPROTECTEDDRIVES		pfnGetProtectDrivers	= NULL;
static PFNMOUNTPTDOSCHAR			pfnMountDosChar			= NULL;
static PFNUMOUNTPTDOSCHAR			pfnUMountDosChar		= NULL;
static PFNGETMOUNTINFO				pfnGetMountInfo			= NULL;
static PFNGETPROTECTAREA			pfnGetProtectArea		= NULL;
static PFNGETHDINFO					pfnGetHDInfo			= NULL;
static PFNUPDATEDIR					pfnUpdateDir			= NULL;
static PFNSETPROTECTAREA			pfnSetProtectArea		= NULL;

static bool hy_Initlialize()
{
	if (_hModule != NULL)
		return true;

	TCHAR szModule[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModule, _countof(szModule));
	PathRemoveFileSpec(szModule);
	PathAddBackslash(szModule);
	lstrcat(szModule, TEXT("KPDiskDll.dll"));
	_hModule = LoadLibrary(szModule);
	if (_hModule != NULL)
	{
		pfnInstall4DosChar		= (PFNINSTALL4DOSCHAR)GetProcAddress(_hModule, "Install4DosChar");
		pfnGetDriveState		= (PFNGETDRIVESTATE)GetProcAddress(_hModule, "GetDriveState");
		pfnUnInstallDriver		= (PFNUNINSTALLDRIVER)GetProcAddress(_hModule, "UnInstallDriver");
		pfnDriverIsProtected	= (PFNDRIVERISPROTECTED)GetProcAddress(_hModule, "DriverIsProtected");	   
		pfnCheckPassword		= (PFNCHECKPASSWORD)GetProcAddress(_hModule, "CheckPassWord");
		pfnChangePassword		= (PFNCHANGEPASSWORD)GetProcAddress(_hModule, "ChangePassWord");
		pfnRWAPData				= (PFNRWAPDATA)GetProcAddress(_hModule, "RWAPData");
		pfnProtArea				= (PFNSETPROTECTAREAFORDOSCHAR)GetProcAddress(_hModule, "SetProtectAreaForDosChar");
		pfnGetProtectDrivers	= (PFNGETPROTECTEDDRIVES)GetProcAddress(_hModule, "GetProtectedDrives");
		pfnMountDosChar			= (PFNMOUNTPTDOSCHAR)GetProcAddress(_hModule, "MountPtDosChar");
		pfnUMountDosChar		= (PFNUMOUNTPTDOSCHAR)GetProcAddress(_hModule, "UMountPtDosChar");
		pfnGetMountInfo			= (PFNGETMOUNTINFO)GetProcAddress(_hModule, "GetMountInfo");
		pfnGetProtectArea		= (PFNGETPROTECTAREA)GetProcAddress(_hModule, "GetProtectArea");
		pfnGetHDInfo			= (PFNGETHDINFO)GetProcAddress(_hModule, "GetHDInfo");
		pfnUpdateDir			= (PFNUPDATEDIR)GetProcAddress(_hModule,"UpDateDir");
		pfnSetProtectArea		= (PFNSETPROTECTAREA)GetProcAddress(_hModule, "SetProtectArea");
		if (pfnInstall4DosChar		!= NULL &&
			pfnGetDriveState		!= NULL &&
			pfnUnInstallDriver		!= NULL &&
			pfnDriverIsProtected	!= NULL &&
			pfnCheckPassword		!= NULL && 
			pfnChangePassword		!= NULL &&
			pfnRWAPData				!= NULL &&
			pfnProtArea				!= NULL &&
			pfnGetProtectDrivers	!= NULL &&
			pfnMountDosChar			!= NULL &&
			pfnUMountDosChar		!= NULL &&
			pfnGetMountInfo			!= NULL && 
			pfnGetProtectArea		!= NULL &&
			pfnGetHDInfo			!= NULL &&
			pfnSetProtectArea		!= NULL)
		{
			return true;
		}
	}
	return false;
}

extern HANDLE ghLogger;

bool hy_DriverProtected(TCHAR drv)
{
	if (!hy_Initlialize())
		return false;
	char driver[5] = {0};
	sprintf_s(driver, _countof(driver), "%c", (char)_totupper(drv));

	if (pfnGetDriveState() == 0 && pfnDriverIsProtected(driver) == 0)
		return true;

	return false;
}

bool hy_LoadVirtualDevice(TCHAR drv)
{
	if (hy_DriverProtected(drv) && pfnMountDosChar != NULL)
	{
		char driver[20] = {0};
		char device[20] = {0};
		sprintf_s(driver, _countof(driver), "%c", (char)_totupper(drv));
		sprintf_s(device, _countof(device), "PKG%c", (char)_totupper(drv));
		pfnMountDosChar(driver, device, PROT_PASSWORD);
		return true;
	}
	return true;
}

tstring hy_ConvertPath(const tstring& path)
{
	tstring file(path);
	if (file.size() > 3 && file[1] == TEXT(':') && file[2] == TEXT('\\') && hy_DriverProtected(file[0]))
	{
		tstring pre = TEXT("\\\\.\\PKG");
		pre += _totupper(file[0]);
		file.replace(0, 2, pre);
	}
	return file;
}

bool hy_CreateDirectory(const tstring& dir)
{
	tstring::size_type pos = 3;	//X:\.(���ܴ�����Ŀ¼.����C:\)
	tstring::size_type len = _tcslen(TEXT("\\\\.\\PKG"));
	if (dir.size() >= len && _tcsnicmp(dir.c_str(), TEXT("\\\\.\\PKG"), len) == 0)
		pos = len + 2;

	pos = dir.find(TEXT('\\'), pos);
	while (pos != dir.npos)
	{
		tstring sub = dir.substr(0, pos+1);
		if (!CreateDirectory(sub.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
		pos = dir.find(TEXT('\\'), pos+1);
	}
	return true;
}

bool hy_GetDiskRoomSize(TCHAR drv, PLARGE_INTEGER pliSize)
{
	if (pliSize == NULL)
		return false;

	char driver = (char)_totupper(drv);
	pliSize->QuadPart = 0;
	if (hy_DriverProtected(drv))
	{
		for (DWORD idx=0; idx<5; idx++)
		{
			tag_HDInfo hdInfo = {0};
			hdInfo.dwHdNumber = idx;
			if (0 != pfnGetHDInfo(&hdInfo))
				continue;
			
			for (DWORD loop=0; loop<hdInfo.dwPtNums; loop++)
			{
				if (hdInfo.pt[loop].bDosChar == driver)
				{
					DWORD dwStartSec = hdInfo.pt[loop].dwStartSec;
					tag_PROTECTAREA_PACK Areainfo = {0};
					if (0 != pfnGetProtectArea(&Areainfo))
						continue;
					for (DWORD idx=0; idx<Areainfo.dwNums; idx++)
					{
						if (Areainfo.Area[idx].dwStartSec == dwStartSec)
						{
							pliSize->QuadPart = (__int64)Areainfo.Area[idx].dwBitmapNotUsedBits * 512;
							return true;
						}
					}
				}
			}
		}
	}

	TCHAR sdriver[] = TEXT("X:\\");
	sdriver[0] = drv;
	return (TRUE == GetDiskFreeSpaceEx(sdriver, (PULARGE_INTEGER)pliSize, NULL, NULL));
}

bool hy_ExueteUpdateDir(LPCTSTR dir)
{
	if (dir != NULL && _tcslen(dir) > 3 && dir[1] == TEXT(':') && 
		hy_DriverProtected(dir[0]) && pfnUpdateDir != NULL && pfnUMountDosChar!= NULL)
	{
		wchar_t path[MAX_PATH] = {0};
#ifdef _UNICODE
		lstrcpy(path, dir);
#else
		MultiByteToWideChar(CP_ACP, 0, dir, -1, path, sizeof(path), NULL, NULL);		
#endif
		char device[10] = {0};
		sprintf_s(device, _countof(device), "PKG%c", toupper(path[0]));
		pfnUMountDosChar(device, PROT_PASSWORD);

		bool ret = true;
		for (size_t idx=0; idx<3; idx++)
			ret = (0 == pfnUpdateDir(path));
		return ret;
	}
	return false;
}

void hy_DyncaRefreDriver(TCHAR drv)
{
	if (hy_DriverProtected(drv) && pfnUMountDosChar != NULL && pfnProtArea != NULL && pfnMountDosChar != NULL)
	{
		char driver[20] = {0};
		char device[20] = {0};
		sprintf_s(driver, _countof(driver), "%c", (char)_totupper(drv));
		sprintf_s(device, _countof(device), "PKG%c", (char)_totupper(drv));
		
		pfnUMountDosChar(device, PROT_PASSWORD);
		pfnProtArea(driver, 1, 1, PROT_PASSWORD, FLAG_IMME);
		pfnMountDosChar(driver, device, PROT_PASSWORD);
	}
}

bool AfxControlMachine(bool bReBoot)
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return false; 

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 

	tkp.PrivilegeCount = 1; 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 	

	ExitWindowsEx(bReBoot ? EWX_REBOOT|EWX_FORCE : EWX_SHUTDOWN|EWX_FORCE, 0);

	return true;
}

bool hy_IsInstall()
{
	if(hy_Initlialize())
		return (pfnGetDriveState() == 0);
	return false;
}

CString hy_FilterPortDrivers(LPCTSTR lpPortList) // ������Ҫ��͸���̷��б�ȥ���Ǳ����̣���Ϸ�̣�
{
	TCHAR szPort[MAX_PATH] = {0};
	int nPos = 0;
	size_t count = _tcslen(lpPortList);
	for (size_t idx=0; idx<count; idx++)
	{
		TCHAR drv = lpPortList[idx];
		CString szItem = TEXT("X:\\");
		szItem.SetAt(0, drv);
		TCHAR szDev[MAX_PATH] = {0};
		if (GetVolumeNameForVolumeMountPoint(szItem,szDev,MAX_PATH))
		{
			if (StrStrI(szDev, _T("4a45-8707-d750b0c8d2a6")) != NULL)
			{
				continue;
			}
			szPort[nPos]=drv;
			nPos++;
		}
	}
	return szPort;
}

bool hy_Install(LPCTSTR lpProtectList)
{
	if (!hy_Initlialize()) return false;
	bool bret = true;
	if(hy_IsInstall())
	{
		bret = hy_PortArea(lpProtectList);
	}
	else
	{
		CString szDrv;
		if (lpProtectList)
		{
			szDrv = hy_FilterPortDrivers(lpProtectList);
		}
		//_bstr_t drvlist(lpProtectList ? lpProtectList : TEXT(""));
		int iRet = pfnInstall4DosChar(_bstr_t((LPCTSTR)szDrv), PROT_PASSWORD);
		bret = (iRet == 0);
		if (bret)
		{
			hy_InstallAndStartAntiDog(true, false);
		}
	}
	AfxControlMachine(true);
	return bret;
}

bool hy_Uninstall()
{
	if(hy_IsInstall() && (pfnUnInstallDriver() == 0))
	{
		PROTECTAREA_PACK	ProtectPack = {0};

		int ret = pfnGetProtectArea(&ProtectPack);
		if ( ret == 0 )
		{
			ProtectPack.dwInOrOut = 1;
			for (DWORD i = 0; i < ProtectPack.dwNums; i++)
			{
				if (ProtectPack.Area[i].bState != PAINFO_STATE_NOT_PROTECT)
				{
					ProtectPack.Area[i].bCmd = PAINFO_CMD_SAVE;
				}
			}
			strcpy_s(ProtectPack.szPassword, PROT_PASSWORD);
			ret = pfnSetProtectArea(&ProtectPack, 0);
		}

		AfxControlMachine(true);
		return true;
	}

	return true;
}

bool hy_SetPortArea(LPCTSTR lpPortList, int iState = PROT_DRIVER, bool bReboot = true)
{
	if(lpPortList == NULL || lstrlen(lpPortList) < 1) return false;
	if(!hy_IsInstall()) return false;

	if(pfnCheckPassword("") == 0)
		pfnChangePassword("", PROT_PASSWORD);
	
	//long lLen = WideCharToMultiByte(CP_ACP, 0, lpPortList, -1, NULL, 0, NULL, NULL);
	//char* pPortList = new char[lLen];
	//WideCharToMultiByte(CP_ACP, 0, lpPortList, -1, pPortList, lLen, NULL, NULL);

	char szPortList[1024] = {0};
	int nPos = 0;
	size_t count = _tcslen(lpPortList);
	for (size_t i = 0; i < count; ++i)
	{
		TCHAR drv = lpPortList[i];
		szPortList[nPos] = (char)drv;
		nPos++;
	}
	szPortList[nPos] = 0;

	if(pfnProtArea(szPortList, iState, 0, PROT_PASSWORD, FLAG_IMME) != 0)
	{
		if(pfnProtArea(szPortList, iState, 0, PROT_PASSWORD, FLAG_REBOOT) == 0)
			AfxControlMachine(bReboot);
	}

	return true;
}

bool hy_PortArea(LPCTSTR lpPortList, bool bReboot)
{
	CString szPort = hy_FilterPortDrivers(lpPortList);

	AfxWriteLogger(ghLogger, _T("disable hy volume:%s"), szPort);
	{
		TCHAR buffer[1024];
		wsprintf(buffer, _T("disable hy volume:%s\r\n"), szPort);
		OutputDebugString(buffer);
	}
	
	return hy_SetPortArea(szPort, PROT_DRIVER);
}

bool hy_UnPortArea(LPCTSTR lpPortList, bool bReboot)
{
	return hy_SetPortArea(lpPortList, UNPROT_DRIVER);
}

bool hy_PortFile(LPCTSTR lpFile)
{
	if (hy_DriverProtected(lpFile[0]) && hy_LoadVirtualDevice(lpFile[0]))
	{
		tstring strFile = hy_ConvertPath(lpFile);
		hy_CreateDirectory(strFile);
		CopyFile(lpFile, strFile.c_str(), FALSE);

		char device[10] = {0};
		sprintf_s(device, _countof(device), "PKG%c", toupper(lpFile[0]));
		pfnUMountDosChar(device, PROT_PASSWORD);
		return true;
	}

	return false;
}

#define ANTIDOG_SERVICENAME		TEXT("KAntiDog")
#define ANTIDOG_DRIVERNAME		TEXT("KAntiDog.sys")

bool hy_InstallAndStartAntiDog(bool binstall, bool bStart)
{
	bool ret = false;
	if (binstall && hy_IsInstall())
	{
		SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager != NULL)
		{
			SC_HANDLE schService = OpenService(schSCManager, ANTIDOG_SERVICENAME, SERVICE_ALL_ACCESS);
			if (schService == NULL && GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST)
			{
				TCHAR path[MAX_PATH] = {0};
				GetSystemDirectory(path, _countof(path));
				PathAddBackslash(path);
				lstrcat(path, TEXT("drivers\\") ANTIDOG_DRIVERNAME);
				if (!PathFileExists(path))
				{
					TCHAR szDriver[MAX_PATH] = {0};
					AfxGetAppPath(szDriver, MAX_PATH, ANTIDOG_DRIVERNAME);
					CopyFile(szDriver, path, FALSE);
				}
				schService = CreateService(schSCManager, ANTIDOG_SERVICENAME, ANTIDOG_SERVICENAME, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
					SERVICE_SYSTEM_START, SERVICE_ERROR_IGNORE, path, NULL, NULL, NULL, NULL, NULL);
			}
			if (schService != NULL)
			{
				CloseServiceHandle(schService);
				ret = true;
			}
			CloseServiceHandle(schSCManager);
		}
	}
	
	if (bStart && hy_IsInstall())
	{
		AfxStartService(ANTIDOG_SERVICENAME);
		HANDLE hFile = CreateFile(TEXT("\\\\.\\") ANTIDOG_SERVICENAME, GENERIC_READ|GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwByteReturned = 0;
			DeviceIoControl(hFile, CTL_CODE(9000, 101, METHOD_BUFFERED, FILE_ANY_ACCESS), NULL, 0, NULL, 0, &dwByteReturned, NULL);
			CloseHandle(hFile);
			ret = true;
		}
	}
	return ret;
}