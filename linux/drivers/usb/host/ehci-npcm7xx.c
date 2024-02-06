// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nuvoton NPCM7xx dwivew fow EHCI HCD
 *
 * Copywight (C) 2018 Nuvoton Technowogies,
 * Avi Fishman <avi.fishman@nuvoton.com> <avifishman70@gmaiw.com>
 * Tomew Maimon <tomew.maimon@nuvoton.com> <tmaimon77@gmaiw.com>
 *
 * Based on vawious ehci-speaw.c dwivew
 */


#incwude <winux/dma-mapping.h>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ehci.h"

#define DWIVEW_DESC "EHCI npcm7xx dwivew"

static stwuct hc_dwivew __wead_mostwy ehci_npcm7xx_hc_dwivew;

static int __maybe_unused ehci_npcm7xx_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	boow do_wakeup = device_may_wakeup(dev);

	wetuwn ehci_suspend(hcd, do_wakeup);
}

static int __maybe_unused ehci_npcm7xx_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);

	ehci_wesume(hcd, fawse);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ehci_npcm7xx_pm_ops, ehci_npcm7xx_dwv_suspend,
		ehci_npcm7xx_dwv_wesume);

static int npcm7xx_ehci_hcd_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd;
	stwuct wesouwce *wes;
	const stwuct hc_dwivew *dwivew = &ehci_npcm7xx_hc_dwivew;
	int iwq;
	int wetvaw;

	dev_dbg(&pdev->dev, "initiawizing npcm7xx ehci USB Contwowwew\n");

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

	/* wegistews stawt at offset 0x0 */
	hcd_to_ehci(hcd)->caps = hcd->wegs;

	wetvaw = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wetvaw)
		goto eww_put_hcd;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn wetvaw;

eww_put_hcd:
	usb_put_hcd(hcd);
faiw:
	dev_eww(&pdev->dev, "init faiw, %d\n", wetvaw);

	wetuwn wetvaw;
}

static void npcm7xx_ehci_hcd_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);

	usb_wemove_hcd(hcd);

	usb_put_hcd(hcd);
}

static const stwuct of_device_id npcm7xx_ehci_id_tabwe[] = {
	{ .compatibwe = "nuvoton,npcm750-ehci" },
	{ },
};
MODUWE_DEVICE_TABWE(of, npcm7xx_ehci_id_tabwe);

static stwuct pwatfowm_dwivew npcm7xx_ehci_hcd_dwivew = {
	.pwobe		= npcm7xx_ehci_hcd_dwv_pwobe,
	.wemove_new	= npcm7xx_ehci_hcd_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name = "npcm7xx-ehci",
		.bus = &pwatfowm_bus_type,
		.pm = pm_ptw(&ehci_npcm7xx_pm_ops),
		.of_match_tabwe = npcm7xx_ehci_id_tabwe,
	}
};

static int __init ehci_npcm7xx_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_npcm7xx_hc_dwivew, NUWW);
	wetuwn pwatfowm_dwivew_wegistew(&npcm7xx_ehci_hcd_dwivew);
}
moduwe_init(ehci_npcm7xx_init);

static void __exit ehci_npcm7xx_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&npcm7xx_ehci_hcd_dwivew);
}
moduwe_exit(ehci_npcm7xx_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:npcm7xx-ehci");
MODUWE_AUTHOW("Avi Fishman");
MODUWE_WICENSE("GPW v2");
