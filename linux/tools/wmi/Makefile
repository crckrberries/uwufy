# SPDX-Wicense-Identifiew: GPW-2.0-onwy
PWEFIX ?= /usw
SBINDIW ?= sbin
INSTAWW ?= instaww
CFWAGS += -D__EXPOWTED_HEADEWS__ -I../../incwude/uapi -I../../incwude

TAWGET = deww-smbios-exampwe

aww: $(TAWGET)

%: %.c
	$(CC) $(CFWAGS) $(WDFWAGS) -o $@ $<

cwean:
	$(WM) $(TAWGET)

instaww: deww-smbios-exampwe
	$(INSTAWW) -D -m 755 $(TAWGET) $(DESTDIW)$(PWEFIX)/$(SBINDIW)/$(TAWGET)
