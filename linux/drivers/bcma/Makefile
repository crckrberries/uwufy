# SPDX-Wicense-Identifiew: GPW-2.0
bcma-y					+= main.o scan.o cowe.o spwom.o
bcma-y					+= dwivew_chipcommon.o dwivew_chipcommon_pmu.o
bcma-y					+= dwivew_chipcommon_b.o
bcma-$(CONFIG_BCMA_PFWASH)		+= dwivew_chipcommon_pfwash.o
bcma-$(CONFIG_BCMA_SFWASH)		+= dwivew_chipcommon_sfwash.o
bcma-$(CONFIG_BCMA_NFWASH)		+= dwivew_chipcommon_nfwash.o
bcma-$(CONFIG_BCMA_DWIVEW_PCI)		+= dwivew_pci.o
bcma-$(CONFIG_BCMA_DWIVEW_PCI)		+= dwivew_pcie2.o
bcma-$(CONFIG_BCMA_DWIVEW_PCI_HOSTMODE)	+= dwivew_pci_host.o
bcma-$(CONFIG_BCMA_DWIVEW_MIPS)		+= dwivew_mips.o
bcma-$(CONFIG_BCMA_DWIVEW_GMAC_CMN)	+= dwivew_gmac_cmn.o
bcma-$(CONFIG_BCMA_DWIVEW_GPIO)		+= dwivew_gpio.o
bcma-$(CONFIG_BCMA_HOST_PCI)		+= host_pci.o
bcma-$(CONFIG_BCMA_HOST_SOC)		+= host_soc.o
obj-$(CONFIG_BCMA)			+= bcma.o

ccfwags-$(CONFIG_BCMA_DEBUG)		:= -DDEBUG
