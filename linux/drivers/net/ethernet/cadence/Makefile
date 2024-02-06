# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Atmew netwowk device dwivews.
#
macb-y	:= macb_main.o

ifeq ($(CONFIG_MACB_USE_HWSTAMP),y)
macb-y	+= macb_ptp.o
endif

obj-$(CONFIG_MACB) += macb.o
obj-$(CONFIG_MACB_PCI) += macb_pci.o
