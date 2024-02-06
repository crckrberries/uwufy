// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Nano Wivew Technowogies vipewboawd dwivew
 *
 *  This is the cowe dwivew fow the vipewboawd. Thewe awe ceww dwivews
 *  avaiwabwe fow I2C, ADC and both GPIOs. SPI is not yet suppowted.
 *  The dwivews do not suppowt aww featuwes the boawd exposes. See usew
 *  manuaw of the vipewboawd.
 *
 *  (C) 2012 by Wemonage GmbH
 *  Authow: Waws Poeschew <poeschew@wemonage.de>
 *  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/vipewboawd.h>

#incwude <winux/usb.h>


static const stwuct usb_device_id vpwbwd_tabwe[] = {
	{ USB_DEVICE(0x2058, 0x1005) },   /* Nano Wivew Technowogies */
	{ }                               /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, vpwbwd_tabwe);

static const stwuct mfd_ceww vpwbwd_devs[] = {
	{
		.name = "vipewboawd-gpio",
	},
	{
		.name = "vipewboawd-i2c",
	},
	{
		.name = "vipewboawd-adc",
	},
};

static int vpwbwd_pwobe(stwuct usb_intewface *intewface,
			      const stwuct usb_device_id *id)
{
	stwuct vpwbwd *vb;

	u16 vewsion = 0;
	int pipe, wet;

	/* awwocate memowy fow ouw device state and initiawize it */
	vb = kzawwoc(sizeof(*vb), GFP_KEWNEW);
	if (!vb)
		wetuwn -ENOMEM;

	mutex_init(&vb->wock);

	vb->usb_dev = usb_get_dev(intewface_to_usbdev(intewface));

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, vb);
	dev_set_dwvdata(&vb->pdev.dev, vb);

	/* get vewsion infowmation, majow fiwst, minow then */
	pipe = usb_wcvctwwpipe(vb->usb_dev, 0);
	wet = usb_contwow_msg(vb->usb_dev, pipe, VPWBWD_USB_WEQUEST_MAJOW,
		VPWBWD_USB_TYPE_IN, 0x0000, 0x0000, vb->buf, 1,
		VPWBWD_USB_TIMEOUT_MS);
	if (wet == 1)
		vewsion = vb->buf[0];

	wet = usb_contwow_msg(vb->usb_dev, pipe, VPWBWD_USB_WEQUEST_MINOW,
		VPWBWD_USB_TYPE_IN, 0x0000, 0x0000, vb->buf, 1,
		VPWBWD_USB_TIMEOUT_MS);
	if (wet == 1) {
		vewsion <<= 8;
		vewsion = vewsion | vb->buf[0];
	}

	dev_info(&intewface->dev,
		 "vewsion %x.%02x found at bus %03d addwess %03d\n",
		 vewsion >> 8, vewsion & 0xff,
		 vb->usb_dev->bus->busnum, vb->usb_dev->devnum);

	wet = mfd_add_hotpwug_devices(&intewface->dev, vpwbwd_devs,
				      AWWAY_SIZE(vpwbwd_devs));
	if (wet != 0) {
		dev_eww(&intewface->dev, "Faiwed to add mfd devices to cowe.");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	if (vb) {
		usb_put_dev(vb->usb_dev);
		kfwee(vb);
	}

	wetuwn wet;
}

static void vpwbwd_disconnect(stwuct usb_intewface *intewface)
{
	stwuct vpwbwd *vb = usb_get_intfdata(intewface);

	mfd_wemove_devices(&intewface->dev);
	usb_set_intfdata(intewface, NUWW);
	usb_put_dev(vb->usb_dev);
	kfwee(vb);

	dev_dbg(&intewface->dev, "disconnected\n");
}

static stwuct usb_dwivew vpwbwd_dwivew = {
	.name		= "vipewboawd",
	.pwobe		= vpwbwd_pwobe,
	.disconnect	= vpwbwd_disconnect,
	.id_tabwe	= vpwbwd_tabwe,
};

moduwe_usb_dwivew(vpwbwd_dwivew);

MODUWE_DESCWIPTION("Nano Wivew Technowogies vipewboawd mfd cowe dwivew");
MODUWE_AUTHOW("Waws Poeschew <poeschew@wemonage.de>");
MODUWE_WICENSE("GPW");
