<!--
  Copyright (c) 2021 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

<!-- markdownlint-disable no-duplicate-heading -->

# Changelog #

All notable changes to this project will be documented in this file.
The format is based on [**Keep a Changelog v1.0.0**](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [**Semantic Versioning v2.0.0**](https://semver.org/spec/v2.0.0.html).

## Unreleased ##

### Removed ###

* The `_MEMTRACE` macro is not queried anymore; **Memtrace** is now always enabled when including `memtrace.h`

## [v2.0.0] - 2020-11-06 ##

[v2.0.0]: https://github.com/mfederczuk/memtrace/releases/v2.0.0

### Changed ###

* Using `_MEMTRACE` as macro instead of `_DEBUG`
* Printing to `stderr` instead to `stdout`

### Fixed ###

* Fixed internal `if` directives.
  If the `_DEBUG` (now `_MEMTRACE`) macro would expand to an empty expression, it would lead to a compiler error

## [v1.0.0] - 2020-09-16 ##

[v1.0.0]: https://github.com/mfederczuk/memtrace/releases/v1.0.0

Initial Release

### Added ###

* `memtrace.h` header that defines macros for `malloc`, `free`, `calloc` and `realloc`
