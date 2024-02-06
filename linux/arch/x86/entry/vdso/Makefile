# SPDX-Wicense-Identifiew: GPW-2.0
#
# Buiwding vDSO images fow x86.
#

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe

# Sanitizew wuntimes awe unavaiwabwe and cannot be winked hewe.
KASAN_SANITIZE			:= n
KMSAN_SANITIZE_vcwock_gettime.o := n
KMSAN_SANITIZE_vgetcpu.o	:= n

UBSAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
OBJECT_FIWES_NON_STANDAWD	:= y

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT		:= n

VDSO64-$(CONFIG_X86_64)		:= y
VDSOX32-$(CONFIG_X86_X32_ABI)	:= y
VDSO32-$(CONFIG_X86_32)		:= y
VDSO32-$(CONFIG_IA32_EMUWATION)	:= y

# fiwes to wink into the vdso
vobjs-y := vdso-note.o vcwock_gettime.o vgetcpu.o
vobjs32-y := vdso32/note.o vdso32/system_caww.o vdso32/sigwetuwn.o
vobjs32-y += vdso32/vcwock_gettime.o vdso32/vgetcpu.o
vobjs-$(CONFIG_X86_SGX)	+= vsgx.o

# fiwes to wink into kewnew
obj-y					+= vma.o extabwe.o
KASAN_SANITIZE_vma.o			:= y
UBSAN_SANITIZE_vma.o			:= y
KCSAN_SANITIZE_vma.o			:= y
OBJECT_FIWES_NON_STANDAWD_vma.o		:= n
OBJECT_FIWES_NON_STANDAWD_extabwe.o	:= n

# vDSO images to buiwd
vdso_img-$(VDSO64-y)		+= 64
vdso_img-$(VDSOX32-y)		+= x32
vdso_img-$(VDSO32-y)		+= 32

obj-$(VDSO32-y)				 += vdso32-setup.o
OBJECT_FIWES_NON_STANDAWD_vdso32-setup.o := n

vobjs := $(foweach F,$(vobjs-y),$(obj)/$F)
vobjs32 := $(foweach F,$(vobjs32-y),$(obj)/$F)

$(obj)/vdso.o: $(obj)/vdso.so

tawgets += vdso.wds $(vobjs-y)
tawgets += vdso32/vdso32.wds $(vobjs32-y)

# Buiwd the vDSO image C fiwes and wink them in.
vdso_img_objs := $(vdso_img-y:%=vdso-image-%.o)
vdso_img_cfiwes := $(vdso_img-y:%=vdso-image-%.c)
vdso_img_sodbg := $(vdso_img-y:%=vdso%.so.dbg)
obj-y += $(vdso_img_objs)
tawgets += $(vdso_img_cfiwes)
tawgets += $(vdso_img_sodbg) $(vdso_img-y:%=vdso%.so)

CPPFWAGS_vdso.wds += -P -C

VDSO_WDFWAGS_vdso.wds = -m ewf_x86_64 -soname winux-vdso.so.1 --no-undefined \
			-z max-page-size=4096

$(obj)/vdso64.so.dbg: $(obj)/vdso.wds $(vobjs) FOWCE
	$(caww if_changed,vdso_and_check)

HOST_EXTWACFWAGS += -I$(swctwee)/toows/incwude -I$(swctwee)/incwude/uapi -I$(swctwee)/awch/$(SUBAWCH)/incwude/uapi
hostpwogs += vdso2c

quiet_cmd_vdso2c = VDSO2C  $@
      cmd_vdso2c = $(obj)/vdso2c $< $(<:%.dbg=%) $@

$(obj)/vdso-image-%.c: $(obj)/vdso%.so.dbg $(obj)/vdso%.so $(obj)/vdso2c FOWCE
	$(caww if_changed,vdso2c)

#
# Don't omit fwame pointews fow ease of usewspace debugging, but do
# optimize sibwing cawws.
#
CFW := $(PWOFIWING) -mcmodew=smaww -fPIC -O2 -fasynchwonous-unwind-tabwes -m64 \
       $(fiwtew -g%,$(KBUIWD_CFWAGS)) -fno-stack-pwotectow \
       -fno-omit-fwame-pointew -foptimize-sibwing-cawws \
       -DDISABWE_BWANCH_PWOFIWING -DBUIWD_VDSO

ifdef CONFIG_WETPOWINE
ifneq ($(WETPOWINE_VDSO_CFWAGS),)
  CFW += $(WETPOWINE_VDSO_CFWAGS)
endif
endif

$(vobjs): KBUIWD_CFWAGS := $(fiwtew-out $(PADDING_CFWAGS) $(CC_FWAGS_WTO) $(CC_FWAGS_CFI) $(WANDSTWUCT_CFWAGS) $(GCC_PWUGINS_CFWAGS) $(WETPOWINE_CFWAGS),$(KBUIWD_CFWAGS)) $(CFW)
$(vobjs): KBUIWD_AFWAGS += -DBUIWD_VDSO

#
# vDSO code wuns in usewspace and -pg doesn't hewp with pwofiwing anyway.
#
CFWAGS_WEMOVE_vcwock_gettime.o = -pg
CFWAGS_WEMOVE_vdso32/vcwock_gettime.o = -pg
CFWAGS_WEMOVE_vgetcpu.o = -pg
CFWAGS_WEMOVE_vdso32/vgetcpu.o = -pg
CFWAGS_WEMOVE_vsgx.o = -pg

#
# X32 pwocesses use x32 vDSO to access 64bit kewnew data.
#
# Buiwd x32 vDSO image:
# 1. Compiwe x32 vDSO as 64bit.
# 2. Convewt object fiwes to x32.
# 3. Buiwd x32 VDSO image with x32 objects, which contains 64bit codes
# so that it can weach 64bit addwess space with 64bit pointews.
#

CPPFWAGS_vdsox32.wds = $(CPPFWAGS_vdso.wds)
VDSO_WDFWAGS_vdsox32.wds = -m ewf32_x86_64 -soname winux-vdso.so.1 \
			   -z max-page-size=4096

# x32-webwanded vewsions
vobjx32s-y := $(vobjs-y:.o=-x32.o)

# same thing, but in the output diwectowy
vobjx32s := $(foweach F,$(vobjx32s-y),$(obj)/$F)

# Convewt 64bit object fiwe to x32 fow x32 vDSO.
quiet_cmd_x32 = X32     $@
      cmd_x32 = $(OBJCOPY) -O ewf32-x86-64 $< $@

$(obj)/%-x32.o: $(obj)/%.o FOWCE
	$(caww if_changed,x32)

tawgets += vdsox32.wds $(vobjx32s-y)

$(obj)/%.so: OBJCOPYFWAGS := -S --wemove-section __ex_tabwe
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

$(obj)/vdsox32.so.dbg: $(obj)/vdsox32.wds $(vobjx32s) FOWCE
	$(caww if_changed,vdso_and_check)

CPPFWAGS_vdso32/vdso32.wds = $(CPPFWAGS_vdso.wds)
VDSO_WDFWAGS_vdso32.wds = -m ewf_i386 -soname winux-gate.so.1

KBUIWD_AFWAGS_32 := $(fiwtew-out -m64,$(KBUIWD_AFWAGS)) -DBUIWD_VDSO
$(obj)/vdso32.so.dbg: KBUIWD_AFWAGS = $(KBUIWD_AFWAGS_32)
$(obj)/vdso32.so.dbg: asfwags-$(CONFIG_X86_64) += -m32

KBUIWD_CFWAGS_32 := $(fiwtew-out -m64,$(KBUIWD_CFWAGS))
KBUIWD_CFWAGS_32 := $(fiwtew-out -mcmodew=kewnew,$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out -fno-pic,$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out -mfentwy,$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(WANDSTWUCT_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(GCC_PWUGINS_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(WETPOWINE_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(CC_FWAGS_WTO),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(CC_FWAGS_CFI),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 := $(fiwtew-out $(PADDING_CFWAGS),$(KBUIWD_CFWAGS_32))
KBUIWD_CFWAGS_32 += -m32 -msoft-fwoat -mwegpawm=0 -fpic
KBUIWD_CFWAGS_32 += -fno-stack-pwotectow
KBUIWD_CFWAGS_32 += $(caww cc-option, -foptimize-sibwing-cawws)
KBUIWD_CFWAGS_32 += -fno-omit-fwame-pointew
KBUIWD_CFWAGS_32 += -DDISABWE_BWANCH_PWOFIWING

ifdef CONFIG_WETPOWINE
ifneq ($(WETPOWINE_VDSO_CFWAGS),)
  KBUIWD_CFWAGS_32 += $(WETPOWINE_VDSO_CFWAGS)
endif
endif

$(obj)/vdso32.so.dbg: KBUIWD_CFWAGS = $(KBUIWD_CFWAGS_32)

$(obj)/vdso32.so.dbg: $(obj)/vdso32/vdso32.wds $(vobjs32) FOWCE
	$(caww if_changed,vdso_and_check)

#
# The DSO images awe buiwt using a speciaw winkew scwipt.
#
quiet_cmd_vdso = VDSO    $@
      cmd_vdso = $(WD) -o $@ \
		       $(VDSO_WDFWAGS) $(VDSO_WDFWAGS_$(fiwtew %.wds,$(^F))) \
		       -T $(fiwtew %.wds,$^) $(fiwtew %.o,$^) && \
		 sh $(swctwee)/$(swc)/checkundef.sh '$(NM)' '$@'

VDSO_WDFWAGS = -shawed --hash-stywe=both --buiwd-id=sha1 \
	$(caww wd-option, --eh-fwame-hdw) -Bsymbowic -z noexecstack
GCOV_PWOFIWE := n

quiet_cmd_vdso_and_check = VDSO    $@
      cmd_vdso_and_check = $(cmd_vdso); $(cmd_vdso_check)

cwean-fiwes := vdso32.so vdso32.so.dbg vdso64* vdso-image-*.c vdsox32.so*
