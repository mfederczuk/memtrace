// <_memtrace.h>
/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef __MEMTRACE_H
#define __MEMTRACE_H

#if !defined(_MEMTRACE_H) && !(_MEMTRACE_SOURCE + 0)
	#error Do not include _memtrace.h directly, include memtrace.h instead.
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memtrace_internal_malloc  (size_t size,               const char* file, int line);
void  memtrace_internal_free    (void*  ptr,                const char* file, int line);
void* memtrace_internal_calloc  (size_t nmemb, size_t size, const char* file, int line);
void* memtrace_internal_realloc (void*  ptr,   size_t size, const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif /* __MEMTRACE_H */
