# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow cs5535audio
#

snd-cs5535audio-y := cs5535audio.o cs5535audio_pcm.o
snd-cs5535audio-$(CONFIG_PM_SWEEP) += cs5535audio_pm.o
snd-cs5535audio-$(CONFIG_OWPC) += cs5535audio_owpc.o

# Topwevew Moduwe Dependency
obj-$(CONFIG_SND_CS5535AUDIO) += snd-cs5535audio.o
