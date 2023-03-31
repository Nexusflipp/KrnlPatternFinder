#pragma once
#include "../Include/Inc_Base.hh"

namespace MEM
{
	NTSTATUS 
	GetKrnlModBase
	(IN LPCWSTR szModName, OUT PULONGLONG ullModBase);

	NTSTATUS 
	FindKrnlModSeg
	(IN ULONGLONG ullModBaseAddr, IN CONST CHAR* szSegName, OUT ULONGLONG* ullSegBaseAddr, OUT SIZE_T* stSizeOfSeg);

	NTSTATUS
	FindPattern
	(IN UCHAR* szBase, IN CONST SIZE_T ullSize, IN CONST CHAR* szPattern, IN CONST CHAR* szMask, OUT ULONGLONG* ullAddr);
}