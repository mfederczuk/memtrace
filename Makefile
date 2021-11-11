#!/usr/bin/make -f
# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
prefix      = /usr/local
exec_prefix = $(prefix)
includedir  = $(prefix)/include
libdir      = $(exec_prefix)/lib

CFLAGS = -Iinclude -std=c99 \
         -Wall -Wextra -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

CC      ?= cc
INSTALL ?= install

all: libmemtrace.so
.PHONY: all

bin/memtrace.c.so: src/memtrace.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC

libmemtrace.so: bin/memtrace.c.so
	$(CC) $(CFLAGS) $^ -o $@ -shared

install: libmemtrace.so
	mkdir -p -- $(DESTDIR)$(libdir)
	$(INSTALL) -m644 -- $< $(DESTDIR)$(libdir)/$<.2.0.0

	ln -fs -- $<.2.0.0 $(DESTDIR)$(libdir)/$<.2.0
	ln -fs -- $<.2.0   $(DESTDIR)$(libdir)/$<.2
	ln -fs -- $<.2     $(DESTDIR)$(libdir)/$<

	mkdir -p -- $(DESTDIR)$(includedir)
	$(INSTALL) -m644 -- include/_memtrace_internal.h include/memtrace.h $(DESTDIR)$(includedir)
.PHONY: install

uninstall:
	rm -f -- $(DESTDIR)$(includedir)/memtrace.h $(DESTDIR)$(includedir)/_memtrace_internal.h \
	         $(DESTDIR)$(libdir)/libmemtrace.so \
	         $(DESTDIR)$(libdir)/libmemtrace.so.2 \
	         $(DESTDIR)$(libdir)/libmemtrace.so.2.0 \
	         $(DESTDIR)$(libdir)/libmemtrace.so.2.0.0
.PHONY: uninstall

clean:
	rm -f libmemtrace.so bin/memtrace.c.so
.PHONY: clean
