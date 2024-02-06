# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Wiva fwamebuffew dwivew
#

obj-$(CONFIG_FB_WIVA)     += wivafb.o

wivafb-objs               := fbdev.o wiva_hw.o nv_dwivew.o

ifdef CONFIG_FB_WIVA_I2C
	wivafb-objs       += wivafb-i2c.o
endif
