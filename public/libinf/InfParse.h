#ifndef _INF_PARSE_H_
#define _INF_PARSE_H_

#include "comment.h"
#include <SetupAPI.h>
#pragma comment(lib, "setupapi.lib")

class CInfParse
{
	struct tDataKeyVal
	{
		std::wstring strKey;
		std::wstring strVal;
	};

	typedef std::vector<tDataKeyVal> vecSectionDataKV_t;

public:
	CInfParse();
	~CInfParse();

public:
	BOOL OpenInfFile(const wchar_t *pFileName, const wchar_t *pFileRelativePath);
	//BOOL OpenInfFile(const wchar_t *pFileName);
	BOOL CloseInfFile();
	
	//
	//���º�������infתxmlʱ ��ȡ��Ϣ

	BOOL GetDriverDate(std::wstring &strDate);
	BOOL GetDriverVer(std::wstring &strVer);
	BOOL GetProvider(std::wstring &strProvider);
	BOOL GetSupportOS(vecSectionFileds_t &vecSupportOSs);
	BOOL GetInfName(std::wstring &name);

	//��ȡManufacturer�У�osǰ����ֶ�ֵ��mfg����
	BOOL GetModulesSectionName(vecSectionFileds_t &vecNames);

	//��ȡven��dev��rev��ֵ
	//����value��˳��ven��dev��rev��ÿ����һ��
	//����value�ĳ���Ӧ����3�ı���
	BOOL GetModulesSectionInfo(const wchar_t *pModuleSection, vecSectionFileds_t &value);
	
	//��GetModulesSectionInfo��ȣ���ȡ����ֵ������subsys
	BOOL GetModuleSectionAllData(const wchar_t *pMfgName, vecSectionFileds_t &value);
	
	//
	//���º�������infתregʱ ��ȡ��Ϣ

	//����os,ven,dev,rev,subsys����Ϣ����ȡ����Ϣ
	//false��ʾû���ʺϵĶ�
	//������Ϣ���뱣֤��ȷƥ��
	BOOL GetSectionName(tSysInfo &sysInfo, std::wstring &strSectionName, std::wstring &strDisplayName, std::wstring &strDevSection);

	//��ȡaddreg����Ϣ
	//���������Ҫ����services�е�addreg��Ϣ
	//���ؽ��
	//key:AddService�еĵ�һ���ӽڵ�����
	//value:addreg������
	BOOL GetAddRegInfo(const wchar_t *pSectionName, mapRetDataInfo_t& mapAddRegInfo, std::wstring &strSvrName);
	
	//���������Ҫ���ڻ�ȡ��services��addreg��Ϣ
	BOOL GetAddRegInfo(const wchar_t *pSectionName, vecSectionFileds_t& vecAddRegInfo);

	//��ȡdelreg��Ϣ
	//���������Ҫ���ڻ�ȡservice�е�delreg��Ϣ
	BOOL GetDelRegInfo(const wchar_t *pSectionName, mapRetDataInfo_t& mapDelRegInfo);
	
	//���������Ҫ���ڻ�ȡ��services�е�delreg��Ϣ
	BOOL GetDelRegInfo(const wchar_t *pSectionName, vecSectionFileds_t& vecDelRegInfo);

	//��ȡservies��ServiceType��StartType��ErrorControl��ServiceBinary��LoadOrderGroup����Ϣ
	//���ؽ��
	//key:AddService�еĵ�һ���ӽڵ�����
	//value:����ServiceType��StartType��ErrorControl��ServiceBinary��LoadOrderGroup��displayname���е�����
	BOOL GetServiceInfo(const wchar_t *pSectionName, mapRetDataInfo_t& mapServiceInfo);

	//��ȡcopyfile����Ϣ
	BOOL GetCopyFileInfo(const wchar_t *pSectionName, mapRetDataInfo_t& mapDelRegInfo);

	//��ȡcopyfile��·����Ϣ
	BOOL GetCopyFilePath(std::wstring &strOSArch, mapSectionKeyValue_t &mapFilePaths);

	//��ȡ������Ϣ
	BOOL GetManufacture(std::wstring &strMfg);

	//��ȡcat�ļ�����
	BOOL GetCatFileName(std::wstring &strCatFileName);

private:
	//��ȡָ���ε�ָ������
	BOOL ReadSectionKey(const wchar_t *pSection, const wchar_t *pKey, std::wstring &strValue);

	//��ȡָ���ε���������
	BOOL ReadSectionAllValue(const wchar_t *pSection, vecSectionDataKV_t &vecValue);

	//��ȡָ���ε�ͬ����������
	BOOL ReadSectionAllValue(const wchar_t *pSection, const wchar_t *pKeyName, vecSectionFileds_t &vecSection);

	//��ȡָ���ε���������
	BOOL ReadSectionAllValue(const wchar_t *pSection, vecSectionFileds_t &vecAddRegSection);

	//��ȡָ���Σ�ָ��key�Ĳ���value
	//ע��:index�У�0��ʾkey��1��ʼ��ʾvalue��ÿ������һ��value
	BOOL ReadSectionSubkey(const wchar_t *pSection, const wchar_t *pKey, DWORD index, std::wstring &strValue);

	//��ȡָ���Σ�ָ��ֵ�����н��������vector
	BOOL ReadSectionKeyAllValue(const wchar_t *pSection, const wchar_t *pKey, vecSectionFileds_t &fileds);
	BOOL GetFields(INFCONTEXT &ctx, vecSectionFileds_t &fileds);

	//��ȡ�ַ����е�ָ��С�ֶε�����
	BOOL GetSubStringValue(std::wstring &strSrcString, wchar_t *pSubName, std::wstring &strValue);

	//����dev,ven,rev,subsys��Ϣ��ת�����ַ���
	void DevDwordInfo2StrInfo(tSysInfo &sysInfo, std::wstring &strDevInfo);

	//���ַ�������ȡdev,ven,rev,subsys��Ϣ
	bool DevStrInfo2DwordInfo(std::wstring &strDevInfo, tSysInfo &sysInfo);

	//��ȡservices��Ϣ��AddService�ֶε����ݣ�reg���� �� ��Ӧ��reg���ݶ����ƣ�����һ�͵���С������
	BOOL GetServicesAddServiceSection(const wchar_t *pSection, vecSectionFileds_t &vecRegSectionInfo);

	//
	BOOL GetAddServiceOperator(const wchar_t *pSection, const wchar_t *pKey, mapRetDataInfo_t& mapDelRegInfo);

	//��ȡservices�У�addreg��delreg�ֶε�����
	BOOL GetServicesRegInfo(const wchar_t *pSection, const wchar_t *pKey, vecSectionFileds_t &vecAddRegSection);

	//�ֽ��ַ���
	BOOL SplitString(const std::wstring &strSrc, const wchar_t mask, std::vector<std::wstring> &vecStrings);

	//��ȡ�ļ���Ŀ��·��
	BOOL GetDstPath(const std::wstring *pKey, mapSectionKeyValue_t &mapDstPath);

private:
	HANDLE m_hInfHandle;
	std::wstring m_strFileName;
};
#endif