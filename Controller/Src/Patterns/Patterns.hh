#pragma once
#include "Structs.hh"
#include "../Driver/Driver.hh"
#include "../Include/Inc_Base.hh"

namespace PAT
{
	NTSTATUS Main();
	void GetWin32KFull(ULONGLONG ullTxtBase, SIZE_T	stTextSize);
}