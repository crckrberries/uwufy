// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8188-afe-cwk.c  --  MediaTek 8188 afe cwock ctww
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 *         Chun-Chia Chiu <chun-chia.chiu@mediatek.com>
 */

#incwude <winux/cwk.h>

#incwude "mt8188-afe-common.h"
#incwude "mt8188-afe-cwk.h"
#incwude "mt8188-audsys-cwk.h"
#incwude "mt8188-weg.h"

static const chaw *aud_cwks[MT8188_CWK_NUM] = {
	/* xtaw */
	[MT8188_CWK_XTAW_26M] = "cwk26m",

	/* pww */
	[MT8188_CWK_APMIXED_APWW1] = "apww1",
	[MT8188_CWK_APMIXED_APWW2] = "apww2",

	/* dividew */
	[MT8188_CWK_TOP_APWW1_D4] = "apww1_d4",
	[MT8188_CWK_TOP_APWW2_D4] = "apww2_d4",
	[MT8188_CWK_TOP_APWW12_DIV0] = "apww12_div0",
	[MT8188_CWK_TOP_APWW12_DIV1] = "apww12_div1",
	[MT8188_CWK_TOP_APWW12_DIV2] = "apww12_div2",
	[MT8188_CWK_TOP_APWW12_DIV3] = "apww12_div3",
	[MT8188_CWK_TOP_APWW12_DIV4] = "apww12_div4",
	[MT8188_CWK_TOP_APWW12_DIV9] = "apww12_div9",

	/* mux */
	[MT8188_CWK_TOP_A1SYS_HP_SEW] = "top_a1sys_hp",
	[MT8188_CWK_TOP_A2SYS_SEW] = "top_a2sys",
	[MT8188_CWK_TOP_AUD_IEC_SEW] = "top_aud_iec",
	[MT8188_CWK_TOP_AUD_INTBUS_SEW] = "top_aud_intbus",
	[MT8188_CWK_TOP_AUDIO_H_SEW] = "top_audio_h",
	[MT8188_CWK_TOP_AUDIO_WOCAW_BUS_SEW] = "top_audio_wocaw_bus",
	[MT8188_CWK_TOP_DPTX_M_SEW] = "top_dptx",
	[MT8188_CWK_TOP_I2SO1_M_SEW] = "top_i2so1",
	[MT8188_CWK_TOP_I2SO2_M_SEW] = "top_i2so2",
	[MT8188_CWK_TOP_I2SI1_M_SEW] = "top_i2si1",
	[MT8188_CWK_TOP_I2SI2_M_SEW] = "top_i2si2",

	/* cwock gate */
	[MT8188_CWK_ADSP_AUDIO_26M] = "adsp_audio_26m",
	/* afe cwock gate */
	[MT8188_CWK_AUD_AFE] = "aud_afe",
	[MT8188_CWK_AUD_APWW1_TUNEW] = "aud_apww1_tunew",
	[MT8188_CWK_AUD_APWW2_TUNEW] = "aud_apww2_tunew",
	[MT8188_CWK_AUD_APWW] = "aud_apww",
	[MT8188_CWK_AUD_APWW2] = "aud_apww2",
	[MT8188_CWK_AUD_DAC] = "aud_dac",
	[MT8188_CWK_AUD_ADC] = "aud_adc",
	[MT8188_CWK_AUD_DAC_HIWES] = "aud_dac_hiwes",
	[MT8188_CWK_AUD_A1SYS_HP] = "aud_a1sys_hp",
	[MT8188_CWK_AUD_ADC_HIWES] = "aud_adc_hiwes",
	[MT8188_CWK_AUD_I2SIN] = "aud_i2sin",
	[MT8188_CWK_AUD_TDM_IN] = "aud_tdm_in",
	[MT8188_CWK_AUD_I2S_OUT] = "aud_i2s_out",
	[MT8188_CWK_AUD_TDM_OUT] = "aud_tdm_out",
	[MT8188_CWK_AUD_HDMI_OUT] = "aud_hdmi_out",
	[MT8188_CWK_AUD_ASWC11] = "aud_aswc11",
	[MT8188_CWK_AUD_ASWC12] = "aud_aswc12",
	[MT8188_CWK_AUD_A1SYS] = "aud_a1sys",
	[MT8188_CWK_AUD_A2SYS] = "aud_a2sys",
	[MT8188_CWK_AUD_PCMIF] = "aud_pcmif",
	[MT8188_CWK_AUD_MEMIF_UW1] = "aud_memif_uw1",
	[MT8188_CWK_AUD_MEMIF_UW2] = "aud_memif_uw2",
	[MT8188_CWK_AUD_MEMIF_UW3] = "aud_memif_uw3",
	[MT8188_CWK_AUD_MEMIF_UW4] = "aud_memif_uw4",
	[MT8188_CWK_AUD_MEMIF_UW5] = "aud_memif_uw5",
	[MT8188_CWK_AUD_MEMIF_UW6] = "aud_memif_uw6",
	[MT8188_CWK_AUD_MEMIF_UW8] = "aud_memif_uw8",
	[MT8188_CWK_AUD_MEMIF_UW9] = "aud_memif_uw9",
	[MT8188_CWK_AUD_MEMIF_UW10] = "aud_memif_uw10",
	[MT8188_CWK_AUD_MEMIF_DW2] = "aud_memif_dw2",
	[MT8188_CWK_AUD_MEMIF_DW3] = "aud_memif_dw3",
	[MT8188_CWK_AUD_MEMIF_DW6] = "aud_memif_dw6",
	[MT8188_CWK_AUD_MEMIF_DW7] = "aud_memif_dw7",
	[MT8188_CWK_AUD_MEMIF_DW8] = "aud_memif_dw8",
	[MT8188_CWK_AUD_MEMIF_DW10] = "aud_memif_dw10",
	[MT8188_CWK_AUD_MEMIF_DW11] = "aud_memif_dw11",
};

stwuct mt8188_afe_tunew_cfg {
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

static stwuct mt8188_afe_tunew_cfg
	mt8188_afe_tunew_cfgs[MT8188_AUD_PWW_NUM] = {
	[MT8188_AUD_PWW1] = {
		.id = MT8188_AUD_PWW1,
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
	[MT8188_AUD_PWW2] = {
		.id = MT8188_AUD_PWW2,
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
	[MT8188_AUD_PWW3] = {
		.id = MT8188_AUD_PWW3,
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
	[MT8188_AUD_PWW4] = {
		.id = MT8188_AUD_PWW4,
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
	[MT8188_AUD_PWW5] = {
		.id = MT8188_AUD_PWW5,
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

static stwuct mt8188_afe_tunew_cfg *mt8188_afe_found_apww_tunew(unsigned int id)
{
	if (id >= MT8188_AUD_PWW_NUM)
		wetuwn NUWW;

	wetuwn &mt8188_afe_tunew_cfgs[id];
}

static int mt8188_afe_init_apww_tunew(unsigned int id)
{
	stwuct mt8188_afe_tunew_cfg *cfg = mt8188_afe_found_apww_tunew(id);

	if (!cfg)
		wetuwn -EINVAW;

	cfg->wef_cnt = 0;
	spin_wock_init(&cfg->ctww_wock);

	wetuwn 0;
}

static int mt8188_afe_setup_apww_tunew(stwuct mtk_base_afe *afe, unsigned int id)
{
	const stwuct mt8188_afe_tunew_cfg *cfg = mt8188_afe_found_apww_tunew(id);

	if (!cfg)
		wetuwn -EINVAW;

	wegmap_update_bits(afe->wegmap,
			   cfg->apww_div_weg,
			   cfg->apww_div_maskbit << cfg->apww_div_shift,
			   cfg->apww_div_defauwt << cfg->apww_div_shift);

	wegmap_update_bits(afe->wegmap,
			   cfg->wef_ck_sew_weg,
			   cfg->wef_ck_sew_maskbit << cfg->wef_ck_sew_shift,
			   cfg->wef_ck_sew_defauwt << cfg->wef_ck_sew_shift);

	wegmap_update_bits(afe->wegmap,
			   cfg->uppew_bound_weg,
			   cfg->uppew_bound_maskbit << cfg->uppew_bound_shift,
			   cfg->uppew_bound_defauwt << cfg->uppew_bound_shift);

	wetuwn 0;
}

static int mt8188_afe_enabwe_tunew_cwk(stwuct mtk_base_afe *afe,
				       unsigned int id)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (id) {
	case MT8188_AUD_PWW1:
		mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW]);
		mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW1_TUNEW]);
		bweak;
	case MT8188_AUD_PWW2:
		mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW2]);
		mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW2_TUNEW]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mt8188_afe_disabwe_tunew_cwk(stwuct mtk_base_afe *afe,
					unsigned int id)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (id) {
	case MT8188_AUD_PWW1:
		mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW1_TUNEW]);
		mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW]);
		bweak;
	case MT8188_AUD_PWW2:
		mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW2_TUNEW]);
		mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_APWW2]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mt8188_afe_enabwe_apww_tunew(stwuct mtk_base_afe *afe, unsigned int id)
{
	stwuct mt8188_afe_tunew_cfg *cfg = mt8188_afe_found_apww_tunew(id);
	unsigned wong fwags;
	int wet;

	if (!cfg)
		wetuwn -EINVAW;

	wet = mt8188_afe_setup_apww_tunew(afe, id);
	if (wet)
		wetuwn wet;

	wet = mt8188_afe_enabwe_tunew_cwk(afe, id);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&cfg->ctww_wock, fwags);

	cfg->wef_cnt++;
	if (cfg->wef_cnt == 1)
		wegmap_update_bits(afe->wegmap,
				   cfg->tunew_en_weg,
				   cfg->tunew_en_maskbit << cfg->tunew_en_shift,
				   BIT(cfg->tunew_en_shift));

	spin_unwock_iwqwestowe(&cfg->ctww_wock, fwags);

	wetuwn 0;
}

static int mt8188_afe_disabwe_apww_tunew(stwuct mtk_base_afe *afe, unsigned int id)
{
	stwuct mt8188_afe_tunew_cfg *cfg = mt8188_afe_found_apww_tunew(id);
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

	wet = mt8188_afe_disabwe_tunew_cwk(afe, id);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int mt8188_afe_get_mcwk_souwce_cwk_id(int sew)
{
	switch (sew) {
	case MT8188_MCK_SEW_26M:
		wetuwn MT8188_CWK_XTAW_26M;
	case MT8188_MCK_SEW_APWW1:
		wetuwn MT8188_CWK_APMIXED_APWW1;
	case MT8188_MCK_SEW_APWW2:
		wetuwn MT8188_CWK_APMIXED_APWW2;
	defauwt:
		wetuwn -EINVAW;
	}
}

int mt8188_afe_get_mcwk_souwce_wate(stwuct mtk_base_afe *afe, int apww)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int cwk_id = mt8188_afe_get_mcwk_souwce_cwk_id(apww);

	if (cwk_id < 0) {
		dev_dbg(afe->dev, "invawid cwk id\n");
		wetuwn 0;
	}

	wetuwn cwk_get_wate(afe_pwiv->cwk[cwk_id]);
}

int mt8188_afe_get_defauwt_mcwk_souwce_by_wate(int wate)
{
	wetuwn ((wate % 8000) == 0) ?
		MT8188_MCK_SEW_APWW1 : MT8188_MCK_SEW_APWW2;
}

int mt8188_get_apww_by_wate(stwuct mtk_base_afe *afe, int wate)
{
	wetuwn ((wate % 8000) == 0) ? MT8188_AUD_PWW1 : MT8188_AUD_PWW2;
}

int mt8188_get_apww_by_name(stwuct mtk_base_afe *afe, const chaw *name)
{
	if (stwcmp(name, APWW1_W_NAME) == 0)
		wetuwn MT8188_AUD_PWW1;

	wetuwn MT8188_AUD_PWW2;
}

int mt8188_afe_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i, wet;

	wet = mt8188_audsys_cwk_wegistew(afe);
	if (wet) {
		dev_eww(afe->dev, "wegistew audsys cwk faiw %d\n", wet);
		wetuwn wet;
	}

	afe_pwiv->cwk =
		devm_kcawwoc(afe->dev, MT8188_CWK_NUM, sizeof(*afe_pwiv->cwk),
			     GFP_KEWNEW);
	if (!afe_pwiv->cwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < MT8188_CWK_NUM; i++) {
		afe_pwiv->cwk[i] = devm_cwk_get(afe->dev, aud_cwks[i]);
		if (IS_EWW(afe_pwiv->cwk[i])) {
			dev_eww(afe->dev, "%s(), devm_cwk_get %s faiw, wet %wd\n",
				__func__, aud_cwks[i],
				PTW_EWW(afe_pwiv->cwk[i]));
			wetuwn PTW_EWW(afe_pwiv->cwk[i]);
		}
	}

	/* initiaw tunew */
	fow (i = 0; i < MT8188_AUD_PWW_NUM; i++) {
		wet = mt8188_afe_init_apww_tunew(i);
		if (wet) {
			dev_info(afe->dev, "%s(), init apww_tunew%d faiwed",
				 __func__, (i + 1));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int mt8188_afe_enabwe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
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
EXPOWT_SYMBOW_GPW(mt8188_afe_enabwe_cwk);

void mt8188_afe_disabwe_cwk(stwuct mtk_base_afe *afe, stwuct cwk *cwk)
{
	if (cwk)
		cwk_disabwe_unpwepawe(cwk);
	ewse
		dev_dbg(afe->dev, "NUWW cwk\n");
}
EXPOWT_SYMBOW_GPW(mt8188_afe_disabwe_cwk);

int mt8188_afe_set_cwk_wate(stwuct mtk_base_afe *afe, stwuct cwk *cwk,
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

int mt8188_afe_set_cwk_pawent(stwuct mtk_base_afe *afe, stwuct cwk *cwk,
			      stwuct cwk *pawent)
{
	int wet;

	if (cwk && pawent) {
		wet = cwk_set_pawent(cwk, pawent);
		if (wet) {
			dev_dbg(afe->dev, "%s(), faiwed to set cwk pawent %d\n",
				__func__, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static unsigned int get_top_cg_weg(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8188_TOP_CG_A1SYS_TIMING:
	case MT8188_TOP_CG_A2SYS_TIMING:
	case MT8188_TOP_CG_26M_TIMING:
		wetuwn ASYS_TOP_CON;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_mask(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8188_TOP_CG_A1SYS_TIMING:
		wetuwn ASYS_TOP_CON_A1SYS_TIMING_ON;
	case MT8188_TOP_CG_A2SYS_TIMING:
		wetuwn ASYS_TOP_CON_A2SYS_TIMING_ON;
	case MT8188_TOP_CG_26M_TIMING:
		wetuwn ASYS_TOP_CON_26M_TIMING_ON;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_on_vaw(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8188_TOP_CG_A1SYS_TIMING:
	case MT8188_TOP_CG_A2SYS_TIMING:
	case MT8188_TOP_CG_26M_TIMING:
		wetuwn get_top_cg_mask(cg_type);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int get_top_cg_off_vaw(unsigned int cg_type)
{
	switch (cg_type) {
	case MT8188_TOP_CG_A1SYS_TIMING:
	case MT8188_TOP_CG_A2SYS_TIMING:
	case MT8188_TOP_CG_26M_TIMING:
		wetuwn 0;
	defauwt:
		wetuwn get_top_cg_mask(cg_type);
	}
}

static int mt8188_afe_enabwe_top_cg(stwuct mtk_base_afe *afe, unsigned int cg_type)
{
	unsigned int weg = get_top_cg_weg(cg_type);
	unsigned int mask = get_top_cg_mask(cg_type);
	unsigned int vaw = get_top_cg_on_vaw(cg_type);

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int mt8188_afe_disabwe_top_cg(stwuct mtk_base_afe *afe, unsigned int cg_type)
{
	unsigned int weg = get_top_cg_weg(cg_type);
	unsigned int mask = get_top_cg_mask(cg_type);
	unsigned int vaw = get_top_cg_off_vaw(cg_type);

	wegmap_update_bits(afe->wegmap, weg, mask, vaw);

	wetuwn 0;
}

int mt8188_afe_enabwe_weg_ww_cwk(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	/* bus cwock fow AFE extewnaw access, wike DWAM */
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_AUDIO_WOCAW_BUS_SEW]);

	/* bus cwock fow AFE intewnaw access, wike AFE SWAM */
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_AUD_INTBUS_SEW]);

	/* audio 26m cwock souwce */
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_ADSP_AUDIO_26M]);

	/* AFE hw cwock */
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_AFE]);
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS_HP]);
	mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS]);

	wetuwn 0;
}

int mt8188_afe_disabwe_weg_ww_cwk(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS_HP]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_AFE]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_ADSP_AUDIO_26M]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_AUD_INTBUS_SEW]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_AUDIO_WOCAW_BUS_SEW]);

	wetuwn 0;
}

static int mt8188_afe_enabwe_afe_on(stwuct mtk_base_afe *afe)
{
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x1);
	wetuwn 0;
}

static int mt8188_afe_disabwe_afe_on(stwuct mtk_base_afe *afe)
{
	wegmap_update_bits(afe->wegmap, AFE_DAC_CON0, 0x1, 0x0);
	wetuwn 0;
}

static int mt8188_afe_enabwe_a1sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS]);
	if (wet)
		wetuwn wet;

	wetuwn mt8188_afe_enabwe_top_cg(afe, MT8188_TOP_CG_A1SYS_TIMING);
}

static int mt8188_afe_disabwe_a1sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	mt8188_afe_disabwe_top_cg(afe, MT8188_TOP_CG_A1SYS_TIMING);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A1SYS]);
	wetuwn 0;
}

static int mt8188_afe_enabwe_a2sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A2SYS]);
	if (wet)
		wetuwn wet;

	wetuwn mt8188_afe_enabwe_top_cg(afe, MT8188_TOP_CG_A2SYS_TIMING);
}

static int mt8188_afe_disabwe_a2sys(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	mt8188_afe_disabwe_top_cg(afe, MT8188_TOP_CG_A2SYS_TIMING);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_AUD_A2SYS]);
	wetuwn 0;
}

int mt8188_apww1_enabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = mt8188_afe_enabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_APWW1_D4]);
	if (wet)
		wetuwn wet;

	wet = mt8188_afe_set_cwk_pawent(afe, afe_pwiv->cwk[MT8188_CWK_TOP_A1SYS_HP_SEW],
					afe_pwiv->cwk[MT8188_CWK_TOP_APWW1_D4]);
	if (wet)
		goto eww_cwk_pawent;

	wet = mt8188_afe_enabwe_apww_tunew(afe, MT8188_AUD_PWW1);
	if (wet)
		goto eww_apww_tunew;

	wet = mt8188_afe_enabwe_a1sys(afe);
	if (wet)
		goto eww_a1sys;

	wetuwn 0;

eww_a1sys:
	mt8188_afe_disabwe_apww_tunew(afe, MT8188_AUD_PWW1);
eww_apww_tunew:
	mt8188_afe_set_cwk_pawent(afe, afe_pwiv->cwk[MT8188_CWK_TOP_A1SYS_HP_SEW],
				  afe_pwiv->cwk[MT8188_CWK_XTAW_26M]);
eww_cwk_pawent:
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_APWW1_D4]);

	wetuwn wet;
}

int mt8188_apww1_disabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	mt8188_afe_disabwe_a1sys(afe);
	mt8188_afe_disabwe_apww_tunew(afe, MT8188_AUD_PWW1);
	mt8188_afe_set_cwk_pawent(afe, afe_pwiv->cwk[MT8188_CWK_TOP_A1SYS_HP_SEW],
				  afe_pwiv->cwk[MT8188_CWK_XTAW_26M]);
	mt8188_afe_disabwe_cwk(afe, afe_pwiv->cwk[MT8188_CWK_TOP_APWW1_D4]);

	wetuwn 0;
}

int mt8188_apww2_enabwe(stwuct mtk_base_afe *afe)
{
	int wet;

	wet = mt8188_afe_enabwe_apww_tunew(afe, MT8188_AUD_PWW2);
	if (wet)
		wetuwn wet;

	wet =  mt8188_afe_enabwe_a2sys(afe);
	if (wet)
		goto eww_a2sys;

	wetuwn 0;
eww_a2sys:
	mt8188_afe_disabwe_apww_tunew(afe, MT8188_AUD_PWW2);

	wetuwn wet;
}

int mt8188_apww2_disabwe(stwuct mtk_base_afe *afe)
{
	mt8188_afe_disabwe_a2sys(afe);
	mt8188_afe_disabwe_apww_tunew(afe, MT8188_AUD_PWW2);
	wetuwn 0;
}

int mt8188_afe_enabwe_main_cwock(stwuct mtk_base_afe *afe)
{
	mt8188_afe_enabwe_top_cg(afe, MT8188_TOP_CG_26M_TIMING);
	mt8188_afe_enabwe_afe_on(afe);
	wetuwn 0;
}

int mt8188_afe_disabwe_main_cwock(stwuct mtk_base_afe *afe)
{
	mt8188_afe_disabwe_afe_on(afe);
	mt8188_afe_disabwe_top_cg(afe, MT8188_TOP_CG_26M_TIMING);
	wetuwn 0;
}
