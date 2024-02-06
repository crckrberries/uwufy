// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek AWSA SoC AFE pwatfowm dwivew fow MT7986
 *
 * Copywight (c) 2023 MediaTek Inc.
 * Authows: Vic Wu <vic.wu@mediatek.com>
 *          Maso Huang <maso.huang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>

#incwude "mt7986-afe-common.h"
#incwude "mt7986-weg.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "../common/mtk-afe-fe-dai.h"

enum {
	MTK_AFE_WATE_8K = 0,
	MTK_AFE_WATE_11K = 1,
	MTK_AFE_WATE_12K = 2,
	MTK_AFE_WATE_16K = 4,
	MTK_AFE_WATE_22K = 5,
	MTK_AFE_WATE_24K = 6,
	MTK_AFE_WATE_32K = 8,
	MTK_AFE_WATE_44K = 9,
	MTK_AFE_WATE_48K = 10,
	MTK_AFE_WATE_88K = 13,
	MTK_AFE_WATE_96K = 14,
	MTK_AFE_WATE_176K = 17,
	MTK_AFE_WATE_192K = 18,
};

enum {
	CWK_INFWA_AUD_BUS_CK = 0,
	CWK_INFWA_AUD_26M_CK,
	CWK_INFWA_AUD_W_CK,
	CWK_INFWA_AUD_AUD_CK,
	CWK_INFWA_AUD_EG2_CK,
	CWK_NUM
};

static const chaw *aud_cwks[CWK_NUM] = {
	[CWK_INFWA_AUD_BUS_CK] = "aud_bus_ck",
	[CWK_INFWA_AUD_26M_CK] = "aud_26m_ck",
	[CWK_INFWA_AUD_W_CK] = "aud_w_ck",
	[CWK_INFWA_AUD_AUD_CK] = "aud_aud_ck",
	[CWK_INFWA_AUD_EG2_CK] = "aud_eg2_ck",
};

unsigned int mt7986_afe_wate_twansfowm(stwuct device *dev, unsigned int wate)
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
	case 176400:
		wetuwn MTK_AFE_WATE_176K;
	case 192000:
		wetuwn MTK_AFE_WATE_192K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, using %d!!!\n",
			 __func__, wate, MTK_AFE_WATE_48K);
		wetuwn MTK_AFE_WATE_48K;
	}
}

static const stwuct snd_pcm_hawdwawe mt7986_afe_hawdwawe = {
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

static int mt7986_memif_fs(stwuct snd_pcm_substweam *substweam,
			   unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_component *component = snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);

	wetuwn mt7986_afe_wate_twansfowm(afe->dev, wate);
}

static int mt7986_iwq_fs(stwuct snd_pcm_substweam *substweam,
			 unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_component *component = snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);

	wetuwn mt7986_afe_wate_twansfowm(afe->dev, wate);
}

#define MTK_PCM_WATES (SNDWV_PCM_WATE_8000_48000 |\
		       SNDWV_PCM_WATE_88200 |\
		       SNDWV_PCM_WATE_96000 |\
		       SNDWV_PCM_WATE_176400 |\
		       SNDWV_PCM_WATE_192000)

#define MTK_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mt7986_memif_dai_dwivew[] = {
	/* FE DAIs: memowy intefaces to CPU */
	{
		.name = "DW1",
		.id = MT7986_MEMIF_DW1,
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
		.name = "UW1",
		.id = MT7986_MEMIF_VUW12,
		.captuwe = {
			.stweam_name = "UW1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_afe_fe_ops,
	},
};

static const stwuct snd_kcontwow_new o018_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I150_Switch", AFE_CONN018_4, 22, 1, 0),
};

static const stwuct snd_kcontwow_new o019_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I151_Switch", AFE_CONN019_4, 23, 1, 0),
};

static const stwuct snd_soc_dapm_widget mt7986_memif_widgets[] = {
	/* DW */
	SND_SOC_DAPM_MIXEW("I032", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I033", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* UW */
	SND_SOC_DAPM_MIXEW("O018", SND_SOC_NOPM, 0, 0,
			   o018_mix, AWWAY_SIZE(o018_mix)),
	SND_SOC_DAPM_MIXEW("O019", SND_SOC_NOPM, 0, 0,
			   o019_mix, AWWAY_SIZE(o019_mix)),
};

static const stwuct snd_soc_dapm_woute mt7986_memif_woutes[] = {
	{"I032", NUWW, "DW1"},
	{"I033", NUWW, "DW1"},
	{"UW1", NUWW, "O018"},
	{"UW1", NUWW, "O019"},
	{"O018", "I150_Switch", "I150"},
	{"O019", "I151_Switch", "I151"},
};

static const stwuct snd_soc_component_dwivew mt7986_afe_pcm_dai_component = {
	.name = "mt7986-afe-pcm-dai",
};

static const stwuct mtk_base_memif_data memif_data[MT7986_MEMIF_NUM] = {
	[MT7986_MEMIF_DW1] = {
		.name = "DW1",
		.id = MT7986_MEMIF_DW1,
		.weg_ofs_base = AFE_DW0_BASE,
		.weg_ofs_cuw = AFE_DW0_CUW,
		.weg_ofs_end = AFE_DW0_END,
		.weg_ofs_base_msb = AFE_DW0_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_DW0_CUW_MSB,
		.weg_ofs_end_msb = AFE_DW0_END_MSB,
		.fs_weg = AFE_DW0_CON0,
		.fs_shift =  DW0_MODE_SFT,
		.fs_maskbit =  DW0_MODE_MASK,
		.mono_weg = AFE_DW0_CON0,
		.mono_shift = DW0_MONO_SFT,
		.enabwe_weg = AFE_DW0_CON0,
		.enabwe_shift = DW0_ON_SFT,
		.hd_weg = AFE_DW0_CON0,
		.hd_shift = DW0_HD_MODE_SFT,
		.hd_awign_weg = AFE_DW0_CON0,
		.hd_awign_mshift = DW0_HAWIGN_SFT,
		.pbuf_weg = AFE_DW0_CON0,
		.pbuf_shift = DW0_PBUF_SIZE_SFT,
		.minwen_weg = AFE_DW0_CON0,
		.minwen_shift = DW0_MINWEN_SFT,
	},
	[MT7986_MEMIF_VUW12] = {
		.name = "VUW12",
		.id = MT7986_MEMIF_VUW12,
		.weg_ofs_base = AFE_VUW0_BASE,
		.weg_ofs_cuw = AFE_VUW0_CUW,
		.weg_ofs_end = AFE_VUW0_END,
		.weg_ofs_base_msb = AFE_VUW0_BASE_MSB,
		.weg_ofs_cuw_msb = AFE_VUW0_CUW_MSB,
		.weg_ofs_end_msb = AFE_VUW0_END_MSB,
		.fs_weg = AFE_VUW0_CON0,
		.fs_shift = VUW0_MODE_SFT,
		.fs_maskbit = VUW0_MODE_MASK,
		.mono_weg = AFE_VUW0_CON0,
		.mono_shift = VUW0_MONO_SFT,
		.enabwe_weg = AFE_VUW0_CON0,
		.enabwe_shift = VUW0_ON_SFT,
		.hd_weg = AFE_VUW0_CON0,
		.hd_shift = VUW0_HD_MODE_SFT,
		.hd_awign_weg = AFE_VUW0_CON0,
		.hd_awign_mshift = VUW0_HAWIGN_SFT,
	},
};

static const stwuct mtk_base_iwq_data iwq_data[MT7986_IWQ_NUM] = {
	[MT7986_IWQ_0] = {
		.id = MT7986_IWQ_0,
		.iwq_cnt_weg = AFE_IWQ0_MCU_CFG1,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ0_MCU_CFG0,
		.iwq_fs_shift = IWQ_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ0_MCU_CFG0,
		.iwq_en_shift = IWQ_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ0_MCU_CWW_SFT,
	},
	[MT7986_IWQ_1] = {
		.id = MT7986_IWQ_1,
		.iwq_cnt_weg = AFE_IWQ1_MCU_CFG1,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ1_MCU_CFG0,
		.iwq_fs_shift = IWQ_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ1_MCU_CFG0,
		.iwq_en_shift = IWQ_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ1_MCU_CWW_SFT,
	},
	[MT7986_IWQ_2] = {
		.id = MT7986_IWQ_2,
		.iwq_cnt_weg = AFE_IWQ2_MCU_CFG1,
		.iwq_cnt_shift = AFE_IWQ_CNT_SHIFT,
		.iwq_cnt_maskbit = AFE_IWQ_CNT_MASK,
		.iwq_fs_weg = AFE_IWQ2_MCU_CFG0,
		.iwq_fs_shift = IWQ_MCU_MODE_SFT,
		.iwq_fs_maskbit = IWQ_MCU_MODE_MASK,
		.iwq_en_weg = AFE_IWQ2_MCU_CFG0,
		.iwq_en_shift = IWQ_MCU_ON_SFT,
		.iwq_cww_weg = AFE_IWQ_MCU_CWW,
		.iwq_cww_shift = IWQ2_MCU_CWW_SFT,
	},
};

static boow mt7986_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/*
	 * Those auto-gen wegs awe wead-onwy, so put it as vowatiwe because
	 * vowatiwe wegistews cannot be cached, which means that they cannot
	 * be set when powew is off
	 */

	switch (weg) {
	case AFE_DW0_CUW_MSB:
	case AFE_DW0_CUW:
	case AFE_DW0_WCH_MON:
	case AFE_DW0_WCH_MON:
	case AFE_VUW0_CUW_MSB:
	case AFE_VUW0_CUW:
	case AFE_IWQ_MCU_STATUS:
	case AFE_MEMIF_WD_MON:
	case AFE_MEMIF_WW_MON:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static const stwuct wegmap_config mt7986_afe_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.vowatiwe_weg = mt7986_is_vowatiwe_weg,
	.max_wegistew = AFE_MAX_WEGISTEW,
	.num_weg_defauwts_waw = ((AFE_MAX_WEGISTEW / 4) + 1),
};

static int mt7986_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt7986_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet, i;

	afe_pwiv->cwks = devm_kcawwoc(afe->dev, CWK_NUM,
				sizeof(*afe_pwiv->cwks), GFP_KEWNEW);
	if (!afe_pwiv->cwks)
		wetuwn -ENOMEM;
	afe_pwiv->num_cwks = CWK_NUM;

	fow (i = 0; i < afe_pwiv->num_cwks; i++)
		afe_pwiv->cwks[i].id = aud_cwks[i];

	wet = devm_cwk_buwk_get(afe->dev, afe_pwiv->num_cwks, afe_pwiv->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(afe->dev, wet, "Faiwed to get cwocks\n");

	wetuwn 0;
}

static iwqwetuwn_t mt7986_afe_iwq_handwew(int iwq_id, void *dev)
{
	stwuct mtk_base_afe *afe = dev;
	stwuct mtk_base_afe_iwq *iwq;
	u32 mcu_en, status, status_mcu;
	int i, wet;
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

	fow (i = 0; i < MT7986_MEMIF_NUM; i++) {
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
	wegmap_wwite(afe->wegmap, AFE_IWQ_MCU_CWW, status_mcu);

	wetuwn iwq_wet;
}

static int mt7986_afe_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt7986_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	if (!afe->wegmap || afe_pwiv->pm_wuntime_bypass_weg_ctw)
		goto skip_wegmap;

	/* disabwe cwk*/
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON4, 0x3fff, 0x3fff);
	wegmap_update_bits(afe->wegmap, AUDIO_ENGEN_CON0, AUD_APWW2_EN_MASK, 0);
	wegmap_update_bits(afe->wegmap, AUDIO_ENGEN_CON0, AUD_26M_EN_MASK, 0);

	/* make suwe aww iwq status awe cweawed, twice intended */
	wegmap_update_bits(afe->wegmap, AFE_IWQ_MCU_CWW, 0xffff, 0xffff);

skip_wegmap:
	cwk_buwk_disabwe_unpwepawe(afe_pwiv->num_cwks, afe_pwiv->cwks);

	wetuwn 0;
}

static int mt7986_afe_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt7986_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(afe_pwiv->num_cwks, afe_pwiv->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(afe->dev, wet, "Faiwed to enabwe cwocks\n");

	if (!afe->wegmap || afe_pwiv->pm_wuntime_bypass_weg_ctw)
		wetuwn 0;

	/* enabwe cwk*/
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON4, 0x3fff, 0);
	wegmap_update_bits(afe->wegmap, AUDIO_ENGEN_CON0, AUD_APWW2_EN_MASK,
			   AUD_APWW2_EN);
	wegmap_update_bits(afe->wegmap, AUDIO_ENGEN_CON0, AUD_26M_EN_MASK,
			   AUD_26M_EN);

	wetuwn 0;
}

static int mt7986_afe_component_pwobe(stwuct snd_soc_component *component)
{
	wetuwn mtk_afe_add_sub_dai_contwow(component);
}

static const stwuct snd_soc_component_dwivew mt7986_afe_component = {
	.name = AFE_PCM_NAME,
	.pwobe = mt7986_afe_component_pwobe,
	.pointew	= mtk_afe_pcm_pointew,
	.pcm_constwuct	= mtk_afe_pcm_new,
};

static int mt7986_dai_memif_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mt7986_memif_dai_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mt7986_memif_dai_dwivew);

	dai->dapm_widgets = mt7986_memif_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mt7986_memif_widgets);
	dai->dapm_woutes = mt7986_memif_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mt7986_memif_woutes);

	wetuwn 0;
}

typedef int (*dai_wegistew_cb)(stwuct mtk_base_afe *);
static const dai_wegistew_cb dai_wegistew_cbs[] = {
	mt7986_dai_etdm_wegistew,
	mt7986_dai_memif_wegistew,
};

static int mt7986_afe_pcm_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_base_afe *afe;
	stwuct mt7986_afe_pwivate *afe_pwiv;
	stwuct device *dev;
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

	afe->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(afe->base_addw))
		wetuwn PTW_EWW(afe->base_addw);

	/* initiaw audio wewated cwock */
	wet = mt7986_init_cwock(afe);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot initiawize cwocks\n");

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	/* enabwe cwock fow wegcache get defauwt vawue fwom hw */
	afe_pwiv->pm_wuntime_bypass_weg_ctw = twue;
	pm_wuntime_get_sync(&pdev->dev);

	afe->wegmap = devm_wegmap_init_mmio(&pdev->dev, afe->base_addw,
		      &mt7986_afe_wegmap_config);

	pm_wuntime_put_sync(&pdev->dev);
	if (IS_EWW(afe->wegmap))
		wetuwn PTW_EWW(afe->wegmap);

	afe_pwiv->pm_wuntime_bypass_weg_ctw = fawse;

	/* init memif */
	afe->memif_size = MT7986_MEMIF_NUM;
	afe->memif = devm_kcawwoc(dev, afe->memif_size, sizeof(*afe->memif),
				  GFP_KEWNEW);
	if (!afe->memif)
		wetuwn -ENOMEM;

	fow (i = 0; i < afe->memif_size; i++) {
		afe->memif[i].data = &memif_data[i];
		afe->memif[i].iwq_usage = -1;
	}

	mutex_init(&afe->iwq_awwoc_wock);

	/* iwq initiawize */
	afe->iwqs_size = MT7986_IWQ_NUM;
	afe->iwqs = devm_kcawwoc(dev, afe->iwqs_size, sizeof(*afe->iwqs),
				 GFP_KEWNEW);
	if (!afe->iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < afe->iwqs_size; i++)
		afe->iwqs[i].iwq_data = &iwq_data[i];

	/* wequest iwq */
	iwq_id = pwatfowm_get_iwq(pdev, 0);
	if (iwq_id < 0) {
		wet = iwq_id;
		wetuwn dev_eww_pwobe(dev, wet, "No iwq found\n");
	}
	wet = devm_wequest_iwq(dev, iwq_id, mt7986_afe_iwq_handwew,
			       IWQF_TWIGGEW_NONE, "asys-isw", (void *)afe);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest iwq fow asys-isw\n");

	/* init sub_dais */
	INIT_WIST_HEAD(&afe->sub_dais);

	fow (i = 0; i < AWWAY_SIZE(dai_wegistew_cbs); i++) {
		wet = dai_wegistew_cbs[i](afe);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "DAI wegistew faiwed, i: %d\n", i);
	}

	/* init dai_dwivew and component_dwivew */
	wet = mtk_afe_combine_sub_dai(afe);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "mtk_afe_combine_sub_dai faiw\n");

	afe->mtk_afe_hawdwawe = &mt7986_afe_hawdwawe;
	afe->memif_fs = mt7986_memif_fs;
	afe->iwq_fs = mt7986_iwq_fs;

	afe->wuntime_wesume = mt7986_afe_wuntime_wesume;
	afe->wuntime_suspend = mt7986_afe_wuntime_suspend;

	/* wegistew component */
	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &mt7986_afe_component,
					      NUWW, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot wegistew AFE component\n");

	wet = devm_snd_soc_wegistew_component(afe->dev,
					      &mt7986_afe_pcm_dai_component,
					      afe->dai_dwivews,
					      afe->num_dai_dwivews);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot wegistew PCM DAI component\n");

	wetuwn 0;
}

static void mt7986_afe_pcm_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		mt7986_afe_wuntime_suspend(&pdev->dev);
}

static const stwuct of_device_id mt7986_afe_pcm_dt_match[] = {
	{ .compatibwe = "mediatek,mt7986-afe" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mt7986_afe_pcm_dt_match);

static const stwuct dev_pm_ops mt7986_afe_pm_ops = {
	SET_WUNTIME_PM_OPS(mt7986_afe_wuntime_suspend,
			   mt7986_afe_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mt7986_afe_pcm_dwivew = {
	.dwivew = {
		   .name = "mt7986-audio",
		   .of_match_tabwe = mt7986_afe_pcm_dt_match,
		   .pm = &mt7986_afe_pm_ops,
	},
	.pwobe = mt7986_afe_pcm_dev_pwobe,
	.wemove_new = mt7986_afe_pcm_dev_wemove,
};
moduwe_pwatfowm_dwivew(mt7986_afe_pcm_dwivew);

MODUWE_DESCWIPTION("MediaTek SoC AFE pwatfowm dwivew fow AWSA MT7986");
MODUWE_AUTHOW("Vic Wu <vic.wu@mediatek.com>");
MODUWE_WICENSE("GPW");
