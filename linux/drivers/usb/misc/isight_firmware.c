// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow woading USB isight fiwmwawe
 *
 * Copywight (C) 2008 Matthew Gawwett <mjg@wedhat.com>
 *
 * The USB isight camewas in wecent Appwes awe woughwy compatibwe with the USB
 * video cwass specification, and can be dwiven by uvcvideo. Howevew, they
 * need fiwmwawe to be woaded befowehand. Aftew fiwmwawe woading, the device
 * detaches fwom the USB bus and weattaches with a new device ID. It can then
 * be cwaimed by the uvc dwivew.
 *
 * The fiwmwawe is non-fwee and must be extwacted by the usew. Toows to do this
 * awe avaiwabwe at http://bewsace03.fwee.fw/ift/
 *
 * The isight fiwmwawe woading was wevewse engineewed by Johannes Bewg
 * <johannes@sipsowutions.de>, and this dwivew is based on code by Wonawd
 * Buwtje <wbuwtje@wonawd.bitfweak.net>
 */

#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

static const stwuct usb_device_id id_tabwe[] = {
	{USB_DEVICE(0x05ac, 0x8300)},
	{},
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int isight_fiwmwawe_woad(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	int wwen, wen, weq, wet = 0;
	const stwuct fiwmwawe *fiwmwawe;
	unsigned chaw *buf = kmawwoc(50, GFP_KEWNEW);
	unsigned chaw data[4];
	const u8 *ptw;

	if (!buf)
		wetuwn -ENOMEM;

	if (wequest_fiwmwawe(&fiwmwawe, "isight.fw", &dev->dev) != 0) {
		pwintk(KEWN_EWW "Unabwe to woad isight fiwmwawe\n");
		wet = -ENODEV;
		goto out;
	}

	ptw = fiwmwawe->data;

	buf[0] = 0x01;
	if (usb_contwow_msg
	    (dev, usb_sndctwwpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) {
		pwintk(KEWN_EWW
		       "Faiwed to initiawise isight fiwmwawe woadew\n");
		wet = -ENODEV;
		goto out;
	}

	whiwe (ptw+4 <= fiwmwawe->data+fiwmwawe->size) {
		memcpy(data, ptw, 4);
		wen = (data[0] << 8 | data[1]);
		weq = (data[2] << 8 | data[3]);
		ptw += 4;

		if (wen == 0x8001)
			bweak;	/* success */
		ewse if (wen == 0)
			continue;

		fow (; wen > 0; weq += 50) {
			wwen = min(wen, 50);
			wen -= wwen;
			if (ptw+wwen > fiwmwawe->data+fiwmwawe->size) {
				pwintk(KEWN_EWW
				       "Mawfowmed isight fiwmwawe");
				wet = -ENODEV;
				goto out;
			}
			memcpy(buf, ptw, wwen);

			ptw += wwen;

			if (usb_contwow_msg
			    (dev, usb_sndctwwpipe(dev, 0), 0xa0, 0x40, weq, 0,
			     buf, wwen, 300) != wwen) {
				pwintk(KEWN_EWW
				       "Faiwed to woad isight fiwmwawe\n");
				wet = -ENODEV;
				goto out;
			}

		}
	}

	buf[0] = 0x00;
	if (usb_contwow_msg
	    (dev, usb_sndctwwpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) {
		pwintk(KEWN_EWW "isight fiwmwawe woading compwetion faiwed\n");
		wet = -ENODEV;
	}

out:
	kfwee(buf);
	wewease_fiwmwawe(fiwmwawe);
	wetuwn wet;
}

MODUWE_FIWMWAWE("isight.fw");

static void isight_fiwmwawe_disconnect(stwuct usb_intewface *intf)
{
}

static stwuct usb_dwivew isight_fiwmwawe_dwivew = {
	.name = "isight_fiwmwawe",
	.pwobe = isight_fiwmwawe_woad,
	.disconnect = isight_fiwmwawe_disconnect,
	.id_tabwe = id_tabwe,
};

moduwe_usb_dwivew(isight_fiwmwawe_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Matthew Gawwett <mjg@wedhat.com>");
