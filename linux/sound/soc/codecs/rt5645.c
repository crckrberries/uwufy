// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5645.c  --  WT5645 AWSA SoC audio codec dwivew
 *
 * Copywight 2013 Weawtek Semiconductow Cowp.
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
#incwude <winux/gpio/consumew.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "ww6231.h"
#incwude "wt5645.h"

#define QUIWK_INV_JD1_1(q)	((q) & 1)
#define QUIWK_WEVEW_IWQ(q)	(((q) >> 1) & 1)
#define QUIWK_IN2_DIFF(q)	(((q) >> 2) & 1)
#define QUIWK_INV_HP_POW(q)	(((q) >> 3) & 1)
#define QUIWK_JD_MODE(q)	(((q) >> 4) & 7)
#define QUIWK_DMIC1_DATA_PIN(q)	(((q) >> 8) & 3)
#define QUIWK_DMIC2_DATA_PIN(q)	(((q) >> 12) & 3)

static unsigned int quiwk = -1;
moduwe_pawam(quiwk, uint, 0444);
MODUWE_PAWM_DESC(quiwk, "WT5645 pdata quiwk ovewwide");

static const stwuct acpi_gpio_mapping *cht_wt5645_gpios;

#define WT5645_DEVICE_ID 0x6308
#define WT5650_DEVICE_ID 0x6419

#define WT5645_PW_WANGE_BASE (0xff + 1)
#define WT5645_PW_SPACING 0x100

#define WT5645_PW_BASE (WT5645_PW_WANGE_BASE + (0 * WT5645_PW_SPACING))

#define WT5645_HWEQ_NUM 57

#define TIME_TO_POWEW_MS 400

static const stwuct wegmap_wange_cfg wt5645_wanges[] = {
	{
		.name = "PW",
		.wange_min = WT5645_PW_BASE,
		.wange_max = WT5645_PW_BASE + 0xf8,
		.sewectow_weg = WT5645_PWIV_INDEX,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0x0,
		.window_stawt = WT5645_PWIV_DATA,
		.window_wen = 0x1,
	},
};

static const stwuct weg_sequence init_wist[] = {
	{WT5645_PW_BASE + 0x3d,	0x3600},
	{WT5645_PW_BASE + 0x1c,	0xfd70},
	{WT5645_PW_BASE + 0x20,	0x611f},
	{WT5645_PW_BASE + 0x21,	0x4040},
	{WT5645_PW_BASE + 0x23,	0x0004},
	{WT5645_ASWC_4, 0x0120},
};

static const stwuct weg_sequence wt5650_init_wist[] = {
	{0xf6,	0x0100},
	{WT5645_PWW_ANWG1, 0x02},
};

static const stwuct weg_defauwt wt5645_weg[] = {
	{ 0x00, 0x0000 },
	{ 0x01, 0xc8c8 },
	{ 0x02, 0xc8c8 },
	{ 0x03, 0xc8c8 },
	{ 0x0a, 0x0002 },
	{ 0x0b, 0x2827 },
	{ 0x0c, 0xe000 },
	{ 0x0d, 0x0000 },
	{ 0x0e, 0x0000 },
	{ 0x0f, 0x0808 },
	{ 0x14, 0x3333 },
	{ 0x16, 0x4b00 },
	{ 0x18, 0x018b },
	{ 0x19, 0xafaf },
	{ 0x1a, 0xafaf },
	{ 0x1b, 0x0001 },
	{ 0x1c, 0x2f2f },
	{ 0x1d, 0x2f2f },
	{ 0x1e, 0x0000 },
	{ 0x20, 0x0000 },
	{ 0x27, 0x7060 },
	{ 0x28, 0x7070 },
	{ 0x29, 0x8080 },
	{ 0x2a, 0x5656 },
	{ 0x2b, 0x5454 },
	{ 0x2c, 0xaaa0 },
	{ 0x2d, 0x0000 },
	{ 0x2f, 0x1002 },
	{ 0x31, 0x5000 },
	{ 0x32, 0x0000 },
	{ 0x33, 0x0000 },
	{ 0x34, 0x0000 },
	{ 0x35, 0x0000 },
	{ 0x3b, 0x0000 },
	{ 0x3c, 0x007f },
	{ 0x3d, 0x0000 },
	{ 0x3e, 0x007f },
	{ 0x3f, 0x0000 },
	{ 0x40, 0x001f },
	{ 0x41, 0x0000 },
	{ 0x42, 0x001f },
	{ 0x45, 0x6000 },
	{ 0x46, 0x003e },
	{ 0x47, 0x003e },
	{ 0x48, 0xf807 },
	{ 0x4a, 0x0004 },
	{ 0x4d, 0x0000 },
	{ 0x4e, 0x0000 },
	{ 0x4f, 0x01ff },
	{ 0x50, 0x0000 },
	{ 0x51, 0x0000 },
	{ 0x52, 0x01ff },
	{ 0x53, 0xf000 },
	{ 0x56, 0x0111 },
	{ 0x57, 0x0064 },
	{ 0x58, 0xef0e },
	{ 0x59, 0xf0f0 },
	{ 0x5a, 0xef0e },
	{ 0x5b, 0xf0f0 },
	{ 0x5c, 0xef0e },
	{ 0x5d, 0xf0f0 },
	{ 0x5e, 0xf000 },
	{ 0x5f, 0x0000 },
	{ 0x61, 0x0300 },
	{ 0x62, 0x0000 },
	{ 0x63, 0x00c2 },
	{ 0x64, 0x0000 },
	{ 0x65, 0x0000 },
	{ 0x66, 0x0000 },
	{ 0x6a, 0x0000 },
	{ 0x6c, 0x0aaa },
	{ 0x70, 0x8000 },
	{ 0x71, 0x8000 },
	{ 0x72, 0x8000 },
	{ 0x73, 0x7770 },
	{ 0x74, 0x3e00 },
	{ 0x75, 0x2409 },
	{ 0x76, 0x000a },
	{ 0x77, 0x0c00 },
	{ 0x78, 0x0000 },
	{ 0x79, 0x0123 },
	{ 0x80, 0x0000 },
	{ 0x81, 0x0000 },
	{ 0x82, 0x0000 },
	{ 0x83, 0x0000 },
	{ 0x84, 0x0000 },
	{ 0x85, 0x0000 },
	{ 0x8a, 0x0120 },
	{ 0x8e, 0x0004 },
	{ 0x8f, 0x1100 },
	{ 0x90, 0x0646 },
	{ 0x91, 0x0c06 },
	{ 0x93, 0x0000 },
	{ 0x94, 0x0200 },
	{ 0x95, 0x0000 },
	{ 0x9a, 0x2184 },
	{ 0x9b, 0x010a },
	{ 0x9c, 0x0aea },
	{ 0x9d, 0x000c },
	{ 0x9e, 0x0400 },
	{ 0xa0, 0xa0a8 },
	{ 0xa1, 0x0059 },
	{ 0xa2, 0x0001 },
	{ 0xae, 0x6000 },
	{ 0xaf, 0x0000 },
	{ 0xb0, 0x6000 },
	{ 0xb1, 0x0000 },
	{ 0xb2, 0x0000 },
	{ 0xb3, 0x001f },
	{ 0xb4, 0x020c },
	{ 0xb5, 0x1f00 },
	{ 0xb6, 0x0000 },
	{ 0xbb, 0x0000 },
	{ 0xbc, 0x0000 },
	{ 0xbd, 0x0000 },
	{ 0xbe, 0x0000 },
	{ 0xbf, 0x3100 },
	{ 0xc0, 0x0000 },
	{ 0xc1, 0x0000 },
	{ 0xc2, 0x0000 },
	{ 0xc3, 0x2000 },
	{ 0xcd, 0x0000 },
	{ 0xce, 0x0000 },
	{ 0xcf, 0x1813 },
	{ 0xd0, 0x0690 },
	{ 0xd1, 0x1c17 },
	{ 0xd3, 0xb320 },
	{ 0xd4, 0x0000 },
	{ 0xd6, 0x0400 },
	{ 0xd9, 0x0809 },
	{ 0xda, 0x0000 },
	{ 0xdb, 0x0003 },
	{ 0xdc, 0x0049 },
	{ 0xdd, 0x001b },
	{ 0xdf, 0x0008 },
	{ 0xe0, 0x4000 },
	{ 0xe6, 0x8000 },
	{ 0xe7, 0x0200 },
	{ 0xec, 0xb300 },
	{ 0xed, 0x0000 },
	{ 0xf0, 0x001f },
	{ 0xf1, 0x020c },
	{ 0xf2, 0x1f00 },
	{ 0xf3, 0x0000 },
	{ 0xf4, 0x4000 },
	{ 0xf8, 0x0000 },
	{ 0xf9, 0x0000 },
	{ 0xfa, 0x2060 },
	{ 0xfb, 0x4040 },
	{ 0xfc, 0x0000 },
	{ 0xfd, 0x0002 },
	{ 0xfe, 0x10ec },
	{ 0xff, 0x6308 },
};

static const stwuct weg_defauwt wt5650_weg[] = {
	{ 0x00, 0x0000 },
	{ 0x01, 0xc8c8 },
	{ 0x02, 0xc8c8 },
	{ 0x03, 0xc8c8 },
	{ 0x0a, 0x0002 },
	{ 0x0b, 0x2827 },
	{ 0x0c, 0xe000 },
	{ 0x0d, 0x0000 },
	{ 0x0e, 0x0000 },
	{ 0x0f, 0x0808 },
	{ 0x14, 0x3333 },
	{ 0x16, 0x4b00 },
	{ 0x18, 0x018b },
	{ 0x19, 0xafaf },
	{ 0x1a, 0xafaf },
	{ 0x1b, 0x0001 },
	{ 0x1c, 0x2f2f },
	{ 0x1d, 0x2f2f },
	{ 0x1e, 0x0000 },
	{ 0x20, 0x0000 },
	{ 0x27, 0x7060 },
	{ 0x28, 0x7070 },
	{ 0x29, 0x8080 },
	{ 0x2a, 0x5656 },
	{ 0x2b, 0x5454 },
	{ 0x2c, 0xaaa0 },
	{ 0x2d, 0x0000 },
	{ 0x2f, 0x5002 },
	{ 0x31, 0x5000 },
	{ 0x32, 0x0000 },
	{ 0x33, 0x0000 },
	{ 0x34, 0x0000 },
	{ 0x35, 0x0000 },
	{ 0x3b, 0x0000 },
	{ 0x3c, 0x007f },
	{ 0x3d, 0x0000 },
	{ 0x3e, 0x007f },
	{ 0x3f, 0x0000 },
	{ 0x40, 0x001f },
	{ 0x41, 0x0000 },
	{ 0x42, 0x001f },
	{ 0x45, 0x6000 },
	{ 0x46, 0x003e },
	{ 0x47, 0x003e },
	{ 0x48, 0xf807 },
	{ 0x4a, 0x0004 },
	{ 0x4d, 0x0000 },
	{ 0x4e, 0x0000 },
	{ 0x4f, 0x01ff },
	{ 0x50, 0x0000 },
	{ 0x51, 0x0000 },
	{ 0x52, 0x01ff },
	{ 0x53, 0xf000 },
	{ 0x56, 0x0111 },
	{ 0x57, 0x0064 },
	{ 0x58, 0xef0e },
	{ 0x59, 0xf0f0 },
	{ 0x5a, 0xef0e },
	{ 0x5b, 0xf0f0 },
	{ 0x5c, 0xef0e },
	{ 0x5d, 0xf0f0 },
	{ 0x5e, 0xf000 },
	{ 0x5f, 0x0000 },
	{ 0x61, 0x0300 },
	{ 0x62, 0x0000 },
	{ 0x63, 0x00c2 },
	{ 0x64, 0x0000 },
	{ 0x65, 0x0000 },
	{ 0x66, 0x0000 },
	{ 0x6a, 0x0000 },
	{ 0x6c, 0x0aaa },
	{ 0x70, 0x8000 },
	{ 0x71, 0x8000 },
	{ 0x72, 0x8000 },
	{ 0x73, 0x7770 },
	{ 0x74, 0x3e00 },
	{ 0x75, 0x2409 },
	{ 0x76, 0x000a },
	{ 0x77, 0x0c00 },
	{ 0x78, 0x0000 },
	{ 0x79, 0x0123 },
	{ 0x7a, 0x0123 },
	{ 0x80, 0x0000 },
	{ 0x81, 0x0000 },
	{ 0x82, 0x0000 },
	{ 0x83, 0x0000 },
	{ 0x84, 0x0000 },
	{ 0x85, 0x0000 },
	{ 0x8a, 0x0120 },
	{ 0x8e, 0x0004 },
	{ 0x8f, 0x1100 },
	{ 0x90, 0x0646 },
	{ 0x91, 0x0c06 },
	{ 0x93, 0x0000 },
	{ 0x94, 0x0200 },
	{ 0x95, 0x0000 },
	{ 0x9a, 0x2184 },
	{ 0x9b, 0x010a },
	{ 0x9c, 0x0aea },
	{ 0x9d, 0x000c },
	{ 0x9e, 0x0400 },
	{ 0xa0, 0xa0a8 },
	{ 0xa1, 0x0059 },
	{ 0xa2, 0x0001 },
	{ 0xae, 0x6000 },
	{ 0xaf, 0x0000 },
	{ 0xb0, 0x6000 },
	{ 0xb1, 0x0000 },
	{ 0xb2, 0x0000 },
	{ 0xb3, 0x001f },
	{ 0xb4, 0x020c },
	{ 0xb5, 0x1f00 },
	{ 0xb6, 0x0000 },
	{ 0xbb, 0x0000 },
	{ 0xbc, 0x0000 },
	{ 0xbd, 0x0000 },
	{ 0xbe, 0x0000 },
	{ 0xbf, 0x3100 },
	{ 0xc0, 0x0000 },
	{ 0xc1, 0x0000 },
	{ 0xc2, 0x0000 },
	{ 0xc3, 0x2000 },
	{ 0xcd, 0x0000 },
	{ 0xce, 0x0000 },
	{ 0xcf, 0x1813 },
	{ 0xd0, 0x0690 },
	{ 0xd1, 0x1c17 },
	{ 0xd3, 0xb320 },
	{ 0xd4, 0x0000 },
	{ 0xd6, 0x0400 },
	{ 0xd9, 0x0809 },
	{ 0xda, 0x0000 },
	{ 0xdb, 0x0003 },
	{ 0xdc, 0x0049 },
	{ 0xdd, 0x001b },
	{ 0xdf, 0x0008 },
	{ 0xe0, 0x4000 },
	{ 0xe6, 0x8000 },
	{ 0xe7, 0x0200 },
	{ 0xec, 0xb300 },
	{ 0xed, 0x0000 },
	{ 0xf0, 0x001f },
	{ 0xf1, 0x020c },
	{ 0xf2, 0x1f00 },
	{ 0xf3, 0x0000 },
	{ 0xf4, 0x4000 },
	{ 0xf8, 0x0000 },
	{ 0xf9, 0x0000 },
	{ 0xfa, 0x2060 },
	{ 0xfb, 0x4040 },
	{ 0xfc, 0x0000 },
	{ 0xfd, 0x0002 },
	{ 0xfe, 0x10ec },
	{ 0xff, 0x6308 },
};

stwuct wt5645_eq_pawam_s {
	unsigned showt weg;
	unsigned showt vaw;
};

stwuct wt5645_eq_pawam_s_be16 {
	__be16 weg;
	__be16 vaw;
};

static const chaw *const wt5645_suppwy_names[] = {
	"avdd",
	"cpvdd",
};

stwuct wt5645_pwatfowm_data {
	/* IN2 can optionawwy be diffewentiaw */
	boow in2_diff;

	unsigned int dmic1_data_pin;
	/* 0 = IN2N; 1 = GPIO5; 2 = GPIO11 */
	unsigned int dmic2_data_pin;
	/* 0 = IN2P; 1 = GPIO6; 2 = GPIO10; 3 = GPIO12 */

	unsigned int jd_mode;
	/* Use wevew twiggewed iwq */
	boow wevew_twiggew_iwq;
	/* Invewt JD1_1 status powawity */
	boow inv_jd1_1;
	/* Invewt HP detect status powawity */
	boow inv_hp_pow;

	/* Onwy 1 speakew connected */
	boow mono_speakew;

	/* Vawue to assign to snd_soc_cawd.wong_name */
	const chaw *wong_name;

	/* Some (package) vawiants have the headset-mic pin not-connected */
	boow no_headset_mic;
};

stwuct wt5645_pwiv {
	stwuct snd_soc_component *component;
	stwuct wt5645_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *i2c;
	stwuct gpio_desc *gpiod_hp_det;
	stwuct snd_soc_jack *hp_jack;
	stwuct snd_soc_jack *mic_jack;
	stwuct snd_soc_jack *btn_jack;
	stwuct dewayed_wowk jack_detect_wowk, wccwock_wowk;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(wt5645_suppwy_names)];
	stwuct wt5645_eq_pawam_s *eq_pawam;
	stwuct timew_wist btn_check_timew;
	stwuct mutex jd_mutex;

	int codec_type;
	int syscwk;
	int syscwk_swc;
	int wwck[WT5645_AIFS];
	int bcwk[WT5645_AIFS];
	int mastew[WT5645_AIFS];

	int pww_swc;
	int pww_in;
	int pww_out;

	int jack_type;
	boow en_button_func;
	int v_id;
};

static int wt5645_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WT5645_WESET, 0);
}

static boow wt5645_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wt5645_wanges); i++) {
		if (weg >= wt5645_wanges[i].wange_min &&
			weg <= wt5645_wanges[i].wange_max) {
			wetuwn twue;
		}
	}

	switch (weg) {
	case WT5645_WESET:
	case WT5645_PWIV_INDEX:
	case WT5645_PWIV_DATA:
	case WT5645_IN1_CTWW1:
	case WT5645_IN1_CTWW2:
	case WT5645_IN1_CTWW3:
	case WT5645_A_JD_CTWW1:
	case WT5645_ADC_EQ_CTWW1:
	case WT5645_EQ_CTWW1:
	case WT5645_AWC_CTWW_1:
	case WT5645_IWQ_CTWW2:
	case WT5645_IWQ_CTWW3:
	case WT5645_INT_IWQ_ST:
	case WT5645_IW_CMD:
	case WT5650_4BTN_IW_CMD1:
	case WT5645_VENDOW_ID:
	case WT5645_VENDOW_ID1:
	case WT5645_VENDOW_ID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5645_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wt5645_wanges); i++) {
		if (weg >= wt5645_wanges[i].wange_min &&
			weg <= wt5645_wanges[i].wange_max) {
			wetuwn twue;
		}
	}

	switch (weg) {
	case WT5645_WESET:
	case WT5645_SPK_VOW:
	case WT5645_HP_VOW:
	case WT5645_WOUT1:
	case WT5645_IN1_CTWW1:
	case WT5645_IN1_CTWW2:
	case WT5645_IN1_CTWW3:
	case WT5645_IN2_CTWW:
	case WT5645_INW1_INW1_VOW:
	case WT5645_SPK_FUNC_WIM:
	case WT5645_ADJ_HPF_CTWW:
	case WT5645_DAC1_DIG_VOW:
	case WT5645_DAC2_DIG_VOW:
	case WT5645_DAC_CTWW:
	case WT5645_STO1_ADC_DIG_VOW:
	case WT5645_MONO_ADC_DIG_VOW:
	case WT5645_ADC_BST_VOW1:
	case WT5645_ADC_BST_VOW2:
	case WT5645_STO1_ADC_MIXEW:
	case WT5645_MONO_ADC_MIXEW:
	case WT5645_AD_DA_MIXEW:
	case WT5645_STO_DAC_MIXEW:
	case WT5645_MONO_DAC_MIXEW:
	case WT5645_DIG_MIXEW:
	case WT5650_A_DAC_SOUW:
	case WT5645_DIG_INF1_DATA:
	case WT5645_PDM_OUT_CTWW:
	case WT5645_WEC_W1_MIXEW:
	case WT5645_WEC_W2_MIXEW:
	case WT5645_WEC_W1_MIXEW:
	case WT5645_WEC_W2_MIXEW:
	case WT5645_HPMIXW_CTWW:
	case WT5645_HPOMIXW_CTWW:
	case WT5645_HPMIXW_CTWW:
	case WT5645_HPOMIXW_CTWW:
	case WT5645_HPO_MIXEW:
	case WT5645_SPK_W_MIXEW:
	case WT5645_SPK_W_MIXEW:
	case WT5645_SPO_MIXEW:
	case WT5645_SPO_CWSD_WATIO:
	case WT5645_OUT_W1_MIXEW:
	case WT5645_OUT_W1_MIXEW:
	case WT5645_OUT_W_GAIN1:
	case WT5645_OUT_W_GAIN2:
	case WT5645_OUT_W_GAIN1:
	case WT5645_OUT_W_GAIN2:
	case WT5645_WOUT_MIXEW:
	case WT5645_HAPTIC_CTWW1:
	case WT5645_HAPTIC_CTWW2:
	case WT5645_HAPTIC_CTWW3:
	case WT5645_HAPTIC_CTWW4:
	case WT5645_HAPTIC_CTWW5:
	case WT5645_HAPTIC_CTWW6:
	case WT5645_HAPTIC_CTWW7:
	case WT5645_HAPTIC_CTWW8:
	case WT5645_HAPTIC_CTWW9:
	case WT5645_HAPTIC_CTWW10:
	case WT5645_PWW_DIG1:
	case WT5645_PWW_DIG2:
	case WT5645_PWW_ANWG1:
	case WT5645_PWW_ANWG2:
	case WT5645_PWW_MIXEW:
	case WT5645_PWW_VOW:
	case WT5645_PWIV_INDEX:
	case WT5645_PWIV_DATA:
	case WT5645_I2S1_SDP:
	case WT5645_I2S2_SDP:
	case WT5645_ADDA_CWK1:
	case WT5645_ADDA_CWK2:
	case WT5645_DMIC_CTWW1:
	case WT5645_DMIC_CTWW2:
	case WT5645_TDM_CTWW_1:
	case WT5645_TDM_CTWW_2:
	case WT5645_TDM_CTWW_3:
	case WT5650_TDM_CTWW_4:
	case WT5645_GWB_CWK:
	case WT5645_PWW_CTWW1:
	case WT5645_PWW_CTWW2:
	case WT5645_ASWC_1:
	case WT5645_ASWC_2:
	case WT5645_ASWC_3:
	case WT5645_ASWC_4:
	case WT5645_DEPOP_M1:
	case WT5645_DEPOP_M2:
	case WT5645_DEPOP_M3:
	case WT5645_CHAWGE_PUMP:
	case WT5645_MICBIAS:
	case WT5645_A_JD_CTWW1:
	case WT5645_VAD_CTWW4:
	case WT5645_CWSD_OUT_CTWW:
	case WT5645_ADC_EQ_CTWW1:
	case WT5645_ADC_EQ_CTWW2:
	case WT5645_EQ_CTWW1:
	case WT5645_EQ_CTWW2:
	case WT5645_AWC_CTWW_1:
	case WT5645_AWC_CTWW_2:
	case WT5645_AWC_CTWW_3:
	case WT5645_AWC_CTWW_4:
	case WT5645_AWC_CTWW_5:
	case WT5645_JD_CTWW:
	case WT5645_IWQ_CTWW1:
	case WT5645_IWQ_CTWW2:
	case WT5645_IWQ_CTWW3:
	case WT5645_INT_IWQ_ST:
	case WT5645_GPIO_CTWW1:
	case WT5645_GPIO_CTWW2:
	case WT5645_GPIO_CTWW3:
	case WT5645_BASS_BACK:
	case WT5645_MP3_PWUS1:
	case WT5645_MP3_PWUS2:
	case WT5645_ADJ_HPF1:
	case WT5645_ADJ_HPF2:
	case WT5645_HP_CAWIB_AMP_DET:
	case WT5645_SV_ZCD1:
	case WT5645_SV_ZCD2:
	case WT5645_IW_CMD:
	case WT5645_IW_CMD2:
	case WT5645_IW_CMD3:
	case WT5650_4BTN_IW_CMD1:
	case WT5650_4BTN_IW_CMD2:
	case WT5645_DWC1_HW_CTWW1:
	case WT5645_DWC2_HW_CTWW1:
	case WT5645_ADC_MONO_HP_CTWW1:
	case WT5645_ADC_MONO_HP_CTWW2:
	case WT5645_DWC2_CTWW1:
	case WT5645_DWC2_CTWW2:
	case WT5645_DWC2_CTWW3:
	case WT5645_DWC2_CTWW4:
	case WT5645_DWC2_CTWW5:
	case WT5645_JD_CTWW3:
	case WT5645_JD_CTWW4:
	case WT5645_GEN_CTWW1:
	case WT5645_GEN_CTWW2:
	case WT5645_GEN_CTWW3:
	case WT5645_VENDOW_ID:
	case WT5645_VENDOW_ID1:
	case WT5645_VENDOW_ID2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -4650, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_bst_twv, 0, 1200, 0);

/* {0, +20, +24, +30, +35, +40, +44, +50, +52} dB */
static const DECWAWE_TWV_DB_WANGE(bst_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(2000, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2400, 0, 0),
	3, 5, TWV_DB_SCAWE_ITEM(3000, 500, 0),
	6, 6, TWV_DB_SCAWE_ITEM(4400, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(5000, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(5200, 0, 0)
);

/* {-6, -4.5, -3, -1.5, 0, 0.82, 1.58, 2.28} dB */
static const DECWAWE_TWV_DB_WANGE(spk_cwsd_twv,
	0, 4, TWV_DB_SCAWE_ITEM(-600, 150, 0),
	5, 5, TWV_DB_SCAWE_ITEM(82, 0, 0),
	6, 6, TWV_DB_SCAWE_ITEM(158, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(228, 0, 0)
);

static int wt5645_hweq_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = WT5645_HWEQ_NUM * sizeof(stwuct wt5645_eq_pawam_s);

	wetuwn 0;
}

static int wt5645_hweq_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	stwuct wt5645_eq_pawam_s_be16 *eq_pawam =
		(stwuct wt5645_eq_pawam_s_be16 *)ucontwow->vawue.bytes.data;
	int i;

	fow (i = 0; i < WT5645_HWEQ_NUM; i++) {
		eq_pawam[i].weg = cpu_to_be16(wt5645->eq_pawam[i].weg);
		eq_pawam[i].vaw = cpu_to_be16(wt5645->eq_pawam[i].vaw);
	}

	wetuwn 0;
}

static boow wt5645_vawidate_hweq(unsigned showt weg)
{
	if ((weg >= 0x1a4 && weg <= 0x1cd) || (weg >= 0x1e5 && weg <= 0x1f8) ||
		(weg == WT5645_EQ_CTWW2))
		wetuwn twue;

	wetuwn fawse;
}

static int wt5645_hweq_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	stwuct wt5645_eq_pawam_s_be16 *eq_pawam =
		(stwuct wt5645_eq_pawam_s_be16 *)ucontwow->vawue.bytes.data;
	int i;

	fow (i = 0; i < WT5645_HWEQ_NUM; i++) {
		wt5645->eq_pawam[i].weg = be16_to_cpu(eq_pawam[i].weg);
		wt5645->eq_pawam[i].vaw = be16_to_cpu(eq_pawam[i].vaw);
	}

	/* The finaw setting of the tabwe shouwd be WT5645_EQ_CTWW2 */
	fow (i = WT5645_HWEQ_NUM - 1; i >= 0; i--) {
		if (wt5645->eq_pawam[i].weg == 0)
			continue;
		ewse if (wt5645->eq_pawam[i].weg != WT5645_EQ_CTWW2)
			wetuwn 0;
		ewse
			bweak;
	}

	fow (i = 0; i < WT5645_HWEQ_NUM; i++) {
		if (!wt5645_vawidate_hweq(wt5645->eq_pawam[i].weg) &&
		    wt5645->eq_pawam[i].weg != 0)
			wetuwn 0;
		ewse if (wt5645->eq_pawam[i].weg == 0)
			bweak;
	}

	wetuwn 0;
}

#define WT5645_HWEQ(xname) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = wt5645_hweq_info, \
	.get = wt5645_hweq_get, \
	.put = wt5645_hweq_put \
}

static int wt5645_spk_put_vowsw(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	int wet;

	wegmap_update_bits(wt5645->wegmap, WT5645_MICBIAS,
		WT5645_PWW_CWK25M_MASK, WT5645_PWW_CWK25M_PU);

	wet = snd_soc_put_vowsw(kcontwow, ucontwow);

	mod_dewayed_wowk(system_powew_efficient_wq, &wt5645->wccwock_wowk,
		msecs_to_jiffies(200));

	wetuwn wet;
}

static const chaw * const wt5645_dac1_vow_ctww_mode_text[] = {
	"immediatewy", "zewo cwossing", "soft wamp"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_dac1_vow_ctww_mode, WT5645_PW_BASE,
	WT5645_DA1_ZDET_SFT, wt5645_dac1_vow_ctww_mode_text);

static const stwuct snd_kcontwow_new wt5645_snd_contwows[] = {
	/* Speakew Output Vowume */
	SOC_DOUBWE("Speakew Channew Switch", WT5645_SPK_VOW,
		WT5645_VOW_W_SFT, WT5645_VOW_W_SFT, 1, 1),
	SOC_DOUBWE_EXT_TWV("Speakew Pwayback Vowume", WT5645_SPK_VOW,
		WT5645_W_VOW_SFT, WT5645_W_VOW_SFT, 39, 1, snd_soc_get_vowsw,
		wt5645_spk_put_vowsw, out_vow_twv),

	/* CwassD moduwatow Speakew Gain Watio */
	SOC_SINGWE_TWV("Speakew CwassD Pwayback Vowume", WT5645_SPO_CWSD_WATIO,
		WT5645_SPK_G_CWSD_SFT, 7, 0, spk_cwsd_twv),

	/* Headphone Output Vowume */
	SOC_DOUBWE("Headphone Channew Switch", WT5645_HP_VOW,
		WT5645_VOW_W_SFT, WT5645_VOW_W_SFT, 1, 1),
	SOC_DOUBWE_TWV("Headphone Pwayback Vowume", WT5645_HP_VOW,
		WT5645_W_VOW_SFT, WT5645_W_VOW_SFT, 39, 1, out_vow_twv),

	/* OUTPUT Contwow */
	SOC_DOUBWE("OUT Pwayback Switch", WT5645_WOUT1,
		WT5645_W_MUTE_SFT, WT5645_W_MUTE_SFT, 1, 1),
	SOC_DOUBWE("OUT Channew Switch", WT5645_WOUT1,
		WT5645_VOW_W_SFT, WT5645_VOW_W_SFT, 1, 1),
	SOC_DOUBWE_TWV("OUT Pwayback Vowume", WT5645_WOUT1,
		WT5645_W_VOW_SFT, WT5645_W_VOW_SFT, 39, 1, out_vow_twv),

	/* DAC Digitaw Vowume */
	SOC_DOUBWE("DAC2 Pwayback Switch", WT5645_DAC_CTWW,
		WT5645_M_DAC_W2_VOW_SFT, WT5645_M_DAC_W2_VOW_SFT, 1, 1),
	SOC_DOUBWE_TWV("DAC1 Pwayback Vowume", WT5645_DAC1_DIG_VOW,
		WT5645_W_VOW_SFT + 1, WT5645_W_VOW_SFT + 1, 87, 0, dac_vow_twv),
	SOC_DOUBWE_TWV("Mono DAC Pwayback Vowume", WT5645_DAC2_DIG_VOW,
		WT5645_W_VOW_SFT + 1, WT5645_W_VOW_SFT + 1, 87, 0, dac_vow_twv),

	/* IN1/IN2 Contwow */
	SOC_SINGWE_TWV("IN1 Boost", WT5645_IN1_CTWW1,
		WT5645_BST_SFT1, 12, 0, bst_twv),
	SOC_SINGWE_TWV("IN2 Boost", WT5645_IN2_CTWW,
		WT5645_BST_SFT2, 8, 0, bst_twv),

	/* INW/INW Vowume Contwow */
	SOC_DOUBWE_TWV("IN Captuwe Vowume", WT5645_INW1_INW1_VOW,
		WT5645_INW_VOW_SFT, WT5645_INW_VOW_SFT, 31, 1, in_vow_twv),

	/* ADC Digitaw Vowume Contwow */
	SOC_DOUBWE("ADC Captuwe Switch", WT5645_STO1_ADC_DIG_VOW,
		WT5645_W_MUTE_SFT, WT5645_W_MUTE_SFT, 1, 1),
	SOC_DOUBWE_TWV("ADC Captuwe Vowume", WT5645_STO1_ADC_DIG_VOW,
		WT5645_W_VOW_SFT + 1, WT5645_W_VOW_SFT + 1, 63, 0, adc_vow_twv),
	SOC_DOUBWE("Mono ADC Captuwe Switch", WT5645_MONO_ADC_DIG_VOW,
		WT5645_W_MUTE_SFT, WT5645_W_MUTE_SFT, 1, 1),
	SOC_DOUBWE_TWV("Mono ADC Captuwe Vowume", WT5645_MONO_ADC_DIG_VOW,
		WT5645_W_VOW_SFT + 1, WT5645_W_VOW_SFT + 1, 63, 0, adc_vow_twv),

	/* ADC Boost Vowume Contwow */
	SOC_DOUBWE_TWV("ADC Boost Captuwe Vowume", WT5645_ADC_BST_VOW1,
		WT5645_STO1_ADC_W_BST_SFT, WT5645_STO1_ADC_W_BST_SFT, 3, 0,
		adc_bst_twv),
	SOC_DOUBWE_TWV("Mono ADC Boost Captuwe Vowume", WT5645_ADC_BST_VOW2,
		WT5645_MONO_ADC_W_BST_SFT, WT5645_MONO_ADC_W_BST_SFT, 3, 0,
		adc_bst_twv),

	/* I2S2 function sewect */
	SOC_SINGWE("I2S2 Func Switch", WT5645_GPIO_CTWW1, WT5645_I2S2_SEW_SFT,
		1, 1),
	WT5645_HWEQ("Speakew HWEQ"),

	/* Digitaw Soft Vowume Contwow */
	SOC_ENUM("DAC1 Digitaw Vowume Contwow Func", wt5645_dac1_vow_ctww_mode),
};

/**
 * set_dmic_cwk - Set pawametew of dmic.
 *
 * @w: DAPM widget.
 * @kcontwow: The kcontwow of this widget.
 * @event: Event id.
 *
 */
static int set_dmic_cwk(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	int idx, wate;

	wate = wt5645->syscwk / ww6231_get_pwe_div(wt5645->wegmap,
		WT5645_ADDA_CWK1, WT5645_I2S_PD1_SFT);
	idx = ww6231_cawc_dmic_cwk(wate);
	if (idx < 0)
		dev_eww(component->dev, "Faiwed to set DMIC cwock\n");
	ewse
		snd_soc_component_update_bits(component, WT5645_DMIC_CTWW1,
			WT5645_DMIC_CWK_MASK, idx << WT5645_DMIC_CWK_SFT);
	wetuwn idx;
}

static int is_sys_cwk_fwom_pww(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, WT5645_GWB_CWK);
	vaw &= WT5645_SCWK_SWC_MASK;
	if (vaw == WT5645_SCWK_SWC_PWW1)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int is_using_aswc(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	unsigned int weg, shift, vaw;

	switch (souwce->shift) {
	case 0:
		weg = WT5645_ASWC_3;
		shift = 0;
		bweak;
	case 1:
		weg = WT5645_ASWC_3;
		shift = 4;
		bweak;
	case 3:
		weg = WT5645_ASWC_2;
		shift = 0;
		bweak;
	case 8:
		weg = WT5645_ASWC_2;
		shift = 4;
		bweak;
	case 9:
		weg = WT5645_ASWC_2;
		shift = 8;
		bweak;
	case 10:
		weg = WT5645_ASWC_2;
		shift = 12;
		bweak;
	defauwt:
		wetuwn 0;
	}

	vaw = (snd_soc_component_wead(component, weg) >> shift) & 0xf;
	switch (vaw) {
	case 1:
	case 2:
	case 3:
	case 4:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}

}

static int wt5645_enabwe_hweq(stwuct snd_soc_component *component)
{
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	int i;

	fow (i = 0; i < WT5645_HWEQ_NUM; i++) {
		if (wt5645_vawidate_hweq(wt5645->eq_pawam[i].weg))
			wegmap_wwite(wt5645->wegmap, wt5645->eq_pawam[i].weg,
					wt5645->eq_pawam[i].vaw);
		ewse
			bweak;
	}

	wetuwn 0;
}

/**
 * wt5645_sew_aswc_cwk_swc - sewect ASWC cwock souwce fow a set of fiwtews
 * @component: SoC audio component device.
 * @fiwtew_mask: mask of fiwtews.
 * @cwk_swc: cwock souwce
 *
 * The ASWC function is fow asynchwonous MCWK and WWCK. Awso, since WT5645 can
 * onwy suppowt standawd 32fs ow 64fs i2s fowmat, ASWC shouwd be enabwed to
 * suppowt speciaw i2s cwock fowmat such as Intew's 100fs(100 * sampwing wate).
 * ASWC function wiww twack i2s cwock and genewate a cowwesponding system cwock
 * fow codec. This function pwovides an API to sewect the cwock souwce fow a
 * set of fiwtews specified by the mask. And the codec dwivew wiww tuwn on ASWC
 * fow these fiwtews if ASWC is sewected as theiw cwock souwce.
 */
int wt5645_sew_aswc_cwk_swc(stwuct snd_soc_component *component,
		unsigned int fiwtew_mask, unsigned int cwk_swc)
{
	unsigned int aswc2_mask = 0;
	unsigned int aswc2_vawue = 0;
	unsigned int aswc3_mask = 0;
	unsigned int aswc3_vawue = 0;

	switch (cwk_swc) {
	case WT5645_CWK_SEW_SYS:
	case WT5645_CWK_SEW_I2S1_ASWC:
	case WT5645_CWK_SEW_I2S2_ASWC:
	case WT5645_CWK_SEW_SYS2:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (fiwtew_mask & WT5645_DA_STEWEO_FIWTEW) {
		aswc2_mask |= WT5645_DA_STO_CWK_SEW_MASK;
		aswc2_vawue = (aswc2_vawue & ~WT5645_DA_STO_CWK_SEW_MASK)
			| (cwk_swc << WT5645_DA_STO_CWK_SEW_SFT);
	}

	if (fiwtew_mask & WT5645_DA_MONO_W_FIWTEW) {
		aswc2_mask |= WT5645_DA_MONOW_CWK_SEW_MASK;
		aswc2_vawue = (aswc2_vawue & ~WT5645_DA_MONOW_CWK_SEW_MASK)
			| (cwk_swc << WT5645_DA_MONOW_CWK_SEW_SFT);
	}

	if (fiwtew_mask & WT5645_DA_MONO_W_FIWTEW) {
		aswc2_mask |= WT5645_DA_MONOW_CWK_SEW_MASK;
		aswc2_vawue = (aswc2_vawue & ~WT5645_DA_MONOW_CWK_SEW_MASK)
			| (cwk_swc << WT5645_DA_MONOW_CWK_SEW_SFT);
	}

	if (fiwtew_mask & WT5645_AD_STEWEO_FIWTEW) {
		aswc2_mask |= WT5645_AD_STO1_CWK_SEW_MASK;
		aswc2_vawue = (aswc2_vawue & ~WT5645_AD_STO1_CWK_SEW_MASK)
			| (cwk_swc << WT5645_AD_STO1_CWK_SEW_SFT);
	}

	if (fiwtew_mask & WT5645_AD_MONO_W_FIWTEW) {
		aswc3_mask |= WT5645_AD_MONOW_CWK_SEW_MASK;
		aswc3_vawue = (aswc3_vawue & ~WT5645_AD_MONOW_CWK_SEW_MASK)
			| (cwk_swc << WT5645_AD_MONOW_CWK_SEW_SFT);
	}

	if (fiwtew_mask & WT5645_AD_MONO_W_FIWTEW)  {
		aswc3_mask |= WT5645_AD_MONOW_CWK_SEW_MASK;
		aswc3_vawue = (aswc3_vawue & ~WT5645_AD_MONOW_CWK_SEW_MASK)
			| (cwk_swc << WT5645_AD_MONOW_CWK_SEW_SFT);
	}

	if (aswc2_mask)
		snd_soc_component_update_bits(component, WT5645_ASWC_2,
			aswc2_mask, aswc2_vawue);

	if (aswc3_mask)
		snd_soc_component_update_bits(component, WT5645_ASWC_3,
			aswc3_mask, aswc3_vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt5645_sew_aswc_cwk_swc);

/* Digitaw Mixew */
static const stwuct snd_kcontwow_new wt5645_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5645_STO1_ADC_MIXEW,
			WT5645_M_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5645_STO1_ADC_MIXEW,
			WT5645_M_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5645_STO1_ADC_MIXEW,
			WT5645_M_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5645_STO1_ADC_MIXEW,
			WT5645_M_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_mono_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5645_MONO_ADC_MIXEW,
			WT5645_M_MONO_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5645_MONO_ADC_MIXEW,
			WT5645_M_MONO_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_mono_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5645_MONO_ADC_MIXEW,
			WT5645_M_MONO_ADC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5645_MONO_ADC_MIXEW,
			WT5645_M_MONO_ADC_W2_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_dac_w_mix[] = {
	SOC_DAPM_SINGWE("Steweo ADC Switch", WT5645_AD_DA_MIXEW,
			WT5645_M_ADCMIX_W_SFT, 1, 1),
	SOC_DAPM_SINGWE_AUTODISABWE("DAC1 Switch", WT5645_AD_DA_MIXEW,
			WT5645_M_DAC1_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_dac_w_mix[] = {
	SOC_DAPM_SINGWE("Steweo ADC Switch", WT5645_AD_DA_MIXEW,
			WT5645_M_ADCMIX_W_SFT, 1, 1),
	SOC_DAPM_SINGWE_AUTODISABWE("DAC1 Switch", WT5645_AD_DA_MIXEW,
			WT5645_M_DAC1_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_sto_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W2_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W1_STO_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_sto_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W1_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W2_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_STO_DAC_MIXEW,
			WT5645_M_DAC_W1_STO_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_mono_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W1_MONO_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W2_MONO_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W2_MONO_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_mono_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W1_MONO_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W2_MONO_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_MONO_DAC_MIXEW,
			WT5645_M_DAC_W2_MONO_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_dig_w_mix[] = {
	SOC_DAPM_SINGWE("Sto DAC Mix W Switch", WT5645_DIG_MIXEW,
			WT5645_M_STO_W_DAC_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_DIG_MIXEW,
			WT5645_M_DAC_W2_DAC_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_DIG_MIXEW,
			WT5645_M_DAC_W2_DAC_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_dig_w_mix[] = {
	SOC_DAPM_SINGWE("Sto DAC Mix W Switch", WT5645_DIG_MIXEW,
			WT5645_M_STO_W_DAC_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_DIG_MIXEW,
			WT5645_M_DAC_W2_DAC_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_DIG_MIXEW,
			WT5645_M_DAC_W2_DAC_W_SFT, 1, 1),
};

/* Anawog Input Mixew */
static const stwuct snd_kcontwow_new wt5645_wec_w_mix[] = {
	SOC_DAPM_SINGWE("HPOW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_HP_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_IN_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_BST2_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_BST1_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUT MIXW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_OM_W_WM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_wec_w_mix[] = {
	SOC_DAPM_SINGWE("HPOW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_HP_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_IN_W_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_BST2_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_BST1_WM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUT MIXW Switch", WT5645_WEC_W2_MIXEW,
			WT5645_M_OM_W_WM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_spk_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_DAC_W1_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_DAC_W2_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_IN_W_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_BST1_W_SM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_spk_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_DAC_W1_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_DAC_W2_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_IN_W_SM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5645_SPK_W_MIXEW,
			WT5645_M_BST2_W_SM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_out_w_mix[] = {
	SOC_DAPM_SINGWE("BST1 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_BST1_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_IN_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_DAC_W2_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_DAC_W1_OM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_out_w_mix[] = {
	SOC_DAPM_SINGWE("BST2 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_BST2_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_IN_W_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W2 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_DAC_W2_OM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_OUT_W1_MIXEW,
			WT5645_M_DAC_W1_OM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_spo_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_SPO_MIXEW,
			WT5645_M_DAC_W1_SPM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_SPO_MIXEW,
			WT5645_M_DAC_W1_SPM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("SPKVOW W Switch", WT5645_SPO_MIXEW,
			WT5645_M_SV_W_SPM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("SPKVOW W Switch", WT5645_SPO_MIXEW,
			WT5645_M_SV_W_SPM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_spo_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_SPO_MIXEW,
			WT5645_M_DAC_W1_SPM_W_SFT, 1, 1),
	SOC_DAPM_SINGWE("SPKVOW W Switch", WT5645_SPO_MIXEW,
			WT5645_M_SV_W_SPM_W_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_hpo_mix[] = {
	SOC_DAPM_SINGWE("DAC1 Switch", WT5645_HPO_MIXEW,
			WT5645_M_DAC1_HM_SFT, 1, 1),
	SOC_DAPM_SINGWE("HPVOW Switch", WT5645_HPO_MIXEW,
			WT5645_M_HPVOW_HM_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_hpvoww_mix[] = {
	SOC_DAPM_SINGWE("DAC1 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_DAC1_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC2 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_DAC2_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_IN_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_BST1_HV_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_hpvoww_mix[] = {
	SOC_DAPM_SINGWE("DAC1 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_DAC1_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC2 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_DAC2_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("INW Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_IN_HV_SFT, 1, 1),
	SOC_DAPM_SINGWE("BST2 Switch", WT5645_HPOMIXW_CTWW,
			WT5645_M_BST2_HV_SFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5645_wout_mix[] = {
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_WOUT_MIXEW,
			WT5645_M_DAC_W1_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W1 Switch", WT5645_WOUT_MIXEW,
			WT5645_M_DAC_W1_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUTMIX W Switch", WT5645_WOUT_MIXEW,
			WT5645_M_OV_W_WM_SFT, 1, 1),
	SOC_DAPM_SINGWE("OUTMIX W Switch", WT5645_WOUT_MIXEW,
			WT5645_M_OV_W_WM_SFT, 1, 1),
};

/*DAC1 W/W souwce*/ /* MX-29 [9:8] [11:10] */
static const chaw * const wt5645_dac1_swc[] = {
	"IF1 DAC", "IF2 DAC", "IF3 DAC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_dac1w_enum, WT5645_AD_DA_MIXEW,
	WT5645_DAC1_W_SEW_SFT, wt5645_dac1_swc);

static const stwuct snd_kcontwow_new wt5645_dac1w_mux =
	SOC_DAPM_ENUM("DAC1 W souwce", wt5645_dac1w_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5645_dac1w_enum, WT5645_AD_DA_MIXEW,
	WT5645_DAC1_W_SEW_SFT, wt5645_dac1_swc);

static const stwuct snd_kcontwow_new wt5645_dac1w_mux =
	SOC_DAPM_ENUM("DAC1 W souwce", wt5645_dac1w_enum);

/*DAC2 W/W souwce*/ /* MX-1B [6:4] [2:0] */
static const chaw * const wt5645_dac12_swc[] = {
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "Mono ADC", "VAD_ADC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_dac2w_enum, WT5645_DAC_CTWW,
	WT5645_DAC2_W_SEW_SFT, wt5645_dac12_swc);

static const stwuct snd_kcontwow_new wt5645_dac_w2_mux =
	SOC_DAPM_ENUM("DAC2 W souwce", wt5645_dac2w_enum);

static const chaw * const wt5645_dacw2_swc[] = {
	"IF1 DAC", "IF2 DAC", "IF3 DAC", "Mono ADC", "Haptic"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_dac2w_enum, WT5645_DAC_CTWW,
	WT5645_DAC2_W_SEW_SFT, wt5645_dacw2_swc);

static const stwuct snd_kcontwow_new wt5645_dac_w2_mux =
	SOC_DAPM_ENUM("DAC2 W souwce", wt5645_dac2w_enum);

/* Steweo1 ADC souwce */
/* MX-27 [12] */
static const chaw * const wt5645_steweo_adc1_swc[] = {
	"DAC MIX", "ADC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_steweo1_adc1_enum, WT5645_STO1_ADC_MIXEW,
	WT5645_ADC_1_SWC_SFT, wt5645_steweo_adc1_swc);

static const stwuct snd_kcontwow_new wt5645_sto_adc1_mux =
	SOC_DAPM_ENUM("Steweo1 ADC1 Mux", wt5645_steweo1_adc1_enum);

/* MX-27 [11] */
static const chaw * const wt5645_steweo_adc2_swc[] = {
	"DAC MIX", "DMIC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_steweo1_adc2_enum, WT5645_STO1_ADC_MIXEW,
	WT5645_ADC_2_SWC_SFT, wt5645_steweo_adc2_swc);

static const stwuct snd_kcontwow_new wt5645_sto_adc2_mux =
	SOC_DAPM_ENUM("Steweo1 ADC2 Mux", wt5645_steweo1_adc2_enum);

/* MX-27 [8] */
static const chaw * const wt5645_steweo_dmic_swc[] = {
	"DMIC1", "DMIC2"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_steweo1_dmic_enum, WT5645_STO1_ADC_MIXEW,
	WT5645_DMIC_SWC_SFT, wt5645_steweo_dmic_swc);

static const stwuct snd_kcontwow_new wt5645_sto1_dmic_mux =
	SOC_DAPM_ENUM("Steweo1 DMIC souwce", wt5645_steweo1_dmic_enum);

/* Mono ADC souwce */
/* MX-28 [12] */
static const chaw * const wt5645_mono_adc_w1_swc[] = {
	"Mono DAC MIXW", "ADC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_adc_w1_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_ADC_W1_SWC_SFT, wt5645_mono_adc_w1_swc);

static const stwuct snd_kcontwow_new wt5645_mono_adc_w1_mux =
	SOC_DAPM_ENUM("Mono ADC1 weft souwce", wt5645_mono_adc_w1_enum);
/* MX-28 [11] */
static const chaw * const wt5645_mono_adc_w2_swc[] = {
	"Mono DAC MIXW", "DMIC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_adc_w2_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_ADC_W2_SWC_SFT, wt5645_mono_adc_w2_swc);

static const stwuct snd_kcontwow_new wt5645_mono_adc_w2_mux =
	SOC_DAPM_ENUM("Mono ADC2 weft souwce", wt5645_mono_adc_w2_enum);

/* MX-28 [8] */
static const chaw * const wt5645_mono_dmic_swc[] = {
	"DMIC1", "DMIC2"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_dmic_w_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_DMIC_W_SWC_SFT, wt5645_mono_dmic_swc);

static const stwuct snd_kcontwow_new wt5645_mono_dmic_w_mux =
	SOC_DAPM_ENUM("Mono DMIC weft souwce", wt5645_mono_dmic_w_enum);
/* MX-28 [1:0] */
static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_dmic_w_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_DMIC_W_SWC_SFT, wt5645_mono_dmic_swc);

static const stwuct snd_kcontwow_new wt5645_mono_dmic_w_mux =
	SOC_DAPM_ENUM("Mono DMIC Wight souwce", wt5645_mono_dmic_w_enum);
/* MX-28 [4] */
static const chaw * const wt5645_mono_adc_w1_swc[] = {
	"Mono DAC MIXW", "ADC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_adc_w1_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_ADC_W1_SWC_SFT, wt5645_mono_adc_w1_swc);

static const stwuct snd_kcontwow_new wt5645_mono_adc_w1_mux =
	SOC_DAPM_ENUM("Mono ADC1 wight souwce", wt5645_mono_adc_w1_enum);
/* MX-28 [3] */
static const chaw * const wt5645_mono_adc_w2_swc[] = {
	"Mono DAC MIXW", "DMIC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_mono_adc_w2_enum, WT5645_MONO_ADC_MIXEW,
	WT5645_MONO_ADC_W2_SWC_SFT, wt5645_mono_adc_w2_swc);

static const stwuct snd_kcontwow_new wt5645_mono_adc_w2_mux =
	SOC_DAPM_ENUM("Mono ADC2 wight souwce", wt5645_mono_adc_w2_enum);

/* MX-77 [9:8] */
static const chaw * const wt5645_if1_adc_in_swc[] = {
	"IF_ADC1/IF_ADC2/VAD_ADC", "IF_ADC2/IF_ADC1/VAD_ADC",
	"VAD_ADC/IF_ADC1/IF_ADC2", "VAD_ADC/IF_ADC2/IF_ADC1"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_if1_adc_in_enum, WT5645_TDM_CTWW_1,
	WT5645_IF1_ADC_IN_SFT, wt5645_if1_adc_in_swc);

static const stwuct snd_kcontwow_new wt5645_if1_adc_in_mux =
	SOC_DAPM_ENUM("IF1 ADC IN souwce", wt5645_if1_adc_in_enum);

/* MX-78 [4:0] */
static const chaw * const wt5650_if1_adc_in_swc[] = {
	"IF_ADC1/IF_ADC2/DAC_WEF/Nuww",
	"IF_ADC1/IF_ADC2/Nuww/DAC_WEF",
	"IF_ADC1/DAC_WEF/IF_ADC2/Nuww",
	"IF_ADC1/DAC_WEF/Nuww/IF_ADC2",
	"IF_ADC1/Nuww/DAC_WEF/IF_ADC2",
	"IF_ADC1/Nuww/IF_ADC2/DAC_WEF",

	"IF_ADC2/IF_ADC1/DAC_WEF/Nuww",
	"IF_ADC2/IF_ADC1/Nuww/DAC_WEF",
	"IF_ADC2/DAC_WEF/IF_ADC1/Nuww",
	"IF_ADC2/DAC_WEF/Nuww/IF_ADC1",
	"IF_ADC2/Nuww/DAC_WEF/IF_ADC1",
	"IF_ADC2/Nuww/IF_ADC1/DAC_WEF",

	"DAC_WEF/IF_ADC1/IF_ADC2/Nuww",
	"DAC_WEF/IF_ADC1/Nuww/IF_ADC2",
	"DAC_WEF/IF_ADC2/IF_ADC1/Nuww",
	"DAC_WEF/IF_ADC2/Nuww/IF_ADC1",
	"DAC_WEF/Nuww/IF_ADC1/IF_ADC2",
	"DAC_WEF/Nuww/IF_ADC2/IF_ADC1",

	"Nuww/IF_ADC1/IF_ADC2/DAC_WEF",
	"Nuww/IF_ADC1/DAC_WEF/IF_ADC2",
	"Nuww/IF_ADC2/IF_ADC1/DAC_WEF",
	"Nuww/IF_ADC2/DAC_WEF/IF_ADC1",
	"Nuww/DAC_WEF/IF_ADC1/IF_ADC2",
	"Nuww/DAC_WEF/IF_ADC2/IF_ADC1",
};

static SOC_ENUM_SINGWE_DECW(
	wt5650_if1_adc_in_enum, WT5645_TDM_CTWW_2,
	0, wt5650_if1_adc_in_swc);

static const stwuct snd_kcontwow_new wt5650_if1_adc_in_mux =
	SOC_DAPM_ENUM("IF1 ADC IN souwce", wt5650_if1_adc_in_enum);

/* MX-78 [15:14][13:12][11:10] */
static const chaw * const wt5645_tdm_adc_swap_sewect[] = {
	"W/W", "W/W", "W/W", "W/W"
};

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_adc_swot0_1_enum,
	WT5645_TDM_CTWW_2, 14, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_adc1_in_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN souwce", wt5650_tdm_adc_swot0_1_enum);

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_adc_swot2_3_enum,
	WT5645_TDM_CTWW_2, 12, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_adc2_in_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN souwce", wt5650_tdm_adc_swot2_3_enum);

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_adc_swot4_5_enum,
	WT5645_TDM_CTWW_2, 10, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_adc3_in_mux =
	SOC_DAPM_ENUM("IF1 ADC3 IN souwce", wt5650_tdm_adc_swot4_5_enum);

/* MX-77 [7:6][5:4][3:2] */
static SOC_ENUM_SINGWE_DECW(wt5645_tdm_adc_swot0_1_enum,
	WT5645_TDM_CTWW_1, 6, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_adc1_in_mux =
	SOC_DAPM_ENUM("IF1 ADC1 IN souwce", wt5645_tdm_adc_swot0_1_enum);

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_adc_swot2_3_enum,
	WT5645_TDM_CTWW_1, 4, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_adc2_in_mux =
	SOC_DAPM_ENUM("IF1 ADC2 IN souwce", wt5645_tdm_adc_swot2_3_enum);

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_adc_swot4_5_enum,
	WT5645_TDM_CTWW_1, 2, wt5645_tdm_adc_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_adc3_in_mux =
	SOC_DAPM_ENUM("IF1 ADC3 IN souwce", wt5645_tdm_adc_swot4_5_enum);

/* MX-79 [14:12][10:8][6:4][2:0] */
static const chaw * const wt5645_tdm_dac_swap_sewect[] = {
	"Swot0", "Swot1", "Swot2", "Swot3"
};

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_dac0_enum,
	WT5645_TDM_CTWW_3, 12, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_dac0_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC0 souwce", wt5645_tdm_dac0_enum);

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_dac1_enum,
	WT5645_TDM_CTWW_3, 8, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_dac1_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC1 souwce", wt5645_tdm_dac1_enum);

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_dac2_enum,
	WT5645_TDM_CTWW_3, 4, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_dac2_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC2 souwce", wt5645_tdm_dac2_enum);

static SOC_ENUM_SINGWE_DECW(wt5645_tdm_dac3_enum,
	WT5645_TDM_CTWW_3, 0, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5645_if1_dac3_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC3 souwce", wt5645_tdm_dac3_enum);

/* MX-7a [14:12][10:8][6:4][2:0] */
static SOC_ENUM_SINGWE_DECW(wt5650_tdm_dac0_enum,
	WT5650_TDM_CTWW_4, 12, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_dac0_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC0 souwce", wt5650_tdm_dac0_enum);

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_dac1_enum,
	WT5650_TDM_CTWW_4, 8, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_dac1_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC1 souwce", wt5650_tdm_dac1_enum);

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_dac2_enum,
	WT5650_TDM_CTWW_4, 4, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_dac2_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC2 souwce", wt5650_tdm_dac2_enum);

static SOC_ENUM_SINGWE_DECW(wt5650_tdm_dac3_enum,
	WT5650_TDM_CTWW_4, 0, wt5645_tdm_dac_swap_sewect);

static const stwuct snd_kcontwow_new wt5650_if1_dac3_tdm_sew_mux =
	SOC_DAPM_ENUM("IF1 DAC3 souwce", wt5650_tdm_dac3_enum);

/* MX-2d [3] [2] */
static const chaw * const wt5650_a_dac1_swc[] = {
	"DAC1", "Steweo DAC Mixew"
};

static SOC_ENUM_SINGWE_DECW(
	wt5650_a_dac1_w_enum, WT5650_A_DAC_SOUW,
	WT5650_A_DAC1_W_IN_SFT, wt5650_a_dac1_swc);

static const stwuct snd_kcontwow_new wt5650_a_dac1_w_mux =
	SOC_DAPM_ENUM("A DAC1 W souwce", wt5650_a_dac1_w_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5650_a_dac1_w_enum, WT5650_A_DAC_SOUW,
	WT5650_A_DAC1_W_IN_SFT, wt5650_a_dac1_swc);

static const stwuct snd_kcontwow_new wt5650_a_dac1_w_mux =
	SOC_DAPM_ENUM("A DAC1 W souwce", wt5650_a_dac1_w_enum);

/* MX-2d [1] [0] */
static const chaw * const wt5650_a_dac2_swc[] = {
	"Steweo DAC Mixew", "Mono DAC Mixew"
};

static SOC_ENUM_SINGWE_DECW(
	wt5650_a_dac2_w_enum, WT5650_A_DAC_SOUW,
	WT5650_A_DAC2_W_IN_SFT, wt5650_a_dac2_swc);

static const stwuct snd_kcontwow_new wt5650_a_dac2_w_mux =
	SOC_DAPM_ENUM("A DAC2 W souwce", wt5650_a_dac2_w_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5650_a_dac2_w_enum, WT5650_A_DAC_SOUW,
	WT5650_A_DAC2_W_IN_SFT, wt5650_a_dac2_swc);

static const stwuct snd_kcontwow_new wt5650_a_dac2_w_mux =
	SOC_DAPM_ENUM("A DAC2 W souwce", wt5650_a_dac2_w_enum);

/* MX-2F [13:12] */
static const chaw * const wt5645_if2_adc_in_swc[] = {
	"IF_ADC1", "IF_ADC2", "VAD_ADC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_if2_adc_in_enum, WT5645_DIG_INF1_DATA,
	WT5645_IF2_ADC_IN_SFT, wt5645_if2_adc_in_swc);

static const stwuct snd_kcontwow_new wt5645_if2_adc_in_mux =
	SOC_DAPM_ENUM("IF2 ADC IN souwce", wt5645_if2_adc_in_enum);

/* MX-31 [15] [13] [11] [9] */
static const chaw * const wt5645_pdm_swc[] = {
	"Mono DAC", "Steweo DAC"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_pdm1_w_enum, WT5645_PDM_OUT_CTWW,
	WT5645_PDM1_W_SFT, wt5645_pdm_swc);

static const stwuct snd_kcontwow_new wt5645_pdm1_w_mux =
	SOC_DAPM_ENUM("PDM1 W souwce", wt5645_pdm1_w_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5645_pdm1_w_enum, WT5645_PDM_OUT_CTWW,
	WT5645_PDM1_W_SFT, wt5645_pdm_swc);

static const stwuct snd_kcontwow_new wt5645_pdm1_w_mux =
	SOC_DAPM_ENUM("PDM1 W souwce", wt5645_pdm1_w_enum);

/* MX-9D [9:8] */
static const chaw * const wt5645_vad_adc_swc[] = {
	"Sto1 ADC W", "Mono ADC W", "Mono ADC W"
};

static SOC_ENUM_SINGWE_DECW(
	wt5645_vad_adc_enum, WT5645_VAD_CTWW4,
	WT5645_VAD_SEW_SFT, wt5645_vad_adc_swc);

static const stwuct snd_kcontwow_new wt5645_vad_adc_mux =
	SOC_DAPM_ENUM("VAD ADC souwce", wt5645_vad_adc_enum);

static const stwuct snd_kcontwow_new spk_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_SPK_VOW,
		WT5645_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new spk_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_SPK_VOW,
		WT5645_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hp_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_HP_VOW,
		WT5645_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new hp_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_HP_VOW,
		WT5645_W_MUTE_SFT, 1, 1);

static const stwuct snd_kcontwow_new pdm1_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_PDM_OUT_CTWW,
		WT5645_M_PDM1_W, 1, 1);

static const stwuct snd_kcontwow_new pdm1_w_vow_contwow =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5645_PDM_OUT_CTWW,
		WT5645_M_PDM1_W, 1, 1);

static void hp_amp_powew(stwuct snd_soc_component *component, int on)
{
	static int hp_amp_powew_count;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	int i, vaw;

	if (on) {
		if (hp_amp_powew_count <= 0) {
			if (wt5645->codec_type == CODEC_TYPE_WT5650) {
				snd_soc_component_wwite(component, WT5645_DEPOP_M2, 0x3100);
				snd_soc_component_wwite(component, WT5645_CHAWGE_PUMP,
					0x0e06);
				snd_soc_component_wwite(component, WT5645_DEPOP_M1, 0x000d);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					WT5645_HP_DCC_INT1, 0x9f01);
				fow (i = 0; i < 20; i++) {
					usweep_wange(1000, 1500);
					wegmap_wead(wt5645->wegmap, WT5645_PW_BASE +
						WT5645_HP_DCC_INT1, &vaw);
					if (!(vaw & 0x8000))
						bweak;
				}
				snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
					WT5645_HP_CO_MASK, WT5645_HP_CO_EN);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					0x3e, 0x7400);
				snd_soc_component_wwite(component, WT5645_DEPOP_M3, 0x0737);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					WT5645_MAMP_INT_WEG2, 0xfc00);
				snd_soc_component_wwite(component, WT5645_DEPOP_M2, 0x1140);
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W);
				msweep(90);
			} ewse {
				/* depop pawametews */
				snd_soc_component_update_bits(component, WT5645_DEPOP_M2,
					WT5645_DEPOP_MASK, WT5645_DEPOP_MAN);
				snd_soc_component_wwite(component, WT5645_DEPOP_M1, 0x000d);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					WT5645_HP_DCC_INT1, 0x9f01);
				mdeway(150);
				/* headphone amp powew on */
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_FV1 | WT5645_PWW_FV2, 0);
				snd_soc_component_update_bits(component, WT5645_PWW_VOW,
					WT5645_PWW_HV_W | WT5645_PWW_HV_W,
					WT5645_PWW_HV_W | WT5645_PWW_HV_W);
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W |
					WT5645_PWW_HA,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W |
					WT5645_PWW_HA);
				mdeway(5);
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_FV1 | WT5645_PWW_FV2,
					WT5645_PWW_FV1 | WT5645_PWW_FV2);

				snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
					WT5645_HP_CO_MASK | WT5645_HP_SG_MASK,
					WT5645_HP_CO_EN | WT5645_HP_SG_EN);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					0x14, 0x1aaa);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					0x24, 0x0430);
			}
		}
		hp_amp_powew_count++;
	} ewse {
		hp_amp_powew_count--;
		if (hp_amp_powew_count <= 0) {
			if (wt5645->codec_type == CODEC_TYPE_WT5650) {
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					0x3e, 0x7400);
				snd_soc_component_wwite(component, WT5645_DEPOP_M3, 0x0737);
				wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
					WT5645_MAMP_INT_WEG2, 0xfc00);
				snd_soc_component_wwite(component, WT5645_DEPOP_M2, 0x1140);
				msweep(100);
				snd_soc_component_wwite(component, WT5645_DEPOP_M1, 0x0001);
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W, 0);
			} ewse {
				snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
					WT5645_HP_SG_MASK |
					WT5645_HP_W_SMT_MASK |
					WT5645_HP_W_SMT_MASK,
					WT5645_HP_SG_DIS |
					WT5645_HP_W_SMT_DIS |
					WT5645_HP_W_SMT_DIS);
				/* headphone amp powew down */
				snd_soc_component_wwite(component, WT5645_DEPOP_M1, 0x0000);
				snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
					WT5645_PWW_HP_W | WT5645_PWW_HP_W |
					WT5645_PWW_HA, 0);
				snd_soc_component_update_bits(component, WT5645_DEPOP_M2,
					WT5645_DEPOP_MASK, 0);
			}
		}
	}
}

static int wt5645_hp_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hp_amp_powew(component, 1);
		/* headphone unmute sequence */
		if (wt5645->codec_type == CODEC_TYPE_WT5645) {
			snd_soc_component_update_bits(component, WT5645_DEPOP_M3,
				WT5645_CP_FQ1_MASK | WT5645_CP_FQ2_MASK |
				WT5645_CP_FQ3_MASK,
				(WT5645_CP_FQ_192_KHZ << WT5645_CP_FQ1_SFT) |
				(WT5645_CP_FQ_12_KHZ << WT5645_CP_FQ2_SFT) |
				(WT5645_CP_FQ_192_KHZ << WT5645_CP_FQ3_SFT));
			wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
				WT5645_MAMP_INT_WEG2, 0xfc00);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_SMT_TWIG_MASK, WT5645_SMT_TWIG_EN);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_WSTN_MASK, WT5645_WSTN_EN);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_WSTN_MASK | WT5645_HP_W_SMT_MASK |
				WT5645_HP_W_SMT_MASK, WT5645_WSTN_DIS |
				WT5645_HP_W_SMT_EN | WT5645_HP_W_SMT_EN);
			msweep(40);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_HP_SG_MASK | WT5645_HP_W_SMT_MASK |
				WT5645_HP_W_SMT_MASK, WT5645_HP_SG_DIS |
				WT5645_HP_W_SMT_DIS | WT5645_HP_W_SMT_DIS);
		}
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		/* headphone mute sequence */
		if (wt5645->codec_type == CODEC_TYPE_WT5645) {
			snd_soc_component_update_bits(component, WT5645_DEPOP_M3,
				WT5645_CP_FQ1_MASK | WT5645_CP_FQ2_MASK |
				WT5645_CP_FQ3_MASK,
				(WT5645_CP_FQ_96_KHZ << WT5645_CP_FQ1_SFT) |
				(WT5645_CP_FQ_12_KHZ << WT5645_CP_FQ2_SFT) |
				(WT5645_CP_FQ_96_KHZ << WT5645_CP_FQ3_SFT));
			wegmap_wwite(wt5645->wegmap, WT5645_PW_BASE +
				WT5645_MAMP_INT_WEG2, 0xfc00);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_HP_SG_MASK, WT5645_HP_SG_EN);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_WSTP_MASK, WT5645_WSTP_EN);
			snd_soc_component_update_bits(component, WT5645_DEPOP_M1,
				WT5645_WSTP_MASK | WT5645_HP_W_SMT_MASK |
				WT5645_HP_W_SMT_MASK, WT5645_WSTP_DIS |
				WT5645_HP_W_SMT_EN | WT5645_HP_W_SMT_EN);
			msweep(30);
		}
		hp_amp_powew(component, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5645_spk_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt5645_enabwe_hweq(component);
		snd_soc_component_update_bits(component, WT5645_PWW_DIG1,
			WT5645_PWW_CWS_D | WT5645_PWW_CWS_D_W |
			WT5645_PWW_CWS_D_W,
			WT5645_PWW_CWS_D | WT5645_PWW_CWS_D_W |
			WT5645_PWW_CWS_D_W);
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW3,
			WT5645_DET_CWK_MASK, WT5645_DET_CWK_MODE1);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW3,
			WT5645_DET_CWK_MASK, WT5645_DET_CWK_DIS);
		snd_soc_component_wwite(component, WT5645_EQ_CTWW2, 0);
		snd_soc_component_update_bits(component, WT5645_PWW_DIG1,
			WT5645_PWW_CWS_D | WT5645_PWW_CWS_D_W |
			WT5645_PWW_CWS_D_W, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5645_wout_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hp_amp_powew(component, 1);
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
			WT5645_PWW_WM, WT5645_PWW_WM);
		snd_soc_component_update_bits(component, WT5645_WOUT1,
			WT5645_W_MUTE | WT5645_W_MUTE, 0);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5645_WOUT1,
			WT5645_W_MUTE | WT5645_W_MUTE,
			WT5645_W_MUTE | WT5645_W_MUTE);
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
			WT5645_PWW_WM, 0);
		hp_amp_powew(component, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5645_bst2_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG2,
			WT5645_PWW_BST2_P, WT5645_PWW_BST2_P);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG2,
			WT5645_PWW_BST2_P, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5645_set_micbias1_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW2,
			WT5645_MICBIAS1_POW_CTWW_SEW_MASK,
			WT5645_MICBIAS1_POW_CTWW_SEW_M);
		bweak;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW2,
			WT5645_MICBIAS1_POW_CTWW_SEW_MASK,
			WT5645_MICBIAS1_POW_CTWW_SEW_A);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5645_set_micbias2_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW2,
			WT5645_MICBIAS2_POW_CTWW_SEW_MASK,
			WT5645_MICBIAS2_POW_CTWW_SEW_M);
		bweak;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, WT5645_GEN_CTWW2,
			WT5645_MICBIAS2_POW_CTWW_SEW_MASK,
			WT5645_MICBIAS2_POW_CTWW_SEW_A);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt5645_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("WDO2", WT5645_PWW_MIXEW,
		WT5645_PWW_WDO2_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW1", WT5645_PWW_ANWG2,
		WT5645_PWW_PWW_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("JD Powew", WT5645_PWW_ANWG2,
		WT5645_PWW_JD1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Det Powew", WT5645_PWW_VOW,
		WT5645_PWW_MIC_DET_BIT, 0, NUWW, 0),

	/* ASWC */
	SND_SOC_DAPM_SUPPWY_S("I2S1 ASWC", 1, WT5645_ASWC_1,
			      11, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S2 ASWC", 1, WT5645_ASWC_1,
			      12, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DAC STO ASWC", 1, WT5645_ASWC_1,
			      10, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DAC MONO W ASWC", 1, WT5645_ASWC_1,
			      9, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DAC MONO W ASWC", 1, WT5645_ASWC_1,
			      8, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DMIC STO1 ASWC", 1, WT5645_ASWC_1,
			      7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DMIC MONO W ASWC", 1, WT5645_ASWC_1,
			      5, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DMIC MONO W ASWC", 1, WT5645_ASWC_1,
			      4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ADC STO1 ASWC", 1, WT5645_ASWC_1,
			      3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ADC MONO W ASWC", 1, WT5645_ASWC_1,
			      1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ADC MONO W ASWC", 1, WT5645_ASWC_1,
			      0, 0, NUWW, 0),

	/* Input Side */
	/* micbias */
	SND_SOC_DAPM_SUPPWY("micbias1", WT5645_PWW_ANWG2,
			WT5645_PWW_MB1_BIT, 0, wt5645_set_micbias1_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("micbias2", WT5645_PWW_ANWG2,
			WT5645_PWW_MB2_BIT, 0, wt5645_set_micbias2_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	/* Input Wines */
	SND_SOC_DAPM_INPUT("DMIC W1"),
	SND_SOC_DAPM_INPUT("DMIC W1"),
	SND_SOC_DAPM_INPUT("DMIC W2"),
	SND_SOC_DAPM_INPUT("DMIC W2"),

	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	SND_SOC_DAPM_INPUT("Haptic Genewatow"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DMIC CWK", SND_SOC_NOPM, 0, 0,
		set_dmic_cwk, SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SUPPWY("DMIC1 Powew", WT5645_DMIC_CTWW1,
		WT5645_DMIC_1_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DMIC2 Powew", WT5645_DMIC_CTWW1,
		WT5645_DMIC_2_EN_SFT, 0, NUWW, 0),
	/* Boost */
	SND_SOC_DAPM_PGA("BST1", WT5645_PWW_ANWG2,
		WT5645_PWW_BST1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_E("BST2", WT5645_PWW_ANWG2,
		WT5645_PWW_BST2_BIT, 0, NUWW, 0, wt5645_bst2_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	/* Input Vowume */
	SND_SOC_DAPM_PGA("INW VOW", WT5645_PWW_VOW,
		WT5645_PWW_IN_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INW VOW", WT5645_PWW_VOW,
		WT5645_PWW_IN_W_BIT, 0, NUWW, 0),
	/* WEC Mixew */
	SND_SOC_DAPM_MIXEW("WECMIXW", WT5645_PWW_MIXEW, WT5645_PWW_WM_W_BIT,
			0, wt5645_wec_w_mix, AWWAY_SIZE(wt5645_wec_w_mix)),
	SND_SOC_DAPM_MIXEW("WECMIXW", WT5645_PWW_MIXEW, WT5645_PWW_WM_W_BIT,
			0, wt5645_wec_w_mix, AWWAY_SIZE(wt5645_wec_w_mix)),
	/* ADCs */
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SUPPWY("ADC W powew", WT5645_PWW_DIG1,
		WT5645_PWW_ADC_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC W powew", WT5645_PWW_DIG1,
		WT5645_PWW_ADC_W_BIT, 0, NUWW, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Steweo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_sto_adc2_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W2 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_sto_adc2_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_sto_adc1_mux),
	SND_SOC_DAPM_MUX("Steweo1 ADC W1 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_sto_adc1_mux),
	SND_SOC_DAPM_MUX("Mono DMIC W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_dmic_w_mux),
	SND_SOC_DAPM_MUX("Mono DMIC W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_dmic_w_mux),
	SND_SOC_DAPM_MUX("Mono ADC W2 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_adc_w2_mux),
	SND_SOC_DAPM_MUX("Mono ADC W1 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_adc_w1_mux),
	SND_SOC_DAPM_MUX("Mono ADC W1 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_adc_w1_mux),
	SND_SOC_DAPM_MUX("Mono ADC W2 Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_mono_adc_w2_mux),
	/* ADC Mixew */

	SND_SOC_DAPM_SUPPWY_S("adc steweo1 fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_ADC_S1F_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW_E("Sto1 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_sto1_adc_w_mix, AWWAY_SIZE(wt5645_sto1_adc_w_mix),
		NUWW, 0),
	SND_SOC_DAPM_MIXEW_E("Sto1 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_sto1_adc_w_mix, AWWAY_SIZE(wt5645_sto1_adc_w_mix),
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("adc mono weft fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_ADC_MF_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW_E("Mono ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_mono_adc_w_mix, AWWAY_SIZE(wt5645_mono_adc_w_mix),
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("adc mono wight fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_ADC_MF_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW_E("Mono ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_mono_adc_w_mix, AWWAY_SIZE(wt5645_mono_adc_w_mix),
		NUWW, 0),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Steweo1 ADC MIXW", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Steweo1 ADC MIXW", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Sto2 ADC WW MIX", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("VAD_ADC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF_ADC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF_ADC2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1_ADC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1_ADC2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1_ADC3", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1_ADC4", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* IF1 2 Mux */
	SND_SOC_DAPM_MUX("IF2 ADC Mux", SND_SOC_NOPM,
		0, 0, &wt5645_if2_adc_in_mux),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SUPPWY("I2S1", WT5645_PWW_DIG1,
		WT5645_PWW_I2S1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC0", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC3", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("I2S2", WT5645_PWW_DIG1,
		WT5645_PWW_I2S2_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 DAC W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF2 ADC", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Digitaw Intewface Sewect */
	SND_SOC_DAPM_MUX("VAD ADC Mux", SND_SOC_NOPM,
		0, 0, &wt5645_vad_adc_mux),

	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WX", "AIF2 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DAC mixew befowe sound effect  */
	SND_SOC_DAPM_MIXEW("DAC1 MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_dac_w_mix, AWWAY_SIZE(wt5645_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("DAC1 MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_dac_w_mix, AWWAY_SIZE(wt5645_dac_w_mix)),

	/* DAC2 channew Mux */
	SND_SOC_DAPM_MUX("DAC W2 Mux", SND_SOC_NOPM, 0, 0, &wt5645_dac_w2_mux),
	SND_SOC_DAPM_MUX("DAC W2 Mux", SND_SOC_NOPM, 0, 0, &wt5645_dac_w2_mux),
	SND_SOC_DAPM_PGA("DAC W2 Vowume", WT5645_PWW_DIG1,
		WT5645_PWW_DAC_W2_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DAC W2 Vowume", WT5645_PWW_DIG1,
		WT5645_PWW_DAC_W2_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("DAC1 W Mux", SND_SOC_NOPM, 0, 0, &wt5645_dac1w_mux),
	SND_SOC_DAPM_MUX("DAC1 W Mux", SND_SOC_NOPM, 0, 0, &wt5645_dac1w_mux),

	/* DAC Mixew */
	SND_SOC_DAPM_SUPPWY_S("dac steweo1 fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_DAC_S1F_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("dac mono weft fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_DAC_MF_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("dac mono wight fiwtew", 1, WT5645_PWW_DIG2,
		WT5645_PWW_DAC_MF_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Steweo DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_sto_dac_w_mix, AWWAY_SIZE(wt5645_sto_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("Steweo DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_sto_dac_w_mix, AWWAY_SIZE(wt5645_sto_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("Mono DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_mono_dac_w_mix, AWWAY_SIZE(wt5645_mono_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("Mono DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_mono_dac_w_mix, AWWAY_SIZE(wt5645_mono_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_dig_w_mix, AWWAY_SIZE(wt5645_dig_w_mix)),
	SND_SOC_DAPM_MIXEW("DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5645_dig_w_mix, AWWAY_SIZE(wt5645_dig_w_mix)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC W1", NUWW, WT5645_PWW_DIG1, WT5645_PWW_DAC_W1_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC W2", NUWW, WT5645_PWW_DIG1, WT5645_PWW_DAC_W2_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC W1", NUWW, WT5645_PWW_DIG1, WT5645_PWW_DAC_W1_BIT,
		0),
	SND_SOC_DAPM_DAC("DAC W2", NUWW, WT5645_PWW_DIG1, WT5645_PWW_DAC_W2_BIT,
		0),
	/* OUT Mixew */
	SND_SOC_DAPM_MIXEW("SPK MIXW", WT5645_PWW_MIXEW, WT5645_PWW_SM_W_BIT,
		0, wt5645_spk_w_mix, AWWAY_SIZE(wt5645_spk_w_mix)),
	SND_SOC_DAPM_MIXEW("SPK MIXW", WT5645_PWW_MIXEW, WT5645_PWW_SM_W_BIT,
		0, wt5645_spk_w_mix, AWWAY_SIZE(wt5645_spk_w_mix)),
	SND_SOC_DAPM_MIXEW("OUT MIXW", WT5645_PWW_MIXEW, WT5645_PWW_OM_W_BIT,
		0, wt5645_out_w_mix, AWWAY_SIZE(wt5645_out_w_mix)),
	SND_SOC_DAPM_MIXEW("OUT MIXW", WT5645_PWW_MIXEW, WT5645_PWW_OM_W_BIT,
		0, wt5645_out_w_mix, AWWAY_SIZE(wt5645_out_w_mix)),
	/* Ouput Vowume */
	SND_SOC_DAPM_SWITCH("SPKVOW W", WT5645_PWW_VOW, WT5645_PWW_SV_W_BIT, 0,
		&spk_w_vow_contwow),
	SND_SOC_DAPM_SWITCH("SPKVOW W", WT5645_PWW_VOW, WT5645_PWW_SV_W_BIT, 0,
		&spk_w_vow_contwow),
	SND_SOC_DAPM_MIXEW("HPOVOW MIXW", WT5645_PWW_VOW, WT5645_PWW_HV_W_BIT,
		0, wt5645_hpvoww_mix, AWWAY_SIZE(wt5645_hpvoww_mix)),
	SND_SOC_DAPM_MIXEW("HPOVOW MIXW", WT5645_PWW_VOW, WT5645_PWW_HV_W_BIT,
		0, wt5645_hpvoww_mix, AWWAY_SIZE(wt5645_hpvoww_mix)),
	SND_SOC_DAPM_SUPPWY("HPOVOW MIXW Powew", WT5645_PWW_MIXEW,
		WT5645_PWW_HM_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("HPOVOW MIXW Powew", WT5645_PWW_MIXEW,
		WT5645_PWW_HM_W_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DAC 1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DAC 2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HPOVOW", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SWITCH("HPOVOW W", SND_SOC_NOPM, 0, 0, &hp_w_vow_contwow),
	SND_SOC_DAPM_SWITCH("HPOVOW W", SND_SOC_NOPM, 0, 0, &hp_w_vow_contwow),

	/* HPO/WOUT/Mono Mixew */
	SND_SOC_DAPM_MIXEW("SPOW MIX", SND_SOC_NOPM, 0, 0, wt5645_spo_w_mix,
		AWWAY_SIZE(wt5645_spo_w_mix)),
	SND_SOC_DAPM_MIXEW("SPOW MIX", SND_SOC_NOPM, 0, 0, wt5645_spo_w_mix,
		AWWAY_SIZE(wt5645_spo_w_mix)),
	SND_SOC_DAPM_MIXEW("HPO MIX", SND_SOC_NOPM, 0, 0, wt5645_hpo_mix,
		AWWAY_SIZE(wt5645_hpo_mix)),
	SND_SOC_DAPM_MIXEW("WOUT MIX", SND_SOC_NOPM, 0, 0, wt5645_wout_mix,
		AWWAY_SIZE(wt5645_wout_mix)),

	SND_SOC_DAPM_PGA_S("HP amp", 1, SND_SOC_NOPM, 0, 0, wt5645_hp_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("WOUT amp", 1, SND_SOC_NOPM, 0, 0, wt5645_wout_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_S("SPK amp", 2, SND_SOC_NOPM, 0, 0, wt5645_spk_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),

	/* PDM */
	SND_SOC_DAPM_SUPPWY("PDM1 Powew", WT5645_PWW_DIG2, WT5645_PWW_PDM1_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_MUX("PDM1 W Mux", SND_SOC_NOPM, 0, 0, &wt5645_pdm1_w_mux),
	SND_SOC_DAPM_MUX("PDM1 W Mux", SND_SOC_NOPM, 0, 0, &wt5645_pdm1_w_mux),

	SND_SOC_DAPM_SWITCH("PDM1 W", SND_SOC_NOPM, 0, 0, &pdm1_w_vow_contwow),
	SND_SOC_DAPM_SWITCH("PDM1 W", SND_SOC_NOPM, 0, 0, &pdm1_w_vow_contwow),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("WOUTW"),
	SND_SOC_DAPM_OUTPUT("WOUTW"),
	SND_SOC_DAPM_OUTPUT("PDM1W"),
	SND_SOC_DAPM_OUTPUT("PDM1W"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
};

static const stwuct snd_soc_dapm_widget wt5645_specific_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("WT5645 IF1 DAC1 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_if1_dac0_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 DAC1 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_if1_dac1_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 DAC2 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_if1_dac2_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 DAC2 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5645_if1_dac3_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 ADC Mux", SND_SOC_NOPM,
		0, 0, &wt5645_if1_adc_in_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 ADC1 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5645_if1_adc1_in_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 ADC2 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5645_if1_adc2_in_mux),
	SND_SOC_DAPM_MUX("WT5645 IF1 ADC3 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5645_if1_adc3_in_mux),
};

static const stwuct snd_soc_dapm_widget wt5650_specific_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("A DAC1 W Mux", SND_SOC_NOPM,
		0, 0, &wt5650_a_dac1_w_mux),
	SND_SOC_DAPM_MUX("A DAC1 W Mux", SND_SOC_NOPM,
		0, 0, &wt5650_a_dac1_w_mux),
	SND_SOC_DAPM_MUX("A DAC2 W Mux", SND_SOC_NOPM,
		0, 0, &wt5650_a_dac2_w_mux),
	SND_SOC_DAPM_MUX("A DAC2 W Mux", SND_SOC_NOPM,
		0, 0, &wt5650_a_dac2_w_mux),

	SND_SOC_DAPM_MUX("WT5650 IF1 ADC1 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5650_if1_adc1_in_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 ADC2 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5650_if1_adc2_in_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 ADC3 Swap Mux", SND_SOC_NOPM,
		0, 0, &wt5650_if1_adc3_in_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 ADC Mux", SND_SOC_NOPM,
		0, 0, &wt5650_if1_adc_in_mux),

	SND_SOC_DAPM_MUX("WT5650 IF1 DAC1 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5650_if1_dac0_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 DAC1 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5650_if1_dac1_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 DAC2 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5650_if1_dac2_tdm_sew_mux),
	SND_SOC_DAPM_MUX("WT5650 IF1 DAC2 W Mux", SND_SOC_NOPM, 0, 0,
		&wt5650_if1_dac3_tdm_sew_mux),
};

static const stwuct snd_soc_dapm_woute wt5645_dapm_woutes[] = {
	{ "adc steweo1 fiwtew", NUWW, "ADC STO1 ASWC", is_using_aswc },
	{ "adc mono weft fiwtew", NUWW, "ADC MONO W ASWC", is_using_aswc },
	{ "adc mono wight fiwtew", NUWW, "ADC MONO W ASWC", is_using_aswc },
	{ "dac mono weft fiwtew", NUWW, "DAC MONO W ASWC", is_using_aswc },
	{ "dac mono wight fiwtew", NUWW, "DAC MONO W ASWC", is_using_aswc },
	{ "dac steweo1 fiwtew", NUWW, "DAC STO ASWC", is_using_aswc },

	{ "I2S1", NUWW, "I2S1 ASWC" },
	{ "I2S2", NUWW, "I2S2 ASWC" },

	{ "IN1P", NUWW, "WDO2" },
	{ "IN2P", NUWW, "WDO2" },

	{ "DMIC1", NUWW, "DMIC W1" },
	{ "DMIC1", NUWW, "DMIC W1" },
	{ "DMIC2", NUWW, "DMIC W2" },
	{ "DMIC2", NUWW, "DMIC W2" },

	{ "BST1", NUWW, "IN1P" },
	{ "BST1", NUWW, "IN1N" },
	{ "BST1", NUWW, "JD Powew" },
	{ "BST1", NUWW, "Mic Det Powew" },
	{ "BST2", NUWW, "IN2P" },
	{ "BST2", NUWW, "IN2N" },

	{ "INW VOW", NUWW, "IN2P" },
	{ "INW VOW", NUWW, "IN2N" },

	{ "WECMIXW", "HPOW Switch", "HPOW" },
	{ "WECMIXW", "INW Switch", "INW VOW" },
	{ "WECMIXW", "BST2 Switch", "BST2" },
	{ "WECMIXW", "BST1 Switch", "BST1" },
	{ "WECMIXW", "OUT MIXW Switch", "OUT MIXW" },

	{ "WECMIXW", "HPOW Switch", "HPOW" },
	{ "WECMIXW", "INW Switch", "INW VOW" },
	{ "WECMIXW", "BST2 Switch", "BST2" },
	{ "WECMIXW", "BST1 Switch", "BST1" },
	{ "WECMIXW", "OUT MIXW Switch", "OUT MIXW" },

	{ "ADC W", NUWW, "WECMIXW" },
	{ "ADC W", NUWW, "ADC W powew" },
	{ "ADC W", NUWW, "WECMIXW" },
	{ "ADC W", NUWW, "ADC W powew" },

	{"DMIC W1", NUWW, "DMIC CWK"},
	{"DMIC W1", NUWW, "DMIC1 Powew"},
	{"DMIC W1", NUWW, "DMIC CWK"},
	{"DMIC W1", NUWW, "DMIC1 Powew"},
	{"DMIC W2", NUWW, "DMIC CWK"},
	{"DMIC W2", NUWW, "DMIC2 Powew"},
	{"DMIC W2", NUWW, "DMIC CWK"},
	{"DMIC W2", NUWW, "DMIC2 Powew"},

	{ "Steweo1 DMIC Mux", "DMIC1", "DMIC1" },
	{ "Steweo1 DMIC Mux", "DMIC2", "DMIC2" },
	{ "Steweo1 DMIC Mux", NUWW, "DMIC STO1 ASWC" },

	{ "Mono DMIC W Mux", "DMIC1", "DMIC W1" },
	{ "Mono DMIC W Mux", "DMIC2", "DMIC W2" },
	{ "Mono DMIC W Mux", NUWW, "DMIC MONO W ASWC" },

	{ "Mono DMIC W Mux", "DMIC1", "DMIC W1" },
	{ "Mono DMIC W Mux", "DMIC2", "DMIC W2" },
	{ "Mono DMIC W Mux", NUWW, "DMIC MONO W ASWC" },

	{ "Steweo1 ADC W2 Mux", "DMIC", "Steweo1 DMIC Mux" },
	{ "Steweo1 ADC W2 Mux", "DAC MIX", "DAC MIXW" },
	{ "Steweo1 ADC W1 Mux", "ADC", "ADC W" },
	{ "Steweo1 ADC W1 Mux", "DAC MIX", "DAC MIXW" },

	{ "Steweo1 ADC W1 Mux", "ADC", "ADC W" },
	{ "Steweo1 ADC W1 Mux", "DAC MIX", "DAC MIXW" },
	{ "Steweo1 ADC W2 Mux", "DMIC", "Steweo1 DMIC Mux" },
	{ "Steweo1 ADC W2 Mux", "DAC MIX", "DAC MIXW" },

	{ "Mono ADC W2 Mux", "DMIC", "Mono DMIC W Mux" },
	{ "Mono ADC W2 Mux", "Mono DAC MIXW", "Mono DAC MIXW" },
	{ "Mono ADC W1 Mux", "Mono DAC MIXW", "Mono DAC MIXW" },
	{ "Mono ADC W1 Mux", "ADC", "ADC W" },

	{ "Mono ADC W1 Mux", "Mono DAC MIXW", "Mono DAC MIXW" },
	{ "Mono ADC W1 Mux", "ADC", "ADC W" },
	{ "Mono ADC W2 Mux", "DMIC", "Mono DMIC W Mux" },
	{ "Mono ADC W2 Mux", "Mono DAC MIXW", "Mono DAC MIXW" },

	{ "Sto1 ADC MIXW", "ADC1 Switch", "Steweo1 ADC W1 Mux" },
	{ "Sto1 ADC MIXW", "ADC2 Switch", "Steweo1 ADC W2 Mux" },
	{ "Sto1 ADC MIXW", "ADC1 Switch", "Steweo1 ADC W1 Mux" },
	{ "Sto1 ADC MIXW", "ADC2 Switch", "Steweo1 ADC W2 Mux" },

	{ "Steweo1 ADC MIXW", NUWW, "Sto1 ADC MIXW" },
	{ "Steweo1 ADC MIXW", NUWW, "adc steweo1 fiwtew" },
	{ "adc steweo1 fiwtew", NUWW, "PWW1", is_sys_cwk_fwom_pww },

	{ "Steweo1 ADC MIXW", NUWW, "Sto1 ADC MIXW" },
	{ "Steweo1 ADC MIXW", NUWW, "adc steweo1 fiwtew" },
	{ "adc steweo1 fiwtew", NUWW, "PWW1", is_sys_cwk_fwom_pww },

	{ "Mono ADC MIXW", "ADC1 Switch", "Mono ADC W1 Mux" },
	{ "Mono ADC MIXW", "ADC2 Switch", "Mono ADC W2 Mux" },
	{ "Mono ADC MIXW", NUWW, "adc mono weft fiwtew" },
	{ "adc mono weft fiwtew", NUWW, "PWW1", is_sys_cwk_fwom_pww },

	{ "Mono ADC MIXW", "ADC1 Switch", "Mono ADC W1 Mux" },
	{ "Mono ADC MIXW", "ADC2 Switch", "Mono ADC W2 Mux" },
	{ "Mono ADC MIXW", NUWW, "adc mono wight fiwtew" },
	{ "adc mono wight fiwtew", NUWW, "PWW1", is_sys_cwk_fwom_pww },

	{ "VAD ADC Mux", "Sto1 ADC W", "Steweo1 ADC MIXW" },
	{ "VAD ADC Mux", "Mono ADC W", "Mono ADC MIXW" },
	{ "VAD ADC Mux", "Mono ADC W", "Mono ADC MIXW" },

	{ "IF_ADC1", NUWW, "Steweo1 ADC MIXW" },
	{ "IF_ADC1", NUWW, "Steweo1 ADC MIXW" },
	{ "IF_ADC2", NUWW, "Mono ADC MIXW" },
	{ "IF_ADC2", NUWW, "Mono ADC MIXW" },
	{ "VAD_ADC", NUWW, "VAD ADC Mux" },

	{ "IF2 ADC Mux", "IF_ADC1", "IF_ADC1" },
	{ "IF2 ADC Mux", "IF_ADC2", "IF_ADC2" },
	{ "IF2 ADC Mux", "VAD_ADC", "VAD_ADC" },

	{ "IF1 ADC", NUWW, "I2S1" },
	{ "IF2 ADC", NUWW, "I2S2" },
	{ "IF2 ADC", NUWW, "IF2 ADC Mux" },

	{ "AIF2TX", NUWW, "IF2 ADC" },

	{ "IF1 DAC0", NUWW, "AIF1WX" },
	{ "IF1 DAC1", NUWW, "AIF1WX" },
	{ "IF1 DAC2", NUWW, "AIF1WX" },
	{ "IF1 DAC3", NUWW, "AIF1WX" },
	{ "IF2 DAC", NUWW, "AIF2WX" },

	{ "IF1 DAC0", NUWW, "I2S1" },
	{ "IF1 DAC1", NUWW, "I2S1" },
	{ "IF1 DAC2", NUWW, "I2S1" },
	{ "IF1 DAC3", NUWW, "I2S1" },
	{ "IF2 DAC", NUWW, "I2S2" },

	{ "IF2 DAC W", NUWW, "IF2 DAC" },
	{ "IF2 DAC W", NUWW, "IF2 DAC" },

	{ "DAC1 W Mux", "IF2 DAC", "IF2 DAC W" },
	{ "DAC1 W Mux", "IF2 DAC", "IF2 DAC W" },

	{ "DAC1 MIXW", "Steweo ADC Switch", "Steweo1 ADC MIXW" },
	{ "DAC1 MIXW", "DAC1 Switch", "DAC1 W Mux" },
	{ "DAC1 MIXW", NUWW, "dac steweo1 fiwtew" },
	{ "DAC1 MIXW", "Steweo ADC Switch", "Steweo1 ADC MIXW" },
	{ "DAC1 MIXW", "DAC1 Switch", "DAC1 W Mux" },
	{ "DAC1 MIXW", NUWW, "dac steweo1 fiwtew" },

	{ "DAC W2 Mux", "IF2 DAC", "IF2 DAC W" },
	{ "DAC W2 Mux", "Mono ADC", "Mono ADC MIXW" },
	{ "DAC W2 Mux", "VAD_ADC", "VAD_ADC" },
	{ "DAC W2 Vowume", NUWW, "DAC W2 Mux" },
	{ "DAC W2 Vowume", NUWW, "dac mono weft fiwtew" },

	{ "DAC W2 Mux", "IF2 DAC", "IF2 DAC W" },
	{ "DAC W2 Mux", "Mono ADC", "Mono ADC MIXW" },
	{ "DAC W2 Mux", "Haptic", "Haptic Genewatow" },
	{ "DAC W2 Vowume", NUWW, "DAC W2 Mux" },
	{ "DAC W2 Vowume", NUWW, "dac mono wight fiwtew" },

	{ "Steweo DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Steweo DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Steweo DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Steweo DAC MIXW", NUWW, "dac steweo1 fiwtew" },
	{ "Steweo DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Steweo DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Steweo DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Steweo DAC MIXW", NUWW, "dac steweo1 fiwtew" },

	{ "Mono DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Mono DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Mono DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Mono DAC MIXW", NUWW, "dac mono weft fiwtew" },
	{ "Mono DAC MIXW", "DAC W1 Switch", "DAC1 MIXW" },
	{ "Mono DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Mono DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "Mono DAC MIXW", NUWW, "dac mono wight fiwtew" },

	{ "DAC MIXW", "Sto DAC Mix W Switch", "Steweo DAC MIXW" },
	{ "DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "DAC MIXW", "Sto DAC Mix W Switch", "Steweo DAC MIXW" },
	{ "DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },
	{ "DAC MIXW", "DAC W2 Switch", "DAC W2 Vowume" },

	{ "DAC W1", NUWW, "PWW1", is_sys_cwk_fwom_pww },
	{ "DAC W1", NUWW, "PWW1", is_sys_cwk_fwom_pww },
	{ "DAC W2", NUWW, "PWW1", is_sys_cwk_fwom_pww },
	{ "DAC W2", NUWW, "PWW1", is_sys_cwk_fwom_pww },

	{ "SPK MIXW", "BST1 Switch", "BST1" },
	{ "SPK MIXW", "INW Switch", "INW VOW" },
	{ "SPK MIXW", "DAC W1 Switch", "DAC W1" },
	{ "SPK MIXW", "DAC W2 Switch", "DAC W2" },
	{ "SPK MIXW", "BST2 Switch", "BST2" },
	{ "SPK MIXW", "INW Switch", "INW VOW" },
	{ "SPK MIXW", "DAC W1 Switch", "DAC W1" },
	{ "SPK MIXW", "DAC W2 Switch", "DAC W2" },

	{ "OUT MIXW", "BST1 Switch", "BST1" },
	{ "OUT MIXW", "INW Switch", "INW VOW" },
	{ "OUT MIXW", "DAC W2 Switch", "DAC W2" },
	{ "OUT MIXW", "DAC W1 Switch", "DAC W1" },

	{ "OUT MIXW", "BST2 Switch", "BST2" },
	{ "OUT MIXW", "INW Switch", "INW VOW" },
	{ "OUT MIXW", "DAC W2 Switch", "DAC W2" },
	{ "OUT MIXW", "DAC W1 Switch", "DAC W1" },

	{ "HPOVOW MIXW", "DAC1 Switch", "DAC W1" },
	{ "HPOVOW MIXW", "DAC2 Switch", "DAC W2" },
	{ "HPOVOW MIXW", "INW Switch", "INW VOW" },
	{ "HPOVOW MIXW", "BST1 Switch", "BST1" },
	{ "HPOVOW MIXW", NUWW, "HPOVOW MIXW Powew" },
	{ "HPOVOW MIXW", "DAC1 Switch", "DAC W1" },
	{ "HPOVOW MIXW", "DAC2 Switch", "DAC W2" },
	{ "HPOVOW MIXW", "INW Switch", "INW VOW" },
	{ "HPOVOW MIXW", "BST2 Switch", "BST2" },
	{ "HPOVOW MIXW", NUWW, "HPOVOW MIXW Powew" },

	{ "DAC 2", NUWW, "DAC W2" },
	{ "DAC 2", NUWW, "DAC W2" },
	{ "DAC 1", NUWW, "DAC W1" },
	{ "DAC 1", NUWW, "DAC W1" },
	{ "HPOVOW W", "Switch", "HPOVOW MIXW" },
	{ "HPOVOW W", "Switch", "HPOVOW MIXW" },
	{ "HPOVOW", NUWW, "HPOVOW W" },
	{ "HPOVOW", NUWW, "HPOVOW W" },
	{ "HPO MIX", "DAC1 Switch", "DAC 1" },
	{ "HPO MIX", "HPVOW Switch", "HPOVOW" },

	{ "SPKVOW W", "Switch", "SPK MIXW" },
	{ "SPKVOW W", "Switch", "SPK MIXW" },

	{ "SPOW MIX", "DAC W1 Switch", "DAC W1" },
	{ "SPOW MIX", "SPKVOW W Switch", "SPKVOW W" },
	{ "SPOW MIX", "DAC W1 Switch", "DAC W1" },
	{ "SPOW MIX", "SPKVOW W Switch", "SPKVOW W" },

	{ "WOUT MIX", "DAC W1 Switch", "DAC W1" },
	{ "WOUT MIX", "DAC W1 Switch", "DAC W1" },
	{ "WOUT MIX", "OUTMIX W Switch", "OUT MIXW" },
	{ "WOUT MIX", "OUTMIX W Switch", "OUT MIXW" },

	{ "PDM1 W Mux", "Steweo DAC", "Steweo DAC MIXW" },
	{ "PDM1 W Mux", "Mono DAC", "Mono DAC MIXW" },
	{ "PDM1 W Mux", NUWW, "PDM1 Powew" },
	{ "PDM1 W Mux", "Steweo DAC", "Steweo DAC MIXW" },
	{ "PDM1 W Mux", "Mono DAC", "Mono DAC MIXW" },
	{ "PDM1 W Mux", NUWW, "PDM1 Powew" },

	{ "HP amp", NUWW, "HPO MIX" },
	{ "HP amp", NUWW, "JD Powew" },
	{ "HP amp", NUWW, "Mic Det Powew" },
	{ "HP amp", NUWW, "WDO2" },
	{ "HPOW", NUWW, "HP amp" },
	{ "HPOW", NUWW, "HP amp" },

	{ "WOUT amp", NUWW, "WOUT MIX" },
	{ "WOUTW", NUWW, "WOUT amp" },
	{ "WOUTW", NUWW, "WOUT amp" },

	{ "PDM1 W", "Switch", "PDM1 W Mux" },
	{ "PDM1 W", "Switch", "PDM1 W Mux" },

	{ "PDM1W", NUWW, "PDM1 W" },
	{ "PDM1W", NUWW, "PDM1 W" },

	{ "SPK amp", NUWW, "SPOW MIX" },
	{ "SPK amp", NUWW, "SPOW MIX" },
	{ "SPOW", NUWW, "SPK amp" },
	{ "SPOW", NUWW, "SPK amp" },
};

static const stwuct snd_soc_dapm_woute wt5650_specific_dapm_woutes[] = {
	{ "A DAC1 W Mux", "DAC1",  "DAC1 MIXW"},
	{ "A DAC1 W Mux", "Steweo DAC Mixew", "Steweo DAC MIXW"},
	{ "A DAC1 W Mux", "DAC1",  "DAC1 MIXW"},
	{ "A DAC1 W Mux", "Steweo DAC Mixew", "Steweo DAC MIXW"},

	{ "A DAC2 W Mux", "Steweo DAC Mixew", "Steweo DAC MIXW"},
	{ "A DAC2 W Mux", "Mono DAC Mixew", "Mono DAC MIXW"},
	{ "A DAC2 W Mux", "Steweo DAC Mixew", "Steweo DAC MIXW"},
	{ "A DAC2 W Mux", "Mono DAC Mixew", "Mono DAC MIXW"},

	{ "DAC W1", NUWW, "A DAC1 W Mux" },
	{ "DAC W1", NUWW, "A DAC1 W Mux" },
	{ "DAC W2", NUWW, "A DAC2 W Mux" },
	{ "DAC W2", NUWW, "A DAC2 W Mux" },

	{ "WT5650 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5650 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5650 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5650 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },

	{ "WT5650 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5650 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5650 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5650 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },

	{ "WT5650 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5650 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5650 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5650 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },

	{ "IF1 ADC", NUWW, "WT5650 IF1 ADC1 Swap Mux" },
	{ "IF1 ADC", NUWW, "WT5650 IF1 ADC2 Swap Mux" },
	{ "IF1 ADC", NUWW, "WT5650 IF1 ADC3 Swap Mux" },

	{ "WT5650 IF1 ADC Mux", "IF_ADC1/IF_ADC2/DAC_WEF/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC1/IF_ADC2/Nuww/DAC_WEF", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC1/DAC_WEF/IF_ADC2/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC1/DAC_WEF/Nuww/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC1/Nuww/DAC_WEF/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC1/Nuww/IF_ADC2/DAC_WEF", "IF1 ADC" },

	{ "WT5650 IF1 ADC Mux", "IF_ADC2/IF_ADC1/DAC_WEF/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC2/IF_ADC1/Nuww/DAC_WEF", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC2/DAC_WEF/IF_ADC1/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC2/DAC_WEF/Nuww/IF_ADC1", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC2/Nuww/DAC_WEF/IF_ADC1", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "IF_ADC2/Nuww/IF_ADC1/DAC_WEF", "IF1 ADC" },

	{ "WT5650 IF1 ADC Mux", "DAC_WEF/IF_ADC1/IF_ADC2/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "DAC_WEF/IF_ADC1/Nuww/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "DAC_WEF/IF_ADC2/IF_ADC1/Nuww", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "DAC_WEF/IF_ADC2/Nuww/IF_ADC1", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "DAC_WEF/Nuww/IF_ADC1/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "DAC_WEF/Nuww/IF_ADC2/IF_ADC1", "IF1 ADC" },

	{ "WT5650 IF1 ADC Mux", "Nuww/IF_ADC1/IF_ADC2/DAC_WEF", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "Nuww/IF_ADC1/DAC_WEF/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "Nuww/IF_ADC2/IF_ADC1/DAC_WEF", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "Nuww/IF_ADC2/DAC_WEF/IF_ADC1", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "Nuww/DAC_WEF/IF_ADC1/IF_ADC2", "IF1 ADC" },
	{ "WT5650 IF1 ADC Mux", "Nuww/DAC_WEF/IF_ADC2/IF_ADC1", "IF1 ADC" },
	{ "AIF1TX", NUWW, "WT5650 IF1 ADC Mux" },

	{ "WT5650 IF1 DAC1 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5650 IF1 DAC1 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5650 IF1 DAC1 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5650 IF1 DAC2 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5650 IF1 DAC2 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5650 IF1 DAC2 W Mux", "Swot3", "IF1 DAC3" },

	{ "DAC1 W Mux", "IF1 DAC", "WT5650 IF1 DAC1 W Mux" },
	{ "DAC1 W Mux", "IF1 DAC", "WT5650 IF1 DAC1 W Mux" },

	{ "DAC W2 Mux", "IF1 DAC", "WT5650 IF1 DAC2 W Mux" },
	{ "DAC W2 Mux", "IF1 DAC", "WT5650 IF1 DAC2 W Mux" },
};

static const stwuct snd_soc_dapm_woute wt5645_specific_dapm_woutes[] = {
	{ "DAC W1", NUWW, "Steweo DAC MIXW" },
	{ "DAC W1", NUWW, "Steweo DAC MIXW" },
	{ "DAC W2", NUWW, "Mono DAC MIXW" },
	{ "DAC W2", NUWW, "Mono DAC MIXW" },

	{ "WT5645 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5645 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5645 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },
	{ "WT5645 IF1 ADC1 Swap Mux", "W/W", "IF_ADC1" },

	{ "WT5645 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5645 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5645 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },
	{ "WT5645 IF1 ADC2 Swap Mux", "W/W", "IF_ADC2" },

	{ "WT5645 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5645 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5645 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },
	{ "WT5645 IF1 ADC3 Swap Mux", "W/W", "VAD_ADC" },

	{ "IF1 ADC", NUWW, "WT5645 IF1 ADC1 Swap Mux" },
	{ "IF1 ADC", NUWW, "WT5645 IF1 ADC2 Swap Mux" },
	{ "IF1 ADC", NUWW, "WT5645 IF1 ADC3 Swap Mux" },

	{ "WT5645 IF1 ADC Mux", "IF_ADC1/IF_ADC2/VAD_ADC", "IF1 ADC" },
	{ "WT5645 IF1 ADC Mux", "IF_ADC2/IF_ADC1/VAD_ADC", "IF1 ADC" },
	{ "WT5645 IF1 ADC Mux", "VAD_ADC/IF_ADC1/IF_ADC2", "IF1 ADC" },
	{ "WT5645 IF1 ADC Mux", "VAD_ADC/IF_ADC2/IF_ADC1", "IF1 ADC" },
	{ "AIF1TX", NUWW, "WT5645 IF1 ADC Mux" },

	{ "WT5645 IF1 DAC1 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5645 IF1 DAC1 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5645 IF1 DAC1 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5645 IF1 DAC2 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot3", "IF1 DAC3" },

	{ "WT5645 IF1 DAC2 W Mux", "Swot0", "IF1 DAC0" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot1", "IF1 DAC1" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot2", "IF1 DAC2" },
	{ "WT5645 IF1 DAC2 W Mux", "Swot3", "IF1 DAC3" },

	{ "DAC1 W Mux", "IF1 DAC", "WT5645 IF1 DAC1 W Mux" },
	{ "DAC1 W Mux", "IF1 DAC", "WT5645 IF1 DAC1 W Mux" },

	{ "DAC W2 Mux", "IF1 DAC", "WT5645 IF1 DAC2 W Mux" },
	{ "DAC W2 Mux", "IF1 DAC", "WT5645 IF1 DAC2 W Mux" },
};

static const stwuct snd_soc_dapm_woute wt5645_owd_dapm_woutes[] = {
	{ "SPOW MIX", "DAC W1 Switch", "DAC W1" },
	{ "SPOW MIX", "SPKVOW W Switch", "SPKVOW W" },
};

static int wt5645_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0, vaw_cwk, mask_cwk, dw_sft;
	int pwe_div, bcwk_ms, fwame_size;

	wt5645->wwck[dai->id] = pawams_wate(pawams);
	pwe_div = ww6231_get_cwk_info(wt5645->syscwk, wt5645->wwck[dai->id]);
	if (pwe_div < 0) {
		dev_eww(component->dev, "Unsuppowted cwock setting\n");
		wetuwn -EINVAW;
	}
	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0) {
		dev_eww(component->dev, "Unsuppowted fwame size: %d\n", fwame_size);
		wetuwn -EINVAW;
	}

	switch (wt5645->codec_type) {
	case CODEC_TYPE_WT5650:
		dw_sft = 4;
		bweak;
	defauwt:
		dw_sft = 2;
		bweak;
	}

	bcwk_ms = fwame_size > 32;
	wt5645->bcwk[dai->id] = wt5645->wwck[dai->id] * (32 << bcwk_ms);

	dev_dbg(dai->dev, "bcwk is %dHz and wwck is %dHz\n",
		wt5645->bcwk[dai->id], wt5645->wwck[dai->id]);
	dev_dbg(dai->dev, "bcwk_ms is %d and pwe_div is %d fow iis %d\n",
				bcwk_ms, pwe_div, dai->id);

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		vaw_wen = 0x1;
		bweak;
	case 24:
		vaw_wen = 0x2;
		bweak;
	case 8:
		vaw_wen = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case WT5645_AIF1:
		mask_cwk = WT5645_I2S_PD1_MASK;
		vaw_cwk = pwe_div << WT5645_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, WT5645_I2S1_SDP,
			(0x3 << dw_sft), (vaw_wen << dw_sft));
		snd_soc_component_update_bits(component, WT5645_ADDA_CWK1, mask_cwk, vaw_cwk);
		bweak;
	case  WT5645_AIF2:
		mask_cwk = WT5645_I2S_BCWK_MS2_MASK | WT5645_I2S_PD2_MASK;
		vaw_cwk = bcwk_ms << WT5645_I2S_BCWK_MS2_SFT |
			pwe_div << WT5645_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, WT5645_I2S2_SDP,
			(0x3 << dw_sft), (vaw_wen << dw_sft));
		snd_soc_component_update_bits(component, WT5645_ADDA_CWK1, mask_cwk, vaw_cwk);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt5645_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0, pow_sft;

	switch (wt5645->codec_type) {
	case CODEC_TYPE_WT5650:
		pow_sft = 8;
		bweak;
	defauwt:
		pow_sft = 7;
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		wt5645->mastew[dai->id] = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		weg_vaw |= WT5645_I2S_MS_S;
		wt5645->mastew[dai->id] = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg_vaw |= (1 << pow_sft);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT5645_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT5645_I2S_DF_PCM_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT5645_I2S_DF_PCM_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	switch (dai->id) {
	case WT5645_AIF1:
		snd_soc_component_update_bits(component, WT5645_I2S1_SDP,
			WT5645_I2S_MS_MASK | (1 << pow_sft) |
			WT5645_I2S_DF_MASK, weg_vaw);
		bweak;
	case WT5645_AIF2:
		snd_soc_component_update_bits(component, WT5645_I2S2_SDP,
			WT5645_I2S_MS_MASK | (1 << pow_sft) |
			WT5645_I2S_DF_MASK, weg_vaw);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid dai->id: %d\n", dai->id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wt5645_set_dai_syscwk(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	if (fweq == wt5645->syscwk && cwk_id == wt5645->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT5645_SCWK_S_MCWK:
		weg_vaw |= WT5645_SCWK_SWC_MCWK;
		bweak;
	case WT5645_SCWK_S_PWW1:
		weg_vaw |= WT5645_SCWK_SWC_PWW1;
		bweak;
	case WT5645_SCWK_S_WCCWK:
		weg_vaw |= WT5645_SCWK_SWC_WCCWK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, WT5645_GWB_CWK,
		WT5645_SCWK_SWC_MASK, weg_vaw);
	wt5645->syscwk = fweq;
	wt5645->syscwk_swc = cwk_id;

	dev_dbg(dai->dev, "Syscwk is %dHz and cwock id is %d\n", fweq, cwk_id);

	wetuwn 0;
}

static int wt5645_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;

	if (souwce == wt5645->pww_swc && fweq_in == wt5645->pww_in &&
	    fweq_out == wt5645->pww_out)
		wetuwn 0;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt5645->pww_in = 0;
		wt5645->pww_out = 0;
		snd_soc_component_update_bits(component, WT5645_GWB_CWK,
			WT5645_SCWK_SWC_MASK, WT5645_SCWK_SWC_MCWK);
		wetuwn 0;
	}

	switch (souwce) {
	case WT5645_PWW1_S_MCWK:
		snd_soc_component_update_bits(component, WT5645_GWB_CWK,
			WT5645_PWW1_SWC_MASK, WT5645_PWW1_SWC_MCWK);
		bweak;
	case WT5645_PWW1_S_BCWK1:
	case WT5645_PWW1_S_BCWK2:
		switch (dai->id) {
		case WT5645_AIF1:
			snd_soc_component_update_bits(component, WT5645_GWB_CWK,
				WT5645_PWW1_SWC_MASK, WT5645_PWW1_SWC_BCWK1);
			bweak;
		case  WT5645_AIF2:
			snd_soc_component_update_bits(component, WT5645_GWB_CWK,
				WT5645_PWW1_SWC_MASK, WT5645_PWW1_SWC_BCWK2);
			bweak;
		defauwt:
			dev_eww(component->dev, "Invawid dai->id: %d\n", dai->id);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown PWW souwce %d\n", souwce);
		wetuwn -EINVAW;
	}

	wet = ww6231_pww_cawc(fweq_in, fweq_out, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pww_code.m_bp, (pww_code.m_bp ? 0 : pww_code.m_code),
		pww_code.n_code, pww_code.k_code);

	snd_soc_component_wwite(component, WT5645_PWW_CTWW1,
		pww_code.n_code << WT5645_PWW_N_SFT | pww_code.k_code);
	snd_soc_component_wwite(component, WT5645_PWW_CTWW2,
		((pww_code.m_bp ? 0 : pww_code.m_code) << WT5645_PWW_M_SFT) |
		(pww_code.m_bp << WT5645_PWW_M_BP_SFT));

	wt5645->pww_in = fweq_in;
	wt5645->pww_out = fweq_out;
	wt5645->pww_swc = souwce;

	wetuwn 0;
}

static int wt5645_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	unsigned int i_swot_sft, o_swot_sft, i_width_sht, o_width_sht, en_sft;
	unsigned int mask, vaw = 0;

	switch (wt5645->codec_type) {
	case CODEC_TYPE_WT5650:
		en_sft = 15;
		i_swot_sft = 10;
		o_swot_sft = 8;
		i_width_sht = 6;
		o_width_sht = 4;
		mask = 0x8ff0;
		bweak;
	defauwt:
		en_sft = 14;
		i_swot_sft = o_swot_sft = 12;
		i_width_sht = o_width_sht = 10;
		mask = 0x7c00;
		bweak;
	}
	if (wx_mask || tx_mask) {
		vaw |= (1 << en_sft);
		if (wt5645->codec_type == CODEC_TYPE_WT5645)
			snd_soc_component_update_bits(component, WT5645_BASS_BACK,
				WT5645_G_BB_BST_MASK, WT5645_G_BB_BST_25DB);
	}

	switch (swots) {
	case 4:
		vaw |= (1 << i_swot_sft) | (1 << o_swot_sft);
		bweak;
	case 6:
		vaw |= (2 << i_swot_sft) | (2 << o_swot_sft);
		bweak;
	case 8:
		vaw |= (3 << i_swot_sft) | (3 << o_swot_sft);
		bweak;
	case 2:
	defauwt:
		bweak;
	}

	switch (swot_width) {
	case 20:
		vaw |= (1 << i_width_sht) | (1 << o_width_sht);
		bweak;
	case 24:
		vaw |= (2 << i_width_sht) | (2 << o_width_sht);
		bweak;
	case 32:
		vaw |= (3 << i_width_sht) | (3 << o_width_sht);
		bweak;
	case 16:
	defauwt:
		bweak;
	}

	snd_soc_component_update_bits(component, WT5645_TDM_CTWW_1, mask, vaw);

	wetuwn 0;
}

static int wt5645_set_bias_wevew(stwuct snd_soc_component *component,
			enum snd_soc_bias_wevew wevew)
{
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_wevew(component)) {
			snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
				WT5645_PWW_VWEF1 | WT5645_PWW_MB |
				WT5645_PWW_BG | WT5645_PWW_VWEF2,
				WT5645_PWW_VWEF1 | WT5645_PWW_MB |
				WT5645_PWW_BG | WT5645_PWW_VWEF2);
			mdeway(10);
			snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
				WT5645_PWW_FV1 | WT5645_PWW_FV2,
				WT5645_PWW_FV1 | WT5645_PWW_FV2);
			snd_soc_component_update_bits(component, WT5645_GEN_CTWW1,
				WT5645_DIG_GATE_CTWW, WT5645_DIG_GATE_CTWW);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
			WT5645_PWW_VWEF1 | WT5645_PWW_MB |
			WT5645_PWW_BG | WT5645_PWW_VWEF2,
			WT5645_PWW_VWEF1 | WT5645_PWW_MB |
			WT5645_PWW_BG | WT5645_PWW_VWEF2);
		mdeway(10);
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
			WT5645_PWW_FV1 | WT5645_PWW_FV2,
			WT5645_PWW_FV1 | WT5645_PWW_FV2);
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_wwite(component, WT5645_DEPOP_M2, 0x1140);
			msweep(40);
			if (wt5645->en_button_func)
				queue_dewayed_wowk(system_powew_efficient_wq,
					&wt5645->jack_detect_wowk,
					msecs_to_jiffies(0));
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WT5645_DEPOP_M2, 0x1100);
		if (!wt5645->en_button_func)
			snd_soc_component_update_bits(component, WT5645_GEN_CTWW1,
					WT5645_DIG_GATE_CTWW, 0);
		snd_soc_component_update_bits(component, WT5645_PWW_ANWG1,
				WT5645_PWW_VWEF1 | WT5645_PWW_MB |
				WT5645_PWW_BG | WT5645_PWW_VWEF2 |
				WT5645_PWW_FV1 | WT5645_PWW_FV2, 0x0);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void wt5645_enabwe_push_button_iwq(stwuct snd_soc_component *component,
	boow enabwe)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (enabwe) {
		snd_soc_dapm_fowce_enabwe_pin(dapm, "ADC W powew");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "ADC W powew");
		snd_soc_dapm_sync(dapm);

		snd_soc_component_update_bits(component, WT5650_4BTN_IW_CMD1, 0x3, 0x3);
		snd_soc_component_update_bits(component,
					WT5645_INT_IWQ_ST, 0x8, 0x8);
		snd_soc_component_update_bits(component,
					WT5650_4BTN_IW_CMD2, 0x8000, 0x8000);
		snd_soc_component_wead(component, WT5650_4BTN_IW_CMD1);
		pw_debug("%s wead %x = %x\n", __func__, WT5650_4BTN_IW_CMD1,
			snd_soc_component_wead(component, WT5650_4BTN_IW_CMD1));
	} ewse {
		snd_soc_component_update_bits(component, WT5650_4BTN_IW_CMD2, 0x8000, 0x0);
		snd_soc_component_update_bits(component, WT5645_INT_IWQ_ST, 0x8, 0x0);

		snd_soc_dapm_disabwe_pin(dapm, "ADC W powew");
		snd_soc_dapm_disabwe_pin(dapm, "ADC W powew");
		snd_soc_dapm_sync(dapm);
	}
}

static int wt5645_jack_detect(stwuct snd_soc_component *component, int jack_insewt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	if (jack_insewt) {
		wegmap_wwite(wt5645->wegmap, WT5645_CHAWGE_PUMP, 0x0206);

		/* fow jack type detect */
		snd_soc_dapm_fowce_enabwe_pin(dapm, "WDO2");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "Mic Det Powew");
		snd_soc_dapm_sync(dapm);
		if (!snd_soc_cawd_is_instantiated(dapm->cawd)) {
			/* Powew up necessawy bits fow JD if dapm is
			   not weady yet */
			wegmap_update_bits(wt5645->wegmap, WT5645_PWW_ANWG1,
				WT5645_PWW_MB | WT5645_PWW_VWEF2,
				WT5645_PWW_MB | WT5645_PWW_VWEF2);
			wegmap_update_bits(wt5645->wegmap, WT5645_PWW_MIXEW,
				WT5645_PWW_WDO2, WT5645_PWW_WDO2);
			wegmap_update_bits(wt5645->wegmap, WT5645_PWW_VOW,
				WT5645_PWW_MIC_DET, WT5645_PWW_MIC_DET);
		}

		wegmap_wwite(wt5645->wegmap, WT5645_JD_CTWW3, 0x00f0);
		wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW2,
			WT5645_CBJ_MN_JD, WT5645_CBJ_MN_JD);
		wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW1,
			WT5645_CBJ_BST1_EN, WT5645_CBJ_BST1_EN);
		msweep(100);
		wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW2,
			WT5645_CBJ_MN_JD, 0);

		msweep(600);
		wegmap_wead(wt5645->wegmap, WT5645_IN1_CTWW3, &vaw);
		vaw &= 0x7;
		dev_dbg(component->dev, "vaw = %d\n", vaw);

		if ((vaw == 1 || vaw == 2) && !wt5645->pdata.no_headset_mic) {
			wt5645->jack_type = SND_JACK_HEADSET;
			if (wt5645->en_button_func) {
				wt5645_enabwe_push_button_iwq(component, twue);
			}
		} ewse {
			if (wt5645->en_button_func)
				wt5645_enabwe_push_button_iwq(component, fawse);
			snd_soc_dapm_disabwe_pin(dapm, "Mic Det Powew");
			snd_soc_dapm_sync(dapm);
			wt5645->jack_type = SND_JACK_HEADPHONE;
		}
		if (wt5645->pdata.wevew_twiggew_iwq)
			wegmap_update_bits(wt5645->wegmap, WT5645_IWQ_CTWW2,
				WT5645_JD_1_1_MASK, WT5645_JD_1_1_NOW);

		wegmap_wwite(wt5645->wegmap, WT5645_CHAWGE_PUMP, 0x0e06);
	} ewse { /* jack out */
		wt5645->jack_type = 0;

		wegmap_update_bits(wt5645->wegmap, WT5645_HP_VOW,
			WT5645_W_MUTE | WT5645_W_MUTE,
			WT5645_W_MUTE | WT5645_W_MUTE);
		wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW2,
			WT5645_CBJ_MN_JD, WT5645_CBJ_MN_JD);
		wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW1,
			WT5645_CBJ_BST1_EN, 0);

		if (wt5645->en_button_func)
			wt5645_enabwe_push_button_iwq(component, fawse);

		if (wt5645->pdata.jd_mode == 0)
			snd_soc_dapm_disabwe_pin(dapm, "WDO2");
		snd_soc_dapm_disabwe_pin(dapm, "Mic Det Powew");
		snd_soc_dapm_sync(dapm);
		if (wt5645->pdata.wevew_twiggew_iwq)
			wegmap_update_bits(wt5645->wegmap, WT5645_IWQ_CTWW2,
				WT5645_JD_1_1_MASK, WT5645_JD_1_1_INV);
	}

	wetuwn wt5645->jack_type;
}

static int wt5645_button_detect(stwuct snd_soc_component *component)
{
	int btn_type, vaw;

	vaw = snd_soc_component_wead(component, WT5650_4BTN_IW_CMD1);
	pw_debug("vaw=0x%x\n", vaw);
	btn_type = vaw & 0xfff0;
	snd_soc_component_wwite(component, WT5650_4BTN_IW_CMD1, vaw);

	wetuwn btn_type;
}

static iwqwetuwn_t wt5645_iwq(int iwq, void *data);

int wt5645_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hp_jack, stwuct snd_soc_jack *mic_jack,
	stwuct snd_soc_jack *btn_jack)
{
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	wt5645->hp_jack = hp_jack;
	wt5645->mic_jack = mic_jack;
	wt5645->btn_jack = btn_jack;
	if (wt5645->btn_jack && wt5645->codec_type == CODEC_TYPE_WT5650) {
		wt5645->en_button_func = twue;
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
				WT5645_GP1_PIN_IWQ, WT5645_GP1_PIN_IWQ);
		wegmap_update_bits(wt5645->wegmap, WT5645_GEN_CTWW1,
				WT5645_DIG_GATE_CTWW, WT5645_DIG_GATE_CTWW);
		wegmap_update_bits(wt5645->wegmap, WT5645_DEPOP_M1,
				WT5645_HP_CB_MASK, WT5645_HP_CB_PU);
	}
	wt5645_iwq(0, wt5645);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt5645_set_jack_detect);

static int wt5645_component_set_jack(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct snd_soc_jack *mic_jack = NUWW;
	stwuct snd_soc_jack *btn_jack = NUWW;
	int type;

	if (hs_jack) {
		type = *(int *)data;

		if (type & SND_JACK_MICWOPHONE)
			mic_jack = hs_jack;
		if (type & (SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3))
			btn_jack = hs_jack;
	}

	wetuwn wt5645_set_jack_detect(component, hs_jack, mic_jack, btn_jack);
}

static void wt5645_jack_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5645_pwiv *wt5645 =
		containew_of(wowk, stwuct wt5645_pwiv, jack_detect_wowk.wowk);
	int vaw, btn_type, gpio_state = 0, wepowt = 0;

	if (!wt5645->component)
		wetuwn;

	mutex_wock(&wt5645->jd_mutex);

	switch (wt5645->pdata.jd_mode) {
	case 0: /* Not using wt5645 JD */
		if (wt5645->gpiod_hp_det) {
			gpio_state = gpiod_get_vawue(wt5645->gpiod_hp_det);
			if (wt5645->pdata.inv_hp_pow)
				gpio_state ^= 1;
			dev_dbg(wt5645->component->dev, "gpio_state = %d\n",
				gpio_state);
			wepowt = wt5645_jack_detect(wt5645->component, gpio_state);
		}
		snd_soc_jack_wepowt(wt5645->hp_jack,
				    wepowt, SND_JACK_HEADPHONE);
		snd_soc_jack_wepowt(wt5645->mic_jack,
				    wepowt, SND_JACK_MICWOPHONE);
		wetuwn;
	case 4:
		vaw = snd_soc_component_wead(wt5645->component, WT5645_A_JD_CTWW1) & 0x0020;
		bweak;
	defauwt: /* wead wt5645 jd1_1 status */
		vaw = snd_soc_component_wead(wt5645->component, WT5645_INT_IWQ_ST) & 0x1000;
		bweak;

	}

	if (!vaw && (wt5645->jack_type == 0)) { /* jack in */
		wepowt = wt5645_jack_detect(wt5645->component, 1);
	} ewse if (!vaw && wt5645->jack_type == SND_JACK_HEADSET) {
		/* fow push button and jack out */
		btn_type = 0;
		if (snd_soc_component_wead(wt5645->component, WT5645_INT_IWQ_ST) & 0x4) {
			/* button pwessed */
			wepowt = SND_JACK_HEADSET;
			btn_type = wt5645_button_detect(wt5645->component);
			/* wt5650 can wepowt thwee kinds of button behaviow,
			   one cwick, doubwe cwick and howd. Howevew,
			   cuwwentwy we wiww wepowt button pwessed/weweased
			   event. So aww the thwee button behaviows awe
			   tweated as button pwessed. */
			switch (btn_type) {
			case 0x8000:
			case 0x4000:
			case 0x2000:
				wepowt |= SND_JACK_BTN_0;
				bweak;
			case 0x1000:
			case 0x0800:
			case 0x0400:
				wepowt |= SND_JACK_BTN_1;
				bweak;
			case 0x0200:
			case 0x0100:
			case 0x0080:
				wepowt |= SND_JACK_BTN_2;
				bweak;
			case 0x0040:
			case 0x0020:
			case 0x0010:
				wepowt |= SND_JACK_BTN_3;
				bweak;
			case 0x0000: /* unpwessed */
				bweak;
			defauwt:
				dev_eww(wt5645->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				bweak;
			}
		}
		if (btn_type == 0)/* button wewease */
			wepowt =  wt5645->jack_type;
		ewse {
			mod_timew(&wt5645->btn_check_timew,
				msecs_to_jiffies(100));
		}
	} ewse {
		/* jack out */
		wepowt = 0;
		snd_soc_component_update_bits(wt5645->component,
				    WT5645_INT_IWQ_ST, 0x1, 0x0);
		wt5645_jack_detect(wt5645->component, 0);
	}

	mutex_unwock(&wt5645->jd_mutex);

	snd_soc_jack_wepowt(wt5645->hp_jack, wepowt, SND_JACK_HEADPHONE);
	snd_soc_jack_wepowt(wt5645->mic_jack, wepowt, SND_JACK_MICWOPHONE);
	if (wt5645->en_button_func)
		snd_soc_jack_wepowt(wt5645->btn_jack,
			wepowt, SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3);
}

static void wt5645_wccwock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5645_pwiv *wt5645 =
		containew_of(wowk, stwuct wt5645_pwiv, wccwock_wowk.wowk);

	wegmap_update_bits(wt5645->wegmap, WT5645_MICBIAS,
		WT5645_PWW_CWK25M_MASK, WT5645_PWW_CWK25M_PD);
}

static iwqwetuwn_t wt5645_iwq(int iwq, void *data)
{
	stwuct wt5645_pwiv *wt5645 = data;

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &wt5645->jack_detect_wowk, msecs_to_jiffies(250));

	wetuwn IWQ_HANDWED;
}

static void wt5645_btn_check_cawwback(stwuct timew_wist *t)
{
	stwuct wt5645_pwiv *wt5645 = fwom_timew(wt5645, t, btn_check_timew);

	queue_dewayed_wowk(system_powew_efficient_wq,
		   &wt5645->jack_detect_wowk, msecs_to_jiffies(5));
}

static int wt5645_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	wt5645->component = component;

	switch (wt5645->codec_type) {
	case CODEC_TYPE_WT5645:
		snd_soc_dapm_new_contwows(dapm,
			wt5645_specific_dapm_widgets,
			AWWAY_SIZE(wt5645_specific_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm,
			wt5645_specific_dapm_woutes,
			AWWAY_SIZE(wt5645_specific_dapm_woutes));
		if (wt5645->v_id < 3) {
			snd_soc_dapm_add_woutes(dapm,
				wt5645_owd_dapm_woutes,
				AWWAY_SIZE(wt5645_owd_dapm_woutes));
		}
		bweak;
	case CODEC_TYPE_WT5650:
		snd_soc_dapm_new_contwows(dapm,
			wt5650_specific_dapm_widgets,
			AWWAY_SIZE(wt5650_specific_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm,
			wt5650_specific_dapm_woutes,
			AWWAY_SIZE(wt5650_specific_dapm_woutes));
		bweak;
	}

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_OFF);

	/* fow JD function */
	if (wt5645->pdata.jd_mode) {
		snd_soc_dapm_fowce_enabwe_pin(dapm, "JD Powew");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "WDO2");
		snd_soc_dapm_sync(dapm);
	}

	if (wt5645->pdata.wong_name)
		component->cawd->wong_name = wt5645->pdata.wong_name;

	wt5645->eq_pawam = devm_kcawwoc(component->dev,
		WT5645_HWEQ_NUM, sizeof(stwuct wt5645_eq_pawam_s),
		GFP_KEWNEW);

	if (!wt5645->eq_pawam)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wt5645_wemove(stwuct snd_soc_component *component)
{
	wt5645_weset(component);
}

#ifdef CONFIG_PM
static int wt5645_suspend(stwuct snd_soc_component *component)
{
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt5645->wegmap, twue);
	wegcache_mawk_diwty(wt5645->wegmap);

	wetuwn 0;
}

static int wt5645_wesume(stwuct snd_soc_component *component)
{
	stwuct wt5645_pwiv *wt5645 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt5645->wegmap, fawse);
	wegcache_sync(wt5645->wegmap);

	wetuwn 0;
}
#ewse
#define wt5645_suspend NUWW
#define wt5645_wesume NUWW
#endif

#define WT5645_STEWEO_WATES SNDWV_PCM_WATE_8000_96000
#define WT5645_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt5645_aif_dai_ops = {
	.hw_pawams = wt5645_hw_pawams,
	.set_fmt = wt5645_set_dai_fmt,
	.set_syscwk = wt5645_set_dai_syscwk,
	.set_tdm_swot = wt5645_set_tdm_swot,
	.set_pww = wt5645_set_dai_pww,
};

static stwuct snd_soc_dai_dwivew wt5645_dai[] = {
	{
		.name = "wt5645-aif1",
		.id = WT5645_AIF1,
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5645_STEWEO_WATES,
			.fowmats = WT5645_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates = WT5645_STEWEO_WATES,
			.fowmats = WT5645_FOWMATS,
		},
		.ops = &wt5645_aif_dai_ops,
	},
	{
		.name = "wt5645-aif2",
		.id = WT5645_AIF2,
		.pwayback = {
			.stweam_name = "AIF2 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5645_STEWEO_WATES,
			.fowmats = WT5645_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5645_STEWEO_WATES,
			.fowmats = WT5645_FOWMATS,
		},
		.ops = &wt5645_aif_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt5645 = {
	.pwobe			= wt5645_pwobe,
	.wemove			= wt5645_wemove,
	.suspend		= wt5645_suspend,
	.wesume			= wt5645_wesume,
	.set_bias_wevew		= wt5645_set_bias_wevew,
	.contwows		= wt5645_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt5645_snd_contwows),
	.dapm_widgets		= wt5645_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt5645_dapm_widgets),
	.dapm_woutes		= wt5645_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt5645_dapm_woutes),
	.set_jack		= wt5645_component_set_jack,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt5645_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = WT5645_VENDOW_ID2 + 1 + (AWWAY_SIZE(wt5645_wanges) *
					       WT5645_PW_SPACING),
	.vowatiwe_weg = wt5645_vowatiwe_wegistew,
	.weadabwe_weg = wt5645_weadabwe_wegistew,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5645_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5645_weg),
	.wanges = wt5645_wanges,
	.num_wanges = AWWAY_SIZE(wt5645_wanges),
};

static const stwuct wegmap_config wt5650_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = WT5645_VENDOW_ID2 + 1 + (AWWAY_SIZE(wt5645_wanges) *
					       WT5645_PW_SPACING),
	.vowatiwe_weg = wt5645_vowatiwe_wegistew,
	.weadabwe_weg = wt5645_weadabwe_wegistew,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5650_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5650_weg),
	.wanges = wt5645_wanges,
	.num_wanges = AWWAY_SIZE(wt5645_wanges),
};

static const stwuct wegmap_config temp_wegmap = {
	.name="nocache",
	.weg_bits = 8,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = WT5645_VENDOW_ID2 + 1,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct i2c_device_id wt5645_i2c_id[] = {
	{ "wt5645", 0 },
	{ "wt5650", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt5645_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id wt5645_of_match[] = {
	{ .compatibwe = "weawtek,wt5645", },
	{ .compatibwe = "weawtek,wt5650", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wt5645_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt5645_acpi_match[] = {
	{ "10EC5645", 0 },
	{ "10EC5648", 0 },
	{ "10EC5650", 0 },
	{ "10EC5640", 0 },
	{ "10EC3270", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt5645_acpi_match);
#endif

static const stwuct wt5645_pwatfowm_data intew_bwasweww_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC1_DISABWE,
	.dmic2_data_pin = WT5645_DMIC_DATA_IN2P,
	.jd_mode = 3,
};

static const stwuct wt5645_pwatfowm_data buddy_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC_DATA_GPIO5,
	.dmic2_data_pin = WT5645_DMIC_DATA_IN2P,
	.jd_mode = 4,
	.wevew_twiggew_iwq = twue,
};

static const stwuct wt5645_pwatfowm_data gpd_win_pwatfowm_data = {
	.jd_mode = 3,
	.inv_jd1_1 = twue,
	.mono_speakew = twue,
	.wong_name = "gpd-win-pocket-wt5645",
	/* The GPD pocket has a diff. mic, fow the win this does not mattew. */
	.in2_diff = twue,
};

static const stwuct wt5645_pwatfowm_data asus_t100ha_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC_DATA_IN2N,
	.dmic2_data_pin = WT5645_DMIC2_DISABWE,
	.jd_mode = 3,
	.inv_jd1_1 = twue,
};

static const stwuct wt5645_pwatfowm_data asus_t101ha_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC_DATA_IN2N,
	.dmic2_data_pin = WT5645_DMIC2_DISABWE,
	.jd_mode = 3,
};

static const stwuct wt5645_pwatfowm_data wenovo_ideapad_miix_310_pdata = {
	.jd_mode = 3,
	.in2_diff = twue,
};

static const stwuct wt5645_pwatfowm_data jd_mode3_monospk_pwatfowm_data = {
	.jd_mode = 3,
	.mono_speakew = twue,
};

static const stwuct wt5645_pwatfowm_data jd_mode3_pwatfowm_data = {
	.jd_mode = 3,
};

static const stwuct wt5645_pwatfowm_data wattepanda_boawd_pwatfowm_data = {
	.jd_mode = 2,
	.inv_jd1_1 = twue
};

static const stwuct wt5645_pwatfowm_data kahwee_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC_DATA_GPIO5,
	.dmic2_data_pin = WT5645_DMIC_DATA_IN2P,
	.jd_mode = 3,
};

static const stwuct wt5645_pwatfowm_data ecs_ef20_pwatfowm_data = {
	.dmic1_data_pin = WT5645_DMIC1_DISABWE,
	.dmic2_data_pin = WT5645_DMIC_DATA_IN2P,
	.inv_hp_pow = 1,
};

static const stwuct acpi_gpio_pawams ef20_hp_detect = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping cht_wt5645_ef20_gpios[] = {
	{ "hp-detect-gpios", &ef20_hp_detect, 1 },
	{ },
};

static int cht_wt5645_ef20_quiwk_cb(const stwuct dmi_system_id *id)
{
	cht_wt5645_gpios = cht_wt5645_ef20_gpios;
	wetuwn 1;
}

static const stwuct dmi_system_id dmi_pwatfowm_data[] = {
	{
		.ident = "Chwome Buddy",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Buddy"),
		},
		.dwivew_data = (void *)&buddy_pwatfowm_data,
	},
	{
		.ident = "Intew Stwago",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Stwago"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		.ident = "Googwe Chwome",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		.ident = "Googwe Setzew",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Setzew"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		.ident = "Micwosoft Suwface 3",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface 3"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		/*
		 * Match fow the GPDwin which unfowtunatewy uses somewhat
		 * genewic dmi stwings, which is why we test fow 4 stwings.
		 * Compawing against 23 othew byt/cht boawds, boawd_vendow
		 * and boawd_name awe unique to the GPDwin, whewe as onwy one
		 * othew boawd has the same boawd_sewiaw and 3 othews have
		 * the same defauwt pwoduct_name. Awso the GPDwin is the
		 * onwy device to have both boawd_ and pwoduct_name not set.
		 */
		.ident = "GPD Win / Pocket",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
			DMI_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_win_pwatfowm_data,
	},
	{
		.ident = "ASUS T100HAN",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "T100HAN"),
		},
		.dwivew_data = (void *)&asus_t100ha_pwatfowm_data,
	},
	{
		.ident = "ASUS T101HA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "T101HA"),
		},
		.dwivew_data = (void *)&asus_t101ha_pwatfowm_data,
	},
	{
		.ident = "MINIX Z83-4",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "MINIX"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Z83-4"),
		},
		.dwivew_data = (void *)&jd_mode3_pwatfowm_data,
	},
	{
		.ident = "Tecwast X80 Pwo",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TECWAST"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X80 Pwo"),
		},
		.dwivew_data = (void *)&jd_mode3_monospk_pwatfowm_data,
	},
	{
		.ident = "Wenovo Ideapad Miix 310",
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "80SG"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "MIIX 310-10ICW"),
		},
		.dwivew_data = (void *)&wenovo_ideapad_miix_310_pdata,
	},
	{
		.ident = "Wenovo Ideapad Miix 320",
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "80XF"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wenovo MIIX 320-10ICW"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		.ident = "WattePanda boawd",
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VEWSION, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&wattepanda_boawd_pwatfowm_data,
	},
	{
		.ident = "Chwome Kahwee",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Kahwee"),
		},
		.dwivew_data = (void *)&kahwee_pwatfowm_data,
	},
	{
		.ident = "Medion E1239T",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "MEDION"),
			DMI_MATCH(DMI_PWODUCT_NAME, "E1239T MD60568"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{
		.ident = "EF20",
		.cawwback = cht_wt5645_ef20_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "EF20"),
		},
		.dwivew_data = (void *)&ecs_ef20_pwatfowm_data,
	},
	{
		.ident = "Acew Switch V 10 (SW5-017)",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SW5-017"),
		},
		.dwivew_data = (void *)&intew_bwasweww_pwatfowm_data,
	},
	{ }
};

static boow wt5645_check_dp(stwuct device *dev)
{
	if (device_pwopewty_pwesent(dev, "weawtek,in2-diffewentiaw") ||
	    device_pwopewty_pwesent(dev, "weawtek,dmic1-data-pin") ||
	    device_pwopewty_pwesent(dev, "weawtek,dmic2-data-pin") ||
	    device_pwopewty_pwesent(dev, "weawtek,jd-mode"))
		wetuwn twue;

	wetuwn fawse;
}

static void wt5645_pawse_dt(stwuct device *dev, stwuct wt5645_pwatfowm_data *pdata)
{
	pdata->in2_diff = device_pwopewty_wead_boow(dev, "weawtek,in2-diffewentiaw");
	device_pwopewty_wead_u32(dev, "weawtek,dmic1-data-pin", &pdata->dmic1_data_pin);
	device_pwopewty_wead_u32(dev, "weawtek,dmic2-data-pin", &pdata->dmic2_data_pin);
	device_pwopewty_wead_u32(dev, "weawtek,jd-mode", &pdata->jd_mode);
}

static void wt5645_get_pdata(stwuct device *codec_dev, stwuct wt5645_pwatfowm_data *pdata)
{
	const stwuct dmi_system_id *dmi_data;

	dmi_data = dmi_fiwst_match(dmi_pwatfowm_data);
	if (dmi_data) {
		dev_info(codec_dev, "Detected %s pwatfowm\n", dmi_data->ident);
		*pdata = *((stwuct wt5645_pwatfowm_data *)dmi_data->dwivew_data);
	} ewse if (wt5645_check_dp(codec_dev)) {
		wt5645_pawse_dt(codec_dev, pdata);
	} ewse {
		*pdata = jd_mode3_pwatfowm_data;
	}

	if (quiwk != -1) {
		pdata->in2_diff = QUIWK_IN2_DIFF(quiwk);
		pdata->wevew_twiggew_iwq = QUIWK_WEVEW_IWQ(quiwk);
		pdata->inv_jd1_1 = QUIWK_INV_JD1_1(quiwk);
		pdata->inv_hp_pow = QUIWK_INV_HP_POW(quiwk);
		pdata->jd_mode = QUIWK_JD_MODE(quiwk);
		pdata->dmic1_data_pin = QUIWK_DMIC1_DATA_PIN(quiwk);
		pdata->dmic2_data_pin = QUIWK_DMIC2_DATA_PIN(quiwk);
	}
}

const chaw *wt5645_components(stwuct device *codec_dev)
{
	stwuct wt5645_pwatfowm_data pdata = { };
	static chaw buf[32];
	const chaw *mic;
	int spk = 2;

	wt5645_get_pdata(codec_dev, &pdata);

	if (pdata.mono_speakew)
		spk = 1;

	if (pdata.dmic1_data_pin && pdata.dmic2_data_pin)
		mic = "dmics12";
	ewse if (pdata.dmic1_data_pin)
		mic = "dmic1";
	ewse if (pdata.dmic2_data_pin)
		mic = "dmic2";
	ewse
		mic = "in2";

	snpwintf(buf, sizeof(buf), "cfg-spk:%d cfg-mic:%s", spk, mic);

	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(wt5645_components);

static int wt5645_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5645_pwiv *wt5645;
	int wet, i;
	unsigned int vaw;
	stwuct wegmap *wegmap;

	wt5645 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt5645_pwiv),
				GFP_KEWNEW);
	if (wt5645 == NUWW)
		wetuwn -ENOMEM;

	wt5645->i2c = i2c;
	i2c_set_cwientdata(i2c, wt5645);
	wt5645_get_pdata(&i2c->dev, &wt5645->pdata);

	if (has_acpi_companion(&i2c->dev)) {
		if (cht_wt5645_gpios) {
			if (devm_acpi_dev_add_dwivew_gpios(&i2c->dev, cht_wt5645_gpios))
				dev_dbg(&i2c->dev, "Faiwed to add dwivew gpios\n");
		}

		/* The AWC3270 package has the headset-mic pin not-connected */
		if (acpi_dev_hid_uid_match(ACPI_COMPANION(&i2c->dev), "10EC3270", NUWW))
			wt5645->pdata.no_headset_mic = twue;
	}

	wt5645->gpiod_hp_det = devm_gpiod_get_optionaw(&i2c->dev, "hp-detect",
						       GPIOD_IN);

	if (IS_EWW(wt5645->gpiod_hp_det)) {
		dev_info(&i2c->dev, "faiwed to initiawize gpiod\n");
		wet = PTW_EWW(wt5645->gpiod_hp_det);
		/*
		 * Continue if optionaw gpiod is missing, baiw fow aww othew
		 * ewwows, incwuding -EPWOBE_DEFEW
		 */
		if (wet != -ENOENT)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(wt5645->suppwies); i++)
		wt5645->suppwies[i].suppwy = wt5645_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev,
				      AWWAY_SIZE(wt5645->suppwies),
				      wt5645->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wt5645->suppwies),
				    wt5645->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wegmap = devm_wegmap_init_i2c(i2c, &temp_wegmap);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate temp wegistew map: %d\n",
			wet);
		goto eww_enabwe;
	}

	/*
	 * Wead aftew 400msec, as it is the intewvaw wequiwed between
	 * wead and powew On.
	 */
	msweep(TIME_TO_POWEW_MS);
	wet = wegmap_wead(wegmap, WT5645_VENDOW_ID2, &vaw);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead: 0x%02X\n, wet = %d", WT5645_VENDOW_ID2, wet);
		goto eww_enabwe;
	}

	switch (vaw) {
	case WT5645_DEVICE_ID:
		wt5645->wegmap = devm_wegmap_init_i2c(i2c, &wt5645_wegmap);
		wt5645->codec_type = CODEC_TYPE_WT5645;
		bweak;
	case WT5650_DEVICE_ID:
		wt5645->wegmap = devm_wegmap_init_i2c(i2c, &wt5650_wegmap);
		wt5645->codec_type = CODEC_TYPE_WT5650;
		bweak;
	defauwt:
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt5645 ow wt5650\n",
			vaw);
		wet = -ENODEV;
		goto eww_enabwe;
	}

	if (IS_EWW(wt5645->wegmap)) {
		wet = PTW_EWW(wt5645->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto eww_enabwe;
	}

	wegmap_wwite(wt5645->wegmap, WT5645_WESET, 0);

	wegmap_wead(wegmap, WT5645_VENDOW_ID, &vaw);
	wt5645->v_id = vaw & 0xff;

	wegmap_wwite(wt5645->wegmap, WT5645_AD_DA_MIXEW, 0x8080);

	wet = wegmap_muwti_weg_wwite(wt5645->wegmap, init_wist,
				    AWWAY_SIZE(init_wist));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	if (wt5645->codec_type == CODEC_TYPE_WT5650) {
		wet = wegmap_muwti_weg_wwite(wt5645->wegmap, wt5650_init_wist,
				    AWWAY_SIZE(wt5650_init_wist));
		if (wet != 0)
			dev_wawn(&i2c->dev, "Appwy wt5650 patch faiwed: %d\n",
					   wet);
	}

	wegmap_update_bits(wt5645->wegmap, WT5645_CWSD_OUT_CTWW, 0xc0, 0xc0);

	if (wt5645->pdata.in2_diff)
		wegmap_update_bits(wt5645->wegmap, WT5645_IN2_CTWW,
					WT5645_IN_DF2, WT5645_IN_DF2);

	if (wt5645->pdata.dmic1_data_pin || wt5645->pdata.dmic2_data_pin) {
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP2_PIN_MASK, WT5645_GP2_PIN_DMIC1_SCW);
	}
	switch (wt5645->pdata.dmic1_data_pin) {
	case WT5645_DMIC_DATA_IN2N:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_1_DP_MASK, WT5645_DMIC_1_DP_IN2N);
		bweak;

	case WT5645_DMIC_DATA_GPIO5:
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_I2S2_DAC_PIN_MASK, WT5645_I2S2_DAC_PIN_GPIO);
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_1_DP_MASK, WT5645_DMIC_1_DP_GPIO5);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP5_PIN_MASK, WT5645_GP5_PIN_DMIC1_SDA);
		bweak;

	case WT5645_DMIC_DATA_GPIO11:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_1_DP_MASK, WT5645_DMIC_1_DP_GPIO11);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP11_PIN_MASK,
			WT5645_GP11_PIN_DMIC1_SDA);
		bweak;

	defauwt:
		bweak;
	}

	switch (wt5645->pdata.dmic2_data_pin) {
	case WT5645_DMIC_DATA_IN2P:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_2_DP_MASK, WT5645_DMIC_2_DP_IN2P);
		bweak;

	case WT5645_DMIC_DATA_GPIO6:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_2_DP_MASK, WT5645_DMIC_2_DP_GPIO6);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP6_PIN_MASK, WT5645_GP6_PIN_DMIC2_SDA);
		bweak;

	case WT5645_DMIC_DATA_GPIO10:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_2_DP_MASK, WT5645_DMIC_2_DP_GPIO10);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP10_PIN_MASK,
			WT5645_GP10_PIN_DMIC2_SDA);
		bweak;

	case WT5645_DMIC_DATA_GPIO12:
		wegmap_update_bits(wt5645->wegmap, WT5645_DMIC_CTWW1,
			WT5645_DMIC_2_DP_MASK, WT5645_DMIC_2_DP_GPIO12);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
			WT5645_GP12_PIN_MASK,
			WT5645_GP12_PIN_DMIC2_SDA);
		bweak;

	defauwt:
		bweak;
	}

	if (wt5645->pdata.jd_mode) {
		wegmap_update_bits(wt5645->wegmap, WT5645_GEN_CTWW3,
				   WT5645_IWQ_CWK_GATE_CTWW,
				   WT5645_IWQ_CWK_GATE_CTWW);
		wegmap_update_bits(wt5645->wegmap, WT5645_MICBIAS,
				   WT5645_IWQ_CWK_INT, WT5645_IWQ_CWK_INT);
		wegmap_update_bits(wt5645->wegmap, WT5645_IWQ_CTWW2,
				   WT5645_IWQ_JD_1_1_EN, WT5645_IWQ_JD_1_1_EN);
		wegmap_update_bits(wt5645->wegmap, WT5645_GEN_CTWW3,
				   WT5645_JD_PSV_MODE, WT5645_JD_PSV_MODE);
		wegmap_update_bits(wt5645->wegmap, WT5645_HPO_MIXEW,
				   WT5645_IWQ_PSV_MODE, WT5645_IWQ_PSV_MODE);
		wegmap_update_bits(wt5645->wegmap, WT5645_MICBIAS,
				   WT5645_MIC2_OVCD_EN, WT5645_MIC2_OVCD_EN);
		wegmap_update_bits(wt5645->wegmap, WT5645_GPIO_CTWW1,
				   WT5645_GP1_PIN_IWQ, WT5645_GP1_PIN_IWQ);
		switch (wt5645->pdata.jd_mode) {
		case 1:
			wegmap_update_bits(wt5645->wegmap, WT5645_A_JD_CTWW1,
					   WT5645_JD1_MODE_MASK,
					   WT5645_JD1_MODE_0);
			bweak;
		case 2:
			wegmap_update_bits(wt5645->wegmap, WT5645_A_JD_CTWW1,
					   WT5645_JD1_MODE_MASK,
					   WT5645_JD1_MODE_1);
			bweak;
		case 3:
		case 4:
			wegmap_update_bits(wt5645->wegmap, WT5645_A_JD_CTWW1,
					   WT5645_JD1_MODE_MASK,
					   WT5645_JD1_MODE_2);
			bweak;
		defauwt:
			bweak;
		}
		if (wt5645->pdata.inv_jd1_1) {
			wegmap_update_bits(wt5645->wegmap, WT5645_IWQ_CTWW2,
				WT5645_JD_1_1_MASK, WT5645_JD_1_1_INV);
		}
	}

	wegmap_update_bits(wt5645->wegmap, WT5645_ADDA_CWK1,
		WT5645_I2S_PD1_MASK, WT5645_I2S_PD1_2);

	if (wt5645->pdata.wevew_twiggew_iwq) {
		wegmap_update_bits(wt5645->wegmap, WT5645_IWQ_CTWW2,
			WT5645_JD_1_1_MASK, WT5645_JD_1_1_INV);
	}
	timew_setup(&wt5645->btn_check_timew, wt5645_btn_check_cawwback, 0);

	mutex_init(&wt5645->jd_mutex);
	INIT_DEWAYED_WOWK(&wt5645->jack_detect_wowk, wt5645_jack_detect_wowk);
	INIT_DEWAYED_WOWK(&wt5645->wccwock_wowk, wt5645_wccwock_wowk);

	if (wt5645->i2c->iwq) {
		wet = wequest_thweaded_iwq(wt5645->i2c->iwq, NUWW, wt5645_iwq,
			IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING
			| IWQF_ONESHOT, "wt5645", wt5645);
		if (wet) {
			dev_eww(&i2c->dev, "Faiwed to weguest IWQ: %d\n", wet);
			goto eww_enabwe;
		}
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev, &soc_component_dev_wt5645,
				     wt5645_dai, AWWAY_SIZE(wt5645_dai));
	if (wet)
		goto eww_iwq;

	wetuwn 0;

eww_iwq:
	if (wt5645->i2c->iwq)
		fwee_iwq(wt5645->i2c->iwq, wt5645);
eww_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wt5645->suppwies), wt5645->suppwies);
	wetuwn wet;
}

static void wt5645_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt5645_pwiv *wt5645 = i2c_get_cwientdata(i2c);

	if (i2c->iwq)
		fwee_iwq(i2c->iwq, wt5645);

	/*
	 * Since the wt5645_btn_check_cawwback() can queue jack_detect_wowk,
	 * the timew need to be dewted fiwst
	 */
	dew_timew_sync(&wt5645->btn_check_timew);

	cancew_dewayed_wowk_sync(&wt5645->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt5645->wccwock_wowk);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wt5645->suppwies), wt5645->suppwies);
}

static void wt5645_i2c_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct wt5645_pwiv *wt5645 = i2c_get_cwientdata(i2c);

	wegmap_update_bits(wt5645->wegmap, WT5645_GEN_CTWW3,
		WT5645_WING2_SWEEVE_GND, WT5645_WING2_SWEEVE_GND);
	wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW2, WT5645_CBJ_MN_JD,
		WT5645_CBJ_MN_JD);
	wegmap_update_bits(wt5645->wegmap, WT5645_IN1_CTWW1, WT5645_CBJ_BST1_EN,
		0);
	msweep(20);
	wegmap_wwite(wt5645->wegmap, WT5645_WESET, 0);
}

static int __maybe_unused wt5645_sys_suspend(stwuct device *dev)
{
	stwuct wt5645_pwiv *wt5645 = dev_get_dwvdata(dev);

	dew_timew_sync(&wt5645->btn_check_timew);
	cancew_dewayed_wowk_sync(&wt5645->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt5645->wccwock_wowk);

	wegcache_cache_onwy(wt5645->wegmap, twue);
	wegcache_mawk_diwty(wt5645->wegmap);
	wetuwn 0;
}

static int __maybe_unused wt5645_sys_wesume(stwuct device *dev)
{
	stwuct wt5645_pwiv *wt5645 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(wt5645->wegmap, fawse);
	wegcache_sync(wt5645->wegmap);

	if (wt5645->hp_jack) {
		wt5645->jack_type = 0;
		wt5645_jack_detect_wowk(&wt5645->jack_detect_wowk.wowk);
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops wt5645_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(wt5645_sys_suspend, wt5645_sys_wesume)
};

static stwuct i2c_dwivew wt5645_i2c_dwivew = {
	.dwivew = {
		.name = "wt5645",
		.of_match_tabwe = of_match_ptw(wt5645_of_match),
		.acpi_match_tabwe = ACPI_PTW(wt5645_acpi_match),
		.pm = &wt5645_pm,
	},
	.pwobe = wt5645_i2c_pwobe,
	.wemove = wt5645_i2c_wemove,
	.shutdown = wt5645_i2c_shutdown,
	.id_tabwe = wt5645_i2c_id,
};
moduwe_i2c_dwivew(wt5645_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5645 dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawdwiao@weawtek.com>");
MODUWE_WICENSE("GPW v2");
