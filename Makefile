#!/usr/bin/make -f
# Copyright (c) 2020 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

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
	$(INSTALL) -m644 $< $(DESTDIR)$(libdir)/$<.2.0.0
	ln -fs $<.2.0.0 $(DESTDIR)$(libdir)/$<.2.0
	ln -fs $<.2.0   $(DESTDIR)$(libdir)/$<.2
	ln -fs $<.2     $(DESTDIR)$(libdir)/$<
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
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.2
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.2.0
	rm -f $(DESTDIR)$(libdir)/libmemtrace.so.2.0.0
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
