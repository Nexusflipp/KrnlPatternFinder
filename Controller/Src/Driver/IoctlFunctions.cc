#include "Driver.hh"
#include "Data/Definitions.hh"
#include "Data/Ioctl_Structs.hh"

NTSTATUS Driver::KrnlGetSysModBaseAddr(IN LPCWSTR szModName, OUT ULONGLONG* ullBaseAddr)
{
	if (m_hDriver == INVALID_HANDLE_VALUE)
		return STATUS_CONNECTION_INVALID;

	ULONG		ulBytes		= 0;
	SYSMODBASE	SysModBase	= { 0 };

	SysModBase.szModName	= szModName;
	SysModBase.ullBaseAddr	= ullBaseAddr;

	if (!DeviceIoControl(m_hDriver, IOCTL_REQ_SYSMOD_BASE, &SysModBase, sizeof(SysModBase), nullptr, NULL, &ulBytes, NULL))
		return STATUS_UNSUCCESSFUL;

	return STATUS_SUCCESS;
}

NTSTATUS Driver::KrnlGetSysModSeg(IN ULONGLONG ullModBaseAddr, IN CONST CHAR* szSegName, OUT ULONGLONG* ullSectBaseAddr, OUT SIZE_T* stSizeOfSect)
{
	if (m_hDriver == INVALID_HANDLE_VALUE)
		return STATUS_CONNECTION_INVALID;

	ULONG			ulBytes		= 0;
	SYSMODSECTION	SysModSect	= { 0 };

	SysModSect.ullModBaseAddr	= ullModBaseAddr;
	SysModSect.szSectName		= szSegName;
	SysModSect.ullSectBaseAddr	= ullSectBaseAddr;
	SysModSect.stSizeOfSect		= stSizeOfSect;

	if (!DeviceIoControl(m_hDriver, IOCTL_REQ_SYSMOD_SEGMENT, &SysModSect, sizeof(SysModSect), nullptr, NULL, &ulBytes, NULL))
		return STATUS_UNSUCCESSFUL;

	return STATUS_SUCCESS;
}

NTSTATUS Driver::KrnlFindPattern(IN UCHAR* szBase, IN SIZE_T ullSize, IN CONST CHAR* szPattern, IN CONST CHAR* szMask, OUT ULONGLONG* ullAddr)
{
	if (m_hDriver == INVALID_HANDLE_VALUE)
		return STATUS_CONNECTION_INVALID;

	ULONG			ulBytes			=	0;
	KRNLFINDPATTERN	KrnlFindPattern = { 0 };

	KrnlFindPattern.szBase		= szBase;
	KrnlFindPattern.ullSize		= ullSize;
	KrnlFindPattern.szPattern	= szPattern;
	KrnlFindPattern.szMask		= szMask;
	KrnlFindPattern.ullAddr		= ullAddr;

	if (!DeviceIoControl(m_hDriver, IOCTL_REQ_FIND_PATTERN, &KrnlFindPattern, sizeof(KrnlFindPattern), nullptr, NULL, &ulBytes, NULL))
		return STATUS_UNSUCCESSFUL;

	return STATUS_SUCCESS;
}