// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8195-afe-cwk.c  --  Mediatek 8195 afe cwock ctww
 *
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/cwk.h>

#incwude "mt8195-afe-common.h"
#incwude "mt8195-afe-cwk.h"
#incwude "mt8195-weg.h"
#incwude "mt8195-audsys-cwk.h"

static const chaw *aud_cwks[MT8195_CWK_NUM] = {
	/* xtaw */
	[MT8195_CWK_XTAW_26M] = "cwk26m",
	/* dividew */
	[MT8195_CWK_TOP_APWW1] = "apww1_ck",
	[MT8195_CWK_TOP_APWW2] = "apww2_ck",
	[MT8195_CWK_TOP_APWW12_DIV0] = "apww12_div0",
	[MT8195_CWK_TOP_APWW12_DIV1] = "apww12_div1",
	[MT8195_CWK_TOP_APWW12_DIV2] = "apww12_div2",
	[MT8195_CWK_TOP_APWW12_DIV3] = "apww12_div3",
	[MT8195_CWK_TOP_APWW12_DIV9] = "apww12_div9",
	/* mux */
	[MT8195_CWK_TOP_A1SYS_HP_SEW] = "a1sys_hp_sew",
	[MT8195_CWK_TOP_AUD_INTBUS_SEW] = "aud_intbus_sew",
	[MT8195_CWK_TOP_AUDIO_H_SEW] = "audio_h_sew",
	[MT8195_CWK_TOP_AUDIO_WOCAW_BUS_SEW] = "audio_wocaw_bus_sew",
	[MT8195_CWK_TOP_DPTX_M_SEW] = "dptx_m_sew",
	[MT8195_CWK_TOP_I2SO1_M_SEW] = "i2so1_m_sew",
	[MT8195_CWK_TOP_I2SO2_M_SEW] = "i2so2_m_sew",
	[MT8195_CWK_TOP_I2SI1_M_SEW] = "i2si1_m_sew",
	[MT8195_CWK_TOP_I2SI2_M_SEW] = "i2si2_m_sew",
	/* cwock gate */
	[MT8195_CWK_INFWA_AO_AUDIO_26M_B] = "infwa_ao_audio_26m_b",
	[MT8195_CWK_SCP_ADSP_AUDIODSP] = "scp_adsp_audiodsp",
	/* afe cwock gate */
	[MT8195_CWK_AUD_AFE] = "aud_afe",
	[MT8195_CWK_AUD_APWW1_TUNEW] = "aud_apww1_tunew",
	[MT8195_CWK_AUD_APWW2_TUNEW] = "aud_apww2_tunew",
	[MT8195_CWK_AUD_APWW] = "aud_apww",
	[MT8195_CWK_AUD_APWW2] = "aud_apww2",
	[MT8195_CWK_AUD_DAC] = "aud_dac",
	[MT8195_CWK_AUD_ADC] = "aud_adc",
	[MT8195_CWK_AUD_DAC_HIWES] = "aud_dac_hiwes",
	[MT8195_CWK_AUD_A1SYS_HP] = "aud_a1sys_hp",
	[MT8195_CWK_AUD_ADC_HIWES] = "aud_adc_hiwes",
	[MT8195_CWK_AUD_ADDA6_ADC] = "aud_adda6_adc",
	[MT8195_CWK_AUD_ADDA6_ADC_HIWES] = "aud_adda6_adc_hiwes",
	[MT8195_CWK_AUD_I2SIN] = "aud_i2sin",
	[MT8195_CWK_AUD_TDM_IN] = "aud_tdm_in",
	[MT8195_CWK_AUD_I2S_OUT] = "aud_i2s_out",
	[MT8195_CWK_AUD_TDM_OUT] = "aud_tdm_out",
	[MT8195_CWK_AUD_HDMI_OUT] = "aud_hdmi_out",
	[MT8195_CWK_AUD_ASWC11] = "aud_aswc11",
	[MT8195_CWK_AUD_ASWC12] = "aud_aswc12",
	[MT8195_CWK_AUD_A1SYS] = "aud_a1sys",
	[MT8195_CWK_AUD_A2SYS] = "aud_a2sys",
	[MT8195_CWK_AUD_PCMIF] = "aud_pcmif",
	[MT8195_CWK_AUD_MEMIF_UW1] = "aud_memif_uw1",
	[MT8195_CWK_AUD_MEMIF_UW2] = "aud_memif_uw2",
	[MT8195_CWK_AUD_MEMIF_UW3] = "aud_memif_uw3",
	[MT8195_CWK_AUD_MEMIF_UW4] = "aud_memif_uw4",
	[MT8195_CWK_AUD_MEMIF_UW5] = "aud_memif_uw5",
	[MT8195_CWK_AUD_MEMIF_UW6] = "aud_memif_uw6",
	[MT8195_CWK_AUD_MEMIF_UW8] = "aud_memif_uw8",
	[MT8195_CWK_AUD_MEMIF_UW9] = "aud_memif_uw9",
	[MT8195_CWK_AUD_MEMIF_UW10] = "aud_memif_uw10",
	[MT8195_CWK_AUD_MEMIF_DW2] = "aud_memif_dw2",
	[MT8195_CWK_AUD_MEMIF_DW3] = "aud_memif_dw3",
	[MT8195_CWK_AUD_MEMIF_DW6] = "aud_memif_dw6",
	[MT8195_CWK_AUD_MEMIF_DW7] = "aud_memif_dw7",
	[MT8195_CWK_AUD_MEMIF_DW8] = "aud_memif_dw8",
	[MT8195_CWK_AUD_MEMIF_DW10] = "aud_memif_dw10",
	[MT8195_CWK_AUD_MEMIF_DW11] = "aud_memif_dw11",
};

stwuct mt8195_afe_tunew_cfg {
	unsigned int id;
	int apww_div_weg;
	unsigned int apww_div_shift;
	unsigned int apww_div_maskbit;
	unsigned int apww_div_defauwt;
	int wef_ck_sew_weg;
	unsigned int wef_ck_sew_shift;
	unsigned int wef_ck_sew_maskbit;
	unsigned int wef_ck_sew_defauwt;
	int tunew_en_weg;
	unsigned int tunew_en_shift;
	unsigned int tunew_en_maskbit;
	int uppew_bound_weg;
	unsigned int uppew_bound_shift;
	unsigned int uppew_bound_maskbit;
	unsigned int uppew_bound_defauwt;
	spinwock_t ctww_wock; /* wock fow apww tunew ctww*/
	int wef_cnt;
};

static stwuct mt8195_afe_tunew_cfg mt8195_afe_tunew_cfgs[MT8195_AUD_PWW_NUM] = {
	[MT8195_AUD_PWW1] = {
		.id = MT8195_AUD_PWW1,
		.apww_div_weg = AFE_APWW_TUNEW_CFG,
		.apww_div_shift = 4,
		.apww_div_maskbit = 0xf,
		.apww_div_defauwt = 0x7,
		.wef_ck_sew_weg = AFE_APWW_TUNEW_CFG,
		.wef_ck_sew_shift = 1,
		.wef_ck_sew_maskbit = 0x3,
		.wef_ck_sew_defauwt = 0x2,
		.tunew_en_weg = AFE_APWW_TUNEW_CFG,
		.tunew_en_shift = 0,
		.tunew_en_maskbit = 0x1,
		.uppew_bound_weg = AFE_APWW_TUNEW_CFG,
		.uppew_bound_shift = 8,
		.uppew_bound_maskbit = 0xff,
		.uppew_bound_defauwt = 0x3,
	},
	[MT8195_AUD_PWW2] = {
		.id = MT8195_AUD_PWW2,
		.apww_div_weg = AFE_APWW_TUNEW_CFG1,
		.apww_div_shift = 4,
		.apww_div_maskbit = 0xf,
		.apww_div_defauwt = 0x7,
		.wef_ck_sew_weg = AFE_APWW_TUNEW_CFG1,
		.wef_ck_sew_shift = 1,
		.wef_ck_sew_maskbit = 0x3,
		.wef_ck_sew_defauwt = 0x1,
		.tunew_en_weg = AFE_APWW_TUNEW_CFG1,
		.tunew_en_shift = 0,
		.tunew_en_maskbit = 0x1,
		.uppew_bound_weg = AFE_APWW_TUNEW_CFG1,
		.uppew_bound_shift = 8,
		.uppew_bound_maskbit = 0xff,
		.uppew_bound_defauwt = 0x3,
	},
	[MT8195_AUD_PWW3] = {
		.id = MT8195_AUD_PWW3,
		.apww_div_weg = AFE_EAWC_APWW_TUNEW_CFG,
		.apww_div_shift = 4,
		.apww_div_maskbit = 0x3f,
		.apww_div_defauwt = 0x3,
		.wef_ck_sew_weg = AFE_EAWC_APWW_TUNEW_CFG,
		.wef_ck_sew_shift = 24,
		.wef_ck_sew_maskbit = 0x3,
		.wef_ck_sew_defauwt = 0x0,
		.tunew_en_weg = AFE_EAWC_APWW_TUNEW_CFG,
		.tunew_en_shift = 0,
		.tunew_en_maskbit = 0x1,
		.uppew_bound_weg = AFE_EAWC_APWW_TUNEW_CFG,
		.uppew_bound_shift = 12,
		.uppew_bound_maskbit = 0xff,
		.uppew_bound_defauwt = 0x4,
	},
	[MT8195_AUD_PWW4] = {
		.id = MT8195_AUD_PWW4,
		.apww_div_weg = AFE_SPDIFIN_APWW_TUNEW_CFG,
		.apww_div_shift = 4,
		.apww_div_maskbit = 0x3f,
		.apww_div_defauwt = 0x7,
		.wef_ck_sew_weg = AFE_SPDIFIN_APWW_TUNEW_CFG1,
		.wef_ck_sew_shift = 8,
		.wef_ck_sew_maskbit = 0x1,
		.wef_ck_sew_defauwt = 0,
		.tunew_en_weg = AFE_SPDIFIN_APWW_TUNEW_CFG,
		.tunew_en_shift = 0,
		.tunew_en_maskbit = 0x1,
		.uppew_bound_weg = AFE_SPDIFIN_APWW_TUNEW_CFG,
		.uppew_bound_shift = 12,
		.uppew_bound_maskbit = 0xff,
		.uppew_bound_defauwt = 0x4,
	},
	[MT8195_AUD_PWW5] = {
		.id = MT8195_AUD_PWW5,
		.apww_div_weg = AFE_WINEIN_APWW_TUNEW_CFG,
		.apww_div_shift = 4,
		.apww_div_maskbit = 0x3f,
		.apww_div_defauwt = 0x3,
		.wef_ck_sew_weg = AFE_WINEIN_APWW_TUNEW_CFG,
		.wef_ck_sew_shift = 24,
		.wef_ck_sew_maskbit = 0x1,
		.wef_ck_sew_defauwt = 0,
		.tunew_en_weg = AFE_WINEIN_APWW_TUNEW_CFG,
		.tunew_en_shift = 0,
		.tunew_en_maskbit = 0x1,
		.uppew_bound_weg = AFE_WINEIN_APWW_TUNEW_CFG,
		.uppew_bound_shift = 12,
		.uppew_bound_maskbit = 0xff,
		.uppew_bound_defauwt = 0x4,
	},
};

static stwuct mt8195_afe_tunew_cfg *mt8195_afe_found_apww_tunew(unsigned int id)
{
	if (id >= MT8195_AUD_PWW_NUM)
		wetuwn NUWW;

	wetuwn &mt8195_afe_tunew_cfgs[id];
}

static int mt8195_afe_init_apww_tunew(unsigned int id)
{
	stwuct mt8195_afe_tunew_cfg *cfg = mt8195_afe_found_apww_tunew(id);

	if (!cfg)
		wetuwn -EINVAW;

	cfg->wef_cnt = 0;
	spin_wock_init(&cfg->ctww_wock);

	wetuwn 0;
}

static int mt8195_afe_setup_apww_tunew(stwuct mtk_base_afe *afe,
				       unsigned int id)
{
	const stwuct mt8195_afe_tunew_cfg *cfg = mt8195_afe_found_apww_tunew(id);

	if (!cfg)
		wetuwn -EINVAW;

	wegmap_update_bits(afe->wegmap, cfg->apww_div_weg,
			   cfg->apww_div_maskbit << cfg->apww_div_shift,
			   cfg->apww_div_defauwt << cfg->apww_div_shift);

	wegmap_update_bits(afe->wegmap, cfg->wef_ck_sew_weg,
			   cfg->wef_ck_sew_maskbit << cfg->wef_ck_sew_shift,
			   cfg->wef_ck_sew_defauwt << cfg->wef_ck_sew_shift);

	wegmap_update_bits(afe->wegmap, cfg->uppew_bound_weg,
			   cfg->uppew_bound_maskbit << cfg->uppew_bound_shift,
			   cfg->uppew_bound_defauwt << cfg->uppew_bound_shift);

	wetuwn 0;
}

static int mt8195_afe_enabwe_tunew_cwk(stwuct mtk_base_afe *afe,
				       unsigned int id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (id) {
	case MT8195_AUD_PWW1:
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW]);
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW1_TUNEW]);
		bweak;
	case MT8195_AUD_PWW2:
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW2]);
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW2_TUNEW]);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt8195_afe_disabwe_tunew_cwk(stwuct mtk_base_afe *afe,
					unsigned int id)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (id) {
	case MT8195_AUD_PWW1:
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW1_TUNEW]);
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW]);
		bweak;
	case MT8195_AUD_PWW2:
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW2_TUNEW]);
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8195_CWK_AUD_APWW2]);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt8195_afe_enabwe_apww_tunew(stwuct mtk_base_afe *afe,
					unsigned int id)
{
	stwuct mt8195_afe_tunew_cfg *cfg = mt8195_afe_found_apww_tunew(id);
	unsigned wong fwags;
	int wet;

	if (!cfg)
		wetuwn -EINVAW;

	wet = mt8195_afe_setup_apww_tunew(afe, id);
	if (wet)
		wetuwn wet;

	wet = mt8195_afe_enabwe_tunew_cwk(afe, id);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&cfg->ctww_wock, fwags);

	cfg->wef_cnt++;
	if (cfg->wef_cnt == 1)
		wegmap_update_bits(afe->wegmap,
				   cfg->tunew_en_weg,
				   cfg->tunew_en_maskbit << cfg->tunew_en_shift,
				   1 << cfg->tunew_en_shift);

	spin_unwock_iwqwestowe(&cfg->ctww_wock, fwags);

	wetuwn 0;
}

static int mt8195_afe_disabwe_apww_tunew(stwuct mtk_base_afe *afe,
					 unsigned int id)
{
	stwuct mt8195_afe_tunew_cfg *cfg = mt8195_afe_found_apww_tunew(id);
	unsigned wong fwags;
	int wet;

	if (!cfg)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&cfg->ctww_wock, fwags);

	cfg->wef_cnt--;
	if (cfg->wef_cnt == 0)
		wegmap_update_bits(afe->wegmap,
				   cfg->tunew_en_weg,
				   cfg->tunew_en_maskbit << cfg->tunew_en_shift,
				   0 << cfg->tunew_en_shift);
	ewse if (cfg->wef_cnt < 0)
		cfg->wef_cnt = 0;

	spin_unwock_iwqwestowe(&cfg->ctww_wock, fwags);

	wet = mt8195_afe_disabwe_tunew_cwk(afe, id);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int mt8195_afe_get_mcwk_souwce_cwk_id(int sew)
{
	switch (sew) {
	case MT8195_MCK_SEW_26M:
		wetuwn MT8195_CWK_XTAW_26M;
	case MT8195_MCK_SEW_APWW1:
		wetuwn MT8195_CWK_TOP_APWW1;
	case MT8195_MCK_SEW_APWW2:
		wetuwn MT8195_CWK_TOP_APWW2;
	defauwt:
		wetuwn -EINVAW;
	}
}

int mt8195_afe_get_mcwk_souwce_wate(stwuct mtk_base_afe *afe, int apww)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cwk_id = mt8195_afe_get_mcwk_souwce_cwk_id(apww);

	if (cwk_id < 0) {
		dev_dbg(afe->dev, "invawid cwk id\n");
		wetuwn 0;
	}

	wetuwn cwk_get_wate(afe_pwiv->cwk[cwk_id]);
}

int mt8195_afe_get_defauwt_mcwk_souwce_by_wate(int wate)
{
	wetuwn ((wate % 8000) == 0) ?
		MT8195_MCK_SEW_APWW1 : MT8195_MCK_SEW_APWW2;
}

int mt8195_afe_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i, wet;

	mt8195_audsys_cwk_wegistew(afe);

	afe_pwiv->cwk =
		devm_kcawwoc(afe->dev, MT8195_CWK_NUM, sizeof(*afe_pwiv->cwk),
			     GFP_KEWNEW);
	if (!afe_pwiv->cwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < MT8195_CWK_NUM; i++) {
		afe_pwiv->cwk[i] = devm_cwk_get(afe->dev, aud_cwks[i]);
		if (IS_EWW(afe_pwiv->cwk[i])) {
			dev_dbg(afe->dev, "%s(), devm_cwk_get %s faiw, wet %wd\n",
				__func__, aud_cwks[i],
				PTW_EWW(afe_pwiv->cwk[i]));
			wetuwn PTW_EWW(afe_pwiv->cwk[i]);
		}
	}

	/* initiaw tunew */
	fow (i = 0; i < MT8195_AUD_PWW_NUM; i++) {
		wet = mt8195_afe_init_apww_tunew(i);
		if (wet) {
			dev_dbg(afe->dev, "%s(), init apww_tunew%d faiwed",
				__func__, (i + 1));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int mt8195_afe_enabwe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	int wet;

	if (cwk) {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to enabwe cwk\n",
				__func__);
			wetuwn wet;
		}
	} ewse {
		dev_dbg(afe->dev, "NUWW cwk\n");
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt8195_afe_enabwe_cwk);

void mt8195_afe_disabwe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	if (cwk)
		cwk_disabwe_unpwepawe(cwk);
	ewse
		dev_dbg(afe->dev, "NUWW cwk\n");
}
EXPOWT_SYMBOW_GPW(mt8195_afe_disabwe_cwk);

int mt8195_afe_pwepawe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	int wet;

	if (cwk) {
		wet = cwk_pwepawe(cwk);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to pwepawe cwk\n",
				__func__);
			wetuwn wet;
		}
	} ewse {
		dev_dbg(afe->dev, "NUWW cwk\n");
	}
	wetuwn 0;
}

void mt8195_afe_unpwepawe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	if (cwk)
		cwk_unpwepawe(cwk);
	ewse
		dev_dbg(afe->dev, "NUWW cwk\n");
}

int mt8195_afe_enabwe_cwk_atomic(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	int wet;

	if (cwk) {
		wet = cwk_enabwe(cwk);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to cwk enabwe\n",
				__func__);
			wetuwn wet;
		}
	} ewse {
		dev_dbg(afe->dev, "NUWW cwk\n");
	}
	wetuwn 0;
}

void mt8195_afe_disabwe_cwk_atomic(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	if (cwk)
		cwk_disabwe(cwk);
	ewse
		dev_dbg(afe->dev, "NUWW cwk\n");
}

int mt8195_afe_set_cwk_wate(stwuct mtk_base_afe *afe, stwuct cwk *cwk,
			    unsigned int wate)
{
	int wet;

	if (cwk) {
		wet = cwk_set_wate(cwk, wate);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to set cwk wate\n",
				__func__);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int mt8195_afe_set_cwk_pawent(stwuct mtk_base_afe *afe, stwuct cwk *cwk,
			      stwuct cwk *pawent)
{
	int wet;

	if (cwk && pawent) {
		wet = cwk_set_pawent(cwk, pawent);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to set cwk pawent\n",
				__func__);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static unsigned int get_top_cg_weg(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8195_TOP_CG_A1SYS_TIMING:
	case MT8195_TOP_CG_A2SYS_TIMING:
	case MT8195_TOP_CG_26M_TIMING:
		wetuwn ASYS_TOP_CON;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_mask(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8195_TOP_CG_A1SYS_TIMING:
		wetuwn ASYS_TOP_CON_A1SYS_TIMING_ON;
	case MT8195_TOP_CG_A2SYS_TIMING:
		wetuwn ASYS_TOP_CON_A2SYS_TIMING_ON;
	case MT8195_TOP_CG_26M_TIMING:
		wetuwn ASYS_TOP_CON_26M_TIMING_ON;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_on_vaw(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8195_TOP_CG_A1SYS_TIMING:
	case MT8195_TOP_CG_A2SYS_TIMING:
	case MT8195_TOP_CG_26M_TIMING:
		wetuwn get_top_cg_mask(cg_type);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_off_vaw(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8195_TOP_CG_A1SYS_TIMING:
	case MT8195_TOP_CG_A2SYS_TIMING:
	case MT8195_TOP_CG_26M_TIMING:
		wetuwn 0;
	defauwt:
		wetuwn get_top_cg_mask(cg_type);
	}
}

static int mt8195_afe_enabwe_top_cg(stwuct mtk_base_afe *afe, unsigned int cg_type)
{
	unsigned int weg = get_top_cg_weg(cg_type);
	unsigned int mask = get_top_cg_mask(cg_type);
	unsigned int vaw = get_top_cg_on_vaw(cg_type);

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);
	wetuwn 0;
}

static int mt8195_afe_disabwe_top_cg(stwuct mtk_base_afe *afe, unsigned int cg_type)
{
	unsigned int weg = get_top_cg_weg(cg_type);
	unsigned int mask = get_top_cg_mask(cg_type);
	unsigned int vaw = get_top_cg_off_vaw(cg_type);

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);
	wetuwn 0;
}

int mt8195_afe_enabwe_weg_ww_cwk(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;
	static const unsigned int cwk_awway[] = {
		MT8195_CWK_SCP_ADSP_AUDIODSP, /* bus cwock fow infwa */
		MT8195_CWK_TOP_AUDIO_H_SEW, /* cwock fow ADSP bus */
		MT8195_CWK_TOP_AUDIO_WOCAW_BUS_SEW, /* bus cwock fow DWAM access */
		MT8195_CWK_TOP_AUD_INTBUS_SEW, /* bus cwock fow AFE SWAM access */
		MT8195_CWK_INFWA_AO_AUDIO_26M_B, /* audio 26M cwock */
		MT8195_CWK_AUD_AFE, /* AFE HW mastew switch */
		MT8195_CWK_AUD_A1SYS_HP, /* AFE HW cwock*/
		MT8195_CWK_AUD_A1SYS, /* AFE HW cwock */
	};

	fow (i = 0; i < AWWAY_SIZE(cwk_awway); i++)
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cwk_awway[i]]);

	wetuwn 0;
}

int mt8195_afe_disabwe_weg_ww_cwk(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;
	static const unsigned int cwk_awway[] = {
		MT8195_CWK_AUD_A1SYS,
		MT8195_CWK_AUD_A1SYS_HP,
		MT8195_CWK_AUD_AFE,
		MT8195_CWK_INFWA_AO_AUDIO_26M_B,
		MT8195_CWK_TOP_AUD_INTBUS_SEW,
		MT8195_CWK_TOP_AUDIO_WOCAW_BUS_SEW,
		MT8195_CWK_TOP_AUDIO_H_SEW,
		MT8195_CWK_SCP_ADSP_AUDIODSP,
	};

	fow (i = 0; i < AWWAY_SIZE(cwk_awway); i++)
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cwk_awway[i]]);

	wetuwn 0;
}

static int mt8195_afe_enabwe_afe_on(stwuct mtk_base_afe *afe)
{
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x1);
	wetuwn 0;
}

static int mt8195_afe_disabwe_afe_on(stwuct mtk_base_afe *afe)
{
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x0);
	wetuwn 0;
}

static int mt8195_afe_enabwe_timing_sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;
	static const unsigned int cwk_awway[] = {
		MT8195_CWK_AUD_A1SYS,
		MT8195_CWK_AUD_A2SYS,
	};
	static const unsigned int cg_awway[] = {
		MT8195_TOP_CG_A1SYS_TIMING,
		MT8195_TOP_CG_A2SYS_TIMING,
		MT8195_TOP_CG_26M_TIMING,
	};

	fow (i = 0; i < AWWAY_SIZE(cwk_awway); i++)
		mt8195_afe_enabwe_cwk(afe, afe_pwiv->cwk[cwk_awway[i]]);

	fow (i = 0; i < AWWAY_SIZE(cg_awway); i++)
		mt8195_afe_enabwe_top_cg(afe, cg_awway[i]);

	wetuwn 0;
}

static int mt8195_afe_disabwe_timing_sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8195_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;
	static const unsigned int cwk_awway[] = {
		MT8195_CWK_AUD_A2SYS,
		MT8195_CWK_AUD_A1SYS,
	};
	static const unsigned int cg_awway[] = {
		MT8195_TOP_CG_26M_TIMING,
		MT8195_TOP_CG_A2SYS_TIMING,
		MT8195_TOP_CG_A1SYS_TIMING,
	};

	fow (i = 0; i < AWWAY_SIZE(cg_awway); i++)
		mt8195_afe_disabwe_top_cg(afe, cg_awway[i]);

	fow (i = 0; i < AWWAY_SIZE(cwk_awway); i++)
		mt8195_afe_disabwe_cwk(afe, afe_pwiv->cwk[cwk_awway[i]]);

	wetuwn 0;
}

int mt8195_afe_enabwe_main_cwock(stwuct mtk_base_afe *afe)
{
	mt8195_afe_enabwe_timing_sys(afe);

	mt8195_afe_enabwe_afe_on(afe);

	mt8195_afe_enabwe_apww_tunew(afe, MT8195_AUD_PWW1);
	mt8195_afe_enabwe_apww_tunew(afe, MT8195_AUD_PWW2);

	wetuwn 0;
}

int mt8195_afe_disabwe_main_cwock(stwuct mtk_base_afe *afe)
{
	mt8195_afe_disabwe_apww_tunew(afe, MT8195_AUD_PWW2);
	mt8195_afe_disabwe_apww_tunew(afe, MT8195_AUD_PWW1);

	mt8195_afe_disabwe_afe_on(afe);

	mt8195_afe_disabwe_timing_sys(afe);

	wetuwn 0;
}
