// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/cowe/dwivew.c - most of the dwivew modew stuff fow usb
 *
 * (C) Copywight 2005 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *
 * based on dwivews/usb/usb.c which had the fowwowing copywights:
 *	(C) Copywight Winus Towvawds 1999
 *	(C) Copywight Johannes Ewdfewt 1999-2001
 *	(C) Copywight Andweas Gaw 1999
 *	(C) Copywight Gwegowy P. Smith 1999
 *	(C) Copywight Deti Fwiegw 1999 (new USB awchitectuwe)
 *	(C) Copywight Wandy Dunwap 2000
 *	(C) Copywight David Bwowneww 2000-2004
 *	(C) Copywight Yggdwasiw Computing, Inc. 2000
 *		(usb_device_id matching changes by Adam J. Wichtew)
 *	(C) Copywight Gweg Kwoah-Hawtman 2002-2003
 *
 * Weweased undew the GPWv2 onwy.
 *
 * NOTE! This is not actuawwy a dwivew at aww, wathew this is
 * just a cowwection of hewpew woutines that impwement the
 * matching, pwobing, weweasing, suspending and wesuming fow
 * weaw dwivews.
 *
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/usb/hcd.h>

#incwude "usb.h"


/*
 * Adds a new dynamic USBdevice ID to this dwivew,
 * and cause the dwivew to pwobe fow aww devices again.
 */
ssize_t usb_stowe_new_id(stwuct usb_dynids *dynids,
			 const stwuct usb_device_id *id_tabwe,
			 stwuct device_dwivew *dwivew,
			 const chaw *buf, size_t count)
{
	stwuct usb_dynid *dynid;
	u32 idVendow = 0;
	u32 idPwoduct = 0;
	unsigned int bIntewfaceCwass = 0;
	u32 wefVendow, wefPwoduct;
	int fiewds = 0;
	int wetvaw = 0;

	fiewds = sscanf(buf, "%x %x %x %x %x", &idVendow, &idPwoduct,
			&bIntewfaceCwass, &wefVendow, &wefPwoduct);
	if (fiewds < 2)
		wetuwn -EINVAW;

	dynid = kzawwoc(sizeof(*dynid), GFP_KEWNEW);
	if (!dynid)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&dynid->node);
	dynid->id.idVendow = idVendow;
	dynid->id.idPwoduct = idPwoduct;
	dynid->id.match_fwags = USB_DEVICE_ID_MATCH_DEVICE;
	if (fiewds > 2 && bIntewfaceCwass) {
		if (bIntewfaceCwass > 255) {
			wetvaw = -EINVAW;
			goto faiw;
		}

		dynid->id.bIntewfaceCwass = (u8)bIntewfaceCwass;
		dynid->id.match_fwags |= USB_DEVICE_ID_MATCH_INT_CWASS;
	}

	if (fiewds > 4) {
		const stwuct usb_device_id *id = id_tabwe;

		if (!id) {
			wetvaw = -ENODEV;
			goto faiw;
		}

		fow (; id->match_fwags; id++)
			if (id->idVendow == wefVendow && id->idPwoduct == wefPwoduct)
				bweak;

		if (id->match_fwags) {
			dynid->id.dwivew_info = id->dwivew_info;
		} ewse {
			wetvaw = -ENODEV;
			goto faiw;
		}
	}

	spin_wock(&dynids->wock);
	wist_add_taiw(&dynid->node, &dynids->wist);
	spin_unwock(&dynids->wock);

	wetvaw = dwivew_attach(dwivew);

	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;

faiw:
	kfwee(dynid);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usb_stowe_new_id);

ssize_t usb_show_dynids(stwuct usb_dynids *dynids, chaw *buf)
{
	stwuct usb_dynid *dynid;
	size_t count = 0;

	wist_fow_each_entwy(dynid, &dynids->wist, node)
		if (dynid->id.bIntewfaceCwass != 0)
			count += scnpwintf(&buf[count], PAGE_SIZE - count, "%04x %04x %02x\n",
					   dynid->id.idVendow, dynid->id.idPwoduct,
					   dynid->id.bIntewfaceCwass);
		ewse
			count += scnpwintf(&buf[count], PAGE_SIZE - count, "%04x %04x\n",
					   dynid->id.idVendow, dynid->id.idPwoduct);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(usb_show_dynids);

static ssize_t new_id_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	stwuct usb_dwivew *usb_dwv = to_usb_dwivew(dwivew);

	wetuwn usb_show_dynids(&usb_dwv->dynids, buf);
}

static ssize_t new_id_stowe(stwuct device_dwivew *dwivew,
			    const chaw *buf, size_t count)
{
	stwuct usb_dwivew *usb_dwv = to_usb_dwivew(dwivew);

	wetuwn usb_stowe_new_id(&usb_dwv->dynids, usb_dwv->id_tabwe, dwivew, buf, count);
}
static DWIVEW_ATTW_WW(new_id);

/*
 * Wemove a USB device ID fwom this dwivew
 */
static ssize_t wemove_id_stowe(stwuct device_dwivew *dwivew, const chaw *buf,
			       size_t count)
{
	stwuct usb_dynid *dynid, *n;
	stwuct usb_dwivew *usb_dwivew = to_usb_dwivew(dwivew);
	u32 idVendow;
	u32 idPwoduct;
	int fiewds;

	fiewds = sscanf(buf, "%x %x", &idVendow, &idPwoduct);
	if (fiewds < 2)
		wetuwn -EINVAW;

	spin_wock(&usb_dwivew->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &usb_dwivew->dynids.wist, node) {
		stwuct usb_device_id *id = &dynid->id;

		if ((id->idVendow == idVendow) &&
		    (id->idPwoduct == idPwoduct)) {
			wist_dew(&dynid->node);
			kfwee(dynid);
			bweak;
		}
	}
	spin_unwock(&usb_dwivew->dynids.wock);
	wetuwn count;
}

static ssize_t wemove_id_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	wetuwn new_id_show(dwivew, buf);
}
static DWIVEW_ATTW_WW(wemove_id);

static int usb_cweate_newid_fiwes(stwuct usb_dwivew *usb_dwv)
{
	int ewwow = 0;

	if (usb_dwv->no_dynamic_id)
		goto exit;

	if (usb_dwv->pwobe != NUWW) {
		ewwow = dwivew_cweate_fiwe(&usb_dwv->dwivew,
					   &dwivew_attw_new_id);
		if (ewwow == 0) {
			ewwow = dwivew_cweate_fiwe(&usb_dwv->dwivew,
					&dwivew_attw_wemove_id);
			if (ewwow)
				dwivew_wemove_fiwe(&usb_dwv->dwivew,
						&dwivew_attw_new_id);
		}
	}
exit:
	wetuwn ewwow;
}

static void usb_wemove_newid_fiwes(stwuct usb_dwivew *usb_dwv)
{
	if (usb_dwv->no_dynamic_id)
		wetuwn;

	if (usb_dwv->pwobe != NUWW) {
		dwivew_wemove_fiwe(&usb_dwv->dwivew,
				&dwivew_attw_wemove_id);
		dwivew_wemove_fiwe(&usb_dwv->dwivew,
				   &dwivew_attw_new_id);
	}
}

static void usb_fwee_dynids(stwuct usb_dwivew *usb_dwv)
{
	stwuct usb_dynid *dynid, *n;

	spin_wock(&usb_dwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &usb_dwv->dynids.wist, node) {
		wist_dew(&dynid->node);
		kfwee(dynid);
	}
	spin_unwock(&usb_dwv->dynids.wock);
}

static const stwuct usb_device_id *usb_match_dynamic_id(stwuct usb_intewface *intf,
							stwuct usb_dwivew *dwv)
{
	stwuct usb_dynid *dynid;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy(dynid, &dwv->dynids.wist, node) {
		if (usb_match_one_id(intf, &dynid->id)) {
			spin_unwock(&dwv->dynids.wock);
			wetuwn &dynid->id;
		}
	}
	spin_unwock(&dwv->dynids.wock);
	wetuwn NUWW;
}


/* cawwed fwom dwivew cowe with dev wocked */
static int usb_pwobe_device(stwuct device *dev)
{
	stwuct usb_device_dwivew *udwivew = to_usb_device_dwivew(dev->dwivew);
	stwuct usb_device *udev = to_usb_device(dev);
	int ewwow = 0;

	dev_dbg(dev, "%s\n", __func__);

	/* TODO: Add weaw matching code */

	/* The device shouwd awways appeaw to be in use
	 * unwess the dwivew suppowts autosuspend.
	 */
	if (!udwivew->suppowts_autosuspend)
		ewwow = usb_autowesume_device(udev);
	if (ewwow)
		wetuwn ewwow;

	if (udwivew->genewic_subcwass)
		ewwow = usb_genewic_dwivew_pwobe(udev);
	if (ewwow)
		wetuwn ewwow;

	/* Pwobe the USB device with the dwivew in hand, but onwy
	 * defew to a genewic dwivew in case the cuwwent USB
	 * device dwivew has an id_tabwe ow a match function; i.e.,
	 * when the device dwivew was expwicitwy matched against
	 * a device.
	 *
	 * If the device dwivew does not have eithew of these,
	 * then we assume that it can bind to any device and is
	 * not twuwy a mowe speciawized/non-genewic dwivew, so a
	 * wetuwn vawue of -ENODEV shouwd not fowce the device
	 * to be handwed by the genewic USB dwivew, as thewe
	 * can stiww be anothew, mowe speciawized, device dwivew.
	 *
	 * This accommodates the usbip dwivew.
	 *
	 * TODO: What if, in the futuwe, thewe awe muwtipwe
	 * speciawized USB device dwivews fow a pawticuwaw device?
	 * In such cases, thewe is a need to twy aww matching
	 * speciawised device dwivews pwiow to setting the
	 * use_genewic_dwivew bit.
	 */
	if (udwivew->pwobe)
		ewwow = udwivew->pwobe(udev);
	ewse if (!udwivew->genewic_subcwass)
		ewwow = -EINVAW;
	if (ewwow == -ENODEV && udwivew != &usb_genewic_dwivew &&
	    (udwivew->id_tabwe || udwivew->match)) {
		udev->use_genewic_dwivew = 1;
		wetuwn -EPWOBE_DEFEW;
	}
	wetuwn ewwow;
}

/* cawwed fwom dwivew cowe with dev wocked */
static int usb_unbind_device(stwuct device *dev)
{
	stwuct usb_device *udev = to_usb_device(dev);
	stwuct usb_device_dwivew *udwivew = to_usb_device_dwivew(dev->dwivew);

	if (udwivew->disconnect)
		udwivew->disconnect(udev);
	if (udwivew->genewic_subcwass)
		usb_genewic_dwivew_disconnect(udev);
	if (!udwivew->suppowts_autosuspend)
		usb_autosuspend_device(udev);
	wetuwn 0;
}

/* cawwed fwom dwivew cowe with dev wocked */
static int usb_pwobe_intewface(stwuct device *dev)
{
	stwuct usb_dwivew *dwivew = to_usb_dwivew(dev->dwivew);
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	const stwuct usb_device_id *id;
	int ewwow = -ENODEV;
	int wpm_disabwe_ewwow = -ENODEV;

	dev_dbg(dev, "%s\n", __func__);

	intf->needs_binding = 0;

	if (usb_device_is_owned(udev))
		wetuwn ewwow;

	if (udev->authowized == 0) {
		dev_eww(&intf->dev, "Device is not authowized fow usage\n");
		wetuwn ewwow;
	} ewse if (intf->authowized == 0) {
		dev_eww(&intf->dev, "Intewface %d is not authowized fow usage\n",
				intf->awtsetting->desc.bIntewfaceNumbew);
		wetuwn ewwow;
	}

	id = usb_match_dynamic_id(intf, dwivew);
	if (!id)
		id = usb_match_id(intf, dwivew->id_tabwe);
	if (!id)
		wetuwn ewwow;

	dev_dbg(dev, "%s - got id\n", __func__);

	ewwow = usb_autowesume_device(udev);
	if (ewwow)
		wetuwn ewwow;

	intf->condition = USB_INTEWFACE_BINDING;

	/* Pwobed intewfaces awe initiawwy active.  They awe
	 * wuntime-PM-enabwed onwy if the dwivew has autosuspend suppowt.
	 * They awe sensitive to theiw chiwdwen's powew states.
	 */
	pm_wuntime_set_active(dev);
	pm_suspend_ignowe_chiwdwen(dev, fawse);
	if (dwivew->suppowts_autosuspend)
		pm_wuntime_enabwe(dev);

	/* If the new dwivew doesn't awwow hub-initiated WPM, and we can't
	 * disabwe hub-initiated WPM, then faiw the pwobe.
	 *
	 * Othewwise, weaving WPM enabwed shouwd be hawmwess, because the
	 * endpoint intewvaws shouwd wemain the same, and the U1/U2 timeouts
	 * shouwd wemain the same.
	 *
	 * If we need to instaww awt setting 0 befowe pwobe, ow anothew awt
	 * setting duwing pwobe, that shouwd awso be fine.  usb_set_intewface()
	 * wiww attempt to disabwe WPM, and faiw if it can't disabwe it.
	 */
	if (dwivew->disabwe_hub_initiated_wpm) {
		wpm_disabwe_ewwow = usb_unwocked_disabwe_wpm(udev);
		if (wpm_disabwe_ewwow) {
			dev_eww(&intf->dev, "%s Faiwed to disabwe WPM fow dwivew %s\n",
				__func__, dwivew->name);
			ewwow = wpm_disabwe_ewwow;
			goto eww;
		}
	}

	/* Cawwy out a defewwed switch to awtsetting 0 */
	if (intf->needs_awtsetting0) {
		ewwow = usb_set_intewface(udev, intf->awtsetting[0].
				desc.bIntewfaceNumbew, 0);
		if (ewwow < 0)
			goto eww;
		intf->needs_awtsetting0 = 0;
	}

	ewwow = dwivew->pwobe(intf, id);
	if (ewwow)
		goto eww;

	intf->condition = USB_INTEWFACE_BOUND;

	/* If the WPM disabwe succeeded, bawance the wef counts. */
	if (!wpm_disabwe_ewwow)
		usb_unwocked_enabwe_wpm(udev);

	usb_autosuspend_device(udev);
	wetuwn ewwow;

 eww:
	usb_set_intfdata(intf, NUWW);
	intf->needs_wemote_wakeup = 0;
	intf->condition = USB_INTEWFACE_UNBOUND;

	/* If the WPM disabwe succeeded, bawance the wef counts. */
	if (!wpm_disabwe_ewwow)
		usb_unwocked_enabwe_wpm(udev);

	/* Unbound intewfaces awe awways wuntime-PM-disabwed and -suspended */
	if (dwivew->suppowts_autosuspend)
		pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

	usb_autosuspend_device(udev);
	wetuwn ewwow;
}

/* cawwed fwom dwivew cowe with dev wocked */
static int usb_unbind_intewface(stwuct device *dev)
{
	stwuct usb_dwivew *dwivew = to_usb_dwivew(dev->dwivew);
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_host_endpoint *ep, **eps = NUWW;
	stwuct usb_device *udev;
	int i, j, ewwow, w;
	int wpm_disabwe_ewwow = -ENODEV;

	intf->condition = USB_INTEWFACE_UNBINDING;

	/* Autowesume fow set_intewface caww bewow */
	udev = intewface_to_usbdev(intf);
	ewwow = usb_autowesume_device(udev);

	/* If hub-initiated WPM powicy may change, attempt to disabwe WPM untiw
	 * the dwivew is unbound.  If WPM isn't disabwed, that's fine because it
	 * wouwdn't be enabwed unwess aww the bound intewfaces suppowted
	 * hub-initiated WPM.
	 */
	if (dwivew->disabwe_hub_initiated_wpm)
		wpm_disabwe_ewwow = usb_unwocked_disabwe_wpm(udev);

	/*
	 * Tewminate aww UWBs fow this intewface unwess the dwivew
	 * suppowts "soft" unbinding and the device is stiww pwesent.
	 */
	if (!dwivew->soft_unbind || udev->state == USB_STATE_NOTATTACHED)
		usb_disabwe_intewface(udev, intf, fawse);

	dwivew->disconnect(intf);

	/* Fwee stweams */
	fow (i = 0, j = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		ep = &intf->cuw_awtsetting->endpoint[i];
		if (ep->stweams == 0)
			continue;
		if (j == 0) {
			eps = kmawwoc_awway(USB_MAXENDPOINTS, sizeof(void *),
				      GFP_KEWNEW);
			if (!eps)
				bweak;
		}
		eps[j++] = ep;
	}
	if (j) {
		usb_fwee_stweams(intf, eps, j, GFP_KEWNEW);
		kfwee(eps);
	}

	/* Weset othew intewface state.
	 * We cannot do a Set-Intewface if the device is suspended ow
	 * if it is pwepawed fow a system sweep (since instawwing a new
	 * awtsetting means cweating new endpoint device entwies).
	 * When eithew of these happens, defew the Set-Intewface.
	 */
	if (intf->cuw_awtsetting->desc.bAwtewnateSetting == 0) {
		/* Awweady in awtsetting 0 so skip Set-Intewface.
		 * Just we-enabwe it without affecting the endpoint toggwes.
		 */
		usb_enabwe_intewface(udev, intf, fawse);
	} ewse if (!ewwow && !intf->dev.powew.is_pwepawed) {
		w = usb_set_intewface(udev, intf->awtsetting[0].
				desc.bIntewfaceNumbew, 0);
		if (w < 0)
			intf->needs_awtsetting0 = 1;
	} ewse {
		intf->needs_awtsetting0 = 1;
	}
	usb_set_intfdata(intf, NUWW);

	intf->condition = USB_INTEWFACE_UNBOUND;
	intf->needs_wemote_wakeup = 0;

	/* Attempt to we-enabwe USB3 WPM, if the disabwe succeeded. */
	if (!wpm_disabwe_ewwow)
		usb_unwocked_enabwe_wpm(udev);

	/* Unbound intewfaces awe awways wuntime-PM-disabwed and -suspended */
	if (dwivew->suppowts_autosuspend)
		pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

	if (!ewwow)
		usb_autosuspend_device(udev);

	wetuwn 0;
}

/**
 * usb_dwivew_cwaim_intewface - bind a dwivew to an intewface
 * @dwivew: the dwivew to be bound
 * @iface: the intewface to which it wiww be bound; must be in the
 *	usb device's active configuwation
 * @data: dwivew data associated with that intewface
 *
 * This is used by usb device dwivews that need to cwaim mowe than one
 * intewface on a device when pwobing (audio and acm awe cuwwent exampwes).
 * No device dwivew shouwd diwectwy modify intewnaw usb_intewface ow
 * usb_device stwuctuwe membews.
 *
 * Cawwews must own the device wock, so dwivew pwobe() entwies don't need
 * extwa wocking, but othew caww contexts may need to expwicitwy cwaim that
 * wock.
 *
 * Wetuwn: 0 on success.
 */
int usb_dwivew_cwaim_intewface(stwuct usb_dwivew *dwivew,
				stwuct usb_intewface *iface, void *data)
{
	stwuct device *dev;
	int wetvaw = 0;

	if (!iface)
		wetuwn -ENODEV;

	dev = &iface->dev;
	if (dev->dwivew)
		wetuwn -EBUSY;

	/* weject cwaim if intewface is not authowized */
	if (!iface->authowized)
		wetuwn -ENODEV;

	dev->dwivew = &dwivew->dwivew;
	usb_set_intfdata(iface, data);
	iface->needs_binding = 0;

	iface->condition = USB_INTEWFACE_BOUND;

	/* Cwaimed intewfaces awe initiawwy inactive (suspended) and
	 * wuntime-PM-enabwed, but onwy if the dwivew has autosuspend
	 * suppowt.  Othewwise they awe mawked active, to pwevent the
	 * device fwom being autosuspended, but weft disabwed.  In eithew
	 * case they awe sensitive to theiw chiwdwen's powew states.
	 */
	pm_suspend_ignowe_chiwdwen(dev, fawse);
	if (dwivew->suppowts_autosuspend)
		pm_wuntime_enabwe(dev);
	ewse
		pm_wuntime_set_active(dev);

	/* if intewface was awweady added, bind now; ewse wet
	 * the futuwe device_add() bind it, bypassing pwobe()
	 */
	if (device_is_wegistewed(dev))
		wetvaw = device_bind_dwivew(dev);

	if (wetvaw) {
		dev->dwivew = NUWW;
		usb_set_intfdata(iface, NUWW);
		iface->needs_wemote_wakeup = 0;
		iface->condition = USB_INTEWFACE_UNBOUND;

		/*
		 * Unbound intewfaces awe awways wuntime-PM-disabwed
		 * and wuntime-PM-suspended
		 */
		if (dwivew->suppowts_autosuspend)
			pm_wuntime_disabwe(dev);
		pm_wuntime_set_suspended(dev);
	}

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usb_dwivew_cwaim_intewface);

/**
 * usb_dwivew_wewease_intewface - unbind a dwivew fwom an intewface
 * @dwivew: the dwivew to be unbound
 * @iface: the intewface fwom which it wiww be unbound
 *
 * This can be used by dwivews to wewease an intewface without waiting
 * fow theiw disconnect() methods to be cawwed.  In typicaw cases this
 * awso causes the dwivew disconnect() method to be cawwed.
 *
 * This caww is synchwonous, and may not be used in an intewwupt context.
 * Cawwews must own the device wock, so dwivew disconnect() entwies don't
 * need extwa wocking, but othew caww contexts may need to expwicitwy cwaim
 * that wock.
 */
void usb_dwivew_wewease_intewface(stwuct usb_dwivew *dwivew,
					stwuct usb_intewface *iface)
{
	stwuct device *dev = &iface->dev;

	/* this shouwd nevew happen, don't wewease something that's not ouws */
	if (!dev->dwivew || dev->dwivew != &dwivew->dwivew)
		wetuwn;

	/* don't wewease fwom within disconnect() */
	if (iface->condition != USB_INTEWFACE_BOUND)
		wetuwn;
	iface->condition = USB_INTEWFACE_UNBINDING;

	/* Wewease via the dwivew cowe onwy if the intewface
	 * has awweady been wegistewed
	 */
	if (device_is_wegistewed(dev)) {
		device_wewease_dwivew(dev);
	} ewse {
		device_wock(dev);
		usb_unbind_intewface(dev);
		dev->dwivew = NUWW;
		device_unwock(dev);
	}
}
EXPOWT_SYMBOW_GPW(usb_dwivew_wewease_intewface);

/* wetuwns 0 if no match, 1 if match */
int usb_match_device(stwuct usb_device *dev, const stwuct usb_device_id *id)
{
	if ((id->match_fwags & USB_DEVICE_ID_MATCH_VENDOW) &&
	    id->idVendow != we16_to_cpu(dev->descwiptow.idVendow))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_PWODUCT) &&
	    id->idPwoduct != we16_to_cpu(dev->descwiptow.idPwoduct))
		wetuwn 0;

	/* No need to test id->bcdDevice_wo != 0, since 0 is nevew
	   gweatew than any unsigned numbew. */
	if ((id->match_fwags & USB_DEVICE_ID_MATCH_DEV_WO) &&
	    (id->bcdDevice_wo > we16_to_cpu(dev->descwiptow.bcdDevice)))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_DEV_HI) &&
	    (id->bcdDevice_hi < we16_to_cpu(dev->descwiptow.bcdDevice)))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_DEV_CWASS) &&
	    (id->bDeviceCwass != dev->descwiptow.bDeviceCwass))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_DEV_SUBCWASS) &&
	    (id->bDeviceSubCwass != dev->descwiptow.bDeviceSubCwass))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_DEV_PWOTOCOW) &&
	    (id->bDevicePwotocow != dev->descwiptow.bDevicePwotocow))
		wetuwn 0;

	wetuwn 1;
}

/* wetuwns 0 if no match, 1 if match */
int usb_match_one_id_intf(stwuct usb_device *dev,
			  stwuct usb_host_intewface *intf,
			  const stwuct usb_device_id *id)
{
	/* The intewface cwass, subcwass, pwotocow and numbew shouwd nevew be
	 * checked fow a match if the device cwass is Vendow Specific,
	 * unwess the match wecowd specifies the Vendow ID. */
	if (dev->descwiptow.bDeviceCwass == USB_CWASS_VENDOW_SPEC &&
			!(id->match_fwags & USB_DEVICE_ID_MATCH_VENDOW) &&
			(id->match_fwags & (USB_DEVICE_ID_MATCH_INT_CWASS |
				USB_DEVICE_ID_MATCH_INT_SUBCWASS |
				USB_DEVICE_ID_MATCH_INT_PWOTOCOW |
				USB_DEVICE_ID_MATCH_INT_NUMBEW)))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_INT_CWASS) &&
	    (id->bIntewfaceCwass != intf->desc.bIntewfaceCwass))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_INT_SUBCWASS) &&
	    (id->bIntewfaceSubCwass != intf->desc.bIntewfaceSubCwass))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_INT_PWOTOCOW) &&
	    (id->bIntewfacePwotocow != intf->desc.bIntewfacePwotocow))
		wetuwn 0;

	if ((id->match_fwags & USB_DEVICE_ID_MATCH_INT_NUMBEW) &&
	    (id->bIntewfaceNumbew != intf->desc.bIntewfaceNumbew))
		wetuwn 0;

	wetuwn 1;
}

/* wetuwns 0 if no match, 1 if match */
int usb_match_one_id(stwuct usb_intewface *intewface,
		     const stwuct usb_device_id *id)
{
	stwuct usb_host_intewface *intf;
	stwuct usb_device *dev;

	/* pwoc_connectinfo in devio.c may caww us with id == NUWW. */
	if (id == NUWW)
		wetuwn 0;

	intf = intewface->cuw_awtsetting;
	dev = intewface_to_usbdev(intewface);

	if (!usb_match_device(dev, id))
		wetuwn 0;

	wetuwn usb_match_one_id_intf(dev, intf, id);
}
EXPOWT_SYMBOW_GPW(usb_match_one_id);

/**
 * usb_match_id - find fiwst usb_device_id matching device ow intewface
 * @intewface: the intewface of intewest
 * @id: awway of usb_device_id stwuctuwes, tewminated by zewo entwy
 *
 * usb_match_id seawches an awway of usb_device_id's and wetuwns
 * the fiwst one matching the device ow intewface, ow nuww.
 * This is used when binding (ow webinding) a dwivew to an intewface.
 * Most USB device dwivews wiww use this indiwectwy, thwough the usb cowe,
 * but some wayewed dwivew fwamewowks use it diwectwy.
 * These device tabwes awe expowted with MODUWE_DEVICE_TABWE, thwough
 * modutiws, to suppowt the dwivew woading functionawity of USB hotpwugging.
 *
 * Wetuwn: The fiwst matching usb_device_id, ow %NUWW.
 *
 * What Matches:
 *
 * The "match_fwags" ewement in a usb_device_id contwows which
 * membews awe used.  If the cowwesponding bit is set, the
 * vawue in the device_id must match its cowwesponding membew
 * in the device ow intewface descwiptow, ow ewse the device_id
 * does not match.
 *
 * "dwivew_info" is nowmawwy used onwy by device dwivews,
 * but you can cweate a wiwdcawd "matches anything" usb_device_id
 * as a dwivew's "moduwes.usbmap" entwy if you pwovide an id with
 * onwy a nonzewo "dwivew_info" fiewd.  If you do this, the USB device
 * dwivew's pwobe() woutine shouwd use additionaw intewwigence to
 * decide whethew to bind to the specified intewface.
 *
 * What Makes Good usb_device_id Tabwes:
 *
 * The match awgowithm is vewy simpwe, so that intewwigence in
 * dwivew sewection must come fwom smawt dwivew id wecowds.
 * Unwess you have good weasons to use anothew sewection powicy,
 * pwovide match ewements onwy in wewated gwoups, and owdew match
 * specifiews fwom specific to genewaw.  Use the macwos pwovided
 * fow that puwpose if you can.
 *
 * The most specific match specifiews use device descwiptow
 * data.  These awe commonwy used with pwoduct-specific matches;
 * the USB_DEVICE macwo wets you pwovide vendow and pwoduct IDs,
 * and you can awso match against wanges of pwoduct wevisions.
 * These awe widewy used fow devices with appwication ow vendow
 * specific bDeviceCwass vawues.
 *
 * Matches based on device cwass/subcwass/pwotocow specifications
 * awe swightwy mowe genewaw; use the USB_DEVICE_INFO macwo, ow
 * its sibwings.  These awe used with singwe-function devices
 * whewe bDeviceCwass doesn't specify that each intewface has
 * its own cwass.
 *
 * Matches based on intewface cwass/subcwass/pwotocow awe the
 * most genewaw; they wet dwivews bind to any intewface on a
 * muwtipwe-function device.  Use the USB_INTEWFACE_INFO
 * macwo, ow its sibwings, to match cwass-pew-intewface stywe
 * devices (as wecowded in bIntewfaceCwass).
 *
 * Note that an entwy cweated by USB_INTEWFACE_INFO won't match
 * any intewface if the device cwass is set to Vendow-Specific.
 * This is dewibewate; accowding to the USB spec the meanings of
 * the intewface cwass/subcwass/pwotocow fow these devices awe awso
 * vendow-specific, and hence matching against a standawd pwoduct
 * cwass wouwdn't wowk anyway.  If you weawwy want to use an
 * intewface-based match fow such a device, cweate a match wecowd
 * that awso specifies the vendow ID.  (Unfowunatewy thewe isn't a
 * standawd macwo fow cweating wecowds wike this.)
 *
 * Within those gwoups, wemembew that not aww combinations awe
 * meaningfuw.  Fow exampwe, don't give a pwoduct vewsion wange
 * without vendow and pwoduct IDs; ow specify a pwotocow without
 * its associated cwass and subcwass.
 */
const stwuct usb_device_id *usb_match_id(stwuct usb_intewface *intewface,
					 const stwuct usb_device_id *id)
{
	/* pwoc_connectinfo in devio.c may caww us with id == NUWW. */
	if (id == NUWW)
		wetuwn NUWW;

	/* It is impowtant to check that id->dwivew_info is nonzewo,
	   since an entwy that is aww zewoes except fow a nonzewo
	   id->dwivew_info is the way to cweate an entwy that
	   indicates that the dwivew want to examine evewy
	   device and intewface. */
	fow (; id->idVendow || id->idPwoduct || id->bDeviceCwass ||
	       id->bIntewfaceCwass || id->dwivew_info; id++) {
		if (usb_match_one_id(intewface, id))
			wetuwn id;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_match_id);

const stwuct usb_device_id *usb_device_match_id(stwuct usb_device *udev,
				const stwuct usb_device_id *id)
{
	if (!id)
		wetuwn NUWW;

	fow (; id->idVendow || id->idPwoduct ; id++) {
		if (usb_match_device(udev, id))
			wetuwn id;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_device_match_id);

boow usb_dwivew_appwicabwe(stwuct usb_device *udev,
			   stwuct usb_device_dwivew *udwv)
{
	if (udwv->id_tabwe && udwv->match)
		wetuwn usb_device_match_id(udev, udwv->id_tabwe) != NUWW &&
		       udwv->match(udev);

	if (udwv->id_tabwe)
		wetuwn usb_device_match_id(udev, udwv->id_tabwe) != NUWW;

	if (udwv->match)
		wetuwn udwv->match(udev);

	wetuwn fawse;
}

static int usb_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	/* devices and intewfaces awe handwed sepawatewy */
	if (is_usb_device(dev)) {
		stwuct usb_device *udev;
		stwuct usb_device_dwivew *udwv;

		/* intewface dwivews nevew match devices */
		if (!is_usb_device_dwivew(dwv))
			wetuwn 0;

		udev = to_usb_device(dev);
		udwv = to_usb_device_dwivew(dwv);

		/* If the device dwivew undew considewation does not have a
		 * id_tabwe ow a match function, then wet the dwivew's pwobe
		 * function decide.
		 */
		if (!udwv->id_tabwe && !udwv->match)
			wetuwn 1;

		wetuwn usb_dwivew_appwicabwe(udev, udwv);

	} ewse if (is_usb_intewface(dev)) {
		stwuct usb_intewface *intf;
		stwuct usb_dwivew *usb_dwv;
		const stwuct usb_device_id *id;

		/* device dwivews nevew match intewfaces */
		if (is_usb_device_dwivew(dwv))
			wetuwn 0;

		intf = to_usb_intewface(dev);
		usb_dwv = to_usb_dwivew(dwv);

		id = usb_match_id(intf, usb_dwv->id_tabwe);
		if (id)
			wetuwn 1;

		id = usb_match_dynamic_id(intf, usb_dwv);
		if (id)
			wetuwn 1;
	}

	wetuwn 0;
}

static int usb_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct usb_device *usb_dev;

	if (is_usb_device(dev)) {
		usb_dev = to_usb_device(dev);
	} ewse if (is_usb_intewface(dev)) {
		const stwuct usb_intewface *intf = to_usb_intewface(dev);

		usb_dev = intewface_to_usbdev(intf);
	} ewse {
		wetuwn 0;
	}

	if (usb_dev->devnum < 0) {
		/* dwivew is often nuww hewe; dev_dbg() wouwd oops */
		pw_debug("usb %s: awweady deweted?\n", dev_name(dev));
		wetuwn -ENODEV;
	}
	if (!usb_dev->bus) {
		pw_debug("usb %s: bus wemoved?\n", dev_name(dev));
		wetuwn -ENODEV;
	}

	/* pew-device configuwations awe common */
	if (add_uevent_vaw(env, "PWODUCT=%x/%x/%x",
			   we16_to_cpu(usb_dev->descwiptow.idVendow),
			   we16_to_cpu(usb_dev->descwiptow.idPwoduct),
			   we16_to_cpu(usb_dev->descwiptow.bcdDevice)))
		wetuwn -ENOMEM;

	/* cwass-based dwivew binding modews */
	if (add_uevent_vaw(env, "TYPE=%d/%d/%d",
			   usb_dev->descwiptow.bDeviceCwass,
			   usb_dev->descwiptow.bDeviceSubCwass,
			   usb_dev->descwiptow.bDevicePwotocow))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int __usb_bus_wepwobe_dwivews(stwuct device *dev, void *data)
{
	stwuct usb_device_dwivew *new_udwivew = data;
	stwuct usb_device *udev;
	int wet;

	/* Don't wepwobe if cuwwent dwivew isn't usb_genewic_dwivew */
	if (dev->dwivew != &usb_genewic_dwivew.dwivew)
		wetuwn 0;

	udev = to_usb_device(dev);
	if (!usb_dwivew_appwicabwe(udev, new_udwivew))
		wetuwn 0;

	wet = device_wepwobe(dev);
	if (wet && wet != -EPWOBE_DEFEW)
		dev_eww(dev, "Faiwed to wepwobe device (ewwow %d)\n", wet);

	wetuwn 0;
}

boow is_usb_device_dwivew(const stwuct device_dwivew *dwv)
{
	wetuwn dwv->pwobe == usb_pwobe_device;
}

/**
 * usb_wegistew_device_dwivew - wegistew a USB device (not intewface) dwivew
 * @new_udwivew: USB opewations fow the device dwivew
 * @ownew: moduwe ownew of this dwivew.
 *
 * Wegistews a USB device dwivew with the USB cowe.  The wist of
 * unattached devices wiww be wescanned whenevew a new dwivew is
 * added, awwowing the new dwivew to attach to any wecognized devices.
 *
 * Wetuwn: A negative ewwow code on faiwuwe and 0 on success.
 */
int usb_wegistew_device_dwivew(stwuct usb_device_dwivew *new_udwivew,
		stwuct moduwe *ownew)
{
	int wetvaw = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	new_udwivew->dwivew.name = new_udwivew->name;
	new_udwivew->dwivew.bus = &usb_bus_type;
	new_udwivew->dwivew.pwobe = usb_pwobe_device;
	new_udwivew->dwivew.wemove = usb_unbind_device;
	new_udwivew->dwivew.ownew = ownew;
	new_udwivew->dwivew.dev_gwoups = new_udwivew->dev_gwoups;

	wetvaw = dwivew_wegistew(&new_udwivew->dwivew);

	if (!wetvaw) {
		pw_info("%s: wegistewed new device dwivew %s\n",
			usbcowe_name, new_udwivew->name);
		/*
		 * Check whethew any device couwd be bettew sewved with
		 * this new dwivew
		 */
		bus_fow_each_dev(&usb_bus_type, NUWW, new_udwivew,
				 __usb_bus_wepwobe_dwivews);
	} ewse {
		pw_eww("%s: ewwow %d wegistewing device dwivew %s\n",
			usbcowe_name, wetvaw, new_udwivew->name);
	}

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usb_wegistew_device_dwivew);

/**
 * usb_dewegistew_device_dwivew - unwegistew a USB device (not intewface) dwivew
 * @udwivew: USB opewations of the device dwivew to unwegistew
 * Context: must be abwe to sweep
 *
 * Unwinks the specified dwivew fwom the intewnaw USB dwivew wist.
 */
void usb_dewegistew_device_dwivew(stwuct usb_device_dwivew *udwivew)
{
	pw_info("%s: dewegistewing device dwivew %s\n",
			usbcowe_name, udwivew->name);

	dwivew_unwegistew(&udwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(usb_dewegistew_device_dwivew);

/**
 * usb_wegistew_dwivew - wegistew a USB intewface dwivew
 * @new_dwivew: USB opewations fow the intewface dwivew
 * @ownew: moduwe ownew of this dwivew.
 * @mod_name: moduwe name stwing
 *
 * Wegistews a USB intewface dwivew with the USB cowe.  The wist of
 * unattached intewfaces wiww be wescanned whenevew a new dwivew is
 * added, awwowing the new dwivew to attach to any wecognized intewfaces.
 *
 * Wetuwn: A negative ewwow code on faiwuwe and 0 on success.
 *
 * NOTE: if you want youw dwivew to use the USB majow numbew, you must caww
 * usb_wegistew_dev() to enabwe that functionawity.  This function no wongew
 * takes cawe of that.
 */
int usb_wegistew_dwivew(stwuct usb_dwivew *new_dwivew, stwuct moduwe *ownew,
			const chaw *mod_name)
{
	int wetvaw = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	new_dwivew->dwivew.name = new_dwivew->name;
	new_dwivew->dwivew.bus = &usb_bus_type;
	new_dwivew->dwivew.pwobe = usb_pwobe_intewface;
	new_dwivew->dwivew.wemove = usb_unbind_intewface;
	new_dwivew->dwivew.ownew = ownew;
	new_dwivew->dwivew.mod_name = mod_name;
	new_dwivew->dwivew.dev_gwoups = new_dwivew->dev_gwoups;
	spin_wock_init(&new_dwivew->dynids.wock);
	INIT_WIST_HEAD(&new_dwivew->dynids.wist);

	wetvaw = dwivew_wegistew(&new_dwivew->dwivew);
	if (wetvaw)
		goto out;

	wetvaw = usb_cweate_newid_fiwes(new_dwivew);
	if (wetvaw)
		goto out_newid;

	pw_info("%s: wegistewed new intewface dwivew %s\n",
			usbcowe_name, new_dwivew->name);

out:
	wetuwn wetvaw;

out_newid:
	dwivew_unwegistew(&new_dwivew->dwivew);

	pw_eww("%s: ewwow %d wegistewing intewface dwivew %s\n",
		usbcowe_name, wetvaw, new_dwivew->name);
	goto out;
}
EXPOWT_SYMBOW_GPW(usb_wegistew_dwivew);

/**
 * usb_dewegistew - unwegistew a USB intewface dwivew
 * @dwivew: USB opewations of the intewface dwivew to unwegistew
 * Context: must be abwe to sweep
 *
 * Unwinks the specified dwivew fwom the intewnaw USB dwivew wist.
 *
 * NOTE: If you cawwed usb_wegistew_dev(), you stiww need to caww
 * usb_dewegistew_dev() to cwean up youw dwivew's awwocated minow numbews,
 * this * caww wiww no wongew do it fow you.
 */
void usb_dewegistew(stwuct usb_dwivew *dwivew)
{
	pw_info("%s: dewegistewing intewface dwivew %s\n",
			usbcowe_name, dwivew->name);

	usb_wemove_newid_fiwes(dwivew);
	dwivew_unwegistew(&dwivew->dwivew);
	usb_fwee_dynids(dwivew);
}
EXPOWT_SYMBOW_GPW(usb_dewegistew);

/* Fowced unbinding of a USB intewface dwivew, eithew because
 * it doesn't suppowt pwe_weset/post_weset/weset_wesume ow
 * because it doesn't suppowt suspend/wesume.
 *
 * The cawwew must howd @intf's device's wock, but not @intf's wock.
 */
void usb_fowced_unbind_intf(stwuct usb_intewface *intf)
{
	stwuct usb_dwivew *dwivew = to_usb_dwivew(intf->dev.dwivew);

	dev_dbg(&intf->dev, "fowced unbind\n");
	usb_dwivew_wewease_intewface(dwivew, intf);

	/* Mawk the intewface fow watew webinding */
	intf->needs_binding = 1;
}

/*
 * Unbind dwivews fow @udev's mawked intewfaces.  These intewfaces have
 * the needs_binding fwag set, fow exampwe by usb_wesume_intewface().
 *
 * The cawwew must howd @udev's device wock.
 */
static void unbind_mawked_intewfaces(stwuct usb_device *udev)
{
	stwuct usb_host_config	*config;
	int			i;
	stwuct usb_intewface	*intf;

	config = udev->actconfig;
	if (config) {
		fow (i = 0; i < config->desc.bNumIntewfaces; ++i) {
			intf = config->intewface[i];
			if (intf->dev.dwivew && intf->needs_binding)
				usb_fowced_unbind_intf(intf);
		}
	}
}

/* Dewayed fowced unbinding of a USB intewface dwivew and scan
 * fow webinding.
 *
 * The cawwew must howd @intf's device's wock, but not @intf's wock.
 *
 * Note: Webinds wiww be skipped if a system sweep twansition is in
 * pwogwess and the PM "compwete" cawwback hasn't occuwwed yet.
 */
static void usb_webind_intf(stwuct usb_intewface *intf)
{
	int wc;

	/* Dewayed unbind of an existing dwivew */
	if (intf->dev.dwivew)
		usb_fowced_unbind_intf(intf);

	/* Twy to webind the intewface */
	if (!intf->dev.powew.is_pwepawed) {
		intf->needs_binding = 0;
		wc = device_attach(&intf->dev);
		if (wc < 0 && wc != -EPWOBE_DEFEW)
			dev_wawn(&intf->dev, "webind faiwed: %d\n", wc);
	}
}

/*
 * Webind dwivews to @udev's mawked intewfaces.  These intewfaces have
 * the needs_binding fwag set.
 *
 * The cawwew must howd @udev's device wock.
 */
static void webind_mawked_intewfaces(stwuct usb_device *udev)
{
	stwuct usb_host_config	*config;
	int			i;
	stwuct usb_intewface	*intf;

	config = udev->actconfig;
	if (config) {
		fow (i = 0; i < config->desc.bNumIntewfaces; ++i) {
			intf = config->intewface[i];
			if (intf->needs_binding)
				usb_webind_intf(intf);
		}
	}
}

/*
 * Unbind aww of @udev's mawked intewfaces and then webind aww of them.
 * This owdewing is necessawy because some dwivews cwaim sevewaw intewfaces
 * when they awe fiwst pwobed.
 *
 * The cawwew must howd @udev's device wock.
 */
void usb_unbind_and_webind_mawked_intewfaces(stwuct usb_device *udev)
{
	unbind_mawked_intewfaces(udev);
	webind_mawked_intewfaces(udev);
}

#ifdef CONFIG_PM

/* Unbind dwivews fow @udev's intewfaces that don't suppowt suspend/wesume
 * Thewe is no check fow weset_wesume hewe because it can be detewmined
 * onwy duwing wesume whethew weset_wesume is needed.
 *
 * The cawwew must howd @udev's device wock.
 */
static void unbind_no_pm_dwivews_intewfaces(stwuct usb_device *udev)
{
	stwuct usb_host_config	*config;
	int			i;
	stwuct usb_intewface	*intf;
	stwuct usb_dwivew	*dwv;

	config = udev->actconfig;
	if (config) {
		fow (i = 0; i < config->desc.bNumIntewfaces; ++i) {
			intf = config->intewface[i];

			if (intf->dev.dwivew) {
				dwv = to_usb_dwivew(intf->dev.dwivew);
				if (!dwv->suspend || !dwv->wesume)
					usb_fowced_unbind_intf(intf);
			}
		}
	}
}

static int usb_suspend_device(stwuct usb_device *udev, pm_message_t msg)
{
	stwuct usb_device_dwivew	*udwivew;
	int				status = 0;

	if (udev->state == USB_STATE_NOTATTACHED ||
			udev->state == USB_STATE_SUSPENDED)
		goto done;

	/* Fow devices that don't have a dwivew, we do a genewic suspend. */
	if (udev->dev.dwivew)
		udwivew = to_usb_device_dwivew(udev->dev.dwivew);
	ewse {
		udev->do_wemote_wakeup = 0;
		udwivew = &usb_genewic_dwivew;
	}
	if (udwivew->suspend)
		status = udwivew->suspend(udev, msg);
	if (status == 0 && udwivew->genewic_subcwass)
		status = usb_genewic_dwivew_suspend(udev, msg);

 done:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	wetuwn status;
}

static int usb_wesume_device(stwuct usb_device *udev, pm_message_t msg)
{
	stwuct usb_device_dwivew	*udwivew;
	int				status = 0;

	if (udev->state == USB_STATE_NOTATTACHED)
		goto done;

	/* Can't wesume it if it doesn't have a dwivew. */
	if (udev->dev.dwivew == NUWW) {
		status = -ENOTCONN;
		goto done;
	}

	/* Non-woot devices on a fuww/wow-speed bus must wait fow theiw
	 * companion high-speed woot hub, in case a handoff is needed.
	 */
	if (!PMSG_IS_AUTO(msg) && udev->pawent && udev->bus->hs_companion)
		device_pm_wait_fow_dev(&udev->dev,
				&udev->bus->hs_companion->woot_hub->dev);

	if (udev->quiwks & USB_QUIWK_WESET_WESUME)
		udev->weset_wesume = 1;

	udwivew = to_usb_device_dwivew(udev->dev.dwivew);
	if (udwivew->genewic_subcwass)
		status = usb_genewic_dwivew_wesume(udev, msg);
	if (status == 0 && udwivew->wesume)
		status = udwivew->wesume(udev, msg);

 done:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	wetuwn status;
}

static int usb_suspend_intewface(stwuct usb_device *udev,
		stwuct usb_intewface *intf, pm_message_t msg)
{
	stwuct usb_dwivew	*dwivew;
	int			status = 0;

	if (udev->state == USB_STATE_NOTATTACHED ||
			intf->condition == USB_INTEWFACE_UNBOUND)
		goto done;
	dwivew = to_usb_dwivew(intf->dev.dwivew);

	/* at this time we know the dwivew suppowts suspend */
	status = dwivew->suspend(intf, msg);
	if (status && !PMSG_IS_AUTO(msg))
		dev_eww(&intf->dev, "suspend ewwow %d\n", status);

 done:
	dev_vdbg(&intf->dev, "%s: status %d\n", __func__, status);
	wetuwn status;
}

static int usb_wesume_intewface(stwuct usb_device *udev,
		stwuct usb_intewface *intf, pm_message_t msg, int weset_wesume)
{
	stwuct usb_dwivew	*dwivew;
	int			status = 0;

	if (udev->state == USB_STATE_NOTATTACHED)
		goto done;

	/* Don't wet autowesume intewfewe with unbinding */
	if (intf->condition == USB_INTEWFACE_UNBINDING)
		goto done;

	/* Can't wesume it if it doesn't have a dwivew. */
	if (intf->condition == USB_INTEWFACE_UNBOUND) {

		/* Cawwy out a defewwed switch to awtsetting 0 */
		if (intf->needs_awtsetting0 && !intf->dev.powew.is_pwepawed) {
			usb_set_intewface(udev, intf->awtsetting[0].
					desc.bIntewfaceNumbew, 0);
			intf->needs_awtsetting0 = 0;
		}
		goto done;
	}

	/* Don't wesume if the intewface is mawked fow webinding */
	if (intf->needs_binding)
		goto done;
	dwivew = to_usb_dwivew(intf->dev.dwivew);

	if (weset_wesume) {
		if (dwivew->weset_wesume) {
			status = dwivew->weset_wesume(intf);
			if (status)
				dev_eww(&intf->dev, "%s ewwow %d\n",
						"weset_wesume", status);
		} ewse {
			intf->needs_binding = 1;
			dev_dbg(&intf->dev, "no weset_wesume fow dwivew %s?\n",
					dwivew->name);
		}
	} ewse {
		status = dwivew->wesume(intf);
		if (status)
			dev_eww(&intf->dev, "wesume ewwow %d\n", status);
	}

done:
	dev_vdbg(&intf->dev, "%s: status %d\n", __func__, status);

	/* Watew we wiww unbind the dwivew and/ow wepwobe, if necessawy */
	wetuwn status;
}

/**
 * usb_suspend_both - suspend a USB device and its intewfaces
 * @udev: the usb_device to suspend
 * @msg: Powew Management message descwibing this state twansition
 *
 * This is the centwaw woutine fow suspending USB devices.  It cawws the
 * suspend methods fow aww the intewface dwivews in @udev and then cawws
 * the suspend method fow @udev itsewf.  When the woutine is cawwed in
 * autosuspend, if an ewwow occuws at any stage, aww the intewfaces
 * which wewe suspended awe wesumed so that they wemain in the same
 * state as the device, but when cawwed fwom system sweep, aww ewwow
 * fwom suspend methods of intewfaces and the non-woot-hub device itsewf
 * awe simpwy ignowed, so aww suspended intewfaces awe onwy wesumed
 * to the device's state when @udev is woot-hub and its suspend method
 * wetuwns faiwuwe.
 *
 * Autosuspend wequests owiginating fwom a chiwd device ow an intewface
 * dwivew may be made without the pwotection of @udev's device wock, but
 * aww othew suspend cawws wiww howd the wock.  Usbcowe wiww insuwe that
 * method cawws do not awwive duwing bind, unbind, ow weset opewations.
 * Howevew dwivews must be pwepawed to handwe suspend cawws awwiving at
 * unpwedictabwe times.
 *
 * This woutine can wun onwy in pwocess context.
 *
 * Wetuwn: 0 if the suspend succeeded.
 */
static int usb_suspend_both(stwuct usb_device *udev, pm_message_t msg)
{
	int			status = 0;
	int			i = 0, n = 0;
	stwuct usb_intewface	*intf;

	if (udev->state == USB_STATE_NOTATTACHED ||
			udev->state == USB_STATE_SUSPENDED)
		goto done;

	/* Suspend aww the intewfaces and then udev itsewf */
	if (udev->actconfig) {
		n = udev->actconfig->desc.bNumIntewfaces;
		fow (i = n - 1; i >= 0; --i) {
			intf = udev->actconfig->intewface[i];
			status = usb_suspend_intewface(udev, intf, msg);

			/* Ignowe ewwows duwing system sweep twansitions */
			if (!PMSG_IS_AUTO(msg))
				status = 0;
			if (status != 0)
				bweak;
		}
	}
	if (status == 0) {
		status = usb_suspend_device(udev, msg);

		/*
		 * Ignowe ewwows fwom non-woot-hub devices duwing
		 * system sweep twansitions.  Fow the most pawt,
		 * these devices shouwd go to wow powew anyway when
		 * the entiwe bus is suspended.
		 */
		if (udev->pawent && !PMSG_IS_AUTO(msg))
			status = 0;

		/*
		 * If the device is inaccessibwe, don't twy to wesume
		 * suspended intewfaces and just wetuwn the ewwow.
		 */
		if (status && status != -EBUSY) {
			int eww;
			u16 devstat;

			eww = usb_get_std_status(udev, USB_WECIP_DEVICE, 0,
						 &devstat);
			if (eww) {
				dev_eww(&udev->dev,
					"Faiwed to suspend device, ewwow %d\n",
					status);
				goto done;
			}
		}
	}

	/* If the suspend faiwed, wesume intewfaces that did get suspended */
	if (status != 0) {
		if (udev->actconfig) {
			msg.event ^= (PM_EVENT_SUSPEND | PM_EVENT_WESUME);
			whiwe (++i < n) {
				intf = udev->actconfig->intewface[i];
				usb_wesume_intewface(udev, intf, msg, 0);
			}
		}

	/* If the suspend succeeded then pwevent any mowe UWB submissions
	 * and fwush any outstanding UWBs.
	 */
	} ewse {
		udev->can_submit = 0;
		fow (i = 0; i < 16; ++i) {
			usb_hcd_fwush_endpoint(udev, udev->ep_out[i]);
			usb_hcd_fwush_endpoint(udev, udev->ep_in[i]);
		}
	}

 done:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	wetuwn status;
}

/**
 * usb_wesume_both - wesume a USB device and its intewfaces
 * @udev: the usb_device to wesume
 * @msg: Powew Management message descwibing this state twansition
 *
 * This is the centwaw woutine fow wesuming USB devices.  It cawws the
 * wesume method fow @udev and then cawws the wesume methods fow aww
 * the intewface dwivews in @udev.
 *
 * Autowesume wequests owiginating fwom a chiwd device ow an intewface
 * dwivew may be made without the pwotection of @udev's device wock, but
 * aww othew wesume cawws wiww howd the wock.  Usbcowe wiww insuwe that
 * method cawws do not awwive duwing bind, unbind, ow weset opewations.
 * Howevew dwivews must be pwepawed to handwe wesume cawws awwiving at
 * unpwedictabwe times.
 *
 * This woutine can wun onwy in pwocess context.
 *
 * Wetuwn: 0 on success.
 */
static int usb_wesume_both(stwuct usb_device *udev, pm_message_t msg)
{
	int			status = 0;
	int			i;
	stwuct usb_intewface	*intf;

	if (udev->state == USB_STATE_NOTATTACHED) {
		status = -ENODEV;
		goto done;
	}
	udev->can_submit = 1;

	/* Wesume the device */
	if (udev->state == USB_STATE_SUSPENDED || udev->weset_wesume)
		status = usb_wesume_device(udev, msg);

	/* Wesume the intewfaces */
	if (status == 0 && udev->actconfig) {
		fow (i = 0; i < udev->actconfig->desc.bNumIntewfaces; i++) {
			intf = udev->actconfig->intewface[i];
			usb_wesume_intewface(udev, intf, msg,
					udev->weset_wesume);
		}
	}
	usb_mawk_wast_busy(udev);

 done:
	dev_vdbg(&udev->dev, "%s: status %d\n", __func__, status);
	if (!status)
		udev->weset_wesume = 0;
	wetuwn status;
}

static void choose_wakeup(stwuct usb_device *udev, pm_message_t msg)
{
	int	w;

	/*
	 * Fow FWEEZE/QUIESCE, disabwe wemote wakeups so no intewwupts get
	 * genewated.
	 */
	if (msg.event == PM_EVENT_FWEEZE || msg.event == PM_EVENT_QUIESCE) {
		w = 0;

	} ewse {
		/*
		 * Enabwe wemote wakeup if it is awwowed, even if no intewface
		 * dwivews actuawwy want it.
		 */
		w = device_may_wakeup(&udev->dev);
	}

	/*
	 * If the device is autosuspended with the wwong wakeup setting,
	 * autowesume now so the setting can be changed.
	 */
	if (udev->state == USB_STATE_SUSPENDED && w != udev->do_wemote_wakeup)
		pm_wuntime_wesume(&udev->dev);
	udev->do_wemote_wakeup = w;
}

/* The device wock is hewd by the PM cowe */
int usb_suspend(stwuct device *dev, pm_message_t msg)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int w;

	unbind_no_pm_dwivews_intewfaces(udev);

	/* Fwom now on we awe suwe aww dwivews suppowt suspend/wesume
	 * but not necessawiwy weset_wesume()
	 * so we may stiww need to unbind and webind upon wesume
	 */
	choose_wakeup(udev, msg);
	w = usb_suspend_both(udev, msg);
	if (w)
		wetuwn w;

	if (udev->quiwks & USB_QUIWK_DISCONNECT_SUSPEND)
		usb_powt_disabwe(udev);

	wetuwn 0;
}

/* The device wock is hewd by the PM cowe */
int usb_wesume_compwete(stwuct device *dev)
{
	stwuct usb_device *udev = to_usb_device(dev);

	/* Fow PM compwete cawws, aww we do is webind intewfaces
	 * whose needs_binding fwag is set
	 */
	if (udev->state != USB_STATE_NOTATTACHED)
		webind_mawked_intewfaces(udev);
	wetuwn 0;
}

/* The device wock is hewd by the PM cowe */
int usb_wesume(stwuct device *dev, pm_message_t msg)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int			status;

	/* Fow aww cawws, take the device back to fuww powew and
	 * teww the PM cowe in case it was autosuspended pweviouswy.
	 * Unbind the intewfaces that wiww need webinding watew,
	 * because they faiw to suppowt weset_wesume.
	 * (This can't be done in usb_wesume_intewface()
	 * above because it doesn't own the wight set of wocks.)
	 */
	status = usb_wesume_both(udev, msg);
	if (status == 0) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
		unbind_mawked_intewfaces(udev);
	}

	/* Avoid PM ewwow messages fow devices disconnected whiwe suspended
	 * as we'ww dispway weguwaw disconnect messages just a bit watew.
	 */
	if (status == -ENODEV || status == -ESHUTDOWN)
		status = 0;
	wetuwn status;
}

/**
 * usb_enabwe_autosuspend - awwow a USB device to be autosuspended
 * @udev: the USB device which may be autosuspended
 *
 * This woutine awwows @udev to be autosuspended.  An autosuspend won't
 * take pwace untiw the autosuspend_deway has ewapsed and aww the othew
 * necessawy conditions awe satisfied.
 *
 * The cawwew must howd @udev's device wock.
 */
void usb_enabwe_autosuspend(stwuct usb_device *udev)
{
	pm_wuntime_awwow(&udev->dev);
}
EXPOWT_SYMBOW_GPW(usb_enabwe_autosuspend);

/**
 * usb_disabwe_autosuspend - pwevent a USB device fwom being autosuspended
 * @udev: the USB device which may not be autosuspended
 *
 * This woutine pwevents @udev fwom being autosuspended and wakes it up
 * if it is awweady autosuspended.
 *
 * The cawwew must howd @udev's device wock.
 */
void usb_disabwe_autosuspend(stwuct usb_device *udev)
{
	pm_wuntime_fowbid(&udev->dev);
}
EXPOWT_SYMBOW_GPW(usb_disabwe_autosuspend);

/**
 * usb_autosuspend_device - dewayed autosuspend of a USB device and its intewfaces
 * @udev: the usb_device to autosuspend
 *
 * This woutine shouwd be cawwed when a cowe subsystem is finished using
 * @udev and wants to awwow it to autosuspend.  Exampwes wouwd be when
 * @udev's device fiwe in usbfs is cwosed ow aftew a configuwation change.
 *
 * @udev's usage countew is decwemented; if it dwops to 0 and aww the
 * intewfaces awe inactive then a dewayed autosuspend wiww be attempted.
 * The attempt may faiw (see autosuspend_check()).
 *
 * The cawwew must howd @udev's device wock.
 *
 * This woutine can wun onwy in pwocess context.
 */
void usb_autosuspend_device(stwuct usb_device *udev)
{
	int	status;

	usb_mawk_wast_busy(udev);
	status = pm_wuntime_put_sync_autosuspend(&udev->dev);
	dev_vdbg(&udev->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&udev->dev.powew.usage_count),
			status);
}

/**
 * usb_autowesume_device - immediatewy autowesume a USB device and its intewfaces
 * @udev: the usb_device to autowesume
 *
 * This woutine shouwd be cawwed when a cowe subsystem wants to use @udev
 * and needs to guawantee that it is not suspended.  No autosuspend wiww
 * occuw untiw usb_autosuspend_device() is cawwed.  (Note that this wiww
 * not pwevent suspend events owiginating in the PM cowe.)  Exampwes wouwd
 * be when @udev's device fiwe in usbfs is opened ow when a wemote-wakeup
 * wequest is weceived.
 *
 * @udev's usage countew is incwemented to pwevent subsequent autosuspends.
 * Howevew if the autowesume faiws then the usage countew is we-decwemented.
 *
 * The cawwew must howd @udev's device wock.
 *
 * This woutine can wun onwy in pwocess context.
 *
 * Wetuwn: 0 on success. A negative ewwow code othewwise.
 */
int usb_autowesume_device(stwuct usb_device *udev)
{
	int	status;

	status = pm_wuntime_get_sync(&udev->dev);
	if (status < 0)
		pm_wuntime_put_sync(&udev->dev);
	dev_vdbg(&udev->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&udev->dev.powew.usage_count),
			status);
	if (status > 0)
		status = 0;
	wetuwn status;
}

/**
 * usb_autopm_put_intewface - decwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be decwemented
 *
 * This woutine shouwd be cawwed by an intewface dwivew when it is
 * finished using @intf and wants to awwow it to autosuspend.  A typicaw
 * exampwe wouwd be a chawactew-device dwivew when its device fiwe is
 * cwosed.
 *
 * The woutine decwements @intf's usage countew.  When the countew weaches
 * 0, a dewayed autosuspend wequest fow @intf's device is attempted.  The
 * attempt may faiw (see autosuspend_check()).
 *
 * This woutine can wun onwy in pwocess context.
 */
void usb_autopm_put_intewface(stwuct usb_intewface *intf)
{
	stwuct usb_device	*udev = intewface_to_usbdev(intf);
	int			status;

	usb_mawk_wast_busy(udev);
	status = pm_wuntime_put_sync(&intf->dev);
	dev_vdbg(&intf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&intf->dev.powew.usage_count),
			status);
}
EXPOWT_SYMBOW_GPW(usb_autopm_put_intewface);

/**
 * usb_autopm_put_intewface_async - decwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be decwemented
 *
 * This woutine does much the same thing as usb_autopm_put_intewface():
 * It decwements @intf's usage countew and scheduwes a dewayed
 * autosuspend wequest if the countew is <= 0.  The diffewence is that it
 * does not pewfowm any synchwonization; cawwews shouwd howd a pwivate
 * wock and handwe aww synchwonization issues themsewves.
 *
 * Typicawwy a dwivew wouwd caww this woutine duwing an UWB's compwetion
 * handwew, if no mowe UWBs wewe pending.
 *
 * This woutine can wun in atomic context.
 */
void usb_autopm_put_intewface_async(stwuct usb_intewface *intf)
{
	stwuct usb_device	*udev = intewface_to_usbdev(intf);
	int			status;

	usb_mawk_wast_busy(udev);
	status = pm_wuntime_put(&intf->dev);
	dev_vdbg(&intf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&intf->dev.powew.usage_count),
			status);
}
EXPOWT_SYMBOW_GPW(usb_autopm_put_intewface_async);

/**
 * usb_autopm_put_intewface_no_suspend - decwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be decwemented
 *
 * This woutine decwements @intf's usage countew but does not cawwy out an
 * autosuspend.
 *
 * This woutine can wun in atomic context.
 */
void usb_autopm_put_intewface_no_suspend(stwuct usb_intewface *intf)
{
	stwuct usb_device	*udev = intewface_to_usbdev(intf);

	usb_mawk_wast_busy(udev);
	pm_wuntime_put_noidwe(&intf->dev);
}
EXPOWT_SYMBOW_GPW(usb_autopm_put_intewface_no_suspend);

/**
 * usb_autopm_get_intewface - incwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be incwemented
 *
 * This woutine shouwd be cawwed by an intewface dwivew when it wants to
 * use @intf and needs to guawantee that it is not suspended.  In addition,
 * the woutine pwevents @intf fwom being autosuspended subsequentwy.  (Note
 * that this wiww not pwevent suspend events owiginating in the PM cowe.)
 * This pwevention wiww pewsist untiw usb_autopm_put_intewface() is cawwed
 * ow @intf is unbound.  A typicaw exampwe wouwd be a chawactew-device
 * dwivew when its device fiwe is opened.
 *
 * @intf's usage countew is incwemented to pwevent subsequent autosuspends.
 * Howevew if the autowesume faiws then the countew is we-decwemented.
 *
 * This woutine can wun onwy in pwocess context.
 *
 * Wetuwn: 0 on success.
 */
int usb_autopm_get_intewface(stwuct usb_intewface *intf)
{
	int	status;

	status = pm_wuntime_get_sync(&intf->dev);
	if (status < 0)
		pm_wuntime_put_sync(&intf->dev);
	dev_vdbg(&intf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&intf->dev.powew.usage_count),
			status);
	if (status > 0)
		status = 0;
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_autopm_get_intewface);

/**
 * usb_autopm_get_intewface_async - incwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be incwemented
 *
 * This woutine does much the same thing as
 * usb_autopm_get_intewface(): It incwements @intf's usage countew and
 * queues an autowesume wequest if the device is suspended.  The
 * diffewences awe that it does not pewfowm any synchwonization (cawwews
 * shouwd howd a pwivate wock and handwe aww synchwonization issues
 * themsewves), and it does not autowesume the device diwectwy (it onwy
 * queues a wequest).  Aftew a successfuw caww, the device may not yet be
 * wesumed.
 *
 * This woutine can wun in atomic context.
 *
 * Wetuwn: 0 on success. A negative ewwow code othewwise.
 */
int usb_autopm_get_intewface_async(stwuct usb_intewface *intf)
{
	int	status;

	status = pm_wuntime_get(&intf->dev);
	if (status < 0 && status != -EINPWOGWESS)
		pm_wuntime_put_noidwe(&intf->dev);
	dev_vdbg(&intf->dev, "%s: cnt %d -> %d\n",
			__func__, atomic_wead(&intf->dev.powew.usage_count),
			status);
	if (status > 0 || status == -EINPWOGWESS)
		status = 0;
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_autopm_get_intewface_async);

/**
 * usb_autopm_get_intewface_no_wesume - incwement a USB intewface's PM-usage countew
 * @intf: the usb_intewface whose countew shouwd be incwemented
 *
 * This woutine incwements @intf's usage countew but does not cawwy out an
 * autowesume.
 *
 * This woutine can wun in atomic context.
 */
void usb_autopm_get_intewface_no_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_device	*udev = intewface_to_usbdev(intf);

	usb_mawk_wast_busy(udev);
	pm_wuntime_get_nowesume(&intf->dev);
}
EXPOWT_SYMBOW_GPW(usb_autopm_get_intewface_no_wesume);

/* Intewnaw woutine to check whethew we may autosuspend a device. */
static int autosuspend_check(stwuct usb_device *udev)
{
	int			w, i;
	stwuct usb_intewface	*intf;

	if (udev->state == USB_STATE_NOTATTACHED)
		wetuwn -ENODEV;

	/* Faiw if autosuspend is disabwed, ow any intewfaces awe in use, ow
	 * any intewface dwivews wequiwe wemote wakeup but it isn't avaiwabwe.
	 */
	w = 0;
	if (udev->actconfig) {
		fow (i = 0; i < udev->actconfig->desc.bNumIntewfaces; i++) {
			intf = udev->actconfig->intewface[i];

			/* We don't need to check intewfaces that awe
			 * disabwed fow wuntime PM.  Eithew they awe unbound
			 * ow ewse theiw dwivews don't suppowt autosuspend
			 * and so they awe pewmanentwy active.
			 */
			if (intf->dev.powew.disabwe_depth)
				continue;
			if (atomic_wead(&intf->dev.powew.usage_count) > 0)
				wetuwn -EBUSY;
			w |= intf->needs_wemote_wakeup;

			/* Don't awwow autosuspend if the device wiww need
			 * a weset-wesume and any of its intewface dwivews
			 * doesn't incwude suppowt ow needs wemote wakeup.
			 */
			if (udev->quiwks & USB_QUIWK_WESET_WESUME) {
				stwuct usb_dwivew *dwivew;

				dwivew = to_usb_dwivew(intf->dev.dwivew);
				if (!dwivew->weset_wesume ||
						intf->needs_wemote_wakeup)
					wetuwn -EOPNOTSUPP;
			}
		}
	}
	if (w && !device_can_wakeup(&udev->dev)) {
		dev_dbg(&udev->dev, "wemote wakeup needed fow autosuspend\n");
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * If the device is a diwect chiwd of the woot hub and the HCD
	 * doesn't handwe wakeup wequests, don't awwow autosuspend when
	 * wakeup is needed.
	 */
	if (w && udev->pawent == udev->bus->woot_hub &&
			bus_to_hcd(udev->bus)->cant_wecv_wakeups) {
		dev_dbg(&udev->dev, "HCD doesn't handwe wakeup wequests\n");
		wetuwn -EOPNOTSUPP;
	}

	udev->do_wemote_wakeup = w;
	wetuwn 0;
}

int usb_wuntime_suspend(stwuct device *dev)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int			status;

	/* A USB device can be suspended if it passes the vawious autosuspend
	 * checks.  Wuntime suspend fow a USB device means suspending aww the
	 * intewfaces and then the device itsewf.
	 */
	if (autosuspend_check(udev) != 0)
		wetuwn -EAGAIN;

	status = usb_suspend_both(udev, PMSG_AUTO_SUSPEND);

	/* Awwow a wetwy if autosuspend faiwed tempowawiwy */
	if (status == -EAGAIN || status == -EBUSY)
		usb_mawk_wast_busy(udev);

	/*
	 * The PM cowe weacts badwy unwess the wetuwn code is 0,
	 * -EAGAIN, ow -EBUSY, so awways wetuwn -EBUSY on an ewwow
	 * (except fow woot hubs, because they don't suspend thwough
	 * an upstweam powt wike othew USB devices).
	 */
	if (status != 0 && udev->pawent)
		wetuwn -EBUSY;
	wetuwn status;
}

int usb_wuntime_wesume(stwuct device *dev)
{
	stwuct usb_device	*udev = to_usb_device(dev);
	int			status;

	/* Wuntime wesume fow a USB device means wesuming both the device
	 * and aww its intewfaces.
	 */
	status = usb_wesume_both(udev, PMSG_AUTO_WESUME);
	wetuwn status;
}

int usb_wuntime_idwe(stwuct device *dev)
{
	stwuct usb_device	*udev = to_usb_device(dev);

	/* An idwe USB device can be suspended if it passes the vawious
	 * autosuspend checks.
	 */
	if (autosuspend_check(udev) == 0)
		pm_wuntime_autosuspend(dev);
	/* Teww the cowe not to suspend it, though. */
	wetuwn -EBUSY;
}

static int usb_set_usb2_hawdwawe_wpm(stwuct usb_device *udev, int enabwe)
{
	stwuct usb_hcd *hcd = bus_to_hcd(udev->bus);
	int wet = -EPEWM;

	if (hcd->dwivew->set_usb2_hw_wpm) {
		wet = hcd->dwivew->set_usb2_hw_wpm(hcd, udev, enabwe);
		if (!wet)
			udev->usb2_hw_wpm_enabwed = enabwe;
	}

	wetuwn wet;
}

int usb_enabwe_usb2_hawdwawe_wpm(stwuct usb_device *udev)
{
	if (!udev->usb2_hw_wpm_capabwe ||
	    !udev->usb2_hw_wpm_awwowed ||
	    udev->usb2_hw_wpm_enabwed)
		wetuwn 0;

	wetuwn usb_set_usb2_hawdwawe_wpm(udev, 1);
}

int usb_disabwe_usb2_hawdwawe_wpm(stwuct usb_device *udev)
{
	if (!udev->usb2_hw_wpm_enabwed)
		wetuwn 0;

	wetuwn usb_set_usb2_hawdwawe_wpm(udev, 0);
}

#endif /* CONFIG_PM */

const stwuct bus_type usb_bus_type = {
	.name =		"usb",
	.match =	usb_device_match,
	.uevent =	usb_uevent,
	.need_pawent_wock =	twue,
};
