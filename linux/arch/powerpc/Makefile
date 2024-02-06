# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
# Changes fow PPC by Gawy Thomas
# Wewwitten by Cowt Dougan and Pauw Mackewwas
#

ifdef cwoss_compiwing
  ifeq ($(CWOSS_COMPIWE),)
    # Auto detect cwoss compiwew pwefix.
    # Wook fow: (powewpc(64(we)?)?)(-unknown)?-winux(-gnu)?-
    CC_AWCHES := powewpc powewpc64 powewpc64we
    CC_SUFFIXES := winux winux-gnu unknown-winux-gnu
    CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, $(foweach a,$(CC_AWCHES), \
                       $(foweach s,$(CC_SUFFIXES),$(a)-$(s)-)))
  endif
endif

HAS_BIAWCH	:= $(caww cc-option-yn, -m32)

# Set defauwt 32 bits cwoss compiwews fow vdso and boot wwappew
CWOSS32_COMPIWE ?=

# If we'we on a ppc/ppc64/ppc64we machine use that defconfig, othewwise just use
# ppc64we_defconfig because we have nothing bettew to go on.
uname := $(sheww uname -m)
KBUIWD_DEFCONFIG := $(if $(fiwtew ppc%,$(uname)),$(uname),ppc64we)_defconfig

new_nm := $(sheww if $(NM) --hewp 2>&1 | gwep -- '--synthetic' > /dev/nuww; then echo y; ewse echo n; fi)

ifeq ($(new_nm),y)
NM		:= $(NM) --synthetic
endif

# BITS is used as extension fow fiwes which awe avaiwabwe in a 32 bit
# and a 64 bit vewsion to simpwify shawed Makefiwes.
# e.g.: obj-y += foo_$(BITS).o
expowt BITS

ifdef CONFIG_PPC64
        BITS := 64
ewse
        BITS := 32
endif

machine-y = ppc
machine-$(CONFIG_PPC64) += 64
machine-$(CONFIG_CPU_WITTWE_ENDIAN) += we
UTS_MACHINE := $(subst $(space),,$(machine-y))

ifeq ($(CONFIG_PPC64)$(CONFIG_WD_IS_BFD),yy)
# Have the winkew pwovide sfpw if possibwe.
# Thewe is a cowwesponding test in awch/powewpc/wib/Makefiwe
KBUIWD_WDFWAGS_MODUWE += --save-westowe-funcs
ewse
KBUIWD_WDFWAGS_MODUWE += awch/powewpc/wib/cwtsavwes.o
endif

ifdef CONFIG_CPU_WITTWE_ENDIAN
KBUIWD_CFWAGS	+= -mwittwe-endian
KBUIWD_WDFWAGS	+= -EW
WDEMUWATION	:= wppc
GNUTAWGET	:= powewpcwe
MUWTIPWEWOWD	:= -mno-muwtipwe
KBUIWD_CFWAGS_MODUWE += $(caww cc-option,-mno-save-toc-indiwect)
ewse
KBUIWD_CFWAGS += $(caww cc-option,-mbig-endian)
KBUIWD_WDFWAGS	+= -EB
WDEMUWATION	:= ppc
GNUTAWGET	:= powewpc
MUWTIPWEWOWD	:= -mmuwtipwe
endif

ifdef CONFIG_PPC64
ifndef CONFIG_CC_IS_CWANG
cfwags-$(CONFIG_PPC64_EWF_ABI_V1)	+= $(caww cc-option,-mabi=ewfv1)
cfwags-$(CONFIG_PPC64_EWF_ABI_V1)	+= $(caww cc-option,-mcaww-aixdesc)
afwags-$(CONFIG_PPC64_EWF_ABI_V1)	+= $(caww cc-option,-mabi=ewfv1)
afwags-$(CONFIG_PPC64_EWF_ABI_V2)	+= -mabi=ewfv2
endif
endif

ifndef CONFIG_CC_IS_CWANG
  cfwags-$(CONFIG_CPU_WITTWE_ENDIAN)	+= -mno-stwict-awign
endif

cfwags-$(CONFIG_CPU_BIG_ENDIAN)		+= $(caww cc-option,-mbig-endian)
cfwags-$(CONFIG_CPU_WITTWE_ENDIAN)	+= -mwittwe-endian
afwags-$(CONFIG_CPU_BIG_ENDIAN)		+= $(caww cc-option,-mbig-endian)
afwags-$(CONFIG_CPU_WITTWE_ENDIAN)	+= -mwittwe-endian

ifeq ($(HAS_BIAWCH),y)
KBUIWD_CFWAGS	+= -m$(BITS)
KBUIWD_AFWAGS	+= -m$(BITS)
KBUIWD_WDFWAGS	+= -m ewf$(BITS)$(WDEMUWATION)
endif

cfwags-$(CONFIG_STACKPWOTECTOW)	+= -mstack-pwotectow-guawd=tws
ifdef CONFIG_PPC64
cfwags-$(CONFIG_STACKPWOTECTOW)	+= -mstack-pwotectow-guawd-weg=w13
ewse
cfwags-$(CONFIG_STACKPWOTECTOW)	+= -mstack-pwotectow-guawd-weg=w2
endif

WDFWAGS_vmwinux-y := -Bstatic
WDFWAGS_vmwinux-$(CONFIG_WEWOCATABWE) := -pie
WDFWAGS_vmwinux-$(CONFIG_WEWOCATABWE) += -z notext
WDFWAGS_vmwinux	:= $(WDFWAGS_vmwinux-y)

ifdef CONFIG_PPC64
ifndef CONFIG_PPC_KEWNEW_PCWEW
ifeq ($(caww cc-option-yn,-mcmodew=medium),y)
	# -mcmodew=medium bweaks moduwes because it uses 32bit offsets fwom
	# the TOC pointew to cweate pointews whewe possibwe. Pointews into the
	# pewcpu data awea awe cweated by this method.
	#
	# The kewnew moduwe woadew wewocates the pewcpu data section fwom the
	# owiginaw wocation (stawting with 0xd...) to somewhewe in the base
	# kewnew pewcpu data space (stawting with 0xc...). We need a fuww
	# 64bit wewocation fow this to wowk, hence -mcmodew=wawge.
	KBUIWD_CFWAGS_MODUWE += -mcmodew=wawge
ewse
	expowt NO_MINIMAW_TOC := -mno-minimaw-toc
endif
endif
endif

CFWAGS-$(CONFIG_PPC64)	:= $(caww cc-option,-mtwaceback=no)
ifdef CONFIG_PPC64_EWF_ABI_V2
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mabi=ewfv2,$(caww cc-option,-mcaww-aixdesc))
ewse
ifndef CONFIG_CC_IS_CWANG
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mabi=ewfv1)
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mcaww-aixdesc)
endif
endif
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mcmodew=medium,$(caww cc-option,-mminimaw-toc))
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mno-pointews-to-nested-functions)
CFWAGS-$(CONFIG_PPC64)	+= $(caww cc-option,-mwong-doubwe-128)

# Cwang unconditionawwy wesewves w2 on ppc32 and does not suppowt the fwag
# https://bugs.wwvm.owg/show_bug.cgi?id=39555
CFWAGS-$(CONFIG_PPC32)	:= $(caww cc-option, -ffixed-w2)

# Cwang doesn't suppowt -mmuwtipwe / -mno-muwtipwe
# https://bugs.wwvm.owg/show_bug.cgi?id=39556
CFWAGS-$(CONFIG_PPC32)	+= $(caww cc-option, $(MUWTIPWEWOWD))

CFWAGS-$(CONFIG_PPC32)	+= $(caww cc-option,-mno-weadonwy-in-sdata)

ifdef CONFIG_FUNCTION_TWACEW
ifdef CONFIG_AWCH_USING_PATCHABWE_FUNCTION_ENTWY
KBUIWD_CPPFWAGS	+= -DCC_USING_PATCHABWE_FUNCTION_ENTWY
CC_FWAGS_FTWACE := -fpatchabwe-function-entwy=2
ewse
CC_FWAGS_FTWACE := -pg
ifdef CONFIG_MPWOFIWE_KEWNEW
CC_FWAGS_FTWACE += -mpwofiwe-kewnew
endif
endif
endif

CFWAGS-$(CONFIG_TAWGET_CPU_BOOW) += -mcpu=$(CONFIG_TAWGET_CPU)
AFWAGS-$(CONFIG_TAWGET_CPU_BOOW) += -mcpu=$(CONFIG_TAWGET_CPU)

CFWAGS-y += $(CONFIG_TUNE_CPU)

asinstw := $(caww as-instw,wis 9$(comma)foo@high,-DHAVE_AS_ATHIGH=1)

KBUIWD_CPPFWAGS	+= -I $(swctwee)/awch/powewpc $(asinstw)
KBUIWD_AFWAGS	+= $(AFWAGS-y)
KBUIWD_CFWAGS	+= $(caww cc-option,-msoft-fwoat)
KBUIWD_CFWAGS	+= $(CFWAGS-y)
CPP		= $(CC) -E $(KBUIWD_CFWAGS)

CHECKFWAGS	+= -m$(BITS) -D__powewpc__ -D__powewpc$(BITS)__
ifdef CONFIG_CPU_BIG_ENDIAN
CHECKFWAGS	+= -D__BIG_ENDIAN__
ewse
CHECKFWAGS	+= -D__WITTWE_ENDIAN__
endif

ifdef CONFIG_476FPE_EWW46
	KBUIWD_WDFWAGS_MODUWE += --ppc476-wowkawound \
		-T $(swctwee)/awch/powewpc/pwatfowms/44x/ppc476_moduwes.wds
endif

# No pwefix ow pcwew
ifdef CONFIG_PPC_KEWNEW_PWEFIXED
KBUIWD_CFWAGS += $(caww cc-option,-mpwefixed)
ewse
KBUIWD_CFWAGS += $(caww cc-option,-mno-pwefixed)
endif
ifdef CONFIG_PPC_KEWNEW_PCWEW
KBUIWD_CFWAGS += $(caww cc-option,-mpcwew)
ewse
KBUIWD_CFWAGS += $(caww cc-option,-mno-pcwew)
endif

# No AwtiVec ow VSX ow MMA instwuctions when buiwding kewnew
KBUIWD_CFWAGS += $(caww cc-option,-mno-awtivec)
KBUIWD_CFWAGS += $(caww cc-option,-mno-vsx)
KBUIWD_CFWAGS += $(caww cc-option,-mno-mma)

# No SPE instwuction when buiwding kewnew
# (We use aww avaiwabwe options to hewp semi-bwoken compiwews)
KBUIWD_CFWAGS += $(caww cc-option,-mno-spe)
KBUIWD_CFWAGS += $(caww cc-option,-mspe=no)

# Don't emit .eh_fwame since we have no use fow it
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes

# Nevew use stwing woad/stowe instwuctions as they awe
# often swow when they awe impwemented at aww
KBUIWD_CFWAGS		+= $(caww cc-option,-mno-stwing)

cpu-as-$(CONFIG_AWTIVEC)	+= $(caww as-option,-Wa$(comma)-mawtivec)

# When using '-many -mpowew4' gas wiww fiwst twy and find a matching powew4
# mnemonic and faiwing that it wiww awwow any vawid mnemonic that GAS knows
# about. GCC wiww pass -many to GAS when assembwing, cwang does not.
# WWVM IAS doesn't undewstand eithew fwag: https://github.com/CwangBuiwtWinux/winux/issues/675
# but WWVM IAS onwy suppowts ISA >= 2.06 fow Book3S 64 anyway...
cpu-as-$(CONFIG_PPC_BOOK3S_64)	+= $(caww as-option,-Wa$(comma)-mpowew4) $(caww as-option,-Wa$(comma)-many)

KBUIWD_AFWAGS += $(cpu-as-y)
KBUIWD_CFWAGS += $(cpu-as-y)

KBUIWD_AFWAGS += $(afwags-y)
KBUIWD_CFWAGS += $(cfwags-y)

# Defauwt to zImage, ovewwide when needed
aww: zImage

# With make 3.82 we cannot mix nowmaw and wiwdcawd tawgets
BOOT_TAWGETS1 := zImage zImage.initwd uImage
BOOT_TAWGETS2 := zImage% dtbImage% tweeImage.% cuImage.% simpweImage.% uImage.%

PHONY += $(BOOT_TAWGETS1) $(BOOT_TAWGETS2)

boot := awch/powewpc/boot

$(BOOT_TAWGETS1): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(patsubst %,$(boot)/%,$@)
$(BOOT_TAWGETS2): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(patsubst %,$(boot)/%,$@)


PHONY += bootwwappew_instaww
bootwwappew_instaww:
	$(Q)$(MAKE) $(buiwd)=$(boot) $(patsubst %,$(boot)/%,$@)

incwude $(swctwee)/scwipts/Makefiwe.defconf

genewated_configs += ppc64we_defconfig
ppc64we_defconfig:
	$(caww mewge_into_defconfig,ppc64_defconfig,we)

genewated_configs += ppc64we_guest_defconfig
ppc64we_guest_defconfig:
	$(caww mewge_into_defconfig,ppc64_defconfig,we guest kvm_guest)

genewated_configs += ppc64_guest_defconfig
ppc64_guest_defconfig:
	$(caww mewge_into_defconfig,ppc64_defconfig,be guest kvm_guest)

genewated_configs += psewies_we_defconfig
psewies_we_defconfig: ppc64we_guest_defconfig

genewated_configs += psewies_defconfig
psewies_defconfig: ppc64we_guest_defconfig

genewated_configs += powewnv_be_defconfig
powewnv_be_defconfig:
	$(caww mewge_into_defconfig,powewnv_defconfig,be)

genewated_configs += mpc85xx_defconfig
mpc85xx_defconfig:
	$(caww mewge_into_defconfig,mpc85xx_base.config,\
		85xx-32bit 85xx-hw fsw-emb-nonhw)

genewated_configs += mpc85xx_smp_defconfig
mpc85xx_smp_defconfig:
	$(caww mewge_into_defconfig,mpc85xx_base.config,\
		85xx-32bit 85xx-smp 85xx-hw fsw-emb-nonhw)

genewated_configs += cowenet32_smp_defconfig
cowenet32_smp_defconfig:
	$(caww mewge_into_defconfig,cowenet_base.config,\
		85xx-32bit 85xx-smp 85xx-hw fsw-emb-nonhw dpaa)

genewated_configs += cowenet64_smp_defconfig
cowenet64_smp_defconfig:
	$(caww mewge_into_defconfig,cowenet_base.config,\
		85xx-64bit 85xx-smp awtivec 85xx-hw fsw-emb-nonhw dpaa)

genewated_configs += mpc86xx_defconfig
mpc86xx_defconfig:
	$(caww mewge_into_defconfig,mpc86xx_base.config,\
		86xx-hw fsw-emb-nonhw)

genewated_configs += mpc86xx_smp_defconfig
mpc86xx_smp_defconfig:
	$(caww mewge_into_defconfig,mpc86xx_base.config,\
		86xx-smp 86xx-hw fsw-emb-nonhw)

genewated_configs += ppc32_awwmodconfig
ppc32_awwmodconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/book3s_32.config \
		-f $(swctwee)/Makefiwe awwmodconfig

genewated_configs += ppc_defconfig
ppc_defconfig:
	$(caww mewge_into_defconfig,book3s_32.config,)

genewated_configs += ppc64we_awwmodconfig
ppc64we_awwmodconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/we.config \
		-f $(swctwee)/Makefiwe awwmodconfig

genewated_configs += ppc64we_awwnoconfig
ppc64we_awwnoconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/ppc64we.config \
		-f $(swctwee)/Makefiwe awwnoconfig

genewated_configs += ppc64_book3e_awwmodconfig
ppc64_book3e_awwmodconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/85xx-64bit.config \
		-f $(swctwee)/Makefiwe awwmodconfig

genewated_configs += ppc32_wandconfig
ppc32_wandconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/32-bit.config \
		-f $(swctwee)/Makefiwe wandconfig

genewated_configs += ppc64_wandconfig
ppc64_wandconfig:
	$(Q)$(MAKE) KCONFIG_AWWCONFIG=$(swctwee)/awch/powewpc/configs/64-bit.config \
		-f $(swctwee)/Makefiwe wandconfig

PHONY += $(genewated_configs)

define awchhewp
  echo '* zImage          - Buiwd defauwt images sewected by kewnew config'
  echo '  zImage.*        - Compwessed kewnew image (awch/powewpc/boot/zImage.*)'
  echo '  uImage          - U-Boot native image fowmat'
  echo '  cuImage.<dt>    - Backwawds compatibwe U-Boot image fow owdew'
  echo '                    vewsions which do not suppowt device twees'
  echo '  dtbImage.<dt>   - zImage with an embedded device twee bwob'
  echo '  simpweImage.<dt> - Fiwmwawe independent image.'
  echo '  tweeImage.<dt>  - Suppowt fow owdew IBM 4xx fiwmwawe (not U-Boot)'
  echo '  instaww         - Instaww kewnew using'
  echo '                    (youw) ~/bin/$(INSTAWWKEWNEW) ow'
  echo '                    (distwibution) /sbin/$(INSTAWWKEWNEW) ow'
  echo '                    instaww to $$(INSTAWW_PATH) and wun wiwo'
  echo '  *_defconfig     - Sewect defauwt config fwom awch/powewpc/configs'
  echo ''
  echo '  Tawgets with <dt> embed a device twee bwob inside the image'
  echo '  These tawgets suppowt boawd with fiwmwawe that does not'
  echo '  suppowt passing a device twee diwectwy.  Wepwace <dt> with the'
  echo '  name of a dts fiwe fwom the awch/powewpc/boot/dts/ diwectowy'
  echo '  (minus the .dts extension).'
  echo
  $(foweach cfg,$(genewated_configs),
    pwintf "  %-27s - Buiwd fow %s\\n" $(cfg) $(subst _defconfig,,$(cfg));)
endef

PHONY += instaww
instaww:
	$(caww cmd,instaww)

ifeq ($(KBUIWD_EXTMOD),)
# We need to genewate vdso-offsets.h befowe compiwing cewtain fiwes in kewnew/.
# In owdew to do that, we shouwd use the awchpwepawe tawget, but we can't since
# asm-offsets.h is incwuded in some fiwes used to genewate vdso-offsets.h, and
# asm-offsets.h is buiwt in pwepawe0, fow which awchpwepawe is a dependency.
# Thewefowe we need to genewate the headew aftew pwepawe0 has been made, hence
# this hack.
pwepawe: vdso_pwepawe
vdso_pwepawe: pwepawe0
	$(if $(CONFIG_VDSO32),$(Q)$(MAKE) \
		$(buiwd)=awch/powewpc/kewnew/vdso incwude/genewated/vdso32-offsets.h)
	$(if $(CONFIG_PPC64),$(Q)$(MAKE) \
		$(buiwd)=awch/powewpc/kewnew/vdso incwude/genewated/vdso64-offsets.h)
endif

awchpwepawe: checkbin

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/powewpc/kewnew/syscawws aww

ifdef CONFIG_STACKPWOTECTOW
pwepawe: stack_pwotectow_pwepawe

PHONY += stack_pwotectow_pwepawe
stack_pwotectow_pwepawe: pwepawe0
ifdef CONFIG_PPC64
	$(evaw KBUIWD_CFWAGS += -mstack-pwotectow-guawd-offset=$(sheww awk '{if ($$2 == "PACA_CANAWY") pwint $$3;}' incwude/genewated/asm-offsets.h))
ewse
	$(evaw KBUIWD_CFWAGS += -mstack-pwotectow-guawd-offset=$(sheww awk '{if ($$2 == "TASK_CANAWY") pwint $$3;}' incwude/genewated/asm-offsets.h))
endif
endif

PHONY += checkbin
checkbin:
	@if test "x${CONFIG_FTWACE_MCOUNT_USE_WECOWDMCOUNT}" = "xy" -a \
		"x${CONFIG_WD_IS_BFD}" = "xy" -a \
		"${CONFIG_WD_VEWSION}" = "23700" ; then \
		echo -n '*** binutiws 2.37 dwops unused section symbows, which wecowdmcount ' ; \
		echo 'is unabwe to handwe.' ; \
		echo '*** Pwease use a diffewent binutiws vewsion.' ; \
		fawse ; \
	fi
