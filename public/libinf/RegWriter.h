#ifndef _REG_WRITER_H_
#define _REG_WRITER_H_

#include "comment.h"

class CRegWriter
{
	struct RegInfo
	{
		std::wstring strValueType;
		std::wstring strValue;

		RegInfo()
		{};
		RegInfo(std::wstring &strVt, std::wstring &strV) : strValueType(strVt), strValue(strV)
		{};
	};

	typedef std::map<std::wstring, RegInfo> mapRegValueInfo_t;
	typedef std::map<std::wstring, mapRegValueInfo_t> mapRegInfo_t;

public:
	CRegWriter();
	~CRegWriter();

public:
	BOOL OpenRegFile(const wchar_t *pFileName);
	BOOL CloseRegFile();
	int WriteReg();
	int WriteCopyFile(const wchar_t *pFileName, const wchar_t *pRootPath, const wchar_t *pCatFileName);

	//�豸��ven��dev��rev��Ϣ
	void SetDeviceInfo(const wchar_t *pDeviceInfo){
		m_strDeviceInfo = pDeviceInfo;
	};
	//inf�ļ�����
	void SetInfName(const wchar_t *pFileName)
	{
		m_strInfName = pFileName;
		size_t pos = m_strInfName.find_last_of(TEXT('\\'));
		if (pos != std::wstring::npos)
		{
			m_strInfName = m_strInfName.substr(pos + 1);
		}
	};

	//�����ļ���·��
	void SetFileRootPath(std::wstring &strPath);

	void SetServiceInfo(mapRetDataInfo_t& mapServiceInfo);
	void SetAddReg(mapRetDataInfo_t& mapServiceInfo);
	void SetAddReg(vecSectionFileds_t& vecDelRegInfo, DWORD dwType = HKR_TYEP_NORM);
	void SetDelReg(mapRetDataInfo_t& mapServiceInfo);
	void SetDelReg(vecSectionFileds_t& vecDelRegInfo);
	void SetCopyFile(mapRetDataInfo_t& mapCopyFiles);
	void SetCopyFilePath(mapSectionKeyValue_t &mapPaths);
	void SetSvrName(std::wstring &strSvrName, std::wstring &strMfgName, 
		std::wstring &strProductName, std::wstring &strSectionName,
		std::wstring &strDevSection);
	void SetDriverInfo(std::wstring &strDate, std::wstring &strVer);

private:
	////���º�������д��inf�� services�������Ϣ
	//BOOL WriteServiceInfo();
	//BOOL WriteServiceAddReg();
	//BOOL WriteServiceDelReg();

	////���º�������д��inf�� ��services�������Ϣ
	//BOOL WriteNormAddReg();
	//BOOL WriteNormDelReg();
	//BOOL WriteNormCopyFileReg();
	
	void GetRegDataFromString(std::wstring &strSrc,
		std::wstring &strRoot, std::wstring &strPath,
		std::wstring &strKey, std::wstring &strValType, std::wstring &strVal);

	void GetCopyInfoFromString(std::wstring &strSrc,
		std::wstring &strDstFile, std::wstring &strSrcFile, DWORD &dwFlag);

	//�����ļ���·��
	void SetFilePath(std::wstring &strDrivicePath, std::wstring &strInfPath){
		m_strDriviceFileRootPath = strDrivicePath;
		m_strInfFilePath = strInfPath;
	};

	//�����ļ�·����Ϣ������Դ�ļ��ĸ�·��
	void ConstuctDriviceRootPath(const wchar_t *pVirtualRootPath, std::wstring &strFile, std::wstring &strRootPath);

	//������д��reg�ļ�
	BOOL WriteServiceInfo();
	BOOL WriteAddReg();
	BOOL WriteDelReg();
	BOOL WritePCI();
	BOOL WriteOther();

	//��������д��
	void WriteDwordValue(const wchar_t *pKey, const wchar_t *pVal);
	void WriteStringValue(const wchar_t *pKey, const wchar_t *pVal);
	void WriteBinaryValue(const wchar_t *pKey, const wchar_t *pVal);
	void WriteESzValue(const wchar_t *pKey, const wchar_t *pVal);
	void WriteMSzValue(const wchar_t *pKey, const wchar_t *pVal);
	void WriteData(const wchar_t *pData, size_t iLen);

	//�����б�ܵ�����
	void CheckString(const wchar_t *pVal, std::wstring &strRest);

	//����������ݲ����ɾ��
	void ConstructRegPath(const DWORD dwHkrType, const std::wstring &strRoot, 
		const std::wstring &strPath, std::wstring &strRestPath);
	void SetRegData(std::wstring &strRegPath, std::wstring strKey, RegInfo &regInfo, mapRegInfo_t &regDatas);
	void DoRegDataAddDel(mapRetDataInfo_t& mapRegDataFrom, mapRegInfo_t &mapRegTo);
	void DoRegDataAddDel(vecSectionFileds_t& vecRegDataFrom, mapRegInfo_t &mapRegTo, DWORD dwType = HKR_TYEP_NORM);

	//���ַ���ת��16�����ַ���
	void Chars2String16(const wchar_t *pSrc, wchar_t *pBuf);
	void CRegWriter::Chars2hex16(const wchar_t *pSrc, wchar_t *pBuf);

	//��inf�е�����ת��ʵ��·��
	std::wstring GetDstPath(const wchar_t *pPath);

	//��addreg��ɾ��delreg�е�����
	void DoDelReg();

	//������ʱ��ĳ�filetime
	void DriverTime2FileTime(std::wstring strDriverTime, FILETIME &ft);

private:
	static const std::wstring HKR;
	static const std::wstring HKCR; //����HKEY_CLASSES_ROOT;
	static const std::wstring HKCU; // ����HKEY_CURRENT_USER;
	static const std::wstring HKLM; // ����HKEY_LOCAL_MACHINE
	static const std::wstring HKU; //����HKEY_USERS

	static const std::wstring HKR_SERVICE; //����service�µ�hKR��·��
	static const std::wstring HKR_HW; //����hw�µ�hkr·��
	static const std::wstring HKR_NORM; //������������µ�hkr·��
	static const std::wstring HKR_COINSTALLERS; //����coinstallers�µ�hkr·��
	static const std::wstring HKR_GENCONFIGDATA; //GeneralConfigData�µ�hkr·��

	static const DWORD HKR_TYEP_NORM;
	static const DWORD HKR_TYEP_SERVICE;
	static const DWORD HKR_TYEP_HW;
	static const DWORD HKR_TYEP_COINSTALLERS;
	static const DWORD HKR_TYEP_GENCONFIGDATA;

	static const std::wstring s_strEndLine;
	static const std::wstring s_strDwordType;
	static const std::wstring s_strStringType;
	static const std::wstring s_strRegSzType2;
	static const std::wstring s_strRegSzType;
	static const std::wstring s_strBinaryType;
	static const std::wstring s_strRegESzType;
	static const std::wstring s_strRegMSzType;
	static const std::wstring s_strRegASzType;

	HANDLE m_hFileHandle;
	std::wstring m_strDeviceInfo;
	std::wstring m_strInfName;

	std::wstring m_strRegFileName;
	std::wstring m_strDriviceFileRootPath;
	std::wstring m_strInfFilePath;
	std::wstring m_strSvrName;
	std::wstring m_strMfgName;
	std::wstring m_strProductName;
	std::wstring m_strSectionName;
	std::wstring m_strDevSection;

	std::wstring m_strDate;
	std::wstring m_strVer;
	std::wstring m_strCompID;

	mapRetDataInfo_t m_mapServiceInfo;
	mapRegInfo_t m_mapAddReg;
	mapRegInfo_t m_mapDelReg;
	mapRetDataInfo_t m_mapCopyFile;
	mapSectionKeyValue_t m_mapCopyFilePaths;

	//���ڱ�����Сдת���Ļ�����
	wchar_t *m_pBufData;
	const DWORD m_dwBufSize;
	void toUpper(const std::wstring &strSrc, std::wstring &strDst);
};
#endif