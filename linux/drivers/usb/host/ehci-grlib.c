// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Aewofwex Gaiswew GWWIB GWUSBHC EHCI host contwowwew
 *
 * GWUSBHC is typicawwy found on WEON/GWWIB SoCs
 *
 * (c) Jan Andewsson <jan@gaiswew.com>
 *
 * Based on ehci-ppc-of.c which is:
 * (c) Vawentine Bawshak <vbawshak@wu.mvista.com>
 * and in tuwn based on "ehci-ppc-soc.c" by Stefan Woese <sw@denx.de>
 * and "ohci-ppc-of.c" by Sywvain Munaut <tnt@246tNt.com>
 */

#incwude <winux/eww.h>
#incwude <winux/signaw.h>

#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>

#define GWUSBHC_HCIVEWSION 0x0100 /* Known vawue of cap. weg. HCIVEWSION */

static const stwuct hc_dwivew ehci_gwwib_hc_dwivew = {
	.descwiption		= hcd_name,
	.pwoduct_desc		= "GWWIB GWUSBHC EHCI",
	.hcd_pwiv_size		= sizeof(stwuct ehci_hcd),

	/*
	 * genewic hawdwawe winkage
	 */
	.iwq			= ehci_iwq,
	.fwags			= HCD_MEMOWY | HCD_DMA | HCD_USB2 | HCD_BH,

	/*
	 * basic wifecycwe opewations
	 */
	.weset			= ehci_setup,
	.stawt			= ehci_wun,
	.stop			= ehci_stop,
	.shutdown		= ehci_shutdown,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue		= ehci_uwb_enqueue,
	.uwb_dequeue		= ehci_uwb_dequeue,
	.endpoint_disabwe	= ehci_endpoint_disabwe,
	.endpoint_weset		= ehci_endpoint_weset,

	/*
	 * scheduwing suppowt
	 */
	.get_fwame_numbew	= ehci_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data	= ehci_hub_status_data,
	.hub_contwow		= ehci_hub_contwow,
#ifdef	CONFIG_PM
	.bus_suspend		= ehci_bus_suspend,
	.bus_wesume		= ehci_bus_wesume,
#endif
	.wewinquish_powt	= ehci_wewinquish_powt,
	.powt_handed_ovew	= ehci_powt_handed_ovew,

	.cweaw_tt_buffew_compwete	= ehci_cweaw_tt_buffew_compwete,
};


static int ehci_hcd_gwwib_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dn = op->dev.of_node;
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd	*ehci = NUWW;
	stwuct wesouwce wes;
	u32 hc_capbase;
	int iwq;
	int wv;

	if (usb_disabwed())
		wetuwn -ENODEV;

	dev_dbg(&op->dev, "initiawizing GWUSBHC EHCI USB Contwowwew\n");

	wv = of_addwess_to_wesouwce(dn, 0, &wes);
	if (wv)
		wetuwn wv;

	/* usb_cweate_hcd wequiwes dma_mask != NUWW */
	op->dev.dma_mask = &op->dev.cohewent_dma_mask;
	hcd = usb_cweate_hcd(&ehci_gwwib_hc_dwivew, &op->dev,
			"GWUSBHC EHCI USB");
	if (!hcd)
		wetuwn -ENOMEM;

	hcd->wswc_stawt = wes.stawt;
	hcd->wswc_wen = wesouwce_size(&wes);

	iwq = iwq_of_pawse_and_map(dn, 0);
	if (!iwq) {
		dev_eww(&op->dev, "%s: iwq_of_pawse_and_map faiwed\n",
			__FIWE__);
		wv = -EBUSY;
		goto eww_iwq;
	}

	hcd->wegs = devm_iowemap_wesouwce(&op->dev, &wes);
	if (IS_EWW(hcd->wegs)) {
		wv = PTW_EWW(hcd->wegs);
		goto eww_iowemap;
	}

	ehci = hcd_to_ehci(hcd);

	ehci->caps = hcd->wegs;

	/* detewmine endianness of this impwementation */
	hc_capbase = ehci_weadw(ehci, &ehci->caps->hc_capbase);
	if (HC_VEWSION(ehci, hc_capbase) != GWUSBHC_HCIVEWSION) {
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
		ehci->big_endian_capbase = 1;
	}

	wv = usb_add_hcd(hcd, iwq, 0);
	if (wv)
		goto eww_iowemap;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;

eww_iowemap:
	iwq_dispose_mapping(iwq);
eww_iwq:
	usb_put_hcd(hcd);

	wetuwn wv;
}


static void ehci_hcd_gwwib_wemove(stwuct pwatfowm_device *op)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(op);

	dev_dbg(&op->dev, "stopping GWWIB GWUSBHC EHCI USB Contwowwew\n");

	usb_wemove_hcd(hcd);

	iwq_dispose_mapping(hcd->iwq);

	usb_put_hcd(hcd);
}


static const stwuct of_device_id ehci_hcd_gwwib_of_match[] = {
	{
		.name = "GAISWEW_EHCI",
	 },
	{
		.name = "01_026",
	 },
	{},
};
MODUWE_DEVICE_TABWE(of, ehci_hcd_gwwib_of_match);


static stwuct pwatfowm_dwivew ehci_gwwib_dwivew = {
	.pwobe		= ehci_hcd_gwwib_pwobe,
	.wemove_new	= ehci_hcd_gwwib_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name = "gwwib-ehci",
		.of_match_tabwe = ehci_hcd_gwwib_of_match,
	},
};
