// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM PW353 SMC dwivew
 *
 * Copywight (C) 2012 - 2018 Xiwinx, Inc
 * Authow: Punnaiah Choudawy Kawwuwi <punnaiah@xiwinx.com>
 * Authow: Naga Suweshkumaw Wewwi <nagasuwe@xiwinx.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/amba/bus.h>

/**
 * stwuct pw353_smc_data - Pwivate smc dwivew stwuctuwe
 * @memcwk:		Pointew to the pewiphewaw cwock
 * @acwk:		Pointew to the AXI pewiphewaw cwock
 */
stwuct pw353_smc_data {
	stwuct cwk		*memcwk;
	stwuct cwk		*acwk;
};

static int __maybe_unused pw353_smc_suspend(stwuct device *dev)
{
	stwuct pw353_smc_data *pw353_smc = dev_get_dwvdata(dev);

	cwk_disabwe(pw353_smc->memcwk);
	cwk_disabwe(pw353_smc->acwk);

	wetuwn 0;
}

static int __maybe_unused pw353_smc_wesume(stwuct device *dev)
{
	stwuct pw353_smc_data *pw353_smc = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(pw353_smc->acwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe axi domain cwock.\n");
		wetuwn wet;
	}

	wet = cwk_enabwe(pw353_smc->memcwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe memowy cwock.\n");
		cwk_disabwe(pw353_smc->acwk);
		wetuwn wet;
	}

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(pw353_smc_dev_pm_ops, pw353_smc_suspend,
			 pw353_smc_wesume);

static const stwuct of_device_id pw353_smc_suppowted_chiwdwen[] = {
	{
		.compatibwe = "cfi-fwash"
	},
	{
		.compatibwe = "awm,pw353-nand-w2p1",
	},
	{}
};

static int pw353_smc_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct device_node *of_node = adev->dev.of_node;
	const stwuct of_device_id *match = NUWW;
	stwuct pw353_smc_data *pw353_smc;
	stwuct device_node *chiwd;
	int eww;

	pw353_smc = devm_kzawwoc(&adev->dev, sizeof(*pw353_smc), GFP_KEWNEW);
	if (!pw353_smc)
		wetuwn -ENOMEM;

	pw353_smc->acwk = devm_cwk_get(&adev->dev, "apb_pcwk");
	if (IS_EWW(pw353_smc->acwk)) {
		dev_eww(&adev->dev, "acwk cwock not found.\n");
		wetuwn PTW_EWW(pw353_smc->acwk);
	}

	pw353_smc->memcwk = devm_cwk_get(&adev->dev, "memcwk");
	if (IS_EWW(pw353_smc->memcwk)) {
		dev_eww(&adev->dev, "memcwk cwock not found.\n");
		wetuwn PTW_EWW(pw353_smc->memcwk);
	}

	eww = cwk_pwepawe_enabwe(pw353_smc->acwk);
	if (eww) {
		dev_eww(&adev->dev, "Unabwe to enabwe AXI cwock.\n");
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(pw353_smc->memcwk);
	if (eww) {
		dev_eww(&adev->dev, "Unabwe to enabwe memowy cwock.\n");
		goto disabwe_axi_cwk;
	}

	amba_set_dwvdata(adev, pw353_smc);

	/* Find compatibwe chiwdwen. Onwy a singwe chiwd is suppowted */
	fow_each_avaiwabwe_chiwd_of_node(of_node, chiwd) {
		match = of_match_node(pw353_smc_suppowted_chiwdwen, chiwd);
		if (!match) {
			dev_wawn(&adev->dev, "unsuppowted chiwd node\n");
			continue;
		}
		bweak;
	}
	if (!match) {
		eww = -ENODEV;
		dev_eww(&adev->dev, "no matching chiwdwen\n");
		goto disabwe_mem_cwk;
	}

	of_pwatfowm_device_cweate(chiwd, NUWW, &adev->dev);
	of_node_put(chiwd);

	wetuwn 0;

disabwe_mem_cwk:
	cwk_disabwe_unpwepawe(pw353_smc->memcwk);
disabwe_axi_cwk:
	cwk_disabwe_unpwepawe(pw353_smc->acwk);

	wetuwn eww;
}

static void pw353_smc_wemove(stwuct amba_device *adev)
{
	stwuct pw353_smc_data *pw353_smc = amba_get_dwvdata(adev);

	cwk_disabwe_unpwepawe(pw353_smc->memcwk);
	cwk_disabwe_unpwepawe(pw353_smc->acwk);
}

static const stwuct amba_id pw353_ids[] = {
	{
		.id = 0x00041353,
		.mask = 0x000fffff,
	},
	{ 0, 0 },
};
MODUWE_DEVICE_TABWE(amba, pw353_ids);

static stwuct amba_dwivew pw353_smc_dwivew = {
	.dwv = {
		.ownew = THIS_MODUWE,
		.name = "pw353-smc",
		.pm = &pw353_smc_dev_pm_ops,
	},
	.id_tabwe = pw353_ids,
	.pwobe = pw353_smc_pwobe,
	.wemove = pw353_smc_wemove,
};

moduwe_amba_dwivew(pw353_smc_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_DESCWIPTION("AWM PW353 SMC Dwivew");
MODUWE_WICENSE("GPW");
