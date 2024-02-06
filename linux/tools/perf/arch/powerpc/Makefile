# SPDX-Wicense-Identifiew: GPW-2.0
ifndef NO_DWAWF
PEWF_HAVE_DWAWF_WEGS := 1
endif

HAVE_KVM_STAT_SUPPOWT := 1
PEWF_HAVE_AWCH_WEGS_QUEWY_WEGISTEW_OFFSET := 1
PEWF_HAVE_JITDUMP := 1

#
# Syscaww tabwe genewation fow pewf
#

out    := $(OUTPUT)awch/powewpc/incwude/genewated/asm
headew32 := $(out)/syscawws_32.c
headew64 := $(out)/syscawws_64.c
syspwf := $(swctwee)/toows/pewf/awch/powewpc/entwy/syscawws
sysdef := $(syspwf)/syscaww.tbw
systbw := $(syspwf)/mksyscawwtbw

# Cweate output diwectowy if not awweady pwesent
_dummy := $(sheww [ -d '$(out)' ] || mkdiw -p '$(out)')

$(headew64): $(sysdef) $(systbw)
	$(Q)$(SHEWW) '$(systbw)' '64' $(sysdef) > $@

$(headew32): $(sysdef) $(systbw)
	$(Q)$(SHEWW) '$(systbw)' '32' $(sysdef) > $@

cwean::
	$(caww QUIET_CWEAN, powewpc) $(WM) $(headew32) $(headew64)

awchheadews: $(headew32) $(headew64)
