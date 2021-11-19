/*
 * Copyright (c) 2022 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#define MEMTRACE3_INTERNAL_SOURCE 1

#define _POSIX_C_SOURCE 200809L // request exposing of >= POSIX.1-2008 functions
                                // if the system doesn't support it, we'll issue warnings further down

#include <_memtrace3_internal_core.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup + 0) || (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup + 0)
	#include <string.h>
#endif

#include "memtrace_print_quoted_string.c"

#ifdef __cplusplus
extern "C" {
#endif



void* memtrace3_internal_malloc(size_t size, const char* file, int line) {
	fprintf(stderr, "%s:%d: malloc(%zu)", file, line, size);

	void* const ret_ptr = malloc(size);
	const int local_errno = errno;

	fprintf(stderr, ": %p\n", ret_ptr);

	errno = local_errno;
	return ret_ptr;
}

void* memtrace3_internal_calloc(size_t nmemb, size_t size, const char* file, int line) {
	fprintf(stderr, "%s:%d: calloc(%zu, %zu)", file, line, nmemb, size);

	void* const ret_ptr = calloc(nmemb, size);
	const int local_errno = errno;

	fprintf(stderr, ": %p\n", ret_ptr);

	errno = local_errno;
	return ret_ptr;
}

void* memtrace3_internal_realloc(void* ptr, size_t size, const char* file, int line) {
	fprintf(stderr, "%s:%d: realloc(%p, %zu)", file, line, ptr, size);

	void* const ret_ptr = realloc(ptr, size);
	const int local_errno = errno;

	fprintf(stderr, ": %p\n", ret_ptr);

	errno = local_errno;
	return ret_ptr;
}

void memtrace3_internal_free(void* ptr, const char* file, int line) {
	fprintf(stderr, "%s:%d: free(%p)\n", file, line, ptr);
	free(ptr);
}



FILE* memtrace3_internal_fopen(const char* pathname, char const* mode, const char* file, int line) {
	fprintf(stderr, "%s:%d: fopen(", file, line);
	memtrace_print_quoted_string(pathname);
	fputs(", ", stderr);
	memtrace_print_quoted_string(mode);
	fputc(')', stderr);

	FILE* const stream = fopen(pathname, mode);
	const int local_errno = errno;

	fprintf(stderr, ": %p\n", (void*)stream);

	errno = local_errno;
	return stream;
}

FILE* memtrace3_internal_freopen(const char* pathname, char const* mode, FILE* stream, const char* file, int line) {
	fprintf(stderr, "%s:%d: freopen(", file, line);
	memtrace_print_quoted_string(pathname);
	fputs(", ", stderr);
	memtrace_print_quoted_string(mode);
	fprintf(stderr, ", %p)", (void*)stream);

	FILE* const new_stream = freopen(pathname, mode, stream);
	const int local_errno = errno;

	fprintf(stderr, ": %p\n", (void*)new_stream);

	errno = local_errno;
	return stream;
}

int memtrace3_internal_fclose(FILE* stream, const char* file, int line) {
	fprintf(stderr, "%s:%d: fclose(%p)", file, line, (void*)stream);

	const int ret_stat = fclose(stream);
	const int local_errno = errno;

	fprintf(stderr, ": %d\n", ret_stat);

	errno = local_errno;
	return ret_stat;
}



#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strdup + 0)
	char* memtrace3_internal_strdup(const char* s, const char* file, int line) {
		fprintf(stderr, "%s:%d: strdup(", file, line);
		memtrace_print_quoted_string(s);
		fputc(')', stderr);

		char* const dup = strdup(s);
		const int local_errno = errno;

		fputs(": ", stderr);
		memtrace_print_quoted_string_with_address(dup);
		fputc('\n', stderr);

		errno = local_errno;
		return dup;
	}
#else
	MEMTRACE3_INTERNAL_ISSUE_WARNING("Compiling without strdup support!")
#endif

#if (MEMTRACE3_INTERNAL_FUNCTION_SUPPORT_strndup + 0)
	char* memtrace3_internal_strndup(const char* s, size_t n, const char* file, int line) {
		fprintf(stderr, "%s:%d: strndup(", file, line);
		memtrace_print_quoted_string(s);
		fprintf(stderr, ", %zu)", n);

		char* const dup = strndup(s, n);
		const int local_errno = errno;

		fputs(": ", stderr);
		memtrace_print_quoted_string_with_address(dup);
		fputc('\n', stderr);

		errno = local_errno;
		return dup;
	}
#else
	MEMTRACE3_INTERNAL_ISSUE_WARNING("Compiling without strndup support!")
#endif



#ifdef __cplusplus
}
#endif
