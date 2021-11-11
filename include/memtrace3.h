/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE3_H
#define MEMTRACE3_H

#if !(MEMTRACE3_CONFIG_IGNORE_NDEBUG + 0) && defined(NDEBUG)
	#warning NDEBUG is defined and memtrace3.h is included.
#endif

#include <_memtrace3_internal.h>
#include <stdlib.h>

#define malloc(size)        (memtrace3_internal_malloc  (size,         __FILE__, __LINE__))
#define free(ptr)           (memtrace3_internal_free    (ptr,          __FILE__, __LINE__))
#define calloc(nmemb, size) (memtrace3_internal_calloc  (nmemb, size,  __FILE__, __LINE__))
#define realloc(ptr, size)  (memtrace3_internal_realloc (ptr,  size,   __FILE__, __LINE__))

#endif /* MEMTRACE3_H */
