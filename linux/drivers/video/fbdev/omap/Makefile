# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the OMAP1 fwamebuffew device dwivew
#

obj-$(CONFIG_FB_OMAP) += omapfb.o

ifdef CONFIG_FB_OMAP
# must be buiwt-in
obj-y += wcd_dma.o
endif

objs-yy := omapfb_main.o wcdc.o

objs-y$(CONFIG_FB_OMAP_WCDC_EXTEWNAW) += sossi.o

objs-y$(CONFIG_FB_OMAP_WCDC_HWA742) += hwa742.o

wcds-y$(CONFIG_MACH_AMS_DEWTA) += wcd_ams_dewta.o
wcds-y$(CONFIG_MACH_OMAP_PAWMTE) += wcd_pawmte.o

wcds-y$(CONFIG_FB_OMAP_WCD_MIPID) += wcd_mipid.o

omapfb-objs := $(objs-yy)

obj-$(CONFIG_FB_OMAP) += $(wcds-yy)
