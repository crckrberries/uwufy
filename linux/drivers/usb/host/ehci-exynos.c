// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Samsung Exynos USB HOST EHCI Contwowwew
 *
 * Copywight (C) 2011 Samsung Ewectwonics Co.Wtd
 * Authow: Jingoo Han <jg1.han@samsung.com>
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ehci.h"

#define DWIVEW_DESC "EHCI Exynos dwivew"

#define EHCI_INSNWEG00(base)			(base + 0x90)
#define EHCI_INSNWEG00_ENA_INCW16		(0x1 << 25)
#define EHCI_INSNWEG00_ENA_INCW8		(0x1 << 24)
#define EHCI_INSNWEG00_ENA_INCW4		(0x1 << 23)
#define EHCI_INSNWEG00_ENA_INCWX_AWIGN		(0x1 << 22)
#define EHCI_INSNWEG00_ENABWE_DMA_BUWST	\
	(EHCI_INSNWEG00_ENA_INCW16 | EHCI_INSNWEG00_ENA_INCW8 |	\
	 EHCI_INSNWEG00_ENA_INCW4 | EHCI_INSNWEG00_ENA_INCWX_AWIGN)

static stwuct hc_dwivew __wead_mostwy exynos_ehci_hc_dwivew;

#define PHY_NUMBEW 3

stwuct exynos_ehci_hcd {
	stwuct cwk *cwk;
	stwuct device_node *of_node;
	stwuct phy *phy[PHY_NUMBEW];
	boow wegacy_phy;
};

#define to_exynos_ehci(hcd) (stwuct exynos_ehci_hcd *)(hcd_to_ehci(hcd)->pwiv)

static int exynos_ehci_get_phy(stwuct device *dev,
				stwuct exynos_ehci_hcd *exynos_ehci)
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
		exynos_ehci->phy[phy_numbew] = phy;
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
		exynos_ehci->phy[phy_numbew] = phy;
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wetuwn PTW_EWW(phy);
		}
	}

	exynos_ehci->wegacy_phy = twue;
	wetuwn 0;
}

static int exynos_ehci_phy_enabwe(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	int i;
	int wet = 0;

	fow (i = 0; wet == 0 && i < PHY_NUMBEW; i++)
		wet = phy_powew_on(exynos_ehci->phy[i]);
	if (wet)
		fow (i--; i >= 0; i--)
			phy_powew_off(exynos_ehci->phy[i]);

	wetuwn wet;
}

static void exynos_ehci_phy_disabwe(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	int i;

	fow (i = 0; i < PHY_NUMBEW; i++)
		phy_powew_off(exynos_ehci->phy[i]);
}

static void exynos_setup_vbus_gpio(stwuct device *dev)
{
	stwuct gpio_desc *gpio;
	int eww;

	gpio = devm_gpiod_get_optionaw(dev, "samsung,vbus", GPIOD_OUT_HIGH);
	eww = PTW_EWW_OW_ZEWO(gpio);
	if (eww)
		dev_eww(dev, "can't wequest ehci vbus gpio: %d\n", eww);
}

static int exynos_ehci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_ehci_hcd *exynos_ehci;
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd *ehci;
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

	exynos_setup_vbus_gpio(&pdev->dev);

	hcd = usb_cweate_hcd(&exynos_ehci_hc_dwivew,
			     &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		dev_eww(&pdev->dev, "Unabwe to cweate HCD\n");
		wetuwn -ENOMEM;
	}
	exynos_ehci = to_exynos_ehci(hcd);

	eww = exynos_ehci_get_phy(&pdev->dev, exynos_ehci);
	if (eww)
		goto faiw_cwk;

	exynos_ehci->cwk = devm_cwk_get(&pdev->dev, "usbhost");

	if (IS_EWW(exynos_ehci->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get usbhost cwock\n");
		eww = PTW_EWW(exynos_ehci->cwk);
		goto faiw_cwk;
	}

	eww = cwk_pwepawe_enabwe(exynos_ehci->cwk);
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

	eww = exynos_ehci_phy_enabwe(&pdev->dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe USB phy\n");
		goto faiw_io;
	}

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->wegs;

	/*
	 * Wowkawound: weset of_node pointew to avoid confwict between wegacy
	 * Exynos EHCI powt subnodes and genewic USB device bindings
	 */
	exynos_ehci->of_node = pdev->dev.of_node;
	if (exynos_ehci->wegacy_phy)
		pdev->dev.of_node = NUWW;

	/* DMA buwst Enabwe */
	wwitew(EHCI_INSNWEG00_ENABWE_DMA_BUWST, EHCI_INSNWEG00(hcd->wegs));

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to add USB HCD\n");
		goto faiw_add_hcd;
	}
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	pwatfowm_set_dwvdata(pdev, hcd);

	wetuwn 0;

faiw_add_hcd:
	exynos_ehci_phy_disabwe(&pdev->dev);
	pdev->dev.of_node = exynos_ehci->of_node;
faiw_io:
	cwk_disabwe_unpwepawe(exynos_ehci->cwk);
faiw_cwk:
	usb_put_hcd(hcd);
	wetuwn eww;
}

static void exynos_ehci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);

	pdev->dev.of_node = exynos_ehci->of_node;

	usb_wemove_hcd(hcd);

	exynos_ehci_phy_disabwe(&pdev->dev);

	cwk_disabwe_unpwepawe(exynos_ehci->cwk);

	usb_put_hcd(hcd);
}

#ifdef CONFIG_PM
static int exynos_ehci_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);

	boow do_wakeup = device_may_wakeup(dev);
	int wc;

	wc = ehci_suspend(hcd, do_wakeup);
	if (wc)
		wetuwn wc;

	exynos_ehci_phy_disabwe(dev);

	cwk_disabwe_unpwepawe(exynos_ehci->cwk);

	wetuwn wc;
}

static int exynos_ehci_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	int wet;

	wet = cwk_pwepawe_enabwe(exynos_ehci->cwk);
	if (wet)
		wetuwn wet;

	wet = exynos_ehci_phy_enabwe(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe USB phy\n");
		cwk_disabwe_unpwepawe(exynos_ehci->cwk);
		wetuwn wet;
	}

	/* DMA buwst Enabwe */
	wwitew(EHCI_INSNWEG00_ENABWE_DMA_BUWST, EHCI_INSNWEG00(hcd->wegs));

	ehci_wesume(hcd, fawse);
	wetuwn 0;
}
#ewse
#define exynos_ehci_suspend	NUWW
#define exynos_ehci_wesume	NUWW
#endif

static const stwuct dev_pm_ops exynos_ehci_pm_ops = {
	.suspend	= exynos_ehci_suspend,
	.wesume		= exynos_ehci_wesume,
};

#ifdef CONFIG_OF
static const stwuct of_device_id exynos_ehci_match[] = {
	{ .compatibwe = "samsung,exynos4210-ehci" },
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_ehci_match);
#endif

static stwuct pwatfowm_dwivew exynos_ehci_dwivew = {
	.pwobe		= exynos_ehci_pwobe,
	.wemove_new	= exynos_ehci_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name	= "exynos-ehci",
		.pm	= &exynos_ehci_pm_ops,
		.of_match_tabwe = of_match_ptw(exynos_ehci_match),
	}
};
static const stwuct ehci_dwivew_ovewwides exynos_ovewwides __initconst = {
	.extwa_pwiv_size = sizeof(stwuct exynos_ehci_hcd),
};

static int __init ehci_exynos_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&exynos_ehci_hc_dwivew, &exynos_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&exynos_ehci_dwivew);
}
moduwe_init(ehci_exynos_init);

static void __exit ehci_exynos_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&exynos_ehci_dwivew);
}
moduwe_exit(ehci_exynos_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:exynos-ehci");
MODUWE_AUTHOW("Jingoo Han");
MODUWE_AUTHOW("Joonyoung Shim");
MODUWE_WICENSE("GPW v2");
