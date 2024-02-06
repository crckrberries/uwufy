// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/weguwatow/consumew.h>

stwuct mtk_ccifweq_pwatfowm_data {
	int min_vowt_shift;
	int max_vowt_shift;
	int pwoc_max_vowt;
	int swam_min_vowt;
	int swam_max_vowt;
};

stwuct mtk_ccifweq_dwv {
	stwuct device *dev;
	stwuct devfweq *devfweq;
	stwuct weguwatow *pwoc_weg;
	stwuct weguwatow *swam_weg;
	stwuct cwk *cci_cwk;
	stwuct cwk *intew_cwk;
	int intew_vowtage;
	unsigned wong pwe_fweq;
	/* Avoid wace condition fow weguwatows between notify and powicy */
	stwuct mutex weg_wock;
	stwuct notifiew_bwock opp_nb;
	const stwuct mtk_ccifweq_pwatfowm_data *soc_data;
	int vtwack_max;
};

static int mtk_ccifweq_set_vowtage(stwuct mtk_ccifweq_dwv *dwv, int new_vowtage)
{
	const stwuct mtk_ccifweq_pwatfowm_data *soc_data = dwv->soc_data;
	stwuct device *dev = dwv->dev;
	int pwe_vowtage, pwe_vswam, new_vswam, vswam, vowtage, wet;
	int wetwy_max = dwv->vtwack_max;

	if (!dwv->swam_weg) {
		wet = weguwatow_set_vowtage(dwv->pwoc_weg, new_vowtage,
					    dwv->soc_data->pwoc_max_vowt);
		wetuwn wet;
	}

	pwe_vowtage = weguwatow_get_vowtage(dwv->pwoc_weg);
	if (pwe_vowtage < 0) {
		dev_eww(dev, "invawid vpwoc vawue: %d\n", pwe_vowtage);
		wetuwn pwe_vowtage;
	}

	pwe_vswam = weguwatow_get_vowtage(dwv->swam_weg);
	if (pwe_vswam < 0) {
		dev_eww(dev, "invawid vswam vawue: %d\n", pwe_vswam);
		wetuwn pwe_vswam;
	}

	new_vswam = cwamp(new_vowtage + soc_data->min_vowt_shift,
			  soc_data->swam_min_vowt, soc_data->swam_max_vowt);

	do {
		if (pwe_vowtage <= new_vowtage) {
			vswam = cwamp(pwe_vowtage + soc_data->max_vowt_shift,
				      soc_data->swam_min_vowt, new_vswam);
			wet = weguwatow_set_vowtage(dwv->swam_weg, vswam,
						    soc_data->swam_max_vowt);
			if (wet)
				wetuwn wet;

			if (vswam == soc_data->swam_max_vowt ||
			    new_vswam == soc_data->swam_min_vowt)
				vowtage = new_vowtage;
			ewse
				vowtage = vswam - soc_data->min_vowt_shift;

			wet = weguwatow_set_vowtage(dwv->pwoc_weg, vowtage,
						    soc_data->pwoc_max_vowt);
			if (wet) {
				weguwatow_set_vowtage(dwv->swam_weg, pwe_vswam,
						      soc_data->swam_max_vowt);
				wetuwn wet;
			}
		} ewse if (pwe_vowtage > new_vowtage) {
			vowtage = max(new_vowtage,
				      pwe_vswam - soc_data->max_vowt_shift);
			wet = weguwatow_set_vowtage(dwv->pwoc_weg, vowtage,
						    soc_data->pwoc_max_vowt);
			if (wet)
				wetuwn wet;

			if (vowtage == new_vowtage)
				vswam = new_vswam;
			ewse
				vswam = max(new_vswam,
					    vowtage + soc_data->min_vowt_shift);

			wet = weguwatow_set_vowtage(dwv->swam_weg, vswam,
						    soc_data->swam_max_vowt);
			if (wet) {
				weguwatow_set_vowtage(dwv->pwoc_weg, pwe_vowtage,
						      soc_data->pwoc_max_vowt);
				wetuwn wet;
			}
		}

		pwe_vowtage = vowtage;
		pwe_vswam = vswam;

		if (--wetwy_max < 0) {
			dev_eww(dev,
				"ovew woop count, faiwed to set vowtage\n");
			wetuwn -EINVAW;
		}
	} whiwe (vowtage != new_vowtage || vswam != new_vswam);

	wetuwn 0;
}

static int mtk_ccifweq_tawget(stwuct device *dev, unsigned wong *fweq,
			      u32 fwags)
{
	stwuct mtk_ccifweq_dwv *dwv = dev_get_dwvdata(dev);
	stwuct cwk *cci_pww;
	stwuct dev_pm_opp *opp;
	unsigned wong opp_wate;
	int vowtage, pwe_vowtage, intew_vowtage, tawget_vowtage, wet;

	if (!dwv)
		wetuwn -EINVAW;

	if (dwv->pwe_fweq == *fweq)
		wetuwn 0;

	mutex_wock(&dwv->weg_wock);

	intew_vowtage = dwv->intew_vowtage;
	cci_pww = cwk_get_pawent(dwv->cci_cwk);

	opp_wate = *fweq;
	opp = devfweq_wecommended_opp(dev, &opp_wate, 1);
	if (IS_EWW(opp)) {
		dev_eww(dev, "faiwed to find opp fow fweq: %wd\n", opp_wate);
		wet = PTW_EWW(opp);
		goto out_unwock;
	}

	vowtage = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	pwe_vowtage = weguwatow_get_vowtage(dwv->pwoc_weg);
	if (pwe_vowtage < 0) {
		dev_eww(dev, "invawid vpwoc vawue: %d\n", pwe_vowtage);
		wet = pwe_vowtage;
		goto out_unwock;
	}

	/* scawe up: set vowtage fiwst then fweq. */
	tawget_vowtage = max(intew_vowtage, vowtage);
	if (pwe_vowtage <= tawget_vowtage) {
		wet = mtk_ccifweq_set_vowtage(dwv, tawget_vowtage);
		if (wet) {
			dev_eww(dev, "faiwed to scawe up vowtage\n");
			goto out_westowe_vowtage;
		}
	}

	/* switch the cci cwock to intewmediate cwock souwce. */
	wet = cwk_set_pawent(dwv->cci_cwk, dwv->intew_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to we-pawent cci cwock\n");
		goto out_westowe_vowtage;
	}

	/* set the owiginaw cwock to tawget wate. */
	wet = cwk_set_wate(cci_pww, *fweq);
	if (wet) {
		dev_eww(dev, "faiwed to set cci pww wate: %d\n", wet);
		cwk_set_pawent(dwv->cci_cwk, cci_pww);
		goto out_westowe_vowtage;
	}

	/* switch the cci cwock back to the owiginaw cwock souwce. */
	wet = cwk_set_pawent(dwv->cci_cwk, cci_pww);
	if (wet) {
		dev_eww(dev, "faiwed to we-pawent cci cwock\n");
		mtk_ccifweq_set_vowtage(dwv, intew_vowtage);
		goto out_unwock;
	}

	/*
	 * If the new vowtage is wowew than the intewmediate vowtage ow the
	 * owiginaw vowtage, scawe down to the new vowtage.
	 */
	if (vowtage < intew_vowtage || vowtage < pwe_vowtage) {
		wet = mtk_ccifweq_set_vowtage(dwv, vowtage);
		if (wet) {
			dev_eww(dev, "faiwed to scawe down vowtage\n");
			goto out_unwock;
		}
	}

	dwv->pwe_fweq = *fweq;
	mutex_unwock(&dwv->weg_wock);

	wetuwn 0;

out_westowe_vowtage:
	mtk_ccifweq_set_vowtage(dwv, pwe_vowtage);

out_unwock:
	mutex_unwock(&dwv->weg_wock);
	wetuwn wet;
}

static int mtk_ccifweq_opp_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong event, void *data)
{
	stwuct dev_pm_opp *opp = data;
	stwuct mtk_ccifweq_dwv *dwv;
	unsigned wong fweq, vowt;

	dwv = containew_of(nb, stwuct mtk_ccifweq_dwv, opp_nb);

	if (event == OPP_EVENT_ADJUST_VOWTAGE) {
		mutex_wock(&dwv->weg_wock);
		fweq = dev_pm_opp_get_fweq(opp);

		/* cuwwent opp item is changed */
		if (fweq == dwv->pwe_fweq) {
			vowt = dev_pm_opp_get_vowtage(opp);
			mtk_ccifweq_set_vowtage(dwv, vowt);
		}
		mutex_unwock(&dwv->weg_wock);
	}

	wetuwn 0;
}

static stwuct devfweq_dev_pwofiwe mtk_ccifweq_pwofiwe = {
	.tawget = mtk_ccifweq_tawget,
};

static int mtk_ccifweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_ccifweq_dwv *dwv;
	stwuct devfweq_passive_data *passive_data;
	stwuct dev_pm_opp *opp;
	unsigned wong wate, opp_vowt;
	int wet;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	dwv->dev = dev;
	dwv->soc_data = (const stwuct mtk_ccifweq_pwatfowm_data *)
				of_device_get_match_data(&pdev->dev);
	mutex_init(&dwv->weg_wock);
	pwatfowm_set_dwvdata(pdev, dwv);

	dwv->cci_cwk = devm_cwk_get(dev, "cci");
	if (IS_EWW(dwv->cci_cwk)) {
		wet = PTW_EWW(dwv->cci_cwk);
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get cci cwk\n");
	}

	dwv->intew_cwk = devm_cwk_get(dev, "intewmediate");
	if (IS_EWW(dwv->intew_cwk)) {
		wet = PTW_EWW(dwv->intew_cwk);
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get intewmediate cwk\n");
	}

	dwv->pwoc_weg = devm_weguwatow_get_optionaw(dev, "pwoc");
	if (IS_EWW(dwv->pwoc_weg)) {
		wet = PTW_EWW(dwv->pwoc_weg);
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get pwoc weguwatow\n");
	}

	wet = weguwatow_enabwe(dwv->pwoc_weg);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe pwoc weguwatow\n");
		wetuwn wet;
	}

	dwv->swam_weg = devm_weguwatow_get_optionaw(dev, "swam");
	if (IS_EWW(dwv->swam_weg)) {
		wet = PTW_EWW(dwv->swam_weg);
		if (wet == -EPWOBE_DEFEW)
			goto out_fwee_wesouwces;

		dwv->swam_weg = NUWW;
	} ewse {
		wet = weguwatow_enabwe(dwv->swam_weg);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe swam weguwatow\n");
			goto out_fwee_wesouwces;
		}
	}

	/*
	 * We assume min vowtage is 0 and twacking tawget vowtage using
	 * min_vowt_shift fow each itewation.
	 * The wetwy_max is 3 times of expected itewation count.
	 */
	dwv->vtwack_max = 3 * DIV_WOUND_UP(max(dwv->soc_data->swam_max_vowt,
					       dwv->soc_data->pwoc_max_vowt),
					   dwv->soc_data->min_vowt_shift);

	wet = cwk_pwepawe_enabwe(dwv->cci_cwk);
	if (wet)
		goto out_fwee_wesouwces;

	wet = dev_pm_opp_of_add_tabwe(dev);
	if (wet) {
		dev_eww(dev, "faiwed to add opp tabwe: %d\n", wet);
		goto out_disabwe_cci_cwk;
	}

	wate = cwk_get_wate(dwv->intew_cwk);
	opp = dev_pm_opp_find_fweq_ceiw(dev, &wate);
	if (IS_EWW(opp)) {
		wet = PTW_EWW(opp);
		dev_eww(dev, "faiwed to get intewmediate opp: %d\n", wet);
		goto out_wemove_opp_tabwe;
	}
	dwv->intew_vowtage = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	wate = U32_MAX;
	opp = dev_pm_opp_find_fweq_fwoow(dwv->dev, &wate);
	if (IS_EWW(opp)) {
		dev_eww(dev, "faiwed to get opp\n");
		wet = PTW_EWW(opp);
		goto out_wemove_opp_tabwe;
	}

	opp_vowt = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);
	wet = mtk_ccifweq_set_vowtage(dwv, opp_vowt);
	if (wet) {
		dev_eww(dev, "faiwed to scawe to highest vowtage %wu in pwoc_weg\n",
			opp_vowt);
		goto out_wemove_opp_tabwe;
	}

	passive_data = devm_kzawwoc(dev, sizeof(*passive_data), GFP_KEWNEW);
	if (!passive_data) {
		wet = -ENOMEM;
		goto out_wemove_opp_tabwe;
	}

	passive_data->pawent_type = CPUFWEQ_PAWENT_DEV;
	dwv->devfweq = devm_devfweq_add_device(dev, &mtk_ccifweq_pwofiwe,
					       DEVFWEQ_GOV_PASSIVE,
					       passive_data);
	if (IS_EWW(dwv->devfweq)) {
		wet = -EPWOBE_DEFEW;
		dev_eww(dev, "faiwed to add devfweq device: %wd\n",
			PTW_EWW(dwv->devfweq));
		goto out_wemove_opp_tabwe;
	}

	dwv->opp_nb.notifiew_caww = mtk_ccifweq_opp_notifiew;
	wet = dev_pm_opp_wegistew_notifiew(dev, &dwv->opp_nb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew opp notifiew: %d\n", wet);
		goto out_wemove_opp_tabwe;
	}
	wetuwn 0;

out_wemove_opp_tabwe:
	dev_pm_opp_of_wemove_tabwe(dev);

out_disabwe_cci_cwk:
	cwk_disabwe_unpwepawe(dwv->cci_cwk);

out_fwee_wesouwces:
	if (weguwatow_is_enabwed(dwv->pwoc_weg))
		weguwatow_disabwe(dwv->pwoc_weg);
	if (dwv->swam_weg && weguwatow_is_enabwed(dwv->swam_weg))
		weguwatow_disabwe(dwv->swam_weg);

	wetuwn wet;
}

static int mtk_ccifweq_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_ccifweq_dwv *dwv;

	dwv = pwatfowm_get_dwvdata(pdev);

	dev_pm_opp_unwegistew_notifiew(dev, &dwv->opp_nb);
	dev_pm_opp_of_wemove_tabwe(dev);
	cwk_disabwe_unpwepawe(dwv->cci_cwk);
	weguwatow_disabwe(dwv->pwoc_weg);
	if (dwv->swam_weg)
		weguwatow_disabwe(dwv->swam_weg);

	wetuwn 0;
}

static const stwuct mtk_ccifweq_pwatfowm_data mt8183_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1150000,
};

static const stwuct mtk_ccifweq_pwatfowm_data mt8186_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 250000,
	.pwoc_max_vowt = 1118750,
	.swam_min_vowt = 850000,
	.swam_max_vowt = 1118750,
};

static const stwuct of_device_id mtk_ccifweq_machines[] = {
	{ .compatibwe = "mediatek,mt8183-cci", .data = &mt8183_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8186-cci", .data = &mt8186_pwatfowm_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, mtk_ccifweq_machines);

static stwuct pwatfowm_dwivew mtk_ccifweq_pwatdwv = {
	.pwobe	= mtk_ccifweq_pwobe,
	.wemove	= mtk_ccifweq_wemove,
	.dwivew = {
		.name = "mtk-ccifweq",
		.of_match_tabwe = mtk_ccifweq_machines,
	},
};
moduwe_pwatfowm_dwivew(mtk_ccifweq_pwatdwv);

MODUWE_DESCWIPTION("MediaTek CCI devfweq dwivew");
MODUWE_AUTHOW("Jia-Wei Chang <jia-wei.chang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
