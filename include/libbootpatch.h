#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

#ifndef START_LIBBOOTPATCH_NAME_SPACE
#define START_LIBBOOTPATCH_NAME_SPACE	namespace libbootpatch {
#endif
#ifndef END_LIBBOOTPATCH_NAME_SPACE
#define END_LIBBOOTPATCH_NAME_SPACE		}
#endif

START_LIBBOOTPATCH_NAME_SPACE

/// ������������
DWORD BootFlashPatch(LPCTSTR lpBootresFile, LPCTSTR lpWinloadFile, LPCTSTR lpWimFile,
	LPTSTR szErrorInfo, DWORD dwLength);

/// ������������
DWORD BootBackgroundPatch(LPCTSTR lpWinloadFile, LPCTSTR lpBackgroundFile,
	LPTSTR szErrorInfo, DWORD dwLength);

/// �������ֲ���
DWORD BootStringPatch(LPCTSTR lpWinloadMuiFile, LPCTSTR lpWinloadFile, LPCTSTR lpNewStirng,
	LPTSTR szErrorInfo, DWORD dwLength);


typedef struct tagBootPatchParam
{
	std::wstring strWinloadFile;

	/// ������������
	std::wstring strBootresFile;
	std::wstring strWimFile;

	/// ������������
	std::wstring strBackgroundFile;

	/// �������ֲ���
	std::wstring strWinloadMuiFile;
	std::wstring strNewStirng;

	bool bIsValid() const
	{
		return strWinloadMuiFile.length() > 0 &&
			((strBootresFile.length() > 0 && strWimFile.length() > 0) ||
			strBackgroundFile.length() > 0 ||
			(strWinloadMuiFile.length() > 0 && strNewStirng.length() > 0));
	}
} BOOTPATCHPARAM, *PBOOTPATCHPARAM;
/// ���ÿ�������
DWORD BootPatch(const BOOTPATCHPARAM& tBootPatchParam, LPTSTR szErrorInfo, DWORD dwLength);


END_LIBBOOTPATCH_NAME_SPACE