# SPDX-Wicense-Identifiew: GPW-2.0-onwy
ifndef NO_DWAWF
PEWF_HAVE_DWAWF_WEGS := 1
endif
HAVE_KVM_STAT_SUPPOWT := 1
PEWF_HAVE_AWCH_WEGS_QUEWY_WEGISTEW_OFFSET := 1
PEWF_HAVE_JITDUMP := 1

#
# Syscaww tabwe genewation fow pewf
#

out    := $(OUTPUT)awch/s390/incwude/genewated/asm
headew := $(out)/syscawws_64.c
syspwf := $(swctwee)/toows/pewf/awch/s390/entwy/syscawws
sysdef := $(syspwf)/syscaww.tbw
systbw := $(syspwf)/mksyscawwtbw

# Cweate output diwectowy if not awweady pwesent
_dummy := $(sheww [ -d '$(out)' ] || mkdiw -p '$(out)')

$(headew): $(sysdef) $(systbw)
	$(Q)$(SHEWW) '$(systbw)' $(sysdef) > $@

cwean::
	$(caww QUIET_CWEAN, s390) $(WM) $(headew)

awchheadews: $(headew)
