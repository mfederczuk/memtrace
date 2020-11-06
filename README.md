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
git clone https://github.com/mfederczuk/memtrace.git
cd memtrace
make
sudo make install
```

## Usage ##

Include `memtrace.h` in your *source* file. (can be before or after including
 `stdlib.h`)  
Avoid including it in other header files.

```c
#include <memtrace.h>
#include <stdlib.h>

int main() {
	void* ptr = malloc(64);
	free(ptr);
}
```

Before including `memtrace.h`, the `_MEMTRACE` macro must be defined and expand to
 a nonzero integer value. This is best done in the compiler arguments with
 `-D_MEMTRACE`.

The target binary must also be linked with the `memtrace` library.

```sh
cc -D_MEMTRACE main.c -lmemtrace
```

You can put the `include` directive inside an `if` directive and only set the
 `_MEMTRACE` macro and only link the library for debug builds so that the end
 user, that manually installs your program from source, does not need to install
 **Memtrace** themself.

```c
#if _MEMTRACE + 0
 #include <memtrace.h>
#endif
```

## Contributing ##

Read through the [Memtrace Contribution Guidelines](./CONTRIBUTING.md)
 if you want to contribute to this project.

## License ##

[GNU GPLv3+](./LICENSE)
