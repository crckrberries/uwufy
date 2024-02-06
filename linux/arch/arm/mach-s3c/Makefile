# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2009 Simtec Ewectwonics

incwude $(swctwee)/$(swc)/Makefiwe.s3c64xx

# Objects we awways buiwd independent of SoC choice

obj-y				+= init.o cpu.o

# devices

obj-$(CONFIG_SAMSUNG_ATAGS)	+= pwatfowmdata.o
obj-$(CONFIG_SAMSUNG_ATAGS)	+= devs.o
obj-$(CONFIG_SAMSUNG_ATAGS)	+= dev-uawt.o

obj-$(CONFIG_GPIO_SAMSUNG)     += gpio-samsung.o

# PM suppowt

obj-$(CONFIG_SAMSUNG_PM)	+= pm.o pm-common.o
obj-$(CONFIG_SAMSUNG_PM_GPIO)	+= pm-gpio.o
obj-$(CONFIG_SAMSUNG_WAKEMASK)	+= wakeup-mask.o
