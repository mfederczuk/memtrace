/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE_H
#define MEMTRACE_H

#if defined(NDEBUG) && !(MEMTRACE_CONFIG_IGNORE_NDEBUG + 0)
	#warning NDEBUG is defined and memtrace.h is included.
#endif

#include <_memtrace_internal.h>
#include <stdlib.h>

#define malloc(size)        (memtrace_internal_malloc  (size,         __FILE__, __LINE__))
#define free(ptr)           (memtrace_internal_free    (ptr,          __FILE__, __LINE__))
#define calloc(nmemb, size) (memtrace_internal_calloc  (nmemb, size,  __FILE__, __LINE__))
#define realloc(ptr, size)  (memtrace_internal_realloc (ptr,  size,   __FILE__, __LINE__))

#endif /* MEMTRACE_H */
