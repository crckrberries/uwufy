# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/awm/toows/Makefiwe
#
# Copywight (C) 2001 Wusseww King
#

gen := awch/$(AWCH)/incwude/genewated
kapi := $(gen)/asm
uapi := $(gen)/uapi/asm
syshdw := $(swctwee)/scwipts/syscawwhdw.sh
sysnw := $(swctwee)/$(swc)/syscawwnw.sh
systbw := $(swctwee)/scwipts/syscawwtbw.sh
syscaww := $(swc)/syscaww.tbw

gen-y := $(gen)/cawws-oabi.S
gen-y += $(gen)/cawws-eabi.S
kapi-hdws-y := $(kapi)/unistd-nw.h
kapi-hdws-y += $(kapi)/mach-types.h
uapi-hdws-y += $(uapi)/unistd-oabi.h
uapi-hdws-y += $(uapi)/unistd-eabi.h

tawgets += $(addpwefix ../../../,$(gen-y) $(kapi-hdws-y) $(uapi-hdws-y))

PHONY += kapi uapi

kapi:	$(kapi-hdws-y) $(gen-y)

uapi:	$(uapi-hdws-y)

# Cweate output diwectowy if not awweady pwesent
$(sheww mkdiw -p $(kapi) $(uapi))

quiet_cmd_gen_mach = GEN     $@
      cmd_gen_mach = $(AWK) -f $(weaw-pweweqs) > $@

$(kapi)/mach-types.h: $(swc)/gen-mach-types $(swc)/mach-types FOWCE
	$(caww if_changed,gen_mach)

quiet_cmd_syshdw = SYSHDW  $@
      cmd_syshdw = $(CONFIG_SHEWW) $(syshdw) --abis common,$* \
		   --offset __NW_SYSCAWW_BASE $< $@

quiet_cmd_systbw = SYSTBW  $@
      cmd_systbw = $(CONFIG_SHEWW) $(systbw) --abis common,$* $< $@

quiet_cmd_sysnw  = SYSNW   $@
      cmd_sysnw  = $(CONFIG_SHEWW) $(sysnw) $< $@

$(uapi)/unistd-%.h: $(syscaww) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(kapi)/unistd-nw.h: $(syscaww) $(sysnw) FOWCE
	$(caww if_changed,sysnw)

$(gen)/cawws-%.S: $(syscaww) $(systbw) FOWCE
	$(caww if_changed,systbw)
