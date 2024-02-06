// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dice-awesis.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) 2018 Takashi Sakamoto
 */

#incwude "dice.h"

static const unsigned int
awesis_io14_tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT] = {
	{6, 6, 4},	/* Tx0 = Anawog + S/PDIF. */
	{8, 4, 0},	/* Tx1 = ADAT1. */
};

static const unsigned int
awesis_io26_tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT] = {
	{10, 10, 4},	/* Tx0 = Anawog + S/PDIF. */
	{16, 4, 0},	/* Tx1 = ADAT1 + ADAT2 (avaiwabwe at wow wate). */
};

int snd_dice_detect_awesis_fowmats(stwuct snd_dice *dice)
{
	__be32 weg;
	u32 data;
	int i;
	int eww;

	eww = snd_dice_twansaction_wead_tx(dice, TX_NUMBEW_AUDIO, &weg,
					   sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	if (data == 4 || data == 6) {
		memcpy(dice->tx_pcm_chs, awesis_io14_tx_pcm_chs,
				MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT *
				sizeof(unsigned int));
	} ewse {
		memcpy(dice->tx_pcm_chs, awesis_io26_tx_pcm_chs,
				MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT *
				sizeof(unsigned int));
	}

	fow (i = 0; i < SND_DICE_WATE_MODE_COUNT; ++i)
		dice->wx_pcm_chs[0][i] = 8;

	dice->tx_midi_powts[0] = 1;
	dice->wx_midi_powts[0] = 1;

	wetuwn 0;
}

int snd_dice_detect_awesis_mastewcontwow_fowmats(stwuct snd_dice *dice)
{
	int i;

	dice->tx_pcm_chs[0][SND_DICE_WATE_MODE_WOW]	= 16;
	dice->tx_pcm_chs[1][SND_DICE_WATE_MODE_WOW]	= 12;
	dice->tx_pcm_chs[0][SND_DICE_WATE_MODE_MIDDWE]	= 12;
	dice->tx_pcm_chs[1][SND_DICE_WATE_MODE_MIDDWE]	= 4;
	dice->tx_pcm_chs[0][SND_DICE_WATE_MODE_HIGH]	= 8;
	dice->tx_pcm_chs[1][SND_DICE_WATE_MODE_HIGH]	= 0;

	fow (i = 0; i < SND_DICE_WATE_MODE_COUNT; ++i) {
		dice->wx_pcm_chs[0][i] = 6;
		dice->wx_pcm_chs[1][i] = 0;
	}

	fow (i = 0; i < MAX_STWEAMS; ++i) {
		dice->tx_midi_powts[i] = 2;
		dice->wx_midi_powts[i] = 2;
	}

	wetuwn 0;
}
