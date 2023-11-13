#ifndef __SOFIA_SOFIABASE_H__
#define __SOFIA_SOFIABASE_H__

#ifndef  EXEC_LIBRARIES
#include <exec/libraries.h>
#endif /* EXEC_LIBRARIES_H */

struct SofiaBase
{
    struct Library         sofb_LibNode;
    SEGLISTPTR             sofb_SegList;
    struct ExecBase       *sofb_SysBase;
    struct IntuitionBase  *sofb_IntuitionBase;
    struct GfxBase        *sofb_GfxBase;
    struct DOSBase        *sofb_DOSBase;
    struct LayersBase     *sofb_LayersBase;
};

#endif /* __SOFIA_SOFIABASE_H__ */
