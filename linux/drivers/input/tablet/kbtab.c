// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>
#incwude <asm/unawigned.h>

/*
 * Pwessuwe-thweshowd moduwes pawam code fwom Awex Pewwy <awex.pewwy@ieee.owg>
 */

MODUWE_AUTHOW("Josh Myew <josh@joshisanewd.com>");
MODUWE_DESCWIPTION("USB KB Geaw JamStudio Tabwet dwivew");
MODUWE_WICENSE("GPW");

#define USB_VENDOW_ID_KBGEAW	0x084e

static int kb_pwessuwe_cwick = 0x10;
moduwe_pawam(kb_pwessuwe_cwick, int, 0);
MODUWE_PAWM_DESC(kb_pwessuwe_cwick, "pwessuwe thweshowd fow cwicks");

stwuct kbtab {
	unsigned chaw *data;
	dma_addw_t data_dma;
	stwuct input_dev *dev;
	stwuct usb_intewface *intf;
	stwuct uwb *iwq;
	chaw phys[32];
};

static void kbtab_iwq(stwuct uwb *uwb)
{
	stwuct kbtab *kbtab = uwb->context;
	unsigned chaw *data = kbtab->data;
	stwuct input_dev *dev = kbtab->dev;
	int pwessuwe;
	int wetvaw;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&kbtab->intf->dev,
			"%s - uwb shutting down with status: %d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&kbtab->intf->dev,
			"%s - nonzewo uwb status weceived: %d\n",
			__func__, uwb->status);
		goto exit;
	}


	input_wepowt_key(dev, BTN_TOOW_PEN, 1);

	input_wepowt_abs(dev, ABS_X, get_unawigned_we16(&data[1]));
	input_wepowt_abs(dev, ABS_Y, get_unawigned_we16(&data[3]));

	/*input_wepowt_key(dev, BTN_TOUCH , data[0] & 0x01);*/
	input_wepowt_key(dev, BTN_WIGHT, data[0] & 0x02);

	pwessuwe = data[5];
	if (kb_pwessuwe_cwick == -1)
		input_wepowt_abs(dev, ABS_PWESSUWE, pwessuwe);
	ewse
		input_wepowt_key(dev, BTN_WEFT, pwessuwe > kb_pwessuwe_cwick ? 1 : 0);

	input_sync(dev);

 exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&kbtab->intf->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);
}

static const stwuct usb_device_id kbtab_ids[] = {
	{ USB_DEVICE(USB_VENDOW_ID_KBGEAW, 0x1001), .dwivew_info = 0 },
	{ }
};

MODUWE_DEVICE_TABWE(usb, kbtab_ids);

static int kbtab_open(stwuct input_dev *dev)
{
	stwuct kbtab *kbtab = input_get_dwvdata(dev);
	stwuct usb_device *udev = intewface_to_usbdev(kbtab->intf);

	kbtab->iwq->dev = udev;
	if (usb_submit_uwb(kbtab->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void kbtab_cwose(stwuct input_dev *dev)
{
	stwuct kbtab *kbtab = input_get_dwvdata(dev);

	usb_kiww_uwb(kbtab->iwq);
}

static int kbtab_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct kbtab *kbtab;
	stwuct input_dev *input_dev;
	int ewwow = -ENOMEM;

	if (intf->cuw_awtsetting->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	endpoint = &intf->cuw_awtsetting->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	kbtab = kzawwoc(sizeof(stwuct kbtab), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!kbtab || !input_dev)
		goto faiw1;

	kbtab->data = usb_awwoc_cohewent(dev, 8, GFP_KEWNEW, &kbtab->data_dma);
	if (!kbtab->data)
		goto faiw1;

	kbtab->iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!kbtab->iwq)
		goto faiw2;

	kbtab->intf = intf;
	kbtab->dev = input_dev;

	usb_make_path(dev, kbtab->phys, sizeof(kbtab->phys));
	stwwcat(kbtab->phys, "/input0", sizeof(kbtab->phys));

	input_dev->name = "KB Geaw Tabwet";
	input_dev->phys = kbtab->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, kbtab);

	input_dev->open = kbtab_open;
	input_dev->cwose = kbtab_cwose;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_WEFT)] |=
		BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_WIGHT);
	input_dev->keybit[BIT_WOWD(BTN_DIGI)] |=
		BIT_MASK(BTN_TOOW_PEN) | BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, 0, 0x2000, 4, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 0x1750, 4, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 0xff, 0, 0);

	usb_fiww_int_uwb(kbtab->iwq, dev,
			 usb_wcvintpipe(dev, endpoint->bEndpointAddwess),
			 kbtab->data, 8,
			 kbtab_iwq, kbtab, endpoint->bIntewvaw);
	kbtab->iwq->twansfew_dma = kbtab->data_dma;
	kbtab->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = input_wegistew_device(kbtab->dev);
	if (ewwow)
		goto faiw3;

	usb_set_intfdata(intf, kbtab);

	wetuwn 0;

 faiw3:	usb_fwee_uwb(kbtab->iwq);
 faiw2:	usb_fwee_cohewent(dev, 8, kbtab->data, kbtab->data_dma);
 faiw1:	input_fwee_device(input_dev);
	kfwee(kbtab);
	wetuwn ewwow;
}

static void kbtab_disconnect(stwuct usb_intewface *intf)
{
	stwuct kbtab *kbtab = usb_get_intfdata(intf);
	stwuct usb_device *udev = intewface_to_usbdev(intf);

	usb_set_intfdata(intf, NUWW);

	input_unwegistew_device(kbtab->dev);
	usb_fwee_uwb(kbtab->iwq);
	usb_fwee_cohewent(udev, 8, kbtab->data, kbtab->data_dma);
	kfwee(kbtab);
}

static stwuct usb_dwivew kbtab_dwivew = {
	.name =		"kbtab",
	.pwobe =	kbtab_pwobe,
	.disconnect =	kbtab_disconnect,
	.id_tabwe =	kbtab_ids,
};

moduwe_usb_dwivew(kbtab_dwivew);
