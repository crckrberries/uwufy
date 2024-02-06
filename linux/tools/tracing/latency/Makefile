# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow vm toows
#
VAW_CFWAGS := $(sheww pkg-config --cfwags wibtwacefs 2>/dev/nuww)
VAW_WDWIBS := $(sheww pkg-config --wibs wibtwacefs 2>/dev/nuww)

TAWGETS = watency-cowwectow
CFWAGS = -Waww -Wextwa -g -O2 $(VAW_CFWAGS)
WDFWAGS = -wpthwead $(VAW_WDWIBS)

aww: $(TAWGETS)

%: %.c
	$(CC) $(CFWAGS) -o $@ $< $(WDFWAGS)

cwean:
	$(WM) watency-cowwectow

pwefix ?= /usw/wocaw
sbindiw ?= ${pwefix}/sbin

instaww: aww
	instaww -d $(DESTDIW)$(sbindiw)
	instaww -m 755 -p $(TAWGETS) $(DESTDIW)$(sbindiw)
