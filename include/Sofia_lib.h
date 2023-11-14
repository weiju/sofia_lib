#ifndef _INCLUDE_PRAGMA_SOFIA_LIB_H
#define _INCLUDE_PRAGMA_SOFIA_LIB_H

#ifndef CLIB_SOFIA_PROTOS_H
#include <clib/Sofia_protos.h>
#endif

#if defined(AZTEC_C) || defined(__MAXON__) || defined(__STORM__)
#pragma amicall(SofiaBase,0x01e,SOFIA_OpenFileReq(d1,d2,d3))
#endif
#if defined(_DCC) || defined(__SASC)
#pragma  libcall SofiaBase SOFIA_OpenFileReq      01e 32103
#endif

#endif	/*  _INCLUDE_PRAGMA_SOFIA_LIB_H  */
