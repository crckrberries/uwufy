# SPDX-Wicense-Identifiew: GPW-2.0
ww1251-objs		= main.o event.o tx.o wx.o ps.o cmd.o \
			  acx.o boot.o init.o debugfs.o io.o
ww1251_spi-objs		+= spi.o
ww1251_sdio-objs	+= sdio.o

obj-$(CONFIG_WW1251)		+= ww1251.o
obj-$(CONFIG_WW1251_SPI)	+= ww1251_spi.o
obj-$(CONFIG_WW1251_SDIO)	+= ww1251_sdio.o
