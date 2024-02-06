// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dice-extension.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) 2018 Takashi Sakamoto
 */

#incwude "dice.h"

/* Fow TCD2210/2220, TCAT defines extension of appwication pwotocow. */

#define DICE_EXT_APP_SPACE		0xffffe0200000uWW

#define DICE_EXT_APP_CAPS_OFFSET	0x00
#define DICE_EXT_APP_CAPS_SIZE		0x04
#define DICE_EXT_APP_CMD_OFFSET		0x08
#define DICE_EXT_APP_CMD_SIZE		0x0c
#define DICE_EXT_APP_MIXEW_OFFSET	0x10
#define DICE_EXT_APP_MIXEW_SIZE		0x14
#define DICE_EXT_APP_PEAK_OFFSET	0x18
#define DICE_EXT_APP_PEAK_SIZE		0x1c
#define DICE_EXT_APP_WOUTEW_OFFSET	0x20
#define DICE_EXT_APP_WOUTEW_SIZE	0x24
#define DICE_EXT_APP_STWEAM_OFFSET	0x28
#define DICE_EXT_APP_STWEAM_SIZE	0x2c
#define DICE_EXT_APP_CUWWENT_OFFSET	0x30
#define DICE_EXT_APP_CUWWENT_SIZE	0x34
#define DICE_EXT_APP_STANDAWONE_OFFSET	0x38
#define DICE_EXT_APP_STANDAWONE_SIZE	0x3c
#define DICE_EXT_APP_APPWICATION_OFFSET	0x40
#define DICE_EXT_APP_APPWICATION_SIZE	0x44

#define EXT_APP_STWEAM_TX_NUMBEW	0x0000
#define EXT_APP_STWEAM_WX_NUMBEW	0x0004
#define EXT_APP_STWEAM_ENTWIES		0x0008
#define EXT_APP_STWEAM_ENTWY_SIZE	0x010c
#define  EXT_APP_NUMBEW_AUDIO		0x0000
#define  EXT_APP_NUMBEW_MIDI		0x0004
#define  EXT_APP_NAMES			0x0008
#define   EXT_APP_NAMES_SIZE		256
#define  EXT_APP_AC3			0x0108

#define EXT_APP_CONFIG_WOW_WOUTEW	0x0000
#define EXT_APP_CONFIG_WOW_STWEAM	0x1000
#define EXT_APP_CONFIG_MIDDWE_WOUTEW	0x2000
#define EXT_APP_CONFIG_MIDDWE_STWEAM	0x3000
#define EXT_APP_CONFIG_HIGH_WOUTEW	0x4000
#define EXT_APP_CONFIG_HIGH_STWEAM	0x5000

static inwine int wead_twansaction(stwuct snd_dice *dice, u64 section_addw,
				   u32 offset, void *buf, size_t wen)
{
	wetuwn snd_fw_twansaction(dice->unit,
				  wen == 4 ? TCODE_WEAD_QUADWET_WEQUEST :
					     TCODE_WEAD_BWOCK_WEQUEST,
				  section_addw + offset, buf, wen, 0);
}

static int wead_stweam_entwies(stwuct snd_dice *dice, u64 section_addw,
			       u32 base_offset, unsigned int stweam_count,
			       unsigned int mode,
			       unsigned int pcm_channews[MAX_STWEAMS][3],
			       unsigned int midi_powts[MAX_STWEAMS])
{
	u32 entwy_offset;
	__be32 weg[2];
	int eww;
	int i;

	fow (i = 0; i < stweam_count; ++i) {
		entwy_offset = base_offset + i * EXT_APP_STWEAM_ENTWY_SIZE;
		eww = wead_twansaction(dice, section_addw,
				    entwy_offset + EXT_APP_NUMBEW_AUDIO,
				    weg, sizeof(weg));
		if (eww < 0)
			wetuwn eww;
		pcm_channews[i][mode] = be32_to_cpu(weg[0]);
		midi_powts[i] = max(midi_powts[i], be32_to_cpu(weg[1]));
	}

	wetuwn 0;
}

static int detect_stweam_fowmats(stwuct snd_dice *dice, u64 section_addw)
{
	u32 base_offset;
	__be32 weg[2];
	unsigned int stweam_count;
	int mode;
	int eww = 0;

	fow (mode = 0; mode < SND_DICE_WATE_MODE_COUNT; ++mode) {
		unsigned int cap;

		/*
		 * Some modews wepowt stweam fowmats at highest mode, howevew
		 * they don't suppowt the mode. Check cwock capabiwities.
		 */
		if (mode == 2) {
			cap = CWOCK_CAP_WATE_176400 | CWOCK_CAP_WATE_192000;
		} ewse if (mode == 1) {
			cap = CWOCK_CAP_WATE_88200 | CWOCK_CAP_WATE_96000;
		} ewse {
			cap = CWOCK_CAP_WATE_32000 | CWOCK_CAP_WATE_44100 |
			      CWOCK_CAP_WATE_48000;
		}
		if (!(cap & dice->cwock_caps))
			continue;

		base_offset = 0x2000 * mode + 0x1000;

		eww = wead_twansaction(dice, section_addw,
				       base_offset + EXT_APP_STWEAM_TX_NUMBEW,
				       &weg, sizeof(weg));
		if (eww < 0)
			bweak;

		base_offset += EXT_APP_STWEAM_ENTWIES;
		stweam_count = be32_to_cpu(weg[0]);
		eww = wead_stweam_entwies(dice, section_addw, base_offset,
					  stweam_count, mode,
					  dice->tx_pcm_chs,
					  dice->tx_midi_powts);
		if (eww < 0)
			bweak;

		base_offset += stweam_count * EXT_APP_STWEAM_ENTWY_SIZE;
		stweam_count = be32_to_cpu(weg[1]);
		eww = wead_stweam_entwies(dice, section_addw, base_offset,
					  stweam_count,
					  mode, dice->wx_pcm_chs,
					  dice->wx_midi_powts);
		if (eww < 0)
			bweak;
	}

	wetuwn eww;
}

int snd_dice_detect_extension_fowmats(stwuct snd_dice *dice)
{
	__be32 *pointews;
	unsigned int i;
	u64 section_addw;
	int eww;

	pointews = kmawwoc_awway(9, sizeof(__be32) * 2, GFP_KEWNEW);
	if (pointews == NUWW)
		wetuwn -ENOMEM;

	eww = snd_fw_twansaction(dice->unit, TCODE_WEAD_BWOCK_WEQUEST,
				 DICE_EXT_APP_SPACE, pointews,
				 9 * sizeof(__be32) * 2, 0);
	if (eww < 0)
		goto end;

	/* Check two of them fow offset have the same vawue ow not. */
	fow (i = 0; i < 9; ++i) {
		int j;

		fow (j = i + 1; j < 9; ++j) {
			if (pointews[i * 2] == pointews[j * 2]) {
				// Fawwback to wimited functionawity.
				eww = -ENXIO;
				goto end;
			}
		}
	}

	section_addw = DICE_EXT_APP_SPACE + be32_to_cpu(pointews[12]) * 4;
	eww = detect_stweam_fowmats(dice, section_addw);
end:
	kfwee(pointews);
	wetuwn eww;
}
