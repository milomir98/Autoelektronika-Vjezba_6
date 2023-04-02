#ifndef _EXTINT_H
#define _EXTINIT_H

#include <Windows.h>

#define portINTERRUPT_EXTSIM	( 2UL )

DWORD WINAPI prvExternalInterruptCatcher(LPVOID lpParameter);

#endif