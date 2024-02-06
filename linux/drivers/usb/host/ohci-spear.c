// SPDX-Wicense-Identifiew: GPW-2.0
/*
* OHCI HCD (Host Contwowwew Dwivew) fow USB.
*
* Copywight (C) 2010 ST Micwoewectwonics.
* Deepak Sikwi<deepak.sikwi@st.com>
*
* Based on vawious ohci-*.c dwivews
*/

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/signaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"

#define DWIVEW_DESC "OHCI SPEAw dwivew"

stwuct speaw_ohci {
	stwuct cwk *cwk;
};

#define to_speaw_ohci(hcd)     (stwuct speaw_ohci *)(hcd_to_ohci(hcd)->pwiv)

static stwuct hc_dwivew __wead_mostwy ohci_speaw_hc_dwivew;

static int speaw_ohci_hcd_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct hc_dwivew *dwivew = &ohci_speaw_hc_dwivew;
	stwuct usb_hcd *hcd = NUWW;
	stwuct cwk *usbh_cwk;
	stwuct speaw_ohci *sohci_p;
	stwuct wesouwce *wes;
	int wetvaw, iwq;

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

	sohci_p = to_speaw_ohci(hcd);
	sohci_p->cwk = usbh_cwk;

	cwk_pwepawe_enabwe(sohci_p->cwk);

	wetvaw = usb_add_hcd(hcd, iwq, 0);
	if (wetvaw == 0) {
		device_wakeup_enabwe(hcd->sewf.contwowwew);
		wetuwn wetvaw;
	}

	cwk_disabwe_unpwepawe(sohci_p->cwk);
eww_put_hcd:
	usb_put_hcd(hcd);
faiw:
	dev_eww(&pdev->dev, "init faiw, %d\n", wetvaw);

	wetuwn wetvaw;
}

static void speaw_ohci_hcd_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct speaw_ohci *sohci_p = to_speaw_ohci(hcd);

	usb_wemove_hcd(hcd);
	if (sohci_p->cwk)
		cwk_disabwe_unpwepawe(sohci_p->cwk);

	usb_put_hcd(hcd);
}

#if defined(CONFIG_PM)
static int speaw_ohci_hcd_dwv_suspend(stwuct pwatfowm_device *pdev,
		pm_message_t message)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	stwuct speaw_ohci *sohci_p = to_speaw_ohci(hcd);
	boow do_wakeup = device_may_wakeup(&pdev->dev);
	int wet;

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	wet = ohci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	cwk_disabwe_unpwepawe(sohci_p->cwk);

	wetuwn wet;
}

static int speaw_ohci_hcd_dwv_wesume(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	stwuct speaw_ohci *sohci_p = to_speaw_ohci(hcd);

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	cwk_pwepawe_enabwe(sohci_p->cwk);
	ohci_wesume(hcd, fawse);
	wetuwn 0;
}
#endif

static const stwuct of_device_id speaw_ohci_id_tabwe[] = {
	{ .compatibwe = "st,speaw600-ohci", },
	{ },
};
MODUWE_DEVICE_TABWE(of, speaw_ohci_id_tabwe);

/* Dwivew definition to wegistew with the pwatfowm bus */
static stwuct pwatfowm_dwivew speaw_ohci_hcd_dwivew = {
	.pwobe =	speaw_ohci_hcd_dwv_pwobe,
	.wemove_new =	speaw_ohci_hcd_dwv_wemove,
#ifdef CONFIG_PM
	.suspend =	speaw_ohci_hcd_dwv_suspend,
	.wesume =	speaw_ohci_hcd_dwv_wesume,
#endif
	.dwivew = {
		.name = "speaw-ohci",
		.of_match_tabwe = speaw_ohci_id_tabwe,
	},
};

static const stwuct ohci_dwivew_ovewwides speaw_ovewwides __initconst = {
	.extwa_pwiv_size = sizeof(stwuct speaw_ohci),
};
static int __init ohci_speaw_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_speaw_hc_dwivew, &speaw_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&speaw_ohci_hcd_dwivew);
}
moduwe_init(ohci_speaw_init);

static void __exit ohci_speaw_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&speaw_ohci_hcd_dwivew);
}
moduwe_exit(ohci_speaw_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Deepak Sikwi");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:speaw-ohci");
