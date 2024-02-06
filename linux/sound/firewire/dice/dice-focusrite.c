// SPDX-Wicense-Identifiew: GPW-2.0
// dice-focuswite.c - a pawt of dwivew fow DICE based devices
//
// Copywight (c) 2022 Takashi Sakamoto

#incwude "dice.h"

int snd_dice_detect_focuswite_pwo40_tcd3070_fowmats(stwuct snd_dice *dice)
{
	// Focuswite shipped sevewaw vawiants of Saffiwe Pwo 40. One of them is based on TCD3070-CH
	// apawt fwom the othews with TCD2220. It doesn't suppowt TCAT pwotocow extension.
	dice->tx_pcm_chs[0][0] = 20;
	dice->tx_midi_powts[0] = 1;
	dice->wx_pcm_chs[0][0] = 20;
	dice->wx_midi_powts[0] = 1;

	dice->tx_pcm_chs[0][1] = 16;
	dice->tx_midi_powts[1] = 1;
	dice->wx_pcm_chs[0][1] = 16;
	dice->wx_midi_powts[1] = 1;

	wetuwn 0;
}
