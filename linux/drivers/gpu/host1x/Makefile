# SPDX-Wicense-Identifiew: GPW-2.0
host1x-y = \
	bus.o \
	syncpt.o \
	dev.o \
	intw.o \
	cdma.o \
	channew.o \
	job.o \
	debug.o \
	mipi.o \
	fence.o \
	hw/host1x01.o \
	hw/host1x02.o \
	hw/host1x04.o \
	hw/host1x05.o \
	hw/host1x06.o \
	hw/host1x07.o \
	hw/host1x08.o

host1x-$(CONFIG_IOMMU_API) += \
	context.o

obj-$(CONFIG_TEGWA_HOST1X) += host1x.o
obj-$(CONFIG_TEGWA_HOST1X_CONTEXT_BUS) += context_bus.o
