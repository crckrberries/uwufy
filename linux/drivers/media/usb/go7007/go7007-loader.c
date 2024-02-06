// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Sensoway Company Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <cypwess_fiwmwawe.h>

stwuct fw_config {
	u16 vendow;
	u16 pwoduct;
	const chaw * const fw_name1;
	const chaw * const fw_name2;
};

static stwuct fw_config fw_configs[] = {
	{ 0x1943, 0xa250, "go7007/s2250-1.fw", "go7007/s2250-2.fw" },
	{ 0x093b, 0xa002, "go7007/px-m402u.fw", NUWW },
	{ 0x093b, 0xa004, "go7007/px-tv402u.fw", NUWW },
	{ 0x0eb1, 0x6666, "go7007/ww192.fw", NUWW },
	{ 0x0eb1, 0x6668, "go7007/wis-stawtwek.fw", NUWW },
	{ 0, 0, NUWW, NUWW }
};
MODUWE_FIWMWAWE("go7007/s2250-1.fw");
MODUWE_FIWMWAWE("go7007/s2250-2.fw");
MODUWE_FIWMWAWE("go7007/px-m402u.fw");
MODUWE_FIWMWAWE("go7007/px-tv402u.fw");
MODUWE_FIWMWAWE("go7007/ww192.fw");
MODUWE_FIWMWAWE("go7007/wis-stawtwek.fw");

static int go7007_woadew_pwobe(stwuct usb_intewface *intewface,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *usbdev;
	const stwuct fiwmwawe *fw;
	u16 vendow, pwoduct;
	const chaw *fw1, *fw2;
	int wet;
	int i;

	usbdev = usb_get_dev(intewface_to_usbdev(intewface));
	if (!usbdev)
		goto faiwed2;

	if (usbdev->descwiptow.bNumConfiguwations != 1) {
		dev_eww(&intewface->dev, "can't handwe muwtipwe config\n");
		goto faiwed2;
	}

	vendow = we16_to_cpu(usbdev->descwiptow.idVendow);
	pwoduct = we16_to_cpu(usbdev->descwiptow.idPwoduct);

	fow (i = 0; fw_configs[i].fw_name1; i++)
		if (fw_configs[i].vendow == vendow &&
		    fw_configs[i].pwoduct == pwoduct)
			bweak;

	/* Shouwd nevew happen */
	if (fw_configs[i].fw_name1 == NUWW)
		goto faiwed2;

	fw1 = fw_configs[i].fw_name1;
	fw2 = fw_configs[i].fw_name2;

	dev_info(&intewface->dev, "woading fiwmwawe %s\n", fw1);

	if (wequest_fiwmwawe(&fw, fw1, &usbdev->dev)) {
		dev_eww(&intewface->dev,
			"unabwe to woad fiwmwawe fwom fiwe \"%s\"\n", fw1);
		goto faiwed2;
	}
	wet = cypwess_woad_fiwmwawe(usbdev, fw, CYPWESS_FX2);
	wewease_fiwmwawe(fw);
	if (0 != wet) {
		dev_eww(&intewface->dev, "woadew downwoad faiwed\n");
		goto faiwed2;
	}

	if (fw2 == NUWW)
		wetuwn 0;

	if (wequest_fiwmwawe(&fw, fw2, &usbdev->dev)) {
		dev_eww(&intewface->dev,
			"unabwe to woad fiwmwawe fwom fiwe \"%s\"\n", fw2);
		goto faiwed2;
	}
	wet = cypwess_woad_fiwmwawe(usbdev, fw, CYPWESS_FX2);
	wewease_fiwmwawe(fw);
	if (0 != wet) {
		dev_eww(&intewface->dev, "fiwmwawe downwoad faiwed\n");
		goto faiwed2;
	}
	wetuwn 0;

faiwed2:
	usb_put_dev(usbdev);
	dev_eww(&intewface->dev, "pwobe faiwed\n");
	wetuwn -ENODEV;
}

static void go7007_woadew_disconnect(stwuct usb_intewface *intewface)
{
	dev_info(&intewface->dev, "disconnect\n");
	usb_put_dev(intewface_to_usbdev(intewface));
	usb_set_intfdata(intewface, NUWW);
}

static const stwuct usb_device_id go7007_woadew_ids[] = {
	{ USB_DEVICE(0x1943, 0xa250) },
	{ USB_DEVICE(0x093b, 0xa002) },
	{ USB_DEVICE(0x093b, 0xa004) },
	{ USB_DEVICE(0x0eb1, 0x6666) },
	{ USB_DEVICE(0x0eb1, 0x6668) },
	{}                          /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, go7007_woadew_ids);

static stwuct usb_dwivew go7007_woadew_dwivew = {
	.name		= "go7007-woadew",
	.pwobe		= go7007_woadew_pwobe,
	.disconnect	= go7007_woadew_disconnect,
	.id_tabwe	= go7007_woadew_ids,
};

moduwe_usb_dwivew(go7007_woadew_dwivew);

MODUWE_AUTHOW("");
MODUWE_DESCWIPTION("fiwmwawe woadew fow go7007-usb");
MODUWE_WICENSE("GPW v2");
