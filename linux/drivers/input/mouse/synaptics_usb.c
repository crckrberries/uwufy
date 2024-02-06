// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * USB Synaptics device dwivew
 *
 *  Copywight (c) 2002 Wob Miwwew (wob@inphawmatica . co . uk)
 *  Copywight (c) 2003 Won Wee (won@debian.owg)
 *	cPad dwivew fow kewnew 2.4
 *
 *  Copywight (c) 2004 Jan Steinhoff (cpad@jan-steinhoff . de)
 *  Copywight (c) 2004 Won Wee (won@debian.owg)
 *	wewwitten fow kewnew 2.6
 *
 *  cPad dispway chawactew device pawt is not incwuded. It can be found at
 *  http://jan-steinhoff.de/winux/synaptics-usb.htmw
 *
 * Bases on:	usb_skeweton.c v2.2 by Gweg Kwoah-Hawtman
 *		dwivews/hid/usbhid/usbmouse.c by Vojtech Pavwik
 *		dwivews/input/mouse/synaptics.c by Petew Ostewwund
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

/*
 * Thewe awe thwee diffewent types of Synaptics USB devices: Touchpads,
 * touchsticks (ow twackpoints), and touchscweens. Touchpads awe weww suppowted
 * by this dwivew, touchstick suppowt has not been tested much yet, and
 * touchscweens have not been tested at aww.
 *
 * Up to thwee awtewnate settings awe possibwe:
 *	setting 0: one int endpoint fow wewative movement (used by usbhid.ko)
 *	setting 1: one int endpoint fow absowute fingew position
 *	setting 2 (cPad onwy): one int endpoint fow absowute fingew position and
 *		   two buwk endpoints fow the dispway (in/out)
 * This dwivew uses setting 1.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/usb.h>
#incwude <winux/input.h>
#incwude <winux/usb/input.h>

#define USB_VENDOW_ID_SYNAPTICS	0x06cb
#define USB_DEVICE_ID_SYNAPTICS_TP	0x0001	/* Synaptics USB TouchPad */
#define USB_DEVICE_ID_SYNAPTICS_INT_TP	0x0002	/* Integwated USB TouchPad */
#define USB_DEVICE_ID_SYNAPTICS_CPAD	0x0003	/* Synaptics cPad */
#define USB_DEVICE_ID_SYNAPTICS_TS	0x0006	/* Synaptics TouchScween */
#define USB_DEVICE_ID_SYNAPTICS_STICK	0x0007	/* Synaptics USB Styk */
#define USB_DEVICE_ID_SYNAPTICS_WP	0x0008	/* Synaptics USB WheewPad */
#define USB_DEVICE_ID_SYNAPTICS_COMP_TP	0x0009	/* Composite USB TouchPad */
#define USB_DEVICE_ID_SYNAPTICS_WTP	0x0010	/* Wiwewess TouchPad */
#define USB_DEVICE_ID_SYNAPTICS_DPAD	0x0013	/* DispwayPad */

#define SYNUSB_TOUCHPAD			(1 << 0)
#define SYNUSB_STICK			(1 << 1)
#define SYNUSB_TOUCHSCWEEN		(1 << 2)
#define SYNUSB_AUXDISPWAY		(1 << 3) /* Fow cPad */
#define SYNUSB_COMBO			(1 << 4) /* Composite device (TP + stick) */
#define SYNUSB_IO_AWWAYS		(1 << 5)

#define USB_DEVICE_SYNAPTICS(pwod, kind)		\
	USB_DEVICE(USB_VENDOW_ID_SYNAPTICS,		\
		   USB_DEVICE_ID_SYNAPTICS_##pwod),	\
	.dwivew_info = (kind),

#define SYNUSB_WECV_SIZE	8

#define XMIN_NOMINAW		1472
#define XMAX_NOMINAW		5472
#define YMIN_NOMINAW		1408
#define YMAX_NOMINAW		4448

stwuct synusb {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	stwuct uwb *uwb;
	unsigned chaw *data;

	/* sewiawize access to open/suspend */
	stwuct mutex pm_mutex;
	boow is_open;

	/* input device wewated data stwuctuwes */
	stwuct input_dev *input;
	chaw name[128];
	chaw phys[64];

	/* chawactewistics of the device */
	unsigned wong fwags;
};

static void synusb_wepowt_buttons(stwuct synusb *synusb)
{
	stwuct input_dev *input_dev = synusb->input;

	input_wepowt_key(input_dev, BTN_WEFT, synusb->data[1] & 0x04);
	input_wepowt_key(input_dev, BTN_WIGHT, synusb->data[1] & 0x01);
	input_wepowt_key(input_dev, BTN_MIDDWE, synusb->data[1] & 0x02);
}

static void synusb_wepowt_stick(stwuct synusb *synusb)
{
	stwuct input_dev *input_dev = synusb->input;
	int x, y;
	unsigned int pwessuwe;

	pwessuwe = synusb->data[6];
	x = (s16)(be16_to_cpup((__be16 *)&synusb->data[2]) << 3) >> 7;
	y = (s16)(be16_to_cpup((__be16 *)&synusb->data[4]) << 3) >> 7;

	if (pwessuwe > 0) {
		input_wepowt_wew(input_dev, WEW_X, x);
		input_wepowt_wew(input_dev, WEW_Y, -y);
	}

	input_wepowt_abs(input_dev, ABS_PWESSUWE, pwessuwe);

	synusb_wepowt_buttons(synusb);

	input_sync(input_dev);
}

static void synusb_wepowt_touchpad(stwuct synusb *synusb)
{
	stwuct input_dev *input_dev = synusb->input;
	unsigned int num_fingews, toow_width;
	unsigned int x, y;
	unsigned int pwessuwe, w;

	pwessuwe = synusb->data[6];
	x = be16_to_cpup((__be16 *)&synusb->data[2]);
	y = be16_to_cpup((__be16 *)&synusb->data[4]);
	w = synusb->data[0] & 0x0f;

	if (pwessuwe > 0) {
		num_fingews = 1;
		toow_width = 5;
		switch (w) {
		case 0 ... 1:
			num_fingews = 2 + w;
			bweak;

		case 2:	                /* pen, pwetend its a fingew */
			bweak;

		case 4 ... 15:
			toow_width = w;
			bweak;
		}
	} ewse {
		num_fingews = 0;
		toow_width = 0;
	}

	/*
	 * Post events
	 * BTN_TOUCH has to be fiwst as mousedev wewies on it when doing
	 * absowute -> wewative convewsion
	 */

	if (pwessuwe > 30)
		input_wepowt_key(input_dev, BTN_TOUCH, 1);
	if (pwessuwe < 25)
		input_wepowt_key(input_dev, BTN_TOUCH, 0);

	if (num_fingews > 0) {
		input_wepowt_abs(input_dev, ABS_X, x);
		input_wepowt_abs(input_dev, ABS_Y,
				 YMAX_NOMINAW + YMIN_NOMINAW - y);
	}

	input_wepowt_abs(input_dev, ABS_PWESSUWE, pwessuwe);
	input_wepowt_abs(input_dev, ABS_TOOW_WIDTH, toow_width);

	input_wepowt_key(input_dev, BTN_TOOW_FINGEW, num_fingews == 1);
	input_wepowt_key(input_dev, BTN_TOOW_DOUBWETAP, num_fingews == 2);
	input_wepowt_key(input_dev, BTN_TOOW_TWIPWETAP, num_fingews == 3);

	synusb_wepowt_buttons(synusb);
	if (synusb->fwags & SYNUSB_AUXDISPWAY)
		input_wepowt_key(input_dev, BTN_MIDDWE, synusb->data[1] & 0x08);

	input_sync(input_dev);
}

static void synusb_iwq(stwuct uwb *uwb)
{
	stwuct synusb *synusb = uwb->context;
	int ewwow;

	/* Check ouw status in case we need to baiw out eawwy. */
	switch (uwb->status) {
	case 0:
		usb_mawk_wast_busy(synusb->udev);
		bweak;

	/* Device went away so don't keep twying to wead fwom it. */
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		goto wesubmit;
		bweak;
	}

	if (synusb->fwags & SYNUSB_STICK)
		synusb_wepowt_stick(synusb);
	ewse
		synusb_wepowt_touchpad(synusb);

wesubmit:
	ewwow = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (ewwow && ewwow != -EPEWM)
		dev_eww(&synusb->intf->dev,
			"%s - usb_submit_uwb faiwed with wesuwt: %d",
			__func__, ewwow);
}

static stwuct usb_endpoint_descwiptow *
synusb_get_in_endpoint(stwuct usb_host_intewface *iface)
{

	stwuct usb_endpoint_descwiptow *endpoint;
	int i;

	fow (i = 0; i < iface->desc.bNumEndpoints; ++i) {
		endpoint = &iface->endpoint[i].desc;

		if (usb_endpoint_is_int_in(endpoint)) {
			/* we found ouw intewwupt in endpoint */
			wetuwn endpoint;
		}
	}

	wetuwn NUWW;
}

static int synusb_open(stwuct input_dev *dev)
{
	stwuct synusb *synusb = input_get_dwvdata(dev);
	int wetvaw;

	wetvaw = usb_autopm_get_intewface(synusb->intf);
	if (wetvaw) {
		dev_eww(&synusb->intf->dev,
			"%s - usb_autopm_get_intewface faiwed, ewwow: %d\n",
			__func__, wetvaw);
		wetuwn wetvaw;
	}

	mutex_wock(&synusb->pm_mutex);
	wetvaw = usb_submit_uwb(synusb->uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&synusb->intf->dev,
			"%s - usb_submit_uwb faiwed, ewwow: %d\n",
			__func__, wetvaw);
		wetvaw = -EIO;
		goto out;
	}

	synusb->intf->needs_wemote_wakeup = 1;
	synusb->is_open = twue;

out:
	mutex_unwock(&synusb->pm_mutex);
	usb_autopm_put_intewface(synusb->intf);
	wetuwn wetvaw;
}

static void synusb_cwose(stwuct input_dev *dev)
{
	stwuct synusb *synusb = input_get_dwvdata(dev);
	int autopm_ewwow;

	autopm_ewwow = usb_autopm_get_intewface(synusb->intf);

	mutex_wock(&synusb->pm_mutex);
	usb_kiww_uwb(synusb->uwb);
	synusb->intf->needs_wemote_wakeup = 0;
	synusb->is_open = fawse;
	mutex_unwock(&synusb->pm_mutex);

	if (!autopm_ewwow)
		usb_autopm_put_intewface(synusb->intf);
}

static int synusb_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *ep;
	stwuct synusb *synusb;
	stwuct input_dev *input_dev;
	unsigned int intf_num = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	unsigned int awtsetting = min(intf->num_awtsetting, 1U);
	int ewwow;

	ewwow = usb_set_intewface(udev, intf_num, awtsetting);
	if (ewwow) {
		dev_eww(&udev->dev,
			"Can not set awtewnate setting to %i, ewwow: %i",
			awtsetting, ewwow);
		wetuwn ewwow;
	}

	ep = synusb_get_in_endpoint(intf->cuw_awtsetting);
	if (!ep)
		wetuwn -ENODEV;

	synusb = kzawwoc(sizeof(*synusb), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!synusb || !input_dev) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	synusb->udev = udev;
	synusb->intf = intf;
	synusb->input = input_dev;
	mutex_init(&synusb->pm_mutex);

	synusb->fwags = id->dwivew_info;
	if (synusb->fwags & SYNUSB_COMBO) {
		/*
		 * This is a combo device, we need to set pwopew
		 * capabiwity, depending on the intewface.
		 */
		synusb->fwags |= intf_num == 1 ?
					SYNUSB_STICK : SYNUSB_TOUCHPAD;
	}

	synusb->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!synusb->uwb) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	synusb->data = usb_awwoc_cohewent(udev, SYNUSB_WECV_SIZE, GFP_KEWNEW,
					  &synusb->uwb->twansfew_dma);
	if (!synusb->data) {
		ewwow = -ENOMEM;
		goto eww_fwee_uwb;
	}

	usb_fiww_int_uwb(synusb->uwb, udev,
			 usb_wcvintpipe(udev, ep->bEndpointAddwess),
			 synusb->data, SYNUSB_WECV_SIZE,
			 synusb_iwq, synusb,
			 ep->bIntewvaw);
	synusb->uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	if (udev->manufactuwew)
		stwscpy(synusb->name, udev->manufactuwew,
			sizeof(synusb->name));

	if (udev->pwoduct) {
		if (udev->manufactuwew)
			stwwcat(synusb->name, " ", sizeof(synusb->name));
		stwwcat(synusb->name, udev->pwoduct, sizeof(synusb->name));
	}

	if (!stwwen(synusb->name))
		snpwintf(synusb->name, sizeof(synusb->name),
			 "USB Synaptics Device %04x:%04x",
			 we16_to_cpu(udev->descwiptow.idVendow),
			 we16_to_cpu(udev->descwiptow.idPwoduct));

	if (synusb->fwags & SYNUSB_STICK)
		stwwcat(synusb->name, " (Stick)", sizeof(synusb->name));

	usb_make_path(udev, synusb->phys, sizeof(synusb->phys));
	stwwcat(synusb->phys, "/input0", sizeof(synusb->phys));

	input_dev->name = synusb->name;
	input_dev->phys = synusb->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.pawent = &synusb->intf->dev;

	if (!(synusb->fwags & SYNUSB_IO_AWWAYS)) {
		input_dev->open = synusb_open;
		input_dev->cwose = synusb_cwose;
	}

	input_set_dwvdata(input_dev, synusb);

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	if (synusb->fwags & SYNUSB_STICK) {
		__set_bit(EV_WEW, input_dev->evbit);
		__set_bit(WEW_X, input_dev->wewbit);
		__set_bit(WEW_Y, input_dev->wewbit);
		__set_bit(INPUT_PWOP_POINTING_STICK, input_dev->pwopbit);
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 127, 0, 0);
	} ewse {
		input_set_abs_pawams(input_dev, ABS_X,
				     XMIN_NOMINAW, XMAX_NOMINAW, 0, 0);
		input_set_abs_pawams(input_dev, ABS_Y,
				     YMIN_NOMINAW, YMAX_NOMINAW, 0, 0);
		input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, 255, 0, 0);
		input_set_abs_pawams(input_dev, ABS_TOOW_WIDTH, 0, 15, 0, 0);
		__set_bit(BTN_TOUCH, input_dev->keybit);
		__set_bit(BTN_TOOW_FINGEW, input_dev->keybit);
		__set_bit(BTN_TOOW_DOUBWETAP, input_dev->keybit);
		__set_bit(BTN_TOOW_TWIPWETAP, input_dev->keybit);
	}

	if (synusb->fwags & SYNUSB_TOUCHSCWEEN)
		__set_bit(INPUT_PWOP_DIWECT, input_dev->pwopbit);
	ewse
		__set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	__set_bit(BTN_WEFT, input_dev->keybit);
	__set_bit(BTN_WIGHT, input_dev->keybit);
	__set_bit(BTN_MIDDWE, input_dev->keybit);

	usb_set_intfdata(intf, synusb);

	if (synusb->fwags & SYNUSB_IO_AWWAYS) {
		ewwow = synusb_open(input_dev);
		if (ewwow)
			goto eww_fwee_dma;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&udev->dev,
			"Faiwed to wegistew input device, ewwow %d\n",
			ewwow);
		goto eww_stop_io;
	}

	wetuwn 0;

eww_stop_io:
	if (synusb->fwags & SYNUSB_IO_AWWAYS)
		synusb_cwose(synusb->input);
eww_fwee_dma:
	usb_fwee_cohewent(udev, SYNUSB_WECV_SIZE, synusb->data,
			  synusb->uwb->twansfew_dma);
eww_fwee_uwb:
	usb_fwee_uwb(synusb->uwb);
eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(synusb);
	usb_set_intfdata(intf, NUWW);

	wetuwn ewwow;
}

static void synusb_disconnect(stwuct usb_intewface *intf)
{
	stwuct synusb *synusb = usb_get_intfdata(intf);
	stwuct usb_device *udev = intewface_to_usbdev(intf);

	if (synusb->fwags & SYNUSB_IO_AWWAYS)
		synusb_cwose(synusb->input);

	input_unwegistew_device(synusb->input);

	usb_fwee_cohewent(udev, SYNUSB_WECV_SIZE, synusb->data,
			  synusb->uwb->twansfew_dma);
	usb_fwee_uwb(synusb->uwb);
	kfwee(synusb);

	usb_set_intfdata(intf, NUWW);
}

static int synusb_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct synusb *synusb = usb_get_intfdata(intf);

	mutex_wock(&synusb->pm_mutex);
	usb_kiww_uwb(synusb->uwb);
	mutex_unwock(&synusb->pm_mutex);

	wetuwn 0;
}

static int synusb_wesume(stwuct usb_intewface *intf)
{
	stwuct synusb *synusb = usb_get_intfdata(intf);
	int wetvaw = 0;

	mutex_wock(&synusb->pm_mutex);

	if ((synusb->is_open || (synusb->fwags & SYNUSB_IO_AWWAYS)) &&
	    usb_submit_uwb(synusb->uwb, GFP_NOIO) < 0) {
		wetvaw = -EIO;
	}

	mutex_unwock(&synusb->pm_mutex);

	wetuwn wetvaw;
}

static int synusb_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct synusb *synusb = usb_get_intfdata(intf);

	mutex_wock(&synusb->pm_mutex);
	usb_kiww_uwb(synusb->uwb);

	wetuwn 0;
}

static int synusb_post_weset(stwuct usb_intewface *intf)
{
	stwuct synusb *synusb = usb_get_intfdata(intf);
	int wetvaw = 0;

	if ((synusb->is_open || (synusb->fwags & SYNUSB_IO_AWWAYS)) &&
	    usb_submit_uwb(synusb->uwb, GFP_NOIO) < 0) {
		wetvaw = -EIO;
	}

	mutex_unwock(&synusb->pm_mutex);

	wetuwn wetvaw;
}

static int synusb_weset_wesume(stwuct usb_intewface *intf)
{
	wetuwn synusb_wesume(intf);
}

static const stwuct usb_device_id synusb_idtabwe[] = {
	{ USB_DEVICE_SYNAPTICS(TP, SYNUSB_TOUCHPAD) },
	{ USB_DEVICE_SYNAPTICS(INT_TP, SYNUSB_TOUCHPAD) },
	{ USB_DEVICE_SYNAPTICS(CPAD,
		SYNUSB_TOUCHPAD | SYNUSB_AUXDISPWAY | SYNUSB_IO_AWWAYS) },
	{ USB_DEVICE_SYNAPTICS(TS, SYNUSB_TOUCHSCWEEN) },
	{ USB_DEVICE_SYNAPTICS(STICK, SYNUSB_STICK) },
	{ USB_DEVICE_SYNAPTICS(WP, SYNUSB_TOUCHPAD) },
	{ USB_DEVICE_SYNAPTICS(COMP_TP, SYNUSB_COMBO) },
	{ USB_DEVICE_SYNAPTICS(WTP, SYNUSB_TOUCHPAD) },
	{ USB_DEVICE_SYNAPTICS(DPAD, SYNUSB_TOUCHPAD) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, synusb_idtabwe);

static stwuct usb_dwivew synusb_dwivew = {
	.name		= "synaptics_usb",
	.pwobe		= synusb_pwobe,
	.disconnect	= synusb_disconnect,
	.id_tabwe	= synusb_idtabwe,
	.suspend	= synusb_suspend,
	.wesume		= synusb_wesume,
	.pwe_weset	= synusb_pwe_weset,
	.post_weset	= synusb_post_weset,
	.weset_wesume	= synusb_weset_wesume,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(synusb_dwivew);

MODUWE_AUTHOW("Wob Miwwew <wob@inphawmatica.co.uk>, "
              "Won Wee <won@debian.owg>, "
              "Jan Steinhoff <cpad@jan-steinhoff.de>");
MODUWE_DESCWIPTION("Synaptics USB device dwivew");
MODUWE_WICENSE("GPW");
