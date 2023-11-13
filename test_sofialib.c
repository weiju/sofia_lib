#include <exec/types.h>
#include <exec/memory.h>
#include <intuition/intuition.h>
#include <clib/exec_protos.h>

#include <sofia/sofia.h>
#include <Sofia_protos.h>

#include <stdio.h>
#include <stdlib.h>

struct SofiaBase *SofiaBase = NULL;
struct Library *VersionBase = NULL;

int main(int argc, char **argv)
{
    SofiaBase = (APTR) OpenLibrary("sofia.library", 0);
    if (SofiaBase) {
        printf("SOFIA LIBRARY OPENED !\n");
        CloseLibrary((APTR) SofiaBase);
        exit(0);
    } else {
        printf("\nLibrary opening failed\n");
        exit(20);
    }
    printf("done.\n");
}
