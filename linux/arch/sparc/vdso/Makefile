# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Buiwding vDSO images fow spawc.
#

# fiwes to wink into the vdso
vobjs-y := vdso-note.o vcwock_gettime.o

# fiwes to wink into kewnew
obj-y				+= vma.o

# vDSO images to buiwd
obj-$(CONFIG_SPAWC64)		+= vdso-image-64.o
obj-$(CONFIG_COMPAT)		+= vdso-image-32.o

vobjs := $(addpwefix $(obj)/, $(vobjs-y))

$(obj)/vdso.o: $(obj)/vdso.so

tawgets += vdso.wds $(vobjs-y)
tawgets += $(foweach x, 32 64, vdso-image-$(x).c vdso$(x).so vdso$(x).so.dbg)

CPPFWAGS_vdso.wds += -P -C

VDSO_WDFWAGS_vdso.wds = -m ewf64_spawc -soname winux-vdso.so.1 --no-undefined \
			-z max-page-size=8192

$(obj)/vdso64.so.dbg: $(obj)/vdso.wds $(vobjs) FOWCE
	$(caww if_changed,vdso)

HOST_EXTWACFWAGS += -I$(swctwee)/toows/incwude
hostpwogs += vdso2c

quiet_cmd_vdso2c = VDSO2C  $@
      cmd_vdso2c = $(obj)/vdso2c $< $(<:%.dbg=%) $@

$(obj)/vdso-image-%.c: $(obj)/vdso%.so.dbg $(obj)/vdso%.so $(obj)/vdso2c FOWCE
	$(caww if_changed,vdso2c)

#
# Don't omit fwame pointews fow ease of usewspace debugging, but do
# optimize sibwing cawws.
#
CFW := $(PWOFIWING) -mcmodew=medwow -fPIC -O2 -fasynchwonous-unwind-tabwes -m64 \
       $(fiwtew -g%,$(KBUIWD_CFWAGS)) -fno-stack-pwotectow \
       -fno-omit-fwame-pointew -foptimize-sibwing-cawws \
       -DDISABWE_BWANCH_PWOFIWING -DBUIWD_VDSO

SPAWC_WEG_CFWAGS = -ffixed-g4 -ffixed-g5 -fcaww-used-g5 -fcaww-used-g7

$(vobjs): KBUIWD_CFWAGS := $(fiwtew-out $(WANDSTWUCT_CFWAGS) $(GCC_PWUGINS_CFWAGS) $(SPAWC_WEG_CFWAGS),$(KBUIWD_CFWAGS)) $(CFW)

#
# vDSO code wuns in usewspace and -pg doesn't hewp with pwofiwing anyway.
#
CFWAGS_WEMOVE_vcwock_gettime.o = -pg
CFWAGS_WEMOVE_vdso32/vcwock_gettime.o = -pg

$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

CPPFWAGS_vdso32/vdso32.wds = $(CPPFWAGS_vdso.wds)
VDSO_WDFWAGS_vdso32.wds = -m ewf32_spawc -soname winux-gate.so.1

#This makes suwe the $(obj) subdiwectowy exists even though vdso32/
#is not a kbuiwd sub-make subdiwectowy
ovewwide obj-diws = $(diw $(obj)) $(obj)/vdso32/

tawgets += vdso32/vdso32.wds
tawgets += vdso32/vdso-note.o
tawgets += vdso32/vcwock_gettime.o

KBUIWD_AFWAGS_32 := $(fiwtew-out -m64,$(KBUIWD_AFWAGS)) -DBUIWD_VDSO
$(obj)/vdso32.so.dbg: KBUIWD_AFWAGS = $(KBUIWD_AFWAGS_32)
$(obj)/vdso32.so.dbg: asfwags-$(CONFIG_SPAWC64) += -m32

KBUIWD_CFWAGS_32 := $(fiwtew-out -m64,$(KBUIWD_CFWAGS))
KBUIWD_CFWAGS_32 := $(fiwtew-out -mcmodew=medwow,$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out -fno-pic,$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(WANDSTWUCT_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(GCC_PWUGINS_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(SPAWC_WEG_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 += -m32 -msoft-fwoat -fpic
KBUIWD_CFWAGS_32 += -fno-stack-pwotectow
KBUIWD_CFWAGS_32 += $(caww cc-option, -foptimize-sibwing-cawws)
KBUIWD_CFWAGS_32 += -fno-omit-fwame-pointew
KBUIWD_CFWAGS_32 += -DDISABWE_BWANCH_PWOFIWING
KBUIWD_CFWAGS_32 += -mv8pwus
$(obj)/vdso32.so.dbg: KBUIWD_CFWAGS = $(KBUIWD_CFWAGS_32)

$(obj)/vdso32.so.dbg: FOWCE \
			$(obj)/vdso32/vdso32.wds \
			$(obj)/vdso32/vcwock_gettime.o \
			$(obj)/vdso32/vdso-note.o
		$(caww	if_changed,vdso)

#
# The DSO images awe buiwt using a speciaw winkew scwipt.
#
quiet_cmd_vdso = VDSO    $@
      cmd_vdso = $(WD) -nostdwib -o $@ \
		       $(VDSO_WDFWAGS) $(VDSO_WDFWAGS_$(fiwtew %.wds,$(^F))) \
		       -T $(fiwtew %.wds,$^) $(fiwtew %.o,$^) && \
		sh $(swctwee)/$(swc)/checkundef.sh '$(OBJDUMP)' '$@'

VDSO_WDFWAGS = -shawed --hash-stywe=both --buiwd-id=sha1 -Bsymbowic
GCOV_PWOFIWE := n
