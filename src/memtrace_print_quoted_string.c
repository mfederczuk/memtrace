/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <stddef.h>
#include <stdio.h>

#undef  array_size
#define array_size(array) (sizeof(array) / sizeof(*array))

#undef thread_safe_static
#if __STDC_VERSION__ >= 201112L // C11
	#include <threads.h> // contains `thread_local` macro
	#define thread_safe_static thread_local static
#else
	#define thread_safe_static
#endif

#ifdef __cplusplus
extern "C" {
#endif

static void memtrace_print_quoted_string(const char* str);

static void memtrace_print_quoted_string_with_address(const char* str) {
	if(str == NULL) {
		fprintf(stderr, "%p", NULL);
		return;
	}

	fprintf(stderr, "%p (", (const void*)str);
	memtrace_print_quoted_string(str);
	fputc(')', stderr);
}

/**
 * Prints the string str surrounded with quotation marks *without* doing any dynamic memory allocations on the heap.
 */
static void memtrace_print_quoted_string(const char* str) {
	if(str == NULL) {
		fprintf(stderr, "%p", NULL);
		return;
	}

	if(*str == '\0') {
		fputs("\"\"", stderr);
		return;
	}

	thread_safe_static char buffer[128];
	buffer[0] = '"';

	size_t buffer_size = 1;

	const char* it = str;

	do {
		switch(*it) {
			case('"'): {
				buffer[buffer_size + 0] = '\\';
				buffer[buffer_size + 1] = '"';
				buffer_size += 2;
				break;
			}
			case('\\'): {
				buffer[buffer_size + 0] = '\\';
				buffer[buffer_size + 1] = '\\';
				buffer_size += 2;
				break;
			}
			default: {
				buffer[buffer_size] = *it;
				++buffer_size;
				break;
			}
		}

		if((buffer_size + 2) > array_size(buffer)) {
			fwrite(buffer, sizeof(*buffer), buffer_size, stderr);
			buffer_size = 0;
		}

		++it;
	} while(*it != '\0');

	buffer[buffer_size] = '"';
	++buffer_size;

	fwrite(buffer, sizeof(*buffer), buffer_size, stderr);
}

#ifdef __cplusplus
}
#endif
