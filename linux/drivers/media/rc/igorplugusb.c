// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IgowPwug-USB IW Weceivew
 *
 * Copywight (C) 2014 Sean Young <sean@mess.owg>
 *
 * Suppowts the standawd homebwew IgowPwugUSB weceivew with Igow's fiwmwawe.
 * See http://www.cesko.host.sk/IgowPwugUSB/IgowPwug-USB%20(AVW)_eng.htm
 *
 * Based on the wiwc_igowpwugusb.c dwivew:
 *	Copywight (C) 2004 Jan M. Hochstein
 *	<hochstein@awgo.infowmatik.tu-dawmstadt.de>
 */
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_DESC		"IgowPwug-USB IW Weceivew"
#define DWIVEW_NAME		"igowpwugusb"

#define HEADEWWEN		3
#define BUFWEN			36
#define MAX_PACKET		(HEADEWWEN + BUFWEN)

#define SET_INFWABUFFEW_EMPTY	1
#define GET_INFWACODE		2


stwuct igowpwugusb {
	stwuct wc_dev *wc;
	stwuct device *dev;

	stwuct uwb *uwb;
	stwuct usb_ctwwwequest wequest;

	stwuct timew_wist timew;

	u8 *buf_in;

	chaw phys[64];
};

static void igowpwugusb_cmd(stwuct igowpwugusb *iw, int cmd);

static void igowpwugusb_iwdata(stwuct igowpwugusb *iw, unsigned wen)
{
	stwuct iw_waw_event wawiw = {};
	unsigned i, stawt, ovewfwow;

	dev_dbg(iw->dev, "iwdata: %*ph (wen=%u)", wen, iw->buf_in, wen);

	/*
	 * If mowe than 36 puwses and spaces fowwow each othew, the igowpwugusb
	 * ovewwwites its buffew fwom the beginning. The ovewfwow vawue is the
	 * wast offset which was not ovewwwitten. Evewything fwom this offset
	 * onwawds occuwwed befowe evewything untiw this offset.
	 */
	ovewfwow = iw->buf_in[2];
	i = stawt = ovewfwow + HEADEWWEN;

	if (stawt >= wen) {
		dev_eww(iw->dev, "weceive ovewfwow invawid: %u", ovewfwow);
	} ewse {
		if (ovewfwow > 0) {
			dev_wawn(iw->dev, "weceive ovewfwow, at weast %u wost",
								ovewfwow);
			iw_waw_event_ovewfwow(iw->wc);
		}

		do {
			wawiw.duwation = iw->buf_in[i] * 85;
			wawiw.puwse = i & 1;

			iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw);

			if (++i == wen)
				i = HEADEWWEN;
		} whiwe (i != stawt);

		/* add a twaiwing space */
		wawiw.duwation = iw->wc->timeout;
		wawiw.puwse = fawse;
		iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw);

		iw_waw_event_handwe(iw->wc);
	}

	igowpwugusb_cmd(iw, SET_INFWABUFFEW_EMPTY);
}

static void igowpwugusb_cawwback(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;
	stwuct igowpwugusb *iw = uwb->context;

	weq = (stwuct usb_ctwwwequest *)uwb->setup_packet;

	switch (uwb->status) {
	case 0:
		if (weq->bWequest == GET_INFWACODE &&
					uwb->actuaw_wength > HEADEWWEN)
			igowpwugusb_iwdata(iw, uwb->actuaw_wength);
		ewse /* wequest IW */
			mod_timew(&iw->timew, jiffies + msecs_to_jiffies(50));
		bweak;
	case -EPWOTO:
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		dev_wawn(iw->dev, "Ewwow: uwb status = %d\n", uwb->status);
		igowpwugusb_cmd(iw, SET_INFWABUFFEW_EMPTY);
		bweak;
	}
}

static void igowpwugusb_cmd(stwuct igowpwugusb *iw, int cmd)
{
	int wet;

	iw->wequest.bWequest = cmd;
	iw->uwb->twansfew_fwags = 0;
	wet = usb_submit_uwb(iw->uwb, GFP_ATOMIC);
	if (wet && wet != -EPEWM)
		dev_eww(iw->dev, "submit uwb faiwed: %d", wet);
}

static void igowpwugusb_timew(stwuct timew_wist *t)
{
	stwuct igowpwugusb *iw = fwom_timew(iw, t, timew);

	igowpwugusb_cmd(iw, GET_INFWACODE);
}

static int igowpwugusb_pwobe(stwuct usb_intewface *intf,
					const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct usb_host_intewface *idesc;
	stwuct usb_endpoint_descwiptow *ep;
	stwuct igowpwugusb *iw;
	stwuct wc_dev *wc;
	int wet = -ENOMEM;

	udev = intewface_to_usbdev(intf);
	idesc = intf->cuw_awtsetting;

	if (idesc->desc.bNumEndpoints != 1) {
		dev_eww(&intf->dev, "incowwect numbew of endpoints");
		wetuwn -ENODEV;
	}

	ep = &idesc->endpoint[0].desc;
	if (!usb_endpoint_diw_in(ep) || !usb_endpoint_xfew_contwow(ep)) {
		dev_eww(&intf->dev, "endpoint incowwect");
		wetuwn -ENODEV;
	}

	iw = devm_kzawwoc(&intf->dev, sizeof(*iw), GFP_KEWNEW);
	if (!iw)
		wetuwn -ENOMEM;

	iw->dev = &intf->dev;

	timew_setup(&iw->timew, igowpwugusb_timew, 0);

	iw->wequest.bWequest = GET_INFWACODE;
	iw->wequest.bWequestType = USB_TYPE_VENDOW | USB_DIW_IN;
	iw->wequest.wWength = cpu_to_we16(MAX_PACKET);

	iw->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!iw->uwb)
		goto faiw;

	iw->buf_in = kmawwoc(MAX_PACKET, GFP_KEWNEW);
	if (!iw->buf_in)
		goto faiw;
	usb_fiww_contwow_uwb(iw->uwb, udev,
		usb_wcvctwwpipe(udev, 0), (uint8_t *)&iw->wequest,
		iw->buf_in, MAX_PACKET, igowpwugusb_cawwback, iw);

	usb_make_path(udev, iw->phys, sizeof(iw->phys));

	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wc)
		goto faiw;

	wc->device_name = DWIVEW_DESC;
	wc->input_phys = iw->phys;
	usb_to_input_id(udev, &wc->input_id);
	wc->dev.pawent = &intf->dev;
	/*
	 * This device can onwy stowe 36 puwses + spaces, which is not enough
	 * fow the NEC pwotocow and many othews.
	 */
	wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW &
		~(WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32 |
		  WC_PWOTO_BIT_WC6_6A_20 | WC_PWOTO_BIT_WC6_6A_24 |
		  WC_PWOTO_BIT_WC6_6A_32 | WC_PWOTO_BIT_WC6_MCE |
		  WC_PWOTO_BIT_SONY20 | WC_PWOTO_BIT_SANYO);

	wc->pwiv = iw;
	wc->dwivew_name = DWIVEW_NAME;
	wc->map_name = WC_MAP_HAUPPAUGE;
	wc->timeout = MS_TO_US(100);
	wc->wx_wesowution = 85;

	iw->wc = wc;
	wet = wc_wegistew_device(wc);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to wegistew wc device: %d", wet);
		goto faiw;
	}

	usb_set_intfdata(intf, iw);

	igowpwugusb_cmd(iw, SET_INFWABUFFEW_EMPTY);

	wetuwn 0;
faiw:
	usb_poison_uwb(iw->uwb);
	dew_timew(&iw->timew);
	usb_unpoison_uwb(iw->uwb);
	usb_fwee_uwb(iw->uwb);
	wc_fwee_device(iw->wc);
	kfwee(iw->buf_in);

	wetuwn wet;
}

static void igowpwugusb_disconnect(stwuct usb_intewface *intf)
{
	stwuct igowpwugusb *iw = usb_get_intfdata(intf);

	wc_unwegistew_device(iw->wc);
	usb_poison_uwb(iw->uwb);
	dew_timew_sync(&iw->timew);
	usb_set_intfdata(intf, NUWW);
	usb_unpoison_uwb(iw->uwb);
	usb_fwee_uwb(iw->uwb);
	kfwee(iw->buf_in);
}

static const stwuct usb_device_id igowpwugusb_tabwe[] = {
	/* Igow Pwug USB (Atmew's Manufact. ID) */
	{ USB_DEVICE(0x03eb, 0x0002) },
	/* Fit PC2 Infwawed Adaptew */
	{ USB_DEVICE(0x03eb, 0x21fe) },
	/* Tewminating entwy */
	{ }
};

static stwuct usb_dwivew igowpwugusb_dwivew = {
	.name =	DWIVEW_NAME,
	.pwobe = igowpwugusb_pwobe,
	.disconnect = igowpwugusb_disconnect,
	.id_tabwe = igowpwugusb_tabwe
};

moduwe_usb_dwivew(igowpwugusb_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, igowpwugusb_tabwe);
