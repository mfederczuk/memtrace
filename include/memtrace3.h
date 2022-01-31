/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE3_H
#define MEMTRACE3_H

#include <_memtrace3_internal_core.h>

#if !(MEMTRACE3_CONFIG_IGNORE_NDEBUG + 0) && defined(NDEBUG)
	MEMTRACE3_INTERNAL_ISSUE_WARNING("NDEBUG is defined and memtrace3.h is included.")
#endif

#include <stdio.h>
#include <stdlib.h>
#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup + 0) || (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup + 0)
	#include <string.h>
#endif

#if !(MEMTRACE3_CONFIG_ALLOW_REDEFINE + 0)
	#ifdef malloc
		#error malloc already defined
	#endif
	#ifdef free
		#error free already defined
	#endif
	#ifdef calloc
		#error calloc already defined
	#endif
	#ifdef realloc
		#error realloc already defined
	#endif


	#ifdef fopen
		#error fopen already defined
	#endif
	#ifdef freopen
		#error freopen already defined
	#endif
	#ifdef fclose
		#error fclose already defined
	#endif


	#if MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup && defined(strdup)
		#error strdup already defined
	#endif
	#if MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup && defined(strndup)
		#error strndup already defined
	#endif
#endif


#undef  malloc
#define malloc(size)        (memtrace3_internal_malloc  ((size),          __FILE__, __LINE__))

#undef  calloc
#define calloc(nmemb, size) (memtrace3_internal_calloc  ((nmemb), (size), __FILE__, __LINE__))

#undef  realloc
#define realloc(ptr, size)  (memtrace3_internal_realloc ((ptr),   (size), __FILE__, __LINE__))

#undef  free
#define free(ptr)           (memtrace3_internal_free    ((ptr),           __FILE__, __LINE__))


#undef  fopen
#define fopen(pathname, mode)           (memtrace3_internal_fopen   ((pathname), (mode),           __FILE__, __LINE__))

#undef  freopen
#define freopen(pathname, mode, stream) (memtrace3_internal_freopen ((pathname), (mode), (stream), __FILE__, __LINE__))

#undef  fclose
#define fclose(stream)                  (memtrace3_internal_fclose  ((stream),                     __FILE__, __LINE__))


#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup + 0)
	#undef  strdup
	#define strdup(s)     (memtrace3_internal_strdup  ((s),      __FILE__, __LINE__))
#endif

#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup + 0)
	#undef  strndup
	#define strndup(s, n) (memtrace3_internal_strndup ((s), (n), __FILE__, __LINE__))
#endif


#endif /* MEMTRACE3_H */
