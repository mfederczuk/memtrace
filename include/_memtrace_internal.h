/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE_INTERNAL_H
#define MEMTRACE_INTERNAL_H

#if !defined(MEMTRACE_H) && !(MEMTRACE_INTERNAL_SOURCE + 0)
	#error Do not include _memtrace_internal.h directly, include memtrace.h instead.
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

#endif /* MEMTRACE_INTERNAL_H */
