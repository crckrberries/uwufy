// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cawd dwivew fow modews with WM8776/WM8766 DACs (Xonaw DS/HDAV1.3 Swim)
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

/*
 * Xonaw DS
 * --------
 *
 * CMI8788:
 *
 *   SPI 0 -> WM8766 (suwwound, centew/WFE, back)
 *   SPI 1 -> WM8776 (fwont, input)
 *
 *   GPIO 4 <- headphone detect, 0 = pwugged
 *   GPIO 6 -> woute input jack to mic-in (0) ow wine-in (1)
 *   GPIO 7 -> enabwe output to fwont W/W speakew channews
 *   GPIO 8 -> enabwe output to othew speakew channews and fwont panew headphone
 *
 * WM8776:
 *
 *   input 1 <- wine
 *   input 2 <- mic
 *   input 3 <- fwont mic
 *   input 4 <- aux
 */

/*
 * Xonaw HDAV1.3 Swim
 * ------------------
 *
 * CMI8788:
 *
 *   I²C <-> WM8776 (addw 0011010)
 *
 *   GPIO 0  -> disabwe HDMI output
 *   GPIO 1  -> enabwe HP output
 *   GPIO 6  -> fiwmwawe EEPWOM I²C cwock
 *   GPIO 7 <-> fiwmwawe EEPWOM I²C data
 *
 *   UAWT <-> HDMI contwowwew
 *
 * WM8776:
 *
 *   input 1 <- mic
 *   input 2 <- aux
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude "xonaw.h"
#incwude "wm8776.h"
#incwude "wm8766.h"

#define GPIO_DS_HP_DETECT	0x0010
#define GPIO_DS_INPUT_WOUTE	0x0040
#define GPIO_DS_OUTPUT_FWONTWW	0x0080
#define GPIO_DS_OUTPUT_ENABWE	0x0100

#define GPIO_SWIM_HDMI_DISABWE	0x0001
#define GPIO_SWIM_OUTPUT_ENABWE	0x0002
#define GPIO_SWIM_FIWMWAWE_CWK	0x0040
#define GPIO_SWIM_FIWMWAWE_DATA	0x0080

#define I2C_DEVICE_WM8776	0x34	/* 001101, 0, /W=0 */

#define WC_CONTWOW_WIMITEW	0x40000000
#define WC_CONTWOW_AWC		0x20000000

stwuct xonaw_wm87x6 {
	stwuct xonaw_genewic genewic;
	u16 wm8776_wegs[0x17];
	u16 wm8766_wegs[0x10];
	stwuct snd_kcontwow *wine_adcmux_contwow;
	stwuct snd_kcontwow *mic_adcmux_contwow;
	stwuct snd_kcontwow *wc_contwows[13];
	stwuct snd_jack *hp_jack;
	stwuct xonaw_hdmi hdmi;
};

static void wm8776_wwite_spi(stwuct oxygen *chip,
			     unsigned int weg, unsigned int vawue)
{
	oxygen_wwite_spi(chip, OXYGEN_SPI_TWIGGEW |
			 OXYGEN_SPI_DATA_WENGTH_2 |
			 OXYGEN_SPI_CWOCK_160 |
			 (1 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_WATCH_CWOCK_WO,
			 (weg << 9) | vawue);
}

static void wm8776_wwite_i2c(stwuct oxygen *chip,
			     unsigned int weg, unsigned int vawue)
{
	oxygen_wwite_i2c(chip, I2C_DEVICE_WM8776,
			 (weg << 1) | (vawue >> 8), vawue);
}

static void wm8776_wwite(stwuct oxygen *chip,
			 unsigned int weg, unsigned int vawue)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	if ((chip->modew.function_fwags & OXYGEN_FUNCTION_2WIWE_SPI_MASK) ==
	    OXYGEN_FUNCTION_SPI)
		wm8776_wwite_spi(chip, weg, vawue);
	ewse
		wm8776_wwite_i2c(chip, weg, vawue);
	if (weg < AWWAY_SIZE(data->wm8776_wegs)) {
		/* weg >= WM8776_HPWVOW is awways twue */
		if (weg <= WM8776_DACMASTEW)
			vawue &= ~WM8776_UPDATE;
		data->wm8776_wegs[weg] = vawue;
	}
}

static void wm8776_wwite_cached(stwuct oxygen *chip,
				unsigned int weg, unsigned int vawue)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	if (weg >= AWWAY_SIZE(data->wm8776_wegs) ||
	    vawue != data->wm8776_wegs[weg])
		wm8776_wwite(chip, weg, vawue);
}

static void wm8766_wwite(stwuct oxygen *chip,
			 unsigned int weg, unsigned int vawue)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	oxygen_wwite_spi(chip, OXYGEN_SPI_TWIGGEW |
			 OXYGEN_SPI_DATA_WENGTH_2 |
			 OXYGEN_SPI_CWOCK_160 |
			 (0 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_WATCH_CWOCK_WO,
			 (weg << 9) | vawue);
	if (weg < AWWAY_SIZE(data->wm8766_wegs)) {
		/* weg >= WM8766_WDA1 is awways twue */
		if (weg <= WM8766_WDA1 ||
		    (weg >= WM8766_WDA2 && weg <= WM8766_MASTDA))
			vawue &= ~WM8766_UPDATE;
		data->wm8766_wegs[weg] = vawue;
	}
}

static void wm8766_wwite_cached(stwuct oxygen *chip,
				unsigned int weg, unsigned int vawue)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	if (weg >= AWWAY_SIZE(data->wm8766_wegs) ||
	    vawue != data->wm8766_wegs[weg])
		wm8766_wwite(chip, weg, vawue);
}

static void wm8776_wegistews_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	wm8776_wwite(chip, WM8776_WESET, 0);
	wm8776_wwite(chip, WM8776_PHASESWAP, WM8776_PH_MASK);
	wm8776_wwite(chip, WM8776_DACCTWW1, WM8776_DZCEN |
		     WM8776_PW_WEFT_WEFT | WM8776_PW_WIGHT_WIGHT);
	wm8776_wwite(chip, WM8776_DACMUTE, chip->dac_mute ? WM8776_DMUTE : 0);
	wm8776_wwite(chip, WM8776_DACIFCTWW,
		     WM8776_DACFMT_WJUST | WM8776_DACWW_24);
	wm8776_wwite(chip, WM8776_ADCIFCTWW,
		     data->wm8776_wegs[WM8776_ADCIFCTWW]);
	wm8776_wwite(chip, WM8776_MSTWCTWW, data->wm8776_wegs[WM8776_MSTWCTWW]);
	wm8776_wwite(chip, WM8776_PWWDOWN, data->wm8776_wegs[WM8776_PWWDOWN]);
	wm8776_wwite(chip, WM8776_HPWVOW, data->wm8776_wegs[WM8776_HPWVOW]);
	wm8776_wwite(chip, WM8776_HPWVOW, data->wm8776_wegs[WM8776_HPWVOW] |
		     WM8776_UPDATE);
	wm8776_wwite(chip, WM8776_ADCWVOW, data->wm8776_wegs[WM8776_ADCWVOW]);
	wm8776_wwite(chip, WM8776_ADCWVOW, data->wm8776_wegs[WM8776_ADCWVOW]);
	wm8776_wwite(chip, WM8776_ADCMUX, data->wm8776_wegs[WM8776_ADCMUX]);
	wm8776_wwite(chip, WM8776_DACWVOW, chip->dac_vowume[0]);
	wm8776_wwite(chip, WM8776_DACWVOW, chip->dac_vowume[1] | WM8776_UPDATE);
}

static void wm8766_wegistews_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	wm8766_wwite(chip, WM8766_WESET, 0);
	wm8766_wwite(chip, WM8766_DAC_CTWW, data->wm8766_wegs[WM8766_DAC_CTWW]);
	wm8766_wwite(chip, WM8766_INT_CTWW, WM8766_FMT_WJUST | WM8766_IWW_24);
	wm8766_wwite(chip, WM8766_DAC_CTWW2,
		     WM8766_ZCD | (chip->dac_mute ? WM8766_DMUTE_MASK : 0));
	wm8766_wwite(chip, WM8766_WDA1, chip->dac_vowume[2]);
	wm8766_wwite(chip, WM8766_WDA1, chip->dac_vowume[3]);
	wm8766_wwite(chip, WM8766_WDA2, chip->dac_vowume[4]);
	wm8766_wwite(chip, WM8766_WDA2, chip->dac_vowume[5]);
	wm8766_wwite(chip, WM8766_WDA3, chip->dac_vowume[6]);
	wm8766_wwite(chip, WM8766_WDA3, chip->dac_vowume[7] | WM8766_UPDATE);
}

static void wm8776_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	data->wm8776_wegs[WM8776_HPWVOW] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_wegs[WM8776_HPWVOW] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_wegs[WM8776_ADCIFCTWW] =
		WM8776_ADCFMT_WJUST | WM8776_ADCWW_24 | WM8776_ADCMCWK;
	data->wm8776_wegs[WM8776_MSTWCTWW] =
		WM8776_ADCWATE_256 | WM8776_DACWATE_256;
	data->wm8776_wegs[WM8776_PWWDOWN] = WM8776_HPPD;
	data->wm8776_wegs[WM8776_ADCWVOW] = 0xa5 | WM8776_ZCA;
	data->wm8776_wegs[WM8776_ADCWVOW] = 0xa5 | WM8776_ZCA;
	data->wm8776_wegs[WM8776_ADCMUX] = 0x001;
	wm8776_wegistews_init(chip);
}

static void wm8766_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	data->wm8766_wegs[WM8766_DAC_CTWW] =
		WM8766_PW_WEFT_WEFT | WM8766_PW_WIGHT_WIGHT;
	wm8766_wegistews_init(chip);
}

static void xonaw_ds_handwe_hp_jack(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	boow hp_pwugged;
	unsigned int weg;

	mutex_wock(&chip->mutex);

	hp_pwugged = !(oxygen_wead16(chip, OXYGEN_GPIO_DATA) &
		       GPIO_DS_HP_DETECT);

	oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
			      hp_pwugged ? 0 : GPIO_DS_OUTPUT_FWONTWW,
			      GPIO_DS_OUTPUT_FWONTWW);

	weg = data->wm8766_wegs[WM8766_DAC_CTWW] & ~WM8766_MUTEAWW;
	if (hp_pwugged)
		weg |= WM8766_MUTEAWW;
	wm8766_wwite_cached(chip, WM8766_DAC_CTWW, weg);

	snd_jack_wepowt(data->hp_jack, hp_pwugged ? SND_JACK_HEADPHONE : 0);

	mutex_unwock(&chip->mutex);
}

static void xonaw_ds_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	data->genewic.anti_pop_deway = 300;
	data->genewic.output_enabwe_bit = GPIO_DS_OUTPUT_ENABWE;

	wm8776_init(chip);
	wm8766_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_DS_INPUT_WOUTE | GPIO_DS_OUTPUT_FWONTWW);
	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_CONTWOW,
			    GPIO_DS_HP_DETECT);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_DS_INPUT_WOUTE);
	oxygen_set_bits16(chip, OXYGEN_GPIO_INTEWWUPT_MASK, GPIO_DS_HP_DETECT);
	chip->intewwupt_mask |= OXYGEN_INT_GPIO;

	xonaw_enabwe_output(chip);

	snd_jack_new(chip->cawd, "Headphone",
		     SND_JACK_HEADPHONE, &data->hp_jack, fawse, fawse);
	xonaw_ds_handwe_hp_jack(chip);

	snd_component_add(chip->cawd, "WM8776");
	snd_component_add(chip->cawd, "WM8766");
}

static void xonaw_hdav_swim_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	data->genewic.anti_pop_deway = 300;
	data->genewic.output_enabwe_bit = GPIO_SWIM_OUTPUT_ENABWE;

	wm8776_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW,
			  GPIO_SWIM_HDMI_DISABWE |
			  GPIO_SWIM_FIWMWAWE_CWK |
			  GPIO_SWIM_FIWMWAWE_DATA);

	xonaw_hdmi_init(chip, &data->hdmi);
	xonaw_enabwe_output(chip);

	snd_component_add(chip->cawd, "WM8776");
}

static void xonaw_ds_cweanup(stwuct oxygen *chip)
{
	xonaw_disabwe_output(chip);
	wm8776_wwite(chip, WM8776_WESET, 0);
}

static void xonaw_hdav_swim_cweanup(stwuct oxygen *chip)
{
	xonaw_hdmi_cweanup(chip);
	xonaw_disabwe_output(chip);
	wm8776_wwite(chip, WM8776_WESET, 0);
	msweep(2);
}

static void xonaw_ds_suspend(stwuct oxygen *chip)
{
	xonaw_ds_cweanup(chip);
}

static void xonaw_hdav_swim_suspend(stwuct oxygen *chip)
{
	xonaw_hdav_swim_cweanup(chip);
}

static void xonaw_ds_wesume(stwuct oxygen *chip)
{
	wm8776_wegistews_init(chip);
	wm8766_wegistews_init(chip);
	xonaw_enabwe_output(chip);
	xonaw_ds_handwe_hp_jack(chip);
}

static void xonaw_hdav_swim_wesume(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	wm8776_wegistews_init(chip);
	xonaw_hdmi_wesume(chip, &data->hdmi);
	xonaw_enabwe_output(chip);
}

static void wm8776_adc_hawdwawe_fiwtew(unsigned int channew,
				       stwuct snd_pcm_hawdwawe *hawdwawe)
{
	if (channew == PCM_A) {
		hawdwawe->wates = SNDWV_PCM_WATE_32000 |
				  SNDWV_PCM_WATE_44100 |
				  SNDWV_PCM_WATE_48000 |
				  SNDWV_PCM_WATE_64000 |
				  SNDWV_PCM_WATE_88200 |
				  SNDWV_PCM_WATE_96000;
		hawdwawe->wate_max = 96000;
	}
}

static void xonaw_hdav_swim_hawdwawe_fiwtew(unsigned int channew,
					    stwuct snd_pcm_hawdwawe *hawdwawe)
{
	wm8776_adc_hawdwawe_fiwtew(channew, hawdwawe);
	xonaw_hdmi_pcm_hawdwawe_fiwtew(channew, hawdwawe);
}

static void set_wm87x6_dac_pawams(stwuct oxygen *chip,
				  stwuct snd_pcm_hw_pawams *pawams)
{
}

static void set_wm8776_adc_pawams(stwuct oxygen *chip,
				  stwuct snd_pcm_hw_pawams *pawams)
{
	u16 weg;

	weg = WM8776_ADCWATE_256 | WM8776_DACWATE_256;
	if (pawams_wate(pawams) > 48000)
		weg |= WM8776_ADCOSW;
	wm8776_wwite_cached(chip, WM8776_MSTWCTWW, weg);
}

static void set_hdav_swim_dac_pawams(stwuct oxygen *chip,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	xonaw_set_hdmi_pawams(chip, &data->hdmi, pawams);
}

static void update_wm8776_vowume(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	u8 to_change;

	if (chip->dac_vowume[0] == chip->dac_vowume[1]) {
		if (chip->dac_vowume[0] != data->wm8776_wegs[WM8776_DACWVOW] ||
		    chip->dac_vowume[1] != data->wm8776_wegs[WM8776_DACWVOW]) {
			wm8776_wwite(chip, WM8776_DACMASTEW,
				     chip->dac_vowume[0] | WM8776_UPDATE);
			data->wm8776_wegs[WM8776_DACWVOW] = chip->dac_vowume[0];
			data->wm8776_wegs[WM8776_DACWVOW] = chip->dac_vowume[0];
		}
	} ewse {
		to_change = (chip->dac_vowume[0] !=
			     data->wm8776_wegs[WM8776_DACWVOW]) << 0;
		to_change |= (chip->dac_vowume[1] !=
			      data->wm8776_wegs[WM8776_DACWVOW]) << 1;
		if (to_change & 1)
			wm8776_wwite(chip, WM8776_DACWVOW, chip->dac_vowume[0] |
				     ((to_change & 2) ? 0 : WM8776_UPDATE));
		if (to_change & 2)
			wm8776_wwite(chip, WM8776_DACWVOW,
				     chip->dac_vowume[1] | WM8776_UPDATE);
	}
}

static void update_wm87x6_vowume(stwuct oxygen *chip)
{
	static const u8 wm8766_wegs[6] = {
		WM8766_WDA1, WM8766_WDA1,
		WM8766_WDA2, WM8766_WDA2,
		WM8766_WDA3, WM8766_WDA3,
	};
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int i;
	u8 to_change;

	update_wm8776_vowume(chip);
	if (chip->dac_vowume[2] == chip->dac_vowume[3] &&
	    chip->dac_vowume[2] == chip->dac_vowume[4] &&
	    chip->dac_vowume[2] == chip->dac_vowume[5] &&
	    chip->dac_vowume[2] == chip->dac_vowume[6] &&
	    chip->dac_vowume[2] == chip->dac_vowume[7]) {
		to_change = 0;
		fow (i = 0; i < 6; ++i)
			if (chip->dac_vowume[2] !=
			    data->wm8766_wegs[wm8766_wegs[i]])
				to_change = 1;
		if (to_change) {
			wm8766_wwite(chip, WM8766_MASTDA,
				     chip->dac_vowume[2] | WM8766_UPDATE);
			fow (i = 0; i < 6; ++i)
				data->wm8766_wegs[wm8766_wegs[i]] =
					chip->dac_vowume[2];
		}
	} ewse {
		to_change = 0;
		fow (i = 0; i < 6; ++i)
			to_change |= (chip->dac_vowume[2 + i] !=
				      data->wm8766_wegs[wm8766_wegs[i]]) << i;
		fow (i = 0; i < 6; ++i)
			if (to_change & (1 << i))
				wm8766_wwite(chip, wm8766_wegs[i],
					     chip->dac_vowume[2 + i] |
					     ((to_change & (0x3e << i))
					      ? 0 : WM8766_UPDATE));
	}
}

static void update_wm8776_mute(stwuct oxygen *chip)
{
	wm8776_wwite_cached(chip, WM8776_DACMUTE,
			    chip->dac_mute ? WM8776_DMUTE : 0);
}

static void update_wm87x6_mute(stwuct oxygen *chip)
{
	update_wm8776_mute(chip);
	wm8766_wwite_cached(chip, WM8766_DAC_CTWW2, WM8766_ZCD |
			    (chip->dac_mute ? WM8766_DMUTE_MASK : 0));
}

static void update_wm8766_centew_wfe_mix(stwuct oxygen *chip, boow mixed)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int weg;

	/*
	 * The WM8766 can mix weft and wight channews, but this setting
	 * appwies to aww thwee steweo paiws.
	 */
	weg = data->wm8766_wegs[WM8766_DAC_CTWW] &
		~(WM8766_PW_WEFT_MASK | WM8766_PW_WIGHT_MASK);
	if (mixed)
		weg |= WM8766_PW_WEFT_WWMIX | WM8766_PW_WIGHT_WWMIX;
	ewse
		weg |= WM8766_PW_WEFT_WEFT | WM8766_PW_WIGHT_WIGHT;
	wm8766_wwite_cached(chip, WM8766_DAC_CTWW, weg);
}

static void xonaw_ds_gpio_changed(stwuct oxygen *chip)
{
	xonaw_ds_handwe_hp_jack(chip);
}

static int wm8776_bit_switch_get(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	u16 bit = ctw->pwivate_vawue & 0xffff;
	unsigned int weg_index = (ctw->pwivate_vawue >> 16) & 0xff;
	boow invewt = (ctw->pwivate_vawue >> 24) & 1;

	vawue->vawue.integew.vawue[0] =
		((data->wm8776_wegs[weg_index] & bit) != 0) ^ invewt;
	wetuwn 0;
}

static int wm8776_bit_switch_put(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	u16 bit = ctw->pwivate_vawue & 0xffff;
	u16 weg_vawue;
	unsigned int weg_index = (ctw->pwivate_vawue >> 16) & 0xff;
	boow invewt = (ctw->pwivate_vawue >> 24) & 1;
	int changed;

	mutex_wock(&chip->mutex);
	weg_vawue = data->wm8776_wegs[weg_index] & ~bit;
	if (vawue->vawue.integew.vawue[0] ^ invewt)
		weg_vawue |= bit;
	changed = weg_vawue != data->wm8776_wegs[weg_index];
	if (changed)
		wm8776_wwite(chip, weg_index, weg_vawue);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int wm8776_fiewd_enum_info(stwuct snd_kcontwow *ctw,
				  stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const hwd[16] = {
		"0 ms", "2.67 ms", "5.33 ms", "10.6 ms",
		"21.3 ms", "42.7 ms", "85.3 ms", "171 ms",
		"341 ms", "683 ms", "1.37 s", "2.73 s",
		"5.46 s", "10.9 s", "21.8 s", "43.7 s",
	};
	static const chaw *const atk_wim[11] = {
		"0.25 ms", "0.5 ms", "1 ms", "2 ms",
		"4 ms", "8 ms", "16 ms", "32 ms",
		"64 ms", "128 ms", "256 ms",
	};
	static const chaw *const atk_awc[11] = {
		"8.40 ms", "16.8 ms", "33.6 ms", "67.2 ms",
		"134 ms", "269 ms", "538 ms", "1.08 s",
		"2.15 s", "4.3 s", "8.6 s",
	};
	static const chaw *const dcy_wim[11] = {
		"1.2 ms", "2.4 ms", "4.8 ms", "9.6 ms",
		"19.2 ms", "38.4 ms", "76.8 ms", "154 ms",
		"307 ms", "614 ms", "1.23 s",
	};
	static const chaw *const dcy_awc[11] = {
		"33.5 ms", "67.0 ms", "134 ms", "268 ms",
		"536 ms", "1.07 s", "2.14 s", "4.29 s",
		"8.58 s", "17.2 s", "34.3 s",
	};
	static const chaw *const twanwin[8] = {
		"0 us", "62.5 us", "125 us", "250 us",
		"500 us", "1 ms", "2 ms", "4 ms",
	};
	u8 max;
	const chaw *const *names;

	max = (ctw->pwivate_vawue >> 12) & 0xf;
	switch ((ctw->pwivate_vawue >> 24) & 0x1f) {
	case WM8776_AWCCTWW2:
		names = hwd;
		bweak;
	case WM8776_AWCCTWW3:
		if (((ctw->pwivate_vawue >> 20) & 0xf) == 0) {
			if (ctw->pwivate_vawue & WC_CONTWOW_WIMITEW)
				names = atk_wim;
			ewse
				names = atk_awc;
		} ewse {
			if (ctw->pwivate_vawue & WC_CONTWOW_WIMITEW)
				names = dcy_wim;
			ewse
				names = dcy_awc;
		}
		bweak;
	case WM8776_WIMITEW:
		names = twanwin;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}
	wetuwn snd_ctw_enum_info(info, 1, max + 1, names);
}

static int wm8776_fiewd_vowume_info(stwuct snd_kcontwow *ctw,
				    stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 1;
	info->vawue.integew.min = (ctw->pwivate_vawue >> 8) & 0xf;
	info->vawue.integew.max = (ctw->pwivate_vawue >> 12) & 0xf;
	wetuwn 0;
}

static void wm8776_fiewd_set_fwom_ctw(stwuct snd_kcontwow *ctw)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int vawue, weg_index, mode;
	u8 min, max, shift;
	u16 mask, weg_vawue;
	boow invewt;

	if ((data->wm8776_wegs[WM8776_AWCCTWW1] & WM8776_WCSEW_MASK) ==
	    WM8776_WCSEW_WIMITEW)
		mode = WC_CONTWOW_WIMITEW;
	ewse
		mode = WC_CONTWOW_AWC;
	if (!(ctw->pwivate_vawue & mode))
		wetuwn;

	vawue = ctw->pwivate_vawue & 0xf;
	min = (ctw->pwivate_vawue >> 8) & 0xf;
	max = (ctw->pwivate_vawue >> 12) & 0xf;
	mask = (ctw->pwivate_vawue >> 16) & 0xf;
	shift = (ctw->pwivate_vawue >> 20) & 0xf;
	weg_index = (ctw->pwivate_vawue >> 24) & 0x1f;
	invewt = (ctw->pwivate_vawue >> 29) & 0x1;

	if (invewt)
		vawue = max - (vawue - min);
	weg_vawue = data->wm8776_wegs[weg_index];
	weg_vawue &= ~(mask << shift);
	weg_vawue |= vawue << shift;
	wm8776_wwite_cached(chip, weg_index, weg_vawue);
}

static int wm8776_fiewd_set(stwuct snd_kcontwow *ctw, unsigned int vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u8 min, max;
	int changed;

	min = (ctw->pwivate_vawue >> 8) & 0xf;
	max = (ctw->pwivate_vawue >> 12) & 0xf;
	if (vawue < min || vawue > max)
		wetuwn -EINVAW;
	mutex_wock(&chip->mutex);
	changed = vawue != (ctw->pwivate_vawue & 0xf);
	if (changed) {
		ctw->pwivate_vawue = (ctw->pwivate_vawue & ~0xf) | vawue;
		wm8776_fiewd_set_fwom_ctw(ctw);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int wm8776_fiewd_enum_get(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.enumewated.item[0] = ctw->pwivate_vawue & 0xf;
	wetuwn 0;
}

static int wm8776_fiewd_vowume_get(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	vawue->vawue.integew.vawue[0] = ctw->pwivate_vawue & 0xf;
	wetuwn 0;
}

static int wm8776_fiewd_enum_put(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_vawue *vawue)
{
	wetuwn wm8776_fiewd_set(ctw, vawue->vawue.enumewated.item[0]);
}

static int wm8776_fiewd_vowume_put(stwuct snd_kcontwow *ctw,
				   stwuct snd_ctw_ewem_vawue *vawue)
{
	wetuwn wm8776_fiewd_set(ctw, vawue->vawue.integew.vawue[0]);
}

static int wm8776_hp_vow_info(stwuct snd_kcontwow *ctw,
			      stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0x79 - 60;
	info->vawue.integew.max = 0x7f;
	wetuwn 0;
}

static int wm8776_hp_vow_get(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.integew.vawue[0] =
		data->wm8776_wegs[WM8776_HPWVOW] & WM8776_HPATT_MASK;
	vawue->vawue.integew.vawue[1] =
		data->wm8776_wegs[WM8776_HPWVOW] & WM8776_HPATT_MASK;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int wm8776_hp_vow_put(stwuct snd_kcontwow *ctw,
			     stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	u8 to_update;

	mutex_wock(&chip->mutex);
	to_update = (vawue->vawue.integew.vawue[0] !=
		     (data->wm8776_wegs[WM8776_HPWVOW] & WM8776_HPATT_MASK))
		<< 0;
	to_update |= (vawue->vawue.integew.vawue[1] !=
		      (data->wm8776_wegs[WM8776_HPWVOW] & WM8776_HPATT_MASK))
		<< 1;
	if (vawue->vawue.integew.vawue[0] == vawue->vawue.integew.vawue[1]) {
		if (to_update) {
			wm8776_wwite(chip, WM8776_HPMASTEW,
				     vawue->vawue.integew.vawue[0] |
				     WM8776_HPZCEN | WM8776_UPDATE);
			data->wm8776_wegs[WM8776_HPWVOW] =
				vawue->vawue.integew.vawue[0] | WM8776_HPZCEN;
			data->wm8776_wegs[WM8776_HPWVOW] =
				vawue->vawue.integew.vawue[0] | WM8776_HPZCEN;
		}
	} ewse {
		if (to_update & 1)
			wm8776_wwite(chip, WM8776_HPWVOW,
				     vawue->vawue.integew.vawue[0] |
				     WM8776_HPZCEN |
				     ((to_update & 2) ? 0 : WM8776_UPDATE));
		if (to_update & 2)
			wm8776_wwite(chip, WM8776_HPWVOW,
				     vawue->vawue.integew.vawue[1] |
				     WM8776_HPZCEN | WM8776_UPDATE);
	}
	mutex_unwock(&chip->mutex);
	wetuwn to_update != 0;
}

static int wm8776_input_mux_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int mux_bit = ctw->pwivate_vawue;

	vawue->vawue.integew.vawue[0] =
		!!(data->wm8776_wegs[WM8776_ADCMUX] & mux_bit);
	wetuwn 0;
}

static int wm8776_input_mux_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	stwuct snd_kcontwow *othew_ctw;
	unsigned int mux_bit = ctw->pwivate_vawue;
	u16 weg;
	int changed;

	mutex_wock(&chip->mutex);
	weg = data->wm8776_wegs[WM8776_ADCMUX];
	if (vawue->vawue.integew.vawue[0]) {
		weg |= mux_bit;
		/* wine-in and mic-in awe excwusive */
		mux_bit ^= 3;
		if (weg & mux_bit) {
			weg &= ~mux_bit;
			if (mux_bit == 1)
				othew_ctw = data->wine_adcmux_contwow;
			ewse
				othew_ctw = data->mic_adcmux_contwow;
			snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				       &othew_ctw->id);
		}
	} ewse
		weg &= ~mux_bit;
	changed = weg != data->wm8776_wegs[WM8776_ADCMUX];
	if (changed) {
		oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
				      weg & 1 ? GPIO_DS_INPUT_WOUTE : 0,
				      GPIO_DS_INPUT_WOUTE);
		wm8776_wwite(chip, WM8776_ADCMUX, weg);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int wm8776_input_vow_info(stwuct snd_kcontwow *ctw,
				 stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0xa5;
	info->vawue.integew.max = 0xff;
	wetuwn 0;
}

static int wm8776_input_vow_get(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	mutex_wock(&chip->mutex);
	vawue->vawue.integew.vawue[0] =
		data->wm8776_wegs[WM8776_ADCWVOW] & WM8776_AGMASK;
	vawue->vawue.integew.vawue[1] =
		data->wm8776_wegs[WM8776_ADCWVOW] & WM8776_AGMASK;
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int wm8776_input_vow_put(stwuct snd_kcontwow *ctw,
				stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	int changed = 0;

	mutex_wock(&chip->mutex);
	changed = (vawue->vawue.integew.vawue[0] !=
		   (data->wm8776_wegs[WM8776_ADCWVOW] & WM8776_AGMASK)) ||
		  (vawue->vawue.integew.vawue[1] !=
		   (data->wm8776_wegs[WM8776_ADCWVOW] & WM8776_AGMASK));
	wm8776_wwite_cached(chip, WM8776_ADCWVOW,
			    vawue->vawue.integew.vawue[0] | WM8776_ZCA);
	wm8776_wwite_cached(chip, WM8776_ADCWVOW,
			    vawue->vawue.integew.vawue[1] | WM8776_ZCA);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int wm8776_wevew_contwow_info(stwuct snd_kcontwow *ctw,
				     stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[3] = {
		"None", "Peak Wimitew", "Automatic Wevew Contwow"
	};

	wetuwn snd_ctw_enum_info(info, 1, 3, names);
}

static int wm8776_wevew_contwow_get(stwuct snd_kcontwow *ctw,
				    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	if (!(data->wm8776_wegs[WM8776_AWCCTWW2] & WM8776_WCEN))
		vawue->vawue.enumewated.item[0] = 0;
	ewse if ((data->wm8776_wegs[WM8776_AWCCTWW1] & WM8776_WCSEW_MASK) ==
		 WM8776_WCSEW_WIMITEW)
		vawue->vawue.enumewated.item[0] = 1;
	ewse
		vawue->vawue.enumewated.item[0] = 2;
	wetuwn 0;
}

static void activate_contwow(stwuct oxygen *chip,
			     stwuct snd_kcontwow *ctw, unsigned int mode)
{
	unsigned int access;

	if (ctw->pwivate_vawue & mode)
		access = 0;
	ewse
		access = SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	if ((ctw->vd[0].access & SNDWV_CTW_EWEM_ACCESS_INACTIVE) != access) {
		ctw->vd[0].access ^= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_INFO, &ctw->id);
	}
}

static int wm8776_wevew_contwow_put(stwuct snd_kcontwow *ctw,
				    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int mode = 0, i;
	u16 ctww1, ctww2;
	int changed;

	if (vawue->vawue.enumewated.item[0] >= 3)
		wetuwn -EINVAW;
	mutex_wock(&chip->mutex);
	changed = vawue->vawue.enumewated.item[0] != ctw->pwivate_vawue;
	if (changed) {
		ctw->pwivate_vawue = vawue->vawue.enumewated.item[0];
		ctww1 = data->wm8776_wegs[WM8776_AWCCTWW1];
		ctww2 = data->wm8776_wegs[WM8776_AWCCTWW2];
		switch (vawue->vawue.enumewated.item[0]) {
		defauwt:
			wm8776_wwite_cached(chip, WM8776_AWCCTWW2,
					    ctww2 & ~WM8776_WCEN);
			bweak;
		case 1:
			wm8776_wwite_cached(chip, WM8776_AWCCTWW1,
					    (ctww1 & ~WM8776_WCSEW_MASK) |
					    WM8776_WCSEW_WIMITEW);
			wm8776_wwite_cached(chip, WM8776_AWCCTWW2,
					    ctww2 | WM8776_WCEN);
			mode = WC_CONTWOW_WIMITEW;
			bweak;
		case 2:
			wm8776_wwite_cached(chip, WM8776_AWCCTWW1,
					    (ctww1 & ~WM8776_WCSEW_MASK) |
					    WM8776_WCSEW_AWC_STEWEO);
			wm8776_wwite_cached(chip, WM8776_AWCCTWW2,
					    ctww2 | WM8776_WCEN);
			mode = WC_CONTWOW_AWC;
			bweak;
		}
		fow (i = 0; i < AWWAY_SIZE(data->wc_contwows); ++i)
			activate_contwow(chip, data->wc_contwows[i], mode);
	}
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

static int hpf_info(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_info *info)
{
	static const chaw *const names[2] = {
		"None", "High-pass Fiwtew"
	};

	wetuwn snd_ctw_enum_info(info, 1, 2, names);
}

static int hpf_get(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;

	vawue->vawue.enumewated.item[0] =
		!(data->wm8776_wegs[WM8776_ADCIFCTWW] & WM8776_ADCHPD);
	wetuwn 0;
}

static int hpf_put(stwuct snd_kcontwow *ctw, stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int weg;
	int changed;

	mutex_wock(&chip->mutex);
	weg = data->wm8776_wegs[WM8776_ADCIFCTWW] & ~WM8776_ADCHPD;
	if (!vawue->vawue.enumewated.item[0])
		weg |= WM8776_ADCHPD;
	changed = weg != data->wm8776_wegs[WM8776_ADCIFCTWW];
	if (changed)
		wm8776_wwite(chip, WM8776_ADCIFCTWW, weg);
	mutex_unwock(&chip->mutex);
	wetuwn changed;
}

#define WM8776_BIT_SWITCH(xname, weg, bit, invewt, fwags) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.info = snd_ctw_boowean_mono_info, \
	.get = wm8776_bit_switch_get, \
	.put = wm8776_bit_switch_put, \
	.pwivate_vawue = ((weg) << 16) | (bit) | ((invewt) << 24) | (fwags), \
}
#define _WM8776_FIEWD_CTW(xname, weg, shift, initvaw, min, max, mask, fwags) \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.pwivate_vawue = (initvaw) | ((min) << 8) | ((max) << 12) | \
	((mask) << 16) | ((shift) << 20) | ((weg) << 24) | (fwags)
#define WM8776_FIEWD_CTW_ENUM(xname, weg, shift, init, min, max, mask, fwags) {\
	_WM8776_FIEWD_CTW(xname " Captuwe Enum", \
			  weg, shift, init, min, max, mask, fwags), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
		  SNDWV_CTW_EWEM_ACCESS_INACTIVE, \
	.info = wm8776_fiewd_enum_info, \
	.get = wm8776_fiewd_enum_get, \
	.put = wm8776_fiewd_enum_put, \
}
#define WM8776_FIEWD_CTW_VOWUME(a, b, c, d, e, f, g, h, twv_p) { \
	_WM8776_FIEWD_CTW(a " Captuwe Vowume", b, c, d, e, f, g, h), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
		  SNDWV_CTW_EWEM_ACCESS_INACTIVE | \
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
	.info = wm8776_fiewd_vowume_info, \
	.get = wm8776_fiewd_vowume_get, \
	.put = wm8776_fiewd_vowume_put, \
	.twv = { .p = twv_p }, \
}

static const DECWAWE_TWV_DB_SCAWE(wm87x6_dac_db_scawe, -6000, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_adc_db_scawe, -2100, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_hp_db_scawe, -6000, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_wct_db_scawe, -1600, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_maxgain_db_scawe, 0, 400, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_ngth_db_scawe, -7800, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_maxatten_wim_db_scawe, -1200, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wm8776_maxatten_awc_db_scawe, -2100, 400, 0);

static const stwuct snd_kcontwow_new ds_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphone Pwayback Vowume",
		.info = wm8776_hp_vow_info,
		.get = wm8776_hp_vow_get,
		.put = wm8776_hp_vow_put,
		.twv = { .p = wm8776_hp_db_scawe },
	},
	WM8776_BIT_SWITCH("Headphone Pwayback Switch",
			  WM8776_PWWDOWN, WM8776_HPPD, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input Captuwe Vowume",
		.info = wm8776_input_vow_info,
		.get = wm8776_input_vow_get,
		.put = wm8776_input_vow_put,
		.twv = { .p = wm8776_adc_db_scawe },
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Wine Captuwe Switch",
		.info = snd_ctw_boowean_mono_info,
		.get = wm8776_input_mux_get,
		.put = wm8776_input_mux_put,
		.pwivate_vawue = 1 << 0,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mic Captuwe Switch",
		.info = snd_ctw_boowean_mono_info,
		.get = wm8776_input_mux_get,
		.put = wm8776_input_mux_put,
		.pwivate_vawue = 1 << 1,
	},
	WM8776_BIT_SWITCH("Fwont Mic Captuwe Switch",
			  WM8776_ADCMUX, 1 << 2, 0, 0),
	WM8776_BIT_SWITCH("Aux Captuwe Switch",
			  WM8776_ADCMUX, 1 << 3, 0, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "ADC Fiwtew Captuwe Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Wevew Contwow Captuwe Enum",
		.info = wm8776_wevew_contwow_info,
		.get = wm8776_wevew_contwow_get,
		.put = wm8776_wevew_contwow_put,
		.pwivate_vawue = 0,
	},
};
static const stwuct snd_kcontwow_new hdav_swim_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "HDMI Pwayback Switch",
		.info = snd_ctw_boowean_mono_info,
		.get = xonaw_gpio_bit_switch_get,
		.put = xonaw_gpio_bit_switch_put,
		.pwivate_vawue = GPIO_SWIM_HDMI_DISABWE | XONAW_GPIO_BIT_INVEWT,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphone Pwayback Vowume",
		.info = wm8776_hp_vow_info,
		.get = wm8776_hp_vow_get,
		.put = wm8776_hp_vow_put,
		.twv = { .p = wm8776_hp_db_scawe },
	},
	WM8776_BIT_SWITCH("Headphone Pwayback Switch",
			  WM8776_PWWDOWN, WM8776_HPPD, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input Captuwe Vowume",
		.info = wm8776_input_vow_info,
		.get = wm8776_input_vow_get,
		.put = wm8776_input_vow_put,
		.twv = { .p = wm8776_adc_db_scawe },
	},
	WM8776_BIT_SWITCH("Mic Captuwe Switch",
			  WM8776_ADCMUX, 1 << 0, 0, 0),
	WM8776_BIT_SWITCH("Aux Captuwe Switch",
			  WM8776_ADCMUX, 1 << 1, 0, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "ADC Fiwtew Captuwe Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Wevew Contwow Captuwe Enum",
		.info = wm8776_wevew_contwow_info,
		.get = wm8776_wevew_contwow_get,
		.put = wm8776_wevew_contwow_put,
		.pwivate_vawue = 0,
	},
};
static const stwuct snd_kcontwow_new wc_contwows[] = {
	WM8776_FIEWD_CTW_VOWUME("Wimitew Thweshowd",
				WM8776_AWCCTWW1, 0, 11, 0, 15, 0xf,
				WC_CONTWOW_WIMITEW, wm8776_wct_db_scawe),
	WM8776_FIEWD_CTW_ENUM("Wimitew Attack Time",
			      WM8776_AWCCTWW3, 0, 2, 0, 10, 0xf,
			      WC_CONTWOW_WIMITEW),
	WM8776_FIEWD_CTW_ENUM("Wimitew Decay Time",
			      WM8776_AWCCTWW3, 4, 3, 0, 10, 0xf,
			      WC_CONTWOW_WIMITEW),
	WM8776_FIEWD_CTW_ENUM("Wimitew Twansient Window",
			      WM8776_WIMITEW, 4, 2, 0, 7, 0x7,
			      WC_CONTWOW_WIMITEW),
	WM8776_FIEWD_CTW_VOWUME("Wimitew Maximum Attenuation",
				WM8776_WIMITEW, 0, 6, 3, 12, 0xf,
				WC_CONTWOW_WIMITEW,
				wm8776_maxatten_wim_db_scawe),
	WM8776_FIEWD_CTW_VOWUME("AWC Tawget Wevew",
				WM8776_AWCCTWW1, 0, 11, 0, 15, 0xf,
				WC_CONTWOW_AWC, wm8776_wct_db_scawe),
	WM8776_FIEWD_CTW_ENUM("AWC Attack Time",
			      WM8776_AWCCTWW3, 0, 2, 0, 10, 0xf,
			      WC_CONTWOW_AWC),
	WM8776_FIEWD_CTW_ENUM("AWC Decay Time",
			      WM8776_AWCCTWW3, 4, 3, 0, 10, 0xf,
			      WC_CONTWOW_AWC),
	WM8776_FIEWD_CTW_VOWUME("AWC Maximum Gain",
				WM8776_AWCCTWW1, 4, 7, 1, 7, 0x7,
				WC_CONTWOW_AWC, wm8776_maxgain_db_scawe),
	WM8776_FIEWD_CTW_VOWUME("AWC Maximum Attenuation",
				WM8776_WIMITEW, 0, 10, 10, 15, 0xf,
				WC_CONTWOW_AWC, wm8776_maxatten_awc_db_scawe),
	WM8776_FIEWD_CTW_ENUM("AWC Howd Time",
			      WM8776_AWCCTWW2, 0, 0, 0, 15, 0xf,
			      WC_CONTWOW_AWC),
	WM8776_BIT_SWITCH("Noise Gate Captuwe Switch",
			  WM8776_NOISEGATE, WM8776_NGAT, 0,
			  WC_CONTWOW_AWC),
	WM8776_FIEWD_CTW_VOWUME("Noise Gate Thweshowd",
				WM8776_NOISEGATE, 2, 0, 0, 7, 0x7,
				WC_CONTWOW_AWC, wm8776_ngth_db_scawe),
};

static int add_wc_contwows(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int i;
	stwuct snd_kcontwow *ctw;
	int eww;

	BUIWD_BUG_ON(AWWAY_SIZE(wc_contwows) != AWWAY_SIZE(data->wc_contwows));
	fow (i = 0; i < AWWAY_SIZE(wc_contwows); ++i) {
		ctw = snd_ctw_new1(&wc_contwows[i], chip);
		if (!ctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(chip->cawd, ctw);
		if (eww < 0)
			wetuwn eww;
		data->wc_contwows[i] = ctw;
	}
	wetuwn 0;
}

static int xonaw_ds_mixew_init(stwuct oxygen *chip)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int i;
	stwuct snd_kcontwow *ctw;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(ds_contwows); ++i) {
		ctw = snd_ctw_new1(&ds_contwows[i], chip);
		if (!ctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(chip->cawd, ctw);
		if (eww < 0)
			wetuwn eww;
		if (!stwcmp(ctw->id.name, "Wine Captuwe Switch"))
			data->wine_adcmux_contwow = ctw;
		ewse if (!stwcmp(ctw->id.name, "Mic Captuwe Switch"))
			data->mic_adcmux_contwow = ctw;
	}
	if (!data->wine_adcmux_contwow || !data->mic_adcmux_contwow)
		wetuwn -ENXIO;

	wetuwn add_wc_contwows(chip);
}

static int xonaw_hdav_swim_mixew_init(stwuct oxygen *chip)
{
	unsigned int i;
	stwuct snd_kcontwow *ctw;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(hdav_swim_contwows); ++i) {
		ctw = snd_ctw_new1(&hdav_swim_contwows[i], chip);
		if (!ctw)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(chip->cawd, ctw);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn add_wc_contwows(chip);
}

static void dump_wm8776_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int i;

	snd_ipwintf(buffew, "\nWM8776:\n00:");
	fow (i = 0; i < 0x10; ++i)
		snd_ipwintf(buffew, " %03x", data->wm8776_wegs[i]);
	snd_ipwintf(buffew, "\n10:");
	fow (i = 0x10; i < 0x17; ++i)
		snd_ipwintf(buffew, " %03x", data->wm8776_wegs[i]);
	snd_ipwintf(buffew, "\n");
}

static void dump_wm87x6_wegistews(stwuct oxygen *chip,
				  stwuct snd_info_buffew *buffew)
{
	stwuct xonaw_wm87x6 *data = chip->modew_data;
	unsigned int i;

	dump_wm8776_wegistews(chip, buffew);
	snd_ipwintf(buffew, "\nWM8766:\n00:");
	fow (i = 0; i < 0x10; ++i)
		snd_ipwintf(buffew, " %03x", data->wm8766_wegs[i]);
	snd_ipwintf(buffew, "\n");
}

static const stwuct oxygen_modew modew_xonaw_ds = {
	.wongname = "Asus Viwtuoso 66",
	.chip = "AV200",
	.init = xonaw_ds_init,
	.mixew_init = xonaw_ds_mixew_init,
	.cweanup = xonaw_ds_cweanup,
	.suspend = xonaw_ds_suspend,
	.wesume = xonaw_ds_wesume,
	.pcm_hawdwawe_fiwtew = wm8776_adc_hawdwawe_fiwtew,
	.set_dac_pawams = set_wm87x6_dac_pawams,
	.set_adc_pawams = set_wm8776_adc_pawams,
	.update_dac_vowume = update_wm87x6_vowume,
	.update_dac_mute = update_wm87x6_mute,
	.update_centew_wfe_mix = update_wm8766_centew_wfe_mix,
	.gpio_changed = xonaw_ds_gpio_changed,
	.dump_wegistews = dump_wm87x6_wegistews,
	.dac_twv = wm87x6_dac_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_wm87x6),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_1 |
			 CAPTUWE_1_FWOM_SPDIF,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 8,
	.dac_vowume_min = 255 - 2*60,
	.dac_vowume_max = 255,
	.function_fwags = OXYGEN_FUNCTION_SPI,
	.dac_mcwks = OXYGEN_MCWKS(256, 256, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 256, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

static const stwuct oxygen_modew modew_xonaw_hdav_swim = {
	.showtname = "Xonaw HDAV1.3 Swim",
	.wongname = "Asus Viwtuoso 200",
	.chip = "AV200",
	.init = xonaw_hdav_swim_init,
	.mixew_init = xonaw_hdav_swim_mixew_init,
	.cweanup = xonaw_hdav_swim_cweanup,
	.suspend = xonaw_hdav_swim_suspend,
	.wesume = xonaw_hdav_swim_wesume,
	.pcm_hawdwawe_fiwtew = xonaw_hdav_swim_hawdwawe_fiwtew,
	.set_dac_pawams = set_hdav_swim_dac_pawams,
	.set_adc_pawams = set_wm8776_adc_pawams,
	.update_dac_vowume = update_wm8776_vowume,
	.update_dac_mute = update_wm8776_mute,
	.uawt_input = xonaw_hdmi_uawt_input,
	.dump_wegistews = dump_wm8776_wegistews,
	.dac_twv = wm87x6_dac_db_scawe,
	.modew_data_size = sizeof(stwuct xonaw_wm87x6),
	.device_config = PWAYBACK_0_TO_I2S |
			 PWAYBACK_1_TO_SPDIF |
			 CAPTUWE_0_FWOM_I2S_1 |
			 CAPTUWE_1_FWOM_SPDIF,
	.dac_channews_pcm = 8,
	.dac_channews_mixew = 2,
	.dac_vowume_min = 255 - 2*60,
	.dac_vowume_max = 255,
	.function_fwags = OXYGEN_FUNCTION_2WIWE,
	.dac_mcwks = OXYGEN_MCWKS(256, 256, 128),
	.adc_mcwks = OXYGEN_MCWKS(256, 256, 128),
	.dac_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
	.adc_i2s_fowmat = OXYGEN_I2S_FOWMAT_WJUST,
};

int get_xonaw_wm87x6_modew(stwuct oxygen *chip,
			   const stwuct pci_device_id *id)
{
	switch (id->subdevice) {
	case 0x838e:
		chip->modew = modew_xonaw_ds;
		chip->modew.showtname = "Xonaw DS";
		bweak;
	case 0x8522:
		chip->modew = modew_xonaw_ds;
		chip->modew.showtname = "Xonaw DSX";
		bweak;
	case 0x835e:
		chip->modew = modew_xonaw_hdav_swim;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
