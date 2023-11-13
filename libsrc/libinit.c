#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <exec/execbase.h>
#include <exec/initializers.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include "compiler.h"
#include "include/sofia/sofiabase.h"
#include "lib_defs.h"
#include "libfuncs.h"


/**
 * Information strings.
 */
char SofiaLibName[] = "sofia.library";
char SofiaLibID[] = VSTRING;
char Copyright [] = "(C)opyright 2023 by Wei-ju Wu. All rights reserved.";
char VERSTRING [] = VERSTAG;

struct MyDataInit DataTab = {
    0xe000, 8, NT_LIBRARY,
    0x0080, 10, (ULONG) &SofiaLibName[0],
    0xe000, 14, LIBF_SUMUSED|LIBF_CHANGED,
    0xd000, 20, VERSION,
    0xd000, 22, REVISION,
    0x80,   24, (ULONG) &SofiaLibID[0],
    (ULONG) 0
};


struct SofiaBase *InitLib(register __a6 struct ExecBase    *sysbase,
                          register __a0 SEGLISTPTR          seglist,
                          register __d0 struct SofiaBase *sofb);

struct SofiaBase *OpenLib(register __a6 struct SofiaBase *SofiaBase);

SEGLISTPTR CloseLib(register __a6 struct SofiaBase *SofiaBase);
SEGLISTPTR ExpungeLib(register __a6 struct SofiaBase *sofb);
ULONG ExtFuncLib(void);

extern APTR FuncTab[];

struct InitTable InitTab = {
    (ULONG)               sizeof(struct SofiaBase),
    (APTR              *) &FuncTab[0],
    (struct MyDataInit *) &DataTab,
    (APTR)                InitLib
};

APTR FuncTab[] = {
    (APTR) OpenLib,
    (APTR) CloseLib,
    (APTR) ExpungeLib,
    (APTR) ExtFuncLib,

    /* library specific functions here */
    (APTR) SOFIA_OpenFileReq,
    /* table end */
    (APTR) ((LONG)-1)
};

extern struct SofiaBase *SofiaBase;

/* ----------------------------------------------------------------------------------------
   ! InitLib:
   !
   ! This one is single-threaded by the Ramlib process. Theoretically you can do, what
   ! you like here, since you have full exclusive control over all the library code and data.
   ! But due to some bugs in Ramlib V37-40, you can easily cause a deadlock when opening
   ! certain libraries here (which open other libraries, that open other libraries, that...)
   !
   ---------------------------------------------------------------------------------------- */
struct ExecBase      *SysBase = NULL;
struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;
struct DOSBase *DOSBase;
struct LayersBase *LayersBase;


struct SofiaBase *InitLib(register __a6 struct ExecBase      *sysbase,
                          register __a0 SEGLISTPTR            seglist,
                          register __d0 struct SofiaBase   *sofb)
{
    SofiaBase = sofb;
    SofiaBase->sofb_SysBase = sysbase;
    SofiaBase->sofb_SegList = seglist;

    SysBase = (*((struct ExecBase **) 4));
    SofiaBase->sofb_SysBase       = SysBase;
    /* TODO: Open other libraries and init static data here */
    SofiaBase->sofb_IntuitionBase = (struct IntuitionBase *) OpenLibrary("intuition.library", 0);
    SofiaBase->sofb_GfxBase = (struct GfxBase *) OpenLibrary("graphics.library", 0);
    SofiaBase->sofb_DOSBase = (struct DOSBase *) OpenLibrary("dos.library", 0);
    SofiaBase->sofb_LayersBase = (struct LayersBase *) OpenLibrary("layers.library", 0);
    return SofiaBase;
}

/* ----------------------------------------------------------------------------------------
   ! OpenLib()/CloseLib()/ExpungeLib():
   !
   ! This one is enclosed within a Forbid/Permit pair by Exec V37-40. Since a Wait() call
   ! would break this Forbid/Permit(), you are not allowed to start any operations that
   ! may cause a Wait() during their processing. It's possible, that future OS versions
   ! won't turn the multi-tasking off, but instead use semaphore protection for this
   ! function.
   !
   ! Currently you only can bypass this restriction by supplying your own semaphore
   ! mechanism. Since expunging can't be done twice, it should be avoided for that
   ! function.
   ---------------------------------------------------------------------------------------- */

struct SofiaBase *OpenLib(register __a6 struct SofiaBase *SofiaBase)
{
    SofiaBase->sofb_LibNode.lib_OpenCnt++;
    SofiaBase->sofb_LibNode.lib_Flags &= ~LIBF_DELEXP;

    IntuitionBase = SofiaBase->sofb_IntuitionBase;
    GfxBase = SofiaBase->sofb_GfxBase;
    DOSBase = SofiaBase->sofb_DOSBase;
    LayersBase = SofiaBase->sofb_LayersBase;

    return SofiaBase;
}

SEGLISTPTR CloseLib(register __a6 struct SofiaBase *SofiaBase)
{
    SofiaBase->sofb_LibNode.lib_OpenCnt--;

    if (!SofiaBase->sofb_LibNode.lib_OpenCnt) {
        if (SofiaBase->sofb_LibNode.lib_Flags & LIBF_DELEXP) {
            return ExpungeLib(SofiaBase);
        }
    }
    return NULL;
}

SEGLISTPTR ExpungeLib(register __a6 struct SofiaBase *sofb)
{
    struct SofiaBase *SofiaBase = sofb;
    SEGLISTPTR seglist;

    if (!SofiaBase->sofb_LibNode.lib_OpenCnt) {
        ULONG negsize, possize, fullsize;
        UBYTE *negptr = (UBYTE *) SofiaBase;

        seglist = SofiaBase->sofb_SegList;
        Remove((struct Node *)SofiaBase);
        /* Close libraries here */
        if (SofiaBase->sofb_GfxBase) CloseLibrary((struct Library *) SofiaBase->sofb_GfxBase);
        if (SofiaBase->sofb_IntuitionBase) CloseLibrary((struct Library *) SofiaBase->sofb_IntuitionBase);

        /**
         * Free memory for the base structure here.
         */
        negsize  = SofiaBase->sofb_LibNode.lib_NegSize;
        possize  = SofiaBase->sofb_LibNode.lib_PosSize;
        fullsize = negsize + possize;
        negptr  -= negsize;

        FreeMem(negptr, fullsize);
        return seglist;
    }

    SofiaBase->sofb_LibNode.lib_Flags |= LIBF_DELEXP;
    return NULL;
}

/* Reserved, not used */
ULONG ExtFuncLib(void) { return (ULONG) NULL; }

struct SofiaBase *SofiaBase = NULL;
