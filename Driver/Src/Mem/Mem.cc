#include "Mem.hh"
#include "../Dbg/Dbg.hh"
#include "../Include/Inc_Ntapi.hh"

NTSTATUS MEM::GetKrnlModBase(IN LPCWSTR szModName, OUT PULONGLONG ullModBase)
{
	UNICODE_STRING ModName;
	UNICODE_STRING PsLoModLi;
	RtlInitUnicodeString(&ModName, szModName);
	RtlInitUnicodeString(&PsLoModLi, L"PsLoadedModuleList");

	PLIST_ENTRY pLiEntry = REINTER<PLIST_ENTRY>(MmGetSystemRoutineAddress(&PsLoModLi));

	if (!pLiEntry)
		return STATUS_NOT_FOUND;

	for (PLIST_ENTRY pLink = pLiEntry; pLink != pLiEntry->Blink; pLink = pLink->Flink)
	{
		PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pLink, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		if (RtlEqualUnicodeString(&pEntry->BaseDllName, &ModName, TRUE))
		{
			if (pEntry->DllBase)
			{
				*ullModBase = REINTER<ULONGLONG>(pEntry->DllBase);
				return STATUS_SUCCESS;
			}
			else
				return STATUS_INVALID_ADDRESS;
		}
	}

	return STATUS_NOT_FOUND;
}

NTSTATUS MEM::FindKrnlModSeg(IN ULONGLONG ullModBaseAddr, IN CONST CHAR* szSegName, OUT ULONGLONG* ullSegBaseAddr, OUT SIZE_T* stSizeOfSeg)
{
	if (!ullModBaseAddr || REINTER<PIMAGE_DOS_HEADER>(ullModBaseAddr)->e_magic != MZ)
		return STATUS_INVALID_ADDRESS;

	CONST AUTO ntHeader			= REINTER<PIMAGE_NT_HEADERS64>(ullModBaseAddr + REINTER<PIMAGE_DOS_HEADER>(ullModBaseAddr)->e_lfanew);
	AUTO SegmentHeader			= IMAGE_FIRST_SECTION(ntHeader);

	for (USHORT i = 0; i < ntHeader->FileHeader.NumberOfSections; i++, SegmentHeader++)
	{
		if (strstr(REINTER<CONST CHAR*>(&SegmentHeader->Name), szSegName))
		{
			*ullSegBaseAddr		= ullModBaseAddr + SegmentHeader->VirtualAddress;
			*stSizeOfSeg		= SegmentHeader->Misc.VirtualSize;
			return STATUS_SUCCESS;
		}
	}

	return STATUS_NOT_FOUND;
}

NTSTATUS MEM::FindPattern(IN UCHAR* szBase, IN CONST SIZE_T ullSize, IN CONST CHAR* szPattern, IN CONST CHAR* szMask, OUT ULONGLONG* ullAddr)
{
	CONST AUTO PatternSize = strlen(szMask);

	for (SIZE_T i = {}; i < ullSize - PatternSize; i++)
	{
		for (SIZE_T j = {}; j < PatternSize; j++)
		{
			if (szMask[j] != '?' && *REINTER<UCHAR*>(szBase + i + j) != STATICCA<UCHAR>(szPattern[j]))
				break;

			if (j == PatternSize - 1)
			{
				*ullAddr = REINTER<ULONGLONG>(szBase) + i;
				return STATUS_SUCCESS;
			}
		}
	}

	return STATUS_NOT_FOUND;
}