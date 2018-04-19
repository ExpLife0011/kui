#pragma once

//////////////////////////////////////////////////////////////////////////
//scsi disk driver function.

DWORD __stdcall ScsiDiskInstallDriver();

//����һ�������̷���.ip, port:������,DriverLetter,ָ���Ŀͻ����̷�,TempDirNameָ����ʱ�ļ���Ŀ¼
DWORD __stdcall ScsiDiskMount(DWORD Ip, WORD Port, TCHAR DriverLetter, TCHAR TmpFileDriverLetter, BOOL bMirrorDisk = FALSE, int nDiskNum = 100, BOOL bIsAdmin = FALSE);

//ж�ؼ��ص������̷�����DriverLetter:�����̷�.
DWORD __stdcall ScsiDiskUnmount(TCHAR DriverLetter, BOOL bMirrorDisk = FALSE, int nDiskNum = 100, BOOL IsAdmin = FALSE);

DWORD __stdcall ScsiDiskQueryDisklessInfo(PDWORD DiskLess, PDWORD IsAdmin, PDWORD ServerIp);
DWORD __stdcall ScsiDiskQueryDisklessInfoEx(PDISKLESS_INFO pDiskLessInfo);

//����diskpart.exe���³�ʼ������
DWORD __stdcall ScsiDiskReinitImage(int nDiskNum, TCHAR cVol, DWORD nSizeInMb);

//����format.exe���¸�ʽ������
DWORD __stdcall ScsiDiskReformatImage(TCHAR szVol);


//////////////////////////////////////////////////////////////////////////
//file disk driver function.
DWORD __stdcall FileDiskInstallDriver();

DWORD __stdcall FileDiskMount(DWORD DiskType, DWORD Ip, WORD Port, TCHAR DriverLetter, LPCTSTR UserId);

DWORD __stdcall FileDiskUnmount(TCHAR DriverLetter);