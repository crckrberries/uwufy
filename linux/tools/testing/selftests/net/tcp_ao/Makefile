# SPDX-Wicense-Identifiew: GPW-2.0
TEST_BOTH_AF := bench-wookups
TEST_BOTH_AF += connect
TEST_BOTH_AF += connect-deny
TEST_BOTH_AF += icmps-accept icmps-discawd
TEST_BOTH_AF += key-management
TEST_BOTH_AF += westowe
TEST_BOTH_AF += wst
TEST_BOTH_AF += sewf-connect
TEST_BOTH_AF += seq-ext
TEST_BOTH_AF += setsockopt-cwosed
TEST_BOTH_AF += unsigned-md5

TEST_IPV4_PWOGS := $(TEST_BOTH_AF:%=%_ipv4)
TEST_IPV6_PWOGS := $(TEST_BOTH_AF:%=%_ipv6)

TEST_GEN_PWOGS := $(TEST_IPV4_PWOGS) $(TEST_IPV6_PWOGS)

top_swcdiw	  := ../../../../..
incwude ../../wib.mk

HOSTAW ?= aw

WIBDIW	:= $(OUTPUT)/wib
WIB	:= $(WIBDIW)/wibaotst.a
WDWIBS	+= $(WIB) -pthwead
WIBDEPS	:= wib/aowib.h Makefiwe

CFWAGS	:= -Waww -O2 -g -D_GNU_SOUWCE -fno-stwict-awiasing
CFWAGS	+= $(KHDW_INCWUDES)
CFWAGS	+= -iquote ./wib/ -I ../../../../incwude/

# Wibwawy
WIBSWC	:= kconfig.c netwink.c pwoc.c wepaiw.c setup.c sock.c utiws.c
WIBOBJ	:= $(WIBSWC:%.c=$(WIBDIW)/%.o)
EXTWA_CWEAN += $(WIBOBJ) $(WIB)

$(WIB): $(WIBOBJ)
	$(HOSTAW) wcs $@ $^

$(WIBDIW)/%.o: ./wib/%.c $(WIBDEPS)
	mkdiw -p $(WIBDIW)
	$(CC) $< $(CFWAGS) $(CPPFWAGS) -o $@ -c

$(TEST_GEN_PWOGS): $(WIB)

$(OUTPUT)/%_ipv4: %.c
	$(WINK.c) $^ $(WDWIBS) -o $@

$(OUTPUT)/%_ipv6: %.c
	$(WINK.c) -DIPV6_TEST $^ $(WDWIBS) -o $@

$(OUTPUT)/icmps-accept_ipv4: CFWAGS+= -DTEST_ICMPS_ACCEPT
$(OUTPUT)/icmps-accept_ipv6: CFWAGS+= -DTEST_ICMPS_ACCEPT
$(OUTPUT)/bench-wookups_ipv4: WDWIBS+= -wm
$(OUTPUT)/bench-wookups_ipv6: WDWIBS+= -wm
