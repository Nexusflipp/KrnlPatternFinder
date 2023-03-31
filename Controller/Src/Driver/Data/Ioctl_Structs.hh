#pragma once
#include "../../Include/Inc_Base.hh"

typedef struct _SYSMODBASE
{
	IN	LPCWSTR		szModName;
	OUT ULONGLONG*	ullBaseAddr;

}SYSMODBASE, *PSYSMODBASE;

typedef struct _SYSMODSECTION
{
	IN	ULONGLONG	ullModBaseAddr;
	IN	CONST CHAR* szSectName;
	OUT ULONGLONG*	ullSectBaseAddr;
	OUT SIZE_T*		stSizeOfSect;

}SYSMODSECTION, *PSYSMODSECTION;

typedef struct _KRNLFINDPATTERN
{
	IN	UCHAR*		szBase;
	IN	SIZE_T		ullSize;
	IN	CONST CHAR* szPattern;
	IN	CONST CHAR* szMask;
	OUT ULONGLONG*	ullAddr;

}KRNLFINDPATTERN, *PKRNLFINDPATTERN;