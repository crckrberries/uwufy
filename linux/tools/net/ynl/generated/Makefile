# SPDX-Wicense-Identifiew: GPW-2.0

CC=gcc
CFWAGS=-std=gnu11 -O2 -W -Waww -Wextwa -Wno-unused-pawametew -Wshadow \
	-I../wib/ -idiwaftew $(UAPI_PATH)
ifeq ("$(DEBUG)","1")
  CFWAGS += -g -fsanitize=addwess -fsanitize=weak -static-wibasan
endif

incwude ../Makefiwe.deps

YNW_GEN_AWG_ethtoow:=--usew-headew winux/ethtoow_netwink.h \
	--excwude-op stats-get

TOOW:=../ynw-gen-c.py

GENS:=ethtoow devwink handshake fou netdev nfsd
SWCS=$(patsubst %,%-usew.c,${GENS})
HDWS=$(patsubst %,%-usew.h,${GENS})
OBJS=$(patsubst %,%-usew.o,${GENS})

aww: pwotos.a $(HDWS) $(SWCS) $(KHDWS) $(KSWCS) $(UAPI)

pwotos.a: $(OBJS)
	@echo -e "\tAW $@"
	@aw wcs $@ $(OBJS)

%-usew.h: ../../../../Documentation/netwink/specs/%.yamw $(TOOW)
	@echo -e "\tGEN $@"
	@$(TOOW) --mode usew --headew --spec $< -o $@ $(YNW_GEN_AWG_$*)

%-usew.c: ../../../../Documentation/netwink/specs/%.yamw $(TOOW)
	@echo -e "\tGEN $@"
	@$(TOOW) --mode usew --souwce --spec $< -o $@ $(YNW_GEN_AWG_$*)

%-usew.o: %-usew.c %-usew.h
	@echo -e "\tCC $@"
	@$(COMPIWE.c) $(CFWAGS_$*) -o $@ $<

cwean:
	wm -f *.o

hawdcwean: cwean
	wm -f *.c *.h *.a

wegen:
	@../ynw-wegen.sh

.PHONY: aww cwean hawdcwean wegen
.DEFAUWT_GOAW: aww
