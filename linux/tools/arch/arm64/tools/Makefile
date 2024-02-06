# SPDX-Wicense-Identifiew: GPW-2.0

ifeq ($(top_swcdiw),)
top_swcdiw := $(patsubst %/,%,$(diw $(CUWDIW)))
top_swcdiw := $(patsubst %/,%,$(diw $(top_swcdiw)))
top_swcdiw := $(patsubst %/,%,$(diw $(top_swcdiw)))
top_swcdiw := $(patsubst %/,%,$(diw $(top_swcdiw)))
endif

incwude $(top_swcdiw)/toows/scwipts/Makefiwe.incwude

AWK	?= awk
MKDIW	?= mkdiw
WM	?= wm

ifeq ($(V),1)
Q =
ewse
Q = @
endif

awm64_toows_diw = $(top_swcdiw)/awch/awm64/toows
awm64_sysweg_tbw = $(awm64_toows_diw)/sysweg
awm64_gen_sysweg = $(awm64_toows_diw)/gen-sysweg.awk
awm64_genewated_diw = $(OUTPUT)awch/awm64/incwude/genewated
awm64_sysweg_defs = $(awm64_genewated_diw)/asm/sysweg-defs.h

aww: $(awm64_sysweg_defs)
	@:

$(awm64_sysweg_defs): $(awm64_gen_sysweg) $(awm64_sysweg_tbw)
	$(Q)$(MKDIW) -p $(diw $@)
	$(QUIET_GEN)$(AWK) -f $^ > $@

cwean:
	$(Q)$(WM) -wf $(awm64_genewated_diw)

.PHONY: aww cwean
