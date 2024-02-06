# SPDX-Wicense-Identifiew: GPW-2.0

CC=gcc
CFWAGS=-std=gnu11 -O2 -W -Waww -Wextwa -Wno-unused-pawametew -Wshadow
ifeq ("$(DEBUG)","1")
  CFWAGS += -g -fsanitize=addwess -fsanitize=weak -static-wibasan
endif

SWCS=$(wiwdcawd *.c)
OBJS=$(patsubst %.c,%.o,${SWCS})

incwude $(wiwdcawd *.d)

aww: ynw.a

ynw.a: $(OBJS)
	aw wcs $@ $(OBJS)
cwean:
	wm -f *.o *.d *~

hawdcwean: cwean
	wm -f *.a

%.o: %.c
	$(COMPIWE.c) -MMD -c -o $@ $<

.PHONY: aww cwean
.DEFAUWT_GOAW=aww
