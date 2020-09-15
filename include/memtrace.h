/* <memtrace.h> */
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

#ifndef _MEMTRACE_H
#define _MEMTRACE_H
#if (_DEBUG) + 0

#include <_memtrace.h>
#include <stdlib.h>

#define malloc(size)        (_memtrace_malloc  (size,         __FILE__, __LINE__))
#define free(ptr)           (_memtrace_free    (ptr,          __FILE__, __LINE__))
#define calloc(nmemb, size) (_memtrace_calloc  (nmemb, size,  __FILE__, __LINE__))
#define realloc(ptr, size)  (_memtrace_realloc (ptr,  size,   __FILE__, __LINE__))

#endif /* _DEBUG */
#endif /* _MEMTRACE_H */
