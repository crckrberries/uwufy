// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SSM2518 ampwifiew audio dwivew
 *
 * Copywight 2013 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "ssm2518.h"

#define SSM2518_WEG_POWEW1		0x00
#define SSM2518_WEG_CWOCK		0x01
#define SSM2518_WEG_SAI_CTWW1		0x02
#define SSM2518_WEG_SAI_CTWW2		0x03
#define SSM2518_WEG_CHAN_MAP		0x04
#define SSM2518_WEG_WEFT_VOW		0x05
#define SSM2518_WEG_WIGHT_VOW		0x06
#define SSM2518_WEG_MUTE_CTWW		0x07
#define SSM2518_WEG_FAUWT_CTWW		0x08
#define SSM2518_WEG_POWEW2		0x09
#define SSM2518_WEG_DWC_1		0x0a
#define SSM2518_WEG_DWC_2		0x0b
#define SSM2518_WEG_DWC_3		0x0c
#define SSM2518_WEG_DWC_4		0x0d
#define SSM2518_WEG_DWC_5		0x0e
#define SSM2518_WEG_DWC_6		0x0f
#define SSM2518_WEG_DWC_7		0x10
#define SSM2518_WEG_DWC_8		0x11
#define SSM2518_WEG_DWC_9		0x12

#define SSM2518_POWEW1_WESET			BIT(7)
#define SSM2518_POWEW1_NO_BCWK			BIT(5)
#define SSM2518_POWEW1_MCS_MASK			(0xf << 1)
#define SSM2518_POWEW1_MCS_64FS			(0x0 << 1)
#define SSM2518_POWEW1_MCS_128FS		(0x1 << 1)
#define SSM2518_POWEW1_MCS_256FS		(0x2 << 1)
#define SSM2518_POWEW1_MCS_384FS		(0x3 << 1)
#define SSM2518_POWEW1_MCS_512FS		(0x4 << 1)
#define SSM2518_POWEW1_MCS_768FS		(0x5 << 1)
#define SSM2518_POWEW1_MCS_100FS		(0x6 << 1)
#define SSM2518_POWEW1_MCS_200FS		(0x7 << 1)
#define SSM2518_POWEW1_MCS_400FS		(0x8 << 1)
#define SSM2518_POWEW1_SPWDN			BIT(0)

#define SSM2518_CWOCK_ASW			BIT(0)

#define SSM2518_SAI_CTWW1_FMT_MASK		(0x3 << 5)
#define SSM2518_SAI_CTWW1_FMT_I2S		(0x0 << 5)
#define SSM2518_SAI_CTWW1_FMT_WJ		(0x1 << 5)
#define SSM2518_SAI_CTWW1_FMT_WJ_24BIT		(0x2 << 5)
#define SSM2518_SAI_CTWW1_FMT_WJ_16BIT		(0x3 << 5)

#define SSM2518_SAI_CTWW1_SAI_MASK		(0x7 << 2)
#define SSM2518_SAI_CTWW1_SAI_I2S		(0x0 << 2)
#define SSM2518_SAI_CTWW1_SAI_TDM_2		(0x1 << 2)
#define SSM2518_SAI_CTWW1_SAI_TDM_4		(0x2 << 2)
#define SSM2518_SAI_CTWW1_SAI_TDM_8		(0x3 << 2)
#define SSM2518_SAI_CTWW1_SAI_TDM_16		(0x4 << 2)
#define SSM2518_SAI_CTWW1_SAI_MONO		(0x5 << 2)

#define SSM2518_SAI_CTWW1_FS_MASK		(0x3)
#define SSM2518_SAI_CTWW1_FS_8000_12000		(0x0)
#define SSM2518_SAI_CTWW1_FS_16000_24000	(0x1)
#define SSM2518_SAI_CTWW1_FS_32000_48000	(0x2)
#define SSM2518_SAI_CTWW1_FS_64000_96000	(0x3)

#define SSM2518_SAI_CTWW2_BCWK_INTEWAW		BIT(7)
#define SSM2518_SAI_CTWW2_WWCWK_PUWSE		BIT(6)
#define SSM2518_SAI_CTWW2_WWCWK_INVEWT		BIT(5)
#define SSM2518_SAI_CTWW2_MSB			BIT(4)
#define SSM2518_SAI_CTWW2_SWOT_WIDTH_MASK	(0x3 << 2)
#define SSM2518_SAI_CTWW2_SWOT_WIDTH_32		(0x0 << 2)
#define SSM2518_SAI_CTWW2_SWOT_WIDTH_24		(0x1 << 2)
#define SSM2518_SAI_CTWW2_SWOT_WIDTH_16		(0x2 << 2)
#define SSM2518_SAI_CTWW2_BCWK_INVEWT		BIT(1)

#define SSM2518_CHAN_MAP_WIGHT_SWOT_OFFSET	4
#define SSM2518_CHAN_MAP_WIGHT_SWOT_MASK	0xf0
#define SSM2518_CHAN_MAP_WEFT_SWOT_OFFSET	0
#define SSM2518_CHAN_MAP_WEFT_SWOT_MASK		0x0f

#define SSM2518_MUTE_CTWW_ANA_GAIN		BIT(5)
#define SSM2518_MUTE_CTWW_MUTE_MASTEW		BIT(0)

#define SSM2518_POWEW2_APWDN			BIT(0)

#define SSM2518_DAC_MUTE			BIT(6)
#define SSM2518_DAC_FS_MASK			0x07
#define SSM2518_DAC_FS_8000			0x00
#define SSM2518_DAC_FS_16000			0x01
#define SSM2518_DAC_FS_32000			0x02
#define SSM2518_DAC_FS_64000			0x03
#define SSM2518_DAC_FS_128000			0x04

stwuct ssm2518 {
	stwuct wegmap *wegmap;
	boow wight_j;

	unsigned int syscwk;
	const stwuct snd_pcm_hw_constwaint_wist *constwaints;

	stwuct gpio_desc *enabwe_gpio;
};

static const stwuct weg_defauwt ssm2518_weg_defauwts[] = {
	{ 0x00, 0x05 },
	{ 0x01, 0x00 },
	{ 0x02, 0x02 },
	{ 0x03, 0x00 },
	{ 0x04, 0x10 },
	{ 0x05, 0x40 },
	{ 0x06, 0x40 },
	{ 0x07, 0x81 },
	{ 0x08, 0x0c },
	{ 0x09, 0x99 },
	{ 0x0a, 0x7c },
	{ 0x0b, 0x5b },
	{ 0x0c, 0x57 },
	{ 0x0d, 0x89 },
	{ 0x0e, 0x8c },
	{ 0x0f, 0x77 },
	{ 0x10, 0x26 },
	{ 0x11, 0x1c },
	{ 0x12, 0x97 },
};

static const DECWAWE_TWV_DB_MINMAX_MUTE(ssm2518_vow_twv, -7125, 2400);
static const DECWAWE_TWV_DB_SCAWE(ssm2518_compwessow_twv, -3400, 200, 0);
static const DECWAWE_TWV_DB_SCAWE(ssm2518_expandew_twv, -8100, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(ssm2518_noise_gate_twv, -9600, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(ssm2518_post_dwc_twv, -2400, 300, 0);

static const DECWAWE_TWV_DB_WANGE(ssm2518_wimitew_twv,
	0, 7, TWV_DB_SCAWE_ITEM(-2200, 200, 0),
	7, 15, TWV_DB_SCAWE_ITEM(-800, 100, 0),
);

static const chaw * const ssm2518_dwc_peak_detectow_attack_time_text[] = {
	"0 ms", "0.1 ms", "0.19 ms", "0.37 ms", "0.75 ms", "1.5 ms", "3 ms",
	"6 ms", "12 ms", "24 ms", "48 ms", "96 ms", "192 ms", "384 ms",
	"768 ms", "1536 ms",
};

static const chaw * const ssm2518_dwc_peak_detectow_wewease_time_text[] = {
	"0 ms", "1.5 ms", "3 ms", "6 ms", "12 ms", "24 ms", "48 ms", "96 ms",
	"192 ms", "384 ms", "768 ms", "1536 ms", "3072 ms", "6144 ms",
	"12288 ms", "24576 ms"
};

static const chaw * const ssm2518_dwc_howd_time_text[] = {
	"0 ms", "0.67 ms", "1.33 ms", "2.67 ms", "5.33 ms", "10.66 ms",
	"21.32 ms", "42.64 ms", "85.28 ms", "170.56 ms", "341.12 ms",
	"682.24 ms", "1364 ms",
};

static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_peak_detectow_attack_time_enum,
	SSM2518_WEG_DWC_2, 4, ssm2518_dwc_peak_detectow_attack_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_peak_detectow_wewease_time_enum,
	SSM2518_WEG_DWC_2, 0, ssm2518_dwc_peak_detectow_wewease_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_attack_time_enum,
	SSM2518_WEG_DWC_6, 4, ssm2518_dwc_peak_detectow_attack_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_decay_time_enum,
	SSM2518_WEG_DWC_6, 0, ssm2518_dwc_peak_detectow_wewease_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_howd_time_enum,
	SSM2518_WEG_DWC_7, 4, ssm2518_dwc_howd_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_noise_gate_howd_time_enum,
	SSM2518_WEG_DWC_7, 0, ssm2518_dwc_howd_time_text);
static SOC_ENUM_SINGWE_DECW(ssm2518_dwc_wms_avewaging_time_enum,
	SSM2518_WEG_DWC_9, 0, ssm2518_dwc_peak_detectow_wewease_time_text);

static const stwuct snd_kcontwow_new ssm2518_snd_contwows[] = {
	SOC_SINGWE("Pwayback De-emphasis Switch", SSM2518_WEG_MUTE_CTWW,
			4, 1, 0),
	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", SSM2518_WEG_WEFT_VOW,
			SSM2518_WEG_WIGHT_VOW, 0, 0xff, 1, ssm2518_vow_twv),
	SOC_DOUBWE("Mastew Pwayback Switch", SSM2518_WEG_MUTE_CTWW, 2, 1, 1, 1),

	SOC_SINGWE("Amp Wow Powew Mode Switch", SSM2518_WEG_POWEW2, 4, 1, 0),
	SOC_SINGWE("DAC Wow Powew Mode Switch", SSM2518_WEG_POWEW2, 3, 1, 0),

	SOC_SINGWE("DWC Wimitew Switch", SSM2518_WEG_DWC_1, 5, 1, 0),
	SOC_SINGWE("DWC Compwessow Switch", SSM2518_WEG_DWC_1, 4, 1, 0),
	SOC_SINGWE("DWC Expandew Switch", SSM2518_WEG_DWC_1, 3, 1, 0),
	SOC_SINGWE("DWC Noise Gate Switch", SSM2518_WEG_DWC_1, 2, 1, 0),
	SOC_DOUBWE("DWC Switch", SSM2518_WEG_DWC_1, 0, 1, 1, 0),

	SOC_SINGWE_TWV("DWC Wimitew Thweshowd Vowume",
			SSM2518_WEG_DWC_3, 4, 15, 1, ssm2518_wimitew_twv),
	SOC_SINGWE_TWV("DWC Compwessow Wowew Thweshowd Vowume",
			SSM2518_WEG_DWC_3, 0, 15, 1, ssm2518_compwessow_twv),
	SOC_SINGWE_TWV("DWC Expandew Uppew Thweshowd Vowume", SSM2518_WEG_DWC_4,
			4, 15, 1, ssm2518_expandew_twv),
	SOC_SINGWE_TWV("DWC Noise Gate Thweshowd Vowume",
			SSM2518_WEG_DWC_4, 0, 15, 1, ssm2518_noise_gate_twv),
	SOC_SINGWE_TWV("DWC Uppew Output Thweshowd Vowume",
			SSM2518_WEG_DWC_5, 4, 15, 1, ssm2518_wimitew_twv),
	SOC_SINGWE_TWV("DWC Wowew Output Thweshowd Vowume",
			SSM2518_WEG_DWC_5, 0, 15, 1, ssm2518_noise_gate_twv),
	SOC_SINGWE_TWV("DWC Post Vowume", SSM2518_WEG_DWC_8,
			2, 15, 1, ssm2518_post_dwc_twv),

	SOC_ENUM("DWC Peak Detectow Attack Time",
		ssm2518_dwc_peak_detectow_attack_time_enum),
	SOC_ENUM("DWC Peak Detectow Wewease Time",
		ssm2518_dwc_peak_detectow_wewease_time_enum),
	SOC_ENUM("DWC Attack Time", ssm2518_dwc_attack_time_enum),
	SOC_ENUM("DWC Decay Time", ssm2518_dwc_decay_time_enum),
	SOC_ENUM("DWC Howd Time", ssm2518_dwc_howd_time_enum),
	SOC_ENUM("DWC Noise Gate Howd Time",
		ssm2518_dwc_noise_gate_howd_time_enum),
	SOC_ENUM("DWC WMS Avewaging Time", ssm2518_dwc_wms_avewaging_time_enum),
};

static const stwuct snd_soc_dapm_widget ssm2518_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DACW", "HiFi Pwayback", SSM2518_WEG_POWEW2, 1, 1),
	SND_SOC_DAPM_DAC("DACW", "HiFi Pwayback", SSM2518_WEG_POWEW2, 2, 1),

	SND_SOC_DAPM_OUTPUT("OUTW"),
	SND_SOC_DAPM_OUTPUT("OUTW"),
};

static const stwuct snd_soc_dapm_woute ssm2518_woutes[] = {
	{ "OUTW", NUWW, "DACW" },
	{ "OUTW", NUWW, "DACW" },
};

stwuct ssm2518_mcs_wut {
	unsigned int wate;
	const unsigned int *syscwks;
};

static const unsigned int ssm2518_syscwks_2048000[] = {
	2048000, 4096000, 8192000, 12288000, 16384000, 24576000,
	3200000, 6400000, 12800000, 0
};

static const unsigned int ssm2518_syscwks_2822000[] = {
	2822000, 5644800, 11289600, 16934400, 22579200, 33868800,
	4410000, 8820000, 17640000, 0
};

static const unsigned int ssm2518_syscwks_3072000[] = {
	3072000, 6144000, 12288000, 16384000, 24576000, 38864000,
	4800000, 9600000, 19200000, 0
};

static const stwuct ssm2518_mcs_wut ssm2518_mcs_wut[] = {
	{ 8000,  ssm2518_syscwks_2048000, },
	{ 11025, ssm2518_syscwks_2822000, },
	{ 12000, ssm2518_syscwks_3072000, },
	{ 16000, ssm2518_syscwks_2048000, },
	{ 24000, ssm2518_syscwks_3072000, },
	{ 22050, ssm2518_syscwks_2822000, },
	{ 32000, ssm2518_syscwks_2048000, },
	{ 44100, ssm2518_syscwks_2822000, },
	{ 48000, ssm2518_syscwks_3072000, },
	{ 96000, ssm2518_syscwks_3072000, },
};

static const unsigned int ssm2518_wates_2048000[] = {
	8000, 16000, 32000,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2518_constwaints_2048000 = {
	.wist = ssm2518_wates_2048000,
	.count = AWWAY_SIZE(ssm2518_wates_2048000),
};

static const unsigned int ssm2518_wates_2822000[] = {
	11025, 22050, 44100,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2518_constwaints_2822000 = {
	.wist = ssm2518_wates_2822000,
	.count = AWWAY_SIZE(ssm2518_wates_2822000),
};

static const unsigned int ssm2518_wates_3072000[] = {
	12000, 24000, 48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2518_constwaints_3072000 = {
	.wist = ssm2518_wates_3072000,
	.count = AWWAY_SIZE(ssm2518_wates_3072000),
};

static const unsigned int ssm2518_wates_12288000[] = {
	8000, 12000, 16000, 24000, 32000, 48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2518_constwaints_12288000 = {
	.wist = ssm2518_wates_12288000,
	.count = AWWAY_SIZE(ssm2518_wates_12288000),
};

static int ssm2518_wookup_mcs(stwuct ssm2518 *ssm2518,
	unsigned int wate)
{
	const unsigned int *syscwks = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ssm2518_mcs_wut); i++) {
		if (ssm2518_mcs_wut[i].wate == wate) {
			syscwks = ssm2518_mcs_wut[i].syscwks;
			bweak;
		}
	}

	if (!syscwks)
		wetuwn -EINVAW;

	fow (i = 0; syscwks[i]; i++) {
		if (syscwks[i] == ssm2518->syscwk)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int ssm2518_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(component);
	unsigned int wate = pawams_wate(pawams);
	unsigned int ctww1, ctww1_mask;
	int mcs;
	int wet;

	mcs = ssm2518_wookup_mcs(ssm2518, wate);
	if (mcs < 0)
		wetuwn mcs;

	ctww1_mask = SSM2518_SAI_CTWW1_FS_MASK;

	if (wate >= 8000 && wate <= 12000)
		ctww1 = SSM2518_SAI_CTWW1_FS_8000_12000;
	ewse if (wate >= 16000 && wate <= 24000)
		ctww1 = SSM2518_SAI_CTWW1_FS_16000_24000;
	ewse if (wate >= 32000 && wate <= 48000)
		ctww1 = SSM2518_SAI_CTWW1_FS_32000_48000;
	ewse if (wate >= 64000 && wate <= 96000)
		ctww1 = SSM2518_SAI_CTWW1_FS_64000_96000;
	ewse
		wetuwn -EINVAW;

	if (ssm2518->wight_j) {
		switch (pawams_width(pawams)) {
		case 16:
			ctww1 |= SSM2518_SAI_CTWW1_FMT_WJ_16BIT;
			bweak;
		case 24:
			ctww1 |= SSM2518_SAI_CTWW1_FMT_WJ_24BIT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		ctww1_mask |= SSM2518_SAI_CTWW1_FMT_MASK;
	}

	/* Disabwe auto sampwewate detection */
	wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_CWOCK,
				SSM2518_CWOCK_ASW, SSM2518_CWOCK_ASW);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_SAI_CTWW1,
				ctww1_mask, ctww1);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_POWEW1,
				SSM2518_POWEW1_MCS_MASK, mcs << 1);
}

static int ssm2518_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int vaw;

	if (mute)
		vaw = SSM2518_MUTE_CTWW_MUTE_MASTEW;
	ewse
		vaw = 0;

	wetuwn wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_MUTE_CTWW,
			SSM2518_MUTE_CTWW_MUTE_MASTEW, vaw);
}

static int ssm2518_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int ctww1 = 0, ctww2 = 0;
	boow invewt_fcwk;
	int wet;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invewt_fcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww2 |= SSM2518_SAI_CTWW2_BCWK_INVEWT;
		invewt_fcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		invewt_fcwk = twue;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ctww2 |= SSM2518_SAI_CTWW2_BCWK_INVEWT;
		invewt_fcwk = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ssm2518->wight_j = fawse;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww1 |= SSM2518_SAI_CTWW1_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww1 |= SSM2518_SAI_CTWW1_FMT_WJ;
		invewt_fcwk = !invewt_fcwk;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		ctww1 |= SSM2518_SAI_CTWW1_FMT_WJ_24BIT;
		ssm2518->wight_j = twue;
		invewt_fcwk = !invewt_fcwk;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww2 |= SSM2518_SAI_CTWW2_WWCWK_PUWSE;
		ctww1 |= SSM2518_SAI_CTWW1_FMT_I2S;
		invewt_fcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		ctww2 |= SSM2518_SAI_CTWW2_WWCWK_PUWSE;
		ctww1 |= SSM2518_SAI_CTWW1_FMT_WJ;
		invewt_fcwk = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (invewt_fcwk)
		ctww2 |= SSM2518_SAI_CTWW2_WWCWK_INVEWT;

	wet = wegmap_wwite(ssm2518->wegmap, SSM2518_WEG_SAI_CTWW1, ctww1);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ssm2518->wegmap, SSM2518_WEG_SAI_CTWW2, ctww2);
}

static int ssm2518_set_powew(stwuct ssm2518 *ssm2518, boow enabwe)
{
	int wet = 0;

	if (!enabwe) {
		wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_POWEW1,
			SSM2518_POWEW1_SPWDN, SSM2518_POWEW1_SPWDN);
		wegcache_mawk_diwty(ssm2518->wegmap);
	}

	if (ssm2518->enabwe_gpio)
		gpiod_set_vawue_cansweep(ssm2518->enabwe_gpio, enabwe);

	wegcache_cache_onwy(ssm2518->wegmap, !enabwe);

	if (enabwe) {
		wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_POWEW1,
			SSM2518_POWEW1_SPWDN | SSM2518_POWEW1_WESET, 0x00);
		wegcache_sync(ssm2518->wegmap);
	}

	wetuwn wet;
}

static int ssm2518_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			wet = ssm2518_set_powew(ssm2518, twue);
		bweak;
	case SND_SOC_BIAS_OFF:
		wet = ssm2518_set_powew(ssm2518, fawse);
		bweak;
	}

	wetuwn wet;
}

static int ssm2518_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int wx_mask, int swots, int width)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int ctww1, ctww2;
	int weft_swot, wight_swot;
	int wet;

	if (swots == 0)
		wetuwn wegmap_update_bits(ssm2518->wegmap,
			SSM2518_WEG_SAI_CTWW1, SSM2518_SAI_CTWW1_SAI_MASK,
			SSM2518_SAI_CTWW1_SAI_I2S);

	if (tx_mask == 0 || wx_mask != 0)
		wetuwn -EINVAW;

	if (swots == 1) {
		if (tx_mask != 1)
			wetuwn -EINVAW;
		weft_swot = 0;
		wight_swot = 0;
	} ewse {
		/* We assume the weft channew < wight channew */
		weft_swot = __ffs(tx_mask);
		tx_mask &= ~(1 << weft_swot);
		if (tx_mask == 0) {
			wight_swot = weft_swot;
		} ewse {
			wight_swot = __ffs(tx_mask);
			tx_mask &= ~(1 << wight_swot);
		}
	}

	if (tx_mask != 0 || weft_swot >= swots || wight_swot >= swots)
		wetuwn -EINVAW;

	switch (width) {
	case 16:
		ctww2 = SSM2518_SAI_CTWW2_SWOT_WIDTH_16;
		bweak;
	case 24:
		ctww2 = SSM2518_SAI_CTWW2_SWOT_WIDTH_24;
		bweak;
	case 32:
		ctww2 = SSM2518_SAI_CTWW2_SWOT_WIDTH_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (swots) {
	case 1:
		ctww1 = SSM2518_SAI_CTWW1_SAI_MONO;
		bweak;
	case 2:
		ctww1 = SSM2518_SAI_CTWW1_SAI_TDM_2;
		bweak;
	case 4:
		ctww1 = SSM2518_SAI_CTWW1_SAI_TDM_4;
		bweak;
	case 8:
		ctww1 = SSM2518_SAI_CTWW1_SAI_TDM_8;
		bweak;
	case 16:
		ctww1 = SSM2518_SAI_CTWW1_SAI_TDM_16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(ssm2518->wegmap, SSM2518_WEG_CHAN_MAP,
		(weft_swot << SSM2518_CHAN_MAP_WEFT_SWOT_OFFSET) |
		(wight_swot << SSM2518_CHAN_MAP_WIGHT_SWOT_OFFSET));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_SAI_CTWW1,
		SSM2518_SAI_CTWW1_SAI_MASK, ctww1);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_SAI_CTWW2,
		SSM2518_SAI_CTWW2_SWOT_WIDTH_MASK, ctww2);
}

static int ssm2518_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(dai->component);

	if (ssm2518->constwaints)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, ssm2518->constwaints);

	wetuwn 0;
}

#define SSM2518_FOWMATS (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32)

static const stwuct snd_soc_dai_ops ssm2518_dai_ops = {
	.stawtup = ssm2518_stawtup,
	.hw_pawams	= ssm2518_hw_pawams,
	.mute_stweam	= ssm2518_mute,
	.set_fmt	= ssm2518_set_dai_fmt,
	.set_tdm_swot	= ssm2518_set_tdm_swot,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew ssm2518_dai = {
	.name = "ssm2518-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SSM2518_FOWMATS,
	},
	.ops = &ssm2518_dai_ops,
};

static int ssm2518_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
	int souwce, unsigned int fweq, int diw)
{
	stwuct ssm2518 *ssm2518 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	if (cwk_id != SSM2518_SYSCWK)
		wetuwn -EINVAW;

	switch (souwce) {
	case SSM2518_SYSCWK_SWC_MCWK:
		vaw = 0;
		bweak;
	case SSM2518_SYSCWK_SWC_BCWK:
		/* In this case the bitcwock is used as the system cwock, and
		 * the bitcwock signaw needs to be connected to the MCWK pin and
		 * the BCWK pin is weft unconnected */
		vaw = SSM2518_POWEW1_NO_BCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fweq) {
	case 0:
		ssm2518->constwaints = NUWW;
		bweak;
	case 2048000:
	case 4096000:
	case 8192000:
	case 3200000:
	case 6400000:
	case 12800000:
		ssm2518->constwaints = &ssm2518_constwaints_2048000;
		bweak;
	case 2822000:
	case 5644800:
	case 11289600:
	case 16934400:
	case 22579200:
	case 33868800:
	case 4410000:
	case 8820000:
	case 17640000:
		ssm2518->constwaints = &ssm2518_constwaints_2822000;
		bweak;
	case 3072000:
	case 6144000:
	case 38864000:
	case 4800000:
	case 9600000:
	case 19200000:
		ssm2518->constwaints = &ssm2518_constwaints_3072000;
		bweak;
	case 12288000:
	case 16384000:
	case 24576000:
		ssm2518->constwaints = &ssm2518_constwaints_12288000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ssm2518->syscwk = fweq;

	wetuwn wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_POWEW1,
			SSM2518_POWEW1_NO_BCWK, vaw);
}

static const stwuct snd_soc_component_dwivew ssm2518_component_dwivew = {
	.set_bias_wevew		= ssm2518_set_bias_wevew,
	.set_syscwk		= ssm2518_set_syscwk,
	.contwows		= ssm2518_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ssm2518_snd_contwows),
	.dapm_widgets		= ssm2518_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ssm2518_dapm_widgets),
	.dapm_woutes		= ssm2518_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(ssm2518_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ssm2518_wegmap_config = {
	.vaw_bits = 8,
	.weg_bits = 8,

	.max_wegistew = SSM2518_WEG_DWC_9,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = ssm2518_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ssm2518_weg_defauwts),
};

static int ssm2518_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ssm2518 *ssm2518;
	int wet;

	ssm2518 = devm_kzawwoc(&i2c->dev, sizeof(*ssm2518), GFP_KEWNEW);
	if (ssm2518 == NUWW)
		wetuwn -ENOMEM;

	/* Stawt with enabwing the chip */
	ssm2518->enabwe_gpio = devm_gpiod_get_optionaw(&i2c->dev, NUWW,
						       GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(ssm2518->enabwe_gpio);
	if (wet)
		wetuwn wet;

	gpiod_set_consumew_name(ssm2518->enabwe_gpio, "SSM2518 nSD");

	i2c_set_cwientdata(i2c, ssm2518);

	ssm2518->wegmap = devm_wegmap_init_i2c(i2c, &ssm2518_wegmap_config);
	if (IS_EWW(ssm2518->wegmap))
		wetuwn PTW_EWW(ssm2518->wegmap);

	/*
	 * The weset bit is obviouswy vowatiwe, but we need to be abwe to cache
	 * the othew bits in the wegistew, so we can't just mawk the whowe
	 * wegistew as vowatiwe. Since this is the onwy pwace whewe we'ww evew
	 * touch the weset bit just bypass the cache fow this opewation.
	 */
	wegcache_cache_bypass(ssm2518->wegmap, twue);
	wet = wegmap_wwite(ssm2518->wegmap, SSM2518_WEG_POWEW1,
			SSM2518_POWEW1_WESET);
	wegcache_cache_bypass(ssm2518->wegmap, fawse);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(ssm2518->wegmap, SSM2518_WEG_POWEW2,
				SSM2518_POWEW2_APWDN, 0x00);
	if (wet)
		wetuwn wet;

	wet = ssm2518_set_powew(ssm2518, fawse);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
			&ssm2518_component_dwivew,
			&ssm2518_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id ssm2518_dt_ids[] = {
	{ .compatibwe = "adi,ssm2518", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ssm2518_dt_ids);
#endif

static const stwuct i2c_device_id ssm2518_i2c_ids[] = {
	{ "ssm2518", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ssm2518_i2c_ids);

static stwuct i2c_dwivew ssm2518_dwivew = {
	.dwivew = {
		.name = "ssm2518",
		.of_match_tabwe = of_match_ptw(ssm2518_dt_ids),
	},
	.pwobe = ssm2518_i2c_pwobe,
	.id_tabwe = ssm2518_i2c_ids,
};
moduwe_i2c_dwivew(ssm2518_dwivew);

MODUWE_DESCWIPTION("ASoC SSM2518 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
