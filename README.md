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

Include both `stdlib.h` and `memtrace.h` in *source* files that you want to debug.
In which order you include `stdlib.h` and `memtrace.h` doesn't matter.  
Do *not* include `memtrace.h` in any header files!

```c
#include <memtrace.h>
#include <stdlib.h>

int main() {
	void* ptr = malloc(64);
	free(ptr);
}
```

To enable **Memtrace**, the `_MEMTRACE` macro must be defined and expand to a nonzero value *before* the `memtrace.h`
header is included.  
To do this, you can pass the option `-D_MEMTRACE` to your compiler.

The target binary must also be linked with the `memtrace` library.

```sh
cc -D_MEMTRACE main.c -lmemtrace
```

For quick debugging, it is also possible to define the macro in the source code.

```c
#define _MEMTRACE 1

#include <memtrace.h>
#include <stdlib.h>
```

**Memtrace** should *purely* be used for debugging purposes.
To make sure that the end user, that is manually building and installing your software, doesn't need to download and
install **Memtrace** themselves, you should wrap the directive where you include `memtrace.h` inside a preprocessor `if`
block, which should only be entered when compiling debug builds of your software.

```c
#ifndef NDEBUG
 #define _MEMTRACE 1
 #include <memtrace.h>
#endif
```

## Download & Installation ##

Clone this repository, build the library and install it.

```sh
git clone https://github.com/mfederczuk/memtrace.git &&
	cd memtrace &&
	make &&
	sudo make install
```

## Contributing ##

Read through the [Contribution Guidelines](CONTRIBUTING.md) if you want to contribute to this project.

## License ##

**Memtrace** is licensed under [**GNU GPL v3.0**](licenses/GNU-GPL-v3.0.txt) or later.  
For more information about copying and licensing, see the [COPYING.txt](COPYING.txt) file.
