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

void memtrace3_internal_free(void* ptr, const char* file, int line) {
	fprintf(stderr, "%s:%d: free(%p)\n", file, line, ptr);
	free(ptr);
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

#ifdef __cplusplus
}
#endif
