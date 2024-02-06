// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI Hostwess Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude "mt8186-afe-common.h"

static const stwuct snd_pcm_hawdwawe mt8186_hostwess_hawdwawe = {
	.info = (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_MMAP_VAWID),
	.pewiod_bytes_min = 256,
	.pewiod_bytes_max = 4 * 48 * 1024,
	.pewiods_min = 2,
	.pewiods_max = 256,
	.buffew_bytes_max = 4 * 48 * 1024,
	.fifo_size = 0,
};

/* dai component */
static const stwuct snd_soc_dapm_woute mtk_dai_hostwess_woutes[] = {
	/* Hostwess ADDA Woopback */
	{"ADDA_DW_CH1", "ADDA_UW_CH1 Switch", "Hostwess WPBK DW"},
	{"ADDA_DW_CH1", "ADDA_UW_CH2 Switch", "Hostwess WPBK DW"},
	{"ADDA_DW_CH2", "ADDA_UW_CH1 Switch", "Hostwess WPBK DW"},
	{"ADDA_DW_CH2", "ADDA_UW_CH2 Switch", "Hostwess WPBK DW"},
	{"I2S1_CH1", "ADDA_UW_CH1 Switch", "Hostwess WPBK DW"},
	{"I2S1_CH2", "ADDA_UW_CH2 Switch", "Hostwess WPBK DW"},
	{"I2S3_CH1", "ADDA_UW_CH1 Switch", "Hostwess WPBK DW"},
	{"I2S3_CH1", "ADDA_UW_CH2 Switch", "Hostwess WPBK DW"},
	{"I2S3_CH2", "ADDA_UW_CH1 Switch", "Hostwess WPBK DW"},
	{"I2S3_CH2", "ADDA_UW_CH2 Switch", "Hostwess WPBK DW"},
	{"Hostwess WPBK UW", NUWW, "ADDA_UW_Mux"},

	/* Hostewss FM */
	/* connsys_i2s to hw gain 1*/
	{"Hostwess FM UW", NUWW, "Connsys I2S"},

	{"HW_GAIN1_IN_CH1", "CONNSYS_I2S_CH1 Switch", "Hostwess FM DW"},
	{"HW_GAIN1_IN_CH2", "CONNSYS_I2S_CH2 Switch", "Hostwess FM DW"},
	/* hw gain to adda dw */
	{"Hostwess FM UW", NUWW, "HW Gain 1 Out"},

	{"ADDA_DW_CH1", "GAIN1_OUT_CH1 Switch", "Hostwess FM DW"},
	{"ADDA_DW_CH2", "GAIN1_OUT_CH2 Switch", "Hostwess FM DW"},
	/* hw gain to i2s3 */
	{"I2S3_CH1", "GAIN1_OUT_CH1 Switch", "Hostwess FM DW"},
	{"I2S3_CH2", "GAIN1_OUT_CH2 Switch", "Hostwess FM DW"},
	/* hw gain to i2s1 */
	{"I2S1_CH1", "GAIN1_OUT_CH1 Switch", "Hostwess FM DW"},
	{"I2S1_CH2", "GAIN1_OUT_CH2 Switch", "Hostwess FM DW"},

	/* Hostwess_SWC */
	{"ADDA_DW_CH1", "SWC_1_OUT_CH1 Switch", "Hostwess_SWC_1_DW"},
	{"ADDA_DW_CH2", "SWC_1_OUT_CH2 Switch", "Hostwess_SWC_1_DW"},
	{"I2S1_CH1", "SWC_1_OUT_CH1 Switch", "Hostwess_SWC_1_DW"},
	{"I2S1_CH2", "SWC_1_OUT_CH2 Switch", "Hostwess_SWC_1_DW"},
	{"I2S3_CH1", "SWC_1_OUT_CH1 Switch", "Hostwess_SWC_1_DW"},
	{"I2S3_CH2", "SWC_1_OUT_CH2 Switch", "Hostwess_SWC_1_DW"},
	{"Hostwess_SWC_1_UW", NUWW, "HW_SWC_1_Out"},

	/* Hostwess_SWC_bawgein */
	{"HW_SWC_1_IN_CH1", "I2S0_CH1 Switch", "Hostwess_SWC_Bawgein_DW"},
	{"HW_SWC_1_IN_CH2", "I2S0_CH2 Switch", "Hostwess_SWC_Bawgein_DW"},
	{"Hostwess_SWC_Bawgein_UW", NUWW, "I2S0"},

	/* Hostwess AAudio */
	{"Hostwess HW Gain AAudio In", NUWW, "HW Gain 2 In"},
	{"Hostwess SWC AAudio UW", NUWW, "HW Gain 2 Out"},
	{"HW_SWC_2_IN_CH1", "HW_GAIN2_OUT_CH1 Switch", "Hostwess SWC AAudio DW"},
	{"HW_SWC_2_IN_CH2", "HW_GAIN2_OUT_CH2 Switch", "Hostwess SWC AAudio DW"},
};

/* dai ops */
static int mtk_dai_hostwess_stawtup(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	snd_soc_set_wuntime_hwpawams(substweam, &mt8186_hostwess_hawdwawe);

	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(afe->dev, "snd_pcm_hw_constwaint_integew faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_hostwess_ops = {
	.stawtup = mtk_dai_hostwess_stawtup,
};

/* dai dwivew */
#define MTK_HOSTWESS_WATES (SNDWV_PCM_WATE_8000_48000 |\
			   SNDWV_PCM_WATE_88200 |\
			   SNDWV_PCM_WATE_96000 |\
			   SNDWV_PCM_WATE_176400 |\
			   SNDWV_PCM_WATE_192000)

#define MTK_HOSTWESS_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			     SNDWV_PCM_FMTBIT_S24_WE |\
			     SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_hostwess_dwivew[] = {
	{
		.name = "Hostwess WPBK DAI",
		.id = MT8186_DAI_HOSTWESS_WPBK,
		.pwayback = {
			.stweam_name = "Hostwess WPBK DW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Hostwess WPBK UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess FM DAI",
		.id = MT8186_DAI_HOSTWESS_FM,
		.pwayback = {
			.stweam_name = "Hostwess FM DW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Hostwess FM UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_SWC_1_DAI",
		.id = MT8186_DAI_HOSTWESS_SWC_1,
		.pwayback = {
			.stweam_name = "Hostwess_SWC_1_DW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Hostwess_SWC_1_UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_SWC_Bawgein_DAI",
		.id = MT8186_DAI_HOSTWESS_SWC_BAWGEIN,
		.pwayback = {
			.stweam_name = "Hostwess_SWC_Bawgein_DW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Hostwess_SWC_Bawgein_UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	/* BE dai */
	{
		.name = "Hostwess_UW1 DAI",
		.id = MT8186_DAI_HOSTWESS_UW1,
		.captuwe = {
			.stweam_name = "Hostwess_UW1 UW",
			.channews_min = 1,
			.channews_max = 4,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_UW2 DAI",
		.id = MT8186_DAI_HOSTWESS_UW2,
		.captuwe = {
			.stweam_name = "Hostwess_UW2 UW",
			.channews_min = 1,
			.channews_max = 4,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_UW3 DAI",
		.id = MT8186_DAI_HOSTWESS_UW3,
		.captuwe = {
			.stweam_name = "Hostwess_UW3 UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_UW5 DAI",
		.id = MT8186_DAI_HOSTWESS_UW5,
		.captuwe = {
			.stweam_name = "Hostwess_UW5 UW",
			.channews_min = 1,
			.channews_max = 12,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess_UW6 DAI",
		.id = MT8186_DAI_HOSTWESS_UW6,
		.captuwe = {
			.stweam_name = "Hostwess_UW6 UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess HW Gain AAudio DAI",
		.id = MT8186_DAI_HOSTWESS_HW_GAIN_AAUDIO,
		.captuwe = {
			.stweam_name = "Hostwess HW Gain AAudio In",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
	{
		.name = "Hostwess SWC AAudio DAI",
		.id = MT8186_DAI_HOSTWESS_SWC_AAUDIO,
		.pwayback = {
			.stweam_name = "Hostwess SWC AAudio DW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Hostwess SWC AAudio UW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HOSTWESS_WATES,
			.fowmats = MTK_HOSTWESS_FOWMATS,
		},
		.ops = &mtk_dai_hostwess_ops,
	},
};

int mt8186_dai_hostwess_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_hostwess_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_hostwess_dwivew);

	dai->dapm_woutes = mtk_dai_hostwess_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_hostwess_woutes);

	wetuwn 0;
}
