#!/usr/bin/make -f
# Library to trace allocation function calls.
# Copyright (C) 2020  Michael Federczuk
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

SHELL = /bin/sh
prefix      = /usr/local
exec_prefix = $(prefix)
includedir  = $(prefix)/include
libdir      = $(exec_prefix)/lib

CFLAGS = -Iinclude -std=c99 -Wall -Wextra -pedantic -pedantic-errors

CC      ?= cc
INSTALL ?= install

all: libmemtrace.so
.PHONY: all

object: bin/memtrace.c.so
bin/memtrace.c.so: src/memtrace.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -fPIC
.PHONY: object

library: libmemtrace.so
libmemtrace.so: bin/memtrace.c.so
	$(CC) $(CFLAGS) $^ -o $@ -shared
.PHONY: library

install: install/headers install/library
install/headers: include/_memtrace.h include/memtrace.h
	mkdir -p $(DESTDIR)$(includedir)
	$(INSTALL) -m644 $^ $(DESTDIR)$(includedir)
install/library: install/libmemtrace.so
install/libmemtrace.so: libmemtrace.so
	mkdir -p $(DESTDIR)$(libdir)
	$(INSTALL) -m644 $< $(DESTDIR)$(libdir)/$<.1.0.0
	ln -s $<.1.0.0 $(DESTDIR)$(libdir)/$<.1.0
	ln -s $<.1.0   $(DESTDIR)$(libdir)/$<.1
	ln -s $<.1     $(DESTDIR)$(libdir)/$<
.PHONY: install \
        install/headers \
        install/library \
        install/libmemtrace.so

uninstall: uninstall/headers uninstall/library
uninstall/headers:
	rm -f $(DESTDIR)$(includedir)/_memtrace.h $(DESTDIR)$(includedir)/memtrace.h
uninstall/library: uninstall/libmemtrace.so
uninstall/libmemtrace.so:
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.1
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.1.0
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.1.0.0
.PHONY: uninstall \
        uninstall/headers \
        uninstall/library \
        uninstall/libmemtrace.so

clean: clean/object clean/library
clean/object: clean/bin/memtrace.c.so
clean/library: clean/libmemtrace.so
clean/bin/memtrace.c.so clean/libmemtrace.so: %:
	rm -f $(@:clean/%=%)
.PHONY: clean \
        clean/object \
        clean/library \
        clean/bin/memtrace.c.so clean/libmemtrace.so
