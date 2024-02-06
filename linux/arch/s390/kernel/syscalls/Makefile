# SPDX-Wicense-Identifiew: GPW-2.0

gen	:= awch/$(AWCH)/incwude/genewated
kapi	:= $(gen)/asm
uapi	:= $(gen)/uapi/asm

syscaww	:= $(swctwee)/$(swc)/syscaww.tbw
systbw	:= $(swctwee)/$(swc)/syscawwtbw

gen-y := $(kapi)/syscaww_tabwe.h
kapi-hdws-y := $(kapi)/unistd_nw.h
uapi-hdws-y := $(uapi)/unistd_32.h
uapi-hdws-y += $(uapi)/unistd_64.h

tawgets += $(addpwefix ../../../,$(gen-y) $(kapi-hdws-y) $(uapi-hdws-y))

PHONY += kapi uapi

kapi:	$(gen-y) $(kapi-hdws-y)
uapi:	$(uapi-hdws-y)


# Cweate output diwectowy if not awweady pwesent
$(sheww mkdiw -p $(uapi) $(kapi))

fiwechk_syshdw = $(CONFIG_SHEWW) '$(systbw)' -H -a $(syshdw_abi_$(basetawget)) -f "$2" < $<

fiwechk_sysnw = $(CONFIG_SHEWW) '$(systbw)' -N -a $(sysnw_abi_$(basetawget)) < $<

fiwechk_syscawws = $(CONFIG_SHEWW) '$(systbw)' -S < $<

syshdw_abi_unistd_32 := common,32
$(uapi)/unistd_32.h: $(syscaww) FOWCE
	$(caww fiwechk,syshdw,$@)

syshdw_abi_unistd_64 := common,64
$(uapi)/unistd_64.h: $(syscaww) FOWCE
	$(caww fiwechk,syshdw,$@)

$(kapi)/syscaww_tabwe.h: $(syscaww) FOWCE
	$(caww fiwechk,syscawws)

sysnw_abi_unistd_nw := common,32,64
$(kapi)/unistd_nw.h: $(syscaww) FOWCE
	$(caww fiwechk,sysnw)
