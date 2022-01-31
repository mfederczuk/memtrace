<!--
  Copyright (c) 2022 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Building & Installing Memtrace #

[← Back (About)](About.md) &nbsp; | &nbsp;
[Up ↑ (README)](README.md) &nbsp; | &nbsp;
[Next → (Configuration)](Configuration.md)

**Memtrace** uses **GNU Make** (*not* **POSIX Make** compliant) as its build system - a [`Makefile`](../Makefile) is
provided.

By default, the system **C** compiler will be used. (the `cc` command)  
This can be customized by setting the `CC` environment variable to the compiler command of your choosing when invoking
`make`.

The Makefile also supports the [`DESTDIR`] environment variable when installing or uninstalling.

By default, no **C** standard and no optimization level is explicitly selected.  
Both of those can be explicitly changed by setting the `STDC` and `O` environment variables.  
When they are not empty, the value of these variables will be prefixed with `-std=` and `-O` respectively, and then will
be given to the compiler.

The following Makefile rules are defined:

* `all` (default)  
  Alias for `libmemtrace.so`

* `obj/memtrace.c.so`  
  Builds the shared object

* `libmemtrace.so` (prerequisite: `obj/memtrace.c.so`)  
  Builds the shared library

* `install` (prerequisite: `libmemtrace.so`)  
  _Note: For the sake of brevity, `DESTDIR` is not mentioned here, rest assured that it still works._

  Installs the shared library and the headers into `/usr/local/lib` and `/usr/local/include`, respectively.  
  Any directories that do not exist will be created.

  The shared library file is installed as `libmemtrace<MAJOR>.<MINOR>.<PATCH>.so`.  
  Where _MAJOR_, _MINOR_ and _PATCH_ are the current major, minor and patch version numbers of **Memtrace** that is
  being installed.

  The following symlinks will be created as well: (also in `/usr/local/lib`)

  * `libmemtrace<MAJOR>.<MINOR>.so` → `libmemtrace<MAJOR>.<MINOR>.<PATCH>.so`

  * `libmemtrace<MAJOR>.so` → `libmemtrace<MAJOR>.<MINOR>.so`

  In the end, the file tree of newly installed files will look like this:

  ```tree
  /
  └── usr/
      └── local/
          ├── include/
          │   ├── memtrace<MAJOR>.h
          │   ├── _memtrace<MAJOR>_internal_core.h
          │   └── _memtrace<MAJOR>_internal_support.h
          └── lib/
              ├── libmemtrace<MAJOR>.<MINOR>.<PATCH>.so
              ├── libmemtrace<MAJOR>.<MINOR>.so -> libmemtrace<MAJOR>.<MINOR>.<PATCH>.so
              └── libmemtrace<MAJOR>.so -> libmemtrace<MAJOR>.<MINOR>.so
  ```
  <!-- graph courtesy of tree(1) -->

* `uninstall`  
  Removes all files and symlinks that were created by the `install` rule, but *not* the directories.
  (not even when they would be empty after deleting the files and symlinks)

* `clean`  
  Removes `libmemtrace.so` and `obj/memtrace.c.so`

Since the library is (by default) installed in `/usr/local/lib`, this path may need to be added to the `LD_LIBRARY_PATH`
environment variable to execute binaries that have been linked with the library.

[`DESTDIR`]: https://www.gnu.org/software/make/manual/html_node/DESTDIR.html
