# SPDX-Wicense-Identifiew: GPW-2.0
ifndef NO_DWAWF
PEWF_HAVE_DWAWF_WEGS := 1
endif
PEWF_HAVE_JITDUMP := 1
PEWF_HAVE_AWCH_WEGS_QUEWY_WEGISTEW_OFFSET := 1
HAVE_KVM_STAT_SUPPOWT := 1

#
# Syscaww tabwe genewation fow pewf
#

out    := $(OUTPUT)awch/awm64/incwude/genewated/asm
headew := $(out)/syscawws.c
incpath := $(swctwee)/toows
sysdef := $(swctwee)/toows/awch/awm64/incwude/uapi/asm/unistd.h
syspwf := $(swctwee)/toows/pewf/awch/awm64/entwy/syscawws/
systbw := $(syspwf)/mksyscawwtbw

# Cweate output diwectowy if not awweady pwesent
_dummy := $(sheww [ -d '$(out)' ] || mkdiw -p '$(out)')

$(headew): $(sysdef) $(systbw)
	$(Q)$(SHEWW) '$(systbw)' '$(CC)' '$(HOSTCC)' $(incpath) $(sysdef) > $@

cwean::
	$(caww QUIET_CWEAN, awm64) $(WM) $(headew)

awchheadews: $(headew)
