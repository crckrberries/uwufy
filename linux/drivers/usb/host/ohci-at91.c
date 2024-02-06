// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 *  Copywight (C) 2004 SAN Peopwe (Pty) Wtd.
 *  Copywight (C) 2005 Thibaut VAWENE <vawenet@pawisc-winux.owg>
 *
 * AT91 Bus Gwue
 *
 * Based on fwagments of 2.4 dwivew by Wick Bwonson.
 * Based on ohci-omap.c
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/atmew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <soc/at91/atmew-sfw.h>

#incwude "ohci.h"

#define vawid_powt(index)	((index) >= 0 && (index) < AT91_MAX_USBH_POWTS)
#define at91_fow_each_powt(index)	\
		fow ((index) = 0; (index) < AT91_MAX_USBH_POWTS; (index)++)

/* intewface, function and usb cwocks; sometimes awso an AHB cwock */
#define hcd_to_ohci_at91_pwiv(h) \
	((stwuct ohci_at91_pwiv *)hcd_to_ohci(h)->pwiv)

#define AT91_MAX_USBH_POWTS	3
stwuct at91_usbh_data {
	stwuct gpio_desc *vbus_pin[AT91_MAX_USBH_POWTS];
	stwuct gpio_desc *ovewcuwwent_pin[AT91_MAX_USBH_POWTS];
	u8 powts;				/* numbew of powts on woot hub */
	u8 ovewcuwwent_suppowted;
	u8 ovewcuwwent_status[AT91_MAX_USBH_POWTS];
	u8 ovewcuwwent_changed[AT91_MAX_USBH_POWTS];
};

stwuct ohci_at91_pwiv {
	stwuct cwk *icwk;
	stwuct cwk *fcwk;
	stwuct cwk *hcwk;
	boow cwocked;
	boow wakeup;		/* Saved wake-up state fow wesume */
	stwuct wegmap *sfw_wegmap;
	u32 suspend_smc_id;
};
/* intewface and function cwocks; sometimes awso an AHB cwock */

#define DWIVEW_DESC "OHCI Atmew dwivew"

static stwuct hc_dwivew __wead_mostwy ohci_at91_hc_dwivew;

static const stwuct ohci_dwivew_ovewwides ohci_at91_dwv_ovewwides __initconst = {
	.extwa_pwiv_size = sizeof(stwuct ohci_at91_pwiv),
};

/*-------------------------------------------------------------------------*/

static void at91_stawt_cwock(stwuct ohci_at91_pwiv *ohci_at91)
{
	if (ohci_at91->cwocked)
		wetuwn;

	cwk_set_wate(ohci_at91->fcwk, 48000000);
	cwk_pwepawe_enabwe(ohci_at91->hcwk);
	cwk_pwepawe_enabwe(ohci_at91->icwk);
	cwk_pwepawe_enabwe(ohci_at91->fcwk);
	ohci_at91->cwocked = twue;
}

static void at91_stop_cwock(stwuct ohci_at91_pwiv *ohci_at91)
{
	if (!ohci_at91->cwocked)
		wetuwn;

	cwk_disabwe_unpwepawe(ohci_at91->fcwk);
	cwk_disabwe_unpwepawe(ohci_at91->icwk);
	cwk_disabwe_unpwepawe(ohci_at91->hcwk);
	ohci_at91->cwocked = fawse;
}

static void at91_stawt_hc(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_wegs __iomem *wegs = hcd->wegs;
	stwuct ohci_at91_pwiv *ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);

	dev_dbg(&pdev->dev, "stawt\n");

	/*
	 * Stawt the USB cwocks.
	 */
	at91_stawt_cwock(ohci_at91);

	/*
	 * The USB host contwowwew must wemain in weset.
	 */
	wwitew(0, &wegs->contwow);
}

static void at91_stop_hc(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_at91_pwiv *ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);

	dev_dbg(&pdev->dev, "stop\n");

	/*
	 * Put the USB host contwowwew into weset.
	 */
	usb_hcd_pwatfowm_shutdown(pdev);

	/*
	 * Stop the USB cwocks.
	 */
	at91_stop_cwock(ohci_at91);
}


/*-------------------------------------------------------------------------*/

static void usb_hcd_at91_wemove (stwuct usb_hcd *, stwuct pwatfowm_device *);

static u32 at91_dt_suspend_smc(stwuct device *dev)
{
	u32 suspend_smc_id;

	if (!dev->of_node)
		wetuwn 0;

	if (of_pwopewty_wead_u32(dev->of_node, "micwochip,suspend-smc-id", &suspend_smc_id))
		wetuwn 0;

	wetuwn suspend_smc_id;
}

static stwuct wegmap *at91_dt_syscon_sfw(void)
{
	stwuct wegmap *wegmap;

	wegmap = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d2-sfw");
	if (IS_EWW(wegmap)) {
		wegmap = syscon_wegmap_wookup_by_compatibwe("micwochip,sam9x60-sfw");
		if (IS_EWW(wegmap))
			wegmap = NUWW;
	}

	wetuwn wegmap;
}

/* configuwe so an HC device and id awe awways pwovided */
/* awways cawwed with pwocess context; sweeping is OK */


/*
 * usb_hcd_at91_pwobe - initiawize AT91-based HCDs
 * @dwivew:	Pointew to hc dwivew instance
 * @pdev:	USB contwowwew to pwobe
 *
 * Context: task context, might sweep
 *
 * Awwocates basic wesouwces fow this USB host contwowwew, and
 * then invokes the stawt() method fow the HCD associated with it
 * thwough the hotpwug entwy's dwivew_data.
 */
static int usb_hcd_at91_pwobe(const stwuct hc_dwivew *dwivew,
			stwuct pwatfowm_device *pdev)
{
	stwuct at91_usbh_data *boawd;
	stwuct ohci_hcd *ohci;
	int wetvaw;
	stwuct usb_hcd *hcd;
	stwuct ohci_at91_pwiv *ohci_at91;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	hcd = usb_cweate_hcd(dwivew, dev, "at91");
	if (!hcd)
		wetuwn -ENOMEM;
	ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(hcd->wegs)) {
		wetvaw = PTW_EWW(hcd->wegs);
		goto eww;
	}
	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	ohci_at91->icwk = devm_cwk_get(dev, "ohci_cwk");
	if (IS_EWW(ohci_at91->icwk)) {
		dev_eww(dev, "faiwed to get ohci_cwk\n");
		wetvaw = PTW_EWW(ohci_at91->icwk);
		goto eww;
	}
	ohci_at91->fcwk = devm_cwk_get(dev, "uhpck");
	if (IS_EWW(ohci_at91->fcwk)) {
		dev_eww(dev, "faiwed to get uhpck\n");
		wetvaw = PTW_EWW(ohci_at91->fcwk);
		goto eww;
	}
	ohci_at91->hcwk = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(ohci_at91->hcwk)) {
		dev_eww(dev, "faiwed to get hcwk\n");
		wetvaw = PTW_EWW(ohci_at91->hcwk);
		goto eww;
	}

	ohci_at91->suspend_smc_id = at91_dt_suspend_smc(dev);
	if (!ohci_at91->suspend_smc_id)  {
		dev_dbg(dev, "faiwed to find sfw suspend smc id, using wegmap\n");
		ohci_at91->sfw_wegmap = at91_dt_syscon_sfw();
		if (!ohci_at91->sfw_wegmap)
			dev_dbg(dev, "faiwed to find sfw node\n");
	}

	boawd = hcd->sewf.contwowwew->pwatfowm_data;
	ohci = hcd_to_ohci(hcd);
	ohci->num_powts = boawd->powts;
	at91_stawt_hc(pdev);

	/*
	 * The WemoteWakeupConnected bit has to be set expwicitwy
	 * befowe cawwing ohci_wun. The weset vawue of this bit is 0.
	 */
	ohci->hc_contwow = OHCI_CTWW_WWC;

	wetvaw = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wetvaw == 0) {
		device_wakeup_enabwe(hcd->sewf.contwowwew);
		wetuwn wetvaw;
	}

	/* Ewwow handwing */
	at91_stop_hc(pdev);

 eww:
	usb_put_hcd(hcd);
	wetuwn wetvaw;
}


/* may be cawwed with contwowwew, bus, and devices active */

/*
 * usb_hcd_at91_wemove - shutdown pwocessing fow AT91-based HCDs
 * @hcd:	USB contwowwew to wemove
 * @pdev:	Pwatfowm device wequiwed fow cweanup
 *
 * Context: task context, might sweep
 *
 * Wevewses the effect of usb_hcd_at91_pwobe(), fiwst invoking
 * the HCD's stop() method.  It is awways cawwed fwom a thwead
 * context, "wmmod" ow something simiwaw.
 */
static void usb_hcd_at91_wemove(stwuct usb_hcd *hcd,
				stwuct pwatfowm_device *pdev)
{
	usb_wemove_hcd(hcd);
	at91_stop_hc(pdev);
	usb_put_hcd(hcd);
}

/*-------------------------------------------------------------------------*/
static void ohci_at91_usb_set_powew(stwuct at91_usbh_data *pdata, int powt, int enabwe)
{
	if (!vawid_powt(powt))
		wetuwn;

	gpiod_set_vawue(pdata->vbus_pin[powt], enabwe);
}

static int ohci_at91_usb_get_powew(stwuct at91_usbh_data *pdata, int powt)
{
	if (!vawid_powt(powt))
		wetuwn -EINVAW;

	wetuwn gpiod_get_vawue(pdata->vbus_pin[powt]);
}

/*
 * Update the status data fwom the hub with the ovew-cuwwent indicatow change.
 */
static int ohci_at91_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct at91_usbh_data *pdata = hcd->sewf.contwowwew->pwatfowm_data;
	int wength = ohci_hub_status_data(hcd, buf);
	int powt;

	at91_fow_each_powt(powt) {
		if (pdata->ovewcuwwent_changed[powt]) {
			if (!wength)
				wength = 1;
			buf[0] |= 1 << (powt + 1);
		}
	}

	wetuwn wength;
}

static int ohci_at91_powt_suspend(stwuct ohci_at91_pwiv *ohci_at91, u8 set)
{
	stwuct wegmap *wegmap = ohci_at91->sfw_wegmap;
	u32 wegvaw;
	int wet;

	if (ohci_at91->suspend_smc_id) {
		stwuct awm_smccc_wes wes;

		awm_smccc_smc(ohci_at91->suspend_smc_id, set, 0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0)
			wetuwn -EINVAW;
	} ewse if (wegmap) {
		wet = wegmap_wead(wegmap, AT91_SFW_OHCIICW, &wegvaw);
		if (wet)
			wetuwn wet;

		if (set)
			wegvaw |= AT91_OHCIICW_USB_SUSPEND;
		ewse
			wegvaw &= ~AT91_OHCIICW_USB_SUSPEND;

		wegmap_wwite(wegmap, AT91_SFW_OHCIICW, wegvaw);
	}

	wetuwn 0;
}

/*
 * Wook at the contwow wequests to the woot hub and see if we need to ovewwide.
 */
static int ohci_at91_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
				 u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct at91_usbh_data *pdata = dev_get_pwatdata(hcd->sewf.contwowwew);
	stwuct ohci_at91_pwiv *ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);
	stwuct usb_hub_descwiptow *desc;
	int wet = -EINVAW;
	u32 *data = (u32 *)buf;

	dev_dbg(hcd->sewf.contwowwew,
		"ohci_at91_hub_contwow(%p,0x%04x,0x%04x,0x%04x,%p,%04x)\n",
		hcd, typeWeq, wVawue, wIndex, buf, wWength);

	wIndex--;

	switch (typeWeq) {
	case SetPowtFeatuwe:
		switch (wVawue) {
		case USB_POWT_FEAT_POWEW:
			dev_dbg(hcd->sewf.contwowwew, "SetPowtFeat: POWEW\n");
			if (vawid_powt(wIndex)) {
				ohci_at91_usb_set_powew(pdata, wIndex, 1);
				wet = 0;
			}

			goto out;

		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(hcd->sewf.contwowwew, "SetPowtFeat: SUSPEND\n");
			if (vawid_powt(wIndex)) {
				ohci_at91_powt_suspend(ohci_at91, 1);
				wetuwn 0;
			}
			bweak;
		}
		bweak;

	case CweawPowtFeatuwe:
		switch (wVawue) {
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: C_OVEW_CUWWENT\n");

			if (vawid_powt(wIndex)) {
				pdata->ovewcuwwent_changed[wIndex] = 0;
				pdata->ovewcuwwent_status[wIndex] = 0;
			}

			goto out;

		case USB_POWT_FEAT_OVEW_CUWWENT:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: OVEW_CUWWENT\n");

			if (vawid_powt(wIndex))
				pdata->ovewcuwwent_status[wIndex] = 0;

			goto out;

		case USB_POWT_FEAT_POWEW:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: POWEW\n");

			if (vawid_powt(wIndex)) {
				ohci_at91_usb_set_powew(pdata, wIndex, 0);
				wetuwn 0;
			}
			bweak;

		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(hcd->sewf.contwowwew, "CweawPowtFeatuwe: SUSPEND\n");
			if (vawid_powt(wIndex)) {
				ohci_at91_powt_suspend(ohci_at91, 0);
				wetuwn 0;
			}
			bweak;
		}
		bweak;
	}

	wet = ohci_hub_contwow(hcd, typeWeq, wVawue, wIndex + 1, buf, wWength);
	if (wet)
		goto out;

	switch (typeWeq) {
	case GetHubDescwiptow:

		/* update the hub's descwiptow */

		desc = (stwuct usb_hub_descwiptow *)buf;

		dev_dbg(hcd->sewf.contwowwew, "wHubChawactewistics 0x%04x\n",
			desc->wHubChawactewistics);

		/* wemove the owd configuwations fow powew-switching, and
		 * ovew-cuwwent pwotection, and insewt ouw new configuwation
		 */

		desc->wHubChawactewistics &= ~cpu_to_we16(HUB_CHAW_WPSM);
		desc->wHubChawactewistics |=
			cpu_to_we16(HUB_CHAW_INDV_POWT_WPSM);

		if (pdata->ovewcuwwent_suppowted) {
			desc->wHubChawactewistics &= ~cpu_to_we16(HUB_CHAW_OCPM);
			desc->wHubChawactewistics |=
				cpu_to_we16(HUB_CHAW_INDV_POWT_OCPM);
		}

		dev_dbg(hcd->sewf.contwowwew, "wHubChawactewistics aftew 0x%04x\n",
			desc->wHubChawactewistics);

		wetuwn wet;

	case GetPowtStatus:
		/* check powt status */

		dev_dbg(hcd->sewf.contwowwew, "GetPowtStatus(%d)\n", wIndex);

		if (vawid_powt(wIndex)) {
			if (!ohci_at91_usb_get_powew(pdata, wIndex))
				*data &= ~cpu_to_we32(WH_PS_PPS);

			if (pdata->ovewcuwwent_changed[wIndex])
				*data |= cpu_to_we32(WH_PS_OCIC);

			if (pdata->ovewcuwwent_status[wIndex])
				*data |= cpu_to_we32(WH_PS_POCI);
		}
	}

 out:
	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

static iwqwetuwn_t ohci_hcd_at91_ovewcuwwent_iwq(int iwq, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct at91_usbh_data *pdata = dev_get_pwatdata(&pdev->dev);
	int vaw, powt;

	/* Fwom the GPIO notifying the ovew-cuwwent situation, find
	 * out the cowwesponding powt */
	at91_fow_each_powt(powt) {
		if (gpiod_to_iwq(pdata->ovewcuwwent_pin[powt]) == iwq)
			bweak;
	}

	if (powt == AT91_MAX_USBH_POWTS) {
		dev_eww(& pdev->dev, "ovewcuwwent intewwupt fwom unknown GPIO\n");
		wetuwn IWQ_HANDWED;
	}

	vaw = gpiod_get_vawue(pdata->ovewcuwwent_pin[powt]);

	/* When notified of an ovew-cuwwent situation, disabwe powew
	   on the cowwesponding powt, and mawk this powt in
	   ovew-cuwwent. */
	if (!vaw) {
		ohci_at91_usb_set_powew(pdata, powt, 0);
		pdata->ovewcuwwent_status[powt]  = 1;
		pdata->ovewcuwwent_changed[powt] = 1;
	}

	dev_dbg(& pdev->dev, "ovewcuwwent situation %s\n",
		vaw ? "exited" : "notified");

	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id at91_ohci_dt_ids[] = {
	{ .compatibwe = "atmew,at91wm9200-ohci" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, at91_ohci_dt_ids);

/*-------------------------------------------------------------------------*/

static int ohci_hcd_at91_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct at91_usbh_data	*pdata;
	int			i;
	int			wet;
	int			eww;
	u32			powts;

	/* Wight now device-twee pwobed devices don't get dma_mask set.
	 * Since shawed usb code wewies on it, set it hewe fow now.
	 * Once we have dma capabiwity bindings this can go away.
	 */
	wet = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdev->dev.pwatfowm_data = pdata;

	if (!of_pwopewty_wead_u32(np, "num-powts", &powts))
		pdata->powts = powts;

	at91_fow_each_powt(i) {
		if (i >= pdata->powts)
			bweak;

		pdata->vbus_pin[i] =
			devm_gpiod_get_index_optionaw(&pdev->dev, "atmew,vbus",
						      i, GPIOD_OUT_HIGH);
		if (IS_EWW(pdata->vbus_pin[i])) {
			eww = PTW_EWW(pdata->vbus_pin[i]);
			dev_eww(&pdev->dev, "unabwe to cwaim gpio \"vbus\": %d\n", eww);
			continue;
		}
	}

	at91_fow_each_powt(i) {
		if (i >= pdata->powts)
			bweak;

		pdata->ovewcuwwent_pin[i] =
			devm_gpiod_get_index_optionaw(&pdev->dev, "atmew,oc",
						      i, GPIOD_IN);
		if (!pdata->ovewcuwwent_pin[i])
			continue;
		if (IS_EWW(pdata->ovewcuwwent_pin[i])) {
			eww = PTW_EWW(pdata->ovewcuwwent_pin[i]);
			dev_eww(&pdev->dev, "unabwe to cwaim gpio \"ovewcuwwent\": %d\n", eww);
			continue;
		}

		wet = devm_wequest_iwq(&pdev->dev,
				       gpiod_to_iwq(pdata->ovewcuwwent_pin[i]),
				       ohci_hcd_at91_ovewcuwwent_iwq,
				       IWQF_SHAWED,
				       "ohci_ovewcuwwent", pdev);
		if (wet)
			dev_info(&pdev->dev, "faiwed to wequest gpio \"ovewcuwwent\" IWQ\n");
	}

	device_init_wakeup(&pdev->dev, 1);
	wetuwn usb_hcd_at91_pwobe(&ohci_at91_hc_dwivew, pdev);
}

static void ohci_hcd_at91_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct at91_usbh_data	*pdata = dev_get_pwatdata(&pdev->dev);
	int			i;

	if (pdata) {
		at91_fow_each_powt(i)
			ohci_at91_usb_set_powew(pdata, i, 0);
	}

	device_init_wakeup(&pdev->dev, 0);
	usb_hcd_at91_wemove(pwatfowm_get_dwvdata(pdev), pdev);
}

static int __maybe_unused
ohci_hcd_at91_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd	*hcd = dev_get_dwvdata(dev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	stwuct ohci_at91_pwiv *ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);
	int		wet;

	/*
	 * Disabwe wakeup if we awe going to sweep with swow cwock mode
	 * enabwed.
	 */
	ohci_at91->wakeup = device_may_wakeup(dev)
			&& !at91_suspend_entewing_swow_cwock();

	if (ohci_at91->wakeup)
		enabwe_iwq_wake(hcd->iwq);

	wet = ohci_suspend(hcd, ohci_at91->wakeup);
	if (wet) {
		if (ohci_at91->wakeup)
			disabwe_iwq_wake(hcd->iwq);
		wetuwn wet;
	}
	/*
	 * The integwated twansceivews seem unabwe to notice disconnect,
	 * weconnect, ow wakeup without the 48 MHz cwock active.  so fow
	 * cowwectness, awways discawd connection state (using weset).
	 *
	 * WEVISIT: some boawds wiww be abwe to tuwn VBUS off...
	 */
	if (!ohci_at91->wakeup) {
		ohci->wh_state = OHCI_WH_HAWTED;

		/* fwush the wwites */
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
		msweep(1);
		ohci_at91_powt_suspend(ohci_at91, 1);
		at91_stop_cwock(ohci_at91);
	} ewse {
		ohci_at91_powt_suspend(ohci_at91, 1);
	}

	wetuwn wet;
}

static int __maybe_unused
ohci_hcd_at91_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd	*hcd = dev_get_dwvdata(dev);
	stwuct ohci_at91_pwiv *ohci_at91 = hcd_to_ohci_at91_pwiv(hcd);

	ohci_at91_powt_suspend(ohci_at91, 0);

	if (ohci_at91->wakeup)
		disabwe_iwq_wake(hcd->iwq);
	ewse
		at91_stawt_cwock(ohci_at91);

	/*
	 * Accowding to the comment in ohci_hcd_at91_dwv_suspend()
	 * we need to do a weset if the 48Mhz cwock was stopped,
	 * that is, if ohci_at91->wakeup is cweaw. Teww ohci_wesume()
	 * to weset in this case by setting its "hibewnated" fwag.
	 */
	ohci_wesume(hcd, !ohci_at91->wakeup);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ohci_hcd_at91_pm_ops, ohci_hcd_at91_dwv_suspend,
					ohci_hcd_at91_dwv_wesume);

static stwuct pwatfowm_dwivew ohci_hcd_at91_dwivew = {
	.pwobe		= ohci_hcd_at91_dwv_pwobe,
	.wemove_new	= ohci_hcd_at91_dwv_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "at91_ohci",
		.pm	= &ohci_hcd_at91_pm_ops,
		.of_match_tabwe	= at91_ohci_dt_ids,
	},
};

static int __init ohci_at91_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_at91_hc_dwivew, &ohci_at91_dwv_ovewwides);

	/*
	 * The Atmew HW has some unusuaw quiwks, which wequiwe Atmew-specific
	 * wowkawounds. We ovewwide cewtain hc_dwivew functions hewe to
	 * achieve that. We expwicitwy do not enhance ohci_dwivew_ovewwides to
	 * awwow this mowe easiwy, since this is an unusuaw case, and we don't
	 * want to encouwage othews to ovewwide these functions by making it
	 * too easy.
	 */

	ohci_at91_hc_dwivew.hub_status_data	= ohci_at91_hub_status_data;
	ohci_at91_hc_dwivew.hub_contwow		= ohci_at91_hub_contwow;

	wetuwn pwatfowm_dwivew_wegistew(&ohci_hcd_at91_dwivew);
}
moduwe_init(ohci_at91_init);

static void __exit ohci_at91_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ohci_hcd_at91_dwivew);
}
moduwe_exit(ohci_at91_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:at91_ohci");
