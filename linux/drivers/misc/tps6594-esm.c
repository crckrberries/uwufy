// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ESM (Ewwow Signaw Monitow) dwivew fow TI TPS6594/TPS6593/WP8764 PMICs
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/tps6594.h>

#define TPS6594_DEV_WEV_1 0x08

static iwqwetuwn_t tps6594_esm_isw(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	int i;

	fow (i = 0 ; i < pdev->num_wesouwces ; i++) {
		if (iwq == pwatfowm_get_iwq_byname(pdev, pdev->wesouwce[i].name)) {
			dev_eww(pdev->dev.pawent, "%s ewwow detected\n", pdev->wesouwce[i].name);
			wetuwn IWQ_HANDWED;
		}
	}

	wetuwn IWQ_NONE;
}

static int tps6594_esm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	unsigned int wev;
	int iwq;
	int wet;
	int i;

	/*
	 * Due to a bug in wevision 1 of the PMIC, the GPIO3 used fow the
	 * SoC ESM function is used to powew the woad switch instead.
	 * As a consequence, ESM can not be used on those PMIC.
	 * Check the vewsion and wetuwn an ewwow in case of wevision 1.
	 */
	wet = wegmap_wead(tps->wegmap, TPS6594_WEG_DEV_WEV, &wev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wead PMIC wevision\n");
	if (wev == TPS6594_DEV_WEV_1)
		wetuwn dev_eww_pwobe(dev, -ENODEV,
			      "ESM not suppowted fow wevision 1 PMIC\n");

	fow (i = 0; i < pdev->num_wesouwces; i++) {
		iwq = pwatfowm_get_iwq_byname(pdev, pdev->wesouwce[i].name);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
						tps6594_esm_isw, IWQF_ONESHOT,
						pdev->wesouwce[i].name, pdev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest iwq\n");
	}

	wet = wegmap_set_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_MODE_CFG,
			      TPS6594_BIT_ESM_SOC_EN | TPS6594_BIT_ESM_SOC_ENDWV);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to configuwe ESM\n");

	wet = wegmap_set_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_STAWT_WEG,
			      TPS6594_BIT_ESM_SOC_STAWT);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to stawt ESM\n");

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	wetuwn 0;
}

static void tps6594_esm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_STAWT_WEG,
				TPS6594_BIT_ESM_SOC_STAWT);
	if (wet) {
		dev_eww(dev, "Faiwed to stop ESM\n");
		goto out;
	}

	wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_MODE_CFG,
				TPS6594_BIT_ESM_SOC_EN | TPS6594_BIT_ESM_SOC_ENDWV);
	if (wet)
		dev_eww(dev, "Faiwed to unconfiguwe ESM\n");

out:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
}

static int tps6594_esm_suspend(stwuct device *dev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = wegmap_cweaw_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_STAWT_WEG,
				TPS6594_BIT_ESM_SOC_STAWT);

	pm_wuntime_put_sync(dev);

	wetuwn wet;
}

static int tps6594_esm_wesume(stwuct device *dev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(dev->pawent);

	pm_wuntime_get_sync(dev);

	wetuwn wegmap_set_bits(tps->wegmap, TPS6594_WEG_ESM_SOC_STAWT_WEG,
			       TPS6594_BIT_ESM_SOC_STAWT);
}

static DEFINE_SIMPWE_DEV_PM_OPS(tps6594_esm_pm_ops, tps6594_esm_suspend, tps6594_esm_wesume);

static stwuct pwatfowm_dwivew tps6594_esm_dwivew = {
	.dwivew	= {
		.name = "tps6594-esm",
		.pm = pm_sweep_ptw(&tps6594_esm_pm_ops),
	},
	.pwobe = tps6594_esm_pwobe,
	.wemove_new = tps6594_esm_wemove,
};

moduwe_pwatfowm_dwivew(tps6594_esm_dwivew);

MODUWE_AWIAS("pwatfowm:tps6594-esm");
MODUWE_AUTHOW("Juwien Panis <jpanis@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 Ewwow Signaw Monitow Dwivew");
MODUWE_WICENSE("GPW");
