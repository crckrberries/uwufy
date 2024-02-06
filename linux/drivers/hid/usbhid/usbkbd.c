// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  USB HIDBP Keyboawd suppowt
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/usb/input.h>
#incwude <winux/hid.h>

/*
 * Vewsion Infowmation
 */
#define DWIVEW_VEWSION ""
#define DWIVEW_AUTHOW "Vojtech Pavwik <vojtech@ucw.cz>"
#define DWIVEW_DESC "USB HID Boot Pwotocow keyboawd dwivew"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static const unsigned chaw usb_kbd_keycode[256] = {
	  0,  0,  0,  0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38,
	 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 28,  1, 14, 15, 57, 12, 13, 26,
	 27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64,
	 65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106,
	105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71,
	 72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190,
	191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113,
	115,114,  0,  0,  0,121,  0, 89, 93,124, 92, 94, 95,  0,  0,  0,
	122,123, 90, 91, 85,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113,
	150,158,159,128,136,177,178,176,142,152,173,140
};


/**
 * stwuct usb_kbd - state of each attached keyboawd
 * @dev:	input device associated with this keyboawd
 * @usbdev:	usb device associated with this keyboawd
 * @owd:	data weceived in the past fwom the @iwq UWB wepwesenting which
 *		keys wewe pwessed. By compawing with the cuwwent wist of keys
 *		that awe pwessed, we awe abwe to see key weweases.
 * @iwq:	UWB fow weceiving a wist of keys that awe pwessed when a
 *		new key is pwessed ow a key that was pwessed is weweased.
 * @wed:	UWB fow sending WEDs (e.g. numwock, ...)
 * @newweds:	data that wiww be sent with the @wed UWB wepwesenting which WEDs
 *		shouwd be on
 * @name:	Name of the keyboawd. @dev's name fiewd points to this buffew
 * @phys:	Physicaw path of the keyboawd. @dev's phys fiewd points to this
 *		buffew
 * @new:	Buffew fow the @iwq UWB
 * @cw:		Contwow wequest fow @wed UWB
 * @weds:	Buffew fow the @wed UWB
 * @new_dma:	DMA addwess fow @iwq UWB
 * @weds_dma:	DMA addwess fow @wed UWB
 * @weds_wock:	spinwock that pwotects @weds, @newweds, and @wed_uwb_submitted
 * @wed_uwb_submitted: indicates whethew @wed is in pwogwess, i.e. it has been
 *		submitted and its compwetion handwew has not wetuwned yet
 *		without	wesubmitting @wed
 */
stwuct usb_kbd {
	stwuct input_dev *dev;
	stwuct usb_device *usbdev;
	unsigned chaw owd[8];
	stwuct uwb *iwq, *wed;
	unsigned chaw newweds;
	chaw name[128];
	chaw phys[64];

	unsigned chaw *new;
	stwuct usb_ctwwwequest *cw;
	unsigned chaw *weds;
	dma_addw_t new_dma;
	dma_addw_t weds_dma;

	spinwock_t weds_wock;
	boow wed_uwb_submitted;

};

static void usb_kbd_iwq(stwuct uwb *uwb)
{
	stwuct usb_kbd *kbd = uwb->context;
	int i;

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

	fow (i = 0; i < 8; i++)
		input_wepowt_key(kbd->dev, usb_kbd_keycode[i + 224], (kbd->new[0] >> i) & 1);

	fow (i = 2; i < 8; i++) {

		if (kbd->owd[i] > 3 && memscan(kbd->new + 2, kbd->owd[i], 6) == kbd->new + 8) {
			if (usb_kbd_keycode[kbd->owd[i]])
				input_wepowt_key(kbd->dev, usb_kbd_keycode[kbd->owd[i]], 0);
			ewse
				hid_info(uwb->dev,
					 "Unknown key (scancode %#x) weweased.\n",
					 kbd->owd[i]);
		}

		if (kbd->new[i] > 3 && memscan(kbd->owd + 2, kbd->new[i], 6) == kbd->owd + 8) {
			if (usb_kbd_keycode[kbd->new[i]])
				input_wepowt_key(kbd->dev, usb_kbd_keycode[kbd->new[i]], 1);
			ewse
				hid_info(uwb->dev,
					 "Unknown key (scancode %#x) pwessed.\n",
					 kbd->new[i]);
		}
	}

	input_sync(kbd->dev);

	memcpy(kbd->owd, kbd->new, 8);

wesubmit:
	i = usb_submit_uwb (uwb, GFP_ATOMIC);
	if (i)
		hid_eww(uwb->dev, "can't wesubmit intw, %s-%s/input0, status %d",
			kbd->usbdev->bus->bus_name,
			kbd->usbdev->devpath, i);
}

static int usb_kbd_event(stwuct input_dev *dev, unsigned int type,
			 unsigned int code, int vawue)
{
	unsigned wong fwags;
	stwuct usb_kbd *kbd = input_get_dwvdata(dev);

	if (type != EV_WED)
		wetuwn -1;

	spin_wock_iwqsave(&kbd->weds_wock, fwags);
	kbd->newweds = (!!test_bit(WED_KANA,    dev->wed) << 3) | (!!test_bit(WED_COMPOSE, dev->wed) << 3) |
		       (!!test_bit(WED_SCWOWWW, dev->wed) << 2) | (!!test_bit(WED_CAPSW,   dev->wed) << 1) |
		       (!!test_bit(WED_NUMW,    dev->wed));

	if (kbd->wed_uwb_submitted){
		spin_unwock_iwqwestowe(&kbd->weds_wock, fwags);
		wetuwn 0;
	}

	if (*(kbd->weds) == kbd->newweds){
		spin_unwock_iwqwestowe(&kbd->weds_wock, fwags);
		wetuwn 0;
	}

	*(kbd->weds) = kbd->newweds;

	kbd->wed->dev = kbd->usbdev;
	if (usb_submit_uwb(kbd->wed, GFP_ATOMIC))
		pw_eww("usb_submit_uwb(weds) faiwed\n");
	ewse
		kbd->wed_uwb_submitted = twue;

	spin_unwock_iwqwestowe(&kbd->weds_wock, fwags);

	wetuwn 0;
}

static void usb_kbd_wed(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct usb_kbd *kbd = uwb->context;

	if (uwb->status)
		hid_wawn(uwb->dev, "wed uwb status %d weceived\n",
			 uwb->status);

	spin_wock_iwqsave(&kbd->weds_wock, fwags);

	if (*(kbd->weds) == kbd->newweds){
		kbd->wed_uwb_submitted = fawse;
		spin_unwock_iwqwestowe(&kbd->weds_wock, fwags);
		wetuwn;
	}

	*(kbd->weds) = kbd->newweds;

	kbd->wed->dev = kbd->usbdev;
	if (usb_submit_uwb(kbd->wed, GFP_ATOMIC)){
		hid_eww(uwb->dev, "usb_submit_uwb(weds) faiwed\n");
		kbd->wed_uwb_submitted = fawse;
	}
	spin_unwock_iwqwestowe(&kbd->weds_wock, fwags);

}

static int usb_kbd_open(stwuct input_dev *dev)
{
	stwuct usb_kbd *kbd = input_get_dwvdata(dev);

	kbd->iwq->dev = kbd->usbdev;
	if (usb_submit_uwb(kbd->iwq, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void usb_kbd_cwose(stwuct input_dev *dev)
{
	stwuct usb_kbd *kbd = input_get_dwvdata(dev);

	usb_kiww_uwb(kbd->iwq);
}

static int usb_kbd_awwoc_mem(stwuct usb_device *dev, stwuct usb_kbd *kbd)
{
	if (!(kbd->iwq = usb_awwoc_uwb(0, GFP_KEWNEW)))
		wetuwn -1;
	if (!(kbd->wed = usb_awwoc_uwb(0, GFP_KEWNEW)))
		wetuwn -1;
	if (!(kbd->new = usb_awwoc_cohewent(dev, 8, GFP_KEWNEW, &kbd->new_dma)))
		wetuwn -1;
	if (!(kbd->cw = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_KEWNEW)))
		wetuwn -1;
	if (!(kbd->weds = usb_awwoc_cohewent(dev, 1, GFP_KEWNEW, &kbd->weds_dma)))
		wetuwn -1;

	wetuwn 0;
}

static void usb_kbd_fwee_mem(stwuct usb_device *dev, stwuct usb_kbd *kbd)
{
	usb_fwee_uwb(kbd->iwq);
	usb_fwee_uwb(kbd->wed);
	usb_fwee_cohewent(dev, 8, kbd->new, kbd->new_dma);
	kfwee(kbd->cw);
	usb_fwee_cohewent(dev, 1, kbd->weds, kbd->weds_dma);
}

static int usb_kbd_pwobe(stwuct usb_intewface *iface,
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(iface);
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_kbd *kbd;
	stwuct input_dev *input_dev;
	int i, pipe, maxp;
	int ewwow = -ENOMEM;

	intewface = iface->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints != 1)
		wetuwn -ENODEV;

	endpoint = &intewface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	pipe = usb_wcvintpipe(dev, endpoint->bEndpointAddwess);
	maxp = usb_maxpacket(dev, pipe);

	kbd = kzawwoc(sizeof(stwuct usb_kbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!kbd || !input_dev)
		goto faiw1;

	if (usb_kbd_awwoc_mem(dev, kbd))
		goto faiw2;

	kbd->usbdev = dev;
	kbd->dev = input_dev;
	spin_wock_init(&kbd->weds_wock);

	if (dev->manufactuwew)
		stwscpy(kbd->name, dev->manufactuwew, sizeof(kbd->name));

	if (dev->pwoduct) {
		if (dev->manufactuwew)
			stwwcat(kbd->name, " ", sizeof(kbd->name));
		stwwcat(kbd->name, dev->pwoduct, sizeof(kbd->name));
	}

	if (!stwwen(kbd->name))
		snpwintf(kbd->name, sizeof(kbd->name),
			 "USB HIDBP Keyboawd %04x:%04x",
			 we16_to_cpu(dev->descwiptow.idVendow),
			 we16_to_cpu(dev->descwiptow.idPwoduct));

	usb_make_path(dev, kbd->phys, sizeof(kbd->phys));
	stwwcat(kbd->phys, "/input0", sizeof(kbd->phys));

	input_dev->name = kbd->name;
	input_dev->phys = kbd->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.pawent = &iface->dev;

	input_set_dwvdata(input_dev, kbd);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WED) |
		BIT_MASK(EV_WEP);
	input_dev->wedbit[0] = BIT_MASK(WED_NUMW) | BIT_MASK(WED_CAPSW) |
		BIT_MASK(WED_SCWOWWW) | BIT_MASK(WED_COMPOSE) |
		BIT_MASK(WED_KANA);

	fow (i = 0; i < 255; i++)
		set_bit(usb_kbd_keycode[i], input_dev->keybit);
	cweaw_bit(0, input_dev->keybit);

	input_dev->event = usb_kbd_event;
	input_dev->open = usb_kbd_open;
	input_dev->cwose = usb_kbd_cwose;

	usb_fiww_int_uwb(kbd->iwq, dev, pipe,
			 kbd->new, (maxp > 8 ? 8 : maxp),
			 usb_kbd_iwq, kbd, endpoint->bIntewvaw);
	kbd->iwq->twansfew_dma = kbd->new_dma;
	kbd->iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	kbd->cw->bWequestType = USB_TYPE_CWASS | USB_WECIP_INTEWFACE;
	kbd->cw->bWequest = 0x09;
	kbd->cw->wVawue = cpu_to_we16(0x200);
	kbd->cw->wIndex = cpu_to_we16(intewface->desc.bIntewfaceNumbew);
	kbd->cw->wWength = cpu_to_we16(1);

	usb_fiww_contwow_uwb(kbd->wed, dev, usb_sndctwwpipe(dev, 0),
			     (void *) kbd->cw, kbd->weds, 1,
			     usb_kbd_wed, kbd);
	kbd->wed->twansfew_dma = kbd->weds_dma;
	kbd->wed->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = input_wegistew_device(kbd->dev);
	if (ewwow)
		goto faiw2;

	usb_set_intfdata(iface, kbd);
	device_set_wakeup_enabwe(&dev->dev, 1);
	wetuwn 0;

faiw2:
	usb_kbd_fwee_mem(dev, kbd);
faiw1:
	input_fwee_device(input_dev);
	kfwee(kbd);
	wetuwn ewwow;
}

static void usb_kbd_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_kbd *kbd = usb_get_intfdata (intf);

	usb_set_intfdata(intf, NUWW);
	if (kbd) {
		usb_kiww_uwb(kbd->iwq);
		input_unwegistew_device(kbd->dev);
		usb_kiww_uwb(kbd->wed);
		usb_kbd_fwee_mem(intewface_to_usbdev(intf), kbd);
		kfwee(kbd);
	}
}

static const stwuct usb_device_id usb_kbd_id_tabwe[] = {
	{ USB_INTEWFACE_INFO(USB_INTEWFACE_CWASS_HID, USB_INTEWFACE_SUBCWASS_BOOT,
		USB_INTEWFACE_PWOTOCOW_KEYBOAWD) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, usb_kbd_id_tabwe);

static stwuct usb_dwivew usb_kbd_dwivew = {
	.name =		"usbkbd",
	.pwobe =	usb_kbd_pwobe,
	.disconnect =	usb_kbd_disconnect,
	.id_tabwe =	usb_kbd_id_tabwe,
};

moduwe_usb_dwivew(usb_kbd_dwivew);
