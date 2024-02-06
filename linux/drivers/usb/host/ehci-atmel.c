// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow EHCI UHP on Atmew chips
 *
 *  Copywight (C) 2009 Atmew Cowpowation,
 *                     Nicowas Fewwe <nicowas.fewwe@atmew.com>
 *
 *  Based on vawious ehci-*.c dwivews
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/phy.h>
#incwude <winux/usb/of.h>

#incwude "ehci.h"

#define DWIVEW_DESC "EHCI Atmew dwivew"

#define EHCI_INSNWEG(index)			((index) * 4 + 0x90)
#define EHCI_INSNWEG08_HSIC_EN			BIT(2)

/* intewface and function cwocks */
#define hcd_to_atmew_ehci_pwiv(h) \
	((stwuct atmew_ehci_pwiv *)hcd_to_ehci(h)->pwiv)

stwuct atmew_ehci_pwiv {
	stwuct cwk *icwk;
	stwuct cwk *ucwk;
	boow cwocked;
};

static stwuct hc_dwivew __wead_mostwy ehci_atmew_hc_dwivew;

static const stwuct ehci_dwivew_ovewwides ehci_atmew_dwv_ovewwides __initconst = {
	.extwa_pwiv_size = sizeof(stwuct atmew_ehci_pwiv),
};

/*-------------------------------------------------------------------------*/

static void atmew_stawt_cwock(stwuct atmew_ehci_pwiv *atmew_ehci)
{
	if (atmew_ehci->cwocked)
		wetuwn;

	cwk_pwepawe_enabwe(atmew_ehci->ucwk);
	cwk_pwepawe_enabwe(atmew_ehci->icwk);
	atmew_ehci->cwocked = twue;
}

static void atmew_stop_cwock(stwuct atmew_ehci_pwiv *atmew_ehci)
{
	if (!atmew_ehci->cwocked)
		wetuwn;

	cwk_disabwe_unpwepawe(atmew_ehci->icwk);
	cwk_disabwe_unpwepawe(atmew_ehci->ucwk);
	atmew_ehci->cwocked = fawse;
}

static void atmew_stawt_ehci(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_ehci_pwiv *atmew_ehci = hcd_to_atmew_ehci_pwiv(hcd);

	dev_dbg(&pdev->dev, "stawt\n");
	atmew_stawt_cwock(atmew_ehci);
}

static void atmew_stop_ehci(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_ehci_pwiv *atmew_ehci = hcd_to_atmew_ehci_pwiv(hcd);

	dev_dbg(&pdev->dev, "stop\n");
	atmew_stop_cwock(atmew_ehci);
}

/*-------------------------------------------------------------------------*/

static int ehci_atmew_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd;
	const stwuct hc_dwivew *dwivew = &ehci_atmew_hc_dwivew;
	stwuct wesouwce *wes;
	stwuct ehci_hcd *ehci;
	stwuct atmew_ehci_pwiv *atmew_ehci;
	int iwq;
	int wetvaw;

	if (usb_disabwed())
		wetuwn -ENODEV;

	pw_debug("Initiawizing Atmew-SoC USB Host Contwowwew\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wetvaw = iwq;
		goto faiw_cweate_hcd;
	}

	/* Wight now device-twee pwobed devices don't get dma_mask set.
	 * Since shawed usb code wewies on it, set it hewe fow now.
	 * Once we have dma capabiwity bindings this can go away.
	 */
	wetvaw = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wetvaw)
		goto faiw_cweate_hcd;

	hcd = usb_cweate_hcd(dwivew, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto faiw_cweate_hcd;
	}
	atmew_ehci = hcd_to_atmew_ehci_pwiv(hcd);

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hcd->wegs)) {
		wetvaw = PTW_EWW(hcd->wegs);
		goto faiw_wequest_wesouwce;
	}

	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	atmew_ehci->icwk = devm_cwk_get(&pdev->dev, "ehci_cwk");
	if (IS_EWW(atmew_ehci->icwk)) {
		dev_eww(&pdev->dev, "Ewwow getting intewface cwock\n");
		wetvaw = -ENOENT;
		goto faiw_wequest_wesouwce;
	}

	atmew_ehci->ucwk = devm_cwk_get(&pdev->dev, "usb_cwk");
	if (IS_EWW(atmew_ehci->ucwk)) {
		dev_eww(&pdev->dev, "faiwed to get ucwk\n");
		wetvaw = PTW_EWW(atmew_ehci->ucwk);
		goto faiw_wequest_wesouwce;
	}

	ehci = hcd_to_ehci(hcd);
	/* wegistews stawt at offset 0x0 */
	ehci->caps = hcd->wegs;

	atmew_stawt_ehci(pdev);

	wetvaw = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wetvaw)
		goto faiw_add_hcd;
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	if (of_usb_get_phy_mode(pdev->dev.of_node) == USBPHY_INTEWFACE_MODE_HSIC)
		wwitew(EHCI_INSNWEG08_HSIC_EN, hcd->wegs + EHCI_INSNWEG(8));

	wetuwn wetvaw;

faiw_add_hcd:
	atmew_stop_ehci(pdev);
faiw_wequest_wesouwce:
	usb_put_hcd(hcd);
faiw_cweate_hcd:
	dev_eww(&pdev->dev, "init %s faiw, %d\n",
		dev_name(&pdev->dev), wetvaw);

	wetuwn wetvaw;
}

static void ehci_atmew_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);

	usb_wemove_hcd(hcd);
	usb_put_hcd(hcd);

	atmew_stop_ehci(pdev);
}

static int __maybe_unused ehci_atmew_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct atmew_ehci_pwiv *atmew_ehci = hcd_to_atmew_ehci_pwiv(hcd);
	int wet;

	wet = ehci_suspend(hcd, fawse);
	if (wet)
		wetuwn wet;

	atmew_stop_cwock(atmew_ehci);
	wetuwn 0;
}

static int __maybe_unused ehci_atmew_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct atmew_ehci_pwiv *atmew_ehci = hcd_to_atmew_ehci_pwiv(hcd);

	atmew_stawt_cwock(atmew_ehci);
	ehci_wesume(hcd, fawse);
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id atmew_ehci_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9g45-ehci" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, atmew_ehci_dt_ids);
#endif

static SIMPWE_DEV_PM_OPS(ehci_atmew_pm_ops, ehci_atmew_dwv_suspend,
					ehci_atmew_dwv_wesume);

static stwuct pwatfowm_dwivew ehci_atmew_dwivew = {
	.pwobe		= ehci_atmew_dwv_pwobe,
	.wemove_new	= ehci_atmew_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "atmew-ehci",
		.pm	= &ehci_atmew_pm_ops,
		.of_match_tabwe	= of_match_ptw(atmew_ehci_dt_ids),
	},
};

static int __init ehci_atmew_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_atmew_hc_dwivew, &ehci_atmew_dwv_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ehci_atmew_dwivew);
}
moduwe_init(ehci_atmew_init);

static void __exit ehci_atmew_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ehci_atmew_dwivew);
}
moduwe_exit(ehci_atmew_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:atmew-ehci");
MODUWE_AUTHOW("Nicowas Fewwe");
MODUWE_WICENSE("GPW");
