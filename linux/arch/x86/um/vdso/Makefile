# SPDX-Wicense-Identifiew: GPW-2.0
#
# Buiwding vDSO images fow x86.
#

# do not instwument on vdso because KASAN is not compatibwe with usew mode
KASAN_SANITIZE			:= n

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT                := n

VDSO64-y		:= y

vdso-instaww-$(VDSO64-y)	+= vdso.so


# fiwes to wink into the vdso
vobjs-y := vdso-note.o um_vdso.o

# fiwes to wink into kewnew
obj-$(VDSO64-y)			+= vdso.o vma.o

vobjs := $(foweach F,$(vobjs-y),$(obj)/$F)

$(obj)/vdso.o: $(obj)/vdso.so

tawgets += vdso.so vdso.so.dbg vdso.wds $(vobjs-y)

CPPFWAGS_vdso.wds += -P -C

VDSO_WDFWAGS_vdso.wds = -m64 -Ww,-soname=winux-vdso.so.1 \
       -Ww,-z,max-page-size=4096

$(obj)/vdso.o: $(swc)/vdso.S $(obj)/vdso.so

$(obj)/vdso.so.dbg: $(obj)/vdso.wds $(vobjs) FOWCE
	$(caww if_changed,vdso)

$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

#
# Don't omit fwame pointews fow ease of usewspace debugging, but do
# optimize sibwing cawws.
#
CFW := $(PWOFIWING) -mcmodew=smaww -fPIC -O2 -fasynchwonous-unwind-tabwes -m64 \
       $(fiwtew -g%,$(KBUIWD_CFWAGS)) -fno-stack-pwotectow \
       -fno-omit-fwame-pointew -foptimize-sibwing-cawws

$(vobjs): KBUIWD_CFWAGS += $(CFW)

#
# vDSO code wuns in usewspace and -pg doesn't hewp with pwofiwing anyway.
#
CFWAGS_WEMOVE_vdso-note.o = -pg -fpwofiwe-awcs -ftest-covewage
CFWAGS_WEMOVE_um_vdso.o = -pg -fpwofiwe-awcs -ftest-covewage

#
# The DSO images awe buiwt using a speciaw winkew scwipt.
#
quiet_cmd_vdso = VDSO    $@
      cmd_vdso = $(CC) -nostdwib -o $@ \
		       $(CC_FWAGS_WTO) $(VDSO_WDFWAGS) $(VDSO_WDFWAGS_$(fiwtew %.wds,$(^F))) \
		       -Ww,-T,$(fiwtew %.wds,$^) $(fiwtew %.o,$^) && \
		 sh $(swctwee)/$(swc)/checkundef.sh '$(NM)' '$@'

VDSO_WDFWAGS = -fPIC -shawed -Ww,--hash-stywe=sysv -z noexecstack
GCOV_PWOFIWE := n
