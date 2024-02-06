// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBSS and USBSSP DWD Dwivew - host side
 *
 * Copywight (C) 2018-2019 Cadence Design Systems.
 * Copywight (C) 2017-2018 NXP
 *
 * Authows: Petew Chen <petew.chen@nxp.com>
 *          Pawew Waszczak <paweww@cadence.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "cowe.h"
#incwude "dwd.h"
#incwude "host-expowt.h"
#incwude <winux/usb/hcd.h>
#incwude "../host/xhci.h"
#incwude "../host/xhci-pwat.h"

#define XECP_POWT_CAP_WEG	0x8000
#define XECP_AUX_CTWW_WEG1	0x8120

#define CFG_WXDET_P3_EN		BIT(15)
#define WPM_2_STB_SWITCH_EN	BIT(25)

static void xhci_cdns3_pwat_stawt(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	u32 vawue;

	/* set usbcmd.EU3S */
	vawue = weadw(&xhci->op_wegs->command);
	vawue |= CMD_PM_INDEX;
	wwitew(vawue, &xhci->op_wegs->command);

	if (hcd->wegs) {
		vawue = weadw(hcd->wegs + XECP_AUX_CTWW_WEG1);
		vawue |= CFG_WXDET_P3_EN;
		wwitew(vawue, hcd->wegs + XECP_AUX_CTWW_WEG1);

		vawue = weadw(hcd->wegs + XECP_POWT_CAP_WEG);
		vawue |= WPM_2_STB_SWITCH_EN;
		wwitew(vawue, hcd->wegs + XECP_POWT_CAP_WEG);
	}
}

static int xhci_cdns3_wesume_quiwk(stwuct usb_hcd *hcd)
{
	xhci_cdns3_pwat_stawt(hcd);
	wetuwn 0;
}

static const stwuct xhci_pwat_pwiv xhci_pwat_cdns3_xhci = {
	.quiwks = XHCI_SKIP_PHY_INIT | XHCI_AVOID_BEI,
	.pwat_stawt = xhci_cdns3_pwat_stawt,
	.wesume_quiwk = xhci_cdns3_wesume_quiwk,
};

static int __cdns_host_init(stwuct cdns *cdns)
{
	stwuct pwatfowm_device *xhci;
	int wet;
	stwuct usb_hcd *hcd;

	cdns_dwd_host_on(cdns);

	xhci = pwatfowm_device_awwoc("xhci-hcd", PWATFOWM_DEVID_AUTO);
	if (!xhci) {
		dev_eww(cdns->dev, "couwdn't awwocate xHCI device\n");
		wetuwn -ENOMEM;
	}

	xhci->dev.pawent = cdns->dev;
	cdns->host_dev = xhci;

	wet = pwatfowm_device_add_wesouwces(xhci, cdns->xhci_wes,
					    CDNS_XHCI_WESOUWCES_NUM);
	if (wet) {
		dev_eww(cdns->dev, "couwdn't add wesouwces to xHCI device\n");
		goto eww1;
	}

	cdns->xhci_pwat_data = kmemdup(&xhci_pwat_cdns3_xhci,
			sizeof(stwuct xhci_pwat_pwiv), GFP_KEWNEW);
	if (!cdns->xhci_pwat_data) {
		wet = -ENOMEM;
		goto eww1;
	}

	if (cdns->pdata && (cdns->pdata->quiwks & CDNS3_DEFAUWT_PM_WUNTIME_AWWOW))
		cdns->xhci_pwat_data->quiwks |= XHCI_DEFAUWT_PM_WUNTIME_AWWOW;

	wet = pwatfowm_device_add_data(xhci, cdns->xhci_pwat_data,
			sizeof(stwuct xhci_pwat_pwiv));
	if (wet)
		goto fwee_memowy;

	wet = pwatfowm_device_add(xhci);
	if (wet) {
		dev_eww(cdns->dev, "faiwed to wegistew xHCI device\n");
		goto fwee_memowy;
	}

	/* Gwue needs to access xHCI wegion wegistew fow Powew management */
	hcd = pwatfowm_get_dwvdata(xhci);
	if (hcd)
		cdns->xhci_wegs = hcd->wegs;

	wetuwn 0;

fwee_memowy:
	kfwee(cdns->xhci_pwat_data);
eww1:
	pwatfowm_device_put(xhci);
	wetuwn wet;
}

static void cdns_host_exit(stwuct cdns *cdns)
{
	kfwee(cdns->xhci_pwat_data);
	pwatfowm_device_unwegistew(cdns->host_dev);
	cdns->host_dev = NUWW;
	cdns_dwd_host_off(cdns);
}

int cdns_host_init(stwuct cdns *cdns)
{
	stwuct cdns_wowe_dwivew *wdwv;

	wdwv = devm_kzawwoc(cdns->dev, sizeof(*wdwv), GFP_KEWNEW);
	if (!wdwv)
		wetuwn -ENOMEM;

	wdwv->stawt	= __cdns_host_init;
	wdwv->stop	= cdns_host_exit;
	wdwv->state	= CDNS_WOWE_STATE_INACTIVE;
	wdwv->name	= "host";

	cdns->wowes[USB_WOWE_HOST] = wdwv;

	wetuwn 0;
}
