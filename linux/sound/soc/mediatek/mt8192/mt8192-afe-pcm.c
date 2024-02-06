// SPDX-Wicense-Identifiew: GPW-2.0
//
// Mediatek AWSA SoC AFE pwatfowm dwivew fow 8192
//
// Copywight (c) 2020 MediaTek Inc.
// Authow: Shane Chien <shane.chien@mediatek.com>
//

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>

#incwude "../common/mtk-afe-fe-dai.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"

#incwude "mt8192-afe-common.h"
#incwude "mt8192-afe-cwk.h"
#incwude "mt8192-afe-gpio.h"
#incwude "mt8192-intewconnection.h"

static const stwuct snd_pcm_hawdwawe mt8192_afe_hawdwawe = {
	.info = (SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats = (SNDWV_PCM_FMTBIT_S16_WE |
		    SNDWV_PCM_FMTBIT_S24_WE |
		    SNDWV_PCM_FMTBIT_S32_WE),
	.pewiod_bytes_min = 96,
	.pewiod_bytes_max = 4 * 48 * 1024,
	.pewiods_min = 2,
	.pewiods_max = 256,
	.buffew_bytes_max = 4 * 48 * 1024,
	.fifo_size = 0,
};

static int mt8192_memif_fs(stwuct snd_pcm_substweam *substweam,
			   unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	int id = snd_soc_wtd_to_cpu(wtd, 0)->id;

	wetuwn mt8192_wate_twansfowm(afe->dev, wate, id);
}

static int mt8192_get_dai_fs(stwuct mtk_base_afe *afe,
			     int dai_id, unsigned int wate)
{
	wetuwn mt8192_wate_twansfowm(afe->dev, wate, dai_id);
}

static int mt8192_iwq_fs(stwuct snd_pcm_substweam *substweam, unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);

	wetuwn mt8192_genewaw_wate_twansfowm(afe->dev, wate);
}

static int mt8192_get_memif_pbuf_size(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if ((wuntime->pewiod_size * 1000) / wuntime->wate > 10)
		wetuwn MT8192_MEMIF_PBUF_SIZE_256_BYTES;
	ewse
		wetuwn MT8192_MEMIF_PBUF_SIZE_32_BYTES;
}

#define MTK_PCM_WATES (SNDWV_PCM_WATE_8000_48000 |\
		       SNDWV_PCM_WATE_88200 |\
		       SNDWV_PCM_WATE_96000 |\
		       SNDWV_PCM_WATE_176400 |\
		       SNDWV_PCM_WATE_192000)

#define MTK_PCM_DAI_WATES (SNDWV_PCM_WATE_8000 |\
			   SNDWV_PCM_WATE_16000 |\
			   SNDWV_PCM_WATE_32000 |\
			   SNDWV_PCM_WATE_48000)

#define MTK_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mt8192_memif_dai_dwivew[] = {
	/* FE DAIs: memowy intefaces to CPU */
	{
		.name = "DW1",
		.id = MT8192_MEMIF_DW1,
		.pwayback = {
			.stweam_name = "DW1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW12",
		.id = MT8192_MEMIF_DW12,
		.pwayback = {
			.stweam_name = "DW12",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW2",
		.id = MT8192_MEMIF_DW2,
		.pwayback = {
			.stweam_name = "DW2",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW3",
		.id = MT8192_MEMIF_DW3,
		.pwayback = {
			.stweam_name = "DW3",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW4",
		.id = MT8192_MEMIF_DW4,
		.pwayback = {
			.stweam_name = "DW4",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW5",
		.id = MT8192_MEMIF_DW5,
		.pwayback = {
			.stweam_name = "DW5",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW6",
		.id = MT8192_MEMIF_DW6,
		.pwayback = {
			.stweam_name = "DW6",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW7",
		.id = MT8192_MEMIF_DW7,
		.pwayback = {
			.stweam_name = "DW7",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW8",
		.id = MT8192_MEMIF_DW8,
		.pwayback = {
			.stweam_name = "DW8",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "DW9",
		.id = MT8192_MEMIF_DW9,
		.pwayback = {
			.stweam_name = "DW9",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW1",
		.id = MT8192_MEMIF_VUW12,
		.captuwe = {
			.stweam_name = "UW1",
			.channews_min = 1,
			.channews_max = 4,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW2",
		.id = MT8192_MEMIF_AWB,
		.captuwe = {
			.stweam_name = "UW2",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW3",
		.id = MT8192_MEMIF_VUW2,
		.captuwe = {
			.stweam_name = "UW3",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW4",
		.id = MT8192_MEMIF_AWB2,
		.captuwe = {
			.stweam_name = "UW4",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW5",
		.id = MT8192_MEMIF_VUW3,
		.captuwe = {
			.stweam_name = "UW5",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW6",
		.id = MT8192_MEMIF_VUW4,
		.captuwe = {
			.stweam_name = "UW6",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW7",
		.id = MT8192_MEMIF_VUW5,
		.captuwe = {
			.stweam_name = "UW7",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW8",
		.id = MT8192_MEMIF_VUW6,
		.captuwe = {
			.stweam_name = "UW8",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW_MONO_1",
		.id = MT8192_MEMIF_MOD_DAI,
		.captuwe = {
			.stweam_name = "UW_MONO_1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_DAI_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW_MONO_2",
		.id = MT8192_MEMIF_DAI,
		.captuwe = {
			.stweam_name = "UW_MONO_2",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_DAI_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW_MONO_3",
		.id = MT8192_MEMIF_DAI2,
		.captuwe = {
			.stweam_name = "UW_MONO_3",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_DAI_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "HDMI",
		.id = MT8192_MEMIF_HDMI,
		.pwayback = {
			.stweam_name = "HDMI",
			.channews_min = 2,
			.channews_max = 8,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
};

static int uw_tinyconn_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int weg_shift;
	unsigned int weg_mask_shift;

	dev_dbg(afe->dev, "%s(), event 0x%x\n", __func__, event);

	if (stwstw(w->name, "UW1")) {
		weg_shift = VUW1_USE_TINY_SFT;
		weg_mask_shift = VUW1_USE_TINY_MASK_SFT;
	} ewse if (stwstw(w->name, "UW2")) {
		weg_shift = VUW2_USE_TINY_SFT;
		weg_mask_shift = VUW2_USE_TINY_MASK_SFT;
	} ewse if (stwstw(w->name, "UW3")) {
		weg_shift = VUW12_USE_TINY_SFT;
		weg_mask_shift = VUW12_USE_TINY_MASK_SFT;
	} ewse if (stwstw(w->name, "UW4")) {
		weg_shift = AWB2_USE_TINY_SFT;
		weg_mask_shift = AWB2_USE_TINY_MASK_SFT;
	} ewse {
		weg_shift = AWB2_USE_TINY_SFT;
		weg_mask_shift = AWB2_USE_TINY_MASK_SFT;
		dev_wawn(afe->dev, "%s(), eww widget name %s, defauwt use UW4",
			 __func__, w->name);
	}

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_update_bits(afe->wegmap, AFE_MEMIF_CONN, weg_mask_shift,
				   0x1 << weg_shift);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(afe->wegmap, AFE_MEMIF_CONN, weg_mask_shift,
				   0x0 << weg_shift);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* dma widget & woutes*/
static const stwuct snd_kcontwow_new memif_uw1_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN21,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN21,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN21,
				    I_ADDA_UW_CH3, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw1_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN22,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN22,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN22,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH4", AFE_CONN22,
				    I_ADDA_UW_CH4, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw1_ch3_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN9,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN9,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN9,
				    I_ADDA_UW_CH3, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw1_ch4_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN10,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN10,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN10,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH4", AFE_CONN10,
				    I_ADDA_UW_CH4, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw2_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH1", AFE_CONN5,
				    I_I2S0_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN5,
				    I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN5,
				    I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN5,
				    I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN5,
				    I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN5_1,
				    I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN5_1,
				    I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN5_1,
				    I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN5,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN5,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH1", AFE_CONN5,
				    I_I2S2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S6_CH1", AFE_CONN5_1,
				    I_I2S6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S8_CH1", AFE_CONN5_1,
				    I_I2S8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH1", AFE_CONN5_1,
				    I_CONNSYS_I2S_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH1", AFE_CONN5_1,
				    I_SWC_1_OUT_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw2_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH2", AFE_CONN6,
				    I_I2S0_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN6,
				    I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN6,
				    I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN6,
				    I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN6,
				    I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN6_1,
				    I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN6_1,
				    I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN6_1,
				    I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN6,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN6,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH2", AFE_CONN6,
				    I_I2S2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S6_CH2", AFE_CONN6_1,
				    I_I2S6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S8_CH2", AFE_CONN6_1,
				    I_I2S8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH2", AFE_CONN6_1,
				    I_CONNSYS_I2S_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH2", AFE_CONN6_1,
				    I_SWC_1_OUT_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw3_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH1", AFE_CONN32_1,
				    I_CONNSYS_I2S_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN32,
				    I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN32,
				    I_DW2_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw3_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH2", AFE_CONN33_1,
				    I_CONNSYS_I2S_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw4_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN38,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH1", AFE_CONN38,
				    I_I2S0_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw4_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN39,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH2", AFE_CONN39,
				    I_I2S0_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw5_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN44,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw5_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN45,
				    I_ADDA_UW_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw6_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN46,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN46,
				    I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN46,
				    I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN46_1,
				    I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN46,
				    I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN46,
				    I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN46_1,
				    I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN46,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN46,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw6_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN47,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN47,
				    I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN47,
				    I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN47_1,
				    I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN47,
				    I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN47,
				    I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN47_1,
				    I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN47,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN47,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw7_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN48,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw7_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN49,
				    I_ADDA_UW_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw8_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN50,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw8_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN51,
				    I_ADDA_UW_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw_mono_1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN12,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN12,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw_mono_2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN11,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw_mono_3_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN35,
				    I_ADDA_UW_CH1, 1, 0),
};

/* TINYCONN MUX */
enum {
	TINYCONN_CH1_MUX_I2S0 = 0x14,
	TINYCONN_CH2_MUX_I2S0 = 0x15,
	TINYCONN_CH1_MUX_I2S6 = 0x1a,
	TINYCONN_CH2_MUX_I2S6 = 0x1b,
	TINYCONN_CH1_MUX_I2S8 = 0x1c,
	TINYCONN_CH2_MUX_I2S8 = 0x1d,
	TINYCONN_MUX_NONE = 0x1f,
};

static const chaw * const tinyconn_mux_map[] = {
	"NONE",
	"I2S0_CH1",
	"I2S0_CH2",
	"I2S6_CH1",
	"I2S6_CH2",
	"I2S8_CH1",
	"I2S8_CH2",
};

static int tinyconn_mux_map_vawue[] = {
	TINYCONN_MUX_NONE,
	TINYCONN_CH1_MUX_I2S0,
	TINYCONN_CH2_MUX_I2S0,
	TINYCONN_CH1_MUX_I2S6,
	TINYCONN_CH2_MUX_I2S6,
	TINYCONN_CH1_MUX_I2S8,
	TINYCONN_CH2_MUX_I2S8,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(uw4_tinyconn_ch1_mux_map_enum,
				  AFE_TINY_CONN0,
				  O_2_CFG_SFT,
				  O_2_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);
static SOC_VAWUE_ENUM_SINGWE_DECW(uw4_tinyconn_ch2_mux_map_enum,
				  AFE_TINY_CONN0,
				  O_3_CFG_SFT,
				  O_3_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);

static const stwuct snd_kcontwow_new uw4_tinyconn_ch1_mux_contwow =
	SOC_DAPM_ENUM("UW4_TINYCONN_CH1_MUX", uw4_tinyconn_ch1_mux_map_enum);
static const stwuct snd_kcontwow_new uw4_tinyconn_ch2_mux_contwow =
	SOC_DAPM_ENUM("UW4_TINYCONN_CH2_MUX", uw4_tinyconn_ch2_mux_map_enum);

static const stwuct snd_soc_dapm_widget mt8192_memif_widgets[] = {
	/* intew-connections */
	SND_SOC_DAPM_MIXEW("UW1_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch1_mix, AWWAY_SIZE(memif_uw1_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW1_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch2_mix, AWWAY_SIZE(memif_uw1_ch2_mix)),
	SND_SOC_DAPM_MIXEW("UW1_CH3", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch3_mix, AWWAY_SIZE(memif_uw1_ch3_mix)),
	SND_SOC_DAPM_MIXEW("UW1_CH4", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch4_mix, AWWAY_SIZE(memif_uw1_ch4_mix)),

	SND_SOC_DAPM_MIXEW("UW2_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw2_ch1_mix, AWWAY_SIZE(memif_uw2_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW2_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw2_ch2_mix, AWWAY_SIZE(memif_uw2_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW3_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw3_ch1_mix, AWWAY_SIZE(memif_uw3_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW3_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw3_ch2_mix, AWWAY_SIZE(memif_uw3_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW4_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw4_ch1_mix, AWWAY_SIZE(memif_uw4_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW4_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw4_ch2_mix, AWWAY_SIZE(memif_uw4_ch2_mix)),
	SND_SOC_DAPM_MUX_E("UW4_TINYCONN_CH1_MUX", SND_SOC_NOPM, 0, 0,
			   &uw4_tinyconn_ch1_mux_contwow,
			   uw_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX_E("UW4_TINYCONN_CH2_MUX", SND_SOC_NOPM, 0, 0,
			   &uw4_tinyconn_ch2_mux_contwow,
			   uw_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_MIXEW("UW5_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw5_ch1_mix, AWWAY_SIZE(memif_uw5_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW5_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw5_ch2_mix, AWWAY_SIZE(memif_uw5_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW6_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw6_ch1_mix, AWWAY_SIZE(memif_uw6_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW6_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw6_ch2_mix, AWWAY_SIZE(memif_uw6_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW7_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw7_ch1_mix, AWWAY_SIZE(memif_uw7_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW7_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw7_ch2_mix, AWWAY_SIZE(memif_uw7_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW8_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw8_ch1_mix, AWWAY_SIZE(memif_uw8_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW8_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw8_ch2_mix, AWWAY_SIZE(memif_uw8_ch2_mix)),

	SND_SOC_DAPM_MIXEW("UW_MONO_1_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw_mono_1_mix,
			   AWWAY_SIZE(memif_uw_mono_1_mix)),

	SND_SOC_DAPM_MIXEW("UW_MONO_2_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw_mono_2_mix,
			   AWWAY_SIZE(memif_uw_mono_2_mix)),

	SND_SOC_DAPM_MIXEW("UW_MONO_3_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw_mono_3_mix,
			   AWWAY_SIZE(memif_uw_mono_3_mix)),

	SND_SOC_DAPM_INPUT("UW1_VIWTUAW_INPUT"),
	SND_SOC_DAPM_INPUT("UW2_VIWTUAW_INPUT"),
	SND_SOC_DAPM_INPUT("UW6_VIWTUAW_INPUT"),
};

static const stwuct snd_soc_dapm_woute mt8192_memif_woutes[] = {
	{"UW1", NUWW, "UW1_CH1"},
	{"UW1", NUWW, "UW1_CH2"},
	{"UW1", NUWW, "UW1_CH3"},
	{"UW1", NUWW, "UW1_CH4"},
	{"UW1_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW1_CH1", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW1_CH1", "ADDA_UW_CH3", "ADDA_CH34_UW_Mux"},
	{"UW1_CH2", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW1_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW1_CH2", "ADDA_UW_CH3", "ADDA_CH34_UW_Mux"},
	{"UW1_CH2", "ADDA_UW_CH4", "ADDA_CH34_UW_Mux"},
	{"UW1_CH3", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW1_CH3", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW1_CH3", "ADDA_UW_CH3", "ADDA_CH34_UW_Mux"},
	{"UW1_CH4", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW1_CH4", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW1_CH4", "ADDA_UW_CH3", "ADDA_CH34_UW_Mux"},
	{"UW1_CH4", "ADDA_UW_CH4", "ADDA_CH34_UW_Mux"},

	{"UW2", NUWW, "UW2_CH1"},
	{"UW2", NUWW, "UW2_CH2"},
	{"UW2_CH1", "I2S0_CH1", "I2S0"},
	{"UW2_CH2", "I2S0_CH2", "I2S0"},
	{"UW2_CH1", "I2S2_CH1", "I2S2"},
	{"UW2_CH2", "I2S2_CH2", "I2S2"},
	{"UW2_CH1", "I2S6_CH1", "I2S6"},
	{"UW2_CH2", "I2S6_CH2", "I2S6"},
	{"UW2_CH1", "I2S8_CH1", "I2S8"},
	{"UW2_CH2", "I2S8_CH2", "I2S8"},

	{"UW2_CH1", "PCM_1_CAP_CH1", "PCM 1 Captuwe"},
	{"UW2_CH2", "PCM_1_CAP_CH1", "PCM 1 Captuwe"},
	{"UW2_CH1", "PCM_2_CAP_CH1", "PCM 2 Captuwe"},
	{"UW2_CH2", "PCM_2_CAP_CH1", "PCM 2 Captuwe"},

	{"UW_MONO_1", NUWW, "UW_MONO_1_CH1"},
	{"UW_MONO_1_CH1", "PCM_1_CAP_CH1", "PCM 1 Captuwe"},
	{"UW_MONO_1_CH1", "PCM_2_CAP_CH1", "PCM 2 Captuwe"},

	{"UW_MONO_2", NUWW, "UW_MONO_2_CH1"},
	{"UW_MONO_2_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},

	{"UW_MONO_3", NUWW, "UW_MONO_3_CH1"},
	{"UW_MONO_3_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},

	{"UW2_CH1", "CONNSYS_I2S_CH1", "Connsys I2S"},
	{"UW2_CH2", "CONNSYS_I2S_CH2", "Connsys I2S"},

	{"UW3", NUWW, "UW3_CH1"},
	{"UW3", NUWW, "UW3_CH2"},
	{"UW3_CH1", "CONNSYS_I2S_CH1", "Connsys I2S"},
	{"UW3_CH2", "CONNSYS_I2S_CH2", "Connsys I2S"},

	{"UW4", NUWW, "UW4_CH1"},
	{"UW4", NUWW, "UW4_CH2"},
	{"UW4", NUWW, "UW4_TINYCONN_CH1_MUX"},
	{"UW4", NUWW, "UW4_TINYCONN_CH2_MUX"},
	{"UW4_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW4_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW4_CH1", "I2S0_CH1", "I2S0"},
	{"UW4_CH2", "I2S0_CH2", "I2S0"},
	{"UW4_TINYCONN_CH1_MUX", "I2S0_CH1", "I2S0"},
	{"UW4_TINYCONN_CH2_MUX", "I2S0_CH2", "I2S0"},

	{"UW5", NUWW, "UW5_CH1"},
	{"UW5", NUWW, "UW5_CH2"},
	{"UW5_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW5_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},

	{"UW6", NUWW, "UW6_CH1"},
	{"UW6", NUWW, "UW6_CH2"},

	{"UW6_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW6_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},
	{"UW6_CH1", "PCM_1_CAP_CH1", "PCM 1 Captuwe"},
	{"UW6_CH2", "PCM_1_CAP_CH1", "PCM 1 Captuwe"},
	{"UW6_CH1", "PCM_2_CAP_CH1", "PCM 2 Captuwe"},
	{"UW6_CH2", "PCM_2_CAP_CH1", "PCM 2 Captuwe"},

	{"UW7", NUWW, "UW7_CH1"},
	{"UW7", NUWW, "UW7_CH2"},
	{"UW7_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW7_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},

	{"UW8", NUWW, "UW8_CH1"},
	{"UW8", NUWW, "UW8_CH2"},
	{"UW8_CH1", "ADDA_UW_CH1", "ADDA_UW_Mux"},
	{"UW8_CH2", "ADDA_UW_CH2", "ADDA_UW_Mux"},
};

static const stwuct mtk_base_memif_data memif_data[MT8192_MEMIF_NUM] = {
	[MT8192_MEMIF_DW1] = {
		.name = "DW1",
		.id = MT8192_MEMIF_DW1,
		.weg_ofs_base = AFE_DW1_BASE,
		.weg_ofs_cuw = AFE_DW1_CUW,
		.weg_ofs_end = AFE_DW1_END,
		.weg_ofs_base_msb = AFE_DW1_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW1_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW1_END_MSB,
		.fs_weg = AFE_DW1_CON0,
		.fs_shift = DW1_MODE_SFT,
		.fs_maskbit = DW1_MODE_MASK,
		.mono_weg = AFE_DW1_CON0,
		.mono_shift = DW1_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW1_ON_SFT,
		.hd_weg = AFE_DW1_CON0,
		.hd_shift = DW1_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW1_CON0,
		.hd_awign_mshift = DW1_HAWIGN_SFT,
		.pbuf_weg = AFE_DW1_CON0,
		.pbuf_shift = DW1_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW1_CON0,
		.minwen_shift = DW1_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW12] = {
		.name = "DW12",
		.id = MT8192_MEMIF_DW12,
		.weg_ofs_base = AFE_DW12_BASE,
		.weg_ofs_cuw = AFE_DW12_CUW,
		.weg_ofs_end = AFE_DW12_END,
		.weg_ofs_base_msb = AFE_DW12_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW12_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW12_END_MSB,
		.fs_weg = AFE_DW12_CON0,
		.fs_shift = DW12_MODE_SFT,
		.fs_maskbit = DW12_MODE_MASK,
		.mono_weg = AFE_DW12_CON0,
		.mono_shift = DW12_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW12_ON_SFT,
		.hd_weg = AFE_DW12_CON0,
		.hd_shift = DW12_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW12_CON0,
		.hd_awign_mshift = DW12_HAWIGN_SFT,
		.pbuf_weg = AFE_DW12_CON0,
		.pbuf_shift = DW12_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW12_CON0,
		.minwen_shift = DW12_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW2] = {
		.name = "DW2",
		.id = MT8192_MEMIF_DW2,
		.weg_ofs_base = AFE_DW2_BASE,
		.weg_ofs_cuw = AFE_DW2_CUW,
		.weg_ofs_end = AFE_DW2_END,
		.weg_ofs_base_msb = AFE_DW2_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW2_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW2_END_MSB,
		.fs_weg = AFE_DW2_CON0,
		.fs_shift = DW2_MODE_SFT,
		.fs_maskbit = DW2_MODE_MASK,
		.mono_weg = AFE_DW2_CON0,
		.mono_shift = DW2_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW2_ON_SFT,
		.hd_weg = AFE_DW2_CON0,
		.hd_shift = DW2_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW2_CON0,
		.hd_awign_mshift = DW2_HAWIGN_SFT,
		.pbuf_weg = AFE_DW2_CON0,
		.pbuf_shift = DW2_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW2_CON0,
		.minwen_shift = DW2_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW3] = {
		.name = "DW3",
		.id = MT8192_MEMIF_DW3,
		.weg_ofs_base = AFE_DW3_BASE,
		.weg_ofs_cuw = AFE_DW3_CUW,
		.weg_ofs_end = AFE_DW3_END,
		.weg_ofs_base_msb = AFE_DW3_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW3_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW3_END_MSB,
		.fs_weg = AFE_DW3_CON0,
		.fs_shift = DW3_MODE_SFT,
		.fs_maskbit = DW3_MODE_MASK,
		.mono_weg = AFE_DW3_CON0,
		.mono_shift = DW3_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW3_ON_SFT,
		.hd_weg = AFE_DW3_CON0,
		.hd_shift = DW3_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW3_CON0,
		.hd_awign_mshift = DW3_HAWIGN_SFT,
		.pbuf_weg = AFE_DW3_CON0,
		.pbuf_shift = DW3_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW3_CON0,
		.minwen_shift = DW3_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW4] = {
		.name = "DW4",
		.id = MT8192_MEMIF_DW4,
		.weg_ofs_base = AFE_DW4_BASE,
		.weg_ofs_cuw = AFE_DW4_CUW,
		.weg_ofs_end = AFE_DW4_END,
		.weg_ofs_base_msb = AFE_DW4_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW4_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW4_END_MSB,
		.fs_weg = AFE_DW4_CON0,
		.fs_shift = DW4_MODE_SFT,
		.fs_maskbit = DW4_MODE_MASK,
		.mono_weg = AFE_DW4_CON0,
		.mono_shift = DW4_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW4_ON_SFT,
		.hd_weg = AFE_DW4_CON0,
		.hd_shift = DW4_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW4_CON0,
		.hd_awign_mshift = DW4_HAWIGN_SFT,
		.pbuf_weg = AFE_DW4_CON0,
		.pbuf_shift = DW4_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW4_CON0,
		.minwen_shift = DW4_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW5] = {
		.name = "DW5",
		.id = MT8192_MEMIF_DW5,
		.weg_ofs_base = AFE_DW5_BASE,
		.weg_ofs_cuw = AFE_DW5_CUW,
		.weg_ofs_end = AFE_DW5_END,
		.weg_ofs_base_msb = AFE_DW5_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW5_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW5_END_MSB,
		.fs_weg = AFE_DW5_CON0,
		.fs_shift = DW5_MODE_SFT,
		.fs_maskbit = DW5_MODE_MASK,
		.mono_weg = AFE_DW5_CON0,
		.mono_shift = DW5_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW5_ON_SFT,
		.hd_weg = AFE_DW5_CON0,
		.hd_shift = DW5_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW5_CON0,
		.hd_awign_mshift = DW5_HAWIGN_SFT,
		.pbuf_weg = AFE_DW5_CON0,
		.pbuf_shift = DW5_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW5_CON0,
		.minwen_shift = DW5_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW6] = {
		.name = "DW6",
		.id = MT8192_MEMIF_DW6,
		.weg_ofs_base = AFE_DW6_BASE,
		.weg_ofs_cuw = AFE_DW6_CUW,
		.weg_ofs_end = AFE_DW6_END,
		.weg_ofs_base_msb = AFE_DW6_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW6_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW6_END_MSB,
		.fs_weg = AFE_DW6_CON0,
		.fs_shift = DW6_MODE_SFT,
		.fs_maskbit = DW6_MODE_MASK,
		.mono_weg = AFE_DW6_CON0,
		.mono_shift = DW6_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW6_ON_SFT,
		.hd_weg = AFE_DW6_CON0,
		.hd_shift = DW6_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW6_CON0,
		.hd_awign_mshift = DW6_HAWIGN_SFT,
		.pbuf_weg = AFE_DW6_CON0,
		.pbuf_shift = DW6_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW6_CON0,
		.minwen_shift = DW6_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW7] = {
		.name = "DW7",
		.id = MT8192_MEMIF_DW7,
		.weg_ofs_base = AFE_DW7_BASE,
		.weg_ofs_cuw = AFE_DW7_CUW,
		.weg_ofs_end = AFE_DW7_END,
		.weg_ofs_base_msb = AFE_DW7_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW7_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW7_END_MSB,
		.fs_weg = AFE_DW7_CON0,
		.fs_shift = DW7_MODE_SFT,
		.fs_maskbit = DW7_MODE_MASK,
		.mono_weg = AFE_DW7_CON0,
		.mono_shift = DW7_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW7_ON_SFT,
		.hd_weg = AFE_DW7_CON0,
		.hd_shift = DW7_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW7_CON0,
		.hd_awign_mshift = DW7_HAWIGN_SFT,
		.pbuf_weg = AFE_DW7_CON0,
		.pbuf_shift = DW7_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW7_CON0,
		.minwen_shift = DW7_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW8] = {
		.name = "DW8",
		.id = MT8192_MEMIF_DW8,
		.weg_ofs_base = AFE_DW8_BASE,
		.weg_ofs_cuw = AFE_DW8_CUW,
		.weg_ofs_end = AFE_DW8_END,
		.weg_ofs_base_msb = AFE_DW8_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW8_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW8_END_MSB,
		.fs_weg = AFE_DW8_CON0,
		.fs_shift = DW8_MODE_SFT,
		.fs_maskbit = DW8_MODE_MASK,
		.mono_weg = AFE_DW8_CON0,
		.mono_shift = DW8_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW8_ON_SFT,
		.hd_weg = AFE_DW8_CON0,
		.hd_shift = DW8_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW8_CON0,
		.hd_awign_mshift = DW8_HAWIGN_SFT,
		.pbuf_weg = AFE_DW8_CON0,
		.pbuf_shift = DW8_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW8_CON0,
		.minwen_shift = DW8_MINWEN_SFT,
	},
	[MT8192_MEMIF_DW9] = {
		.name = "DW9",
		.id = MT8192_MEMIF_DW9,
		.weg_ofs_base = AFE_DW9_BASE,
		.weg_ofs_cuw = AFE_DW9_CUW,
		.weg_ofs_end = AFE_DW9_END,
		.weg_ofs_base_msb = AFE_DW9_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW9_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW9_END_MSB,
		.fs_weg = AFE_DW9_CON0,
		.fs_shift = DW9_MODE_SFT,
		.fs_maskbit = DW9_MODE_MASK,
		.mono_weg = AFE_DW9_CON0,
		.mono_shift = DW9_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW9_ON_SFT,
		.hd_weg = AFE_DW9_CON0,
		.hd_shift = DW9_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW9_CON0,
		.hd_awign_mshift = DW9_HAWIGN_SFT,
		.pbuf_weg = AFE_DW9_CON0,
		.pbuf_shift = DW9_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW9_CON0,
		.minwen_shift = DW9_MINWEN_SFT,
	},
	[MT8192_MEMIF_DAI] = {
		.name = "DAI",
		.id = MT8192_MEMIF_DAI,
		.weg_ofs_base = AFE_DAI_BASE,
		.weg_ofs_cuw = AFE_DAI_CUW,
		.weg_ofs_end = AFE_DAI_END,
		.weg_ofs_base_msb = AFE_DAI_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DAI_CUW_MSB,
		.weg_ofs_end_msb = AFE_DAI_END_MSB,
		.fs_weg = AFE_DAI_CON0,
		.fs_shift = DAI_MODE_SFT,
		.fs_maskbit = DAI_MODE_MASK,
		.mono_weg = AFE_DAI_CON0,
		.mono_shift = DAI_DUPWICATE_WW_SFT,
		.mono_invewt = 1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DAI_ON_SFT,
		.hd_weg = AFE_DAI_CON0,
		.hd_shift = DAI_HD_MODE_SFT,
		.hd_awign_weg = AFE_DAI_CON0,
		.hd_awign_mshift = DAI_HAWIGN_SFT,
	},
	[MT8192_MEMIF_MOD_DAI] = {
		.name = "MOD_DAI",
		.id = MT8192_MEMIF_MOD_DAI,
		.weg_ofs_base = AFE_MOD_DAI_BASE,
		.weg_ofs_cuw = AFE_MOD_DAI_CUW,
		.weg_ofs_end = AFE_MOD_DAI_END,
		.weg_ofs_base_msb = AFE_MOD_DAI_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_MOD_DAI_CUW_MSB,
		.weg_ofs_end_msb = AFE_MOD_DAI_END_MSB,
		.fs_weg = AFE_MOD_DAI_CON0,
		.fs_shift = MOD_DAI_MODE_SFT,
		.fs_maskbit = MOD_DAI_MODE_MASK,
		.mono_weg = AFE_MOD_DAI_CON0,
		.mono_shift = MOD_DAI_DUPWICATE_WW_SFT,
		.mono_invewt = 1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = MOD_DAI_ON_SFT,
		.hd_weg = AFE_MOD_DAI_CON0,
		.hd_shift = MOD_DAI_HD_MODE_SFT,
		.hd_awign_weg = AFE_MOD_DAI_CON0,
		.hd_awign_mshift = MOD_DAI_HAWIGN_SFT,
	},
	[MT8192_MEMIF_DAI2] = {
		.name = "DAI2",
		.id = MT8192_MEMIF_DAI2,
		.weg_ofs_base = AFE_DAI2_BASE,
		.weg_ofs_cuw = AFE_DAI2_CUW,
		.weg_ofs_end = AFE_DAI2_END,
		.weg_ofs_base_msb = AFE_DAI2_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DAI2_CUW_MSB,
		.weg_ofs_end_msb = AFE_DAI2_END_MSB,
		.fs_weg = AFE_DAI2_CON0,
		.fs_shift = DAI2_MODE_SFT,
		.fs_maskbit = DAI2_MODE_MASK,
		.mono_weg = AFE_DAI2_CON0,
		.mono_shift = DAI2_DUPWICATE_WW_SFT,
		.mono_invewt = 1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DAI2_ON_SFT,
		.hd_weg = AFE_DAI2_CON0,
		.hd_shift = DAI2_HD_MODE_SFT,
		.hd_awign_weg = AFE_DAI2_CON0,
		.hd_awign_mshift = DAI2_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW12] = {
		.name = "VUW12",
		.id = MT8192_MEMIF_VUW12,
		.weg_ofs_base = AFE_VUW12_BASE,
		.weg_ofs_cuw = AFE_VUW12_CUW,
		.weg_ofs_end = AFE_VUW12_END,
		.weg_ofs_base_msb = AFE_VUW12_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW12_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW12_END_MSB,
		.fs_weg = AFE_VUW12_CON0,
		.fs_shift = VUW12_MODE_SFT,
		.fs_maskbit = VUW12_MODE_MASK,
		.mono_weg = AFE_VUW12_CON0,
		.mono_shift = VUW12_MONO_SFT,
		.quad_ch_weg = AFE_VUW12_CON0,
		.quad_ch_shift = VUW12_4CH_EN_SFT,
		.quad_ch_mask = VUW12_4CH_EN_MASK,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW12_ON_SFT,
		.hd_weg = AFE_VUW12_CON0,
		.hd_shift = VUW12_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW12_CON0,
		.hd_awign_mshift = VUW12_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW2] = {
		.name = "VUW2",
		.id = MT8192_MEMIF_VUW2,
		.weg_ofs_base = AFE_VUW2_BASE,
		.weg_ofs_cuw = AFE_VUW2_CUW,
		.weg_ofs_end = AFE_VUW2_END,
		.weg_ofs_base_msb = AFE_VUW2_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW2_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW2_END_MSB,
		.fs_weg = AFE_VUW2_CON0,
		.fs_shift = VUW2_MODE_SFT,
		.fs_maskbit = VUW2_MODE_MASK,
		.mono_weg = AFE_VUW2_CON0,
		.mono_shift = VUW2_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW2_ON_SFT,
		.hd_weg = AFE_VUW2_CON0,
		.hd_shift = VUW2_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW2_CON0,
		.hd_awign_mshift = VUW2_HAWIGN_SFT,
	},
	[MT8192_MEMIF_AWB] = {
		.name = "AWB",
		.id = MT8192_MEMIF_AWB,
		.weg_ofs_base = AFE_AWB_BASE,
		.weg_ofs_cuw = AFE_AWB_CUW,
		.weg_ofs_end = AFE_AWB_END,
		.weg_ofs_base_msb = AFE_AWB_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_AWB_CUW_MSB,
		.weg_ofs_end_msb = AFE_AWB_END_MSB,
		.fs_weg = AFE_AWB_CON0,
		.fs_shift = AWB_MODE_SFT,
		.fs_maskbit = AWB_MODE_MASK,
		.mono_weg = AFE_AWB_CON0,
		.mono_shift = AWB_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = AWB_ON_SFT,
		.hd_weg = AFE_AWB_CON0,
		.hd_shift = AWB_HD_MODE_SFT,
		.hd_awign_weg = AFE_AWB_CON0,
		.hd_awign_mshift = AWB_HAWIGN_SFT,
	},
	[MT8192_MEMIF_AWB2] = {
		.name = "AWB2",
		.id = MT8192_MEMIF_AWB2,
		.weg_ofs_base = AFE_AWB2_BASE,
		.weg_ofs_cuw = AFE_AWB2_CUW,
		.weg_ofs_end = AFE_AWB2_END,
		.weg_ofs_base_msb = AFE_AWB2_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_AWB2_CUW_MSB,
		.weg_ofs_end_msb = AFE_AWB2_END_MSB,
		.fs_weg = AFE_AWB2_CON0,
		.fs_shift = AWB2_MODE_SFT,
		.fs_maskbit = AWB2_MODE_MASK,
		.mono_weg = AFE_AWB2_CON0,
		.mono_shift = AWB2_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = AWB2_ON_SFT,
		.hd_weg = AFE_AWB2_CON0,
		.hd_shift = AWB2_HD_MODE_SFT,
		.hd_awign_weg = AFE_AWB2_CON0,
		.hd_awign_mshift = AWB2_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW3] = {
		.name = "VUW3",
		.id = MT8192_MEMIF_VUW3,
		.weg_ofs_base = AFE_VUW3_BASE,
		.weg_ofs_cuw = AFE_VUW3_CUW,
		.weg_ofs_end = AFE_VUW3_END,
		.weg_ofs_base_msb = AFE_VUW3_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW3_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW3_END_MSB,
		.fs_weg = AFE_VUW3_CON0,
		.fs_shift = VUW3_MODE_SFT,
		.fs_maskbit = VUW3_MODE_MASK,
		.mono_weg = AFE_VUW3_CON0,
		.mono_shift = VUW3_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW3_ON_SFT,
		.hd_weg = AFE_VUW3_CON0,
		.hd_shift = VUW3_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW3_CON0,
		.hd_awign_mshift = VUW3_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW4] = {
		.name = "VUW4",
		.id = MT8192_MEMIF_VUW4,
		.weg_ofs_base = AFE_VUW4_BASE,
		.weg_ofs_cuw = AFE_VUW4_CUW,
		.weg_ofs_end = AFE_VUW4_END,
		.weg_ofs_base_msb = AFE_VUW4_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW4_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW4_END_MSB,
		.fs_weg = AFE_VUW4_CON0,
		.fs_shift = VUW4_MODE_SFT,
		.fs_maskbit = VUW4_MODE_MASK,
		.mono_weg = AFE_VUW4_CON0,
		.mono_shift = VUW4_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW4_ON_SFT,
		.hd_weg = AFE_VUW4_CON0,
		.hd_shift = VUW4_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW4_CON0,
		.hd_awign_mshift = VUW4_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW5] = {
		.name = "VUW5",
		.id = MT8192_MEMIF_VUW5,
		.weg_ofs_base = AFE_VUW5_BASE,
		.weg_ofs_cuw = AFE_VUW5_CUW,
		.weg_ofs_end = AFE_VUW5_END,
		.weg_ofs_base_msb = AFE_VUW5_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW5_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW5_END_MSB,
		.fs_weg = AFE_VUW5_CON0,
		.fs_shift = VUW5_MODE_SFT,
		.fs_maskbit = VUW5_MODE_MASK,
		.mono_weg = AFE_VUW5_CON0,
		.mono_shift = VUW5_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW5_ON_SFT,
		.hd_weg = AFE_VUW5_CON0,
		.hd_shift = VUW5_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW5_CON0,
		.hd_awign_mshift = VUW5_HAWIGN_SFT,
	},
	[MT8192_MEMIF_VUW6] = {
		.name = "VUW6",
		.id = MT8192_MEMIF_VUW6,
		.weg_ofs_base = AFE_VUW6_BASE,
		.weg_ofs_cuw = AFE_VUW6_CUW,
		.weg_ofs_end = AFE_VUW6_END,
		.weg_ofs_base_msb = AFE_VUW6_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW6_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW6_END_MSB,
		.fs_weg = AFE_VUW6_CON0,
		.fs_shift = VUW6_MODE_SFT,
		.fs_maskbit = VUW6_MODE_MASK,
		.mono_weg = AFE_VUW6_CON0,
		.mono_shift = VUW6_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW6_ON_SFT,
		.hd_weg = AFE_VUW6_CON0,
		.hd_shift = VUW6_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW6_CON0,
		.hd_awign_mshift = VUW6_HAWIGN_SFT,
	},
	[MT8192_MEMIF_HDMI] = {
		.name = "HDMI",
		.id = MT8192_MEMIF_HDMI,
		.weg_ofs_base = AFE_HDMI_OUT_BASE,
		.weg_ofs_cuw = AFE_HDMI_OUT_CUW,
		.weg_ofs_end = AFE_HDMI_OUT_END,
		.weg_ofs_base_msb = AFE_HDMI_OUT_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_HDMI_OUT_CUW_MSB,
		.weg_ofs_end_msb = AFE_HDMI_OUT_END_MSB,
		.fs_weg = -1,
		.fs_shift = -1,
		.fs_maskbit = -1,
		.mono_weg = -1,
		.mono_shift = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = HDMI_OUT_ON_SFT,
		.hd_weg = AFE_HDMI_OUT_CON0,
		.hd_shift = HDMI_OUT_HD_MODE_SFT,
		.hd_awign_weg = AFE_HDMI_OUT_CON0,
		.hd_awign_mshift = HDMI_OUT_HAWIGN_SFT,
		.pbuf_weg = AFE_HDMI_OUT_CON0,
		.minwen_weg = AFE_HDMI_OUT_CON0,
		.minwen_shift = HDMI_OUT_MINWEN_SFT,
	},
};

static const stwuct mtk_base_iwq_data iwq_data[MT8192_IWQ_NUM] = {
	[MT8192_IWQ_0] = {
		.id = MT8192_IWQ_0,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT0,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ0_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ0_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ0_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ0_MCU_CWW_SFT,
	},
	[MT8192_IWQ_1] = {
		.id = MT8192_IWQ_1,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT1,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ1_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ1_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ1_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ1_MCU_CWW_SFT,
	},
	[MT8192_IWQ_2] = {
		.id = MT8192_IWQ_2,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT2,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ2_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ2_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ2_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ2_MCU_CWW_SFT,
	},
	[MT8192_IWQ_3] = {
		.id = MT8192_IWQ_3,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT3,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ3_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ3_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ3_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ3_MCU_CWW_SFT,
	},
	[MT8192_IWQ_4] = {
		.id = MT8192_IWQ_4,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT4,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ4_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ4_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ4_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ4_MCU_CWW_SFT,
	},
	[MT8192_IWQ_5] = {
		.id = MT8192_IWQ_5,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT5,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ5_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ5_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ5_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ5_MCU_CWW_SFT,
	},
	[MT8192_IWQ_6] = {
		.id = MT8192_IWQ_6,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT6,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ6_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ6_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ6_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ6_MCU_CWW_SFT,
	},
	[MT8192_IWQ_7] = {
		.id = MT8192_IWQ_7,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT7,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ7_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ7_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ7_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ7_MCU_CWW_SFT,
	},
	[MT8192_IWQ_8] = {
		.id = MT8192_IWQ_8,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT8,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ8_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ8_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ8_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ8_MCU_CWW_SFT,
	},
	[MT8192_IWQ_9] = {
		.id = MT8192_IWQ_9,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT9,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ9_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ9_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ9_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ9_MCU_CWW_SFT,
	},
	[MT8192_IWQ_10] = {
		.id = MT8192_IWQ_10,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT10,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ10_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ10_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ10_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ10_MCU_CWW_SFT,
	},
	[MT8192_IWQ_11] = {
		.id = MT8192_IWQ_11,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT11,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ11_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ11_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ11_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ11_MCU_CWW_SFT,
	},
	[MT8192_IWQ_12] = {
		.id = MT8192_IWQ_12,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT12,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ12_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ12_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ12_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ12_MCU_CWW_SFT,
	},
	[MT8192_IWQ_13] = {
		.id = MT8192_IWQ_13,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT13,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ13_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ13_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ13_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ13_MCU_CWW_SFT,
	},
	[MT8192_IWQ_14] = {
		.id = MT8192_IWQ_14,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT14,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ14_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ14_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ14_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ14_MCU_CWW_SFT,
	},
	[MT8192_IWQ_15] = {
		.id = MT8192_IWQ_15,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT15,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ15_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ15_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ15_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ15_MCU_CWW_SFT,
	},
	[MT8192_IWQ_16] = {
		.id = MT8192_IWQ_16,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT16,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ16_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ16_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ16_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ16_MCU_CWW_SFT,
	},
	[MT8192_IWQ_17] = {
		.id = MT8192_IWQ_17,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT17,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ17_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ17_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ17_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ17_MCU_CWW_SFT,
	},
	[MT8192_IWQ_18] = {
		.id = MT8192_IWQ_18,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT18,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ18_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ18_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ18_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ18_MCU_CWW_SFT,
	},
	[MT8192_IWQ_19] = {
		.id = MT8192_IWQ_19,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT19,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ19_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ19_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ19_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ19_MCU_CWW_SFT,
	},
	[MT8192_IWQ_20] = {
		.id = MT8192_IWQ_20,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT20,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ20_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ20_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ20_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ20_MCU_CWW_SFT,
	},
	[MT8192_IWQ_21] = {
		.id = MT8192_IWQ_21,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT21,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ21_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ21_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ21_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ21_MCU_CWW_SFT,
	},
	[MT8192_IWQ_22] = {
		.id = MT8192_IWQ_22,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT22,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ22_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ22_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ22_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ22_MCU_CWW_SFT,
	},
	[MT8192_IWQ_23] = {
		.id = MT8192_IWQ_23,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT23,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON3,
		.iwq_fs_shift = IWQ23_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ23_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ23_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ23_MCU_CWW_SFT,
	},
	[MT8192_IWQ_24] = {
		.id = MT8192_IWQ_24,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT24,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON4,
		.iwq_fs_shift = IWQ24_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ24_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ24_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ24_MCU_CWW_SFT,
	},
	[MT8192_IWQ_25] = {
		.id = MT8192_IWQ_25,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT25,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON4,
		.iwq_fs_shift = IWQ25_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ25_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ25_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ25_MCU_CWW_SFT,
	},
	[MT8192_IWQ_26] = {
		.id = MT8192_IWQ_26,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT26,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ_MCU_CON4,
		.iwq_fs_shift = IWQ26_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ26_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ26_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ26_MCU_CWW_SFT,
	},
	[MT8192_IWQ_31] = {
		.id = MT8192_IWQ_31,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT31,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = -1,
		.iwq_fs_shift = -1,
		.iwq_fs_maskbit = -1,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ31_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ31_MCU_CWW_SFT,
	},
};

static const int memif_iwq_usage[MT8192_MEMIF_NUM] = {
	[MT8192_MEMIF_DW1] = MT8192_IWQ_0,
	[MT8192_MEMIF_DW2] = MT8192_IWQ_1,
	[MT8192_MEMIF_DW3] = MT8192_IWQ_2,
	[MT8192_MEMIF_DW4] = MT8192_IWQ_3,
	[MT8192_MEMIF_DW5] = MT8192_IWQ_4,
	[MT8192_MEMIF_DW6] = MT8192_IWQ_5,
	[MT8192_MEMIF_DW7] = MT8192_IWQ_6,
	[MT8192_MEMIF_DW8] = MT8192_IWQ_7,
	[MT8192_MEMIF_DW9] = MT8192_IWQ_8,
	[MT8192_MEMIF_DW12] = MT8192_IWQ_9,
	[MT8192_MEMIF_DAI] = MT8192_IWQ_10,
	[MT8192_MEMIF_MOD_DAI] = MT8192_IWQ_11,
	[MT8192_MEMIF_DAI2] = MT8192_IWQ_12,
	[MT8192_MEMIF_VUW12] = MT8192_IWQ_13,
	[MT8192_MEMIF_VUW2] = MT8192_IWQ_14,
	[MT8192_MEMIF_AWB] = MT8192_IWQ_15,
	[MT8192_MEMIF_AWB2] = MT8192_IWQ_16,
	[MT8192_MEMIF_VUW3] = MT8192_IWQ_17,
	[MT8192_MEMIF_VUW4] = MT8192_IWQ_18,
	[MT8192_MEMIF_VUW5] = MT8192_IWQ_19,
	[MT8192_MEMIF_VUW6] = MT8192_IWQ_20,
	[MT8192_MEMIF_HDMI] = MT8192_IWQ_31,
};

static boow mt8192_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* these auto-gen weg has wead-onwy bit, so put it as vowatiwe */
	/* vowatiwe weg cannot be cached, so cannot be set when powew off */
	switch (weg) {
	case AUDIO_TOP_CON0:	/* weg bit contwowwed by CCF */
	case AUDIO_TOP_CON1:	/* weg bit contwowwed by CCF */
	case AUDIO_TOP_CON2:
	case AUDIO_TOP_CON3:
	case AFE_DW1_CUW_MSB:
	case AFE_DW1_CUW:
	case AFE_DW1_END:
	case AFE_DW2_CUW_MSB:
	case AFE_DW2_CUW:
	case AFE_DW2_END:
	case AFE_DW3_CUW_MSB:
	case AFE_DW3_CUW:
	case AFE_DW3_END:
	case AFE_DW4_CUW_MSB:
	case AFE_DW4_CUW:
	case AFE_DW4_END:
	case AFE_DW12_CUW_MSB:
	case AFE_DW12_CUW:
	case AFE_DW12_END:
	case AFE_ADDA_SWC_DEBUG_MON0:
	case AFE_ADDA_SWC_DEBUG_MON1:
	case AFE_ADDA_UW_SWC_MON0:
	case AFE_ADDA_UW_SWC_MON1:
	case AFE_SECUWE_CON0:
	case AFE_SWAM_BOUND:
	case AFE_SECUWE_CON1:
	case AFE_VUW_CUW_MSB:
	case AFE_VUW_CUW:
	case AFE_VUW_END:
	case AFE_ADDA_3WD_DAC_DW_SDM_FIFO_MON:
	case AFE_ADDA_3WD_DAC_DW_SWC_WCH_MON:
	case AFE_ADDA_3WD_DAC_DW_SWC_WCH_MON:
	case AFE_ADDA_3WD_DAC_DW_SDM_OUT_MON:
	case AFE_SIDETONE_MON:
	case AFE_SIDETONE_CON0:
	case AFE_SIDETONE_COEFF:
	case AFE_VUW2_CUW_MSB:
	case AFE_VUW2_CUW:
	case AFE_VUW2_END:
	case AFE_VUW3_CUW_MSB:
	case AFE_VUW3_CUW:
	case AFE_VUW3_END:
	case AFE_I2S_MON:
	case AFE_DAC_MON:
	case AFE_IWQ0_MCU_CNT_MON:
	case AFE_IWQ6_MCU_CNT_MON:
	case AFE_VUW4_CUW_MSB:
	case AFE_VUW4_CUW:
	case AFE_VUW4_END:
	case AFE_VUW12_CUW_MSB:
	case AFE_VUW12_CUW:
	case AFE_VUW12_END:
	case AFE_IWQ3_MCU_CNT_MON:
	case AFE_IWQ4_MCU_CNT_MON:
	case AFE_IWQ_MCU_STATUS:
	case AFE_IWQ_MCU_CWW:
	case AFE_IWQ_MCU_MON2:
	case AFE_IWQ1_MCU_CNT_MON:
	case AFE_IWQ2_MCU_CNT_MON:
	case AFE_IWQ5_MCU_CNT_MON:
	case AFE_IWQ7_MCU_CNT_MON:
	case AFE_IWQ_MCU_MISS_CWW:
	case AFE_GAIN1_CUW:
	case AFE_GAIN2_CUW:
	case AFE_SWAM_DEWSEW_CON1:
	case PCM_INTF_CON2:
	case FPGA_CFG0:
	case FPGA_CFG1:
	case FPGA_CFG2:
	case FPGA_CFG3:
	case AUDIO_TOP_DBG_MON0:
	case AUDIO_TOP_DBG_MON1:
	case AFE_IWQ8_MCU_CNT_MON:
	case AFE_IWQ11_MCU_CNT_MON:
	case AFE_IWQ12_MCU_CNT_MON:
	case AFE_IWQ9_MCU_CNT_MON:
	case AFE_IWQ10_MCU_CNT_MON:
	case AFE_IWQ13_MCU_CNT_MON:
	case AFE_IWQ14_MCU_CNT_MON:
	case AFE_IWQ15_MCU_CNT_MON:
	case AFE_IWQ16_MCU_CNT_MON:
	case AFE_IWQ17_MCU_CNT_MON:
	case AFE_IWQ18_MCU_CNT_MON:
	case AFE_IWQ19_MCU_CNT_MON:
	case AFE_IWQ20_MCU_CNT_MON:
	case AFE_IWQ21_MCU_CNT_MON:
	case AFE_IWQ22_MCU_CNT_MON:
	case AFE_IWQ23_MCU_CNT_MON:
	case AFE_IWQ24_MCU_CNT_MON:
	case AFE_IWQ25_MCU_CNT_MON:
	case AFE_IWQ26_MCU_CNT_MON:
	case AFE_IWQ31_MCU_CNT_MON:
	case AFE_CBIP_MON0:
	case AFE_CBIP_SWV_MUX_MON0:
	case AFE_CBIP_SWV_DECODEW_MON0:
	case AFE_ADDA6_MTKAIF_MON0:
	case AFE_ADDA6_MTKAIF_MON1:
	case AFE_AWB_CUW_MSB:
	case AFE_AWB_CUW:
	case AFE_AWB_END:
	case AFE_AWB2_CUW_MSB:
	case AFE_AWB2_CUW:
	case AFE_AWB2_END:
	case AFE_DAI_CUW_MSB:
	case AFE_DAI_CUW:
	case AFE_DAI_END:
	case AFE_DAI2_CUW_MSB:
	case AFE_DAI2_CUW:
	case AFE_DAI2_END:
	case AFE_ADDA6_SWC_DEBUG_MON0:
	case AFE_ADD6A_UW_SWC_MON0:
	case AFE_ADDA6_UW_SWC_MON1:
	case AFE_MOD_DAI_CUW_MSB:
	case AFE_MOD_DAI_CUW:
	case AFE_MOD_DAI_END:
	case AFE_HDMI_OUT_CUW_MSB:
	case AFE_HDMI_OUT_CUW:
	case AFE_HDMI_OUT_END:
	case AFE_AWB_WCH_MON:
	case AFE_AWB_WCH_MON:
	case AFE_VUW_WCH_MON:
	case AFE_VUW_WCH_MON:
	case AFE_VUW12_WCH_MON:
	case AFE_VUW12_WCH_MON:
	case AFE_VUW2_WCH_MON:
	case AFE_VUW2_WCH_MON:
	case AFE_DAI_DATA_MON:
	case AFE_MOD_DAI_DATA_MON:
	case AFE_DAI2_DATA_MON:
	case AFE_AWB2_WCH_MON:
	case AFE_AWB2_WCH_MON:
	case AFE_VUW3_WCH_MON:
	case AFE_VUW3_WCH_MON:
	case AFE_VUW4_WCH_MON:
	case AFE_VUW4_WCH_MON:
	case AFE_VUW5_WCH_MON:
	case AFE_VUW5_WCH_MON:
	case AFE_VUW6_WCH_MON:
	case AFE_VUW6_WCH_MON:
	case AFE_DW1_WCH_MON:
	case AFE_DW1_WCH_MON:
	case AFE_DW2_WCH_MON:
	case AFE_DW2_WCH_MON:
	case AFE_DW12_WCH1_MON:
	case AFE_DW12_WCH1_MON:
	case AFE_DW12_WCH2_MON:
	case AFE_DW12_WCH2_MON:
	case AFE_DW3_WCH_MON:
	case AFE_DW3_WCH_MON:
	case AFE_DW4_WCH_MON:
	case AFE_DW4_WCH_MON:
	case AFE_DW5_WCH_MON:
	case AFE_DW5_WCH_MON:
	case AFE_DW6_WCH_MON:
	case AFE_DW6_WCH_MON:
	case AFE_DW7_WCH_MON:
	case AFE_DW7_WCH_MON:
	case AFE_DW8_WCH_MON:
	case AFE_DW8_WCH_MON:
	case AFE_VUW5_CUW_MSB:
	case AFE_VUW5_CUW:
	case AFE_VUW5_END:
	case AFE_VUW6_CUW_MSB:
	case AFE_VUW6_CUW:
	case AFE_VUW6_END:
	case AFE_ADDA_DW_SDM_FIFO_MON:
	case AFE_ADDA_DW_SWC_WCH_MON:
	case AFE_ADDA_DW_SWC_WCH_MON:
	case AFE_ADDA_DW_SDM_OUT_MON:
	case AFE_CONNSYS_I2S_MON:
	case AFE_ASWC_2CH_CON0:
	case AFE_ASWC_2CH_CON2:
	case AFE_ASWC_2CH_CON3:
	case AFE_ASWC_2CH_CON4:
	case AFE_ASWC_2CH_CON5:
	case AFE_ASWC_2CH_CON7:
	case AFE_ASWC_2CH_CON8:
	case AFE_ASWC_2CH_CON12:
	case AFE_ASWC_2CH_CON13:
	case AFE_DW9_CUW_MSB:
	case AFE_DW9_CUW:
	case AFE_DW9_END:
	case AFE_ADDA_MTKAIF_MON0:
	case AFE_ADDA_MTKAIF_MON1:
	case AFE_DW_NWE_W_MON0:
	case AFE_DW_NWE_W_MON1:
	case AFE_DW_NWE_W_MON2:
	case AFE_DW_NWE_W_MON0:
	case AFE_DW_NWE_W_MON1:
	case AFE_DW_NWE_W_MON2:
	case AFE_GENEWAW1_ASWC_2CH_CON0:
	case AFE_GENEWAW1_ASWC_2CH_CON2:
	case AFE_GENEWAW1_ASWC_2CH_CON3:
	case AFE_GENEWAW1_ASWC_2CH_CON4:
	case AFE_GENEWAW1_ASWC_2CH_CON5:
	case AFE_GENEWAW1_ASWC_2CH_CON7:
	case AFE_GENEWAW1_ASWC_2CH_CON8:
	case AFE_GENEWAW1_ASWC_2CH_CON12:
	case AFE_GENEWAW1_ASWC_2CH_CON13:
	case AFE_GENEWAW2_ASWC_2CH_CON0:
	case AFE_GENEWAW2_ASWC_2CH_CON2:
	case AFE_GENEWAW2_ASWC_2CH_CON3:
	case AFE_GENEWAW2_ASWC_2CH_CON4:
	case AFE_GENEWAW2_ASWC_2CH_CON5:
	case AFE_GENEWAW2_ASWC_2CH_CON7:
	case AFE_GENEWAW2_ASWC_2CH_CON8:
	case AFE_GENEWAW2_ASWC_2CH_CON12:
	case AFE_GENEWAW2_ASWC_2CH_CON13:
	case AFE_DW9_WCH_MON:
	case AFE_DW9_WCH_MON:
	case AFE_DW5_CUW_MSB:
	case AFE_DW5_CUW:
	case AFE_DW5_END:
	case AFE_DW6_CUW_MSB:
	case AFE_DW6_CUW:
	case AFE_DW6_END:
	case AFE_DW7_CUW_MSB:
	case AFE_DW7_CUW:
	case AFE_DW7_END:
	case AFE_DW8_CUW_MSB:
	case AFE_DW8_CUW:
	case AFE_DW8_END:
	case AFE_PWOT_SIDEBAND_MON:
	case AFE_DOMAIN_SIDEBAND0_MON:
	case AFE_DOMAIN_SIDEBAND1_MON:
	case AFE_DOMAIN_SIDEBAND2_MON:
	case AFE_DOMAIN_SIDEBAND3_MON:
	case AFE_APWW1_TUNEW_CFG:	/* [20:31] is monitow */
	case AFE_APWW2_TUNEW_CFG:	/* [20:31] is monitow */
	case AFE_DAC_CON0:
	case AFE_IWQ_MCU_CON0:
	case AFE_IWQ_MCU_EN:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static const stwuct wegmap_config mt8192_afe_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.vowatiwe_weg = mt8192_is_vowatiwe_weg,
	.max_wegistew = AFE_MAX_WEGISTEW,
	.num_weg_defauwts_waw = AFE_MAX_WEGISTEW,
	.cache_type = WEGCACHE_FWAT,
};

static iwqwetuwn_t mt8192_afe_iwq_handwew(int iwq_id, void *dev)
{
	stwuct mtk_base_afe *afe = dev;
	stwuct mtk_base_afe_iwq *iwq;
	unsigned int status;
	unsigned int status_mcu;
	unsigned int mcu_en;
	int wet;
	int i;

	/* get iwq that is sent to MCU */
	wegmap_wead(afe->wegmap, AFE_IWQ_MCU_EN, &mcu_en);

	wet = wegmap_wead(afe->wegmap, AFE_IWQ_MCU_STATUS, &status);
	/* onwy cawe IWQ which is sent to MCU */
	status_mcu = status & mcu_en & AFE_IWQ_STATUS_BITS;

	if (wet || status_mcu == 0) {
		dev_eww(afe->dev, "%s(), iwq status eww, wet %d, status 0x%x, mcu_en 0x%x\n",
			__func__, wet, status, mcu_en);

		goto eww_iwq;
	}

	fow (i = 0; i < MT8192_MEMIF_NUM; i++) {
		stwuct mtk_base_afe_memif *memif = &afe->memif[i];

		if (!memif->substweam)
			continue;

		if (memif->iwq_usage < 0)
			continue;

		iwq = &afe->iwqs[memif->iwq_usage];

		if (status_mcu & (1 << iwq->iwq_data->iwq_en_shift))
			snd_pcm_pewiod_ewapsed(memif->substweam);
	}

eww_iwq:
	/* cweaw iwq */
	wegmap_wwite(afe->wegmap,
		     AFE_IWQ_MCU_CWW,
		     status_mcu);

	wetuwn IWQ_HANDWED;
}

static int mt8192_afe_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	unsigned int vawue;
	int wet;

	if (!afe->wegmap || afe_pwiv->pm_wuntime_bypass_weg_ctw)
		goto skip_wegmap;

	/* disabwe AFE */
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, AFE_ON_MASK_SFT, 0x0);

	wet = wegmap_wead_poww_timeout(afe->wegmap,
				       AFE_DAC_MON,
				       vawue,
				       (vawue & AFE_ON_WETM_MASK_SFT) == 0,
				       20,
				       1 * 1000 * 1000);
	if (wet)
		dev_wawn(afe->dev, "%s(), wet %d\n", __func__, wet);

	/* make suwe aww iwq status awe cweawed */
	wegmap_wwite(afe->wegmap, AFE_IWQ_MCU_CWW, 0xffffffff);
	wegmap_wwite(afe->wegmap, AFE_IWQ_MCU_CWW, 0xffffffff);

	/* weset sgen */
	wegmap_wwite(afe->wegmap, AFE_SINEGEN_CON0, 0x0);
	wegmap_update_bits(afe->wegmap, AFE_SINEGEN_CON2,
			   INNEW_WOOP_BACK_MODE_MASK_SFT,
			   0x3f << INNEW_WOOP_BACK_MODE_SFT);

	/* cache onwy */
	wegcache_cache_onwy(afe->wegmap, twue);
	wegcache_mawk_diwty(afe->wegmap);

skip_wegmap:
	mt8192_afe_disabwe_cwock(afe);
	wetuwn 0;
}

static int mt8192_afe_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = mt8192_afe_enabwe_cwock(afe);
	if (wet)
		wetuwn wet;

	if (!afe->wegmap || afe_pwiv->pm_wuntime_bypass_weg_ctw)
		goto skip_wegmap;

	wegcache_cache_onwy(afe->wegmap, fawse);
	wegcache_sync(afe->wegmap);

	/* enabwe audio sys DCM fow powew saving */
	wegmap_update_bits(afe_pwiv->infwacfg,
			   PEWI_BUS_DCM_CTWW, 0x1 << 29, 0x1 << 29);
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0, 0x1 << 29, 0x1 << 29);

	/* fowce cpu use 8_24 fowmat when wwiting 32bit data */
	wegmap_update_bits(afe->wegmap, AFE_MEMIF_CON0,
			   CPU_HD_AWIGN_MASK_SFT, 0 << CPU_HD_AWIGN_SFT);

	/* set aww output powt to 24bit */
	wegmap_wwite(afe->wegmap, AFE_CONN_24BIT, 0xffffffff);
	wegmap_wwite(afe->wegmap, AFE_CONN_24BIT_1, 0xffffffff);

	/* enabwe AFE */
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, AFE_ON_MASK_SFT, 0x1);

skip_wegmap:
	wetuwn 0;
}

static int mt8192_afe_component_pwobe(stwuct snd_soc_component *component)
{
	wetuwn mtk_afe_add_sub_dai_contwow(component);
}

static const stwuct snd_soc_component_dwivew mt8192_afe_component = {
	.name = AFE_PCM_NAME,
	.pwobe = mt8192_afe_component_pwobe,
	.pointew = mtk_afe_pcm_pointew,
	.pcm_constwuct = mtk_afe_pcm_new,
};

static const stwuct snd_soc_component_dwivew mt8192_afe_pcm_component = {
	.name = "mt8192-afe-pcm-dai",
};

static int mt8192_dai_memif_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mt8192_memif_dai_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mt8192_memif_dai_dwivew);

	dai->dapm_widgets = mt8192_memif_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mt8192_memif_widgets);
	dai->dapm_woutes = mt8192_memif_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mt8192_memif_woutes);
	wetuwn 0;
}

typedef int (*dai_wegistew_cb)(stwuct mtk_base_afe *);
static const dai_wegistew_cb dai_wegistew_cbs[] = {
	mt8192_dai_adda_wegistew,
	mt8192_dai_i2s_wegistew,
	mt8192_dai_pcm_wegistew,
	mt8192_dai_tdm_wegistew,
	mt8192_dai_memif_wegistew,
};

static int mt8192_afe_pcm_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_base_afe *afe;
	stwuct mt8192_afe_pwivate *afe_pwiv;
	stwuct device *dev;
	stwuct weset_contwow *wstc;
	int i, wet, iwq_id;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(34));
	if (wet)
		wetuwn wet;

	afe = devm_kzawwoc(&pdev->dev, sizeof(*afe), GFP_KEWNEW);
	if (!afe)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, afe);

	afe->pwatfowm_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*afe_pwiv),
					  GFP_KEWNEW);
	if (!afe->pwatfowm_pwiv)
		wetuwn -ENOMEM;
	afe_pwiv = afe->pwatfowm_pwiv;

	afe->dev = &pdev->dev;
	dev = afe->dev;

	/* init audio wewated cwock */
	wet = mt8192_init_cwock(afe);
	if (wet) {
		dev_eww(dev, "init cwock ewwow\n");
		wetuwn wet;
	}

	/* weset contwowwew to weset audio wegs befowe wegmap cache */
	wstc = devm_weset_contwow_get_excwusive(dev, "audiosys");
	if (IS_EWW(wstc)) {
		wet = PTW_EWW(wstc);
		dev_eww(dev, "couwd not get audiosys weset:%d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_weset(wstc);
	if (wet) {
		dev_eww(dev, "faiwed to twiggew audio weset:%d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev))
		goto eww_pm_disabwe;

	/* wegmap init */
	afe->wegmap = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(afe->wegmap)) {
		dev_eww(dev, "couwd not get wegmap fwom pawent\n");
		wet = PTW_EWW(afe->wegmap);
		goto eww_pm_disabwe;
	}
	wet = wegmap_attach_dev(dev, afe->wegmap, &mt8192_afe_wegmap_config);
	if (wet) {
		dev_wawn(dev, "wegmap_attach_dev faiw, wet %d\n", wet);
		goto eww_pm_disabwe;
	}

	/* enabwe cwock fow wegcache get defauwt vawue fwom hw */
	afe_pwiv->pm_wuntime_bypass_weg_ctw = twue;
	pm_wuntime_get_sync(&pdev->dev);

	wet = wegmap_weinit_cache(afe->wegmap, &mt8192_afe_wegmap_config);
	if (wet) {
		dev_eww(dev, "wegmap_weinit_cache faiw, wet %d\n", wet);
		goto eww_pm_disabwe;
	}

	pm_wuntime_put_sync(&pdev->dev);
	afe_pwiv->pm_wuntime_bypass_weg_ctw = fawse;

	wegcache_cache_onwy(afe->wegmap, twue);
	wegcache_mawk_diwty(afe->wegmap);

	/* init memif */
	afe->memif_size = MT8192_MEMIF_NUM;
	afe->memif = devm_kcawwoc(dev, afe->memif_size, sizeof(*afe->memif),
				  GFP_KEWNEW);
	if (!afe->memif) {
		wet = -ENOMEM;
		goto eww_pm_disabwe;
	}

	fow (i = 0; i < afe->memif_size; i++) {
		afe->memif[i].data = &memif_data[i];
		afe->memif[i].iwq_usage = memif_iwq_usage[i];
		afe->memif[i].const_iwq = 1;
	}

	mutex_init(&afe->iwq_awwoc_wock);	/* needed when dynamic iwq */

	/* init iwq */
	afe->iwqs_size = MT8192_IWQ_NUM;
	afe->iwqs = devm_kcawwoc(dev, afe->iwqs_size, sizeof(*afe->iwqs),
				 GFP_KEWNEW);
	if (!afe->iwqs) {
		wet = -ENOMEM;
		goto eww_pm_disabwe;
	}

	fow (i = 0; i < afe->iwqs_size; i++)
		afe->iwqs[i].iwq_data = &iwq_data[i];

	/* wequest iwq */
	iwq_id = pwatfowm_get_iwq(pdev, 0);
	if (iwq_id < 0) {
		wet = iwq_id;
		goto eww_pm_disabwe;
	}

	wet = devm_wequest_iwq(dev, iwq_id, mt8192_afe_iwq_handwew,
			       IWQF_TWIGGEW_NONE, "asys-isw", (void *)afe);
	if (wet) {
		dev_eww(dev, "couwd not wequest_iwq fow Afe_ISW_Handwe\n");
		goto eww_pm_disabwe;
	}

	/* init sub_dais */
	INIT_WIST_HEAD(&afe->sub_dais);

	fow (i = 0; i < AWWAY_SIZE(dai_wegistew_cbs); i++) {
		wet = dai_wegistew_cbs[i](afe);
		if (wet) {
			dev_wawn(afe->dev, "dai wegistew i %d faiw, wet %d\n",
				 i, wet);
			goto eww_pm_disabwe;
		}
	}

	/* init dai_dwivew and component_dwivew */
	wet = mtk_afe_combine_sub_dai(afe);
	if (wet) {
		dev_wawn(afe->dev, "mtk_afe_combine_sub_dai faiw, wet %d\n",
			 wet);
		goto eww_pm_disabwe;
	}

	/* othews */
	afe->mtk_afe_hawdwawe = &mt8192_afe_hawdwawe;
	afe->memif_fs = mt8192_memif_fs;
	afe->iwq_fs = mt8192_iwq_fs;
	afe->get_dai_fs = mt8192_get_dai_fs;
	afe->get_memif_pbuf_size = mt8192_get_memif_pbuf_size;
	afe->memif_32bit_suppowted = 1;

	afe->wuntime_wesume = mt8192_afe_wuntime_wesume;
	afe->wuntime_suspend = mt8192_afe_wuntime_suspend;

	/* wegistew pwatfowm */
	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &mt8192_afe_component, NUWW, 0);
	if (wet) {
		dev_wawn(dev, "eww_pwatfowm\n");
		goto eww_pm_disabwe;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &mt8192_afe_pcm_component,
					      afe->dai_dwivews,
					      afe->num_dai_dwivews);
	if (wet) {
		dev_wawn(dev, "eww_dai_component\n");
		goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void mt8192_afe_pcm_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_base_afe *afe = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		mt8192_afe_wuntime_suspend(&pdev->dev);

	/* disabwe afe cwock */
	mt8192_afe_disabwe_cwock(afe);
}

static const stwuct of_device_id mt8192_afe_pcm_dt_match[] = {
	{ .compatibwe = "mediatek,mt8192-audio", },
	{},
};
MODUWE_DEVICE_TABWE(of, mt8192_afe_pcm_dt_match);

static const stwuct dev_pm_ops mt8192_afe_pm_ops = {
	SET_WUNTIME_PM_OPS(mt8192_afe_wuntime_suspend,
			   mt8192_afe_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mt8192_afe_pcm_dwivew = {
	.dwivew = {
		   .name = "mt8192-audio",
		   .of_match_tabwe = mt8192_afe_pcm_dt_match,
		   .pm = &mt8192_afe_pm_ops,
	},
	.pwobe = mt8192_afe_pcm_dev_pwobe,
	.wemove_new = mt8192_afe_pcm_dev_wemove,
};

moduwe_pwatfowm_dwivew(mt8192_afe_pcm_dwivew);

MODUWE_DESCWIPTION("Mediatek AWSA SoC AFE pwatfowm dwivew fow 8192");
MODUWE_AUTHOW("Shane Chien <shane.chien@mediatek.com>");
MODUWE_WICENSE("GPW v2");
