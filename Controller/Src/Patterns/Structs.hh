#pragma once
#include "../Include/Inc_Base.hh"

struct Drivers
{
	const wchar_t* szDrvName;
	ULONGLONG	ullBase;
	ULONGLONG	ullTxtBase;
	SIZE_T		stTextSize;
	std::function<void(ULONGLONG, SIZE_T)> PatternExec;
};

struct Patterns
{
	std::string szFnName;
	const char* szPattern;
	const char* szMask;
	ULONGLONG ullAddr;
};