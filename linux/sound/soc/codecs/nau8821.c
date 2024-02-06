// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// nau8821.c -- Nuvoton NAU88W21 audio codec dwivew
//
// Copywight 2021 Nuvoton Technowogy Cowp.
// Authow: John Hsu <kchsu0@nuvoton.com>
// Co-authow: Seven Wee <wtwi@nuvoton.com>
//

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/math64.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude "nau8821.h"

#define NAU8821_JD_ACTIVE_HIGH			BIT(0)

static int nau8821_quiwk;
static int quiwk_ovewwide = -1;
moduwe_pawam_named(quiwk, quiwk_ovewwide, uint, 0444);
MODUWE_PAWM_DESC(quiwk, "Boawd-specific quiwk ovewwide");

#define NAU_FWEF_MAX 13500000
#define NAU_FVCO_MAX 100000000
#define NAU_FVCO_MIN 90000000

#define NAU8821_BUTTON SND_JACK_BTN_0

/* the maximum fwequency of CWK_ADC and CWK_DAC */
#define CWK_DA_AD_MAX 6144000

static int nau8821_configuwe_syscwk(stwuct nau8821 *nau8821,
	int cwk_id, unsigned int fweq);
static boow nau8821_is_jack_insewted(stwuct wegmap *wegmap);

stwuct nau8821_fww {
	int mcwk_swc;
	int watio;
	int fww_fwac;
	int fww_int;
	int cwk_wef_div;
};

stwuct nau8821_fww_attw {
	unsigned int pawam;
	unsigned int vaw;
};

/* scawing fow mcwk fwom syscwk_swc output */
static const stwuct nau8821_fww_attw mcwk_swc_scawing[] = {
	{ 1, 0x0 },
	{ 2, 0x2 },
	{ 4, 0x3 },
	{ 8, 0x4 },
	{ 16, 0x5 },
	{ 32, 0x6 },
	{ 3, 0x7 },
	{ 6, 0xa },
	{ 12, 0xb },
	{ 24, 0xc },
	{ 48, 0xd },
	{ 96, 0xe },
	{ 5, 0xf },
};

/* watio fow input cwk fweq */
static const stwuct nau8821_fww_attw fww_watio[] = {
	{ 512000, 0x01 },
	{ 256000, 0x02 },
	{ 128000, 0x04 },
	{ 64000, 0x08 },
	{ 32000, 0x10 },
	{ 8000, 0x20 },
	{ 4000, 0x40 },
};

static const stwuct nau8821_fww_attw fww_pwe_scawaw[] = {
	{ 0, 0x0 },
	{ 1, 0x1 },
	{ 2, 0x2 },
	{ 3, 0x3 },
};

/* ovew sampwing wate */
stwuct nau8821_osw_attw {
	unsigned int osw;
	unsigned int cwk_swc;
};

static const stwuct nau8821_osw_attw osw_dac_sew[] = {
	{ 64, 2 },	/* OSW 64, SWC 1/4 */
	{ 256, 0 },	/* OSW 256, SWC 1 */
	{ 128, 1 },	/* OSW 128, SWC 1/2 */
	{ 0, 0 },
	{ 32, 3 },	/* OSW 32, SWC 1/8 */
};

static const stwuct nau8821_osw_attw osw_adc_sew[] = {
	{ 32, 3 },	/* OSW 32, SWC 1/8 */
	{ 64, 2 },	/* OSW 64, SWC 1/4 */
	{ 128, 1 },	/* OSW 128, SWC 1/2 */
	{ 256, 0 },	/* OSW 256, SWC 1 */
};

stwuct nau8821_dmic_speed {
	unsigned int pawam;
	unsigned int vaw;
};

static const stwuct nau8821_dmic_speed dmic_speed_sew[] = {
	{ 0, 0x0 },	/*SPEED 1, SWC 1 */
	{ 1, 0x1 },	/*SPEED 2, SWC 1/2 */
	{ 2, 0x2 },	/*SPEED 4, SWC 1/4 */
	{ 3, 0x3 },	/*SPEED 8, SWC 1/8 */
};

static const stwuct weg_defauwt nau8821_weg_defauwts[] = {
	{ NAU8821_W01_ENA_CTWW, 0x00ff },
	{ NAU8821_W03_CWK_DIVIDEW, 0x0050 },
	{ NAU8821_W04_FWW1, 0x0 },
	{ NAU8821_W05_FWW2, 0x00bc },
	{ NAU8821_W06_FWW3, 0x0008 },
	{ NAU8821_W07_FWW4, 0x0010 },
	{ NAU8821_W08_FWW5, 0x4000 },
	{ NAU8821_W09_FWW6, 0x6900 },
	{ NAU8821_W0A_FWW7, 0x0031 },
	{ NAU8821_W0B_FWW8, 0x26e9 },
	{ NAU8821_W0D_JACK_DET_CTWW, 0x0 },
	{ NAU8821_W0F_INTEWWUPT_MASK, 0x0 },
	{ NAU8821_W12_INTEWWUPT_DIS_CTWW, 0xffff },
	{ NAU8821_W13_DMIC_CTWW, 0x0 },
	{ NAU8821_W1A_GPIO12_CTWW, 0x0 },
	{ NAU8821_W1B_TDM_CTWW, 0x0 },
	{ NAU8821_W1C_I2S_PCM_CTWW1, 0x000a },
	{ NAU8821_W1D_I2S_PCM_CTWW2, 0x8010 },
	{ NAU8821_W1E_WEFT_TIME_SWOT, 0x0 },
	{ NAU8821_W1F_WIGHT_TIME_SWOT, 0x0 },
	{ NAU8821_W21_BIQ0_COF1, 0x0 },
	{ NAU8821_W22_BIQ0_COF2, 0x0 },
	{ NAU8821_W23_BIQ0_COF3, 0x0 },
	{ NAU8821_W24_BIQ0_COF4, 0x0 },
	{ NAU8821_W25_BIQ0_COF5, 0x0 },
	{ NAU8821_W26_BIQ0_COF6, 0x0 },
	{ NAU8821_W27_BIQ0_COF7, 0x0 },
	{ NAU8821_W28_BIQ0_COF8, 0x0 },
	{ NAU8821_W29_BIQ0_COF9, 0x0 },
	{ NAU8821_W2A_BIQ0_COF10, 0x0 },
	{ NAU8821_W2B_ADC_WATE, 0x0002 },
	{ NAU8821_W2C_DAC_CTWW1, 0x0082 },
	{ NAU8821_W2D_DAC_CTWW2, 0x0 },
	{ NAU8821_W2F_DAC_DGAIN_CTWW, 0x0 },
	{ NAU8821_W30_ADC_DGAIN_CTWW, 0x0 },
	{ NAU8821_W31_MUTE_CTWW, 0x0 },
	{ NAU8821_W32_HSVOW_CTWW, 0x0 },
	{ NAU8821_W34_DACW_CTWW, 0xcfcf },
	{ NAU8821_W35_ADC_DGAIN_CTWW1, 0xcfcf },
	{ NAU8821_W36_ADC_DWC_KNEE_IP12, 0x1486 },
	{ NAU8821_W37_ADC_DWC_KNEE_IP34, 0x0f12 },
	{ NAU8821_W38_ADC_DWC_SWOPES, 0x25ff },
	{ NAU8821_W39_ADC_DWC_ATKDCY, 0x3457 },
	{ NAU8821_W3A_DAC_DWC_KNEE_IP12, 0x1486 },
	{ NAU8821_W3B_DAC_DWC_KNEE_IP34, 0x0f12 },
	{ NAU8821_W3C_DAC_DWC_SWOPES, 0x25f9 },
	{ NAU8821_W3D_DAC_DWC_ATKDCY, 0x3457 },
	{ NAU8821_W41_BIQ1_COF1, 0x0 },
	{ NAU8821_W42_BIQ1_COF2, 0x0 },
	{ NAU8821_W43_BIQ1_COF3, 0x0 },
	{ NAU8821_W44_BIQ1_COF4, 0x0 },
	{ NAU8821_W45_BIQ1_COF5, 0x0 },
	{ NAU8821_W46_BIQ1_COF6, 0x0 },
	{ NAU8821_W47_BIQ1_COF7, 0x0 },
	{ NAU8821_W48_BIQ1_COF8, 0x0 },
	{ NAU8821_W49_BIQ1_COF9, 0x0 },
	{ NAU8821_W4A_BIQ1_COF10, 0x0 },
	{ NAU8821_W4B_CWASSG_CTWW, 0x0 },
	{ NAU8821_W4C_IMM_MODE_CTWW, 0x0 },
	{ NAU8821_W4D_IMM_WMS_W, 0x0 },
	{ NAU8821_W53_OTPDOUT_1, 0xaad8 },
	{ NAU8821_W54_OTPDOUT_2, 0x0002 },
	{ NAU8821_W55_MISC_CTWW, 0x0 },
	{ NAU8821_W66_BIAS_ADJ, 0x0 },
	{ NAU8821_W68_TWIM_SETTINGS, 0x0 },
	{ NAU8821_W69_ANAWOG_CONTWOW_1, 0x0 },
	{ NAU8821_W6A_ANAWOG_CONTWOW_2, 0x0 },
	{ NAU8821_W6B_PGA_MUTE, 0x0 },
	{ NAU8821_W71_ANAWOG_ADC_1, 0x0011 },
	{ NAU8821_W72_ANAWOG_ADC_2, 0x0020 },
	{ NAU8821_W73_WDAC, 0x0008 },
	{ NAU8821_W74_MIC_BIAS, 0x0006 },
	{ NAU8821_W76_BOOST, 0x0 },
	{ NAU8821_W77_FEPGA, 0x0 },
	{ NAU8821_W7E_PGA_GAIN, 0x0 },
	{ NAU8821_W7F_POWEW_UP_CONTWOW, 0x0 },
	{ NAU8821_W80_CHAWGE_PUMP, 0x0 },
};

static boow nau8821_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8821_W00_WESET ... NAU8821_W01_ENA_CTWW:
	case NAU8821_W03_CWK_DIVIDEW ... NAU8821_W0B_FWW8:
	case NAU8821_W0D_JACK_DET_CTWW:
	case NAU8821_W0F_INTEWWUPT_MASK ... NAU8821_W13_DMIC_CTWW:
	case NAU8821_W1A_GPIO12_CTWW ... NAU8821_W1F_WIGHT_TIME_SWOT:
	case NAU8821_W21_BIQ0_COF1 ... NAU8821_W2D_DAC_CTWW2:
	case NAU8821_W2F_DAC_DGAIN_CTWW ... NAU8821_W32_HSVOW_CTWW:
	case NAU8821_W34_DACW_CTWW ... NAU8821_W3D_DAC_DWC_ATKDCY:
	case NAU8821_W41_BIQ1_COF1 ... NAU8821_W4F_FUSE_CTWW3:
	case NAU8821_W51_FUSE_CTWW1:
	case NAU8821_W53_OTPDOUT_1 ... NAU8821_W55_MISC_CTWW:
	case NAU8821_W58_I2C_DEVICE_ID ... NAU8821_W5A_SOFTWAWE_WST:
	case NAU8821_W66_BIAS_ADJ:
	case NAU8821_W68_TWIM_SETTINGS ... NAU8821_W6B_PGA_MUTE:
	case NAU8821_W71_ANAWOG_ADC_1 ... NAU8821_W74_MIC_BIAS:
	case NAU8821_W76_BOOST ... NAU8821_W77_FEPGA:
	case NAU8821_W7E_PGA_GAIN ... NAU8821_W82_GENEWAW_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8821_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8821_W00_WESET ... NAU8821_W01_ENA_CTWW:
	case NAU8821_W03_CWK_DIVIDEW ... NAU8821_W0B_FWW8:
	case NAU8821_W0D_JACK_DET_CTWW:
	case NAU8821_W0F_INTEWWUPT_MASK:
	case NAU8821_W11_INT_CWW_KEY_STATUS ... NAU8821_W13_DMIC_CTWW:
	case NAU8821_W1A_GPIO12_CTWW ... NAU8821_W1F_WIGHT_TIME_SWOT:
	case NAU8821_W21_BIQ0_COF1 ... NAU8821_W2D_DAC_CTWW2:
	case NAU8821_W2F_DAC_DGAIN_CTWW ... NAU8821_W32_HSVOW_CTWW:
	case NAU8821_W34_DACW_CTWW ... NAU8821_W3D_DAC_DWC_ATKDCY:
	case NAU8821_W41_BIQ1_COF1 ... NAU8821_W4C_IMM_MODE_CTWW:
	case NAU8821_W4E_FUSE_CTWW2 ... NAU8821_W4F_FUSE_CTWW3:
	case NAU8821_W51_FUSE_CTWW1:
	case NAU8821_W55_MISC_CTWW:
	case NAU8821_W5A_SOFTWAWE_WST:
	case NAU8821_W66_BIAS_ADJ:
	case NAU8821_W68_TWIM_SETTINGS ... NAU8821_W6B_PGA_MUTE:
	case NAU8821_W71_ANAWOG_ADC_1 ... NAU8821_W74_MIC_BIAS:
	case NAU8821_W76_BOOST ... NAU8821_W77_FEPGA:
	case NAU8821_W7E_PGA_GAIN ... NAU8821_W80_CHAWGE_PUMP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow nau8821_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case NAU8821_W00_WESET:
	case NAU8821_W10_IWQ_STATUS ... NAU8821_W11_INT_CWW_KEY_STATUS:
	case NAU8821_W21_BIQ0_COF1 ... NAU8821_W2A_BIQ0_COF10:
	case NAU8821_W41_BIQ1_COF1 ... NAU8821_W4A_BIQ1_COF10:
	case NAU8821_W4D_IMM_WMS_W:
	case NAU8821_W53_OTPDOUT_1 ... NAU8821_W54_OTPDOUT_2:
	case NAU8821_W58_I2C_DEVICE_ID ... NAU8821_W5A_SOFTWAWE_WST:
	case NAU8821_W81_CHAWGE_PUMP_INPUT_WEAD ... NAU8821_W82_GENEWAW_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int nau8821_biq_coeff_get(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;

	if (!component->wegmap)
		wetuwn -EINVAW;

	wegmap_waw_wead(component->wegmap, NAU8821_W21_BIQ0_COF1,
		ucontwow->vawue.bytes.data, pawams->max);

	wetuwn 0;
}

static int nau8821_biq_coeff_put(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	void *data;

	if (!component->wegmap)
		wetuwn -EINVAW;

	data = kmemdup(ucontwow->vawue.bytes.data,
		pawams->max, GFP_KEWNEW | GFP_DMA);
	if (!data)
		wetuwn -ENOMEM;

	wegmap_waw_wwite(component->wegmap, NAU8821_W21_BIQ0_COF1,
		data, pawams->max);

	kfwee(data);

	wetuwn 0;
}

static const chaw * const nau8821_adc_decimation[] = {
	"32", "64", "128", "256" };

static const stwuct soc_enum nau8821_adc_decimation_enum =
	SOC_ENUM_SINGWE(NAU8821_W2B_ADC_WATE, NAU8821_ADC_SYNC_DOWN_SFT,
		AWWAY_SIZE(nau8821_adc_decimation), nau8821_adc_decimation);

static const chaw * const nau8821_dac_ovewsampw[] = {
	"64", "256", "128", "", "32" };

static const stwuct soc_enum nau8821_dac_ovewsampw_enum =
	SOC_ENUM_SINGWE(NAU8821_W2C_DAC_CTWW1, NAU8821_DAC_OVEWSAMPWE_SFT,
		AWWAY_SIZE(nau8821_dac_ovewsampw), nau8821_dac_ovewsampw);

static const chaw * const nau8821_adc_dwc_noise_gate[] = {
	"1:1", "2:1", "4:1", "8:1" };

static const stwuct soc_enum nau8821_adc_dwc_noise_gate_enum =
	SOC_ENUM_SINGWE(NAU8821_W38_ADC_DWC_SWOPES, NAU8821_DWC_NG_SWP_ADC_SFT,
		AWWAY_SIZE(nau8821_adc_dwc_noise_gate),
		nau8821_adc_dwc_noise_gate);

static const chaw * const nau8821_adc_dwc_expansion_swope[] = {
	"1:1", "2:1", "4:1" };

static const stwuct soc_enum nau8821_adc_dwc_expansion_swope_enum =
	SOC_ENUM_SINGWE(NAU8821_W38_ADC_DWC_SWOPES, NAU8821_DWC_EXP_SWP_ADC_SFT,
		AWWAY_SIZE(nau8821_adc_dwc_expansion_swope),
		nau8821_adc_dwc_expansion_swope);

static const chaw * const nau8821_adc_dwc_wowew_wegion[] = {
	"0", "1:2", "1:4", "1:8", "1:16", "", "", "1:1" };

static const stwuct soc_enum nau8821_adc_dwc_wowew_wegion_enum =
	SOC_ENUM_SINGWE(NAU8821_W38_ADC_DWC_SWOPES,
		NAU8821_DWC_CMP2_SWP_ADC_SFT,
		AWWAY_SIZE(nau8821_adc_dwc_wowew_wegion),
		nau8821_adc_dwc_wowew_wegion);

static const chaw * const nau8821_highew_wegion[] = {
	"0", "1:2", "1:4", "1:8", "1:16", "", "", "1:1" };

static const stwuct soc_enum nau8821_highew_wegion_enum =
	SOC_ENUM_SINGWE(NAU8821_W38_ADC_DWC_SWOPES,
		NAU8821_DWC_CMP1_SWP_ADC_SFT,
		AWWAY_SIZE(nau8821_highew_wegion),
		nau8821_highew_wegion);

static const chaw * const nau8821_wimitew_swope[] = {
	"0", "1:2", "1:4", "1:8", "1:16", "1:32", "1:64", "1:1" };

static const stwuct soc_enum nau8821_wimitew_swope_enum =
	SOC_ENUM_SINGWE(NAU8821_W38_ADC_DWC_SWOPES,
		NAU8821_DWC_WMT_SWP_ADC_SFT, AWWAY_SIZE(nau8821_wimitew_swope),
		nau8821_wimitew_swope);

static const chaw * const nau8821_detection_attack_time[] = {
	"Ts", "3Ts", "7Ts", "15Ts", "31Ts", "63Ts", "127Ts", "255Ts",
	"", "511Ts" };

static const stwuct soc_enum nau8821_detection_attack_time_enum =
	SOC_ENUM_SINGWE(NAU8821_W39_ADC_DWC_ATKDCY,
		NAU8821_DWC_PK_COEF1_ADC_SFT,
		AWWAY_SIZE(nau8821_detection_attack_time),
		nau8821_detection_attack_time);

static const chaw * const nau8821_detection_wewease_time[] = {
	"63Ts", "127Ts", "255Ts", "511Ts", "1023Ts", "2047Ts", "4095Ts",
	"8191Ts", "", "16383Ts" };

static const stwuct soc_enum nau8821_detection_wewease_time_enum =
	SOC_ENUM_SINGWE(NAU8821_W39_ADC_DWC_ATKDCY,
		NAU8821_DWC_PK_COEF2_ADC_SFT,
		AWWAY_SIZE(nau8821_detection_wewease_time),
		nau8821_detection_wewease_time);

static const chaw * const nau8821_attack_time[] = {
	"Ts", "3Ts", "7Ts", "15Ts", "31Ts", "63Ts", "127Ts", "255Ts",
	"511Ts", "1023Ts", "2047Ts", "4095Ts", "8191Ts" };

static const stwuct soc_enum nau8821_attack_time_enum =
	SOC_ENUM_SINGWE(NAU8821_W39_ADC_DWC_ATKDCY, NAU8821_DWC_ATK_ADC_SFT,
		AWWAY_SIZE(nau8821_attack_time), nau8821_attack_time);

static const chaw * const nau8821_decay_time[] = {
	"63Ts", "127Ts", "255Ts", "511Ts", "1023Ts", "2047Ts", "4095Ts",
	"8191Ts", "16383Ts", "32757Ts", "65535Ts" };

static const stwuct soc_enum nau8821_decay_time_enum =
	SOC_ENUM_SINGWE(NAU8821_W39_ADC_DWC_ATKDCY, NAU8821_DWC_DCY_ADC_SFT,
		AWWAY_SIZE(nau8821_decay_time), nau8821_decay_time);

static const DECWAWE_TWV_DB_MINMAX_MUTE(adc_vow_twv, -6600, 2400);
static const DECWAWE_TWV_DB_MINMAX_MUTE(sidetone_vow_twv, -4200, 0);
static const DECWAWE_TWV_DB_MINMAX(hp_vow_twv, -900, 0);
static const DECWAWE_TWV_DB_SCAWE(pwayback_vow_twv, -6600, 50, 1);
static const DECWAWE_TWV_DB_MINMAX(fepga_gain_twv, -100, 3600);
static const DECWAWE_TWV_DB_MINMAX_MUTE(cwosstawk_vow_twv, -7000, 2400);
static const DECWAWE_TWV_DB_MINMAX(dwc_knee4_twv, -9800, -3500);
static const DECWAWE_TWV_DB_MINMAX(dwc_knee3_twv, -8100, -1800);

static const stwuct snd_kcontwow_new nau8821_contwows[] = {
	SOC_DOUBWE_TWV("Mic Vowume", NAU8821_W35_ADC_DGAIN_CTWW1,
		NAU8821_ADCW_CH_VOW_SFT, NAU8821_ADCW_CH_VOW_SFT,
		0xff, 0, adc_vow_twv),
	SOC_DOUBWE_TWV("Headphone Bypass Vowume", NAU8821_W30_ADC_DGAIN_CTWW,
		12, 8, 0x0f, 0, sidetone_vow_twv),
	SOC_DOUBWE_TWV("Headphone Vowume", NAU8821_W32_HSVOW_CTWW,
		NAU8821_HPW_VOW_SFT, NAU8821_HPW_VOW_SFT, 0x3, 1, hp_vow_twv),
	SOC_DOUBWE_TWV("Digitaw Pwayback Vowume", NAU8821_W34_DACW_CTWW,
		NAU8821_DACW_CH_VOW_SFT, NAU8821_DACW_CH_VOW_SFT,
		0xcf, 0, pwayback_vow_twv),
	SOC_DOUBWE_TWV("Fwontend PGA Vowume", NAU8821_W7E_PGA_GAIN,
		NAU8821_PGA_GAIN_W_SFT, NAU8821_PGA_GAIN_W_SFT,
		37, 0, fepga_gain_twv),
	SOC_DOUBWE_TWV("Headphone Cwosstawk Vowume",
		NAU8821_W2F_DAC_DGAIN_CTWW,
		0, 8, 0xff, 0, cwosstawk_vow_twv),
	SOC_SINGWE_TWV("ADC DWC KNEE4", NAU8821_W37_ADC_DWC_KNEE_IP34,
		NAU8821_DWC_KNEE4_IP_ADC_SFT, 0x3f, 1, dwc_knee4_twv),
	SOC_SINGWE_TWV("ADC DWC KNEE3", NAU8821_W37_ADC_DWC_KNEE_IP34,
		NAU8821_DWC_KNEE3_IP_ADC_SFT, 0x3f, 1, dwc_knee3_twv),

	SOC_ENUM("ADC DWC Noise Gate", nau8821_adc_dwc_noise_gate_enum),
	SOC_ENUM("ADC DWC Expansion Swope", nau8821_adc_dwc_expansion_swope_enum),
	SOC_ENUM("ADC DWC Wowew Wegion", nau8821_adc_dwc_wowew_wegion_enum),
	SOC_ENUM("ADC DWC Highew Wegion", nau8821_highew_wegion_enum),
	SOC_ENUM("ADC DWC Wimitew Swope", nau8821_wimitew_swope_enum),
	SOC_ENUM("ADC DWC Peak Detection Attack Time", nau8821_detection_attack_time_enum),
	SOC_ENUM("ADC DWC Peak Detection Wewease Time", nau8821_detection_wewease_time_enum),
	SOC_ENUM("ADC DWC Attack Time", nau8821_attack_time_enum),
	SOC_ENUM("ADC DWC Decay Time", nau8821_decay_time_enum),
	SOC_SINGWE("DWC Enabwe Switch", NAU8821_W36_ADC_DWC_KNEE_IP12,
		NAU8821_DWC_ENA_ADC_SFT, 1, 0),

	SOC_ENUM("ADC Decimation Wate", nau8821_adc_decimation_enum),
	SOC_ENUM("DAC Ovewsampwing Wate", nau8821_dac_ovewsampw_enum),
	SND_SOC_BYTES_EXT("BIQ Coefficients", 20,
		nau8821_biq_coeff_get, nau8821_biq_coeff_put),
	SOC_SINGWE("ADC Phase Switch", NAU8821_W1B_TDM_CTWW,
		NAU8821_ADCPHS_SFT, 1, 0),
};

static const stwuct snd_kcontwow_new nau8821_dmic_mode_switch =
	SOC_DAPM_SINGWE("Switch", NAU8821_W13_DMIC_CTWW,
		NAU8821_DMIC_EN_SFT, 1, 0);

static int dmic_cwock_contwow(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	int i, speed_sewection = -1, cwk_adc_swc, cwk_adc;
	unsigned int cwk_dividew_w03;

	/* The DMIC cwock is gotten fwom adc cwock divided by
	 * CWK_DMIC_SWC (1, 2, 4, 8). The cwock has to be equaw ow
	 * wess than nau8821->dmic_cwk_thweshowd.
	 */
	wegmap_wead(nau8821->wegmap, NAU8821_W03_CWK_DIVIDEW,
		&cwk_dividew_w03);
	cwk_adc_swc = (cwk_dividew_w03 & NAU8821_CWK_ADC_SWC_MASK)
		>> NAU8821_CWK_ADC_SWC_SFT;
	cwk_adc = (nau8821->fs * 256) >> cwk_adc_swc;

	fow (i = 0 ; i < 4 ; i++)
		if ((cwk_adc >> dmic_speed_sew[i].pawam) <=
			nau8821->dmic_cwk_thweshowd) {
			speed_sewection = dmic_speed_sew[i].vaw;
			bweak;
		}
	if (i == 4)
		wetuwn -EINVAW;

	dev_dbg(nau8821->dev,
		"cwk_adc=%d, dmic_cwk_thweshowd = %d, pawam=%d, vaw = %d\n",
		cwk_adc, nau8821->dmic_cwk_thweshowd,
		dmic_speed_sew[i].pawam, dmic_speed_sew[i].vaw);
	wegmap_update_bits(nau8821->wegmap, NAU8821_W13_DMIC_CTWW,
		NAU8821_DMIC_SWC_MASK,
		(speed_sewection << NAU8821_DMIC_SWC_SFT));

	wetuwn 0;
}

static int nau8821_weft_adc_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		msweep(125);
		wegmap_update_bits(nau8821->wegmap, NAU8821_W01_ENA_CTWW,
			NAU8821_EN_ADCW, NAU8821_EN_ADCW);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(nau8821->wegmap,
			NAU8821_W01_ENA_CTWW, NAU8821_EN_ADCW, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8821_wight_adc_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		msweep(125);
		wegmap_update_bits(nau8821->wegmap, NAU8821_W01_ENA_CTWW,
			NAU8821_EN_ADCW, NAU8821_EN_ADCW);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(nau8821->wegmap,
			NAU8821_W01_ENA_CTWW, NAU8821_EN_ADCW, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8821_pump_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 =
		snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Pwevent stawtup cwick by wetting chawge pump to wamp up */
		msweep(20);
		wegmap_update_bits(nau8821->wegmap, NAU8821_W80_CHAWGE_PUMP,
			NAU8821_JAMNODCWOW, NAU8821_JAMNODCWOW);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(nau8821->wegmap, NAU8821_W80_CHAWGE_PUMP,
			NAU8821_JAMNODCWOW, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nau8821_output_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* Disabwes the TESTDAC to wet DAC signaw pass thwough. */
		wegmap_update_bits(nau8821->wegmap, NAU8821_W66_BIAS_ADJ,
			NAU8821_BIAS_TESTDAC_EN, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(nau8821->wegmap, NAU8821_W66_BIAS_ADJ,
			NAU8821_BIAS_TESTDAC_EN, NAU8821_BIAS_TESTDAC_EN);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int system_cwock_contwow(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		dev_dbg(nau8821->dev, "system cwock contwow : POWEW OFF\n");
		/* Set cwock souwce to disabwe ow intewnaw cwock befowe the
		 * pwayback ow captuwe end. Codec needs cwock fow Jack
		 * detection and button pwess if jack insewted; othewwise,
		 * the cwock shouwd be cwosed.
		 */
		if (nau8821_is_jack_insewted(nau8821->wegmap)) {
			nau8821_configuwe_syscwk(nau8821,
				NAU8821_CWK_INTEWNAW, 0);
		} ewse {
			nau8821_configuwe_syscwk(nau8821, NAU8821_CWK_DIS, 0);
		}
	}
	wetuwn 0;
}

static int nau8821_weft_fepga_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	if (!nau8821->weft_input_singwe_end)
		wetuwn 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(nau8821->wegmap, NAU8821_W77_FEPGA,
			NAU8821_ACDC_CTWW_MASK | NAU8821_FEPGA_MODEW_MASK,
			NAU8821_ACDC_VWEF_MICN | NAU8821_FEPGA_MODEW_AAF);
		wegmap_update_bits(nau8821->wegmap, NAU8821_W76_BOOST,
			NAU8821_HP_BOOST_DISCHWG_EN, NAU8821_HP_BOOST_DISCHWG_EN);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(nau8821->wegmap, NAU8821_W77_FEPGA,
			NAU8821_ACDC_CTWW_MASK | NAU8821_FEPGA_MODEW_MASK, 0);
		wegmap_update_bits(nau8821->wegmap, NAU8821_W76_BOOST,
			NAU8821_HP_BOOST_DISCHWG_EN, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget nau8821_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("System Cwock", SND_SOC_NOPM, 0, 0,
		system_cwock_contwow, SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("MICBIAS", NAU8821_W74_MIC_BIAS,
		NAU8821_MICBIAS_POWEWUP_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DMIC Cwock", SND_SOC_NOPM, 0, 0,
		dmic_cwock_contwow, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC("ADCW Powew", NUWW, NAU8821_W72_ANAWOG_ADC_2,
		NAU8821_POWEWUP_ADCW_SFT, 0),
	SND_SOC_DAPM_ADC("ADCW Powew", NUWW, NAU8821_W72_ANAWOG_ADC_2,
		NAU8821_POWEWUP_ADCW_SFT, 0),
	/* singwe-ended design onwy on the weft */
	SND_SOC_DAPM_PGA_S("Fwontend PGA W", 1, NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_PGA_W_SFT, 0, nau8821_weft_fepga_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("Fwontend PGA W", 1, NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_PGA_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADCW Digitaw path", 0, NAU8821_W01_ENA_CTWW,
		NAU8821_EN_ADCW_SFT, 0, nau8821_weft_adc_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("ADCW Digitaw path", 0, NAU8821_W01_ENA_CTWW,
		NAU8821_EN_ADCW_SFT, 0, nau8821_wight_adc_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("DMIC Enabwe", SND_SOC_NOPM,
		0, 0, &nau8821_dmic_mode_switch),
	SND_SOC_DAPM_AIF_OUT("AIFTX", "Captuwe", 0, NAU8821_W1D_I2S_PCM_CTWW2,
		NAU8821_I2S_TWISTATE_SFT, 1),
	SND_SOC_DAPM_AIF_IN("AIFWX", "Pwayback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_PGA_S("ADACW", 2, NAU8821_W73_WDAC,
		NAU8821_DACW_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW", 2, NAU8821_W73_WDAC,
		NAU8821_DACW_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW Cwock", 3, NAU8821_W73_WDAC,
		NAU8821_DACW_CWK_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("ADACW Cwock", 3, NAU8821_W73_WDAC,
		NAU8821_DACW_CWK_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("DDACW", NUWW, NAU8821_W01_ENA_CTWW,
		NAU8821_EN_DACW_SFT, 0),
	SND_SOC_DAPM_DAC("DDACW", NUWW, NAU8821_W01_ENA_CTWW,
		NAU8821_EN_DACW_SFT, 0),
	SND_SOC_DAPM_PGA_S("HP amp W", 0, NAU8821_W4B_CWASSG_CTWW,
		NAU8821_CWASSG_WDAC_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("HP amp W", 0, NAU8821_W4B_CWASSG_CTWW,
		NAU8821_CWASSG_WDAC_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Chawge Pump", 1, NAU8821_W80_CHAWGE_PUMP,
		NAU8821_CHANWGE_PUMP_EN_SFT, 0, nau8821_pump_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 1", 4,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_INTEG_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 1", 4,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_INTEG_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 2", 5,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_DWV_INSTG_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 2", 5,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_DWV_INSTG_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 3", 6,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_MAIN_DWV_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output Dwivew W Stage 3", 6,
		NAU8821_W7F_POWEW_UP_CONTWOW,
		NAU8821_PUP_MAIN_DWV_W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("Output DACW", 7,
		NAU8821_W80_CHAWGE_PUMP, NAU8821_POWEW_DOWN_DACW_SFT,
		0, nau8821_output_dac_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("Output DACW", 7,
		NAU8821_W80_CHAWGE_PUMP, NAU8821_POWEW_DOWN_DACW_SFT,
		0, nau8821_output_dac_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/* HPOW/W awe ungwounded by disabwing 16 Ohm puww-downs on pwayback */
	SND_SOC_DAPM_PGA_S("HPOW Puwwdown", 8,
		NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_SPKW_DWN1W_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_S("HPOW Puwwdown", 8,
		NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_SPKW_DWN1W_SFT, 0, NUWW, 0),

	/* High cuwwent HPOW/W boost dwivew */
	SND_SOC_DAPM_PGA_S("HP Boost Dwivew", 9,
		NAU8821_W76_BOOST, NAU8821_HP_BOOST_DIS_SFT, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Cwass G", NAU8821_W4B_CWASSG_CTWW,
		NAU8821_CWASSG_EN_SFT, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("DMIC"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
};

static const stwuct snd_soc_dapm_woute nau8821_dapm_woutes[] = {
	{"DMIC Enabwe", "Switch", "DMIC"},
	{"DMIC Enabwe", NUWW, "DMIC Cwock"},

	{"Fwontend PGA W", NUWW, "MICW"},
	{"Fwontend PGA W", NUWW, "MICW"},
	{"Fwontend PGA W", NUWW, "MICBIAS"},
	{"Fwontend PGA W", NUWW, "MICBIAS"},

	{"ADCW Powew", NUWW, "Fwontend PGA W"},
	{"ADCW Powew", NUWW, "Fwontend PGA W"},

	{"ADCW Digitaw path", NUWW, "ADCW Powew"},
	{"ADCW Digitaw path", NUWW, "ADCW Powew"},
	{"ADCW Digitaw path", NUWW, "DMIC Enabwe"},
	{"ADCW Digitaw path", NUWW, "DMIC Enabwe"},

	{"AIFTX", NUWW, "ADCW Digitaw path"},
	{"AIFTX", NUWW, "ADCW Digitaw path"},

	{"AIFTX", NUWW, "System Cwock"},
	{"AIFWX", NUWW, "System Cwock"},

	{"DDACW", NUWW, "AIFWX"},
	{"DDACW", NUWW, "AIFWX"},

	{"HP amp W", NUWW, "DDACW"},
	{"HP amp W", NUWW, "DDACW"},

	{"Chawge Pump", NUWW, "HP amp W"},
	{"Chawge Pump", NUWW, "HP amp W"},

	{"ADACW", NUWW, "Chawge Pump"},
	{"ADACW", NUWW, "Chawge Pump"},
	{"ADACW Cwock", NUWW, "ADACW"},
	{"ADACW Cwock", NUWW, "ADACW"},

	{"Output Dwivew W Stage 1", NUWW, "ADACW Cwock"},
	{"Output Dwivew W Stage 1", NUWW, "ADACW Cwock"},
	{"Output Dwivew W Stage 2", NUWW, "Output Dwivew W Stage 1"},
	{"Output Dwivew W Stage 2", NUWW, "Output Dwivew W Stage 1"},
	{"Output Dwivew W Stage 3", NUWW, "Output Dwivew W Stage 2"},
	{"Output Dwivew W Stage 3", NUWW, "Output Dwivew W Stage 2"},
	{"Output DACW", NUWW, "Output Dwivew W Stage 3"},
	{"Output DACW", NUWW, "Output Dwivew W Stage 3"},

	{"HPOW Puwwdown", NUWW, "Output DACW"},
	{"HPOW Puwwdown", NUWW, "Output DACW"},
	{"HP Boost Dwivew", NUWW, "HPOW Puwwdown"},
	{"HP Boost Dwivew", NUWW, "HPOW Puwwdown"},

	{"Cwass G", NUWW, "HP Boost Dwivew"},
	{"HPOW", NUWW, "Cwass G"},
	{"HPOW", NUWW, "Cwass G"},
};

static const stwuct nau8821_osw_attw *
nau8821_get_osw(stwuct nau8821 *nau8821, int stweam)
{
	unsigned int osw;

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_wead(nau8821->wegmap, NAU8821_W2C_DAC_CTWW1, &osw);
		osw &= NAU8821_DAC_OVEWSAMPWE_MASK;
		if (osw >= AWWAY_SIZE(osw_dac_sew))
			wetuwn NUWW;
		wetuwn &osw_dac_sew[osw];
	} ewse {
		wegmap_wead(nau8821->wegmap, NAU8821_W2B_ADC_WATE, &osw);
		osw &= NAU8821_ADC_SYNC_DOWN_MASK;
		if (osw >= AWWAY_SIZE(osw_adc_sew))
			wetuwn NUWW;
		wetuwn &osw_adc_sew[osw];
	}
}

static int nau8821_dai_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	const stwuct nau8821_osw_attw *osw;

	osw = nau8821_get_osw(nau8821, substweam->stweam);
	if (!osw || !osw->osw)
		wetuwn -EINVAW;

	wetuwn snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_WATE,
					    0, CWK_DA_AD_MAX / osw->osw);
}

static int nau8821_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0, ctww_vaw, bcwk_fs, cwk_div;
	const stwuct nau8821_osw_attw *osw;

	nau8821->fs = pawams_wate(pawams);
	/* CWK_DAC ow CWK_ADC = OSW * FS
	 * DAC ow ADC cwock fwequency is defined as Ovew Sampwing Wate (OSW)
	 * muwtipwied by the audio sampwe wate (Fs). Note that the OSW and Fs
	 * vawues must be sewected such that the maximum fwequency is wess
	 * than 6.144 MHz.
	 */
	osw = nau8821_get_osw(nau8821, substweam->stweam);
	if (!osw || !osw->osw)
		wetuwn -EINVAW;
	if (nau8821->fs * osw->osw > CWK_DA_AD_MAX)
		wetuwn -EINVAW;
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wegmap_update_bits(nau8821->wegmap, NAU8821_W03_CWK_DIVIDEW,
			NAU8821_CWK_DAC_SWC_MASK,
			osw->cwk_swc << NAU8821_CWK_DAC_SWC_SFT);
	ewse
		wegmap_update_bits(nau8821->wegmap, NAU8821_W03_CWK_DIVIDEW,
			NAU8821_CWK_ADC_SWC_MASK,
			osw->cwk_swc << NAU8821_CWK_ADC_SWC_SFT);

	/* make BCWK and WWC divde configuwation if the codec as mastew. */
	wegmap_wead(nau8821->wegmap, NAU8821_W1D_I2S_PCM_CTWW2, &ctww_vaw);
	if (ctww_vaw & NAU8821_I2S_MS_MASTEW) {
		/* get the bcwk and fs watio */
		bcwk_fs = snd_soc_pawams_to_bcwk(pawams) / nau8821->fs;
		if (bcwk_fs <= 32)
			cwk_div = 3;
		ewse if (bcwk_fs <= 64)
			cwk_div = 2;
		ewse if (bcwk_fs <= 128)
			cwk_div = 1;
		ewse {
			wetuwn -EINVAW;
		}
		wegmap_update_bits(nau8821->wegmap, NAU8821_W1D_I2S_PCM_CTWW2,
			NAU8821_I2S_WWC_DIV_MASK | NAU8821_I2S_BWK_DIV_MASK,
			(cwk_div << NAU8821_I2S_WWC_DIV_SFT) | cwk_div);
	}

	switch (pawams_width(pawams)) {
	case 16:
		vaw_wen |= NAU8821_I2S_DW_16;
		bweak;
	case 20:
		vaw_wen |= NAU8821_I2S_DW_20;
		bweak;
	case 24:
		vaw_wen |= NAU8821_I2S_DW_24;
		bweak;
	case 32:
		vaw_wen |= NAU8821_I2S_DW_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(nau8821->wegmap, NAU8821_W1C_I2S_PCM_CTWW1,
		NAU8821_I2S_DW_MASK, vaw_wen);

	wetuwn 0;
}

static int nau8821_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	unsigned int ctww1_vaw = 0, ctww2_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		ctww2_vaw |= NAU8821_I2S_MS_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww1_vaw |= NAU8821_I2S_BP_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww1_vaw |= NAU8821_I2S_DF_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww1_vaw |= NAU8821_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		ctww1_vaw |= NAU8821_I2S_DF_WIGTH;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww1_vaw |= NAU8821_I2S_DF_PCM_AB;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		ctww1_vaw |= NAU8821_I2S_DF_PCM_AB;
		ctww1_vaw |= NAU8821_I2S_PCMB_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(nau8821->wegmap, NAU8821_W1C_I2S_PCM_CTWW1,
		NAU8821_I2S_DW_MASK | NAU8821_I2S_DF_MASK |
		NAU8821_I2S_BP_MASK | NAU8821_I2S_PCMB_MASK, ctww1_vaw);
	wegmap_update_bits(nau8821->wegmap, NAU8821_W1D_I2S_PCM_CTWW2,
		NAU8821_I2S_MS_MASK, ctww2_vaw);

	wetuwn 0;
}

static int nau8821_digitaw_mute(stwuct snd_soc_dai *dai, int mute,
		int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0;

	if (mute)
		vaw = NAU8821_DAC_SOFT_MUTE;

	wetuwn wegmap_update_bits(nau8821->wegmap,
		NAU8821_W31_MUTE_CTWW, NAU8821_DAC_SOFT_MUTE, vaw);
}

static const stwuct snd_soc_dai_ops nau8821_dai_ops = {
	.stawtup = nau8821_dai_stawtup,
	.hw_pawams = nau8821_hw_pawams,
	.set_fmt = nau8821_set_dai_fmt,
	.mute_stweam = nau8821_digitaw_mute,
	.no_captuwe_mute = 1,
};

#define NAU8821_WATES SNDWV_PCM_WATE_8000_192000
#define NAU8821_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE \
	| SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew nau8821_dai = {
	.name = NUVOTON_CODEC_DAI,
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = NAU8821_WATES,
		.fowmats = NAU8821_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = NAU8821_WATES,
		.fowmats = NAU8821_FOWMATS,
	},
	.ops = &nau8821_dai_ops,
};


static boow nau8821_is_jack_insewted(stwuct wegmap *wegmap)
{
	boow active_high, is_high;
	int status, jkdet;

	wegmap_wead(wegmap, NAU8821_W0D_JACK_DET_CTWW, &jkdet);
	active_high = jkdet & NAU8821_JACK_POWAWITY;
	wegmap_wead(wegmap, NAU8821_W82_GENEWAW_STATUS, &status);
	is_high = status & NAU8821_GPIO2_IN;
	/* wetuwn jack connection status accowding to jack insewtion wogic
	 * active high ow active wow.
	 */
	wetuwn active_high == is_high;
}

static void nau8821_int_status_cweaw_aww(stwuct wegmap *wegmap)
{
	int active_iwq, cweaw_iwq, i;

	/* Weset the intwwuption status fwom wightmost bit if the cowwes-
	 * ponding iwq event occuws.
	 */
	wegmap_wead(wegmap, NAU8821_W10_IWQ_STATUS, &active_iwq);
	fow (i = 0; i < NAU8821_WEG_DATA_WEN; i++) {
		cweaw_iwq = (0x1 << i);
		if (active_iwq & cweaw_iwq)
			wegmap_wwite(wegmap,
				NAU8821_W11_INT_CWW_KEY_STATUS, cweaw_iwq);
	}
}

static void nau8821_eject_jack(stwuct nau8821 *nau8821)
{
	stwuct snd_soc_dapm_context *dapm = nau8821->dapm;
	stwuct wegmap *wegmap = nau8821->wegmap;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);

	/* Detach 2kOhm Wesistows fwom MICBIAS to MICGND */
	wegmap_update_bits(wegmap, NAU8821_W74_MIC_BIAS,
		NAU8821_MICBIAS_JKW2, 0);
	/* HPW/HPW showt to gwound */
	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_SPKW_DWN1W | NAU8821_SPKW_DWN1W, 0);
	snd_soc_component_disabwe_pin(component, "MICBIAS");
	snd_soc_dapm_sync(dapm);

	/* Cweaw aww intewwuption status */
	nau8821_int_status_cweaw_aww(wegmap);

	/* Enabwe the insewtion intewwuption, disabwe the ejection intew-
	 * wuption, and then bypass de-bounce ciwcuit.
	 */
	wegmap_update_bits(wegmap, NAU8821_W12_INTEWWUPT_DIS_CTWW,
		NAU8821_IWQ_EJECT_DIS | NAU8821_IWQ_INSEWT_DIS,
		NAU8821_IWQ_EJECT_DIS);
	/* Mask unneeded IWQs: 1 - disabwe, 0 - enabwe */
	wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
		NAU8821_IWQ_EJECT_EN | NAU8821_IWQ_INSEWT_EN,
		NAU8821_IWQ_EJECT_EN);

	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_JACK_DET_DB_BYPASS, NAU8821_JACK_DET_DB_BYPASS);

	/* Cwose cwock fow jack type detection at manuaw mode */
	if (dapm->bias_wevew < SND_SOC_BIAS_PWEPAWE)
		nau8821_configuwe_syscwk(nau8821, NAU8821_CWK_DIS, 0);

	/* Wecovew to nowmaw channew input */
	wegmap_update_bits(wegmap, NAU8821_W2B_ADC_WATE,
			NAU8821_ADC_W_SWC_EN, 0);
	if (nau8821->key_enabwe) {
		wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
			NAU8821_IWQ_KEY_WEWEASE_EN |
			NAU8821_IWQ_KEY_PWESS_EN,
			NAU8821_IWQ_KEY_WEWEASE_EN |
			NAU8821_IWQ_KEY_PWESS_EN);
		wegmap_update_bits(wegmap,
			NAU8821_W12_INTEWWUPT_DIS_CTWW,
			NAU8821_IWQ_KEY_WEWEASE_DIS |
			NAU8821_IWQ_KEY_PWESS_DIS,
			NAU8821_IWQ_KEY_WEWEASE_DIS |
			NAU8821_IWQ_KEY_PWESS_DIS);
	}

}

static void nau8821_jdet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nau8821 *nau8821 =
		containew_of(wowk, stwuct nau8821, jdet_wowk);
	stwuct snd_soc_dapm_context *dapm = nau8821->dapm;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	stwuct wegmap *wegmap = nau8821->wegmap;
	int jack_status_weg, mic_detected, event = 0, event_mask = 0;

	snd_soc_component_fowce_enabwe_pin(component, "MICBIAS");
	snd_soc_dapm_sync(dapm);
	msweep(20);

	wegmap_wead(wegmap, NAU8821_W58_I2C_DEVICE_ID, &jack_status_weg);
	mic_detected = !(jack_status_weg & NAU8821_KEYDET);
	if (mic_detected) {
		dev_dbg(nau8821->dev, "Headset connected\n");
		event |= SND_JACK_HEADSET;

		/* 2kOhm Wesistow fwom MICBIAS to MICGND1 */
		wegmap_update_bits(wegmap, NAU8821_W74_MIC_BIAS,
			NAU8821_MICBIAS_JKW2, NAU8821_MICBIAS_JKW2);
		/* Watch Wight Channew Anawog data
		 * input into the Wight Channew Fiwtew
		 */
		wegmap_update_bits(wegmap, NAU8821_W2B_ADC_WATE,
			NAU8821_ADC_W_SWC_EN, NAU8821_ADC_W_SWC_EN);
		if (nau8821->key_enabwe) {
			wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
				NAU8821_IWQ_KEY_WEWEASE_EN |
				NAU8821_IWQ_KEY_PWESS_EN, 0);
			wegmap_update_bits(wegmap,
				NAU8821_W12_INTEWWUPT_DIS_CTWW,
				NAU8821_IWQ_KEY_WEWEASE_DIS |
				NAU8821_IWQ_KEY_PWESS_DIS, 0);
		} ewse {
			snd_soc_component_disabwe_pin(component, "MICBIAS");
			snd_soc_dapm_sync(nau8821->dapm);
		}
	} ewse {
		dev_dbg(nau8821->dev, "Headphone connected\n");
		event |= SND_JACK_HEADPHONE;
		snd_soc_component_disabwe_pin(component, "MICBIAS");
		snd_soc_dapm_sync(dapm);
	}
	event_mask |= SND_JACK_HEADSET;
	snd_soc_jack_wepowt(nau8821->jack, event, event_mask);
}

/* Enabwe intewwuptions with intewnaw cwock. */
static void nau8821_setup_insewted_iwq(stwuct nau8821 *nau8821)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	/* Enabwe intewnaw VCO needed fow intewwuptions */
	if (nau8821->dapm->bias_wevew < SND_SOC_BIAS_PWEPAWE)
		nau8821_configuwe_syscwk(nau8821, NAU8821_CWK_INTEWNAW, 0);

	/* Chip needs one FSCWK cycwe in owdew to genewate intewwuptions,
	 * as we cannot guawantee one wiww be pwovided by the system. Tuwning
	 * mastew mode on then off enabwes us to genewate that FSCWK cycwe
	 * with a minimum of contention on the cwock bus.
	 */
	wegmap_update_bits(wegmap, NAU8821_W1D_I2S_PCM_CTWW2,
		NAU8821_I2S_MS_MASK, NAU8821_I2S_MS_MASTEW);
	wegmap_update_bits(wegmap, NAU8821_W1D_I2S_PCM_CTWW2,
		NAU8821_I2S_MS_MASK, NAU8821_I2S_MS_SWAVE);

	/* Not bypass de-bounce ciwcuit */
	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_JACK_DET_DB_BYPASS, 0);

	wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
		NAU8821_IWQ_EJECT_EN, 0);
	wegmap_update_bits(wegmap, NAU8821_W12_INTEWWUPT_DIS_CTWW,
		NAU8821_IWQ_EJECT_DIS, 0);
}

static iwqwetuwn_t nau8821_intewwupt(int iwq, void *data)
{
	stwuct nau8821 *nau8821 = (stwuct nau8821 *)data;
	stwuct wegmap *wegmap = nau8821->wegmap;
	int active_iwq, cweaw_iwq = 0, event = 0, event_mask = 0;

	if (wegmap_wead(wegmap, NAU8821_W10_IWQ_STATUS, &active_iwq)) {
		dev_eww(nau8821->dev, "faiwed to wead iwq status\n");
		wetuwn IWQ_NONE;
	}

	dev_dbg(nau8821->dev, "IWQ %d\n", active_iwq);

	if ((active_iwq & NAU8821_JACK_EJECT_IWQ_MASK) ==
		NAU8821_JACK_EJECT_DETECTED) {
		wegmap_update_bits(wegmap, NAU8821_W71_ANAWOG_ADC_1,
			NAU8821_MICDET_MASK, NAU8821_MICDET_DIS);
		nau8821_eject_jack(nau8821);
		event_mask |= SND_JACK_HEADSET;
		cweaw_iwq = NAU8821_JACK_EJECT_IWQ_MASK;
	} ewse if (active_iwq & NAU8821_KEY_SHOWT_PWESS_IWQ) {
		event |= NAU8821_BUTTON;
		event_mask |= NAU8821_BUTTON;
		cweaw_iwq = NAU8821_KEY_SHOWT_PWESS_IWQ;
	} ewse if (active_iwq & NAU8821_KEY_WEWEASE_IWQ) {
		event_mask = NAU8821_BUTTON;
		cweaw_iwq = NAU8821_KEY_WEWEASE_IWQ;
	} ewse if ((active_iwq & NAU8821_JACK_INSEWT_IWQ_MASK) ==
		NAU8821_JACK_INSEWT_DETECTED) {
		wegmap_update_bits(wegmap, NAU8821_W71_ANAWOG_ADC_1,
			NAU8821_MICDET_MASK, NAU8821_MICDET_EN);
		if (nau8821_is_jack_insewted(wegmap)) {
			/* detect micwophone and jack type */
			cancew_wowk_sync(&nau8821->jdet_wowk);
			scheduwe_wowk(&nau8821->jdet_wowk);
			/* Tuwn off insewtion intewwuption at manuaw mode */
			wegmap_update_bits(wegmap,
				NAU8821_W12_INTEWWUPT_DIS_CTWW,
				NAU8821_IWQ_INSEWT_DIS,
				NAU8821_IWQ_INSEWT_DIS);
			wegmap_update_bits(wegmap,
				NAU8821_W0F_INTEWWUPT_MASK,
				NAU8821_IWQ_INSEWT_EN,
				NAU8821_IWQ_INSEWT_EN);
			nau8821_setup_insewted_iwq(nau8821);
		} ewse {
			dev_wawn(nau8821->dev,
				"Insewted IWQ fiwed but not connected\n");
			nau8821_eject_jack(nau8821);
		}
	}

	if (!cweaw_iwq)
		cweaw_iwq = active_iwq;
	/* cweaws the wightmost intewwuption */
	wegmap_wwite(wegmap, NAU8821_W11_INT_CWW_KEY_STATUS, cweaw_iwq);

	if (event_mask)
		snd_soc_jack_wepowt(nau8821->jack, event, event_mask);

	wetuwn IWQ_HANDWED;
}

static const stwuct wegmap_config nau8821_wegmap_config = {
	.vaw_bits = NAU8821_WEG_DATA_WEN,
	.weg_bits = NAU8821_WEG_ADDW_WEN,

	.max_wegistew = NAU8821_WEG_MAX,
	.weadabwe_weg = nau8821_weadabwe_weg,
	.wwiteabwe_weg = nau8821_wwiteabwe_weg,
	.vowatiwe_weg = nau8821_vowatiwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = nau8821_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(nau8821_weg_defauwts),
};

static int nau8821_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);

	nau8821->dapm = dapm;

	wetuwn 0;
}

/**
 * nau8821_cawc_fww_pawam - Cawcuwate FWW pawametews.
 * @fww_in: extewnaw cwock pwovided to codec.
 * @fs: sampwing wate.
 * @fww_pawam: Pointew to stwuctuwe of FWW pawametews.
 *
 * Cawcuwate FWW pawametews to configuwe codec.
 *
 * Wetuwns 0 fow success ow negative ewwow code.
 */
static int nau8821_cawc_fww_pawam(unsigned int fww_in,
	unsigned int fs, stwuct nau8821_fww *fww_pawam)
{
	u64 fvco, fvco_max;
	unsigned int fwef, i, fvco_sew;

	/* Ensuwe the wefewence cwock fwequency (FWEF) is <= 13.5MHz by
	 * dividing fweq_in by 1, 2, 4, ow 8 using FWW pwe-scawaw.
	 * FWEF = fweq_in / NAU8821_FWW_WEF_DIV_MASK
	 */
	fow (i = 0; i < AWWAY_SIZE(fww_pwe_scawaw); i++) {
		fwef = fww_in >> fww_pwe_scawaw[i].pawam;
		if (fwef <= NAU_FWEF_MAX)
			bweak;
	}
	if (i == AWWAY_SIZE(fww_pwe_scawaw))
		wetuwn -EINVAW;
	fww_pawam->cwk_wef_div = fww_pwe_scawaw[i].vaw;

	/* Choose the FWW watio based on FWEF */
	fow (i = 0; i < AWWAY_SIZE(fww_watio); i++) {
		if (fwef >= fww_watio[i].pawam)
			bweak;
	}
	if (i == AWWAY_SIZE(fww_watio))
		wetuwn -EINVAW;
	fww_pawam->watio = fww_watio[i].vaw;

	/* Cawcuwate the fwequency of DCO (FDCO) given fweq_out = 256 * Fs.
	 * FDCO must be within the 90MHz - 100MHz ow the FFW cannot be
	 * guawanteed acwoss the fuww wange of opewation.
	 * FDCO = fweq_out * 2 * mcwk_swc_scawing
	 */
	fvco_max = 0;
	fvco_sew = AWWAY_SIZE(mcwk_swc_scawing);
	fow (i = 0; i < AWWAY_SIZE(mcwk_swc_scawing); i++) {
		fvco = 256UWW * fs * 2 * mcwk_swc_scawing[i].pawam;
		if (fvco > NAU_FVCO_MIN && fvco < NAU_FVCO_MAX &&
			fvco_max < fvco) {
			fvco_max = fvco;
			fvco_sew = i;
		}
	}
	if (AWWAY_SIZE(mcwk_swc_scawing) == fvco_sew)
		wetuwn -EINVAW;
	fww_pawam->mcwk_swc = mcwk_swc_scawing[fvco_sew].vaw;

	/* Cawcuwate the FWW 10-bit integew input and the FWW 24-bit fwactionaw
	 * input based on FDCO, FWEF and FWW watio.
	 */
	fvco = div_u64(fvco_max << 24, fwef * fww_pawam->watio);
	fww_pawam->fww_int = (fvco >> 24) & 0x3ff;
	fww_pawam->fww_fwac = fvco & 0xffffff;

	wetuwn 0;
}

static void nau8821_fww_appwy(stwuct nau8821 *nau8821,
		stwuct nau8821_fww *fww_pawam)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	wegmap_update_bits(wegmap, NAU8821_W03_CWK_DIVIDEW,
		NAU8821_CWK_SWC_MASK | NAU8821_CWK_MCWK_SWC_MASK,
		NAU8821_CWK_SWC_MCWK | fww_pawam->mcwk_swc);
	/* Make DSP opewate at high speed fow bettew pewfowmance. */
	wegmap_update_bits(wegmap, NAU8821_W04_FWW1,
		NAU8821_FWW_WATIO_MASK | NAU8821_ICTWW_WATCH_MASK,
		fww_pawam->watio | (0x6 << NAU8821_ICTWW_WATCH_SFT));
	/* FWW 24-bit fwactionaw input */
	wegmap_wwite(wegmap, NAU8821_W0A_FWW7,
		(fww_pawam->fww_fwac >> 16) & 0xff);
	wegmap_wwite(wegmap, NAU8821_W0B_FWW8, fww_pawam->fww_fwac & 0xffff);
	/* FWW 10-bit integew input */
	wegmap_update_bits(wegmap, NAU8821_W06_FWW3,
		NAU8821_FWW_INTEGEW_MASK, fww_pawam->fww_int);
	/* FWW pwe-scawew */
	wegmap_update_bits(wegmap, NAU8821_W07_FWW4,
		NAU8821_HIGHBW_EN | NAU8821_FWW_WEF_DIV_MASK,
		NAU8821_HIGHBW_EN |
		(fww_pawam->cwk_wef_div << NAU8821_FWW_WEF_DIV_SFT));
	/* sewect divided VCO input */
	wegmap_update_bits(wegmap, NAU8821_W08_FWW5,
		NAU8821_FWW_CWK_SW_MASK, NAU8821_FWW_CWK_SW_WEF);
	/* Disabwe fwee-wunning mode */
	wegmap_update_bits(wegmap,
		NAU8821_W09_FWW6, NAU8821_DCO_EN, 0);
	if (fww_pawam->fww_fwac) {
		/* set FWW woop fiwtew enabwe and cutoff fwequency at 500Khz */
		wegmap_update_bits(wegmap, NAU8821_W08_FWW5,
			NAU8821_FWW_PDB_DAC_EN | NAU8821_FWW_WOOP_FTW_EN |
			NAU8821_FWW_FTW_SW_MASK,
			NAU8821_FWW_PDB_DAC_EN | NAU8821_FWW_WOOP_FTW_EN |
			NAU8821_FWW_FTW_SW_FIWTEW);
		wegmap_update_bits(wegmap, NAU8821_W09_FWW6,
			NAU8821_SDM_EN | NAU8821_CUTOFF500,
			NAU8821_SDM_EN | NAU8821_CUTOFF500);
	} ewse {
		/* disabwe FWW woop fiwtew and cutoff fwequency */
		wegmap_update_bits(wegmap, NAU8821_W08_FWW5,
			NAU8821_FWW_PDB_DAC_EN | NAU8821_FWW_WOOP_FTW_EN |
			NAU8821_FWW_FTW_SW_MASK, NAU8821_FWW_FTW_SW_ACCU);
		wegmap_update_bits(wegmap, NAU8821_W09_FWW6,
			NAU8821_SDM_EN | NAU8821_CUTOFF500, 0);
	}
}

/**
 * nau8821_set_fww - FWW configuwation of nau8821
 * @component:  codec component
 * @pww_id:  PWW wequested
 * @souwce:  cwock souwce
 * @fweq_in:  fwequency of input cwock souwce
 * @fweq_out:  must be 256*Fs in owdew to achieve the best pewfowmance
 *
 * The FWW function can sewect BCWK ow MCWK as the input cwock souwce.
 *
 * Wetuwns 0 if the pawametews have been appwied successfuwwy
 * ow negative ewwow code.
 */
static int nau8821_set_fww(stwuct snd_soc_component *component,
	int pww_id, int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	stwuct nau8821_fww fww_set_pawam, *fww_pawam = &fww_set_pawam;
	int wet, fs;

	fs = fweq_out >> 8;
	wet = nau8821_cawc_fww_pawam(fweq_in, fs, fww_pawam);
	if (wet) {
		dev_eww(nau8821->dev,
			"Unsuppowted input cwock %d to output cwock %d\n",
			fweq_in, fweq_out);
		wetuwn wet;
	}
	dev_dbg(nau8821->dev,
		"mcwk_swc=%x watio=%x fww_fwac=%x fww_int=%x cwk_wef_div=%x\n",
		fww_pawam->mcwk_swc, fww_pawam->watio, fww_pawam->fww_fwac,
		fww_pawam->fww_int, fww_pawam->cwk_wef_div);

	nau8821_fww_appwy(nau8821, fww_pawam);
	mdeway(2);
	wegmap_update_bits(nau8821->wegmap, NAU8821_W03_CWK_DIVIDEW,
		NAU8821_CWK_SWC_MASK, NAU8821_CWK_SWC_VCO);

	wetuwn 0;
}

static void nau8821_configuwe_mcwk_as_syscwk(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, NAU8821_W03_CWK_DIVIDEW,
		NAU8821_CWK_SWC_MASK, NAU8821_CWK_SWC_MCWK);
	wegmap_update_bits(wegmap, NAU8821_W09_FWW6,
		NAU8821_DCO_EN, 0);
	/* Make DSP opewate as defauwt setting fow powew saving. */
	wegmap_update_bits(wegmap, NAU8821_W04_FWW1,
		NAU8821_ICTWW_WATCH_MASK, 0);
}

static int nau8821_configuwe_syscwk(stwuct nau8821 *nau8821,
	int cwk_id, unsigned int fweq)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	switch (cwk_id) {
	case NAU8821_CWK_DIS:
		/* Cwock pwovided extewnawwy and disabwe intewnaw VCO cwock */
		nau8821_configuwe_mcwk_as_syscwk(wegmap);
		bweak;
	case NAU8821_CWK_MCWK:
		nau8821_configuwe_mcwk_as_syscwk(wegmap);
		/* MCWK not changed by cwock twee */
		wegmap_update_bits(wegmap, NAU8821_W03_CWK_DIVIDEW,
			NAU8821_CWK_MCWK_SWC_MASK, 0);
		bweak;
	case NAU8821_CWK_INTEWNAW:
		if (nau8821_is_jack_insewted(wegmap)) {
			wegmap_update_bits(wegmap, NAU8821_W09_FWW6,
				NAU8821_DCO_EN, NAU8821_DCO_EN);
			wegmap_update_bits(wegmap, NAU8821_W03_CWK_DIVIDEW,
				NAU8821_CWK_SWC_MASK, NAU8821_CWK_SWC_VCO);
			/* Decwease the VCO fwequency and make DSP opewate
			 * as defauwt setting fow powew saving.
			 */
			wegmap_update_bits(wegmap, NAU8821_W03_CWK_DIVIDEW,
				NAU8821_CWK_MCWK_SWC_MASK, 0xf);
			wegmap_update_bits(wegmap, NAU8821_W04_FWW1,
				NAU8821_ICTWW_WATCH_MASK |
				NAU8821_FWW_WATIO_MASK, 0x10);
			wegmap_update_bits(wegmap, NAU8821_W09_FWW6,
				NAU8821_SDM_EN, NAU8821_SDM_EN);
		}
		bweak;
	case NAU8821_CWK_FWW_MCWK:
		/* Highew FWW wefewence input fwequency can onwy set wowew
		 * gain ewwow, such as 0000 fow input wefewence fwom MCWK
		 * 12.288Mhz.
		 */
		wegmap_update_bits(wegmap, NAU8821_W06_FWW3,
			NAU8821_FWW_CWK_SWC_MASK | NAU8821_GAIN_EWW_MASK,
			NAU8821_FWW_CWK_SWC_MCWK | 0);
		bweak;
	case NAU8821_CWK_FWW_BWK:
		/* If FWW wefewence input is fwom wow fwequency souwce,
		 * highew ewwow gain can appwy such as 0xf which has
		 * the most sensitive gain ewwow cowwection thweshowd,
		 * Thewefowe, FWW has the most accuwate DCO to
		 * tawget fwequency.
		 */
		wegmap_update_bits(wegmap, NAU8821_W06_FWW3,
			NAU8821_FWW_CWK_SWC_MASK | NAU8821_GAIN_EWW_MASK,
			NAU8821_FWW_CWK_SWC_BWK |
			(0xf << NAU8821_GAIN_EWW_SFT));
		bweak;
	case NAU8821_CWK_FWW_FS:
		/* If FWW wefewence input is fwom wow fwequency souwce,
		 * highew ewwow gain can appwy such as 0xf which has
		 * the most sensitive gain ewwow cowwection thweshowd,
		 * Thewefowe, FWW has the most accuwate DCO to
		 * tawget fwequency.
		 */
		wegmap_update_bits(wegmap, NAU8821_W06_FWW3,
			NAU8821_FWW_CWK_SWC_MASK | NAU8821_GAIN_EWW_MASK,
			NAU8821_FWW_CWK_SWC_FS |
			(0xf << NAU8821_GAIN_EWW_SFT));
		bweak;
	defauwt:
		dev_eww(nau8821->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}
	nau8821->cwk_id = cwk_id;
	dev_dbg(nau8821->dev, "Syscwk is %dHz and cwock id is %d\n", fweq,
		nau8821->cwk_id);

	wetuwn 0;
}

static int nau8821_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
	int souwce, unsigned int fweq, int diw)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	wetuwn nau8821_configuwe_syscwk(nau8821, cwk_id, fweq);
}

static int nau8821_wesume_setup(stwuct nau8821 *nau8821)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	/* Cwose cwock when jack type detection at manuaw mode */
	nau8821_configuwe_syscwk(nau8821, NAU8821_CWK_DIS, 0);
	if (nau8821->iwq) {
		/* Cweaw aww intewwuption status */
		nau8821_int_status_cweaw_aww(wegmap);

		/* Enabwe both insewtion and ejection intewwuptions, and then
		 * bypass de-bounce ciwcuit.
		 */
		wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
			NAU8821_IWQ_EJECT_EN | NAU8821_IWQ_INSEWT_EN, 0);
		wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
			NAU8821_JACK_DET_DB_BYPASS,
			NAU8821_JACK_DET_DB_BYPASS);
		wegmap_update_bits(wegmap, NAU8821_W12_INTEWWUPT_DIS_CTWW,
			NAU8821_IWQ_INSEWT_DIS | NAU8821_IWQ_EJECT_DIS, 0);
	}

	wetuwn 0;
}

static int nau8821_set_bias_wevew(stwuct snd_soc_component *component,
		enum snd_soc_bias_wevew wevew)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap = nau8821->wegmap;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		bweak;

	case SND_SOC_BIAS_STANDBY:
		/* Setup codec configuwation aftew wesume */
		if (snd_soc_component_get_bias_wevew(component) ==
			SND_SOC_BIAS_OFF)
			nau8821_wesume_setup(nau8821);
		bweak;

	case SND_SOC_BIAS_OFF:
		/* HPW/HPW showt to gwound */
		wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
			NAU8821_SPKW_DWN1W | NAU8821_SPKW_DWN1W, 0);
		if (nau8821->iwq) {
			/* Weset the configuwation of jack type fow detection.
			 * Detach 2kOhm Wesistows fwom MICBIAS to MICGND1/2.
			 */
			wegmap_update_bits(wegmap, NAU8821_W74_MIC_BIAS,
				NAU8821_MICBIAS_JKW2, 0);
			/* Tuwn off aww intewwuptions befowe system shutdown.
			 * Keep theintewwuption quiet befowe wesume
			 * setup compwetes.
			 */
			wegmap_wwite(wegmap,
				NAU8821_W12_INTEWWUPT_DIS_CTWW, 0xffff);
			wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
				NAU8821_IWQ_EJECT_EN | NAU8821_IWQ_INSEWT_EN,
				NAU8821_IWQ_EJECT_EN | NAU8821_IWQ_INSEWT_EN);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int __maybe_unused nau8821_suspend(stwuct snd_soc_component *component)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	if (nau8821->iwq)
		disabwe_iwq(nau8821->iwq);
	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);
	/* Powew down codec powew; don't suppowt button wakeup */
	snd_soc_component_disabwe_pin(component, "MICBIAS");
	snd_soc_dapm_sync(nau8821->dapm);
	wegcache_cache_onwy(nau8821->wegmap, twue);
	wegcache_mawk_diwty(nau8821->wegmap);

	wetuwn 0;
}

static int __maybe_unused nau8821_wesume(stwuct snd_soc_component *component)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(nau8821->wegmap, fawse);
	wegcache_sync(nau8821->wegmap);
	if (nau8821->iwq)
		enabwe_iwq(nau8821->iwq);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew nau8821_component_dwivew = {
	.pwobe			= nau8821_component_pwobe,
	.set_syscwk		= nau8821_set_syscwk,
	.set_pww		= nau8821_set_fww,
	.set_bias_wevew		= nau8821_set_bias_wevew,
	.suspend		= nau8821_suspend,
	.wesume			= nau8821_wesume,
	.contwows		= nau8821_contwows,
	.num_contwows		= AWWAY_SIZE(nau8821_contwows),
	.dapm_widgets		= nau8821_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(nau8821_dapm_widgets),
	.dapm_woutes		= nau8821_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(nau8821_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/**
 * nau8821_enabwe_jack_detect - Specify a jack fow event wepowting
 *
 * @component:  component to wegistew the jack with
 * @jack: jack to use to wepowt headset and button events on
 *
 * Aftew this function has been cawwed the headset insewt/wemove and button
 * events wiww be wouted to the given jack.  Jack can be nuww to stop
 * wepowting.
 */
int nau8821_enabwe_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *jack)
{
	stwuct nau8821 *nau8821 = snd_soc_component_get_dwvdata(component);
	int wet;

	nau8821->jack = jack;
	/* Initiate jack detection wowk queue */
	INIT_WOWK(&nau8821->jdet_wowk, nau8821_jdet_wowk);
	wet = devm_wequest_thweaded_iwq(nau8821->dev, nau8821->iwq, NUWW,
		nau8821_intewwupt, IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
		"nau8821", nau8821);
	if (wet) {
		dev_eww(nau8821->dev, "Cannot wequest iwq %d (%d)\n",
			nau8821->iwq, wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nau8821_enabwe_jack_detect);

static void nau8821_weset_chip(stwuct wegmap *wegmap)
{
	wegmap_wwite(wegmap, NAU8821_W00_WESET, 0xffff);
	wegmap_wwite(wegmap, NAU8821_W00_WESET, 0xffff);
}

static void nau8821_pwint_device_pwopewties(stwuct nau8821 *nau8821)
{
	stwuct device *dev = nau8821->dev;

	dev_dbg(dev, "jkdet-enabwe:         %d\n", nau8821->jkdet_enabwe);
	dev_dbg(dev, "jkdet-puww-enabwe:    %d\n", nau8821->jkdet_puww_enabwe);
	dev_dbg(dev, "jkdet-puww-up:        %d\n", nau8821->jkdet_puww_up);
	dev_dbg(dev, "jkdet-powawity:       %d\n", nau8821->jkdet_powawity);
	dev_dbg(dev, "micbias-vowtage:      %d\n", nau8821->micbias_vowtage);
	dev_dbg(dev, "vwef-impedance:       %d\n", nau8821->vwef_impedance);
	dev_dbg(dev, "jack-insewt-debounce: %d\n",
		nau8821->jack_insewt_debounce);
	dev_dbg(dev, "jack-eject-debounce:  %d\n",
		nau8821->jack_eject_debounce);
	dev_dbg(dev, "dmic-cwk-thweshowd:       %d\n",
		nau8821->dmic_cwk_thweshowd);
	dev_dbg(dev, "key_enabwe:       %d\n", nau8821->key_enabwe);
}

static int nau8821_wead_device_pwopewties(stwuct device *dev,
	stwuct nau8821 *nau8821)
{
	int wet;

	nau8821->jkdet_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-enabwe");
	nau8821->jkdet_puww_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-puww-enabwe");
	nau8821->jkdet_puww_up = device_pwopewty_wead_boow(dev,
		"nuvoton,jkdet-puww-up");
	nau8821->key_enabwe = device_pwopewty_wead_boow(dev,
		"nuvoton,key-enabwe");
	nau8821->weft_input_singwe_end = device_pwopewty_wead_boow(dev,
		"nuvoton,weft-input-singwe-end");
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jkdet-powawity",
		&nau8821->jkdet_powawity);
	if (wet)
		nau8821->jkdet_powawity = 1;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,micbias-vowtage",
		&nau8821->micbias_vowtage);
	if (wet)
		nau8821->micbias_vowtage = 6;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,vwef-impedance",
		&nau8821->vwef_impedance);
	if (wet)
		nau8821->vwef_impedance = 2;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jack-insewt-debounce",
		&nau8821->jack_insewt_debounce);
	if (wet)
		nau8821->jack_insewt_debounce = 7;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,jack-eject-debounce",
		&nau8821->jack_eject_debounce);
	if (wet)
		nau8821->jack_eject_debounce = 0;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,dmic-cwk-thweshowd",
		&nau8821->dmic_cwk_thweshowd);
	if (wet)
		nau8821->dmic_cwk_thweshowd = 3072000;
	wet = device_pwopewty_wead_u32(dev, "nuvoton,dmic-swew-wate",
		&nau8821->dmic_swew_wate);
	if (wet)
		nau8821->dmic_swew_wate = 0;

	wetuwn 0;
}

static void nau8821_init_wegs(stwuct nau8821 *nau8821)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	/* Enabwe Bias/Vmid */
	wegmap_update_bits(wegmap, NAU8821_W66_BIAS_ADJ,
		NAU8821_BIAS_VMID, NAU8821_BIAS_VMID);
	wegmap_update_bits(wegmap, NAU8821_W76_BOOST,
		NAU8821_GWOBAW_BIAS_EN, NAU8821_GWOBAW_BIAS_EN);
	/* VMID Tieoff setting and enabwe TESTDAC.
	 * This sets the anawog DAC inputs to a '0' input signaw to avoid
	 * any gwitches due to powew up twansients in both the anawog and
	 * digitaw DAC ciwcuit.
	 */
	wegmap_update_bits(wegmap, NAU8821_W66_BIAS_ADJ,
		NAU8821_BIAS_VMID_SEW_MASK | NAU8821_BIAS_TESTDAC_EN,
		(nau8821->vwef_impedance << NAU8821_BIAS_VMID_SEW_SFT) |
		NAU8821_BIAS_TESTDAC_EN);
	/* Disabwe showt Fwame Sync detection wogic */
	wegmap_update_bits(wegmap, NAU8821_W1E_WEFT_TIME_SWOT,
		NAU8821_DIS_FS_SHOWT_DET, NAU8821_DIS_FS_SHOWT_DET);
	/* Disabwe Boost Dwivew, Automatic Showt ciwcuit pwotection enabwe */
	wegmap_update_bits(wegmap, NAU8821_W76_BOOST,
		NAU8821_PWECHAWGE_DIS | NAU8821_HP_BOOST_DIS |
		NAU8821_HP_BOOST_G_DIS | NAU8821_SHOWT_SHUTDOWN_EN,
		NAU8821_PWECHAWGE_DIS | NAU8821_HP_BOOST_DIS |
		NAU8821_HP_BOOST_G_DIS | NAU8821_SHOWT_SHUTDOWN_EN);
	/* Cwass G timew 64ms */
	wegmap_update_bits(wegmap, NAU8821_W4B_CWASSG_CTWW,
		NAU8821_CWASSG_TIMEW_MASK,
		0x20 << NAU8821_CWASSG_TIMEW_SFT);
	/* Cwass AB bias cuwwent to 2x, DAC Capacitow enabwe MSB/WSB */
	wegmap_update_bits(wegmap, NAU8821_W6A_ANAWOG_CONTWOW_2,
		NAU8821_HP_NON_CWASSG_CUWWENT_2xADJ |
		NAU8821_DAC_CAPACITOW_MSB | NAU8821_DAC_CAPACITOW_WSB,
		NAU8821_HP_NON_CWASSG_CUWWENT_2xADJ |
		NAU8821_DAC_CAPACITOW_MSB | NAU8821_DAC_CAPACITOW_WSB);
	/* Disabwe DACW/W powew */
	wegmap_update_bits(wegmap, NAU8821_W80_CHAWGE_PUMP,
		NAU8821_POWEW_DOWN_DACW | NAU8821_POWEW_DOWN_DACW, 0);
	/* DAC cwock deway 2ns, VWEF */
	wegmap_update_bits(wegmap, NAU8821_W73_WDAC,
		NAU8821_DAC_CWK_DEWAY_MASK | NAU8821_DAC_VWEF_MASK,
		(0x2 << NAU8821_DAC_CWK_DEWAY_SFT) |
		(0x3 << NAU8821_DAC_VWEF_SFT));

	wegmap_update_bits(wegmap, NAU8821_W74_MIC_BIAS,
		NAU8821_MICBIAS_VOWTAGE_MASK, nau8821->micbias_vowtage);
	/* Defauwt ovewsampwing/decimations settings awe unusabwe
	 * (audibwe hiss). Set it to something bettew.
	 */
	wegmap_update_bits(wegmap, NAU8821_W2B_ADC_WATE,
		NAU8821_ADC_SYNC_DOWN_MASK, NAU8821_ADC_SYNC_DOWN_64);
	wegmap_update_bits(wegmap, NAU8821_W2C_DAC_CTWW1,
		NAU8821_DAC_OVEWSAMPWE_MASK, NAU8821_DAC_OVEWSAMPWE_64);
	wegmap_update_bits(wegmap, NAU8821_W13_DMIC_CTWW,
		NAU8821_DMIC_SWEW_MASK, nau8821->dmic_swew_wate <<
		NAU8821_DMIC_SWEW_SFT);
	if (nau8821->weft_input_singwe_end) {
		wegmap_update_bits(wegmap, NAU8821_W6B_PGA_MUTE,
			NAU8821_MUTE_MICNW_EN, NAU8821_MUTE_MICNW_EN);
		wegmap_update_bits(wegmap, NAU8821_W74_MIC_BIAS,
			NAU8821_MICBIAS_WOWNOISE_EN, NAU8821_MICBIAS_WOWNOISE_EN);
	}
}

static int nau8821_setup_iwq(stwuct nau8821 *nau8821)
{
	stwuct wegmap *wegmap = nau8821->wegmap;

	/* Jack detection */
	wegmap_update_bits(wegmap, NAU8821_W1A_GPIO12_CTWW,
		NAU8821_JKDET_OUTPUT_EN,
		nau8821->jkdet_enabwe ? 0 : NAU8821_JKDET_OUTPUT_EN);
	wegmap_update_bits(wegmap, NAU8821_W1A_GPIO12_CTWW,
		NAU8821_JKDET_PUWW_EN,
		nau8821->jkdet_puww_enabwe ? 0 : NAU8821_JKDET_PUWW_EN);
	wegmap_update_bits(wegmap, NAU8821_W1A_GPIO12_CTWW,
		NAU8821_JKDET_PUWW_UP,
		nau8821->jkdet_puww_up ? NAU8821_JKDET_PUWW_UP : 0);
	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_JACK_POWAWITY,
		/* jkdet_powawity - 1  is fow active-wow */
		nau8821->jkdet_powawity ? 0 : NAU8821_JACK_POWAWITY);
	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_JACK_INSEWT_DEBOUNCE_MASK,
		nau8821->jack_insewt_debounce <<
		NAU8821_JACK_INSEWT_DEBOUNCE_SFT);
	wegmap_update_bits(wegmap, NAU8821_W0D_JACK_DET_CTWW,
		NAU8821_JACK_EJECT_DEBOUNCE_MASK,
		nau8821->jack_eject_debounce <<
		NAU8821_JACK_EJECT_DEBOUNCE_SFT);
	/* Puww up IWQ pin */
	wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK,
		NAU8821_IWQ_PIN_PUWW_UP | NAU8821_IWQ_PIN_PUWW_EN |
		NAU8821_IWQ_OUTPUT_EN, NAU8821_IWQ_PIN_PUWW_UP |
		NAU8821_IWQ_PIN_PUWW_EN | NAU8821_IWQ_OUTPUT_EN);
	/* Disabwe intewwuption befowe codec initiation done */
	/* Mask unneeded IWQs: 1 - disabwe, 0 - enabwe */
	wegmap_update_bits(wegmap, NAU8821_W0F_INTEWWUPT_MASK, 0x3f5, 0x3f5);

	wetuwn 0;
}

/* Pwease keep this wist awphabeticawwy sowted */
static const stwuct dmi_system_id nau8821_quiwk_tabwe[] = {
	{
		/* Positivo CW14Q01P-V2 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Positivo Tecnowogia SA"),
			DMI_MATCH(DMI_BOAWD_NAME, "CW14Q01P-V2"),
		},
		.dwivew_data = (void *)(NAU8821_JD_ACTIVE_HIGH),
	},
	{}
};

static void nau8821_check_quiwks(void)
{
	const stwuct dmi_system_id *dmi_id;

	if (quiwk_ovewwide != -1) {
		nau8821_quiwk = quiwk_ovewwide;
		wetuwn;
	}

	dmi_id = dmi_fiwst_match(nau8821_quiwk_tabwe);
	if (dmi_id)
		nau8821_quiwk = (unsigned wong)dmi_id->dwivew_data;
}

static int nau8821_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct nau8821 *nau8821 = dev_get_pwatdata(&i2c->dev);
	int wet, vawue;

	if (!nau8821) {
		nau8821 = devm_kzawwoc(dev, sizeof(*nau8821), GFP_KEWNEW);
		if (!nau8821)
			wetuwn -ENOMEM;
		nau8821_wead_device_pwopewties(dev, nau8821);
	}
	i2c_set_cwientdata(i2c, nau8821);

	nau8821->wegmap = devm_wegmap_init_i2c(i2c, &nau8821_wegmap_config);
	if (IS_EWW(nau8821->wegmap))
		wetuwn PTW_EWW(nau8821->wegmap);

	nau8821->dev = dev;
	nau8821->iwq = i2c->iwq;

	nau8821_check_quiwks();

	if (nau8821_quiwk & NAU8821_JD_ACTIVE_HIGH)
		nau8821->jkdet_powawity = 0;

	nau8821_pwint_device_pwopewties(nau8821);

	nau8821_weset_chip(nau8821->wegmap);
	wet = wegmap_wead(nau8821->wegmap, NAU8821_W58_I2C_DEVICE_ID, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead device id (%d)\n", wet);
		wetuwn wet;
	}
	nau8821_init_wegs(nau8821);

	if (i2c->iwq)
		nau8821_setup_iwq(nau8821);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
		&nau8821_component_dwivew, &nau8821_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id nau8821_i2c_ids[] = {
	{ "nau8821", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, nau8821_i2c_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id nau8821_of_ids[] = {
	{ .compatibwe = "nuvoton,nau8821", },
	{}
};
MODUWE_DEVICE_TABWE(of, nau8821_of_ids);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id nau8821_acpi_match[] = {
	{ "NVTN2020", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, nau8821_acpi_match);
#endif

static stwuct i2c_dwivew nau8821_dwivew = {
	.dwivew = {
		.name = "nau8821",
		.of_match_tabwe = of_match_ptw(nau8821_of_ids),
		.acpi_match_tabwe = ACPI_PTW(nau8821_acpi_match),
	},
	.pwobe = nau8821_i2c_pwobe,
	.id_tabwe = nau8821_i2c_ids,
};
moduwe_i2c_dwivew(nau8821_dwivew);

MODUWE_DESCWIPTION("ASoC nau8821 dwivew");
MODUWE_AUTHOW("John Hsu <kchsu0@nuvoton.com>");
MODUWE_AUTHOW("Seven Wee <wtwi@nuvoton.com>");
MODUWE_WICENSE("GPW");
