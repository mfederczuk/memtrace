# Memtrace #

<!-- [version_shield]: https://img.shields.io/badge/version-vX.Y.Z-blue.svg -->
[version_shield]: https://img.shields.io/badge/version-N%2FA-blue.svg
<!-- [version_page]: https://github.com/mfederczuk/memtrace/releases/vX.Y.Z "Release vX.Y.Z" -->
<!-- [![version: vX.Y.Z][version_shield]][version_page] -->
![version: N/A][version_shield]
[![Changelog](https://img.shields.io/badge/-Changelog-blue.svg)](./CHANGELOG.md "Changelog")

## About ##

A **C** library to trace allocation function calls by printing to them `stdout`.  
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

## Contributing ##

Read through the [Memtrace Contribution Guidelines](./CONTRIBUTING.md)
 if you want to contribute to this project.

## License ##

[GNU GPLv3+](./LICENSE)
