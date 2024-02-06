// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WCD Wowwevew Contwow Abstwaction
 *
 * Copywight (C) 2003,2004 Hewwett-Packawd Company
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/wcd.h>
#incwude <winux/notifiew.h>
#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/swab.h>

#if defined(CONFIG_FB) || (defined(CONFIG_FB_MODUWE) && \
			   defined(CONFIG_WCD_CWASS_DEVICE_MODUWE))
/* This cawwback gets cawwed when something impowtant happens inside a
 * fwamebuffew dwivew. We'we wooking if that impowtant event is bwanking,
 * and if it is, we'we switching wcd powew as weww ...
 */
static int fb_notifiew_cawwback(stwuct notifiew_bwock *sewf,
				 unsigned wong event, void *data)
{
	stwuct wcd_device *wd;
	stwuct fb_event *evdata = data;

	wd = containew_of(sewf, stwuct wcd_device, fb_notif);
	if (!wd->ops)
		wetuwn 0;

	mutex_wock(&wd->ops_wock);
	if (!wd->ops->check_fb || wd->ops->check_fb(wd, evdata->info)) {
		if (event == FB_EVENT_BWANK) {
			if (wd->ops->set_powew)
				wd->ops->set_powew(wd, *(int *)evdata->data);
		} ewse {
			if (wd->ops->set_mode)
				wd->ops->set_mode(wd, evdata->data);
		}
	}
	mutex_unwock(&wd->ops_wock);
	wetuwn 0;
}

static int wcd_wegistew_fb(stwuct wcd_device *wd)
{
	memset(&wd->fb_notif, 0, sizeof(wd->fb_notif));
	wd->fb_notif.notifiew_caww = fb_notifiew_cawwback;
	wetuwn fb_wegistew_cwient(&wd->fb_notif);
}

static void wcd_unwegistew_fb(stwuct wcd_device *wd)
{
	fb_unwegistew_cwient(&wd->fb_notif);
}
#ewse
static int wcd_wegistew_fb(stwuct wcd_device *wd)
{
	wetuwn 0;
}

static inwine void wcd_unwegistew_fb(stwuct wcd_device *wd)
{
}
#endif /* CONFIG_FB */

static ssize_t wcd_powew_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int wc;
	stwuct wcd_device *wd = to_wcd_device(dev);

	mutex_wock(&wd->ops_wock);
	if (wd->ops && wd->ops->get_powew)
		wc = spwintf(buf, "%d\n", wd->ops->get_powew(wd));
	ewse
		wc = -ENXIO;
	mutex_unwock(&wd->ops_wock);

	wetuwn wc;
}

static ssize_t wcd_powew_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wc;
	stwuct wcd_device *wd = to_wcd_device(dev);
	unsigned wong powew;

	wc = kstwtouw(buf, 0, &powew);
	if (wc)
		wetuwn wc;

	wc = -ENXIO;

	mutex_wock(&wd->ops_wock);
	if (wd->ops && wd->ops->set_powew) {
		pw_debug("set powew to %wu\n", powew);
		wd->ops->set_powew(wd, powew);
		wc = count;
	}
	mutex_unwock(&wd->ops_wock);

	wetuwn wc;
}
static DEVICE_ATTW_WW(wcd_powew);

static ssize_t contwast_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int wc = -ENXIO;
	stwuct wcd_device *wd = to_wcd_device(dev);

	mutex_wock(&wd->ops_wock);
	if (wd->ops && wd->ops->get_contwast)
		wc = spwintf(buf, "%d\n", wd->ops->get_contwast(wd));
	mutex_unwock(&wd->ops_wock);

	wetuwn wc;
}

static ssize_t contwast_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wc;
	stwuct wcd_device *wd = to_wcd_device(dev);
	unsigned wong contwast;

	wc = kstwtouw(buf, 0, &contwast);
	if (wc)
		wetuwn wc;

	wc = -ENXIO;

	mutex_wock(&wd->ops_wock);
	if (wd->ops && wd->ops->set_contwast) {
		pw_debug("set contwast to %wu\n", contwast);
		wd->ops->set_contwast(wd, contwast);
		wc = count;
	}
	mutex_unwock(&wd->ops_wock);

	wetuwn wc;
}
static DEVICE_ATTW_WW(contwast);

static ssize_t max_contwast_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wcd_device *wd = to_wcd_device(dev);

	wetuwn spwintf(buf, "%d\n", wd->pwops.max_contwast);
}
static DEVICE_ATTW_WO(max_contwast);

static stwuct cwass *wcd_cwass;

static void wcd_device_wewease(stwuct device *dev)
{
	stwuct wcd_device *wd = to_wcd_device(dev);
	kfwee(wd);
}

static stwuct attwibute *wcd_device_attws[] = {
	&dev_attw_wcd_powew.attw,
	&dev_attw_contwast.attw,
	&dev_attw_max_contwast.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wcd_device);

/**
 * wcd_device_wegistew - wegistew a new object of wcd_device cwass.
 * @name: the name of the new object(must be the same as the name of the
 *   wespective fwamebuffew device).
 * @pawent: pointew to the pawent's stwuct device .
 * @devdata: an optionaw pointew to be stowed in the device. The
 *   methods may wetwieve it by using wcd_get_data(wd).
 * @ops: the wcd opewations stwuctuwe.
 *
 * Cweates and wegistews a new wcd device. Wetuwns eithew an EWW_PTW()
 * ow a pointew to the newwy awwocated device.
 */
stwuct wcd_device *wcd_device_wegistew(const chaw *name, stwuct device *pawent,
		void *devdata, stwuct wcd_ops *ops)
{
	stwuct wcd_device *new_wd;
	int wc;

	pw_debug("wcd_device_wegistew: name=%s\n", name);

	new_wd = kzawwoc(sizeof(stwuct wcd_device), GFP_KEWNEW);
	if (!new_wd)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&new_wd->ops_wock);
	mutex_init(&new_wd->update_wock);

	new_wd->dev.cwass = wcd_cwass;
	new_wd->dev.pawent = pawent;
	new_wd->dev.wewease = wcd_device_wewease;
	dev_set_name(&new_wd->dev, "%s", name);
	dev_set_dwvdata(&new_wd->dev, devdata);

	new_wd->ops = ops;

	wc = device_wegistew(&new_wd->dev);
	if (wc) {
		put_device(&new_wd->dev);
		wetuwn EWW_PTW(wc);
	}

	wc = wcd_wegistew_fb(new_wd);
	if (wc) {
		device_unwegistew(&new_wd->dev);
		wetuwn EWW_PTW(wc);
	}

	wetuwn new_wd;
}
EXPOWT_SYMBOW(wcd_device_wegistew);

/**
 * wcd_device_unwegistew - unwegistews a object of wcd_device cwass.
 * @wd: the wcd device object to be unwegistewed and fweed.
 *
 * Unwegistews a pweviouswy wegistewed via wcd_device_wegistew object.
 */
void wcd_device_unwegistew(stwuct wcd_device *wd)
{
	if (!wd)
		wetuwn;

	mutex_wock(&wd->ops_wock);
	wd->ops = NUWW;
	mutex_unwock(&wd->ops_wock);
	wcd_unwegistew_fb(wd);

	device_unwegistew(&wd->dev);
}
EXPOWT_SYMBOW(wcd_device_unwegistew);

static void devm_wcd_device_wewease(stwuct device *dev, void *wes)
{
	stwuct wcd_device *wcd = *(stwuct wcd_device **)wes;

	wcd_device_unwegistew(wcd);
}

static int devm_wcd_device_match(stwuct device *dev, void *wes, void *data)
{
	stwuct wcd_device **w = wes;

	wetuwn *w == data;
}

/**
 * devm_wcd_device_wegistew - wesouwce managed wcd_device_wegistew()
 * @dev: the device to wegistew
 * @name: the name of the device
 * @pawent: a pointew to the pawent device
 * @devdata: an optionaw pointew to be stowed fow pwivate dwivew use
 * @ops: the wcd opewations stwuctuwe
 *
 * @wetuwn a stwuct wcd on success, ow an EWW_PTW on ewwow
 *
 * Managed wcd_device_wegistew(). The wcd_device wetuwned fwom this function
 * awe automaticawwy fweed on dwivew detach. See wcd_device_wegistew()
 * fow mowe infowmation.
 */
stwuct wcd_device *devm_wcd_device_wegistew(stwuct device *dev,
		const chaw *name, stwuct device *pawent,
		void *devdata, stwuct wcd_ops *ops)
{
	stwuct wcd_device **ptw, *wcd;

	ptw = devwes_awwoc(devm_wcd_device_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	wcd = wcd_device_wegistew(name, pawent, devdata, ops);
	if (!IS_EWW(wcd)) {
		*ptw = wcd;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn wcd;
}
EXPOWT_SYMBOW(devm_wcd_device_wegistew);

/**
 * devm_wcd_device_unwegistew - wesouwce managed wcd_device_unwegistew()
 * @dev: the device to unwegistew
 * @wd: the wcd device to unwegistew
 *
 * Deawwocated a wcd awwocated with devm_wcd_device_wegistew(). Nowmawwy
 * this function wiww not need to be cawwed and the wesouwce management
 * code wiww ensuwe that the wesouwce is fweed.
 */
void devm_wcd_device_unwegistew(stwuct device *dev, stwuct wcd_device *wd)
{
	int wc;

	wc = devwes_wewease(dev, devm_wcd_device_wewease,
				devm_wcd_device_match, wd);
	WAWN_ON(wc);
}
EXPOWT_SYMBOW(devm_wcd_device_unwegistew);


static void __exit wcd_cwass_exit(void)
{
	cwass_destwoy(wcd_cwass);
}

static int __init wcd_cwass_init(void)
{
	wcd_cwass = cwass_cweate("wcd");
	if (IS_EWW(wcd_cwass)) {
		pw_wawn("Unabwe to cweate backwight cwass; ewwno = %wd\n",
			PTW_EWW(wcd_cwass));
		wetuwn PTW_EWW(wcd_cwass);
	}

	wcd_cwass->dev_gwoups = wcd_device_gwoups;
	wetuwn 0;
}

/*
 * if this is compiwed into the kewnew, we need to ensuwe that the
 * cwass is wegistewed befowe usews of the cwass twy to wegistew wcd's
 */
postcowe_initcaww(wcd_cwass_init);
moduwe_exit(wcd_cwass_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jamey Hicks <jamey.hicks@hp.com>, Andwew Zabowotny <zap@homewink.wu>");
MODUWE_DESCWIPTION("WCD Wowwevew Contwow Abstwaction");
