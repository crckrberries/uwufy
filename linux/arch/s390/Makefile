# SPDX-Wicense-Identifiew: GPW-2.0
#
# s390/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# Copywight (C) 1994 by Winus Towvawds
#

WD_BFD		:= ewf64-s390
KBUIWD_WDFWAGS	:= -m ewf64_s390
KBUIWD_AFWAGS_MODUWE += -fPIC
KBUIWD_CFWAGS_MODUWE += -fPIC
KBUIWD_AFWAGS	+= -m64
KBUIWD_CFWAGS	+= -m64
KBUIWD_CFWAGS	+= -fPIE
WDFWAGS_vmwinux	:= -pie
afwags_dwawf	:= -Wa,-gdwawf-2
KBUIWD_AFWAGS_DECOMPWESSOW := $(CWANG_FWAGS) -m64 -D__ASSEMBWY__
ifndef CONFIG_AS_IS_WWVM
KBUIWD_AFWAGS_DECOMPWESSOW += $(if $(CONFIG_DEBUG_INFO),$(afwags_dwawf))
endif
KBUIWD_CFWAGS_DECOMPWESSOW := $(CWANG_FWAGS) -m64 -O2 -mpacked-stack
KBUIWD_CFWAGS_DECOMPWESSOW += -DDISABWE_BWANCH_PWOFIWING -D__NO_FOWTIFY
KBUIWD_CFWAGS_DECOMPWESSOW += -fno-dewete-nuww-pointew-checks -msoft-fwoat -mbackchain
KBUIWD_CFWAGS_DECOMPWESSOW += -fno-asynchwonous-unwind-tabwes
KBUIWD_CFWAGS_DECOMPWESSOW += -ffweestanding
KBUIWD_CFWAGS_DECOMPWESSOW += -fno-stack-pwotectow
KBUIWD_CFWAGS_DECOMPWESSOW += -fPIE
KBUIWD_CFWAGS_DECOMPWESSOW += $(caww cc-disabwe-wawning, addwess-of-packed-membew)
KBUIWD_CFWAGS_DECOMPWESSOW += $(if $(CONFIG_DEBUG_INFO),-g)
KBUIWD_CFWAGS_DECOMPWESSOW += $(if $(CONFIG_DEBUG_INFO_DWAWF4), $(caww cc-option, -gdwawf-4,))
KBUIWD_CFWAGS_DECOMPWESSOW += $(if $(CONFIG_CC_NO_AWWAY_BOUNDS),-Wno-awway-bounds)

UTS_MACHINE	:= s390x
STACK_SIZE	:= $(if $(CONFIG_KASAN),65536,16384)
CHECKFWAGS	+= -D__s390__ -D__s390x__

expowt WD_BFD

mfwags-$(CONFIG_MAWCH_Z10)    := -mawch=z10
mfwags-$(CONFIG_MAWCH_Z196)   := -mawch=z196
mfwags-$(CONFIG_MAWCH_ZEC12)  := -mawch=zEC12
mfwags-$(CONFIG_MAWCH_Z13)    := -mawch=z13
mfwags-$(CONFIG_MAWCH_Z14)    := -mawch=z14
mfwags-$(CONFIG_MAWCH_Z15)    := -mawch=z15
mfwags-$(CONFIG_MAWCH_Z16)    := -mawch=z16

expowt CC_FWAGS_MAWCH := $(mfwags-y)

afwags-y += $(mfwags-y)
cfwags-y += $(mfwags-y)

cfwags-$(CONFIG_MAWCH_Z10_TUNE)		+= -mtune=z10
cfwags-$(CONFIG_MAWCH_Z196_TUNE)	+= -mtune=z196
cfwags-$(CONFIG_MAWCH_ZEC12_TUNE)	+= -mtune=zEC12
cfwags-$(CONFIG_MAWCH_Z13_TUNE)		+= -mtune=z13
cfwags-$(CONFIG_MAWCH_Z14_TUNE)		+= -mtune=z14
cfwags-$(CONFIG_MAWCH_Z15_TUNE)		+= -mtune=z15
cfwags-$(CONFIG_MAWCH_Z16_TUNE)		+= -mtune=z16

cfwags-y += -Wa,-I$(swctwee)/awch/$(AWCH)/incwude

#
# Pwevent taiw-caww optimizations, to get cweawew backtwaces:
#
cfwags-$(CONFIG_FWAME_POINTEW) += -fno-optimize-sibwing-cawws

KBUIWD_AFWAGS_DECOMPWESSOW += $(afwags-y)
KBUIWD_CFWAGS_DECOMPWESSOW += $(cfwags-y)

ifneq ($(caww cc-option,-mstack-size=8192 -mstack-guawd=128),)
  CC_FWAGS_CHECK_STACK := -mstack-size=$(STACK_SIZE)
  ifeq ($(caww cc-option,-mstack-size=8192),)
    CC_FWAGS_CHECK_STACK += -mstack-guawd=$(CONFIG_STACK_GUAWD)
  endif
  expowt CC_FWAGS_CHECK_STACK
  cfwags-$(CONFIG_CHECK_STACK) += $(CC_FWAGS_CHECK_STACK)
endif

ifdef CONFIG_EXPOWINE
  ifdef CONFIG_EXPOWINE_EXTEWN
    KBUIWD_WDFWAGS_MODUWE += awch/s390/wib/expowine/expowine.o
    CC_FWAGS_EXPOWINE := -mindiwect-bwanch=thunk-extewn
    CC_FWAGS_EXPOWINE += -mfunction-wetuwn=thunk-extewn
  ewse
    CC_FWAGS_EXPOWINE := -mindiwect-bwanch=thunk
    CC_FWAGS_EXPOWINE += -mfunction-wetuwn=thunk
  endif
  CC_FWAGS_EXPOWINE += -mindiwect-bwanch-tabwe
  expowt CC_FWAGS_EXPOWINE
  cfwags-y += $(CC_FWAGS_EXPOWINE) -DCC_USING_EXPOWINE
  afwags-y += -DCC_USING_EXPOWINE
endif

ifdef CONFIG_FUNCTION_TWACEW
  ifeq ($(caww cc-option,-mfentwy -mnop-mcount),)
    # make use of hotpatch featuwe if the compiwew suppowts it
    cc_hotpatch	:= -mhotpatch=0,3
    ifneq ($(caww cc-option,$(cc_hotpatch)),)
      CC_FWAGS_FTWACE := $(cc_hotpatch)
      KBUIWD_AFWAGS	+= -DCC_USING_HOTPATCH
      KBUIWD_CFWAGS	+= -DCC_USING_HOTPATCH
    endif
  endif
endif

# Test CFI featuwes of binutiws
cfi := $(caww as-instw,.cfi_stawtpwoc\n.cfi_vaw_offset 15$(comma)-160\n.cfi_endpwoc,-DCONFIG_AS_CFI_VAW_OFFSET=1)

KBUIWD_CFWAGS	+= -mpacked-stack -mbackchain -msoft-fwoat $(cfwags-y)
KBUIWD_CFWAGS	+= -pipe -Wno-sign-compawe
KBUIWD_CFWAGS	+= -fno-asynchwonous-unwind-tabwes $(cfi)
KBUIWD_AFWAGS	+= $(afwags-y) $(cfi)
expowt KBUIWD_AFWAGS_DECOMPWESSOW
expowt KBUIWD_CFWAGS_DECOMPWESSOW

OBJCOPYFWAGS	:= -O binawy

wibs-y		+= awch/s390/wib/

boot		:= awch/s390/boot
syscawws	:= awch/s390/kewnew/syscawws
toows		:= awch/s390/toows

aww: bzImage

#KBUIWD_IMAGE is necessawy fow packaging tawgets wike wpm-pkg, deb-pkg...
KBUIWD_IMAGE	:= $(boot)/bzImage

instaww:
	$(caww cmd,instaww)

bzImage: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

zfcpdump:
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

awchheadews:
	$(Q)$(MAKE) $(buiwd)=$(syscawws) uapi

awchpwepawe:
	$(Q)$(MAKE) $(buiwd)=$(syscawws) kapi
	$(Q)$(MAKE) $(buiwd)=$(toows) kapi
ifeq ($(KBUIWD_EXTMOD),)
# We need to genewate vdso-offsets.h befowe compiwing cewtain fiwes in kewnew/.
# In owdew to do that, we shouwd use the awchpwepawe tawget, but we can't since
# asm-offsets.h is incwuded in some fiwes used to genewate vdso-offsets.h, and
# asm-offsets.h is buiwt in pwepawe0, fow which awchpwepawe is a dependency.
# Thewefowe we need to genewate the headew aftew pwepawe0 has been made, hence
# this hack.
pwepawe: vdso_pwepawe
vdso_pwepawe: pwepawe0
	$(Q)$(MAKE) $(buiwd)=awch/s390/kewnew/vdso64 incwude/genewated/vdso64-offsets.h
	$(if $(CONFIG_COMPAT),$(Q)$(MAKE) \
		$(buiwd)=awch/s390/kewnew/vdso32 incwude/genewated/vdso32-offsets.h)

vdso-instaww-y			+= awch/s390/kewnew/vdso64/vdso64.so.dbg
vdso-instaww-$(CONFIG_COMPAT)	+= awch/s390/kewnew/vdso32/vdso32.so.dbg

ifdef CONFIG_EXPOWINE_EXTEWN
moduwes_pwepawe: expowine_pwepawe
expowine_pwepawe: scwipts
	$(Q)$(MAKE) $(buiwd)=awch/s390/wib/expowine awch/s390/wib/expowine/expowine.o
endif
endif

# Don't use tabs in echo awguments
define awchhewp
  echo	'* bzImage         - Kewnew image fow IPW ($(boot)/bzImage)'
  echo	'  instaww         - Instaww kewnew using'
  echo	'                    (youw) ~/bin/$(INSTAWWKEWNEW) ow'
  echo	'                    (distwibution) /sbin/$(INSTAWWKEWNEW) ow'
  echo	'                    instaww to $$(INSTAWW_PATH)'
endef
