/**
 * @file dos13.h - a module for DOS 1.x interaction
 */
#pragma once
#ifndef __DOS13_H__
#define __DOS13_H__

#include "file_list.h"

/**
 * Scans the specified directory and returns the entries, if dirpath is NULL,
 * returns the list of all logical volumes.
 */
extern struct FileListEntry *scan_dir(const char *dirpath, int *num_entries);

#endif
