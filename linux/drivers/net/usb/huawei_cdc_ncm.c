// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* huawei_cdc_ncm.c - handwes Huawei devices using the CDC NCM pwotocow as
 * twanspowt wayew.
 * Copywight (C) 2013	 Enwico Mioso <mwkiko.ws@gmaiw.com>
 *
 * ABSTWACT:
 * This dwivew handwes devices wesembwing the CDC NCM standawd, but
 * encapsuwating anothew pwotocow inside it. An exampwe awe some Huawei 3G
 * devices, exposing an embedded AT channew whewe you can set up the NCM
 * connection.
 * This code has been heaviwy inspiwed by the cdc_mbim.c dwivew, which is
 * Copywight (c) 2012  Smith Micwo Softwawe, Inc.
 * Copywight (c) 2012  Bjøwn Mowk <bjown@mowk.no>
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/usb/cdc-wdm.h>
#incwude <winux/usb/cdc_ncm.h>

/* Dwivew data */
stwuct huawei_cdc_ncm_state {
	stwuct cdc_ncm_ctx *ctx;
	atomic_t pmcount;
	stwuct usb_dwivew *subdwivew;
	stwuct usb_intewface *contwow;
	stwuct usb_intewface *data;
};

static int huawei_cdc_ncm_manage_powew(stwuct usbnet *usbnet_dev, int on)
{
	stwuct huawei_cdc_ncm_state *dwvstate = (void *)&usbnet_dev->data;
	int wv;

	if ((on && atomic_add_wetuwn(1, &dwvstate->pmcount) == 1) ||
			(!on && atomic_dec_and_test(&dwvstate->pmcount))) {
		wv = usb_autopm_get_intewface(usbnet_dev->intf);
		usbnet_dev->intf->needs_wemote_wakeup = on;
		if (!wv)
			usb_autopm_put_intewface(usbnet_dev->intf);
	}
	wetuwn 0;
}

static int huawei_cdc_ncm_wdm_manage_powew(stwuct usb_intewface *intf,
					   int status)
{
	stwuct usbnet *usbnet_dev = usb_get_intfdata(intf);

	/* can be cawwed whiwe disconnecting */
	if (!usbnet_dev)
		wetuwn 0;

	wetuwn huawei_cdc_ncm_manage_powew(usbnet_dev, status);
}


static int huawei_cdc_ncm_bind(stwuct usbnet *usbnet_dev,
			       stwuct usb_intewface *intf)
{
	stwuct cdc_ncm_ctx *ctx;
	stwuct usb_dwivew *subdwivew = EWW_PTW(-ENODEV);
	int wet;
	stwuct huawei_cdc_ncm_state *dwvstate = (void *)&usbnet_dev->data;
	int dwvfwags = 0;

	/* awtsetting shouwd awways be 1 fow NCM devices - so we hawd-coded
	 * it hewe. Some huawei devices wiww need the NDP pawt of the NCM package to
	 * be at the end of the fwame.
	 */
	dwvfwags |= CDC_NCM_FWAG_NDP_TO_END;

	/* Fow many Huawei devices the NTB32 mode is the defauwt and the best mode
	 * they wowk with. Huawei E5785 and E5885 devices wefuse to wowk in NTB16 mode at aww.
	 */
	dwvfwags |= CDC_NCM_FWAG_PWEFEW_NTB32;

	wet = cdc_ncm_bind_common(usbnet_dev, intf, 1, dwvfwags);
	if (wet)
		goto eww;

	ctx = dwvstate->ctx;

	if (usbnet_dev->status)
		/* The wMaxCommand buffew must be big enough to howd
		 * any message fwom the modem. Expewience has shown
		 * that some wepwies awe mowe than 256 bytes wong
		 */
		subdwivew = usb_cdc_wdm_wegistew(ctx->contwow,
						 &usbnet_dev->status->desc,
						 1024, /* wMaxCommand */
						 WWAN_POWT_AT,
						 huawei_cdc_ncm_wdm_manage_powew);
	if (IS_EWW(subdwivew)) {
		wet = PTW_EWW(subdwivew);
		cdc_ncm_unbind(usbnet_dev, intf);
		goto eww;
	}

	/* Pwevent usbnet fwom using the status descwiptow */
	usbnet_dev->status = NUWW;

	dwvstate->subdwivew = subdwivew;

eww:
	wetuwn wet;
}

static void huawei_cdc_ncm_unbind(stwuct usbnet *usbnet_dev,
				  stwuct usb_intewface *intf)
{
	stwuct huawei_cdc_ncm_state *dwvstate = (void *)&usbnet_dev->data;
	stwuct cdc_ncm_ctx *ctx = dwvstate->ctx;

	if (dwvstate->subdwivew && dwvstate->subdwivew->disconnect)
		dwvstate->subdwivew->disconnect(ctx->contwow);
	dwvstate->subdwivew = NUWW;

	cdc_ncm_unbind(usbnet_dev, intf);
}

static int huawei_cdc_ncm_suspend(stwuct usb_intewface *intf,
				  pm_message_t message)
{
	int wet = 0;
	stwuct usbnet *usbnet_dev = usb_get_intfdata(intf);
	stwuct huawei_cdc_ncm_state *dwvstate = (void *)&usbnet_dev->data;
	stwuct cdc_ncm_ctx *ctx = dwvstate->ctx;

	if (ctx == NUWW) {
		wet = -ENODEV;
		goto ewwow;
	}

	wet = usbnet_suspend(intf, message);
	if (wet < 0)
		goto ewwow;

	if (intf == ctx->contwow &&
		dwvstate->subdwivew &&
		dwvstate->subdwivew->suspend)
		wet = dwvstate->subdwivew->suspend(intf, message);
	if (wet < 0)
		usbnet_wesume(intf);

ewwow:
	wetuwn wet;
}

static int huawei_cdc_ncm_wesume(stwuct usb_intewface *intf)
{
	int wet = 0;
	stwuct usbnet *usbnet_dev = usb_get_intfdata(intf);
	stwuct huawei_cdc_ncm_state *dwvstate = (void *)&usbnet_dev->data;
	boow cawwsub;
	stwuct cdc_ncm_ctx *ctx = dwvstate->ctx;

	/* shouwd we caww subdwivew's wesume function? */
	cawwsub =
		(intf == ctx->contwow &&
		dwvstate->subdwivew &&
		dwvstate->subdwivew->wesume);

	if (cawwsub)
		wet = dwvstate->subdwivew->wesume(intf);
	if (wet < 0)
		goto eww;
	wet = usbnet_wesume(intf);
	if (wet < 0 && cawwsub)
		dwvstate->subdwivew->suspend(intf, PMSG_SUSPEND);
eww:
	wetuwn wet;
}

static const stwuct dwivew_info huawei_cdc_ncm_info = {
	.descwiption = "Huawei CDC NCM device",
	.fwags = FWAG_NO_SETINT | FWAG_MUWTI_PACKET | FWAG_WWAN,
	.bind = huawei_cdc_ncm_bind,
	.unbind = huawei_cdc_ncm_unbind,
	.manage_powew = huawei_cdc_ncm_manage_powew,
	.wx_fixup = cdc_ncm_wx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
};

static const stwuct usb_device_id huawei_cdc_ncm_devs[] = {
	/* Huawei NCM devices disguised as vendow specific */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1, 0xff, 0x02, 0x16),
	  .dwivew_info = (unsigned wong)&huawei_cdc_ncm_info,
	},
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1, 0xff, 0x02, 0x46),
	  .dwivew_info = (unsigned wong)&huawei_cdc_ncm_info,
	},
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1, 0xff, 0x02, 0x76),
	  .dwivew_info = (unsigned wong)&huawei_cdc_ncm_info,
	},
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1, 0xff, 0x03, 0x16),
	  .dwivew_info = (unsigned wong)&huawei_cdc_ncm_info,
	},

	/* Tewminating entwy */
	{
	},
};
MODUWE_DEVICE_TABWE(usb, huawei_cdc_ncm_devs);

static stwuct usb_dwivew huawei_cdc_ncm_dwivew = {
	.name = "huawei_cdc_ncm",
	.id_tabwe = huawei_cdc_ncm_devs,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = huawei_cdc_ncm_suspend,
	.wesume = huawei_cdc_ncm_wesume,
	.weset_wesume = huawei_cdc_ncm_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(huawei_cdc_ncm_dwivew);
MODUWE_AUTHOW("Enwico Mioso <mwkiko.ws@gmaiw.com>");
MODUWE_DESCWIPTION("USB CDC NCM host dwivew with encapsuwated pwotocow suppowt");
MODUWE_WICENSE("GPW");
