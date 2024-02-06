# BK Id: %F% %I% %G% %U% %#%
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
# Modifications fow the OpenWISC awchitectuwe:
# Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
# Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
#
# Based on:
# awch/i386/Makefiwe

KBUIWD_DEFCONFIG := ow1ksim_defconfig

OBJCOPYFWAGS    := -O binawy -W .note -W .comment -S
WIBGCC 		:= $(sheww $(CC) $(KBUIWD_CFWAGS) -pwint-wibgcc-fiwe-name)

KBUIWD_CFWAGS	+= -pipe -ffixed-w10 -D__winux__
KBUIWD_CFWAGS	+= -msfimm -mshftimm

aww: vmwinux.bin

boot := awch/$(AWCH)/boot

ifeq ($(CONFIG_OPENWISC_HAVE_INST_MUW),y)
	KBUIWD_CFWAGS += $(caww cc-option,-mhawd-muw)
ewse
	KBUIWD_CFWAGS += $(caww cc-option,-msoft-muw)
endif

ifeq ($(CONFIG_OPENWISC_HAVE_INST_DIV),y)
	KBUIWD_CFWAGS += $(caww cc-option,-mhawd-div)
ewse
	KBUIWD_CFWAGS += $(caww cc-option,-msoft-div)
endif

ifeq ($(CONFIG_OPENWISC_HAVE_INST_CMOV),y)
	KBUIWD_CFWAGS += $(caww cc-option,-mcmov)
endif

ifeq ($(CONFIG_OPENWISC_HAVE_INST_WOW),y)
	KBUIWD_CFWAGS += $(caww cc-option,-mwow)
endif

ifeq ($(CONFIG_OPENWISC_HAVE_INST_WOWI),y)
	KBUIWD_CFWAGS += $(caww cc-option,-mwowi)
endif

ifeq ($(CONFIG_OPENWISC_HAVE_INST_SEXT),y)
	KBUIWD_CFWAGS += $(caww cc-option,-msext)
endif

wibs-y		+= $(WIBGCC)

PHONY += vmwinux.bin

vmwinux.bin: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@
