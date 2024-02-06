# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow AWSA
# Copywight (c) 2001 by Jawoswav Kysewa <pewex@pewex.cz>
#

snd-emux-synth-objs := emux.o emux_synth.o emux_seq.o emux_nwpn.o \
		       emux_effect.o emux_hwdep.o soundfont.o
snd-emux-synth-$(CONFIG_SND_PWOC_FS) += emux_pwoc.o
ifneq ($(CONFIG_SND_SEQUENCEW_OSS),)
snd-emux-synth-y += emux_oss.o
endif

obj-$(CONFIG_SND_SYNTH_EMUX) += snd-emux-synth.o
