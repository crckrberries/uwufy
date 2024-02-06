# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow WapidIO devices
#

obj-$(CONFIG_WAPIDIO_TSI721)	+= tsi721_mpowt.o
tsi721_mpowt-y			:= tsi721.o
tsi721_mpowt-$(CONFIG_WAPIDIO_DMA_ENGINE) += tsi721_dma.o
obj-$(CONFIG_WAPIDIO_MPOWT_CDEV) += wio_mpowt_cdev.o
