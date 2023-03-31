#include "Com.hh"
#include "Ioctl_Codes.hh"
#include "../Defs/Driver/Ioctl_Structs.hh"

NTSTATUS COM::Main(PDEVICE_OBJECT pDrvObj, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(pDrvObj);

	NTSTATUS Status				= STATUS_SUCCESS;
	PIO_STACK_LOCATION pIoStack = IoGetCurrentIrpStackLocation(pIrp);

	if (pIoStack->MajorFunction == IRP_MJ_DEVICE_CONTROL)
	{
		ULONG ulCtrlCode = NULL;
		ULONG pInBuffLen = NULL;
		ULONG pOutBuffLen = NULL;

		PVOID pBuff = pIrp->AssociatedIrp.SystemBuffer;
		ulCtrlCode = pIoStack->Parameters.DeviceIoControl.IoControlCode;
		pInBuffLen = pIoStack->Parameters.DeviceIoControl.InputBufferLength;
		pOutBuffLen = pIoStack->Parameters.DeviceIoControl.OutputBufferLength;

		switch (ulCtrlCode)
		{

		case IOCTL_REQ_SYSMOD_BASE:
		{
			if (pInBuffLen >= sizeof(PSYSMODBASE) && pBuff)
				pIrp->IoStatus.Status = IoctlSysModBase(REINTER<PSYSMODBASE>(pBuff));
			else
				return pIrp->IoStatus.Status = STATUS_INFO_LENGTH_MISMATCH;

			break;
		}

		case IOCTL_REQ_SYSMOD_SEGMENT:
		{
			if (pInBuffLen >= sizeof(PSYSMODSECTION) && pBuff)
				pIrp->IoStatus.Status = IoctlSysModSeg(REINTER<PSYSMODSECTION>(pBuff));
			else
				return pIrp->IoStatus.Status = STATUS_INFO_LENGTH_MISMATCH;

			break;
		}

		case IOCTL_REQ_FIND_PATTERN:
		{
			if (pInBuffLen >= sizeof(PKRNLFINDPATTERN) && pBuff)
				pIrp->IoStatus.Status = IoctlKrnlFindPattern(REINTER<PKRNLFINDPATTERN>(pBuff));
			else
				return pIrp->IoStatus.Status = STATUS_INFO_LENGTH_MISMATCH;

			break;
		}

		default:
			break;
		}
	}

	Status = pIrp->IoStatus.Status;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return Status;
}
