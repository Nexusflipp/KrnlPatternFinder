#include "Patterns.hh"
#include "Structs.hh"
#include "../Dbg/Dbg.hh"

std::array<Drivers, 3> DriverInfo = 
{{
	{ L"win32k.sys",	0, 0, 0, nullptr},
	{ L"win32kfull.sys",	0, 0, 0, PAT::GetWin32KFull},
	{ L"win32kbase.sys",	0, 0, 0, nullptr}
}};

NTSTATUS PAT::Main()
{
	NTSTATUS Status = STATUS_SUCCESS;

	for (auto& Drvs : DriverInfo)
	{
		Status = Drv->KrnlGetSysModBaseAddr(Drvs.szDrvName, &Drvs.ullBase);
		if (!NT_SUCCESS(Status))
		{
			DBG::PrintObjHex(LogType::Err, Drvs.szDrvName, Status);
			return Status;
		}
		else
			DBG::PrintObjHex(LogType::Info, Drvs.szDrvName, Drvs.ullBase);

		Status = Drv->KrnlGetSysModSeg(Drvs.ullBase, ".text", &Drvs.ullTxtBase, &Drvs.stTextSize);
		if (!NT_SUCCESS(Status))
		{
			DBG::PrintObjHex(LogType::Err, L"Failed to get text segment from", Drvs.szDrvName, Status);
			return Status;
		}
		else
			DBG::PrintObjHex(LogType::Info, Drvs.szDrvName, L"Text Segment", Drvs.ullTxtBase);

		if (Drvs.PatternExec != nullptr)
			Drvs.PatternExec(Drvs.ullTxtBase, Drvs.stTextSize);
	}

	return Status;
}
