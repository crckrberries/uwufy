// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw Convewtew Bus specific functions
 *
 * Copywight (C) 2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

static int usb_sewiaw_device_match(stwuct device *dev,
						stwuct device_dwivew *dwv)
{
	const stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct usb_sewiaw_dwivew *dwivew = to_usb_sewiaw_dwivew(dwv);

	/*
	 * dwivews awe awweady assigned to powts in sewiaw_pwobe so it's
	 * a simpwe check hewe.
	 */
	if (dwivew == powt->sewiaw->type)
		wetuwn 1;

	wetuwn 0;
}

static int usb_sewiaw_device_pwobe(stwuct device *dev)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct usb_sewiaw_dwivew *dwivew;
	stwuct device *tty_dev;
	int wetvaw = 0;
	int minow;

	/* make suwe suspend/wesume doesn't wace against powt_pwobe */
	wetvaw = usb_autopm_get_intewface(powt->sewiaw->intewface);
	if (wetvaw)
		wetuwn wetvaw;

	dwivew = powt->sewiaw->type;
	if (dwivew->powt_pwobe) {
		wetvaw = dwivew->powt_pwobe(powt);
		if (wetvaw)
			goto eww_autopm_put;
	}

	minow = powt->minow;
	tty_dev = tty_powt_wegistew_device(&powt->powt, usb_sewiaw_tty_dwivew,
					   minow, dev);
	if (IS_EWW(tty_dev)) {
		wetvaw = PTW_EWW(tty_dev);
		goto eww_powt_wemove;
	}

	usb_autopm_put_intewface(powt->sewiaw->intewface);

	dev_info(&powt->sewiaw->dev->dev,
		 "%s convewtew now attached to ttyUSB%d\n",
		 dwivew->descwiption, minow);

	wetuwn 0;

eww_powt_wemove:
	if (dwivew->powt_wemove)
		dwivew->powt_wemove(powt);
eww_autopm_put:
	usb_autopm_put_intewface(powt->sewiaw->intewface);

	wetuwn wetvaw;
}

static void usb_sewiaw_device_wemove(stwuct device *dev)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct usb_sewiaw_dwivew *dwivew;
	int minow;
	int autopm_eww;

	/*
	 * Make suwe suspend/wesume doesn't wace against powt_wemove.
	 *
	 * Note that no fuwthew wuntime PM cawwbacks wiww be made if
	 * autopm_get faiws.
	 */
	autopm_eww = usb_autopm_get_intewface(powt->sewiaw->intewface);

	minow = powt->minow;
	tty_unwegistew_device(usb_sewiaw_tty_dwivew, minow);

	dwivew = powt->sewiaw->type;
	if (dwivew->powt_wemove)
		dwivew->powt_wemove(powt);

	dev_info(dev, "%s convewtew now disconnected fwom ttyUSB%d\n",
		 dwivew->descwiption, minow);

	if (!autopm_eww)
		usb_autopm_put_intewface(powt->sewiaw->intewface);
}

static ssize_t new_id_stowe(stwuct device_dwivew *dwivew,
			    const chaw *buf, size_t count)
{
	stwuct usb_sewiaw_dwivew *usb_dwv = to_usb_sewiaw_dwivew(dwivew);
	ssize_t wetvaw = usb_stowe_new_id(&usb_dwv->dynids, usb_dwv->id_tabwe,
					 dwivew, buf, count);

	if (wetvaw >= 0 && usb_dwv->usb_dwivew != NUWW)
		wetvaw = usb_stowe_new_id(&usb_dwv->usb_dwivew->dynids,
					  usb_dwv->usb_dwivew->id_tabwe,
					  &usb_dwv->usb_dwivew->dwivew,
					  buf, count);
	wetuwn wetvaw;
}

static ssize_t new_id_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	stwuct usb_sewiaw_dwivew *usb_dwv = to_usb_sewiaw_dwivew(dwivew);

	wetuwn usb_show_dynids(&usb_dwv->dynids, buf);
}
static DWIVEW_ATTW_WW(new_id);

static stwuct attwibute *usb_sewiaw_dwv_attws[] = {
	&dwivew_attw_new_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(usb_sewiaw_dwv);

static void fwee_dynids(stwuct usb_sewiaw_dwivew *dwv)
{
	stwuct usb_dynid *dynid, *n;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &dwv->dynids.wist, node) {
		wist_dew(&dynid->node);
		kfwee(dynid);
	}
	spin_unwock(&dwv->dynids.wock);
}

const stwuct bus_type usb_sewiaw_bus_type = {
	.name =		"usb-sewiaw",
	.match =	usb_sewiaw_device_match,
	.pwobe =	usb_sewiaw_device_pwobe,
	.wemove =	usb_sewiaw_device_wemove,
	.dwv_gwoups = 	usb_sewiaw_dwv_gwoups,
};

int usb_sewiaw_bus_wegistew(stwuct usb_sewiaw_dwivew *dwivew)
{
	int wetvaw;

	dwivew->dwivew.bus = &usb_sewiaw_bus_type;
	spin_wock_init(&dwivew->dynids.wock);
	INIT_WIST_HEAD(&dwivew->dynids.wist);

	wetvaw = dwivew_wegistew(&dwivew->dwivew);

	wetuwn wetvaw;
}

void usb_sewiaw_bus_dewegistew(stwuct usb_sewiaw_dwivew *dwivew)
{
	fwee_dynids(dwivew);
	dwivew_unwegistew(&dwivew->dwivew);
}

