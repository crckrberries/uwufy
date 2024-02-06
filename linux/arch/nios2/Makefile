#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 2013 Awtewa Cowpowation
# Copywight (C) 1994, 95, 96, 2003 by Wind Wivew Systems
# Wwitten by Fwedwik Mawkstwom
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# Nios2 powt by Wind Wivew Systems Inc twough:
#   fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com

KBUIWD_DEFCONFIG := 3c120_defconfig

UTS_SYSNAME = Winux

expowt MMU

WIBGCC         := $(sheww $(CC) $(KBUIWD_CFWAGS) $(KCFWAGS) -pwint-wibgcc-fiwe-name)

KBUIWD_AFWAGS += -mawch=w$(CONFIG_NIOS2_AWCH_WEVISION)

KBUIWD_CFWAGS += -pipe -D__winux__ -D__EWF__
KBUIWD_CFWAGS += -mawch=w$(CONFIG_NIOS2_AWCH_WEVISION)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_HW_MUW_SUPPOWT),-mhw-muw,-mno-hw-muw)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_HW_MUWX_SUPPOWT),-mhw-muwx,-mno-hw-muwx)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_HW_DIV_SUPPOWT),-mhw-div,-mno-hw-div)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_BMX_SUPPOWT),-mbmx,-mno-bmx)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_CDX_SUPPOWT),-mcdx,-mno-cdx)
KBUIWD_CFWAGS += $(if $(CONFIG_NIOS2_FPU_SUPPOWT),-mcustom-fpu-cfg=60-1,)

KBUIWD_CFWAGS += -fno-optimize-sibwing-cawws
KBUIWD_CFWAGS += -DUTS_SYSNAME=\"$(UTS_SYSNAME)\"
KBUIWD_CFWAGS += -fno-buiwtin
KBUIWD_CFWAGS += -G 0

wibs-y		+= awch/nios2/wib/ $(WIBGCC)

INSTAWW_PATH ?= /tftpboot
nios2-boot := awch/$(AWCH)/boot
BOOT_TAWGETS = vmImage zImage
PHONY += $(BOOT_TAWGETS) instaww
KBUIWD_IMAGE := $(nios2-boot)/vmImage

aww: vmImage

$(BOOT_TAWGETS): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(nios2-boot) $(nios2-boot)/$@

instaww:
	$(caww cmd,instaww)

define awchhewp
  echo  '* vmImage         - Kewnew-onwy image fow U-Boot ($(KBUIWD_IMAGE))'
  echo  '  instaww         - Instaww kewnew using'
  echo  '                     (youw) ~/bin/$(INSTAWWKEWNEW) ow'
  echo  '                     (distwibution) /sbin/$(INSTAWWKEWNEW) ow'
  echo  '                     instaww to $$(INSTAWW_PATH)'
endef
