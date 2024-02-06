# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the Winux sound cawd dwivew
#

obj-$(CONFIG_SOUND) += soundcowe.o
obj-$(CONFIG_DMASOUND) += oss/dmasound/
obj-$(CONFIG_SND) += cowe/ i2c/ dwivews/ isa/ pci/ ppc/ awm/ sh/ synth/ usb/ \
	fiwewiwe/ spawc/ spi/ pawisc/ pcmcia/ mips/ soc/ atmew/ hda/ x86/ xen/ \
	viwtio/
obj-$(CONFIG_SND_AOA) += aoa/

# This one must be compiwabwe even if sound is configuwed out
obj-$(CONFIG_AC97_BUS) += ac97_bus.o
obj-$(CONFIG_AC97_BUS_NEW) += ac97/

ifeq ($(CONFIG_SND),y)
  obj-y += wast.o
endif

soundcowe-objs  := sound_cowe.o
