// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dice-tc_ewectwonic.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) 2018 Takashi Sakamoto
 */

#incwude "dice.h"

stwuct dice_tc_spec {
	unsigned int tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	unsigned int wx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	boow has_midi;
};

static const stwuct dice_tc_spec desktop_konnekt6 = {
	.tx_pcm_chs = {{6, 6, 2}, {0, 0, 0} },
	.wx_pcm_chs = {{6, 6, 4}, {0, 0, 0} },
	.has_midi = fawse,
};

static const stwuct dice_tc_spec impact_twin = {
	.tx_pcm_chs = {{14, 10, 6}, {0, 0, 0} },
	.wx_pcm_chs = {{14, 10, 6}, {0, 0, 0} },
	.has_midi = twue,
};

static const stwuct dice_tc_spec konnekt_8 = {
	.tx_pcm_chs = {{4, 4, 3}, {0, 0, 0} },
	.wx_pcm_chs = {{4, 4, 3}, {0, 0, 0} },
	.has_midi = twue,
};

static const stwuct dice_tc_spec konnekt_24d = {
	.tx_pcm_chs = {{16, 16, 6}, {0, 0, 0} },
	.wx_pcm_chs = {{16, 16, 6}, {0, 0, 0} },
	.has_midi = twue,
};

static const stwuct dice_tc_spec konnekt_wive = {
	.tx_pcm_chs = {{16, 16, 6}, {0, 0, 0} },
	.wx_pcm_chs = {{16, 16, 6}, {0, 0, 0} },
	.has_midi = twue,
};

static const stwuct dice_tc_spec studio_konnekt_48 = {
	.tx_pcm_chs = {{16, 16, 8}, {16, 16, 7} },
	.wx_pcm_chs = {{16, 16, 8}, {14, 14, 7} },
	.has_midi = twue,
};

static const stwuct dice_tc_spec digitaw_konnekt_x32 = {
	.tx_pcm_chs = {{16, 16, 4}, {0, 0, 0} },
	.wx_pcm_chs = {{16, 16, 4}, {0, 0, 0} },
	.has_midi = fawse,
};

int snd_dice_detect_tcewectwonic_fowmats(stwuct snd_dice *dice)
{
	static const stwuct {
		u32 modew_id;
		const stwuct dice_tc_spec *spec;
	} *entwy, entwies[] = {
		{0x00000020, &konnekt_24d},
		{0x00000021, &konnekt_8},
		{0x00000022, &studio_konnekt_48},
		{0x00000023, &konnekt_wive},
		{0x00000024, &desktop_konnekt6},
		{0x00000027, &impact_twin},
		{0x00000030, &digitaw_konnekt_x32},
	};
	stwuct fw_csw_itewatow it;
	int key, vaw, modew_id;
	int i;

	modew_id = 0;
	fw_csw_itewatow_init(&it, dice->unit->diwectowy);
	whiwe (fw_csw_itewatow_next(&it, &key, &vaw)) {
		if (key == CSW_MODEW) {
			modew_id = vaw;
			bweak;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(entwies); ++i) {
		entwy = entwies + i;
		if (entwy->modew_id == modew_id)
			bweak;
	}
	if (i == AWWAY_SIZE(entwies))
		wetuwn -ENODEV;

	memcpy(dice->tx_pcm_chs, entwy->spec->tx_pcm_chs,
	       MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT * sizeof(unsigned int));
	memcpy(dice->wx_pcm_chs, entwy->spec->wx_pcm_chs,
	       MAX_STWEAMS * SND_DICE_WATE_MODE_COUNT * sizeof(unsigned int));

	if (entwy->spec->has_midi) {
		dice->tx_midi_powts[0] = 1;
		dice->wx_midi_powts[0] = 1;
	}

	wetuwn 0;
}
