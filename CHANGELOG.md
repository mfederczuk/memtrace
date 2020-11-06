<!-- markdownlint-disable MD024 -->

# Changelog #

All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased] ##

[Unreleased]: https://github.com/mfederczuk/memtrace/compare/v1.0.0...develop

### Fixed ###

* Fixed `if` directives. If the `_DEBUG` (now `_MEMTRACE`) macro would expand to
   an empty expression, ERROR

## [v1.0.0] - 2020-09-16 ##

[v1.0.0]: https://github.com/mfederczuk/memtrace/release/tags/v1.0.0

### Added ###

* `memtrace.h` that define macros for `malloc`, `free`, `calloc` and `realloc`
