#pragma once
#include "Structs.hh"

#define MZ 0x5A4D
#define IMAGE_SIZEOF_SHORT_NAME 8
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
#define INVALID_HANDLE_VALUE (HANDLE)(-1)
#define IMAGE_FIRST_SECTION(h) ((PIMAGE_SECTION_HEADER) ((ULONG_PTR)h+FIELD_OFFSET(IMAGE_NT_HEADERS64,OptionalHeader)+((PIMAGE_NT_HEADERS)(h))->FileHeader.SizeOfOptionalHeader))