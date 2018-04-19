#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

#include "ntfspublic.h"

struct _ntfs_volume;
struct ntfs_device_operations;
struct ntfs_device;

START_NAMESPACE_NTFS

enum 
{
	NTFS_IMP_NONE                   = 0x00000000,
	NTFS_IMP_RDONLY                 = 0x00000001,
};

// ��λ:(��λ:�ֽ�)
typedef struct tagFileClusters
{
	unsigned __int64 ul64Vcn;			// �ļ���Ե�ַ
	unsigned __int64 ui64Lcn;			// ʵ�ʵ�ַ
	unsigned __int64 ui64Length;		// �ܴ�С
} FILECLUSTERS, *PFILECLUSTERS;

class NtfsImp
{
public:

	NtfsImp();

	virtual ~NtfsImp();

public:

	/// ��ʼ��
	virtual DWORD Init(void *pParam = NULL, unsigned long flags = NTFS_IMP_NONE, const char *name  = NULL);

	/// �ͷ�
	virtual void Release();

public:

	/// ��ʼ��
	virtual signed long on_device_init(void *pParam) = 0;

	/// �ͷ�
	virtual signed long on_device_release(void *pParam) = 0;

	/// ���õ���������С
	virtual signed long on_device_setsectorsize(void *pParam, unsigned short bytespersector) = 0;

	/// ������
	virtual signed long on_device_readdata(void *pParam, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize) = 0;

	/// д����
	virtual signed long on_device_writedata(void *pParam, unsigned __int64 ullOffSet, const void *pBuffer, unsigned long dwSize) = 0;

	/// ������
	virtual signed long on_device_readsector(void *pParam, unsigned __int64 ullStartSector,  unsigned long dwNumber, void *pBuffer) = 0;

	/// д����
	virtual signed long on_device_writesector(void *pParam, unsigned __int64  ullStartSector, unsigned long dwNumber, const void *pBuffer) = 0;

	/// ˢ�´���
	virtual signed long on_device_sync(void *pParam) = 0;

	/// ��Ե�ַ����Ե�ַת��
	virtual signed long on_device_daddresstofaddress(void *pParam, unsigned __int64  ullOffSet,
		unsigned __int64*  pullOffSet) = 0;

public:

	/// �����ļ���(pszDirPath= .\test\path)
	DWORD CreateDirectory(LPCTSTR pszDirPath);

	/// �����ļ�(pszFilePath= .\test\path\file)
	DWORD CreateFile(LPCTSTR pszFilePath, HANDLE *phFile = NULL);

	/// д���ļ�����
	DWORD WriteFile(HANDLE hFile, LPCVOID lpBuffer, ULONGLONG ullOffset, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWrite);

	/// ɾ���ļ�(pszFilePath= .\test\path\file)
	DWORD DeleteFile(LPCTSTR pszFilePath);

	/// ��ȡ�ļ���С
	DWORD SetFileSize(HANDLE hFile, ULONGLONG ullSize);

	/// ���������ļ���NTFS(lpNtfsFileName= .\test\path\file)
	DWORD CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNtfsFileName, HANDLE hEvent = NULL);

	/// ���������ļ���NTFS(lpNtfsFileName= .\test\path\file)
	typedef DWORD(*COPYFILECALLBACK)(LPVOID pParam, LPCTSTR lpSrc, LPCTSTR lpDest,
		DWORD dwWriteBytes, LPCTSTR szError);
	DWORD CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNtfsFileName,
		COPYFILECALLBACK pCopyFileCallBack = NULL, LPVOID pParam = NULL);

	/// ����NTFS�ļ��������ļ�(lpNtfsFileName= .\test\path\file)
	DWORD CopyFileEx(LPCTSTR lpNtfsFileName, LPCTSTR lpFileName, HANDLE hEvent = NULL);

	/// ��������Ŀ¼��NTFS(lpNtfsDirName= .\test\path\path)
	DWORD CopyDirectory(LPCTSTR lpExistingDirName, LPCTSTR lpNtfsDirName, HANDLE hEvent = NULL);

	/// ��������Ŀ¼��NTFS(lpNtfsDirName= .\test\path\path)
	DWORD CopyDirectory(LPCTSTR lpExistingDirName, LPCTSTR lpNtfsDirName,
		COPYFILECALLBACK pCopyFileCallBack = NULL, LPVOID pParam = NULL);

	/// �����ļ�ʱ����Ϣ
	DWORD SetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

	/// ���DIRTY��ʶ
	DWORD ClearDirtyFlag();

	/// ������־�ļ�
	DWORD ResetLogFile(__int64 i64Size, bool bReset = false);

public:

	/// ���ļ�(pszFilePath= .\test\path\file, �ļ��������)
	DWORD OpenFile(LPCTSTR pszFilePath, HANDLE &hFile);

	/// �ر��ļ����
	void CloseFile(HANDLE hFile);

	/// ��ȡ�ļ�����
	DWORD ReadFile(HANDLE hFile, LPVOID lpBuffer, ULONGLONG ullOffset, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);

	/// ��ȡ�ļ���С
	DWORD GetFileSize(HANDLE hFile, ULONGLONG &ullSize);

	/// ��ȡ�ļ�����
	DWORD GetFileName(HANDLE hFile, LPTSTR szFileName, DWORD dwLen);

	/// �Ƿ��ļ���
	BOOL IsDirectory(HANDLE hFile);
	
	/// ��ȡ�ļ�ʱ����Ϣ
	DWORD GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

	/// ���ļ�����Ϣ
	DWORD GetFileCluster(HANDLE hFile, std::vector<FILECLUSTERS> &vtFileClusters);

public:

	/// ��ȡ�ظ���
	ULONGLONG GetTotalClusters();

public:

	/// ��ʼ��
	static signed long device_init(struct ntfs_device *dev);

	/// �ͷ�
	static signed long device_release(struct ntfs_device *dev);

	/// ���õ���������С
	static signed long device_setsectorsize(struct ntfs_device *dev, unsigned short bytespersector);

	/// ������
	static signed long device_readdata(struct ntfs_device *dev, unsigned __int64 ullOffSet, void *pBuffer, unsigned long dwSize);

	/// д����
	static signed long device_writedata(struct ntfs_device *dev, unsigned __int64 ullOffSet, const void *pBuffer, unsigned long dwSize);

	/// ������
	static signed long device_readsector(struct ntfs_device *dev, unsigned __int64 ullStartSector,  unsigned long dwNumber, void *pBuffer);

	/// д����
	static signed long device_writesector(struct ntfs_device *dev, unsigned __int64  ullStartSector, unsigned long dwNumber, const void *pBuffer);

	/// ˢ�´���
	static signed long device_sync(struct ntfs_device *dev);

private:

	/// �����豸�����ص�
	unsigned long ntfs_set_device_callback(void *init, void *release, void *setsectorsize, void *readdata, 
		void *writedata, void *readsector, void *writesector, void *sync);

private:

	struct ntfs_device_operations *m_pdevice;

	struct _ntfs_volume *m_pVolume;

	void *m_pParam;

};

END_NAMESPACE_NTFS