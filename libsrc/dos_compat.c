#include <stddef.h>
#include <string.h>

#include "dos_compat.h"

const char *dc_PathPart(const char *path)
{
    if (path) {
        int slen = strlen(path);
        if (slen == 0) return path;
        int i = slen - 1;
        for (i = slen - 1; i > 0; i--) {
            if (path[i] == '/') break;
            if (path[i] == ':' && i < (slen - 1)) return &(path[i + 1]);
        }
        return &(path[i]);
    }
    return NULL;
}

const char *dc_FilePart(const char *path)
{
    if (path) {
        int slen = strlen(path);
        if (slen == 0) return path;
        int i = slen - 1;
        for (i = slen - 1; i > 0; i--) {
            if (path[i] == '/') return &(path[i + 1]);
            if (path[i] == ':' && i < (slen - 1)) return &(path[i + 1]);
        }
        return &(path[i]);
    }
    return NULL;
}

int dc_AddPart(char *dirname, const char *filename, int size)
{
    if (size == 0) return 0;
    int pathlen = strlen(dirname);
    int filename_len = strlen(filename);
    // check final path length and return if it would exceed
    if ((pathlen + filename_len + 1) > size) return 0;

    char last_char = dirname[pathlen - 1];
    // Add the separator at the end if not a volume
    if (last_char != ':' && last_char != '/') {
        dirname[pathlen] = '/';
        dirname[pathlen + 1] = '\0';
        pathlen++;
    }
    strncat(dirname, filename, size - pathlen);
    return 1;
}
