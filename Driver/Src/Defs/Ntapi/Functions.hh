#pragma once
#include "../../Include/Inc_Base.hh"

EXTERN "C"
NTSTATUS
ZwQuerySystemInformation(ULONG InfoClass, PVOID Buffer, ULONG Lenght, PULONG ReturnLenght);