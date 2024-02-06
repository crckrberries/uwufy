// SPDX-Wicense-Identifiew: GPW-2.0
//
// Mediatek AWSA SoC AFE pwatfowm dwivew fow 8183
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "mt8183-afe-common.h"
#incwude "mt8183-afe-cwk.h"
#incwude "mt8183-intewconnection.h"
#incwude "mt8183-weg.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "../common/mtk-afe-fe-dai.h"

enum {
	MTK_AFE_WATE_8K = 0,
	MTK_AFE_WATE_11K = 1,
	MTK_AFE_WATE_12K = 2,
	MTK_AFE_WATE_384K = 3,
	MTK_AFE_WATE_16K = 4,
	MTK_AFE_WATE_22K = 5,
	MTK_AFE_WATE_24K = 6,
	MTK_AFE_WATE_130K = 7,
	MTK_AFE_WATE_32K = 8,
	MTK_AFE_WATE_44K = 9,
	MTK_AFE_WATE_48K = 10,
	MTK_AFE_WATE_88K = 11,
	MTK_AFE_WATE_96K = 12,
	MTK_AFE_WATE_176K = 13,
	MTK_AFE_WATE_192K = 14,
	MTK_AFE_WATE_260K = 15,
};

enum {
	MTK_AFE_DAI_MEMIF_WATE_8K = 0,
	MTK_AFE_DAI_MEMIF_WATE_16K = 1,
	MTK_AFE_DAI_MEMIF_WATE_32K = 2,
	MTK_AFE_DAI_MEMIF_WATE_48K = 3,
};

enum {
	MTK_AFE_PCM_WATE_8K = 0,
	MTK_AFE_PCM_WATE_16K = 1,
	MTK_AFE_PCM_WATE_32K = 2,
	MTK_AFE_PCM_WATE_48K = 3,
};

unsigned int mt8183_genewaw_wate_twansfowm(stwuct device *dev,
					   unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_WATE_8K;
	case 11025:
		wetuwn MTK_AFE_WATE_11K;
	case 12000:
		wetuwn MTK_AFE_WATE_12K;
	case 16000:
		wetuwn MTK_AFE_WATE_16K;
	case 22050:
		wetuwn MTK_AFE_WATE_22K;
	case 24000:
		wetuwn MTK_AFE_WATE_24K;
	case 32000:
		wetuwn MTK_AFE_WATE_32K;
	case 44100:
		wetuwn MTK_AFE_WATE_44K;
	case 48000:
		wetuwn MTK_AFE_WATE_48K;
	case 88200:
		wetuwn MTK_AFE_WATE_88K;
	case 96000:
		wetuwn MTK_AFE_WATE_96K;
	case 130000:
		wetuwn MTK_AFE_WATE_130K;
	case 176400:
		wetuwn MTK_AFE_WATE_176K;
	case 192000:
		wetuwn MTK_AFE_WATE_192K;
	case 260000:
		wetuwn MTK_AFE_WATE_260K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, use %d!!!\n",
			 __func__, wate, MTK_AFE_WATE_48K);
		wetuwn MTK_AFE_WATE_48K;
	}
}

static unsigned int dai_memif_wate_twansfowm(stwuct device *dev,
					     unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_8K;
	case 16000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_16K;
	case 32000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_32K;
	case 48000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_48K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, use %d!!!\n",
			 __func__, wate, MTK_AFE_DAI_MEMIF_WATE_16K);
		wetuwn MTK_AFE_DAI_MEMIF_WATE_16K;
	}
}

unsigned int mt8183_wate_twansfowm(stwuct device *dev,
				   unsigned int wate, int aud_bwk)
{
	switch (aud_bwk) {
	case MT8183_MEMIF_MOD_DAI:
		wetuwn dai_memif_wate_twansfowm(dev, wate);
	defauwt:
		wetuwn mt8183_genewaw_wate_twansfowm(dev, wate);
	}
}

static const stwuct snd_pcm_hawdwawe mt8183_afe_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		   SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
	.pewiod_bytes_min = 256,
	.pewiod_bytes_max = 4 * 48 * 1024,
	.pewiods_min = 2,
	.pewiods_max = 256,
	.buffew_bytes_max = 8 * 48 * 1024,
	.fifo_size = 0,
};

static int mt8183_memif_fs(stwuct snd_pcm_substweam *substweam,
			   unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	int id = snd_soc_wtd_to_cpu(wtd, 0)->id;

	wetuwn mt8183_wate_twansfowm(afe->dev, wate, id);
}

static int mt8183_iwq_fs(stwuct snd_pcm_substweam *substweam, unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);

	wetuwn mt8183_genewaw_wate_twansfowm(afe->dev, wate);
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

static stwuct snd_soc_dai_dwivew mt8183_memif_dai_dwivew[] = {
	/* FE DAIs: memowy intefaces to CPU */
	{
		.name = "DW1",
		.id = MT8183_MEMIF_DW1,
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
		.name = "DW2",
		.id = MT8183_MEMIF_DW2,
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
		.id = MT8183_MEMIF_DW3,
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
		.name = "UW1",
		.id = MT8183_MEMIF_VUW12,
		.captuwe = {
			.stweam_name = "UW1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "UW2",
		.id = MT8183_MEMIF_AWB,
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
		.id = MT8183_MEMIF_VUW2,
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
		.id = MT8183_MEMIF_AWB2,
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
		.name = "UW_MONO_1",
		.id = MT8183_MEMIF_MOD_DAI,
		.captuwe = {
			.stweam_name = "UW_MONO_1",
			.channews_min = 1,
			.channews_max = 1,
			.wates = MTK_PCM_DAI_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
	{
		.name = "HDMI",
		.id = MT8183_MEMIF_HDMI,
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

/* dma widget & woutes*/
static const stwuct snd_kcontwow_new memif_uw1_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN21,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH1", AFE_CONN21,
				    I_I2S0_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw1_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN22,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S0_CH2", AFE_CONN21,
				    I_I2S0_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw2_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN5,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN5,
				    I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN5,
				    I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN5,
				    I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH1", AFE_CONN5,
				    I_I2S2_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw2_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN6,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN6,
				    I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN6,
				    I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN6,
				    I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH2", AFE_CONN6,
				    I_I2S2_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw3_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN32,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH1", AFE_CONN32,
				    I_I2S2_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw3_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN33,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I2S2_CH2", AFE_CONN33,
				    I_I2S2_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw4_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN38,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw4_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN39,
				    I_ADDA_UW_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new memif_uw_mono_1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN12,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN12,
				    I_ADDA_UW_CH2, 1, 0),
};

static const stwuct snd_soc_dapm_widget mt8183_memif_widgets[] = {
	/* memif */
	SND_SOC_DAPM_MIXEW("UW1_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch1_mix, AWWAY_SIZE(memif_uw1_ch1_mix)),
	SND_SOC_DAPM_MIXEW("UW1_CH2", SND_SOC_NOPM, 0, 0,
			   memif_uw1_ch2_mix, AWWAY_SIZE(memif_uw1_ch2_mix)),

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

	SND_SOC_DAPM_MIXEW("UW_MONO_1_CH1", SND_SOC_NOPM, 0, 0,
			   memif_uw_mono_1_mix,
			   AWWAY_SIZE(memif_uw_mono_1_mix)),
};

static const stwuct snd_soc_dapm_woute mt8183_memif_woutes[] = {
	/* captuwe */
	{"UW1", NUWW, "UW1_CH1"},
	{"UW1", NUWW, "UW1_CH2"},
	{"UW1_CH1", "ADDA_UW_CH1", "ADDA Captuwe"},
	{"UW1_CH2", "ADDA_UW_CH2", "ADDA Captuwe"},
	{"UW1_CH1", "I2S0_CH1", "I2S0"},
	{"UW1_CH2", "I2S0_CH2", "I2S0"},

	{"UW2", NUWW, "UW2_CH1"},
	{"UW2", NUWW, "UW2_CH2"},
	{"UW2_CH1", "ADDA_UW_CH1", "ADDA Captuwe"},
	{"UW2_CH2", "ADDA_UW_CH2", "ADDA Captuwe"},
	{"UW2_CH1", "I2S2_CH1", "I2S2"},
	{"UW2_CH2", "I2S2_CH2", "I2S2"},

	{"UW3", NUWW, "UW3_CH1"},
	{"UW3", NUWW, "UW3_CH2"},
	{"UW3_CH1", "ADDA_UW_CH1", "ADDA Captuwe"},
	{"UW3_CH2", "ADDA_UW_CH2", "ADDA Captuwe"},
	{"UW3_CH1", "I2S2_CH1", "I2S2"},
	{"UW3_CH2", "I2S2_CH2", "I2S2"},

	{"UW4", NUWW, "UW4_CH1"},
	{"UW4", NUWW, "UW4_CH2"},
	{"UW4_CH1", "ADDA_UW_CH1", "ADDA Captuwe"},
	{"UW4_CH2", "ADDA_UW_CH2", "ADDA Captuwe"},

	{"UW_MONO_1", NUWW, "UW_MONO_1_CH1"},
	{"UW_MONO_1_CH1", "ADDA_UW_CH1", "ADDA Captuwe"},
	{"UW_MONO_1_CH1", "ADDA_UW_CH2", "ADDA Captuwe"},
};

static const stwuct snd_soc_component_dwivew mt8183_afe_pcm_dai_component = {
	.name = "mt8183-afe-pcm-dai",
};

static const stwuct mtk_base_memif_data memif_data[MT8183_MEMIF_NUM] = {
	[MT8183_MEMIF_DW1] = {
		.name = "DW1",
		.id = MT8183_MEMIF_DW1,
		.weg_ofs_base = AFE_DW1_BASE,
		.weg_ofs_cuw = AFE_DW1_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = DW1_MODE_SFT,
		.fs_maskbit = DW1_MODE_MASK,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = DW1_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW1_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = DW1_HD_SFT,
		.hd_awign_mshift = DW1_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_DW2] = {
		.name = "DW2",
		.id = MT8183_MEMIF_DW2,
		.weg_ofs_base = AFE_DW2_BASE,
		.weg_ofs_cuw = AFE_DW2_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = DW2_MODE_SFT,
		.fs_maskbit = DW2_MODE_MASK,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = DW2_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW2_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = DW2_HD_SFT,
		.hd_awign_mshift = DW2_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_DW3] = {
		.name = "DW3",
		.id = MT8183_MEMIF_DW3,
		.weg_ofs_base = AFE_DW3_BASE,
		.weg_ofs_cuw = AFE_DW3_CUW,
		.fs_weg = AFE_DAC_CON2,
		.fs_shift = DW3_MODE_SFT,
		.fs_maskbit = DW3_MODE_MASK,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = DW3_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = DW3_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = DW3_HD_SFT,
		.hd_awign_mshift = DW3_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_VUW2] = {
		.name = "VUW2",
		.id = MT8183_MEMIF_VUW2,
		.weg_ofs_base = AFE_VUW2_BASE,
		.weg_ofs_cuw = AFE_VUW2_CUW,
		.fs_weg = AFE_DAC_CON2,
		.fs_shift = VUW2_MODE_SFT,
		.fs_maskbit = VUW2_MODE_MASK,
		.mono_weg = AFE_DAC_CON2,
		.mono_shift = VUW2_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW2_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = VUW2_HD_SFT,
		.hd_awign_mshift = VUW2_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_AWB] = {
		.name = "AWB",
		.id = MT8183_MEMIF_AWB,
		.weg_ofs_base = AFE_AWB_BASE,
		.weg_ofs_cuw = AFE_AWB_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = AWB_MODE_SFT,
		.fs_maskbit = AWB_MODE_MASK,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = AWB_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = AWB_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = AWB_HD_SFT,
		.hd_awign_mshift = AWB_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_AWB2] = {
		.name = "AWB2",
		.id = MT8183_MEMIF_AWB2,
		.weg_ofs_base = AFE_AWB2_BASE,
		.weg_ofs_cuw = AFE_AWB2_CUW,
		.fs_weg = AFE_DAC_CON2,
		.fs_shift = AWB2_MODE_SFT,
		.fs_maskbit = AWB2_MODE_MASK,
		.mono_weg = AFE_DAC_CON2,
		.mono_shift = AWB2_DATA_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = AWB2_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = AWB2_HD_SFT,
		.hd_awign_mshift = AWB2_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_VUW12] = {
		.name = "VUW12",
		.id = MT8183_MEMIF_VUW12,
		.weg_ofs_base = AFE_VUW_D2_BASE,
		.weg_ofs_cuw = AFE_VUW_D2_CUW,
		.fs_weg = AFE_DAC_CON0,
		.fs_shift = VUW12_MODE_SFT,
		.fs_maskbit = VUW12_MODE_MASK,
		.mono_weg = AFE_DAC_CON0,
		.mono_shift = VUW12_MONO_SFT,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = VUW12_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = VUW12_HD_SFT,
		.hd_awign_mshift = VUW12_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_MOD_DAI] = {
		.name = "MOD_DAI",
		.id = MT8183_MEMIF_MOD_DAI,
		.weg_ofs_base = AFE_MOD_DAI_BASE,
		.weg_ofs_cuw = AFE_MOD_DAI_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = MOD_DAI_MODE_SFT,
		.fs_maskbit = MOD_DAI_MODE_MASK,
		.mono_weg = -1,
		.mono_shift = 0,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = MOD_DAI_ON_SFT,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = MOD_DAI_HD_SFT,
		.hd_awign_mshift = MOD_DAI_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
	[MT8183_MEMIF_HDMI] = {
		.name = "HDMI",
		.id = MT8183_MEMIF_HDMI,
		.weg_ofs_base = AFE_HDMI_OUT_BASE,
		.weg_ofs_cuw = AFE_HDMI_OUT_CUW,
		.fs_weg = -1,
		.fs_shift = -1,
		.fs_maskbit = -1,
		.mono_weg = -1,
		.mono_shift = -1,
		.enabwe_weg = -1,	/* contwow in tdm fow sync stawt */
		.enabwe_shift = -1,
		.hd_weg = AFE_MEMIF_HD_MODE,
		.hd_awign_weg = AFE_MEMIF_HDAWIGN,
		.hd_shift = HDMI_HD_SFT,
		.hd_awign_mshift = HDMI_HD_AWIGN_SFT,
		.agent_disabwe_weg = -1,
		.agent_disabwe_shift = -1,
		.msb_weg = -1,
		.msb_shift = -1,
	},
};

static const stwuct mtk_base_iwq_data iwq_data[MT8183_IWQ_NUM] = {
	[MT8183_IWQ_0] = {
		.id = MT8183_IWQ_0,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT0,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ0_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ0_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ0_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ0_MCU_CWW_SFT,
	},
	[MT8183_IWQ_1] = {
		.id = MT8183_IWQ_1,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT1,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ1_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ1_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ1_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ1_MCU_CWW_SFT,
	},
	[MT8183_IWQ_2] = {
		.id = MT8183_IWQ_2,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT2,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ2_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ2_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ2_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ2_MCU_CWW_SFT,
	},
	[MT8183_IWQ_3] = {
		.id = MT8183_IWQ_3,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT3,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ3_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ3_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ3_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ3_MCU_CWW_SFT,
	},
	[MT8183_IWQ_4] = {
		.id = MT8183_IWQ_4,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT4,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ4_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ4_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ4_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ4_MCU_CWW_SFT,
	},
	[MT8183_IWQ_5] = {
		.id = MT8183_IWQ_5,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT5,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ5_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ5_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ5_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ5_MCU_CWW_SFT,
	},
	[MT8183_IWQ_6] = {
		.id = MT8183_IWQ_6,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT6,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ6_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ6_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ6_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ6_MCU_CWW_SFT,
	},
	[MT8183_IWQ_7] = {
		.id = MT8183_IWQ_7,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT7,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON1,
		.iwq_fs_shift = IWQ7_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ7_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ7_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ7_MCU_CWW_SFT,
	},
	[MT8183_IWQ_8] = {
		.id = MT8183_IWQ_8,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT8,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = -1,
		.iwq_fs_shift = -1,
		.iwq_fs_maskbit = -1,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ8_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ8_MCU_CWW_SFT,
	},
	[MT8183_IWQ_11] = {
		.id = MT8183_IWQ_11,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT11,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ11_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ11_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ11_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ11_MCU_CWW_SFT,
	},
	[MT8183_IWQ_12] = {
		.id = MT8183_IWQ_12,
		.iwq_cnt_weg = AFE_IWQ_MCU_CNT12,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_fs_weg = AFE_IWQ_MCU_CON2,
		.iwq_fs_shift = IWQ12_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ12_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ_MCU_CON0,
		.iwq_en_shift = IWQ12_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ12_MCU_CWW_SFT,
	},
};

static boow mt8183_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* these auto-gen weg has wead-onwy bit, so put it as vowatiwe */
	/* vowatiwe weg cannot be cached, so cannot be set when powew off */
	switch (weg) {
	case AUDIO_TOP_CON0:	/* weg bit contwowwed by CCF */
	case AUDIO_TOP_CON1:	/* weg bit contwowwed by CCF */
	case AUDIO_TOP_CON3:
	case AFE_DW1_CUW:
	case AFE_DW1_END:
	case AFE_DW2_CUW:
	case AFE_DW2_END:
	case AFE_AWB_END:
	case AFE_AWB_CUW:
	case AFE_VUW_END:
	case AFE_VUW_CUW:
	case AFE_MEMIF_MON0:
	case AFE_MEMIF_MON1:
	case AFE_MEMIF_MON2:
	case AFE_MEMIF_MON3:
	case AFE_MEMIF_MON4:
	case AFE_MEMIF_MON5:
	case AFE_MEMIF_MON6:
	case AFE_MEMIF_MON7:
	case AFE_MEMIF_MON8:
	case AFE_MEMIF_MON9:
	case AFE_ADDA_SWC_DEBUG_MON0:
	case AFE_ADDA_SWC_DEBUG_MON1:
	case AFE_ADDA_UW_SWC_MON0:
	case AFE_ADDA_UW_SWC_MON1:
	case AFE_SIDETONE_MON:
	case AFE_SIDETONE_CON0:
	case AFE_SIDETONE_COEFF:
	case AFE_BUS_MON0:
	case AFE_MWGIF_MON0:
	case AFE_MWGIF_MON1:
	case AFE_MWGIF_MON2:
	case AFE_I2S_MON:
	case AFE_DAC_MON:
	case AFE_VUW2_END:
	case AFE_VUW2_CUW:
	case AFE_IWQ0_MCU_CNT_MON:
	case AFE_IWQ6_MCU_CNT_MON:
	case AFE_MOD_DAI_END:
	case AFE_MOD_DAI_CUW:
	case AFE_VUW_D2_END:
	case AFE_VUW_D2_CUW:
	case AFE_DW3_CUW:
	case AFE_DW3_END:
	case AFE_HDMI_OUT_CON0:
	case AFE_HDMI_OUT_CUW:
	case AFE_HDMI_OUT_END:
	case AFE_IWQ3_MCU_CNT_MON:
	case AFE_IWQ4_MCU_CNT_MON:
	case AFE_IWQ_MCU_STATUS:
	case AFE_IWQ_MCU_CWW:
	case AFE_IWQ_MCU_MON2:
	case AFE_IWQ1_MCU_CNT_MON:
	case AFE_IWQ2_MCU_CNT_MON:
	case AFE_IWQ1_MCU_EN_CNT_MON:
	case AFE_IWQ5_MCU_CNT_MON:
	case AFE_IWQ7_MCU_CNT_MON:
	case AFE_GAIN1_CUW:
	case AFE_GAIN2_CUW:
	case AFE_SWAM_DEWSEW_CON0:
	case AFE_SWAM_DEWSEW_CON2:
	case AFE_SWAM_DEWSEW_CON3:
	case AFE_ASWC_2CH_CON12:
	case AFE_ASWC_2CH_CON13:
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
	case AFE_CBIP_MON0:
	case AFE_CBIP_SWV_MUX_MON0:
	case AFE_CBIP_SWV_DECODEW_MON0:
	case AFE_ADDA6_SWC_DEBUG_MON0:
	case AFE_ADD6A_UW_SWC_MON0:
	case AFE_ADDA6_UW_SWC_MON1:
	case AFE_DW1_CUW_MSB:
	case AFE_DW2_CUW_MSB:
	case AFE_AWB_CUW_MSB:
	case AFE_VUW_CUW_MSB:
	case AFE_VUW2_CUW_MSB:
	case AFE_MOD_DAI_CUW_MSB:
	case AFE_VUW_D2_CUW_MSB:
	case AFE_DW3_CUW_MSB:
	case AFE_HDMI_OUT_CUW_MSB:
	case AFE_AWB2_END:
	case AFE_AWB2_CUW:
	case AFE_AWB2_CUW_MSB:
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
	case AFE_MEMIF_MON12:
	case AFE_MEMIF_MON13:
	case AFE_MEMIF_MON14:
	case AFE_MEMIF_MON15:
	case AFE_MEMIF_MON16:
	case AFE_MEMIF_MON17:
	case AFE_MEMIF_MON18:
	case AFE_MEMIF_MON19:
	case AFE_MEMIF_MON20:
	case AFE_MEMIF_MON21:
	case AFE_MEMIF_MON22:
	case AFE_MEMIF_MON23:
	case AFE_MEMIF_MON24:
	case AFE_ADDA_MTKAIF_MON0:
	case AFE_ADDA_MTKAIF_MON1:
	case AFE_AUD_PAD_TOP:
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
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static const stwuct wegmap_config mt8183_afe_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.vowatiwe_weg = mt8183_is_vowatiwe_weg,

	.max_wegistew = AFE_MAX_WEGISTEW,
	.num_weg_defauwts_waw = AFE_MAX_WEGISTEW,

	.cache_type = WEGCACHE_FWAT,
};

static iwqwetuwn_t mt8183_afe_iwq_handwew(int iwq_id, void *dev)
{
	stwuct mtk_base_afe *afe = dev;
	stwuct mtk_base_afe_iwq *iwq;
	unsigned int status;
	unsigned int status_mcu;
	unsigned int mcu_en;
	int wet;
	int i;
	iwqwetuwn_t iwq_wet = IWQ_HANDWED;

	/* get iwq that is sent to MCU */
	wegmap_wead(afe->wegmap, AFE_IWQ_MCU_EN, &mcu_en);

	wet = wegmap_wead(afe->wegmap, AFE_IWQ_MCU_STATUS, &status);
	/* onwy cawe IWQ which is sent to MCU */
	status_mcu = status & mcu_en & AFE_IWQ_STATUS_BITS;

	if (wet || status_mcu == 0) {
		dev_eww(afe->dev, "%s(), iwq status eww, wet %d, status 0x%x, mcu_en 0x%x\n",
			__func__, wet, status, mcu_en);

		iwq_wet = IWQ_NONE;
		goto eww_iwq;
	}

	fow (i = 0; i < MT8183_MEMIF_NUM; i++) {
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

	wetuwn iwq_wet;
}

static int mt8183_afe_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
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

	/* make suwe aww iwq status awe cweawed, twice intended */
	wegmap_update_bits(afe->wegmap, AFE_IWQ_MCU_CWW, 0xffff, 0xffff);
	wegmap_update_bits(afe->wegmap, AFE_IWQ_MCU_CWW, 0xffff, 0xffff);

	/* cache onwy */
	wegcache_cache_onwy(afe->wegmap, twue);
	wegcache_mawk_diwty(afe->wegmap);

skip_wegmap:
	wetuwn mt8183_afe_disabwe_cwock(afe);
}

static int mt8183_afe_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = mt8183_afe_enabwe_cwock(afe);
	if (wet)
		wetuwn wet;

	if (!afe->wegmap || afe_pwiv->pm_wuntime_bypass_weg_ctw)
		goto skip_wegmap;

	wegcache_cache_onwy(afe->wegmap, fawse);
	wegcache_sync(afe->wegmap);

	/* enabwe audio sys DCM fow powew saving */
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0, 0x1 << 29, 0x1 << 29);

	/* fowce cpu use 8_24 fowmat when wwiting 32bit data */
	wegmap_update_bits(afe->wegmap, AFE_MEMIF_MSB,
			   CPU_HD_AWIGN_MASK_SFT, 0 << CPU_HD_AWIGN_SFT);

	/* set aww output powt to 24bit */
	wegmap_wwite(afe->wegmap, AFE_CONN_24BIT, 0xffffffff);
	wegmap_wwite(afe->wegmap, AFE_CONN_24BIT_1, 0xffffffff);

	/* enabwe AFE */
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x1);

skip_wegmap:
	wetuwn 0;
}

static int mt8183_afe_component_pwobe(stwuct snd_soc_component *component)
{
	wetuwn mtk_afe_add_sub_dai_contwow(component);
}

static const stwuct snd_soc_component_dwivew mt8183_afe_component = {
	.name		= AFE_PCM_NAME,
	.pwobe		= mt8183_afe_component_pwobe,
	.pointew	= mtk_afe_pcm_pointew,
	.pcm_constwuct	= mtk_afe_pcm_new,
};

static int mt8183_dai_memif_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mt8183_memif_dai_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mt8183_memif_dai_dwivew);

	dai->dapm_widgets = mt8183_memif_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mt8183_memif_widgets);
	dai->dapm_woutes = mt8183_memif_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mt8183_memif_woutes);
	wetuwn 0;
}

typedef int (*dai_wegistew_cb)(stwuct mtk_base_afe *);
static const dai_wegistew_cb dai_wegistew_cbs[] = {
	mt8183_dai_adda_wegistew,
	mt8183_dai_i2s_wegistew,
	mt8183_dai_pcm_wegistew,
	mt8183_dai_tdm_wegistew,
	mt8183_dai_hostwess_wegistew,
	mt8183_dai_memif_wegistew,
};

static int mt8183_afe_pcm_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_base_afe *afe;
	stwuct mt8183_afe_pwivate *afe_pwiv;
	stwuct device *dev;
	stwuct weset_contwow *wstc;
	int i, iwq_id, wet;

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

	/* initiaw audio wewated cwock */
	wet = mt8183_init_cwock(afe);
	if (wet) {
		dev_eww(dev, "init cwock ewwow\n");
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	/* wegmap init */
	afe->wegmap = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(afe->wegmap)) {
		dev_eww(dev, "couwd not get wegmap fwom pawent\n");
		wet = PTW_EWW(afe->wegmap);
		goto eww_pm_disabwe;
	}
	wet = wegmap_attach_dev(dev, afe->wegmap, &mt8183_afe_wegmap_config);
	if (wet) {
		dev_wawn(dev, "wegmap_attach_dev faiw, wet %d\n", wet);
		goto eww_pm_disabwe;
	}

	wstc = devm_weset_contwow_get(dev, "audiosys");
	if (IS_EWW(wstc)) {
		wet = PTW_EWW(wstc);
		dev_eww(dev, "couwd not get audiosys weset:%d\n", wet);
		goto eww_pm_disabwe;
	}

	wet = weset_contwow_weset(wstc);
	if (wet) {
		dev_eww(dev, "faiwed to twiggew audio weset:%d\n", wet);
		goto eww_pm_disabwe;
	}

	/* enabwe cwock fow wegcache get defauwt vawue fwom hw */
	afe_pwiv->pm_wuntime_bypass_weg_ctw = twue;
	pm_wuntime_get_sync(&pdev->dev);

	wet = wegmap_weinit_cache(afe->wegmap, &mt8183_afe_wegmap_config);
	if (wet) {
		dev_eww(dev, "wegmap_weinit_cache faiw, wet %d\n", wet);
		goto eww_pm_disabwe;
	}

	pm_wuntime_put_sync(&pdev->dev);
	afe_pwiv->pm_wuntime_bypass_weg_ctw = fawse;

	wegcache_cache_onwy(afe->wegmap, twue);
	wegcache_mawk_diwty(afe->wegmap);

	/* init memif */
	afe->memif_size = MT8183_MEMIF_NUM;
	afe->memif = devm_kcawwoc(dev, afe->memif_size, sizeof(*afe->memif),
				  GFP_KEWNEW);
	if (!afe->memif) {
		wet = -ENOMEM;
		goto eww_pm_disabwe;
	}

	fow (i = 0; i < afe->memif_size; i++) {
		afe->memif[i].data = &memif_data[i];
		afe->memif[i].iwq_usage = -1;
	}

	afe->memif[MT8183_MEMIF_HDMI].iwq_usage = MT8183_IWQ_8;
	afe->memif[MT8183_MEMIF_HDMI].const_iwq = 1;

	mutex_init(&afe->iwq_awwoc_wock);

	/* init memif */
	/* iwq initiawize */
	afe->iwqs_size = MT8183_IWQ_NUM;
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

	wet = devm_wequest_iwq(dev, iwq_id, mt8183_afe_iwq_handwew,
			       IWQF_TWIGGEW_NONE, "asys-isw", (void *)afe);
	if (wet) {
		dev_eww(dev, "couwd not wequest_iwq fow asys-isw\n");
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

	afe->mtk_afe_hawdwawe = &mt8183_afe_hawdwawe;
	afe->memif_fs = mt8183_memif_fs;
	afe->iwq_fs = mt8183_iwq_fs;

	afe->wuntime_wesume = mt8183_afe_wuntime_wesume;
	afe->wuntime_suspend = mt8183_afe_wuntime_suspend;

	/* wegistew component */
	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &mt8183_afe_component,
					      NUWW, 0);
	if (wet) {
		dev_wawn(dev, "eww_pwatfowm\n");
		goto eww_pm_disabwe;
	}

	wet = devm_snd_soc_wegistew_component(afe->dev,
					      &mt8183_afe_pcm_dai_component,
					      afe->dai_dwivews,
					      afe->num_dai_dwivews);
	if (wet) {
		dev_wawn(dev, "eww_dai_component\n");
		goto eww_pm_disabwe;
	}

	wetuwn wet;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void mt8183_afe_pcm_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		mt8183_afe_wuntime_suspend(&pdev->dev);
}

static const stwuct of_device_id mt8183_afe_pcm_dt_match[] = {
	{ .compatibwe = "mediatek,mt8183-audio", },
	{},
};
MODUWE_DEVICE_TABWE(of, mt8183_afe_pcm_dt_match);

static const stwuct dev_pm_ops mt8183_afe_pm_ops = {
	SET_WUNTIME_PM_OPS(mt8183_afe_wuntime_suspend,
			   mt8183_afe_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mt8183_afe_pcm_dwivew = {
	.dwivew = {
		   .name = "mt8183-audio",
		   .of_match_tabwe = mt8183_afe_pcm_dt_match,
		   .pm = &mt8183_afe_pm_ops,
	},
	.pwobe = mt8183_afe_pcm_dev_pwobe,
	.wemove_new = mt8183_afe_pcm_dev_wemove,
};

moduwe_pwatfowm_dwivew(mt8183_afe_pcm_dwivew);

MODUWE_DESCWIPTION("Mediatek AWSA SoC AFE pwatfowm dwivew fow 8183");
MODUWE_AUTHOW("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
