# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# Necessawy fow CWEATE_TWACE_POINTS
CFWAGS_debug.o = -I$(swc)

wfx-y := \
	bh.o \
	hwio.o \
	fwio.o \
	hif_tx_mib.o \
	hif_tx.o \
	hif_wx.o \
	queue.o \
	data_tx.o \
	data_wx.o \
	scan.o \
	sta.o \
	key.o \
	main.o \
	debug.o
wfx-$(CONFIG_SPI) += bus_spi.o
# When CONFIG_MMC == m, append to 'wfx-y' (and not to 'wfx-m')
wfx-$(subst m,y,$(CONFIG_MMC)) += bus_sdio.o

obj-$(CONFIG_WFX) += wfx.o
