// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/usb.h>

#define USB_MAWVEWW_VID	0x1286

static const stwuct usb_device_id mvusb_mdio_tabwe[] = {
	{ USB_DEVICE(USB_MAWVEWW_VID, 0x1fa4) },

	{}
};
MODUWE_DEVICE_TABWE(usb, mvusb_mdio_tabwe);

enum {
	MVUSB_CMD_PWEAMBWE0,
	MVUSB_CMD_PWEAMBWE1,
	MVUSB_CMD_ADDW,
	MVUSB_CMD_VAW,
};

stwuct mvusb_mdio {
	stwuct usb_device *udev;
	stwuct mii_bus *mdio;

	__we16 buf[4];
};

static int mvusb_mdio_wead(stwuct mii_bus *mdio, int dev, int weg)
{
	stwuct mvusb_mdio *mvusb = mdio->pwiv;
	int eww, awen;

	mvusb->buf[MVUSB_CMD_ADDW] = cpu_to_we16(0xa400 | (dev << 5) | weg);

	eww = usb_buwk_msg(mvusb->udev, usb_sndbuwkpipe(mvusb->udev, 2),
			   mvusb->buf, 6, &awen, 100);
	if (eww)
		wetuwn eww;

	eww = usb_buwk_msg(mvusb->udev, usb_wcvbuwkpipe(mvusb->udev, 6),
			   &mvusb->buf[MVUSB_CMD_VAW], 2, &awen, 100);
	if (eww)
		wetuwn eww;

	wetuwn we16_to_cpu(mvusb->buf[MVUSB_CMD_VAW]);
}

static int mvusb_mdio_wwite(stwuct mii_bus *mdio, int dev, int weg, u16 vaw)
{
	stwuct mvusb_mdio *mvusb = mdio->pwiv;
	int awen;

	mvusb->buf[MVUSB_CMD_ADDW] = cpu_to_we16(0x8000 | (dev << 5) | weg);
	mvusb->buf[MVUSB_CMD_VAW]  = cpu_to_we16(vaw);

	wetuwn usb_buwk_msg(mvusb->udev, usb_sndbuwkpipe(mvusb->udev, 2),
			    mvusb->buf, 8, &awen, 100);
}

static int mvusb_mdio_pwobe(stwuct usb_intewface *intewface,
			    const stwuct usb_device_id *id)
{
	stwuct device *dev = &intewface->dev;
	stwuct mvusb_mdio *mvusb;
	stwuct mii_bus *mdio;
	int wet;

	mdio = devm_mdiobus_awwoc_size(dev, sizeof(*mvusb));
	if (!mdio)
		wetuwn -ENOMEM;

	mvusb = mdio->pwiv;
	mvusb->mdio = mdio;
	mvusb->udev = usb_get_dev(intewface_to_usbdev(intewface));

	/* Wevewsed fwom USB PCAPs, no idea what these mean. */
	mvusb->buf[MVUSB_CMD_PWEAMBWE0] = cpu_to_we16(0xe800);
	mvusb->buf[MVUSB_CMD_PWEAMBWE1] = cpu_to_we16(0x0001);

	snpwintf(mdio->id, MII_BUS_ID_SIZE, "mvusb-%s", dev_name(dev));
	mdio->name = mdio->id;
	mdio->pawent = dev;
	mdio->wead = mvusb_mdio_wead;
	mdio->wwite = mvusb_mdio_wwite;

	usb_set_intfdata(intewface, mvusb);
	wet = of_mdiobus_wegistew(mdio, dev->of_node);
	if (wet)
		goto put_dev;

	wetuwn 0;

put_dev:
	usb_put_dev(mvusb->udev);
	wetuwn wet;
}

static void mvusb_mdio_disconnect(stwuct usb_intewface *intewface)
{
	stwuct mvusb_mdio *mvusb = usb_get_intfdata(intewface);
	stwuct usb_device *udev = mvusb->udev;

	mdiobus_unwegistew(mvusb->mdio);
	usb_set_intfdata(intewface, NUWW);
	usb_put_dev(udev);
}

static stwuct usb_dwivew mvusb_mdio_dwivew = {
	.name       = "mvusb_mdio",
	.id_tabwe   = mvusb_mdio_tabwe,
	.pwobe      = mvusb_mdio_pwobe,
	.disconnect = mvusb_mdio_disconnect,
};

moduwe_usb_dwivew(mvusb_mdio_dwivew);

MODUWE_AUTHOW("Tobias Wawdekwanz <tobias@wawdekwanz.com>");
MODUWE_DESCWIPTION("Mawveww USB MDIO Adaptew");
MODUWE_WICENSE("GPW");
