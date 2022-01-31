<!--
  Copyright (c) 2022 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Memtrace #

[![version: 3.0.0][release_shield]][release_page]
[![Changelog][changelog_shield]](CHANGELOG.md "Changelog") &nbsp;
[![Documentation][documentation_shield]](Documentation/README.md)

[release_shield]: https://img.shields.io/badge/version-3.0.0-informational.svg
[release_page]: https://github.com/mfederczuk/memtrace/releases/tag/v3.0.0 "Release v3.0.0"
[changelog_shield]: https://img.shields.io/badge/-Changelog-informational.svg
[documentation_shield]: https://img.shields.io/badge/-Documentation-informational.svg

## About ##

> Library to trace allocation function calls.

**Memtrace** is a **C** library to trace allocation function calls by printing them to `stderr`.  
The calls are printed out in the format of "`<source_file>:<line>: <function_name>(<args>...)[: <return_value>]`".

## Usage ##

Include `memtrace3.h` in *source* files that you want to debug.  
It is not recommended to include `memtrace3.h` in any header files.

```c
#include <memtrace3.h>
#include <stdlib.h>

int main() {
	void* ptr = malloc(64);
	free(ptr);
}
```

The target binary must be linked with the `memtrace3` library.

```sh
cc main.c -lmemtrace3
```

Possible output:

```console
main.c:5: malloc(64): 0x47c2a0
main.c:6: free(0x47c2a0)
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

For more information visit the [extensive documentation](Documentation/README.md).

## Download & Installation ##

Download the source code (by cloning the repository), build the library and install it.

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
