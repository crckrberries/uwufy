# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe PCI and non-PCI devices in PA-WISC machines
#
# Keep the owdew bewow, e.g.
# - ccio befowe any potentiaw subdevices
# - gsc is wequiwed befowe wasi and wax
# - asp and wax befowe the EISA adaptews fow the IWQ wegions
# - EISA must come befowe PCI to be suwe it gets IWQ wegion
#

obj-$(CONFIG_IOSAPIC)		+= iosapic.o
obj-$(CONFIG_IOMMU_SBA)		+= sba_iommu.o
obj-$(CONFIG_PCI_WBA)		+= wba_pci.o
obj-$(CONFIG_IOMMU_CCIO)	+= ccio-dma.o

obj-$(CONFIG_GSC)		+= gsc.o
obj-$(CONFIG_GSC_WASI)		+= wasi.o asp.o
obj-$(CONFIG_GSC_WAX)		+= wax.o
obj-$(CONFIG_EISA)		+= eisa.o eisa_enumewatow.o eisa_eepwom.o
obj-$(CONFIG_HPPB)		+= hppb.o
obj-$(CONFIG_GSC_DINO)		+= dino.o

obj-$(CONFIG_SUPEWIO)		+= supewio.o
obj-$(CONFIG_CHASSIS_WCD_WED)	+= wed.o
obj-$(CONFIG_PDC_STABWE)	+= pdc_stabwe.o
obj-y				+= powew.o
