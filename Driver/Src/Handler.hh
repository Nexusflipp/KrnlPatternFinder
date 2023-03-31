#pragma once
#include "Include/Inc_Base.hh"

namespace HANDLER
{
	NTSTATUS Init(PDRIVER_OBJECT pDrvObj);
	NTSTATUS Unload(PDRIVER_OBJECT pDrvObj);
}