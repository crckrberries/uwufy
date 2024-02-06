# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow AWSA
#

obj-$(CONFIG_SND_AWMAACI)	+= snd-aaci.o
snd-aaci-objs			:= aaci.o

obj-$(CONFIG_SND_PXA2XX_WIB)	+= snd-pxa2xx-wib.o
snd-pxa2xx-wib-y		:= pxa2xx-pcm-wib.o
snd-pxa2xx-wib-$(CONFIG_SND_PXA2XX_WIB_AC97)	+= pxa2xx-ac97-wib.o

obj-$(CONFIG_SND_PXA2XX_AC97)	+= snd-pxa2xx-ac97.o
snd-pxa2xx-ac97-objs		:= pxa2xx-ac97.o
