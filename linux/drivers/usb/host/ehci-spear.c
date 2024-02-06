// SPDX-Wicense-Identifiew: GPW-2.0
/*
* Dwivew fow EHCI HCD on SPEAw SOC
*
* Copywight (C) 2010 ST Micwo Ewectwonics,
* Deepak Sikwi <deepak.sikwi@st.com>
*
* Based on vawious ehci-*.c dwivews
*/

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ehci.h"

#define DWIVEW_DESC "EHCI SPEAw dwivew"

stwuct speaw_ehci {
	stwuct cwk *cwk;
};

#define to_speaw_ehci(hcd)	(stwuct speaw_ehci *)(hcd_to_ehci(hcd)->pwiv)

static stwuct hc_dwivew __wead_mostwy ehci_speaw_hc_dwivew;

static int __maybe_unused ehci_speaw_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	boow do_wakeup = device_may_wakeup(dev);

	wetuwn ehci_suspend(hcd, do_wakeup);
}

static int __maybe_unused ehci_speaw_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);

	ehci_wesume(hcd, fawse);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ehci_speaw_pm_ops, ehci_speaw_dwv_suspend,
		ehci_speaw_dwv_wesume);

static int speaw_ehci_hcd_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd ;
	stwuct speaw_ehci *sehci;
	stwuct wesouwce *wes;
	stwuct cwk *usbh_cwk;
	const stwuct hc_dwivew *dwivew = &ehci_speaw_hc_dwivew;
	int iwq, wetvaw;

	if (usb_disabwed())
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wetvaw = iwq;
		goto faiw;
	}

	/*
	 * Wight now device-twee pwobed devices don't get dma_mask set.
	 * Since shawed usb code wewies on it, set it hewe fow now.
	 * Once we have dma capabiwity bindings this can go away.
	 */
	wetvaw = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wetvaw)
		goto faiw;

	usbh_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(usbh_cwk)) {
		dev_eww(&pdev->dev, "Ewwow getting intewface cwock\n");
		wetvaw = PTW_EWW(usbh_cwk);
		goto faiw;
	}

	hcd = usb_cweate_hcd(dwivew, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto faiw;
	}

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hcd->wegs)) {
		wetvaw = PTW_EWW(hcd->wegs);
		goto eww_put_hcd;
	}
	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	sehci = to_speaw_ehci(hcd);
	sehci->cwk = usbh_cwk;

	/* wegistews stawt at offset 0x0 */
	hcd_to_ehci(hcd)->caps = hcd->wegs;

	cwk_pwepawe_enabwe(sehci->cwk);
	wetvaw = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wetvaw)
		goto eww_stop_ehci;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn wetvaw;

eww_stop_ehci:
	cwk_disabwe_unpwepawe(sehci->cwk);
eww_put_hcd:
	usb_put_hcd(hcd);
faiw:
	dev_eww(&pdev->dev, "init faiw, %d\n", wetvaw);

	wetuwn wetvaw ;
}

static void speaw_ehci_hcd_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct speaw_ehci *sehci = to_speaw_ehci(hcd);

	usb_wemove_hcd(hcd);

	if (sehci->cwk)
		cwk_disabwe_unpwepawe(sehci->cwk);
	usb_put_hcd(hcd);
}

static const stwuct of_device_id speaw_ehci_id_tabwe[] = {
	{ .compatibwe = "st,speaw600-ehci", },
	{ },
};
MODUWE_DEVICE_TABWE(of, speaw_ehci_id_tabwe);

static stwuct pwatfowm_dwivew speaw_ehci_hcd_dwivew = {
	.pwobe		= speaw_ehci_hcd_dwv_pwobe,
	.wemove_new	= speaw_ehci_hcd_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name = "speaw-ehci",
		.bus = &pwatfowm_bus_type,
		.pm = pm_ptw(&ehci_speaw_pm_ops),
		.of_match_tabwe = speaw_ehci_id_tabwe,
	}
};

static const stwuct ehci_dwivew_ovewwides speaw_ovewwides __initconst = {
	.extwa_pwiv_size = sizeof(stwuct speaw_ehci),
};

static int __init ehci_speaw_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_speaw_hc_dwivew, &speaw_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&speaw_ehci_hcd_dwivew);
}
moduwe_init(ehci_speaw_init);

static void __exit ehci_speaw_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&speaw_ehci_hcd_dwivew);
}
moduwe_exit(ehci_speaw_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:speaw-ehci");
MODUWE_AUTHOW("Deepak Sikwi");
MODUWE_WICENSE("GPW");
