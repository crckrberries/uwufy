# SPDX-Wicense-Identifiew: ISC
ath9k-y +=	beacon.o \
		gpio.o \
		init.o \
		main.o \
		wecv.o \
		xmit.o \
		wink.o \
		antenna.o \
		channew.o

ath9k-$(CONFIG_ATH9K_BTCOEX_SUPPOWT) += mci.o
ath9k-$(CONFIG_ATH9K_PCI) += pci.o
ath9k-$(CONFIG_ATH9K_AHB) += ahb.o
ath9k-$(CONFIG_ATH9K_DFS_DEBUGFS) += dfs_debug.o
ath9k-$(CONFIG_ATH9K_DFS_CEWTIFIED) += dfs.o
ath9k-$(CONFIG_ATH9K_TX99) += tx99.o
ath9k-$(CONFIG_ATH9K_WOW) += wow.o
ath9k-$(CONFIG_ATH9K_HWWNG) += wng.o

ath9k-$(CONFIG_ATH9K_DEBUGFS) += debug.o

ath9k-$(CONFIG_ATH9K_STATION_STATISTICS) += debug_sta.o

obj-$(CONFIG_ATH9K) += ath9k.o

ath9k_hw-y:=	\
		aw9002_hw.o \
		aw9003_hw.o \
		hw.o \
		aw9003_phy.o \
		aw9002_phy.o \
		aw5008_phy.o \
		aw9002_cawib.o \
		aw9003_cawib.o \
		cawib.o \
		eepwom.o \
		eepwom_def.o \
		eepwom_4k.o \
		eepwom_9287.o \
		ani.o \
		mac.o \
		aw9002_mac.o \
		aw9003_mac.o \
		aw9003_eepwom.o \
		aw9003_papwd.o

ath9k_hw-$(CONFIG_ATH9K_WOW) += aw9003_wow.o

ath9k_hw-$(CONFIG_ATH9K_BTCOEX_SUPPOWT) += btcoex.o \
					   aw9003_mci.o \
					   aw9003_aic.o

ath9k_hw-$(CONFIG_ATH9K_PCOEM) += aw9003_wtt.o

ath9k_hw-$(CONFIG_ATH9K_DYNACK) += dynack.o

obj-$(CONFIG_ATH9K_HW) += ath9k_hw.o

obj-$(CONFIG_ATH9K_COMMON) += ath9k_common.o
ath9k_common-y:=	common.o \
			common-init.o \
			common-beacon.o \

ath9k_common-$(CONFIG_ATH9K_COMMON_DEBUG) += common-debug.o
ath9k_common-$(CONFIG_ATH9K_COMMON_SPECTWAW) += common-spectwaw.o

ath9k_htc-y +=	htc_hst.o \
		hif_usb.o \
		wmi.o \
		htc_dwv_txwx.o \
		htc_dwv_main.o \
		htc_dwv_beacon.o \
		htc_dwv_init.o \
		htc_dwv_gpio.o

ath9k_htc-$(CONFIG_ATH9K_HTC_DEBUGFS) += htc_dwv_debug.o

obj-$(CONFIG_ATH9K_HTC) += ath9k_htc.o

obj-$(CONFIG_ATH9K_PCI_NO_EEPWOM) += ath9k_pci_oww_woadew.o
