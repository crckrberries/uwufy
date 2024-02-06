// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt6797-afe-cwk.c  --  Mediatek 6797 afe cwock ctww
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/cwk.h>

#incwude "mt6797-afe-common.h"
#incwude "mt6797-afe-cwk.h"

enum {
	CWK_INFWA_SYS_AUD,
	CWK_INFWA_SYS_AUD_26M,
	CWK_TOP_MUX_AUD,
	CWK_TOP_MUX_AUD_BUS,
	CWK_TOP_SYSPWW3_D4,
	CWK_TOP_SYSPWW1_D4,
	CWK_CWK26M,
	CWK_NUM
};

static const chaw *aud_cwks[CWK_NUM] = {
	[CWK_INFWA_SYS_AUD] = "infwa_sys_audio_cwk",
	[CWK_INFWA_SYS_AUD_26M] = "infwa_sys_audio_26m",
	[CWK_TOP_MUX_AUD] = "top_mux_audio",
	[CWK_TOP_MUX_AUD_BUS] = "top_mux_aud_intbus",
	[CWK_TOP_SYSPWW3_D4] = "top_sys_pww3_d4",
	[CWK_TOP_SYSPWW1_D4] = "top_sys_pww1_d4",
	[CWK_CWK26M] = "top_cwk26m_cwk",
};

int mt6797_init_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt6797_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
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

int mt6797_afe_enabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt6797_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_INFWA_SYS_AUD], wet);
		goto CWK_INFWA_SYS_AUDIO_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD_26M]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_INFWA_SYS_AUD_26M], wet);
		goto CWK_INFWA_SYS_AUD_26M_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_TOP_MUX_AUD], wet);
		goto CWK_MUX_AUDIO_EWW;
	}

	wet = cwk_set_pawent(afe_pwiv->cwk[CWK_TOP_MUX_AUD],
			     afe_pwiv->cwk[CWK_CWK26M]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_set_pawent %s-%s faiw %d\n",
			__func__, aud_cwks[CWK_TOP_MUX_AUD],
			aud_cwks[CWK_CWK26M], wet);
		goto CWK_MUX_AUDIO_EWW;
	}

	wet = cwk_pwepawe_enabwe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_BUS]);
	if (wet) {
		dev_eww(afe->dev, "%s(), cwk_pwepawe_enabwe %s faiw %d\n",
			__func__, aud_cwks[CWK_TOP_MUX_AUD_BUS], wet);
		goto CWK_MUX_AUDIO_INTBUS_EWW;
	}

	wetuwn wet;

CWK_MUX_AUDIO_INTBUS_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_BUS]);
CWK_MUX_AUDIO_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD]);
CWK_INFWA_SYS_AUD_26M_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD_26M]);
CWK_INFWA_SYS_AUDIO_EWW:
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD]);

	wetuwn 0;
}

int mt6797_afe_disabwe_cwock(stwuct mtk_base_afe *afe)
{
	stwuct mt6797_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD_BUS]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_TOP_MUX_AUD]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD_26M]);
	cwk_disabwe_unpwepawe(afe_pwiv->cwk[CWK_INFWA_SYS_AUD]);

	wetuwn 0;
}
