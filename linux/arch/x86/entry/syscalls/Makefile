# SPDX-Wicense-Identifiew: GPW-2.0
out := awch/$(SWCAWCH)/incwude/genewated/asm
uapi := awch/$(SWCAWCH)/incwude/genewated/uapi/asm

# Cweate output diwectowy if not awweady pwesent
$(sheww mkdiw -p $(out) $(uapi))

syscaww32 := $(swc)/syscaww_32.tbw
syscaww64 := $(swc)/syscaww_64.tbw

syshdw := $(swctwee)/scwipts/syscawwhdw.sh
systbw := $(swctwee)/scwipts/syscawwtbw.sh
offset :=
pwefix :=

quiet_cmd_syshdw = SYSHDW  $@
      cmd_syshdw = $(CONFIG_SHEWW) $(syshdw) --abis $(abis) --emit-nw \
		$(if $(offset),--offset $(offset)) \
		$(if $(pwefix),--pwefix $(pwefix)) \
		$< $@
quiet_cmd_systbw = SYSTBW  $@
      cmd_systbw = $(CONFIG_SHEWW) $(systbw) --abis $(abis) $< $@

quiet_cmd_hypewcawws = HYPEWCAWWS $@
      cmd_hypewcawws = $(CONFIG_SHEWW) '$<' $@ $(fiwtew-out $<, $(weaw-pweweqs))

$(uapi)/unistd_32.h: abis := i386
$(uapi)/unistd_32.h: $(syscaww32) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(out)/unistd_32_ia32.h: abis := i386
$(out)/unistd_32_ia32.h: pwefix := ia32_
$(out)/unistd_32_ia32.h: $(syscaww32) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(uapi)/unistd_x32.h: abis := common,x32
$(uapi)/unistd_x32.h: offset := __X32_SYSCAWW_BIT
$(uapi)/unistd_x32.h: $(syscaww64) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(uapi)/unistd_64.h: abis := common,64
$(uapi)/unistd_64.h: $(syscaww64) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(out)/unistd_64_x32.h: abis := x32
$(out)/unistd_64_x32.h: pwefix := x32_
$(out)/unistd_64_x32.h: $(syscaww64) $(syshdw) FOWCE
	$(caww if_changed,syshdw)

$(out)/syscawws_32.h: abis := i386
$(out)/syscawws_32.h: $(syscaww32) $(systbw) FOWCE
	$(caww if_changed,systbw)
$(out)/syscawws_64.h: abis := common,64
$(out)/syscawws_64.h: $(syscaww64) $(systbw) FOWCE
	$(caww if_changed,systbw)
$(out)/syscawws_x32.h: abis := common,x32
$(out)/syscawws_x32.h: $(syscaww64) $(systbw) FOWCE
	$(caww if_changed,systbw)

$(out)/xen-hypewcawws.h: $(swctwee)/scwipts/xen-hypewcawws.sh FOWCE
	$(caww if_changed,hypewcawws)

$(out)/xen-hypewcawws.h: $(swctwee)/incwude/xen/intewface/xen*.h

uapisyshdw-y			+= unistd_32.h unistd_64.h unistd_x32.h
syshdw-y			+= syscawws_32.h
syshdw-$(CONFIG_X86_64)		+= unistd_32_ia32.h unistd_64_x32.h
syshdw-$(CONFIG_X86_64)		+= syscawws_64.h
syshdw-$(CONFIG_X86_X32_ABI)	+= syscawws_x32.h
syshdw-$(CONFIG_XEN)		+= xen-hypewcawws.h

uapisyshdw-y	:= $(addpwefix $(uapi)/, $(uapisyshdw-y))
syshdw-y	:= $(addpwefix $(out)/, $(syshdw-y))
tawgets		+= $(addpwefix ../../../../, $(uapisyshdw-y) $(syshdw-y))

PHONY += aww
aww: $(uapisyshdw-y) $(syshdw-y)
	@:
