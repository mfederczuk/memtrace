#!/usr/bin/make -f
# Copyright (c) 2022 Michael Federczuk
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


ifneq "$(STDC)" ""
 override STDC := -std=$(STDC)
endif

CFLAGS = $(STDC) $(c99_compat) \
         -Wall -Wextra -Wconversion \
         -pedantic -Wpedantic -pedantic-errors -Werror=pedantic


override memtrace_major_version := 3
override memtrace_minor_version := 0
override memtrace_patch_version := 0

override memtrace_major_minor_version := $(memtrace_major_version).$(memtrace_minor_version)
override memtrace_version := $(memtrace_major_minor_version).$(memtrace_patch_version)


all: libmemtrace.so
.PHONY: all

obj/memtrace.c.so: src/memtrace.c src/memtrace_print_quoted_string.c
	mkdir -p -- $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Iinclude -fPIC -c $< -o $@

libmemtrace.so: obj/memtrace.c.so
	$(CC) $(LDFLAGS) $(CFLAGS) -shared $^ -o $@

install: libmemtrace.so memtrace.7.gz
	$(INSTALL) -m644 -DT -- $< $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_version)$(suffix $<)

	ln -fs -- $(basename $<)$(memtrace_version)$(suffix $<)             $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_major_minor_version)$(suffix $<)
	ln -fs -- $(basename $<)$(memtrace_major_minor_version)$(suffix $<) $(DESTDIR)$(libdir)/$(basename $<)$(memtrace_major_version)$(suffix $<)

	mkdir -p -- $(DESTDIR)$(includedir)
	$(INSTALL) -m644 -Dt $(DESTDIR)$(includedir) -- include/_memtrace$(memtrace_major_version)_internal_support.h \
	                                                include/_memtrace$(memtrace_major_version)_internal_core.h \
	                                                include/memtrace$(memtrace_major_version).h
.PHONY: install

uninstall:
	rm -fv -- $(DESTDIR)$(includedir)/memtrace$(memtrace_major_version).h \
	          $(DESTDIR)$(includedir)/_memtrace$(memtrace_major_version)_internal_core.h \
	          $(DESTDIR)$(includedir)/_memtrace$(memtrace_major_version)_internal_support.h \
	          $(DESTDIR)$(libdir)/libmemtrace$(memtrace_major_version).so \
	          $(DESTDIR)$(libdir)/libmemtrace$(memtrace_major_minor_version).so \
	          $(DESTDIR)$(libdir)/libmemtrace$(memtrace_version).so
.PHONY: uninstall

clean:
	rm -fv libmemtrace.so obj/memtrace.c.so
.PHONY: clean
