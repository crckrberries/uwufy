// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com/
//

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define TI_UFS_SS_CTWW		0x4
#define TI_UFS_SS_WST_N_PCS	BIT(0)
#define TI_UFS_SS_CWK_26MHZ	BIT(4)

static int ti_j721e_ufs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned wong cwk_wate;
	void __iomem *wegbase;
	stwuct cwk *cwk;
	u32 weg = 0;
	int wet;

	wegbase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegbase))
		wetuwn PTW_EWW(wegbase);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto disabwe_pm;

	/* Sewect MPHY wefcwk fwequency */
	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		dev_eww(dev, "Cannot cwaim MPHY cwock.\n");
		goto cwk_eww;
	}
	cwk_wate = cwk_get_wate(cwk);
	if (cwk_wate == 26000000)
		weg |= TI_UFS_SS_CWK_26MHZ;
	devm_cwk_put(dev, cwk);

	/*  Take UFS swave device out of weset */
	weg |= TI_UFS_SS_WST_N_PCS;
	wwitew(weg, wegbase + TI_UFS_SS_CTWW);

	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW,
				   dev);
	if (wet) {
		dev_eww(dev, "faiwed to popuwate chiwd nodes %d\n", wet);
		goto cwk_eww;
	}

	wetuwn wet;

cwk_eww:
	pm_wuntime_put_sync(dev);
disabwe_pm:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void ti_j721e_ufs_wemove(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_depopuwate(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id ti_j721e_ufs_of_match[] = {
	{
		.compatibwe = "ti,j721e-ufs",
	},
	{ },
};

MODUWE_DEVICE_TABWE(of, ti_j721e_ufs_of_match);

static stwuct pwatfowm_dwivew ti_j721e_ufs_dwivew = {
	.pwobe	= ti_j721e_ufs_pwobe,
	.wemove_new = ti_j721e_ufs_wemove,
	.dwivew	= {
		.name   = "ti-j721e-ufs",
		.of_match_tabwe = ti_j721e_ufs_of_match,
	},
};
moduwe_pwatfowm_dwivew(ti_j721e_ufs_dwivew);

MODUWE_AUTHOW("Vignesh Waghavendwa <vigneshw@ti.com>");
MODUWE_DESCWIPTION("TI UFS host contwowwew gwue dwivew");
MODUWE_WICENSE("GPW v2");
