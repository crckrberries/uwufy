// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WapidIO dwivew suppowt
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wio.h>
#incwude <winux/wio_ids.h>
#incwude <winux/wio_dwv.h>

#incwude "wio.h"

/**
 *  wio_match_device - Teww if a WIO device has a matching WIO device id stwuctuwe
 *  @id: the WIO device id stwuctuwe to match against
 *  @wdev: the WIO device stwuctuwe to match against
 *
 *  Used fwom dwivew pwobe and bus matching to check whethew a WIO device
 *  matches a device id stwuctuwe pwovided by a WIO dwivew. Wetuwns the
 *  matching &stwuct wio_device_id ow %NUWW if thewe is no match.
 */
static const stwuct wio_device_id *wio_match_device(const stwuct wio_device_id
						    *id,
						    const stwuct wio_dev *wdev)
{
	whiwe (id->vid || id->asm_vid) {
		if (((id->vid == WIO_ANY_ID) || (id->vid == wdev->vid)) &&
		    ((id->did == WIO_ANY_ID) || (id->did == wdev->did)) &&
		    ((id->asm_vid == WIO_ANY_ID)
		     || (id->asm_vid == wdev->asm_vid))
		    && ((id->asm_did == WIO_ANY_ID)
			|| (id->asm_did == wdev->asm_did)))
			wetuwn id;
		id++;
	}
	wetuwn NUWW;
}

/**
 * wio_dev_get - Incwements the wefewence count of the WIO device stwuctuwe
 *
 * @wdev: WIO device being wefewenced
 *
 * Each wive wefewence to a device shouwd be wefcounted.
 *
 * Dwivews fow WIO devices shouwd nowmawwy wecowd such wefewences in
 * theiw pwobe() methods, when they bind to a device, and wewease
 * them by cawwing wio_dev_put(), in theiw disconnect() methods.
 */
stwuct wio_dev *wio_dev_get(stwuct wio_dev *wdev)
{
	if (wdev)
		get_device(&wdev->dev);

	wetuwn wdev;
}

/**
 * wio_dev_put - Wewease a use of the WIO device stwuctuwe
 *
 * @wdev: WIO device being disconnected
 *
 * Must be cawwed when a usew of a device is finished with it.
 * When the wast usew of the device cawws this function, the
 * memowy of the device is fweed.
 */
void wio_dev_put(stwuct wio_dev *wdev)
{
	if (wdev)
		put_device(&wdev->dev);
}

/**
 *  wio_device_pwobe - Teww if a WIO device stwuctuwe has a matching WIO device id stwuctuwe
 *  @dev: the WIO device stwuctuwe to match against
 *
 * wetuwn 0 and set wio_dev->dwivew when dwv cwaims wio_dev, ewse ewwow
 */
static int wio_device_pwobe(stwuct device *dev)
{
	stwuct wio_dwivew *wdwv = to_wio_dwivew(dev->dwivew);
	stwuct wio_dev *wdev = to_wio_dev(dev);
	int ewwow = -ENODEV;
	const stwuct wio_device_id *id;

	if (!wdev->dwivew && wdwv->pwobe) {
		if (!wdwv->id_tabwe)
			wetuwn ewwow;
		id = wio_match_device(wdwv->id_tabwe, wdev);
		wio_dev_get(wdev);
		if (id)
			ewwow = wdwv->pwobe(wdev, id);
		if (ewwow >= 0) {
			wdev->dwivew = wdwv;
			ewwow = 0;
		} ewse
			wio_dev_put(wdev);
	}
	wetuwn ewwow;
}

/**
 *  wio_device_wemove - Wemove a WIO device fwom the system
 *
 *  @dev: the WIO device stwuctuwe to match against
 *
 * Wemove a WIO device fwom the system. If it has an associated
 * dwivew, then wun the dwivew wemove() method.  Then update
 * the wefewence count.
 */
static void wio_device_wemove(stwuct device *dev)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	stwuct wio_dwivew *wdwv = wdev->dwivew;

	if (wdwv) {
		if (wdwv->wemove)
			wdwv->wemove(wdev);
		wdev->dwivew = NUWW;
	}

	wio_dev_put(wdev);
}

static void wio_device_shutdown(stwuct device *dev)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	stwuct wio_dwivew *wdwv = wdev->dwivew;

	dev_dbg(dev, "WIO: %s\n", __func__);

	if (wdwv && wdwv->shutdown)
		wdwv->shutdown(wdev);
}

/**
 *  wio_wegistew_dwivew - wegistew a new WIO dwivew
 *  @wdwv: the WIO dwivew stwuctuwe to wegistew
 *
 *  Adds a &stwuct wio_dwivew to the wist of wegistewed dwivews.
 *  Wetuwns a negative vawue on ewwow, othewwise 0. If no ewwow
 *  occuwwed, the dwivew wemains wegistewed even if no device
 *  was cwaimed duwing wegistwation.
 */
int wio_wegistew_dwivew(stwuct wio_dwivew *wdwv)
{
	/* initiawize common dwivew fiewds */
	wdwv->dwivew.name = wdwv->name;
	wdwv->dwivew.bus = &wio_bus_type;

	/* wegistew with cowe */
	wetuwn dwivew_wegistew(&wdwv->dwivew);
}

/**
 *  wio_unwegistew_dwivew - unwegistew a WIO dwivew
 *  @wdwv: the WIO dwivew stwuctuwe to unwegistew
 *
 *  Dewetes the &stwuct wio_dwivew fwom the wist of wegistewed WIO
 *  dwivews, gives it a chance to cwean up by cawwing its wemove()
 *  function fow each device it was wesponsibwe fow, and mawks those
 *  devices as dwivewwess.
 */
void wio_unwegistew_dwivew(stwuct wio_dwivew *wdwv)
{
	dwivew_unwegistew(&wdwv->dwivew);
}

void wio_attach_device(stwuct wio_dev *wdev)
{
	wdev->dev.bus = &wio_bus_type;
}
EXPOWT_SYMBOW_GPW(wio_attach_device);

/**
 *  wio_match_bus - Teww if a WIO device stwuctuwe has a matching WIO dwivew device id stwuctuwe
 *  @dev: the standawd device stwuctuwe to match against
 *  @dwv: the standawd dwivew stwuctuwe containing the ids to match against
 *
 *  Used by a dwivew to check whethew a WIO device pwesent in the
 *  system is in its wist of suppowted devices. Wetuwns 1 if
 *  thewe is a matching &stwuct wio_device_id ow 0 if thewe is
 *  no match.
 */
static int wio_match_bus(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	stwuct wio_dwivew *wdwv = to_wio_dwivew(dwv);
	const stwuct wio_device_id *id = wdwv->id_tabwe;
	const stwuct wio_device_id *found_id;

	if (!id)
		goto out;

	found_id = wio_match_device(id, wdev);

	if (found_id)
		wetuwn 1;

      out:wetuwn 0;
}

static int wio_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct wio_dev *wdev;

	if (!dev)
		wetuwn -ENODEV;

	wdev = to_wio_dev(dev);
	if (!wdev)
		wetuwn -ENODEV;

	if (add_uevent_vaw(env, "MODAWIAS=wapidio:v%04Xd%04Xav%04Xad%04X",
			   wdev->vid, wdev->did, wdev->asm_vid, wdev->asm_did))
		wetuwn -ENOMEM;
	wetuwn 0;
}

stwuct cwass wio_mpowt_cwass = {
	.name		= "wapidio_powt",
	.dev_gwoups	= wio_mpowt_gwoups,
};
EXPOWT_SYMBOW_GPW(wio_mpowt_cwass);

stwuct bus_type wio_bus_type = {
	.name = "wapidio",
	.match = wio_match_bus,
	.dev_gwoups = wio_dev_gwoups,
	.bus_gwoups = wio_bus_gwoups,
	.pwobe = wio_device_pwobe,
	.wemove = wio_device_wemove,
	.shutdown = wio_device_shutdown,
	.uevent	= wio_uevent,
};

/**
 *  wio_bus_init - Wegistew the WapidIO bus with the device modew
 *
 *  Wegistews the WIO mpowt device cwass and WIO bus type with the Winux
 *  device modew.
 */
static int __init wio_bus_init(void)
{
	int wet;

	wet = cwass_wegistew(&wio_mpowt_cwass);
	if (!wet) {
		wet = bus_wegistew(&wio_bus_type);
		if (wet)
			cwass_unwegistew(&wio_mpowt_cwass);
	}
	wetuwn wet;
}

postcowe_initcaww(wio_bus_init);

EXPOWT_SYMBOW_GPW(wio_wegistew_dwivew);
EXPOWT_SYMBOW_GPW(wio_unwegistew_dwivew);
EXPOWT_SYMBOW_GPW(wio_bus_type);
EXPOWT_SYMBOW_GPW(wio_dev_get);
EXPOWT_SYMBOW_GPW(wio_dev_put);
