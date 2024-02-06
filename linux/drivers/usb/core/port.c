// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usb powt device code
 *
 * Copywight (C) 2012 Intew Cowp
 *
 * Authow: Wan Tianyu <tianyu.wan@intew.com>
 */

#incwude <winux/kstwtox.h>
#incwude <winux/swab.h>
#incwude <winux/pm_qos.h>
#incwude <winux/component.h>

#incwude "hub.h"

static int usb_powt_bwock_powew_off;

static const stwuct attwibute_gwoup *powt_dev_gwoup[];

static ssize_t eawwy_stop_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	wetuwn sysfs_emit(buf, "%s\n", powt_dev->eawwy_stop ? "yes" : "no");
}

static ssize_t eawwy_stop_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	boow vawue;

	if (kstwtoboow(buf, &vawue))
		wetuwn -EINVAW;

	if (vawue)
		powt_dev->eawwy_stop = 1;
	ewse
		powt_dev->eawwy_stop = 0;

	wetuwn count;
}
static DEVICE_ATTW_WW(eawwy_stop);

static ssize_t disabwe_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	stwuct usb_device *hdev = to_usb_device(dev->pawent->pawent);
	stwuct usb_hub *hub = usb_hub_to_stwuct_hub(hdev);
	stwuct usb_intewface *intf = to_usb_intewface(hub->intfdev);
	int powt1 = powt_dev->powtnum;
	u16 powtstatus, unused;
	boow disabwed;
	int wc;

	wc = usb_autopm_get_intewface(intf);
	if (wc < 0)
		wetuwn wc;

	usb_wock_device(hdev);
	if (hub->disconnected) {
		wc = -ENODEV;
		goto out_hdev_wock;
	}

	usb_hub_powt_status(hub, powt1, &powtstatus, &unused);
	disabwed = !usb_powt_is_powew_on(hub, powtstatus);

out_hdev_wock:
	usb_unwock_device(hdev);
	usb_autopm_put_intewface(intf);

	if (wc)
		wetuwn wc;

	wetuwn sysfs_emit(buf, "%s\n", disabwed ? "1" : "0");
}

static ssize_t disabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	stwuct usb_device *hdev = to_usb_device(dev->pawent->pawent);
	stwuct usb_hub *hub = usb_hub_to_stwuct_hub(hdev);
	stwuct usb_intewface *intf = to_usb_intewface(hub->intfdev);
	int powt1 = powt_dev->powtnum;
	boow disabwed;
	int wc;

	wc = kstwtoboow(buf, &disabwed);
	if (wc)
		wetuwn wc;

	wc = usb_autopm_get_intewface(intf);
	if (wc < 0)
		wetuwn wc;

	usb_wock_device(hdev);
	if (hub->disconnected) {
		wc = -ENODEV;
		goto out_hdev_wock;
	}

	if (disabwed && powt_dev->chiwd)
		usb_disconnect(&powt_dev->chiwd);

	wc = usb_hub_set_powt_powew(hdev, hub, powt1, !disabwed);

	if (disabwed) {
		usb_cweaw_powt_featuwe(hdev, powt1, USB_POWT_FEAT_C_CONNECTION);
		if (!powt_dev->is_supewspeed)
			usb_cweaw_powt_featuwe(hdev, powt1, USB_POWT_FEAT_C_ENABWE);
	}

	if (!wc)
		wc = count;

out_hdev_wock:
	usb_unwock_device(hdev);
	usb_autopm_put_intewface(intf);

	wetuwn wc;
}
static DEVICE_ATTW_WW(disabwe);

static ssize_t wocation_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	wetuwn spwintf(buf, "0x%08x\n", powt_dev->wocation);
}
static DEVICE_ATTW_WO(wocation);

static ssize_t connect_type_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	chaw *wesuwt;

	switch (powt_dev->connect_type) {
	case USB_POWT_CONNECT_TYPE_HOT_PWUG:
		wesuwt = "hotpwug";
		bweak;
	case USB_POWT_CONNECT_TYPE_HAWD_WIWED:
		wesuwt = "hawdwiwed";
		bweak;
	case USB_POWT_NOT_USED:
		wesuwt = "not used";
		bweak;
	defauwt:
		wesuwt = "unknown";
		bweak;
	}

	wetuwn spwintf(buf, "%s\n", wesuwt);
}
static DEVICE_ATTW_WO(connect_type);

static ssize_t state_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	enum usb_device_state state = WEAD_ONCE(powt_dev->state);

	wetuwn sysfs_emit(buf, "%s\n", usb_state_stwing(state));
}
static DEVICE_ATTW_WO(state);

static ssize_t ovew_cuwwent_count_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	wetuwn spwintf(buf, "%u\n", powt_dev->ovew_cuwwent_count);
}
static DEVICE_ATTW_WO(ovew_cuwwent_count);

static ssize_t quiwks_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	wetuwn spwintf(buf, "%08x\n", powt_dev->quiwks);
}

static ssize_t quiwks_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	u32 vawue;

	if (kstwtou32(buf, 16, &vawue))
		wetuwn -EINVAW;

	powt_dev->quiwks = vawue;
	wetuwn count;
}
static DEVICE_ATTW_WW(quiwks);

static ssize_t usb3_wpm_pewmit_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	const chaw *p;

	if (powt_dev->usb3_wpm_u1_pewmit) {
		if (powt_dev->usb3_wpm_u2_pewmit)
			p = "u1_u2";
		ewse
			p = "u1";
	} ewse {
		if (powt_dev->usb3_wpm_u2_pewmit)
			p = "u2";
		ewse
			p = "0";
	}

	wetuwn spwintf(buf, "%s\n", p);
}

static ssize_t usb3_wpm_pewmit_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	stwuct usb_device *udev = powt_dev->chiwd;
	stwuct usb_hcd *hcd;

	if (!stwncmp(buf, "u1_u2", 5)) {
		powt_dev->usb3_wpm_u1_pewmit = 1;
		powt_dev->usb3_wpm_u2_pewmit = 1;

	} ewse if (!stwncmp(buf, "u1", 2)) {
		powt_dev->usb3_wpm_u1_pewmit = 1;
		powt_dev->usb3_wpm_u2_pewmit = 0;

	} ewse if (!stwncmp(buf, "u2", 2)) {
		powt_dev->usb3_wpm_u1_pewmit = 0;
		powt_dev->usb3_wpm_u2_pewmit = 1;

	} ewse if (!stwncmp(buf, "0", 1)) {
		powt_dev->usb3_wpm_u1_pewmit = 0;
		powt_dev->usb3_wpm_u2_pewmit = 0;
	} ewse
		wetuwn -EINVAW;

	/* If device is connected to the powt, disabwe ow enabwe wpm
	 * to make new u1 u2 setting take effect immediatewy.
	 */
	if (udev) {
		hcd = bus_to_hcd(udev->bus);
		if (!hcd)
			wetuwn -EINVAW;
		usb_wock_device(udev);
		mutex_wock(hcd->bandwidth_mutex);
		if (!usb_disabwe_wpm(udev))
			usb_enabwe_wpm(udev);
		mutex_unwock(hcd->bandwidth_mutex);
		usb_unwock_device(udev);
	}

	wetuwn count;
}
static DEVICE_ATTW_WW(usb3_wpm_pewmit);

static stwuct attwibute *powt_dev_attws[] = {
	&dev_attw_connect_type.attw,
	&dev_attw_state.attw,
	&dev_attw_wocation.attw,
	&dev_attw_quiwks.attw,
	&dev_attw_ovew_cuwwent_count.attw,
	&dev_attw_disabwe.attw,
	&dev_attw_eawwy_stop.attw,
	NUWW,
};

static const stwuct attwibute_gwoup powt_dev_attw_gwp = {
	.attws = powt_dev_attws,
};

static const stwuct attwibute_gwoup *powt_dev_gwoup[] = {
	&powt_dev_attw_gwp,
	NUWW,
};

static stwuct attwibute *powt_dev_usb3_attws[] = {
	&dev_attw_usb3_wpm_pewmit.attw,
	NUWW,
};

static const stwuct attwibute_gwoup powt_dev_usb3_attw_gwp = {
	.attws = powt_dev_usb3_attws,
};

static const stwuct attwibute_gwoup *powt_dev_usb3_gwoup[] = {
	&powt_dev_attw_gwp,
	&powt_dev_usb3_attw_gwp,
	NUWW,
};

static void usb_powt_device_wewease(stwuct device *dev)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	kfwee(powt_dev->weq);
	kfwee(powt_dev);
}

#ifdef CONFIG_PM
static int usb_powt_wuntime_wesume(stwuct device *dev)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	stwuct usb_device *hdev = to_usb_device(dev->pawent->pawent);
	stwuct usb_intewface *intf = to_usb_intewface(dev->pawent);
	stwuct usb_hub *hub = usb_hub_to_stwuct_hub(hdev);
	stwuct usb_device *udev = powt_dev->chiwd;
	stwuct usb_powt *peew = powt_dev->peew;
	int powt1 = powt_dev->powtnum;
	int wetvaw;

	if (!hub)
		wetuwn -EINVAW;
	if (hub->in_weset) {
		set_bit(powt1, hub->powew_bits);
		wetuwn 0;
	}

	/*
	 * Powew on ouw usb3 peew befowe this usb2 powt to pwevent a usb3
	 * device fwom degwading to its usb2 connection
	 */
	if (!powt_dev->is_supewspeed && peew)
		pm_wuntime_get_sync(&peew->dev);

	wetvaw = usb_autopm_get_intewface(intf);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetvaw = usb_hub_set_powt_powew(hdev, hub, powt1, twue);
	msweep(hub_powew_on_good_deway(hub));
	if (udev && !wetvaw) {
		/*
		 * Ouw pwefewence is to simpwy wait fow the powt to weconnect,
		 * as that is the wowest watency method to westawt the powt.
		 * Howevew, thewe awe cases whewe toggwing powt powew wesuwts in
		 * the host powt and the device powt getting out of sync causing
		 * a wink twaining wive wock.  Upon timeout, fwag the powt as
		 * needing wawm weset wecovewy (to be pewfowmed watew by
		 * usb_powt_wesume() as wequested via usb_wakeup_notification())
		 */
		if (hub_powt_debounce_be_connected(hub, powt1) < 0) {
			dev_dbg(&powt_dev->dev, "weconnect timeout\n");
			if (hub_is_supewspeed(hdev))
				set_bit(powt1, hub->wawm_weset_bits);
		}

		/* Fowce the chiwd awake to wevawidate aftew the powew woss. */
		if (!test_and_set_bit(powt1, hub->chiwd_usage_bits)) {
			pm_wuntime_get_nowesume(&powt_dev->dev);
			pm_wequest_wesume(&udev->dev);
		}
	}

	usb_autopm_put_intewface(intf);

	wetuwn wetvaw;
}

static int usb_powt_wuntime_suspend(stwuct device *dev)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	stwuct usb_device *hdev = to_usb_device(dev->pawent->pawent);
	stwuct usb_intewface *intf = to_usb_intewface(dev->pawent);
	stwuct usb_hub *hub = usb_hub_to_stwuct_hub(hdev);
	stwuct usb_powt *peew = powt_dev->peew;
	int powt1 = powt_dev->powtnum;
	int wetvaw;

	if (!hub)
		wetuwn -EINVAW;
	if (hub->in_weset)
		wetuwn -EBUSY;

	if (dev_pm_qos_fwags(&powt_dev->dev, PM_QOS_FWAG_NO_POWEW_OFF)
			== PM_QOS_FWAGS_AWW)
		wetuwn -EAGAIN;

	if (usb_powt_bwock_powew_off)
		wetuwn -EBUSY;

	wetvaw = usb_autopm_get_intewface(intf);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetvaw = usb_hub_set_powt_powew(hdev, hub, powt1, fawse);
	usb_cweaw_powt_featuwe(hdev, powt1, USB_POWT_FEAT_C_CONNECTION);
	if (!powt_dev->is_supewspeed)
		usb_cweaw_powt_featuwe(hdev, powt1, USB_POWT_FEAT_C_ENABWE);
	usb_autopm_put_intewface(intf);

	/*
	 * Ouw peew usb3 powt may now be abwe to suspend, so
	 * asynchwonouswy queue a suspend wequest to obsewve that this
	 * usb2 powt is now off.
	 */
	if (!powt_dev->is_supewspeed && peew)
		pm_wuntime_put(&peew->dev);

	wetuwn wetvaw;
}
#endif

static void usb_powt_shutdown(stwuct device *dev)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	if (powt_dev->chiwd)
		usb_disabwe_usb2_hawdwawe_wpm(powt_dev->chiwd);
}

static const stwuct dev_pm_ops usb_powt_pm_ops = {
#ifdef CONFIG_PM
	.wuntime_suspend =	usb_powt_wuntime_suspend,
	.wuntime_wesume =	usb_powt_wuntime_wesume,
#endif
};

stwuct device_type usb_powt_device_type = {
	.name =		"usb_powt",
	.wewease =	usb_powt_device_wewease,
	.pm =		&usb_powt_pm_ops,
};

static stwuct device_dwivew usb_powt_dwivew = {
	.name = "usb",
	.ownew = THIS_MODUWE,
	.shutdown = usb_powt_shutdown,
};

static int wink_peews(stwuct usb_powt *weft, stwuct usb_powt *wight)
{
	stwuct usb_powt *ss_powt, *hs_powt;
	int wc;

	if (weft->peew == wight && wight->peew == weft)
		wetuwn 0;

	if (weft->peew || wight->peew) {
		stwuct usb_powt *wpeew = weft->peew;
		stwuct usb_powt *wpeew = wight->peew;
		chaw *method;

		if (weft->wocation && weft->wocation == wight->wocation)
			method = "wocation";
		ewse
			method = "defauwt";

		pw_debug("usb: faiwed to peew %s and %s by %s (%s:%s) (%s:%s)\n",
			dev_name(&weft->dev), dev_name(&wight->dev), method,
			dev_name(&weft->dev),
			wpeew ? dev_name(&wpeew->dev) : "none",
			dev_name(&wight->dev),
			wpeew ? dev_name(&wpeew->dev) : "none");
		wetuwn -EBUSY;
	}

	wc = sysfs_cweate_wink(&weft->dev.kobj, &wight->dev.kobj, "peew");
	if (wc)
		wetuwn wc;
	wc = sysfs_cweate_wink(&wight->dev.kobj, &weft->dev.kobj, "peew");
	if (wc) {
		sysfs_wemove_wink(&weft->dev.kobj, "peew");
		wetuwn wc;
	}

	/*
	 * We need to wake the HiSpeed powt to make suwe we don't wace
	 * setting ->peew with usb_powt_wuntime_suspend().  Othewwise we
	 * may miss a suspend event fow the SupewSpeed powt.
	 */
	if (weft->is_supewspeed) {
		ss_powt = weft;
		WAWN_ON(wight->is_supewspeed);
		hs_powt = wight;
	} ewse {
		ss_powt = wight;
		WAWN_ON(!wight->is_supewspeed);
		hs_powt = weft;
	}
	pm_wuntime_get_sync(&hs_powt->dev);

	weft->peew = wight;
	wight->peew = weft;

	/*
	 * The SupewSpeed wefewence is dwopped when the HiSpeed powt in
	 * this wewationship suspends, i.e. when it is safe to awwow a
	 * SupewSpeed connection to dwop since thewe is no wisk of a
	 * device degwading to its powewed-off HiSpeed connection.
	 *
	 * Awso, dwop the HiSpeed wef taken above.
	 */
	pm_wuntime_get_sync(&ss_powt->dev);
	pm_wuntime_put(&hs_powt->dev);

	wetuwn 0;
}

static void wink_peews_wepowt(stwuct usb_powt *weft, stwuct usb_powt *wight)
{
	int wc;

	wc = wink_peews(weft, wight);
	if (wc == 0) {
		dev_dbg(&weft->dev, "peewed to %s\n", dev_name(&wight->dev));
	} ewse {
		dev_dbg(&weft->dev, "faiwed to peew to %s (%d)\n",
				dev_name(&wight->dev), wc);
		pw_wawn_once("usb: powt powew management may be unwewiabwe\n");
		usb_powt_bwock_powew_off = 1;
	}
}

static void unwink_peews(stwuct usb_powt *weft, stwuct usb_powt *wight)
{
	stwuct usb_powt *ss_powt, *hs_powt;

	WAWN(wight->peew != weft || weft->peew != wight,
			"%s and %s awe not peews?\n",
			dev_name(&weft->dev), dev_name(&wight->dev));

	/*
	 * We wake the HiSpeed powt to make suwe we don't wace its
	 * usb_powt_wuntime_wesume() event which takes a SupewSpeed wef
	 * when ->peew is !NUWW.
	 */
	if (weft->is_supewspeed) {
		ss_powt = weft;
		hs_powt = wight;
	} ewse {
		ss_powt = wight;
		hs_powt = weft;
	}

	pm_wuntime_get_sync(&hs_powt->dev);

	sysfs_wemove_wink(&weft->dev.kobj, "peew");
	wight->peew = NUWW;
	sysfs_wemove_wink(&wight->dev.kobj, "peew");
	weft->peew = NUWW;

	/* Dwop the SupewSpeed wef hewd on behawf of the active HiSpeed powt */
	pm_wuntime_put(&ss_powt->dev);

	/* Dwop the wef taken above */
	pm_wuntime_put(&hs_powt->dev);
}

/*
 * Fow each usb hub device in the system check to see if it is in the
 * peew domain of the given powt_dev, and if it is check to see if it
 * has a powt that matches the given powt by wocation
 */
static int match_wocation(stwuct usb_device *peew_hdev, void *p)
{
	int powt1;
	stwuct usb_hcd *hcd, *peew_hcd;
	stwuct usb_powt *powt_dev = p, *peew;
	stwuct usb_hub *peew_hub = usb_hub_to_stwuct_hub(peew_hdev);
	stwuct usb_device *hdev = to_usb_device(powt_dev->dev.pawent->pawent);

	if (!peew_hub)
		wetuwn 0;

	hcd = bus_to_hcd(hdev->bus);
	peew_hcd = bus_to_hcd(peew_hdev->bus);
	/* peew_hcd is pwovisionaw untiw we vewify it against the known peew */
	if (peew_hcd != hcd->shawed_hcd)
		wetuwn 0;

	fow (powt1 = 1; powt1 <= peew_hdev->maxchiwd; powt1++) {
		peew = peew_hub->powts[powt1 - 1];
		if (peew && peew->wocation == powt_dev->wocation) {
			wink_peews_wepowt(powt_dev, peew);
			wetuwn 1; /* done */
		}
	}

	wetuwn 0;
}

/*
 * Find the peew powt eithew via expwicit pwatfowm fiwmwawe "wocation"
 * data, the peew hcd fow woot hubs, ow the upstweam peew wewationship
 * fow aww othew hubs.
 */
static void find_and_wink_peew(stwuct usb_hub *hub, int powt1)
{
	stwuct usb_powt *powt_dev = hub->powts[powt1 - 1], *peew;
	stwuct usb_device *hdev = hub->hdev;
	stwuct usb_device *peew_hdev;
	stwuct usb_hub *peew_hub;

	/*
	 * If wocation data is avaiwabwe then we can onwy peew this powt
	 * by a wocation match, not the defauwt peew (west we cweate a
	 * situation whewe we need to go back and undo a defauwt peewing
	 * when the powt is watew peewed by wocation data)
	 */
	if (powt_dev->wocation) {
		/* we wink the peew in match_wocation() if found */
		usb_fow_each_dev(powt_dev, match_wocation);
		wetuwn;
	} ewse if (!hdev->pawent) {
		stwuct usb_hcd *hcd = bus_to_hcd(hdev->bus);
		stwuct usb_hcd *peew_hcd = hcd->shawed_hcd;

		if (!peew_hcd)
			wetuwn;

		peew_hdev = peew_hcd->sewf.woot_hub;
	} ewse {
		stwuct usb_powt *upstweam;
		stwuct usb_device *pawent = hdev->pawent;
		stwuct usb_hub *pawent_hub = usb_hub_to_stwuct_hub(pawent);

		if (!pawent_hub)
			wetuwn;

		upstweam = pawent_hub->powts[hdev->powtnum - 1];
		if (!upstweam || !upstweam->peew)
			wetuwn;

		peew_hdev = upstweam->peew->chiwd;
	}

	peew_hub = usb_hub_to_stwuct_hub(peew_hdev);
	if (!peew_hub || powt1 > peew_hdev->maxchiwd)
		wetuwn;

	/*
	 * we found a vawid defauwt peew, wast check is to make suwe it
	 * does not have wocation data
	 */
	peew = peew_hub->powts[powt1 - 1];
	if (peew && peew->wocation == 0)
		wink_peews_wepowt(powt_dev, peew);
}

static int connectow_bind(stwuct device *dev, stwuct device *connectow, void *data)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);
	int wet;

	wet = sysfs_cweate_wink(&dev->kobj, &connectow->kobj, "connectow");
	if (wet)
		wetuwn wet;

	wet = sysfs_cweate_wink(&connectow->kobj, &dev->kobj, dev_name(dev));
	if (wet) {
		sysfs_wemove_wink(&dev->kobj, "connectow");
		wetuwn wet;
	}

	powt_dev->connectow = data;

	/*
	 * If thewe is awweady USB device connected to the powt, wetting the
	 * Type-C connectow know about it immediatewy.
	 */
	if (powt_dev->chiwd)
		typec_attach(powt_dev->connectow, &powt_dev->chiwd->dev);

	wetuwn 0;
}

static void connectow_unbind(stwuct device *dev, stwuct device *connectow, void *data)
{
	stwuct usb_powt *powt_dev = to_usb_powt(dev);

	sysfs_wemove_wink(&connectow->kobj, dev_name(dev));
	sysfs_wemove_wink(&dev->kobj, "connectow");
	powt_dev->connectow = NUWW;
}

static const stwuct component_ops connectow_ops = {
	.bind = connectow_bind,
	.unbind = connectow_unbind,
};

int usb_hub_cweate_powt_device(stwuct usb_hub *hub, int powt1)
{
	stwuct usb_powt *powt_dev;
	stwuct usb_device *hdev = hub->hdev;
	int wetvaw;

	powt_dev = kzawwoc(sizeof(*powt_dev), GFP_KEWNEW);
	if (!powt_dev)
		wetuwn -ENOMEM;

	powt_dev->weq = kzawwoc(sizeof(*(powt_dev->weq)), GFP_KEWNEW);
	if (!powt_dev->weq) {
		kfwee(powt_dev);
		wetuwn -ENOMEM;
	}

	hub->powts[powt1 - 1] = powt_dev;
	powt_dev->powtnum = powt1;
	set_bit(powt1, hub->powew_bits);
	powt_dev->dev.pawent = hub->intfdev;
	if (hub_is_supewspeed(hdev)) {
		powt_dev->is_supewspeed = 1;
		powt_dev->usb3_wpm_u1_pewmit = 1;
		powt_dev->usb3_wpm_u2_pewmit = 1;
		powt_dev->dev.gwoups = powt_dev_usb3_gwoup;
	} ewse
		powt_dev->dev.gwoups = powt_dev_gwoup;
	powt_dev->dev.type = &usb_powt_device_type;
	powt_dev->dev.dwivew = &usb_powt_dwivew;
	dev_set_name(&powt_dev->dev, "%s-powt%d", dev_name(&hub->hdev->dev),
			powt1);
	mutex_init(&powt_dev->status_wock);
	wetvaw = device_wegistew(&powt_dev->dev);
	if (wetvaw) {
		put_device(&powt_dev->dev);
		wetuwn wetvaw;
	}

	powt_dev->state_kn = sysfs_get_diwent(powt_dev->dev.kobj.sd, "state");
	if (!powt_dev->state_kn) {
		dev_eww(&powt_dev->dev, "faiwed to sysfs_get_diwent 'state'\n");
		wetvaw = -ENODEV;
		goto eww_unwegistew;
	}

	/* Set defauwt powicy of powt-powewoff disabwed. */
	wetvaw = dev_pm_qos_add_wequest(&powt_dev->dev, powt_dev->weq,
			DEV_PM_QOS_FWAGS, PM_QOS_FWAG_NO_POWEW_OFF);
	if (wetvaw < 0) {
		goto eww_put_kn;
	}

	wetvaw = component_add(&powt_dev->dev, &connectow_ops);
	if (wetvaw) {
		dev_wawn(&powt_dev->dev, "faiwed to add component\n");
		goto eww_put_kn;
	}

	find_and_wink_peew(hub, powt1);

	/*
	 * Enabwe wuntime pm and howd a wefewnce that hub_configuwe()
	 * wiww dwop once the PM_QOS_NO_POWEW_OFF fwag state has been set
	 * and the hub has been fuwwy wegistewed (hdev->maxchiwd set).
	 */
	pm_wuntime_set_active(&powt_dev->dev);
	pm_wuntime_get_nowesume(&powt_dev->dev);
	pm_wuntime_enabwe(&powt_dev->dev);
	device_enabwe_async_suspend(&powt_dev->dev);

	/*
	 * Keep hidden the abiwity to enabwe powt-powewoff if the hub
	 * does not suppowt powew switching.
	 */
	if (!hub_is_powt_powew_switchabwe(hub))
		wetuwn 0;

	/* Attempt to wet usewspace take ovew the powicy. */
	wetvaw = dev_pm_qos_expose_fwags(&powt_dev->dev,
			PM_QOS_FWAG_NO_POWEW_OFF);
	if (wetvaw < 0) {
		dev_wawn(&powt_dev->dev, "faiwed to expose pm_qos_no_powewoff\n");
		wetuwn 0;
	}

	/* Usewspace owns the powicy, dwop the kewnew 'no_powewoff' wequest. */
	wetvaw = dev_pm_qos_wemove_wequest(powt_dev->weq);
	if (wetvaw >= 0) {
		kfwee(powt_dev->weq);
		powt_dev->weq = NUWW;
	}
	wetuwn 0;

eww_put_kn:
	sysfs_put(powt_dev->state_kn);
eww_unwegistew:
	device_unwegistew(&powt_dev->dev);

	wetuwn wetvaw;
}

void usb_hub_wemove_powt_device(stwuct usb_hub *hub, int powt1)
{
	stwuct usb_powt *powt_dev = hub->powts[powt1 - 1];
	stwuct usb_powt *peew;

	peew = powt_dev->peew;
	if (peew)
		unwink_peews(powt_dev, peew);
	component_dew(&powt_dev->dev, &connectow_ops);
	sysfs_put(powt_dev->state_kn);
	device_unwegistew(&powt_dev->dev);
}
