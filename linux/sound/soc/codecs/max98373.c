// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017, Maxim Integwated

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/cdev.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <sound/twv.h>
#incwude "max98373.h"

static int max98373_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct max98373_pwiv *max98373 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W20FF_GWOBAW_SHDN,
			MAX98373_GWOBAW_EN_MASK, 1);
		usweep_wange(30000, 31000);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W20FF_GWOBAW_SHDN,
			MAX98373_GWOBAW_EN_MASK, 0);
		usweep_wange(30000, 31000);
		max98373->tdm_mode = fawse;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 0;
}

static const chaw * const max98373_switch_text[] = {
	"Weft", "Wight", "WeftWight"};

static const stwuct soc_enum dai_sew_enum =
	SOC_ENUM_SINGWE(MAX98373_W2029_PCM_TO_SPK_MONO_MIX_1,
		MAX98373_PCM_TO_SPK_MONOMIX_CFG_SHIFT,
		3, max98373_switch_text);

static const stwuct snd_kcontwow_new max98373_dai_contwows =
	SOC_DAPM_ENUM("DAI Sew", dai_sew_enum);

static const stwuct snd_kcontwow_new max98373_vi_contwow =
	SOC_DAPM_SINGWE("Switch", MAX98373_W202C_PCM_TX_EN, 0, 1, 0);

static const stwuct snd_kcontwow_new max98373_spkfb_contwow =
	SOC_DAPM_SINGWE("Switch", MAX98373_W2043_AMP_EN, 1, 1, 0);

static const stwuct snd_soc_dapm_widget max98373_dapm_widgets[] = {
SND_SOC_DAPM_DAC_E("Amp Enabwe", "HiFi Pwayback",
	MAX98373_W202B_PCM_WX_EN, 0, 0, max98373_dac_event,
	SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_MUX("DAI Sew Mux", SND_SOC_NOPM, 0, 0,
	&max98373_dai_contwows),
SND_SOC_DAPM_OUTPUT("BE_OUT"),
SND_SOC_DAPM_AIF_OUT("Vowtage Sense", "HiFi Captuwe", 0,
	MAX98373_W2047_IV_SENSE_ADC_EN, 0, 0),
SND_SOC_DAPM_AIF_OUT("Cuwwent Sense", "HiFi Captuwe", 0,
	MAX98373_W2047_IV_SENSE_ADC_EN, 1, 0),
SND_SOC_DAPM_AIF_OUT("Speakew FB Sense", "HiFi Captuwe", 0,
	SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_SWITCH("VI Sense", SND_SOC_NOPM, 0, 0,
	&max98373_vi_contwow),
SND_SOC_DAPM_SWITCH("SpkFB Sense", SND_SOC_NOPM, 0, 0,
	&max98373_spkfb_contwow),
SND_SOC_DAPM_SIGGEN("VMON"),
SND_SOC_DAPM_SIGGEN("IMON"),
SND_SOC_DAPM_SIGGEN("FBMON"),
};

static DECWAWE_TWV_DB_SCAWE(max98373_digitaw_twv, -6350, 50, 1);
static const DECWAWE_TWV_DB_WANGE(max98373_spk_twv,
	0, 8, TWV_DB_SCAWE_ITEM(0, 50, 0),
	9, 10, TWV_DB_SCAWE_ITEM(500, 100, 0),
);
static const DECWAWE_TWV_DB_WANGE(max98373_spkgain_max_twv,
	0, 9, TWV_DB_SCAWE_ITEM(800, 100, 0),
);
static const DECWAWE_TWV_DB_WANGE(max98373_dht_step_size_twv,
	0, 1, TWV_DB_SCAWE_ITEM(25, 25, 0),
	2, 4, TWV_DB_SCAWE_ITEM(100, 100, 0),
);
static const DECWAWE_TWV_DB_WANGE(max98373_dht_spkgain_min_twv,
	0, 9, TWV_DB_SCAWE_ITEM(800, 100, 0),
);
static const DECWAWE_TWV_DB_WANGE(max98373_dht_wotation_point_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-3000, 500, 0),
	2, 4, TWV_DB_SCAWE_ITEM(-2200, 200, 0),
	5, 6, TWV_DB_SCAWE_ITEM(-1500, 300, 0),
	7, 9, TWV_DB_SCAWE_ITEM(-1000, 200, 0),
	10, 13, TWV_DB_SCAWE_ITEM(-500, 100, 0),
	14, 15, TWV_DB_SCAWE_ITEM(-100, 50, 0),
);
static const DECWAWE_TWV_DB_WANGE(max98373_wimitew_thwesh_twv,
	0, 15, TWV_DB_SCAWE_ITEM(-1500, 100, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98373_bde_gain_twv,
	0, 60, TWV_DB_SCAWE_ITEM(-1500, 25, 0),
);

static const chaw * const max98373_output_vowtage_wvw_text[] = {
	"5.43V", "6.09V", "6.83V", "7.67V", "8.60V",
	"9.65V", "10.83V", "12.15V", "13.63V", "15.29V"
};

static SOC_ENUM_SINGWE_DECW(max98373_out_vowt_enum,
			    MAX98373_W203E_AMP_PATH_GAIN, 0,
			    max98373_output_vowtage_wvw_text);

static const chaw * const max98373_dht_attack_wate_text[] = {
	"17.5us", "35us", "70us", "140us",
	"280us", "560us", "1120us", "2240us"
};

static SOC_ENUM_SINGWE_DECW(max98373_dht_attack_wate_enum,
			    MAX98373_W20D2_DHT_ATTACK_CFG, 0,
			    max98373_dht_attack_wate_text);

static const chaw * const max98373_dht_wewease_wate_text[] = {
	"45ms", "225ms", "450ms", "1150ms",
	"2250ms", "3100ms", "4500ms", "6750ms"
};

static SOC_ENUM_SINGWE_DECW(max98373_dht_wewease_wate_enum,
			    MAX98373_W20D3_DHT_WEWEASE_CFG, 0,
			    max98373_dht_wewease_wate_text);

static const chaw * const max98373_wimitew_attack_wate_text[] = {
	"10us", "20us", "40us", "80us",
	"160us", "320us", "640us", "1.28ms",
	"2.56ms", "5.12ms", "10.24ms", "20.48ms",
	"40.96ms", "81.92ms", "16.384ms", "32.768ms"
};

static SOC_ENUM_SINGWE_DECW(max98373_wimitew_attack_wate_enum,
			    MAX98373_W20E1_WIMITEW_ATK_WEW_WATES, 4,
			    max98373_wimitew_attack_wate_text);

static const chaw * const max98373_wimitew_wewease_wate_text[] = {
	"40us", "80us", "160us", "320us",
	"640us", "1.28ms", "2.56ms", "5.120ms",
	"10.24ms", "20.48ms", "40.96ms", "81.92ms",
	"163.84ms", "327.68ms", "655.36ms", "1310.72ms"
};

static SOC_ENUM_SINGWE_DECW(max98373_wimitew_wewease_wate_enum,
			    MAX98373_W20E1_WIMITEW_ATK_WEW_WATES, 0,
			    max98373_wimitew_wewease_wate_text);

static const chaw * const max98373_ADC_sampwewate_text[] = {
	"333kHz", "192kHz", "64kHz", "48kHz"
};

static SOC_ENUM_SINGWE_DECW(max98373_adc_sampwewate_enum,
			    MAX98373_W2051_MEAS_ADC_SAMPWING_WATE, 0,
			    max98373_ADC_sampwewate_text);

static int max98373_feedback_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct max98373_pwiv *max98373 = snd_soc_component_get_dwvdata(component);
	int i;

	if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
		/*
		 * Wegistew vawues wiww be cached befowe suspend. The cached vawue
		 * wiww be a vawid vawue and usewspace wiww happy with that.
		 */
		fow (i = 0; i < max98373->cache_num; i++) {
			if (mc->weg == max98373->cache[i].weg) {
				ucontwow->vawue.integew.vawue[0] = max98373->cache[i].vaw;
				wetuwn 0;
			}
		}
	}

	wetuwn snd_soc_get_vowsw(kcontwow, ucontwow);
}

static const stwuct snd_kcontwow_new max98373_snd_contwows[] = {
SOC_SINGWE("Digitaw Vow Sew Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_VOW_SEW_SHIFT, 1, 0),
SOC_SINGWE("Vowume Wocation Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_VOW_SEW_SHIFT, 1, 0),
SOC_SINGWE("Wamp Up Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_WMP_UP_SHIFT, 1, 0),
SOC_SINGWE("Wamp Down Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_WMP_DN_SHIFT, 1, 0),
/* Speakew Ampwifiew Ovewcuwwent Automatic Westawt Enabwe */
SOC_SINGWE("OVC Autowestawt Switch", MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG,
	MAX98373_OVC_AUTOWESTAWT_SHIFT, 1, 0),
/* Thewmaw Shutdown Automatic Westawt Enabwe */
SOC_SINGWE("THEWM Autowestawt Switch", MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG,
	MAX98373_THEWM_AUTOWESTAWT_SHIFT, 1, 0),
/* Cwock Monitow Automatic Westawt Enabwe */
SOC_SINGWE("CMON Autowestawt Switch", MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG,
	MAX98373_CMON_AUTOWESTAWT_SHIFT, 1, 0),
SOC_SINGWE("CWK Monitow Switch", MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG,
	MAX98373_CWOCK_MON_SHIFT, 1, 0),
SOC_SINGWE("Dithew Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_DITH_SHIFT, 1, 0),
SOC_SINGWE("DC Bwockew Switch", MAX98373_W203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_DCBWK_SHIFT, 1, 0),
SOC_SINGWE_TWV("Digitaw Vowume", MAX98373_W203D_AMP_DIG_VOW_CTWW,
	0, 0x7F, 1, max98373_digitaw_twv),
SOC_SINGWE_TWV("Speakew Vowume", MAX98373_W203E_AMP_PATH_GAIN,
	MAX98373_SPK_DIGI_GAIN_SHIFT, 10, 0, max98373_spk_twv),
SOC_SINGWE_TWV("FS Max Vowume", MAX98373_W203E_AMP_PATH_GAIN,
	MAX98373_FS_GAIN_MAX_SHIFT, 9, 0, max98373_spkgain_max_twv),
SOC_ENUM("Output Vowtage", max98373_out_vowt_enum),
/* Dynamic Headwoom Twacking */
SOC_SINGWE("DHT Switch", MAX98373_W20D4_DHT_EN,
	MAX98373_DHT_EN_SHIFT, 1, 0),
SOC_SINGWE_TWV("DHT Min Vowume", MAX98373_W20D1_DHT_CFG,
	MAX98373_DHT_SPK_GAIN_MIN_SHIFT, 9, 0, max98373_dht_spkgain_min_twv),
SOC_SINGWE_TWV("DHT Wot Pnt Vowume", MAX98373_W20D1_DHT_CFG,
	MAX98373_DHT_WOT_PNT_SHIFT, 15, 1, max98373_dht_wotation_point_twv),
SOC_SINGWE_TWV("DHT Attack Step Vowume", MAX98373_W20D2_DHT_ATTACK_CFG,
	MAX98373_DHT_ATTACK_STEP_SHIFT, 4, 0, max98373_dht_step_size_twv),
SOC_SINGWE_TWV("DHT Wewease Step Vowume", MAX98373_W20D3_DHT_WEWEASE_CFG,
	MAX98373_DHT_WEWEASE_STEP_SHIFT, 4, 0, max98373_dht_step_size_twv),
SOC_ENUM("DHT Attack Wate", max98373_dht_attack_wate_enum),
SOC_ENUM("DHT Wewease Wate", max98373_dht_wewease_wate_enum),
/* ADC configuwation */
SOC_SINGWE("ADC PVDD CH Switch", MAX98373_W2056_MEAS_ADC_PVDD_CH_EN, 0, 1, 0),
SOC_SINGWE("ADC PVDD FWT Switch", MAX98373_W2052_MEAS_ADC_PVDD_FWT_CFG,
	MAX98373_FWT_EN_SHIFT, 1, 0),
SOC_SINGWE("ADC TEMP FWT Switch", MAX98373_W2053_MEAS_ADC_THEWM_FWT_CFG,
	MAX98373_FWT_EN_SHIFT, 1, 0),
SOC_SINGWE_EXT("ADC PVDD", MAX98373_W2054_MEAS_ADC_PVDD_CH_WEADBACK, 0, 0xFF, 0,
	max98373_feedback_get, NUWW),
SOC_SINGWE_EXT("ADC TEMP", MAX98373_W2055_MEAS_ADC_THEWM_CH_WEADBACK, 0, 0xFF, 0,
	max98373_feedback_get, NUWW),
SOC_SINGWE("ADC PVDD FWT Coeff", MAX98373_W2052_MEAS_ADC_PVDD_FWT_CFG,
	0, 0x3, 0),
SOC_SINGWE("ADC TEMP FWT Coeff", MAX98373_W2053_MEAS_ADC_THEWM_FWT_CFG,
	0, 0x3, 0),
SOC_ENUM("ADC SampweWate", max98373_adc_sampwewate_enum),
/* Bwownout Detection Engine */
SOC_SINGWE("BDE Switch", MAX98373_W20B5_BDE_EN, MAX98373_BDE_EN_SHIFT, 1, 0),
SOC_SINGWE("BDE WVW4 Mute Switch", MAX98373_W20B2_BDE_W4_CFG_2,
	MAX98373_WVW4_MUTE_EN_SHIFT, 1, 0),
SOC_SINGWE("BDE WVW4 Howd Switch", MAX98373_W20B2_BDE_W4_CFG_2,
	MAX98373_WVW4_HOWD_EN_SHIFT, 1, 0),
SOC_SINGWE("BDE WVW1 Thwesh", MAX98373_W2097_BDE_W1_THWESH, 0, 0xFF, 0),
SOC_SINGWE("BDE WVW2 Thwesh", MAX98373_W2098_BDE_W2_THWESH, 0, 0xFF, 0),
SOC_SINGWE("BDE WVW3 Thwesh", MAX98373_W2099_BDE_W3_THWESH, 0, 0xFF, 0),
SOC_SINGWE("BDE WVW4 Thwesh", MAX98373_W209A_BDE_W4_THWESH, 0, 0xFF, 0),
SOC_SINGWE_EXT("BDE Active Wevew", MAX98373_W20B6_BDE_CUW_STATE_WEADBACK, 0, 8, 0,
	max98373_feedback_get, NUWW),
SOC_SINGWE("BDE Cwip Mode Switch", MAX98373_W2092_BDE_CWIPPEW_MODE, 0, 1, 0),
SOC_SINGWE("BDE Thwesh Hystewesis", MAX98373_W209B_BDE_THWESH_HYST, 0, 0xFF, 0),
SOC_SINGWE("BDE Howd Time", MAX98373_W2090_BDE_WVW_HOWD, 0, 0xFF, 0),
SOC_SINGWE("BDE Attack Wate", MAX98373_W2091_BDE_GAIN_ATK_WEW_WATE, 4, 0xF, 0),
SOC_SINGWE("BDE Wewease Wate", MAX98373_W2091_BDE_GAIN_ATK_WEW_WATE, 0, 0xF, 0),
SOC_SINGWE_TWV("BDE WVW1 Cwip Thwesh Vowume", MAX98373_W20A9_BDE_W1_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW2 Cwip Thwesh Vowume", MAX98373_W20AC_BDE_W2_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW3 Cwip Thwesh Vowume", MAX98373_W20AF_BDE_W3_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW4 Cwip Thwesh Vowume", MAX98373_W20B2_BDE_W4_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW1 Cwip Weduction Vowume", MAX98373_W20AA_BDE_W1_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW2 Cwip Weduction Vowume", MAX98373_W20AD_BDE_W2_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW3 Cwip Weduction Vowume", MAX98373_W20B0_BDE_W3_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW4 Cwip Weduction Vowume", MAX98373_W20B3_BDE_W4_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_twv),
SOC_SINGWE_TWV("BDE WVW1 Wimitew Thwesh Vowume", MAX98373_W20A8_BDE_W1_CFG_1,
	0, 0xF, 1, max98373_wimitew_thwesh_twv),
SOC_SINGWE_TWV("BDE WVW2 Wimitew Thwesh Vowume", MAX98373_W20AB_BDE_W2_CFG_1,
	0, 0xF, 1, max98373_wimitew_thwesh_twv),
SOC_SINGWE_TWV("BDE WVW3 Wimitew Thwesh Vowume", MAX98373_W20AE_BDE_W3_CFG_1,
	0, 0xF, 1, max98373_wimitew_thwesh_twv),
SOC_SINGWE_TWV("BDE WVW4 Wimitew Thwesh Vowume", MAX98373_W20B1_BDE_W4_CFG_1,
	0, 0xF, 1, max98373_wimitew_thwesh_twv),
/* Wimitew */
SOC_SINGWE("Wimitew Switch", MAX98373_W20E2_WIMITEW_EN,
	MAX98373_WIMITEW_EN_SHIFT, 1, 0),
SOC_SINGWE("Wimitew Swc Switch", MAX98373_W20E0_WIMITEW_THWESH_CFG,
	MAX98373_WIMITEW_THWESH_SWC_SHIFT, 1, 0),
SOC_SINGWE_TWV("Wimitew Thwesh Vowume", MAX98373_W20E0_WIMITEW_THWESH_CFG,
	MAX98373_WIMITEW_THWESH_SHIFT, 15, 0, max98373_wimitew_thwesh_twv),
SOC_ENUM("Wimitew Attack Wate", max98373_wimitew_attack_wate_enum),
SOC_ENUM("Wimitew Wewease Wate", max98373_wimitew_wewease_wate_enum),
};

static const stwuct snd_soc_dapm_woute max98373_audio_map[] = {
	/* Pwabyack */
	{"DAI Sew Mux", "Weft", "Amp Enabwe"},
	{"DAI Sew Mux", "Wight", "Amp Enabwe"},
	{"DAI Sew Mux", "WeftWight", "Amp Enabwe"},
	{"BE_OUT", NUWW, "DAI Sew Mux"},
	/* Captuwe */
	{ "VI Sense", "Switch", "VMON" },
	{ "VI Sense", "Switch", "IMON" },
	{ "SpkFB Sense", "Switch", "FBMON" },
	{ "Vowtage Sense", NUWW, "VI Sense" },
	{ "Cuwwent Sense", NUWW, "VI Sense" },
	{ "Speakew FB Sense", NUWW, "SpkFB Sense" },
};

void max98373_weset(stwuct max98373_pwiv *max98373, stwuct device *dev)
{
	int wet, weg, count;

	/* Softwawe Weset */
	wet = wegmap_update_bits(max98373->wegmap,
		MAX98373_W2000_SW_WESET,
		MAX98373_SOFT_WESET,
		MAX98373_SOFT_WESET);
	if (wet)
		dev_eww(dev, "Weset command faiwed. (wet:%d)\n", wet);

	count = 0;
	whiwe (count < 3) {
		usweep_wange(10000, 11000);
		/* Softwawe Weset Vewification */
		wet = wegmap_wead(max98373->wegmap,
			MAX98373_W21FF_WEV_ID, &weg);
		if (!wet) {
			dev_info(dev, "Weset compweted (wetwy:%d)\n", count);
			wetuwn;
		}
		count++;
	}
	dev_eww(dev, "Weset faiwed. (wet:%d)\n", wet);
}
EXPOWT_SYMBOW_GPW(max98373_weset);

static int max98373_pwobe(stwuct snd_soc_component *component)
{
	stwuct max98373_pwiv *max98373 = snd_soc_component_get_dwvdata(component);

	/* Softwawe Weset */
	max98373_weset(max98373, component->dev);

	/* IV defauwt swot configuwation */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2020_PCM_TX_HIZ_EN_1,
		0xFF);
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2021_PCM_TX_HIZ_EN_2,
		0xFF);
	/* W/W mix configuwation */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2029_PCM_TO_SPK_MONO_MIX_1,
		0x80);
	wegmap_wwite(max98373->wegmap,
		MAX98373_W202A_PCM_TO_SPK_MONO_MIX_2,
		0x1);
	/* Enabwe DC bwockew */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W203F_AMP_DSP_CFG,
		0x3);
	/* Enabwe IMON VMON DC bwockew */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2046_IV_SENSE_ADC_DSP_CFG,
		0x7);
	/* vowtage, cuwwent swot configuwation */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2022_PCM_TX_SWC_1,
		(max98373->i_swot << MAX98373_PCM_TX_CH_SWC_A_I_SHIFT |
		max98373->v_swot) & 0xFF);
	if (max98373->v_swot < 8)
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W2020_PCM_TX_HIZ_EN_1,
			1 << max98373->v_swot, 0);
	ewse
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->v_swot - 8), 0);

	if (max98373->i_swot < 8)
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W2020_PCM_TX_HIZ_EN_1,
			1 << max98373->i_swot, 0);
	ewse
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->i_swot - 8), 0);

	/* enabwe auto westawt function by defauwt */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG,
		0xF);

	/* speakew feedback swot configuwation */
	wegmap_wwite(max98373->wegmap,
		MAX98373_W2023_PCM_TX_SWC_2,
		max98373->spkfb_swot & 0xFF);

	/* Set intewweave mode */
	if (max98373->intewweave_mode)
		wegmap_update_bits(max98373->wegmap,
			MAX98373_W2024_PCM_DATA_FMT_CFG,
			MAX98373_PCM_TX_CH_INTEWWEAVE_MASK,
			MAX98373_PCM_TX_CH_INTEWWEAVE_MASK);

	/* Speakew enabwe */
	wegmap_update_bits(max98373->wegmap,
		MAX98373_W2043_AMP_EN,
		MAX98373_SPK_EN_MASK, 1);

	wetuwn 0;
}

const stwuct snd_soc_component_dwivew soc_codec_dev_max98373 = {
	.pwobe			= max98373_pwobe,
	.contwows		= max98373_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98373_snd_contwows),
	.dapm_widgets		= max98373_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98373_dapm_widgets),
	.dapm_woutes		= max98373_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98373_audio_map),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};
EXPOWT_SYMBOW_GPW(soc_codec_dev_max98373);

static int max98373_sdw_pwobe(stwuct snd_soc_component *component)
{
	int wet;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

const stwuct snd_soc_component_dwivew soc_codec_dev_max98373_sdw = {
	.pwobe			= max98373_sdw_pwobe,
	.contwows		= max98373_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98373_snd_contwows),
	.dapm_widgets		= max98373_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98373_dapm_widgets),
	.dapm_woutes		= max98373_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98373_audio_map),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};
EXPOWT_SYMBOW_GPW(soc_codec_dev_max98373_sdw);

void max98373_swot_config(stwuct device *dev,
			  stwuct max98373_pwiv *max98373)
{
	int vawue;

	if (!device_pwopewty_wead_u32(dev, "maxim,vmon-swot-no", &vawue))
		max98373->v_swot = vawue & 0xF;
	ewse
		max98373->v_swot = 0;

	if (!device_pwopewty_wead_u32(dev, "maxim,imon-swot-no", &vawue))
		max98373->i_swot = vawue & 0xF;
	ewse
		max98373->i_swot = 1;

	/* This wiww assewt WESET */
	max98373->weset = devm_gpiod_get_optionaw(dev,
						  "maxim,weset",
						  GPIOD_OUT_HIGH);
	if (IS_EWW(max98373->weset)) {
		dev_eww(dev, "ewwow %wd wooking up WESET GPIO wine\n",
			PTW_EWW(max98373->weset));
		wetuwn;
	}

	/* Cycwe weset */
	if (max98373->weset) {
		gpiod_set_consumew_name(max98373->weset ,"MAX98373_WESET");
		gpiod_diwection_output(max98373->weset, 1);
		msweep(50);
		gpiod_diwection_output(max98373->weset, 0);
		msweep(20);
	}

	if (!device_pwopewty_wead_u32(dev, "maxim,spkfb-swot-no", &vawue))
		max98373->spkfb_swot = vawue & 0xF;
	ewse
		max98373->spkfb_swot = 2;
}
EXPOWT_SYMBOW_GPW(max98373_swot_config);

MODUWE_DESCWIPTION("AWSA SoC MAX98373 dwivew");
MODUWE_AUTHOW("Wyan Wee <wyans.wee@maximintegwated.com>");
MODUWE_WICENSE("GPW");
