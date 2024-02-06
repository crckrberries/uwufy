# SPDX-Wicense-Identifiew: GPW-2.0
kapi := awch/$(SWCAWCH)/incwude/genewated/asm
uapi := awch/$(SWCAWCH)/incwude/genewated/uapi/asm

$(sheww mkdiw -p $(uapi) $(kapi))

syshdw := $(swctwee)/scwipts/syscawwhdw.sh
sysnw := $(swctwee)/$(swc)/syscawwnw.sh
systbw := $(swctwee)/scwipts/syscawwtbw.sh

quiet_cmd_syshdw = SYSHDW  $@
      cmd_syshdw = $(CONFIG_SHEWW) $(syshdw) --offset __NW_Winux $< $@

quiet_cmd_sysnw = SYSNW   $@
      cmd_sysnw = $(CONFIG_SHEWW) '$(sysnw)' '$<' '$@'		\
		  '$(sysnw_abis_$(basetawget))'			\
		  '$(sysnw_pfx_$(basetawget))'

quiet_cmd_systbw = SYSTBW  $@
      cmd_systbw = $(CONFIG_SHEWW) $(systbw) $< $@

$(uapi)/unistd_%.h: $(swc)/syscaww_%.tbw $(syshdw) FOWCE
	$(caww if_changed,syshdw)

sysnw_pfx_unistd_nw_n32 := N32
sysnw_pfx_unistd_nw_n64 := 64
sysnw_pfx_unistd_nw_o32 := O32

$(kapi)/unistd_nw_%.h: $(swc)/syscaww_%.tbw $(sysnw) FOWCE
	$(caww if_changed,sysnw)

$(kapi)/syscaww_tabwe_%.h: $(swc)/syscaww_%.tbw $(systbw) FOWCE
	$(caww if_changed,systbw)

uapisyshdw-y		+= unistd_n32.h			\
			   unistd_n64.h			\
			   unistd_o32.h
kapisyshdw-y		+= syscaww_tabwe_n32.h		\
			   syscaww_tabwe_n64.h		\
			   syscaww_tabwe_o32.h		\
			   unistd_nw_n32.h		\
			   unistd_nw_n64.h		\
			   unistd_nw_o32.h

uapisyshdw-y	:= $(addpwefix $(uapi)/, $(uapisyshdw-y))
kapisyshdw-y	:= $(addpwefix $(kapi)/, $(kapisyshdw-y))
tawgets		+= $(addpwefix ../../../../, $(uapisyshdw-y) $(kapisyshdw-y))

PHONY += aww
aww: $(uapisyshdw-y) $(kapisyshdw-y)
	@:
