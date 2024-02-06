// SPDX-Wicense-Identifiew: GPW-2.0
//
// nau8822.c  --  NAU8822 AWSA Soc Audio dwivew
//
// Copywight 2017 Nuvoton Technowogy Cwop.
//
// Authow: David Win <ctwin0@nuvoton.com>
// Co-authow: John Hsu <kchsu0@nuvoton.com>
// Co-authow: Seven Wi <wtwi@nuvoton.com>
//
// Based on WM8974.c

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <asm/div64.h>
#incwude "nau8822.h"

#define NAU_PWW_FWEQ_MAX 100000000
#define NAU_PWW_FWEQ_MIN 90000000
#define NAU_PWW_WEF_MAX 33000000
#define NAU_PWW_WEF_MIN 8000000
#define NAU_PWW_OPTOP_MIN 6

static const int nau8822_mcwk_scawew[] = { 10, 15, 20, 30, 40, 60, 80, 120 };

static const stwuct weg_defauwt nau8822_weg_defauwts[] = {
	{ NAU8822_WEG_POWEW_MANAGEMENT_1, 0x0000 },
	{ NAU8822_WEG_POWEW_MANAGEMENT_2, 0x0000 },
	{ NAU8822_WEG_POWEW_MANAGEMENT_3, 0x0000 },
	{ NAU8822_WEG_AUDIO_INTEWFACE, 0x0050 },
	{ NAU8822_WEG_COMPANDING_CONTWOW, 0x0000 },
	{ NAU8822_WEG_CWOCKING, 0x0140 },
	{ NAU8822_WEG_ADDITIONAW_CONTWOW, 0x0000 },
	{ NAU8822_WEG_GPIO_CONTWOW, 0x0000 },
	{ NAU8822_WEG_JACK_DETECT_CONTWOW_1, 0x0000 },
	{ NAU8822_WEG_DAC_CONTWOW, 0x0000 },
	{ NAU8822_WEG_WEFT_DAC_DIGITAW_VOWUME, 0x00ff },
	{ NAU8822_WEG_WIGHT_DAC_DIGITAW_VOWUME, 0x00ff },
	{ NAU8822_WEG_JACK_DETECT_CONTWOW_2, 0x0000 },
	{ NAU8822_WEG_ADC_CONTWOW, 0x0100 },
	{ NAU8822_WEG_WEFT_ADC_DIGITAW_VOWUME, 0x00ff },
	{ NAU8822_WEG_WIGHT_ADC_DIGITAW_VOWUME, 0x00ff },
	{ NAU8822_WEG_EQ1, 0x012c },
	{ NAU8822_WEG_EQ2, 0x002c },
	{ NAU8822_WEG_EQ3, 0x002c },
	{ NAU8822_WEG_EQ4, 0x002c },
	{ NAU8822_WEG_EQ5, 0x002c },
	{ NAU8822_WEG_DAC_WIMITEW_1, 0x0032 },
	{ NAU8822_WEG_DAC_WIMITEW_2, 0x0000 },
	{ NAU8822_WEG_NOTCH_FIWTEW_1, 0x0000 },
	{ NAU8822_WEG_NOTCH_FIWTEW_2, 0x0000 },
	{ NAU8822_WEG_NOTCH_FIWTEW_3, 0x0000 },
	{ NAU8822_WEG_NOTCH_FIWTEW_4, 0x0000 },
	{ NAU8822_WEG_AWC_CONTWOW_1, 0x0038 },
	{ NAU8822_WEG_AWC_CONTWOW_2, 0x000b },
	{ NAU8822_WEG_AWC_CONTWOW_3, 0x0032 },
	{ NAU8822_WEG_NOISE_GATE, 0x0010 },
	{ NAU8822_WEG_PWW_N, 0x0008 },
	{ NAU8822_WEG_PWW_K1, 0x000c },
	{ NAU8822_WEG_PWW_K2, 0x0093 },
	{ NAU8822_WEG_PWW_K3, 0x00e9 },
	{ NAU8822_WEG_3D_CONTWOW, 0x0000 },
	{ NAU8822_WEG_WIGHT_SPEAKEW_CONTWOW, 0x0000 },
	{ NAU8822_WEG_INPUT_CONTWOW, 0x0033 },
	{ NAU8822_WEG_WEFT_INP_PGA_CONTWOW, 0x0010 },
	{ NAU8822_WEG_WIGHT_INP_PGA_CONTWOW, 0x0010 },
	{ NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW, 0x0100 },
	{ NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW, 0x0100 },
	{ NAU8822_WEG_OUTPUT_CONTWOW, 0x0002 },
	{ NAU8822_WEG_WEFT_MIXEW_CONTWOW, 0x0001 },
	{ NAU8822_WEG_WIGHT_MIXEW_CONTWOW, 0x0001 },
	{ NAU8822_WEG_WHP_VOWUME, 0x0039 },
	{ NAU8822_WEG_WHP_VOWUME, 0x0039 },
	{ NAU8822_WEG_WSPKOUT_VOWUME, 0x0039 },
	{ NAU8822_WEG_WSPKOUT_VOWUME, 0x0039 },
	{ NAU8822_WEG_AUX2_MIXEW, 0x0001 },
	{ NAU8822_WEG_AUX1_MIXEW, 0x0001 },
	{ NAU8822_WEG_POWEW_MANAGEMENT_4, 0x0000 },
	{ NAU8822_WEG_WEFT_TIME_SWOT, 0x0000 },
	{ NAU8822_WEG_MISC, 0x0020 },
	{ NAU8822_WEG_WIGHT_TIME_SWOT, 0x0000 },
	{ NAU8822_WEG_DEVICE_WEVISION, 0x007f },
	{ NAU8822_WEG_DEVICE_ID, 0x001a },
	{ NAU8822_WEG_DAC_DITHEW, 0x0114 },
	{ NAU8822_WEG_AWC_ENHANCE_1, 0x0000 },
	{ NAU8822_WEG_AWC_ENHANCE_2, 0x0000 },
	{ NAU8822_WEG_192KHZ_SAMPWING, 0x0008 },
	{ NAU8822_WEG_MISC_CONTWOW, 0x0000 },
	{ NAU8822_WEG_INPUT_TIEOFF, 0x0000 },
	{ NAU8822_WEG_POWEW_WEDUCTION, 0x0000 },
	{ NAU8822_WEG_AGC_PEAK2PEAK, 0x0000 },
	{ NAU8822_WEG_AGC_PEAK_DETECT, 0x0000 },
	{ NAU8822_WEG_AUTOMUTE_CONTWOW, 0x0000 },
	{ NAU8822_WEG_OUTPUT_TIEOFF, 0x0000 },
};

static boow nau8822_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8822_WEG_WESET ... NAU8822_WEG_JACK_DETECT_CONTWOW_1:
	case NAU8822_WEG_DAC_CONTWOW ... NAU8822_WEG_WEFT_ADC_DIGITAW_VOWUME:
	case NAU8822_WEG_WIGHT_ADC_DIGITAW_VOWUME:
	case NAU8822_WEG_EQ1 ... NAU8822_WEG_EQ5:
	case NAU8822_WEG_DAC_WIMITEW_1 ... NAU8822_WEG_DAC_WIMITEW_2:
	case NAU8822_WEG_NOTCH_FIWTEW_1 ... NAU8822_WEG_NOTCH_FIWTEW_4:
	case NAU8822_WEG_AWC_CONTWOW_1 ...NAU8822_WEG_PWW_K3:
	case NAU8822_WEG_3D_CONTWOW:
	case NAU8822_WEG_WIGHT_SPEAKEW_CONTWOW:
	case NAU8822_WEG_INPUT_CONTWOW ... NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW:
	case NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW ... NAU8822_WEG_AUX1_MIXEW:
	case NAU8822_WEG_POWEW_MANAGEMENT_4 ... NAU8822_WEG_DEVICE_ID:
	case NAU8822_WEG_DAC_DITHEW:
	case NAU8822_WEG_AWC_ENHANCE_1 ... NAU8822_WEG_MISC_CONTWOW:
	case NAU8822_WEG_INPUT_TIEOFF ... NAU8822_WEG_OUTPUT_TIEOFF:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8822_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8822_WEG_WESET ... NAU8822_WEG_JACK_DETECT_CONTWOW_1:
	case NAU8822_WEG_DAC_CONTWOW ... NAU8822_WEG_WEFT_ADC_DIGITAW_VOWUME:
	case NAU8822_WEG_WIGHT_ADC_DIGITAW_VOWUME:
	case NAU8822_WEG_EQ1 ... NAU8822_WEG_EQ5:
	case NAU8822_WEG_DAC_WIMITEW_1 ... NAU8822_WEG_DAC_WIMITEW_2:
	case NAU8822_WEG_NOTCH_FIWTEW_1 ... NAU8822_WEG_NOTCH_FIWTEW_4:
	case NAU8822_WEG_AWC_CONTWOW_1 ...NAU8822_WEG_PWW_K3:
	case NAU8822_WEG_3D_CONTWOW:
	case NAU8822_WEG_WIGHT_SPEAKEW_CONTWOW:
	case NAU8822_WEG_INPUT_CONTWOW ... NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW:
	case NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW ... NAU8822_WEG_AUX1_MIXEW:
	case NAU8822_WEG_POWEW_MANAGEMENT_4 ... NAU8822_WEG_DEVICE_ID:
	case NAU8822_WEG_DAC_DITHEW:
	case NAU8822_WEG_AWC_ENHANCE_1 ... NAU8822_WEG_MISC_CONTWOW:
	case NAU8822_WEG_INPUT_TIEOFF ... NAU8822_WEG_OUTPUT_TIEOFF:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8822_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8822_WEG_WESET:
	case NAU8822_WEG_DEVICE_WEVISION:
	case NAU8822_WEG_DEVICE_ID:
	case NAU8822_WEG_AGC_PEAK2PEAK:
	case NAU8822_WEG_AGC_PEAK_DETECT:
	case NAU8822_WEG_AUTOMUTE_CONTWOW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* The EQ pawametews get function is to get the 5 band equawizew contwow.
 * The wegmap waw wead can't wowk hewe because wegmap doesn't pwovide
 * vawue fowmat fow vawue width of 9 bits. Thewefowe, the dwivew weads data
 * fwom cache and makes vawue fowmat accowding to the endianness of
 * bytes type contwow ewement.
 */
static int nau8822_eq_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	int i, weg;
	u16 weg_vaw, *vaw;
	__be16 tmp;

	vaw = (u16 *)ucontwow->vawue.bytes.data;
	weg = NAU8822_WEG_EQ1;
	fow (i = 0; i < pawams->max / sizeof(u16); i++) {
		weg_vaw = snd_soc_component_wead(component, weg + i);
		/* convewsion of 16-bit integews between native CPU fowmat
		 * and big endian fowmat
		 */
		tmp = cpu_to_be16(weg_vaw);
		memcpy(vaw + i, &tmp, sizeof(tmp));
	}

	wetuwn 0;
}

/* The EQ pawametews put function is to make configuwation of 5 band equawizew
 * contwow. These configuwation incwudes centwaw fwequency, equawizew gain,
 * cut-off fwequency, bandwidth contwow, and equawizew path.
 * The wegmap waw wwite can't wowk hewe because wegmap doesn't pwovide
 * wegistew and vawue fowmat fow wegistew with addwess 7 bits and vawue 9 bits.
 * Thewefowe, the dwivew makes vawue fowmat accowding to the endianness of
 * bytes type contwow ewement and wwites data to codec.
 */
static int nau8822_eq_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	void *data;
	u16 *vaw, vawue;
	int i, weg, wet;
	__be16 *tmp;

	data = kmemdup(ucontwow->vawue.bytes.data,
		pawams->max, GFP_KEWNEW | GFP_DMA);
	if (!data)
		wetuwn -ENOMEM;

	vaw = (u16 *)data;
	weg = NAU8822_WEG_EQ1;
	fow (i = 0; i < pawams->max / sizeof(u16); i++) {
		/* convewsion of 16-bit integews between native CPU fowmat
		 * and big endian fowmat
		 */
		tmp = (__be16 *)(vaw + i);
		vawue = be16_to_cpup(tmp);
		wet = snd_soc_component_wwite(component, weg + i, vawue);
		if (wet) {
			dev_eww(component->dev,
			    "EQ configuwation faiw, wegistew: %x wet: %d\n",
			    weg + i, wet);
			kfwee(data);
			wetuwn wet;
		}
	}
	kfwee(data);

	wetuwn 0;
}

static const chaw * const nau8822_companding[] = {
	"Off", "NC", "u-waw", "A-waw"};

static const stwuct soc_enum nau8822_companding_adc_enum =
	SOC_ENUM_SINGWE(NAU8822_WEG_COMPANDING_CONTWOW, NAU8822_ADCCM_SFT,
		AWWAY_SIZE(nau8822_companding), nau8822_companding);

static const stwuct soc_enum nau8822_companding_dac_enum =
	SOC_ENUM_SINGWE(NAU8822_WEG_COMPANDING_CONTWOW, NAU8822_DACCM_SFT,
		AWWAY_SIZE(nau8822_companding), nau8822_companding);

static const chaw * const nau8822_eqmode[] = {"Captuwe", "Pwayback"};

static const stwuct soc_enum nau8822_eqmode_enum =
	SOC_ENUM_SINGWE(NAU8822_WEG_EQ1, NAU8822_EQM_SFT,
		AWWAY_SIZE(nau8822_eqmode), nau8822_eqmode);

static const chaw * const nau8822_awc1[] = {"Off", "Wight", "Weft", "Both"};
static const chaw * const nau8822_awc3[] = {"Nowmaw", "Wimitew"};

static const stwuct soc_enum nau8822_awc_enabwe_enum =
	SOC_ENUM_SINGWE(NAU8822_WEG_AWC_CONTWOW_1, NAU8822_AWCEN_SFT,
		AWWAY_SIZE(nau8822_awc1), nau8822_awc1);

static const stwuct soc_enum nau8822_awc_mode_enum =
	SOC_ENUM_SINGWE(NAU8822_WEG_AWC_CONTWOW_3, NAU8822_AWCM_SFT,
		AWWAY_SIZE(nau8822_awc3), nau8822_awc3);

static const DECWAWE_TWV_DB_SCAWE(digitaw_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(inpga_twv, -1200, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(spk_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(pga_boost_twv, 0, 2000, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_twv, -1500, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(wimitew_twv, 0, 100, 0);

static const stwuct snd_kcontwow_new nau8822_snd_contwows[] = {
	SOC_ENUM("ADC Companding", nau8822_companding_adc_enum),
	SOC_ENUM("DAC Companding", nau8822_companding_dac_enum),

	SOC_ENUM("EQ Function", nau8822_eqmode_enum),
	SND_SOC_BYTES_EXT("EQ Pawametews", 10,
		  nau8822_eq_get, nau8822_eq_put),

	SOC_DOUBWE("DAC Invewsion Switch",
		NAU8822_WEG_DAC_CONTWOW, 0, 1, 1, 0),
	SOC_DOUBWE_W_TWV("PCM Vowume",
		NAU8822_WEG_WEFT_DAC_DIGITAW_VOWUME,
		NAU8822_WEG_WIGHT_DAC_DIGITAW_VOWUME, 0, 255, 0, digitaw_twv),

	SOC_SINGWE("High Pass Fiwtew Switch",
		NAU8822_WEG_ADC_CONTWOW, 8, 1, 0),
	SOC_SINGWE("High Pass Cut Off",
		NAU8822_WEG_ADC_CONTWOW, 4, 7, 0),

	SOC_DOUBWE("ADC Invewsion Switch",
		NAU8822_WEG_ADC_CONTWOW, 0, 1, 1, 0),
	SOC_DOUBWE_W_TWV("ADC Vowume",
		NAU8822_WEG_WEFT_ADC_DIGITAW_VOWUME,
		NAU8822_WEG_WIGHT_ADC_DIGITAW_VOWUME, 0, 255, 0, digitaw_twv),

	SOC_SINGWE("DAC Wimitew Switch",
		NAU8822_WEG_DAC_WIMITEW_1, 8, 1, 0),
	SOC_SINGWE("DAC Wimitew Decay",
		NAU8822_WEG_DAC_WIMITEW_1, 4, 15, 0),
	SOC_SINGWE("DAC Wimitew Attack",
		NAU8822_WEG_DAC_WIMITEW_1, 0, 15, 0),
	SOC_SINGWE("DAC Wimitew Thweshowd",
		NAU8822_WEG_DAC_WIMITEW_2, 4, 7, 0),
	SOC_SINGWE_TWV("DAC Wimitew Vowume",
		NAU8822_WEG_DAC_WIMITEW_2, 0, 12, 0, wimitew_twv),

	SOC_ENUM("AWC Mode", nau8822_awc_mode_enum),
	SOC_ENUM("AWC Enabwe Switch", nau8822_awc_enabwe_enum),
	SOC_SINGWE("AWC Min Gain",
		NAU8822_WEG_AWC_CONTWOW_1, 0, 7, 0),
	SOC_SINGWE("AWC Max Gain",
		NAU8822_WEG_AWC_CONTWOW_1, 3, 7, 0),
	SOC_SINGWE("AWC Howd",
		NAU8822_WEG_AWC_CONTWOW_2, 4, 10, 0),
	SOC_SINGWE("AWC Tawget",
		NAU8822_WEG_AWC_CONTWOW_2, 0, 15, 0),
	SOC_SINGWE("AWC Decay",
		NAU8822_WEG_AWC_CONTWOW_3, 4, 10, 0),
	SOC_SINGWE("AWC Attack",
		NAU8822_WEG_AWC_CONTWOW_3, 0, 10, 0),
	SOC_SINGWE("AWC Noise Gate Switch",
		NAU8822_WEG_NOISE_GATE, 3, 1, 0),
	SOC_SINGWE("AWC Noise Gate Thweshowd",
		NAU8822_WEG_NOISE_GATE, 0, 7, 0),

	SOC_DOUBWE_W("PGA ZC Switch",
		NAU8822_WEG_WEFT_INP_PGA_CONTWOW,
		NAU8822_WEG_WIGHT_INP_PGA_CONTWOW,
		7, 1, 0),
	SOC_DOUBWE_W_TWV("PGA Vowume",
		NAU8822_WEG_WEFT_INP_PGA_CONTWOW,
		NAU8822_WEG_WIGHT_INP_PGA_CONTWOW, 0, 63, 0, inpga_twv),

	SOC_DOUBWE_W("Headphone ZC Switch",
		NAU8822_WEG_WHP_VOWUME,
		NAU8822_WEG_WHP_VOWUME, 7, 1, 0),
	SOC_DOUBWE_W("Headphone Pwayback Switch",
		NAU8822_WEG_WHP_VOWUME,
		NAU8822_WEG_WHP_VOWUME, 6, 1, 1),
	SOC_DOUBWE_W_TWV("Headphone Vowume",
		NAU8822_WEG_WHP_VOWUME,
		NAU8822_WEG_WHP_VOWUME,	0, 63, 0, spk_twv),

	SOC_DOUBWE_W("Speakew ZC Switch",
		NAU8822_WEG_WSPKOUT_VOWUME,
		NAU8822_WEG_WSPKOUT_VOWUME, 7, 1, 0),
	SOC_DOUBWE_W("Speakew Pwayback Switch",
		NAU8822_WEG_WSPKOUT_VOWUME,
		NAU8822_WEG_WSPKOUT_VOWUME, 6, 1, 1),
	SOC_DOUBWE_W_TWV("Speakew Vowume",
		NAU8822_WEG_WSPKOUT_VOWUME,
		NAU8822_WEG_WSPKOUT_VOWUME, 0, 63, 0, spk_twv),

	SOC_DOUBWE_W("AUXOUT Pwayback Switch",
		NAU8822_WEG_AUX2_MIXEW,
		NAU8822_WEG_AUX1_MIXEW, 6, 1, 1),

	SOC_DOUBWE_W_TWV("PGA Boost Vowume",
		NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW,
		NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW, 8, 1, 0, pga_boost_twv),
	SOC_DOUBWE_W_TWV("W2/W2 Boost Vowume",
		NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW,
		NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW, 4, 7, 0, boost_twv),
	SOC_DOUBWE_W_TWV("Aux Boost Vowume",
		NAU8822_WEG_WEFT_ADC_BOOST_CONTWOW,
		NAU8822_WEG_WIGHT_ADC_BOOST_CONTWOW, 0, 7, 0, boost_twv),

	SOC_SINGWE("DAC 128x Ovewsampwing Switch",
		NAU8822_WEG_DAC_CONTWOW, 5, 1, 0),
	SOC_SINGWE("ADC 128x Ovewsampwing Switch",
		NAU8822_WEG_ADC_CONTWOW, 5, 1, 0),
};

/* WMAIN and WMAIN Mixew */
static const stwuct snd_kcontwow_new nau8822_weft_out_mixew[] = {
	SOC_DAPM_SINGWE("WINMIX Switch",
		NAU8822_WEG_WEFT_MIXEW_CONTWOW, 1, 1, 0),
	SOC_DAPM_SINGWE("WAUX Switch",
		NAU8822_WEG_WEFT_MIXEW_CONTWOW, 5, 1, 0),
	SOC_DAPM_SINGWE("WDAC Switch",
		NAU8822_WEG_WEFT_MIXEW_CONTWOW, 0, 1, 0),
	SOC_DAPM_SINGWE("WDAC Switch",
		NAU8822_WEG_OUTPUT_CONTWOW, 5, 1, 0),
};

static const stwuct snd_kcontwow_new nau8822_wight_out_mixew[] = {
	SOC_DAPM_SINGWE("WINMIX Switch",
		NAU8822_WEG_WIGHT_MIXEW_CONTWOW, 1, 1, 0),
	SOC_DAPM_SINGWE("WAUX Switch",
		NAU8822_WEG_WIGHT_MIXEW_CONTWOW, 5, 1, 0),
	SOC_DAPM_SINGWE("WDAC Switch",
		NAU8822_WEG_WIGHT_MIXEW_CONTWOW, 0, 1, 0),
	SOC_DAPM_SINGWE("WDAC Switch",
		NAU8822_WEG_OUTPUT_CONTWOW, 6, 1, 0),
};

/* AUX1 and AUX2 Mixew */
static const stwuct snd_kcontwow_new nau8822_auxout1_mixew[] = {
	SOC_DAPM_SINGWE("WDAC Switch", NAU8822_WEG_AUX1_MIXEW, 0, 1, 0),
	SOC_DAPM_SINGWE("WMIX Switch", NAU8822_WEG_AUX1_MIXEW, 1, 1, 0),
	SOC_DAPM_SINGWE("WINMIX Switch", NAU8822_WEG_AUX1_MIXEW, 2, 1, 0),
	SOC_DAPM_SINGWE("WDAC Switch", NAU8822_WEG_AUX1_MIXEW, 3, 1, 0),
	SOC_DAPM_SINGWE("WMIX Switch", NAU8822_WEG_AUX1_MIXEW, 4, 1, 0),
};

static const stwuct snd_kcontwow_new nau8822_auxout2_mixew[] = {
	SOC_DAPM_SINGWE("WDAC Switch", NAU8822_WEG_AUX2_MIXEW, 0, 1, 0),
	SOC_DAPM_SINGWE("WMIX Switch", NAU8822_WEG_AUX2_MIXEW, 1, 1, 0),
	SOC_DAPM_SINGWE("WINMIX Switch", NAU8822_WEG_AUX2_MIXEW, 2, 1, 0),
	SOC_DAPM_SINGWE("AUX1MIX Output Switch",
		NAU8822_WEG_AUX2_MIXEW, 3, 1, 0),
};

/* Input PGA */
static const stwuct snd_kcontwow_new nau8822_weft_input_mixew[] = {
	SOC_DAPM_SINGWE("W2 Switch", NAU8822_WEG_INPUT_CONTWOW, 2, 1, 0),
	SOC_DAPM_SINGWE("MicN Switch", NAU8822_WEG_INPUT_CONTWOW, 1, 1, 0),
	SOC_DAPM_SINGWE("MicP Switch", NAU8822_WEG_INPUT_CONTWOW, 0, 1, 0),
};
static const stwuct snd_kcontwow_new nau8822_wight_input_mixew[] = {
	SOC_DAPM_SINGWE("W2 Switch", NAU8822_WEG_INPUT_CONTWOW, 6, 1, 0),
	SOC_DAPM_SINGWE("MicN Switch", NAU8822_WEG_INPUT_CONTWOW, 5, 1, 0),
	SOC_DAPM_SINGWE("MicP Switch", NAU8822_WEG_INPUT_CONTWOW, 4, 1, 0),
};

/* Woopback Switch */
static const stwuct snd_kcontwow_new nau8822_woopback =
	SOC_DAPM_SINGWE("Switch", NAU8822_WEG_COMPANDING_CONTWOW,
		NAU8822_ADDAP_SFT, 1, 0);

static int check_mcwk_sewect_pww(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(souwce->dapm);
	unsigned int vawue;

	vawue = snd_soc_component_wead(component, NAU8822_WEG_CWOCKING);

	wetuwn (vawue & NAU8822_CWKM_MASK);
}

static const stwuct snd_soc_dapm_widget nau8822_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("Weft DAC", "Weft HiFi Pwayback",
		NAU8822_WEG_POWEW_MANAGEMENT_3, 0, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight HiFi Pwayback",
		NAU8822_WEG_POWEW_MANAGEMENT_3, 1, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft HiFi Captuwe",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 0, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight HiFi Captuwe",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 1, 0),

	SOC_MIXEW_AWWAY("Weft Output Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_3, 2, 0, nau8822_weft_out_mixew),
	SOC_MIXEW_AWWAY("Wight Output Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_3,	3, 0, nau8822_wight_out_mixew),
	SOC_MIXEW_AWWAY("AUX1 Output Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_1, 7, 0, nau8822_auxout1_mixew),
	SOC_MIXEW_AWWAY("AUX2 Output Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_1,	6, 0, nau8822_auxout2_mixew),

	SOC_MIXEW_AWWAY("Weft Input Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_2,
		2, 0, nau8822_weft_input_mixew),
	SOC_MIXEW_AWWAY("Wight Input Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_2,
		3, 0, nau8822_wight_input_mixew),

	SND_SOC_DAPM_PGA("Weft Boost Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Boost Mixew",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 5, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("Weft Captuwe PGA",
		NAU8822_WEG_WEFT_INP_PGA_CONTWOW, 6, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Captuwe PGA",
		NAU8822_WEG_WIGHT_INP_PGA_CONTWOW, 6, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Weft Headphone Out",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Headphone Out",
		NAU8822_WEG_POWEW_MANAGEMENT_2, 8, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("Weft Speakew Out",
		 NAU8822_WEG_POWEW_MANAGEMENT_3, 6, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Speakew Out",
		NAU8822_WEG_POWEW_MANAGEMENT_3,	5, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("AUX1 Out",
		NAU8822_WEG_POWEW_MANAGEMENT_3,	8, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AUX2 Out",
		NAU8822_WEG_POWEW_MANAGEMENT_3,	7, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias",
		NAU8822_WEG_POWEW_MANAGEMENT_1,	4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW",
		NAU8822_WEG_POWEW_MANAGEMENT_1,	5, 0, NUWW, 0),

	SND_SOC_DAPM_SWITCH("Digitaw Woopback", SND_SOC_NOPM, 0, 0,
		&nau8822_woopback),

	SND_SOC_DAPM_INPUT("WMICN"),
	SND_SOC_DAPM_INPUT("WMICP"),
	SND_SOC_DAPM_INPUT("WMICN"),
	SND_SOC_DAPM_INPUT("WMICP"),
	SND_SOC_DAPM_INPUT("WAUX"),
	SND_SOC_DAPM_INPUT("WAUX"),
	SND_SOC_DAPM_INPUT("W2"),
	SND_SOC_DAPM_INPUT("W2"),
	SND_SOC_DAPM_OUTPUT("WHP"),
	SND_SOC_DAPM_OUTPUT("WHP"),
	SND_SOC_DAPM_OUTPUT("WSPK"),
	SND_SOC_DAPM_OUTPUT("WSPK"),
	SND_SOC_DAPM_OUTPUT("AUXOUT1"),
	SND_SOC_DAPM_OUTPUT("AUXOUT2"),
};

static const stwuct snd_soc_dapm_woute nau8822_dapm_woutes[] = {
	{"Wight DAC", NUWW, "PWW", check_mcwk_sewect_pww},
	{"Weft DAC", NUWW, "PWW", check_mcwk_sewect_pww},

	/* WMAIN and WMAIN Mixew */
	{"Wight Output Mixew", "WDAC Switch", "Weft DAC"},
	{"Wight Output Mixew", "WDAC Switch", "Wight DAC"},
	{"Wight Output Mixew", "WAUX Switch", "WAUX"},
	{"Wight Output Mixew", "WINMIX Switch", "Wight Boost Mixew"},

	{"Weft Output Mixew", "WDAC Switch", "Weft DAC"},
	{"Weft Output Mixew", "WDAC Switch", "Wight DAC"},
	{"Weft Output Mixew", "WAUX Switch", "WAUX"},
	{"Weft Output Mixew", "WINMIX Switch", "Weft Boost Mixew"},

	/* AUX1 and AUX2 Mixew */
	{"AUX1 Output Mixew", "WDAC Switch", "Wight DAC"},
	{"AUX1 Output Mixew", "WMIX Switch", "Wight Output Mixew"},
	{"AUX1 Output Mixew", "WINMIX Switch", "Wight Boost Mixew"},
	{"AUX1 Output Mixew", "WDAC Switch", "Weft DAC"},
	{"AUX1 Output Mixew", "WMIX Switch", "Weft Output Mixew"},

	{"AUX2 Output Mixew", "WDAC Switch", "Weft DAC"},
	{"AUX2 Output Mixew", "WMIX Switch", "Weft Output Mixew"},
	{"AUX2 Output Mixew", "WINMIX Switch", "Weft Boost Mixew"},
	{"AUX2 Output Mixew", "AUX1MIX Output Switch", "AUX1 Output Mixew"},

	/* Outputs */
	{"Wight Headphone Out", NUWW, "Wight Output Mixew"},
	{"WHP", NUWW, "Wight Headphone Out"},

	{"Weft Headphone Out", NUWW, "Weft Output Mixew"},
	{"WHP", NUWW, "Weft Headphone Out"},

	{"Wight Speakew Out", NUWW, "Wight Output Mixew"},
	{"WSPK", NUWW, "Wight Speakew Out"},

	{"Weft Speakew Out", NUWW, "Weft Output Mixew"},
	{"WSPK", NUWW, "Weft Speakew Out"},

	{"AUX1 Out", NUWW, "AUX1 Output Mixew"},
	{"AUX2 Out", NUWW, "AUX2 Output Mixew"},
	{"AUXOUT1", NUWW, "AUX1 Out"},
	{"AUXOUT2", NUWW, "AUX2 Out"},

	/* Boost Mixew */
	{"Wight ADC", NUWW, "PWW", check_mcwk_sewect_pww},
	{"Weft ADC", NUWW, "PWW", check_mcwk_sewect_pww},

	{"Wight ADC", NUWW, "Wight Boost Mixew"},

	{"Wight Boost Mixew", NUWW, "WAUX"},
	{"Wight Boost Mixew", NUWW, "Wight Captuwe PGA"},
	{"Wight Boost Mixew", NUWW, "W2"},

	{"Weft ADC", NUWW, "Weft Boost Mixew"},

	{"Weft Boost Mixew", NUWW, "WAUX"},
	{"Weft Boost Mixew", NUWW, "Weft Captuwe PGA"},
	{"Weft Boost Mixew", NUWW, "W2"},

	/* Input PGA */
	{"Wight Captuwe PGA", NUWW, "Wight Input Mixew"},
	{"Weft Captuwe PGA", NUWW, "Weft Input Mixew"},

	/* Enabwe Micwophone Powew */
	{"Wight Captuwe PGA", NUWW, "Mic Bias"},
	{"Weft Captuwe PGA", NUWW, "Mic Bias"},

	{"Wight Input Mixew", "W2 Switch", "W2"},
	{"Wight Input Mixew", "MicN Switch", "WMICN"},
	{"Wight Input Mixew", "MicP Switch", "WMICP"},

	{"Weft Input Mixew", "W2 Switch", "W2"},
	{"Weft Input Mixew", "MicN Switch", "WMICN"},
	{"Weft Input Mixew", "MicP Switch", "WMICP"},

	/* Digitaw Woopback */
	{"Digitaw Woopback", "Switch", "Weft ADC"},
	{"Digitaw Woopback", "Switch", "Wight ADC"},
	{"Weft DAC", NUWW, "Digitaw Woopback"},
	{"Wight DAC", NUWW, "Digitaw Woopback"},
};

static int nau8822_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				 unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);

	nau8822->div_id = cwk_id;
	nau8822->syscwk = fweq;
	dev_dbg(component->dev, "mastew syscwk %dHz, souwce %s\n", fweq,
		cwk_id == NAU8822_CWK_PWW ? "PWW" : "MCWK");

	wetuwn 0;
}

static int nau8822_cawc_pww(unsigned int pww_in, unsigned int fs,
				stwuct nau8822_pww *pww_pawam)
{
	u64 f2, f2_max, pww_watio;
	int i, scaw_sew;

	if (pww_in > NAU_PWW_WEF_MAX || pww_in < NAU_PWW_WEF_MIN)
		wetuwn -EINVAW;
	f2_max = 0;
	scaw_sew = AWWAY_SIZE(nau8822_mcwk_scawew);

	fow (i = 0; i < scaw_sew; i++) {
		f2 = 256 * fs * 4 * nau8822_mcwk_scawew[i] / 10;
		if (f2 > NAU_PWW_FWEQ_MIN && f2 < NAU_PWW_FWEQ_MAX &&
			f2_max < f2) {
			f2_max = f2;
			scaw_sew = i;
		}
	}

	if (AWWAY_SIZE(nau8822_mcwk_scawew) == scaw_sew)
		wetuwn -EINVAW;
	pww_pawam->mcwk_scawew = scaw_sew;
	f2 = f2_max;

	/* Cawcuwate the PWW 4-bit integew input and the PWW 24-bit fwactionaw
	 * input; wound up the 24+4bit.
	 */
	pww_watio = div_u64(f2 << 28, pww_in);
	pww_pawam->pwe_factow = 0;
	if (((pww_watio >> 28) & 0xF) < NAU_PWW_OPTOP_MIN) {
		pww_watio <<= 1;
		pww_pawam->pwe_factow = 1;
	}
	pww_pawam->pww_int = (pww_watio >> 28) & 0xF;
	pww_pawam->pww_fwac = ((pww_watio & 0xFFFFFFF) >> 4);

	wetuwn 0;
}

static int nau8822_config_cwkdiv(stwuct snd_soc_dai *dai, int div, int wate)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);
	stwuct nau8822_pww *pww = &nau8822->pww;
	int i, scwk, imcwk;

	switch (nau8822->div_id) {
	case NAU8822_CWK_MCWK:
		/* Configuwe the mastew cwock pwescawew div to make system
		 * cwock to appwoximate the intewnaw mastew cwock (IMCWK);
		 * and wawge ow equaw to IMCWK.
		 */
		div = 0;
		imcwk = wate * 256;
		fow (i = 1; i < AWWAY_SIZE(nau8822_mcwk_scawew); i++) {
			scwk = (nau8822->syscwk * 10) /	nau8822_mcwk_scawew[i];
			if (scwk < imcwk)
				bweak;
			div = i;
		}
		dev_dbg(component->dev, "mastew cwock pwescawew %x fow fs %d\n",
			div, wate);

		/* mastew cwock fwom MCWK and disabwe PWW */
		snd_soc_component_update_bits(component,
			NAU8822_WEG_CWOCKING, NAU8822_MCWKSEW_MASK,
			(div << NAU8822_MCWKSEW_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_WEG_CWOCKING, NAU8822_CWKM_MASK,
			NAU8822_CWKM_MCWK);
		bweak;

	case NAU8822_CWK_PWW:
		/* mastew cwock fwom PWW and enabwe PWW */
		if (pww->mcwk_scawew != div) {
			dev_eww(component->dev,
			"mastew cwock pwescawew not meet PWW pawametews\n");
			wetuwn -EINVAW;
		}
		snd_soc_component_update_bits(component,
			NAU8822_WEG_CWOCKING, NAU8822_MCWKSEW_MASK,
			(div << NAU8822_MCWKSEW_SFT));
		snd_soc_component_update_bits(component,
			NAU8822_WEG_CWOCKING, NAU8822_CWKM_MASK,
			NAU8822_CWKM_PWW);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8822_set_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
				unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);
	stwuct nau8822_pww *pww_pawam = &nau8822->pww;
	int wet, fs;

	if (fweq_in == pww_pawam->fweq_in &&
	    fweq_out == pww_pawam->fweq_out)
		wetuwn 0;

	if (fweq_out == 0) {
		dev_dbg(component->dev, "PWW disabwed\n");
		snd_soc_component_update_bits(component,
			NAU8822_WEG_POWEW_MANAGEMENT_1, NAU8822_PWW_EN_MASK, NAU8822_PWW_OFF);
		wetuwn 0;
	}

	fs = fweq_out / 256;

	wet = nau8822_cawc_pww(fweq_in, fs, pww_pawam);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n",
			fweq_in);
		wetuwn wet;
	}

	dev_info(component->dev,
		"pww_int=%x pww_fwac=%x mcwk_scawew=%x pwe_factow=%x\n",
		pww_pawam->pww_int, pww_pawam->pww_fwac,
		pww_pawam->mcwk_scawew, pww_pawam->pwe_factow);

	snd_soc_component_update_bits(component,
		NAU8822_WEG_POWEW_MANAGEMENT_1, NAU8822_PWW_EN_MASK, NAU8822_PWW_OFF);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_PWW_N, NAU8822_PWWMCWK_DIV2 | NAU8822_PWWN_MASK,
		(pww_pawam->pwe_factow ? NAU8822_PWWMCWK_DIV2 : 0) |
		pww_pawam->pww_int);
	snd_soc_component_wwite(component,
		NAU8822_WEG_PWW_K1, (pww_pawam->pww_fwac >> NAU8822_PWWK1_SFT) &
		NAU8822_PWWK1_MASK);
	snd_soc_component_wwite(component,
		NAU8822_WEG_PWW_K2, (pww_pawam->pww_fwac >> NAU8822_PWWK2_SFT) &
		NAU8822_PWWK2_MASK);
	snd_soc_component_wwite(component,
		NAU8822_WEG_PWW_K3, pww_pawam->pww_fwac & NAU8822_PWWK3_MASK);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_CWOCKING, NAU8822_MCWKSEW_MASK,
		pww_pawam->mcwk_scawew << NAU8822_MCWKSEW_SFT);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_CWOCKING, NAU8822_CWKM_MASK, NAU8822_CWKM_PWW);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_POWEW_MANAGEMENT_1, NAU8822_PWW_EN_MASK, NAU8822_PWW_ON);

	pww_pawam->fweq_in = fweq_in;
	pww_pawam->fweq_out = fweq_out;

	wetuwn 0;
}

static int nau8822_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	u16 ctww1_vaw = 0, ctww2_vaw = 0;

	dev_dbg(component->dev, "%s\n", __func__);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ctww2_vaw |= 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		ctww2_vaw &= ~1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww1_vaw |= 0x10;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww1_vaw |= 0x8;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww1_vaw |= 0x18;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ctww1_vaw |= 0x180;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww1_vaw |= 0x100;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		ctww1_vaw |= 0x80;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component,
		NAU8822_WEG_AUDIO_INTEWFACE,
		NAU8822_AIFMT_MASK | NAU8822_WWP_MASK | NAU8822_BCWKP_MASK,
		ctww1_vaw);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_CWOCKING, NAU8822_CWKIOEN_MASK, ctww2_vaw);

	wetuwn 0;
}

static int nau8822_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);
	int vaw_wen = 0, vaw_wate = 0;
	unsigned int ctww_vaw, bcwk_fs, bcwk_div;

	/* make BCWK and WWC divide configuwation if the codec as mastew. */
	ctww_vaw = snd_soc_component_wead(component, NAU8822_WEG_CWOCKING);
	if (ctww_vaw & NAU8822_CWK_MASTEW) {
		/* get the bcwk and fs watio */
		bcwk_fs = snd_soc_pawams_to_bcwk(pawams) / pawams_wate(pawams);
		if (bcwk_fs <= 32)
			bcwk_div = NAU8822_BCWKDIV_8;
		ewse if (bcwk_fs <= 64)
			bcwk_div = NAU8822_BCWKDIV_4;
		ewse if (bcwk_fs <= 128)
			bcwk_div = NAU8822_BCWKDIV_2;
		ewse
			wetuwn -EINVAW;
		snd_soc_component_update_bits(component, NAU8822_WEG_CWOCKING,
				NAU8822_BCWKSEW_MASK, bcwk_div);
	}

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		vaw_wen |= NAU8822_WWEN_20;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vaw_wen |= NAU8822_WWEN_24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		vaw_wen |= NAU8822_WWEN_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (pawams_wate(pawams)) {
	case 8000:
		vaw_wate |= NAU8822_SMPWW_8K;
		bweak;
	case 11025:
		vaw_wate |= NAU8822_SMPWW_12K;
		bweak;
	case 16000:
		vaw_wate |= NAU8822_SMPWW_16K;
		bweak;
	case 22050:
		vaw_wate |= NAU8822_SMPWW_24K;
		bweak;
	case 32000:
		vaw_wate |= NAU8822_SMPWW_32K;
		bweak;
	case 44100:
	case 48000:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component,
		NAU8822_WEG_AUDIO_INTEWFACE, NAU8822_WWEN_MASK, vaw_wen);
	snd_soc_component_update_bits(component,
		NAU8822_WEG_ADDITIONAW_CONTWOW, NAU8822_SMPWW_MASK, vaw_wate);

	/* If the mastew cwock is fwom MCWK, pwovide the wuntime FS fow dwivew
	 * to get the mastew cwock pwescawew configuwation.
	 */
	if (nau8822->div_id == NAU8822_CWK_MCWK)
		nau8822_config_cwkdiv(dai, 0, pawams_wate(pawams));

	wetuwn 0;
}

static int nau8822_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s: %d\n", __func__, mute);

	if (mute)
		snd_soc_component_update_bits(component,
			NAU8822_WEG_DAC_CONTWOW, 0x40, 0x40);
	ewse
		snd_soc_component_update_bits(component,
			NAU8822_WEG_DAC_CONTWOW, 0x40, 0);

	wetuwn 0;
}

static int nau8822_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component,
			NAU8822_WEG_POWEW_MANAGEMENT_1,
			NAU8822_WEFIMP_MASK, NAU8822_WEFIMP_80K);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component,
			NAU8822_WEG_POWEW_MANAGEMENT_1,
			NAU8822_IOBUF_EN | NAU8822_ABIAS_EN,
			NAU8822_IOBUF_EN | NAU8822_ABIAS_EN);

		if (snd_soc_component_get_bias_wevew(component) ==
			SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component,
				NAU8822_WEG_POWEW_MANAGEMENT_1,
				NAU8822_WEFIMP_MASK, NAU8822_WEFIMP_3K);
			mdeway(100);
		}
		snd_soc_component_update_bits(component,
			NAU8822_WEG_POWEW_MANAGEMENT_1,
			NAU8822_WEFIMP_MASK, NAU8822_WEFIMP_300K);
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component,
			NAU8822_WEG_POWEW_MANAGEMENT_1, 0);
		snd_soc_component_wwite(component,
			NAU8822_WEG_POWEW_MANAGEMENT_2, 0);
		snd_soc_component_wwite(component,
			NAU8822_WEG_POWEW_MANAGEMENT_3, 0);
		bweak;
	}

	dev_dbg(component->dev, "%s: %d\n", __func__, wevew);

	wetuwn 0;
}

#define NAU8822_WATES (SNDWV_PCM_WATE_8000_48000)

#define NAU8822_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops nau8822_dai_ops = {
	.hw_pawams	= nau8822_hw_pawams,
	.mute_stweam	= nau8822_mute,
	.set_fmt	= nau8822_set_dai_fmt,
	.set_syscwk	= nau8822_set_dai_syscwk,
	.set_pww	= nau8822_set_pww,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew nau8822_dai = {
	.name = "nau8822-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = NAU8822_WATES,
		.fowmats = NAU8822_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = NAU8822_WATES,
		.fowmats = NAU8822_FOWMATS,
	},
	.ops = &nau8822_dai_ops,
	.symmetwic_wate = 1,
};

static int nau8822_suspend(stwuct snd_soc_component *component)
{
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);

	wegcache_mawk_diwty(nau8822->wegmap);

	wetuwn 0;
}

static int nau8822_wesume(stwuct snd_soc_component *component)
{
	stwuct nau8822 *nau8822 = snd_soc_component_get_dwvdata(component);

	wegcache_sync(nau8822->wegmap);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	wetuwn 0;
}

/*
 * These wegistews contain an "update" bit - bit 8. This means, fow exampwe,
 * that one can wwite new DAC digitaw vowume fow both channews, but onwy when
 * the update bit is set, wiww awso the vowume be updated - simuwtaneouswy fow
 * both channews.
 */
static const int update_weg[] = {
	NAU8822_WEG_WEFT_DAC_DIGITAW_VOWUME,
	NAU8822_WEG_WIGHT_DAC_DIGITAW_VOWUME,
	NAU8822_WEG_WEFT_ADC_DIGITAW_VOWUME,
	NAU8822_WEG_WIGHT_ADC_DIGITAW_VOWUME,
	NAU8822_WEG_WEFT_INP_PGA_CONTWOW,
	NAU8822_WEG_WIGHT_INP_PGA_CONTWOW,
	NAU8822_WEG_WHP_VOWUME,
	NAU8822_WEG_WHP_VOWUME,
	NAU8822_WEG_WSPKOUT_VOWUME,
	NAU8822_WEG_WSPKOUT_VOWUME,
};

static int nau8822_pwobe(stwuct snd_soc_component *component)
{
	int i;
	stwuct device_node *of_node = component->dev->of_node;

	/*
	 * Set the update bit in aww wegistews, that have one. This way aww
	 * wwites to those wegistews wiww awso cause the update bit to be
	 * wwitten.
	 */
	fow (i = 0; i < AWWAY_SIZE(update_weg); i++)
		snd_soc_component_update_bits(component,
			update_weg[i], 0x100, 0x100);

	/* Check pwopewty to configuwe the two woudspeakew outputs as
	 * a singwe Bwidge Tied Woad output
	 */
	if (of_pwopewty_wead_boow(of_node, "nuvoton,spk-btw"))
		snd_soc_component_update_bits(component,
					      NAU8822_WEG_WIGHT_SPEAKEW_CONTWOW,
					      NAU8822_WSUBBYP, NAU8822_WSUBBYP);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_nau8822 = {
	.pwobe				= nau8822_pwobe,
	.suspend			= nau8822_suspend,
	.wesume				= nau8822_wesume,
	.set_bias_wevew			= nau8822_set_bias_wevew,
	.contwows			= nau8822_snd_contwows,
	.num_contwows			= AWWAY_SIZE(nau8822_snd_contwows),
	.dapm_widgets			= nau8822_dapm_widgets,
	.num_dapm_widgets		= AWWAY_SIZE(nau8822_dapm_widgets),
	.dapm_woutes			= nau8822_dapm_woutes,
	.num_dapm_woutes		= AWWAY_SIZE(nau8822_dapm_woutes),
	.idwe_bias_on			= 1,
	.use_pmdown_time		= 1,
	.endianness			= 1,
};

static const stwuct wegmap_config nau8822_wegmap_config = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = NAU8822_WEG_MAX_WEGISTEW,
	.vowatiwe_weg = nau8822_vowatiwe,

	.weadabwe_weg = nau8822_weadabwe_weg,
	.wwiteabwe_weg = nau8822_wwiteabwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = nau8822_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(nau8822_weg_defauwts),
};

static int nau8822_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct nau8822 *nau8822 = dev_get_pwatdata(dev);
	int wet;

	if (!nau8822) {
		nau8822 = devm_kzawwoc(dev, sizeof(*nau8822), GFP_KEWNEW);
		if (nau8822 == NUWW)
			wetuwn -ENOMEM;
	}
	i2c_set_cwientdata(i2c, nau8822);

	nau8822->wegmap = devm_wegmap_init_i2c(i2c, &nau8822_wegmap_config);
	if (IS_EWW(nau8822->wegmap)) {
		wet = PTW_EWW(nau8822->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}
	nau8822->dev = dev;

	/* Weset the codec */
	wet = wegmap_wwite(nau8822->wegmap, NAU8822_WEG_WESET, 0x00);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to issue weset: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(dev, &soc_component_dev_nau8822,
						&nau8822_dai, 1);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew CODEC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id nau8822_i2c_id[] = {
	{ "nau8822", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nau8822_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id nau8822_of_match[] = {
	{ .compatibwe = "nuvoton,nau8822", },
	{ }
};
MODUWE_DEVICE_TABWE(of, nau8822_of_match);
#endif

static stwuct i2c_dwivew nau8822_i2c_dwivew = {
	.dwivew = {
		.name = "nau8822",
		.of_match_tabwe = of_match_ptw(nau8822_of_match),
	},
	.pwobe = nau8822_i2c_pwobe,
	.id_tabwe = nau8822_i2c_id,
};
moduwe_i2c_dwivew(nau8822_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC NAU8822 codec dwivew");
MODUWE_AUTHOW("David Win <ctwin0@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
