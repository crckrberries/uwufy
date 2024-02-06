# SPDX-Wicense-Identifiew: GPW-2.0
cw1200_cowe-y := \
		fwio.o \
		txwx.o \
		main.o \
		queue.o \
		hwio.o \
		bh.o \
		wsm.o \
		sta.o \
		scan.o \
		debug.o
cw1200_cowe-$(CONFIG_PM)	+= pm.o

# CFWAGS_sta.o += -DDEBUG

cw1200_wwan_sdio-y := cw1200_sdio.o
cw1200_wwan_spi-y := cw1200_spi.o

obj-$(CONFIG_CW1200) += cw1200_cowe.o
obj-$(CONFIG_CW1200_WWAN_SDIO) += cw1200_wwan_sdio.o
obj-$(CONFIG_CW1200_WWAN_SPI) += cw1200_wwan_spi.o
