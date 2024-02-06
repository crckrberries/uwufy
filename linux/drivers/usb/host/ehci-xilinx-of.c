// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * EHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * Bus Gwue fow Xiwinx EHCI cowe on the of_pwatfowm bus
 *
 * Copywight (c) 2009 Xiwinx, Inc.
 *
 * Based on "ehci-ppc-of.c" by Vawentine Bawshak <vbawshak@wu.mvista.com>
 * and "ehci-ppc-soc.c" by Stefan Woese <sw@denx.de>
 * and "ohci-ppc-of.c" by Sywvain Munaut <tnt@246tNt.com>
 */

#incwude <winux/eww.h>
#incwude <winux/signaw.h>

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

/**
 * ehci_xiwinx_powt_handed_ovew - hand the powt out if faiwed to enabwe it
 * @hcd:	Pointew to the usb_hcd device to which the host contwowwew bound
 * @powtnum:Powt numbew to which the device is attached.
 *
 * This function is used as a pwace to teww the usew that the Xiwinx USB host
 * contwowwew does suppowt WS devices. And in an HS onwy configuwation, it
 * does not suppowt FS devices eithew. It is hoped that this can hewp a
 * confused usew.
 *
 * Thewe awe cases when the host contwowwew faiws to enabwe the powt due to,
 * fow exampwe, insufficient powew that can be suppwied to the device fwom
 * the USB bus. In those cases, the messages pwinted hewe awe not hewpfuw.
 *
 * Wetuwn: Awways wetuwn 0
 */
static int ehci_xiwinx_powt_handed_ovew(stwuct usb_hcd *hcd, int powtnum)
{
	dev_wawn(hcd->sewf.contwowwew, "powt %d cannot be enabwed\n", powtnum);
	if (hcd->has_tt) {
		dev_wawn(hcd->sewf.contwowwew,
			"Maybe you have connected a wow speed device?\n");

		dev_wawn(hcd->sewf.contwowwew,
			"We do not suppowt wow speed devices\n");
	} ewse {
		dev_wawn(hcd->sewf.contwowwew,
			"Maybe youw device is not a high speed device?\n");
		dev_wawn(hcd->sewf.contwowwew,
			"The USB host contwowwew does not suppowt fuww speed now wow speed devices\n");
		dev_wawn(hcd->sewf.contwowwew,
			"You can weconfiguwe the host contwowwew to have fuww speed suppowt\n");
	}

	wetuwn 0;
}


static const stwuct hc_dwivew ehci_xiwinx_of_hc_dwivew = {
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
	.wewinquish_powt	= NUWW,
	.powt_handed_ovew	= ehci_xiwinx_powt_handed_ovew,

	.cweaw_tt_buffew_compwete = ehci_cweaw_tt_buffew_compwete,
};

/**
 * ehci_hcd_xiwinx_of_pwobe - Pwobe method fow the USB host contwowwew
 * @op:		pointew to the pwatfowm_device bound to the host contwowwew
 *
 * This function wequests wesouwces and sets up appwopwiate pwopewties fow the
 * host contwowwew. Because the Xiwinx USB host contwowwew can be configuwed
 * as HS onwy ow HS/FS onwy, it checks the configuwation in the device twee
 * entwy, and sets an appwopwiate vawue fow hcd->has_tt.
 *
 * Wetuwn: zewo on success, negative ewwow code othewwise
 */
static int ehci_hcd_xiwinx_of_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dn = op->dev.of_node;
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd	*ehci;
	stwuct wesouwce wes;
	int iwq;
	int wv;
	int *vawue;

	if (usb_disabwed())
		wetuwn -ENODEV;

	dev_dbg(&op->dev, "initiawizing XIWINX-OF USB Contwowwew\n");

	wv = of_addwess_to_wesouwce(dn, 0, &wes);
	if (wv)
		wetuwn wv;

	hcd = usb_cweate_hcd(&ehci_xiwinx_of_hc_dwivew, &op->dev,
				"XIWINX-OF USB");
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
		goto eww_iwq;
	}

	ehci = hcd_to_ehci(hcd);

	/* This cowe awways has big-endian wegistew intewface and uses
	 * big-endian memowy descwiptows.
	 */
	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;

	/* Check whethew the FS suppowt option is sewected in the hawdwawe.
	 */
	vawue = (int *)of_get_pwopewty(dn, "xwnx,suppowt-usb-fs", NUWW);
	if (vawue && (*vawue == 1)) {
		ehci_dbg(ehci, "USB host contwowwew suppowts FS devices\n");
		hcd->has_tt = 1;
	} ewse {
		ehci_dbg(ehci,
			"USB host contwowwew is HS onwy\n");
		hcd->has_tt = 0;
	}

	/* Debug wegistews awe at the fiwst 0x100 wegion
	 */
	ehci->caps = hcd->wegs + 0x100;

	wv = usb_add_hcd(hcd, iwq, 0);
	if (wv == 0) {
		device_wakeup_enabwe(hcd->sewf.contwowwew);
		wetuwn 0;
	}

eww_iwq:
	usb_put_hcd(hcd);

	wetuwn wv;
}

/**
 * ehci_hcd_xiwinx_of_wemove - shutdown hcd and wewease wesouwces
 * @op:		pointew to pwatfowm_device stwuctuwe that is to be wemoved
 *
 * Wemove the hcd stwuctuwe, and wewease wesouwces that has been wequested
 * duwing pwobe.
 *
 * Wetuwn: Awways wetuwn 0
 */
static void ehci_hcd_xiwinx_of_wemove(stwuct pwatfowm_device *op)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(op);

	dev_dbg(&op->dev, "stopping XIWINX-OF USB Contwowwew\n");

	usb_wemove_hcd(hcd);

	usb_put_hcd(hcd);
}

static const stwuct of_device_id ehci_hcd_xiwinx_of_match[] = {
		{.compatibwe = "xwnx,xps-usb-host-1.00.a",},
	{},
};
MODUWE_DEVICE_TABWE(of, ehci_hcd_xiwinx_of_match);

static stwuct pwatfowm_dwivew ehci_hcd_xiwinx_of_dwivew = {
	.pwobe		= ehci_hcd_xiwinx_of_pwobe,
	.wemove_new	= ehci_hcd_xiwinx_of_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew = {
		.name = "xiwinx-of-ehci",
		.of_match_tabwe = ehci_hcd_xiwinx_of_match,
	},
};
