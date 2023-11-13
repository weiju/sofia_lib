#ifndef __CLIB_SOFIA_PROTOS_H__
#define __CLIB_SOFIA_PROTOS_H__

#include <sofia/sofia.h>

const char *SOFIA_OpenFileReq(struct Window *window,
                              const char *title,
                              const char *confirm_text);

#endif /* __CLIB_SOFIA_PROTOS_H__ */
