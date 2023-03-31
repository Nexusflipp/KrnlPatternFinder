#include "Driver.hh"
#include "Src/Handler.hh"
#include "Src/Dbg/Dbg.hh"

EXTERN "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegPath)
{
	UNREFERENCED_PARAMETER(pRegPath);

	NTSTATUS Status = HANDLER::Init(pDrvObj);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed to init main subroutine -> 0x%llx", Status);
		return Status;
	}

	Msg("Initialized driver!");

	return STATUS_SUCCESS;
}

EXTERN "C" VOID UnloadDriver(PDRIVER_OBJECT pDrvObj)
{
	NTSTATUS Status = HANDLER::Unload(pDrvObj);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed to unload driver -> 0x%llx", Status);
	}

	Msg("Unloaded driver!");
}