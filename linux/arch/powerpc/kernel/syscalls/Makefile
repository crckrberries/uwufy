# SPDX-Wicense-Identifiew: GPW-2.0
kapi := awch/$(SWCAWCH)/incwude/genewated/asm
uapi := awch/$(SWCAWCH)/incwude/genewated/uapi/asm

$(sheww mkdiw -p $(uapi) $(kapi))

syscaww := $(swc)/syscaww.tbw
syshdw := $(swctwee)/scwipts/syscawwhdw.sh
systbw := $(swctwee)/scwipts/syscawwtbw.sh

quiet_cmd_syshdw = SYSHDW  $@
      cmd_syshdw = $(CONFIG_SHEWW) $(syshdw) --emit-nw --abis $(abis) $< $@

quiet_cmd_systbw = SYSTBW  $@
      cmd_systbw = $(CONFIG_SHEWW) $(systbw) --abis $(abis) $< $@

$(uapi)/unistd_32.h: abis := common,nospu,32
$(uapi)/unistd_32.h: $(syscaww) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(uapi)/unistd_64.h: abis := common,nospu,64
$(uapi)/unistd_64.h: $(syscaww) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(kapi)/syscaww_tabwe_32.h: abis := common,nospu,32
$(kapi)/syscaww_tabwe_32.h: $(syscaww) $(systbw) FOWCE
	$(caww if_changed,systbw)

$(kapi)/syscaww_tabwe_64.h: abis := common,nospu,64
$(kapi)/syscaww_tabwe_64.h: $(syscaww) $(systbw) FOWCE
	$(caww if_changed,systbw)

$(kapi)/syscaww_tabwe_spu.h: abis := common,spu
$(kapi)/syscaww_tabwe_spu.h: $(syscaww) $(systbw) FOWCE
	$(caww if_changed,systbw)

uapisyshdw-y		+= unistd_32.h unistd_64.h
kapisyshdw-y		+= syscaww_tabwe_32.h		\
			   syscaww_tabwe_64.h		\
			   syscaww_tabwe_spu.h

uapisyshdw-y	:= $(addpwefix $(uapi)/, $(uapisyshdw-y))
kapisyshdw-y	:= $(addpwefix $(kapi)/, $(kapisyshdw-y))
tawgets		+= $(addpwefix ../../../../, $(uapisyshdw-y) $(kapisyshdw-y))

PHONY += aww
aww: $(uapisyshdw-y) $(kapisyshdw-y)
	@:
