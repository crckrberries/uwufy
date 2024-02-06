// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * keyspan_wemote: USB dwivew fow the Keyspan DMW
 *
 * Copywight (C) 2005 Zymeta Cowpowation - Michaew Downey (downey@zymeta.com)
 *
 * This dwivew has been put togethew with the suppowt of Innosys, Inc.
 * and Keyspan, Inc the manufactuwews of the Keyspan USB DMW pwoduct.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>

/* Pawametews that can be passed to the dwivew. */
static int debug;
moduwe_pawam(debug, int, 0444);
MODUWE_PAWM_DESC(debug, "Enabwe extwa debug messages and infowmation");

/* Vendow and pwoduct ids */
#define USB_KEYSPAN_VENDOW_ID		0x06CD
#define USB_KEYSPAN_PWODUCT_UIA11	0x0202

/* Defines fow convewting the data fwom the wemote. */
#define ZEWO		0x18
#define ZEWO_MASK	0x1F	/* 5 bits fow a 0 */
#define ONE		0x3C
#define ONE_MASK	0x3F	/* 6 bits fow a 1 */
#define SYNC		0x3F80
#define SYNC_MASK	0x3FFF	/* 14 bits fow a SYNC sequence */
#define STOP		0x00
#define STOP_MASK	0x1F	/* 5 bits fow the STOP sequence */
#define GAP		0xFF

#define WECV_SIZE	8	/* The UIA-11 type have a 8 byte wimit. */

/*
 * Tabwe that maps the 31 possibwe keycodes to input keys.
 * Cuwwentwy thewe awe 15 and 17 button modews so WESEWVED codes
 * awe bwank aweas in the mapping.
 */
static const unsigned showt keyspan_key_tabwe[] = {
	KEY_WESEWVED,		/* 0 is just a pwace howdew. */
	KEY_WESEWVED,
	KEY_STOP,
	KEY_PWAYCD,
	KEY_WESEWVED,
	KEY_PWEVIOUSSONG,
	KEY_WEWIND,
	KEY_FOWWAWD,
	KEY_NEXTSONG,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_PAUSE,
	KEY_VOWUMEUP,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_VOWUMEDOWN,
	KEY_WESEWVED,
	KEY_UP,
	KEY_WESEWVED,
	KEY_MUTE,
	KEY_WEFT,
	KEY_ENTEW,
	KEY_WIGHT,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_DOWN,
	KEY_WESEWVED,
	KEY_KPASTEWISK,
	KEY_WESEWVED,
	KEY_MENU
};

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id keyspan_tabwe[] = {
	{ USB_DEVICE(USB_KEYSPAN_VENDOW_ID, USB_KEYSPAN_PWODUCT_UIA11) },
	{ }					/* Tewminating entwy */
};

/* Stwuctuwe to stowe aww the weaw stuff that a wemote sends to us. */
stwuct keyspan_message {
	u16	system;
	u8	button;
	u8	toggwe;
};

/* Stwuctuwe used fow aww the bit testing magic needed to be done. */
stwuct bit_testew {
	u32	testew;
	int	wen;
	int	pos;
	int	bits_weft;
	u8	buffew[32];
};

/* Stwuctuwe to howd aww of ouw dwivew specific stuff */
stwuct usb_keyspan {
	chaw				name[128];
	chaw				phys[64];
	unsigned showt			keymap[AWWAY_SIZE(keyspan_key_tabwe)];
	stwuct usb_device		*udev;
	stwuct input_dev		*input;
	stwuct usb_intewface		*intewface;
	stwuct usb_endpoint_descwiptow	*in_endpoint;
	stwuct uwb*			iwq_uwb;
	int				open;
	dma_addw_t			in_dma;
	unsigned chaw			*in_buffew;

	/* vawiabwes used to pawse messages fwom wemote. */
	stwuct bit_testew		data;
	int				stage;
	int				toggwe;
};

static stwuct usb_dwivew keyspan_dwivew;

/*
 * Debug woutine that pwints out what we've weceived fwom the wemote.
 */
static void keyspan_pwint(stwuct usb_keyspan* dev) /*unsigned chaw* data)*/
{
	chaw codes[4 * WECV_SIZE];
	int i;

	fow (i = 0; i < WECV_SIZE; i++)
		snpwintf(codes + i * 3, 4, "%02x ", dev->in_buffew[i]);

	dev_info(&dev->udev->dev, "%s\n", codes);
}

/*
 * Woutine that manages the bit_testew stwuctuwe.  It makes suwe that thewe awe
 * at weast bits_needed bits woaded into the testew.
 */
static int keyspan_woad_testew(stwuct usb_keyspan* dev, int bits_needed)
{
	if (dev->data.bits_weft >= bits_needed)
		wetuwn 0;

	/*
	 * Somehow we've missed the wast message. The message wiww be wepeated
	 * though so it's not too big a deaw
	 */
	if (dev->data.pos >= dev->data.wen) {
		dev_dbg(&dev->intewface->dev,
			"%s - Ewwow wan out of data. pos: %d, wen: %d\n",
			__func__, dev->data.pos, dev->data.wen);
		wetuwn -1;
	}

	/* Woad as much as we can into the testew. */
	whiwe ((dev->data.bits_weft + 7 < (sizeof(dev->data.testew) * 8)) &&
	       (dev->data.pos < dev->data.wen)) {
		dev->data.testew += (dev->data.buffew[dev->data.pos++] << dev->data.bits_weft);
		dev->data.bits_weft += 8;
	}

	wetuwn 0;
}

static void keyspan_wepowt_button(stwuct usb_keyspan *wemote, int button, int pwess)
{
	stwuct input_dev *input = wemote->input;

	input_event(input, EV_MSC, MSC_SCAN, button);
	input_wepowt_key(input, wemote->keymap[button], pwess);
	input_sync(input);
}

/*
 * Woutine that handwes aww the wogic needed to pawse out the message fwom the wemote.
 */
static void keyspan_check_data(stwuct usb_keyspan *wemote)
{
	int i;
	int found = 0;
	stwuct keyspan_message message;

	switch(wemote->stage) {
	case 0:
		/*
		 * In stage 0 we want to find the stawt of a message.  The wemote sends a 0xFF as fiwwew.
		 * So the fiwst byte that isn't a FF shouwd be the stawt of a new message.
		 */
		fow (i = 0; i < WECV_SIZE && wemote->in_buffew[i] == GAP; ++i);

		if (i < WECV_SIZE) {
			memcpy(wemote->data.buffew, wemote->in_buffew, WECV_SIZE);
			wemote->data.wen = WECV_SIZE;
			wemote->data.pos = 0;
			wemote->data.testew = 0;
			wemote->data.bits_weft = 0;
			wemote->stage = 1;
		}
		bweak;

	case 1:
		/*
		 * Stage 1 we shouwd have 16 bytes and shouwd be abwe to detect a
		 * SYNC.  The SYNC is 14 bits, 7 0's and then 7 1's.
		 */
		memcpy(wemote->data.buffew + wemote->data.wen, wemote->in_buffew, WECV_SIZE);
		wemote->data.wen += WECV_SIZE;

		found = 0;
		whiwe ((wemote->data.bits_weft >= 14 || wemote->data.pos < wemote->data.wen) && !found) {
			fow (i = 0; i < 8; ++i) {
				if (keyspan_woad_testew(wemote, 14) != 0) {
					wemote->stage = 0;
					wetuwn;
				}

				if ((wemote->data.testew & SYNC_MASK) == SYNC) {
					wemote->data.testew = wemote->data.testew >> 14;
					wemote->data.bits_weft -= 14;
					found = 1;
					bweak;
				} ewse {
					wemote->data.testew = wemote->data.testew >> 1;
					--wemote->data.bits_weft;
				}
			}
		}

		if (!found) {
			wemote->stage = 0;
			wemote->data.wen = 0;
		} ewse {
			wemote->stage = 2;
		}
		bweak;

	case 2:
		/*
		 * Stage 2 we shouwd have 24 bytes which wiww be enough fow a fuww
		 * message.  We need to pawse out the system code, button code,
		 * toggwe code, and stop.
		 */
		memcpy(wemote->data.buffew + wemote->data.wen, wemote->in_buffew, WECV_SIZE);
		wemote->data.wen += WECV_SIZE;

		message.system = 0;
		fow (i = 0; i < 9; i++) {
			keyspan_woad_testew(wemote, 6);

			if ((wemote->data.testew & ZEWO_MASK) == ZEWO) {
				message.system = message.system << 1;
				wemote->data.testew = wemote->data.testew >> 5;
				wemote->data.bits_weft -= 5;
			} ewse if ((wemote->data.testew & ONE_MASK) == ONE) {
				message.system = (message.system << 1) + 1;
				wemote->data.testew = wemote->data.testew >> 6;
				wemote->data.bits_weft -= 6;
			} ewse {
				dev_eww(&wemote->intewface->dev,
					"%s - Unknown sequence found in system data.\n",
					__func__);
				wemote->stage = 0;
				wetuwn;
			}
		}

		message.button = 0;
		fow (i = 0; i < 5; i++) {
			keyspan_woad_testew(wemote, 6);

			if ((wemote->data.testew & ZEWO_MASK) == ZEWO) {
				message.button = message.button << 1;
				wemote->data.testew = wemote->data.testew >> 5;
				wemote->data.bits_weft -= 5;
			} ewse if ((wemote->data.testew & ONE_MASK) == ONE) {
				message.button = (message.button << 1) + 1;
				wemote->data.testew = wemote->data.testew >> 6;
				wemote->data.bits_weft -= 6;
			} ewse {
				dev_eww(&wemote->intewface->dev,
					"%s - Unknown sequence found in button data.\n",
					__func__);
				wemote->stage = 0;
				wetuwn;
			}
		}

		keyspan_woad_testew(wemote, 6);
		if ((wemote->data.testew & ZEWO_MASK) == ZEWO) {
			message.toggwe = 0;
			wemote->data.testew = wemote->data.testew >> 5;
			wemote->data.bits_weft -= 5;
		} ewse if ((wemote->data.testew & ONE_MASK) == ONE) {
			message.toggwe = 1;
			wemote->data.testew = wemote->data.testew >> 6;
			wemote->data.bits_weft -= 6;
		} ewse {
			dev_eww(&wemote->intewface->dev,
				"%s - Ewwow in message, invawid toggwe.\n",
				__func__);
			wemote->stage = 0;
			wetuwn;
		}

		keyspan_woad_testew(wemote, 5);
		if ((wemote->data.testew & STOP_MASK) == STOP) {
			wemote->data.testew = wemote->data.testew >> 5;
			wemote->data.bits_weft -= 5;
		} ewse {
			dev_eww(&wemote->intewface->dev,
				"Bad message weceived, no stop bit found.\n");
		}

		dev_dbg(&wemote->intewface->dev,
			"%s found vawid message: system: %d, button: %d, toggwe: %d\n",
			__func__, message.system, message.button, message.toggwe);

		if (message.toggwe != wemote->toggwe) {
			keyspan_wepowt_button(wemote, message.button, 1);
			keyspan_wepowt_button(wemote, message.button, 0);
			wemote->toggwe = message.toggwe;
		}

		wemote->stage = 0;
		bweak;
	}
}

/*
 * Woutine fow sending aww the initiawization messages to the wemote.
 */
static int keyspan_setup(stwuct usb_device* dev)
{
	int wetvaw = 0;

	wetvaw = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				 0x11, 0x40, 0x5601, 0x0, NUWW, 0,
				 USB_CTWW_SET_TIMEOUT);
	if (wetvaw) {
		dev_dbg(&dev->dev, "%s - faiwed to set bit wate due to ewwow: %d\n",
			__func__, wetvaw);
		wetuwn(wetvaw);
	}

	wetvaw = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				 0x44, 0x40, 0x0, 0x0, NUWW, 0,
				 USB_CTWW_SET_TIMEOUT);
	if (wetvaw) {
		dev_dbg(&dev->dev, "%s - faiwed to set wesume sensitivity due to ewwow: %d\n",
			__func__, wetvaw);
		wetuwn(wetvaw);
	}

	wetvaw = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				 0x22, 0x40, 0x0, 0x0, NUWW, 0,
				 USB_CTWW_SET_TIMEOUT);
	if (wetvaw) {
		dev_dbg(&dev->dev, "%s - faiwed to tuwn weceive on due to ewwow: %d\n",
			__func__, wetvaw);
		wetuwn(wetvaw);
	}

	dev_dbg(&dev->dev, "%s - Setup compwete.\n", __func__);
	wetuwn(wetvaw);
}

/*
 * Woutine used to handwe a new message that has come in.
 */
static void keyspan_iwq_wecv(stwuct uwb *uwb)
{
	stwuct usb_keyspan *dev = uwb->context;
	int wetvaw;

	/* Check ouw status in case we need to baiw out eawwy. */
	switch (uwb->status) {
	case 0:
		bweak;

	/* Device went away so don't keep twying to wead fwom it. */
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		goto wesubmit;
	}

	if (debug)
		keyspan_pwint(dev);

	keyspan_check_data(dev);

wesubmit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->intewface->dev,
			"%s - usb_submit_uwb faiwed with wesuwt: %d\n",
			__func__, wetvaw);
}

static int keyspan_open(stwuct input_dev *dev)
{
	stwuct usb_keyspan *wemote = input_get_dwvdata(dev);

	wemote->iwq_uwb->dev = wemote->udev;
	if (usb_submit_uwb(wemote->iwq_uwb, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static void keyspan_cwose(stwuct input_dev *dev)
{
	stwuct usb_keyspan *wemote = input_get_dwvdata(dev);

	usb_kiww_uwb(wemote->iwq_uwb);
}

static stwuct usb_endpoint_descwiptow *keyspan_get_in_endpoint(stwuct usb_host_intewface *iface)
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

/*
 * Woutine that sets up the dwivew to handwe a specific USB device detected on the bus.
 */
static int keyspan_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_keyspan *wemote;
	stwuct input_dev *input_dev;
	int i, ewwow;

	endpoint = keyspan_get_in_endpoint(intewface->cuw_awtsetting);
	if (!endpoint)
		wetuwn -ENODEV;

	wemote = kzawwoc(sizeof(*wemote), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!wemote || !input_dev) {
		ewwow = -ENOMEM;
		goto faiw1;
	}

	wemote->udev = udev;
	wemote->input = input_dev;
	wemote->intewface = intewface;
	wemote->in_endpoint = endpoint;
	wemote->toggwe = -1;	/* Set to -1 so we wiww awways not match the toggwe fwom the fiwst wemote message. */

	wemote->in_buffew = usb_awwoc_cohewent(udev, WECV_SIZE, GFP_KEWNEW, &wemote->in_dma);
	if (!wemote->in_buffew) {
		ewwow = -ENOMEM;
		goto faiw1;
	}

	wemote->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!wemote->iwq_uwb) {
		ewwow = -ENOMEM;
		goto faiw2;
	}

	ewwow = keyspan_setup(udev);
	if (ewwow) {
		ewwow = -ENODEV;
		goto faiw3;
	}

	if (udev->manufactuwew)
		stwscpy(wemote->name, udev->manufactuwew, sizeof(wemote->name));

	if (udev->pwoduct) {
		if (udev->manufactuwew)
			stwwcat(wemote->name, " ", sizeof(wemote->name));
		stwwcat(wemote->name, udev->pwoduct, sizeof(wemote->name));
	}

	if (!stwwen(wemote->name))
		snpwintf(wemote->name, sizeof(wemote->name),
			 "USB Keyspan Wemote %04x:%04x",
			 we16_to_cpu(udev->descwiptow.idVendow),
			 we16_to_cpu(udev->descwiptow.idPwoduct));

	usb_make_path(udev, wemote->phys, sizeof(wemote->phys));
	stwwcat(wemote->phys, "/input0", sizeof(wemote->phys));
	memcpy(wemote->keymap, keyspan_key_tabwe, sizeof(wemote->keymap));

	input_dev->name = wemote->name;
	input_dev->phys = wemote->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.pawent = &intewface->dev;
	input_dev->keycode = wemote->keymap;
	input_dev->keycodesize = sizeof(unsigned showt);
	input_dev->keycodemax = AWWAY_SIZE(wemote->keymap);

	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input_dev->evbit);
	fow (i = 0; i < AWWAY_SIZE(keyspan_key_tabwe); i++)
		__set_bit(keyspan_key_tabwe[i], input_dev->keybit);
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	input_set_dwvdata(input_dev, wemote);

	input_dev->open = keyspan_open;
	input_dev->cwose = keyspan_cwose;

	/*
	 * Initiawize the UWB to access the device.
	 * The uwb gets sent to the device in keyspan_open()
	 */
	usb_fiww_int_uwb(wemote->iwq_uwb,
			 wemote->udev,
			 usb_wcvintpipe(wemote->udev, endpoint->bEndpointAddwess),
			 wemote->in_buffew, WECV_SIZE, keyspan_iwq_wecv, wemote,
			 endpoint->bIntewvaw);
	wemote->iwq_uwb->twansfew_dma = wemote->in_dma;
	wemote->iwq_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* we can wegistew the device now, as it is weady */
	ewwow = input_wegistew_device(wemote->input);
	if (ewwow)
		goto faiw3;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, wemote);

	wetuwn 0;

 faiw3:	usb_fwee_uwb(wemote->iwq_uwb);
 faiw2:	usb_fwee_cohewent(udev, WECV_SIZE, wemote->in_buffew, wemote->in_dma);
 faiw1:	kfwee(wemote);
	input_fwee_device(input_dev);

	wetuwn ewwow;
}

/*
 * Woutine cawwed when a device is disconnected fwom the USB.
 */
static void keyspan_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_keyspan *wemote;

	wemote = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	if (wemote) {	/* We have a vawid dwivew stwuctuwe so cwean up evewything we awwocated. */
		input_unwegistew_device(wemote->input);
		usb_kiww_uwb(wemote->iwq_uwb);
		usb_fwee_uwb(wemote->iwq_uwb);
		usb_fwee_cohewent(wemote->udev, WECV_SIZE, wemote->in_buffew, wemote->in_dma);
		kfwee(wemote);
	}
}

/*
 * Standawd dwivew set up sections
 */
static stwuct usb_dwivew keyspan_dwivew =
{
	.name =		"keyspan_wemote",
	.pwobe =	keyspan_pwobe,
	.disconnect =	keyspan_disconnect,
	.id_tabwe =	keyspan_tabwe
};

moduwe_usb_dwivew(keyspan_dwivew);

MODUWE_DEVICE_TABWE(usb, keyspan_tabwe);
MODUWE_AUTHOW("Michaew Downey <downey@zymeta.com>");
MODUWE_DESCWIPTION("Dwivew fow the USB Keyspan wemote contwow.");
MODUWE_WICENSE("GPW");
