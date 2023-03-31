#pragma once
#include "Src/Include/Inc_Base.hh"

EXTERN "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegPath);
EXTERN "C" VOID UnloadDriver(PDRIVER_OBJECT pDrvObj);