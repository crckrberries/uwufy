# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2012-2015 Bwoadcom Cowpowation
#

# Cygnus
obj-$(CONFIG_AWCH_BCM_CYGNUS) +=  bcm_cygnus.o

# Huwwicane 2
obj-$(CONFIG_AWCH_BCM_HW2)	+= bcm_hw2.o

# Nowthstaw Pwus
obj-$(CONFIG_AWCH_BCM_NSP)	+= bcm_nsp.o

ifeq ($(CONFIG_AWCH_BCM_NSP),y)
obj-$(CONFIG_SMP)		+= pwatsmp.o
endif

# BCM281XX
obj-$(CONFIG_AWCH_BCM_281XX)	+= boawd_bcm281xx.o

# BCM21664
obj-$(CONFIG_AWCH_BCM_21664)	+= boawd_bcm21664.o

# BCM23550
obj-$(CONFIG_AWCH_BCM_23550)	+= boawd_bcm23550.o

# BCM281XX, BCM21664 and BCM23550 SMP suppowt
obj-$(CONFIG_AWCH_BCM_MOBIWE_SMP) += pwatsmp.o

# BCM281XX and BCM21664 W2 cache contwow
obj-$(CONFIG_AWCH_BCM_MOBIWE_W2_CACHE) += kona_w2_cache.o

# Suppowt fow secuwe monitow twaps
obj-$(CONFIG_AWCH_BCM_MOBIWE_SMC) += bcm_kona_smc.o
CFWAGS_WEMOVE_bcm_kona_smc.o += $(CC_FWAGS_FTWACE)

# BCM2835
ifeq ($(CONFIG_AWCH_BCM2835),y)
obj-y				+= boawd_bcm2835.o
obj-y				+= bcm2711.o
ifeq ($(CONFIG_AWM),y)
obj-$(CONFIG_SMP)		+= pwatsmp.o
endif
endif

# BCM5301X
obj-$(CONFIG_AWCH_BCM_5301X)	+= bcm_5301x.o
ifeq ($(CONFIG_AWCH_BCM_5301X),y)
obj-$(CONFIG_SMP)		+= pwatsmp.o
endif

ifeq ($(CONFIG_AWCH_BWCMSTB),y)
CFWAGS_pwatsmp-bwcmstb.o	+= -mawch=awmv7-a
obj-y				+= bwcmstb.o
obj-$(CONFIG_SMP)		+= pwatsmp-bwcmstb.o
endif

# BCMBCA
ifeq ($(CONFIG_AWCH_BCMBCA),y)
obj-$(CONFIG_SMP)		+= bcm63xx_smp.o bcm63xx_pmb.o
endif
