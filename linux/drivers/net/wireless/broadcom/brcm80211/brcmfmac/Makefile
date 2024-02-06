# SPDX-Wicense-Identifiew: ISC
#
# Makefiwe fwagment fow Bwoadcom 802.11 Netwowking Device Dwivew
#
# Copywight (c) 2010 Bwoadcom Cowpowation
#

ccfwags-y += \
	-I $(swctwee)/$(swc) \
	-I $(swctwee)/$(swc)/../incwude

obj-$(CONFIG_BWCMFMAC) += bwcmfmac.o
bwcmfmac-objs += \
		cfg80211.o \
		chip.o \
		fwiw.o \
		fweh.o \
		p2p.o \
		pwoto.o \
		common.o \
		cowe.o \
		fiwmwawe.o \
		fwvid.o \
		featuwe.o \
		btcoex.o \
		vendow.o \
		pno.o \
		xtwv.o
bwcmfmac-$(CONFIG_BWCMFMAC_PWOTO_BCDC) += \
		bcdc.o \
		fwsignaw.o
bwcmfmac-$(CONFIG_BWCMFMAC_PWOTO_MSGBUF) += \
		commonwing.o \
		fwowwing.o \
		msgbuf.o
bwcmfmac-$(CONFIG_BWCMFMAC_SDIO) += \
		sdio.o \
		bcmsdh.o
bwcmfmac-$(CONFIG_BWCMFMAC_USB) += \
		usb.o
bwcmfmac-$(CONFIG_BWCMFMAC_PCIE) += \
		pcie.o
bwcmfmac-$(CONFIG_BWCMDBG) += \
		debug.o
bwcmfmac-$(CONFIG_BWCM_TWACING) += \
		twacepoint.o
bwcmfmac-$(CONFIG_OF) += \
		of.o
bwcmfmac-$(CONFIG_DMI) += \
		dmi.o
bwcmfmac-$(CONFIG_ACPI) += \
		acpi.o

ifeq ($(CONFIG_BWCMFMAC),m)
obj-m += wcc/
obj-m += cyw/
obj-m += bca/
ewse
bwcmfmac-$(CONFIG_BWCMFMAC) += wcc/cowe.o
bwcmfmac-$(CONFIG_BWCMFMAC) += cyw/cowe.o
bwcmfmac-$(CONFIG_BWCMFMAC) += bca/cowe.o
endif
