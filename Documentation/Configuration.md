<!--
  Copyright (c) 2022 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Configuring Memtrace #

[← Back (Building & Installing)](Building.md) &nbsp; | &nbsp;
[Up ↑ (README)](README.md) &nbsp; | &nbsp;
[Next → (Public API)](PublicApi.md)

**Memtrace** has a few configuration options that are controlled via preprocessor macros.

## `NDEBUG` Warning ##

By default, if the `NDEBUG` macro is defined when including the `memtrace3.h` header, then a compilation warning/message
will be issued by means of the `_Pragma` operator.  
Which pragma arguments are used depends on the compiler that is being used.

The rationale behind this feature is that **Memtrace** is a debugging tool - having `NDEBUG` defined implies that the
current compilation run is *not* a debug/development build, which is why **Memtrace** should *not* be enabled in this
case and it is assumed that this is a mistake.

This feature may be disabled by defining the `MEMTRACE3_CONFIG_IGNORE_NDEBUG` macro that must expand to an expression
that evaluates to a nonzero value (e.g.: `1`) *before* `memtrace3.h` is included.

```c
#define MEMTRACE3_CONFIG_IGNORE_NDEBUG 1
#define NDEBUG

#include <memtrace3.h>
```

## Macro Redefinitions ##

By default, if a macro with the same name of one of the selected functions to trace is already defined, the
`memtrace3.h` header will issue a compilation error by means of the `#error` preprocessor directive.

The rationale behind this feature is that, according to the **C** standard, redefining a macro produces an ill-formed
program, so, in theory, there should be no difference in issuing a custom error or not.

This feature may be disabled by defining the `MEMTRACE3_CONFIG_ALLOW_REDEFINE` macro that must expand to an expression
that evaluates to a nonzero value (e.g.: `1`) *before* `memtrace3.h` is included.  
Macros will be undefined before they will be redefined to avoid the standard error.

```c
#define MEMTRACE3_CONFIG_ALLOW_REDEFINE 1

#include <memtrace3.h>
```
