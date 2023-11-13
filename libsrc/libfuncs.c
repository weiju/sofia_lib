#include <exec/types.h>
#include <exec/memory.h>

#include <clib/exec_protos.h>
#include <clib/intuition_protos.h>
#include <intuition/intuition.h>

#include "compiler.h"
#include "filereq.h"

const char *SOFIA_OpenFileReq(register __d1 struct Window *window,
                        register __d2 const char *title,
                        register __d3 const char *confirm_text)
{
    return open_file(window, title, confirm_text);
}
