/*
 * Library to trace allocation function calls.
 * Copyright (C) 2020  Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define _MEMTRACE_SOURCE 1

#include <_memtrace.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void* _memtrace_malloc(size_t size, const char* file, int line) {
	void* ret_ptr = malloc(size);
	printf("%s:%d: malloc(%zd): %p\n", file, line, size, ret_ptr);
	return ret_ptr;
}

void _memtrace_free(void* ptr, const char* file, int line) {
	free(ptr);
	printf("%s:%d: free(%p)\n", file, line, ptr);
}

void* _memtrace_calloc(size_t nmemb, size_t size, const char* file, int line) {
	void* ret_ptr = calloc(nmemb, size);
	printf("%s:%d: calloc(%zd, %zd): %p\n", file, line, nmemb, size, ret_ptr);
	return ret_ptr;
}

void* _memtrace_realloc(void* ptr, size_t size, const char* file, int line) {
	void* ret_ptr = realloc(ptr, size);
	printf("%s:%d: realloc(%p, %zd): %p\n", file, line, ptr, size, ret_ptr);
	return ret_ptr;
}
