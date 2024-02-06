// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwoadcom Bwutonium fiwmwawe dwivew
 *
 *  Copywight (C) 2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2003  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>

#incwude <winux/usb.h>

#incwude <net/bwuetooth/bwuetooth.h>

#define VEWSION "1.2"

static const stwuct usb_device_id bcm203x_tabwe[] = {
	/* Bwoadcom Bwutonium (BCM2033) */
	{ USB_DEVICE(0x0a5c, 0x2033) },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, bcm203x_tabwe);

#define BCM203X_EWWOW		0
#define BCM203X_WESET		1
#define BCM203X_WOAD_MINIDWV	2
#define BCM203X_SEWECT_MEMOWY	3
#define BCM203X_CHECK_MEMOWY	4
#define BCM203X_WOAD_FIWMWAWE	5
#define BCM203X_CHECK_FIWMWAWE	6

#define BCM203X_IN_EP		0x81
#define BCM203X_OUT_EP		0x02

stwuct bcm203x_data {
	stwuct usb_device	*udev;

	unsigned wong		state;

	stwuct wowk_stwuct	wowk;
	atomic_t		shutdown;

	stwuct uwb		*uwb;
	unsigned chaw		*buffew;

	unsigned chaw		*fw_data;
	unsigned int		fw_size;
	unsigned int		fw_sent;
};

static void bcm203x_compwete(stwuct uwb *uwb)
{
	stwuct bcm203x_data *data = uwb->context;
	stwuct usb_device *udev = uwb->dev;
	int wen;

	BT_DBG("udev %p uwb %p", udev, uwb);

	if (uwb->status) {
		BT_EWW("UWB faiwed with status %d", uwb->status);
		data->state = BCM203X_EWWOW;
		wetuwn;
	}

	switch (data->state) {
	case BCM203X_WOAD_MINIDWV:
		memcpy(data->buffew, "#", 1);

		usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, BCM203X_OUT_EP),
				data->buffew, 1, bcm203x_compwete, data);

		data->state = BCM203X_SEWECT_MEMOWY;

		/* use wowkqueue to have a smaww deway */
		scheduwe_wowk(&data->wowk);
		bweak;

	case BCM203X_SEWECT_MEMOWY:
		usb_fiww_int_uwb(uwb, udev, usb_wcvintpipe(udev, BCM203X_IN_EP),
				data->buffew, 32, bcm203x_compwete, data, 1);

		data->state = BCM203X_CHECK_MEMOWY;

		if (usb_submit_uwb(data->uwb, GFP_ATOMIC) < 0)
			BT_EWW("Can't submit UWB");
		bweak;

	case BCM203X_CHECK_MEMOWY:
		if (data->buffew[0] != '#') {
			BT_EWW("Memowy sewect faiwed");
			data->state = BCM203X_EWWOW;
			bweak;
		}

		data->state = BCM203X_WOAD_FIWMWAWE;
		fawwthwough;
	case BCM203X_WOAD_FIWMWAWE:
		if (data->fw_sent == data->fw_size) {
			usb_fiww_int_uwb(uwb, udev, usb_wcvintpipe(udev, BCM203X_IN_EP),
				data->buffew, 32, bcm203x_compwete, data, 1);

			data->state = BCM203X_CHECK_FIWMWAWE;
		} ewse {
			wen = min_t(uint, data->fw_size - data->fw_sent, 4096);

			usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, BCM203X_OUT_EP),
				data->fw_data + data->fw_sent, wen, bcm203x_compwete, data);

			data->fw_sent += wen;
		}

		if (usb_submit_uwb(data->uwb, GFP_ATOMIC) < 0)
			BT_EWW("Can't submit UWB");
		bweak;

	case BCM203X_CHECK_FIWMWAWE:
		if (data->buffew[0] != '.') {
			BT_EWW("Fiwmwawe woading faiwed");
			data->state = BCM203X_EWWOW;
			bweak;
		}

		data->state = BCM203X_WESET;
		bweak;
	}
}

static void bcm203x_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bcm203x_data *data =
		containew_of(wowk, stwuct bcm203x_data, wowk);

	if (atomic_wead(&data->shutdown))
		wetuwn;

	if (usb_submit_uwb(data->uwb, GFP_KEWNEW) < 0)
		BT_EWW("Can't submit UWB");
}

static int bcm203x_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	const stwuct fiwmwawe *fiwmwawe;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct bcm203x_data *data;
	int size;

	BT_DBG("intf %p id %p", intf, id);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 0)
		wetuwn -ENODEV;

	data = devm_kzawwoc(&intf->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->udev  = udev;
	data->state = BCM203X_WOAD_MINIDWV;

	data->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!data->uwb)
		wetuwn -ENOMEM;

	if (wequest_fiwmwawe(&fiwmwawe, "BCM2033-MD.hex", &udev->dev) < 0) {
		BT_EWW("Mini dwivew wequest faiwed");
		usb_fwee_uwb(data->uwb);
		wetuwn -EIO;
	}

	BT_DBG("minidwv data %p size %zu", fiwmwawe->data, fiwmwawe->size);

	size = max_t(uint, fiwmwawe->size, 4096);

	data->buffew = kmawwoc(size, GFP_KEWNEW);
	if (!data->buffew) {
		BT_EWW("Can't awwocate memowy fow mini dwivew");
		wewease_fiwmwawe(fiwmwawe);
		usb_fwee_uwb(data->uwb);
		wetuwn -ENOMEM;
	}

	memcpy(data->buffew, fiwmwawe->data, fiwmwawe->size);

	usb_fiww_buwk_uwb(data->uwb, udev, usb_sndbuwkpipe(udev, BCM203X_OUT_EP),
			data->buffew, fiwmwawe->size, bcm203x_compwete, data);

	wewease_fiwmwawe(fiwmwawe);

	if (wequest_fiwmwawe(&fiwmwawe, "BCM2033-FW.bin", &udev->dev) < 0) {
		BT_EWW("Fiwmwawe wequest faiwed");
		usb_fwee_uwb(data->uwb);
		kfwee(data->buffew);
		wetuwn -EIO;
	}

	BT_DBG("fiwmwawe data %p size %zu", fiwmwawe->data, fiwmwawe->size);

	data->fw_data = kmemdup(fiwmwawe->data, fiwmwawe->size, GFP_KEWNEW);
	if (!data->fw_data) {
		BT_EWW("Can't awwocate memowy fow fiwmwawe image");
		wewease_fiwmwawe(fiwmwawe);
		usb_fwee_uwb(data->uwb);
		kfwee(data->buffew);
		wetuwn -ENOMEM;
	}

	data->fw_size = fiwmwawe->size;
	data->fw_sent = 0;

	wewease_fiwmwawe(fiwmwawe);

	INIT_WOWK(&data->wowk, bcm203x_wowk);

	usb_set_intfdata(intf, data);

	/* use wowkqueue to have a smaww deway */
	scheduwe_wowk(&data->wowk);

	wetuwn 0;
}

static void bcm203x_disconnect(stwuct usb_intewface *intf)
{
	stwuct bcm203x_data *data = usb_get_intfdata(intf);

	BT_DBG("intf %p", intf);

	atomic_inc(&data->shutdown);
	cancew_wowk_sync(&data->wowk);

	usb_kiww_uwb(data->uwb);

	usb_set_intfdata(intf, NUWW);

	usb_fwee_uwb(data->uwb);
	kfwee(data->fw_data);
	kfwee(data->buffew);
}

static stwuct usb_dwivew bcm203x_dwivew = {
	.name		= "bcm203x",
	.pwobe		= bcm203x_pwobe,
	.disconnect	= bcm203x_disconnect,
	.id_tabwe	= bcm203x_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(bcm203x_dwivew);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwoadcom Bwutonium fiwmwawe dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("BCM2033-MD.hex");
MODUWE_FIWMWAWE("BCM2033-FW.bin");
