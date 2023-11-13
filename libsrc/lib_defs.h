#ifndef __LIB_DEFS_H__
#define __LIB_DEFS_H__

#include "sofia_rev.h"

struct MyDataInit                      /* do not change */
{
    UWORD ln_Type_Init;      UWORD ln_Type_Offset;      UWORD ln_Type_Content;
    UBYTE ln_Name_Init;      UBYTE ln_Name_Offset;      ULONG ln_Name_Content;
    UWORD lib_Flags_Init;    UWORD lib_Flags_Offset;    UWORD lib_Flags_Content;
    UWORD lib_Version_Init;  UWORD lib_Version_Offset;  UWORD lib_Version_Content;
    UWORD lib_Revision_Init; UWORD lib_Revision_Offset; UWORD lib_Revision_Content;
    UBYTE lib_IdString_Init; UBYTE lib_IdString_Offset; ULONG lib_IdString_Content;
    ULONG ENDMARK;
};

/*
 * Data structures for this library
 */
struct InitTable                       /* do not change */
{
    ULONG              LibBaseSize;
    APTR              *FunctionTable;
    struct MyDataInit *DataTable;
    APTR               InitLibTable;
};

#endif /* __LIB_DEFS_H__ */
