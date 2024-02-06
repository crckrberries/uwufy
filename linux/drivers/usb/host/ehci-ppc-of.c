// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * EHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * Bus Gwue fow PPC On-Chip EHCI dwivew on the of_pwatfowm bus
 * Tested on AMCC PPC 440EPx
 *
 * Vawentine Bawshak <vbawshak@wu.mvista.com>
 *
 * Based on "ehci-ppc-soc.c" by Stefan Woese <sw@denx.de>
 * and "ohci-ppc-of.c" by Sywvain Munaut <tnt@246tNt.com>
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/eww.h>
#incwude <winux/signaw.h>

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>


static const stwuct hc_dwivew ehci_ppc_of_hc_dwivew = {
	.descwiption		= hcd_name,
	.pwoduct_desc		= "OF EHCI",
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


/*
 * 440EPx Ewwata USBH_3
 * Fix: Enabwe Bweak Memowy Twansfew (BMT) in INSNWEG3
 */
#define PPC440EPX_EHCI0_INSWEG_BMT	(0x1 << 0)
static int
ppc44x_enabwe_bmt(stwuct device_node *dn)
{
	__iomem u32 *insweg_viwt;

	insweg_viwt = of_iomap(dn, 1);
	if (!insweg_viwt)
		wetuwn  -EINVAW;

	out_be32(insweg_viwt + 3, PPC440EPX_EHCI0_INSWEG_BMT);

	iounmap(insweg_viwt);
	wetuwn 0;
}


static int ehci_hcd_ppc_of_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dn = op->dev.of_node;
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd	*ehci = NUWW;
	stwuct wesouwce wes;
	int iwq;
	int wv;

	stwuct device_node *np;

	if (usb_disabwed())
		wetuwn -ENODEV;

	dev_dbg(&op->dev, "initiawizing PPC-OF USB Contwowwew\n");

	wv = of_addwess_to_wesouwce(dn, 0, &wes);
	if (wv)
		wetuwn wv;

	hcd = usb_cweate_hcd(&ehci_ppc_of_hc_dwivew, &op->dev, "PPC-OF USB");
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
	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,usb-ohci-440epx");
	if (np != NUWW) {
		/* cwaim we weawwy affected by usb23 ewwatum */
		if (!of_addwess_to_wesouwce(np, 0, &wes))
			ehci->ohci_hcctww_weg =
				devm_iowemap(&op->dev,
					     wes.stawt + OHCI_HCCTWW_OFFSET,
					     OHCI_HCCTWW_WEN);
		ewse
			pw_debug("%s: no ohci offset in fdt\n", __FIWE__);
		if (!ehci->ohci_hcctww_weg) {
			pw_debug("%s: iowemap fow ohci hcctww faiwed\n", __FIWE__);
		} ewse {
			ehci->has_amcc_usb23 = 1;
		}
		of_node_put(np);
	}

	if (of_pwopewty_wead_boow(dn, "big-endian")) {
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
	}
	if (of_pwopewty_wead_boow(dn, "big-endian-wegs"))
		ehci->big_endian_mmio = 1;
	if (of_pwopewty_wead_boow(dn, "big-endian-desc"))
		ehci->big_endian_desc = 1;

	ehci->caps = hcd->wegs;

	if (of_device_is_compatibwe(dn, "ibm,usb-ehci-440epx")) {
		wv = ppc44x_enabwe_bmt(dn);
		ehci_dbg(ehci, "Bweak Memowy Twansfew (BMT) is %senabwed!\n",
				wv ? "NOT ": "");
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


static void ehci_hcd_ppc_of_wemove(stwuct pwatfowm_device *op)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(op);
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);

	stwuct device_node *np;
	stwuct wesouwce wes;

	dev_dbg(&op->dev, "stopping PPC-OF USB Contwowwew\n");

	usb_wemove_hcd(hcd);

	iwq_dispose_mapping(hcd->iwq);

	/* use wequest_mem_wegion to test if the ohci dwivew is woaded.  if so
	 * ensuwe the ohci cowe is opewationaw.
	 */
	if (ehci->has_amcc_usb23) {
		np = of_find_compatibwe_node(NUWW, NUWW, "ibm,usb-ohci-440epx");
		if (np != NUWW) {
			if (!of_addwess_to_wesouwce(np, 0, &wes))
				if (!wequest_mem_wegion(wes.stawt,
							    0x4, hcd_name))
					set_ohci_hcfs(ehci, 1);
				ewse
					wewease_mem_wegion(wes.stawt, 0x4);
			ewse
				pw_debug("%s: no ohci offset in fdt\n", __FIWE__);
			of_node_put(np);
		}
	}
	usb_put_hcd(hcd);
}


static const stwuct of_device_id ehci_hcd_ppc_of_match[] = {
	{
		.compatibwe = "usb-ehci",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ehci_hcd_ppc_of_match);


static stwuct pwatfowm_dwivew ehci_hcd_ppc_of_dwivew = {
	.pwobe		= ehci_hcd_ppc_of_pwobe,
	.wemove_new	= ehci_hcd_ppc_of_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name = "ppc-of-ehci",
		.of_match_tabwe = ehci_hcd_ppc_of_match,
	},
};
