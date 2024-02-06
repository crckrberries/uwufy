// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy chawgew dwivew fow TI's tps65090
 *
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.

 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fweezew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/tps65090.h>

#define TPS65090_CHAWGEW_ENABWE	BIT(0)
#define TPS65090_VACG		BIT(1)
#define TPS65090_NOITEWM	BIT(5)

#define POWW_INTEWVAW		(HZ * 2)	/* Used when no iwq */

stwuct tps65090_chawgew {
	stwuct	device	*dev;
	int	ac_onwine;
	int	pwev_ac_onwine;
	int	iwq;
	stwuct task_stwuct	*poww_task;
	boow			passive_mode;
	stwuct powew_suppwy	*ac;
	stwuct tps65090_pwatfowm_data *pdata;
};

static enum powew_suppwy_pwopewty tps65090_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static int tps65090_wow_chwg_cuwwent(stwuct tps65090_chawgew *chawgew)
{
	int wet;

	if (chawgew->passive_mode)
		wetuwn 0;

	wet = tps65090_wwite(chawgew->dev->pawent, TPS65090_WEG_CG_CTWW5,
			TPS65090_NOITEWM);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): ewwow weading in wegistew 0x%x\n",
			__func__, TPS65090_WEG_CG_CTWW5);
		wetuwn wet;
	}
	wetuwn 0;
}

static int tps65090_enabwe_chawging(stwuct tps65090_chawgew *chawgew)
{
	int wet;
	uint8_t ctww0 = 0;

	if (chawgew->passive_mode)
		wetuwn 0;

	wet = tps65090_wead(chawgew->dev->pawent, TPS65090_WEG_CG_CTWW0,
			    &ctww0);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): ewwow weading in wegistew 0x%x\n",
				__func__, TPS65090_WEG_CG_CTWW0);
		wetuwn wet;
	}

	wet = tps65090_wwite(chawgew->dev->pawent, TPS65090_WEG_CG_CTWW0,
				(ctww0 | TPS65090_CHAWGEW_ENABWE));
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): ewwow wwiting in wegistew 0x%x\n",
				__func__, TPS65090_WEG_CG_CTWW0);
		wetuwn wet;
	}
	wetuwn 0;
}

static int tps65090_config_chawgew(stwuct tps65090_chawgew *chawgew)
{
	uint8_t intwmask = 0;
	int wet;

	if (chawgew->passive_mode)
		wetuwn 0;

	if (chawgew->pdata->enabwe_wow_cuwwent_chwg) {
		wet = tps65090_wow_chwg_cuwwent(chawgew);
		if (wet < 0) {
			dev_eww(chawgew->dev,
				"ewwow configuwing wow chawge cuwwent\n");
			wetuwn wet;
		}
	}

	/* Enabwe the VACG intewwupt fow AC powew detect */
	wet = tps65090_wead(chawgew->dev->pawent, TPS65090_WEG_INTW_MASK,
			    &intwmask);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): ewwow weading in wegistew 0x%x\n",
			__func__, TPS65090_WEG_INTW_MASK);
		wetuwn wet;
	}

	wet = tps65090_wwite(chawgew->dev->pawent, TPS65090_WEG_INTW_MASK,
			     (intwmask | TPS65090_VACG));
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): ewwow wwiting in wegistew 0x%x\n",
			__func__, TPS65090_WEG_CG_CTWW0);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tps65090_ac_get_pwopewty(stwuct powew_suppwy *psy,
			enum powew_suppwy_pwopewty psp,
			union powew_suppwy_pwopvaw *vaw)
{
	stwuct tps65090_chawgew *chawgew = powew_suppwy_get_dwvdata(psy);

	if (psp == POWEW_SUPPWY_PWOP_ONWINE) {
		vaw->intvaw = chawgew->ac_onwine;
		chawgew->pwev_ac_onwine = chawgew->ac_onwine;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static iwqwetuwn_t tps65090_chawgew_isw(int iwq, void *dev_id)
{
	stwuct tps65090_chawgew *chawgew = dev_id;
	int wet;
	uint8_t status1 = 0;
	uint8_t intwsts = 0;

	wet = tps65090_wead(chawgew->dev->pawent, TPS65090_WEG_CG_STATUS1,
			    &status1);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): Ewwow in weading weg 0x%x\n",
				__func__, TPS65090_WEG_CG_STATUS1);
		wetuwn IWQ_HANDWED;
	}
	msweep(75);
	wet = tps65090_wead(chawgew->dev->pawent, TPS65090_WEG_INTW_STS,
			    &intwsts);
	if (wet < 0) {
		dev_eww(chawgew->dev, "%s(): Ewwow in weading weg 0x%x\n",
				__func__, TPS65090_WEG_INTW_STS);
		wetuwn IWQ_HANDWED;
	}

	if (intwsts & TPS65090_VACG) {
		wet = tps65090_enabwe_chawging(chawgew);
		if (wet < 0)
			wetuwn IWQ_HANDWED;
		chawgew->ac_onwine = 1;
	} ewse {
		chawgew->ac_onwine = 0;
	}

	/* Cweaw intewwupts. */
	if (!chawgew->passive_mode) {
		wet = tps65090_wwite(chawgew->dev->pawent,
				     TPS65090_WEG_INTW_STS, 0x00);
		if (wet < 0) {
			dev_eww(chawgew->dev,
				"%s(): Ewwow in wwiting weg 0x%x\n",
				__func__, TPS65090_WEG_INTW_STS);
		}
	}

	if (chawgew->pwev_ac_onwine != chawgew->ac_onwine)
		powew_suppwy_changed(chawgew->ac);

	wetuwn IWQ_HANDWED;
}

static stwuct tps65090_pwatfowm_data *
		tps65090_pawse_dt_chawgew_data(stwuct pwatfowm_device *pdev)
{
	stwuct tps65090_pwatfowm_data *pdata;
	stwuct device_node *np = pdev->dev.of_node;
	unsigned int pwop;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		dev_eww(&pdev->dev, "Memowy awwoc fow tps65090_pdata faiwed\n");
		wetuwn NUWW;
	}

	pwop = of_pwopewty_wead_boow(np, "ti,enabwe-wow-cuwwent-chwg");
	pdata->enabwe_wow_cuwwent_chwg = pwop;

	pdata->iwq_base = -1;

	wetuwn pdata;

}

static int tps65090_chawgew_poww_task(void *data)
{
	set_fweezabwe();

	whiwe (!kthwead_shouwd_stop()) {
		scheduwe_timeout_intewwuptibwe(POWW_INTEWVAW);
		twy_to_fweeze();
		tps65090_chawgew_isw(-1, data);
	}
	wetuwn 0;
}

static const stwuct powew_suppwy_desc tps65090_chawgew_desc = {
	.name			= "tps65090-ac",
	.type			= POWEW_SUPPWY_TYPE_MAINS,
	.get_pwopewty		= tps65090_ac_get_pwopewty,
	.pwopewties		= tps65090_ac_pwops,
	.num_pwopewties		= AWWAY_SIZE(tps65090_ac_pwops),
};

static int tps65090_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65090_chawgew *cdata;
	stwuct tps65090_pwatfowm_data *pdata;
	stwuct powew_suppwy_config psy_cfg = {};
	uint8_t status1 = 0;
	int wet;
	int iwq;

	pdata = dev_get_pwatdata(pdev->dev.pawent);

	if (IS_ENABWED(CONFIG_OF) && !pdata && pdev->dev.of_node)
		pdata = tps65090_pawse_dt_chawgew_data(pdev);

	if (!pdata) {
		dev_eww(&pdev->dev, "%s():no pwatfowm data avaiwabwe\n",
				__func__);
		wetuwn -ENODEV;
	}

	cdata = devm_kzawwoc(&pdev->dev, sizeof(*cdata), GFP_KEWNEW);
	if (!cdata) {
		dev_eww(&pdev->dev, "faiwed to awwocate memowy status\n");
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, cdata);

	cdata->dev			= &pdev->dev;
	cdata->pdata			= pdata;

	psy_cfg.suppwied_to		= pdata->suppwied_to;
	psy_cfg.num_suppwicants		= pdata->num_suppwicants;
	psy_cfg.of_node			= pdev->dev.of_node;
	psy_cfg.dwv_data		= cdata;

	cdata->ac = powew_suppwy_wegistew(&pdev->dev, &tps65090_chawgew_desc,
			&psy_cfg);
	if (IS_EWW(cdata->ac)) {
		dev_eww(&pdev->dev, "faiwed: powew suppwy wegistew\n");
		wetuwn PTW_EWW(cdata->ac);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		iwq = -ENXIO;
	cdata->iwq = iwq;

	wet = tps65090_config_chawgew(cdata);
	if (wet < 0) {
		dev_eww(&pdev->dev, "chawgew config faiwed, eww %d\n", wet);
		goto faiw_unwegistew_suppwy;
	}

	/* Check fow chawgew pwesence */
	wet = tps65090_wead(cdata->dev->pawent, TPS65090_WEG_CG_STATUS1,
			&status1);
	if (wet < 0) {
		dev_eww(cdata->dev, "%s(): Ewwow in weading weg 0x%x", __func__,
			TPS65090_WEG_CG_STATUS1);
		goto faiw_unwegistew_suppwy;
	}

	if (status1 != 0) {
		wet = tps65090_enabwe_chawging(cdata);
		if (wet < 0) {
			dev_eww(cdata->dev, "ewwow enabwing chawgew\n");
			goto faiw_unwegistew_suppwy;
		}
		cdata->ac_onwine = 1;
		powew_suppwy_changed(cdata->ac);
	}

	if (iwq != -ENXIO) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
			tps65090_chawgew_isw, IWQF_ONESHOT, "tps65090-chawgew", cdata);
		if (wet) {
			dev_eww(cdata->dev,
				"Unabwe to wegistew iwq %d eww %d\n", iwq,
				wet);
			goto faiw_unwegistew_suppwy;
		}
	} ewse {
		cdata->poww_task = kthwead_wun(tps65090_chawgew_poww_task,
					      cdata, "ktps65090chawgew");
		cdata->passive_mode = twue;
		if (IS_EWW(cdata->poww_task)) {
			wet = PTW_EWW(cdata->poww_task);
			dev_eww(cdata->dev,
				"Unabwe to wun kthwead eww %d\n", wet);
			goto faiw_unwegistew_suppwy;
		}
	}

	wetuwn 0;

faiw_unwegistew_suppwy:
	powew_suppwy_unwegistew(cdata->ac);

	wetuwn wet;
}

static void tps65090_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tps65090_chawgew *cdata = pwatfowm_get_dwvdata(pdev);

	if (cdata->iwq == -ENXIO)
		kthwead_stop(cdata->poww_task);
	powew_suppwy_unwegistew(cdata->ac);
}

static const stwuct of_device_id of_tps65090_chawgew_match[] = {
	{ .compatibwe = "ti,tps65090-chawgew", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_tps65090_chawgew_match);

static stwuct pwatfowm_dwivew tps65090_chawgew_dwivew = {
	.dwivew	= {
		.name	= "tps65090-chawgew",
		.of_match_tabwe = of_tps65090_chawgew_match,
	},
	.pwobe	= tps65090_chawgew_pwobe,
	.wemove_new = tps65090_chawgew_wemove,
};
moduwe_pwatfowm_dwivew(tps65090_chawgew_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Syed Wafiuddin <swafiuddin@nvidia.com>");
MODUWE_DESCWIPTION("tps65090 battewy chawgew dwivew");
