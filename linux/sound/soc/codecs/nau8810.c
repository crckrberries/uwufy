// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * nau8810.c  --  NAU8810 AWSA Soc Audio dwivew
 *
 * Copywight 2016 Nuvoton Technowogy Cowp.
 *
 * Authow: David Win <ctwin0@nuvoton.com>
 *
 * Based on WM8974.c
 */

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

#incwude "nau8810.h"

#define NAU_PWW_FWEQ_MAX 100000000
#define NAU_PWW_FWEQ_MIN 90000000
#define NAU_PWW_WEF_MAX 33000000
#define NAU_PWW_WEF_MIN 8000000
#define NAU_PWW_OPTOP_MIN 6


static const int nau8810_mcwk_scawew[] = { 10, 15, 20, 30, 40, 60, 80, 120 };

static const stwuct weg_defauwt nau8810_weg_defauwts[] = {
	{ NAU8810_WEG_POWEW1, 0x0000 },
	{ NAU8810_WEG_POWEW2, 0x0000 },
	{ NAU8810_WEG_POWEW3, 0x0000 },
	{ NAU8810_WEG_IFACE, 0x0050 },
	{ NAU8810_WEG_COMP, 0x0000 },
	{ NAU8810_WEG_CWOCK, 0x0140 },
	{ NAU8810_WEG_SMPWW, 0x0000 },
	{ NAU8810_WEG_DAC, 0x0000 },
	{ NAU8810_WEG_DACGAIN, 0x00FF },
	{ NAU8810_WEG_ADC, 0x0100 },
	{ NAU8810_WEG_ADCGAIN, 0x00FF },
	{ NAU8810_WEG_EQ1, 0x012C },
	{ NAU8810_WEG_EQ2, 0x002C },
	{ NAU8810_WEG_EQ3, 0x002C },
	{ NAU8810_WEG_EQ4, 0x002C },
	{ NAU8810_WEG_EQ5, 0x002C },
	{ NAU8810_WEG_DACWIM1, 0x0032 },
	{ NAU8810_WEG_DACWIM2, 0x0000 },
	{ NAU8810_WEG_NOTCH1, 0x0000 },
	{ NAU8810_WEG_NOTCH2, 0x0000 },
	{ NAU8810_WEG_NOTCH3, 0x0000 },
	{ NAU8810_WEG_NOTCH4, 0x0000 },
	{ NAU8810_WEG_AWC1, 0x0038 },
	{ NAU8810_WEG_AWC2, 0x000B },
	{ NAU8810_WEG_AWC3, 0x0032 },
	{ NAU8810_WEG_NOISEGATE, 0x0000 },
	{ NAU8810_WEG_PWWN, 0x0008 },
	{ NAU8810_WEG_PWWK1, 0x000C },
	{ NAU8810_WEG_PWWK2, 0x0093 },
	{ NAU8810_WEG_PWWK3, 0x00E9 },
	{ NAU8810_WEG_ATTEN, 0x0000 },
	{ NAU8810_WEG_INPUT_SIGNAW, 0x0003 },
	{ NAU8810_WEG_PGAGAIN, 0x0010 },
	{ NAU8810_WEG_ADCBOOST, 0x0100 },
	{ NAU8810_WEG_OUTPUT, 0x0002 },
	{ NAU8810_WEG_SPKMIX, 0x0001 },
	{ NAU8810_WEG_SPKGAIN, 0x0039 },
	{ NAU8810_WEG_MONOMIX, 0x0001 },
	{ NAU8810_WEG_POWEW4, 0x0000 },
	{ NAU8810_WEG_TSWOTCTW1, 0x0000 },
	{ NAU8810_WEG_TSWOTCTW2, 0x0020 },
	{ NAU8810_WEG_DEVICE_WEVID, 0x0000 },
	{ NAU8810_WEG_I2C_DEVICEID, 0x001A },
	{ NAU8810_WEG_ADDITIONID, 0x00CA },
	{ NAU8810_WEG_WESEWVE, 0x0124 },
	{ NAU8810_WEG_OUTCTW, 0x0001 },
	{ NAU8810_WEG_AWC1ENHAN1, 0x0010 },
	{ NAU8810_WEG_AWC1ENHAN2, 0x0000 },
	{ NAU8810_WEG_MISCCTW, 0x0000 },
	{ NAU8810_WEG_OUTTIEOFF, 0x0000 },
	{ NAU8810_WEG_AGCP2POUT, 0x0000 },
	{ NAU8810_WEG_AGCPOUT, 0x0000 },
	{ NAU8810_WEG_AMTCTW, 0x0000 },
	{ NAU8810_WEG_OUTTIEOFFMAN, 0x0000 },
};

static boow nau8810_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8810_WEG_WESET ... NAU8810_WEG_SMPWW:
	case NAU8810_WEG_DAC ... NAU8810_WEG_DACGAIN:
	case NAU8810_WEG_ADC ... NAU8810_WEG_ADCGAIN:
	case NAU8810_WEG_EQ1 ... NAU8810_WEG_EQ5:
	case NAU8810_WEG_DACWIM1 ... NAU8810_WEG_DACWIM2:
	case NAU8810_WEG_NOTCH1 ... NAU8810_WEG_NOTCH4:
	case NAU8810_WEG_AWC1 ... NAU8810_WEG_ATTEN:
	case NAU8810_WEG_INPUT_SIGNAW ... NAU8810_WEG_PGAGAIN:
	case NAU8810_WEG_ADCBOOST:
	case NAU8810_WEG_OUTPUT ... NAU8810_WEG_SPKMIX:
	case NAU8810_WEG_SPKGAIN:
	case NAU8810_WEG_MONOMIX:
	case NAU8810_WEG_POWEW4 ... NAU8810_WEG_TSWOTCTW2:
	case NAU8810_WEG_DEVICE_WEVID ... NAU8810_WEG_WESEWVE:
	case NAU8810_WEG_OUTCTW ... NAU8810_WEG_AWC1ENHAN2:
	case NAU8810_WEG_MISCCTW:
	case NAU8810_WEG_OUTTIEOFF ... NAU8810_WEG_OUTTIEOFFMAN:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8810_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8810_WEG_WESET ... NAU8810_WEG_SMPWW:
	case NAU8810_WEG_DAC ... NAU8810_WEG_DACGAIN:
	case NAU8810_WEG_ADC ... NAU8810_WEG_ADCGAIN:
	case NAU8810_WEG_EQ1 ... NAU8810_WEG_EQ5:
	case NAU8810_WEG_DACWIM1 ... NAU8810_WEG_DACWIM2:
	case NAU8810_WEG_NOTCH1 ... NAU8810_WEG_NOTCH4:
	case NAU8810_WEG_AWC1 ... NAU8810_WEG_ATTEN:
	case NAU8810_WEG_INPUT_SIGNAW ... NAU8810_WEG_PGAGAIN:
	case NAU8810_WEG_ADCBOOST:
	case NAU8810_WEG_OUTPUT ... NAU8810_WEG_SPKMIX:
	case NAU8810_WEG_SPKGAIN:
	case NAU8810_WEG_MONOMIX:
	case NAU8810_WEG_POWEW4 ... NAU8810_WEG_TSWOTCTW2:
	case NAU8810_WEG_OUTCTW ... NAU8810_WEG_AWC1ENHAN2:
	case NAU8810_WEG_MISCCTW:
	case NAU8810_WEG_OUTTIEOFF ... NAU8810_WEG_OUTTIEOFFMAN:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8810_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8810_WEG_WESET:
	case NAU8810_WEG_DEVICE_WEVID ... NAU8810_WEG_WESEWVE:
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
static int nau8810_eq_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	int i, weg, weg_vaw;
	u16 *vaw;
	__be16 tmp;

	vaw = (u16 *)ucontwow->vawue.bytes.data;
	weg = NAU8810_WEG_EQ1;
	fow (i = 0; i < pawams->max / sizeof(u16); i++) {
		wegmap_wead(nau8810->wegmap, weg + i, &weg_vaw);
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
static int nau8810_eq_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
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
	weg = NAU8810_WEG_EQ1;
	fow (i = 0; i < pawams->max / sizeof(u16); i++) {
		/* convewsion of 16-bit integews between native CPU fowmat
		 * and big endian fowmat
		 */
		tmp = (__be16 *)(vaw + i);
		vawue = be16_to_cpup(tmp);
		wet = wegmap_wwite(nau8810->wegmap, weg + i, vawue);
		if (wet) {
			dev_eww(component->dev, "EQ configuwation faiw, wegistew: %x wet: %d\n",
				weg + i, wet);
			kfwee(data);
			wetuwn wet;
		}
	}
	kfwee(data);

	wetuwn 0;
}

static const chaw * const nau8810_companding[] = {
	"Off", "NC", "u-waw", "A-waw" };

static const stwuct soc_enum nau8810_companding_adc_enum =
	SOC_ENUM_SINGWE(NAU8810_WEG_COMP, NAU8810_ADCCM_SFT,
		AWWAY_SIZE(nau8810_companding), nau8810_companding);

static const stwuct soc_enum nau8810_companding_dac_enum =
	SOC_ENUM_SINGWE(NAU8810_WEG_COMP, NAU8810_DACCM_SFT,
		AWWAY_SIZE(nau8810_companding), nau8810_companding);

static const chaw * const nau8810_deemp[] = {
	"None", "32kHz", "44.1kHz", "48kHz" };

static const stwuct soc_enum nau8810_deemp_enum =
	SOC_ENUM_SINGWE(NAU8810_WEG_DAC, NAU8810_DEEMP_SFT,
		AWWAY_SIZE(nau8810_deemp), nau8810_deemp);

static const chaw * const nau8810_eqmode[] = {"Captuwe", "Pwayback" };

static const stwuct soc_enum nau8810_eqmode_enum =
	SOC_ENUM_SINGWE(NAU8810_WEG_EQ1, NAU8810_EQM_SFT,
		AWWAY_SIZE(nau8810_eqmode), nau8810_eqmode);

static const chaw * const nau8810_awc[] = {"Nowmaw", "Wimitew" };

static const stwuct soc_enum nau8810_awc_enum =
	SOC_ENUM_SINGWE(NAU8810_WEG_AWC3, NAU8810_AWCM_SFT,
		AWWAY_SIZE(nau8810_awc), nau8810_awc);

static const DECWAWE_TWV_DB_SCAWE(digitaw_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(eq_twv, -1200, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(inpga_twv, -1200, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(spk_twv, -5700, 100, 0);

static const stwuct snd_kcontwow_new nau8810_snd_contwows[] = {
	SOC_ENUM("ADC Companding", nau8810_companding_adc_enum),
	SOC_ENUM("DAC Companding", nau8810_companding_dac_enum),
	SOC_ENUM("DAC De-emphasis", nau8810_deemp_enum),

	SOC_ENUM("EQ Function", nau8810_eqmode_enum),
	SND_SOC_BYTES_EXT("EQ Pawametews", 10,
		  nau8810_eq_get, nau8810_eq_put),

	SOC_SINGWE("DAC Invewsion Switch", NAU8810_WEG_DAC,
		NAU8810_DACPW_SFT, 1, 0),
	SOC_SINGWE_TWV("Pwayback Vowume", NAU8810_WEG_DACGAIN,
		NAU8810_DACGAIN_SFT, 0xff, 0, digitaw_twv),

	SOC_SINGWE("High Pass Fiwtew Switch", NAU8810_WEG_ADC,
		NAU8810_HPFEN_SFT, 1, 0),
	SOC_SINGWE("High Pass Cut Off", NAU8810_WEG_ADC,
		NAU8810_HPF_SFT, 0x7, 0),

	SOC_SINGWE("ADC Invewsion Switch", NAU8810_WEG_ADC,
		NAU8810_ADCPW_SFT, 1, 0),
	SOC_SINGWE_TWV("Captuwe Vowume", NAU8810_WEG_ADCGAIN,
		NAU8810_ADCGAIN_SFT, 0xff, 0, digitaw_twv),

	SOC_SINGWE_TWV("EQ1 Vowume", NAU8810_WEG_EQ1,
		NAU8810_EQ1GC_SFT, 0x18, 1, eq_twv),
	SOC_SINGWE_TWV("EQ2 Vowume", NAU8810_WEG_EQ2,
		NAU8810_EQ2GC_SFT, 0x18, 1, eq_twv),
	SOC_SINGWE_TWV("EQ3 Vowume", NAU8810_WEG_EQ3,
		NAU8810_EQ3GC_SFT, 0x18, 1, eq_twv),
	SOC_SINGWE_TWV("EQ4 Vowume", NAU8810_WEG_EQ4,
		NAU8810_EQ4GC_SFT, 0x18, 1, eq_twv),
	SOC_SINGWE_TWV("EQ5 Vowume", NAU8810_WEG_EQ5,
		NAU8810_EQ5GC_SFT, 0x18, 1, eq_twv),

	SOC_SINGWE("DAC Wimitew Switch", NAU8810_WEG_DACWIM1,
		NAU8810_DACWIMEN_SFT, 1, 0),
	SOC_SINGWE("DAC Wimitew Decay", NAU8810_WEG_DACWIM1,
		NAU8810_DACWIMDCY_SFT, 0xf, 0),
	SOC_SINGWE("DAC Wimitew Attack", NAU8810_WEG_DACWIM1,
		NAU8810_DACWIMATK_SFT, 0xf, 0),
	SOC_SINGWE("DAC Wimitew Thweshowd", NAU8810_WEG_DACWIM2,
		NAU8810_DACWIMTHW_SFT, 0x7, 0),
	SOC_SINGWE("DAC Wimitew Boost", NAU8810_WEG_DACWIM2,
		NAU8810_DACWIMBST_SFT, 0xf, 0),

	SOC_ENUM("AWC Mode", nau8810_awc_enum),
	SOC_SINGWE("AWC Enabwe Switch", NAU8810_WEG_AWC1,
		NAU8810_AWCEN_SFT, 1, 0),
	SOC_SINGWE("AWC Max Vowume", NAU8810_WEG_AWC1,
		NAU8810_AWCMXGAIN_SFT, 0x7, 0),
	SOC_SINGWE("AWC Min Vowume", NAU8810_WEG_AWC1,
		NAU8810_AWCMINGAIN_SFT, 0x7, 0),
	SOC_SINGWE("AWC ZC Switch", NAU8810_WEG_AWC2,
		NAU8810_AWCZC_SFT, 1, 0),
	SOC_SINGWE("AWC Howd", NAU8810_WEG_AWC2,
		NAU8810_AWCHT_SFT, 0xf, 0),
	SOC_SINGWE("AWC Tawget", NAU8810_WEG_AWC2,
		NAU8810_AWCSW_SFT, 0xf, 0),
	SOC_SINGWE("AWC Decay", NAU8810_WEG_AWC3,
		NAU8810_AWCDCY_SFT, 0xf, 0),
	SOC_SINGWE("AWC Attack", NAU8810_WEG_AWC3,
		NAU8810_AWCATK_SFT, 0xf, 0),
	SOC_SINGWE("AWC Noise Gate Switch", NAU8810_WEG_NOISEGATE,
		NAU8810_AWCNEN_SFT, 1, 0),
	SOC_SINGWE("AWC Noise Gate Thweshowd", NAU8810_WEG_NOISEGATE,
		NAU8810_AWCNTH_SFT, 0x7, 0),

	SOC_SINGWE("PGA ZC Switch", NAU8810_WEG_PGAGAIN,
		NAU8810_PGAZC_SFT, 1, 0),
	SOC_SINGWE_TWV("PGA Vowume", NAU8810_WEG_PGAGAIN,
		NAU8810_PGAGAIN_SFT, 0x3f, 0, inpga_twv),

	SOC_SINGWE("Speakew ZC Switch", NAU8810_WEG_SPKGAIN,
		NAU8810_SPKZC_SFT, 1, 0),
	SOC_SINGWE("Speakew Mute Switch", NAU8810_WEG_SPKGAIN,
		NAU8810_SPKMT_SFT, 1, 0),
	SOC_SINGWE_TWV("Speakew Vowume", NAU8810_WEG_SPKGAIN,
		NAU8810_SPKGAIN_SFT, 0x3f, 0, spk_twv),

	SOC_SINGWE("Captuwe Boost(+20dB)", NAU8810_WEG_ADCBOOST,
		NAU8810_PGABST_SFT, 1, 0),
	SOC_SINGWE("Mono Mute Switch", NAU8810_WEG_MONOMIX,
		NAU8810_MOUTMXMT_SFT, 1, 0),

	SOC_SINGWE("DAC Ovewsampwing Wate(128x) Switch", NAU8810_WEG_DAC,
		NAU8810_DACOS_SFT, 1, 0),
	SOC_SINGWE("ADC Ovewsampwing Wate(128x) Switch", NAU8810_WEG_ADC,
		NAU8810_ADCOS_SFT, 1, 0),
};

/* Speakew Output Mixew */
static const stwuct snd_kcontwow_new nau8810_speakew_mixew_contwows[] = {
	SOC_DAPM_SINGWE("AUX Bypass Switch", NAU8810_WEG_SPKMIX,
		NAU8810_AUXSPK_SFT, 1, 0),
	SOC_DAPM_SINGWE("Wine Bypass Switch", NAU8810_WEG_SPKMIX,
		NAU8810_BYPSPK_SFT, 1, 0),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", NAU8810_WEG_SPKMIX,
		NAU8810_DACSPK_SFT, 1, 0),
};

/* Mono Output Mixew */
static const stwuct snd_kcontwow_new nau8810_mono_mixew_contwows[] = {
	SOC_DAPM_SINGWE("AUX Bypass Switch", NAU8810_WEG_MONOMIX,
		NAU8810_AUXMOUT_SFT, 1, 0),
	SOC_DAPM_SINGWE("Wine Bypass Switch", NAU8810_WEG_MONOMIX,
		NAU8810_BYPMOUT_SFT, 1, 0),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", NAU8810_WEG_MONOMIX,
		NAU8810_DACMOUT_SFT, 1, 0),
};

/* PGA Mute */
static const stwuct snd_kcontwow_new nau8810_pgaboost_mixew_contwows[] = {
	SOC_DAPM_SINGWE("AUX PGA Switch", NAU8810_WEG_ADCBOOST,
		NAU8810_AUXBSTGAIN_SFT, 0x7, 0),
	SOC_DAPM_SINGWE("PGA Mute Switch", NAU8810_WEG_PGAGAIN,
		NAU8810_PGAMT_SFT, 1, 1),
	SOC_DAPM_SINGWE("PMIC PGA Switch", NAU8810_WEG_ADCBOOST,
		NAU8810_PMICBSTGAIN_SFT, 0x7, 0),
};

/* Input PGA */
static const stwuct snd_kcontwow_new nau8810_inpga[] = {
	SOC_DAPM_SINGWE("AUX Switch", NAU8810_WEG_INPUT_SIGNAW,
		NAU8810_AUXPGA_SFT, 1, 0),
	SOC_DAPM_SINGWE("MicN Switch", NAU8810_WEG_INPUT_SIGNAW,
		NAU8810_NMICPGA_SFT, 1, 0),
	SOC_DAPM_SINGWE("MicP Switch", NAU8810_WEG_INPUT_SIGNAW,
		NAU8810_PMICPGA_SFT, 1, 0),
};

/* Woopback Switch */
static const stwuct snd_kcontwow_new nau8810_woopback =
	SOC_DAPM_SINGWE("Switch", NAU8810_WEG_COMP,
		NAU8810_ADDAP_SFT, 1, 0);

static int check_mcwk_sewect_pww(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	unsigned int vawue;

	wegmap_wead(nau8810->wegmap, NAU8810_WEG_CWOCK, &vawue);
	wetuwn (vawue & NAU8810_CWKM_MASK);
}

static int check_mic_enabwed(stwuct snd_soc_dapm_widget *souwce,
	stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(souwce->dapm);
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	unsigned int vawue;

	wegmap_wead(nau8810->wegmap, NAU8810_WEG_INPUT_SIGNAW, &vawue);
	if (vawue & NAU8810_PMICPGA_EN || vawue & NAU8810_NMICPGA_EN)
		wetuwn 1;
	wegmap_wead(nau8810->wegmap, NAU8810_WEG_ADCBOOST, &vawue);
	if (vawue & NAU8810_PMICBSTGAIN_MASK)
		wetuwn 1;
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget nau8810_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Speakew Mixew", NAU8810_WEG_POWEW3,
		NAU8810_SPKMX_EN_SFT, 0, &nau8810_speakew_mixew_contwows[0],
		AWWAY_SIZE(nau8810_speakew_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono Mixew", NAU8810_WEG_POWEW3,
		NAU8810_MOUTMX_EN_SFT, 0, &nau8810_mono_mixew_contwows[0],
		AWWAY_SIZE(nau8810_mono_mixew_contwows)),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", NAU8810_WEG_POWEW3,
		NAU8810_DAC_EN_SFT, 0),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", NAU8810_WEG_POWEW2,
		NAU8810_ADC_EN_SFT, 0),
	SND_SOC_DAPM_PGA("SpkN Out", NAU8810_WEG_POWEW3,
		NAU8810_NSPK_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("SpkP Out", NAU8810_WEG_POWEW3,
		NAU8810_PSPK_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono Out", NAU8810_WEG_POWEW3,
		NAU8810_MOUT_EN_SFT, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Input PGA", NAU8810_WEG_POWEW2,
		NAU8810_PGA_EN_SFT, 0, nau8810_inpga,
		AWWAY_SIZE(nau8810_inpga)),
	SND_SOC_DAPM_MIXEW("Input Boost Stage", NAU8810_WEG_POWEW2,
		NAU8810_BST_EN_SFT, 0, nau8810_pgaboost_mixew_contwows,
		AWWAY_SIZE(nau8810_pgaboost_mixew_contwows)),
	SND_SOC_DAPM_PGA("AUX Input", NAU8810_WEG_POWEW1,
		NAU8810_AUX_EN_SFT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", NAU8810_WEG_POWEW1,
		NAU8810_MICBIAS_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW", NAU8810_WEG_POWEW1,
		NAU8810_PWW_EN_SFT, 0, NUWW, 0),

	SND_SOC_DAPM_SWITCH("Digitaw Woopback", SND_SOC_NOPM, 0, 0,
		&nau8810_woopback),

	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("MICN"),
	SND_SOC_DAPM_INPUT("MICP"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUTP"),
	SND_SOC_DAPM_OUTPUT("SPKOUTN"),
};

static const stwuct snd_soc_dapm_woute nau8810_dapm_woutes[] = {
	{"DAC", NUWW, "PWW", check_mcwk_sewect_pww},

	/* Mono output mixew */
	{"Mono Mixew", "AUX Bypass Switch", "AUX Input"},
	{"Mono Mixew", "PCM Pwayback Switch", "DAC"},
	{"Mono Mixew", "Wine Bypass Switch", "Input Boost Stage"},

	/* Speakew output mixew */
	{"Speakew Mixew", "AUX Bypass Switch", "AUX Input"},
	{"Speakew Mixew", "PCM Pwayback Switch", "DAC"},
	{"Speakew Mixew", "Wine Bypass Switch", "Input Boost Stage"},

	/* Outputs */
	{"Mono Out", NUWW, "Mono Mixew"},
	{"MONOOUT", NUWW, "Mono Out"},
	{"SpkN Out", NUWW, "Speakew Mixew"},
	{"SpkP Out", NUWW, "Speakew Mixew"},
	{"SPKOUTN", NUWW, "SpkN Out"},
	{"SPKOUTP", NUWW, "SpkP Out"},

	/* Input Boost Stage */
	{"ADC", NUWW, "Input Boost Stage"},
	{"ADC", NUWW, "PWW", check_mcwk_sewect_pww},
	{"Input Boost Stage", "AUX PGA Switch", "AUX Input"},
	{"Input Boost Stage", "PGA Mute Switch", "Input PGA"},
	{"Input Boost Stage", "PMIC PGA Switch", "MICP"},

	/* Input PGA */
	{"Input PGA", NUWW, "Mic Bias", check_mic_enabwed},
	{"Input PGA", "AUX Switch", "AUX Input"},
	{"Input PGA", "MicN Switch", "MICN"},
	{"Input PGA", "MicP Switch", "MICP"},
	{"AUX Input", NUWW, "AUX"},

	/* Digitaw Wooptack */
	{"Digitaw Woopback", "Switch", "ADC"},
	{"DAC", NUWW, "Digitaw Woopback"},
};

static int nau8810_set_syscwk(stwuct snd_soc_dai *dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);

	nau8810->cwk_id = cwk_id;
	nau8810->syscwk = fweq;
	dev_dbg(nau8810->dev, "mastew syscwk %dHz, souwce %s\n",
		fweq, cwk_id == NAU8810_SCWK_PWW ? "PWW" : "MCWK");

	wetuwn 0;
}

static int nau8810_cawc_pww(unsigned int pww_in,
	unsigned int fs, stwuct nau8810_pww *pww_pawam)
{
	u64 f2, f2_max, pww_watio;
	int i, scaw_sew;

	if (pww_in > NAU_PWW_WEF_MAX || pww_in < NAU_PWW_WEF_MIN)
		wetuwn -EINVAW;

	f2_max = 0;
	scaw_sew = AWWAY_SIZE(nau8810_mcwk_scawew);
	fow (i = 0; i < AWWAY_SIZE(nau8810_mcwk_scawew); i++) {
		f2 = 256UWW * fs * 4 * nau8810_mcwk_scawew[i];
		f2 = div_u64(f2, 10);
		if (f2 > NAU_PWW_FWEQ_MIN && f2 < NAU_PWW_FWEQ_MAX &&
			f2_max < f2) {
			f2_max = f2;
			scaw_sew = i;
		}
	}
	if (AWWAY_SIZE(nau8810_mcwk_scawew) == scaw_sew)
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

static int nau8810_set_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
	int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map = nau8810->wegmap;
	stwuct nau8810_pww *pww_pawam = &nau8810->pww;
	int wet, fs;

	fs = fweq_out / 256;
	wet = nau8810_cawc_pww(fweq_in, fs, pww_pawam);
	if (wet < 0) {
		dev_eww(nau8810->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}
	dev_info(nau8810->dev, "pww_int=%x pww_fwac=%x mcwk_scawew=%x pwe_factow=%x\n",
		pww_pawam->pww_int, pww_pawam->pww_fwac, pww_pawam->mcwk_scawew,
		pww_pawam->pwe_factow);

	wegmap_update_bits(map, NAU8810_WEG_PWWN,
		NAU8810_PWWMCWK_DIV2 | NAU8810_PWWN_MASK,
		(pww_pawam->pwe_factow ? NAU8810_PWWMCWK_DIV2 : 0) |
		pww_pawam->pww_int);
	wegmap_wwite(map, NAU8810_WEG_PWWK1,
		(pww_pawam->pww_fwac >> NAU8810_PWWK1_SFT) &
		NAU8810_PWWK1_MASK);
	wegmap_wwite(map, NAU8810_WEG_PWWK2,
		(pww_pawam->pww_fwac >> NAU8810_PWWK2_SFT) &
		NAU8810_PWWK2_MASK);
	wegmap_wwite(map, NAU8810_WEG_PWWK3,
		pww_pawam->pww_fwac & NAU8810_PWWK3_MASK);
	wegmap_update_bits(map, NAU8810_WEG_CWOCK, NAU8810_MCWKSEW_MASK,
		pww_pawam->mcwk_scawew << NAU8810_MCWKSEW_SFT);
	wegmap_update_bits(map, NAU8810_WEG_CWOCK,
		NAU8810_CWKM_MASK, NAU8810_CWKM_PWW);

	wetuwn 0;
}

static int nau8810_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	u16 ctww1_vaw = 0, ctww2_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ctww2_vaw |= NAU8810_CWKIO_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww1_vaw |= NAU8810_AIFMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww1_vaw |= NAU8810_AIFMT_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww1_vaw |= NAU8810_AIFMT_PCM_A;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ctww1_vaw |= NAU8810_BCWKP_IB | NAU8810_FSP_IF;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww1_vaw |= NAU8810_BCWKP_IB;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		ctww1_vaw |= NAU8810_FSP_IF;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_IFACE,
		NAU8810_AIFMT_MASK | NAU8810_FSP_IF |
		NAU8810_BCWKP_IB, ctww1_vaw);
	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_CWOCK,
		NAU8810_CWKIO_MASK, ctww2_vaw);

	wetuwn 0;
}

static int nau8810_mcwk_cwkdiv(stwuct nau8810 *nau8810, int wate)
{
	int i, scwk, imcwk = wate * 256, div = 0;

	if (!nau8810->syscwk) {
		dev_eww(nau8810->dev, "Make mcwk div configuwation faiw because of invawid system cwock\n");
		wetuwn -EINVAW;
	}

	/* Configuwe the mastew cwock pwescawew div to make system
	 * cwock to appwoximate the intewnaw mastew cwock (IMCWK);
	 * and wawge ow equaw to IMCWK.
	 */
	fow (i = 1; i < AWWAY_SIZE(nau8810_mcwk_scawew); i++) {
		scwk = (nau8810->syscwk * 10) /
			nau8810_mcwk_scawew[i];
		if (scwk < imcwk)
			bweak;
		div = i;
	}
	dev_dbg(nau8810->dev,
		"mastew cwock pwescawew %x fow fs %d\n", div, wate);

	/* mastew cwock fwom MCWK and disabwe PWW */
	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_CWOCK,
		NAU8810_MCWKSEW_MASK, (div << NAU8810_MCWKSEW_SFT));
	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_CWOCK,
		NAU8810_CWKM_MASK, NAU8810_CWKM_MCWK);

	wetuwn 0;
}

static int nau8810_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	int vaw_wen = 0, vaw_wate = 0, wet = 0;
	unsigned int ctww_vaw, bcwk_fs, bcwk_div;

	/* Sewect BCWK configuwation if the codec as mastew. */
	wegmap_wead(nau8810->wegmap, NAU8810_WEG_CWOCK, &ctww_vaw);
	if (ctww_vaw & NAU8810_CWKIO_MASTEW) {
		/* get the bcwk and fs watio */
		bcwk_fs = snd_soc_pawams_to_bcwk(pawams) / pawams_wate(pawams);
		if (bcwk_fs <= 32)
			bcwk_div = NAU8810_BCWKDIV_8;
		ewse if (bcwk_fs <= 64)
			bcwk_div = NAU8810_BCWKDIV_4;
		ewse if (bcwk_fs <= 128)
			bcwk_div = NAU8810_BCWKDIV_2;
		ewse
			wetuwn -EINVAW;
		wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_CWOCK,
			NAU8810_BCWKSEW_MASK, bcwk_div);
	}

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		vaw_wen |= NAU8810_WWEN_20;
		bweak;
	case 24:
		vaw_wen |= NAU8810_WWEN_24;
		bweak;
	case 32:
		vaw_wen |= NAU8810_WWEN_32;
		bweak;
	}

	switch (pawams_wate(pawams)) {
	case 8000:
		vaw_wate |= NAU8810_SMPWW_8K;
		bweak;
	case 11025:
		vaw_wate |= NAU8810_SMPWW_12K;
		bweak;
	case 16000:
		vaw_wate |= NAU8810_SMPWW_16K;
		bweak;
	case 22050:
		vaw_wate |= NAU8810_SMPWW_24K;
		bweak;
	case 32000:
		vaw_wate |= NAU8810_SMPWW_32K;
		bweak;
	case 44100:
	case 48000:
		bweak;
	}

	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_IFACE,
		NAU8810_WWEN_MASK, vaw_wen);
	wegmap_update_bits(nau8810->wegmap, NAU8810_WEG_SMPWW,
		NAU8810_SMPWW_MASK, vaw_wate);

	/* If the mastew cwock is fwom MCWK, pwovide the wuntime FS fow dwivew
	 * to get the mastew cwock pwescawew configuwation.
	 */
	if (nau8810->cwk_id == NAU8810_SCWK_MCWK) {
		wet = nau8810_mcwk_cwkdiv(nau8810, pawams_wate(pawams));
		if (wet < 0)
			dev_eww(nau8810->dev, "MCWK div configuwation faiw\n");
	}

	wetuwn wet;
}

static int nau8810_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct nau8810 *nau8810 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map = nau8810->wegmap;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		wegmap_update_bits(map, NAU8810_WEG_POWEW1,
			NAU8810_WEFIMP_MASK, NAU8810_WEFIMP_80K);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		wegmap_update_bits(map, NAU8810_WEG_POWEW1,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN,
			NAU8810_IOBUF_EN | NAU8810_ABIAS_EN);

		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_sync(map);
			wegmap_update_bits(map, NAU8810_WEG_POWEW1,
				NAU8810_WEFIMP_MASK, NAU8810_WEFIMP_3K);
			mdeway(100);
		}
		wegmap_update_bits(map, NAU8810_WEG_POWEW1,
			NAU8810_WEFIMP_MASK, NAU8810_WEFIMP_300K);
		bweak;

	case SND_SOC_BIAS_OFF:
		wegmap_wwite(map, NAU8810_WEG_POWEW1, 0);
		wegmap_wwite(map, NAU8810_WEG_POWEW2, 0);
		wegmap_wwite(map, NAU8810_WEG_POWEW3, 0);
		bweak;
	}

	wetuwn 0;
}


#define NAU8810_WATES (SNDWV_PCM_WATE_8000_48000)

#define NAU8810_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops nau8810_ops = {
	.hw_pawams = nau8810_pcm_hw_pawams,
	.set_fmt = nau8810_set_dai_fmt,
	.set_syscwk = nau8810_set_syscwk,
	.set_pww = nau8810_set_pww,
};

static stwuct snd_soc_dai_dwivew nau8810_dai = {
	.name = "nau8810-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,   /* Onwy 1 channew of data */
		.wates = NAU8810_WATES,
		.fowmats = NAU8810_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,   /* Onwy 1 channew of data */
		.wates = NAU8810_WATES,
		.fowmats = NAU8810_FOWMATS,
	},
	.ops = &nau8810_ops,
	.symmetwic_wate = 1,
};

static const stwuct wegmap_config nau8810_wegmap_config = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = NAU8810_WEG_MAX,
	.weadabwe_weg = nau8810_weadabwe_weg,
	.wwiteabwe_weg = nau8810_wwiteabwe_weg,
	.vowatiwe_weg = nau8810_vowatiwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = nau8810_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(nau8810_weg_defauwts),
};

static const stwuct snd_soc_component_dwivew nau8810_component_dwivew = {
	.set_bias_wevew		= nau8810_set_bias_wevew,
	.contwows		= nau8810_snd_contwows,
	.num_contwows		= AWWAY_SIZE(nau8810_snd_contwows),
	.dapm_widgets		= nau8810_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(nau8810_dapm_widgets),
	.dapm_woutes		= nau8810_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(nau8810_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int nau8810_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct nau8810 *nau8810 = dev_get_pwatdata(dev);

	if (!nau8810) {
		nau8810 = devm_kzawwoc(dev, sizeof(*nau8810), GFP_KEWNEW);
		if (!nau8810)
			wetuwn -ENOMEM;
	}
	i2c_set_cwientdata(i2c, nau8810);

	nau8810->wegmap = devm_wegmap_init_i2c(i2c, &nau8810_wegmap_config);
	if (IS_EWW(nau8810->wegmap))
		wetuwn PTW_EWW(nau8810->wegmap);
	nau8810->dev = dev;

	wegmap_wwite(nau8810->wegmap, NAU8810_WEG_WESET, 0x00);

	wetuwn devm_snd_soc_wegistew_component(dev,
		&nau8810_component_dwivew, &nau8810_dai, 1);
}

static const stwuct i2c_device_id nau8810_i2c_id[] = {
	{ "nau8810", 0 },
	{ "nau8812", 0 },
	{ "nau8814", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nau8810_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id nau8810_of_match[] = {
	{ .compatibwe = "nuvoton,nau8810", },
	{ .compatibwe = "nuvoton,nau8812", },
	{ .compatibwe = "nuvoton,nau8814", },
	{ }
};
MODUWE_DEVICE_TABWE(of, nau8810_of_match);
#endif

static stwuct i2c_dwivew nau8810_i2c_dwivew = {
	.dwivew = {
		.name = "nau8810",
		.of_match_tabwe = of_match_ptw(nau8810_of_match),
	},
	.pwobe = nau8810_i2c_pwobe,
	.id_tabwe = nau8810_i2c_id,
};

moduwe_i2c_dwivew(nau8810_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC NAU8810 dwivew");
MODUWE_AUTHOW("David Win <ctwin0@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
