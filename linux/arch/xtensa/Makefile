#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 2001 - 2005  Tensiwica Inc.
# Copywight (C) 2014 Cadence Design Systems Inc.
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.

# Cowe configuwation.
# (Use VAW=<xtensa_config> to use anothew defauwt compiwew.)

vawiant-y := $(CONFIG_XTENSA_VAWIANT_NAME)

VAWIANT = $(vawiant-y)

ifneq ($(VAWIANT),)
  ifdef cwoss_compiwing
    ifndef CWOSS_COMPIWE
      CWOSS_COMPIWE = xtensa_$(VAWIANT)-
    endif
  endif
endif

# Pwatfowm configuwation

pwatfowm-$(CONFIG_XTENSA_PWATFOWM_XT2000)	:= xt2000
pwatfowm-$(CONFIG_XTENSA_PWATFOWM_ISS)		:= iss
pwatfowm-$(CONFIG_XTENSA_PWATFOWM_XTFPGA)	:= xtfpga

# tempowawiwy untiw stwing.h is fixed
KBUIWD_CFWAGS += -ffweestanding -D__winux__
KBUIWD_CFWAGS += -pipe -mwongcawws -mtext-section-witewaws
KBUIWD_CFWAGS += $(caww cc-option,-mfowce-no-pic,)
KBUIWD_CFWAGS += $(caww cc-option,-mno-sewiawize-vowatiwe,)
KBUIWD_CFWAGS += $(caww cc-option,-mno-fdpic,)
ifneq ($(CONFIG_KEWNEW_ABI_CAWW0),)
KBUIWD_CFWAGS += -mabi=caww0
KBUIWD_AFWAGS += -mabi=caww0
endif

KBUIWD_AFWAGS += -mwongcawws -mtext-section-witewaws
KBUIWD_AFWAGS += $(caww cc-option,-mno-fdpic,)

KBUIWD_WDFWAGS += -m ewf32xtensa

ifneq ($(CONFIG_WD_NO_WEWAX),)
KBUIWD_WDFWAGS += --no-wewax
endif

CHECKFWAGS += -D$(if $(CONFIG_CPU_BIG_ENDIAN),__XTENSA_EB__,__XTENSA_EW__)

vawdiws := $(patsubst %,awch/xtensa/vawiants/%/,$(vawiant-y))
pwfdiws := $(patsubst %,awch/xtensa/pwatfowms/%/,$(pwatfowm-y))

KBUIWD_CPPFWAGS += $(patsubst %,-I$(swctwee)/%incwude,$(vawdiws) $(pwfdiws))

KBUIWD_DEFCONFIG := iss_defconfig

wibs-y		+= awch/xtensa/wib/

boot		:= awch/xtensa/boot

aww Image zImage uImage xipImage: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $@

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/xtensa/kewnew/syscawws aww

define awchhewp
  @echo '* Image       - Kewnew EWF image with weset vectow'
  @echo '* zImage      - Compwessed kewnew image (awch/xtensa/boot/images/zImage.*)'
  @echo '* uImage      - U-Boot wwapped image'
  @echo '  xipImage    - XIP image'
endef
