/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef MEMTRACE3_INTERNAL_SUPPORT_H
#define MEMTRACE3_INTERNAL_SUPPORT_H

#if !defined(MEMTRACE3_H) && !defined(MEMTRACE3_INTERNAL_CORE_H)
	#error Do not include _memtrace3_internal_support.h directly, include memtrace3.h instead.
#endif

// this is a very convoluted way to check for strdup and/or strndup support



// first checking for official C23 suport
#if __STDC_VERSION__ >= 202300L // TODO i couldn't find the official value of __STDC_VERSION__ in C23 (there might not
                                //      be one yet) but it obviously must be at least 202300.
                                //      once there is an official value, this should be replaced
	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup  1
	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup 1
#endif



// checking for Unix-like systems
#ifdef __has_include
	#if __has_include(<unistd.h>)
		#include <unistd.h>
		#define MEMTRACE3_INTERNAL_NO_UNISTD_H 0
	#else
		#define MEMTRACE3_INTERNAL_NO_UNISTD_H 1
	#endif
#endif
// only checking MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup & MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup here because
// this here should the only place where we are not certain that an include may or may not fail - checking the macros
// before may reduce errors on some systems
#if !(MEMTRACE3_INTERNAL_NO_UNISTD_H + 0) && \
    (!(MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup + 0) || !(MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup + 0)) && \
    (defined(__unix__) || defined(__unix) || defined(unix) || \
     (defined(__APPLE__) && defined(__MACH__)))

	// this may fail - there is no reliable way to test for POSIX systems
	#include <unistd.h>
#endif

// required POSIX standards taken from the strdup(3) Linux 5.13 Programmer's Manual page

// checking for POSIX.1-2001 support
#if (_POSIX_VERSION + 0) >= 200112L
	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup 1
#endif

// checking for POSIX.1-2008 support
#if (_POSIX_VERSION + 0) >= 200809L
	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup 1
#endif



// checking glib support

#ifdef __has_include
	#if __has_include(<features.h>)
		#include <features.h>
	#endif
#endif

#include <limits.h> // hopefully this includes glib features.h or we included it from somwhere else at this point

// feature test macros taken from the strdup(3) Linux 5.13 Programmer's Manual page

// strdup
#if _XOPEN_SOURCE >= 500
	// in this case we actually included features.h and limits.h for nothing

	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup 1
#elif ((((__GLIBC__       + 0) == 2 && (__GLIBC_MINOR__       + 0) >= 12) || \
        ((__GNU_LIBRARY__ + 0) == 2 && (__GNU_LIBRARY_MINOR__ + 0) >= 12)) && \
       (_POSIX_C_SOURCE + 0) >= 200809L) || \
      ((((__GLIBC__       + 0) == 2 && (__GLIBC_MINOR__       + 0) <= 19) || \
        ((__GNU_LIBRARY__ + 0) == 2 && (__GNU_LIBRARY_MINOR__ + 0) <= 19)) && \
       defined(_BSD_SOURCE) || defined(_SVID_SOURCE))

	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup 1
#endif

// strndup
#if (((__GLIBC__       + 0) == 2 && (__GLIBC_MINOR__       + 0) >= 10) || \
     ((__GNU_LIBRARY__ + 0) == 2 && (__GNU_LIBRARY_MINOR__ + 0) >= 10)) && \
    (_POSIX_C_SOURCE + 0) >= 200809L

	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup 1
#elif (((__GLIBC__       + 0) == 2 && (__GLIBC_MINOR__       + 0) < 10) || \
       ((__GNU_LIBRARY__ + 0) == 2 && (__GNU_LIBRARY_MINOR__ + 0) < 10)) && \
      defined(_GNU_SOURCE)

	#define MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup 1
#endif



#endif /* MEMTRACE3_INTERNAL_SUPPORT_H */
