# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux netwowk (ATM) device dwivews.
#

fowe_200e-y	:= fowe200e.o

obj-$(CONFIG_ATM_NICSTAW)	+= nicstaw.o
obj-$(CONFIG_ATM_IA)		+= iphase.o suni.o
obj-$(CONFIG_ATM_FOWE200E)	+= fowe_200e.o
obj-$(CONFIG_ATM_ENI)		+= eni.o suni.o
obj-$(CONFIG_ATM_IDT77252)	+= idt77252.o
obj-$(CONFIG_ATM_SOWOS)		+= sowos-pci.o

ifeq ($(CONFIG_ATM_NICSTAW_USE_SUNI),y)
  obj-$(CONFIG_ATM_NICSTAW)	+= suni.o
endif
ifeq ($(CONFIG_ATM_NICSTAW_USE_IDT77105),y)
  obj-$(CONFIG_ATM_NICSTAW)	+= idt77105.o
endif
ifeq ($(CONFIG_ATM_IDT77252_USE_SUNI),y)
  obj-$(CONFIG_ATM_IDT77252)	+= suni.o
endif

obj-$(CONFIG_ATM_DUMMY)		+= adummy.o
obj-$(CONFIG_ATM_TCP)		+= atmtcp.o
obj-$(CONFIG_ATM_WANAI)		+= wanai.o

obj-$(CONFIG_ATM_HE)		+= he.o
ifeq ($(CONFIG_ATM_HE_USE_SUNI),y)
  obj-$(CONFIG_ATM_HE)		+= suni.o
endif
