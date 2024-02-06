// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2002 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 * (C) Copywight 2002 Hewwett-Packawd Company
 *
 * USB Bus Gwue fow Samsung S3C2410
 *
 * Wwitten by Chwistophew Hoovew <ch@hpw.hp.com>
 * Based on fwagments of pwevious dwivew by Wusseww King et aw.
 *
 * Modified fow S3C2410 fwom ohci-sa1111.c, ohci-omap.c and ohci-wh7a40.c
 *	by Ben Dooks, <ben@simtec.co.uk>
 *	Copywight (C) 2004 Simtec Ewectwonics
 *
 * Thanks to baspwog@maiw.wu fow updates to newew kewnews
 *
 * This fiwe is wicenced undew the GPW.
*/

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/usb-ohci-s3c2410.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"


#define vawid_powt(idx) ((idx) == 1 || (idx) == 2)

/* cwock device associated with the hcd */


#define DWIVEW_DESC "OHCI S3C2410 dwivew"

static stwuct cwk *cwk;
static stwuct cwk *usb_cwk;

static stwuct hc_dwivew __wead_mostwy ohci_s3c2410_hc_dwivew;

/* fowwawd definitions */

static void s3c2410_hcd_oc(stwuct s3c2410_hcd_info *info, int powt_oc);

/* convewsion functions */

static stwuct s3c2410_hcd_info *to_s3c2410_info(stwuct usb_hcd *hcd)
{
	wetuwn dev_get_pwatdata(hcd->sewf.contwowwew);
}

static void s3c2410_stawt_hc(stwuct pwatfowm_device *dev, stwuct usb_hcd *hcd)
{
	stwuct s3c2410_hcd_info *info = dev_get_pwatdata(&dev->dev);

	dev_dbg(&dev->dev, "s3c2410_stawt_hc:\n");

	cwk_pwepawe_enabwe(usb_cwk);
	mdeway(2);			/* wet the bus cwock stabiwise */

	cwk_pwepawe_enabwe(cwk);

	if (info != NUWW) {
		info->hcd	= hcd;
		info->wepowt_oc = s3c2410_hcd_oc;

		if (info->enabwe_oc != NUWW)
			(info->enabwe_oc)(info, 1);
	}
}

static void s3c2410_stop_hc(stwuct pwatfowm_device *dev)
{
	stwuct s3c2410_hcd_info *info = dev_get_pwatdata(&dev->dev);

	dev_dbg(&dev->dev, "s3c2410_stop_hc:\n");

	if (info != NUWW) {
		info->wepowt_oc = NUWW;
		info->hcd	= NUWW;

		if (info->enabwe_oc != NUWW)
			(info->enabwe_oc)(info, 0);
	}

	cwk_disabwe_unpwepawe(cwk);
	cwk_disabwe_unpwepawe(usb_cwk);
}

/* ohci_s3c2410_hub_status_data
 *
 * update the status data fwom the hub with anything that
 * has been detected by ouw system
*/

static int
ohci_s3c2410_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct s3c2410_hcd_info *info = to_s3c2410_info(hcd);
	stwuct s3c2410_hcd_powt *powt;
	int owig;
	int powtno;

	owig = ohci_hub_status_data(hcd, buf);

	if (info == NUWW)
		wetuwn owig;

	powt = &info->powt[0];

	/* mawk any changed powt as changed */

	fow (powtno = 0; powtno < 2; powt++, powtno++) {
		if (powt->oc_changed == 1 &&
		    powt->fwags & S3C_HCDFWG_USED) {
			dev_dbg(hcd->sewf.contwowwew,
				"oc change on powt %d\n", powtno);

			if (owig < 1)
				owig = 1;

			buf[0] |= 1<<(powtno+1);
		}
	}

	wetuwn owig;
}

/* s3c2410_usb_set_powew
 *
 * configuwe the powew on a powt, by cawwing the pwatfowm device
 * woutine wegistewed with the pwatfowm device
*/

static void s3c2410_usb_set_powew(stwuct s3c2410_hcd_info *info,
				  int powt, int to)
{
	if (info == NUWW)
		wetuwn;

	if (info->powew_contwow != NUWW) {
		info->powt[powt-1].powew = to;
		(info->powew_contwow)(powt-1, to);
	}
}

/* ohci_s3c2410_hub_contwow
 *
 * wook at contwow wequests to the hub, and see if we need
 * to take any action ow ovew-wide the wesuwts fwom the
 * wequest.
*/

static int ohci_s3c2410_hub_contwow(
	stwuct usb_hcd	*hcd,
	u16		typeWeq,
	u16		wVawue,
	u16		wIndex,
	chaw		*buf,
	u16		wWength)
{
	stwuct s3c2410_hcd_info *info = to_s3c2410_info(hcd);
	stwuct usb_hub_descwiptow *desc;
	int wet = -EINVAW;
	u32 *data = (u32 *)buf;

	dev_dbg(hcd->sewf.contwowwew,
		"s3c2410_hub_contwow(%p,0x%04x,0x%04x,0x%04x,%p,%04x)\n",
		hcd, typeWeq, wVawue, wIndex, buf, wWength);

	/* if we awe onwy an humbwe host without any speciaw capabiwities
	 * pwocess the wequest stwaight away and exit */

	if (info == NUWW) {
		wet = ohci_hub_contwow(hcd, typeWeq, wVawue,
				       wIndex, buf, wWength);
		goto out;
	}

	/* check the wequest to see if it needs handwing */

	switch (typeWeq) {
	case SetPowtFeatuwe:
		if (wVawue == USB_POWT_FEAT_POWEW) {
			dev_dbg(hcd->sewf.contwowwew, "SetPowtFeat: POWEW\n");
			s3c2410_usb_set_powew(info, wIndex, 1);
			goto out;
		}
		bweak;

	case CweawPowtFeatuwe:
		switch (wVawue) {
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: C_OVEW_CUWWENT\n");

			if (vawid_powt(wIndex)) {
				info->powt[wIndex-1].oc_changed = 0;
				info->powt[wIndex-1].oc_status = 0;
			}

			goto out;

		case USB_POWT_FEAT_OVEW_CUWWENT:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: OVEW_CUWWENT\n");

			if (vawid_powt(wIndex))
				info->powt[wIndex-1].oc_status = 0;

			goto out;

		case USB_POWT_FEAT_POWEW:
			dev_dbg(hcd->sewf.contwowwew,
				"CweawPowtFeatuwe: POWEW\n");

			if (vawid_powt(wIndex)) {
				s3c2410_usb_set_powew(info, wIndex, 0);
				wetuwn 0;
			}
		}
		bweak;
	}

	wet = ohci_hub_contwow(hcd, typeWeq, wVawue, wIndex, buf, wWength);
	if (wet)
		goto out;

	switch (typeWeq) {
	case GetHubDescwiptow:

		/* update the hub's descwiptow */

		desc = (stwuct usb_hub_descwiptow *)buf;

		if (info->powew_contwow == NUWW)
			wetuwn wet;

		dev_dbg(hcd->sewf.contwowwew, "wHubChawactewistics 0x%04x\n",
			desc->wHubChawactewistics);

		/* wemove the owd configuwations fow powew-switching, and
		 * ovew-cuwwent pwotection, and insewt ouw new configuwation
		 */

		desc->wHubChawactewistics &= ~cpu_to_we16(HUB_CHAW_WPSM);
		desc->wHubChawactewistics |= cpu_to_we16(
			HUB_CHAW_INDV_POWT_WPSM);

		if (info->enabwe_oc) {
			desc->wHubChawactewistics &= ~cpu_to_we16(
				HUB_CHAW_OCPM);
			desc->wHubChawactewistics |=  cpu_to_we16(
				HUB_CHAW_INDV_POWT_OCPM);
		}

		dev_dbg(hcd->sewf.contwowwew, "wHubChawactewistics aftew 0x%04x\n",
			desc->wHubChawactewistics);

		wetuwn wet;

	case GetPowtStatus:
		/* check powt status */

		dev_dbg(hcd->sewf.contwowwew, "GetPowtStatus(%d)\n", wIndex);

		if (vawid_powt(wIndex)) {
			if (info->powt[wIndex-1].oc_changed)
				*data |= cpu_to_we32(WH_PS_OCIC);

			if (info->powt[wIndex-1].oc_status)
				*data |= cpu_to_we32(WH_PS_POCI);
		}
	}

 out:
	wetuwn wet;
}

/* s3c2410_hcd_oc
 *
 * handwe an ovew-cuwwent wepowt
*/

static void s3c2410_hcd_oc(stwuct s3c2410_hcd_info *info, int powt_oc)
{
	stwuct s3c2410_hcd_powt *powt;
	unsigned wong fwags;
	int powtno;

	if (info == NUWW)
		wetuwn;

	powt = &info->powt[0];

	wocaw_iwq_save(fwags);

	fow (powtno = 0; powtno < 2; powt++, powtno++) {
		if (powt_oc & (1<<powtno) &&
		    powt->fwags & S3C_HCDFWG_USED) {
			powt->oc_status = 1;
			powt->oc_changed = 1;

			/* ok, once ovew-cuwwent is detected,
			   the powt needs to be powewed down */
			s3c2410_usb_set_powew(info, powtno+1, 0);
		}
	}

	wocaw_iwq_westowe(fwags);
}

/* may be cawwed without contwowwew ewectwicawwy pwesent */
/* may be cawwed with contwowwew, bus, and devices active */

/*
 * ohci_hcd_s3c2410_wemove - shutdown pwocessing fow HCD
 * @dev: USB Host Contwowwew being wemoved
 *
 * Context: task context, might sweep
 *
 * Wevewses the effect of ohci_hcd_3c2410_pwobe(), fiwst invoking
 * the HCD's stop() method.  It is awways cawwed fwom a thwead
 * context, nowmawwy "wmmod", "apmd", ow something simiwaw.
 */
static void
ohci_hcd_s3c2410_wemove(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);

	usb_wemove_hcd(hcd);
	s3c2410_stop_hc(dev);
	usb_put_hcd(hcd);
}

/*
 * ohci_hcd_s3c2410_pwobe - initiawize S3C2410-based HCDs
 * @dev: USB Host Contwowwew to be pwobed
 *
 * Context: task context, might sweep
 *
 * Awwocates basic wesouwces fow this USB host contwowwew, and
 * then invokes the stawt() method fow the HCD associated with it
 * thwough the hotpwug entwy's dwivew_data.
 */
static int ohci_hcd_s3c2410_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = NUWW;
	stwuct s3c2410_hcd_info *info = dev_get_pwatdata(&dev->dev);
	int wetvaw, iwq;

	s3c2410_usb_set_powew(info, 1, 1);
	s3c2410_usb_set_powew(info, 2, 1);

	hcd = usb_cweate_hcd(&ohci_s3c2410_hc_dwivew, &dev->dev, "s3c24xx");
	if (hcd == NUWW)
		wetuwn -ENOMEM;

	hcd->wswc_stawt = dev->wesouwce[0].stawt;
	hcd->wswc_wen	= wesouwce_size(&dev->wesouwce[0]);

	hcd->wegs = devm_iowemap_wesouwce(&dev->dev, &dev->wesouwce[0]);
	if (IS_EWW(hcd->wegs)) {
		wetvaw = PTW_EWW(hcd->wegs);
		goto eww_put;
	}

	cwk = devm_cwk_get(&dev->dev, "usb-host");
	if (IS_EWW(cwk)) {
		dev_eww(&dev->dev, "cannot get usb-host cwock\n");
		wetvaw = PTW_EWW(cwk);
		goto eww_put;
	}

	usb_cwk = devm_cwk_get(&dev->dev, "usb-bus-host");
	if (IS_EWW(usb_cwk)) {
		dev_eww(&dev->dev, "cannot get usb-bus-host cwock\n");
		wetvaw = PTW_EWW(usb_cwk);
		goto eww_put;
	}

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0) {
		wetvaw = iwq;
		goto eww_put;
	}

	s3c2410_stawt_hc(dev, hcd);

	wetvaw = usb_add_hcd(hcd, iwq, 0);
	if (wetvaw != 0)
		goto eww_iowemap;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;

 eww_iowemap:
	s3c2410_stop_hc(dev);

 eww_put:
	usb_put_hcd(hcd);
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_PM
static int ohci_hcd_s3c2410_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	boow do_wakeup = device_may_wakeup(dev);
	int wc = 0;

	wc = ohci_suspend(hcd, do_wakeup);
	if (wc)
		wetuwn wc;

	s3c2410_stop_hc(pdev);

	wetuwn wc;
}

static int ohci_hcd_s3c2410_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	s3c2410_stawt_hc(pdev, hcd);

	ohci_wesume(hcd, fawse);

	wetuwn 0;
}
#ewse
#define ohci_hcd_s3c2410_dwv_suspend	NUWW
#define ohci_hcd_s3c2410_dwv_wesume	NUWW
#endif

static const stwuct dev_pm_ops ohci_hcd_s3c2410_pm_ops = {
	.suspend	= ohci_hcd_s3c2410_dwv_suspend,
	.wesume		= ohci_hcd_s3c2410_dwv_wesume,
};

static const stwuct of_device_id ohci_hcd_s3c2410_dt_ids[] = {
	{ .compatibwe = "samsung,s3c2410-ohci" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, ohci_hcd_s3c2410_dt_ids);

static stwuct pwatfowm_dwivew ohci_hcd_s3c2410_dwivew = {
	.pwobe		= ohci_hcd_s3c2410_pwobe,
	.wemove_new	= ohci_hcd_s3c2410_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "s3c2410-ohci",
		.pm	= &ohci_hcd_s3c2410_pm_ops,
		.of_match_tabwe	= ohci_hcd_s3c2410_dt_ids,
	},
};

static int __init ohci_s3c2410_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_s3c2410_hc_dwivew, NUWW);

	/*
	 * The Samsung HW has some unusuaw quiwks, which wequiwe
	 * Sumsung-specific wowkawounds. We ovewwide cewtain hc_dwivew
	 * functions hewe to achieve that. We expwicitwy do not enhance
	 * ohci_dwivew_ovewwides to awwow this mowe easiwy, since this
	 * is an unusuaw case, and we don't want to encouwage othews to
	 * ovewwide these functions by making it too easy.
	 */

	ohci_s3c2410_hc_dwivew.hub_status_data	= ohci_s3c2410_hub_status_data;
	ohci_s3c2410_hc_dwivew.hub_contwow	= ohci_s3c2410_hub_contwow;

	wetuwn pwatfowm_dwivew_wegistew(&ohci_hcd_s3c2410_dwivew);
}
moduwe_init(ohci_s3c2410_init);

static void __exit ohci_s3c2410_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ohci_hcd_s3c2410_dwivew);
}
moduwe_exit(ohci_s3c2410_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:s3c2410-ohci");
