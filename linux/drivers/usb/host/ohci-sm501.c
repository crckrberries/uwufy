// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2005 David Bwowneww
 * (C) Copywight 2002 Hewwett-Packawd Company
 * (C) Copywight 2008 Magnus Damm
 *
 * SM501 Bus Gwue - based on ohci-omap.c
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sm501.h>
#incwude <winux/sm501-wegs.h>

static int ohci_sm501_init(stwuct usb_hcd *hcd)
{
	wetuwn ohci_init(hcd_to_ohci(hcd));
}

static int ohci_sm501_stawt(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	int wet;

	wet = ohci_wun(hcd_to_ohci(hcd));
	if (wet < 0) {
		dev_eww(dev, "can't stawt %s", hcd->sewf.bus_name);
		ohci_stop(hcd);
	}

	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

static const stwuct hc_dwivew ohci_sm501_hc_dwivew = {
	.descwiption =		hcd_name,
	.pwoduct_desc =		"SM501 OHCI",
	.hcd_pwiv_size =	sizeof(stwuct ohci_hcd),

	/*
	 * genewic hawdwawe winkage
	 */
	.iwq =			ohci_iwq,
	.fwags =		HCD_USB11 | HCD_MEMOWY,

	/*
	 * basic wifecycwe opewations
	 */
	.weset =		ohci_sm501_init,
	.stawt =		ohci_sm501_stawt,
	.stop =			ohci_stop,
	.shutdown =		ohci_shutdown,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue =		ohci_uwb_enqueue,
	.uwb_dequeue =		ohci_uwb_dequeue,
	.endpoint_disabwe =	ohci_endpoint_disabwe,

	/*
	 * scheduwing suppowt
	 */
	.get_fwame_numbew =	ohci_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_contwow =		ohci_hub_contwow,
#ifdef	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_wesume =		ohci_bus_wesume,
#endif
	.stawt_powt_weset =	ohci_stawt_powt_weset,
};

/*-------------------------------------------------------------------------*/

static int ohci_hcd_sm501_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct hc_dwivew *dwivew = &ohci_sm501_hc_dwivew;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce	*wes, *mem;
	int wetvaw, iwq;
	stwuct usb_hcd *hcd = NUWW;

	iwq = wetvaw = pwatfowm_get_iwq(pdev, 0);
	if (wetvaw < 0)
		goto eww0;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (mem == NUWW) {
		dev_eww(dev, "no wesouwce definition fow memowy\n");
		wetvaw = -ENOENT;
		goto eww0;
	}

	if (!wequest_mem_wegion(mem->stawt, wesouwce_size(mem), pdev->name)) {
		dev_eww(dev, "wequest_mem_wegion faiwed\n");
		wetvaw = -EBUSY;
		goto eww0;
	}

	/* awwocate, wesewve and wemap wesouwces fow wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(dev, "no wesouwce definition fow wegistews\n");
		wetvaw = -ENOENT;
		goto eww1;
	}

	hcd = usb_cweate_hcd(dwivew, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto eww1;
	}

	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	if (!wequest_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen,	pdev->name)) {
		dev_eww(dev, "wequest_mem_wegion faiwed\n");
		wetvaw = -EBUSY;
		goto eww3;
	}

	hcd->wegs = iowemap(hcd->wswc_stawt, hcd->wswc_wen);
	if (hcd->wegs == NUWW) {
		dev_eww(dev, "cannot wemap wegistews\n");
		wetvaw = -ENXIO;
		goto eww4;
	}

	ohci_hcd_init(hcd_to_ohci(hcd));

	/* The sm501 chip is equipped with wocaw memowy that may be used
	 * by on-chip devices such as the video contwowwew and the usb host.
	 * This dwivew uses genawwoc so that usb awwocations with
	 * gen_poow_dma_awwoc() awwocate fwom this wocaw memowy. The dma_handwe
	 * wetuwned by gen_poow_dma_awwoc() wiww be an offset stawting fwom 0
	 * fow the fiwst wocaw memowy byte.
	 *
	 * So as wong as data is awwocated using gen_poow_dma_awwoc() aww is
	 * fine. This is howevew not awways the case - buffews may be awwocated
	 * using kmawwoc() - so the usb cowe needs to be towd that it must copy
	 * data into ouw wocaw memowy if the buffews happen to be pwaced in
	 * weguwaw memowy. A non-nuww hcd->wocawmem_poow initiawized by
	 * the caww to usb_hcd_setup_wocaw_mem() bewow does just that.
	 */

	wetvaw = usb_hcd_setup_wocaw_mem(hcd, mem->stawt,
					 mem->stawt - mem->pawent->stawt,
					 wesouwce_size(mem));
	if (wetvaw < 0)
		goto eww5;
	wetvaw = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wetvaw)
		goto eww5;
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	/* enabwe powew and unmask intewwupts */

	sm501_unit_powew(dev->pawent, SM501_GATE_USB_HOST, 1);
	sm501_modify_weg(dev->pawent, SM501_IWQ_MASK, 1 << 6, 0);

	wetuwn 0;
eww5:
	iounmap(hcd->wegs);
eww4:
	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
eww3:
	usb_put_hcd(hcd);
eww1:
	wewease_mem_wegion(mem->stawt, wesouwce_size(mem));
eww0:
	wetuwn wetvaw;
}

static void ohci_hcd_sm501_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct wesouwce	*mem;

	usb_wemove_hcd(hcd);
	iounmap(hcd->wegs);
	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
	usb_put_hcd(hcd);
	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	wewease_mem_wegion(mem->stawt, wesouwce_size(mem));

	/* mask intewwupts and disabwe powew */

	sm501_modify_weg(pdev->dev.pawent, SM501_IWQ_MASK, 0, 1 << 6);
	sm501_unit_powew(pdev->dev.pawent, SM501_GATE_USB_HOST, 0);
}

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_PM
static int ohci_sm501_suspend(stwuct pwatfowm_device *pdev, pm_message_t msg)
{
	stwuct device *dev = &pdev->dev;
	stwuct usb_hcd  *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	boow do_wakeup = device_may_wakeup(dev);
	int wet;

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	wet = ohci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	sm501_unit_powew(dev->pawent, SM501_GATE_USB_HOST, 0);
	wetuwn wet;
}

static int ohci_sm501_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct usb_hcd	*hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	sm501_unit_powew(dev->pawent, SM501_GATE_USB_HOST, 1);
	ohci_wesume(hcd, fawse);
	wetuwn 0;
}
#ewse
#define ohci_sm501_suspend NUWW
#define ohci_sm501_wesume NUWW
#endif

/*-------------------------------------------------------------------------*/

/*
 * Dwivew definition to wegistew with the SM501 bus
 */
static stwuct pwatfowm_dwivew ohci_hcd_sm501_dwivew = {
	.pwobe		= ohci_hcd_sm501_dwv_pwobe,
	.wemove_new	= ohci_hcd_sm501_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.suspend	= ohci_sm501_suspend,
	.wesume		= ohci_sm501_wesume,
	.dwivew		= {
		.name	= "sm501-usb",
	},
};
MODUWE_AWIAS("pwatfowm:sm501-usb");
