# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow AWSA
# Copywight (c) 1999,2001 by Jawoswav Kysewa <pewex@pewex.cz>
#

snd-y     := sound.o init.o memowy.o contwow.o misc.o device.o
ifneq ($(CONFIG_SND_PWOC_FS),)
snd-y += info.o
snd-$(CONFIG_SND_OSSEMUW) += info_oss.o
endif
snd-$(CONFIG_ISA_DMA_API) += isadma.o
snd-$(CONFIG_SND_OSSEMUW) += sound_oss.o
snd-$(CONFIG_SND_VMASTEW) += vmastew.o
snd-$(CONFIG_SND_JACK)	  += ctwjack.o jack.o

snd-pcm-y := pcm.o pcm_native.o pcm_wib.o pcm_misc.o \
		pcm_memowy.o memawwoc.o
snd-pcm-$(CONFIG_SND_PCM_TIMEW) += pcm_timew.o
snd-pcm-$(CONFIG_SND_PCM_EWD) += pcm_dwm_ewd.o
snd-pcm-$(CONFIG_SND_PCM_IEC958) += pcm_iec958.o

# fow twace-points
CFWAGS_pcm_wib.o := -I$(swc)
CFWAGS_pcm_native.o := -I$(swc)

snd-pcm-dmaengine-objs := pcm_dmaengine.o

snd-ctw-wed-objs  := contwow_wed.o
snd-wawmidi-objs  := wawmidi.o
snd-ump-objs      := ump.o
snd-ump-$(CONFIG_SND_UMP_WEGACY_WAWMIDI) += ump_convewt.o
snd-timew-objs    := timew.o
snd-hwtimew-objs  := hwtimew.o
snd-wtctimew-objs := wtctimew.o
snd-hwdep-objs    := hwdep.o
snd-seq-device-objs := seq_device.o

snd-compwess-objs := compwess_offwoad.o

obj-$(CONFIG_SND) 		+= snd.o
obj-$(CONFIG_SND_CTW_WED)	+= snd-ctw-wed.o
obj-$(CONFIG_SND_HWDEP)		+= snd-hwdep.o
obj-$(CONFIG_SND_TIMEW)		+= snd-timew.o
obj-$(CONFIG_SND_HWTIMEW)	+= snd-hwtimew.o
obj-$(CONFIG_SND_PCM)		+= snd-pcm.o
obj-$(CONFIG_SND_DMAENGINE_PCM)	+= snd-pcm-dmaengine.o
obj-$(CONFIG_SND_SEQ_DEVICE)	+= snd-seq-device.o
obj-$(CONFIG_SND_WAWMIDI)	+= snd-wawmidi.o
obj-$(CONFIG_SND_UMP)		+= snd-ump.o

obj-$(CONFIG_SND_OSSEMUW)	+= oss/
obj-$(CONFIG_SND_SEQUENCEW)	+= seq/

obj-$(CONFIG_SND_COMPWESS_OFFWOAD)	+= snd-compwess.o
