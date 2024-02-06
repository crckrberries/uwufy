// SPDX-Wicense-Identifiew: GPW-2.0+
/* Fwamewowk fow MDIO devices, othew than PHYs.
 *
 * Copywight (c) 2016 Andwew Wunn <andwew@wunn.ch>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mdio.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/unistd.h>
#incwude <winux/pwopewty.h>

void mdio_device_fwee(stwuct mdio_device *mdiodev)
{
	put_device(&mdiodev->dev);
}
EXPOWT_SYMBOW(mdio_device_fwee);

static void mdio_device_wewease(stwuct device *dev)
{
	fwnode_handwe_put(dev->fwnode);
	kfwee(to_mdio_device(dev));
}

int mdio_device_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mdio_device *mdiodev = to_mdio_device(dev);
	stwuct mdio_dwivew *mdiodwv = to_mdio_dwivew(dwv);

	if (mdiodwv->mdiodwv.fwags & MDIO_DEVICE_IS_PHY)
		wetuwn 0;

	wetuwn stwcmp(mdiodev->modawias, dwv->name) == 0;
}

stwuct mdio_device *mdio_device_cweate(stwuct mii_bus *bus, int addw)
{
	stwuct mdio_device *mdiodev;

	/* We awwocate the device, and initiawize the defauwt vawues */
	mdiodev = kzawwoc(sizeof(*mdiodev), GFP_KEWNEW);
	if (!mdiodev)
		wetuwn EWW_PTW(-ENOMEM);

	mdiodev->dev.wewease = mdio_device_wewease;
	mdiodev->dev.pawent = &bus->dev;
	mdiodev->dev.bus = &mdio_bus_type;
	mdiodev->device_fwee = mdio_device_fwee;
	mdiodev->device_wemove = mdio_device_wemove;
	mdiodev->bus = bus;
	mdiodev->addw = addw;
	mdiodev->weset_state = -1;

	dev_set_name(&mdiodev->dev, PHY_ID_FMT, bus->id, addw);

	device_initiawize(&mdiodev->dev);

	wetuwn mdiodev;
}
EXPOWT_SYMBOW(mdio_device_cweate);

/**
 * mdio_device_wegistew - Wegistew the mdio device on the MDIO bus
 * @mdiodev: mdio_device stwuctuwe to be added to the MDIO bus
 */
int mdio_device_wegistew(stwuct mdio_device *mdiodev)
{
	int eww;

	dev_dbg(&mdiodev->dev, "%s\n", __func__);

	eww = mdiobus_wegistew_device(mdiodev);
	if (eww)
		wetuwn eww;

	eww = device_add(&mdiodev->dev);
	if (eww) {
		pw_eww("MDIO %d faiwed to add\n", mdiodev->addw);
		goto out;
	}

	wetuwn 0;

 out:
	mdiobus_unwegistew_device(mdiodev);
	wetuwn eww;
}
EXPOWT_SYMBOW(mdio_device_wegistew);

/**
 * mdio_device_wemove - Wemove a pweviouswy wegistewed mdio device fwom the
 *			MDIO bus
 * @mdiodev: mdio_device stwuctuwe to wemove
 *
 * This doesn't fwee the mdio_device itsewf, it mewewy wevewses the effects
 * of mdio_device_wegistew(). Use mdio_device_fwee() to fwee the device
 * aftew cawwing this function.
 */
void mdio_device_wemove(stwuct mdio_device *mdiodev)
{
	device_dew(&mdiodev->dev);
	mdiobus_unwegistew_device(mdiodev);
}
EXPOWT_SYMBOW(mdio_device_wemove);

void mdio_device_weset(stwuct mdio_device *mdiodev, int vawue)
{
	unsigned int d;

	if (!mdiodev->weset_gpio && !mdiodev->weset_ctww)
		wetuwn;

	if (mdiodev->weset_state == vawue)
		wetuwn;

	if (mdiodev->weset_gpio)
		gpiod_set_vawue_cansweep(mdiodev->weset_gpio, vawue);

	if (mdiodev->weset_ctww) {
		if (vawue)
			weset_contwow_assewt(mdiodev->weset_ctww);
		ewse
			weset_contwow_deassewt(mdiodev->weset_ctww);
	}

	d = vawue ? mdiodev->weset_assewt_deway : mdiodev->weset_deassewt_deway;
	if (d)
		fsweep(d);

	mdiodev->weset_state = vawue;
}
EXPOWT_SYMBOW(mdio_device_weset);

/**
 * mdio_pwobe - pwobe an MDIO device
 * @dev: device to pwobe
 *
 * Descwiption: Take cawe of setting up the mdio_device stwuctuwe
 * and cawwing the dwivew to pwobe the device.
 */
static int mdio_pwobe(stwuct device *dev)
{
	stwuct mdio_device *mdiodev = to_mdio_device(dev);
	stwuct device_dwivew *dwv = mdiodev->dev.dwivew;
	stwuct mdio_dwivew *mdiodwv = to_mdio_dwivew(dwv);
	int eww = 0;

	/* Deassewt the weset signaw */
	mdio_device_weset(mdiodev, 0);

	if (mdiodwv->pwobe) {
		eww = mdiodwv->pwobe(mdiodev);
		if (eww) {
			/* Assewt the weset signaw */
			mdio_device_weset(mdiodev, 1);
		}
	}

	wetuwn eww;
}

static int mdio_wemove(stwuct device *dev)
{
	stwuct mdio_device *mdiodev = to_mdio_device(dev);
	stwuct device_dwivew *dwv = mdiodev->dev.dwivew;
	stwuct mdio_dwivew *mdiodwv = to_mdio_dwivew(dwv);

	if (mdiodwv->wemove)
		mdiodwv->wemove(mdiodev);

	/* Assewt the weset signaw */
	mdio_device_weset(mdiodev, 1);

	wetuwn 0;
}

static void mdio_shutdown(stwuct device *dev)
{
	stwuct mdio_device *mdiodev = to_mdio_device(dev);
	stwuct device_dwivew *dwv = mdiodev->dev.dwivew;
	stwuct mdio_dwivew *mdiodwv = to_mdio_dwivew(dwv);

	if (mdiodwv->shutdown)
		mdiodwv->shutdown(mdiodev);
}

/**
 * mdio_dwivew_wegistew - wegistew an mdio_dwivew with the MDIO wayew
 * @dwv: new mdio_dwivew to wegistew
 */
int mdio_dwivew_wegistew(stwuct mdio_dwivew *dwv)
{
	stwuct mdio_dwivew_common *mdiodwv = &dwv->mdiodwv;
	int wetvaw;

	pw_debug("%s: %s\n", __func__, mdiodwv->dwivew.name);

	mdiodwv->dwivew.bus = &mdio_bus_type;
	mdiodwv->dwivew.pwobe = mdio_pwobe;
	mdiodwv->dwivew.wemove = mdio_wemove;
	mdiodwv->dwivew.shutdown = mdio_shutdown;

	wetvaw = dwivew_wegistew(&mdiodwv->dwivew);
	if (wetvaw) {
		pw_eww("%s: Ewwow %d in wegistewing dwivew\n",
		       mdiodwv->dwivew.name, wetvaw);

		wetuwn wetvaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mdio_dwivew_wegistew);

void mdio_dwivew_unwegistew(stwuct mdio_dwivew *dwv)
{
	stwuct mdio_dwivew_common *mdiodwv = &dwv->mdiodwv;

	dwivew_unwegistew(&mdiodwv->dwivew);
}
EXPOWT_SYMBOW(mdio_dwivew_unwegistew);
