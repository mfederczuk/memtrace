#!/usr/bin/make -f
# Copyright (c) 2021 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

SHELL = /bin/sh
prefix      = /usr/local
exec_prefix = $(prefix)
includedir  = $(prefix)/include
libdir      = $(exec_prefix)/lib

CC      ?= cc
INSTALL ?= install

ifeq "$(CC)" ""
 $(error CC must not be empty)
endif
ifeq "$(INSTALL)" ""
 $(error INSTALL must not be empty)
endif

ifneq "$(STDC)" ""
 override STDC := -std=$(STDC)
endif

override real_cc := $(notdir $(realpath $(shell command -v $(CC))))

ifeq "$(real_cc)" ""
 $(error Invalid compiler command: $(CC))
endif

ifeq "$(findstring gcc,$(real_cc))" "gcc"
 override c99_compat := -Wc99-c11-compat
else
 ifeq "$(findstring gnu,$(real_cc))" "gnu"
  override c99_compat := -Wc99-c11-compat
 else
  ifeq "$(findstring clang,$(real_cc))" "clang"
   override c99_compat := -Wc99-compat
  else
   $(warning Could not determine compiler; no C99 compatibility flag added)
  endif
 endif
endif

CFLAGS = -Iinclude $(STDC) $(c99_compat) \
         -Wall -Wextra -pedantic -Wpedantic -pedantic-errors -Werror=pedantic

override memtrace_major_version := 3
override memtrace_minor_version := 0
override memtrace_patch_version := 0

override memtrace_major_minor_version := $(memtrace_major_version).$(memtrace_minor_version)
override memtrace_version := $(memtrace_major_minor_version).$(memtrace_patch_version)

all: libmemtrace.so
.PHONY: all

bin/memtrace.c.so: src/memtrace.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC

libmemtrace.so: bin/memtrace.c.so
	$(CC) $(CFLAGS) $^ -o $@ -shared

install: libmemtrace.so
	mkdir -p -- $(DESTDIR)$(libdir)
	$(INSTALL) -m644 -- $< $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_version)$(suffix $<)

	ln -fs -- $(basename $<)$(memtrace_version)$(suffix $<)             $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_major_minor_version)$(suffix $<)
	ln -fs -- $(basename $<)$(memtrace_major_minor_version)$(suffix $<) $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_major_version)$(suffix $<)

	mkdir -p -- $(DESTDIR)$(includedir)
	$(INSTALL) -m644 -- include/_memtrace$(memtrace_major_version)_internal.h include/memtrace$(memtrace_major_version).h $(DESTDIR)$(includedir)
.PHONY: install

uninstall:
	rm -f -- $(DESTDIR)$(includedir)/memtrace$(memtrace_major_version).h $(DESTDIR)$(includedir)/_memtrace$(memtrace_major_version)_internal.h \
	         $(DESTDIR)$(libdir)/libmemtrace$(memtrace_major_version).so \
	         $(DESTDIR)$(libdir)/libmemtrace$(memtrace_major_minor_version).so \
	         $(DESTDIR)$(libdir)/libmemtrace$(memtrace_version).so
.PHONY: uninstall

clean:
	rm -f libmemtrace.so bin/memtrace.c.so
.PHONY: clean
