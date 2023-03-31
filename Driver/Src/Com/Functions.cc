#include "Com.hh"
#include "../Mem/Mem.hh"
#include "../Dbg/Dbg.hh"

NTSTATUS COM::IoctlSysModBase(PSYSMODBASE pSysModBase)
{
	NTSTATUS Status = MEM::GetKrnlModBase(pSysModBase->szModName, pSysModBase->ullBaseAddr);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed call GetKrnlModBase -> 0x%llx", Status);
		return Status;
	}

	return Status;
}

NTSTATUS COM::IoctlSysModSeg(PSYSMODSECTION pSysModSection)
{
	NTSTATUS Status = MEM::FindKrnlModSeg(pSysModSection->ullModBaseAddr, pSysModSection->szSectName, pSysModSection->ullSectBaseAddr, pSysModSection->stSizeOfSect);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed calling FindKrnlModSect -> 0x%llx", Status);
		return Status;
	}
	
	return Status;
}

NTSTATUS COM::IoctlKrnlFindPattern(PKRNLFINDPATTERN pKrnlFindPattern)
{
	NTSTATUS Status = MEM::FindPattern(pKrnlFindPattern->szBase, pKrnlFindPattern->ullSize, pKrnlFindPattern->szPattern, pKrnlFindPattern->szMask, pKrnlFindPattern->ullAddr);
	if (!NT_SUCCESS(Status))
	{
		Msg("Failed calling FindPattern -> 0x%llx", Status);
		return Status;
	}

	return Status;
}
