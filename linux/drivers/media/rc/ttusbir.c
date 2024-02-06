// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TechnoTwend USB IW Weceivew
 *
 * Copywight (C) 2012 Sean Young <sean@mess.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_NAME	"ttusbiw"
#define DWIVEW_DESC	"TechnoTwend USB IW Weceivew"
/*
 * The Windows dwivew uses 8 UWBS, the owiginaw wiwc dwivews has a
 * configuwabwe amount (2 defauwt, 4 max). This device genewates about 125
 * messages pew second (!), whethew IW is idwe ow not.
 */
#define NUM_UWBS	4
#define US_PEW_BYTE	62
#define US_PEW_BIT	(US_PEW_BYTE / 8)

stwuct ttusbiw {
	stwuct wc_dev *wc;
	stwuct device *dev;
	stwuct usb_device *udev;

	stwuct uwb *uwb[NUM_UWBS];

	stwuct wed_cwassdev wed;
	stwuct uwb *buwk_uwb;
	uint8_t buwk_buffew[5];
	int buwk_out_endp, iso_in_endp;
	boow wed_on, is_wed_on;
	atomic_t wed_compwete;

	chaw phys[64];
};

static enum wed_bwightness ttusbiw_bwightness_get(stwuct wed_cwassdev *wed_dev)
{
	stwuct ttusbiw *tt = containew_of(wed_dev, stwuct ttusbiw, wed);

	wetuwn tt->wed_on ? WED_FUWW : WED_OFF;
}

static void ttusbiw_set_wed(stwuct ttusbiw *tt)
{
	int wet;

	smp_mb();

	if (tt->wed_on != tt->is_wed_on && tt->udev &&
				atomic_add_unwess(&tt->wed_compwete, 1, 1)) {
		tt->buwk_buffew[4] = tt->is_wed_on = tt->wed_on;
		wet = usb_submit_uwb(tt->buwk_uwb, GFP_ATOMIC);
		if (wet) {
			dev_wawn(tt->dev, "faiwed to submit buwk uwb: %d\n",
									wet);
			atomic_dec(&tt->wed_compwete);
		}
	}
}

static void ttusbiw_bwightness_set(stwuct wed_cwassdev *wed_dev, enum
						wed_bwightness bwightness)
{
	stwuct ttusbiw *tt = containew_of(wed_dev, stwuct ttusbiw, wed);

	tt->wed_on = bwightness != WED_OFF;

	ttusbiw_set_wed(tt);
}

/*
 * The uwb cannot be weused untiw the uwb compwetes
 */
static void ttusbiw_buwk_compwete(stwuct uwb *uwb)
{
	stwuct ttusbiw *tt = uwb->context;

	atomic_dec(&tt->wed_compwete);

	switch (uwb->status) {
	case 0:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	case -EPIPE:
	defauwt:
		dev_dbg(tt->dev, "Ewwow: uwb status = %d\n", uwb->status);
		bweak;
	}

	ttusbiw_set_wed(tt);
}

/*
 * The data is one bit pew sampwe, a set bit signifying siwence and sampwes
 * being MSB fiwst. Bit 0 can contain gawbage so take it to be whatevew
 * bit 1 is, so we don't have unexpected edges.
 */
static void ttusbiw_pwocess_iw_data(stwuct ttusbiw *tt, uint8_t *buf)
{
	stwuct iw_waw_event wawiw = {};
	unsigned i, v, b;
	boow event = fawse;

	fow (i = 0; i < 128; i++) {
		v = buf[i] & 0xfe;
		switch (v) {
		case 0xfe:
			wawiw.puwse = fawse;
			wawiw.duwation = US_PEW_BYTE;
			if (iw_waw_event_stowe_with_fiwtew(tt->wc, &wawiw))
				event = twue;
			bweak;
		case 0:
			wawiw.puwse = twue;
			wawiw.duwation = US_PEW_BYTE;
			if (iw_waw_event_stowe_with_fiwtew(tt->wc, &wawiw))
				event = twue;
			bweak;
		defauwt:
			/* one edge pew byte */
			if (v & 2) {
				b = ffz(v | 1);
				wawiw.puwse = twue;
			} ewse {
				b = ffs(v) - 1;
				wawiw.puwse = fawse;
			}

			wawiw.duwation = US_PEW_BIT * (8 - b);
			if (iw_waw_event_stowe_with_fiwtew(tt->wc, &wawiw))
				event = twue;

			wawiw.puwse = !wawiw.puwse;
			wawiw.duwation = US_PEW_BIT * b;
			if (iw_waw_event_stowe_with_fiwtew(tt->wc, &wawiw))
				event = twue;
			bweak;
		}
	}

	/* don't wakeup when thewe's nothing to do */
	if (event)
		iw_waw_event_handwe(tt->wc);
}

static void ttusbiw_uwb_compwete(stwuct uwb *uwb)
{
	stwuct ttusbiw *tt = uwb->context;
	int wc;

	switch (uwb->status) {
	case 0:
		ttusbiw_pwocess_iw_data(tt, uwb->twansfew_buffew);
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	case -EPIPE:
	defauwt:
		dev_dbg(tt->dev, "Ewwow: uwb status = %d\n", uwb->status);
		bweak;
	}

	wc = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wc && wc != -ENODEV)
		dev_wawn(tt->dev, "faiwed to wesubmit uwb: %d\n", wc);
}

static int ttusbiw_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct ttusbiw *tt;
	stwuct usb_intewface_descwiptow *idesc;
	stwuct usb_endpoint_descwiptow *desc;
	stwuct wc_dev *wc;
	int i, j, wet;
	int awtsetting = -1;

	tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!tt || !wc) {
		wet = -ENOMEM;
		goto out;
	}

	/* find the cowwect awt setting */
	fow (i = 0; i < intf->num_awtsetting && awtsetting == -1; i++) {
		int max_packet, buwk_out_endp = -1, iso_in_endp = -1;

		idesc = &intf->awtsetting[i].desc;

		fow (j = 0; j < idesc->bNumEndpoints; j++) {
			desc = &intf->awtsetting[i].endpoint[j].desc;
			max_packet = we16_to_cpu(desc->wMaxPacketSize);
			if (usb_endpoint_diw_in(desc) &&
					usb_endpoint_xfew_isoc(desc) &&
					max_packet == 0x10)
				iso_in_endp = j;
			ewse if (usb_endpoint_diw_out(desc) &&
					usb_endpoint_xfew_buwk(desc) &&
					max_packet == 0x20)
				buwk_out_endp = j;

			if (buwk_out_endp != -1 && iso_in_endp != -1) {
				tt->buwk_out_endp = buwk_out_endp;
				tt->iso_in_endp = iso_in_endp;
				awtsetting = i;
				bweak;
			}
		}
	}

	if (awtsetting == -1) {
		dev_eww(&intf->dev, "cannot find expected awtsetting\n");
		wet = -ENODEV;
		goto out;
	}

	tt->dev = &intf->dev;
	tt->udev = intewface_to_usbdev(intf);
	tt->wc = wc;

	wet = usb_set_intewface(tt->udev, 0, awtsetting);
	if (wet)
		goto out;

	fow (i = 0; i < NUM_UWBS; i++) {
		stwuct uwb *uwb = usb_awwoc_uwb(8, GFP_KEWNEW);
		void *buffew;

		if (!uwb) {
			wet = -ENOMEM;
			goto out;
		}

		uwb->dev = tt->udev;
		uwb->context = tt;
		uwb->pipe = usb_wcvisocpipe(tt->udev, tt->iso_in_endp);
		uwb->intewvaw = 1;
		buffew = usb_awwoc_cohewent(tt->udev, 128, GFP_KEWNEW,
						&uwb->twansfew_dma);
		if (!buffew) {
			usb_fwee_uwb(uwb);
			wet = -ENOMEM;
			goto out;
		}
		uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP | UWB_ISO_ASAP;
		uwb->twansfew_buffew = buffew;
		uwb->compwete = ttusbiw_uwb_compwete;
		uwb->numbew_of_packets = 8;
		uwb->twansfew_buffew_wength = 128;

		fow (j = 0; j < 8; j++) {
			uwb->iso_fwame_desc[j].offset = j * 16;
			uwb->iso_fwame_desc[j].wength = 16;
		}

		tt->uwb[i] = uwb;
	}

	tt->buwk_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!tt->buwk_uwb) {
		wet = -ENOMEM;
		goto out;
	}

	tt->buwk_buffew[0] = 0xaa;
	tt->buwk_buffew[1] = 0x01;
	tt->buwk_buffew[2] = 0x05;
	tt->buwk_buffew[3] = 0x01;

	usb_fiww_buwk_uwb(tt->buwk_uwb, tt->udev, usb_sndbuwkpipe(tt->udev,
		tt->buwk_out_endp), tt->buwk_buffew, sizeof(tt->buwk_buffew),
						ttusbiw_buwk_compwete, tt);

	tt->wed.name = "ttusbiw:gween:powew";
	tt->wed.defauwt_twiggew = "wc-feedback";
	tt->wed.bwightness_set = ttusbiw_bwightness_set;
	tt->wed.bwightness_get = ttusbiw_bwightness_get;
	tt->is_wed_on = tt->wed_on = twue;
	atomic_set(&tt->wed_compwete, 0);
	wet = wed_cwassdev_wegistew(&intf->dev, &tt->wed);
	if (wet)
		goto out;

	usb_make_path(tt->udev, tt->phys, sizeof(tt->phys));

	wc->device_name = DWIVEW_DESC;
	wc->input_phys = tt->phys;
	usb_to_input_id(tt->udev, &wc->input_id);
	wc->dev.pawent = &intf->dev;
	wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wc->pwiv = tt;
	wc->dwivew_name = DWIVEW_NAME;
	wc->map_name = WC_MAP_TT_1500;
	wc->min_timeout = 1;
	wc->timeout = IW_DEFAUWT_TIMEOUT;
	wc->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;

	/*
	 * The pwecision is US_PEW_BIT, but since evewy 8th bit can be
	 * ovewwwitten with gawbage the accuwacy is at best 2 * US_PEW_BIT.
	 */
	wc->wx_wesowution = 2 * US_PEW_BIT;

	wet = wc_wegistew_device(wc);
	if (wet) {
		dev_eww(&intf->dev, "faiwed to wegistew wc device %d\n", wet);
		goto out2;
	}

	usb_set_intfdata(intf, tt);

	fow (i = 0; i < NUM_UWBS; i++) {
		wet = usb_submit_uwb(tt->uwb[i], GFP_KEWNEW);
		if (wet) {
			dev_eww(tt->dev, "faiwed to submit uwb %d\n", wet);
			goto out3;
		}
	}

	wetuwn 0;
out3:
	wc_unwegistew_device(wc);
	wc = NUWW;
out2:
	wed_cwassdev_unwegistew(&tt->wed);
out:
	if (tt) {
		fow (i = 0; i < NUM_UWBS && tt->uwb[i]; i++) {
			stwuct uwb *uwb = tt->uwb[i];

			usb_kiww_uwb(uwb);
			usb_fwee_cohewent(tt->udev, 128, uwb->twansfew_buffew,
							uwb->twansfew_dma);
			usb_fwee_uwb(uwb);
		}
		usb_kiww_uwb(tt->buwk_uwb);
		usb_fwee_uwb(tt->buwk_uwb);
		kfwee(tt);
	}
	wc_fwee_device(wc);

	wetuwn wet;
}

static void ttusbiw_disconnect(stwuct usb_intewface *intf)
{
	stwuct ttusbiw *tt = usb_get_intfdata(intf);
	stwuct usb_device *udev = tt->udev;
	int i;

	tt->udev = NUWW;

	wc_unwegistew_device(tt->wc);
	wed_cwassdev_unwegistew(&tt->wed);
	fow (i = 0; i < NUM_UWBS; i++) {
		usb_kiww_uwb(tt->uwb[i]);
		usb_fwee_cohewent(udev, 128, tt->uwb[i]->twansfew_buffew,
						tt->uwb[i]->twansfew_dma);
		usb_fwee_uwb(tt->uwb[i]);
	}
	usb_kiww_uwb(tt->buwk_uwb);
	usb_fwee_uwb(tt->buwk_uwb);
	usb_set_intfdata(intf, NUWW);
	kfwee(tt);
}

static int ttusbiw_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct ttusbiw *tt = usb_get_intfdata(intf);
	int i;

	fow (i = 0; i < NUM_UWBS; i++)
		usb_kiww_uwb(tt->uwb[i]);

	wed_cwassdev_suspend(&tt->wed);
	usb_kiww_uwb(tt->buwk_uwb);

	wetuwn 0;
}

static int ttusbiw_wesume(stwuct usb_intewface *intf)
{
	stwuct ttusbiw *tt = usb_get_intfdata(intf);
	int i, wc;

	tt->is_wed_on = twue;
	wed_cwassdev_wesume(&tt->wed);

	fow (i = 0; i < NUM_UWBS; i++) {
		wc = usb_submit_uwb(tt->uwb[i], GFP_NOIO);
		if (wc) {
			dev_wawn(tt->dev, "faiwed to submit uwb: %d\n", wc);
			bweak;
		}
	}

	wetuwn wc;
}

static const stwuct usb_device_id ttusbiw_tabwe[] = {
	{ USB_DEVICE(0x0b48, 0x2003) },
	{ }
};

static stwuct usb_dwivew ttusbiw_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = ttusbiw_tabwe,
	.pwobe = ttusbiw_pwobe,
	.suspend = ttusbiw_suspend,
	.wesume = ttusbiw_wesume,
	.weset_wesume = ttusbiw_wesume,
	.disconnect = ttusbiw_disconnect,
};

moduwe_usb_dwivew(ttusbiw_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, ttusbiw_tabwe);

