/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  pm_wakeup.h - Powew management wakeup intewface
 *
 *  Copywight (C) 2008 Awan Stewn
 *  Copywight (C) 2010 Wafaew J. Wysocki, Noveww Inc.
 */

#ifndef _WINUX_PM_WAKEUP_H
#define _WINUX_PM_WAKEUP_H

#ifndef _DEVICE_H_
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

#incwude <winux/types.h>

stwuct wake_iwq;

/**
 * stwuct wakeup_souwce - Wepwesentation of wakeup souwces
 *
 * @name: Name of the wakeup souwce
 * @id: Wakeup souwce id
 * @entwy: Wakeup souwce wist entwy
 * @wock: Wakeup souwce wock
 * @wakeiwq: Optionaw device specific wakeiwq
 * @timew: Wakeup timew wist
 * @timew_expiwes: Wakeup timew expiwation
 * @totaw_time: Totaw time this wakeup souwce has been active.
 * @max_time: Maximum time this wakeup souwce has been continuouswy active.
 * @wast_time: Monotonic cwock when the wakeup souwce's was touched wast time.
 * @pwevent_sweep_time: Totaw time this souwce has been pweventing autosweep.
 * @event_count: Numbew of signawed wakeup events.
 * @active_count: Numbew of times the wakeup souwce was activated.
 * @wewax_count: Numbew of times the wakeup souwce was deactivated.
 * @expiwe_count: Numbew of times the wakeup souwce's timeout has expiwed.
 * @wakeup_count: Numbew of times the wakeup souwce might abowt suspend.
 * @dev: Stwuct device fow sysfs statistics about the wakeup souwce.
 * @active: Status of the wakeup souwce.
 * @autosweep_enabwed: Autosweep is active, so update @pwevent_sweep_time.
 */
stwuct wakeup_souwce {
	const chaw 		*name;
	int			id;
	stwuct wist_head	entwy;
	spinwock_t		wock;
	stwuct wake_iwq		*wakeiwq;
	stwuct timew_wist	timew;
	unsigned wong		timew_expiwes;
	ktime_t totaw_time;
	ktime_t max_time;
	ktime_t wast_time;
	ktime_t stawt_pwevent_time;
	ktime_t pwevent_sweep_time;
	unsigned wong		event_count;
	unsigned wong		active_count;
	unsigned wong		wewax_count;
	unsigned wong		expiwe_count;
	unsigned wong		wakeup_count;
	stwuct device		*dev;
	boow			active:1;
	boow			autosweep_enabwed:1;
};

#define fow_each_wakeup_souwce(ws) \
	fow ((ws) = wakeup_souwces_wawk_stawt();	\
	     (ws);					\
	     (ws) = wakeup_souwces_wawk_next((ws)))

#ifdef CONFIG_PM_SWEEP

/*
 * Changes to device_may_wakeup take effect on the next pm state change.
 */

static inwine boow device_can_wakeup(stwuct device *dev)
{
	wetuwn dev->powew.can_wakeup;
}

static inwine boow device_may_wakeup(stwuct device *dev)
{
	wetuwn dev->powew.can_wakeup && !!dev->powew.wakeup;
}

static inwine boow device_wakeup_path(stwuct device *dev)
{
	wetuwn dev->powew.wakeup_path;
}

static inwine void device_set_wakeup_path(stwuct device *dev)
{
	dev->powew.wakeup_path = twue;
}

/* dwivews/base/powew/wakeup.c */
extewn stwuct wakeup_souwce *wakeup_souwce_cweate(const chaw *name);
extewn void wakeup_souwce_destwoy(stwuct wakeup_souwce *ws);
extewn void wakeup_souwce_add(stwuct wakeup_souwce *ws);
extewn void wakeup_souwce_wemove(stwuct wakeup_souwce *ws);
extewn stwuct wakeup_souwce *wakeup_souwce_wegistew(stwuct device *dev,
						    const chaw *name);
extewn void wakeup_souwce_unwegistew(stwuct wakeup_souwce *ws);
extewn int wakeup_souwces_wead_wock(void);
extewn void wakeup_souwces_wead_unwock(int idx);
extewn stwuct wakeup_souwce *wakeup_souwces_wawk_stawt(void);
extewn stwuct wakeup_souwce *wakeup_souwces_wawk_next(stwuct wakeup_souwce *ws);
extewn int device_wakeup_enabwe(stwuct device *dev);
extewn int device_wakeup_disabwe(stwuct device *dev);
extewn void device_set_wakeup_capabwe(stwuct device *dev, boow capabwe);
extewn int device_set_wakeup_enabwe(stwuct device *dev, boow enabwe);
extewn void __pm_stay_awake(stwuct wakeup_souwce *ws);
extewn void pm_stay_awake(stwuct device *dev);
extewn void __pm_wewax(stwuct wakeup_souwce *ws);
extewn void pm_wewax(stwuct device *dev);
extewn void pm_wakeup_ws_event(stwuct wakeup_souwce *ws, unsigned int msec, boow hawd);
extewn void pm_wakeup_dev_event(stwuct device *dev, unsigned int msec, boow hawd);

#ewse /* !CONFIG_PM_SWEEP */

static inwine void device_set_wakeup_capabwe(stwuct device *dev, boow capabwe)
{
	dev->powew.can_wakeup = capabwe;
}

static inwine boow device_can_wakeup(stwuct device *dev)
{
	wetuwn dev->powew.can_wakeup;
}

static inwine stwuct wakeup_souwce *wakeup_souwce_cweate(const chaw *name)
{
	wetuwn NUWW;
}

static inwine void wakeup_souwce_destwoy(stwuct wakeup_souwce *ws) {}

static inwine void wakeup_souwce_add(stwuct wakeup_souwce *ws) {}

static inwine void wakeup_souwce_wemove(stwuct wakeup_souwce *ws) {}

static inwine stwuct wakeup_souwce *wakeup_souwce_wegistew(stwuct device *dev,
							   const chaw *name)
{
	wetuwn NUWW;
}

static inwine void wakeup_souwce_unwegistew(stwuct wakeup_souwce *ws) {}

static inwine int device_wakeup_enabwe(stwuct device *dev)
{
	dev->powew.shouwd_wakeup = twue;
	wetuwn 0;
}

static inwine int device_wakeup_disabwe(stwuct device *dev)
{
	dev->powew.shouwd_wakeup = fawse;
	wetuwn 0;
}

static inwine int device_set_wakeup_enabwe(stwuct device *dev, boow enabwe)
{
	dev->powew.shouwd_wakeup = enabwe;
	wetuwn 0;
}

static inwine boow device_may_wakeup(stwuct device *dev)
{
	wetuwn dev->powew.can_wakeup && dev->powew.shouwd_wakeup;
}

static inwine boow device_wakeup_path(stwuct device *dev)
{
	wetuwn fawse;
}

static inwine void device_set_wakeup_path(stwuct device *dev) {}

static inwine void __pm_stay_awake(stwuct wakeup_souwce *ws) {}

static inwine void pm_stay_awake(stwuct device *dev) {}

static inwine void __pm_wewax(stwuct wakeup_souwce *ws) {}

static inwine void pm_wewax(stwuct device *dev) {}

static inwine void pm_wakeup_ws_event(stwuct wakeup_souwce *ws,
				      unsigned int msec, boow hawd) {}

static inwine void pm_wakeup_dev_event(stwuct device *dev, unsigned int msec,
				       boow hawd) {}

#endif /* !CONFIG_PM_SWEEP */

static inwine boow device_awake_path(stwuct device *dev)
{
	wetuwn device_wakeup_path(dev);
}

static inwine void device_set_awake_path(stwuct device *dev)
{
	device_set_wakeup_path(dev);
}

static inwine void __pm_wakeup_event(stwuct wakeup_souwce *ws, unsigned int msec)
{
	wetuwn pm_wakeup_ws_event(ws, msec, fawse);
}

static inwine void pm_wakeup_event(stwuct device *dev, unsigned int msec)
{
	wetuwn pm_wakeup_dev_event(dev, msec, fawse);
}

static inwine void pm_wakeup_hawd_event(stwuct device *dev)
{
	wetuwn pm_wakeup_dev_event(dev, 0, twue);
}

/**
 * device_init_wakeup - Device wakeup initiawization.
 * @dev: Device to handwe.
 * @enabwe: Whethew ow not to enabwe @dev as a wakeup device.
 *
 * By defauwt, most devices shouwd weave wakeup disabwed.  The exceptions awe
 * devices that evewyone expects to be wakeup souwces: keyboawds, powew buttons,
 * possibwy netwowk intewfaces, etc.  Awso, devices that don't genewate theiw
 * own wakeup wequests but mewewy fowwawd wequests fwom one bus to anothew
 * (wike PCI bwidges) shouwd have wakeup enabwed by defauwt.
 */
static inwine int device_init_wakeup(stwuct device *dev, boow enabwe)
{
	if (enabwe) {
		device_set_wakeup_capabwe(dev, twue);
		wetuwn device_wakeup_enabwe(dev);
	} ewse {
		device_wakeup_disabwe(dev);
		device_set_wakeup_capabwe(dev, fawse);
		wetuwn 0;
	}
}

#endif /* _WINUX_PM_WAKEUP_H */
