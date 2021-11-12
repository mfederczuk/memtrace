<!--
  Copyright (c) 2021 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Memtrace #

[version_shield]: https://img.shields.io/badge/version-v2.0.0-informational.svg
[release_page]: https://github.com/mfederczuk/memtrace/releases/tag/v2.0.0 "Release v2.0.0"
[![version: v2.0.0][version_shield]][release_page]
[![Changelog](https://img.shields.io/badge/-Changelog-informational.svg)](CHANGELOG.md "Changelog")

## About ##

> Library to trace allocation function calls.

**Memtrace** is a **C** library to trace allocation function calls by printing them to `stderr`.  
The calls are printed out in the format of "`<source_file>:<line>: <function_name>(<args>...)[: <return_value>]`".

## Usage ##

Include both `stdlib.h` and `memtrace3.h` in *source* files that you want to debug.
In which order you include `stdlib.h` and `memtrace3.h` doesn't matter.  
Do *not* include `memtrace3.h` in any header files!

```c
#include <memtrace3.h>
#include <stdlib.h>

int main() {
	void* ptr = malloc(64);
	free(ptr);
}
```

The target binary must also be linked with the `memtrace3` library.

```sh
cc main.c -lmemtrace3
```

Major and minor versions can also be specified when linking.

```sh
cc main.c -lmemtrace3.0
cc main.c -lmemtrace3.0.0
```

**Memtrace** should *purely* be used for debugging purposes.
To make sure that the end user, that is manually building and installing your software, doesn't need to download and
install **Memtrace** themselves, you should wrap the directive where you include `memtrace3.h` inside a preprocessor `if`
block, which should only be entered when compiling debug builds of your software.

```c
#ifndef NDEBUG
 #include <memtrace3.h>
#endif
```

When the `NDEBUG` macro is defined and `memtrace3.h` is included, a warning will be given.  
This warning may be disabled by defining the `MEMTRACE3_CONFIG_IGNORE_NDEBUG` macro as an expression that evaluates to a
nonzero value.

By default, when a macro with the same name of an allocation function is defined, including `memtrace3.h` will issue an
error.  
Defining the `MEMTRACE3_CONFIG_ALLOW_REDEFINE` macro as an expression that evaluates to a nonzero value will first
undefine the macros.

### Example ###

#### `main.c` ####

```c
#include <memtrace3.h>
#include <stdlib.h>

int main() {
	int *v = malloc(sizeof(int) * 64);

	v = realloc(v, sizeof(int) * 128);

	free(v);

	v = calloc(32, sizeof(int));

	free(v);
}
```

#### Possible Output ####

```txt
$ cc main.c -lmemtrace3 && ./a.out
main.c:7: malloc(256): 0x561d520912a0
main.c:9: realloc(0x561d520912a0, 512): 0x561d520912a0
main.c:11: free(0x561d520912a0)
main.c:13: calloc(32, 4): 0x561d520914b0
main.c:15: free(0x561d520914b0)
```

## Download & Installation ##

Clone this repository, build the library and install it.

```sh
git clone -b v3.0.0 -o memtrace3 https://github.com/mfederczuk/memtrace.git &&
	cd memtrace3 &&
	make &&
	sudo make install
```

## Contributing ##

Read through the [Contribution Guidelines](CONTRIBUTING.md) if you want to contribute to this project.

## License ##

**Memtrace** is licensed under both the [**Mozilla Public License 2.0**](LICENSES/MPL-2.0.txt) AND the
[**Apache License 2.0**](LICENSES/Apache-2.0.txt).  
For more information about copying and licensing, see the [`COPYING.txt`](COPYING.txt) file.
