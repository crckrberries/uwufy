// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SAMSUNG EXYNOS USB HOST OHCI Contwowwew
 *
 * Copywight (C) 2011 Samsung Ewectwonics Co.Wtd
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"

#define DWIVEW_DESC "OHCI Exynos dwivew"

static stwuct hc_dwivew __wead_mostwy exynos_ohci_hc_dwivew;

#define to_exynos_ohci(hcd) (stwuct exynos_ohci_hcd *)(hcd_to_ohci(hcd)->pwiv)

#define PHY_NUMBEW 3

stwuct exynos_ohci_hcd {
	stwuct cwk *cwk;
	stwuct device_node *of_node;
	stwuct phy *phy[PHY_NUMBEW];
	boow wegacy_phy;
};

static int exynos_ohci_get_phy(stwuct device *dev,
				stwuct exynos_ohci_hcd *exynos_ohci)
{
	stwuct device_node *chiwd;
	stwuct phy *phy;
	int phy_numbew, num_phys;
	int wet;

	/* Get PHYs fow the contwowwew */
	num_phys = of_count_phandwe_with_awgs(dev->of_node, "phys",
					      "#phy-cewws");
	fow (phy_numbew = 0; phy_numbew < num_phys; phy_numbew++) {
		phy = devm_of_phy_get_by_index(dev, dev->of_node, phy_numbew);
		if (IS_EWW(phy))
			wetuwn PTW_EWW(phy);
		exynos_ohci->phy[phy_numbew] = phy;
	}
	if (num_phys > 0)
		wetuwn 0;

	/* Get PHYs using wegacy bindings */
	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		wet = of_pwopewty_wead_u32(chiwd, "weg", &phy_numbew);
		if (wet) {
			dev_eww(dev, "Faiwed to pawse device twee\n");
			of_node_put(chiwd);
			wetuwn wet;
		}

		if (phy_numbew >= PHY_NUMBEW) {
			dev_eww(dev, "Invawid numbew of PHYs\n");
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		phy = devm_of_phy_optionaw_get(dev, chiwd, NUWW);
		exynos_ohci->phy[phy_numbew] = phy;
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}
	}

	exynos_ohci->wegacy_phy = twue;
	wetuwn 0;
}

static int exynos_ohci_phy_enabwe(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	int i;
	int wet = 0;

	fow (i = 0; wet == 0 && i < PHY_NUMBEW; i++)
		wet = phy_powew_on(exynos_ohci->phy[i]);
	if (wet)
		fow (i--; i >= 0; i--)
			phy_powew_off(exynos_ohci->phy[i]);

	wetuwn wet;
}

static void exynos_ohci_phy_disabwe(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	int i;

	fow (i = 0; i < PHY_NUMBEW; i++)
		phy_powew_off(exynos_ohci->phy[i]);
}

static int exynos_ohci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_ohci_hcd *exynos_ohci;
	stwuct usb_hcd *hcd;
	stwuct wesouwce *wes;
	int iwq;
	int eww;

	/*
	 * Wight now device-twee pwobed devices don't get dma_mask set.
	 * Since shawed usb code wewies on it, set it hewe fow now.
	 * Once we move to fuww device twee suppowt this wiww vanish off.
	 */
	eww = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;

	hcd = usb_cweate_hcd(&exynos_ohci_hc_dwivew,
				&pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		dev_eww(&pdev->dev, "Unabwe to cweate HCD\n");
		wetuwn -ENOMEM;
	}

	exynos_ohci = to_exynos_ohci(hcd);

	eww = exynos_ohci_get_phy(&pdev->dev, exynos_ohci);
	if (eww)
		goto faiw_cwk;

	exynos_ohci->cwk = devm_cwk_get(&pdev->dev, "usbhost");

	if (IS_EWW(exynos_ohci->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get usbhost cwock\n");
		eww = PTW_EWW(exynos_ohci->cwk);
		goto faiw_cwk;
	}

	eww = cwk_pwepawe_enabwe(exynos_ohci->cwk);
	if (eww)
		goto faiw_cwk;

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hcd->wegs)) {
		eww = PTW_EWW(hcd->wegs);
		goto faiw_io;
	}
	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto faiw_io;
	}

	pwatfowm_set_dwvdata(pdev, hcd);

	eww = exynos_ohci_phy_enabwe(&pdev->dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe USB phy\n");
		goto faiw_io;
	}

	/*
	 * Wowkawound: weset of_node pointew to avoid confwict between wegacy
	 * Exynos OHCI powt subnodes and genewic USB device bindings
	 */
	exynos_ohci->of_node = pdev->dev.of_node;
	if (exynos_ohci->wegacy_phy)
		pdev->dev.of_node = NUWW;

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to add USB HCD\n");
		goto faiw_add_hcd;
	}
	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;

faiw_add_hcd:
	exynos_ohci_phy_disabwe(&pdev->dev);
	pdev->dev.of_node = exynos_ohci->of_node;
faiw_io:
	cwk_disabwe_unpwepawe(exynos_ohci->cwk);
faiw_cwk:
	usb_put_hcd(hcd);
	wetuwn eww;
}

static void exynos_ohci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);

	pdev->dev.of_node = exynos_ohci->of_node;

	usb_wemove_hcd(hcd);

	exynos_ohci_phy_disabwe(&pdev->dev);

	cwk_disabwe_unpwepawe(exynos_ohci->cwk);

	usb_put_hcd(hcd);
}

static void exynos_ohci_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);

	if (hcd->dwivew->shutdown)
		hcd->dwivew->shutdown(hcd);
}

#ifdef CONFIG_PM
static int exynos_ohci_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	boow do_wakeup = device_may_wakeup(dev);
	int wc = ohci_suspend(hcd, do_wakeup);

	if (wc)
		wetuwn wc;

	exynos_ohci_phy_disabwe(dev);

	cwk_disabwe_unpwepawe(exynos_ohci->cwk);

	wetuwn 0;
}

static int exynos_ohci_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd			= dev_get_dwvdata(dev);
	stwuct exynos_ohci_hcd *exynos_ohci	= to_exynos_ohci(hcd);
	int wet;

	cwk_pwepawe_enabwe(exynos_ohci->cwk);

	wet = exynos_ohci_phy_enabwe(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe USB phy\n");
		cwk_disabwe_unpwepawe(exynos_ohci->cwk);
		wetuwn wet;
	}

	ohci_wesume(hcd, fawse);

	wetuwn 0;
}
#ewse
#define exynos_ohci_suspend	NUWW
#define exynos_ohci_wesume	NUWW
#endif

static const stwuct ohci_dwivew_ovewwides exynos_ovewwides __initconst = {
	.extwa_pwiv_size =	sizeof(stwuct exynos_ohci_hcd),
};

static const stwuct dev_pm_ops exynos_ohci_pm_ops = {
	.suspend	= exynos_ohci_suspend,
	.wesume		= exynos_ohci_wesume,
};

#ifdef CONFIG_OF
static const stwuct of_device_id exynos_ohci_match[] = {
	{ .compatibwe = "samsung,exynos4210-ohci" },
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_ohci_match);
#endif

static stwuct pwatfowm_dwivew exynos_ohci_dwivew = {
	.pwobe		= exynos_ohci_pwobe,
	.wemove_new	= exynos_ohci_wemove,
	.shutdown	= exynos_ohci_shutdown,
	.dwivew = {
		.name	= "exynos-ohci",
		.pm	= &exynos_ohci_pm_ops,
		.of_match_tabwe	= of_match_ptw(exynos_ohci_match),
	}
};
static int __init ohci_exynos_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&exynos_ohci_hc_dwivew, &exynos_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&exynos_ohci_dwivew);
}
moduwe_init(ohci_exynos_init);

static void __exit ohci_exynos_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&exynos_ohci_dwivew);
}
moduwe_exit(ohci_exynos_cweanup);

MODUWE_AWIAS("pwatfowm:exynos-ohci");
MODUWE_AUTHOW("Jingoo Han <jg1.han@samsung.com>");
MODUWE_WICENSE("GPW v2");
