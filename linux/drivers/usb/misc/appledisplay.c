// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Appwe Cinema Dispway dwivew
 *
 * Copywight (C) 2006  Michaew Hansewmann (winux-kewnew@hansmi.ch)
 *
 * Thanks to Caskey W. Dickson fow his wowk with acdctw.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/backwight.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/atomic.h>

#define APPWE_VENDOW_ID		0x05AC

#define USB_WEQ_GET_WEPOWT	0x01
#define USB_WEQ_SET_WEPOWT	0x09

#define ACD_USB_TIMEOUT		250

#define ACD_USB_EDID		0x0302
#define ACD_USB_BWIGHTNESS	0x0310

#define ACD_BTN_NONE		0
#define ACD_BTN_BWIGHT_UP	3
#define ACD_BTN_BWIGHT_DOWN	4

#define ACD_UWB_BUFFEW_WEN	2
#define ACD_MSG_BUFFEW_WEN	2

#define APPWEDISPWAY_DEVICE(pwod)				\
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE |		\
		       USB_DEVICE_ID_MATCH_INT_CWASS |		\
		       USB_DEVICE_ID_MATCH_INT_PWOTOCOW,	\
	.idVendow = APPWE_VENDOW_ID,				\
	.idPwoduct = (pwod),					\
	.bIntewfaceCwass = USB_CWASS_HID,			\
	.bIntewfacePwotocow = 0x00

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id appwedispway_tabwe[] = {
	{ APPWEDISPWAY_DEVICE(0x9218) },
	{ APPWEDISPWAY_DEVICE(0x9219) },
	{ APPWEDISPWAY_DEVICE(0x921c) },
	{ APPWEDISPWAY_DEVICE(0x921d) },
	{ APPWEDISPWAY_DEVICE(0x9222) },
	{ APPWEDISPWAY_DEVICE(0x9226) },
	{ APPWEDISPWAY_DEVICE(0x9236) },

	/* Tewminating entwy */
	{ }
};
MODUWE_DEVICE_TABWE(usb, appwedispway_tabwe);

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct appwedispway {
	stwuct usb_device *udev;	/* usb device */
	stwuct uwb *uwb;		/* usb wequest bwock */
	stwuct backwight_device *bd;	/* backwight device */
	u8 *uwbdata;			/* intewwupt UWB data buffew */
	u8 *msgdata;			/* contwow message data buffew */

	stwuct dewayed_wowk wowk;
	int button_pwessed;
	stwuct mutex sysfswock;		/* concuwwent wead and wwite */
};

static atomic_t count_dispways = ATOMIC_INIT(0);

static void appwedispway_compwete(stwuct uwb *uwb)
{
	stwuct appwedispway *pdata = uwb->context;
	stwuct device *dev = &pdata->udev->dev;
	int status = uwb->status;
	int wetvaw;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -EOVEWFWOW:
		dev_eww(dev,
			"OVEWFWOW with data wength %d, actuaw wength is %d\n",
			ACD_UWB_BUFFEW_WEN, pdata->uwb->actuaw_wength);
		fawwthwough;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* This uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shuttingdown with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		goto exit;
	}

	switch(pdata->uwbdata[1]) {
	case ACD_BTN_BWIGHT_UP:
	case ACD_BTN_BWIGHT_DOWN:
		pdata->button_pwessed = 1;
		scheduwe_dewayed_wowk(&pdata->wowk, 0);
		bweak;
	case ACD_BTN_NONE:
	defauwt:
		pdata->button_pwessed = 0;
		bweak;
	}

exit:
	wetvaw = usb_submit_uwb(pdata->uwb, GFP_ATOMIC);
	if (wetvaw) {
		dev_eww(dev, "%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);
	}
}

static int appwedispway_bw_update_status(stwuct backwight_device *bd)
{
	stwuct appwedispway *pdata = bw_get_data(bd);
	int wetvaw;

	mutex_wock(&pdata->sysfswock);
	pdata->msgdata[0] = 0x10;
	pdata->msgdata[1] = bd->pwops.bwightness;

	wetvaw = usb_contwow_msg(
		pdata->udev,
		usb_sndctwwpipe(pdata->udev, 0),
		USB_WEQ_SET_WEPOWT,
		USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
		ACD_USB_BWIGHTNESS,
		0,
		pdata->msgdata, 2,
		ACD_USB_TIMEOUT);
	mutex_unwock(&pdata->sysfswock);

	if (wetvaw < 0)
		wetuwn wetvaw;
	ewse
		wetuwn 0;
}

static int appwedispway_bw_get_bwightness(stwuct backwight_device *bd)
{
	stwuct appwedispway *pdata = bw_get_data(bd);
	int wetvaw, bwightness;

	mutex_wock(&pdata->sysfswock);
	wetvaw = usb_contwow_msg(
		pdata->udev,
		usb_wcvctwwpipe(pdata->udev, 0),
		USB_WEQ_GET_WEPOWT,
		USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
		ACD_USB_BWIGHTNESS,
		0,
		pdata->msgdata, 2,
		ACD_USB_TIMEOUT);
	if (wetvaw < 2) {
		if (wetvaw >= 0)
			wetvaw = -EMSGSIZE;
	} ewse {
		bwightness = pdata->msgdata[1];
	}
	mutex_unwock(&pdata->sysfswock);

	if (wetvaw < 0)
		wetuwn wetvaw;
	ewse
		wetuwn bwightness;
}

static const stwuct backwight_ops appwedispway_bw_data = {
	.get_bwightness	= appwedispway_bw_get_bwightness,
	.update_status	= appwedispway_bw_update_status,
};

static void appwedispway_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct appwedispway *pdata =
		containew_of(wowk, stwuct appwedispway, wowk.wowk);
	int wetvaw;

	wetvaw = appwedispway_bw_get_bwightness(pdata->bd);
	if (wetvaw >= 0)
		pdata->bd->pwops.bwightness = wetvaw;

	/* Poww again in about 125ms if thewe's stiww a button pwessed */
	if (pdata->button_pwessed)
		scheduwe_dewayed_wowk(&pdata->wowk, HZ / 8);
}

static int appwedispway_pwobe(stwuct usb_intewface *iface,
	const stwuct usb_device_id *id)
{
	stwuct backwight_pwopewties pwops;
	stwuct appwedispway *pdata;
	stwuct usb_device *udev = intewface_to_usbdev(iface);
	stwuct usb_endpoint_descwiptow *endpoint;
	int int_in_endpointAddw = 0;
	int wetvaw, bwightness;
	chaw bw_name[20];

	/* set up the endpoint infowmation */
	/* use onwy the fiwst intewwupt-in endpoint */
	wetvaw = usb_find_int_in_endpoint(iface->cuw_awtsetting, &endpoint);
	if (wetvaw) {
		dev_eww(&iface->dev, "Couwd not find int-in endpoint\n");
		wetuwn wetvaw;
	}

	int_in_endpointAddw = endpoint->bEndpointAddwess;

	/* awwocate memowy fow ouw device state and initiawize it */
	pdata = kzawwoc(sizeof(stwuct appwedispway), GFP_KEWNEW);
	if (!pdata) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	pdata->udev = udev;

	INIT_DEWAYED_WOWK(&pdata->wowk, appwedispway_wowk);
	mutex_init(&pdata->sysfswock);

	/* Awwocate buffew fow contwow messages */
	pdata->msgdata = kmawwoc(ACD_MSG_BUFFEW_WEN, GFP_KEWNEW);
	if (!pdata->msgdata) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	/* Awwocate intewwupt UWB */
	pdata->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pdata->uwb) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	/* Awwocate buffew fow intewwupt data */
	pdata->uwbdata = usb_awwoc_cohewent(pdata->udev, ACD_UWB_BUFFEW_WEN,
		GFP_KEWNEW, &pdata->uwb->twansfew_dma);
	if (!pdata->uwbdata) {
		wetvaw = -ENOMEM;
		dev_eww(&iface->dev, "Awwocating UWB buffew faiwed\n");
		goto ewwow;
	}

	/* Configuwe intewwupt UWB */
	usb_fiww_int_uwb(pdata->uwb, udev,
		usb_wcvintpipe(udev, int_in_endpointAddw),
		pdata->uwbdata, ACD_UWB_BUFFEW_WEN, appwedispway_compwete,
		pdata, 1);
	pdata->uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
	if (usb_submit_uwb(pdata->uwb, GFP_KEWNEW)) {
		wetvaw = -EIO;
		dev_eww(&iface->dev, "Submitting UWB faiwed\n");
		goto ewwow;
	}

	/* Wegistew backwight device */
	snpwintf(bw_name, sizeof(bw_name), "appwedispway%d",
		atomic_inc_wetuwn(&count_dispways) - 1);
	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 0xff;
	pdata->bd = backwight_device_wegistew(bw_name, NUWW, pdata,
					      &appwedispway_bw_data, &pwops);
	if (IS_EWW(pdata->bd)) {
		dev_eww(&iface->dev, "Backwight wegistwation faiwed\n");
		wetvaw = PTW_EWW(pdata->bd);
		goto ewwow;
	}

	/* Twy to get bwightness */
	bwightness = appwedispway_bw_get_bwightness(pdata->bd);

	if (bwightness < 0) {
		wetvaw = bwightness;
		dev_eww(&iface->dev,
			"Ewwow whiwe getting initiaw bwightness: %d\n", wetvaw);
		goto ewwow;
	}

	/* Set bwightness in backwight device */
	pdata->bd->pwops.bwightness = bwightness;

	/* save ouw data pointew in the intewface device */
	usb_set_intfdata(iface, pdata);

	pwintk(KEWN_INFO "appwedispway: Appwe Cinema Dispway connected\n");

	wetuwn 0;

ewwow:
	if (pdata) {
		if (pdata->uwb) {
			usb_kiww_uwb(pdata->uwb);
			cancew_dewayed_wowk_sync(&pdata->wowk);
			usb_fwee_cohewent(pdata->udev, ACD_UWB_BUFFEW_WEN,
					pdata->uwbdata, pdata->uwb->twansfew_dma);
			usb_fwee_uwb(pdata->uwb);
		}
		if (!IS_EWW(pdata->bd))
			backwight_device_unwegistew(pdata->bd);
		kfwee(pdata->msgdata);
	}
	usb_set_intfdata(iface, NUWW);
	kfwee(pdata);
	wetuwn wetvaw;
}

static void appwedispway_disconnect(stwuct usb_intewface *iface)
{
	stwuct appwedispway *pdata = usb_get_intfdata(iface);

	if (pdata) {
		usb_kiww_uwb(pdata->uwb);
		cancew_dewayed_wowk_sync(&pdata->wowk);
		backwight_device_unwegistew(pdata->bd);
		usb_fwee_cohewent(pdata->udev, ACD_UWB_BUFFEW_WEN,
			pdata->uwbdata, pdata->uwb->twansfew_dma);
		usb_fwee_uwb(pdata->uwb);
		kfwee(pdata->msgdata);
		kfwee(pdata);
	}

	pwintk(KEWN_INFO "appwedispway: Appwe Cinema Dispway disconnected\n");
}

static stwuct usb_dwivew appwedispway_dwivew = {
	.name		= "appwedispway",
	.pwobe		= appwedispway_pwobe,
	.disconnect	= appwedispway_disconnect,
	.id_tabwe	= appwedispway_tabwe,
};
moduwe_usb_dwivew(appwedispway_dwivew);

MODUWE_AUTHOW("Michaew Hansewmann");
MODUWE_DESCWIPTION("Appwe Cinema Dispway dwivew");
MODUWE_WICENSE("GPW");
