#ifndef __khwmonitor_h__
#define __khwmonitor_h__

#include <tchar.h>
#include <string>
#include <sstream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma once


#ifndef KHWMONITOR_EXPORTS
#define HWMONITOR_API  _declspec(dllimport)
#else
#define HWMONITOR_API _declspec(dllexport)
#endif

#ifdef _UNICODE
#define tstring std::wstring
#define tstringstream  std::wstringstream
#else
#define tstring std::string
#define tstringstream  std::stringstream
#endif

//stru
//�Ƹ��¿���̨
#define MAX_NAME_LEN				64
struct tTemperature
{
	TCHAR	Machine[MAX_NAME_LEN];
	DWORD	CpuVal;
	DWORD	CpuMaxVal;
	DWORD	BoardVal;
	DWORD	BoardMaxVal;
	DWORD	DisplayVal;
	DWORD	DisplayMaxVal;
	DWORD	DiskVal;
	DWORD	DiskMaxVal;
	DWORD	CpuFanSpeed;
	DWORD	LastTime;
};
//CPU
typedef struct tagCPU
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
	TCHAR szSerialNumber[512];//���к�
	float fTemperature;//�¶�
	int   iFanSpeed[2];//����ת�٣�����һ����1�����һ�㲻����2��
}CPU, *LPCPU;
//�Կ�
typedef struct tagDisplayAdapter
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
	float fTemperature;//�¶�
}DISPLAYADAPTER, *LPDISPLAYADAPTER;
//����
typedef struct tagMainBoard
{
	DWORD dwID;
	TCHAR szVendor[512];//���쳧��
	TCHAR szModel[512];//�ͺ�
	float fTemperature;//�¶�
	TCHAR szSerialNumber[512];//���к�
}MAINBOARD, *LPMAINBOARD;
//�ڴ���
typedef struct tagMem
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
	int fSize;//��С����λM��
}MEM, *LPMEM;
//����
typedef struct tagAudioCard
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
}AUDIOCARD, *LPAUDIOCARD;
//Ӳ��
typedef struct tagHardDisk
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
	UINT64 ullDiskSize;//Ӳ�̴�С
	float fTemperature;//�¶�
	bool  bSSDDisk;//�Ƿ���SSD
}HARDDISK, *LPHARDDISK;
//����
typedef struct tagKeysBoard
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
}KEYBOARD, *LPKEYBOARD;
//���
typedef struct tagMouse
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
}MOUSE, *LPMOUSE;
//����ͷ
typedef struct tagCamera
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
}CAMERA, *LPCAMERA;
//��˷�
typedef struct tagMicroPhone
{
	DWORD dwID;
	TCHAR szModel[512];//�ͺ�
}MICROPHONE, *LPMICROPHONE;

extern "C" {
	HWMONITOR_API bool __stdcall HWMONITOR_Init();
	HWMONITOR_API void __stdcall HWMONITOR_UnInit();

	HWMONITOR_API bool __stdcall HWMONITOR_GetCPUInfo(__out LPCPU lpCPUInfo);
	HWMONITOR_API int  __stdcall HWMONITOR_GetDisplayAdapterCount();
	HWMONITOR_API bool __stdcall HWMONITOR_GetDisplayAdapterInfo(__out LPDISPLAYADAPTER lpDisplayAdapterInfo,__in int iNextIndex);
	HWMONITOR_API bool __stdcall HWMONITOR_GetMainBoardInfo(__out LPMAINBOARD lpMainBoardInfo);
	HWMONITOR_API int  __stdcall HWMONITOR_GetMemCount();
	HWMONITOR_API bool __stdcall HWMONITOR_GetMemInfo(__out LPMEM lpMemInfo,__in int iNextIndex);
	HWMONITOR_API bool __stdcall HWMONITOR_GetAudioCardInfo(__out LPAUDIOCARD lpAudioCardInfo);
	HWMONITOR_API int  __stdcall HWMONITOR_GetHardDiskCount();
	HWMONITOR_API bool __stdcall HWMONITOR_GetHardDiskInfo(__out LPHARDDISK lpHardDiskInfo,__in int iNextIndex);
	HWMONITOR_API bool __stdcall HWMONITOR_GetKeysBoardInfo(__out LPKEYBOARD lpKeyBoardInfo);
	HWMONITOR_API bool __stdcall HWMONITOR_GetMouseInfo(__out LPMOUSE lpMouseInfo);
	HWMONITOR_API bool __stdcall HWMONITOR_GetCameraInfo(__out LPCAMERA lpCameraInfo);
	HWMONITOR_API bool __stdcall HWMONITOR_GetMicroPhoneInfo(__out LPMICROPHONE lpMicroPhoneInfo);

	//��ȡ�����Կ���Ϣ
	HWMONITOR_API bool __stdcall HWMONITOR_GetDisplayAdapterInfoALL(
		__out LPDISPLAYADAPTER *&lpDisplayAdapterInfo,//�����Կ���Ϣ��ʹ����֮�����ɾ��<delete>
		__out int& iDisplayAdapterCount//�Կ�����
		);
	//��ȡ�����ڴ�����Ϣ
	HWMONITOR_API bool __stdcall HWMONITOR_GetMemInfoAll(
		__out LPMEM *&lpMemInfo,//�����ڴ�����Ϣ��ʹ����֮�����ɾ��<delete>
		__out int& iMemCount//�ڴ�������
		);
	//��ȡ����Ӳ����Ϣ
	HWMONITOR_API bool __stdcall HWMONITOR_GetHardDiskInfoALL(
		__out LPHARDDISK *&lpHardDiskInfoArray,//����Ӳ����Ϣ��ʹ����֮�����ɾ��<delete>
		__out int& iHardDiskCount//Ӳ�̸���
		);

	//�Ƹ��¿���̨�淶�ӿ�
	HWMONITOR_API bool __stdcall GetTemperature(__inout tTemperature* pBuffer);//��������Ӳ���¶���Ϣ
	HWMONITOR_API bool __stdcall GetMainBoardNameInfo(__inout TCHAR* pBuffer,__in int nLenth);//��ȡ������Ϣ
	HWMONITOR_API bool __stdcall GetRamInfo(__inout TCHAR* pBuffer,__in int nLenth);//��ȡ�ڴ���Ϣ
}

#endif