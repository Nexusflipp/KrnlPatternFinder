#pragma once
#include "../Include/Inc_Base.hh"

//  enable this macro to print krnl dbg msgs in release mode
//#define REL_DBG_MSG

#if defined(_DEBUG) || defined(REL_DBG_MSG)
namespace DBGF
{
	VOID DbgMsg(CONST CHAR* Format, ...);
}
#endif

#if defined (_DEBUG) || defined(REL_DBG_MSG)
#define Msg(x, ...) DBGF::DbgMsg(x, __VA_ARGS__)
#else
#define Msg(x, ...)
#endif