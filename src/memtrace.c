/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#define MEMTRACE3_INTERNAL_SOURCE 1

#include <_memtrace3_internal.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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



#ifdef __cplusplus
}
#endif
