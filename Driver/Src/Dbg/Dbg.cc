#include "Dbg.hh"

#if defined (_DEBUG) || defined(REL_DBG_MSG)
VOID DBGF::DbgMsg(CONST CHAR* Format, ...)
{
	CHAR MsgBuff[420];
	va_list VaList;
	va_start(VaList, Format);
	const ULONG N = _vsnprintf_s(MsgBuff, sizeof(MsgBuff) - 1, Format, VaList);
	MsgBuff[N] = L'\0';

	vDbgPrintExWithPrefix("[+] [KrnlPatternFinder] -> ", DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, MsgBuff, VaList);

	va_end(VaList);
}
#endif