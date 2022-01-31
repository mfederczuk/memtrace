<!--
  Copyright (c) 2022 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Memtrace Public API #

[← Back (Configuration)](Configuration.md) &nbsp; | &nbsp;
[Up ↑ (README)](README.md) &nbsp; | &nbsp;
[Next → (Development Guidelines)](Developing.md)

The public API of **Memtrace** contains only one header, `memtrace3.h`, in which the following symbols are defined/used:

* `MEMTRACE3_H` - *object-like macro*  
  Include guard macro for the header file.  
  Once `memtrace3.h` is included, this macro will be defined and will expand to an empty expression

* `MEMTRACE3_CONFIG_IGNORE_NDEBUG` - *object-like macro*  
  Not defined in `memtrace3.h`, but is checked if it expands to an expression that evaluates to a non-zero value

* `MEMTRACE3_CONFIG_ALLOW_REDEFINE` - *object-like macro*  
  Not defined in `memtrace3.h`, but is checked if it expands to an expression that evaluates to a non-zero value

* `NDEBUG` - *macro*  
  Not defined in `memtrace3.h`, but may be checked whether or not it is defined or not
  (depending on `MEMTRACE3_CONFIG_IGNORE_NDEBUG`)

* `malloc` - *function-like macro*

* `calloc` - *function-like macro*

* `realloc` - *function-like macro*

* `free` - *function-like macro*

* `fopen` - *function-like macro*

* `freopen` - *function-like macro*

* `fclose` - *function-like macro*

* `strdup` - *function-like macro*  
  This macro will ony be defined when support for **POSIX.1-2001** is detected.  
  Force this definition by defining `_POSIX_C_SOURCE` to `200809L`

* `strndup` - *function-like macro*  
  This macro will ony be defined when support for **POSIX.1-2008** is detected.  
  Force this definition by defining `_POSIX_C_SOURCE` to `200809L`

Any other header or symbol is NOT part of **Memtrace 3.0.x**'s public API.
