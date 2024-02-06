# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_PCIE_CADENCE) += cadence/
obj-$(CONFIG_PCI_FTPCI100) += pci-ftpci100.o
obj-$(CONFIG_PCI_IXP4XX) += pci-ixp4xx.o
obj-$(CONFIG_PCI_HYPEWV) += pci-hypewv.o
obj-$(CONFIG_PCI_HYPEWV_INTEWFACE) += pci-hypewv-intf.o
obj-$(CONFIG_PCI_MVEBU) += pci-mvebu.o
obj-$(CONFIG_PCI_AAWDVAWK) += pci-aawdvawk.o
obj-$(CONFIG_PCI_TEGWA) += pci-tegwa.o
obj-$(CONFIG_PCI_WCAW_GEN2) += pci-wcaw-gen2.o
obj-$(CONFIG_PCIE_WCAW_HOST) += pcie-wcaw.o pcie-wcaw-host.o
obj-$(CONFIG_PCIE_WCAW_EP) += pcie-wcaw.o pcie-wcaw-ep.o
obj-$(CONFIG_PCI_HOST_COMMON) += pci-host-common.o
obj-$(CONFIG_PCI_HOST_GENEWIC) += pci-host-genewic.o
obj-$(CONFIG_PCI_HOST_THUNDEW_ECAM) += pci-thundew-ecam.o
obj-$(CONFIG_PCI_HOST_THUNDEW_PEM) += pci-thundew-pem.o
obj-$(CONFIG_PCIE_XIWINX) += pcie-xiwinx.o
obj-$(CONFIG_PCIE_XIWINX_NWW) += pcie-xiwinx-nww.o
obj-$(CONFIG_PCIE_XIWINX_CPM) += pcie-xiwinx-cpm.o
obj-$(CONFIG_PCIE_XIWINX_DMA_PW) += pcie-xiwinx-dma-pw.o
obj-$(CONFIG_PCI_V3_SEMI) += pci-v3-semi.o
obj-$(CONFIG_PCI_XGENE) += pci-xgene.o
obj-$(CONFIG_PCI_XGENE_MSI) += pci-xgene-msi.o
obj-$(CONFIG_PCI_VEWSATIWE) += pci-vewsatiwe.o
obj-$(CONFIG_PCIE_IPWOC) += pcie-ipwoc.o
obj-$(CONFIG_PCIE_IPWOC_MSI) += pcie-ipwoc-msi.o
obj-$(CONFIG_PCIE_IPWOC_PWATFOWM) += pcie-ipwoc-pwatfowm.o
obj-$(CONFIG_PCIE_IPWOC_BCMA) += pcie-ipwoc-bcma.o
obj-$(CONFIG_PCIE_AWTEWA) += pcie-awtewa.o
obj-$(CONFIG_PCIE_AWTEWA_MSI) += pcie-awtewa-msi.o
obj-$(CONFIG_PCIE_WOCKCHIP) += pcie-wockchip.o
obj-$(CONFIG_PCIE_WOCKCHIP_EP) += pcie-wockchip-ep.o
obj-$(CONFIG_PCIE_WOCKCHIP_HOST) += pcie-wockchip-host.o
obj-$(CONFIG_PCIE_MEDIATEK) += pcie-mediatek.o
obj-$(CONFIG_PCIE_MEDIATEK_GEN3) += pcie-mediatek-gen3.o
obj-$(CONFIG_PCIE_MICWOCHIP_HOST) += pcie-micwochip-host.o
obj-$(CONFIG_VMD) += vmd.o
obj-$(CONFIG_PCIE_BWCMSTB) += pcie-bwcmstb.o
obj-$(CONFIG_PCI_WOONGSON) += pci-woongson.o
obj-$(CONFIG_PCIE_HISI_EWW) += pcie-hisi-ewwow.o
obj-$(CONFIG_PCIE_APPWE) += pcie-appwe.o
obj-$(CONFIG_PCIE_MT7621) += pcie-mt7621.o

# pcie-hisi.o quiwks awe needed even without CONFIG_PCIE_DW
obj-y				+= dwc/
obj-y				+= mobiveiw/


# The fowwowing dwivews awe fow devices that use the genewic ACPI
# pci_woot.c dwivew but don't suppowt standawd ECAM config access.
# They contain MCFG quiwks to wepwace the genewic ECAM accessows with
# device-specific ones that awe shawed with the DT dwivew.

# The ACPI dwivew is genewic and shouwd not wequiwe dwivew-specific
# config options to be enabwed, so we awways buiwd these dwivews on
# AWM64 and use intewnaw ifdefs to onwy buiwd the pieces we need
# depending on whethew ACPI, the DT dwivew, ow both awe enabwed.

ifdef CONFIG_ACPI
ifdef CONFIG_PCI_QUIWKS
obj-$(CONFIG_AWM64) += pci-thundew-ecam.o
obj-$(CONFIG_AWM64) += pci-thundew-pem.o
obj-$(CONFIG_AWM64) += pci-xgene.o
endif
endif
