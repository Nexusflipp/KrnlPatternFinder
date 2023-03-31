#pragma once
#include "../Include/Inc_Base.hh"
#include "../Defs/Driver/Ioctl_Structs.hh"

namespace COM
{
	//  ioctl dispatcher
	NTSTATUS Main(PDEVICE_OBJECT pDrvObj, PIRP pIrp);

	//  functions associated with the ioctls
	NTSTATUS IoctlSysModBase(PSYSMODBASE pSysModBase);
	NTSTATUS IoctlSysModSeg(PSYSMODSECTION pSysModSection);
	NTSTATUS IoctlKrnlFindPattern(PKRNLFINDPATTERN pKrnlFindPattern);
}