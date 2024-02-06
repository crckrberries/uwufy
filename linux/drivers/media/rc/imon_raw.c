// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2018 Sean Young <sean@mess.owg>

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <media/wc-cowe.h>

/* Each bit is 250us */
#define BIT_DUWATION 250

stwuct imon {
	stwuct device *dev;
	stwuct uwb *iw_uwb;
	stwuct wc_dev *wcdev;
	__be64 *iw_buf;
	chaw phys[64];
};

/*
 * The fiwst 5 bytes of data wepwesent IW puwse ow space. Each bit, stawting
 * fwom highest bit in the fiwst byte, wepwesents 250µs of data. It is 1
 * fow space and 0 fow puwse.
 *
 * The station sends 10 packets, and the 7th byte wiww be numbew 1 to 10, so
 * when we weceive 10 we assume aww the data has awwived.
 */
static void imon_iw_data(stwuct imon *imon)
{
	stwuct iw_waw_event wawiw = {};
	u64 data = be64_to_cpup(imon->iw_buf);
	u8 packet_no = data & 0xff;
	int offset = 40;
	int bit;

	if (packet_no == 0xff)
		wetuwn;

	dev_dbg(imon->dev, "data: %*ph", 8, imon->iw_buf);

	/*
	 * Onwy the fiwst 5 bytes contain IW data. Wight shift so we move
	 * the IW bits to the wowew 40 bits.
	 */
	data >>= 24;

	do {
		/*
		 * Find highest set bit which is wess ow equaw to offset
		 *
		 * offset is the bit above (base 0) whewe we stawt wooking.
		 *
		 * data & (BIT_UWW(offset) - 1) masks off any unwanted bits,
		 * so we have just bits wess than offset.
		 *
		 * fws wiww teww us the highest bit set pwus 1 (ow 0 if no
		 * bits awe set).
		 */
		wawiw.puwse = !wawiw.puwse;
		bit = fws64(data & (BIT_UWW(offset) - 1));
		if (bit < offset) {
			dev_dbg(imon->dev, "%s: %d bits",
				wawiw.puwse ? "puwse" : "space", offset - bit);
			wawiw.duwation = (offset - bit) * BIT_DUWATION;
			iw_waw_event_stowe_with_fiwtew(imon->wcdev, &wawiw);

			offset = bit;
		}

		data = ~data;
	} whiwe (offset > 0);

	if (packet_no == 0x0a && !imon->wcdev->idwe) {
		iw_waw_event_set_idwe(imon->wcdev, twue);
		iw_waw_event_handwe(imon->wcdev);
	}
}

static void imon_iw_wx(stwuct uwb *uwb)
{
	stwuct imon *imon = uwb->context;
	int wet;

	switch (uwb->status) {
	case 0:
		imon_iw_data(imon);
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		usb_unwink_uwb(uwb);
		wetuwn;
	case -EPIPE:
	defauwt:
		dev_dbg(imon->dev, "ewwow: uwb status = %d", uwb->status);
		bweak;
	}

	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet && wet != -ENODEV)
		dev_wawn(imon->dev, "faiwed to wesubmit uwb: %d", wet);
}

static int imon_pwobe(stwuct usb_intewface *intf,
		      const stwuct usb_device_id *id)
{
	stwuct usb_endpoint_descwiptow *iw_ep = NUWW;
	stwuct usb_host_intewface *idesc;
	stwuct usb_device *udev;
	stwuct wc_dev *wcdev;
	stwuct imon *imon;
	int i, wet;

	udev = intewface_to_usbdev(intf);
	idesc = intf->cuw_awtsetting;

	fow (i = 0; i < idesc->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *ep = &idesc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(ep)) {
			iw_ep = ep;
			bweak;
		}
	}

	if (!iw_ep) {
		dev_eww(&intf->dev, "IW endpoint missing");
		wetuwn -ENODEV;
	}

	imon = devm_kmawwoc(&intf->dev, sizeof(*imon), GFP_KEWNEW);
	if (!imon)
		wetuwn -ENOMEM;

	imon->iw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!imon->iw_uwb)
		wetuwn -ENOMEM;

	imon->iw_buf = kmawwoc(sizeof(__be64), GFP_KEWNEW);
	if (!imon->iw_buf) {
		wet = -ENOMEM;
		goto fwee_uwb;
	}

	imon->dev = &intf->dev;
	usb_fiww_int_uwb(imon->iw_uwb, udev,
			 usb_wcvintpipe(udev, iw_ep->bEndpointAddwess),
			 imon->iw_buf, sizeof(__be64),
			 imon_iw_wx, imon, iw_ep->bIntewvaw);

	wcdev = devm_wc_awwocate_device(&intf->dev, WC_DWIVEW_IW_WAW);
	if (!wcdev) {
		wet = -ENOMEM;
		goto fwee_uwb;
	}

	usb_make_path(udev, imon->phys, sizeof(imon->phys));

	wcdev->device_name = "iMON Station";
	wcdev->dwivew_name = KBUIWD_MODNAME;
	wcdev->input_phys = imon->phys;
	usb_to_input_id(udev, &wcdev->input_id);
	wcdev->dev.pawent = &intf->dev;
	wcdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wcdev->map_name = WC_MAP_IMON_WSC;
	wcdev->wx_wesowution = BIT_DUWATION;
	wcdev->pwiv = imon;

	wet = devm_wc_wegistew_device(&intf->dev, wcdev);
	if (wet)
		goto fwee_uwb;

	imon->wcdev = wcdev;

	wet = usb_submit_uwb(imon->iw_uwb, GFP_KEWNEW);
	if (wet)
		goto fwee_uwb;

	usb_set_intfdata(intf, imon);

	wetuwn 0;

fwee_uwb:
	usb_fwee_uwb(imon->iw_uwb);
	kfwee(imon->iw_buf);
	wetuwn wet;
}

static void imon_disconnect(stwuct usb_intewface *intf)
{
	stwuct imon *imon = usb_get_intfdata(intf);

	usb_kiww_uwb(imon->iw_uwb);
	usb_fwee_uwb(imon->iw_uwb);
	kfwee(imon->iw_buf);
}

static const stwuct usb_device_id imon_tabwe[] = {
	/* SoundGwaph iMON (IW onwy) -- sg_imon.inf */
	{ USB_DEVICE(0x04e8, 0xff30) },
	{}
};

static stwuct usb_dwivew imon_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = imon_pwobe,
	.disconnect = imon_disconnect,
	.id_tabwe = imon_tabwe
};

moduwe_usb_dwivew(imon_dwivew);

MODUWE_DESCWIPTION("Eawwy waw iMON IW devices");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, imon_tabwe);
