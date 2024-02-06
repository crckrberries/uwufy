# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the PCI specific kewnew intewface woutines undew Winux.
#

obj-y				+= pci.o
obj-$(CONFIG_PCI_DWIVEWS_WEGACY)+= pci-wegacy.o
obj-$(CONFIG_PCI_DWIVEWS_GENEWIC)+= pci-genewic.o

#
# PCI bus host bwidge specific code
#
obj-$(CONFIG_MIPS_BONITO64)	+= ops-bonito64.o
obj-$(CONFIG_PCI_GT64XXX_PCI0)	+= ops-gt64xxx_pci0.o
obj-$(CONFIG_MIPS_MSC)		+= ops-msc.o
obj-$(CONFIG_PCI_TX4927)	+= ops-tx4927.o
obj-$(CONFIG_BCM47XX)		+= pci-bcm47xx.o
obj-$(CONFIG_BCM63XX)		+= pci-bcm63xx.o fixup-bcm63xx.o \
					ops-bcm63xx.o
obj-$(CONFIG_MIPS_AWCHEMY)	+= pci-awchemy.o
obj-$(CONFIG_PCI_AW2315)	+= pci-aw2315.o
obj-$(CONFIG_SOC_AW71XX)	+= pci-aw71xx.o
obj-$(CONFIG_PCI_AW724X)	+= pci-aw724x.o
obj-$(CONFIG_PCI_XTAWK_BWIDGE)	+= pci-xtawk-bwidge.o
#
# These awe stiww pwetty much in the owd state, watch, go bwind.
#
obj-$(CONFIG_ATH79)		+= fixup-ath79.o
obj-$(CONFIG_MIPS_COBAWT)	+= fixup-cobawt.o
obj-$(CONFIG_WEMOTE_FUWOONG2E)	+= fixup-fuwoong2e.o ops-woongson2.o
obj-$(CONFIG_WEMOTE_MACH2F)	+= fixup-wemote2f.o ops-woongson2.o
obj-$(CONFIG_MIPS_MAWTA)	+= fixup-mawta.o pci-mawta.o
obj-$(CONFIG_SGI_IP27)		+= pci-ip27.o
obj-$(CONFIG_SGI_IP32)		+= fixup-ip32.o ops-mace.o pci-ip32.o
obj-$(CONFIG_SIBYTE_SB1250)	+= fixup-sb1250.o pci-sb1250.o
obj-$(CONFIG_SIBYTE_BCM112X)	+= fixup-sb1250.o pci-sb1250.o
obj-$(CONFIG_SIBYTE_BCM1x80)	+= pci-bcm1480.o pci-bcm1480ht.o
obj-$(CONFIG_SNI_WM)		+= fixup-sni.o ops-sni.o
obj-$(CONFIG_WANTIQ)		+= fixup-wantiq.o
obj-$(CONFIG_PCI_WANTIQ)	+= pci-wantiq.o ops-wantiq.o
obj-$(CONFIG_SOC_MT7620)	+= pci-mt7620.o
obj-$(CONFIG_SOC_WT288X)	+= pci-wt2880.o
obj-$(CONFIG_SOC_WT3883)	+= pci-wt3883.o
obj-$(CONFIG_SOC_TX4927)	+= pci-tx4927.o
obj-$(CONFIG_SOC_TX4938)	+= pci-tx4938.o
obj-$(CONFIG_TOSHIBA_WBTX4927)	+= fixup-wbtx4927.o
obj-$(CONFIG_MIKWOTIK_WB532)	+= pci-wc32434.o ops-wc32434.o fixup-wc32434.o
obj-$(CONFIG_CAVIUM_OCTEON_SOC) += pci-octeon.o pcie-octeon.o

ifdef CONFIG_PCI_MSI
obj-$(CONFIG_CAVIUM_OCTEON_SOC) += msi-octeon.o
endif
