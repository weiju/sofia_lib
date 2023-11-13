/**
 * @file dos_compat.h
 *
 * Compatibility functions to implement AmigaDOS 2.x functionality on 1.x systems.
 */
#pragma once
#ifndef __DOS_COMPAT_H__
#define __DOS_COMPAT_H__

/**
 * Returns a pointer to the end of the next-to-last component of the path.
 * Mimics the behavior of the V36 function on a Kickstart 1.3 system.
 *
 * @param path pointer to a path string. May be relative to the current
 * directory or the current disk
 * @return pointer to the end of the next-to-last component of the path
 */
extern const char *dc_PathPart(const char *path);

/**
 * Returns the last component of a path.
 * Mimics the behavior of the V36 function on a Kickstart 1.3 system.
 *
 * @param path pointer to a path string. May be relative to the current
 * directory or the current disk
 * @return pointer to the last component of the path
 */
extern const char *dc_FilePart(const char *path);

/**
 * Appends a file/dir to the end of a path.
 * Mimics the behavior of the V36 function on a Kickstart 1.3 system.
 *
 * NOTE: currently does not handle leading "/" or ":", or relative path names
 * until I actually need it in a project
 *
 * @param dirname the path to add a file/directory name to
 * @param filename the filename or directory name to add. currently needs to be
          absolute (differs from V36 behavior)
 * @param size size in bytes of the space allocated for dirname.  Must
 *        not be 0
 * @return success - non-zero for ok, FALSE if the buffer would have overflowed.
 *         If an overflow would have occured, dirname will not be
 *         changed
 */
extern int dc_AddPart(char *dirname, const char *filename, int size);

#endif /* __DOS_COMPAT_H__ */
