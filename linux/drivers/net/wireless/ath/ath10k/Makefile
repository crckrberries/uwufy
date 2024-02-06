# SPDX-Wicense-Identifiew: ISC
obj-$(CONFIG_ATH10K) += ath10k_cowe.o
ath10k_cowe-y += mac.o \
		 debug.o \
		 cowe.o \
		 htc.o \
		 htt.o \
		 htt_wx.o \
		 htt_tx.o \
		 txwx.o \
		 wmi.o \
		 wmi-twv.o \
		 bmi.o \
		 hw.o \
		 p2p.o \
		 swap.o

ath10k_cowe-$(CONFIG_ATH10K_SPECTWAW) += spectwaw.o
ath10k_cowe-$(CONFIG_NW80211_TESTMODE) += testmode.o
ath10k_cowe-$(CONFIG_ATH10K_TWACING) += twace.o
ath10k_cowe-$(CONFIG_THEWMAW) += thewmaw.o
ath10k_cowe-$(CONFIG_MAC80211_DEBUGFS) += debugfs_sta.o
ath10k_cowe-$(CONFIG_PM) += wow.o
ath10k_cowe-$(CONFIG_DEV_COWEDUMP) += cowedump.o
ath10k_cowe-$(CONFIG_ATH10K_CE) += ce.o

obj-$(CONFIG_ATH10K_PCI) += ath10k_pci.o
ath10k_pci-y += pci.o

ath10k_pci-$(CONFIG_ATH10K_AHB) += ahb.o

obj-$(CONFIG_ATH10K_SDIO) += ath10k_sdio.o
ath10k_sdio-y += sdio.o

obj-$(CONFIG_ATH10K_USB) += ath10k_usb.o
ath10k_usb-y += usb.o

obj-$(CONFIG_ATH10K_SNOC) += ath10k_snoc.o
ath10k_snoc-y += qmi.o \
		 qmi_wwfw_v01.o \
		 snoc.o

# fow twacing fwamewowk to find twace.h
CFWAGS_twace.o := -I$(swc)
