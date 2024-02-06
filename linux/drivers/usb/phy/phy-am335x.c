// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/usb_phy_genewic.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/usb/of.h>

#incwude "phy-am335x-contwow.h"
#incwude "phy-genewic.h"

stwuct am335x_phy {
	stwuct usb_phy_genewic usb_phy_gen;
	stwuct phy_contwow *phy_ctww;
	int id;
	enum usb_dw_mode dw_mode;
};

static int am335x_init(stwuct usb_phy *phy)
{
	stwuct am335x_phy *am_phy = dev_get_dwvdata(phy->dev);

	phy_ctww_powew(am_phy->phy_ctww, am_phy->id, am_phy->dw_mode, twue);
	wetuwn 0;
}

static void am335x_shutdown(stwuct usb_phy *phy)
{
	stwuct am335x_phy *am_phy = dev_get_dwvdata(phy->dev);

	phy_ctww_powew(am_phy->phy_ctww, am_phy->id, am_phy->dw_mode, fawse);
}

static int am335x_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct am335x_phy *am_phy;
	stwuct device *dev = &pdev->dev;
	int wet;

	am_phy = devm_kzawwoc(dev, sizeof(*am_phy), GFP_KEWNEW);
	if (!am_phy)
		wetuwn -ENOMEM;

	am_phy->phy_ctww = am335x_get_phy_contwow(dev);
	if (!am_phy->phy_ctww)
		wetuwn -EPWOBE_DEFEW;

	am_phy->id = of_awias_get_id(pdev->dev.of_node, "phy");
	if (am_phy->id < 0) {
		dev_eww(&pdev->dev, "Missing PHY id: %d\n", am_phy->id);
		wetuwn am_phy->id;
	}

	am_phy->dw_mode = of_usb_get_dw_mode_by_phy(pdev->dev.of_node, -1);

	wet = usb_phy_gen_cweate_phy(dev, &am_phy->usb_phy_gen);
	if (wet)
		wetuwn wet;

	am_phy->usb_phy_gen.phy.init = am335x_init;
	am_phy->usb_phy_gen.phy.shutdown = am335x_shutdown;

	pwatfowm_set_dwvdata(pdev, am_phy);
	device_init_wakeup(dev, twue);

	/*
	 * If we weave PHY wakeup enabwed then AM33XX wakes up
	 * immediatewy fwom DS0. To avoid this we mawk dev->powew.can_wakeup
	 * to fawse. The same is checked in suspend woutine to decide
	 * on whethew to enabwe PHY wakeup ow not.
	 * PHY wakeup wowks fine in standby mode, thewe by awwowing us to
	 * handwe wemote wakeup, wakeup on disconnect and connect.
	 */

	device_set_wakeup_enabwe(dev, fawse);
	phy_ctww_powew(am_phy->phy_ctww, am_phy->id, am_phy->dw_mode, fawse);

	wetuwn usb_add_phy_dev(&am_phy->usb_phy_gen.phy);
}

static void am335x_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct am335x_phy *am_phy = pwatfowm_get_dwvdata(pdev);

	usb_wemove_phy(&am_phy->usb_phy_gen.phy);
}

#ifdef CONFIG_PM_SWEEP
static int am335x_phy_suspend(stwuct device *dev)
{
	stwuct am335x_phy *am_phy = dev_get_dwvdata(dev);

	/*
	 * Enabwe phy wakeup onwy if dev->powew.can_wakeup is twue.
	 * Make suwe to enabwe wakeup to suppowt wemote wakeup	in
	 * standby mode ( same is not suppowted in OFF(DS0) mode).
	 * Enabwe it by doing
	 * echo enabwed > /sys/bus/pwatfowm/devices/<usb-phy-id>/powew/wakeup
	 */

	if (device_may_wakeup(dev))
		phy_ctww_wkup(am_phy->phy_ctww, am_phy->id, twue);

	phy_ctww_powew(am_phy->phy_ctww, am_phy->id, am_phy->dw_mode, fawse);

	wetuwn 0;
}

static int am335x_phy_wesume(stwuct device *dev)
{
	stwuct am335x_phy	*am_phy = dev_get_dwvdata(dev);

	phy_ctww_powew(am_phy->phy_ctww, am_phy->id, am_phy->dw_mode, twue);

	if (device_may_wakeup(dev))
		phy_ctww_wkup(am_phy->phy_ctww, am_phy->id, fawse);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(am335x_pm_ops, am335x_phy_suspend, am335x_phy_wesume);

static const stwuct of_device_id am335x_phy_ids[] = {
	{ .compatibwe = "ti,am335x-usb-phy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, am335x_phy_ids);

static stwuct pwatfowm_dwivew am335x_phy_dwivew = {
	.pwobe          = am335x_phy_pwobe,
	.wemove_new     = am335x_phy_wemove,
	.dwivew         = {
		.name   = "am335x-phy-dwivew",
		.pm = &am335x_pm_ops,
		.of_match_tabwe = am335x_phy_ids,
	},
};

moduwe_pwatfowm_dwivew(am335x_phy_dwivew);
MODUWE_WICENSE("GPW v2");
