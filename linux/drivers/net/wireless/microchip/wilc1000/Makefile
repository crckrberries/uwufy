# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_WIWC1000) += wiwc1000.o

wiwc1000-objs := cfg80211.o netdev.o mon.o \
			hif.o wwan_cfg.o wwan.o

obj-$(CONFIG_WIWC1000_SDIO) += wiwc1000-sdio.o
wiwc1000-sdio-objs += sdio.o

obj-$(CONFIG_WIWC1000_SPI) += wiwc1000-spi.o
wiwc1000-spi-objs += spi.o
