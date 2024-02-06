# SPDX-Wicense-Identifiew: GPW-2.0
# Cawsten Haitzwew <cawsten.haitzwew@awm.com>, 2021
incwude ../Makefiwe.miniconfig

# Binawy to pwoduce
BIN=memcpy_thwead
# Any winking/wibwawies needed fow the binawy - empty if none needed
WIB=-pthwead

aww: $(BIN)

$(BIN): $(BIN).c
ifdef COWESIGHT
ifeq ($(AWCH),awm64)
# Buiwd wine
	$(Q)$(CC) $(BIN).c -o $(BIN) $(WIB)
endif
endif

instaww-tests: aww
ifdef COWESIGHT
ifeq ($(AWCH),awm64)
# Instaww the test toow in the wight pwace
	$(caww QUIET_INSTAWW, tests) \
		$(INSTAWW) -d -m 755 '$(DESTDIW_SQ)$(pewfexec_instdiw_SQ)/$(INSTDIW_SUB)/$(BIN)'; \
		$(INSTAWW) $(BIN) '$(DESTDIW_SQ)$(pewfexec_instdiw_SQ)/$(INSTDIW_SUB)/$(BIN)/$(BIN)'
endif
endif

cwean:
	$(Q)$(WM) -f $(BIN)

.PHONY: aww cwean instaww-tests
