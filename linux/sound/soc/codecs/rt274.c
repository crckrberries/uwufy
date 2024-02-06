// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt274.c  --  WT274 AWSA SoC audio codec dwivew
 *
 * Copywight 2017 Weawtek Semiconductow Cowp.
 * Authow: Bawd Wiao <bawdwiao@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>
#incwude <winux/wowkqueue.h>

#incwude "ww6347a.h"
#incwude "wt274.h"

#define WT274_VENDOW_ID 0x10ec0274

stwuct wt274_pwiv {
	stwuct weg_defauwt *index_cache;
	int index_cache_size;
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	stwuct i2c_cwient *i2c;
	stwuct snd_soc_jack *jack;
	stwuct dewayed_wowk jack_detect_wowk;
	int sys_cwk;
	int cwk_id;
	int fs;
	boow mastew;
};

static const stwuct weg_defauwt wt274_index_def[] = {
	{ 0x00, 0x1004 },
	{ 0x01, 0xaaaa },
	{ 0x02, 0x88aa },
	{ 0x03, 0x0002 },
	{ 0x04, 0xaa09 },
	{ 0x05, 0x0700 },
	{ 0x06, 0x6110 },
	{ 0x07, 0x0200 },
	{ 0x08, 0xa807 },
	{ 0x09, 0x0021 },
	{ 0x0a, 0x7770 },
	{ 0x0b, 0x7770 },
	{ 0x0c, 0x002b },
	{ 0x0d, 0x2420 },
	{ 0x0e, 0x65c0 },
	{ 0x0f, 0x7770 },
	{ 0x10, 0x0420 },
	{ 0x11, 0x7418 },
	{ 0x12, 0x6bd0 },
	{ 0x13, 0x645f },
	{ 0x14, 0x0400 },
	{ 0x15, 0x8ccc },
	{ 0x16, 0x4c50 },
	{ 0x17, 0xff00 },
	{ 0x18, 0x0003 },
	{ 0x19, 0x2c11 },
	{ 0x1a, 0x830b },
	{ 0x1b, 0x4e4b },
	{ 0x1c, 0x0000 },
	{ 0x1d, 0x0000 },
	{ 0x1e, 0x0000 },
	{ 0x1f, 0x0000 },
	{ 0x20, 0x51ff },
	{ 0x21, 0x8000 },
	{ 0x22, 0x8f00 },
	{ 0x23, 0x88f4 },
	{ 0x24, 0x0000 },
	{ 0x25, 0x0000 },
	{ 0x26, 0x0000 },
	{ 0x27, 0x0000 },
	{ 0x28, 0x0000 },
	{ 0x29, 0x3000 },
	{ 0x2a, 0x0000 },
	{ 0x2b, 0x0000 },
	{ 0x2c, 0x0f00 },
	{ 0x2d, 0x100f },
	{ 0x2e, 0x2902 },
	{ 0x2f, 0xe280 },
	{ 0x30, 0x1000 },
	{ 0x31, 0x8400 },
	{ 0x32, 0x5aaa },
	{ 0x33, 0x8420 },
	{ 0x34, 0xa20c },
	{ 0x35, 0x096a },
	{ 0x36, 0x5757 },
	{ 0x37, 0xfe05 },
	{ 0x38, 0x4901 },
	{ 0x39, 0x110a },
	{ 0x3a, 0x0010 },
	{ 0x3b, 0x60d9 },
	{ 0x3c, 0xf214 },
	{ 0x3d, 0xc2ba },
	{ 0x3e, 0xa928 },
	{ 0x3f, 0x0000 },
	{ 0x40, 0x9800 },
	{ 0x41, 0x0000 },
	{ 0x42, 0x2000 },
	{ 0x43, 0x3d90 },
	{ 0x44, 0x4900 },
	{ 0x45, 0x5289 },
	{ 0x46, 0x0004 },
	{ 0x47, 0xa47a },
	{ 0x48, 0xd049 },
	{ 0x49, 0x0049 },
	{ 0x4a, 0xa83b },
	{ 0x4b, 0x0777 },
	{ 0x4c, 0x065c },
	{ 0x4d, 0x7fff },
	{ 0x4e, 0x7fff },
	{ 0x4f, 0x0000 },
	{ 0x50, 0x0000 },
	{ 0x51, 0x0000 },
	{ 0x52, 0xbf5f },
	{ 0x53, 0x3320 },
	{ 0x54, 0xcc00 },
	{ 0x55, 0x0000 },
	{ 0x56, 0x3f00 },
	{ 0x57, 0x0000 },
	{ 0x58, 0x0000 },
	{ 0x59, 0x0000 },
	{ 0x5a, 0x1300 },
	{ 0x5b, 0x005f },
	{ 0x5c, 0x0000 },
	{ 0x5d, 0x1001 },
	{ 0x5e, 0x1000 },
	{ 0x5f, 0x0000 },
	{ 0x60, 0x5554 },
	{ 0x61, 0xffc0 },
	{ 0x62, 0xa000 },
	{ 0x63, 0xd010 },
	{ 0x64, 0x0000 },
	{ 0x65, 0x3fb1 },
	{ 0x66, 0x1881 },
	{ 0x67, 0xc810 },
	{ 0x68, 0x2000 },
	{ 0x69, 0xfff0 },
	{ 0x6a, 0x0300 },
	{ 0x6b, 0x5060 },
	{ 0x6c, 0x0000 },
	{ 0x6d, 0x0000 },
	{ 0x6e, 0x0c25 },
	{ 0x6f, 0x0c0b },
	{ 0x70, 0x8000 },
	{ 0x71, 0x4008 },
	{ 0x72, 0x0000 },
	{ 0x73, 0x0800 },
	{ 0x74, 0xa28f },
	{ 0x75, 0xa050 },
	{ 0x76, 0x7fe8 },
	{ 0x77, 0xdb8c },
	{ 0x78, 0x0000 },
	{ 0x79, 0x0000 },
	{ 0x7a, 0x2a96 },
	{ 0x7b, 0x800f },
	{ 0x7c, 0x0200 },
	{ 0x7d, 0x1600 },
	{ 0x7e, 0x0000 },
	{ 0x7f, 0x0000 },
};
#define INDEX_CACHE_SIZE AWWAY_SIZE(wt274_index_def)

static const stwuct weg_defauwt wt274_weg[] = {
	{ 0x00170500, 0x00000400 },
	{ 0x00220000, 0x00000031 },
	{ 0x00239000, 0x00000057 },
	{ 0x0023a000, 0x00000057 },
	{ 0x00270500, 0x00000400 },
	{ 0x00370500, 0x00000400 },
	{ 0x00870500, 0x00000400 },
	{ 0x00920000, 0x00000031 },
	{ 0x00935000, 0x00000097 },
	{ 0x00936000, 0x00000097 },
	{ 0x00970500, 0x00000400 },
	{ 0x00b37000, 0x00000400 },
	{ 0x00b37200, 0x00000400 },
	{ 0x00b37300, 0x00000400 },
	{ 0x00c37000, 0x00000400 },
	{ 0x00c37100, 0x00000400 },
	{ 0x01270500, 0x00000400 },
	{ 0x01370500, 0x00000400 },
	{ 0x01371f00, 0x411111f0 },
	{ 0x01937000, 0x00000000 },
	{ 0x01970500, 0x00000400 },
	{ 0x02050000, 0x0000001b },
	{ 0x02139000, 0x00000080 },
	{ 0x0213a000, 0x00000080 },
	{ 0x02170100, 0x00000001 },
	{ 0x02170500, 0x00000400 },
	{ 0x02170700, 0x00000000 },
	{ 0x02270100, 0x00000000 },
	{ 0x02370100, 0x00000000 },
	{ 0x01970700, 0x00000020 },
	{ 0x00830000, 0x00000097 },
	{ 0x00930000, 0x00000097 },
	{ 0x01270700, 0x00000000 },
};

static boow wt274_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0 ... 0xff:
	case WT274_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID):
	case WT274_GET_HP_SENSE:
	case WT274_GET_MIC_SENSE:
	case WT274_PWOC_COEF:
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_DAC_OUT0, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_DAC_OUT1, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_ADC_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_ADC_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DAC_OUT0, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DAC_OUT1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_ADC_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_ADC_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DMIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DMIC2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_WINE1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_WINE2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_MIXEW_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_MIXEW_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_DMIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_DMIC2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_WINE1, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_WINE2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_INWINE_CMD, 0):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}


}

static boow wt274_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0 ... 0xff:
	case WT274_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID):
	case WT274_GET_HP_SENSE:
	case WT274_GET_MIC_SENSE:
	case WT274_SET_AUDIO_POWEW:
	case WT274_SET_HPO_POWEW:
	case WT274_SET_DMIC1_POWEW:
	case WT274_WOUT_MUX:
	case WT274_HPO_MUX:
	case WT274_ADC0_MUX:
	case WT274_ADC1_MUX:
	case WT274_SET_MIC:
	case WT274_SET_PIN_HPO:
	case WT274_SET_PIN_WOUT3:
	case WT274_SET_PIN_DMIC1:
	case WT274_SET_AMP_GAIN_HPO:
	case WT274_SET_DMIC2_DEFAUWT:
	case WT274_DAC0W_GAIN:
	case WT274_DAC0W_GAIN:
	case WT274_DAC1W_GAIN:
	case WT274_DAC1W_GAIN:
	case WT274_ADCW_GAIN:
	case WT274_ADCW_GAIN:
	case WT274_MIC_GAIN:
	case WT274_HPOW_GAIN:
	case WT274_HPOW_GAIN:
	case WT274_WOUTW_GAIN:
	case WT274_WOUTW_GAIN:
	case WT274_DAC_FOWMAT:
	case WT274_ADC_FOWMAT:
	case WT274_COEF_INDEX:
	case WT274_PWOC_COEF:
	case WT274_SET_AMP_GAIN_ADC_IN1:
	case WT274_SET_AMP_GAIN_ADC_IN2:
	case WT274_SET_POWEW(WT274_DAC_OUT0):
	case WT274_SET_POWEW(WT274_DAC_OUT1):
	case WT274_SET_POWEW(WT274_ADC_IN1):
	case WT274_SET_POWEW(WT274_ADC_IN2):
	case WT274_SET_POWEW(WT274_DMIC2):
	case WT274_SET_POWEW(WT274_MIC):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_EAPD_BTWENABWE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_DAC_OUT0, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_DAC_OUT1, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_ADC_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_STWEAM_FOWMAT, WT274_ADC_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DAC_OUT0, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DAC_OUT1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_ADC_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_ADC_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DMIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_DMIC2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_WINE1, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_WINE2, 0):
	case VEWB_CMD(AC_VEWB_GET_AMP_GAIN_MUTE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_MIXEW_IN1, 0):
	case VEWB_CMD(AC_VEWB_GET_CONNECT_SEW, WT274_MIXEW_IN2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_DMIC1, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_DMIC2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_WINE1, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_WINE2, 0):
	case VEWB_CMD(AC_VEWB_GET_PIN_WIDGET_CONTWOW, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_HP_OUT, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_MIC, 0):
	case VEWB_CMD(AC_VEWB_GET_UNSOWICITED_WESPONSE, WT274_INWINE_CMD, 0):
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#ifdef CONFIG_PM
static void wt274_index_sync(stwuct snd_soc_component *component)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);
	int i;

	fow (i = 0; i < INDEX_CACHE_SIZE; i++) {
		snd_soc_component_wwite(component, wt274->index_cache[i].weg,
				  wt274->index_cache[i].def);
	}
}
#endif

static int wt274_jack_detect(stwuct wt274_pwiv *wt274, boow *hp, boow *mic)
{
	unsigned int buf;
	int wet;

	*hp = fawse;
	*mic = fawse;

	if (!wt274->component)
		wetuwn -EINVAW;

	wet = wegmap_wead(wt274->wegmap, WT274_GET_HP_SENSE, &buf);
	if (wet)
		wetuwn wet;

	*hp = buf & 0x80000000;
	wet = wegmap_wead(wt274->wegmap, WT274_GET_MIC_SENSE, &buf);
	if (wet)
		wetuwn wet;

	*mic = buf & 0x80000000;

	pw_debug("*hp = %d *mic = %d\n", *hp, *mic);

	wetuwn 0;
}

static void wt274_jack_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt274_pwiv *wt274 =
		containew_of(wowk, stwuct wt274_pwiv, jack_detect_wowk.wowk);
	int status = 0;
	boow hp = fawse;
	boow mic = fawse;

	if (wt274_jack_detect(wt274, &hp, &mic) < 0)
		wetuwn;

	if (hp)
		status |= SND_JACK_HEADPHONE;

	if (mic)
		status |= SND_JACK_MICWOPHONE;

	snd_soc_jack_wepowt(wt274->jack, status,
		SND_JACK_MICWOPHONE | SND_JACK_HEADPHONE);
}

static iwqwetuwn_t wt274_iwq(int iwq, void *data);

static int wt274_mic_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *jack,  void *data)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	wt274->jack = jack;

	if (jack == NUWW) {
		/* Disabwe jack detection */
		wegmap_update_bits(wt274->wegmap, WT274_EAPD_GPIO_IWQ_CTWW,
					WT274_IWQ_EN, WT274_IWQ_DIS);

		wetuwn 0;
	}

	wegmap_update_bits(wt274->wegmap, WT274_EAPD_GPIO_IWQ_CTWW,
				WT274_IWQ_EN, WT274_IWQ_EN);

	/* Send an initiaw wepowt */
	wt274_iwq(0, wt274);

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6350, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt274_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("DAC0 Pwayback Vowume", WT274_DAC0W_GAIN,
			 WT274_DAC0W_GAIN, 0, 0x7f, 0, out_vow_twv),
	SOC_DOUBWE_W_TWV("DAC1 Pwayback Vowume", WT274_DAC1W_GAIN,
			 WT274_DAC1W_GAIN, 0, 0x7f, 0, out_vow_twv),
	SOC_DOUBWE_W_TWV("ADC0 Captuwe Vowume", WT274_ADCW_GAIN,
			    WT274_ADCW_GAIN, 0, 0x7f, 0, out_vow_twv),
	SOC_DOUBWE_W("ADC0 Captuwe Switch", WT274_ADCW_GAIN,
			    WT274_ADCW_GAIN, WT274_MUTE_SFT, 1, 1),
	SOC_SINGWE_TWV("AMIC Vowume", WT274_MIC_GAIN,
			    0, 0x3, 0, mic_vow_twv),
};

static const stwuct snd_kcontwow_new hpow_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT274_HPOW_GAIN,
			WT274_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hpow_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT274_HPOW_GAIN,
			WT274_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new woutw_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT274_WOUTW_GAIN,
			WT274_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new woutw_enabwe_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT274_WOUTW_GAIN,
			WT274_MUTE_SFT, 1, 1);

/* ADC0 souwce */
static const chaw * const wt274_adc_swc[] = {
	"Mic", "Wine1", "Wine2", "Dmic"
};

static SOC_ENUM_SINGWE_DECW(
	wt274_adc0_enum, WT274_ADC0_MUX, WT274_ADC_SEW_SFT,
	wt274_adc_swc);

static const stwuct snd_kcontwow_new wt274_adc0_mux =
	SOC_DAPM_ENUM("ADC 0 souwce", wt274_adc0_enum);

static SOC_ENUM_SINGWE_DECW(
	wt274_adc1_enum, WT274_ADC1_MUX, WT274_ADC_SEW_SFT,
	wt274_adc_swc);

static const stwuct snd_kcontwow_new wt274_adc1_mux =
	SOC_DAPM_ENUM("ADC 1 souwce", wt274_adc1_enum);

static const chaw * const wt274_dac_swc[] = {
	"DAC OUT0", "DAC OUT1"
};
/* HP-OUT souwce */
static SOC_ENUM_SINGWE_DECW(wt274_hpo_enum, WT274_HPO_MUX,
				0, wt274_dac_swc);

static const stwuct snd_kcontwow_new wt274_hpo_mux =
SOC_DAPM_ENUM("HPO souwce", wt274_hpo_enum);

/* Wine out souwce */
static SOC_ENUM_SINGWE_DECW(wt274_wout_enum, WT274_WOUT_MUX,
				0, wt274_dac_swc);

static const stwuct snd_kcontwow_new wt274_wout_mux =
SOC_DAPM_ENUM("WOUT souwce", wt274_wout_enum);

static const stwuct snd_soc_dapm_widget wt274_dapm_widgets[] = {
	/* Input Wines */
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("WINE2"),

	/* DMIC */
	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 0", NUWW, WT274_SET_STWEAMID_ADC1, 4, 0),
	SND_SOC_DAPM_ADC("ADC 1", NUWW, WT274_SET_STWEAMID_ADC2, 4, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("ADC 0 Mux", SND_SOC_NOPM, 0, 0,
		&wt274_adc0_mux),
	SND_SOC_DAPM_MUX("ADC 1 Mux", SND_SOC_NOPM, 0, 0,
		&wt274_adc1_mux),

	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WXW", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF1WXW", "AIF1 Pwayback", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TXW", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TXW", "AIF1 Captuwe", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WXW", "AIF1 Pwayback", 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WXW", "AIF1 Pwayback", 3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TXW", "AIF1 Captuwe", 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TXW", "AIF1 Captuwe", 3, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC 0", NUWW, WT274_SET_STWEAMID_DAC0, 4, 0),
	SND_SOC_DAPM_DAC("DAC 1", NUWW, WT274_SET_STWEAMID_DAC1, 4, 0),

	/* Output Mux */
	SND_SOC_DAPM_MUX("HPO Mux", SND_SOC_NOPM, 0, 0, &wt274_hpo_mux),
	SND_SOC_DAPM_MUX("WOUT Mux", SND_SOC_NOPM, 0, 0, &wt274_wout_mux),

	SND_SOC_DAPM_SUPPWY("HP Powew", WT274_SET_PIN_HPO,
		WT274_SET_PIN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WOUT Powew", WT274_SET_PIN_WOUT3,
		WT274_SET_PIN_SFT, 0, NUWW, 0),

	/* Output Mixew */
	SND_SOC_DAPM_PGA("DAC OUT0", SND_SOC_NOPM, 0, 0,
			NUWW, 0),
	SND_SOC_DAPM_PGA("DAC OUT1", SND_SOC_NOPM, 0, 0,
			NUWW, 0),

	/* Output Pga */
	SND_SOC_DAPM_SWITCH("WOUT W", SND_SOC_NOPM, 0, 0,
		&woutw_enabwe_contwow),
	SND_SOC_DAPM_SWITCH("WOUT W", SND_SOC_NOPM, 0, 0,
		&woutw_enabwe_contwow),
	SND_SOC_DAPM_SWITCH("HPO W", SND_SOC_NOPM, 0, 0,
		&hpow_enabwe_contwow),
	SND_SOC_DAPM_SWITCH("HPO W", SND_SOC_NOPM, 0, 0,
		&hpow_enabwe_contwow),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPO Pin"),
	SND_SOC_DAPM_OUTPUT("SPDIF"),
	SND_SOC_DAPM_OUTPUT("WINE3"),
};

static const stwuct snd_soc_dapm_woute wt274_dapm_woutes[] = {
	{"DMIC1", NUWW, "DMIC1 Pin"},
	{"DMIC2", NUWW, "DMIC2 Pin"},

	{"ADC 0 Mux", "Mic", "MIC"},
	{"ADC 0 Mux", "Dmic", "DMIC1"},
	{"ADC 0 Mux", "Wine1", "WINE1"},
	{"ADC 0 Mux", "Wine2", "WINE2"},
	{"ADC 1 Mux", "Mic", "MIC"},
	{"ADC 1 Mux", "Dmic", "DMIC2"},
	{"ADC 1 Mux", "Wine1", "WINE1"},
	{"ADC 1 Mux", "Wine2", "WINE2"},

	{"ADC 0", NUWW, "ADC 0 Mux"},
	{"ADC 1", NUWW, "ADC 1 Mux"},

	{"AIF1TXW", NUWW, "ADC 0"},
	{"AIF1TXW", NUWW, "ADC 0"},
	{"AIF2TXW", NUWW, "ADC 1"},
	{"AIF2TXW", NUWW, "ADC 1"},

	{"DAC 0", NUWW, "AIF1WXW"},
	{"DAC 0", NUWW, "AIF1WXW"},
	{"DAC 1", NUWW, "AIF2WXW"},
	{"DAC 1", NUWW, "AIF2WXW"},

	{"DAC OUT0", NUWW, "DAC 0"},

	{"DAC OUT1", NUWW, "DAC 1"},

	{"WOUT Mux", "DAC OUT0", "DAC OUT0"},
	{"WOUT Mux", "DAC OUT1", "DAC OUT1"},

	{"WOUT W", "Switch", "WOUT Mux"},
	{"WOUT W", "Switch", "WOUT Mux"},
	{"WOUT W", NUWW, "WOUT Powew"},
	{"WOUT W", NUWW, "WOUT Powew"},

	{"WINE3", NUWW, "WOUT W"},
	{"WINE3", NUWW, "WOUT W"},

	{"HPO Mux", "DAC OUT0", "DAC OUT0"},
	{"HPO Mux", "DAC OUT1", "DAC OUT1"},

	{"HPO W", "Switch", "HPO Mux"},
	{"HPO W", "Switch", "HPO Mux"},
	{"HPO W", NUWW, "HP Powew"},
	{"HPO W", NUWW, "HP Powew"},

	{"HPO Pin", NUWW, "HPO W"},
	{"HPO Pin", NUWW, "HPO W"},
};

static int wt274_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0;
	int d_wen_code = 0, c_wen_code = 0;

	switch (pawams_wate(pawams)) {
	/* bit 14 0:48K 1:44.1K */
	case 44100:
	case 48000:
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted sampwe wate %d\n",
					pawams_wate(pawams));
		wetuwn -EINVAW;
	}
	switch (wt274->sys_cwk) {
	case 12288000:
	case 24576000:
		if (pawams_wate(pawams) != 48000) {
			dev_eww(component->dev, "Sys_cwk is not matched (%d %d)\n",
					pawams_wate(pawams), wt274->sys_cwk);
			wetuwn -EINVAW;
		}
		bweak;
	case 11289600:
	case 22579200:
		if (pawams_wate(pawams) != 44100) {
			dev_eww(component->dev, "Sys_cwk is not matched (%d %d)\n",
					pawams_wate(pawams), wt274->sys_cwk);
			wetuwn -EINVAW;
		}
		bweak;
	}

	if (pawams_channews(pawams) <= 16) {
		/* bit 3:0 Numbew of Channew */
		vaw |= (pawams_channews(pawams) - 1);
	} ewse {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
					pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	switch (pawams_width(pawams)) {
	/* bit 6:4 Bits pew Sampwe */
	case 16:
		d_wen_code = 0;
		c_wen_code = 0;
		vaw |= (0x1 << 4);
		bweak;
	case 32:
		d_wen_code = 2;
		c_wen_code = 3;
		vaw |= (0x4 << 4);
		bweak;
	case 20:
		d_wen_code = 1;
		c_wen_code = 1;
		vaw |= (0x2 << 4);
		bweak;
	case 24:
		d_wen_code = 2;
		c_wen_code = 2;
		vaw |= (0x3 << 4);
		bweak;
	case 8:
		d_wen_code = 3;
		c_wen_code = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wt274->mastew)
		c_wen_code = 0x3;

	snd_soc_component_update_bits(component,
		WT274_I2S_CTWW1, 0xc018, d_wen_code << 3 | c_wen_code << 14);
	dev_dbg(component->dev, "fowmat vaw = 0x%x\n", vaw);

	snd_soc_component_update_bits(component, WT274_DAC_FOWMAT, 0x407f, vaw);
	snd_soc_component_update_bits(component, WT274_ADC_FOWMAT, 0x407f, vaw);

	wetuwn 0;
}

static int wt274_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_I2S_MODE_MASK, WT274_I2S_MODE_M);
		wt274->mastew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_I2S_MODE_MASK, WT274_I2S_MODE_S);
		wt274->mastew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component, WT274_I2S_CTWW1,
					WT274_I2S_FMT_MASK, WT274_I2S_FMT_I2S);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		snd_soc_component_update_bits(component, WT274_I2S_CTWW1,
					WT274_I2S_FMT_MASK, WT274_I2S_FMT_WJ);
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		snd_soc_component_update_bits(component, WT274_I2S_CTWW1,
					WT274_I2S_FMT_MASK, WT274_I2S_FMT_PCMA);
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		snd_soc_component_update_bits(component, WT274_I2S_CTWW1,
					WT274_I2S_FMT_MASK, WT274_I2S_FMT_PCMB);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* bit 15 Stweam Type 0:PCM 1:Non-PCM */
	snd_soc_component_update_bits(component, WT274_DAC_FOWMAT, 0x8000, 0);
	snd_soc_component_update_bits(component, WT274_ADC_FOWMAT, 0x8000, 0);

	wetuwn 0;
}

static int wt274_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	switch (souwce) {
	case WT274_PWW2_S_MCWK:
		snd_soc_component_update_bits(component, WT274_PWW2_CTWW,
				WT274_PWW2_SWC_MASK, WT274_PWW2_SWC_MCWK);
		bweak;
	defauwt:
		dev_wawn(component->dev, "invawid pww souwce, use BCWK\n");
		fawwthwough;
	case WT274_PWW2_S_BCWK:
		snd_soc_component_update_bits(component, WT274_PWW2_CTWW,
				WT274_PWW2_SWC_MASK, WT274_PWW2_SWC_BCWK);
		bweak;
	}

	if (souwce == WT274_PWW2_S_BCWK) {
		snd_soc_component_update_bits(component, WT274_MCWK_CTWW,
				(0x3 << 12), (0x3 << 12));
		switch (wt274->fs) {
		case 50:
			snd_soc_component_wwite(component, 0x7a, 0xaab6);
			snd_soc_component_wwite(component, 0x7b, 0x0301);
			snd_soc_component_wwite(component, 0x7c, 0x04fe);
			bweak;
		case 64:
			snd_soc_component_wwite(component, 0x7a, 0xaa96);
			snd_soc_component_wwite(component, 0x7b, 0x8003);
			snd_soc_component_wwite(component, 0x7c, 0x081e);
			bweak;
		case 128:
			snd_soc_component_wwite(component, 0x7a, 0xaa96);
			snd_soc_component_wwite(component, 0x7b, 0x8003);
			snd_soc_component_wwite(component, 0x7c, 0x080e);
			bweak;
		defauwt:
			dev_wawn(component->dev, "invawid fweq_in, assume 4.8M\n");
			fawwthwough;
		case 100:
			snd_soc_component_wwite(component, 0x7a, 0xaab6);
			snd_soc_component_wwite(component, 0x7b, 0x0301);
			snd_soc_component_wwite(component, 0x7c, 0x047e);
			bweak;
		}
	}

	wetuwn 0;
}

static int wt274_set_dai_syscwk(stwuct snd_soc_dai *dai,
				int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);
	unsigned int cwk_swc, mcwk_en;

	dev_dbg(component->dev, "%s fweq=%d\n", __func__, fweq);

	switch (cwk_id) {
	case WT274_SCWK_S_MCWK:
		mcwk_en = WT274_MCWK_MODE_EN;
		cwk_swc = WT274_CWK_SWC_MCWK;
		bweak;
	case WT274_SCWK_S_PWW1:
		mcwk_en = WT274_MCWK_MODE_DIS;
		cwk_swc = WT274_CWK_SWC_MCWK;
		bweak;
	case WT274_SCWK_S_PWW2:
		mcwk_en = WT274_MCWK_MODE_EN;
		cwk_swc = WT274_CWK_SWC_PWW2;
		bweak;
	defauwt:
		mcwk_en = WT274_MCWK_MODE_DIS;
		cwk_swc = WT274_CWK_SWC_MCWK;
		dev_wawn(component->dev, "invawid syscwk souwce, use PWW1\n");
		bweak;
	}
	snd_soc_component_update_bits(component, WT274_MCWK_CTWW,
			WT274_MCWK_MODE_MASK, mcwk_en);
	snd_soc_component_update_bits(component, WT274_CWK_CTWW,
			WT274_CWK_SWC_MASK, cwk_swc);

	switch (fweq) {
	case 19200000:
		if (cwk_id == WT274_SCWK_S_MCWK) {
			dev_eww(component->dev, "Shouwd not use MCWK\n");
			wetuwn -EINVAW;
		}
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW2, 0x40, 0x40);
		bweak;
	case 24000000:
		if (cwk_id == WT274_SCWK_S_MCWK) {
			dev_eww(component->dev, "Shouwd not use MCWK\n");
			wetuwn -EINVAW;
		}
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW2, 0x40, 0x0);
		bweak;
	case 12288000:
	case 11289600:
		snd_soc_component_update_bits(component,
			WT274_MCWK_CTWW, 0x1fcf, 0x0008);
		bweak;
	case 24576000:
	case 22579200:
		snd_soc_component_update_bits(component,
			WT274_MCWK_CTWW, 0x1fcf, 0x1543);
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted system cwock\n");
		wetuwn -EINVAW;
	}

	wt274->sys_cwk = fweq;
	wt274->cwk_id = cwk_id;

	wetuwn 0;
}

static int wt274_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "%s watio=%d\n", __func__, watio);
	wt274->fs = watio;
	if ((watio / 50) == 0)
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, 0x1000, 0x1000);
	ewse
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, 0x1000, 0x0);


	wetuwn 0;
}

static int wt274_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int wx_mask, int swots, int swot_width)

{
	stwuct snd_soc_component *component = dai->component;

	if (wx_mask || tx_mask) {
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_TDM_EN, WT274_TDM_EN);
	} ewse {
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_TDM_EN, WT274_TDM_DIS);
		wetuwn 0;
	}

	switch (swots) {
	case 4:
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_TDM_CH_NUM, WT274_TDM_4CH);
		bweak;
	case 2:
		snd_soc_component_update_bits(component,
			WT274_I2S_CTWW1, WT274_TDM_CH_NUM, WT274_TDM_2CH);
		bweak;
	defauwt:
		dev_eww(component->dev,
			"Suppowt 2 ow 4 swots TDM onwy\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt274_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (SND_SOC_BIAS_STANDBY ==
			snd_soc_component_get_bias_wevew(component)) {
			snd_soc_component_wwite(component,
				WT274_SET_AUDIO_POWEW, AC_PWWST_D0);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_wwite(component,
			WT274_SET_AUDIO_POWEW, AC_PWWST_D3);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static iwqwetuwn_t wt274_iwq(int iwq, void *data)
{
	stwuct wt274_pwiv *wt274 = data;
	boow hp = fawse;
	boow mic = fawse;
	int wet, status = 0;

	/* Cweaw IWQ */
	wegmap_update_bits(wt274->wegmap, WT274_EAPD_GPIO_IWQ_CTWW,
				WT274_IWQ_CWW, WT274_IWQ_CWW);

	wet = wt274_jack_detect(wt274, &hp, &mic);

	if (wet == 0) {
		if (hp)
			status |= SND_JACK_HEADPHONE;

		if (mic)
			status |= SND_JACK_MICWOPHONE;

		snd_soc_jack_wepowt(wt274->jack, status,
			SND_JACK_MICWOPHONE | SND_JACK_HEADPHONE);

		pm_wakeup_event(&wt274->i2c->dev, 300);
	}

	wetuwn IWQ_HANDWED;
}

static int wt274_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	wt274->component = component;
	INIT_DEWAYED_WOWK(&wt274->jack_detect_wowk, wt274_jack_detect_wowk);

	if (wt274->i2c->iwq)
		scheduwe_dewayed_wowk(&wt274->jack_detect_wowk,
				      msecs_to_jiffies(1250));
	wetuwn 0;
}

static void wt274_wemove(stwuct snd_soc_component *component)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	cancew_dewayed_wowk_sync(&wt274->jack_detect_wowk);
	wt274->component = NUWW;
}

#ifdef CONFIG_PM
static int wt274_suspend(stwuct snd_soc_component *component)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt274->wegmap, twue);
	wegcache_mawk_diwty(wt274->wegmap);

	wetuwn 0;
}

static int wt274_wesume(stwuct snd_soc_component *component)
{
	stwuct wt274_pwiv *wt274 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt274->wegmap, fawse);
	wt274_index_sync(component);
	wegcache_sync(wt274->wegmap);

	wetuwn 0;
}
#ewse
#define wt274_suspend NUWW
#define wt274_wesume NUWW
#endif

#define WT274_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define WT274_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt274_aif_dai_ops = {
	.hw_pawams = wt274_hw_pawams,
	.set_fmt = wt274_set_dai_fmt,
	.set_syscwk = wt274_set_dai_syscwk,
	.set_pww = wt274_set_dai_pww,
	.set_bcwk_watio = wt274_set_bcwk_watio,
	.set_tdm_swot = wt274_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew wt274_dai[] = {
	{
		.name = "wt274-aif1",
		.id = WT274_AIF1,
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT274_STEWEO_WATES,
			.fowmats = WT274_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT274_STEWEO_WATES,
			.fowmats = WT274_FOWMATS,
		},
		.ops = &wt274_aif_dai_ops,
		.symmetwic_wate = 1,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt274 = {
	.pwobe			= wt274_pwobe,
	.wemove			= wt274_wemove,
	.suspend		= wt274_suspend,
	.wesume			= wt274_wesume,
	.set_bias_wevew		= wt274_set_bias_wevew,
	.set_jack		= wt274_mic_detect,
	.contwows		= wt274_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt274_snd_contwows),
	.dapm_widgets		= wt274_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt274_dapm_widgets),
	.dapm_woutes		= wt274_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt274_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt274_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.max_wegistew = 0x05bfffff,
	.vowatiwe_weg = wt274_vowatiwe_wegistew,
	.weadabwe_weg = wt274_weadabwe_wegistew,
	.weg_wwite = ww6347a_hw_wwite,
	.weg_wead = ww6347a_hw_wead,
	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = wt274_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt274_weg),
};

#ifdef CONFIG_OF
static const stwuct of_device_id wt274_of_match[] = {
	{.compatibwe = "weawtek,wt274"},
	{},
};
MODUWE_DEVICE_TABWE(of, wt274_of_match);
#endif

static const stwuct i2c_device_id wt274_i2c_id[] = {
	{"wt274", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt274_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt274_acpi_match[] = {
	{ "10EC0274", 0 },
	{ "INT34C2", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt274_acpi_match);
#endif

static int wt274_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt274_pwiv *wt274;

	int wet;
	unsigned int vaw;

	wt274 = devm_kzawwoc(&i2c->dev,	sizeof(*wt274),
				GFP_KEWNEW);
	if (wt274 == NUWW)
		wetuwn -ENOMEM;

	wt274->wegmap = devm_wegmap_init(&i2c->dev, NUWW, i2c, &wt274_wegmap);
	if (IS_EWW(wt274->wegmap)) {
		wet = PTW_EWW(wt274->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_wead(wt274->wegmap,
		WT274_GET_PAWAM(AC_NODE_WOOT, AC_PAW_VENDOW_ID), &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != WT274_VENDOW_ID) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt274\n", vaw);
		wetuwn -ENODEV;
	}

	wt274->index_cache = devm_kmemdup(&i2c->dev, wt274_index_def,
					  sizeof(wt274_index_def), GFP_KEWNEW);
	if (!wt274->index_cache)
		wetuwn -ENOMEM;

	wt274->index_cache_size = INDEX_CACHE_SIZE;
	wt274->i2c = i2c;
	i2c_set_cwientdata(i2c, wt274);

	/* weset codec */
	wegmap_wwite(wt274->wegmap, WT274_WESET, 0);
	wegmap_update_bits(wt274->wegmap, 0x1a, 0x4000, 0x4000);

	/* Set Pad PDB is fwoating */
	wegmap_update_bits(wt274->wegmap, WT274_PAD_CTWW12, 0x3, 0x0);
	wegmap_wwite(wt274->wegmap, WT274_COEF5b_INDEX, 0x01);
	wegmap_wwite(wt274->wegmap, WT274_COEF5b_COEF, 0x8540);
	wegmap_update_bits(wt274->wegmap, 0x6f, 0x0100, 0x0100);
	/* Combo jack auto detect */
	wegmap_wwite(wt274->wegmap, 0x4a, 0x201b);
	/* Aux mode off */
	wegmap_update_bits(wt274->wegmap, 0x6f, 0x3000, 0x2000);
	/* HP DC Cawibwation */
	wegmap_update_bits(wt274->wegmap, 0x6f, 0xf, 0x0);
	/* Set NID=58h.Index 00h [15]= 1b; */
	wegmap_wwite(wt274->wegmap, WT274_COEF58_INDEX, 0x00);
	wegmap_wwite(wt274->wegmap, WT274_COEF58_COEF, 0xb888);
	msweep(500);
	wegmap_update_bits(wt274->wegmap, 0x6f, 0xf, 0xb);
	wegmap_wwite(wt274->wegmap, WT274_COEF58_INDEX, 0x00);
	wegmap_wwite(wt274->wegmap, WT274_COEF58_COEF, 0x3888);
	/* Set pin widget */
	wegmap_wwite(wt274->wegmap, WT274_SET_PIN_HPO, 0x40);
	wegmap_wwite(wt274->wegmap, WT274_SET_PIN_WOUT3, 0x40);
	wegmap_wwite(wt274->wegmap, WT274_SET_MIC, 0x20);
	wegmap_wwite(wt274->wegmap, WT274_SET_PIN_DMIC1, 0x20);

	wegmap_update_bits(wt274->wegmap, WT274_I2S_CTWW2, 0xc004, 0x4004);
	wegmap_update_bits(wt274->wegmap, WT274_EAPD_GPIO_IWQ_CTWW,
				WT274_GPI2_SEW_MASK, WT274_GPI2_SEW_DMIC_CWK);

	/* jack detection */
	wegmap_wwite(wt274->wegmap, WT274_UNSOWICITED_HP_OUT, 0x81);
	wegmap_wwite(wt274->wegmap, WT274_UNSOWICITED_MIC, 0x82);

	if (wt274->i2c->iwq) {
		wet = wequest_thweaded_iwq(wt274->i2c->iwq, NUWW, wt274_iwq,
			IWQF_TWIGGEW_HIGH | IWQF_ONESHOT, "wt274", wt274);
		if (wet != 0) {
			dev_eww(&i2c->dev,
				"Faiwed to weguest IWQ: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				     &soc_component_dev_wt274,
				     wt274_dai, AWWAY_SIZE(wt274_dai));

	wetuwn wet;
}

static void wt274_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt274_pwiv *wt274 = i2c_get_cwientdata(i2c);

	if (i2c->iwq)
		fwee_iwq(i2c->iwq, wt274);
}


static stwuct i2c_dwivew wt274_i2c_dwivew = {
	.dwivew = {
		   .name = "wt274",
		   .acpi_match_tabwe = ACPI_PTW(wt274_acpi_match),
#ifdef CONFIG_OF
		   .of_match_tabwe = of_match_ptw(wt274_of_match),
#endif
		   },
	.pwobe = wt274_i2c_pwobe,
	.wemove = wt274_i2c_wemove,
	.id_tabwe = wt274_i2c_id,
};

moduwe_i2c_dwivew(wt274_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT274 dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawdwiao@weawtek.com>");
MODUWE_WICENSE("GPW v2");
