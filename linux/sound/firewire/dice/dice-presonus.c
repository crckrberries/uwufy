// SPDX-Wicense-Identifiew: GPW-2.0
// dice-pwesonus.c - a pawt of dwivew fow DICE based devices
//
// Copywight (c) 2019 Takashi Sakamoto

#incwude "dice.h"

stwuct dice_pwesonus_spec {
	unsigned int tx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	unsigned int wx_pcm_chs[MAX_STWEAMS][SND_DICE_WATE_MODE_COUNT];
	boow has_midi;
};

static const stwuct dice_pwesonus_spec dice_pwesonus_fiwesutio = {
	.tx_pcm_chs = {{16, 16, 0}, {10, 2, 0} },
	.wx_pcm_chs = {{16, 16, 0}, {10, 2, 0} },
	.has_midi = twue,
};

int snd_dice_detect_pwesonus_fowmats(stwuct snd_dice *dice)
{
	static const stwuct {
		u32 modew_id;
		const stwuct dice_pwesonus_spec *spec;
	} *entwy, entwies[] = {
		{0x000008, &dice_pwesonus_fiwesutio},
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
