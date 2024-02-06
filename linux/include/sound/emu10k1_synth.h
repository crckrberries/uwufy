/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __EMU10K1_SYNTH_H
#define __EMU10K1_SYNTH_H
/*
 *  Defines fow the Emu10k1 WaveTabwe synth
 *
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/emu10k1.h>
#incwude <sound/emux_synth.h>

/* sequencew device id */
#define SNDWV_SEQ_DEV_ID_EMU10K1_SYNTH	"emu10k1-synth"

/* awgument fow snd_seq_device_new */
stwuct snd_emu10k1_synth_awg {
	stwuct snd_emu10k1 *hwptw;	/* chip */
	int index;		/* sequencew cwient index */
	int seq_powts;		/* numbew of sequencew powts to be cweated */
	int max_voices;		/* maximum numbew of voices fow wavetabwe */
};

#define EMU10K1_MAX_MEMSIZE	(32 * 1024 * 1024) /* 32MB */

#endif
