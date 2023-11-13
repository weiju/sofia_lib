/**
 * @file file_list.h
 *
 * File list implementation, this is a system independent module that can be unit tested
 * easily.
 */
#pragma once
#ifndef __FILE_LIST_H__
#define __FILE_LIST_H__

#ifdef __VBCC__
#include <exec/types.h>

#else

#include <stdint.h>
typedef uint16_t UWORD;
typedef uint8_t BOOL;
#ifndef NULL
#define NULL (0L)
#endif
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#endif /* __VBCC__ */

#define FILETYPE_FILE   0
#define FILETYPE_DIR    1
#define FILETYPE_VOLUME 2

// This file requester is only for 1.x, so 31 characters is the
// maximum
#define MAX_FILENAME_LEN 31

/**
 * Store file list entries in these entries. Storing a previous pointer allows us to
 * navigate backwards, e.g. for scrolling up a file list.
 */
struct FileListEntry {
    /** \brief next entry in the list */
    struct FileListEntry *next;
    /** \brief previous entry in the list */
    struct FileListEntry *prev;
    /** \brief type of entry */
    UWORD file_type;
    /** \brief index in the list */
    UWORD index;
    /** \brief selection flag */
    UWORD selected;
    /** \brief file name */
    char name[MAX_FILENAME_LEN + 1];
};

/**
 * Free memory for all entries in the file list.
 *
 * @param entries list of file entries
 */
extern void free_file_list(struct FileListEntry *entries);

/**
 * Allocates a new file list entry.
 *
 * @return pointer to allocated and initialized FileListEntry element
 */
extern struct FileListEntry *new_file_list_entry();

/**
 * Sorts the specified list of FileListEntry elements.
 *
 * @param list list of entries
 * @param asc flag to indicate the sort order, TRUE for ascending, FALSE
 *            for descending
 */
extern struct FileListEntry *sort_file_list(struct FileListEntry *list, BOOL asc);

#endif /* __FILE_LIST_H__ */
