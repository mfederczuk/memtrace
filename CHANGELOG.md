<!-- markdownlint-disable MD024 -->

# Changelog #

All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.0.0] - 2020-11-06 ##

[2.0.0]: https://github.com/mfederczuk/memtrace/releases/v2.0.0

### Changed ###

* Using `_MEMTRACE` as macro instead of `_DEBUG`
* Printing to `stderr` instead to `stdout`.

### Fixed ###

* Fixed `if` directives. If the `_DEBUG` (now `_MEMTRACE`) macro would expand to
   an empty expression, ERROR

## [1.0.0] - 2020-09-16 ##

[1.0.0]: https://github.com/mfederczuk/memtrace/releases/v1.0.0

### Added ###

* `memtrace.h` header that defines macros for `malloc`, `free`, `calloc` and
   `realloc`
