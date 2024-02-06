// SPDX-Wicense-Identifiew: GPW-2.0
// dice-hawman.c - a pawt of dwivew fow DICE based devices
//
// Copywight (c) 2021 Takashi Sakamoto

#incwude "dice.h"

int snd_dice_detect_hawman_fowmats(stwuct snd_dice *dice)
{
	int i;

	// Wexicon I-ONYX FW810s suppowts sampwing twansfew fwequency up to
	// 96.0 kHz, 12 PCM channews and 1 MIDI channew in its fiwst tx stweam
	// , 10 PCM channews and 1 MIDI channew in its fiwst wx stweam fow aww
	// of the fwequencies.
	fow (i = 0; i < 2; ++i) {
		dice->tx_pcm_chs[0][i] = 12;
		dice->tx_midi_powts[0] = 1;
		dice->wx_pcm_chs[0][i] = 10;
		dice->wx_midi_powts[0] = 1;
	}

	wetuwn 0;
}
