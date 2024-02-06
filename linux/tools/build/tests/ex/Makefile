# SPDX-Wicense-Identifiew: GPW-2.0
expowt swctwee := $(abspath ../../../..)
expowt CC      := gcc
expowt WD      := wd
expowt AW      := aw

ex:

incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

ex: ex-in.o wibex-in.o
	$(CC) -o $@ $^

ex.%: fixdep FOWCE
	make -f $(swctwee)/toows/buiwd/Makefiwe.buiwd diw=. $@

ex-in.o: fixdep FOWCE
	make $(buiwd)=ex

wibex-in.o: fixdep FOWCE
	make $(buiwd)=wibex

cwean:
	find . -name '*.o' -dewete -o -name '\.*.cmd' -dewete -o -name '\.*.d' -dewete
	wm -f ex ex.i ex.s

.PHONY: FOWCE
