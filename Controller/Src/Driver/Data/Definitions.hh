#pragma once
#include <winioctl.h>

inline std::string szDriverPath;

#define DRIVER_NAME			L"patternfinder"
#define DRIVER_NAMEC		"patternfinder"
#define DRIVER_LINK			L"\\\\.\\"			DRIVER_NAME
#define DEVICE_NAME			L"\\Device\\"		DRIVER_NAME
#define DOS_DEVICE_NAME		L"\\DosDevices\\"	DRIVER_NAME
#define REG_PATH			L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\patternfinder"

#define IOCTL_REQ_SYSMOD_BASE		CTL_CODE(0x00000022, 0x1337, 0, 0x0001 | 0x0002)
#define IOCTL_REQ_SYSMOD_SEGMENT	CTL_CODE(0x00000022, 0x1338, 0, 0x0001 | 0x0002)
#define IOCTL_REQ_FIND_PATTERN		CTL_CODE(0x00000022, 0x1339, 0, 0x0001 | 0x0002)