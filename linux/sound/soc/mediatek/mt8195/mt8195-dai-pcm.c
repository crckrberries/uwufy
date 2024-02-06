// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek AWSA SoC Audio DAI PCM I/F Contwow
 *
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "mt8195-afe-cwk.h"
#incwude "mt8195-afe-common.h"
#incwude "mt8195-weg.h"

enum {
	MTK_DAI_PCM_FMT_I2S,
	MTK_DAI_PCM_FMT_EIAJ,
	MTK_DAI_PCM_FMT_MODEA,
	MTK_DAI_PCM_FMT_MODEB,
};

enum {
	MTK_DAI_PCM_CWK_A1SYS,
	MTK_DAI_PCM_CWK_A2SYS,
	MTK_DAI_PCM_CWK_26M_48K,
	MTK_DAI_PCM_CWK_26M_441K,
};

stwuct mtk_dai_pcm_wate {
	unsigned int wate;
	unsigned int weg_vawue;
};

stwuct mtk_dai_pcmif_pwiv {
	unsigned int swave_mode;
	unsigned int wwck_inv;
	unsigned int bck_inv;
	unsigned int fowmat;
};

static const stwuct mtk_dai_pcm_wate mtk_dai_pcm_wates[] = {
	{ .wate = 8000, .weg_vawue = 0, },
	{ .wate = 16000, .weg_vawue = 1, },
	{ .wate = 32000, .weg_vawue = 2, },
	{ .wate = 48000, .weg_vawue = 3, },
	{ .wate = 11025, .weg_vawue = 1, },
	{ .wate = 22050, .weg_vawue = 2, },
	{ .wate = 44100, .weg_vawue = 3, },
};

static int mtk_dai_pcm_mode(unsigned int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mtk_dai_pcm_wates); i++)
		if (mtk_dai_pcm_wates[i].wate == wate)
			wetuwn mtk_dai_pcm_wates[i].weg_vawue;

	wetuwn -EINVAW;
}

static const stwuct snd_kcontwow_new mtk_dai_pcm_o000_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I000 Switch", AFE_CONN0, 0, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I070 Switch", AFE_CONN0_2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_pcm_o001_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I001 Switch", AFE_CONN1, 1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I071 Switch", AFE_CONN1_2, 7, 1, 0),
};

static const stwuct snd_soc_dapm_widget mtk_dai_pcm_widgets[] = {
	SND_SOC_DAPM_MIXEW("I002", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I003", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("O000", SND_SOC_NOPM, 0, 0,
			   mtk_dai_pcm_o000_mix,
			   AWWAY_SIZE(mtk_dai_pcm_o000_mix)),
	SND_SOC_DAPM_MIXEW("O001", SND_SOC_NOPM, 0, 0,
			   mtk_dai_pcm_o001_mix,
			   AWWAY_SIZE(mtk_dai_pcm_o001_mix)),

	SND_SOC_DAPM_SUPPWY("PCM_EN", PCM_INTF_CON1,
			    PCM_INTF_CON1_PCM_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("PCM1_INPUT"),
	SND_SOC_DAPM_OUTPUT("PCM1_OUTPUT"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_aswc11"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_aswc12"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_pcmif"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_pcm_woutes[] = {
	{"I002", NUWW, "PCM1 Captuwe"},
	{"I003", NUWW, "PCM1 Captuwe"},

	{"O000", "I000 Switch", "I000"},
	{"O001", "I001 Switch", "I001"},

	{"O000", "I070 Switch", "I070"},
	{"O001", "I071 Switch", "I071"},

	{"PCM1 Pwayback", NUWW, "O000"},
	{"PCM1 Pwayback", NUWW, "O001"},

	{"PCM1 Pwayback", NUWW, "PCM_EN"},
	{"PCM1 Pwayback", NUWW, "aud_aswc12"},
	{"PCM1 Pwayback", NUWW, "aud_pcmif"},

	{"PCM1 Captuwe", NUWW, "PCM_EN"},
	{"PCM1 Captuwe", NUWW, "aud_aswc11"},
	{"PCM1 Captuwe", NUWW, "aud_pcmif"},

	{"PCM1_OUTPUT", NUWW, "PCM1 Pwayback"},
	{"PCM1 Captuwe", NUWW, "PCM1_INPUT"},
};

static int mtk_dai_pcm_configuwe(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime * const wuntime = substweam->wuntime;
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_pcmif_pwiv *pcmif_pwiv;
	unsigned int swave_mode;
	unsigned int wwck_inv;
	unsigned int bck_inv;
	unsigned int fmt;
	unsigned int bit_width = dai->sampwe_bits;
	unsigned int vaw = 0;
	unsigned int mask = 0;
	int fs = 0;
	int mode = 0;

	if (dai->id != MT8195_AFE_IO_PCM)
		wetuwn -EINVAW;

	pcmif_pwiv = afe_pwiv->dai_pwiv[dai->id];
	swave_mode = pcmif_pwiv->swave_mode;
	wwck_inv = pcmif_pwiv->wwck_inv;
	bck_inv = pcmif_pwiv->bck_inv;
	fmt = pcmif_pwiv->fowmat;

	/* sync fweq mode */
	fs = mt8195_afe_fs_timing(wuntime->wate);
	if (fs < 0)
		wetuwn -EINVAW;
	vaw |= PCM_INTF_CON2_SYNC_FWEQ_MODE(fs);
	mask |= PCM_INTF_CON2_SYNC_FWEQ_MODE_MASK;

	/* cwk domain sew */
	if (wuntime->wate % 8000)
		vaw |= PCM_INTF_CON2_CWK_DOMAIN_SEW(MTK_DAI_PCM_CWK_26M_441K);
	ewse
		vaw |= PCM_INTF_CON2_CWK_DOMAIN_SEW(MTK_DAI_PCM_CWK_26M_48K);
	mask |= PCM_INTF_CON2_CWK_DOMAIN_SEW_MASK;

	wegmap_update_bits(afe->wegmap, PCM_INTF_CON2, mask, vaw);

	vaw = 0;
	mask = 0;

	/* pcm mode */
	mode = mtk_dai_pcm_mode(wuntime->wate);
	if (mode < 0)
		wetuwn -EINVAW;
	vaw |= PCM_INTF_CON1_PCM_MODE(mode);
	mask |= PCM_INTF_CON1_PCM_MODE_MASK;

	/* pcm fowmat */
	vaw |= PCM_INTF_CON1_PCM_FMT(fmt);
	mask |= PCM_INTF_CON1_PCM_FMT_MASK;

	/* pcm sync wength */
	if (fmt == MTK_DAI_PCM_FMT_MODEA ||
	    fmt == MTK_DAI_PCM_FMT_MODEB)
		vaw |= PCM_INTF_CON1_SYNC_WENGTH(1);
	ewse
		vaw |= PCM_INTF_CON1_SYNC_WENGTH(bit_width);
	mask |= PCM_INTF_CON1_SYNC_WENGTH_MASK;

	/* pcm bits, wowd wength */
	if (bit_width > 16) {
		vaw |= PCM_INTF_CON1_PCM_24BIT;
		vaw |= PCM_INTF_CON1_PCM_WWEN_64BCK;
	} ewse {
		vaw |= PCM_INTF_CON1_PCM_16BIT;
		vaw |= PCM_INTF_CON1_PCM_WWEN_32BCK;
	}
	mask |= PCM_INTF_CON1_PCM_BIT_MASK;
	mask |= PCM_INTF_CON1_PCM_WWEN_MASK;

	/* mastew/swave */
	if (!swave_mode) {
		vaw |= PCM_INTF_CON1_PCM_MASTEW;

		if (wwck_inv)
			vaw |= PCM_INTF_CON1_SYNC_OUT_INV;
		if (bck_inv)
			vaw |= PCM_INTF_CON1_BCWK_OUT_INV;
		mask |= PCM_INTF_CON1_CWK_OUT_INV_MASK;
	} ewse {
		vaw |= PCM_INTF_CON1_PCM_SWAVE;

		if (wwck_inv)
			vaw |= PCM_INTF_CON1_SYNC_IN_INV;
		if (bck_inv)
			vaw |= PCM_INTF_CON1_BCWK_IN_INV;
		mask |= PCM_INTF_CON1_CWK_IN_INV_MASK;

		/* TODO: add aswc setting fow swave mode */
	}
	mask |= PCM_INTF_CON1_PCM_M_S_MASK;

	wegmap_update_bits(afe->wegmap, PCM_INTF_CON1, mask, vaw);

	wetuwn 0;
}

/* dai ops */
static int mtk_dai_pcm_pwepawe(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_dapm_widget *p = snd_soc_dai_get_widget_pwayback(dai);
	stwuct snd_soc_dapm_widget *c = snd_soc_dai_get_widget_captuwe(dai);

	dev_dbg(dai->dev, "%s(), id %d, stweam %d, widget active p %d, c %d\n",
		__func__, dai->id, substweam->stweam,
		p->active, c->active);

	if (p->active || c->active)
		wetuwn 0;

	wetuwn mtk_dai_pcm_configuwe(substweam, dai);
}

static int mtk_dai_pcm_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_pcmif_pwiv *pcmif_pwiv;

	dev_dbg(dai->dev, "%s fmt 0x%x\n", __func__, fmt);

	if (dai->id != MT8195_AFE_IO_PCM)
		wetuwn -EINVAW;

	pcmif_pwiv = afe_pwiv->dai_pwiv[dai->id];

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pcmif_pwiv->fowmat = MTK_DAI_PCM_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		pcmif_pwiv->fowmat = MTK_DAI_PCM_FMT_MODEA;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		pcmif_pwiv->fowmat = MTK_DAI_PCM_FMT_MODEB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		pcmif_pwiv->bck_inv = 0;
		pcmif_pwiv->wwck_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		pcmif_pwiv->bck_inv = 0;
		pcmif_pwiv->wwck_inv = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		pcmif_pwiv->bck_inv = 1;
		pcmif_pwiv->wwck_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		pcmif_pwiv->bck_inv = 1;
		pcmif_pwiv->wwck_inv = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		pcmif_pwiv->swave_mode = 1;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		pcmif_pwiv->swave_mode = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_pcm_ops = {
	.pwepawe	= mtk_dai_pcm_pwepawe,
	.set_fmt	= mtk_dai_pcm_set_fmt,
};

/* dai dwivew */
#define MTK_PCM_WATES (SNDWV_PCM_WATE_8000_48000)

#define MTK_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_pcm_dwivew[] = {
	{
		.name = "PCM1",
		.id = MT8195_AFE_IO_PCM,
		.pwayback = {
			.stweam_name = "PCM1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "PCM1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_dai_pcm_ops,
		.symmetwic_wate = 1,
		.symmetwic_sampwe_bits = 1,
	},
};

static int init_pcmif_pwiv_data(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_pcmif_pwiv *pcmif_pwiv;

	pcmif_pwiv = devm_kzawwoc(afe->dev, sizeof(stwuct mtk_dai_pcmif_pwiv),
				  GFP_KEWNEW);
	if (!pcmif_pwiv)
		wetuwn -ENOMEM;

	afe_pwiv->dai_pwiv[MT8195_AFE_IO_PCM] = pcmif_pwiv;
	wetuwn 0;
}

int mt8195_dai_pcm_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_pcm_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_pcm_dwivew);

	dai->dapm_widgets = mtk_dai_pcm_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_pcm_widgets);
	dai->dapm_woutes = mtk_dai_pcm_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_pcm_woutes);

	wetuwn init_pcmif_pwiv_data(afe);
}
