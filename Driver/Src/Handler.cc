#include "Handler.hh"
#include "Com/Com.hh"
#include "Dbg/Dbg.hh"
#include "Mem/Mem.hh"
#include "../Driver.hh"
#include "Include/Inc_Driver.hh"

NTSTATUS HANDLER::Init(PDRIVER_OBJECT pDrvObj)
{
	NTSTATUS		Status	= STATUS_SUCCESS;
	PDEVICE_OBJECT	pDev	= NULL;
	UNICODE_STRING	DevName = { 0 };
	UNICODE_STRING	DevLink = { 0 };

	RtlUnicodeStringInit(&DevName, DEVICE_NAME);
	RtlUnicodeStringInit(&DevLink, DOS_DEVICE_NAME);

	Status = IoCreateDevice(pDrvObj, NULL, &DevName, FILE_DEVICE_UNKNOWN, NULL, FALSE, &pDev);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed to create device -> 0x%llx", Status);
		return Status;
	}

	pDrvObj->DriverUnload							= UnloadDriver;
	pDrvObj->MajorFunction[IRP_MJ_CREATE]			=
	pDrvObj->MajorFunction[IRP_MJ_CLOSE]			=
	pDrvObj->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= COM::Main;

	Status = IoCreateSymbolicLink(&DevLink, &DevName);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed to create symbolic link -> 0x%llx", Status);
		IoDeleteDevice(pDev);
		return Status;
	}

	return Status;
}

NTSTATUS HANDLER::Unload(PDRIVER_OBJECT pDrvObj)
{
	UNICODE_STRING deviceLinkUnicodeString;
	RtlUnicodeStringInit(&deviceLinkUnicodeString, DOS_DEVICE_NAME);

	NTSTATUS Status = IoDeleteSymbolicLink(&deviceLinkUnicodeString);
	IoDeleteDevice(pDrvObj->DeviceObject);

	return Status;
}
