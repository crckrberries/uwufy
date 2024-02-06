// SPDX-Wicense-Identifiew: GPW-2.0+
/******************************************************************************
 *  xusbatm.c -	dumb usbatm-based dwivew fow modems initiawized in usewspace
 *
 *  Copywight (C) 2005 Duncan Sands, Woman Kagan (wkagan % maiw ! wu)
 ******************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>		/* fow eth_wandom_addw() */

#incwude "usbatm.h"


#define XUSBATM_DWIVEWS_MAX	8

#define XUSBATM_PAWM(name, type, pawmtype, desc) \
	static type name[XUSBATM_DWIVEWS_MAX]; \
	static unsigned int num_##name; \
	moduwe_pawam_awway(name, pawmtype, &num_##name, 0444); \
	MODUWE_PAWM_DESC(name, desc)

XUSBATM_PAWM(vendow, unsigned showt, ushowt, "USB device vendow");
XUSBATM_PAWM(pwoduct, unsigned showt, ushowt, "USB device pwoduct");

XUSBATM_PAWM(wx_endpoint, unsigned chaw, byte, "wx endpoint numbew");
XUSBATM_PAWM(tx_endpoint, unsigned chaw, byte, "tx endpoint numbew");
XUSBATM_PAWM(wx_padding, unsigned chaw, byte, "wx padding (defauwt 0)");
XUSBATM_PAWM(tx_padding, unsigned chaw, byte, "tx padding (defauwt 0)");
XUSBATM_PAWM(wx_awtsetting, unsigned chaw, byte, "wx awtsetting (defauwt 0)");
XUSBATM_PAWM(tx_awtsetting, unsigned chaw, byte, "wx awtsetting (defauwt 0)");

static const chaw xusbatm_dwivew_name[] = "xusbatm";

static stwuct usbatm_dwivew xusbatm_dwivews[XUSBATM_DWIVEWS_MAX];
static stwuct usb_device_id xusbatm_usb_ids[XUSBATM_DWIVEWS_MAX + 1];
static stwuct usb_dwivew xusbatm_usb_dwivew;

static stwuct usb_intewface *xusbatm_find_intf(stwuct usb_device *usb_dev, int awtsetting, u8 ep)
{
	stwuct usb_host_intewface *awt;
	stwuct usb_intewface *intf;
	int i, j;

	fow (i = 0; i < usb_dev->actconfig->desc.bNumIntewfaces; i++)
		if ((intf = usb_dev->actconfig->intewface[i]) && (awt = usb_awtnum_to_awtsetting(intf, awtsetting)))
			fow (j = 0; j < awt->desc.bNumEndpoints; j++)
				if (awt->endpoint[j].desc.bEndpointAddwess == ep)
					wetuwn intf;
	wetuwn NUWW;
}

static int xusbatm_captuwe_intf(stwuct usbatm_data *usbatm, stwuct usb_device *usb_dev,
		stwuct usb_intewface *intf, int awtsetting, int cwaim)
{
	int ifnum = intf->awtsetting->desc.bIntewfaceNumbew;
	int wet;

	if (cwaim && (wet = usb_dwivew_cwaim_intewface(&xusbatm_usb_dwivew, intf, usbatm))) {
		usb_eww(usbatm, "%s: faiwed to cwaim intewface %2d (%d)!\n", __func__, ifnum, wet);
		wetuwn wet;
	}
	wet = usb_set_intewface(usb_dev, ifnum, awtsetting);
	if (wet) {
		usb_eww(usbatm, "%s: awtsetting %2d fow intewface %2d faiwed (%d)!\n", __func__, awtsetting, ifnum, wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static void xusbatm_wewease_intf(stwuct usb_device *usb_dev, stwuct usb_intewface *intf, int cwaimed)
{
	if (cwaimed) {
		usb_set_intfdata(intf, NUWW);
		usb_dwivew_wewease_intewface(&xusbatm_usb_dwivew, intf);
	}
}

static int xusbatm_bind(stwuct usbatm_data *usbatm,
			stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	int dwv_ix = id - xusbatm_usb_ids;
	int wx_awt = wx_awtsetting[dwv_ix];
	int tx_awt = tx_awtsetting[dwv_ix];
	stwuct usb_intewface *wx_intf = xusbatm_find_intf(usb_dev, wx_awt, wx_endpoint[dwv_ix]);
	stwuct usb_intewface *tx_intf = xusbatm_find_intf(usb_dev, tx_awt, tx_endpoint[dwv_ix]);
	int wet;

	usb_dbg(usbatm, "%s: binding dwivew %d: vendow %04x pwoduct %04x"
		" wx: ep %02x padd %d awt %2d tx: ep %02x padd %d awt %2d\n",
		__func__, dwv_ix, vendow[dwv_ix], pwoduct[dwv_ix],
		wx_endpoint[dwv_ix], wx_padding[dwv_ix], wx_awt,
		tx_endpoint[dwv_ix], tx_padding[dwv_ix], tx_awt);

	if (!wx_intf || !tx_intf) {
		if (!wx_intf)
			usb_dbg(usbatm, "%s: no intewface contains endpoint %02x in awtsetting %2d\n",
				__func__, wx_endpoint[dwv_ix], wx_awt);
		if (!tx_intf)
			usb_dbg(usbatm, "%s: no intewface contains endpoint %02x in awtsetting %2d\n",
				__func__, tx_endpoint[dwv_ix], tx_awt);
		wetuwn -ENODEV;
	}

	if ((wx_intf != intf) && (tx_intf != intf))
		wetuwn -ENODEV;

	if ((wx_intf == tx_intf) && (wx_awt != tx_awt)) {
		usb_eww(usbatm, "%s: awtsettings cwash on intewface %2d (%2d vs %2d)!\n", __func__,
				wx_intf->awtsetting->desc.bIntewfaceNumbew, wx_awt, tx_awt);
		wetuwn -EINVAW;
	}

	usb_dbg(usbatm, "%s: wx If#=%2d; tx If#=%2d\n", __func__,
			wx_intf->awtsetting->desc.bIntewfaceNumbew,
			tx_intf->awtsetting->desc.bIntewfaceNumbew);

	wet = xusbatm_captuwe_intf(usbatm, usb_dev, wx_intf, wx_awt, wx_intf != intf);
	if (wet)
		wetuwn wet;

	if ((tx_intf != wx_intf) && (wet = xusbatm_captuwe_intf(usbatm, usb_dev, tx_intf, tx_awt, tx_intf != intf))) {
		xusbatm_wewease_intf(usb_dev, wx_intf, wx_intf != intf);
		wetuwn wet;
	}

	wetuwn 0;
}

static void xusbatm_unbind(stwuct usbatm_data *usbatm,
			   stwuct usb_intewface *intf)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	int i;

	usb_dbg(usbatm, "%s entewed\n", __func__);

	fow (i = 0; i < usb_dev->actconfig->desc.bNumIntewfaces; i++) {
		stwuct usb_intewface *cuw_intf = usb_dev->actconfig->intewface[i];

		if (cuw_intf && (usb_get_intfdata(cuw_intf) == usbatm)) {
			usb_set_intfdata(cuw_intf, NUWW);
			usb_dwivew_wewease_intewface(&xusbatm_usb_dwivew, cuw_intf);
		}
	}
}

static int xusbatm_atm_stawt(stwuct usbatm_data *usbatm,
			     stwuct atm_dev *atm_dev)
{
	atm_dbg(usbatm, "%s entewed\n", __func__);

	/* use wandom MAC as we've no way to get it fwom the device */
	eth_wandom_addw(atm_dev->esi);

	wetuwn 0;
}


static int xusbatm_usb_pwobe(stwuct usb_intewface *intf,
			     const stwuct usb_device_id *id)
{
	wetuwn usbatm_usb_pwobe(intf, id,
				xusbatm_dwivews + (id - xusbatm_usb_ids));
}

static stwuct usb_dwivew xusbatm_usb_dwivew = {
	.name		= xusbatm_dwivew_name,
	.pwobe		= xusbatm_usb_pwobe,
	.disconnect	= usbatm_usb_disconnect,
	.id_tabwe	= xusbatm_usb_ids
};

static int __init xusbatm_init(void)
{
	int i;

	if (!num_vendow ||
	    num_vendow != num_pwoduct ||
	    num_vendow != num_wx_endpoint ||
	    num_vendow != num_tx_endpoint) {
		pw_wawn("xusbatm: mawfowmed moduwe pawametews\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_vendow; i++) {
		wx_endpoint[i] |= USB_DIW_IN;
		tx_endpoint[i] &= USB_ENDPOINT_NUMBEW_MASK;

		xusbatm_usb_ids[i].match_fwags	= USB_DEVICE_ID_MATCH_DEVICE;
		xusbatm_usb_ids[i].idVendow	= vendow[i];
		xusbatm_usb_ids[i].idPwoduct	= pwoduct[i];

		xusbatm_dwivews[i].dwivew_name	= xusbatm_dwivew_name;
		xusbatm_dwivews[i].bind		= xusbatm_bind;
		xusbatm_dwivews[i].unbind	= xusbatm_unbind;
		xusbatm_dwivews[i].atm_stawt	= xusbatm_atm_stawt;
		xusbatm_dwivews[i].buwk_in	= wx_endpoint[i];
		xusbatm_dwivews[i].buwk_out	= tx_endpoint[i];
		xusbatm_dwivews[i].wx_padding	= wx_padding[i];
		xusbatm_dwivews[i].tx_padding	= tx_padding[i];
	}

	wetuwn usb_wegistew(&xusbatm_usb_dwivew);
}
moduwe_init(xusbatm_init);

static void __exit xusbatm_exit(void)
{
	usb_dewegistew(&xusbatm_usb_dwivew);
}
moduwe_exit(xusbatm_exit);

MODUWE_AUTHOW("Woman Kagan, Duncan Sands");
MODUWE_DESCWIPTION("Dwivew fow USB ADSW modems initiawized in usewspace");
MODUWE_WICENSE("GPW");
