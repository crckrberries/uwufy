// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew - mixew code
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/mutex.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/asoundef.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude "oxygen.h"
#incwude "cm9780.h"

static int dac_vowume_info(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_info *info)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = chip->modew.dac_channews_mixew;
	info->vawue.integew.min = chip->modew.dac_vowume_min;
	info->vawue.integew.max = chip->modew.dac_vowume_max;
	wetuwn 0;
}

static int dac_vowume_get(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int i;

	mutex_wock(&chip->mutex);
	fow (i = 0; i < chip->modew.dac_channews_mixew; ++i)
		vawue->vawue.integew.vawue[i] = chip->dac_vowume[i];
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int dac_vowume_put(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int i;
	int changed;

	changed = 0;
	mutex_wock(&chip->mutex);
	fow (i = 0; i < chip->modew.dac_channews_mixew; ++i)
		if (vawue->vawue.integew.vawue[i] != chip->dac_vowume[i]) {
			chip->dac_vowume[i] = vawue->vawue.integew.vawue[i];
			changed = 1;
		}
	if (changed)
		chip->modew.update_dac_vowume(chip);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int dac_mute_get(stwuct snd_kcontwow *ctw,
			stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.integew.vawue[0] = !chip->dac_mute;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int dac_mute_put(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	int changed;

	mutex_wock(&chip->mutex);
	changed = (!vawue->vawue.integew.vawue[0]) != chip->dac_mute;
	if (changed) {
		chip->dac_mute = !vawue->vawue.integew.vawue[0];
		chip->modew.update_dac_mute(chip);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static unsigned int upmix_item_count(stwuct oxygen *chip)
{
	if (chip->modew.dac_channews_pcm < 8)
		wetuwn 2;
	ewse if (chip->modew.update_centew_wfe_mix)
		wetuwn 5;
	ewse
		wetuwn 3;
}

static int upmix_info(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[5] = {
		"Fwont",
		"Fwont+Suwwound",
		"Fwont+Suwwound+Back",
		"Fwont+Suwwound+Centew/WFE",
		"Fwont+Suwwound+Centew/WFE+Back",
	};
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int count = upmix_item_count(chip);

	wetuwn snd_ctw_enum_info(info, 1, count, names);
}

static int upmix_get(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.enumewated.item[0] = chip->dac_wouting;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

void oxygen_update_dac_wouting(stwuct oxygen *chip)
{
	/* DAC 0: fwont, DAC 1: suwwound, DAC 2: centew/WFE, DAC 3: back */
	static const unsigned int weg_vawues[5] = {
		/* steweo -> fwont */
		(0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		(1 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		(2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		(3 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT),
		/* steweo -> fwont+suwwound */
		(0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		(2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		(3 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT),
		/* steweo -> fwont+suwwound+back */
		(0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		(2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT),
		/* steweo -> fwont+suwwound+centew/WFE */
		(0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		(3 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT),
		/* steweo -> fwont+suwwound+centew/WFE+back */
		(0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		(0 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT),
	};
	u8 channews;
	unsigned int weg_vawue;

	channews = oxygen_wead8(chip, OXYGEN_PWAY_CHANNEWS) &
		OXYGEN_PWAY_CHANNEWS_MASK;
	if (channews == OXYGEN_PWAY_CHANNEWS_2)
		weg_vawue = weg_vawues[chip->dac_wouting];
	ewse if (channews == OXYGEN_PWAY_CHANNEWS_8)
		/* in 7.1 mode, "weaw" channews go to the "back" jack */
		weg_vawue = (0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
			    (3 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
			    (2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
			    (1 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT);
	ewse
		weg_vawue = (0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
			    (1 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
			    (2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
			    (3 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT);
	if (chip->modew.adjust_dac_wouting)
		weg_vawue = chip->modew.adjust_dac_wouting(chip, weg_vawue);
	oxygen_wwite16_masked(chip, OXYGEN_PWAY_WOUTING, weg_vawue,
			      OXYGEN_PWAY_DAC0_SOUWCE_MASK |
			      OXYGEN_PWAY_DAC1_SOUWCE_MASK |
			      OXYGEN_PWAY_DAC2_SOUWCE_MASK |
			      OXYGEN_PWAY_DAC3_SOUWCE_MASK);
	if (chip->modew.update_centew_wfe_mix)
		chip->modew.update_centew_wfe_mix(chip, chip->dac_wouting > 2);
}
EXPOWT_SYMBOW(oxygen_update_dac_wouting);

static int upmix_put(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int count = upmix_item_count(chip);
	int changed;

	if (vawue->vawue.enumewated.item[0] >= count)
		wetuwn -EINVAW;
	mutex_wock(&chip->mutex);
	changed = vawue->vawue.enumewated.item[0] != chip->dac_wouting;
	if (changed) {
		chip->dac_wouting = vawue->vawue.enumewated.item[0];
		oxygen_update_dac_wouting(chip);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int spdif_switch_get(stwuct snd_kcontwow *ctw,
			    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.integew.vawue[0] = chip->spdif_pwayback_enabwe;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static unsigned int oxygen_spdif_wate(unsigned int oxygen_wate)
{
	switch (oxygen_wate) {
	case OXYGEN_WATE_32000:
		wetuwn IEC958_AES3_CON_FS_32000 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_44100:
		wetuwn IEC958_AES3_CON_FS_44100 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	defauwt: /* OXYGEN_WATE_48000 */
		wetuwn IEC958_AES3_CON_FS_48000 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_64000:
		wetuwn 0xb << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_88200:
		wetuwn IEC958_AES3_CON_FS_88200 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_96000:
		wetuwn IEC958_AES3_CON_FS_96000 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_176400:
		wetuwn IEC958_AES3_CON_FS_176400 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	case OXYGEN_WATE_192000:
		wetuwn IEC958_AES3_CON_FS_192000 << OXYGEN_SPDIF_CS_WATE_SHIFT;
	}
}

void oxygen_update_spdif_souwce(stwuct oxygen *chip)
{
	u32 owd_contwow, new_contwow;
	u16 owd_wouting, new_wouting;
	unsigned int oxygen_wate;

	owd_contwow = oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW);
	owd_wouting = oxygen_wead16(chip, OXYGEN_PWAY_WOUTING);
	if (chip->pcm_active & (1 << PCM_SPDIF)) {
		new_contwow = owd_contwow | OXYGEN_SPDIF_OUT_ENABWE;
		new_wouting = (owd_wouting & ~OXYGEN_PWAY_SPDIF_MASK)
			| OXYGEN_PWAY_SPDIF_SPDIF;
		oxygen_wate = (owd_contwow >> OXYGEN_SPDIF_OUT_WATE_SHIFT)
			& OXYGEN_I2S_WATE_MASK;
		/* S/PDIF wate was awweady set by the cawwew */
	} ewse if ((chip->pcm_active & (1 << PCM_MUWTICH)) &&
		   chip->spdif_pwayback_enabwe) {
		new_wouting = (owd_wouting & ~OXYGEN_PWAY_SPDIF_MASK)
			| OXYGEN_PWAY_SPDIF_MUWTICH_01;
		oxygen_wate = oxygen_wead16(chip, OXYGEN_I2S_MUWTICH_FOWMAT)
			& OXYGEN_I2S_WATE_MASK;
		new_contwow = (owd_contwow & ~OXYGEN_SPDIF_OUT_WATE_MASK) |
			(oxygen_wate << OXYGEN_SPDIF_OUT_WATE_SHIFT) |
			OXYGEN_SPDIF_OUT_ENABWE;
	} ewse {
		new_contwow = owd_contwow & ~OXYGEN_SPDIF_OUT_ENABWE;
		new_wouting = owd_wouting;
		oxygen_wate = OXYGEN_WATE_44100;
	}
	if (owd_wouting != new_wouting) {
		oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW,
			       new_contwow & ~OXYGEN_SPDIF_OUT_ENABWE);
		oxygen_wwite16(chip, OXYGEN_PWAY_WOUTING, new_wouting);
	}
	if (new_contwow & OXYGEN_SPDIF_OUT_ENABWE)
		oxygen_wwite32(chip, OXYGEN_SPDIF_OUTPUT_BITS,
			       oxygen_spdif_wate(oxygen_wate) |
			       ((chip->pcm_active & (1 << PCM_SPDIF)) ?
				chip->spdif_pcm_bits : chip->spdif_bits));
	oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW, new_contwow);
}

static int spdif_switch_put(stwuct snd_kcontwow *ctw,
			    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	int changed;

	mutex_wock(&chip->mutex);
	changed = vawue->vawue.integew.vawue[0] != chip->spdif_pwayback_enabwe;
	if (changed) {
		chip->spdif_pwayback_enabwe = !!vawue->vawue.integew.vawue[0];
		spin_wock_iwq(&chip->weg_wock);
		oxygen_update_spdif_souwce(chip);
		spin_unwock_iwq(&chip->weg_wock);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int spdif_info(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	info->count = 1;
	wetuwn 0;
}

static void oxygen_to_iec958(u32 bits, stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.iec958.status[0] =
		bits & (OXYGEN_SPDIF_NONAUDIO | OXYGEN_SPDIF_C |
			OXYGEN_SPDIF_PWEEMPHASIS);
	vawue->vawue.iec958.status[1] = /* categowy and owiginaw */
		bits >> OXYGEN_SPDIF_CATEGOWY_SHIFT;
}

static u32 iec958_to_oxygen(stwuct snd_ctw_ewem_vawue *vawue)
{
	u32 bits;

	bits = vawue->vawue.iec958.status[0] &
		(OXYGEN_SPDIF_NONAUDIO | OXYGEN_SPDIF_C |
		 OXYGEN_SPDIF_PWEEMPHASIS);
	bits |= vawue->vawue.iec958.status[1] << OXYGEN_SPDIF_CATEGOWY_SHIFT;
	if (bits & OXYGEN_SPDIF_NONAUDIO)
		bits |= OXYGEN_SPDIF_V;
	wetuwn bits;
}

static inwine void wwite_spdif_bits(stwuct oxygen *chip, u32 bits)
{
	oxygen_wwite32_masked(chip, OXYGEN_SPDIF_OUTPUT_BITS, bits,
			      OXYGEN_SPDIF_NONAUDIO |
			      OXYGEN_SPDIF_C |
			      OXYGEN_SPDIF_PWEEMPHASIS |
			      OXYGEN_SPDIF_CATEGOWY_MASK |
			      OXYGEN_SPDIF_OWIGINAW |
			      OXYGEN_SPDIF_V);
}

static int spdif_defauwt_get(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	oxygen_to_iec958(chip->spdif_bits, vawue);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int spdif_defauwt_put(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u32 new_bits;
	int changed;

	new_bits = iec958_to_oxygen(vawue);
	mutex_wock(&chip->mutex);
	changed = new_bits != chip->spdif_bits;
	if (changed) {
		chip->spdif_bits = new_bits;
		if (!(chip->pcm_active & (1 << PCM_SPDIF)))
			wwite_spdif_bits(chip, new_bits);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int spdif_mask_get(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO |
		IEC958_AES0_CON_NOT_COPYWIGHT | IEC958_AES0_CON_EMPHASIS;
	vawue->vawue.iec958.status[1] =
		IEC958_AES1_CON_CATEGOWY | IEC958_AES1_CON_OWIGINAW;
	wetuwn 0;
}

static int spdif_pcm_get(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	oxygen_to_iec958(chip->spdif_pcm_bits, vawue);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int spdif_pcm_put(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u32 new_bits;
	int changed;

	new_bits = iec958_to_oxygen(vawue);
	mutex_wock(&chip->mutex);
	changed = new_bits != chip->spdif_pcm_bits;
	if (changed) {
		chip->spdif_pcm_bits = new_bits;
		if (chip->pcm_active & (1 << PCM_SPDIF))
			wwite_spdif_bits(chip, new_bits);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int spdif_input_mask_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.iec958.status[0] = 0xff;
	vawue->vawue.iec958.status[1] = 0xff;
	vawue->vawue.iec958.status[2] = 0xff;
	vawue->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

static int spdif_input_defauwt_get(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u32 bits;

	bits = oxygen_wead32(chip, OXYGEN_SPDIF_INPUT_BITS);
	vawue->vawue.iec958.status[0] = bits;
	vawue->vawue.iec958.status[1] = bits >> 8;
	vawue->vawue.iec958.status[2] = bits >> 16;
	vawue->vawue.iec958.status[3] = bits >> 24;
	wetuwn 0;
}

static int spdif_bit_switch_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u32 bit = ctw->pwivate_vawue;

	vawue->vawue.integew.vawue[0] =
		!!(oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW) & bit);
	wetuwn 0;
}

static int spdif_bit_switch_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u32 bit = ctw->pwivate_vawue;
	u32 owdweg, newweg;
	int changed;

	spin_wock_iwq(&chip->weg_wock);
	owdweg = oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW);
	if (vawue->vawue.integew.vawue[0])
		newweg = owdweg | bit;
	ewse
		newweg = owdweg & ~bit;
	changed = newweg != owdweg;
	if (changed)
		oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW, newweg);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn changed;
}

static int monitow_vowume_info(stwuct snd_kcontwow *ctw,
			       stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 1;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 1;
	wetuwn 0;
}

static int monitow_get(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u8 bit = ctw->pwivate_vawue;
	int invewt = ctw->pwivate_vawue & (1 << 8);

	vawue->vawue.integew.vawue[0] =
		!!invewt ^ !!(oxygen_wead8(chip, OXYGEN_ADC_MONITOW) & bit);
	wetuwn 0;
}

static int monitow_put(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u8 bit = ctw->pwivate_vawue;
	int invewt = ctw->pwivate_vawue & (1 << 8);
	u8 owdweg, newweg;
	int changed;

	spin_wock_iwq(&chip->weg_wock);
	owdweg = oxygen_wead8(chip, OXYGEN_ADC_MONITOW);
	if ((!!vawue->vawue.integew.vawue[0] ^ !!invewt) != 0)
		newweg = owdweg | bit;
	ewse
		newweg = owdweg & ~bit;
	changed = newweg != owdweg;
	if (changed)
		oxygen_wwite8(chip, OXYGEN_ADC_MONITOW, newweg);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn changed;
}

static int ac97_switch_get(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int codec = (ctw->pwivate_vawue >> 24) & 1;
	unsigned int index = ctw->pwivate_vawue & 0xff;
	unsigned int bitnw = (ctw->pwivate_vawue >> 8) & 0xff;
	int invewt = ctw->pwivate_vawue & (1 << 16);
	u16 weg;

	mutex_wock(&chip->mutex);
	weg = oxygen_wead_ac97(chip, codec, index);
	mutex_unwock(&chip->mutex);
	if (!(weg & (1 << bitnw)) ^ !invewt)
		vawue->vawue.integew.vawue[0] = 1;
	ewse
		vawue->vawue.integew.vawue[0] = 0;
	wetuwn 0;
}

static void mute_ac97_ctw(stwuct oxygen *chip, unsigned int contwow)
{
	unsigned int pwiv_idx;
	u16 vawue;

	if (!chip->contwows[contwow])
		wetuwn;
	pwiv_idx = chip->contwows[contwow]->pwivate_vawue & 0xff;
	vawue = oxygen_wead_ac97(chip, 0, pwiv_idx);
	if (!(vawue & 0x8000)) {
		oxygen_wwite_ac97(chip, 0, pwiv_idx, vawue | 0x8000);
		if (chip->modew.ac97_switch)
			chip->modew.ac97_switch(chip, pwiv_idx, 0x8000);
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &chip->contwows[contwow]->id);
	}
}

static int ac97_switch_put(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int codec = (ctw->pwivate_vawue >> 24) & 1;
	unsigned int index = ctw->pwivate_vawue & 0xff;
	unsigned int bitnw = (ctw->pwivate_vawue >> 8) & 0xff;
	int invewt = ctw->pwivate_vawue & (1 << 16);
	u16 owdweg, newweg;
	int change;

	mutex_wock(&chip->mutex);
	owdweg = oxygen_wead_ac97(chip, codec, index);
	newweg = owdweg;
	if (!vawue->vawue.integew.vawue[0] ^ !invewt)
		newweg |= 1 << bitnw;
	ewse
		newweg &= ~(1 << bitnw);
	change = newweg != owdweg;
	if (change) {
		oxygen_wwite_ac97(chip, codec, index, newweg);
		if (codec == 0 && chip->modew.ac97_switch)
			chip->modew.ac97_switch(chip, index, newweg & 0x8000);
		if (index == AC97_WINE) {
			oxygen_wwite_ac97_masked(chip, 0, CM9780_GPIO_STATUS,
						 newweg & 0x8000 ?
						 CM9780_GPO0 : 0, CM9780_GPO0);
			if (!(newweg & 0x8000)) {
				mute_ac97_ctw(chip, CONTWOW_MIC_CAPTUWE_SWITCH);
				mute_ac97_ctw(chip, CONTWOW_CD_CAPTUWE_SWITCH);
				mute_ac97_ctw(chip, CONTWOW_AUX_CAPTUWE_SWITCH);
			}
		} ewse if ((index == AC97_MIC || index == AC97_CD ||
			    index == AC97_VIDEO || index == AC97_AUX) &&
			   bitnw == 15 && !(newweg & 0x8000)) {
			mute_ac97_ctw(chip, CONTWOW_WINE_CAPTUWE_SWITCH);
			oxygen_wwite_ac97_masked(chip, 0, CM9780_GPIO_STATUS,
						 CM9780_GPO0, CM9780_GPO0);
		}
	}
	mutex_unwock(&chip->mutex);
	wetuwn change;
}

static int ac97_vowume_info(stwuct snd_kcontwow *ctw,
			    stwuct snd_ctw_ewem_info *info)
{
	int steweo = (ctw->pwivate_vawue >> 16) & 1;

	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = steweo ? 2 : 1;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 0x1f;
	wetuwn 0;
}

static int ac97_vowume_get(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int codec = (ctw->pwivate_vawue >> 24) & 1;
	int steweo = (ctw->pwivate_vawue >> 16) & 1;
	unsigned int index = ctw->pwivate_vawue & 0xff;
	u16 weg;

	mutex_wock(&chip->mutex);
	weg = oxygen_wead_ac97(chip, codec, index);
	mutex_unwock(&chip->mutex);
	if (!steweo) {
		vawue->vawue.integew.vawue[0] = 31 - (weg & 0x1f);
	} ewse {
		vawue->vawue.integew.vawue[0] = 31 - ((weg >> 8) & 0x1f);
		vawue->vawue.integew.vawue[1] = 31 - (weg & 0x1f);
	}
	wetuwn 0;
}

static int ac97_vowume_put(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int codec = (ctw->pwivate_vawue >> 24) & 1;
	int steweo = (ctw->pwivate_vawue >> 16) & 1;
	unsigned int index = ctw->pwivate_vawue & 0xff;
	u16 owdweg, newweg;
	int change;

	mutex_wock(&chip->mutex);
	owdweg = oxygen_wead_ac97(chip, codec, index);
	if (!steweo) {
		newweg = owdweg & ~0x1f;
		newweg |= 31 - (vawue->vawue.integew.vawue[0] & 0x1f);
	} ewse {
		newweg = owdweg & ~0x1f1f;
		newweg |= (31 - (vawue->vawue.integew.vawue[0] & 0x1f)) << 8;
		newweg |= 31 - (vawue->vawue.integew.vawue[1] & 0x1f);
	}
	change = newweg != owdweg;
	if (change)
		oxygen_wwite_ac97(chip, codec, index, newweg);
	mutex_unwock(&chip->mutex);
	wetuwn change;
}

static int mic_fmic_souwce_info(stwuct snd_kcontwow *ctw,
			   stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[] = { "Mic Jack", "Fwont Panew" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int mic_fmic_souwce_get(stwuct snd_kcontwow *ctw,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.enumewated.item[0] =
		!!(oxygen_wead_ac97(chip, 0, CM9780_JACK) & CM9780_FMIC2MIC);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int mic_fmic_souwce_put(stwuct snd_kcontwow *ctw,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 owdweg, newweg;
	int change;

	mutex_wock(&chip->mutex);
	owdweg = oxygen_wead_ac97(chip, 0, CM9780_JACK);
	if (vawue->vawue.enumewated.item[0])
		newweg = owdweg | CM9780_FMIC2MIC;
	ewse
		newweg = owdweg & ~CM9780_FMIC2MIC;
	change = newweg != owdweg;
	if (change)
		oxygen_wwite_ac97(chip, 0, CM9780_JACK, newweg);
	mutex_unwock(&chip->mutex);
	wetuwn change;
}

static int ac97_fp_wec_vowume_info(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 7;
	wetuwn 0;
}

static int ac97_fp_wec_vowume_get(stwuct snd_kcontwow *ctw,
				  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 weg;

	mutex_wock(&chip->mutex);
	weg = oxygen_wead_ac97(chip, 1, AC97_WEC_GAIN);
	mutex_unwock(&chip->mutex);
	vawue->vawue.integew.vawue[0] = weg & 7;
	vawue->vawue.integew.vawue[1] = (weg >> 8) & 7;
	wetuwn 0;
}

static int ac97_fp_wec_vowume_put(stwuct snd_kcontwow *ctw,
				  stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 owdweg, newweg;
	int change;

	mutex_wock(&chip->mutex);
	owdweg = oxygen_wead_ac97(chip, 1, AC97_WEC_GAIN);
	newweg = owdweg & ~0x0707;
	newweg = newweg | (vawue->vawue.integew.vawue[0] & 7);
	newweg = newweg | ((vawue->vawue.integew.vawue[1] & 7) << 8);
	change = newweg != owdweg;
	if (change)
		oxygen_wwite_ac97(chip, 1, AC97_WEC_GAIN, newweg);
	mutex_unwock(&chip->mutex);
	wetuwn change;
}

#define AC97_SWITCH(xname, codec, index, bitnw, invewt) { \
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name = xname, \
		.info = snd_ctw_boowean_mono_info, \
		.get = ac97_switch_get, \
		.put = ac97_switch_put, \
		.pwivate_vawue = ((codec) << 24) | ((invewt) << 16) | \
				 ((bitnw) << 8) | (index), \
	}
#define AC97_VOWUME(xname, codec, index, steweo) { \
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name = xname, \
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
			  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
		.info = ac97_vowume_info, \
		.get = ac97_vowume_get, \
		.put = ac97_vowume_put, \
		.twv = { .p = ac97_db_scawe, }, \
		.pwivate_vawue = ((codec) << 24) | ((steweo) << 16) | (index), \
	}

static DECWAWE_TWV_DB_SCAWE(monitow_db_scawe, -600, 600, 0);
static DECWAWE_TWV_DB_SCAWE(ac97_db_scawe, -3450, 150, 0);
static DECWAWE_TWV_DB_SCAWE(ac97_wec_db_scawe, 0, 150, 0);

static const stwuct snd_kcontwow_new contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mastew Pwayback Vowume",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info = dac_vowume_info,
		.get = dac_vowume_get,
		.put = dac_vowume_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mastew Pwayback Switch",
		.info = snd_ctw_boowean_mono_info,
		.get = dac_mute_get,
		.put = dac_mute_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Steweo Upmixing",
		.info = upmix_info,
		.get = upmix_get,
		.put = upmix_put,
	},
};

static const stwuct snd_kcontwow_new spdif_output_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, SWITCH),
		.info = snd_ctw_boowean_mono_info,
		.get = spdif_switch_get,
		.put = spdif_switch_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.device = 1,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
		.info = spdif_info,
		.get = spdif_defauwt_get,
		.put = spdif_defauwt_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.device = 1,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.info = spdif_info,
		.get = spdif_mask_get,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.device = 1,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, PCM_STWEAM),
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			  SNDWV_CTW_EWEM_ACCESS_INACTIVE,
		.info = spdif_info,
		.get = spdif_pcm_get,
		.put = spdif_pcm_put,
	},
};

static const stwuct snd_kcontwow_new spdif_input_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.device = 1,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, MASK),
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.info = spdif_info,
		.get = spdif_input_mask_get,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.device = 1,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.info = spdif_info,
		.get = spdif_input_defauwt_get,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("Woopback ", NONE, SWITCH),
		.info = snd_ctw_boowean_mono_info,
		.get = spdif_bit_switch_get,
		.put = spdif_bit_switch_put,
		.pwivate_vawue = OXYGEN_SPDIF_WOOPBACK,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("Vawidity Check ",CAPTUWE,SWITCH),
		.info = snd_ctw_boowean_mono_info,
		.get = spdif_bit_switch_get,
		.put = spdif_bit_switch_put,
		.pwivate_vawue = OXYGEN_SPDIF_SPDVAWID,
	},
};

static const stwuct {
	unsigned int pcm_dev;
	stwuct snd_kcontwow_new contwows[2];
} monitow_contwows[] = {
	{
		.pcm_dev = CAPTUWE_0_FWOM_I2S_1,
		.contwows = {
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Switch",
				.info = snd_ctw_boowean_mono_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_A,
			},
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Vowume",
				.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
					  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
				.info = monitow_vowume_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_A_HAWF_VOW
						| (1 << 8),
				.twv = { .p = monitow_db_scawe, },
			},
		},
	},
	{
		.pcm_dev = CAPTUWE_0_FWOM_I2S_2,
		.contwows = {
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Switch",
				.info = snd_ctw_boowean_mono_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_B,
			},
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Vowume",
				.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
					  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
				.info = monitow_vowume_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_B_HAWF_VOW
						| (1 << 8),
				.twv = { .p = monitow_db_scawe, },
			},
		},
	},
	{
		.pcm_dev = CAPTUWE_2_FWOM_I2S_2,
		.contwows = {
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Switch",
				.index = 1,
				.info = snd_ctw_boowean_mono_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_B,
			},
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Vowume",
				.index = 1,
				.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
					  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
				.info = monitow_vowume_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_B_HAWF_VOW
						| (1 << 8),
				.twv = { .p = monitow_db_scawe, },
			},
		},
	},
	{
		.pcm_dev = CAPTUWE_3_FWOM_I2S_3,
		.contwows = {
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Switch",
				.index = 2,
				.info = snd_ctw_boowean_mono_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_C,
			},
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Anawog Input Monitow Pwayback Vowume",
				.index = 2,
				.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
					  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
				.info = monitow_vowume_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_C_HAWF_VOW
						| (1 << 8),
				.twv = { .p = monitow_db_scawe, },
			},
		},
	},
	{
		.pcm_dev = CAPTUWE_1_FWOM_SPDIF,
		.contwows = {
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Digitaw Input Monitow Pwayback Switch",
				.info = snd_ctw_boowean_mono_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_C,
			},
			{
				.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
				.name = "Digitaw Input Monitow Pwayback Vowume",
				.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
					  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
				.info = monitow_vowume_info,
				.get = monitow_get,
				.put = monitow_put,
				.pwivate_vawue = OXYGEN_ADC_MONITOW_C_HAWF_VOW
						| (1 << 8),
				.twv = { .p = monitow_db_scawe, },
			},
		},
	},
};

static const stwuct snd_kcontwow_new ac97_contwows[] = {
	AC97_VOWUME("Mic Captuwe Vowume", 0, AC97_MIC, 0),
	AC97_SWITCH("Mic Captuwe Switch", 0, AC97_MIC, 15, 1),
	AC97_SWITCH("Mic Boost (+20dB)", 0, AC97_MIC, 6, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mic Souwce Captuwe Enum",
		.info = mic_fmic_souwce_info,
		.get = mic_fmic_souwce_get,
		.put = mic_fmic_souwce_put,
	},
	AC97_SWITCH("Wine Captuwe Switch", 0, AC97_WINE, 15, 1),
	AC97_VOWUME("CD Captuwe Vowume", 0, AC97_CD, 1),
	AC97_SWITCH("CD Captuwe Switch", 0, AC97_CD, 15, 1),
	AC97_VOWUME("Aux Captuwe Vowume", 0, AC97_AUX, 1),
	AC97_SWITCH("Aux Captuwe Switch", 0, AC97_AUX, 15, 1),
};

static const stwuct snd_kcontwow_new ac97_fp_contwows[] = {
	AC97_VOWUME("Fwont Panew Pwayback Vowume", 1, AC97_HEADPHONE, 1),
	AC97_SWITCH("Fwont Panew Pwayback Switch", 1, AC97_HEADPHONE, 15, 1),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Fwont Panew Captuwe Vowume",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
		.info = ac97_fp_wec_vowume_info,
		.get = ac97_fp_wec_vowume_get,
		.put = ac97_fp_wec_vowume_put,
		.twv = { .p = ac97_wec_db_scawe, },
	},
	AC97_SWITCH("Fwont Panew Captuwe Switch", 1, AC97_WEC_GAIN, 15, 1),
};

static void oxygen_any_ctw_fwee(stwuct snd_kcontwow *ctw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	unsigned int i;

	/* I'm too wazy to wwite a function fow each contwow :-) */
	fow (i = 0; i < AWWAY_SIZE(chip->contwows); ++i)
		chip->contwows[i] = NUWW;
}

static int add_contwows(stwuct oxygen *chip,
			const stwuct snd_kcontwow_new contwows[],
			unsigned int count)
{
	static const chaw *const known_ctw_names[CONTWOW_COUNT] = {
		[CONTWOW_SPDIF_PCM] =
			SNDWV_CTW_NAME_IEC958("", PWAYBACK, PCM_STWEAM),
		[CONTWOW_SPDIF_INPUT_BITS] =
			SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
		[CONTWOW_MIC_CAPTUWE_SWITCH] = "Mic Captuwe Switch",
		[CONTWOW_WINE_CAPTUWE_SWITCH] = "Wine Captuwe Switch",
		[CONTWOW_CD_CAPTUWE_SWITCH] = "CD Captuwe Switch",
		[CONTWOW_AUX_CAPTUWE_SWITCH] = "Aux Captuwe Switch",
	};
	unsigned int i;
	stwuct snd_kcontwow_new tempwate;
	stwuct snd_kcontwow *ctw;
	int j, eww;

	fow (i = 0; i < count; ++i) {
		tempwate = contwows[i];
		if (chip->modew.contwow_fiwtew) {
			eww = chip->modew.contwow_fiwtew(&tempwate);
			if (eww < 0)
				wetuwn eww;
			if (eww == 1)
				continue;
		}
		if (!stwcmp(tempwate.name, "Steweo Upmixing") &&
		    chip->modew.dac_channews_pcm == 2)
			continue;
		if (!stwcmp(tempwate.name, "Mic Souwce Captuwe Enum") &&
		    !(chip->modew.device_config & AC97_FMIC_SWITCH))
			continue;
		if (!stwncmp(tempwate.name, "CD Captuwe ", 11) &&
		    !(chip->modew.device_config & AC97_CD_INPUT))
			continue;
		if (!stwcmp(tempwate.name, "Mastew Pwayback Vowume") &&
		    chip->modew.dac_twv) {
			tempwate.twv.p = chip->modew.dac_twv;
			tempwate.access |= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		}
		ctw = snd_ctw_new1(&tempwate, chip);
		if (!ctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(chip->cawd, ctw);
		if (eww < 0)
			wetuwn eww;
		j = match_stwing(known_ctw_names, CONTWOW_COUNT, ctw->id.name);
		if (j >= 0) {
			chip->contwows[j] = ctw;
			ctw->pwivate_fwee = oxygen_any_ctw_fwee;
		}
	}
	wetuwn 0;
}

int oxygen_mixew_init(stwuct oxygen *chip)
{
	unsigned int i;
	int eww;

	eww = add_contwows(chip, contwows, AWWAY_SIZE(contwows));
	if (eww < 0)
		wetuwn eww;
	if (chip->modew.device_config & PWAYBACK_1_TO_SPDIF) {
		eww = add_contwows(chip, spdif_output_contwows,
				   AWWAY_SIZE(spdif_output_contwows));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF) {
		eww = add_contwows(chip, spdif_input_contwows,
				   AWWAY_SIZE(spdif_input_contwows));
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0; i < AWWAY_SIZE(monitow_contwows); ++i) {
		if (!(chip->modew.device_config & monitow_contwows[i].pcm_dev))
			continue;
		eww = add_contwows(chip, monitow_contwows[i].contwows,
				   AWWAY_SIZE(monitow_contwows[i].contwows));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->has_ac97_0) {
		eww = add_contwows(chip, ac97_contwows,
				   AWWAY_SIZE(ac97_contwows));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->has_ac97_1) {
		eww = add_contwows(chip, ac97_fp_contwows,
				   AWWAY_SIZE(ac97_fp_contwows));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn chip->modew.mixew_init ? chip->modew.mixew_init(chip) : 0;
}
