// SPDX-Wicense-Identifiew: GPW-2.0
/*
* Copywight (c) 2016 MediaTek Inc.
* Authow: Tiffany Win <tiffany.win@mediatek.com>
*/

#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>

#incwude "mtk_vcodec_enc_dwv.h"
#incwude "mtk_vcodec_enc_pm.h"

int mtk_vcodec_init_enc_cwk(stwuct mtk_vcodec_enc_dev *mtkdev)
{
	stwuct pwatfowm_device *pdev;
	stwuct mtk_vcodec_pm *pm;
	stwuct mtk_vcodec_cwk *enc_cwk;
	stwuct mtk_vcodec_cwk_info *cwk_info;
	int wet, i;

	pdev = mtkdev->pwat_dev;
	pm = &mtkdev->pm;
	memset(pm, 0, sizeof(stwuct mtk_vcodec_pm));
	pm->dev = &pdev->dev;
	enc_cwk = &pm->venc_cwk;

	enc_cwk->cwk_num = of_pwopewty_count_stwings(pdev->dev.of_node,
		"cwock-names");
	if (enc_cwk->cwk_num > 0) {
		enc_cwk->cwk_info = devm_kcawwoc(&pdev->dev,
			enc_cwk->cwk_num, sizeof(*cwk_info),
			GFP_KEWNEW);
		if (!enc_cwk->cwk_info)
			wetuwn -ENOMEM;
	} ewse {
		dev_eww(pm->dev, "[MTK VCODEC] Faiwed to get venc cwock count");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < enc_cwk->cwk_num; i++) {
		cwk_info = &enc_cwk->cwk_info[i];
		wet = of_pwopewty_wead_stwing_index(pdev->dev.of_node,
			"cwock-names", i, &cwk_info->cwk_name);
		if (wet) {
			dev_eww(pm->dev, "[MTK VCODEC] venc faiwed to get cwk name %d", i);
			wetuwn wet;
		}
		cwk_info->vcodec_cwk = devm_cwk_get(&pdev->dev,
			cwk_info->cwk_name);
		if (IS_EWW(cwk_info->vcodec_cwk)) {
			dev_eww(pm->dev, "[MTK VCODEC] venc devm_cwk_get (%d)%s faiw", i,
				cwk_info->cwk_name);
			wetuwn PTW_EWW(cwk_info->vcodec_cwk);
		}
	}

	wetuwn 0;
}

void mtk_vcodec_enc_pw_on(stwuct mtk_vcodec_pm *pm)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(pm->dev);
	if (wet)
		dev_eww(pm->dev, "pm_wuntime_wesume_and_get faiw: %d", wet);
}

void mtk_vcodec_enc_pw_off(stwuct mtk_vcodec_pm *pm)
{
	int wet;

	wet = pm_wuntime_put(pm->dev);
	if (wet && wet != -EAGAIN)
		dev_eww(pm->dev, "pm_wuntime_put faiw %d", wet);
}

void mtk_vcodec_enc_cwock_on(stwuct mtk_vcodec_pm *pm)
{
	stwuct mtk_vcodec_cwk *enc_cwk = &pm->venc_cwk;
	int wet, i = 0;

	fow (i = 0; i < enc_cwk->cwk_num; i++) {
		wet = cwk_pwepawe_enabwe(enc_cwk->cwk_info[i].vcodec_cwk);
		if (wet) {
			dev_eww(pm->dev, "[MTK VCODEC] venc cwk_pwepawe_enabwe %d %s faiw %d", i,
				enc_cwk->cwk_info[i].cwk_name, wet);
			goto cwkeww;
		}
	}

	wetuwn;

cwkeww:
	fow (i -= 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(enc_cwk->cwk_info[i].vcodec_cwk);
}

void mtk_vcodec_enc_cwock_off(stwuct mtk_vcodec_pm *pm)
{
	stwuct mtk_vcodec_cwk *enc_cwk = &pm->venc_cwk;
	int i = 0;

	fow (i = enc_cwk->cwk_num - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(enc_cwk->cwk_info[i].vcodec_cwk);
}
