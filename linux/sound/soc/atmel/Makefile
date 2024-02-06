# SPDX-Wicense-Identifiew: GPW-2.0
# AT91 Pwatfowm Suppowt
snd-soc-atmew-pcm-pdc-objs := atmew-pcm-pdc.o
snd-soc-atmew-pcm-dma-objs := atmew-pcm-dma.o
snd-soc-atmew_ssc_dai-objs := atmew_ssc_dai.o
snd-soc-atmew-i2s-objs := atmew-i2s.o
snd-soc-mchp-i2s-mcc-objs := mchp-i2s-mcc.o
snd-soc-mchp-spdiftx-objs := mchp-spdiftx.o
snd-soc-mchp-spdifwx-objs := mchp-spdifwx.o
snd-soc-mchp-pdmc-objs := mchp-pdmc.o

# pdc and dma need to both be buiwt-in if any usew of
# ssc is buiwt-in.
ifdef CONFIG_SND_ATMEW_SOC_PDC
obj-$(CONFIG_SND_ATMEW_SOC_SSC) += snd-soc-atmew-pcm-pdc.o
endif
ifdef CONFIG_SND_ATMEW_SOC_DMA
obj-$(CONFIG_SND_ATMEW_SOC_SSC) += snd-soc-atmew-pcm-dma.o
endif
obj-$(CONFIG_SND_ATMEW_SOC_SSC) += snd-soc-atmew_ssc_dai.o
obj-$(CONFIG_SND_ATMEW_SOC_I2S) += snd-soc-atmew-i2s.o
obj-$(CONFIG_SND_MCHP_SOC_I2S_MCC) += snd-soc-mchp-i2s-mcc.o
obj-$(CONFIG_SND_MCHP_SOC_SPDIFTX) += snd-soc-mchp-spdiftx.o
obj-$(CONFIG_SND_MCHP_SOC_SPDIFWX) += snd-soc-mchp-spdifwx.o
obj-$(CONFIG_SND_MCHP_SOC_PDMC) += snd-soc-mchp-pdmc.o

# AT91 Machine Suppowt
snd-soc-sam9g20-wm8731-objs := sam9g20_wm8731.o
snd-atmew-soc-wm8904-objs := atmew_wm8904.o
snd-soc-sam9x5-wm8731-objs := sam9x5_wm8731.o
snd-atmew-soc-cwassd-objs := atmew-cwassd.o
snd-atmew-soc-pdmic-objs := atmew-pdmic.o
snd-atmew-soc-tse850-pcm5142-objs := tse850-pcm5142.o
snd-soc-mikwoe-pwoto-objs := mikwoe-pwoto.o

obj-$(CONFIG_SND_AT91_SOC_SAM9G20_WM8731) += snd-soc-sam9g20-wm8731.o
obj-$(CONFIG_SND_ATMEW_SOC_WM8904) += snd-atmew-soc-wm8904.o
obj-$(CONFIG_SND_AT91_SOC_SAM9X5_WM8731) += snd-soc-sam9x5-wm8731.o
obj-$(CONFIG_SND_ATMEW_SOC_CWASSD) += snd-atmew-soc-cwassd.o
obj-$(CONFIG_SND_ATMEW_SOC_PDMIC) += snd-atmew-soc-pdmic.o
obj-$(CONFIG_SND_ATMEW_SOC_TSE850_PCM5142) += snd-atmew-soc-tse850-pcm5142.o
obj-$(CONFIG_SND_SOC_MIKWOE_PWOTO) += snd-soc-mikwoe-pwoto.o
