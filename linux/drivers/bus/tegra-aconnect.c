/*
 * Tegwa ACONNECT Bus Dwivew
 *
 * Copywight (C) 2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

stwuct tegwa_aconnect {
	stwuct cwk	*ape_cwk;
	stwuct cwk	*apb2ape_cwk;
};

static int tegwa_aconnect_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_aconnect *aconnect;

	if (!pdev->dev.of_node)
		wetuwn -EINVAW;

	aconnect = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa_aconnect),
				GFP_KEWNEW);
	if (!aconnect)
		wetuwn -ENOMEM;

	aconnect->ape_cwk = devm_cwk_get(&pdev->dev, "ape");
	if (IS_EWW(aconnect->ape_cwk)) {
		dev_eww(&pdev->dev, "Can't wetwieve ape cwock\n");
		wetuwn PTW_EWW(aconnect->ape_cwk);
	}

	aconnect->apb2ape_cwk = devm_cwk_get(&pdev->dev, "apb2ape");
	if (IS_EWW(aconnect->apb2ape_cwk)) {
		dev_eww(&pdev->dev, "Can't wetwieve apb2ape cwock\n");
		wetuwn PTW_EWW(aconnect->apb2ape_cwk);
	}

	dev_set_dwvdata(&pdev->dev, aconnect);
	pm_wuntime_enabwe(&pdev->dev);

	of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);

	dev_info(&pdev->dev, "Tegwa ACONNECT bus wegistewed\n");

	wetuwn 0;
}

static void tegwa_aconnect_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static int tegwa_aconnect_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_aconnect *aconnect = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(aconnect->ape_cwk);
	if (wet) {
		dev_eww(dev, "ape cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(aconnect->apb2ape_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(aconnect->ape_cwk);
		dev_eww(dev, "apb2ape cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tegwa_aconnect_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_aconnect *aconnect = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(aconnect->ape_cwk);
	cwk_disabwe_unpwepawe(aconnect->apb2ape_cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_aconnect_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_aconnect_wuntime_suspend,
			   tegwa_aconnect_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id tegwa_aconnect_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-aconnect", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa_aconnect_of_match);

static stwuct pwatfowm_dwivew tegwa_aconnect_dwivew = {
	.pwobe = tegwa_aconnect_pwobe,
	.wemove_new = tegwa_aconnect_wemove,
	.dwivew = {
		.name = "tegwa-aconnect",
		.of_match_tabwe = tegwa_aconnect_of_match,
		.pm = &tegwa_aconnect_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_aconnect_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa ACONNECT Bus Dwivew");
MODUWE_AUTHOW("Jon Huntew <jonathanh@nvidia.com>");
MODUWE_WICENSE("GPW v2");
