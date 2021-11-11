/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#define MEMTRACE_INTERNAL_SOURCE 1

#include <_memtrace_internal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memtrace_internal_malloc(size_t size, const char* file, int line) {
	void* ret_ptr = malloc(size);
	fprintf(stderr, "%s:%d: malloc(%zu): %p\n", file, line, size, ret_ptr);
	return ret_ptr;
}

void memtrace_internal_free(void* ptr, const char* file, int line) {
	free(ptr);
	fprintf(stderr, "%s:%d: free(%p)\n", file, line, ptr);
}

void* memtrace_internal_calloc(size_t nmemb, size_t size, const char* file, int line) {
	void* ret_ptr = calloc(nmemb, size);
	fprintf(stderr, "%s:%d: calloc(%zu, %zu): %p\n", file, line, nmemb, size, ret_ptr);
	return ret_ptr;
}

void* memtrace_internal_realloc(void* ptr, size_t size, const char* file, int line) {
	void* ret_ptr = realloc(ptr, size);
	fprintf(stderr, "%s:%d: realloc(%p, %zu): %p\n", file, line, ptr, size, ret_ptr);
	return ret_ptr;
}

#ifdef __cplusplus
}
#endif
