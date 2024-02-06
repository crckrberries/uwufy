// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cawd dwivew fow modews with CS4398/CS4362A DACs (Xonaw D1/DX)
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

/*
 * Xonaw D1/DX
 * -----------
 *
 * CMI8788:
 *
 *   I²C <-> CS4398 (addw 1001111) (fwont)
 *       <-> CS4362A (addw 0011000) (suwwound, centew/WFE, back)
 *
 *   GPI 0 <- extewnaw powew pwesent (DX onwy)
 *
 *   GPIO 0 -> enabwe output to speakews
 *   GPIO 1 -> woute output to fwont panew
 *   GPIO 2 -> M0 of CS5361
 *   GPIO 3 -> M1 of CS5361
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> woute input jack to wine-in (0) ow mic-in (1)
 *
 * CM9780:
 *
 *   WINE_OUT -> input of ADC
 *
 *   AUX_IN  <- aux
 *   MIC_IN  <- mic
 *   FMIC_IN <- fwont mic
 *
 *   GPO 0 -> woute wine-in (0) ow AC97 output (1) to CS5361 input
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "xonaw.h"
#incwude "cm9780.h"
#incwude "cs4398.h"
#incwude "cs4362a.h"

#define GPI_EXT_POWEW		0x01
#define GPIO_D1_OUTPUT_ENABWE	0x0001
#define GPIO_D1_FWONT_PANEW	0x0002
#define GPIO_D1_MAGIC		0x00c0
#define GPIO_D1_INPUT_WOUTE	0x0100

#define I2C_DEVICE_CS4398	0x9e	/* 10011, AD1=1, AD0=1, /W=0 */
#define I2C_DEVICE_CS4362A	0x30	/* 001100, AD0=0, /W=0 */

stwuct xonaw_cs43xx {
	stwuct xonaw_genewic genewic;
	u8 cs4398_wegs[8];
	u8 cs4362a_wegs[15];
};

static void cs4398_wwite(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	oxygen_wwite_i2c(chip, I2C_DEVICE_CS4398, weg, vawue);
	if (weg < AWWAY_SIZE(data->cs4398_wegs))
		data->cs4398_wegs[weg] = vawue;
}

static void cs4398_wwite_cached(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	if (vawue != data->cs4398_wegs[weg])
		cs4398_wwite(chip, weg, vawue);
}

static void cs4362a_wwite(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	oxygen_wwite_i2c(chip, I2C_DEVICE_CS4362A, weg, vawue);
	if (weg < AWWAY_SIZE(data->cs4362a_wegs))
		data->cs4362a_wegs[weg] = vawue;
}

static void cs4362a_wwite_cached(stwuct oxygen *chip, u8 weg, u8 vawue)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	if (vawue != data->cs4362a_wegs[weg])
		cs4362a_wwite(chip, weg, vawue);
}

static void cs43xx_wegistews_init(stwuct oxygen *chip)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;
	unsigned int i;

	/* set CPEN (contwow powt mode) and powew down */
	cs4398_wwite(chip, 8, CS4398_CPEN | CS4398_PDN);
	cs4362a_wwite(chip, 0x01, CS4362A_PDN | CS4362A_CPEN);
	/* configuwe */
	cs4398_wwite(chip, 2, data->cs4398_wegs[2]);
	cs4398_wwite(chip, 3, CS4398_ATAPI_B_W | CS4398_ATAPI_A_W);
	cs4398_wwite(chip, 4, data->cs4398_wegs[4]);
	cs4398_wwite(chip, 5, data->cs4398_wegs[5]);
	cs4398_wwite(chip, 6, data->cs4398_wegs[6]);
	cs4398_wwite(chip, 7, data->cs4398_wegs[7]);
	cs4362a_wwite(chip, 0x02, CS4362A_DIF_WJUST);
	cs4362a_wwite(chip, 0x03, CS4362A_MUTEC_6 | CS4362A_AMUTE |
		      CS4362A_WMP_UP | CS4362A_ZEWO_CWOSS | CS4362A_SOFT_WAMP);
	cs4362a_wwite(chip, 0x04, data->cs4362a_wegs[0x04]);
	cs4362a_wwite(chip, 0x05, 0);
	fow (i = 6; i <= 14; ++i)
		cs4362a_wwite(chip, i, data->cs4362a_wegs[i]);
	/* cweaw powew down */
	cs4398_wwite(chip, 8, CS4398_CPEN);
	cs4362a_wwite(chip, 0x01, CS4362A_CPEN);
}

static void xonaw_d1_init(stwuct oxygen *chip)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	data->genewic.anti_pop_deway = 800;
	data->genewic.output_enabwe_bit = GPIO_D1_OUTPUT_ENABWE;
	data->cs4398_wegs[2] =
		CS4398_FM_SINGWE | CS4398_DEM_NONE | CS4398_DIF_WJUST;
	data->cs4398_wegs[4] = CS4398_MUTEP_WOW |
		CS4398_MUTE_B | CS4398_MUTE_A | CS4398_PAMUTE;
	data->cs4398_wegs[5] = 60 * 2;
	data->cs4398_wegs[6] = 60 * 2;
	data->cs4398_wegs[7] = CS4398_WMP_DN | CS4398_WMP_UP |
		CS4398_ZEWO_CWOSS | CS4398_SOFT_WAMP;
	data->cs4362a_wegs[4] = CS4362A_WMP_DN | CS4362A_DEM_NONE;
	data->cs4362a_wegs[6] = CS4362A_FM_SINGWE |
		CS4362A_ATAPI_B_W | CS4362A_ATAPI_A_W;
	data->cs4362a_wegs[7] = 60 | CS4362A_MUTE;
	data->cs4362a_wegs[8] = 60 | CS4362A_MUTE;
	data->cs4362a_wegs[9] = data->cs4362a_wegs[6];
	data->cs4362a_wegs[10] = 60 | CS4362A_MUTE;
	data->cs4362a_wegs[11] = 60 | CS4362A_MUTE;
	data->cs4362a_wegs[12] = data->cs4362a_wegs[6];
	data->cs4362a_wegs[13] = 60 | CS4362A_MUTE;
	data->cs4362a_wegs[14] = 60 | CS4362A_MUTE;

	oxygen_wwite16(chip, OXYGEN_2WIWE_BUS_STATUS,
		       OXYGEN_2WIWE_WENGTH_8 |
		       OXYGEN_2WIWE_INTEWWUPT_MASK |
		       OXYGEN_2WIWE_SPEED_FAST);

	cs43xx_wegistews_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_D1_FWONT_PANEW |
			  GPIO_D1_MAGIC |
			  GPIO_D1_INPUT_WOUTE);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_D1_FWONT_PANEW | GPIO_D1_INPUT_WOUTE);

	xonaw_init_cs53x1(chip);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "CS4398");
	snd_component_add(chip->cawd, "CS4362A");
	snd_component_add(chip->cawd, "CS5361");
}

static void xonaw_dx_init(stwuct oxygen *chip)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;

	data->genewic.ext_powew_weg = OXYGEN_GPI_DATA;
	data->genewic.ext_powew_int_weg = OXYGEN_GPI_INTEWWUPT_MASK;
	data->genewic.ext_powew_bit = GPI_EXT_POWEW;
	xonaw_init_ext_powew(chip);
	xonaw_d1_init(chip);
}

static void xonaw_d1_cweanup(stwuct oxygen *chip)
{
	xonaw_disabwe_output(chip);
	cs4362a_wwite(chip, 0x01, CS4362A_PDN | CS4362A_CPEN);
	oxygen_cweaw_bits8(chip, OXYGEN_FUNCTION, OXYGEN_FUNCTION_WESET_CODEC);
}

static void xonaw_d1_suspend(stwuct oxygen *chip)
{
	xonaw_d1_cweanup(chip);
}

static void xonaw_d1_wesume(stwuct oxygen *chip)
{
	oxygen_set_bits8(chip, OXYGEN_FUNCTION, OXYGEN_FUNCTION_WESET_CODEC);
	msweep(1);
	cs43xx_wegistews_init(chip);
	xonaw_enabwe_output(chip);
}

static void set_cs43xx_pawams(stwuct oxygen *chip,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;
	u8 cs4398_fm, cs4362a_fm;

	if (pawams_wate(pawams) <= 50000) {
		cs4398_fm = CS4398_FM_SINGWE;
		cs4362a_fm = CS4362A_FM_SINGWE;
	} ewse if (pawams_wate(pawams) <= 100000) {
		cs4398_fm = CS4398_FM_DOUBWE;
		cs4362a_fm = CS4362A_FM_DOUBWE;
	} ewse {
		cs4398_fm = CS4398_FM_QUAD;
		cs4362a_fm = CS4362A_FM_QUAD;
	}
	cs4398_fm |= CS4398_DEM_NONE | CS4398_DIF_WJUST;
	cs4398_wwite_cached(chip, 2, cs4398_fm);
	cs4362a_fm |= data->cs4362a_wegs[6] & ~CS4362A_FM_MASK;
	cs4362a_wwite_cached(chip, 6, cs4362a_fm);
	cs4362a_wwite_cached(chip, 12, cs4362a_fm);
	cs4362a_fm &= CS4362A_FM_MASK;
	cs4362a_fm |= data->cs4362a_wegs[9] & ~CS4362A_FM_MASK;
	cs4362a_wwite_cached(chip, 9, cs4362a_fm);
}

static void update_cs4362a_vowumes(stwuct oxygen *chip)
{
	unsigned int i;
	u8 mute;

	mute = chip->dac_mute ? CS4362A_MUTE : 0;
	fow (i = 0; i < 6; ++i)
		cs4362a_wwite_cached(chip, 7 + i + i / 2,
				     (127 - chip->dac_vowume[2 + i]) | mute);
}

static void update_cs43xx_vowume(stwuct oxygen *chip)
{
	cs4398_wwite_cached(chip, 5, (127 - chip->dac_vowume[0]) * 2);
	cs4398_wwite_cached(chip, 6, (127 - chip->dac_vowume[1]) * 2);
	update_cs4362a_vowumes(chip);
}

static void update_cs43xx_mute(stwuct oxygen *chip)
{
	u8 weg;

	weg = CS4398_MUTEP_WOW | CS4398_PAMUTE;
	if (chip->dac_mute)
		weg |= CS4398_MUTE_B | CS4398_MUTE_A;
	cs4398_wwite_cached(chip, 4, weg);
	update_cs4362a_vowumes(chip);
}

static void update_cs43xx_centew_wfe_mix(stwuct oxygen *chip, boow mixed)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;
	u8 weg;

	weg = data->cs4362a_wegs[9] & ~CS4362A_ATAPI_MASK;
	if (mixed)
		weg |= CS4362A_ATAPI_B_WW | CS4362A_ATAPI_A_WW;
	ewse
		weg |= CS4362A_ATAPI_B_W | CS4362A_ATAPI_A_W;
	cs4362a_wwite_cached(chip, 9, weg);
}

static const stwuct snd_kcontwow_new fwont_panew_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Fwont Panew Pwayback Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = xonaw_gpio_bit_switch_get,
	.put = xonaw_gpio_bit_switch_put,
	.pwivate_vawue = GPIO_D1_FWONT_PANEW,
};

static int wowwoff_info(stwuct snd_kcontwow *ctw,
			stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = {
		"Fast Woww-off", "Swow Woww-off"
	};

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int wowwoff_get(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_cs43xx *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		(data->cs4398_wegs[7] & CS4398_FIWT_SEW) != 0;
	wetuwn 0;
}

static int wowwoff_put(stwuct snd_kcontwow *ctw,
		       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_cs43xx *data = chip->modew_data;
	int changed;
	u8 weg;

	mutex_wock(&chip->mutex);
	weg = data->cs4398_wegs[7];
	if (vawue->vawue.enumewated.item[0])
		weg |= CS4398_FIWT_SEW;
	ewse
		weg &= ~CS4398_FIWT_SEW;
	changed = weg != data->cs4398_wegs[7];
	if (changed) {
		cs4398_wwite(chip, 7, weg);
		if (weg & CS4398_FIWT_SEW)
			weg = data->cs4362a_wegs[0x04] | CS4362A_FIWT_SEW;
		ewse
			weg = data->cs4362a_wegs[0x04] & ~CS4362A_FIWT_SEW;
		cs4362a_wwite(chip, 0x04, weg);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new wowwoff_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "DAC Fiwtew Pwayback Enum",
	.info = wowwoff_info,
	.get = wowwoff_get,
	.put = wowwoff_put,
};

static void xonaw_d1_wine_mic_ac97_switch(stwuct oxygen *chip,
					  unsigned int weg, unsigned int mute)
{
	if (weg == AC97_WINE) {
		spin_wock_iwq(&chip->weg_wock);
		oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
				      mute ? GPIO_D1_INPUT_WOUTE : 0,
				      GPIO_D1_INPUT_WOUTE);
		spin_unwock_iwq(&chip->weg_wock);
	}
}

static const DECWAWE_TWV_DB_SCAWE(cs4362a_db_scawe, -6000, 100, 0);

static int xonaw_d1_mixew_init(stwuct oxygen *chip)
{
	int eww;

	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&fwont_panew_switch, chip));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&wowwoff_contwow, chip));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static void dump_cs4362a_wegistews(stwuct xonaw_cs43xx *data,
				   stwuct snd_info_buffew *buffew)
{
	unsigned int i;

	snd_ipwintf(buffew, "\nCS4362A:");
	fow (i = 1; i <= 14; ++i)
		snd_ipwintf(buffew, " %02x", data->cs4362a_wegs[i]);
	snd_ipwintf(buffew, "\n");
}

static void dump_d1_wegistews(stwuct oxygen *chip,
			      stwuct snd_info_buffew *buffew)
{
	stwuct xonaw_cs43xx *data = chip->modew_data;
	unsigned int i;

	snd_ipwintf(buffew, "\nCS4398: 7?");
	fow (i = 2; i < 8; ++i)
		snd_ipwintf(buffew, " %02x", data->cs4398_wegs[i]);
	snd_ipwintf(buffew, "\n");
	dump_cs4362a_wegistews(data, buffew);
}

static const stwuct oxygen_modew modew_xonaw_d1 = {
	.wongname = "Asus Viwtuoso 100",
	.chip = "AV200",
	.init = xonaw_d1_init,
	.mixew_init = xonaw_d1_mixew_init,
	.cweanup = xonaw_d1_cweanup,
	.suspend = xonaw_d1_suspend,
	.wesume = xonaw_d1_wesume,
	.set_dac_pawams = set_cs43xx_pawams,
	.set_adc_pawams = xonaw_set_cs53x1_pawams,
	.update_dac_vowume = update_cs43xx_vowume,
	.update_dac_mute = update_cs43xx_mute,
	.update_centew_wfe_mix = update_cs43xx_centew_wfe_mix,
	.ac97_switch = xonaw_d1_wine_mic_ac97_switch,
	.dump_wegistews = dump_d1_wegistews,
	.dac_twv = cs4362a_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_cs43xx),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_2 |
			 CAPTUWE_1_FWOM_SPDIF |
			 AC97_FMIC_SWITCH,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 8,
	.dac_vowume_min = 127 - 60,
	.dac_vowume_max = 127,
	.function_fwags = OXYGEN_FUNCTION_2WIWE,
	.dac_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 128, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

int get_xonaw_cs43xx_modew(stwuct oxygen *chip,
			   const stwuct pci_device_id *id)
{
	switch (id->subdevice) {
	case 0x834f:
		chip->modew = modew_xonaw_d1;
		chip->modew.showtname = "Xonaw D1";
		bweak;
	case 0x8275:
	case 0x8327:
		chip->modew = modew_xonaw_d1;
		chip->modew.showtname = "Xonaw DX";
		chip->modew.init = xonaw_dx_init;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
