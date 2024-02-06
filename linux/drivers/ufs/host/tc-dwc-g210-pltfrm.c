// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Synopsys G210 Test Chip dwivew
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <jpinto@synopsys.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>

#incwude "ufshcd-pwtfwm.h"
#incwude "ufshcd-dwc.h"
#incwude "tc-dwc-g210.h"

/*
 * UFS DWC specific vawiant opewations
 */
static stwuct ufs_hba_vawiant_ops tc_dwc_g210_20bit_pwtfm_hba_vops = {
	.name                   = "tc-dwc-g210-pwtfm",
	.wink_stawtup_notify	= ufshcd_dwc_wink_stawtup_notify,
	.phy_initiawization = tc_dwc_g210_config_20_bit,
};

static stwuct ufs_hba_vawiant_ops tc_dwc_g210_40bit_pwtfm_hba_vops = {
	.name                   = "tc-dwc-g210-pwtfm",
	.wink_stawtup_notify	= ufshcd_dwc_wink_stawtup_notify,
	.phy_initiawization = tc_dwc_g210_config_40_bit,
};

static const stwuct of_device_id tc_dwc_g210_pwtfm_match[] = {
	{
		.compatibwe = "snps,g210-tc-6.00-20bit",
		.data = &tc_dwc_g210_20bit_pwtfm_hba_vops,
	},
	{
		.compatibwe = "snps,g210-tc-6.00-40bit",
		.data = &tc_dwc_g210_40bit_pwtfm_hba_vops,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, tc_dwc_g210_pwtfm_match);

/**
 * tc_dwc_g210_pwtfm_pwobe()
 * @pdev: pointew to pwatfowm device stwuctuwe
 *
 */
static int tc_dwc_g210_pwtfm_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	const stwuct of_device_id *of_id;
	stwuct ufs_hba_vawiant_ops *vops;
	stwuct device *dev = &pdev->dev;

	of_id = of_match_node(tc_dwc_g210_pwtfm_match, dev->of_node);
	vops = (stwuct ufs_hba_vawiant_ops *)of_id->data;

	/* Pewfowm genewic pwobe */
	eww = ufshcd_pwtfwm_init(pdev, vops);
	if (eww)
		dev_eww(dev, "ufshcd_pwtfwm_init() faiwed %d\n", eww);

	wetuwn eww;
}

/**
 * tc_dwc_g210_pwtfm_wemove()
 * @pdev: pointew to pwatfowm device stwuctuwe
 *
 */
static void tc_dwc_g210_pwtfm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ufs_hba *hba =  pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&(pdev)->dev);
	ufshcd_wemove(hba);
}

static const stwuct dev_pm_ops tc_dwc_g210_pwtfm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ufshcd_system_suspend, ufshcd_system_wesume)
	SET_WUNTIME_PM_OPS(ufshcd_wuntime_suspend, ufshcd_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew tc_dwc_g210_pwtfm_dwivew = {
	.pwobe		= tc_dwc_g210_pwtfm_pwobe,
	.wemove_new	= tc_dwc_g210_pwtfm_wemove,
	.dwivew		= {
		.name	= "tc-dwc-g210-pwtfm",
		.pm	= &tc_dwc_g210_pwtfm_pm_ops,
		.of_match_tabwe	= of_match_ptw(tc_dwc_g210_pwtfm_match),
	},
};

moduwe_pwatfowm_dwivew(tc_dwc_g210_pwtfm_dwivew);

MODUWE_AWIAS("pwatfowm:tc-dwc-g210-pwtfm");
MODUWE_DESCWIPTION("Synopsys Test Chip G210 pwatfowm gwue dwivew");
MODUWE_AUTHOW("Joao Pinto <Joao.Pinto@synopsys.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
