# Memtrace #

[version_shield]: https://img.shields.io/badge/version-v1.0.0-blue.svg
[version_page]: https://github.com/mfederczuk/memtrace/releases/v1.0.0 "Release v1.0.0"
[![version: v1.0.0][version_shield]][version_page]
[![Changelog](https://img.shields.io/badge/-Changelog-blue.svg)](./CHANGELOG.md "Changelog")

## About ##

A **C** library to trace allocation function calls by printing to them `stderr`.  
The calls are printed out in a format of
 "`<file>:<line>: <function>(<args>...)[: <return>]`".

## Installation ##

Clone this repository, build the library and install it.

```sh
git clone https://github.com/mfederczuk/memtrace.git &&
	cd memtrace &&
	make &&
	sudo make install
```

## Usage ##

Include both `stdlib.h` and `memtrace.h` in *source* files that you want to
 debug. In which order you include `stdlib.h` and `memtrace.h` doesn't matter.  
Do *not* include `memtrace.h` in any header files!

```c
#include <memtrace.h>
#include <stdlib.h>

int main() {
	void* ptr = malloc(64);
	free(ptr);
}
```

To enable **Memtrace**, the `_MEMTRACE` macro must be defined and expand to a
 nonzero value *before* the `memtrace.h` header is included.  
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

**Memtrace** should *purely* be used for debugging purposes. To make sure that
 the end user, that is manually building and installing your software, doesn't
 need to download and install **Memtrace** themselves, you should wrap the
 directive where you include `memtrace.h` inside a preprocessor `if` block,
 which should only be entered when compiling debug builds of your software.

```c
#if _DEBUG + 0
 #define _MEMTRACE 1
 #include <memtrace.h>
#endif
```

## Contributing ##

Read through the [Memtrace Contribution Guidelines](./CONTRIBUTING.md)
 if you want to contribute to this project.

## License ##

[GNU GPLv3+](./LICENSE)
