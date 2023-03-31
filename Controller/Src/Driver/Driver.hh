#pragma once
#include "../Include/Inc_Base.hh"

class Driver
{
public:
	NTSTATUS Init();
	NTSTATUS ShutDown();

public:
	/// <summary>
	/// gets the mod base addr of a sys mod
	/// </summary>
	/// <param name="szModName: name of the sysmod"></param>
	/// <param name="ullBaseAddr: variable to store the base addr"></param>
	/// <returns>returns STATUS_CONNECTION_INVALID if the driver handle is invalid, STATUS_UNSUCCESSFUL if DeviceIoControl is zero, and STATUS_SUCCESS if the call was successful</returns>
	NTSTATUS 
	KrnlGetSysModBaseAddr
	(IN LPCWSTR szModName, OUT ULONGLONG* ullBaseAddr);

	/// <summary>
	/// gets the base addr and size of a sys mod
	/// </summary>
	/// <param name="ullModBaseAddr: base addr of the sys mod"></param>
	/// <param name="szSegName: which segment is targeted"></param>
	/// <param name="ullSectBaseAddr: variable to store the base addr"></param>
	/// <param name="stSizeOfSect: variable to store the size"></param>
	/// <returns>returns STATUS_CONNECTION_INVALID if the driver handle is invalid, STATUS_UNSUCCESSFUL if DeviceIoControl is zero, and STATUS_SUCCESS if the call was successful</returns>
	NTSTATUS 
	KrnlGetSysModSeg
	(IN ULONGLONG ullModBaseAddr, IN CONST CHAR* szSegName, OUT ULONGLONG* ullSectBaseAddr, OUT SIZE_T* stSizeOfSect);

	/// <summary>
	/// gets the addr of a byte pattern
	/// </summary>
	/// <param name="szBase: base addr for search"></param>
	/// <param name="ullSize: size of the mod/seg"></param>
	/// <param name="szPattern: byte pattern to search for"></param>
	/// <param name="szMask: mask of the pattern"></param>
	/// <param name="ullAddr: variable to store the addr"></param>
	/// <returns>returns STATUS_CONNECTION_INVALID if the driver handle is invalid, STATUS_UNSUCCESSFUL if DeviceIoControl is zero, and STATUS_SUCCESS if the call was successful</returns>
	NTSTATUS
	KrnlFindPattern
	(IN UCHAR* szBase, IN SIZE_T ullSize, IN CONST CHAR* szPattern, IN CONST CHAR* szMask, OUT ULONGLONG* ullAddr);

private:
	NTSTATUS LoadDriver(LPCSTR szDriverPath, LPCSTR szService);
	NTSTATUS InitCom();
	NTSTATUS UnloadDriver(LPCSTR szService);
	NTSTATUS RemoveCom();

private:
	HANDLE		m_hDriver;
	NTSTATUS	m_Status	= STATUS_UNSUCCESSFUL;
};

inline std::unique_ptr<Driver> Drv;