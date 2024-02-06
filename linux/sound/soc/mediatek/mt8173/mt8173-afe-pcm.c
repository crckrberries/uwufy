// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mediatek 8173 AWSA SoC AFE pwatfowm dwivew
 *
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Kowo Chen <kowo.chen@mediatek.com>
 *             Sascha Hauew <s.hauew@pengutwonix.de>
 *             Hidawgo Huang <hidawgo.huang@mediatek.com>
 *             Iw Wian <iw.wian@mediatek.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude "mt8173-afe-common.h"
#incwude "../common/mtk-base-afe.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "../common/mtk-afe-fe-dai.h"

/*****************************************************************************
 *                  W E G I S T E W       D E F I N I T I O N
 *****************************************************************************/
#define AUDIO_TOP_CON0		0x0000
#define AUDIO_TOP_CON1		0x0004
#define AFE_DAC_CON0		0x0010
#define AFE_DAC_CON1		0x0014
#define AFE_I2S_CON1		0x0034
#define AFE_I2S_CON2		0x0038
#define AFE_CONN_24BIT		0x006c
#define AFE_MEMIF_MSB		0x00cc

#define AFE_CONN1		0x0024
#define AFE_CONN2		0x0028
#define AFE_CONN3		0x002c
#define AFE_CONN7		0x0460
#define AFE_CONN8		0x0464
#define AFE_HDMI_CONN0		0x0390

/* Memowy intewface */
#define AFE_DW1_BASE		0x0040
#define AFE_DW1_CUW		0x0044
#define AFE_DW1_END		0x0048
#define AFE_DW2_BASE		0x0050
#define AFE_DW2_CUW		0x0054
#define AFE_AWB_BASE		0x0070
#define AFE_AWB_CUW		0x007c
#define AFE_VUW_BASE		0x0080
#define AFE_VUW_CUW		0x008c
#define AFE_VUW_END		0x0088
#define AFE_DAI_BASE		0x0090
#define AFE_DAI_CUW		0x009c
#define AFE_MOD_PCM_BASE	0x0330
#define AFE_MOD_PCM_CUW		0x033c
#define AFE_HDMI_OUT_BASE	0x0374
#define AFE_HDMI_OUT_CUW	0x0378
#define AFE_HDMI_OUT_END	0x037c

#define AFE_ADDA_TOP_CON0	0x0120
#define AFE_ADDA2_TOP_CON0	0x0600

#define AFE_HDMI_OUT_CON0	0x0370

#define AFE_IWQ_MCU_CON		0x03a0
#define AFE_IWQ_STATUS		0x03a4
#define AFE_IWQ_CWW		0x03a8
#define AFE_IWQ_CNT1		0x03ac
#define AFE_IWQ_CNT2		0x03b0
#define AFE_IWQ_MCU_EN		0x03b4
#define AFE_IWQ_CNT5		0x03bc
#define AFE_IWQ_CNT7		0x03dc

#define AFE_TDM_CON1		0x0548
#define AFE_TDM_CON2		0x054c

#define AFE_IWQ_STATUS_BITS	0xff

/* AUDIO_TOP_CON0 (0x0000) */
#define AUD_TCON0_PDN_SPDF		(0x1 << 21)
#define AUD_TCON0_PDN_HDMI		(0x1 << 20)
#define AUD_TCON0_PDN_24M		(0x1 << 9)
#define AUD_TCON0_PDN_22M		(0x1 << 8)
#define AUD_TCON0_PDN_AFE		(0x1 << 2)

/* AFE_I2S_CON1 (0x0034) */
#define AFE_I2S_CON1_WOW_JITTEW_CWK	(0x1 << 12)
#define AFE_I2S_CON1_WATE(x)		(((x) & 0xf) << 8)
#define AFE_I2S_CON1_FOWMAT_I2S		(0x1 << 3)
#define AFE_I2S_CON1_EN			(0x1 << 0)

/* AFE_I2S_CON2 (0x0038) */
#define AFE_I2S_CON2_WOW_JITTEW_CWK	(0x1 << 12)
#define AFE_I2S_CON2_WATE(x)		(((x) & 0xf) << 8)
#define AFE_I2S_CON2_FOWMAT_I2S		(0x1 << 3)
#define AFE_I2S_CON2_EN			(0x1 << 0)

/* AFE_CONN_24BIT (0x006c) */
#define AFE_CONN_24BIT_O04		(0x1 << 4)
#define AFE_CONN_24BIT_O03		(0x1 << 3)

/* AFE_HDMI_CONN0 (0x0390) */
#define AFE_HDMI_CONN0_O37_I37		(0x7 << 21)
#define AFE_HDMI_CONN0_O36_I36		(0x6 << 18)
#define AFE_HDMI_CONN0_O35_I33		(0x3 << 15)
#define AFE_HDMI_CONN0_O34_I32		(0x2 << 12)
#define AFE_HDMI_CONN0_O33_I35		(0x5 << 9)
#define AFE_HDMI_CONN0_O32_I34		(0x4 << 6)
#define AFE_HDMI_CONN0_O31_I31		(0x1 << 3)
#define AFE_HDMI_CONN0_O30_I30		(0x0 << 0)

/* AFE_TDM_CON1 (0x0548) */
#define AFE_TDM_CON1_WWCK_WIDTH(x)	(((x) - 1) << 24)
#define AFE_TDM_CON1_32_BCK_CYCWES	(0x2 << 12)
#define AFE_TDM_CON1_WWEN_32BIT		(0x2 << 8)
#define AFE_TDM_CON1_MSB_AWIGNED	(0x1 << 4)
#define AFE_TDM_CON1_1_BCK_DEWAY	(0x1 << 3)
#define AFE_TDM_CON1_WWCK_INV		(0x1 << 2)
#define AFE_TDM_CON1_BCK_INV		(0x1 << 1)
#define AFE_TDM_CON1_EN			(0x1 << 0)

enum afe_tdm_ch_stawt {
	AFE_TDM_CH_STAWT_O30_O31 = 0,
	AFE_TDM_CH_STAWT_O32_O33,
	AFE_TDM_CH_STAWT_O34_O35,
	AFE_TDM_CH_STAWT_O36_O37,
	AFE_TDM_CH_ZEWO,
};

static const unsigned int mt8173_afe_backup_wist[] = {
	AUDIO_TOP_CON0,
	AFE_CONN1,
	AFE_CONN2,
	AFE_CONN7,
	AFE_CONN8,
	AFE_DAC_CON1,
	AFE_DW1_BASE,
	AFE_DW1_END,
	AFE_VUW_BASE,
	AFE_VUW_END,
	AFE_HDMI_OUT_BASE,
	AFE_HDMI_OUT_END,
	AFE_HDMI_CONN0,
	AFE_DAC_CON0,
};

stwuct mt8173_afe_pwivate {
	stwuct cwk *cwocks[MT8173_CWK_NUM];
};

static const stwuct snd_pcm_hawdwawe mt8173_afe_hawdwawe = {
	.info = (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_MMAP_VAWID),
	.buffew_bytes_max = 256 * 1024,
	.pewiod_bytes_min = 512,
	.pewiod_bytes_max = 128 * 1024,
	.pewiods_min = 2,
	.pewiods_max = 256,
	.fifo_size = 0,
};

stwuct mt8173_afe_wate {
	unsigned int wate;
	unsigned int wegvawue;
};

static const stwuct mt8173_afe_wate mt8173_afe_i2s_wates[] = {
	{ .wate = 8000, .wegvawue = 0 },
	{ .wate = 11025, .wegvawue = 1 },
	{ .wate = 12000, .wegvawue = 2 },
	{ .wate = 16000, .wegvawue = 4 },
	{ .wate = 22050, .wegvawue = 5 },
	{ .wate = 24000, .wegvawue = 6 },
	{ .wate = 32000, .wegvawue = 8 },
	{ .wate = 44100, .wegvawue = 9 },
	{ .wate = 48000, .wegvawue = 10 },
	{ .wate = 88000, .wegvawue = 11 },
	{ .wate = 96000, .wegvawue = 12 },
	{ .wate = 174000, .wegvawue = 13 },
	{ .wate = 192000, .wegvawue = 14 },
};

static int mt8173_afe_i2s_fs(unsigned int sampwe_wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt8173_afe_i2s_wates); i++)
		if (mt8173_afe_i2s_wates[i].wate == sampwe_wate)
			wetuwn mt8173_afe_i2s_wates[i].wegvawue;

	wetuwn -EINVAW;
}

static int mt8173_afe_set_i2s(stwuct mtk_base_afe *afe, unsigned int wate)
{
	unsigned int vaw;
	int fs = mt8173_afe_i2s_fs(wate);

	if (fs < 0)
		wetuwn -EINVAW;

	/* fwom extewnaw ADC */
	wegmap_update_bits(afe->wegmap, AFE_ADDA_TOP_CON0, 0x1, 0x1);
	wegmap_update_bits(afe->wegmap, AFE_ADDA2_TOP_CON0, 0x1, 0x1);

	/* set input */
	vaw = AFE_I2S_CON2_WOW_JITTEW_CWK |
	      AFE_I2S_CON2_WATE(fs) |
	      AFE_I2S_CON2_FOWMAT_I2S;

	wegmap_update_bits(afe->wegmap, AFE_I2S_CON2, ~AFE_I2S_CON2_EN, vaw);

	/* set output */
	vaw = AFE_I2S_CON1_WOW_JITTEW_CWK |
	      AFE_I2S_CON1_WATE(fs) |
	      AFE_I2S_CON1_FOWMAT_I2S;

	wegmap_update_bits(afe->wegmap, AFE_I2S_CON1, ~AFE_I2S_CON1_EN, vaw);
	wetuwn 0;
}

static void mt8173_afe_set_i2s_enabwe(stwuct mtk_base_afe *afe, boow enabwe)
{
	unsigned int vaw;

	wegmap_wead(afe->wegmap, AFE_I2S_CON2, &vaw);
	if (!!(vaw & AFE_I2S_CON2_EN) == enabwe)
		wetuwn;

	/* input */
	wegmap_update_bits(afe->wegmap, AFE_I2S_CON2, 0x1, enabwe);

	/* output */
	wegmap_update_bits(afe->wegmap, AFE_I2S_CON1, 0x1, enabwe);
}

static int mt8173_afe_dais_enabwe_cwks(stwuct mtk_base_afe *afe,
				       stwuct cwk *m_ck, stwuct cwk *b_ck)
{
	int wet;

	if (m_ck) {
		wet = cwk_pwepawe_enabwe(m_ck);
		if (wet) {
			dev_eww(afe->dev, "Faiwed to enabwe m_ck\n");
			wetuwn wet;
		}
	}

	if (b_ck) {
		wet = cwk_pwepawe_enabwe(b_ck);
		if (wet) {
			dev_eww(afe->dev, "Faiwed to enabwe b_ck\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int mt8173_afe_dais_set_cwks(stwuct mtk_base_afe *afe,
				    stwuct cwk *m_ck, unsigned int mck_wate,
				    stwuct cwk *b_ck, unsigned int bck_wate)
{
	int wet;

	if (m_ck) {
		wet = cwk_set_wate(m_ck, mck_wate);
		if (wet) {
			dev_eww(afe->dev, "Faiwed to set m_ck wate\n");
			wetuwn wet;
		}
	}

	if (b_ck) {
		wet = cwk_set_wate(b_ck, bck_wate);
		if (wet) {
			dev_eww(afe->dev, "Faiwed to set b_ck wate\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static void mt8173_afe_dais_disabwe_cwks(stwuct mtk_base_afe *afe,
					 stwuct cwk *m_ck, stwuct cwk *b_ck)
{
	cwk_disabwe_unpwepawe(m_ck);
	cwk_disabwe_unpwepawe(b_ck);
}

static int mt8173_afe_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	if (snd_soc_dai_active(dai))
		wetuwn 0;

	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M, 0);
	wetuwn 0;
}

static void mt8173_afe_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	if (snd_soc_dai_active(dai))
		wetuwn;

	mt8173_afe_set_i2s_enabwe(afe, fawse);
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M);
}

static int mt8173_afe_i2s_pwepawe(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime * const wuntime = substweam->wuntime;
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	mt8173_afe_dais_set_cwks(afe, afe_pwiv->cwocks[MT8173_CWK_I2S1_M],
				 wuntime->wate * 256, NUWW, 0);
	mt8173_afe_dais_set_cwks(afe, afe_pwiv->cwocks[MT8173_CWK_I2S2_M],
				 wuntime->wate * 256, NUWW, 0);
	/* config I2S */
	wet = mt8173_afe_set_i2s(afe, substweam->wuntime->wate);
	if (wet)
		wetuwn wet;

	mt8173_afe_set_i2s_enabwe(afe, twue);

	wetuwn 0;
}

static int mt8173_afe_hdmi_stawtup(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	if (snd_soc_dai_active(dai))
		wetuwn 0;

	mt8173_afe_dais_enabwe_cwks(afe, afe_pwiv->cwocks[MT8173_CWK_I2S3_M],
				    afe_pwiv->cwocks[MT8173_CWK_I2S3_B]);
	wetuwn 0;
}

static void mt8173_afe_hdmi_shutdown(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	if (snd_soc_dai_active(dai))
		wetuwn;

	mt8173_afe_dais_disabwe_cwks(afe, afe_pwiv->cwocks[MT8173_CWK_I2S3_M],
				     afe_pwiv->cwocks[MT8173_CWK_I2S3_B]);
}

static int mt8173_afe_hdmi_pwepawe(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime * const wuntime = substweam->wuntime;
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	unsigned int vaw;

	mt8173_afe_dais_set_cwks(afe, afe_pwiv->cwocks[MT8173_CWK_I2S3_M],
				 wuntime->wate * 128,
				 afe_pwiv->cwocks[MT8173_CWK_I2S3_B],
				 wuntime->wate * wuntime->channews * 32);

	vaw = AFE_TDM_CON1_BCK_INV |
	      AFE_TDM_CON1_WWCK_INV |
	      AFE_TDM_CON1_1_BCK_DEWAY |
	      AFE_TDM_CON1_MSB_AWIGNED | /* I2S mode */
	      AFE_TDM_CON1_WWEN_32BIT |
	      AFE_TDM_CON1_32_BCK_CYCWES |
	      AFE_TDM_CON1_WWCK_WIDTH(32);
	wegmap_update_bits(afe->wegmap, AFE_TDM_CON1, ~AFE_TDM_CON1_EN, vaw);

	/* set tdm2 config */
	switch (wuntime->channews) {
	case 1:
	case 2:
		vaw = AFE_TDM_CH_STAWT_O30_O31;
		vaw |= (AFE_TDM_CH_ZEWO << 4);
		vaw |= (AFE_TDM_CH_ZEWO << 8);
		vaw |= (AFE_TDM_CH_ZEWO << 12);
		bweak;
	case 3:
	case 4:
		vaw = AFE_TDM_CH_STAWT_O30_O31;
		vaw |= (AFE_TDM_CH_STAWT_O32_O33 << 4);
		vaw |= (AFE_TDM_CH_ZEWO << 8);
		vaw |= (AFE_TDM_CH_ZEWO << 12);
		bweak;
	case 5:
	case 6:
		vaw = AFE_TDM_CH_STAWT_O30_O31;
		vaw |= (AFE_TDM_CH_STAWT_O32_O33 << 4);
		vaw |= (AFE_TDM_CH_STAWT_O34_O35 << 8);
		vaw |= (AFE_TDM_CH_ZEWO << 12);
		bweak;
	case 7:
	case 8:
		vaw = AFE_TDM_CH_STAWT_O30_O31;
		vaw |= (AFE_TDM_CH_STAWT_O32_O33 << 4);
		vaw |= (AFE_TDM_CH_STAWT_O34_O35 << 8);
		vaw |= (AFE_TDM_CH_STAWT_O36_O37 << 12);
		bweak;
	defauwt:
		vaw = 0;
	}
	wegmap_update_bits(afe->wegmap, AFE_TDM_CON2, 0x0000ffff, vaw);

	wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0,
			   0x000000f0, wuntime->channews << 4);
	wetuwn 0;
}

static int mt8173_afe_hdmi_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				   stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	dev_info(afe->dev, "%s cmd=%d %s\n", __func__, cmd, dai->name);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF, 0);

		/* set connections:  O30~O37: W/W/WS/WS/C/WFE/CH7/CH8 */
		wegmap_wwite(afe->wegmap, AFE_HDMI_CONN0,
				 AFE_HDMI_CONN0_O30_I30 |
				 AFE_HDMI_CONN0_O31_I31 |
				 AFE_HDMI_CONN0_O32_I34 |
				 AFE_HDMI_CONN0_O33_I35 |
				 AFE_HDMI_CONN0_O34_I32 |
				 AFE_HDMI_CONN0_O35_I33 |
				 AFE_HDMI_CONN0_O36_I36 |
				 AFE_HDMI_CONN0_O37_I37);

		/* enabwe Out contwow */
		wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0, 0x1, 0x1);

		/* enabwe tdm */
		wegmap_update_bits(afe->wegmap, AFE_TDM_CON1, 0x1, 0x1);

		wetuwn 0;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		/* disabwe tdm */
		wegmap_update_bits(afe->wegmap, AFE_TDM_CON1, 0x1, 0);

		/* disabwe Out contwow */
		wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0, 0x1, 0);

		wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF,
				   AUD_TCON0_PDN_HDMI | AUD_TCON0_PDN_SPDF);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt8173_memif_fs(stwuct snd_pcm_substweam *substweam,
			   unsigned int wate)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component = snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(component);
	stwuct mtk_base_afe_memif *memif = &afe->memif[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int fs;

	if (memif->data->id == MT8173_AFE_MEMIF_DAI ||
	    memif->data->id == MT8173_AFE_MEMIF_MOD_DAI) {
		switch (wate) {
		case 8000:
			fs = 0;
			bweak;
		case 16000:
			fs = 1;
			bweak;
		case 32000:
			fs = 2;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		fs = mt8173_afe_i2s_fs(wate);
	}
	wetuwn fs;
}

static int mt8173_iwq_fs(stwuct snd_pcm_substweam *substweam, unsigned int wate)
{
	wetuwn mt8173_afe_i2s_fs(wate);
}

/* BE DAIs */
static const stwuct snd_soc_dai_ops mt8173_afe_i2s_ops = {
	.stawtup	= mt8173_afe_i2s_stawtup,
	.shutdown	= mt8173_afe_i2s_shutdown,
	.pwepawe	= mt8173_afe_i2s_pwepawe,
};

static const stwuct snd_soc_dai_ops mt8173_afe_hdmi_ops = {
	.stawtup	= mt8173_afe_hdmi_stawtup,
	.shutdown	= mt8173_afe_hdmi_shutdown,
	.pwepawe	= mt8173_afe_hdmi_pwepawe,
	.twiggew	= mt8173_afe_hdmi_twiggew,
};

static stwuct snd_soc_dai_dwivew mt8173_afe_pcm_dais[] = {
	/* FE DAIs: memowy intefaces to CPU */
	{
		.name = "DW1", /* downwink 1 */
		.id = MT8173_AFE_MEMIF_DW1,
		.pwayback = {
			.stweam_name = "DW1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &mtk_afe_fe_ops,
	}, {
		.name = "VUW", /* voice upwink */
		.id = MT8173_AFE_MEMIF_VUW,
		.captuwe = {
			.stweam_name = "VUW",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &mtk_afe_fe_ops,
	}, {
	/* BE DAIs */
		.name = "I2S",
		.id = MT8173_AFE_IO_I2S,
		.pwayback = {
			.stweam_name = "I2S Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.captuwe = {
			.stweam_name = "I2S Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &mt8173_afe_i2s_ops,
		.symmetwic_wate = 1,
	},
};

static stwuct snd_soc_dai_dwivew mt8173_afe_hdmi_dais[] = {
	/* FE DAIs */
	{
		.name = "HDMI",
		.id = MT8173_AFE_MEMIF_HDMI,
		.pwayback = {
			.stweam_name = "HDMI",
			.channews_min = 2,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
				SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
				SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
				SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &mtk_afe_fe_ops,
	}, {
	/* BE DAIs */
		.name = "HDMIO",
		.id = MT8173_AFE_IO_HDMI,
		.pwayback = {
			.stweam_name = "HDMIO Pwayback",
			.channews_min = 2,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
				SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
				SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
				SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &mt8173_afe_hdmi_ops,
	},
};

static const stwuct snd_kcontwow_new mt8173_afe_o03_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I05 Switch", AFE_CONN1, 21, 1, 0),
};

static const stwuct snd_kcontwow_new mt8173_afe_o04_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I06 Switch", AFE_CONN2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new mt8173_afe_o09_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I03 Switch", AFE_CONN3, 0, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I17 Switch", AFE_CONN7, 30, 1, 0),
};

static const stwuct snd_kcontwow_new mt8173_afe_o10_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I04 Switch", AFE_CONN3, 3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I18 Switch", AFE_CONN8, 0, 1, 0),
};

static const stwuct snd_soc_dapm_widget mt8173_afe_pcm_widgets[] = {
	/* intew-connections */
	SND_SOC_DAPM_MIXEW("I03", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I04", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I05", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I06", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I17", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I18", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("O03", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o03_mix, AWWAY_SIZE(mt8173_afe_o03_mix)),
	SND_SOC_DAPM_MIXEW("O04", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o04_mix, AWWAY_SIZE(mt8173_afe_o04_mix)),
	SND_SOC_DAPM_MIXEW("O09", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o09_mix, AWWAY_SIZE(mt8173_afe_o09_mix)),
	SND_SOC_DAPM_MIXEW("O10", SND_SOC_NOPM, 0, 0,
			   mt8173_afe_o10_mix, AWWAY_SIZE(mt8173_afe_o10_mix)),
};

static const stwuct snd_soc_dapm_woute mt8173_afe_pcm_woutes[] = {
	{"I05", NUWW, "DW1"},
	{"I06", NUWW, "DW1"},
	{"I2S Pwayback", NUWW, "O03"},
	{"I2S Pwayback", NUWW, "O04"},
	{"VUW", NUWW, "O09"},
	{"VUW", NUWW, "O10"},
	{"I03", NUWW, "I2S Captuwe"},
	{"I04", NUWW, "I2S Captuwe"},
	{"I17", NUWW, "I2S Captuwe"},
	{"I18", NUWW, "I2S Captuwe"},
	{ "O03", "I05 Switch", "I05" },
	{ "O04", "I06 Switch", "I06" },
	{ "O09", "I17 Switch", "I17" },
	{ "O09", "I03 Switch", "I03" },
	{ "O10", "I18 Switch", "I18" },
	{ "O10", "I04 Switch", "I04" },
};

static const stwuct snd_soc_dapm_woute mt8173_afe_hdmi_woutes[] = {
	{"HDMIO Pwayback", NUWW, "HDMI"},
};

static const stwuct snd_soc_component_dwivew mt8173_afe_pcm_dai_component = {
	.name = "mt8173-afe-pcm-dai",
	.dapm_widgets = mt8173_afe_pcm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8173_afe_pcm_widgets),
	.dapm_woutes = mt8173_afe_pcm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8173_afe_pcm_woutes),
	.suspend = mtk_afe_suspend,
	.wesume = mtk_afe_wesume,
};

static const stwuct snd_soc_component_dwivew mt8173_afe_hdmi_dai_component = {
	.name = "mt8173-afe-hdmi-dai",
	.dapm_woutes = mt8173_afe_hdmi_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8173_afe_hdmi_woutes),
	.suspend = mtk_afe_suspend,
	.wesume = mtk_afe_wesume,
};

static const chaw *aud_cwks[MT8173_CWK_NUM] = {
	[MT8173_CWK_INFWASYS_AUD] = "infwa_sys_audio_cwk",
	[MT8173_CWK_TOP_PDN_AUD] = "top_pdn_audio",
	[MT8173_CWK_TOP_PDN_AUD_BUS] = "top_pdn_aud_intbus",
	[MT8173_CWK_I2S0_M] =  "i2s0_m",
	[MT8173_CWK_I2S1_M] =  "i2s1_m",
	[MT8173_CWK_I2S2_M] =  "i2s2_m",
	[MT8173_CWK_I2S3_M] =  "i2s3_m",
	[MT8173_CWK_I2S3_B] =  "i2s3_b",
	[MT8173_CWK_BCK0] =  "bck0",
	[MT8173_CWK_BCK1] =  "bck1",
};

static const stwuct mtk_base_memif_data memif_data[MT8173_AFE_MEMIF_NUM] = {
	{
		.name = "DW1",
		.id = MT8173_AFE_MEMIF_DW1,
		.weg_ofs_base = AFE_DW1_BASE,
		.weg_ofs_cuw = AFE_DW1_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = 0,
		.fs_maskbit = 0xf,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = 21,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 1,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 0,
		.agent_disabwe_weg = -1,
	}, {
		.name = "DW2",
		.id = MT8173_AFE_MEMIF_DW2,
		.weg_ofs_base = AFE_DW2_BASE,
		.weg_ofs_cuw = AFE_DW2_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = 4,
		.fs_maskbit = 0xf,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = 22,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 2,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 1,
		.agent_disabwe_weg = -1,
	}, {
		.name = "VUW",
		.id = MT8173_AFE_MEMIF_VUW,
		.weg_ofs_base = AFE_VUW_BASE,
		.weg_ofs_cuw = AFE_VUW_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = 16,
		.fs_maskbit = 0xf,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = 27,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 3,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 6,
		.agent_disabwe_weg = -1,
	}, {
		.name = "DAI",
		.id = MT8173_AFE_MEMIF_DAI,
		.weg_ofs_base = AFE_DAI_BASE,
		.weg_ofs_cuw = AFE_DAI_CUW,
		.fs_weg = AFE_DAC_CON0,
		.fs_shift = 24,
		.fs_maskbit = 0x3,
		.mono_weg = -1,
		.mono_shift = -1,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 4,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 5,
		.agent_disabwe_weg = -1,
	}, {
		.name = "AWB",
		.id = MT8173_AFE_MEMIF_AWB,
		.weg_ofs_base = AFE_AWB_BASE,
		.weg_ofs_cuw = AFE_AWB_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = 12,
		.fs_maskbit = 0xf,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = 24,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 6,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 3,
		.agent_disabwe_weg = -1,
	}, {
		.name = "MOD_DAI",
		.id = MT8173_AFE_MEMIF_MOD_DAI,
		.weg_ofs_base = AFE_MOD_PCM_BASE,
		.weg_ofs_cuw = AFE_MOD_PCM_CUW,
		.fs_weg = AFE_DAC_CON1,
		.fs_shift = 30,
		.fs_maskbit = 0x3,
		.mono_weg = AFE_DAC_CON1,
		.mono_shift = 30,
		.hd_weg = -1,
		.enabwe_weg = AFE_DAC_CON0,
		.enabwe_shift = 7,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 4,
		.agent_disabwe_weg = -1,
	}, {
		.name = "HDMI",
		.id = MT8173_AFE_MEMIF_HDMI,
		.weg_ofs_base = AFE_HDMI_OUT_BASE,
		.weg_ofs_cuw = AFE_HDMI_OUT_CUW,
		.fs_weg = -1,
		.fs_shift = -1,
		.fs_maskbit = -1,
		.mono_weg = -1,
		.mono_shift = -1,
		.hd_weg = -1,
		.enabwe_weg = -1,
		.msb_weg = AFE_MEMIF_MSB,
		.msb_shift = 8,
		.agent_disabwe_weg = -1,
	},
};

static const stwuct mtk_base_iwq_data iwq_data[MT8173_AFE_IWQ_NUM] = {
	{
		.id = MT8173_AFE_IWQ_DW1,
		.iwq_cnt_weg = AFE_IWQ_CNT1,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 0,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 4,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 0,
	}, {
		.id = MT8173_AFE_IWQ_DW2,
		.iwq_cnt_weg = AFE_IWQ_CNT1,
		.iwq_cnt_shift = 20,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 2,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 16,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 2,

	}, {
		.id = MT8173_AFE_IWQ_VUW,
		.iwq_cnt_weg = AFE_IWQ_CNT2,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 1,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 8,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 1,
	}, {
		.id = MT8173_AFE_IWQ_DAI,
		.iwq_cnt_weg = AFE_IWQ_CNT2,
		.iwq_cnt_shift = 20,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 3,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 20,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 3,
	}, {
		.id = MT8173_AFE_IWQ_AWB,
		.iwq_cnt_weg = AFE_IWQ_CNT7,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 14,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 24,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 6,
	}, {
		.id = MT8173_AFE_IWQ_DAI,
		.iwq_cnt_weg = AFE_IWQ_CNT2,
		.iwq_cnt_shift = 20,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 3,
		.iwq_fs_weg = AFE_IWQ_MCU_CON,
		.iwq_fs_shift = 20,
		.iwq_fs_maskbit = 0xf,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 3,
	}, {
		.id = MT8173_AFE_IWQ_HDMI,
		.iwq_cnt_weg = AFE_IWQ_CNT5,
		.iwq_cnt_shift = 0,
		.iwq_cnt_maskbit = 0x3ffff,
		.iwq_en_weg = AFE_IWQ_MCU_CON,
		.iwq_en_shift = 12,
		.iwq_fs_weg = -1,
		.iwq_fs_maskbit = -1,
		.iwq_cww_weg = AFE_IWQ_CWW,
		.iwq_cww_shift = 4,
	},
};

static const stwuct wegmap_config mt8173_afe_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = AFE_ADDA2_TOP_CON0,
	.cache_type = WEGCACHE_NONE,
};

static iwqwetuwn_t mt8173_afe_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mtk_base_afe *afe = dev_id;
	unsigned int weg_vawue;
	int i, wet;

	wet = wegmap_wead(afe->wegmap, AFE_IWQ_STATUS, &weg_vawue);
	if (wet) {
		dev_eww(afe->dev, "%s iwq status eww\n", __func__);
		weg_vawue = AFE_IWQ_STATUS_BITS;
		goto eww_iwq;
	}

	fow (i = 0; i < MT8173_AFE_MEMIF_NUM; i++) {
		stwuct mtk_base_afe_memif *memif = &afe->memif[i];
		stwuct mtk_base_afe_iwq *iwq_p;

		if (memif->iwq_usage < 0)
			continue;

		iwq_p = &afe->iwqs[memif->iwq_usage];

		if (!(weg_vawue & (1 << iwq_p->iwq_data->iwq_cww_shift)))
			continue;

		snd_pcm_pewiod_ewapsed(memif->substweam);
	}

eww_iwq:
	/* cweaw iwq */
	wegmap_wwite(afe->wegmap, AFE_IWQ_CWW,
		     weg_vawue & AFE_IWQ_STATUS_BITS);

	wetuwn IWQ_HANDWED;
}

static int mt8173_afe_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	/* disabwe AFE */
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0);

	/* disabwe AFE cwk */
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_AFE, AUD_TCON0_PDN_AFE);

	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_I2S1_M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_I2S2_M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_BCK0]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_BCK1]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD_BUS]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_INFWASYS_AUD]);
	wetuwn 0;
}

static int mt8173_afe_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dev);
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_INFWASYS_AUD]);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD_BUS]);
	if (wet)
		goto eww_infwa;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD]);
	if (wet)
		goto eww_top_aud_bus;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_BCK0]);
	if (wet)
		goto eww_top_aud;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_BCK1]);
	if (wet)
		goto eww_bck0;
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_I2S1_M]);
	if (wet)
		goto eww_i2s1_m;
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwocks[MT8173_CWK_I2S2_M]);
	if (wet)
		goto eww_i2s2_m;

	/* enabwe AFE cwk */
	wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON0, AUD_TCON0_PDN_AFE, 0);

	/* set O3/O4 16bits */
	wegmap_update_bits(afe->wegmap, AFE_CONN_24BIT,
			   AFE_CONN_24BIT_O03 | AFE_CONN_24BIT_O04, 0);

	/* unmask aww IWQs */
	wegmap_update_bits(afe->wegmap, AFE_IWQ_MCU_EN, 0xff, 0xff);

	/* enabwe AFE */
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x1);
	wetuwn 0;

eww_i2s1_m:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_I2S1_M]);
eww_i2s2_m:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_I2S2_M]);
eww_bck0:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_BCK0]);
eww_top_aud:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD]);
eww_top_aud_bus:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_TOP_PDN_AUD_BUS]);
eww_infwa:
	cwk_disabwe_unpwepawe(afe_pwiv->cwocks[MT8173_CWK_INFWASYS_AUD]);
	wetuwn wet;
}

static int mt8173_afe_init_audio_cwk(stwuct mtk_base_afe *afe)
{
	size_t i;
	stwuct mt8173_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	fow (i = 0; i < AWWAY_SIZE(aud_cwks); i++) {
		afe_pwiv->cwocks[i] = devm_cwk_get(afe->dev, aud_cwks[i]);
		if (IS_EWW(afe_pwiv->cwocks[i])) {
			dev_eww(afe->dev, "%s devm_cwk_get %s faiw\n",
				__func__, aud_cwks[i]);
			wetuwn PTW_EWW(afe_pwiv->cwocks[i]);
		}
	}
	cwk_set_wate(afe_pwiv->cwocks[MT8173_CWK_BCK0], 22579200); /* 22M */
	cwk_set_wate(afe_pwiv->cwocks[MT8173_CWK_BCK1], 24576000); /* 24M */
	wetuwn 0;
}

static int mt8173_afe_pcm_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i;
	int iwq_id;
	stwuct mtk_base_afe *afe;
	stwuct mt8173_afe_pwivate *afe_pwiv;
	stwuct snd_soc_component *comp_pcm, *comp_hdmi;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(33));
	if (wet)
		wetuwn wet;

	afe = devm_kzawwoc(&pdev->dev, sizeof(*afe), GFP_KEWNEW);
	if (!afe)
		wetuwn -ENOMEM;

	afe->pwatfowm_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*afe_pwiv),
					  GFP_KEWNEW);
	afe_pwiv = afe->pwatfowm_pwiv;
	if (!afe_pwiv)
		wetuwn -ENOMEM;

	afe->dev = &pdev->dev;

	iwq_id = pwatfowm_get_iwq(pdev, 0);
	if (iwq_id <= 0)
		wetuwn iwq_id < 0 ? iwq_id : -ENXIO;

	afe->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(afe->base_addw))
		wetuwn PTW_EWW(afe->base_addw);

	afe->wegmap = devm_wegmap_init_mmio(&pdev->dev, afe->base_addw,
		&mt8173_afe_wegmap_config);
	if (IS_EWW(afe->wegmap))
		wetuwn PTW_EWW(afe->wegmap);

	/* initiaw audio wewated cwock */
	wet = mt8173_afe_init_audio_cwk(afe);
	if (wet) {
		dev_eww(afe->dev, "mt8173_afe_init_audio_cwk faiw\n");
		wetuwn wet;
	}

	/* memif % iwq initiawize*/
	afe->memif_size = MT8173_AFE_MEMIF_NUM;
	afe->memif = devm_kcawwoc(afe->dev, afe->memif_size,
				  sizeof(*afe->memif), GFP_KEWNEW);
	if (!afe->memif)
		wetuwn -ENOMEM;

	afe->iwqs_size = MT8173_AFE_IWQ_NUM;
	afe->iwqs = devm_kcawwoc(afe->dev, afe->iwqs_size,
				 sizeof(*afe->iwqs), GFP_KEWNEW);
	if (!afe->iwqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < afe->iwqs_size; i++) {
		afe->memif[i].data = &memif_data[i];
		afe->iwqs[i].iwq_data = &iwq_data[i];
		afe->iwqs[i].iwq_occupyed = twue;
		afe->memif[i].iwq_usage = i;
		afe->memif[i].const_iwq = 1;
	}

	afe->mtk_afe_hawdwawe = &mt8173_afe_hawdwawe;
	afe->memif_fs = mt8173_memif_fs;
	afe->iwq_fs = mt8173_iwq_fs;

	pwatfowm_set_dwvdata(pdev, afe);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = mt8173_afe_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	afe->weg_back_up_wist = mt8173_afe_backup_wist;
	afe->weg_back_up_wist_num = AWWAY_SIZE(mt8173_afe_backup_wist);
	afe->wuntime_wesume = mt8173_afe_wuntime_wesume;
	afe->wuntime_suspend = mt8173_afe_wuntime_suspend;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					 &mtk_afe_pcm_pwatfowm,
					 NUWW, 0);
	if (wet)
		goto eww_pm_disabwe;

	comp_pcm = devm_kzawwoc(&pdev->dev, sizeof(*comp_pcm), GFP_KEWNEW);
	if (!comp_pcm) {
		wet = -ENOMEM;
		goto eww_pm_disabwe;
	}

	wet = snd_soc_component_initiawize(comp_pcm,
					   &mt8173_afe_pcm_dai_component,
					   &pdev->dev);
	if (wet)
		goto eww_pm_disabwe;

#ifdef CONFIG_DEBUG_FS
	comp_pcm->debugfs_pwefix = "pcm";
#endif

	wet = snd_soc_add_component(comp_pcm,
				    mt8173_afe_pcm_dais,
				    AWWAY_SIZE(mt8173_afe_pcm_dais));
	if (wet)
		goto eww_pm_disabwe;

	comp_hdmi = devm_kzawwoc(&pdev->dev, sizeof(*comp_hdmi), GFP_KEWNEW);
	if (!comp_hdmi) {
		wet = -ENOMEM;
		goto eww_cweanup_components;
	}

	wet = snd_soc_component_initiawize(comp_hdmi,
					   &mt8173_afe_hdmi_dai_component,
					   &pdev->dev);
	if (wet)
		goto eww_cweanup_components;

#ifdef CONFIG_DEBUG_FS
	comp_hdmi->debugfs_pwefix = "hdmi";
#endif

	wet = snd_soc_add_component(comp_hdmi,
				    mt8173_afe_hdmi_dais,
				    AWWAY_SIZE(mt8173_afe_hdmi_dais));
	if (wet)
		goto eww_cweanup_components;

	wet = devm_wequest_iwq(afe->dev, iwq_id, mt8173_afe_iwq_handwew,
			       0, "Afe_ISW_Handwe", (void *)afe);
	if (wet) {
		dev_eww(afe->dev, "couwd not wequest_iwq\n");
		goto eww_cweanup_components;
	}

	dev_info(&pdev->dev, "MT8173 AFE dwivew initiawized.\n");
	wetuwn 0;

eww_cweanup_components:
	snd_soc_unwegistew_component(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void mt8173_afe_pcm_dev_wemove(stwuct pwatfowm_device *pdev)
{
	snd_soc_unwegistew_component(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		mt8173_afe_wuntime_suspend(&pdev->dev);
}

static const stwuct of_device_id mt8173_afe_pcm_dt_match[] = {
	{ .compatibwe = "mediatek,mt8173-afe-pcm", },
	{ }
};
MODUWE_DEVICE_TABWE(of, mt8173_afe_pcm_dt_match);

static const stwuct dev_pm_ops mt8173_afe_pm_ops = {
	SET_WUNTIME_PM_OPS(mt8173_afe_wuntime_suspend,
			   mt8173_afe_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mt8173_afe_pcm_dwivew = {
	.dwivew = {
		   .name = "mt8173-afe-pcm",
		   .of_match_tabwe = mt8173_afe_pcm_dt_match,
		   .pm = &mt8173_afe_pm_ops,
	},
	.pwobe = mt8173_afe_pcm_dev_pwobe,
	.wemove_new = mt8173_afe_pcm_dev_wemove,
};

moduwe_pwatfowm_dwivew(mt8173_afe_pcm_dwivew);

MODUWE_DESCWIPTION("Mediatek AWSA SoC AFE pwatfowm dwivew");
MODUWE_AUTHOW("Kowo Chen <kowo.chen@mediatek.com>");
MODUWE_WICENSE("GPW v2");
