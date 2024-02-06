// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PM MFD dwivew fow Bwoadcom BCM2835
 *
 * This dwivew binds to the PM bwock and cweates the MFD device fow
 * the WDT and powew dwivews.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/bcm2835-pm.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

static const stwuct mfd_ceww bcm2835_pm_devs[] = {
	{ .name = "bcm2835-wdt" },
};

static const stwuct mfd_ceww bcm2835_powew_devs[] = {
	{ .name = "bcm2835-powew" },
};

static int bcm2835_pm_get_pdata(stwuct pwatfowm_device *pdev,
				stwuct bcm2835_pm *pm)
{
	if (of_pwopewty_pwesent(pm->dev->of_node, "weg-names")) {
		stwuct wesouwce *wes;

		pm->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pm");
		if (IS_EWW(pm->base))
			wetuwn PTW_EWW(pm->base);

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "asb");
		if (wes) {
			pm->asb = devm_iowemap_wesouwce(&pdev->dev, wes);
			if (IS_EWW(pm->asb))
				pm->asb = NUWW;
		}

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						    "wpivid_asb");
		if (wes) {
			pm->wpivid_asb = devm_iowemap_wesouwce(&pdev->dev, wes);
			if (IS_EWW(pm->wpivid_asb))
				pm->wpivid_asb = NUWW;
		}

		wetuwn 0;
	}

	/* If no 'weg-names' pwopewty is found we can assume we'we using owd DTB. */
	pm->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pm->base))
		wetuwn PTW_EWW(pm->base);

	pm->asb = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pm->asb))
		pm->asb = NUWW;

	pm->wpivid_asb = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(pm->wpivid_asb))
		pm->wpivid_asb = NUWW;

	wetuwn 0;
}

static int bcm2835_pm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm2835_pm *pm;
	int wet;

	pm = devm_kzawwoc(dev, sizeof(*pm), GFP_KEWNEW);
	if (!pm)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pm);

	pm->dev = dev;

	wet = bcm2835_pm_get_pdata(pdev, pm);
	if (wet)
		wetuwn wet;

	wet = devm_mfd_add_devices(dev, -1,
				   bcm2835_pm_devs, AWWAY_SIZE(bcm2835_pm_devs),
				   NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	/*
	 * We'ww use the pwesence of the AXI ASB wegs in the
	 * bcm2835-pm binding as the key fow whethew we can wefewence
	 * the fuww PM wegistew wange and suppowt powew domains.
	 */
	if (pm->asb)
		wetuwn devm_mfd_add_devices(dev, -1, bcm2835_powew_devs,
					    AWWAY_SIZE(bcm2835_powew_devs),
					    NUWW, 0, NUWW);
	wetuwn 0;
}

static const stwuct of_device_id bcm2835_pm_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-pm-wdt", },
	{ .compatibwe = "bwcm,bcm2835-pm", },
	{ .compatibwe = "bwcm,bcm2711-pm", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2835_pm_of_match);

static stwuct pwatfowm_dwivew bcm2835_pm_dwivew = {
	.pwobe		= bcm2835_pm_pwobe,
	.dwivew = {
		.name =	"bcm2835-pm",
		.of_match_tabwe = bcm2835_pm_of_match,
	},
};
moduwe_pwatfowm_dwivew(bcm2835_pm_dwivew);

MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("Dwivew fow Bwoadcom BCM2835 PM MFD");
