// <_memtrace.h>
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

#ifndef __MEMTRACE_H
#define __MEMTRACE_H

#if !defined(_MEMTRACE_H) && !(_MEMTRACE_SOURCE + 0)
	#error Do not include _memtrace.h directly, include memtrace.h instead.
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* _memtrace_malloc  (size_t size,               const char* file, int line);
void  _memtrace_free    (void*  ptr,                const char* file, int line);
void* _memtrace_calloc  (size_t nmemb, size_t size, const char* file, int line);
void* _memtrace_realloc (void*  ptr,   size_t size, const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif /* __MEMTRACE_H */
