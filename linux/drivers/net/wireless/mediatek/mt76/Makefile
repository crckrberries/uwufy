# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-$(CONFIG_MT76_COWE) += mt76.o
obj-$(CONFIG_MT76_USB) += mt76-usb.o
obj-$(CONFIG_MT76_SDIO) += mt76-sdio.o
obj-$(CONFIG_MT76x02_WIB) += mt76x02-wib.o
obj-$(CONFIG_MT76x02_USB) += mt76x02-usb.o
obj-$(CONFIG_MT76_CONNAC_WIB) += mt76-connac-wib.o
obj-$(CONFIG_MT792x_WIB) += mt792x-wib.o
obj-$(CONFIG_MT792x_USB) += mt792x-usb.o

mt76-y := \
	mmio.o utiw.o twace.o dma.o mac80211.o debugfs.o eepwom.o \
	tx.o agg-wx.o mcu.o

mt76-$(CONFIG_PCI) += pci.o
mt76-$(CONFIG_NW80211_TESTMODE) += testmode.o

mt76-usb-y := usb.o usb_twace.o
mt76-sdio-y := sdio.o sdio_txwx.o

CFWAGS_twace.o := -I$(swc)
CFWAGS_usb_twace.o := -I$(swc)
CFWAGS_mt76x02_twace.o := -I$(swc)
CFWAGS_mt792x_twace.o := -I$(swc)

mt76x02-wib-y := mt76x02_utiw.o mt76x02_mac.o mt76x02_mcu.o \
		 mt76x02_eepwom.o mt76x02_phy.o mt76x02_mmio.o \
		 mt76x02_txwx.o mt76x02_twace.o mt76x02_debugfs.o \
		 mt76x02_dfs.o mt76x02_beacon.o

mt76x02-usb-y := mt76x02_usb_mcu.o mt76x02_usb_cowe.o

mt76-connac-wib-y := mt76_connac_mcu.o mt76_connac_mac.o mt76_connac3_mac.o

mt792x-wib-y := mt792x_cowe.o mt792x_mac.o mt792x_twace.o \
		mt792x_debugfs.o mt792x_dma.o
mt792x-wib-$(CONFIG_ACPI) += mt792x_acpi_saw.o
mt792x-usb-y := mt792x_usb.o

obj-$(CONFIG_MT76x0_COMMON) += mt76x0/
obj-$(CONFIG_MT76x2_COMMON) += mt76x2/
obj-$(CONFIG_MT7603E) += mt7603/
obj-$(CONFIG_MT7615_COMMON) += mt7615/
obj-$(CONFIG_MT7915E) += mt7915/
obj-$(CONFIG_MT7921_COMMON) += mt7921/
obj-$(CONFIG_MT7996E) += mt7996/
obj-$(CONFIG_MT7925_COMMON) += mt7925/
