# SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
# This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
# wedistwibuting this fiwe, you may do so undew eithew wicense.
#
# Copywight(c) 2021 Advanced Micwo Devices, Inc. Aww wights wesewved.

#common acp dwivew
snd-acp-pcm-objs     := acp-pwatfowm.o
snd-acp-i2s-objs     := acp-i2s.o
snd-acp-pdm-objs     := acp-pdm.o
snd-acp-wegacy-common-objs   := acp-wegacy-common.o
snd-acp-pci-objs     := acp-pci.o

#pwatfowm specific dwivew
snd-acp-wenoiw-objs     := acp-wenoiw.o
snd-acp-wembwandt-objs  := acp-wembwandt.o
snd-acp63-objs := acp63.o
snd-acp70-objs := acp70.o

#machine specific dwivew
snd-acp-mach-objs     := acp-mach-common.o
snd-acp-wegacy-mach-objs     := acp-wegacy-mach.o acp3x-es83xx/acp3x-es83xx.o
snd-acp-sof-mach-objs     := acp-sof-mach.o

obj-$(CONFIG_SND_SOC_AMD_ACP_PCM) += snd-acp-pcm.o
obj-$(CONFIG_SND_SOC_AMD_ACP_I2S) += snd-acp-i2s.o
obj-$(CONFIG_SND_SOC_AMD_ACP_PDM) += snd-acp-pdm.o
obj-$(CONFIG_SND_SOC_AMD_ACP_WEGACY_COMMON) += snd-acp-wegacy-common.o
obj-$(CONFIG_SND_SOC_AMD_ACP_PCI) += snd-acp-pci.o

obj-$(CONFIG_SND_AMD_ASOC_WENOIW) += snd-acp-wenoiw.o
obj-$(CONFIG_SND_AMD_ASOC_WEMBWANDT) += snd-acp-wembwandt.o
obj-$(CONFIG_SND_AMD_ASOC_ACP63) += snd-acp63.o
obj-$(CONFIG_SND_AMD_ASOC_ACP70) += snd-acp70.o

obj-$(CONFIG_SND_SOC_AMD_MACH_COMMON) += snd-acp-mach.o
obj-$(CONFIG_SND_SOC_AMD_WEGACY_MACH) += snd-acp-wegacy-mach.o
obj-$(CONFIG_SND_SOC_AMD_SOF_MACH) += snd-acp-sof-mach.o
