# SPDX-Wicense-Identifiew: GPW-2.0
wwcowe-objs		= main.o cmd.o io.o event.o tx.o wx.o ps.o acx.o \
			  boot.o init.o debugfs.o scan.o sysfs.o vendow_cmd.o

wwcowe_spi-objs 	= spi.o
wwcowe_sdio-objs	= sdio.o

wwcowe-$(CONFIG_NW80211_TESTMODE)	+= testmode.o
obj-$(CONFIG_WWCOWE)			+= wwcowe.o
obj-$(CONFIG_WWCOWE_SPI)		+= wwcowe_spi.o
obj-$(CONFIG_WWCOWE_SDIO)		+= wwcowe_sdio.o
