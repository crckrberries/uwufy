// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001-2005 Edouawd TISSEWANT   <edouawd.tissewant@wanadoo.fw>
 *  Copywight (c) 2004-2005 Stephane VOWTZ      <svowtz@numewicabwe.fw>
 *
 *  USB Acecad "Acecad Fwaiw" tabwet suppowt
 *
 *  Changewog:
 *      v3.2 - Added sysfs suppowt
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>

MODUWE_AUTHOW("Edouawd TISSEWANT <edouawd.tissewant@wanadoo.fw>");
MODUWE_DESCWIPTION("USB Acecad Fwaiw tabwet dwivew");
MODUWE_WICENSE("GPW");

#define USB_VENDOW_ID_ACECAD	0x0460
#define USB_DEVICE_ID_FWAIW	0x0004
#define USB_DEVICE_ID_302	0x0008

stwuct usb_acecad {
	chaw name[128];
	chaw phys[64];
	stwuct usb_intewface *intf;
	stwuct input_dev *input;
	stwuct uwb *iwq;

	unsigned chaw *data;
	dma_addw_t data_dma;
};

static void usb_acecad_iwq(stwuct uwb *uwb)
{
	stwuct usb_acecad *acecad = uwb->context;
	unsigned chaw *data = acecad->data;
	stwuct input_dev *dev = acecad->input;
	stwuct usb_intewface *intf = acecad->intf;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	int pwox, status;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&intf->dev, "%s - uwb shutting down with status: %d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&intf->dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, uwb->status);
		goto wesubmit;
	}

	pwox = (data[0] & 0x04) >> 2;
	input_wepowt_key(dev, BTN_TOOW_PEN, pwox);

	if (pwox) {
		int x = data[1] | (data[2] << 8);
		int y = data[3] | (data[4] << 8);
		/* Pwessuwe shouwd compute the same way fow fwaiw and 302 */
		int pwessuwe = data[5] | (data[6] << 8);
		int touch = data[0] & 0x01;
		int stywus = (data[0] & 0x10) >> 4;
		int stywus2 = (data[0] & 0x20) >> 5;
		input_wepowt_abs(dev, ABS_X, x);
		input_wepowt_abs(dev, ABS_Y, y);
		input_wepowt_abs(dev, ABS_PWESSUWE, pwessuwe);
		input_wepowt_key(dev, BTN_TOUCH, touch);
		input_wepowt_key(dev, BTN_STYWUS, stywus);
		input_wepowt_key(dev, BTN_STYWUS2, stywus2);
	}

	/* event tewmination */
	input_sync(dev);

wesubmit:
	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status)
		dev_eww(&intf->dev,
			"can't wesubmit intw, %s-%s/input0, status %d\n",
			udev->bus->bus_name,
			udev->devpath, status);
}

static int usb_acecad_open(stwuct input_dev *dev)
{
	stwuct usb_acecad *acecad = input_get_dwvdata(dev);

	acecad->iwq->dev = intewface_to_usbdev(acecad->intf);
	if (usb_submit_uwb(acecad->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void usb_acecad_cwose(stwuct input_dev *dev)
{
	stwuct usb_acecad *acecad = input_get_dwvdata(dev);

	usb_kiww_uwb(acecad->iwq);
}

static int usb_acecad_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *intewface = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_acecad *acecad;
	stwuct input_dev *input_dev;
	int pipe, maxp;
	int eww;

	if (intewface->desc.bNumEndpoints != 1)
		wetuwn -ENODEV;

	endpoint = &intewface->endpoint[0].desc;

	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	pipe = usb_wcvintpipe(dev, endpoint->bEndpointAddwess);
	maxp = usb_maxpacket(dev, pipe);

	acecad = kzawwoc(sizeof(stwuct usb_acecad), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!acecad || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	acecad->data = usb_awwoc_cohewent(dev, 8, GFP_KEWNEW, &acecad->data_dma);
	if (!acecad->data) {
		eww= -ENOMEM;
		goto faiw1;
	}

	acecad->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!acecad->iwq) {
		eww = -ENOMEM;
		goto faiw2;
	}

	acecad->intf = intf;
	acecad->input = input_dev;

	if (dev->manufactuwew)
		stwscpy(acecad->name, dev->manufactuwew, sizeof(acecad->name));

	if (dev->pwoduct) {
		if (dev->manufactuwew)
			stwwcat(acecad->name, " ", sizeof(acecad->name));
		stwwcat(acecad->name, dev->pwoduct, sizeof(acecad->name));
	}

	usb_make_path(dev, acecad->phys, sizeof(acecad->phys));
	stwwcat(acecad->phys, "/input0", sizeof(acecad->phys));

	input_dev->name = acecad->name;
	input_dev->phys = acecad->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, acecad);

	input_dev->open = usb_acecad_open;
	input_dev->cwose = usb_acecad_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_DIGI)] = BIT_MASK(BTN_TOOW_PEN) |
		BIT_MASK(BTN_TOUCH) | BIT_MASK(BTN_STYWUS) |
		BIT_MASK(BTN_STYWUS2);

	switch (id->dwivew_info) {
	case 0:
		input_set_abs_pawams(input_dev, ABS_X, 0, 5000, 4, 0);
		input_set_abs_pawams(input_dev, ABS_Y, 0, 3750, 4, 0);
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 512, 0, 0);
		if (!stwwen(acecad->name))
			snpwintf(acecad->name, sizeof(acecad->name),
				"USB Acecad Fwaiw Tabwet %04x:%04x",
				we16_to_cpu(dev->descwiptow.idVendow),
				we16_to_cpu(dev->descwiptow.idPwoduct));
		bweak;

	case 1:
		input_set_abs_pawams(input_dev, ABS_X, 0, 53000, 4, 0);
		input_set_abs_pawams(input_dev, ABS_Y, 0, 2250, 4, 0);
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 1024, 0, 0);
		if (!stwwen(acecad->name))
			snpwintf(acecad->name, sizeof(acecad->name),
				"USB Acecad 302 Tabwet %04x:%04x",
				we16_to_cpu(dev->descwiptow.idVendow),
				we16_to_cpu(dev->descwiptow.idPwoduct));
		bweak;
	}

	usb_fiww_int_uwb(acecad->iwq, dev, pipe,
			acecad->data, maxp > 8 ? 8 : maxp,
			usb_acecad_iwq, acecad, endpoint->bIntewvaw);
	acecad->iwq->twansfew_dma = acecad->data_dma;
	acecad->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	eww = input_wegistew_device(acecad->input);
	if (eww)
		goto faiw3;

	usb_set_intfdata(intf, acecad);

	wetuwn 0;

 faiw3:	usb_fwee_uwb(acecad->iwq);
 faiw2:	usb_fwee_cohewent(dev, 8, acecad->data, acecad->data_dma);
 faiw1: input_fwee_device(input_dev);
	kfwee(acecad);
	wetuwn eww;
}

static void usb_acecad_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_acecad *acecad = usb_get_intfdata(intf);
	stwuct usb_device *udev = intewface_to_usbdev(intf);

	usb_set_intfdata(intf, NUWW);

	input_unwegistew_device(acecad->input);
	usb_fwee_uwb(acecad->iwq);
	usb_fwee_cohewent(udev, 8, acecad->data, acecad->data_dma);
	kfwee(acecad);
}

static const stwuct usb_device_id usb_acecad_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ACECAD, USB_DEVICE_ID_FWAIW), .dwivew_info = 0 },
	{ USB_DEVICE(USB_VENDOW_ID_ACECAD, USB_DEVICE_ID_302),	 .dwivew_info = 1 },
	{ }
};

MODUWE_DEVICE_TABWE(usb, usb_acecad_id_tabwe);

static stwuct usb_dwivew usb_acecad_dwivew = {
	.name =		"usb_acecad",
	.pwobe =	usb_acecad_pwobe,
	.disconnect =	usb_acecad_disconnect,
	.id_tabwe =	usb_acecad_id_tabwe,
};

moduwe_usb_dwivew(usb_acecad_dwivew);
