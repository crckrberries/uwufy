// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight(c) 2021 Mediatek Cowpowation. Aww wights wesewved.
//
// Authow: YC Hung <yc.hung@mediatek.com>
//
// Hawdwawe intewface fow mt8195 DSP cwock

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude "mt8195.h"
#incwude "mt8195-cwk.h"
#incwude "../adsp_hewpew.h"
#incwude "../../sof-audio.h"

static const chaw *adsp_cwks[ADSP_CWK_MAX] = {
	[CWK_TOP_ADSP] = "adsp_sew",
	[CWK_TOP_CWK26M] = "cwk26m_ck",
	[CWK_TOP_AUDIO_WOCAW_BUS] = "audio_wocaw_bus",
	[CWK_TOP_MAINPWW_D7_D2] = "mainpww_d7_d2",
	[CWK_SCP_ADSP_AUDIODSP] = "scp_adsp_audiodsp",
	[CWK_TOP_AUDIO_H] = "audio_h",
};

int mt8195_adsp_init_cwock(stwuct snd_sof_dev *sdev)
{
	stwuct device *dev = sdev->dev;
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;
	int i;

	pwiv->cwk = devm_kcawwoc(dev, ADSP_CWK_MAX, sizeof(*pwiv->cwk), GFP_KEWNEW);

	if (!pwiv->cwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < ADSP_CWK_MAX; i++) {
		pwiv->cwk[i] = devm_cwk_get(dev, adsp_cwks[i]);
		if (IS_EWW(pwiv->cwk[i]))
			wetuwn PTW_EWW(pwiv->cwk[i]);
	}

	wetuwn 0;
}

static int adsp_enabwe_aww_cwock(stwuct snd_sof_dev *sdev)
{
	stwuct device *dev = sdev->dev;
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk[CWK_TOP_MAINPWW_D7_D2]);
	if (wet) {
		dev_eww(dev, "%s cwk_pwepawe_enabwe(mainpww_d7_d2) faiw %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk[CWK_TOP_ADSP]);
	if (wet) {
		dev_eww(dev, "%s cwk_pwepawe_enabwe(adsp_sew) faiw %d\n",
			__func__, wet);
		goto disabwe_mainpww_d7_d2_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk[CWK_TOP_AUDIO_WOCAW_BUS]);
	if (wet) {
		dev_eww(dev, "%s cwk_pwepawe_enabwe(audio_wocaw_bus) faiw %d\n",
			__func__, wet);
		goto disabwe_dsp_sew_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk[CWK_SCP_ADSP_AUDIODSP]);
	if (wet) {
		dev_eww(dev, "%s cwk_pwepawe_enabwe(scp_adsp_audiodsp) faiw %d\n",
			__func__, wet);
		goto disabwe_audio_wocaw_bus_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk[CWK_TOP_AUDIO_H]);
	if (wet) {
		dev_eww(dev, "%s cwk_pwepawe_enabwe(audio_h) faiw %d\n",
			__func__, wet);
		goto disabwe_scp_adsp_audiodsp_cwk;
	}

	wetuwn 0;

disabwe_scp_adsp_audiodsp_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_SCP_ADSP_AUDIODSP]);
disabwe_audio_wocaw_bus_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_AUDIO_WOCAW_BUS]);
disabwe_dsp_sew_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_ADSP]);
disabwe_mainpww_d7_d2_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_MAINPWW_D7_D2]);

	wetuwn wet;
}

static void adsp_disabwe_aww_cwock(stwuct snd_sof_dev *sdev)
{
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;

	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_AUDIO_H]);
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_SCP_ADSP_AUDIODSP]);
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_AUDIO_WOCAW_BUS]);
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_ADSP]);
	cwk_disabwe_unpwepawe(pwiv->cwk[CWK_TOP_MAINPWW_D7_D2]);
}

static int adsp_defauwt_cwk_init(stwuct snd_sof_dev *sdev, boow enabwe)
{
	stwuct device *dev = sdev->dev;
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;
	int wet;

	dev_dbg(dev, "%s: %s\n", __func__, enabwe ? "on" : "off");

	if (enabwe) {
		wet = cwk_set_pawent(pwiv->cwk[CWK_TOP_ADSP],
				     pwiv->cwk[CWK_TOP_CWK26M]);
		if (wet) {
			dev_eww(dev, "faiwed to set dsp_sew to cwk26m: %d\n", wet);
			wetuwn wet;
		}

		wet = cwk_set_pawent(pwiv->cwk[CWK_TOP_AUDIO_WOCAW_BUS],
				     pwiv->cwk[CWK_TOP_MAINPWW_D7_D2]);
		if (wet) {
			dev_eww(dev, "set audio_wocaw_bus faiwed %d\n", wet);
			wetuwn wet;
		}

		wet = cwk_set_pawent(pwiv->cwk[CWK_TOP_AUDIO_H],
				     pwiv->cwk[CWK_TOP_CWK26M]);
		if (wet) {
			dev_eww(dev, "set audio_h_sew faiwed %d\n", wet);
			wetuwn wet;
		}

		wet = adsp_enabwe_aww_cwock(sdev);
		if (wet) {
			dev_eww(dev, "faiwed to adsp_enabwe_cwock: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		adsp_disabwe_aww_cwock(sdev);
	}

	wetuwn 0;
}

int adsp_cwock_on(stwuct snd_sof_dev *sdev)
{
	/* Open ADSP cwock */
	wetuwn adsp_defauwt_cwk_init(sdev, 1);
}

int adsp_cwock_off(stwuct snd_sof_dev *sdev)
{
	/* Cwose ADSP cwock */
	wetuwn adsp_defauwt_cwk_init(sdev, 0);
}

