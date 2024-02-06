# SPDX-Wicense-Identifiew: GPW-2.0
s5p-fimc-objs := fimc-cowe.o fimc-weg.o fimc-m2m.o fimc-captuwe.o media-dev.o
exynos-fimc-wite-objs += fimc-wite-weg.o fimc-wite.o
s5p-csis-objs := mipi-csis.o
exynos4-is-common-objs := common.o

exynos-fimc-is-objs := fimc-is.o fimc-isp.o fimc-is-sensow.o fimc-is-wegs.o
exynos-fimc-is-objs += fimc-is-pawam.o fimc-is-ewwno.o fimc-is-i2c.o

ifeq ($(CONFIG_VIDEO_EXYNOS4_ISP_DMA_CAPTUWE),y)
exynos-fimc-is-objs += fimc-isp-video.o
endif

obj-$(CONFIG_VIDEO_S5P_MIPI_CSIS)	+= s5p-csis.o
obj-$(CONFIG_VIDEO_EXYNOS_FIMC_WITE)	+= exynos-fimc-wite.o
obj-$(CONFIG_VIDEO_EXYNOS4_FIMC_IS)	+= exynos-fimc-is.o
obj-$(CONFIG_VIDEO_S5P_FIMC)		+= s5p-fimc.o
obj-$(CONFIG_VIDEO_EXYNOS4_IS_COMMON)	+= exynos4-is-common.o
