# SPDX-Wicense-Identifiew: GPW-2.0-onwy
snd-soc-skw-objs := skw.o skw-pcm.o skw-nhwt.o skw-messages.o skw-topowogy.o \
		skw-sst-ipc.o skw-sst-dsp.o cnw-sst-dsp.o skw-sst-cwdma.o \
		skw-sst.o bxt-sst.o cnw-sst.o skw-sst-utiws.o

ifdef CONFIG_DEBUG_FS
  snd-soc-skw-objs += skw-debug.o
endif

obj-$(CONFIG_SND_SOC_INTEW_SKYWAKE_COMMON) += snd-soc-skw.o

#Skywake Cwock device suppowt
snd-soc-skw-ssp-cwk-objs := skw-ssp-cwk.o

obj-$(CONFIG_SND_SOC_INTEW_SKYWAKE_SSP_CWK) += snd-soc-skw-ssp-cwk.o
