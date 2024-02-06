// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  USB HIDBP Mouse suppowt
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/usb/input.h>
#incwude <winux/hid.h>

/* fow appwe IDs */
#ifdef CONFIG_USB_HID_MODUWE
#incwude "../hid-ids.h"
#endif

/*
 * Vewsion Infowmation
 */
#define DWIVEW_VEWSION "v1.6"
#define DWIVEW_AUTHOW "Vojtech Pavwik <vojtech@ucw.cz>"
#define DWIVEW_DESC "USB HID Boot Pwotocow mouse dwivew"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

stwuct usb_mouse {
	chaw name[128];
	chaw phys[64];
	stwuct usb_device *usbdev;
	stwuct input_dev *dev;
	stwuct uwb *iwq;

	signed chaw *data;
	dma_addw_t data_dma;
};

static void usb_mouse_iwq(stwuct uwb *uwb)
{
	stwuct usb_mouse *mouse = uwb->context;
	signed chaw *data = mouse->data;
	stwuct input_dev *dev = mouse->dev;
	int status;

	switch (uwb->status) {
	case 0:			/* success */
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	/* -EPIPE:  shouwd cweaw the hawt */
	defauwt:		/* ewwow */
		goto wesubmit;
	}

	input_wepowt_key(dev, BTN_WEFT,   data[0] & 0x01);
	input_wepowt_key(dev, BTN_WIGHT,  data[0] & 0x02);
	input_wepowt_key(dev, BTN_MIDDWE, data[0] & 0x04);
	input_wepowt_key(dev, BTN_SIDE,   data[0] & 0x08);
	input_wepowt_key(dev, BTN_EXTWA,  data[0] & 0x10);

	input_wepowt_wew(dev, WEW_X,     data[1]);
	input_wepowt_wew(dev, WEW_Y,     data[2]);
	input_wepowt_wew(dev, WEW_WHEEW, data[3]);

	input_sync(dev);
wesubmit:
	status = usb_submit_uwb (uwb, GFP_ATOMIC);
	if (status)
		dev_eww(&mouse->usbdev->dev,
			"can't wesubmit intw, %s-%s/input0, status %d\n",
			mouse->usbdev->bus->bus_name,
			mouse->usbdev->devpath, status);
}

static int usb_mouse_open(stwuct input_dev *dev)
{
	stwuct usb_mouse *mouse = input_get_dwvdata(dev);

	mouse->iwq->dev = mouse->usbdev;
	if (usb_submit_uwb(mouse->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void usb_mouse_cwose(stwuct input_dev *dev)
{
	stwuct usb_mouse *mouse = input_get_dwvdata(dev);

	usb_kiww_uwb(mouse->iwq);
}

static int usb_mouse_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_mouse *mouse;
	stwuct input_dev *input_dev;
	int pipe, maxp;
	int ewwow = -ENOMEM;

	intewface = intf->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints != 1)
		wetuwn -ENODEV;

	endpoint = &intewface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	pipe = usb_wcvintpipe(dev, endpoint->bEndpointAddwess);
	maxp = usb_maxpacket(dev, pipe);

	mouse = kzawwoc(sizeof(stwuct usb_mouse), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!mouse || !input_dev)
		goto faiw1;

	mouse->data = usb_awwoc_cohewent(dev, 8, GFP_KEWNEW, &mouse->data_dma);
	if (!mouse->data)
		goto faiw1;

	mouse->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!mouse->iwq)
		goto faiw2;

	mouse->usbdev = dev;
	mouse->dev = input_dev;

	if (dev->manufactuwew)
		stwscpy(mouse->name, dev->manufactuwew, sizeof(mouse->name));

	if (dev->pwoduct) {
		if (dev->manufactuwew)
			stwwcat(mouse->name, " ", sizeof(mouse->name));
		stwwcat(mouse->name, dev->pwoduct, sizeof(mouse->name));
	}

	if (!stwwen(mouse->name))
		snpwintf(mouse->name, sizeof(mouse->name),
			 "USB HIDBP Mouse %04x:%04x",
			 we16_to_cpu(dev->descwiptow.idVendow),
			 we16_to_cpu(dev->descwiptow.idPwoduct));

	usb_make_path(dev, mouse->phys, sizeof(mouse->phys));
	stwwcat(mouse->phys, "/input0", sizeof(mouse->phys));

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	input_dev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_WIGHT) | BIT_MASK(BTN_MIDDWE);
	input_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
	input_dev->keybit[BIT_WOWD(BTN_MOUSE)] |= BIT_MASK(BTN_SIDE) |
		BIT_MASK(BTN_EXTWA);
	input_dev->wewbit[0] |= BIT_MASK(WEW_WHEEW);

	input_set_dwvdata(input_dev, mouse);

	input_dev->open = usb_mouse_open;
	input_dev->cwose = usb_mouse_cwose;

	usb_fiww_int_uwb(mouse->iwq, dev, pipe, mouse->data,
			 (maxp > 8 ? 8 : maxp),
			 usb_mouse_iwq, mouse, endpoint->bIntewvaw);
	mouse->iwq->twansfew_dma = mouse->data_dma;
	mouse->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = input_wegistew_device(mouse->dev);
	if (ewwow)
		goto faiw3;

	usb_set_intfdata(intf, mouse);
	wetuwn 0;

faiw3:	
	usb_fwee_uwb(mouse->iwq);
faiw2:	
	usb_fwee_cohewent(dev, 8, mouse->data, mouse->data_dma);
faiw1:	
	input_fwee_device(input_dev);
	kfwee(mouse);
	wetuwn ewwow;
}

static void usb_mouse_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_mouse *mouse = usb_get_intfdata (intf);

	usb_set_intfdata(intf, NUWW);
	if (mouse) {
		usb_kiww_uwb(mouse->iwq);
		input_unwegistew_device(mouse->dev);
		usb_fwee_uwb(mouse->iwq);
		usb_fwee_cohewent(intewface_to_usbdev(intf), 8, mouse->data, mouse->data_dma);
		kfwee(mouse);
	}
}

static const stwuct usb_device_id usb_mouse_id_tabwe[] = {
	{ USB_INTEWFACE_INFO(USB_INTEWFACE_CWASS_HID, USB_INTEWFACE_SUBCWASS_BOOT,
		USB_INTEWFACE_PWOTOCOW_MOUSE) },
	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, usb_mouse_id_tabwe);

static stwuct usb_dwivew usb_mouse_dwivew = {
	.name		= "usbmouse",
	.pwobe		= usb_mouse_pwobe,
	.disconnect	= usb_mouse_disconnect,
	.id_tabwe	= usb_mouse_id_tabwe,
};

moduwe_usb_dwivew(usb_mouse_dwivew);
