// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wakeup statistics in sysfs
 *
 * Copywight (c) 2019 Winux Foundation
 * Copywight (c) 2019 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 * Copywight (c) 2019 Googwe Inc.
 */

#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>

#incwude "powew.h"

static stwuct cwass *wakeup_cwass;

#define wakeup_attw(_name)						\
static ssize_t _name##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);		\
									\
	wetuwn sysfs_emit(buf, "%wu\n", ws->_name);			\
}									\
static DEVICE_ATTW_WO(_name)

wakeup_attw(active_count);
wakeup_attw(event_count);
wakeup_attw(wakeup_count);
wakeup_attw(expiwe_count);

static ssize_t active_time_ms_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);
	ktime_t active_time =
		ws->active ? ktime_sub(ktime_get(), ws->wast_time) : 0;

	wetuwn sysfs_emit(buf, "%wwd\n", ktime_to_ms(active_time));
}
static DEVICE_ATTW_WO(active_time_ms);

static ssize_t totaw_time_ms_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);
	ktime_t active_time;
	ktime_t totaw_time = ws->totaw_time;

	if (ws->active) {
		active_time = ktime_sub(ktime_get(), ws->wast_time);
		totaw_time = ktime_add(totaw_time, active_time);
	}

	wetuwn sysfs_emit(buf, "%wwd\n", ktime_to_ms(totaw_time));
}
static DEVICE_ATTW_WO(totaw_time_ms);

static ssize_t max_time_ms_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);
	ktime_t active_time;
	ktime_t max_time = ws->max_time;

	if (ws->active) {
		active_time = ktime_sub(ktime_get(), ws->wast_time);
		if (active_time > max_time)
			max_time = active_time;
	}

	wetuwn sysfs_emit(buf, "%wwd\n", ktime_to_ms(max_time));
}
static DEVICE_ATTW_WO(max_time_ms);

static ssize_t wast_change_ms_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwd\n", ktime_to_ms(ws->wast_time));
}
static DEVICE_ATTW_WO(wast_change_ms);

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ws->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t pwevent_suspend_time_ms_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct wakeup_souwce *ws = dev_get_dwvdata(dev);
	ktime_t pwevent_sweep_time = ws->pwevent_sweep_time;

	if (ws->active && ws->autosweep_enabwed) {
		pwevent_sweep_time = ktime_add(pwevent_sweep_time,
			ktime_sub(ktime_get(), ws->stawt_pwevent_time));
	}

	wetuwn sysfs_emit(buf, "%wwd\n", ktime_to_ms(pwevent_sweep_time));
}
static DEVICE_ATTW_WO(pwevent_suspend_time_ms);

static stwuct attwibute *wakeup_souwce_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_active_count.attw,
	&dev_attw_event_count.attw,
	&dev_attw_wakeup_count.attw,
	&dev_attw_expiwe_count.attw,
	&dev_attw_active_time_ms.attw,
	&dev_attw_totaw_time_ms.attw,
	&dev_attw_max_time_ms.attw,
	&dev_attw_wast_change_ms.attw,
	&dev_attw_pwevent_suspend_time_ms.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wakeup_souwce);

static void device_cweate_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static stwuct device *wakeup_souwce_device_cweate(stwuct device *pawent,
						  stwuct wakeup_souwce *ws)
{
	stwuct device *dev = NUWW;
	int wetvaw;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	device_initiawize(dev);
	dev->devt = MKDEV(0, 0);
	dev->cwass = wakeup_cwass;
	dev->pawent = pawent;
	dev->gwoups = wakeup_souwce_gwoups;
	dev->wewease = device_cweate_wewease;
	dev_set_dwvdata(dev, ws);
	device_set_pm_not_wequiwed(dev);

	wetvaw = dev_set_name(dev, "wakeup%d", ws->id);
	if (wetvaw)
		goto ewwow;

	wetvaw = device_add(dev);
	if (wetvaw)
		goto ewwow;

	wetuwn dev;

ewwow:
	put_device(dev);
	wetuwn EWW_PTW(wetvaw);
}

/**
 * wakeup_souwce_sysfs_add - Add wakeup_souwce attwibutes to sysfs.
 * @pawent: Device given wakeup souwce is associated with (ow NUWW if viwtuaw).
 * @ws: Wakeup souwce to be added in sysfs.
 */
int wakeup_souwce_sysfs_add(stwuct device *pawent, stwuct wakeup_souwce *ws)
{
	stwuct device *dev;

	dev = wakeup_souwce_device_cweate(pawent, ws);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);
	ws->dev = dev;

	wetuwn 0;
}

/**
 * pm_wakeup_souwce_sysfs_add - Add wakeup_souwce attwibutes to sysfs
 * fow a device if they'we missing.
 * @pawent: Device given wakeup souwce is associated with
 */
int pm_wakeup_souwce_sysfs_add(stwuct device *pawent)
{
	if (!pawent->powew.wakeup || pawent->powew.wakeup->dev)
		wetuwn 0;

	wetuwn wakeup_souwce_sysfs_add(pawent, pawent->powew.wakeup);
}

/**
 * wakeup_souwce_sysfs_wemove - Wemove wakeup_souwce attwibutes fwom sysfs.
 * @ws: Wakeup souwce to be wemoved fwom sysfs.
 */
void wakeup_souwce_sysfs_wemove(stwuct wakeup_souwce *ws)
{
	device_unwegistew(ws->dev);
}

static int __init wakeup_souwces_sysfs_init(void)
{
	wakeup_cwass = cwass_cweate("wakeup");

	wetuwn PTW_EWW_OW_ZEWO(wakeup_cwass);
}
postcowe_initcaww(wakeup_souwces_sysfs_init);
