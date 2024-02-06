// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max98095.c -- MAX98095 AWSA SoC Audio dwivew
 *
 * Copywight 2011 Maxim Integwated Pwoducts
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>
#incwude <sound/max98095.h>
#incwude <sound/jack.h>
#incwude "max98095.h"

enum max98095_type {
	MAX98095,
};

stwuct max98095_cdata {
	unsigned int wate;
	unsigned int fmt;
	int eq_sew;
	int bq_sew;
};

stwuct max98095_pwiv {
	stwuct wegmap *wegmap;
	enum max98095_type devtype;
	stwuct max98095_pdata *pdata;
	stwuct cwk *mcwk;
	unsigned int syscwk;
	stwuct max98095_cdata dai[3];
	const chaw **eq_texts;
	const chaw **bq_texts;
	stwuct soc_enum eq_enum;
	stwuct soc_enum bq_enum;
	int eq_textcnt;
	int bq_textcnt;
	u8 win_state;
	unsigned int mic1pwe;
	unsigned int mic2pwe;
	stwuct snd_soc_jack *headphone_jack;
	stwuct snd_soc_jack *mic_jack;
	stwuct mutex wock;
};

static const stwuct weg_defauwt max98095_weg_def[] = {
	{  0xf, 0x00 }, /* 0F */
	{ 0x10, 0x00 }, /* 10 */
	{ 0x11, 0x00 }, /* 11 */
	{ 0x12, 0x00 }, /* 12 */
	{ 0x13, 0x00 }, /* 13 */
	{ 0x14, 0x00 }, /* 14 */
	{ 0x15, 0x00 }, /* 15 */
	{ 0x16, 0x00 }, /* 16 */
	{ 0x17, 0x00 }, /* 17 */
	{ 0x18, 0x00 }, /* 18 */
	{ 0x19, 0x00 }, /* 19 */
	{ 0x1a, 0x00 }, /* 1A */
	{ 0x1b, 0x00 }, /* 1B */
	{ 0x1c, 0x00 }, /* 1C */
	{ 0x1d, 0x00 }, /* 1D */
	{ 0x1e, 0x00 }, /* 1E */
	{ 0x1f, 0x00 }, /* 1F */
	{ 0x20, 0x00 }, /* 20 */
	{ 0x21, 0x00 }, /* 21 */
	{ 0x22, 0x00 }, /* 22 */
	{ 0x23, 0x00 }, /* 23 */
	{ 0x24, 0x00 }, /* 24 */
	{ 0x25, 0x00 }, /* 25 */
	{ 0x26, 0x00 }, /* 26 */
	{ 0x27, 0x00 }, /* 27 */
	{ 0x28, 0x00 }, /* 28 */
	{ 0x29, 0x00 }, /* 29 */
	{ 0x2a, 0x00 }, /* 2A */
	{ 0x2b, 0x00 }, /* 2B */
	{ 0x2c, 0x00 }, /* 2C */
	{ 0x2d, 0x00 }, /* 2D */
	{ 0x2e, 0x00 }, /* 2E */
	{ 0x2f, 0x00 }, /* 2F */
	{ 0x30, 0x00 }, /* 30 */
	{ 0x31, 0x00 }, /* 31 */
	{ 0x32, 0x00 }, /* 32 */
	{ 0x33, 0x00 }, /* 33 */
	{ 0x34, 0x00 }, /* 34 */
	{ 0x35, 0x00 }, /* 35 */
	{ 0x36, 0x00 }, /* 36 */
	{ 0x37, 0x00 }, /* 37 */
	{ 0x38, 0x00 }, /* 38 */
	{ 0x39, 0x00 }, /* 39 */
	{ 0x3a, 0x00 }, /* 3A */
	{ 0x3b, 0x00 }, /* 3B */
	{ 0x3c, 0x00 }, /* 3C */
	{ 0x3d, 0x00 }, /* 3D */
	{ 0x3e, 0x00 }, /* 3E */
	{ 0x3f, 0x00 }, /* 3F */
	{ 0x40, 0x00 }, /* 40 */
	{ 0x41, 0x00 }, /* 41 */
	{ 0x42, 0x00 }, /* 42 */
	{ 0x43, 0x00 }, /* 43 */
	{ 0x44, 0x00 }, /* 44 */
	{ 0x45, 0x00 }, /* 45 */
	{ 0x46, 0x00 }, /* 46 */
	{ 0x47, 0x00 }, /* 47 */
	{ 0x48, 0x00 }, /* 48 */
	{ 0x49, 0x00 }, /* 49 */
	{ 0x4a, 0x00 }, /* 4A */
	{ 0x4b, 0x00 }, /* 4B */
	{ 0x4c, 0x00 }, /* 4C */
	{ 0x4d, 0x00 }, /* 4D */
	{ 0x4e, 0x00 }, /* 4E */
	{ 0x4f, 0x00 }, /* 4F */
	{ 0x50, 0x00 }, /* 50 */
	{ 0x51, 0x00 }, /* 51 */
	{ 0x52, 0x00 }, /* 52 */
	{ 0x53, 0x00 }, /* 53 */
	{ 0x54, 0x00 }, /* 54 */
	{ 0x55, 0x00 }, /* 55 */
	{ 0x56, 0x00 }, /* 56 */
	{ 0x57, 0x00 }, /* 57 */
	{ 0x58, 0x00 }, /* 58 */
	{ 0x59, 0x00 }, /* 59 */
	{ 0x5a, 0x00 }, /* 5A */
	{ 0x5b, 0x00 }, /* 5B */
	{ 0x5c, 0x00 }, /* 5C */
	{ 0x5d, 0x00 }, /* 5D */
	{ 0x5e, 0x00 }, /* 5E */
	{ 0x5f, 0x00 }, /* 5F */
	{ 0x60, 0x00 }, /* 60 */
	{ 0x61, 0x00 }, /* 61 */
	{ 0x62, 0x00 }, /* 62 */
	{ 0x63, 0x00 }, /* 63 */
	{ 0x64, 0x00 }, /* 64 */
	{ 0x65, 0x00 }, /* 65 */
	{ 0x66, 0x00 }, /* 66 */
	{ 0x67, 0x00 }, /* 67 */
	{ 0x68, 0x00 }, /* 68 */
	{ 0x69, 0x00 }, /* 69 */
	{ 0x6a, 0x00 }, /* 6A */
	{ 0x6b, 0x00 }, /* 6B */
	{ 0x6c, 0x00 }, /* 6C */
	{ 0x6d, 0x00 }, /* 6D */
	{ 0x6e, 0x00 }, /* 6E */
	{ 0x6f, 0x00 }, /* 6F */
	{ 0x70, 0x00 }, /* 70 */
	{ 0x71, 0x00 }, /* 71 */
	{ 0x72, 0x00 }, /* 72 */
	{ 0x73, 0x00 }, /* 73 */
	{ 0x74, 0x00 }, /* 74 */
	{ 0x75, 0x00 }, /* 75 */
	{ 0x76, 0x00 }, /* 76 */
	{ 0x77, 0x00 }, /* 77 */
	{ 0x78, 0x00 }, /* 78 */
	{ 0x79, 0x00 }, /* 79 */
	{ 0x7a, 0x00 }, /* 7A */
	{ 0x7b, 0x00 }, /* 7B */
	{ 0x7c, 0x00 }, /* 7C */
	{ 0x7d, 0x00 }, /* 7D */
	{ 0x7e, 0x00 }, /* 7E */
	{ 0x7f, 0x00 }, /* 7F */
	{ 0x80, 0x00 }, /* 80 */
	{ 0x81, 0x00 }, /* 81 */
	{ 0x82, 0x00 }, /* 82 */
	{ 0x83, 0x00 }, /* 83 */
	{ 0x84, 0x00 }, /* 84 */
	{ 0x85, 0x00 }, /* 85 */
	{ 0x86, 0x00 }, /* 86 */
	{ 0x87, 0x00 }, /* 87 */
	{ 0x88, 0x00 }, /* 88 */
	{ 0x89, 0x00 }, /* 89 */
	{ 0x8a, 0x00 }, /* 8A */
	{ 0x8b, 0x00 }, /* 8B */
	{ 0x8c, 0x00 }, /* 8C */
	{ 0x8d, 0x00 }, /* 8D */
	{ 0x8e, 0x00 }, /* 8E */
	{ 0x8f, 0x00 }, /* 8F */
	{ 0x90, 0x00 }, /* 90 */
	{ 0x91, 0x00 }, /* 91 */
	{ 0x92, 0x30 }, /* 92 */
	{ 0x93, 0xF0 }, /* 93 */
	{ 0x94, 0x00 }, /* 94 */
	{ 0x95, 0x00 }, /* 95 */
	{ 0x96, 0x3F }, /* 96 */
	{ 0x97, 0x00 }, /* 97 */
	{ 0xff, 0x00 }, /* FF */
};

static boow max98095_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case M98095_001_HOST_INT_STS ... M98095_097_PWW_SYS:
	case M98095_0FF_WEV_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max98095_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case M98095_00F_HOST_CFG ... M98095_097_PWW_SYS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max98095_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case M98095_000_HOST_DATA ... M98095_00E_TEMP_SENSOW_STS:
	case M98095_WEG_MAX_CACHED + 1 ... M98095_0FF_WEV_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config max98095_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = max98095_weg_def,
	.num_weg_defauwts = AWWAY_SIZE(max98095_weg_def),
	.max_wegistew = M98095_0FF_WEV_ID,
	.cache_type = WEGCACHE_WBTWEE,

	.weadabwe_weg = max98095_weadabwe,
	.wwiteabwe_weg = max98095_wwiteabwe,
	.vowatiwe_weg = max98095_vowatiwe,
};

/*
 * Woad equawizew DSP coefficient configuwations wegistews
 */
static void m98095_eq_band(stwuct snd_soc_component *component, unsigned int dai,
		    unsigned int band, u16 *coefs)
{
	unsigned int eq_weg;
	unsigned int i;

	if (WAWN_ON(band > 4) ||
	    WAWN_ON(dai > 1))
		wetuwn;

	/* Woad the base wegistew addwess */
	eq_weg = dai ? M98095_142_DAI2_EQ_BASE : M98095_110_DAI1_EQ_BASE;

	/* Add the band addwess offset, note adjustment fow wowd addwess */
	eq_weg += band * (M98095_COEFS_PEW_BAND << 1);

	/* Step thwough the wegistews and coefs */
	fow (i = 0; i < M98095_COEFS_PEW_BAND; i++) {
		snd_soc_component_wwite(component, eq_weg++, M98095_BYTE1(coefs[i]));
		snd_soc_component_wwite(component, eq_weg++, M98095_BYTE0(coefs[i]));
	}
}

/*
 * Woad biquad fiwtew coefficient configuwations wegistews
 */
static void m98095_biquad_band(stwuct snd_soc_component *component, unsigned int dai,
		    unsigned int band, u16 *coefs)
{
	unsigned int bq_weg;
	unsigned int i;

	if (WAWN_ON(band > 1) ||
	    WAWN_ON(dai > 1))
		wetuwn;

	/* Woad the base wegistew addwess */
	bq_weg = dai ? M98095_17E_DAI2_BQ_BASE : M98095_174_DAI1_BQ_BASE;

	/* Add the band addwess offset, note adjustment fow wowd addwess */
	bq_weg += band * (M98095_COEFS_PEW_BAND << 1);

	/* Step thwough the wegistews and coefs */
	fow (i = 0; i < M98095_COEFS_PEW_BAND; i++) {
		snd_soc_component_wwite(component, bq_weg++, M98095_BYTE1(coefs[i]));
		snd_soc_component_wwite(component, bq_weg++, M98095_BYTE0(coefs[i]));
	}
}

static const chaw * const max98095_fwtw_mode[] = { "Voice", "Music" };
static SOC_ENUM_SINGWE_DECW(max98095_dai1_fiwtew_mode_enum,
			    M98095_02E_DAI1_FIWTEWS, 7,
			    max98095_fwtw_mode);
static SOC_ENUM_SINGWE_DECW(max98095_dai2_fiwtew_mode_enum,
			    M98095_038_DAI2_FIWTEWS, 7,
			    max98095_fwtw_mode);

static const chaw * const max98095_extmic_text[] = { "None", "MIC1", "MIC2" };

static SOC_ENUM_SINGWE_DECW(max98095_extmic_enum,
			    M98095_087_CFG_MIC, 0,
			    max98095_extmic_text);

static const stwuct snd_kcontwow_new max98095_extmic_mux =
	SOC_DAPM_ENUM("Extewnaw MIC Mux", max98095_extmic_enum);

static const chaw * const max98095_winein_text[] = { "INA", "INB" };

static SOC_ENUM_SINGWE_DECW(max98095_winein_enum,
			    M98095_086_CFG_WINE, 6,
			    max98095_winein_text);

static const stwuct snd_kcontwow_new max98095_winein_mux =
	SOC_DAPM_ENUM("Winein Input Mux", max98095_winein_enum);

static const chaw * const max98095_wine_mode_text[] = {
	"Steweo", "Diffewentiaw"};

static SOC_ENUM_SINGWE_DECW(max98095_winein_mode_enum,
			    M98095_086_CFG_WINE, 7,
			    max98095_wine_mode_text);

static SOC_ENUM_SINGWE_DECW(max98095_wineout_mode_enum,
			    M98095_086_CFG_WINE, 4,
			    max98095_wine_mode_text);

static const chaw * const max98095_dai_fwtw[] = {
	"Off", "Ewwipticaw-HPF-16k", "Buttewwowth-HPF-16k",
	"Ewwipticaw-HPF-8k", "Buttewwowth-HPF-8k", "Buttewwowth-HPF-Fs/240"};
static SOC_ENUM_SINGWE_DECW(max98095_dai1_dac_fiwtew_enum,
			    M98095_02E_DAI1_FIWTEWS, 0,
			    max98095_dai_fwtw);
static SOC_ENUM_SINGWE_DECW(max98095_dai2_dac_fiwtew_enum,
			    M98095_038_DAI2_FIWTEWS, 0,
			    max98095_dai_fwtw);
static SOC_ENUM_SINGWE_DECW(max98095_dai3_dac_fiwtew_enum,
			    M98095_042_DAI3_FIWTEWS, 0,
			    max98095_dai_fwtw);

static int max98095_mic1pwe_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	unsigned int sew = ucontwow->vawue.integew.vawue[0];

	max98095->mic1pwe = sew;
	snd_soc_component_update_bits(component, M98095_05F_WVW_MIC1, M98095_MICPWE_MASK,
		(1+sew)<<M98095_MICPWE_SHIFT);

	wetuwn 0;
}

static int max98095_mic1pwe_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = max98095->mic1pwe;
	wetuwn 0;
}

static int max98095_mic2pwe_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	unsigned int sew = ucontwow->vawue.integew.vawue[0];

	max98095->mic2pwe = sew;
	snd_soc_component_update_bits(component, M98095_060_WVW_MIC2, M98095_MICPWE_MASK,
		(1+sew)<<M98095_MICPWE_SHIFT);

	wetuwn 0;
}

static int max98095_mic2pwe_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = max98095->mic2pwe;
	wetuwn 0;
}

static const DECWAWE_TWV_DB_WANGE(max98095_micboost_twv,
	0, 1, TWV_DB_SCAWE_ITEM(0, 2000, 0),
	2, 2, TWV_DB_SCAWE_ITEM(3000, 0, 0)
);

static const DECWAWE_TWV_DB_SCAWE(max98095_mic_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(max98095_adc_twv, -1200, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(max98095_adcboost_twv, 0, 600, 0);

static const DECWAWE_TWV_DB_WANGE(max98095_hp_twv,
	0, 6, TWV_DB_SCAWE_ITEM(-6700, 400, 0),
	7, 14, TWV_DB_SCAWE_ITEM(-4000, 300, 0),
	15, 21, TWV_DB_SCAWE_ITEM(-1700, 200, 0),
	22, 27, TWV_DB_SCAWE_ITEM(-400, 100, 0),
	28, 31, TWV_DB_SCAWE_ITEM(150, 50, 0)
);

static const DECWAWE_TWV_DB_WANGE(max98095_spk_twv,
	0, 10, TWV_DB_SCAWE_ITEM(-5900, 400, 0),
	11, 18, TWV_DB_SCAWE_ITEM(-1700, 200, 0),
	19, 27, TWV_DB_SCAWE_ITEM(-200, 100, 0),
	28, 39, TWV_DB_SCAWE_ITEM(650, 50, 0)
);

static const DECWAWE_TWV_DB_WANGE(max98095_wcv_wout_twv,
	0, 6, TWV_DB_SCAWE_ITEM(-6200, 400, 0),
	7, 14, TWV_DB_SCAWE_ITEM(-3500, 300, 0),
	15, 21, TWV_DB_SCAWE_ITEM(-1200, 200, 0),
	22, 27, TWV_DB_SCAWE_ITEM(100, 100, 0),
	28, 31, TWV_DB_SCAWE_ITEM(650, 50, 0)
);

static const DECWAWE_TWV_DB_WANGE(max98095_win_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-600, 300, 0),
	3, 3, TWV_DB_SCAWE_ITEM(300, 1100, 0),
	4, 5, TWV_DB_SCAWE_ITEM(1400, 600, 0)
);

static const stwuct snd_kcontwow_new max98095_snd_contwows[] = {

	SOC_DOUBWE_W_TWV("Headphone Vowume", M98095_064_WVW_HP_W,
		M98095_065_WVW_HP_W, 0, 31, 0, max98095_hp_twv),

	SOC_DOUBWE_W_TWV("Speakew Vowume", M98095_067_WVW_SPK_W,
		M98095_068_WVW_SPK_W, 0, 39, 0, max98095_spk_twv),

	SOC_SINGWE_TWV("Weceivew Vowume", M98095_066_WVW_WCV,
		0, 31, 0, max98095_wcv_wout_twv),

	SOC_DOUBWE_W_TWV("Wineout Vowume", M98095_062_WVW_WINEOUT1,
		M98095_063_WVW_WINEOUT2, 0, 31, 0, max98095_wcv_wout_twv),

	SOC_DOUBWE_W("Headphone Switch", M98095_064_WVW_HP_W,
		M98095_065_WVW_HP_W, 7, 1, 1),

	SOC_DOUBWE_W("Speakew Switch", M98095_067_WVW_SPK_W,
		M98095_068_WVW_SPK_W, 7, 1, 1),

	SOC_SINGWE("Weceivew Switch", M98095_066_WVW_WCV, 7, 1, 1),

	SOC_DOUBWE_W("Wineout Switch", M98095_062_WVW_WINEOUT1,
		M98095_063_WVW_WINEOUT2, 7, 1, 1),

	SOC_SINGWE_TWV("MIC1 Vowume", M98095_05F_WVW_MIC1, 0, 20, 1,
		max98095_mic_twv),

	SOC_SINGWE_TWV("MIC2 Vowume", M98095_060_WVW_MIC2, 0, 20, 1,
		max98095_mic_twv),

	SOC_SINGWE_EXT_TWV("MIC1 Boost Vowume",
			M98095_05F_WVW_MIC1, 5, 2, 0,
			max98095_mic1pwe_get, max98095_mic1pwe_set,
			max98095_micboost_twv),
	SOC_SINGWE_EXT_TWV("MIC2 Boost Vowume",
			M98095_060_WVW_MIC2, 5, 2, 0,
			max98095_mic2pwe_get, max98095_mic2pwe_set,
			max98095_micboost_twv),

	SOC_SINGWE_TWV("Winein Vowume", M98095_061_WVW_WINEIN, 0, 5, 1,
		max98095_win_twv),

	SOC_SINGWE_TWV("ADCW Vowume", M98095_05D_WVW_ADC_W, 0, 15, 1,
		max98095_adc_twv),
	SOC_SINGWE_TWV("ADCW Vowume", M98095_05E_WVW_ADC_W, 0, 15, 1,
		max98095_adc_twv),

	SOC_SINGWE_TWV("ADCW Boost Vowume", M98095_05D_WVW_ADC_W, 4, 3, 0,
		max98095_adcboost_twv),
	SOC_SINGWE_TWV("ADCW Boost Vowume", M98095_05E_WVW_ADC_W, 4, 3, 0,
		max98095_adcboost_twv),

	SOC_SINGWE("EQ1 Switch", M98095_088_CFG_WEVEW, 0, 1, 0),
	SOC_SINGWE("EQ2 Switch", M98095_088_CFG_WEVEW, 1, 1, 0),

	SOC_SINGWE("Biquad1 Switch", M98095_088_CFG_WEVEW, 2, 1, 0),
	SOC_SINGWE("Biquad2 Switch", M98095_088_CFG_WEVEW, 3, 1, 0),

	SOC_ENUM("DAI1 Fiwtew Mode", max98095_dai1_fiwtew_mode_enum),
	SOC_ENUM("DAI2 Fiwtew Mode", max98095_dai2_fiwtew_mode_enum),
	SOC_ENUM("DAI1 DAC Fiwtew", max98095_dai1_dac_fiwtew_enum),
	SOC_ENUM("DAI2 DAC Fiwtew", max98095_dai2_dac_fiwtew_enum),
	SOC_ENUM("DAI3 DAC Fiwtew", max98095_dai3_dac_fiwtew_enum),

	SOC_ENUM("Winein Mode", max98095_winein_mode_enum),
	SOC_ENUM("Wineout Mode", max98095_wineout_mode_enum),
};

/* Weft speakew mixew switch */
static const stwuct snd_kcontwow_new max98095_weft_speakew_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_050_MIX_SPK_WEFT, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_050_MIX_SPK_WEFT, 6, 1, 0),
	SOC_DAPM_SINGWE("Mono DAC2 Switch", M98095_050_MIX_SPK_WEFT, 3, 1, 0),
	SOC_DAPM_SINGWE("Mono DAC3 Switch", M98095_050_MIX_SPK_WEFT, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_050_MIX_SPK_WEFT, 4, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_050_MIX_SPK_WEFT, 5, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_050_MIX_SPK_WEFT, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_050_MIX_SPK_WEFT, 2, 1, 0),
};

/* Wight speakew mixew switch */
static const stwuct snd_kcontwow_new max98095_wight_speakew_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_051_MIX_SPK_WIGHT, 6, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_051_MIX_SPK_WIGHT, 0, 1, 0),
	SOC_DAPM_SINGWE("Mono DAC2 Switch", M98095_051_MIX_SPK_WIGHT, 3, 1, 0),
	SOC_DAPM_SINGWE("Mono DAC3 Switch", M98095_051_MIX_SPK_WIGHT, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_051_MIX_SPK_WIGHT, 5, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_051_MIX_SPK_WIGHT, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_051_MIX_SPK_WIGHT, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_051_MIX_SPK_WIGHT, 2, 1, 0),
};

/* Weft headphone mixew switch */
static const stwuct snd_kcontwow_new max98095_weft_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_04C_MIX_HP_WEFT, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_04C_MIX_HP_WEFT, 5, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_04C_MIX_HP_WEFT, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_04C_MIX_HP_WEFT, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_04C_MIX_HP_WEFT, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_04C_MIX_HP_WEFT, 2, 1, 0),
};

/* Wight headphone mixew switch */
static const stwuct snd_kcontwow_new max98095_wight_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_04D_MIX_HP_WIGHT, 5, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_04D_MIX_HP_WIGHT, 0, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_04D_MIX_HP_WIGHT, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_04D_MIX_HP_WIGHT, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_04D_MIX_HP_WIGHT, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_04D_MIX_HP_WIGHT, 2, 1, 0),
};

/* Weceivew eawpiece mixew switch */
static const stwuct snd_kcontwow_new max98095_mono_wcv_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_04F_MIX_WCV, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_04F_MIX_WCV, 5, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_04F_MIX_WCV, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_04F_MIX_WCV, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_04F_MIX_WCV, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_04F_MIX_WCV, 2, 1, 0),
};

/* Weft wineout mixew switch */
static const stwuct snd_kcontwow_new max98095_weft_wineout_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_053_MIX_WINEOUT1, 5, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_053_MIX_WINEOUT1, 0, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_053_MIX_WINEOUT1, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_053_MIX_WINEOUT1, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_053_MIX_WINEOUT1, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_053_MIX_WINEOUT1, 2, 1, 0),
};

/* Wight wineout mixew switch */
static const stwuct snd_kcontwow_new max98095_wight_wineout_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", M98095_054_MIX_WINEOUT2, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC1 Switch", M98095_054_MIX_WINEOUT2, 5, 1, 0),
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_054_MIX_WINEOUT2, 3, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_054_MIX_WINEOUT2, 4, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_054_MIX_WINEOUT2, 1, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_054_MIX_WINEOUT2, 2, 1, 0),
};

/* Weft ADC mixew switch */
static const stwuct snd_kcontwow_new max98095_weft_ADC_mixew_contwows[] = {
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_04A_MIX_ADC_WEFT, 7, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_04A_MIX_ADC_WEFT, 6, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_04A_MIX_ADC_WEFT, 3, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_04A_MIX_ADC_WEFT, 2, 1, 0),
};

/* Wight ADC mixew switch */
static const stwuct snd_kcontwow_new max98095_wight_ADC_mixew_contwows[] = {
	SOC_DAPM_SINGWE("MIC1 Switch", M98095_04B_MIX_ADC_WIGHT, 7, 1, 0),
	SOC_DAPM_SINGWE("MIC2 Switch", M98095_04B_MIX_ADC_WIGHT, 6, 1, 0),
	SOC_DAPM_SINGWE("IN1 Switch", M98095_04B_MIX_ADC_WIGHT, 3, 1, 0),
	SOC_DAPM_SINGWE("IN2 Switch", M98095_04B_MIX_ADC_WIGHT, 2, 1, 0),
};

static int max98095_mic_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (w->weg == M98095_05F_WVW_MIC1) {
			snd_soc_component_update_bits(component, w->weg, M98095_MICPWE_MASK,
				(1+max98095->mic1pwe)<<M98095_MICPWE_SHIFT);
		} ewse {
			snd_soc_component_update_bits(component, w->weg, M98095_MICPWE_MASK,
				(1+max98095->mic2pwe)<<M98095_MICPWE_SHIFT);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->weg, M98095_MICPWE_MASK, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * The wine inputs awe steweo inputs with the weft and wight
 * channews shawing a common PGA powew contwow signaw.
 */
static int max98095_wine_pga(stwuct snd_soc_dapm_widget *w,
			     int event, u8 channew)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	u8 *state;

	if (WAWN_ON(!(channew == 1 || channew == 2)))
		wetuwn -EINVAW;

	state = &max98095->win_state;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		*state |= channew;
		snd_soc_component_update_bits(component, w->weg,
			(1 << w->shift), (1 << w->shift));
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		*state &= ~channew;
		if (*state == 0) {
			snd_soc_component_update_bits(component, w->weg,
				(1 << w->shift), 0);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int max98095_pga_in1_event(stwuct snd_soc_dapm_widget *w,
				   stwuct snd_kcontwow *k, int event)
{
	wetuwn max98095_wine_pga(w, event, 1);
}

static int max98095_pga_in2_event(stwuct snd_soc_dapm_widget *w,
				   stwuct snd_kcontwow *k, int event)
{
	wetuwn max98095_wine_pga(w, event, 2);
}

/*
 * The steweo wine out mixew outputs to two steweo wine outs.
 * The 2nd paiw has a sepawate set of enabwes.
 */
static int max98095_wineout_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, w->weg,
			(1 << (w->shift+2)), (1 << (w->shift+2)));
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->weg,
			(1 << (w->shift+2)), 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget max98095_dapm_widgets[] = {

	SND_SOC_DAPM_ADC("ADCW", "HiFi Captuwe", M98095_090_PWW_EN_IN, 0, 0),
	SND_SOC_DAPM_ADC("ADCW", "HiFi Captuwe", M98095_090_PWW_EN_IN, 1, 0),

	SND_SOC_DAPM_DAC("DACW1", "HiFi Pwayback",
		M98095_091_PWW_EN_OUT, 0, 0),
	SND_SOC_DAPM_DAC("DACW1", "HiFi Pwayback",
		M98095_091_PWW_EN_OUT, 1, 0),
	SND_SOC_DAPM_DAC("DACM2", "Aux Pwayback",
		M98095_091_PWW_EN_OUT, 2, 0),
	SND_SOC_DAPM_DAC("DACM3", "Voice Pwayback",
		M98095_091_PWW_EN_OUT, 2, 0),

	SND_SOC_DAPM_PGA("HP Weft Out", M98095_091_PWW_EN_OUT,
		6, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HP Wight Out", M98095_091_PWW_EN_OUT,
		7, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("SPK Weft Out", M98095_091_PWW_EN_OUT,
		4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("SPK Wight Out", M98095_091_PWW_EN_OUT,
		5, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("WCV Mono Out", M98095_091_PWW_EN_OUT,
		3, 0, NUWW, 0),

	SND_SOC_DAPM_PGA_E("WINE Weft Out", M98095_092_PWW_EN_OUT,
		0, 0, NUWW, 0, max98095_wineout_event, SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("WINE Wight Out", M98095_092_PWW_EN_OUT,
		1, 0, NUWW, 0, max98095_wineout_event, SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_MUX("Extewnaw MIC", SND_SOC_NOPM, 0, 0,
		&max98095_extmic_mux),

	SND_SOC_DAPM_MUX("Winein Mux", SND_SOC_NOPM, 0, 0,
		&max98095_winein_mux),

	SND_SOC_DAPM_MIXEW("Weft Headphone Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_weft_hp_mixew_contwows[0],
		AWWAY_SIZE(max98095_weft_hp_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight Headphone Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_wight_hp_mixew_contwows[0],
		AWWAY_SIZE(max98095_wight_hp_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft Speakew Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_weft_speakew_mixew_contwows[0],
		AWWAY_SIZE(max98095_weft_speakew_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight Speakew Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_wight_speakew_mixew_contwows[0],
		AWWAY_SIZE(max98095_wight_speakew_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weceivew Mixew", SND_SOC_NOPM, 0, 0,
	  &max98095_mono_wcv_mixew_contwows[0],
		AWWAY_SIZE(max98095_mono_wcv_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft Wineout Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_weft_wineout_mixew_contwows[0],
		AWWAY_SIZE(max98095_weft_wineout_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight Wineout Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_wight_wineout_mixew_contwows[0],
		AWWAY_SIZE(max98095_wight_wineout_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft ADC Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_weft_ADC_mixew_contwows[0],
		AWWAY_SIZE(max98095_weft_ADC_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight ADC Mixew", SND_SOC_NOPM, 0, 0,
		&max98095_wight_ADC_mixew_contwows[0],
		AWWAY_SIZE(max98095_wight_ADC_mixew_contwows)),

	SND_SOC_DAPM_PGA_E("MIC1 Input", M98095_05F_WVW_MIC1,
		5, 0, NUWW, 0, max98095_mic_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("MIC2 Input", M98095_060_WVW_MIC2,
		5, 0, NUWW, 0, max98095_mic_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("IN1 Input", M98095_090_PWW_EN_IN,
		7, 0, NUWW, 0, max98095_pga_in1_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("IN2 Input", M98095_090_PWW_EN_IN,
		7, 0, NUWW, 0, max98095_pga_in2_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MICBIAS("MICBIAS1", M98095_090_PWW_EN_IN, 2, 0),
	SND_SOC_DAPM_MICBIAS("MICBIAS2", M98095_090_PWW_EN_IN, 3, 0),

	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("SPKW"),
	SND_SOC_DAPM_OUTPUT("SPKW"),
	SND_SOC_DAPM_OUTPUT("WCV"),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4"),

	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("INA1"),
	SND_SOC_DAPM_INPUT("INA2"),
	SND_SOC_DAPM_INPUT("INB1"),
	SND_SOC_DAPM_INPUT("INB2"),
};

static const stwuct snd_soc_dapm_woute max98095_audio_map[] = {
	/* Weft headphone output mixew */
	{"Weft Headphone Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Weft Headphone Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Weft Headphone Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Weft Headphone Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Weft Headphone Mixew", "IN1 Switch", "IN1 Input"},
	{"Weft Headphone Mixew", "IN2 Switch", "IN2 Input"},

	/* Wight headphone output mixew */
	{"Wight Headphone Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Wight Headphone Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Wight Headphone Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Wight Headphone Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Wight Headphone Mixew", "IN1 Switch", "IN1 Input"},
	{"Wight Headphone Mixew", "IN2 Switch", "IN2 Input"},

	/* Weft speakew output mixew */
	{"Weft Speakew Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Weft Speakew Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Weft Speakew Mixew", "Mono DAC2 Switch", "DACM2"},
	{"Weft Speakew Mixew", "Mono DAC3 Switch", "DACM3"},
	{"Weft Speakew Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Weft Speakew Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Weft Speakew Mixew", "IN1 Switch", "IN1 Input"},
	{"Weft Speakew Mixew", "IN2 Switch", "IN2 Input"},

	/* Wight speakew output mixew */
	{"Wight Speakew Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Wight Speakew Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Wight Speakew Mixew", "Mono DAC2 Switch", "DACM2"},
	{"Wight Speakew Mixew", "Mono DAC3 Switch", "DACM3"},
	{"Wight Speakew Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Wight Speakew Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Wight Speakew Mixew", "IN1 Switch", "IN1 Input"},
	{"Wight Speakew Mixew", "IN2 Switch", "IN2 Input"},

	/* Eawpiece/Weceivew output mixew */
	{"Weceivew Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Weceivew Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Weceivew Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Weceivew Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Weceivew Mixew", "IN1 Switch", "IN1 Input"},
	{"Weceivew Mixew", "IN2 Switch", "IN2 Input"},

	/* Weft Wineout output mixew */
	{"Weft Wineout Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Weft Wineout Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Weft Wineout Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Weft Wineout Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Weft Wineout Mixew", "IN1 Switch", "IN1 Input"},
	{"Weft Wineout Mixew", "IN2 Switch", "IN2 Input"},

	/* Wight wineout output mixew */
	{"Wight Wineout Mixew", "Weft DAC1 Switch", "DACW1"},
	{"Wight Wineout Mixew", "Wight DAC1 Switch", "DACW1"},
	{"Wight Wineout Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Wight Wineout Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Wight Wineout Mixew", "IN1 Switch", "IN1 Input"},
	{"Wight Wineout Mixew", "IN2 Switch", "IN2 Input"},

	{"HP Weft Out", NUWW, "Weft Headphone Mixew"},
	{"HP Wight Out", NUWW, "Wight Headphone Mixew"},
	{"SPK Weft Out", NUWW, "Weft Speakew Mixew"},
	{"SPK Wight Out", NUWW, "Wight Speakew Mixew"},
	{"WCV Mono Out", NUWW, "Weceivew Mixew"},
	{"WINE Weft Out", NUWW, "Weft Wineout Mixew"},
	{"WINE Wight Out", NUWW, "Wight Wineout Mixew"},

	{"HPW", NUWW, "HP Weft Out"},
	{"HPW", NUWW, "HP Wight Out"},
	{"SPKW", NUWW, "SPK Weft Out"},
	{"SPKW", NUWW, "SPK Wight Out"},
	{"WCV", NUWW, "WCV Mono Out"},
	{"OUT1", NUWW, "WINE Weft Out"},
	{"OUT2", NUWW, "WINE Wight Out"},
	{"OUT3", NUWW, "WINE Weft Out"},
	{"OUT4", NUWW, "WINE Wight Out"},

	/* Weft ADC input mixew */
	{"Weft ADC Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Weft ADC Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Weft ADC Mixew", "IN1 Switch", "IN1 Input"},
	{"Weft ADC Mixew", "IN2 Switch", "IN2 Input"},

	/* Wight ADC input mixew */
	{"Wight ADC Mixew", "MIC1 Switch", "MIC1 Input"},
	{"Wight ADC Mixew", "MIC2 Switch", "MIC2 Input"},
	{"Wight ADC Mixew", "IN1 Switch", "IN1 Input"},
	{"Wight ADC Mixew", "IN2 Switch", "IN2 Input"},

	/* Inputs */
	{"ADCW", NUWW, "Weft ADC Mixew"},
	{"ADCW", NUWW, "Wight ADC Mixew"},

	{"IN1 Input", NUWW, "INA1"},
	{"IN2 Input", NUWW, "INA2"},

	{"MIC1 Input", NUWW, "MIC1"},
	{"MIC2 Input", NUWW, "MIC2"},
};

/* codec mcwk cwock dividew coefficients */
static const stwuct {
	u32 wate;
	u8  sw;
} wate_tabwe[] = {
	{8000,  0x01},
	{11025, 0x02},
	{16000, 0x03},
	{22050, 0x04},
	{24000, 0x05},
	{32000, 0x06},
	{44100, 0x07},
	{48000, 0x08},
	{88200, 0x09},
	{96000, 0x0A},
};

static int wate_vawue(int wate, u8 *vawue)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wate_tabwe); i++) {
		if (wate_tabwe[i].wate >= wate) {
			*vawue = wate_tabwe[i].sw;
			wetuwn 0;
		}
	}
	*vawue = wate_tabwe[0].sw;
	wetuwn -EINVAW;
}

static int max98095_dai1_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	unsigned wong wong ni;
	unsigned int wate;
	u8 wegvaw;

	cdata = &max98095->dai[0];

	wate = pawams_wate(pawams);

	switch (pawams_width(pawams)) {
	case 16:
		snd_soc_component_update_bits(component, M98095_02A_DAI1_FOWMAT,
			M98095_DAI_WS, 0);
		bweak;
	case 24:
		snd_soc_component_update_bits(component, M98095_02A_DAI1_FOWMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wate_vawue(wate, &wegvaw))
		wetuwn -EINVAW;

	snd_soc_component_update_bits(component, M98095_027_DAI1_CWKMODE,
		M98095_CWKMODE_MASK, wegvaw);
	cdata->wate = wate;

	/* Configuwe NI when opewating as mastew */
	if (snd_soc_component_wead(component, M98095_02A_DAI1_FOWMAT) & M98095_DAI_MAS) {
		if (max98095->syscwk == 0) {
			dev_eww(component->dev, "Invawid system cwock fwequency\n");
			wetuwn -EINVAW;
		}
		ni = 65536UWW * (wate < 50000 ? 96UWW : 48UWW)
				* (unsigned wong wong int)wate;
		do_div(ni, (unsigned wong wong int)max98095->syscwk);
		snd_soc_component_wwite(component, M98095_028_DAI1_CWKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_wwite(component, M98095_029_DAI1_CWKCFG_WO,
			ni & 0xFF);
	}

	/* Update sampwe wate mode */
	if (wate < 50000)
		snd_soc_component_update_bits(component, M98095_02E_DAI1_FIWTEWS,
			M98095_DAI_DHF, 0);
	ewse
		snd_soc_component_update_bits(component, M98095_02E_DAI1_FIWTEWS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	wetuwn 0;
}

static int max98095_dai2_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	unsigned wong wong ni;
	unsigned int wate;
	u8 wegvaw;

	cdata = &max98095->dai[1];

	wate = pawams_wate(pawams);

	switch (pawams_width(pawams)) {
	case 16:
		snd_soc_component_update_bits(component, M98095_034_DAI2_FOWMAT,
			M98095_DAI_WS, 0);
		bweak;
	case 24:
		snd_soc_component_update_bits(component, M98095_034_DAI2_FOWMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wate_vawue(wate, &wegvaw))
		wetuwn -EINVAW;

	snd_soc_component_update_bits(component, M98095_031_DAI2_CWKMODE,
		M98095_CWKMODE_MASK, wegvaw);
	cdata->wate = wate;

	/* Configuwe NI when opewating as mastew */
	if (snd_soc_component_wead(component, M98095_034_DAI2_FOWMAT) & M98095_DAI_MAS) {
		if (max98095->syscwk == 0) {
			dev_eww(component->dev, "Invawid system cwock fwequency\n");
			wetuwn -EINVAW;
		}
		ni = 65536UWW * (wate < 50000 ? 96UWW : 48UWW)
				* (unsigned wong wong int)wate;
		do_div(ni, (unsigned wong wong int)max98095->syscwk);
		snd_soc_component_wwite(component, M98095_032_DAI2_CWKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_wwite(component, M98095_033_DAI2_CWKCFG_WO,
			ni & 0xFF);
	}

	/* Update sampwe wate mode */
	if (wate < 50000)
		snd_soc_component_update_bits(component, M98095_038_DAI2_FIWTEWS,
			M98095_DAI_DHF, 0);
	ewse
		snd_soc_component_update_bits(component, M98095_038_DAI2_FIWTEWS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	wetuwn 0;
}

static int max98095_dai3_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	unsigned wong wong ni;
	unsigned int wate;
	u8 wegvaw;

	cdata = &max98095->dai[2];

	wate = pawams_wate(pawams);

	switch (pawams_width(pawams)) {
	case 16:
		snd_soc_component_update_bits(component, M98095_03E_DAI3_FOWMAT,
			M98095_DAI_WS, 0);
		bweak;
	case 24:
		snd_soc_component_update_bits(component, M98095_03E_DAI3_FOWMAT,
			M98095_DAI_WS, M98095_DAI_WS);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wate_vawue(wate, &wegvaw))
		wetuwn -EINVAW;

	snd_soc_component_update_bits(component, M98095_03B_DAI3_CWKMODE,
		M98095_CWKMODE_MASK, wegvaw);
	cdata->wate = wate;

	/* Configuwe NI when opewating as mastew */
	if (snd_soc_component_wead(component, M98095_03E_DAI3_FOWMAT) & M98095_DAI_MAS) {
		if (max98095->syscwk == 0) {
			dev_eww(component->dev, "Invawid system cwock fwequency\n");
			wetuwn -EINVAW;
		}
		ni = 65536UWW * (wate < 50000 ? 96UWW : 48UWW)
				* (unsigned wong wong int)wate;
		do_div(ni, (unsigned wong wong int)max98095->syscwk);
		snd_soc_component_wwite(component, M98095_03C_DAI3_CWKCFG_HI,
			(ni >> 8) & 0x7F);
		snd_soc_component_wwite(component, M98095_03D_DAI3_CWKCFG_WO,
			ni & 0xFF);
	}

	/* Update sampwe wate mode */
	if (wate < 50000)
		snd_soc_component_update_bits(component, M98095_042_DAI3_FIWTEWS,
			M98095_DAI_DHF, 0);
	ewse
		snd_soc_component_update_bits(component, M98095_042_DAI3_FIWTEWS,
			M98095_DAI_DHF, M98095_DAI_DHF);

	wetuwn 0;
}

static int max98095_dai_set_syscwk(stwuct snd_soc_dai *dai,
				   int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);

	/* Wequested cwock fwequency is awweady setup */
	if (fweq == max98095->syscwk)
		wetuwn 0;

	if (!IS_EWW(max98095->mcwk)) {
		fweq = cwk_wound_wate(max98095->mcwk, fweq);
		cwk_set_wate(max98095->mcwk, fweq);
	}

	/* Setup cwocks fow swave mode, and using the PWW
	 * PSCWK = 0x01 (when mastew cwk is 10MHz to 20MHz)
	 *         0x02 (when mastew cwk is 20MHz to 40MHz)..
	 *         0x03 (when mastew cwk is 40MHz to 60MHz)..
	 */
	if ((fweq >= 10000000) && (fweq < 20000000)) {
		snd_soc_component_wwite(component, M98095_026_SYS_CWK, 0x10);
	} ewse if ((fweq >= 20000000) && (fweq < 40000000)) {
		snd_soc_component_wwite(component, M98095_026_SYS_CWK, 0x20);
	} ewse if ((fweq >= 40000000) && (fweq < 60000000)) {
		snd_soc_component_wwite(component, M98095_026_SYS_CWK, 0x30);
	} ewse {
		dev_eww(component->dev, "Invawid mastew cwock fwequency\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dai->dev, "Cwock souwce is %d at %uHz\n", cwk_id, fweq);

	max98095->syscwk = fweq;
	wetuwn 0;
}

static int max98095_dai1_set_fmt(stwuct snd_soc_dai *codec_dai,
				 unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	u8 wegvaw = 0;

	cdata = &max98095->dai[0];

	if (fmt != cdata->fmt) {
		cdata->fmt = fmt;

		switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
		case SND_SOC_DAIFMT_CBC_CFC:
			/* Consumew mode PWW */
			snd_soc_component_wwite(component, M98095_028_DAI1_CWKCFG_HI,
				0x80);
			snd_soc_component_wwite(component, M98095_029_DAI1_CWKCFG_WO,
				0x00);
			bweak;
		case SND_SOC_DAIFMT_CBP_CFP:
			/* Set to pwovidew mode */
			wegvaw |= M98095_DAI_MAS;
			bweak;
		defauwt:
			dev_eww(component->dev, "Cwock mode unsuppowted");
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
		case SND_SOC_DAIFMT_I2S:
			wegvaw |= M98095_DAI_DWY;
			bweak;
		case SND_SOC_DAIFMT_WEFT_J:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			wegvaw |= M98095_DAI_WCI;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			wegvaw |= M98095_DAI_BCI;
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			wegvaw |= M98095_DAI_BCI|M98095_DAI_WCI;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		snd_soc_component_update_bits(component, M98095_02A_DAI1_FOWMAT,
			M98095_DAI_MAS | M98095_DAI_DWY | M98095_DAI_BCI |
			M98095_DAI_WCI, wegvaw);

		snd_soc_component_wwite(component, M98095_02B_DAI1_CWOCK, M98095_DAI_BSEW64);
	}

	wetuwn 0;
}

static int max98095_dai2_set_fmt(stwuct snd_soc_dai *codec_dai,
				 unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	u8 wegvaw = 0;

	cdata = &max98095->dai[1];

	if (fmt != cdata->fmt) {
		cdata->fmt = fmt;

		switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
		case SND_SOC_DAIFMT_CBC_CFC:
			/* Consumew mode PWW */
			snd_soc_component_wwite(component, M98095_032_DAI2_CWKCFG_HI,
				0x80);
			snd_soc_component_wwite(component, M98095_033_DAI2_CWKCFG_WO,
				0x00);
			bweak;
		case SND_SOC_DAIFMT_CBP_CFP:
			/* Set to pwovidew mode */
			wegvaw |= M98095_DAI_MAS;
			bweak;
		defauwt:
			dev_eww(component->dev, "Cwock mode unsuppowted");
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
		case SND_SOC_DAIFMT_I2S:
			wegvaw |= M98095_DAI_DWY;
			bweak;
		case SND_SOC_DAIFMT_WEFT_J:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			wegvaw |= M98095_DAI_WCI;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			wegvaw |= M98095_DAI_BCI;
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			wegvaw |= M98095_DAI_BCI|M98095_DAI_WCI;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		snd_soc_component_update_bits(component, M98095_034_DAI2_FOWMAT,
			M98095_DAI_MAS | M98095_DAI_DWY | M98095_DAI_BCI |
			M98095_DAI_WCI, wegvaw);

		snd_soc_component_wwite(component, M98095_035_DAI2_CWOCK,
			M98095_DAI_BSEW64);
	}

	wetuwn 0;
}

static int max98095_dai3_set_fmt(stwuct snd_soc_dai *codec_dai,
				 unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	u8 wegvaw = 0;

	cdata = &max98095->dai[2];

	if (fmt != cdata->fmt) {
		cdata->fmt = fmt;

		switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
		case SND_SOC_DAIFMT_CBC_CFC:
			/* Consumew mode PWW */
			snd_soc_component_wwite(component, M98095_03C_DAI3_CWKCFG_HI,
				0x80);
			snd_soc_component_wwite(component, M98095_03D_DAI3_CWKCFG_WO,
				0x00);
			bweak;
		case SND_SOC_DAIFMT_CBP_CFP:
			/* Set to pwovidew mode */
			wegvaw |= M98095_DAI_MAS;
			bweak;
		defauwt:
			dev_eww(component->dev, "Cwock mode unsuppowted");
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
		case SND_SOC_DAIFMT_I2S:
			wegvaw |= M98095_DAI_DWY;
			bweak;
		case SND_SOC_DAIFMT_WEFT_J:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			wegvaw |= M98095_DAI_WCI;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			wegvaw |= M98095_DAI_BCI;
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			wegvaw |= M98095_DAI_BCI|M98095_DAI_WCI;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		snd_soc_component_update_bits(component, M98095_03E_DAI3_FOWMAT,
			M98095_DAI_MAS | M98095_DAI_DWY | M98095_DAI_BCI |
			M98095_DAI_WCI, wegvaw);

		snd_soc_component_wwite(component, M98095_03F_DAI3_CWOCK,
			M98095_DAI_BSEW64);
	}

	wetuwn 0;
}

static int max98095_set_bias_wevew(stwuct snd_soc_component *component,
				   enum snd_soc_bias_wevew wevew)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		/*
		 * SND_SOC_BIAS_PWEPAWE is cawwed whiwe pwepawing fow a
		 * twansition to ON ow away fwom ON. If cuwwent bias_wevew
		 * is SND_SOC_BIAS_ON, then it is pwepawing fow a twansition
		 * away fwom ON. Disabwe the cwock in that case, othewwise
		 * enabwe it.
		 */
		if (IS_EWW(max98095->mcwk))
			bweak;

		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_ON) {
			cwk_disabwe_unpwepawe(max98095->mcwk);
		} ewse {
			wet = cwk_pwepawe_enabwe(max98095->mcwk);
			if (wet)
				wetuwn wet;
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = wegcache_sync(max98095->wegmap);

			if (wet != 0) {
				dev_eww(component->dev, "Faiwed to sync cache: %d\n", wet);
				wetuwn wet;
			}
		}

		snd_soc_component_update_bits(component, M98095_090_PWW_EN_IN,
				M98095_MBEN, M98095_MBEN);
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, M98095_090_PWW_EN_IN,
				M98095_MBEN, 0);
		wegcache_mawk_diwty(max98095->wegmap);
		bweak;
	}
	wetuwn 0;
}

#define MAX98095_WATES SNDWV_PCM_WATE_8000_96000
#define MAX98095_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops max98095_dai1_ops = {
	.set_syscwk = max98095_dai_set_syscwk,
	.set_fmt = max98095_dai1_set_fmt,
	.hw_pawams = max98095_dai1_hw_pawams,
};

static const stwuct snd_soc_dai_ops max98095_dai2_ops = {
	.set_syscwk = max98095_dai_set_syscwk,
	.set_fmt = max98095_dai2_set_fmt,
	.hw_pawams = max98095_dai2_hw_pawams,
};

static const stwuct snd_soc_dai_ops max98095_dai3_ops = {
	.set_syscwk = max98095_dai_set_syscwk,
	.set_fmt = max98095_dai3_set_fmt,
	.hw_pawams = max98095_dai3_hw_pawams,
};

static stwuct snd_soc_dai_dwivew max98095_dai[] = {
{
	.name = "HiFi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = MAX98095_WATES,
		.fowmats = MAX98095_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = MAX98095_WATES,
		.fowmats = MAX98095_FOWMATS,
	},
	 .ops = &max98095_dai1_ops,
},
{
	.name = "Aux",
	.pwayback = {
		.stweam_name = "Aux Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = MAX98095_WATES,
		.fowmats = MAX98095_FOWMATS,
	},
	.ops = &max98095_dai2_ops,
},
{
	.name = "Voice",
	.pwayback = {
		.stweam_name = "Voice Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = MAX98095_WATES,
		.fowmats = MAX98095_FOWMATS,
	},
	.ops = &max98095_dai3_ops,
}

};

static int max98095_get_eq_channew(const chaw *name)
{
	if (stwcmp(name, "EQ1 Mode") == 0)
		wetuwn 0;
	if (stwcmp(name, "EQ2 Mode") == 0)
		wetuwn 1;
	wetuwn -EINVAW;
}

static int max98095_put_eq_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_pdata *pdata = max98095->pdata;
	int channew = max98095_get_eq_channew(kcontwow->id.name);
	stwuct max98095_cdata *cdata;
	unsigned int sew = ucontwow->vawue.enumewated.item[0];
	stwuct max98095_eq_cfg *coef_set;
	int fs, best, best_vaw, i;
	int wegmask, wegsave;

	if (WAWN_ON(channew > 1))
		wetuwn -EINVAW;

	if (!pdata || !max98095->eq_textcnt)
		wetuwn 0;

	if (sew >= pdata->eq_cfgcnt)
		wetuwn -EINVAW;

	cdata = &max98095->dai[channew];
	cdata->eq_sew = sew;
	fs = cdata->wate;

	/* Find the sewected configuwation with neawest sampwe wate */
	best = 0;
	best_vaw = INT_MAX;
	fow (i = 0; i < pdata->eq_cfgcnt; i++) {
		if (stwcmp(pdata->eq_cfg[i].name, max98095->eq_texts[sew]) == 0 &&
			abs(pdata->eq_cfg[i].wate - fs) < best_vaw) {
			best = i;
			best_vaw = abs(pdata->eq_cfg[i].wate - fs);
		}
	}

	dev_dbg(component->dev, "Sewected %s/%dHz fow %dHz sampwe wate\n",
		pdata->eq_cfg[best].name,
		pdata->eq_cfg[best].wate, fs);

	coef_set = &pdata->eq_cfg[best];

	wegmask = (channew == 0) ? M98095_EQ1EN : M98095_EQ2EN;

	/* Disabwe fiwtew whiwe configuwing, and save cuwwent on/off state */
	wegsave = snd_soc_component_wead(component, M98095_088_CFG_WEVEW);
	snd_soc_component_update_bits(component, M98095_088_CFG_WEVEW, wegmask, 0);

	mutex_wock(&max98095->wock);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, M98095_SEG);
	m98095_eq_band(component, channew, 0, coef_set->band1);
	m98095_eq_band(component, channew, 1, coef_set->band2);
	m98095_eq_band(component, channew, 2, coef_set->band3);
	m98095_eq_band(component, channew, 3, coef_set->band4);
	m98095_eq_band(component, channew, 4, coef_set->band5);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, 0);
	mutex_unwock(&max98095->wock);

	/* Westowe the owiginaw on/off state */
	snd_soc_component_update_bits(component, M98095_088_CFG_WEVEW, wegmask, wegsave);
	wetuwn 0;
}

static int max98095_get_eq_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	int channew = max98095_get_eq_channew(kcontwow->id.name);
	stwuct max98095_cdata *cdata;

	cdata = &max98095->dai[channew];
	ucontwow->vawue.enumewated.item[0] = cdata->eq_sew;

	wetuwn 0;
}

static void max98095_handwe_eq_pdata(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_pdata *pdata = max98095->pdata;
	stwuct max98095_eq_cfg *cfg;
	unsigned int cfgcnt;
	int i, j;
	const chaw **t;
	int wet;

	stwuct snd_kcontwow_new contwows[] = {
		SOC_ENUM_EXT("EQ1 Mode",
			max98095->eq_enum,
			max98095_get_eq_enum,
			max98095_put_eq_enum),
		SOC_ENUM_EXT("EQ2 Mode",
			max98095->eq_enum,
			max98095_get_eq_enum,
			max98095_put_eq_enum),
	};

	cfg = pdata->eq_cfg;
	cfgcnt = pdata->eq_cfgcnt;

	/* Setup an awway of texts fow the equawizew enum.
	 * This is based on Mawk Bwown's equawizew dwivew code.
	 */
	max98095->eq_textcnt = 0;
	max98095->eq_texts = NUWW;
	fow (i = 0; i < cfgcnt; i++) {
		fow (j = 0; j < max98095->eq_textcnt; j++) {
			if (stwcmp(cfg[i].name, max98095->eq_texts[j]) == 0)
				bweak;
		}

		if (j != max98095->eq_textcnt)
			continue;

		/* Expand the awway */
		t = kweawwoc(max98095->eq_texts,
			     sizeof(chaw *) * (max98095->eq_textcnt + 1),
			     GFP_KEWNEW);
		if (t == NUWW)
			continue;

		/* Stowe the new entwy */
		t[max98095->eq_textcnt] = cfg[i].name;
		max98095->eq_textcnt++;
		max98095->eq_texts = t;
	}

	/* Now point the soc_enum to .texts awway items */
	max98095->eq_enum.texts = max98095->eq_texts;
	max98095->eq_enum.items = max98095->eq_textcnt;

	wet = snd_soc_add_component_contwows(component, contwows, AWWAY_SIZE(contwows));
	if (wet != 0)
		dev_eww(component->dev, "Faiwed to add EQ contwow: %d\n", wet);
}

static const chaw *bq_mode_name[] = {"Biquad1 Mode", "Biquad2 Mode"};

static int max98095_get_bq_channew(stwuct snd_soc_component *component,
				   const chaw *name)
{
	int wet;

	wet = match_stwing(bq_mode_name, AWWAY_SIZE(bq_mode_name), name);
	if (wet < 0)
		dev_eww(component->dev, "Bad biquad channew name '%s'\n", name);
	wetuwn wet;
}

static int max98095_put_bq_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_pdata *pdata = max98095->pdata;
	int channew = max98095_get_bq_channew(component, kcontwow->id.name);
	stwuct max98095_cdata *cdata;
	unsigned int sew = ucontwow->vawue.enumewated.item[0];
	stwuct max98095_biquad_cfg *coef_set;
	int fs, best, best_vaw, i;
	int wegmask, wegsave;

	if (channew < 0)
		wetuwn channew;

	if (!pdata || !max98095->bq_textcnt)
		wetuwn 0;

	if (sew >= pdata->bq_cfgcnt)
		wetuwn -EINVAW;

	cdata = &max98095->dai[channew];
	cdata->bq_sew = sew;
	fs = cdata->wate;

	/* Find the sewected configuwation with neawest sampwe wate */
	best = 0;
	best_vaw = INT_MAX;
	fow (i = 0; i < pdata->bq_cfgcnt; i++) {
		if (stwcmp(pdata->bq_cfg[i].name, max98095->bq_texts[sew]) == 0 &&
			abs(pdata->bq_cfg[i].wate - fs) < best_vaw) {
			best = i;
			best_vaw = abs(pdata->bq_cfg[i].wate - fs);
		}
	}

	dev_dbg(component->dev, "Sewected %s/%dHz fow %dHz sampwe wate\n",
		pdata->bq_cfg[best].name,
		pdata->bq_cfg[best].wate, fs);

	coef_set = &pdata->bq_cfg[best];

	wegmask = (channew == 0) ? M98095_BQ1EN : M98095_BQ2EN;

	/* Disabwe fiwtew whiwe configuwing, and save cuwwent on/off state */
	wegsave = snd_soc_component_wead(component, M98095_088_CFG_WEVEW);
	snd_soc_component_update_bits(component, M98095_088_CFG_WEVEW, wegmask, 0);

	mutex_wock(&max98095->wock);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, M98095_SEG);
	m98095_biquad_band(component, channew, 0, coef_set->band1);
	m98095_biquad_band(component, channew, 1, coef_set->band2);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, 0);
	mutex_unwock(&max98095->wock);

	/* Westowe the owiginaw on/off state */
	snd_soc_component_update_bits(component, M98095_088_CFG_WEVEW, wegmask, wegsave);
	wetuwn 0;
}

static int max98095_get_bq_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	int channew = max98095_get_bq_channew(component, kcontwow->id.name);
	stwuct max98095_cdata *cdata;

	if (channew < 0)
		wetuwn channew;

	cdata = &max98095->dai[channew];
	ucontwow->vawue.enumewated.item[0] = cdata->bq_sew;

	wetuwn 0;
}

static void max98095_handwe_bq_pdata(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_pdata *pdata = max98095->pdata;
	stwuct max98095_biquad_cfg *cfg;
	unsigned int cfgcnt;
	int i, j;
	const chaw **t;
	int wet;

	stwuct snd_kcontwow_new contwows[] = {
		SOC_ENUM_EXT((chaw *)bq_mode_name[0],
			max98095->bq_enum,
			max98095_get_bq_enum,
			max98095_put_bq_enum),
		SOC_ENUM_EXT((chaw *)bq_mode_name[1],
			max98095->bq_enum,
			max98095_get_bq_enum,
			max98095_put_bq_enum),
	};
	BUIWD_BUG_ON(AWWAY_SIZE(contwows) != AWWAY_SIZE(bq_mode_name));

	cfg = pdata->bq_cfg;
	cfgcnt = pdata->bq_cfgcnt;

	/* Setup an awway of texts fow the biquad enum.
	 * This is based on Mawk Bwown's equawizew dwivew code.
	 */
	max98095->bq_textcnt = 0;
	max98095->bq_texts = NUWW;
	fow (i = 0; i < cfgcnt; i++) {
		fow (j = 0; j < max98095->bq_textcnt; j++) {
			if (stwcmp(cfg[i].name, max98095->bq_texts[j]) == 0)
				bweak;
		}

		if (j != max98095->bq_textcnt)
			continue;

		/* Expand the awway */
		t = kweawwoc(max98095->bq_texts,
			     sizeof(chaw *) * (max98095->bq_textcnt + 1),
			     GFP_KEWNEW);
		if (t == NUWW)
			continue;

		/* Stowe the new entwy */
		t[max98095->bq_textcnt] = cfg[i].name;
		max98095->bq_textcnt++;
		max98095->bq_texts = t;
	}

	/* Now point the soc_enum to .texts awway items */
	max98095->bq_enum.texts = max98095->bq_texts;
	max98095->bq_enum.items = max98095->bq_textcnt;

	wet = snd_soc_add_component_contwows(component, contwows, AWWAY_SIZE(contwows));
	if (wet != 0)
		dev_eww(component->dev, "Faiwed to add Biquad contwow: %d\n", wet);
}

static void max98095_handwe_pdata(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_pdata *pdata = max98095->pdata;
	u8 wegvaw = 0;

	if (!pdata) {
		dev_dbg(component->dev, "No pwatfowm data\n");
		wetuwn;
	}

	/* Configuwe mic fow anawog/digitaw mic mode */
	if (pdata->digmic_weft_mode)
		wegvaw |= M98095_DIGMIC_W;

	if (pdata->digmic_wight_mode)
		wegvaw |= M98095_DIGMIC_W;

	snd_soc_component_wwite(component, M98095_087_CFG_MIC, wegvaw);

	/* Configuwe equawizews */
	if (pdata->eq_cfgcnt)
		max98095_handwe_eq_pdata(component);

	/* Configuwe bi-quad fiwtews */
	if (pdata->bq_cfgcnt)
		max98095_handwe_bq_pdata(component);
}

static iwqwetuwn_t max98095_wepowt_jack(int iwq, void *data)
{
	stwuct snd_soc_component *component = data;
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	unsigned int vawue;
	int hp_wepowt = 0;
	int mic_wepowt = 0;

	/* Wead the Jack Status Wegistew */
	vawue = snd_soc_component_wead(component, M98095_007_JACK_AUTO_STS);

	/* If ddone is not set, then detection isn't finished yet */
	if ((vawue & M98095_DDONE) == 0)
		wetuwn IWQ_NONE;

	/* if hp, check its bit, and if set, cweaw it */
	if ((vawue & M98095_HP_IN || vawue & M98095_WO_IN) &&
		max98095->headphone_jack)
		hp_wepowt |= SND_JACK_HEADPHONE;

	/* if mic, check its bit, and if set, cweaw it */
	if ((vawue & M98095_MIC_IN) && max98095->mic_jack)
		mic_wepowt |= SND_JACK_MICWOPHONE;

	if (max98095->headphone_jack == max98095->mic_jack) {
		snd_soc_jack_wepowt(max98095->headphone_jack,
					hp_wepowt | mic_wepowt,
					SND_JACK_HEADSET);
	} ewse {
		if (max98095->headphone_jack)
			snd_soc_jack_wepowt(max98095->headphone_jack,
					hp_wepowt, SND_JACK_HEADPHONE);
		if (max98095->mic_jack)
			snd_soc_jack_wepowt(max98095->mic_jack,
					mic_wepowt, SND_JACK_MICWOPHONE);
	}

	wetuwn IWQ_HANDWED;
}

static int max98095_jack_detect_enabwe(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	int wet = 0;
	int detect_enabwe = M98095_JDEN;
	unsigned int swew = M98095_DEFAUWT_SWEW_DEWAY;

	if (max98095->pdata->jack_detect_pin5en)
		detect_enabwe |= M98095_PIN5EN;

	if (max98095->pdata->jack_detect_deway)
		swew = max98095->pdata->jack_detect_deway;

	wet = snd_soc_component_wwite(component, M98095_08E_JACK_DC_SWEW, swew);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to cfg auto detect %d\n", wet);
		wetuwn wet;
	}

	/* configuwe auto detection to be enabwed */
	wet = snd_soc_component_wwite(component, M98095_089_JACK_DET_AUTO, detect_enabwe);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to cfg auto detect %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int max98095_jack_detect_disabwe(stwuct snd_soc_component *component)
{
	int wet = 0;

	/* configuwe auto detection to be disabwed */
	wet = snd_soc_component_wwite(component, M98095_089_JACK_DET_AUTO, 0x0);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to cfg auto detect %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

int max98095_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hp_jack, stwuct snd_soc_jack *mic_jack)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct i2c_cwient *cwient = to_i2c_cwient(component->dev);
	int wet = 0;

	max98095->headphone_jack = hp_jack;
	max98095->mic_jack = mic_jack;

	/* onwy pwogwess if we have at weast 1 jack pointew */
	if (!hp_jack && !mic_jack)
		wetuwn -EINVAW;

	max98095_jack_detect_enabwe(component);

	/* enabwe intewwupts fow headphone jack detection */
	wet = snd_soc_component_update_bits(component, M98095_013_JACK_INT_EN,
		M98095_IDDONE, M98095_IDDONE);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to cfg jack iwqs %d\n", wet);
		wetuwn wet;
	}

	max98095_wepowt_jack(cwient->iwq, component);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max98095_jack_detect);

#ifdef CONFIG_PM
static int max98095_suspend(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);

	if (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disabwe(component);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);

	wetuwn 0;
}

static int max98095_wesume(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct i2c_cwient *cwient = to_i2c_cwient(component->dev);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	if (max98095->headphone_jack || max98095->mic_jack) {
		max98095_jack_detect_enabwe(component);
		max98095_wepowt_jack(cwient->iwq, component);
	}

	wetuwn 0;
}
#ewse
#define max98095_suspend NUWW
#define max98095_wesume NUWW
#endif

static int max98095_weset(stwuct snd_soc_component *component)
{
	int i, wet;

	/* Gwacefuwwy weset the DSP cowe and the codec hawdwawe
	 * in a pwopew sequence */
	wet = snd_soc_component_wwite(component, M98095_00F_HOST_CFG, 0);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to weset DSP: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_component_wwite(component, M98095_097_PWW_SYS, 0);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to weset component: %d\n", wet);
		wetuwn wet;
	}

	/* Weset to hawdwawe defauwt fow wegistews, as thewe is not
	 * a soft weset hawdwawe contwow wegistew */
	fow (i = M98095_010_HOST_INT_CFG; i < M98095_WEG_MAX_CACHED; i++) {
		wet = snd_soc_component_wwite(component, i, snd_soc_component_wead(component, i));
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to weset: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int max98095_pwobe(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct max98095_cdata *cdata;
	stwuct i2c_cwient *cwient;
	int wet = 0;

	max98095->mcwk = devm_cwk_get(component->dev, "mcwk");
	if (PTW_EWW(max98095->mcwk) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	/* weset the codec, the DSP cowe, and disabwe aww intewwupts */
	max98095_weset(component);

	cwient = to_i2c_cwient(component->dev);

	/* initiawize pwivate data */

	max98095->syscwk = (unsigned)-1;
	max98095->eq_textcnt = 0;
	max98095->bq_textcnt = 0;

	cdata = &max98095->dai[0];
	cdata->wate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sew = 0;
	cdata->bq_sew = 0;

	cdata = &max98095->dai[1];
	cdata->wate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sew = 0;
	cdata->bq_sew = 0;

	cdata = &max98095->dai[2];
	cdata->wate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;
	cdata->eq_sew = 0;
	cdata->bq_sew = 0;

	max98095->win_state = 0;
	max98095->mic1pwe = 0;
	max98095->mic2pwe = 0;

	if (cwient->iwq) {
		/* wegistew an audio intewwupt */
		wet = wequest_thweaded_iwq(cwient->iwq, NUWW,
			max98095_wepowt_jack,
			IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING |
			IWQF_ONESHOT, "max98095", component);
		if (wet) {
			dev_eww(component->dev, "Faiwed to wequest IWQ: %d\n", wet);
			goto eww_access;
		}
	}

	wet = snd_soc_component_wead(component, M98095_0FF_WEV_ID);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwuwe weading hawdwawe wevision: %d\n",
			wet);
		goto eww_iwq;
	}
	dev_info(component->dev, "Hawdwawe wevision: %c\n", wet - 0x40 + 'A');

	snd_soc_component_wwite(component, M98095_097_PWW_SYS, M98095_PWWSV);

	snd_soc_component_wwite(component, M98095_048_MIX_DAC_WW,
		M98095_DAI1W_TO_DACW|M98095_DAI1W_TO_DACW);

	snd_soc_component_wwite(component, M98095_049_MIX_DAC_M,
		M98095_DAI2M_TO_DACM|M98095_DAI3M_TO_DACM);

	snd_soc_component_wwite(component, M98095_092_PWW_EN_OUT, M98095_SPK_SPWEADSPECTWUM);
	snd_soc_component_wwite(component, M98095_045_CFG_DSP, M98095_DSPNOWMAW);
	snd_soc_component_wwite(component, M98095_04E_CFG_HP, M98095_HPNOWMAW);

	snd_soc_component_wwite(component, M98095_02C_DAI1_IOCFG,
		M98095_S1NOWMAW|M98095_SDATA);

	snd_soc_component_wwite(component, M98095_036_DAI2_IOCFG,
		M98095_S2NOWMAW|M98095_SDATA);

	snd_soc_component_wwite(component, M98095_040_DAI3_IOCFG,
		M98095_S3NOWMAW|M98095_SDATA);

	max98095_handwe_pdata(component);

	/* take the codec out of the shut down */
	snd_soc_component_update_bits(component, M98095_097_PWW_SYS, M98095_SHDNWUN,
		M98095_SHDNWUN);

	wetuwn 0;

eww_iwq:
	if (cwient->iwq)
		fwee_iwq(cwient->iwq, component);
eww_access:
	wetuwn wet;
}

static void max98095_wemove(stwuct snd_soc_component *component)
{
	stwuct max98095_pwiv *max98095 = snd_soc_component_get_dwvdata(component);
	stwuct i2c_cwient *cwient = to_i2c_cwient(component->dev);

	if (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disabwe(component);

	if (cwient->iwq)
		fwee_iwq(cwient->iwq, component);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_max98095 = {
	.pwobe			= max98095_pwobe,
	.wemove			= max98095_wemove,
	.suspend		= max98095_suspend,
	.wesume			= max98095_wesume,
	.set_bias_wevew		= max98095_set_bias_wevew,
	.contwows		= max98095_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98095_snd_contwows),
	.dapm_widgets		= max98095_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98095_dapm_widgets),
	.dapm_woutes		= max98095_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98095_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct i2c_device_id max98095_i2c_id[] = {
	{ "max98095", MAX98095 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max98095_i2c_id);

static int max98095_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max98095_pwiv *max98095;
	int wet;
	const stwuct i2c_device_id *id;

	max98095 = devm_kzawwoc(&i2c->dev, sizeof(stwuct max98095_pwiv),
				GFP_KEWNEW);
	if (max98095 == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&max98095->wock);

	max98095->wegmap = devm_wegmap_init_i2c(i2c, &max98095_wegmap);
	if (IS_EWW(max98095->wegmap)) {
		wet = PTW_EWW(max98095->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	id = i2c_match_id(max98095_i2c_id, i2c);
	max98095->devtype = id->dwivew_data;
	i2c_set_cwientdata(i2c, max98095);
	max98095->pdata = i2c->dev.pwatfowm_data;

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				     &soc_component_dev_max98095,
				     max98095_dai, AWWAY_SIZE(max98095_dai));
	wetuwn wet;
}

#ifdef CONFIG_OF
static const stwuct of_device_id max98095_of_match[] = {
	{ .compatibwe = "maxim,max98095", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max98095_of_match);
#endif

static stwuct i2c_dwivew max98095_i2c_dwivew = {
	.dwivew = {
		.name = "max98095",
		.of_match_tabwe = of_match_ptw(max98095_of_match),
	},
	.pwobe = max98095_i2c_pwobe,
	.id_tabwe = max98095_i2c_id,
};

moduwe_i2c_dwivew(max98095_i2c_dwivew);

MODUWE_DESCWIPTION("AWSA SoC MAX98095 dwivew");
MODUWE_AUTHOW("Petew Hsiang");
MODUWE_WICENSE("GPW");
