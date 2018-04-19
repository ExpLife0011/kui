#ifndef _COMMENT_
#define _COMMENT_
#include <string>
#include <map>
#include <vector>
#include <Windows.h>

struct tSysInfo;

#define OS_51_X86_A	("5.1_x86")
#define OS_61_X86_A	("6.1_x86")
#define OS_61_X64_A	("6.1_x64")
#define OS_10_X86_A	("10.0_x86")
#define OS_10_X64_A	("10.0_x64")

//inf�ļ�����ʱʹ�õ����ݽṹ
typedef std::map<std::wstring, std::wstring> mapSectionKeyValue_t;
typedef std::vector<std::wstring> vecSectionFileds_t;
typedef std::map<std::wstring, int> mapKeyCount_t;
typedef std::map<std::wstring, vecSectionFileds_t> mapRetDataInfo_t;

////��ȡxml���ݵķ��ؽ��
////����tinyxml2ʹ�ö��ֽڱ��룬�������ﵥ������һ�Σ�����д����
//typedef std::map<std::string, int> mapKeyInfo_t;
////xml�ļ����ݣ�key:os; val: key:ven_dev_rev, val:count
//typedef std::map<std::string, mapKeyInfo_t> mapXmlComtext_t;

extern void ParseCmdWideChar2MultiByte(const wchar_t *pData, std::string &strRestCmd);
extern void ParseCmdWideChar2MultiByte(std::wstring &strSrc, std::string &strRestCmd);
#endif