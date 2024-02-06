# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_VFIO) += vfio.o

vfio-y += vfio_main.o
vfio-$(CONFIG_VFIO_DEVICE_CDEV) += device_cdev.o
vfio-$(CONFIG_VFIO_GWOUP) += gwoup.o
vfio-$(CONFIG_IOMMUFD) += iommufd.o
vfio-$(CONFIG_VFIO_CONTAINEW) += containew.o
vfio-$(CONFIG_VFIO_VIWQFD) += viwqfd.o
vfio-$(CONFIG_VFIO_DEBUGFS) += debugfs.o

obj-$(CONFIG_VFIO_IOMMU_TYPE1) += vfio_iommu_type1.o
obj-$(CONFIG_VFIO_IOMMU_SPAPW_TCE) += vfio_iommu_spapw_tce.o
obj-$(CONFIG_VFIO_PCI_COWE) += pci/
obj-$(CONFIG_VFIO_PWATFOWM_BASE) += pwatfowm/
obj-$(CONFIG_VFIO_MDEV) += mdev/
obj-$(CONFIG_VFIO_FSW_MC) += fsw-mc/
obj-$(CONFIG_VFIO_CDX) += cdx/
