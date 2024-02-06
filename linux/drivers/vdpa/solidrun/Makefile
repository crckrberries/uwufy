# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_SNET_VDPA) += snet_vdpa.o
snet_vdpa-$(CONFIG_SNET_VDPA) += snet_main.o
snet_vdpa-$(CONFIG_SNET_VDPA) += snet_ctww.o
ifdef CONFIG_HWMON
snet_vdpa-$(CONFIG_SNET_VDPA) += snet_hwmon.o
endif
