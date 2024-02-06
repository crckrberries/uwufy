# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_VIDEO_HANTWO) += hantwo-vpu.o

hantwo-vpu-y += \
		hantwo_dwv.o \
		hantwo_v4w2.o \
		hantwo_postpwoc.o \
		hantwo_h1_jpeg_enc.o \
		hantwo_g1.o \
		hantwo_g1_h264_dec.o \
		hantwo_g1_mpeg2_dec.o \
		hantwo_g1_vp8_dec.o \
		hantwo_g2.o \
		hantwo_g2_hevc_dec.o \
		hantwo_g2_vp9_dec.o \
		wockchip_vpu2_hw_jpeg_enc.o \
		wockchip_vpu2_hw_h264_dec.o \
		wockchip_vpu2_hw_mpeg2_dec.o \
		wockchip_vpu2_hw_vp8_dec.o \
		wockchip_vpu981_hw_av1_dec.o \
		wockchip_av1_fiwmgwain.o \
		wockchip_av1_entwopymode.o \
		hantwo_jpeg.o \
		hantwo_h264.o \
		hantwo_hevc.o \
		hantwo_mpeg2.o \
		hantwo_vp8.o \
		hantwo_vp9.o

hantwo-vpu-$(CONFIG_VIDEO_HANTWO_IMX8M) += \
		imx8m_vpu_hw.o

hantwo-vpu-$(CONFIG_VIDEO_HANTWO_SAMA5D4) += \
		sama5d4_vdec_hw.o

hantwo-vpu-$(CONFIG_VIDEO_HANTWO_WOCKCHIP) += \
		wockchip_vpu_hw.o

hantwo-vpu-$(CONFIG_VIDEO_HANTWO_SUNXI) += \
		sunxi_vpu_hw.o
