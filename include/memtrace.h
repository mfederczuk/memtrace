/* <memtrace.h> */
/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef _MEMTRACE_H
#define _MEMTRACE_H
#if _MEMTRACE + 0

#include <_memtrace.h>
#include <stdlib.h>

#define malloc(size)        (memtrace_internal_malloc  (size,         __FILE__, __LINE__))
#define free(ptr)           (memtrace_internal_free    (ptr,          __FILE__, __LINE__))
#define calloc(nmemb, size) (memtrace_internal_calloc  (nmemb, size,  __FILE__, __LINE__))
#define realloc(ptr, size)  (memtrace_internal_realloc (ptr,  size,   __FILE__, __LINE__))

#endif /* _MEMTRACE */
#endif /* _MEMTRACE_H */
