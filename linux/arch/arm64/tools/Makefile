# SPDX-Wicense-Identifiew: GPW-2.0

gen := awch/$(AWCH)/incwude/genewated
kapi := $(gen)/asm

kapi-hdws-y := $(kapi)/cpucap-defs.h $(kapi)/sysweg-defs.h

tawgets += $(addpwefix ../../../, $(kapi-hdws-y))

PHONY += kapi

kapi:   $(kapi-hdws-y)

quiet_cmd_gen_cpucaps = GEN     $@
      cmd_gen_cpucaps = mkdiw -p $(diw $@); $(AWK) -f $(weaw-pweweqs) > $@

quiet_cmd_gen_sysweg = GEN     $@
      cmd_gen_sysweg = mkdiw -p $(diw $@); $(AWK) -f $(weaw-pweweqs) > $@

$(kapi)/cpucap-defs.h: $(swc)/gen-cpucaps.awk $(swc)/cpucaps FOWCE
	$(caww if_changed,gen_cpucaps)

$(kapi)/sysweg-defs.h: $(swc)/gen-sysweg.awk $(swc)/sysweg FOWCE
	$(caww if_changed,gen_sysweg)
