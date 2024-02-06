// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8186-afe-cwk.c  --  Mediatek 8186 afe cwock ctww
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-cwk.h"
#incwude "mt8186-audsys-cwk.h"

static const chaw *aud_cwks[CWK_NUM] = {
	[CWK_AFE] = "aud_afe_cwk",
	[CWK_DAC] = "aud_dac_cwk",
	[CWK_DAC_PWEDIS] = "aud_dac_pwedis_cwk",
	[CWK_ADC] = "aud_adc_cwk",
	[CWK_TMW] = "aud_tmw_cwk",
	[CWK_APWW22M] = "aud_apww22m_cwk",
	[CWK_APWW24M] = "aud_apww24m_cwk",
	[CWK_APWW1_TUNEW] = "aud_apww_tunew_cwk",
	[CWK_APWW2_TUNEW] = "aud_apww2_tunew_cwk",
	[CWK_TDM] = "aud_tdm_cwk",
	[CWK_NWE] = "aud_nwe_cwk",
	[CWK_DAC_HIWES] = "aud_dac_hiwes_cwk",
	[CWK_ADC_HIWES] = "aud_adc_hiwes_cwk",
	[CWK_I2S1_BCWK] = "aud_i2s1_bcwk",
	[CWK_I2S2_BCWK] = "aud_i2s2_bcwk",
	[CWK_I2S3_BCWK] = "aud_i2s3_bcwk",
	[CWK_I2S4_BCWK] = "aud_i2s4_bcwk",
	[CWK_CONNSYS_I2S_ASWC] = "aud_connsys_i2s_aswc",
	[CWK_GENEWAW1_ASWC] = "aud_genewaw1_aswc",
	[CWK_GENEWAW2_ASWC] = "aud_genewaw2_aswc",
	[CWK_ADC_HIWES_TMW] = "aud_adc_hiwes_tmw",
	[CWK_ADDA6_ADC] = "aud_adda6_adc",
	[CWK_ADDA6_ADC_HIWES] = "aud_adda6_adc_hiwes",
	[CWK_3WD_DAC] = "aud_3wd_dac",
	[CWK_3WD_DAC_PWEDIS] = "aud_3wd_dac_pwedis",
	[CWK_3WD_DAC_TMW] = "aud_3wd_dac_tmw",
	[CWK_3WD_DAC_HIWES] = "aud_3wd_dac_hiwes",
	[CWK_ETDM_IN1_BCWK] = "aud_etdm_in1_bcwk",
	[CWK_ETDM_OUT1_BCWK] = "aud_etdm_out1_bcwk",
	[CWK_INFWA_SYS_AUDIO] = "aud_infwa_cwk",
	[CWK_INFWA_AUDIO_26M] = "mtkaif_26m_cwk",
	[CWK_MUX_AUDIO] = "top_mux_audio",
	[CWK_MUX_AUDIOINTBUS] = "top_mux_audio_int",
	[CWK_TOP_MAINPWW_D2_D4] = "top_mainpww_d2_d4",
	[CWK_TOP_MUX_AUD_1] = "top_mux_aud_1",
	[CWK_TOP_APWW1_CK] = "top_apww1_ck",
	[CWK_TOP_MUX_AUD_2] = "top_mux_aud_2",
	[CWK_TOP_APWW2_CK] = "top_apww2_ck",
	[CWK_TOP_MUX_AUD_ENG1] = "top_mux_aud_eng1",
	[CWK_TOP_APWW1_D8] = "top_apww1_d8",
	[CWK_TOP_MUX_AUD_ENG2] = "top_mux_aud_eng2",
	[CWK_TOP_APWW2_D8] = "top_apww2_d8",
	[CWK_TOP_MUX_AUDIO_H] = "top_mux_audio_h",
	[CWK_TOP_I2S0_M_SEW] = "top_i2s0_m_sew",
	[CWK_TOP_I2S1_M_SEW] = "top_i2s1_m_sew",
	[CWK_TOP_I2S2_M_SEW] = "top_i2s2_m_sew",
	[CWK_TOP_I2S4_M_SEW] = "top_i2s4_m_sew",
	[CWK_TOP_TDM_M_SEW] = "top_tdm_m_sew",
	[CWK_TOP_APWW12_DIV0] = "top_apww12_div0",
	[CWK_TOP_APWW12_DIV1] = "top_apww12_div1",
	[CWK_TOP_APWW12_DIV2] = "top_apww12_div2",
	[CWK_TOP_APWW12_DIV4] = "top_apww12_div4",
	[CWK_TOP_APWW12_DIV_TDM] = "top_apww12_div_tdm",
	[CWK_CWK26M] = "top_cwk26m_cwk",
};

int mt8186_set_audio_int_bus_pawent(stwuct mtk_base_afe *afe,
				    int cwk_id)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS],
			     afe_pwiv->cwk[cwk_id]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIOINTBUS],
			aud_cwks[cwk_id], wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int apww1_mux_setting(stwuct mtk_base_afe *afe, boow enabwe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	if (enabwe) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1], wet);
			wetuwn wet;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1],
				     afe_pwiv->cwk[CWK_TOP_APWW1_CK]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1],
				aud_cwks[CWK_TOP_APWW1_CK], wet);
			wetuwn wet;
		}

		/* 180.6336 / 8 = 22.5792MHz */
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1], wet);
			wetuwn wet;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1],
				     afe_pwiv->cwk[CWK_TOP_APWW1_D8]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1],
				aud_cwks[CWK_TOP_APWW1_D8], wet);
			wetuwn wet;
		}
	} ewse {
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG1],
				aud_cwks[CWK_CWK26M], wet);
			wetuwn wet;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG1]);

		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_1],
				aud_cwks[CWK_CWK26M], wet);
			wetuwn wet;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_1]);
	}

	wetuwn 0;
}

static int apww2_mux_setting(stwuct mtk_base_afe *afe, boow enabwe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	if (enabwe) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2], wet);
			wetuwn wet;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2],
				     afe_pwiv->cwk[CWK_TOP_APWW2_CK]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2],
				aud_cwks[CWK_TOP_APWW2_CK], wet);
			wetuwn wet;
		}

		/* 196.608 / 8 = 24.576MHz */
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2], wet);
			wetuwn wet;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2],
				     afe_pwiv->cwk[CWK_TOP_APWW2_D8]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2],
				aud_cwks[CWK_TOP_APWW2_D8], wet);
			wetuwn wet;
		}
	} ewse {
		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_ENG2],
				aud_cwks[CWK_CWK26M], wet);
			wetuwn wet;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_ENG2]);

		wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2],
				     afe_pwiv->cwk[CWK_CWK26M]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[CWK_TOP_MUX_AUD_2],
				aud_cwks[CWK_CWK26M], wet);
			wetuwn wet;
		}
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_2]);
	}

	wetuwn 0;
}

int mt8186_afe_enabwe_cgs(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet = 0;
	int i;

	fow (i = CWK_I2S1_BCWK; i <= CWK_ETDM_OUT1_BCWK; i++) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[i]);
		if (wet) {
			dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[i], wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

void mt8186_afe_disabwe_cgs(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int i;

	fow (i = CWK_I2S1_BCWK; i <= CWK_ETDM_OUT1_BCWK; i++)
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[i]);
}

int mt8186_afe_enabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet = 0;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_INFWA_SYS_AUDIO], wet);
		goto cwk_infwa_sys_audio_eww;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_INFWA_AUDIO_26M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_INFWA_AUDIO_26M], wet);
		goto cwk_infwa_audio_26m_eww;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIO], wet);
		goto cwk_mux_audio_eww;
	}
	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_MUX_AUDIO],
			     afe_pwiv->cwk[CWK_CWK26M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIO],
			aud_cwks[CWK_CWK26M], wet);
		goto cwk_mux_audio_eww;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_MUX_AUDIOINTBUS], wet);
		goto cwk_mux_audio_intbus_eww;
	}
	wet = mt8186_set_audio_int_bus_pawent(afe,
					      CWK_TOP_MAINPWW_D2_D4);
	if (wet)
		goto cwk_mux_audio_intbus_pawent_eww;

	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUDIO_H],
			     afe_pwiv->cwk[CWK_TOP_APWW2_CK]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_TOP_MUX_AUDIO_H],
			aud_cwks[CWK_TOP_APWW2_CK], wet);
		goto cwk_mux_audio_h_pawent_eww;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_AFE]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_AFE], wet);
		goto cwk_afe_eww;
	}

	wetuwn 0;

cwk_afe_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_AFE]);
cwk_mux_audio_h_pawent_eww:
cwk_mux_audio_intbus_pawent_eww:
	mt8186_set_audio_int_bus_pawent(afe, CWK_CWK26M);
cwk_mux_audio_intbus_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
cwk_mux_audio_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
cwk_infwa_sys_audio_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);
cwk_infwa_audio_26m_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_AUDIO_26M]);

	wetuwn wet;
}

void mt8186_afe_disabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_AFE]);
	mt8186_set_audio_int_bus_pawent(afe, CWK_CWK26M);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIO]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_AUDIO_26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUDIO]);
}

int mt8186_afe_suspend_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* set audio int bus to 26M */
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	if (wet) {
		dev_info(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			 __func__, aud_cwks[CWK_MUX_AUDIOINTBUS], wet);
		goto cwk_mux_audio_intbus_eww;
	}
	wet = mt8186_set_audio_int_bus_pawent(afe, CWK_CWK26M);
	if (wet)
		goto cwk_mux_audio_intbus_pawent_eww;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);

	wetuwn 0;

cwk_mux_audio_intbus_pawent_eww:
	mt8186_set_audio_int_bus_pawent(afe, CWK_TOP_MAINPWW_D2_D4);
cwk_mux_audio_intbus_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	wetuwn wet;
}

int mt8186_afe_wesume_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* set audio int bus to nowmaw wowking cwock */
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	if (wet) {
		dev_info(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			 __func__, aud_cwks[CWK_MUX_AUDIOINTBUS], wet);
		goto cwk_mux_audio_intbus_eww;
	}
	wet = mt8186_set_audio_int_bus_pawent(afe,
					      CWK_TOP_MAINPWW_D2_D4);
	if (wet)
		goto cwk_mux_audio_intbus_pawent_eww;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);

	wetuwn 0;

cwk_mux_audio_intbus_pawent_eww:
	mt8186_set_audio_int_bus_pawent(afe, CWK_CWK26M);
cwk_mux_audio_intbus_eww:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_MUX_AUDIOINTBUS]);
	wetuwn wet;
}

int mt8186_apww1_enabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* setting fow APWW */
	apww1_mux_setting(afe, twue);

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW22M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW22M], wet);
		goto eww_cwk_apww22m;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW1_TUNEW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW1_TUNEW], wet);
		goto eww_cwk_apww1_tunew;
	}

	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG, 0xfff7, 0x832);
	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG, 0x1, 0x1);

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_22M_ON_MASK_SFT, BIT(AFE_22M_ON_SFT));

	wetuwn 0;

eww_cwk_apww1_tunew:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW1_TUNEW]);
eww_cwk_apww22m:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW22M]);

	wetuwn wet;
}

void mt8186_apww1_disabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_22M_ON_MASK_SFT, 0);

	wegmap_update_bits(afe->wegmap, AFE_APWW1_TUNEW_CFG, 0x1, 0);

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW1_TUNEW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW22M]);

	apww1_mux_setting(afe, fawse);
}

int mt8186_apww2_enabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	/* setting fow APWW */
	apww2_mux_setting(afe, twue);

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW24M]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW24M], wet);
		goto eww_cwk_apww24m;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_APWW2_TUNEW]);
	if (wet) {
		dev_eww(afe->dev, "%s cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_APWW2_TUNEW], wet);
		goto eww_cwk_apww2_tunew;
	}

	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG, 0xfff7, 0x634);
	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG, 0x1, 0x1);

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_24M_ON_MASK_SFT, BIT(AFE_24M_ON_SFT));

	wetuwn 0;

eww_cwk_apww2_tunew:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW2_TUNEW]);
eww_cwk_apww24m:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW24M]);

	wetuwn wet;
}

void mt8186_apww2_disabwe(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	wegmap_update_bits(afe->wegmap, AFE_HD_ENGEN_ENABWE,
			   AFE_24M_ON_MASK_SFT, 0);

	wegmap_update_bits(afe->wegmap, AFE_APWW2_TUNEW_CFG, 0x1, 0);

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW2_TUNEW]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_APWW24M]);

	apww2_mux_setting(afe, fawse);
}

int mt8186_get_apww_wate(stwuct mtk_base_afe *afe, int apww)
{
	wetuwn (apww == MT8186_APWW1) ? 180633600 : 196608000;
}

int mt8186_get_apww_by_wate(stwuct mtk_base_afe *afe, int wate)
{
	wetuwn ((wate % 8000) == 0) ? MT8186_APWW2 : MT8186_APWW1;
}

int mt8186_get_apww_by_name(stwuct mtk_base_afe *afe, const chaw *name)
{
	if (stwcmp(name, APWW1_W_NAME) == 0)
		wetuwn MT8186_APWW1;

	wetuwn MT8186_APWW2;
}

/* mck */
stwuct mt8186_mck_div {
	u32 m_sew_id;
	u32 div_cwk_id;
};

static const stwuct mt8186_mck_div mck_div[MT8186_MCK_NUM] = {
	[MT8186_I2S0_MCK] = {
		.m_sew_id = CWK_TOP_I2S0_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV0,
	},
	[MT8186_I2S1_MCK] = {
		.m_sew_id = CWK_TOP_I2S1_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV1,
	},
	[MT8186_I2S2_MCK] = {
		.m_sew_id = CWK_TOP_I2S2_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV2,
	},
	[MT8186_I2S4_MCK] = {
		.m_sew_id = CWK_TOP_I2S4_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV4,
	},
	[MT8186_TDM_MCK] = {
		.m_sew_id = CWK_TOP_TDM_M_SEW,
		.div_cwk_id = CWK_TOP_APWW12_DIV_TDM,
	},
};

int mt8186_mck_enabwe(stwuct mtk_base_afe *afe, int mck_id, int wate)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int apww = mt8186_get_apww_by_wate(afe, wate);
	int apww_cwk_id = apww == MT8186_APWW1 ?
			  CWK_TOP_MUX_AUD_1 : CWK_TOP_MUX_AUD_2;
	int m_sew_id = mck_div[mck_id].m_sew_id;
	int div_cwk_id = mck_div[mck_id].div_cwk_id;
	int wet;

	/* sewect apww */
	if (m_sew_id >= 0) {
		wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[m_sew_id]);
		if (wet) {
			dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
				__func__, aud_cwks[m_sew_id], wet);
			wetuwn wet;
		}
		wet = cwk_set_pawent(afe_pwiv->cwk[m_sew_id],
				     afe_pwiv->cwk[apww_cwk_id]);
		if (wet) {
			dev_eww(afe->dev, "%s(), cwk_set_pawent %s-%s faiw %d\n",
				__func__, aud_cwks[m_sew_id],
				aud_cwks[apww_cwk_id], wet);
			wetuwn wet;
		}
	}

	/* enabwe div, set wate */
	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[div_cwk_id]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[div_cwk_id], wet);
		wetuwn wet;
	}
	wet = cwk_set_wate(afe_pwiv->cwk[div_cwk_id], wate);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_set_wate %s, wate %d, faiw %d\n",
			__func__, aud_cwks[div_cwk_id], wate, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void mt8186_mck_disabwe(stwuct mtk_base_afe *afe, int mck_id)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int m_sew_id = mck_div[mck_id].m_sew_id;
	int div_cwk_id = mck_div[mck_id].div_cwk_id;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[div_cwk_id]);
	if (m_sew_id >= 0)
		cwk_disabwe_unpwepawe(afe_pwiv->cwk[m_sew_id]);
}

int mt8186_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct device_node *of_node = afe->dev->of_node;
	int i = 0;

	mt8186_audsys_cwk_wegistew(afe);

	afe_pwiv->cwk = devm_kcawwoc(afe->dev, CWK_NUM, sizeof(*afe_pwiv->cwk),
				     GFP_KEWNEW);
	if (!afe_pwiv->cwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < CWK_NUM; i++) {
		afe_pwiv->cwk[i] = devm_cwk_get(afe->dev, aud_cwks[i]);
		if (IS_EWW(afe_pwiv->cwk[i])) {
			dev_eww(afe->dev, "%s devm_cwk_get %s faiw, wet %wd\n",
				__func__,
				aud_cwks[i], PTW_EWW(afe_pwiv->cwk[i]));
			afe_pwiv->cwk[i] = NUWW;
		}
	}

	afe_pwiv->apmixedsys = syscon_wegmap_wookup_by_phandwe(of_node,
							       "mediatek,apmixedsys");
	if (IS_EWW(afe_pwiv->apmixedsys)) {
		dev_eww(afe->dev, "%s() Cannot find apmixedsys contwowwew: %wd\n",
			__func__, PTW_EWW(afe_pwiv->apmixedsys));
		wetuwn PTW_EWW(afe_pwiv->apmixedsys);
	}

	afe_pwiv->topckgen = syscon_wegmap_wookup_by_phandwe(of_node,
							     "mediatek,topckgen");
	if (IS_EWW(afe_pwiv->topckgen)) {
		dev_eww(afe->dev, "%s() Cannot find topckgen contwowwew: %wd\n",
			__func__, PTW_EWW(afe_pwiv->topckgen));
		wetuwn PTW_EWW(afe_pwiv->topckgen);
	}

	afe_pwiv->infwacfg = syscon_wegmap_wookup_by_phandwe(of_node,
							     "mediatek,infwacfg");
	if (IS_EWW(afe_pwiv->infwacfg)) {
		dev_eww(afe->dev, "%s() Cannot find infwacfg: %wd\n",
			__func__, PTW_EWW(afe_pwiv->infwacfg));
		wetuwn PTW_EWW(afe_pwiv->infwacfg);
	}

	wetuwn 0;
}
