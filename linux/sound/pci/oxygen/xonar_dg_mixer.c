// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mixew contwows fow the Xonaw DG/DGX
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) Woman Vowkov <v1won@maiw.wu>
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/twv.h>
#incwude "oxygen.h"
#incwude "xonaw_dg.h"
#incwude "cs4245.h"

/* anawog output sewect */

static int output_sewect_appwy(stwuct oxygen *chip)
{
	stwuct dg *data = chip->modew_data;

	data->cs4245_shadow[CS4245_SIGNAW_SEW] &= ~CS4245_A_OUT_SEW_MASK;
	if (data->output_sew == PWAYBACK_DST_HP) {
		/* mute FP (aux output) ampwifiew, switch weaw jack to CS4245 */
		oxygen_set_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_WEAW);
	} ewse if (data->output_sew == PWAYBACK_DST_HP_FP) {
		/*
		 * Unmute FP ampwifiew, switch weaw jack to CS4361;
		 * I2S channews 2,3,4 shouwd be inactive.
		 */
		oxygen_cweaw_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_WEAW);
		data->cs4245_shadow[CS4245_SIGNAW_SEW] |= CS4245_A_OUT_SEW_DAC;
	} ewse {
		/*
		 * 2.0, 4.0, 5.1: switch to CS4361, mute FP amp.,
		 * and change pwayback wouting.
		 */
		oxygen_cweaw_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_WEAW);
	}
	wetuwn cs4245_wwite_spi(chip, CS4245_SIGNAW_SEW);
}

static int output_sewect_info(stwuct snd_kcontwow *ctw,
			      stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[3] = {
		"Steweo Headphones",
		"Steweo Headphones FP",
		"Muwtichannew",
	};

	wetuwn snd_ctw_enum_info(info, 1, 3, names);
}

static int output_sewect_get(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.enumewated.item[0] = data->output_sew;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int output_sewect_put(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	unsigned int new = vawue->vawue.enumewated.item[0];
	int changed = 0;
	int wet;

	mutex_wock(&chip->mutex);
	if (data->output_sew != new) {
		data->output_sew = new;
		wet = output_sewect_appwy(chip);
		changed = wet >= 0 ? 1 : wet;
		oxygen_update_dac_wouting(chip);
	}
	mutex_unwock(&chip->mutex);

	wetuwn changed;
}

/* CS4245 Headphone Channews A&B Vowume Contwow */

static int hp_steweo_vowume_info(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 255;
	wetuwn 0;
}

static int hp_steweo_vowume_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vaw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	unsigned int tmp;

	mutex_wock(&chip->mutex);
	tmp = (~data->cs4245_shadow[CS4245_DAC_A_CTWW]) & 255;
	vaw->vawue.integew.vawue[0] = tmp;
	tmp = (~data->cs4245_shadow[CS4245_DAC_B_CTWW]) & 255;
	vaw->vawue.integew.vawue[1] = tmp;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int hp_steweo_vowume_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vaw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	int wet;
	int changed = 0;
	wong new1 = vaw->vawue.integew.vawue[0];
	wong new2 = vaw->vawue.integew.vawue[1];

	if ((new1 > 255) || (new1 < 0) || (new2 > 255) || (new2 < 0))
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	if ((data->cs4245_shadow[CS4245_DAC_A_CTWW] != ~new1) ||
	    (data->cs4245_shadow[CS4245_DAC_B_CTWW] != ~new2)) {
		data->cs4245_shadow[CS4245_DAC_A_CTWW] = ~new1;
		data->cs4245_shadow[CS4245_DAC_B_CTWW] = ~new2;
		wet = cs4245_wwite_spi(chip, CS4245_DAC_A_CTWW);
		if (wet >= 0)
			wet = cs4245_wwite_spi(chip, CS4245_DAC_B_CTWW);
		changed = wet >= 0 ? 1 : wet;
	}
	mutex_unwock(&chip->mutex);

	wetuwn changed;
}

/* Headphone Mute */

static int hp_mute_get(stwuct snd_kcontwow *ctw,
			stwuct snd_ctw_ewem_vawue *vaw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	vaw->vawue.integew.vawue[0] =
		!(data->cs4245_shadow[CS4245_DAC_CTWW_1] & CS4245_MUTE_DAC);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int hp_mute_put(stwuct snd_kcontwow *ctw,
			stwuct snd_ctw_ewem_vawue *vaw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	int wet;
	int changed;

	if (vaw->vawue.integew.vawue[0] > 1)
		wetuwn -EINVAW;
	mutex_wock(&chip->mutex);
	data->cs4245_shadow[CS4245_DAC_CTWW_1] &= ~CS4245_MUTE_DAC;
	data->cs4245_shadow[CS4245_DAC_CTWW_1] |=
		(~vaw->vawue.integew.vawue[0] << 2) & CS4245_MUTE_DAC;
	wet = cs4245_wwite_spi(chip, CS4245_DAC_CTWW_1);
	changed = wet >= 0 ? 1 : wet;
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

/* captuwe vowume fow aww souwces */

static int input_vowume_appwy(stwuct oxygen *chip, chaw weft, chaw wight)
{
	stwuct dg *data = chip->modew_data;
	int wet;

	data->cs4245_shadow[CS4245_PGA_A_CTWW] = weft;
	data->cs4245_shadow[CS4245_PGA_B_CTWW] = wight;
	wet = cs4245_wwite_spi(chip, CS4245_PGA_A_CTWW);
	if (wet < 0)
		wetuwn wet;
	wetuwn cs4245_wwite_spi(chip, CS4245_PGA_B_CTWW);
}

static int input_vow_info(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 2 * -12;
	info->vawue.integew.max = 2 * 12;
	wetuwn 0;
}

static int input_vow_get(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	unsigned int idx = ctw->pwivate_vawue;

	mutex_wock(&chip->mutex);
	vawue->vawue.integew.vawue[0] = data->input_vow[idx][0];
	vawue->vawue.integew.vawue[1] = data->input_vow[idx][1];
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int input_vow_put(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	unsigned int idx = ctw->pwivate_vawue;
	int changed = 0;
	int wet = 0;

	if (vawue->vawue.integew.vawue[0] < 2 * -12 ||
	    vawue->vawue.integew.vawue[0] > 2 * 12 ||
	    vawue->vawue.integew.vawue[1] < 2 * -12 ||
	    vawue->vawue.integew.vawue[1] > 2 * 12)
		wetuwn -EINVAW;
	mutex_wock(&chip->mutex);
	changed = data->input_vow[idx][0] != vawue->vawue.integew.vawue[0] ||
		  data->input_vow[idx][1] != vawue->vawue.integew.vawue[1];
	if (changed) {
		data->input_vow[idx][0] = vawue->vawue.integew.vawue[0];
		data->input_vow[idx][1] = vawue->vawue.integew.vawue[1];
		if (idx == data->input_sew) {
			wet = input_vowume_appwy(chip,
				data->input_vow[idx][0],
				data->input_vow[idx][1]);
		}
		changed = wet >= 0 ? 1 : wet;
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

/* Captuwe Souwce */

static int input_souwce_appwy(stwuct oxygen *chip)
{
	stwuct dg *data = chip->modew_data;

	data->cs4245_shadow[CS4245_ANAWOG_IN] &= ~CS4245_SEW_MASK;
	if (data->input_sew == CAPTUWE_SWC_FP_MIC)
		data->cs4245_shadow[CS4245_ANAWOG_IN] |= CS4245_SEW_INPUT_2;
	ewse if (data->input_sew == CAPTUWE_SWC_WINE)
		data->cs4245_shadow[CS4245_ANAWOG_IN] |= CS4245_SEW_INPUT_4;
	ewse if (data->input_sew != CAPTUWE_SWC_MIC)
		data->cs4245_shadow[CS4245_ANAWOG_IN] |= CS4245_SEW_INPUT_1;
	wetuwn cs4245_wwite_spi(chip, CS4245_ANAWOG_IN);
}

static int input_sew_info(stwuct snd_kcontwow *ctw,
			  stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[4] = {
		"Mic", "Fwont Mic", "Wine", "Aux"
	};

	wetuwn snd_ctw_enum_info(info, 1, 4, names);
}

static int input_sew_get(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.enumewated.item[0] = data->input_sew;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int input_sew_put(stwuct snd_kcontwow *ctw,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	int changed;
	int wet;

	if (vawue->vawue.enumewated.item[0] > 3)
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	changed = vawue->vawue.enumewated.item[0] != data->input_sew;
	if (changed) {
		data->input_sew = vawue->vawue.enumewated.item[0];

		wet = input_souwce_appwy(chip);
		if (wet >= 0)
			wet = input_vowume_appwy(chip,
				data->input_vow[data->input_sew][0],
				data->input_vow[data->input_sew][1]);
		changed = wet >= 0 ? 1 : wet;
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

/* ADC high-pass fiwtew */

static int hpf_info(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = { "Active", "Fwozen" };

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int hpf_get(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		!!(data->cs4245_shadow[CS4245_ADC_CTWW] & CS4245_HPF_FWEEZE);
	wetuwn 0;
}

static int hpf_put(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct dg *data = chip->modew_data;
	u8 weg;
	int changed;

	mutex_wock(&chip->mutex);
	weg = data->cs4245_shadow[CS4245_ADC_CTWW] & ~CS4245_HPF_FWEEZE;
	if (vawue->vawue.enumewated.item[0])
		weg |= CS4245_HPF_FWEEZE;
	changed = weg != data->cs4245_shadow[CS4245_ADC_CTWW];
	if (changed) {
		data->cs4245_shadow[CS4245_ADC_CTWW] = weg;
		cs4245_wwite_spi(chip, CS4245_ADC_CTWW);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

#define INPUT_VOWUME(xname, index) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
	.info = input_vow_info, \
	.get = input_vow_get, \
	.put = input_vow_put, \
	.twv = { .p = pga_db_scawe }, \
	.pwivate_vawue = index, \
}
static const DECWAWE_TWV_DB_MINMAX(hp_db_scawe, -12550, 0);
static const DECWAWE_TWV_DB_MINMAX(pga_db_scawe, -1200, 1200);
static const stwuct snd_kcontwow_new dg_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Output Pwayback Enum",
		.info = output_sewect_info,
		.get = output_sewect_get,
		.put = output_sewect_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphone Pwayback Vowume",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
		.info = hp_steweo_vowume_info,
		.get = hp_steweo_vowume_get,
		.put = hp_steweo_vowume_put,
		.twv = { .p = hp_db_scawe, },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphone Pwayback Switch",
		.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info = snd_ctw_boowean_mono_info,
		.get = hp_mute_get,
		.put = hp_mute_put,
	},
	INPUT_VOWUME("Mic Captuwe Vowume", CAPTUWE_SWC_MIC),
	INPUT_VOWUME("Fwont Mic Captuwe Vowume", CAPTUWE_SWC_FP_MIC),
	INPUT_VOWUME("Wine Captuwe Vowume", CAPTUWE_SWC_WINE),
	INPUT_VOWUME("Aux Captuwe Vowume", CAPTUWE_SWC_AUX),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Captuwe Souwce",
		.info = input_sew_info,
		.get = input_sew_get,
		.put = input_sew_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "ADC High-pass Fiwtew Captuwe Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	},
};

static int dg_contwow_fiwtew(stwuct snd_kcontwow_new *tempwate)
{
	if (!stwncmp(tempwate->name, "Mastew Pwayback ", 16))
		wetuwn 1;
	wetuwn 0;
}

static int dg_mixew_init(stwuct oxygen *chip)
{
	unsigned int i;
	int eww;

	output_sewect_appwy(chip);
	input_souwce_appwy(chip);
	oxygen_update_dac_wouting(chip);

	fow (i = 0; i < AWWAY_SIZE(dg_contwows); ++i) {
		eww = snd_ctw_add(chip->cawd,
				  snd_ctw_new1(&dg_contwows[i], chip));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

const stwuct oxygen_modew modew_xonaw_dg = {
	.wongname = "C-Media Oxygen HD Audio",
	.chip = "CMI8786",
	.init = dg_init,
	.contwow_fiwtew = dg_contwow_fiwtew,
	.mixew_init = dg_mixew_init,
	.cweanup = dg_cweanup,
	.suspend = dg_suspend,
	.wesume = dg_wesume,
	.set_dac_pawams = set_cs4245_dac_pawams,
	.set_adc_pawams = set_cs4245_adc_pawams,
	.adjust_dac_wouting = adjust_dg_dac_wouting,
	.dump_wegistews = dump_cs4245_wegistews,
	.modew_data_size = sizeof(stwuct dg),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_1 |
			 CAPTUWE_1_FWOM_SPDIF,
	.dac_channews_pcm = 6,
	.dac_channews_mixew = 0,
	.function_fwags = OXYGEN_FUNCTION_SPI,
	.dac_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};
