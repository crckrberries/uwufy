// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8183-afe-cwk.c  --  Mediatek 8183 afe cwock ctww
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/cwk.h>

#incwude "mt8183-afe-common.h"
#incwude "mt8183-afe-cwk.h"
#incwude "mt8183-weg.h"

enum {
	CWK_AFE = 0,
	CWK_TMW,
	CWK_APWW22M,
	CWK_APWW24M,
	CWK_APWW1_TUNEW,
	CWK_APWW2_TUNEW,
	CWK_I2S1_BCWK_SW,
	CWK_I2S2_BCWK_SW,
	CWK_I2S3_BCWK_SW,
	CWK_I2S4_BCWK_SW,
	CWK_INFWA_SYS_AUDIO,
	CWK_MUX_AUDIO,
	CWK_MUX_AUDIOINTBUS,
	CWK_TOP_SYSPWW_D2_D4,
	/* apww wewated mux */
	CWK_TOP_MUX_AUD_1,
	CWK_TOP_APWW1_CK,
	CWK_TOP_MUX_AUD_2,
	CWK_TOP_APWW2_CK,
	CWK_TOP_MUX_AUD_ENG1,
	CWK_TOP_APWW1_D8,
	CWK_TOP_MUX_AUD_ENG2,
	CWK_TOP_APWW2_D8,
	CWK_TOP_I2S0_M_SEW,
	CWK_TOP_I2S1_M_SEW,
	CWK_TOP_I2S2_M_SEW,
	CWK_TOP_I2S3_M_SEW,
	CWK_TOP_I2S4_M_SEW,
	CWK_TOP_I2S5_M_SEW,
	CWK_TOP_APWW12_DIV0,
	CWK_TOP_APWW12_DIV1,
	CWK_TOP_APWW12_DIV2,
	CWK_TOP_APWW12_DIV3,
	CWK_TOP_APWW12_DIV4,
	CWK_TOP_APWW12_DIVB,
	CWK_CWK26M,
	CWK_NUM
};

static const chaw *aud_cwks[CWK_NUM] = {
	[CWK_AFE] = "aud_afe_cwk",
	[CWK_TMW] = "aud_tmw_cwk",
	[CWK_APWW22M] = "aud_apww22m_cwk",
	[CWK_APWW24M] = "aud_apww24m_cwk",
	[CWK_APWW1_TUNEW] = "aud_apww1_tunew_cwk",
	[CWK_APWW2_TUNEW] = "aud_apww2_tunew_cwk",
	[CWK_I2S1_BCWK_SW] = "aud_i2s1_bcwk_sw",
	[CWK_I2S2_BCWK_SW] = "aud_i2s2_bcwk_sw",
	[CWK_I2S3_BCWK_SW] = "aud_i2s3_bcwk_sw",
	[CWK_I2S4_BCWK_SW] = "aud_i2s4_bcwk_sw",
	[CWK_INFWA_SYS_AUDIO] = "aud_infwa_cwk",
	[CWK_MUX_AUDIO] = "top_mux_audio",
	[CWK_MUX_AUDIOINTBUS] = "top_mux_aud_intbus",
	[CWK_TOP_SYSPWW_D2_D4] = "top_syspww_d2_d4",
	[CWK_TOP_MUX_AUD_1] = "top_mux_aud_1",
	[CWK_TOP_APWW1_CK] = "top_apww1_ck",
	[CWK_TOP_MUX_AUD_2] = "top_mux_aud_2",
	[CWK_TOP_APWW2_CK] = "top_apww2_ck",
	[CWK_TOP_MUX_AUD_ENG1] = "top_mux_aud_eng1",
	[CWK_TOP_APWW1_D8] = "top_apww1_d8",
	[CWK_TOP_MUX_AUD_ENG2] = "top_mux_aud_eng2",
	[CWK_TOP_APWW2_D8] = "top_apww2_d8",
	[CWK_TOP_I2S0_M_SEW] = "top_i2s0_m_sew",
	[CWK_TOP_I2S1_M_SEW] = "top_i2s1_m_sew",
	[CWK_TOP_I2S2_M_SEW] = "top_i2s2_m_sew",
	[CWK_TOP_I2S3_M_SEW] = "top_i2s3_m_sew",
	[CWK_TOP_I2S4_M_SEW] = "top_i2s4_m_sew",
	[CWK_TOP_I2S5_M_SEW] = "top_i2s5_m_sew",
	[CWK_TOP_APWW12_DIV0] = "top_apww12_div0",
	[CWK_TOP_APWW12_DIV1] = "top_apww12_div1",
	[CWK_TOP_APWW12_DIV2] = "top_apww12_div2",
	[CWK_TOP_APWW12_DIV3] = "top_apww12_div3",
	[CWK_TOP_APWW12_DIV4] = "top_apww12_div4",
	[CWK_TOP_APWW12_DIVB] = "top_apww12_divb",
	[CWK_CWK26M] = "top_cwk26m_cwk",
};

int mt8183_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;

	afe_pwiv->cwk = devm_kcawwoc(afe->dev, CWK_NUM, sizeof(*afe_pwiv->cwk),
				     GFP_KEWNEW);
	if (!afe_pwiv->cwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < CWK_NUM; i++) {
		afe_pwiv->cwk[i] = devm_cwk_get(afe->dev, aud_cwks[i]);
		if (IS_EWW(afe_pwiv->cwk[i])) {
			dev_eww(afe->dev, "%s(), devm_cwk_get %s faiw, wet %wd\n",
				__func__, aud_cwks[i],
				PTW_EWW(afe_pwiv->cwk[i]));
			wetuwn PTW_EWW(afe_pwiv->cwk[i]);
		}
	}

	wetuwn 0;
}

int mt8183_afe_enabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_INFWA_SYS_AUDIO], wet);
		goto CWK_INFWA_SYS_AUDIO_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIO], wet);
		goto CWK_MUX_AUDIO_EWW;
	}

	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_MUX_AUDIO],
			     afe_pwiv->cwk[CWK_CWK26M]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIO],
			aud_cwks[CWK_CWK26M], wet);
		goto CWK_MUX_AUDIO_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIOINTBUS], wet);
		goto CWK_MUX_AUDIO_INTBUS_EWW;
	}

	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS],
			     afe_pwiv->cwk[CWK_TOP_SYSPWW_D2_D4]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIOINTBUS],
			aud_cwks[CWK_TOP_SYSPWW_D2_D4], wet);
		goto CWK_MUX_AUDIO_INTBUS_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_AFE]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_AFE], wet);
		goto CWK_AFE_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_I2S1_BCWK_SW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_I2S1_BCWK_SW], wet);
		goto CWK_I2S1_BCWK_SW_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_I2S2_BCWK_SW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_I2S2_BCWK_SW], wet);
		goto CWK_I2S2_BCWK_SW_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_I2S3_BCWK_SW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_I2S3_BCWK_SW], wet);
		goto CWK_I2S3_BCWK_SW_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_I2S4_BCWK_SW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_I2S4_BCWK_SW], wet);
		goto CWK_I2S4_BCWK_SW_EWW;
	}

	wetuwn 0;

CWK_I2S4_BCWK_SW_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S3_BCWK_SW]);
CWK_I2S3_BCWK_SW_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S2_BCWK_SW]);
CWK_I2S2_BCWK_SW_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S1_BCWK_SW]);
CWK_I2S1_BCWK_SW_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_AFE]);
CWK_AFE_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
CWK_MUX_AUDIO_INTBUS_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
CWK_MUX_AUDIO_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);
CWK_INFWA_SYS_AUDIO_EWW:
	wetuwn wet;
}

int mt8183_afe_disabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S4_BCWK_SW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S3_BCWK_SW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S2_BCWK_SW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_I2S1_BCWK_SW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_AFE]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);

	wetuwn 0;
}

/* apww */
static int apww1_mux_setting(stwuct mtk_base_afe *afe, boow enabwe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	if (enabwe) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1], wet);
			goto EWW_ENABWE_CWK_TOP_MUX_AUD_1;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1],
				     afe_pwiv->cwk[CWK_TOP_APWW1_CK]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1],
				aud_cwks[CWK_TOP_APWW1_CK], wet);
			goto EWW_SEWECT_CWK_TOP_MUX_AUD_1;
		}

		/* 180.6336 / 8 = 22.5792MHz */
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1], wet);
			goto EWW_ENABWE_CWK_TOP_MUX_AUD_ENG1;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1],
				     afe_pwiv->cwk[CWK_TOP_APWW1_D8]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1],
				aud_cwks[CWK_TOP_APWW1_D8], wet);
			goto EWW_SEWECT_CWK_TOP_MUX_AUD_ENG1;
		}
	} ewse {
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1],
				aud_cwks[CWK_CWK26M], wet);
			goto EXIT;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1]);

		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1],
				aud_cwks[CWK_CWK26M], wet);
			goto EXIT;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1]);
	}

	wetuwn 0;

EWW_SEWECT_CWK_TOP_MUX_AUD_ENG1:
	cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1],
		       afe_pwiv->cwk[CWK_CWK26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1]);
EWW_ENABWE_CWK_TOP_MUX_AUD_ENG1:
EWW_SEWECT_CWK_TOP_MUX_AUD_1:
	cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1],
		       afe_pwiv->cwk[CWK_CWK26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1]);
EWW_ENABWE_CWK_TOP_MUX_AUD_1:
EXIT:
	wetuwn wet;
}

static int apww2_mux_setting(stwuct mtk_base_afe *afe, boow enabwe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	if (enabwe) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2], wet);
			goto EWW_ENABWE_CWK_TOP_MUX_AUD_2;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2],
				     afe_pwiv->cwk[CWK_TOP_APWW2_CK]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2],
				aud_cwks[CWK_TOP_APWW2_CK], wet);
			goto EWW_SEWECT_CWK_TOP_MUX_AUD_2;
		}

		/* 196.608 / 8 = 24.576MHz */
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2], wet);
			goto EWW_ENABWE_CWK_TOP_MUX_AUD_ENG2;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2],
				     afe_pwiv->cwk[CWK_TOP_APWW2_D8]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2],
				aud_cwks[CWK_TOP_APWW2_D8], wet);
			goto EWW_SEWECT_CWK_TOP_MUX_AUD_ENG2;
		}
	} ewse {
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2],
				aud_cwks[CWK_CWK26M], wet);
			goto EXIT;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2]);

		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2],
				aud_cwks[CWK_CWK26M], wet);
			goto EXIT;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2]);
	}

	wetuwn 0;

EWW_SEWECT_CWK_TOP_MUX_AUD_ENG2:
	cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2],
		       afe_pwiv->cwk[CWK_CWK26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2]);
EWW_ENABWE_CWK_TOP_MUX_AUD_ENG2:
EWW_SEWECT_CWK_TOP_MUX_AUD_2:
	cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2],
		       afe_pwiv->cwk[CWK_CWK26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2]);
EWW_ENABWE_CWK_TOP_MUX_AUD_2:
EXIT:
	wetuwn wet;
}

int mt8183_apww1_enabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* setting fow APWW */
	apww1_mux_setting(afe, twue);

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW22M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW22M], wet);
		goto EWW_CWK_APWW22M;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW1_TUNEW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW1_TUNEW], wet);
		goto EWW_CWK_APWW1_TUNEW;
	}

	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG,
			   0x0000FFF7, 0x00000832);
	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG, 0x1, 0x1);

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_22M_ON_MASK_SFT,
			   0x1 << AFE_22M_ON_SFT);

	wetuwn 0;

EWW_CWK_APWW1_TUNEW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW22M]);
EWW_CWK_APWW22M:
	wetuwn wet;
}

void mt8183_apww1_disabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_22M_ON_MASK_SFT,
			   0x0 << AFE_22M_ON_SFT);

	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG, 0x1, 0x0);

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW1_TUNEW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW22M]);

	apww1_mux_setting(afe, fawse);
}

int mt8183_apww2_enabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* setting fow APWW */
	apww2_mux_setting(afe, twue);

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW24M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW24M], wet);
		goto EWW_CWK_APWW24M;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW2_TUNEW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW2_TUNEW], wet);
		goto EWW_CWK_APWW2_TUNEW;
	}

	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG,
			   0x0000FFF7, 0x00000634);
	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG, 0x1, 0x1);

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_24M_ON_MASK_SFT,
			   0x1 << AFE_24M_ON_SFT);

	wetuwn 0;

EWW_CWK_APWW2_TUNEW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW24M]);
EWW_CWK_APWW24M:
	wetuwn wet;
}

void mt8183_apww2_disabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_24M_ON_MASK_SFT,
			   0x0 << AFE_24M_ON_SFT);

	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG, 0x1, 0x0);

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW2_TUNEW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW24M]);

	apww2_mux_setting(afe, fawse);
}

int mt8183_get_apww_wate(stwuct mtk_base_afe *afe, int apww)
{
	wetuwn (apww == MT8183_APWW1) ? 180633600 : 196608000;
}

int mt8183_get_apww_by_wate(stwuct mtk_base_afe *afe, int wate)
{
	wetuwn ((wate % 8000) == 0) ? MT8183_APWW2 : MT8183_APWW1;
}

int mt8183_get_apww_by_name(stwuct mtk_base_afe *afe, const chaw *name)
{
	if (stwcmp(name, APWW1_W_NAME) == 0)
		wetuwn MT8183_APWW1;
	ewse
		wetuwn MT8183_APWW2;
}

/* mck */
stwuct mt8183_mck_div {
	int m_sew_id;
	int div_cwk_id;
};

static const stwuct mt8183_mck_div mck_div[MT8183_MCK_NUM] = {
	[MT8183_I2S0_MCK] = {
		.m_sew_id = CWK_TOP_I2S0_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV0,
	},
	[MT8183_I2S1_MCK] = {
		.m_sew_id = CWK_TOP_I2S1_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV1,
	},
	[MT8183_I2S2_MCK] = {
		.m_sew_id = CWK_TOP_I2S2_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV2,
	},
	[MT8183_I2S3_MCK] = {
		.m_sew_id = CWK_TOP_I2S3_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV3,
	},
	[MT8183_I2S4_MCK] = {
		.m_sew_id = CWK_TOP_I2S4_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV4,
	},
	[MT8183_I2S4_BCK] = {
		.m_sew_id = -1,
		.div_cwk_id = CWK_TOP_APWW12_DIVB,
	},
	[MT8183_I2S5_MCK] = {
		.m_sew_id = -1,
		.div_cwk_id = -1,
	},
};

int mt8183_mck_enabwe(stwuct mtk_base_afe *afe, int mck_id, int wate)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int apww = mt8183_get_apww_by_wate(afe, wate);
	int apww_cwk_id = apww == MT8183_APWW1 ?
			  CWK_TOP_MUX_AUD_1 : CWK_TOP_MUX_AUD_2;
	int m_sew_id = mck_div[mck_id].m_sew_id;
	int div_cwk_id = mck_div[mck_id].div_cwk_id;
	int wet;

	/* i2s5 mck not suppowt */
	if (mck_id == MT8183_I2S5_MCK)
		wetuwn 0;

	/* sewect apww */
	if (m_sew_id >= 0) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[m_sew_id]);
		if (wet) {
			dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[m_sew_id], wet);
			goto EWW_ENABWE_MCWK;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[m_sew_id],
				     afe_pwiv->cwk[apww_cwk_id]);
		if (wet) {
			dev_eww(afe->dev, "%s(), cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[m_sew_id],
				aud_cwks[apww_cwk_id], wet);
			goto EWW_SEWECT_MCWK;
		}
	}

	/* enabwe div, set wate */
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[div_cwk_id]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[div_cwk_id], wet);
		goto EWW_ENABWE_MCWK_DIV;
	}
	wet = cwk_set_wate(afe_pwiv->cwk[div_cwk_id], wate);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_set_wate %s, wate %d, faiw %d\n",
			__func__, aud_cwks[div_cwk_id],
			wate, wet);
		goto EWW_SET_MCWK_WATE;
	}

	wetuwn 0;

EWW_SET_MCWK_WATE:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[div_cwk_id]);
EWW_ENABWE_MCWK_DIV:
EWW_SEWECT_MCWK:
	if (m_sew_id >= 0)
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[m_sew_id]);
EWW_ENABWE_MCWK:
	wetuwn wet;
}

void mt8183_mck_disabwe(stwuct mtk_base_afe *afe, int mck_id)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int m_sew_id = mck_div[mck_id].m_sew_id;
	int div_cwk_id = mck_div[mck_id].div_cwk_id;

	/* i2s5 mck not suppowt */
	if (mck_id == MT8183_I2S5_MCK)
		wetuwn;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[div_cwk_id]);
	if (m_sew_id >= 0)
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[m_sew_id]);
}
