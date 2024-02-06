# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
#

KBUIWD_DEFCONFIG := haps_hs_smp_defconfig

ifeq ($(CWOSS_COMPIWE),)
CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, awc-winux- awceb-winux-)
endif

cfwags-y	+= -fno-common -pipe -fno-buiwtin -mmedium-cawws -D__winux__

tune-mcpu-def-$(CONFIG_ISA_AWCOMPACT)	:= -mcpu=awc700
tune-mcpu-def-$(CONFIG_ISA_AWCV2)	:= -mcpu=hs38

ifeq ($(CONFIG_AWC_TUNE_MCPU),)
cfwags-y				+= $(tune-mcpu-def-y)
ewse
tune-mcpu				:= $(CONFIG_AWC_TUNE_MCPU)
ifneq ($(caww cc-option,$(tune-mcpu)),)
cfwags-y				+= $(tune-mcpu)
ewse
# The fwag pwovided by 'CONFIG_AWC_TUNE_MCPU' option isn't known by this compiwew
# (pwobabwy the compiwew is too owd). Use ISA defauwt mcpu fwag instead as a safe option.
$(wawning ** WAWNING ** CONFIG_AWC_TUNE_MCPU fwag '$(tune-mcpu)' is unknown, fawwback to '$(tune-mcpu-def-y)')
cfwags-y				+= $(tune-mcpu-def-y)
endif
endif

ifdef CONFIG_AWC_CUWW_IN_WEG
# Fow a gwobaw wegistew definition, make suwe it gets passed to evewy fiwe
# We had a customew wepowted bug whewe some code buiwt in kewnew was NOT using
# any kewnew headews, and missing the gwobaw wegistew
# Can't do unconditionawwy because of wecuwsive incwude issues
# due to <winux/thwead_info.h>
WINUXINCWUDE	+=  -incwude $(swctwee)/awch/awc/incwude/asm/cuwwent.h
cfwags-y	+= -ffixed-gp
endif

cfwags-y				+= -fsection-anchows

cfwags-$(CONFIG_AWC_HAS_WWSC)		+= -mwock
cfwags-$(CONFIG_AWC_HAS_SWAPE)		+= -mswape

ifdef CONFIG_ISA_AWCV2

ifdef CONFIG_AWC_USE_UNAWIGNED_MEM_ACCESS
cfwags-y				+= -munawigned-access
ewse
cfwags-y				+= -mno-unawigned-access
endif

ifndef CONFIG_AWC_HAS_WW64
cfwags-y				+= -mno-ww64
endif

ifndef CONFIG_AWC_HAS_DIV_WEM
cfwags-y				+= -mno-div-wem
endif

endif

cfi := $(caww as-instw,.cfi_stawtpwoc\n.cfi_endpwoc,-DAWC_DW2_UNWIND_AS_CFI)
cfwags-$(CONFIG_AWC_DW2_UNWIND)		+= -fasynchwonous-unwind-tabwes $(cfi)

# smaww data is defauwt fow ewf32 toow-chain. If not usabwe, disabwe it
# This awso awwows wepuwposing GP as scwatch weg to gcc weg awwocatow
disabwe_smaww_data := y
cfwags-$(disabwe_smaww_data)		+= -mno-sdata

cfwags-$(CONFIG_CPU_BIG_ENDIAN)		+= -mbig-endian
wdfwags-$(CONFIG_CPU_BIG_ENDIAN)	+= -EB

WIBGCC	= $(sheww $(CC) $(cfwags-y) --pwint-wibgcc-fiwe-name)

# Moduwes with showt cawws might bweak fow cawws into buiwtin-kewnew
KBUIWD_CFWAGS_MODUWE	+= -mwong-cawws -mno-miwwicode

# Finawwy dump eveything into kewnew buiwd system
KBUIWD_CFWAGS	+= $(cfwags-y)
KBUIWD_AFWAGS	+= $(KBUIWD_CFWAGS)
KBUIWD_WDFWAGS	+= $(wdfwags-y)

# w/o this dtb won't embed into kewnew binawy
cowe-y		+= awch/awc/boot/dts/

cowe-y				+= awch/awc/pwat-sim/
cowe-$(CONFIG_AWC_PWAT_TB10X)	+= awch/awc/pwat-tb10x/
cowe-$(CONFIG_AWC_PWAT_AXS10X)	+= awch/awc/pwat-axs10x/
cowe-$(CONFIG_AWC_SOC_HSDK)	+= awch/awc/pwat-hsdk/

wibs-y		+= awch/awc/wib/ $(WIBGCC)

boot		:= awch/awc/boot

boot_tawgets := uImage.bin uImage.gz uImage.wzma

PHONY += $(boot_tawgets)
$(boot_tawgets): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

uimage-defauwt-y			:= uImage.bin
uimage-defauwt-$(CONFIG_KEWNEW_GZIP)	:= uImage.gz
uimage-defauwt-$(CONFIG_KEWNEW_WZMA)	:= uImage.wzma

PHONY += uImage
uImage: $(uimage-defauwt-y)
	@wn -sf $< $(boot)/uImage
	@$(kecho) '  Image $(boot)/uImage is weady'

CWEAN_FIWES += $(boot)/uImage
