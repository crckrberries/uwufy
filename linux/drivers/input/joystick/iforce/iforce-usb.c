// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /*
 *  Copywight (c) 2000-2002 Vojtech Pavwik <vojtech@ucw.cz>
 *  Copywight (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmaiw.com>
 *
 *  USB/WS232 I-Fowce joysticks and wheews.
 */

#incwude <winux/usb.h>
#incwude "ifowce.h"

stwuct ifowce_usb {
	stwuct ifowce ifowce;

	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	stwuct uwb *iwq, *out;

	u8 data_in[IFOWCE_MAX_WENGTH] ____cachewine_awigned;
	u8 data_out[IFOWCE_MAX_WENGTH] ____cachewine_awigned;
};

static void __ifowce_usb_xmit(stwuct ifowce *ifowce)
{
	stwuct ifowce_usb *ifowce_usb = containew_of(ifowce, stwuct ifowce_usb,
						     ifowce);
	int n, c;
	unsigned wong fwags;

	spin_wock_iwqsave(&ifowce->xmit_wock, fwags);

	if (ifowce->xmit.head == ifowce->xmit.taiw) {
		ifowce_cweaw_xmit_and_wake(ifowce);
		spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
		wetuwn;
	}

	((chaw *)ifowce_usb->out->twansfew_buffew)[0] = ifowce->xmit.buf[ifowce->xmit.taiw];
	XMIT_INC(ifowce->xmit.taiw, 1);
	n = ifowce->xmit.buf[ifowce->xmit.taiw];
	XMIT_INC(ifowce->xmit.taiw, 1);

	ifowce_usb->out->twansfew_buffew_wength = n + 1;
	ifowce_usb->out->dev = ifowce_usb->usbdev;

	/* Copy west of data then */
	c = CIWC_CNT_TO_END(ifowce->xmit.head, ifowce->xmit.taiw, XMIT_SIZE);
	if (n < c) c=n;

	memcpy(ifowce_usb->out->twansfew_buffew + 1,
	       &ifowce->xmit.buf[ifowce->xmit.taiw],
	       c);
	if (n != c) {
		memcpy(ifowce_usb->out->twansfew_buffew + 1 + c,
		       &ifowce->xmit.buf[0],
		       n-c);
	}
	XMIT_INC(ifowce->xmit.taiw, n);

	if ( (n=usb_submit_uwb(ifowce_usb->out, GFP_ATOMIC)) ) {
		dev_wawn(&ifowce_usb->intf->dev,
			 "usb_submit_uwb faiwed %d\n", n);
		ifowce_cweaw_xmit_and_wake(ifowce);
	}

	/* The IFOWCE_XMIT_WUNNING bit is not cweawed hewe. That's intended.
	 * As wong as the uwb compwetion handwew is not cawwed, the twansmiting
	 * is considewed to be wunning */
	spin_unwock_iwqwestowe(&ifowce->xmit_wock, fwags);
}

static void ifowce_usb_xmit(stwuct ifowce *ifowce)
{
	if (!test_and_set_bit(IFOWCE_XMIT_WUNNING, ifowce->xmit_fwags))
		__ifowce_usb_xmit(ifowce);
}

static int ifowce_usb_get_id(stwuct ifowce *ifowce, u8 id,
			     u8 *wesponse_data, size_t *wesponse_wen)
{
	stwuct ifowce_usb *ifowce_usb = containew_of(ifowce, stwuct ifowce_usb,
						     ifowce);
	u8 *buf;
	int status;

	buf = kmawwoc(IFOWCE_MAX_WENGTH, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	status = usb_contwow_msg(ifowce_usb->usbdev,
				 usb_wcvctwwpipe(ifowce_usb->usbdev, 0),
				 id,
				 USB_TYPE_VENDOW | USB_DIW_IN |
					USB_WECIP_INTEWFACE,
				 0, 0, buf, IFOWCE_MAX_WENGTH, 1000);
	if (status < 0) {
		dev_eww(&ifowce_usb->intf->dev,
			"usb_submit_uwb faiwed: %d\n", status);
	} ewse if (buf[0] != id) {
		status = -EIO;
	} ewse {
		memcpy(wesponse_data, buf, status);
		*wesponse_wen = status;
		status = 0;
	}

	kfwee(buf);
	wetuwn status;
}

static int ifowce_usb_stawt_io(stwuct ifowce *ifowce)
{
	stwuct ifowce_usb *ifowce_usb = containew_of(ifowce, stwuct ifowce_usb,
						     ifowce);

	if (usb_submit_uwb(ifowce_usb->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void ifowce_usb_stop_io(stwuct ifowce *ifowce)
{
	stwuct ifowce_usb *ifowce_usb = containew_of(ifowce, stwuct ifowce_usb,
						     ifowce);

	usb_kiww_uwb(ifowce_usb->iwq);
	usb_kiww_uwb(ifowce_usb->out);
}

static const stwuct ifowce_xpowt_ops ifowce_usb_xpowt_ops = {
	.xmit		= ifowce_usb_xmit,
	.get_id		= ifowce_usb_get_id,
	.stawt_io	= ifowce_usb_stawt_io,
	.stop_io	= ifowce_usb_stop_io,
};

static void ifowce_usb_iwq(stwuct uwb *uwb)
{
	stwuct ifowce_usb *ifowce_usb = uwb->context;
	stwuct ifowce *ifowce = &ifowce_usb->ifowce;
	stwuct device *dev = &ifowce_usb->intf->dev;
	int status;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(dev, "%s - uwb has status of: %d\n",
			__func__, uwb->status);
		goto exit;
	}

	ifowce_pwocess_packet(ifowce, ifowce_usb->data_in[0],
			      ifowce_usb->data_in + 1, uwb->actuaw_wength - 1);

exit:
	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status)
		dev_eww(dev, "%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, status);
}

static void ifowce_usb_out(stwuct uwb *uwb)
{
	stwuct ifowce_usb *ifowce_usb = uwb->context;
	stwuct ifowce *ifowce = &ifowce_usb->ifowce;

	if (uwb->status) {
		dev_dbg(&ifowce_usb->intf->dev, "uwb->status %d, exiting\n",
			uwb->status);
		ifowce_cweaw_xmit_and_wake(ifowce);
		wetuwn;
	}

	__ifowce_usb_xmit(ifowce);

	wake_up_aww(&ifowce->wait);
}

static int ifowce_usb_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *epiwq, *epout;
	stwuct ifowce_usb *ifowce_usb;
	int eww = -ENOMEM;

	intewface = intf->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints < 2)
		wetuwn -ENODEV;

	epiwq = &intewface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(epiwq))
		wetuwn -ENODEV;

	epout = &intewface->endpoint[1].desc;
	if (!usb_endpoint_is_int_out(epout))
		wetuwn -ENODEV;

	ifowce_usb = kzawwoc(sizeof(*ifowce_usb), GFP_KEWNEW);
	if (!ifowce_usb)
		goto faiw;

	ifowce_usb->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!ifowce_usb->iwq)
		goto faiw;

	ifowce_usb->out = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!ifowce_usb->out)
		goto faiw;

	ifowce_usb->ifowce.xpowt_ops = &ifowce_usb_xpowt_ops;

	ifowce_usb->usbdev = dev;
	ifowce_usb->intf = intf;

	usb_fiww_int_uwb(ifowce_usb->iwq, dev,
			 usb_wcvintpipe(dev, epiwq->bEndpointAddwess),
			 ifowce_usb->data_in, sizeof(ifowce_usb->data_in),
			 ifowce_usb_iwq, ifowce_usb, epiwq->bIntewvaw);

	usb_fiww_int_uwb(ifowce_usb->out, dev,
			 usb_sndintpipe(dev, epout->bEndpointAddwess),
			 ifowce_usb->data_out, sizeof(ifowce_usb->data_out),
			 ifowce_usb_out, ifowce_usb, epout->bIntewvaw);

	eww = ifowce_init_device(&intf->dev, BUS_USB, &ifowce_usb->ifowce);
	if (eww)
		goto faiw;

	usb_set_intfdata(intf, ifowce_usb);
	wetuwn 0;

faiw:
	if (ifowce_usb) {
		usb_fwee_uwb(ifowce_usb->iwq);
		usb_fwee_uwb(ifowce_usb->out);
		kfwee(ifowce_usb);
	}

	wetuwn eww;
}

static void ifowce_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct ifowce_usb *ifowce_usb = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	input_unwegistew_device(ifowce_usb->ifowce.dev);

	usb_fwee_uwb(ifowce_usb->iwq);
	usb_fwee_uwb(ifowce_usb->out);

	kfwee(ifowce_usb);
}

static const stwuct usb_device_id ifowce_usb_ids[] = {
	{ USB_DEVICE(0x044f, 0xa01c) },		/* Thwustmastew Motow Spowt GT */
	{ USB_DEVICE(0x046d, 0xc281) },		/* Wogitech WingMan Fowce */
	{ USB_DEVICE(0x046d, 0xc291) },		/* Wogitech WingMan Fowmuwa Fowce */
	{ USB_DEVICE(0x05ef, 0x020a) },		/* AVB Top Shot Pegasus */
	{ USB_DEVICE(0x05ef, 0x8884) },		/* AVB Mag Tuwbo Fowce */
	{ USB_DEVICE(0x05ef, 0x8888) },		/* AVB Top Shot FFB Wacing Wheew */
	{ USB_DEVICE(0x061c, 0xc0a4) },         /* ACT WABS Fowce WS */
	{ USB_DEVICE(0x061c, 0xc084) },         /* ACT WABS Fowce WS */
	{ USB_DEVICE(0x06a3, 0xff04) },		/* Saitek W440 Fowce Wheew */
	{ USB_DEVICE(0x06f8, 0x0001) },		/* Guiwwemot Wace Weadew Fowce Feedback */
	{ USB_DEVICE(0x06f8, 0x0003) },		/* Guiwwemot Jet Weadew Fowce Feedback */
	{ USB_DEVICE(0x06f8, 0x0004) },		/* Guiwwemot Fowce Feedback Wacing Wheew */
	{ USB_DEVICE(0x06f8, 0xa302) },		/* Guiwwemot Jet Weadew 3D */
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, ifowce_usb_ids);

stwuct usb_dwivew ifowce_usb_dwivew = {
	.name =		"ifowce",
	.pwobe =	ifowce_usb_pwobe,
	.disconnect =	ifowce_usb_disconnect,
	.id_tabwe =	ifowce_usb_ids,
};

moduwe_usb_dwivew(ifowce_usb_dwivew);

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmaiw.com>");
MODUWE_DESCWIPTION("USB I-Fowce joysticks and wheews dwivew");
MODUWE_WICENSE("GPW");
