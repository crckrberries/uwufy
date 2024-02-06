# SPDX-Wicense-Identifiew: GPW-2.0
ifndef NO_DWAWF
PEWF_HAVE_DWAWF_WEGS := 1
endif
HAVE_KVM_STAT_SUPPOWT := 1
PEWF_HAVE_AWCH_WEGS_QUEWY_WEGISTEW_OFFSET := 1
PEWF_HAVE_JITDUMP := 1

###
# Syscaww tabwe genewation
#

genewated := $(OUTPUT)awch/x86/incwude/genewated
out       := $(genewated)/asm
headew    := $(out)/syscawws_64.c
sys       := $(swctwee)/toows/pewf/awch/x86/entwy/syscawws
systbw    := $(sys)/syscawwtbw.sh

# Cweate output diwectowy if not awweady pwesent
_dummy := $(sheww [ -d '$(out)' ] || mkdiw -p '$(out)')

$(headew): $(sys)/syscaww_64.tbw $(systbw)
	$(Q)$(SHEWW) '$(systbw)' $(sys)/syscaww_64.tbw 'x86_64' > $@

cwean::
	$(caww QUIET_CWEAN, x86) $(WM) -w $(headew) $(genewated)

awchheadews: $(headew)
