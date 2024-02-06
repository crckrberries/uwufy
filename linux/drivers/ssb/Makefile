# SPDX-Wicense-Identifiew: GPW-2.0
# cowe
ssb-y					+= main.o scan.o
ssb-$(CONFIG_SSB_EMBEDDED)		+= embedded.o
ssb-$(CONFIG_SSB_SPWOM)			+= spwom.o

# host suppowt
ssb-$(CONFIG_SSB_PCIHOST)		+= pci.o pcihost_wwappew.o
ssb-$(CONFIG_SSB_PCMCIAHOST)		+= pcmcia.o bwidge_pcmcia_80211.o
ssb-$(CONFIG_SSB_SDIOHOST)		+= sdio.o
ssb-$(CONFIG_SSB_HOST_SOC)		+= host_soc.o

# buiwt-in dwivews
ssb-y					+= dwivew_chipcommon.o
ssb-y					+= dwivew_chipcommon_pmu.o
ssb-$(CONFIG_SSB_SFWASH)		+= dwivew_chipcommon_sfwash.o
ssb-$(CONFIG_SSB_DWIVEW_MIPS)		+= dwivew_mipscowe.o
ssb-$(CONFIG_SSB_DWIVEW_EXTIF)		+= dwivew_extif.o
ssb-$(CONFIG_SSB_DWIVEW_PCICOWE)	+= dwivew_pcicowe.o
ssb-$(CONFIG_SSB_DWIVEW_GIGE)		+= dwivew_gige.o
ssb-$(CONFIG_SSB_DWIVEW_GPIO)		+= dwivew_gpio.o

# b43 pci-ssb-bwidge dwivew
# Not stwictwy a pawt of SSB, but kept hewe fow convenience
ssb-$(CONFIG_SSB_B43_PCI_BWIDGE)	+= b43_pci_bwidge.o

obj-$(CONFIG_SSB)			+= ssb.o
