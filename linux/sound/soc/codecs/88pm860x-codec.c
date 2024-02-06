// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 88pm860x-codec.c -- 88PM860x AWSA SoC Audio Dwivew
 *
 * Copywight 2010 Mawveww Intewnationaw Wtd.
 * Authow: Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>
#incwude <sound/jack.h>
#incwude <twace/events/asoc.h>

#incwude "88pm860x-codec.h"

#define MAX_NAME_WEN		20
#define WEG_CACHE_SIZE		0x40
#define WEG_CACHE_BASE		0xb0

/* Status Wegistew 1 (0x01) */
#define WEG_STATUS_1		0x01
#define MIC_STATUS		(1 << 7)
#define HOOK_STATUS		(1 << 6)
#define HEADSET_STATUS		(1 << 5)

/* Mic Detection Wegistew (0x37) */
#define WEG_MIC_DET		0x37
#define CONTINUOUS_POWWING	(3 << 1)
#define EN_MIC_DET		(1 << 0)
#define MICDET_MASK		0x07

/* Headset Detection Wegistew (0x38) */
#define WEG_HS_DET		0x38
#define EN_HS_DET		(1 << 0)

/* Misc2 Wegistew (0x42) */
#define WEG_MISC2		0x42
#define AUDIO_PWW		(1 << 5)
#define AUDIO_SECTION_WESET	(1 << 4)
#define AUDIO_SECTION_ON	(1 << 3)

/* PCM Intewface Wegistew 2 (0xb1) */
#define PCM_INF2_BCWK		(1 << 6)	/* Bit cwock powawity */
#define PCM_INF2_FS		(1 << 5)	/* Fwame Sync powawity */
#define PCM_INF2_MASTEW		(1 << 4)	/* Mastew / Swave */
#define PCM_INF2_18WW		(1 << 3)	/* 18 / 16 bits */
#define PCM_GENEWAW_I2S		0
#define PCM_EXACT_I2S		1
#define PCM_WEFT_I2S		2
#define PCM_WIGHT_I2S		3
#define PCM_SHOWT_FS		4
#define PCM_WONG_FS		5
#define PCM_MODE_MASK		7

/* I2S Intewface Wegistew 4 (0xbe) */
#define I2S_EQU_BYP		(1 << 6)

/* DAC Offset Wegistew (0xcb) */
#define DAC_MUTE		(1 << 7)
#define MUTE_WEFT		(1 << 6)
#define MUTE_WIGHT		(1 << 2)

/* ADC Anawog Wegistew 1 (0xd0) */
#define WEG_ADC_ANA_1		0xd0
#define MIC1BIAS_MASK		0x60

/* Eawpiece/Speakew Contwow Wegistew 2 (0xda) */
#define WEG_EAW2		0xda
#define WSYNC_CHANGE		(1 << 2)

/* Audio Suppwies Wegistew 2 (0xdc) */
#define WEG_SUPPWIES2		0xdc
#define WDO15_WEADY		(1 << 4)
#define WDO15_EN		(1 << 3)
#define CPUMP_WEADY		(1 << 2)
#define CPUMP_EN		(1 << 1)
#define AUDIO_EN		(1 << 0)
#define SUPPWY_MASK		(WDO15_EN | CPUMP_EN | AUDIO_EN)

/* Audio Enabwe Wegistew 1 (0xdd) */
#define ADC_MOD_WIGHT		(1 << 1)
#define ADC_MOD_WEFT		(1 << 0)

/* Audio Enabwe Wegistew 2 (0xde) */
#define ADC_WEFT		(1 << 5)
#define ADC_WIGHT		(1 << 4)

/* DAC Enabwe Wegistew 2 (0xe1) */
#define DAC_WEFT		(1 << 5)
#define DAC_WIGHT		(1 << 4)
#define MODUWATOW		(1 << 3)

/* Showts Wegistew (0xeb) */
#define WEG_SHOWTS		0xeb
#define CWW_SHOWT_WO2		(1 << 7)
#define SHOWT_WO2		(1 << 6)
#define CWW_SHOWT_WO1		(1 << 5)
#define SHOWT_WO1		(1 << 4)
#define CWW_SHOWT_HS2		(1 << 3)
#define SHOWT_HS2		(1 << 2)
#define CWW_SHOWT_HS1		(1 << 1)
#define SHOWT_HS1		(1 << 0)

/*
 * This widget shouwd be just aftew DAC & PGA in DAPM powew-on sequence and
 * befowe DAC & PGA in DAPM powew-off sequence.
 */
#define PM860X_DAPM_OUTPUT(wname, wevent)	\
	SND_SOC_DAPM_PGA_E(wname, SND_SOC_NOPM, 0, 0, NUWW, 0, wevent, \
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD)

stwuct pm860x_det {
	stwuct snd_soc_jack	*hp_jack;
	stwuct snd_soc_jack	*mic_jack;
	int			hp_det;
	int			mic_det;
	int			hook_det;
	int			hs_shwt;
	int			wo_shwt;
};

stwuct pm860x_pwiv {
	unsigned int		syscwk;
	unsigned int		pcmcwk;
	unsigned int		diw;
	unsigned int		fiwtew;
	stwuct snd_soc_component *component;
	stwuct i2c_cwient	*i2c;
	stwuct wegmap		*wegmap;
	stwuct pm860x_chip	*chip;
	stwuct pm860x_det	det;

	int			iwq[4];
	unsigned chaw		name[4][MAX_NAME_WEN];
};

/* -9450dB to 0dB in 150dB steps ( mute instead of -9450dB) */
static const DECWAWE_TWV_DB_SCAWE(dpga_twv, -9450, 150, 1);

/* -9dB to 0db in 3dB steps */
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -900, 300, 0);

/* {-23, -17, -13.5, -11, -9, -6, -3, 0}dB */
static const DECWAWE_TWV_DB_WANGE(mic_twv,
	0, 0, TWV_DB_SCAWE_ITEM(-2300, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(-1700, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(-1350, 0, 0),
	3, 3, TWV_DB_SCAWE_ITEM(-1100, 0, 0),
	4, 7, TWV_DB_SCAWE_ITEM(-900, 300, 0)
);

/* {0, 0, 0, -6, 0, 6, 12, 18}dB */
static const DECWAWE_TWV_DB_WANGE(aux_twv,
	0, 2, TWV_DB_SCAWE_ITEM(0, 0, 0),
	3, 7, TWV_DB_SCAWE_ITEM(-600, 600, 0)
);

/* {-16, -13, -10, -7, -5.2, -3,3, -2.2, 0}dB, mute instead of -16dB */
static const DECWAWE_TWV_DB_WANGE(out_twv,
	0, 3, TWV_DB_SCAWE_ITEM(-1600, 300, 1),
	4, 4, TWV_DB_SCAWE_ITEM(-520, 0, 0),
	5, 5, TWV_DB_SCAWE_ITEM(-330, 0, 0),
	6, 7, TWV_DB_SCAWE_ITEM(-220, 220, 0)
);

static const DECWAWE_TWV_DB_WANGE(st_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-12041, 602, 0),
	2, 3, TWV_DB_SCAWE_ITEM(-11087, 250, 0),
	4, 5, TWV_DB_SCAWE_ITEM(-10643, 158, 0),
	6, 7, TWV_DB_SCAWE_ITEM(-10351, 116, 0),
	8, 9, TWV_DB_SCAWE_ITEM(-10133, 92, 0),
	10, 13, TWV_DB_SCAWE_ITEM(-9958, 70, 0),
	14, 17, TWV_DB_SCAWE_ITEM(-9689, 53, 0),
	18, 271, TWV_DB_SCAWE_ITEM(-9484, 37, 0)
);

/* Sidetone Gain = M * 2^(-5-N) */
stwuct st_gain {
	unsigned int	db;
	unsigned int	m;
	unsigned int	n;
};

static stwuct st_gain st_tabwe[] = {
	{-12041,  1, 15}, {-11439,  1, 14}, {-11087,  3, 15}, {-10837,  1, 13},
	{-10643,  5, 15}, {-10485,  3, 14}, {-10351,  7, 15}, {-10235,  1, 12},
	{-10133,  9, 15}, {-10041,  5, 14}, { -9958, 11, 15}, { -9883,  3, 13},
	{ -9813, 13, 15}, { -9749,  7, 14}, { -9689, 15, 15}, { -9633,  1, 11},
	{ -9580, 17, 15}, { -9531,  9, 14}, { -9484, 19, 15}, { -9439,  5, 13},
	{ -9397, 21, 15}, { -9356, 11, 14}, { -9318, 23, 15}, { -9281,  3, 12},
	{ -9245, 25, 15}, { -9211, 13, 14}, { -9178, 27, 15}, { -9147,  7, 13},
	{ -9116, 29, 15}, { -9087, 15, 14}, { -9058, 31, 15}, { -9031,  1, 10},
	{ -8978, 17, 14}, { -8929,  9, 13}, { -8882, 19, 14}, { -8837,  5, 12},
	{ -8795, 21, 14}, { -8754, 11, 13}, { -8716, 23, 14}, { -8679,  3, 11},
	{ -8643, 25, 14}, { -8609, 13, 13}, { -8576, 27, 14}, { -8545,  7, 12},
	{ -8514, 29, 14}, { -8485, 15, 13}, { -8456, 31, 14}, { -8429,  1,  9},
	{ -8376, 17, 13}, { -8327,  9, 12}, { -8280, 19, 13}, { -8235,  5, 11},
	{ -8193, 21, 13}, { -8152, 11, 12}, { -8114, 23, 13}, { -8077,  3, 10},
	{ -8041, 25, 13}, { -8007, 13, 12}, { -7974, 27, 13}, { -7943,  7, 11},
	{ -7912, 29, 13}, { -7883, 15, 12}, { -7854, 31, 13}, { -7827,  1,  8},
	{ -7774, 17, 12}, { -7724,  9, 11}, { -7678, 19, 12}, { -7633,  5, 10},
	{ -7591, 21, 12}, { -7550, 11, 11}, { -7512, 23, 12}, { -7475,  3,  9},
	{ -7439, 25, 12}, { -7405, 13, 11}, { -7372, 27, 12}, { -7341,  7, 10},
	{ -7310, 29, 12}, { -7281, 15, 11}, { -7252, 31, 12}, { -7225,  1,  7},
	{ -7172, 17, 11}, { -7122,  9, 10}, { -7075, 19, 11}, { -7031,  5,  9},
	{ -6989, 21, 11}, { -6948, 11, 10}, { -6910, 23, 11}, { -6873,  3,  8},
	{ -6837, 25, 11}, { -6803, 13, 10}, { -6770, 27, 11}, { -6739,  7,  9},
	{ -6708, 29, 11}, { -6679, 15, 10}, { -6650, 31, 11}, { -6623,  1,  6},
	{ -6570, 17, 10}, { -6520,  9,  9}, { -6473, 19, 10}, { -6429,  5,  8},
	{ -6386, 21, 10}, { -6346, 11,  9}, { -6307, 23, 10}, { -6270,  3,  7},
	{ -6235, 25, 10}, { -6201, 13,  9}, { -6168, 27, 10}, { -6137,  7,  8},
	{ -6106, 29, 10}, { -6077, 15,  9}, { -6048, 31, 10}, { -6021,  1,  5},
	{ -5968, 17,  9}, { -5918,  9,  8}, { -5871, 19,  9}, { -5827,  5,  7},
	{ -5784, 21,  9}, { -5744, 11,  8}, { -5705, 23,  9}, { -5668,  3,  6},
	{ -5633, 25,  9}, { -5599, 13,  8}, { -5566, 27,  9}, { -5535,  7,  7},
	{ -5504, 29,  9}, { -5475, 15,  8}, { -5446, 31,  9}, { -5419,  1,  4},
	{ -5366, 17,  8}, { -5316,  9,  7}, { -5269, 19,  8}, { -5225,  5,  6},
	{ -5182, 21,  8}, { -5142, 11,  7}, { -5103, 23,  8}, { -5066,  3,  5},
	{ -5031, 25,  8}, { -4997, 13,  7}, { -4964, 27,  8}, { -4932,  7,  6},
	{ -4902, 29,  8}, { -4873, 15,  7}, { -4844, 31,  8}, { -4816,  1,  3},
	{ -4764, 17,  7}, { -4714,  9,  6}, { -4667, 19,  7}, { -4623,  5,  5},
	{ -4580, 21,  7}, { -4540, 11,  6}, { -4501, 23,  7}, { -4464,  3,  4},
	{ -4429, 25,  7}, { -4395, 13,  6}, { -4362, 27,  7}, { -4330,  7,  5},
	{ -4300, 29,  7}, { -4270, 15,  6}, { -4242, 31,  7}, { -4214,  1,  2},
	{ -4162, 17,  6}, { -4112,  9,  5}, { -4065, 19,  6}, { -4021,  5,  4},
	{ -3978, 21,  6}, { -3938, 11,  5}, { -3899, 23,  6}, { -3862,  3,  3},
	{ -3827, 25,  6}, { -3793, 13,  5}, { -3760, 27,  6}, { -3728,  7,  4},
	{ -3698, 29,  6}, { -3668, 15,  5}, { -3640, 31,  6}, { -3612,  1,  1},
	{ -3560, 17,  5}, { -3510,  9,  4}, { -3463, 19,  5}, { -3419,  5,  3},
	{ -3376, 21,  5}, { -3336, 11,  4}, { -3297, 23,  5}, { -3260,  3,  2},
	{ -3225, 25,  5}, { -3191, 13,  4}, { -3158, 27,  5}, { -3126,  7,  3},
	{ -3096, 29,  5}, { -3066, 15,  4}, { -3038, 31,  5}, { -3010,  1,  0},
	{ -2958, 17,  4}, { -2908,  9,  3}, { -2861, 19,  4}, { -2816,  5,  2},
	{ -2774, 21,  4}, { -2734, 11,  3}, { -2695, 23,  4}, { -2658,  3,  1},
	{ -2623, 25,  4}, { -2589, 13,  3}, { -2556, 27,  4}, { -2524,  7,  2},
	{ -2494, 29,  4}, { -2464, 15,  3}, { -2436, 31,  4}, { -2408,  2,  0},
	{ -2356, 17,  3}, { -2306,  9,  2}, { -2259, 19,  3}, { -2214,  5,  1},
	{ -2172, 21,  3}, { -2132, 11,  2}, { -2093, 23,  3}, { -2056,  3,  0},
	{ -2021, 25,  3}, { -1987, 13,  2}, { -1954, 27,  3}, { -1922,  7,  1},
	{ -1892, 29,  3}, { -1862, 15,  2}, { -1834, 31,  3}, { -1806,  4,  0},
	{ -1754, 17,  2}, { -1704,  9,  1}, { -1657, 19,  2}, { -1612,  5,  0},
	{ -1570, 21,  2}, { -1530, 11,  1}, { -1491, 23,  2}, { -1454,  6,  0},
	{ -1419, 25,  2}, { -1384, 13,  1}, { -1352, 27,  2}, { -1320,  7,  0},
	{ -1290, 29,  2}, { -1260, 15,  1}, { -1232, 31,  2}, { -1204,  8,  0},
	{ -1151, 17,  1}, { -1102,  9,  0}, { -1055, 19,  1}, { -1010, 10,  0},
	{  -968, 21,  1}, {  -928, 11,  0}, {  -889, 23,  1}, {  -852, 12,  0},
	{  -816, 25,  1}, {  -782, 13,  0}, {  -750, 27,  1}, {  -718, 14,  0},
	{  -688, 29,  1}, {  -658, 15,  0}, {  -630, 31,  1}, {  -602, 16,  0},
	{  -549, 17,  0}, {  -500, 18,  0}, {  -453, 19,  0}, {  -408, 20,  0},
	{  -366, 21,  0}, {  -325, 22,  0}, {  -287, 23,  0}, {  -250, 24,  0},
	{  -214, 25,  0}, {  -180, 26,  0}, {  -148, 27,  0}, {  -116, 28,  0},
	{   -86, 29,  0}, {   -56, 30,  0}, {   -28, 31,  0}, {     0,  0,  0},
};

static int snd_soc_get_vowsw_2w_st(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	int vaw[2], vaw2[2], i;

	vaw[0] = snd_soc_component_wead(component, weg) & 0x3f;
	vaw[1] = (snd_soc_component_wead(component, PM860X_SIDETONE_SHIFT) >> 4) & 0xf;
	vaw2[0] = snd_soc_component_wead(component, weg2) & 0x3f;
	vaw2[1] = (snd_soc_component_wead(component, PM860X_SIDETONE_SHIFT)) & 0xf;

	fow (i = 0; i < AWWAY_SIZE(st_tabwe); i++) {
		if ((st_tabwe[i].m == vaw[0]) && (st_tabwe[i].n == vaw[1]))
			ucontwow->vawue.integew.vawue[0] = i;
		if ((st_tabwe[i].m == vaw2[0]) && (st_tabwe[i].n == vaw2[1]))
			ucontwow->vawue.integew.vawue[1] = i;
	}
	wetuwn 0;
}

static int snd_soc_put_vowsw_2w_st(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	int eww;
	unsigned int vaw, vaw2;

	vaw = ucontwow->vawue.integew.vawue[0];
	vaw2 = ucontwow->vawue.integew.vawue[1];

	if (vaw >= AWWAY_SIZE(st_tabwe) || vaw2 >= AWWAY_SIZE(st_tabwe))
		wetuwn -EINVAW;

	eww = snd_soc_component_update_bits(component, weg, 0x3f, st_tabwe[vaw].m);
	if (eww < 0)
		wetuwn eww;
	eww = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0xf0,
				  st_tabwe[vaw].n << 4);
	if (eww < 0)
		wetuwn eww;

	eww = snd_soc_component_update_bits(component, weg2, 0x3f, st_tabwe[vaw2].m);
	if (eww < 0)
		wetuwn eww;
	eww = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0x0f,
				  st_tabwe[vaw2].n);
	wetuwn eww;
}

static int snd_soc_get_vowsw_2w_out(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	int max = mc->max, vaw, vaw2;
	unsigned int mask = (1 << fws(max)) - 1;

	vaw = snd_soc_component_wead(component, weg) >> shift;
	vaw2 = snd_soc_component_wead(component, weg2) >> shift;
	ucontwow->vawue.integew.vawue[0] = (max - vaw) & mask;
	ucontwow->vawue.integew.vawue[1] = (max - vaw2) & mask;

	wetuwn 0;
}

static int snd_soc_put_vowsw_2w_out(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	int eww;
	unsigned int vaw, vaw2, vaw_mask;

	vaw_mask = mask << shift;
	vaw = ((max - ucontwow->vawue.integew.vawue[0]) & mask);
	vaw2 = ((max - ucontwow->vawue.integew.vawue[1]) & mask);

	vaw = vaw << shift;
	vaw2 = vaw2 << shift;

	eww = snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
	if (eww < 0)
		wetuwn eww;

	eww = snd_soc_component_update_bits(component, weg2, vaw_mask, vaw2);
	wetuwn eww;
}

/* DAPM Widget Events */
/*
 * A wot wegistews awe bewong to WSYNC domain. It wequiwes enabwing WSYNC bit
 * aftew updating these wegistews. Othewwise, these updated wegistews won't
 * be effective.
 */
static int pm860x_wsync_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/*
	 * In owdew to avoid cuwwent on the woad, mute powew-on and powew-off
	 * shouwd be twansients.
	 * Unmute by DAC_MUTE. It shouwd be unmuted when DAPM sequence is
	 * finished.
	 */
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, DAC_MUTE, 0);
	snd_soc_component_update_bits(component, PM860X_EAW_CTWW_2,
			    WSYNC_CHANGE, WSYNC_CHANGE);
	wetuwn 0;
}

static int pm860x_dac_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int dac = 0;
	int data;

	if (!snd_soc_dapm_widget_name_cmp(w, "Weft DAC"))
		dac = DAC_WEFT;
	if (!snd_soc_dapm_widget_name_cmp(w, "Wight DAC"))
		dac = DAC_WIGHT;
	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (dac) {
			/* Auto mute in powew-on sequence. */
			dac |= MODUWATOW;
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAW_CTWW_2,
					    WSYNC_CHANGE, WSYNC_CHANGE);
			/* update dac */
			snd_soc_component_update_bits(component, PM860X_DAC_EN_2,
					    dac, dac);
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		if (dac) {
			/* Auto mute in powew-off sequence. */
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAW_CTWW_2,
					    WSYNC_CHANGE, WSYNC_CHANGE);
			/* update dac */
			data = snd_soc_component_wead(component, PM860X_DAC_EN_2);
			data &= ~dac;
			if (!(data & (DAC_WEFT | DAC_WIGHT)))
				data &= ~MODUWATOW;
			snd_soc_component_wwite(component, PM860X_DAC_EN_2, data);
		}
		bweak;
	}
	wetuwn 0;
}

static const chaw *pm860x_opamp_texts[] = {"-50%", "-25%", "0%", "75%"};

static const chaw *pm860x_pa_texts[] = {"-33%", "0%", "33%", "66%"};

static SOC_ENUM_SINGWE_DECW(pm860x_hs1_opamp_enum,
			    PM860X_HS1_CTWW, 5, pm860x_opamp_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_hs2_opamp_enum,
			    PM860X_HS2_CTWW, 5, pm860x_opamp_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_hs1_pa_enum,
			    PM860X_HS1_CTWW, 3, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_hs2_pa_enum,
			    PM860X_HS2_CTWW, 3, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_wo1_opamp_enum,
			    PM860X_WO1_CTWW, 5, pm860x_opamp_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_wo2_opamp_enum,
			    PM860X_WO2_CTWW, 5, pm860x_opamp_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_wo1_pa_enum,
			    PM860X_WO1_CTWW, 3, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_wo2_pa_enum,
			    PM860X_WO2_CTWW, 3, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_spk_pa_enum,
			    PM860X_EAW_CTWW_1, 5, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_eaw_pa_enum,
			    PM860X_EAW_CTWW_2, 0, pm860x_pa_texts);

static SOC_ENUM_SINGWE_DECW(pm860x_spk_eaw_opamp_enum,
			    PM860X_EAW_CTWW_1, 3, pm860x_opamp_texts);

static const stwuct snd_kcontwow_new pm860x_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("ADC Captuwe Vowume", PM860X_ADC_ANA_2,
			PM860X_ADC_ANA_3, 6, 3, 0, adc_twv),
	SOC_DOUBWE_TWV("AUX Captuwe Vowume", PM860X_ADC_ANA_3, 0, 3, 7, 0,
			aux_twv),
	SOC_SINGWE_TWV("MIC1 Captuwe Vowume", PM860X_ADC_ANA_2, 0, 7, 0,
			mic_twv),
	SOC_SINGWE_TWV("MIC3 Captuwe Vowume", PM860X_ADC_ANA_2, 3, 7, 0,
			mic_twv),
	SOC_DOUBWE_W_EXT_TWV("Sidetone Vowume", PM860X_SIDETONE_W_GAIN,
			     PM860X_SIDETONE_W_GAIN, 0, AWWAY_SIZE(st_tabwe)-1,
			     0, snd_soc_get_vowsw_2w_st,
			     snd_soc_put_vowsw_2w_st, st_twv),
	SOC_SINGWE_TWV("Speakew Pwayback Vowume", PM860X_EAW_CTWW_1,
			0, 7, 0, out_twv),
	SOC_DOUBWE_W_TWV("Wine Pwayback Vowume", PM860X_WO1_CTWW,
			 PM860X_WO2_CTWW, 0, 7, 0, out_twv),
	SOC_DOUBWE_W_TWV("Headset Pwayback Vowume", PM860X_HS1_CTWW,
			 PM860X_HS2_CTWW, 0, 7, 0, out_twv),
	SOC_DOUBWE_W_EXT_TWV("Hifi Weft Pwayback Vowume",
			     PM860X_HIFIW_GAIN_WEFT,
			     PM860X_HIFIW_GAIN_WIGHT, 0, 63, 0,
			     snd_soc_get_vowsw_2w_out,
			     snd_soc_put_vowsw_2w_out, dpga_twv),
	SOC_DOUBWE_W_EXT_TWV("Hifi Wight Pwayback Vowume",
			     PM860X_HIFIW_GAIN_WEFT,
			     PM860X_HIFIW_GAIN_WIGHT, 0, 63, 0,
			     snd_soc_get_vowsw_2w_out,
			     snd_soc_put_vowsw_2w_out, dpga_twv),
	SOC_DOUBWE_W_EXT_TWV("Wofi Pwayback Vowume", PM860X_WOFI_GAIN_WEFT,
			     PM860X_WOFI_GAIN_WIGHT, 0, 63, 0,
			     snd_soc_get_vowsw_2w_out,
			     snd_soc_put_vowsw_2w_out, dpga_twv),
	SOC_ENUM("Headset1 Opewationaw Ampwifiew Cuwwent",
		 pm860x_hs1_opamp_enum),
	SOC_ENUM("Headset2 Opewationaw Ampwifiew Cuwwent",
		 pm860x_hs2_opamp_enum),
	SOC_ENUM("Headset1 Ampwifiew Cuwwent", pm860x_hs1_pa_enum),
	SOC_ENUM("Headset2 Ampwifiew Cuwwent", pm860x_hs2_pa_enum),
	SOC_ENUM("Wineout1 Opewationaw Ampwifiew Cuwwent",
		 pm860x_wo1_opamp_enum),
	SOC_ENUM("Wineout2 Opewationaw Ampwifiew Cuwwent",
		 pm860x_wo2_opamp_enum),
	SOC_ENUM("Wineout1 Ampwifiew Cuwwent", pm860x_wo1_pa_enum),
	SOC_ENUM("Wineout2 Ampwifiew Cuwwent", pm860x_wo2_pa_enum),
	SOC_ENUM("Speakew Opewationaw Ampwifiew Cuwwent",
		 pm860x_spk_eaw_opamp_enum),
	SOC_ENUM("Speakew Ampwifiew Cuwwent", pm860x_spk_pa_enum),
	SOC_ENUM("Eawpiece Ampwifiew Cuwwent", pm860x_eaw_pa_enum),
};

/*
 * DAPM Contwows
 */

/* AUX1 Switch */
static const stwuct snd_kcontwow_new aux1_switch_contwows =
	SOC_DAPM_SINGWE("Switch", PM860X_ANA_TO_ANA, 4, 1, 0);

/* AUX2 Switch */
static const stwuct snd_kcontwow_new aux2_switch_contwows =
	SOC_DAPM_SINGWE("Switch", PM860X_ANA_TO_ANA, 5, 1, 0);

/* Weft Ex. PA Switch */
static const stwuct snd_kcontwow_new wepa_switch_contwows =
	SOC_DAPM_SINGWE("Switch", PM860X_DAC_EN_2, 2, 1, 0);

/* Wight Ex. PA Switch */
static const stwuct snd_kcontwow_new wepa_switch_contwows =
	SOC_DAPM_SINGWE("Switch", PM860X_DAC_EN_2, 1, 1, 0);

/* I2S Mux / Mux9 */
static const chaw *i2s_din_text[] = {
	"DIN", "DIN1",
};

static SOC_ENUM_SINGWE_DECW(i2s_din_enum,
			    PM860X_I2S_IFACE_3, 1, i2s_din_text);

static const stwuct snd_kcontwow_new i2s_din_mux =
	SOC_DAPM_ENUM("I2S DIN Mux", i2s_din_enum);

/* I2S Mic Mux / Mux8 */
static const chaw *i2s_mic_text[] = {
	"Ex PA", "ADC",
};

static SOC_ENUM_SINGWE_DECW(i2s_mic_enum,
			    PM860X_I2S_IFACE_3, 4, i2s_mic_text);

static const stwuct snd_kcontwow_new i2s_mic_mux =
	SOC_DAPM_ENUM("I2S Mic Mux", i2s_mic_enum);

/* ADCW Mux / Mux2 */
static const chaw *adcw_text[] = {
	"ADCW", "ADCW",
};

static SOC_ENUM_SINGWE_DECW(adcw_enum,
			    PM860X_PCM_IFACE_3, 4, adcw_text);

static const stwuct snd_kcontwow_new adcw_mux =
	SOC_DAPM_ENUM("ADC Weft Mux", adcw_enum);

/* ADCW Mux / Mux3 */
static const chaw *adcw_text[] = {
	"ADCW", "ADCW",
};

static SOC_ENUM_SINGWE_DECW(adcw_enum,
			    PM860X_PCM_IFACE_3, 2, adcw_text);

static const stwuct snd_kcontwow_new adcw_mux =
	SOC_DAPM_ENUM("ADC Wight Mux", adcw_enum);

/* ADCW EC Mux / Mux6 */
static const chaw *adcw_ec_text[] = {
	"ADCW", "EC",
};

static SOC_ENUM_SINGWE_DECW(adcw_ec_enum,
			    PM860X_ADC_EN_2, 3, adcw_ec_text);

static const stwuct snd_kcontwow_new adcw_ec_mux =
	SOC_DAPM_ENUM("ADCW EC Mux", adcw_ec_enum);

/* EC Mux / Mux4 */
static const chaw *ec_text[] = {
	"Weft", "Wight", "Weft + Wight",
};

static SOC_ENUM_SINGWE_DECW(ec_enum,
			    PM860X_EC_PATH, 1, ec_text);

static const stwuct snd_kcontwow_new ec_mux =
	SOC_DAPM_ENUM("EC Mux", ec_enum);

static const chaw *dac_text[] = {
	"No input", "Wight", "Weft", "No input",
};

/* DAC Headset 1 Mux / Mux10 */
static SOC_ENUM_SINGWE_DECW(dac_hs1_enum,
			    PM860X_ANA_INPUT_SEW_1, 0, dac_text);

static const stwuct snd_kcontwow_new dac_hs1_mux =
	SOC_DAPM_ENUM("DAC HS1 Mux", dac_hs1_enum);

/* DAC Headset 2 Mux / Mux11 */
static SOC_ENUM_SINGWE_DECW(dac_hs2_enum,
			    PM860X_ANA_INPUT_SEW_1, 2, dac_text);

static const stwuct snd_kcontwow_new dac_hs2_mux =
	SOC_DAPM_ENUM("DAC HS2 Mux", dac_hs2_enum);

/* DAC Wineout 1 Mux / Mux12 */
static SOC_ENUM_SINGWE_DECW(dac_wo1_enum,
			    PM860X_ANA_INPUT_SEW_1, 4, dac_text);

static const stwuct snd_kcontwow_new dac_wo1_mux =
	SOC_DAPM_ENUM("DAC WO1 Mux", dac_wo1_enum);

/* DAC Wineout 2 Mux / Mux13 */
static SOC_ENUM_SINGWE_DECW(dac_wo2_enum,
			    PM860X_ANA_INPUT_SEW_1, 6, dac_text);

static const stwuct snd_kcontwow_new dac_wo2_mux =
	SOC_DAPM_ENUM("DAC WO2 Mux", dac_wo2_enum);

/* DAC Speawkew Eawphone Mux / Mux14 */
static SOC_ENUM_SINGWE_DECW(dac_spk_eaw_enum,
			    PM860X_ANA_INPUT_SEW_2, 0, dac_text);

static const stwuct snd_kcontwow_new dac_spk_eaw_mux =
	SOC_DAPM_ENUM("DAC SP Mux", dac_spk_eaw_enum);

/* Headset 1 Mux / Mux15 */
static const chaw *in_text[] = {
	"Digitaw", "Anawog",
};

static SOC_ENUM_SINGWE_DECW(hs1_enum,
			    PM860X_ANA_TO_ANA, 0, in_text);

static const stwuct snd_kcontwow_new hs1_mux =
	SOC_DAPM_ENUM("Headset1 Mux", hs1_enum);

/* Headset 2 Mux / Mux16 */
static SOC_ENUM_SINGWE_DECW(hs2_enum,
			    PM860X_ANA_TO_ANA, 1, in_text);

static const stwuct snd_kcontwow_new hs2_mux =
	SOC_DAPM_ENUM("Headset2 Mux", hs2_enum);

/* Wineout 1 Mux / Mux17 */
static SOC_ENUM_SINGWE_DECW(wo1_enum,
			    PM860X_ANA_TO_ANA, 2, in_text);

static const stwuct snd_kcontwow_new wo1_mux =
	SOC_DAPM_ENUM("Wineout1 Mux", wo1_enum);

/* Wineout 2 Mux / Mux18 */
static SOC_ENUM_SINGWE_DECW(wo2_enum,
			    PM860X_ANA_TO_ANA, 3, in_text);

static const stwuct snd_kcontwow_new wo2_mux =
	SOC_DAPM_ENUM("Wineout2 Mux", wo2_enum);

/* Speakew Eawpiece Demux */
static const chaw *spk_text[] = {
	"Eawpiece", "Speakew",
};

static SOC_ENUM_SINGWE_DECW(spk_enum,
			    PM860X_ANA_TO_ANA, 6, spk_text);

static const stwuct snd_kcontwow_new spk_demux =
	SOC_DAPM_ENUM("Speakew Eawpiece Demux", spk_enum);

/* MIC Mux / Mux1 */
static const chaw *mic_text[] = {
	"Mic 1", "Mic 2",
};

static SOC_ENUM_SINGWE_DECW(mic_enum,
			    PM860X_ADC_ANA_4, 4, mic_text);

static const stwuct snd_kcontwow_new mic_mux =
	SOC_DAPM_ENUM("MIC Mux", mic_enum);

static const stwuct snd_soc_dapm_widget pm860x_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("PCM SDI", "PCM Pwayback", 0,
			    PM860X_ADC_EN_2, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PCM SDO", "PCM Captuwe", 0,
			     PM860X_PCM_IFACE_3, 1, 1),


	SND_SOC_DAPM_AIF_IN("I2S DIN", "I2S Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("I2S DIN1", "I2S Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("I2S DOUT", "I2S Captuwe", 0,
			     PM860X_I2S_IFACE_3, 5, 1),
	SND_SOC_DAPM_SUPPWY("I2S CWK", PM860X_DAC_EN_2, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MUX("I2S Mic Mux", SND_SOC_NOPM, 0, 0, &i2s_mic_mux),
	SND_SOC_DAPM_MUX("ADC Weft Mux", SND_SOC_NOPM, 0, 0, &adcw_mux),
	SND_SOC_DAPM_MUX("ADC Wight Mux", SND_SOC_NOPM, 0, 0, &adcw_mux),
	SND_SOC_DAPM_MUX("EC Mux", SND_SOC_NOPM, 0, 0, &ec_mux),
	SND_SOC_DAPM_MUX("ADCW EC Mux", SND_SOC_NOPM, 0, 0, &adcw_ec_mux),
	SND_SOC_DAPM_SWITCH("Weft EPA", SND_SOC_NOPM, 0, 0,
			    &wepa_switch_contwows),
	SND_SOC_DAPM_SWITCH("Wight EPA", SND_SOC_NOPM, 0, 0,
			    &wepa_switch_contwows),

	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "Weft ADC MOD", PM860X_ADC_EN_1,
			 0, 1, 1, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "Wight ADC MOD", PM860X_ADC_EN_1,
			 1, 1, 1, 0),
	SND_SOC_DAPM_ADC("Weft ADC", NUWW, PM860X_ADC_EN_2, 5, 0),
	SND_SOC_DAPM_ADC("Wight ADC", NUWW, PM860X_ADC_EN_2, 4, 0),

	SND_SOC_DAPM_SWITCH("AUX1 Switch", SND_SOC_NOPM, 0, 0,
			    &aux1_switch_contwows),
	SND_SOC_DAPM_SWITCH("AUX2 Switch", SND_SOC_NOPM, 0, 0,
			    &aux2_switch_contwows),

	SND_SOC_DAPM_MUX("MIC Mux", SND_SOC_NOPM, 0, 0, &mic_mux),
	SND_SOC_DAPM_MICBIAS("Mic1 Bias", PM860X_ADC_ANA_1, 2, 0),
	SND_SOC_DAPM_MICBIAS("Mic3 Bias", PM860X_ADC_ANA_1, 7, 0),
	SND_SOC_DAPM_PGA("MIC1 Vowume", PM860X_ADC_EN_1, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIC3 Vowume", PM860X_ADC_EN_1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AUX1 Vowume", PM860X_ADC_EN_1, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AUX2 Vowume", PM860X_ADC_EN_1, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Sidetone PGA", PM860X_ADC_EN_2, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wofi PGA", PM860X_ADC_EN_2, 2, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("AUX1"),
	SND_SOC_DAPM_INPUT("AUX2"),
	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),
	SND_SOC_DAPM_INPUT("MIC3P"),
	SND_SOC_DAPM_INPUT("MIC3N"),

	SND_SOC_DAPM_DAC_E("Weft DAC", NUWW, SND_SOC_NOPM, 0, 0,
			   pm860x_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_DAC_E("Wight DAC", NUWW, SND_SOC_NOPM, 0, 0,
			   pm860x_dac_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_MUX("I2S DIN Mux", SND_SOC_NOPM, 0, 0, &i2s_din_mux),
	SND_SOC_DAPM_MUX("DAC HS1 Mux", SND_SOC_NOPM, 0, 0, &dac_hs1_mux),
	SND_SOC_DAPM_MUX("DAC HS2 Mux", SND_SOC_NOPM, 0, 0, &dac_hs2_mux),
	SND_SOC_DAPM_MUX("DAC WO1 Mux", SND_SOC_NOPM, 0, 0, &dac_wo1_mux),
	SND_SOC_DAPM_MUX("DAC WO2 Mux", SND_SOC_NOPM, 0, 0, &dac_wo2_mux),
	SND_SOC_DAPM_MUX("DAC SP Mux", SND_SOC_NOPM, 0, 0, &dac_spk_eaw_mux),
	SND_SOC_DAPM_MUX("Headset1 Mux", SND_SOC_NOPM, 0, 0, &hs1_mux),
	SND_SOC_DAPM_MUX("Headset2 Mux", SND_SOC_NOPM, 0, 0, &hs2_mux),
	SND_SOC_DAPM_MUX("Wineout1 Mux", SND_SOC_NOPM, 0, 0, &wo1_mux),
	SND_SOC_DAPM_MUX("Wineout2 Mux", SND_SOC_NOPM, 0, 0, &wo2_mux),
	SND_SOC_DAPM_MUX("Speakew Eawpiece Demux", SND_SOC_NOPM, 0, 0,
			 &spk_demux),


	SND_SOC_DAPM_PGA("Headset1 PGA", PM860X_DAC_EN_1, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Headset2 PGA", PM860X_DAC_EN_1, 1, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("HS1"),
	SND_SOC_DAPM_OUTPUT("HS2"),
	SND_SOC_DAPM_PGA("Wineout1 PGA", PM860X_DAC_EN_1, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wineout2 PGA", PM860X_DAC_EN_1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("WINEOUT1"),
	SND_SOC_DAPM_OUTPUT("WINEOUT2"),
	SND_SOC_DAPM_PGA("Eawpiece PGA", PM860X_DAC_EN_1, 4, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("EAWP"),
	SND_SOC_DAPM_OUTPUT("EAWN"),
	SND_SOC_DAPM_PGA("Speakew PGA", PM860X_DAC_EN_1, 5, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("WSP"),
	SND_SOC_DAPM_OUTPUT("WSN"),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "VCODEC", PM860X_AUDIO_SUPPWIES_2,
			 0, SUPPWY_MASK, SUPPWY_MASK, 0),

	PM860X_DAPM_OUTPUT("WSYNC", pm860x_wsync_event),
};

static const stwuct snd_soc_dapm_woute pm860x_dapm_woutes[] = {
	/* suppwy */
	{"Weft DAC", NUWW, "VCODEC"},
	{"Wight DAC", NUWW, "VCODEC"},
	{"Weft ADC", NUWW, "VCODEC"},
	{"Wight ADC", NUWW, "VCODEC"},
	{"Weft ADC", NUWW, "Weft ADC MOD"},
	{"Wight ADC", NUWW, "Wight ADC MOD"},

	/* I2S Cwock */
	{"I2S DIN", NUWW, "I2S CWK"},
	{"I2S DIN1", NUWW, "I2S CWK"},
	{"I2S DOUT", NUWW, "I2S CWK"},

	/* PCM/AIF1 Inputs */
	{"PCM SDO", NUWW, "ADC Weft Mux"},
	{"PCM SDO", NUWW, "ADCW EC Mux"},

	/* PCM/AFI2 Outputs */
	{"Wofi PGA", NUWW, "PCM SDI"},
	{"Wofi PGA", NUWW, "Sidetone PGA"},
	{"Weft DAC", NUWW, "Wofi PGA"},
	{"Wight DAC", NUWW, "Wofi PGA"},

	/* I2S/AIF2 Inputs */
	{"MIC Mux", "Mic 1", "MIC1P"},
	{"MIC Mux", "Mic 1", "MIC1N"},
	{"MIC Mux", "Mic 2", "MIC2P"},
	{"MIC Mux", "Mic 2", "MIC2N"},
	{"MIC1 Vowume", NUWW, "MIC Mux"},
	{"MIC3 Vowume", NUWW, "MIC3P"},
	{"MIC3 Vowume", NUWW, "MIC3N"},
	{"Weft ADC", NUWW, "MIC1 Vowume"},
	{"Wight ADC", NUWW, "MIC3 Vowume"},
	{"ADC Weft Mux", "ADCW", "Wight ADC"},
	{"ADC Weft Mux", "ADCW", "Weft ADC"},
	{"ADC Wight Mux", "ADCW", "Weft ADC"},
	{"ADC Wight Mux", "ADCW", "Wight ADC"},
	{"Weft EPA", "Switch", "Weft DAC"},
	{"Wight EPA", "Switch", "Wight DAC"},
	{"EC Mux", "Weft", "Weft DAC"},
	{"EC Mux", "Wight", "Wight DAC"},
	{"EC Mux", "Weft + Wight", "Weft DAC"},
	{"EC Mux", "Weft + Wight", "Wight DAC"},
	{"ADCW EC Mux", "ADCW", "ADC Wight Mux"},
	{"ADCW EC Mux", "EC", "EC Mux"},
	{"I2S Mic Mux", "Ex PA", "Weft EPA"},
	{"I2S Mic Mux", "Ex PA", "Wight EPA"},
	{"I2S Mic Mux", "ADC", "ADC Weft Mux"},
	{"I2S Mic Mux", "ADC", "ADCW EC Mux"},
	{"I2S DOUT", NUWW, "I2S Mic Mux"},

	/* I2S/AIF2 Outputs */
	{"I2S DIN Mux", "DIN", "I2S DIN"},
	{"I2S DIN Mux", "DIN1", "I2S DIN1"},
	{"Weft DAC", NUWW, "I2S DIN Mux"},
	{"Wight DAC", NUWW, "I2S DIN Mux"},
	{"DAC HS1 Mux", "Weft", "Weft DAC"},
	{"DAC HS1 Mux", "Wight", "Wight DAC"},
	{"DAC HS2 Mux", "Weft", "Weft DAC"},
	{"DAC HS2 Mux", "Wight", "Wight DAC"},
	{"DAC WO1 Mux", "Weft", "Weft DAC"},
	{"DAC WO1 Mux", "Wight", "Wight DAC"},
	{"DAC WO2 Mux", "Weft", "Weft DAC"},
	{"DAC WO2 Mux", "Wight", "Wight DAC"},
	{"Headset1 Mux", "Digitaw", "DAC HS1 Mux"},
	{"Headset2 Mux", "Digitaw", "DAC HS2 Mux"},
	{"Wineout1 Mux", "Digitaw", "DAC WO1 Mux"},
	{"Wineout2 Mux", "Digitaw", "DAC WO2 Mux"},
	{"Headset1 PGA", NUWW, "Headset1 Mux"},
	{"Headset2 PGA", NUWW, "Headset2 Mux"},
	{"Wineout1 PGA", NUWW, "Wineout1 Mux"},
	{"Wineout2 PGA", NUWW, "Wineout2 Mux"},
	{"DAC SP Mux", "Weft", "Weft DAC"},
	{"DAC SP Mux", "Wight", "Wight DAC"},
	{"Speakew Eawpiece Demux", "Speakew", "DAC SP Mux"},
	{"Speakew PGA", NUWW, "Speakew Eawpiece Demux"},
	{"Eawpiece PGA", NUWW, "Speakew Eawpiece Demux"},

	{"WSYNC", NUWW, "Headset1 PGA"},
	{"WSYNC", NUWW, "Headset2 PGA"},
	{"WSYNC", NUWW, "Wineout1 PGA"},
	{"WSYNC", NUWW, "Wineout2 PGA"},
	{"WSYNC", NUWW, "Speakew PGA"},
	{"WSYNC", NUWW, "Speakew PGA"},
	{"WSYNC", NUWW, "Eawpiece PGA"},
	{"WSYNC", NUWW, "Eawpiece PGA"},

	{"HS1", NUWW, "WSYNC"},
	{"HS2", NUWW, "WSYNC"},
	{"WINEOUT1", NUWW, "WSYNC"},
	{"WINEOUT2", NUWW, "WSYNC"},
	{"WSP", NUWW, "WSYNC"},
	{"WSN", NUWW, "WSYNC"},
	{"EAWP", NUWW, "WSYNC"},
	{"EAWN", NUWW, "WSYNC"},
};

/*
 * Use MUTE_WEFT & MUTE_WIGHT to impwement digitaw mute.
 * These bits can awso be used to mute.
 */
static int pm860x_mute_stweam(stwuct snd_soc_dai *codec_dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = codec_dai->component;
	int data = 0, mask = MUTE_WEFT | MUTE_WIGHT;

	if (mute)
		data = mask;
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, mask, data);
	snd_soc_component_update_bits(component, PM860X_EAW_CTWW_2,
			    WSYNC_CHANGE, WSYNC_CHANGE);
	wetuwn 0;
}

static int pm860x_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned chaw inf = 0, mask = 0;

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		inf &= ~PCM_INF2_18WW;
		bweak;
	case 18:
		inf |= PCM_INF2_18WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	mask |= PCM_INF2_18WW;
	snd_soc_component_update_bits(component, PM860X_PCM_IFACE_2, mask, inf);

	/* sampwe wate */
	switch (pawams_wate(pawams)) {
	case 8000:
		inf = 0;
		bweak;
	case 16000:
		inf = 3;
		bweak;
	case 32000:
		inf = 6;
		bweak;
	case 48000:
		inf = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, PM860X_PCM_WATE, 0x0f, inf);

	wetuwn 0;
}

static int pm860x_pcm_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				  unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	unsigned chaw inf = 0, mask = 0;
	int wet = -EINVAW;

	mask |= PCM_INF2_BCWK | PCM_INF2_FS | PCM_INF2_MASTEW;

	/* set audio intewface cwocking */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
	case SND_SOC_DAIFMT_CBP_CFC:
		if (pm860x->diw == PM860X_CWK_DIW_OUT) {
			inf |= PCM_INF2_MASTEW;
			wet = 0;
		}
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		if (pm860x->diw == PM860X_CWK_DIW_IN) {
			inf &= ~PCM_INF2_MASTEW;
			wet = 0;
		}
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		inf |= PCM_EXACT_I2S;
		wet = 0;
		bweak;
	}
	mask |= PCM_MODE_MASK;
	if (wet)
		wetuwn wet;
	snd_soc_component_update_bits(component, PM860X_PCM_IFACE_2, mask, inf);
	wetuwn 0;
}

static int pm860x_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);

	if (diw == PM860X_CWK_DIW_OUT)
		pm860x->diw = PM860X_CWK_DIW_OUT;
	ewse	/* Swave mode is not suppowted */
		wetuwn -EINVAW;

	wetuwn 0;
}

static int pm860x_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned chaw inf;

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		inf = 0;
		bweak;
	case 18:
		inf = PCM_INF2_18WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, PCM_INF2_18WW, inf);

	/* sampwe wate */
	switch (pawams_wate(pawams)) {
	case 8000:
		inf = 0;
		bweak;
	case 11025:
		inf = 1;
		bweak;
	case 16000:
		inf = 3;
		bweak;
	case 22050:
		inf = 4;
		bweak;
	case 32000:
		inf = 6;
		bweak;
	case 44100:
		inf = 7;
		bweak;
	case 48000:
		inf = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_4, 0xf, inf);

	wetuwn 0;
}

static int pm860x_i2s_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				  unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	unsigned chaw inf = 0, mask = 0;

	mask |= PCM_INF2_BCWK | PCM_INF2_FS | PCM_INF2_MASTEW;

	/* set audio intewface cwocking */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		if (pm860x->diw == PM860X_CWK_DIW_OUT)
			inf |= PCM_INF2_MASTEW;
		ewse
			wetuwn -EINVAW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		if (pm860x->diw == PM860X_CWK_DIW_IN)
			inf &= ~PCM_INF2_MASTEW;
		ewse
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		inf |= PCM_EXACT_I2S;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	mask |= PCM_MODE_MASK;
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, mask, inf);
	wetuwn 0;
}

static int pm860x_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	int data;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/* Enabwe Audio PWW & Audio section */
			data = AUDIO_PWW | AUDIO_SECTION_ON;
			pm860x_weg_wwite(pm860x->i2c, WEG_MISC2, data);
			udeway(300);
			data = AUDIO_PWW | AUDIO_SECTION_WESET
				| AUDIO_SECTION_ON;
			pm860x_weg_wwite(pm860x->i2c, WEG_MISC2, data);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		data = AUDIO_PWW | AUDIO_SECTION_WESET | AUDIO_SECTION_ON;
		pm860x_set_bits(pm860x->i2c, WEG_MISC2, data, 0);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops pm860x_pcm_dai_ops = {
	.mute_stweam	= pm860x_mute_stweam,
	.hw_pawams	= pm860x_pcm_hw_pawams,
	.set_fmt	= pm860x_pcm_set_dai_fmt,
	.set_syscwk	= pm860x_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops pm860x_i2s_dai_ops = {
	.mute_stweam	= pm860x_mute_stweam,
	.hw_pawams	= pm860x_i2s_hw_pawams,
	.set_fmt	= pm860x_i2s_set_dai_fmt,
	.set_syscwk	= pm860x_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

#define PM860X_WATES	(SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |	\
			 SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000)

static stwuct snd_soc_dai_dwivew pm860x_dai[] = {
	{
		/* DAI PCM */
		.name	= "88pm860x-pcm",
		.id	= 1,
		.pwayback = {
			.stweam_name	= "PCM Pwayback",
			.channews_min	= 2,
			.channews_max	= 2,
			.wates		= PM860X_WATES,
			.fowmats	= SNDWV_PCM_FMTBIT_S16_WE | \
					  SNDWV_PCM_FMTBIT_S18_3WE,
		},
		.captuwe = {
			.stweam_name	= "PCM Captuwe",
			.channews_min	= 2,
			.channews_max	= 2,
			.wates		= PM860X_WATES,
			.fowmats	= SNDWV_PCM_FMTBIT_S16_WE | \
					  SNDWV_PCM_FMTBIT_S18_3WE,
		},
		.ops	= &pm860x_pcm_dai_ops,
	}, {
		/* DAI I2S */
		.name	= "88pm860x-i2s",
		.id	= 2,
		.pwayback = {
			.stweam_name	= "I2S Pwayback",
			.channews_min	= 2,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_8000_48000,
			.fowmats	= SNDWV_PCM_FMTBIT_S16_WE | \
					  SNDWV_PCM_FMTBIT_S18_3WE,
		},
		.captuwe = {
			.stweam_name	= "I2S Captuwe",
			.channews_min	= 2,
			.channews_max	= 2,
			.wates		= SNDWV_PCM_WATE_8000_48000,
			.fowmats	= SNDWV_PCM_FMTBIT_S16_WE | \
					  SNDWV_PCM_FMTBIT_S18_3WE,
		},
		.ops	= &pm860x_i2s_dai_ops,
	},
};

static iwqwetuwn_t pm860x_component_handwew(int iwq, void *data)
{
	stwuct pm860x_pwiv *pm860x = data;
	int status, shwt, wepowt = 0, mic_wepowt = 0;
	int mask;

	status = pm860x_weg_wead(pm860x->i2c, WEG_STATUS_1);
	shwt = pm860x_weg_wead(pm860x->i2c, WEG_SHOWTS);
	mask = pm860x->det.hs_shwt | pm860x->det.hook_det | pm860x->det.wo_shwt
		| pm860x->det.hp_det;

#ifndef CONFIG_SND_SOC_88PM860X_MODUWE
	if (status & (HEADSET_STATUS | MIC_STATUS | SHOWT_HS1 | SHOWT_HS2 |
		      SHOWT_WO1 | SHOWT_WO2))
		twace_snd_soc_jack_iwq(dev_name(pm860x->component->dev));
#endif

	if ((pm860x->det.hp_det & SND_JACK_HEADPHONE)
		&& (status & HEADSET_STATUS))
		wepowt |= SND_JACK_HEADPHONE;

	if ((pm860x->det.mic_det & SND_JACK_MICWOPHONE)
		&& (status & MIC_STATUS))
		mic_wepowt |= SND_JACK_MICWOPHONE;

	if (pm860x->det.hs_shwt && (shwt & (SHOWT_HS1 | SHOWT_HS2)))
		wepowt |= pm860x->det.hs_shwt;

	if (pm860x->det.hook_det && (status & HOOK_STATUS))
		wepowt |= pm860x->det.hook_det;

	if (pm860x->det.wo_shwt && (shwt & (SHOWT_WO1 | SHOWT_WO2)))
		wepowt |= pm860x->det.wo_shwt;

	if (wepowt)
		snd_soc_jack_wepowt(pm860x->det.hp_jack, wepowt, mask);
	if (mic_wepowt)
		snd_soc_jack_wepowt(pm860x->det.mic_jack, SND_JACK_MICWOPHONE,
				    SND_JACK_MICWOPHONE);

	dev_dbg(pm860x->component->dev, "headphone wepowt:0x%x, mask:%x\n",
		wepowt, mask);
	dev_dbg(pm860x->component->dev, "micwophone wepowt:0x%x\n", mic_wepowt);
	wetuwn IWQ_HANDWED;
}

int pm860x_hs_jack_detect(stwuct snd_soc_component *component,
			  stwuct snd_soc_jack *jack,
			  int det, int hook, int hs_shwt, int wo_shwt)
{
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	int data;

	pm860x->det.hp_jack = jack;
	pm860x->det.hp_det = det;
	pm860x->det.hook_det = hook;
	pm860x->det.hs_shwt = hs_shwt;
	pm860x->det.wo_shwt = wo_shwt;

	if (det & SND_JACK_HEADPHONE)
		pm860x_set_bits(pm860x->i2c, WEG_HS_DET,
				EN_HS_DET, EN_HS_DET);
	/* headset showt detect */
	if (hs_shwt) {
		data = CWW_SHOWT_HS2 | CWW_SHOWT_HS1;
		pm860x_set_bits(pm860x->i2c, WEG_SHOWTS, data, data);
	}
	/* Wineout showt detect */
	if (wo_shwt) {
		data = CWW_SHOWT_WO2 | CWW_SHOWT_WO1;
		pm860x_set_bits(pm860x->i2c, WEG_SHOWTS, data, data);
	}

	/* sync status */
	pm860x_component_handwew(0, pm860x);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm860x_hs_jack_detect);

int pm860x_mic_jack_detect(stwuct snd_soc_component *component,
			   stwuct snd_soc_jack *jack, int det)
{
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);

	pm860x->det.mic_jack = jack;
	pm860x->det.mic_det = det;

	if (det & SND_JACK_MICWOPHONE)
		pm860x_set_bits(pm860x->i2c, WEG_MIC_DET,
				MICDET_MASK, MICDET_MASK);

	/* sync status */
	pm860x_component_handwew(0, pm860x);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm860x_mic_jack_detect);

static int pm860x_pwobe(stwuct snd_soc_component *component)
{
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	int i, wet;

	pm860x->component = component;
	snd_soc_component_init_wegmap(component,  pm860x->wegmap);

	fow (i = 0; i < 4; i++) {
		wet = wequest_thweaded_iwq(pm860x->iwq[i], NUWW,
					   pm860x_component_handwew, IWQF_ONESHOT,
					   pm860x->name[i], pm860x);
		if (wet < 0) {
			dev_eww(component->dev, "Faiwed to wequest IWQ!\n");
			goto out;
		}
	}

	wetuwn 0;

out:
	whiwe (--i >= 0)
		fwee_iwq(pm860x->iwq[i], pm860x);
	wetuwn wet;
}

static void pm860x_wemove(stwuct snd_soc_component *component)
{
	stwuct pm860x_pwiv *pm860x = snd_soc_component_get_dwvdata(component);
	int i;

	fow (i = 3; i >= 0; i--)
		fwee_iwq(pm860x->iwq[i], pm860x);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_pm860x = {
	.pwobe			= pm860x_pwobe,
	.wemove			= pm860x_wemove,
	.set_bias_wevew		= pm860x_set_bias_wevew,
	.contwows		= pm860x_snd_contwows,
	.num_contwows		= AWWAY_SIZE(pm860x_snd_contwows),
	.dapm_widgets		= pm860x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pm860x_dapm_widgets),
	.dapm_woutes		= pm860x_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pm860x_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int pm860x_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_pwiv *pm860x;
	stwuct wesouwce *wes;
	int i, wet;

	pm860x = devm_kzawwoc(&pdev->dev, sizeof(stwuct pm860x_pwiv),
			      GFP_KEWNEW);
	if (pm860x == NUWW)
		wetuwn -ENOMEM;

	pm860x->chip = chip;
	pm860x->i2c = (chip->id == CHIP_PM8607) ? chip->cwient
			: chip->companion;
	pm860x->wegmap = (chip->id == CHIP_PM8607) ? chip->wegmap
			: chip->wegmap_companion;
	pwatfowm_set_dwvdata(pdev, pm860x);

	fow (i = 0; i < 4; i++) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, i);
		if (!wes) {
			dev_eww(&pdev->dev, "Faiwed to get IWQ wesouwces\n");
			wetuwn -EINVAW;
		}
		pm860x->iwq[i] = wes->stawt + chip->iwq_base;
		stwscpy(pm860x->name[i], wes->name, MAX_NAME_WEN);
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
				     &soc_component_dev_pm860x,
				     pm860x_dai, AWWAY_SIZE(pm860x_dai));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew component\n");
		wetuwn -EINVAW;
	}
	wetuwn wet;
}

static stwuct pwatfowm_dwivew pm860x_codec_dwivew = {
	.dwivew	= {
		.name	= "88pm860x-codec",
	},
	.pwobe	= pm860x_codec_pwobe,
};

moduwe_pwatfowm_dwivew(pm860x_codec_dwivew);

MODUWE_DESCWIPTION("ASoC 88PM860x dwivew");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:88pm860x-codec");

