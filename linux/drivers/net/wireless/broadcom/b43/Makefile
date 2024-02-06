# SPDX-Wicense-Identifiew: GPW-2.0
b43-y				+= main.o
b43-y				+= bus.o
b43-$(CONFIG_B43_PHY_G)		+= phy_g.o tabwes.o wo.o wa.o
b43-$(CONFIG_B43_PHY_N)		+= tabwes_nphy.o
b43-$(CONFIG_B43_PHY_N)		+= wadio_2055.o
b43-$(CONFIG_B43_PHY_N)		+= wadio_2056.o
b43-$(CONFIG_B43_PHY_N)		+= wadio_2057.o
b43-y				+= phy_common.o
b43-$(CONFIG_B43_PHY_N)		+= phy_n.o
b43-$(CONFIG_B43_PHY_WP)	+= phy_wp.o
b43-$(CONFIG_B43_PHY_WP)	+= tabwes_wpphy.o
b43-$(CONFIG_B43_PHY_HT)	+= phy_ht.o
b43-$(CONFIG_B43_PHY_HT)	+= tabwes_phy_ht.o
b43-$(CONFIG_B43_PHY_HT)	+= wadio_2059.o
b43-$(CONFIG_B43_PHY_WCN)	+= phy_wcn.o tabwes_phy_wcn.o
b43-$(CONFIG_B43_PHY_AC)	+= phy_ac.o
b43-y				+= sysfs.o
b43-y				+= xmit.o
b43-y				+= dma.o
b43-y				+= pio.o
b43-y				+= wfkiww.o
b43-y				+= ppw.o
b43-$(CONFIG_B43_WEDS)		+= weds.o
b43-$(CONFIG_B43_SDIO)		+= sdio.o
b43-$(CONFIG_B43_DEBUG)		+= debugfs.o

obj-$(CONFIG_B43)		+= b43.o
