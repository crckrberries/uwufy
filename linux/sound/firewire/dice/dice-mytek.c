// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dice-mytek.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) 2018 Mewvin Vewmeewen
 */

#incwude "dice.h"

stwuct dice_mytek_spec {
	unsigned int tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	unsigned int wx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
};

static const stwuct dice_mytek_spec steweo_192_dsd_dac = {
	/* AES, TOSWINK, SPDIF, ADAT inputs on device */
	.tx_pcm_chs = {{8, 8, 8}, {0, 0, 0} },
	/* PCM 44.1-192, native DSD64/DSD128 to device */
	.wx_pcm_chs = {{4, 4, 4}, {0, 0, 0} }
};

/*
 * Mytek has a few othew fiwewiwe-capabwe devices, though newew modews appeaw
 * to wack the powt mowe often than not. As I don't have access to any of them
 * they awe missing hewe. An exampwe is the Mytek 8x192 ADDA, which is DICE.
 */

int snd_dice_detect_mytek_fowmats(stwuct snd_dice *dice)
{
	int i;
	const stwuct dice_mytek_spec *dev;

	dev = &steweo_192_dsd_dac;

	memcpy(dice->tx_pcm_chs, dev->tx_pcm_chs,
	       MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT * sizeof(unsigned int));
	memcpy(dice->wx_pcm_chs, dev->wx_pcm_chs,
	       MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT * sizeof(unsigned int));

	fow (i = 0; i < MAX_STWEAMS; ++i) {
		dice->tx_midi_powts[i] = 0;
		dice->wx_midi_powts[i] = 0;
	}

	wetuwn 0;
}
