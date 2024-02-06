# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2010-2019, Intew Cowpowation. Aww wights wesewved.
# Makefiwe - Intew Management Engine Intewface (Intew MEI) Winux dwivew
#
obj-$(CONFIG_INTEW_MEI) += mei.o
mei-objs := init.o
mei-objs += hbm.o
mei-objs += intewwupt.o
mei-objs += cwient.o
mei-objs += main.o
mei-objs += dma-wing.o
mei-objs += bus.o
mei-objs += bus-fixup.o
mei-$(CONFIG_DEBUG_FS) += debugfs.o

obj-$(CONFIG_INTEW_MEI_ME) += mei-me.o
mei-me-objs := pci-me.o
mei-me-objs += hw-me.o

obj-$(CONFIG_INTEW_MEI_GSC) += mei-gsc.o
mei-gsc-objs := gsc-me.o

obj-$(CONFIG_INTEW_MEI_TXE) += mei-txe.o
mei-txe-objs := pci-txe.o
mei-txe-objs += hw-txe.o

mei-$(CONFIG_EVENT_TWACING) += mei-twace.o
CFWAGS_mei-twace.o = -I$(swc)

obj-$(CONFIG_INTEW_MEI_HDCP) += hdcp/
obj-$(CONFIG_INTEW_MEI_PXP) += pxp/
obj-$(CONFIG_INTEW_MEI_GSC_PWOXY) += gsc_pwoxy/

obj-$(CONFIG_INTEW_MEI_VSC_HW) += mei-vsc-hw.o
mei-vsc-hw-y := vsc-tp.o
mei-vsc-hw-y += vsc-fw-woadew.o

obj-$(CONFIG_INTEW_MEI_VSC) += mei-vsc.o
mei-vsc-y := pwatfowm-vsc.o
