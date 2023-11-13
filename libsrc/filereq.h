/** @file filereq.h - Filerequester for V1.x systems */
#pragma once
#ifndef __FILEREQ_H__
#define __FILEREQ_H__

/**
 * Open the file requester.
 *
 * @param window parent window
 * @param requester window title
 * @return selected file path or NULL
 */
extern const char *open_file(struct Window *window, const char *title, const char *confirm_text);

#endif /* __FILEREQ_H__ */
