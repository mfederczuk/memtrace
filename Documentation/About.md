<!--
  Copyright (c) 2022 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# About Memtrace #

[← Back (README)](README.md) &nbsp; | &nbsp;
[Up ↑ (README)](README.md) &nbsp; | &nbsp;
[Next → (Building & Installing)](Building.md)

**Memtrace** is a debugging library for **C** to trace calls of functions that do resource allocations.  
When certain functions are called, the source file location, function name, parameters and the return value are all
printed to the standard error stream - "tracing" the function that was called.  
The functions that are "traced" are listed in the next section.

The earliest **C** standard that is supported is **C99**.  
**C11** and **C17**/**C18** also supported.

## Selected Functions ##

The following standard functions are traced:

* `malloc(3)`
* `realloc(3)`
* `calloc(3)`
* `free(3)`
* `fopen(3)`
* `freopen(3)`
* `fclose(3)`
* `strdup(3)`
* `strndup(3)`

_Note: Both `strdup` and `strndup` are not standard **C** functions, see section
[Non **C**-Standard Functions](#non-c-standard-functions) for more information._

## Printed Format ##

For functions that return `void`, (e.g.: `free(3)`) the message printed is formatted in the following way:

```console
<source_file>:<line_number>: <function_name>(<parameter_values>)
```

And for functions that return a non-`void` value: (e.g.: `malloc(3)`, `fopen(3)`, ...)

```console
<source_file>:<line_number>: <function_name>(<parameter_values>): <return_value>
```

Example:

```console
main.c:6: malloc(32): 0x4a60040
main.c:7: fopen("file.txt", "r"): 0x4a600a0
main.c:9: fclose(0x4a600a0): 0
main.c:10: free(0x4a60040)
```

## How it works ##

The library is implemented using macros.  
For each of the selected functions, a function-like macro with the same name and number of parameters of the selected
function is defined.  
This macro expands to a call of an internally declared function, which calls the actual, originally selected function,
but also prints the information passed along.

```c
// header files

void* memtrace3_internal_malloc(size_t size, char* file, int line);

#define malloc(size) memtrace3_internal_malloc(size, __FILE__, __LINE__)
```

```c
// source files

void* memtrace3_internal_malloc(size_t size, char* file, int line) {
	void* ptr = malloc(size);
	fprintf(stderr, "%s:%d: malloc(%zu): %p\n", file, line, size, ptr);
	return ptr;
}
```

## Non **C**-Standard Functions ##

**Memtrace** also supports function that are not ([yet][P2391R0]) included in the **C** standard.  
Currently, the only such functions are `strdup(3)` and `strndup(3)`, which are part of **POSIX.1-2001** and
**POSIX.1-2008**, respectively.  
Whether or not a target system supports these functions is automatically detected. In case the library is built without
either support, a compiler warning/message is issued.

[P2391R0]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2391r0.pdf "C23 Update Report"
