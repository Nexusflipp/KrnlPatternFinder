#include "Patterns.hh"
#include "Structs.hh"
#include "../Dbg/Dbg.hh"

std::array<Patterns, 3> Win32KFullPatt = 
{{
	{ "GreGetBkColor",		"\xE8\x00\x00\x00\x00\x48\x8B\xCF\x89\x45\xB0\xE8\x00\x00\x00\x00",										"x????xxxxxxx????",			0},
	{ "GreSetBkColor",		"\xE8\x00\x00\x00\x00\x8B\xD8\x48\x8B\x05\xE0\x71\x2D\x00\x48\x8B\x08\x8B\x91\x00\x00\x00\x00",			"x????xxxxxxxx?xxxxx????",	0},
	{ "GreSetBkMode",		"\xE8\x00\x00\x00\x00\x89\x45\x7F\x85\xC0\x0F\x00\x00\x00\x00\x00",										"x????xxxxxx?????",			0}
}};

void PAT::GetWin32KFull(ULONGLONG ullTxtBase, SIZE_T stTextSize)
{
	unsigned int iNotFound = 0;
	NTSTATUS Status = STATUS_SUCCESS;

	for (auto& Pat : Win32KFullPatt)
	{
		Status = Drv->KrnlFindPattern(REINTER<UCHAR*>(ullTxtBase), stTextSize, Pat.szPattern, Pat.szMask, &Pat.ullAddr);
		if (!NT_SUCCESS(Status))
		{
			DBG::PrintObjHex(LogType::Err, Pat.szFnName += ": Not found, status", Status);
			iNotFound++;
		}
		else
			DBG::PrintObjHex(LogType::Info, Pat.szFnName, Pat.ullAddr);
	}

	if (iNotFound > 0)
		DBG::PrintObj(LogType::Err, "Failed to find", iNotFound);
	else
		DBG::Print(LogType::Info, "Found all win32kfull signatures!");
}