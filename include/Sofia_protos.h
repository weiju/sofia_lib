#ifndef _VBCCINLINE_SOFIA_H
#define _VBCCINLINE_SOFIA_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

const char * __SOFIA_OpenFileReq(__reg("a6") struct Library *, __reg("d1") struct Window * window, __reg("d2") const char * title, __reg("d3") const char * confirm_text)="\tjsr\t-30(a6)";
#define SOFIA_OpenFileReq(window, title, confirm_text) __SOFIA_OpenFileReq(SofiaBase, (window), (title), (confirm_text))

#endif /*  _VBCCINLINE_SOFIA_H  */
