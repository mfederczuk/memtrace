/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE3_INTERNAL_H
#define MEMTRACE3_INTERNAL_H

#if !defined(MEMTRACE3_H) && !(MEMTRACE3_INTERNAL_SOURCE + 0)
	#error Do not include _memtrace_internal.h directly, include memtrace.h instead.
#endif

#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memtrace3_internal_malloc  (size_t size,               const char* file, int line);
void* memtrace3_internal_calloc  (size_t nmemb, size_t size, const char* file, int line);
void* memtrace3_internal_realloc (void*  ptr,   size_t size, const char* file, int line);
void  memtrace3_internal_free    (void*  ptr,                const char* file, int line);

FILE* memtrace3_internal_fopen   (const char* pathname, char const* mode,               const char* file, int line);
FILE* memtrace3_internal_freopen (const char* pathname, char const* mode, FILE* stream, const char* file, int line);
int   memtrace3_internal_fclose  (FILE* stream,                                         const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif /* MEMTRACE3_INTERNAL_H */
