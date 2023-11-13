#include <exec/types.h>
#include <exec/resident.h>
#include <exec/libraries.h>
#include "lib_defs.h"

/* ----------------------------------------------------------------------------------------
   ! ROMTag and Library initialization structure:
   !
   ! Below you find the ROMTag, which is the most important "magic" part of a library
   ! (as for any other resident module). You should not need to modify any of the
   ! structures directly, since all the data is referenced from constants from somewhere else.
   !
   ! You may place the ROMTag directly after the LibStart (-> StartUp.c) function as well.
   !
   ! Note, that the data initialization structure may be somewhat redundant - it's
   ! for demonstration purposes.
   !
   ! EndResident can be placed somewhere else - but it must follow the ROMTag and
   ! it must not be placed in a different SECTION.
   ---------------------------------------------------------------------------------------- */

extern struct InitTable InitTab;
extern APTR EndResident; /* below */
extern char SofiaLibName[];
extern char SofiaLibID[];

const struct Resident ROMTag =     /* do not change */
{
    RTC_MATCHWORD,
    &ROMTag,        /* Pointer to the previous word */
    &EndResident,
    RTF_AUTOINIT,
    VERSION,
    NT_LIBRARY,
    0,
    &SofiaLibName[0],
    &SofiaLibID[0],
    &InitTab
};

APTR EndResident;
