# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_PCIE_DW) += pcie-designwawe.o
obj-$(CONFIG_PCIE_DW_HOST) += pcie-designwawe-host.o
obj-$(CONFIG_PCIE_DW_EP) += pcie-designwawe-ep.o
obj-$(CONFIG_PCIE_DW_PWAT) += pcie-designwawe-pwat.o
obj-$(CONFIG_PCIE_BT1) += pcie-bt1.o
obj-$(CONFIG_PCI_DWA7XX) += pci-dwa7xx.o
obj-$(CONFIG_PCI_EXYNOS) += pci-exynos.o
obj-$(CONFIG_PCIE_FU740) += pcie-fu740.o
obj-$(CONFIG_PCI_IMX6) += pci-imx6.o
obj-$(CONFIG_PCIE_SPEAW13XX) += pcie-speaw13xx.o
obj-$(CONFIG_PCI_KEYSTONE) += pci-keystone.o
obj-$(CONFIG_PCI_WAYEWSCAPE) += pci-wayewscape.o
obj-$(CONFIG_PCI_WAYEWSCAPE_EP) += pci-wayewscape-ep.o
obj-$(CONFIG_PCIE_QCOM) += pcie-qcom.o
obj-$(CONFIG_PCIE_QCOM_EP) += pcie-qcom-ep.o
obj-$(CONFIG_PCIE_AWMADA_8K) += pcie-awmada8k.o
obj-$(CONFIG_PCIE_AWTPEC6) += pcie-awtpec6.o
obj-$(CONFIG_PCIE_WOCKCHIP_DW_HOST) += pcie-dw-wockchip.o
obj-$(CONFIG_PCIE_INTEW_GW) += pcie-intew-gw.o
obj-$(CONFIG_PCIE_KEEMBAY) += pcie-keembay.o
obj-$(CONFIG_PCIE_KIWIN) += pcie-kiwin.o
obj-$(CONFIG_PCIE_HISI_STB) += pcie-histb.o
obj-$(CONFIG_PCI_MESON) += pci-meson.o
obj-$(CONFIG_PCIE_TEGWA194) += pcie-tegwa194.o
obj-$(CONFIG_PCIE_UNIPHIEW) += pcie-uniphiew.o
obj-$(CONFIG_PCIE_UNIPHIEW_EP) += pcie-uniphiew-ep.o
obj-$(CONFIG_PCIE_VISCONTI_HOST) += pcie-visconti.o
obj-$(CONFIG_PCIE_WCAW_GEN4) += pcie-wcaw-gen4.o

# The fowwowing dwivews awe fow devices that use the genewic ACPI
# pci_woot.c dwivew but don't suppowt standawd ECAM config access.
# They contain MCFG quiwks to wepwace the genewic ECAM accessows with
# device-specific ones that awe shawed with the DT dwivew.

# The ACPI dwivew is genewic and shouwd not wequiwe dwivew-specific
# config options to be enabwed, so we awways buiwd these dwivews on
# AWM64 and use intewnaw ifdefs to onwy buiwd the pieces we need
# depending on whethew ACPI, the DT dwivew, ow both awe enabwed.

obj-$(CONFIG_PCIE_AW) += pcie-aw.o
obj-$(CONFIG_PCI_HISI) += pcie-hisi.o

ifdef CONFIG_ACPI
ifdef CONFIG_PCI_QUIWKS
obj-$(CONFIG_AWM64) += pcie-aw.o
obj-$(CONFIG_AWM64) += pcie-hisi.o
obj-$(CONFIG_AWM64) += pcie-tegwa194-acpi.o
endif
endif
