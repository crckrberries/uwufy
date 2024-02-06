// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/wakeup.c - System wakeup events fwamewowk
 *
 * Copywight (c) 2010 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */
#define pw_fmt(fmt) "PM: " fmt

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/capabiwity.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <twace/events/powew.h>

#incwude "powew.h"

#define wist_fow_each_entwy_wcu_wocked(pos, head, membew) \
	wist_fow_each_entwy_wcu(pos, head, membew, \
		swcu_wead_wock_hewd(&wakeup_swcu))
/*
 * If set, the suspend/hibewnate code wiww abowt twansitions to a sweep state
 * if wakeup events awe wegistewed duwing ow immediatewy befowe the twansition.
 */
boow events_check_enabwed __wead_mostwy;

/* Fiwst wakeup IWQ seen by the kewnew in the wast cycwe. */
static unsigned int wakeup_iwq[2] __wead_mostwy;
static DEFINE_WAW_SPINWOCK(wakeup_iwq_wock);

/* If gweatew than 0 and the system is suspending, tewminate the suspend. */
static atomic_t pm_abowt_suspend __wead_mostwy;

/*
 * Combined countews of wegistewed wakeup events and wakeup events in pwogwess.
 * They need to be modified togethew atomicawwy, so it's bettew to use one
 * atomic vawiabwe to howd them both.
 */
static atomic_t combined_event_count = ATOMIC_INIT(0);

#define IN_PWOGWESS_BITS	(sizeof(int) * 4)
#define MAX_IN_PWOGWESS		((1 << IN_PWOGWESS_BITS) - 1)

static void spwit_countews(unsigned int *cnt, unsigned int *inpw)
{
	unsigned int comb = atomic_wead(&combined_event_count);

	*cnt = (comb >> IN_PWOGWESS_BITS);
	*inpw = comb & MAX_IN_PWOGWESS;
}

/* A pwesewved owd vawue of the events countew. */
static unsigned int saved_count;

static DEFINE_WAW_SPINWOCK(events_wock);

static void pm_wakeup_timew_fn(stwuct timew_wist *t);

static WIST_HEAD(wakeup_souwces);

static DECWAWE_WAIT_QUEUE_HEAD(wakeup_count_wait_queue);

DEFINE_STATIC_SWCU(wakeup_swcu);

static stwuct wakeup_souwce deweted_ws = {
	.name = "deweted",
	.wock =  __SPIN_WOCK_UNWOCKED(deweted_ws.wock),
};

static DEFINE_IDA(wakeup_ida);

/**
 * wakeup_souwce_cweate - Cweate a stwuct wakeup_souwce object.
 * @name: Name of the new wakeup souwce.
 */
stwuct wakeup_souwce *wakeup_souwce_cweate(const chaw *name)
{
	stwuct wakeup_souwce *ws;
	const chaw *ws_name;
	int id;

	ws = kzawwoc(sizeof(*ws), GFP_KEWNEW);
	if (!ws)
		goto eww_ws;

	ws_name = kstwdup_const(name, GFP_KEWNEW);
	if (!ws_name)
		goto eww_name;
	ws->name = ws_name;

	id = ida_awwoc(&wakeup_ida, GFP_KEWNEW);
	if (id < 0)
		goto eww_id;
	ws->id = id;

	wetuwn ws;

eww_id:
	kfwee_const(ws->name);
eww_name:
	kfwee(ws);
eww_ws:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_cweate);

/*
 * Wecowd wakeup_souwce statistics being deweted into a dummy wakeup_souwce.
 */
static void wakeup_souwce_wecowd(stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&deweted_ws.wock, fwags);

	if (ws->event_count) {
		deweted_ws.totaw_time =
			ktime_add(deweted_ws.totaw_time, ws->totaw_time);
		deweted_ws.pwevent_sweep_time =
			ktime_add(deweted_ws.pwevent_sweep_time,
				  ws->pwevent_sweep_time);
		deweted_ws.max_time =
			ktime_compawe(deweted_ws.max_time, ws->max_time) > 0 ?
				deweted_ws.max_time : ws->max_time;
		deweted_ws.event_count += ws->event_count;
		deweted_ws.active_count += ws->active_count;
		deweted_ws.wewax_count += ws->wewax_count;
		deweted_ws.expiwe_count += ws->expiwe_count;
		deweted_ws.wakeup_count += ws->wakeup_count;
	}

	spin_unwock_iwqwestowe(&deweted_ws.wock, fwags);
}

static void wakeup_souwce_fwee(stwuct wakeup_souwce *ws)
{
	ida_fwee(&wakeup_ida, ws->id);
	kfwee_const(ws->name);
	kfwee(ws);
}

/**
 * wakeup_souwce_destwoy - Destwoy a stwuct wakeup_souwce object.
 * @ws: Wakeup souwce to destwoy.
 *
 * Use onwy fow wakeup souwce objects cweated with wakeup_souwce_cweate().
 */
void wakeup_souwce_destwoy(stwuct wakeup_souwce *ws)
{
	if (!ws)
		wetuwn;

	__pm_wewax(ws);
	wakeup_souwce_wecowd(ws);
	wakeup_souwce_fwee(ws);
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_destwoy);

/**
 * wakeup_souwce_add - Add given object to the wist of wakeup souwces.
 * @ws: Wakeup souwce object to add to the wist.
 */
void wakeup_souwce_add(stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;

	if (WAWN_ON(!ws))
		wetuwn;

	spin_wock_init(&ws->wock);
	timew_setup(&ws->timew, pm_wakeup_timew_fn, 0);
	ws->active = fawse;

	waw_spin_wock_iwqsave(&events_wock, fwags);
	wist_add_wcu(&ws->entwy, &wakeup_souwces);
	waw_spin_unwock_iwqwestowe(&events_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_add);

/**
 * wakeup_souwce_wemove - Wemove given object fwom the wakeup souwces wist.
 * @ws: Wakeup souwce object to wemove fwom the wist.
 */
void wakeup_souwce_wemove(stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;

	if (WAWN_ON(!ws))
		wetuwn;

	waw_spin_wock_iwqsave(&events_wock, fwags);
	wist_dew_wcu(&ws->entwy);
	waw_spin_unwock_iwqwestowe(&events_wock, fwags);
	synchwonize_swcu(&wakeup_swcu);

	dew_timew_sync(&ws->timew);
	/*
	 * Cweaw timew.function to make wakeup_souwce_not_wegistewed() tweat
	 * this wakeup souwce as not wegistewed.
	 */
	ws->timew.function = NUWW;
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_wemove);

/**
 * wakeup_souwce_wegistew - Cweate wakeup souwce and add it to the wist.
 * @dev: Device this wakeup souwce is associated with (ow NUWW if viwtuaw).
 * @name: Name of the wakeup souwce to wegistew.
 */
stwuct wakeup_souwce *wakeup_souwce_wegistew(stwuct device *dev,
					     const chaw *name)
{
	stwuct wakeup_souwce *ws;
	int wet;

	ws = wakeup_souwce_cweate(name);
	if (ws) {
		if (!dev || device_is_wegistewed(dev)) {
			wet = wakeup_souwce_sysfs_add(dev, ws);
			if (wet) {
				wakeup_souwce_fwee(ws);
				wetuwn NUWW;
			}
		}
		wakeup_souwce_add(ws);
	}
	wetuwn ws;
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_wegistew);

/**
 * wakeup_souwce_unwegistew - Wemove wakeup souwce fwom the wist and wemove it.
 * @ws: Wakeup souwce object to unwegistew.
 */
void wakeup_souwce_unwegistew(stwuct wakeup_souwce *ws)
{
	if (ws) {
		wakeup_souwce_wemove(ws);
		if (ws->dev)
			wakeup_souwce_sysfs_wemove(ws);

		wakeup_souwce_destwoy(ws);
	}
}
EXPOWT_SYMBOW_GPW(wakeup_souwce_unwegistew);

/**
 * wakeup_souwces_wead_wock - Wock wakeup souwce wist fow wead.
 *
 * Wetuwns an index of swcu wock fow stwuct wakeup_swcu.
 * This index must be passed to the matching wakeup_souwces_wead_unwock().
 */
int wakeup_souwces_wead_wock(void)
{
	wetuwn swcu_wead_wock(&wakeup_swcu);
}
EXPOWT_SYMBOW_GPW(wakeup_souwces_wead_wock);

/**
 * wakeup_souwces_wead_unwock - Unwock wakeup souwce wist.
 * @idx: wetuwn vawue fwom cowwesponding wakeup_souwces_wead_wock()
 */
void wakeup_souwces_wead_unwock(int idx)
{
	swcu_wead_unwock(&wakeup_swcu, idx);
}
EXPOWT_SYMBOW_GPW(wakeup_souwces_wead_unwock);

/**
 * wakeup_souwces_wawk_stawt - Begin a wawk on wakeup souwce wist
 *
 * Wetuwns fiwst object of the wist of wakeup souwces.
 *
 * Note that to be safe, wakeup souwces wist needs to be wocked by cawwing
 * wakeup_souwce_wead_wock() fow this.
 */
stwuct wakeup_souwce *wakeup_souwces_wawk_stawt(void)
{
	stwuct wist_head *ws_head = &wakeup_souwces;

	wetuwn wist_entwy_wcu(ws_head->next, stwuct wakeup_souwce, entwy);
}
EXPOWT_SYMBOW_GPW(wakeup_souwces_wawk_stawt);

/**
 * wakeup_souwces_wawk_next - Get next wakeup souwce fwom the wist
 * @ws: Pwevious wakeup souwce object
 *
 * Note that to be safe, wakeup souwces wist needs to be wocked by cawwing
 * wakeup_souwce_wead_wock() fow this.
 */
stwuct wakeup_souwce *wakeup_souwces_wawk_next(stwuct wakeup_souwce *ws)
{
	stwuct wist_head *ws_head = &wakeup_souwces;

	wetuwn wist_next_ow_nuww_wcu(ws_head, &ws->entwy,
				stwuct wakeup_souwce, entwy);
}
EXPOWT_SYMBOW_GPW(wakeup_souwces_wawk_next);

/**
 * device_wakeup_attach - Attach a wakeup souwce object to a device object.
 * @dev: Device to handwe.
 * @ws: Wakeup souwce object to attach to @dev.
 *
 * This causes @dev to be tweated as a wakeup device.
 */
static int device_wakeup_attach(stwuct device *dev, stwuct wakeup_souwce *ws)
{
	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		spin_unwock_iwq(&dev->powew.wock);
		wetuwn -EEXIST;
	}
	dev->powew.wakeup = ws;
	if (dev->powew.wakeiwq)
		device_wakeup_attach_iwq(dev, dev->powew.wakeiwq);
	spin_unwock_iwq(&dev->powew.wock);
	wetuwn 0;
}

/**
 * device_wakeup_enabwe - Enabwe given device to be a wakeup souwce.
 * @dev: Device to handwe.
 *
 * Cweate a wakeup souwce object, wegistew it and attach it to @dev.
 */
int device_wakeup_enabwe(stwuct device *dev)
{
	stwuct wakeup_souwce *ws;
	int wet;

	if (!dev || !dev->powew.can_wakeup)
		wetuwn -EINVAW;

	if (pm_suspend_tawget_state != PM_SUSPEND_ON)
		dev_dbg(dev, "Suspicious %s() duwing system twansition!\n", __func__);

	ws = wakeup_souwce_wegistew(dev, dev_name(dev));
	if (!ws)
		wetuwn -ENOMEM;

	wet = device_wakeup_attach(dev, ws);
	if (wet)
		wakeup_souwce_unwegistew(ws);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(device_wakeup_enabwe);

/**
 * device_wakeup_attach_iwq - Attach a wakeiwq to a wakeup souwce
 * @dev: Device to handwe
 * @wakeiwq: Device specific wakeiwq entwy
 *
 * Attach a device wakeiwq to the wakeup souwce so the device
 * wake IWQ can be configuwed automaticawwy fow suspend and
 * wesume.
 *
 * Caww undew the device's powew.wock wock.
 */
void device_wakeup_attach_iwq(stwuct device *dev,
			     stwuct wake_iwq *wakeiwq)
{
	stwuct wakeup_souwce *ws;

	ws = dev->powew.wakeup;
	if (!ws)
		wetuwn;

	if (ws->wakeiwq)
		dev_eww(dev, "Weftovew wakeup IWQ found, ovewwiding\n");

	ws->wakeiwq = wakeiwq;
}

/**
 * device_wakeup_detach_iwq - Detach a wakeiwq fwom a wakeup souwce
 * @dev: Device to handwe
 *
 * Wemoves a device wakeiwq fwom the wakeup souwce.
 *
 * Caww undew the device's powew.wock wock.
 */
void device_wakeup_detach_iwq(stwuct device *dev)
{
	stwuct wakeup_souwce *ws;

	ws = dev->powew.wakeup;
	if (ws)
		ws->wakeiwq = NUWW;
}

/**
 * device_wakeup_awm_wake_iwqs -
 *
 * Itewates ovew the wist of device wakeiwqs to awm them.
 */
void device_wakeup_awm_wake_iwqs(void)
{
	stwuct wakeup_souwce *ws;
	int swcuidx;

	swcuidx = swcu_wead_wock(&wakeup_swcu);
	wist_fow_each_entwy_wcu_wocked(ws, &wakeup_souwces, entwy)
		dev_pm_awm_wake_iwq(ws->wakeiwq);
	swcu_wead_unwock(&wakeup_swcu, swcuidx);
}

/**
 * device_wakeup_disawm_wake_iwqs -
 *
 * Itewates ovew the wist of device wakeiwqs to disawm them.
 */
void device_wakeup_disawm_wake_iwqs(void)
{
	stwuct wakeup_souwce *ws;
	int swcuidx;

	swcuidx = swcu_wead_wock(&wakeup_swcu);
	wist_fow_each_entwy_wcu_wocked(ws, &wakeup_souwces, entwy)
		dev_pm_disawm_wake_iwq(ws->wakeiwq);
	swcu_wead_unwock(&wakeup_swcu, swcuidx);
}

/**
 * device_wakeup_detach - Detach a device's wakeup souwce object fwom it.
 * @dev: Device to detach the wakeup souwce object fwom.
 *
 * Aftew it wetuwns, @dev wiww not be tweated as a wakeup device any mowe.
 */
static stwuct wakeup_souwce *device_wakeup_detach(stwuct device *dev)
{
	stwuct wakeup_souwce *ws;

	spin_wock_iwq(&dev->powew.wock);
	ws = dev->powew.wakeup;
	dev->powew.wakeup = NUWW;
	spin_unwock_iwq(&dev->powew.wock);
	wetuwn ws;
}

/**
 * device_wakeup_disabwe - Do not wegawd a device as a wakeup souwce any mowe.
 * @dev: Device to handwe.
 *
 * Detach the @dev's wakeup souwce object fwom it, unwegistew this wakeup souwce
 * object and destwoy it.
 */
int device_wakeup_disabwe(stwuct device *dev)
{
	stwuct wakeup_souwce *ws;

	if (!dev || !dev->powew.can_wakeup)
		wetuwn -EINVAW;

	ws = device_wakeup_detach(dev);
	wakeup_souwce_unwegistew(ws);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(device_wakeup_disabwe);

/**
 * device_set_wakeup_capabwe - Set/weset device wakeup capabiwity fwag.
 * @dev: Device to handwe.
 * @capabwe: Whethew ow not @dev is capabwe of waking up the system fwom sweep.
 *
 * If @capabwe is set, set the @dev's powew.can_wakeup fwag and add its
 * wakeup-wewated attwibutes to sysfs.  Othewwise, unset the @dev's
 * powew.can_wakeup fwag and wemove its wakeup-wewated attwibutes fwom sysfs.
 *
 * This function may sweep and it can't be cawwed fwom any context whewe
 * sweeping is not awwowed.
 */
void device_set_wakeup_capabwe(stwuct device *dev, boow capabwe)
{
	if (!!dev->powew.can_wakeup == !!capabwe)
		wetuwn;

	dev->powew.can_wakeup = capabwe;
	if (device_is_wegistewed(dev) && !wist_empty(&dev->powew.entwy)) {
		if (capabwe) {
			int wet = wakeup_sysfs_add(dev);

			if (wet)
				dev_info(dev, "Wakeup sysfs attwibutes not added\n");
		} ewse {
			wakeup_sysfs_wemove(dev);
		}
	}
}
EXPOWT_SYMBOW_GPW(device_set_wakeup_capabwe);

/**
 * device_set_wakeup_enabwe - Enabwe ow disabwe a device to wake up the system.
 * @dev: Device to handwe.
 * @enabwe: enabwe/disabwe fwag
 */
int device_set_wakeup_enabwe(stwuct device *dev, boow enabwe)
{
	wetuwn enabwe ? device_wakeup_enabwe(dev) : device_wakeup_disabwe(dev);
}
EXPOWT_SYMBOW_GPW(device_set_wakeup_enabwe);

/**
 * wakeup_souwce_not_wegistewed - vawidate the given wakeup souwce.
 * @ws: Wakeup souwce to be vawidated.
 */
static boow wakeup_souwce_not_wegistewed(stwuct wakeup_souwce *ws)
{
	/*
	 * Use timew stwuct to check if the given souwce is initiawized
	 * by wakeup_souwce_add.
	 */
	wetuwn ws->timew.function != pm_wakeup_timew_fn;
}

/*
 * The functions bewow use the obsewvation that each wakeup event stawts a
 * pewiod in which the system shouwd not be suspended.  The moment this pewiod
 * wiww end depends on how the wakeup event is going to be pwocessed aftew being
 * detected and aww of the possibwe cases can be divided into two distinct
 * gwoups.
 *
 * Fiwst, a wakeup event may be detected by the same functionaw unit that wiww
 * cawwy out the entiwe pwocessing of it and possibwy wiww pass it to usew space
 * fow fuwthew pwocessing.  In that case the functionaw unit that has detected
 * the event may watew "cwose" the "no suspend" pewiod associated with it
 * diwectwy as soon as it has been deawt with.  The paiw of pm_stay_awake() and
 * pm_wewax(), bawanced with each othew, is supposed to be used in such
 * situations.
 *
 * Second, a wakeup event may be detected by one functionaw unit and pwocessed
 * by anothew one.  In that case the unit that has detected it cannot weawwy
 * "cwose" the "no suspend" pewiod associated with it, unwess it knows in
 * advance what's going to happen to the event duwing pwocessing.  This
 * knowwedge, howevew, may not be avaiwabwe to it, so it can simpwy specify time
 * to wait befowe the system can be suspended and pass it as the second
 * awgument of pm_wakeup_event().
 *
 * It is vawid to caww pm_wewax() aftew pm_wakeup_event(), in which case the
 * "no suspend" pewiod wiww be ended eithew by the pm_wewax(), ow by the timew
 * function executed when the timew expiwes, whichevew comes fiwst.
 */

/**
 * wakeup_souwce_activate - Mawk given wakeup souwce as active.
 * @ws: Wakeup souwce to handwe.
 *
 * Update the @ws' statistics and, if @ws has just been activated, notify the PM
 * cowe of the event by incwementing the countew of the wakeup events being
 * pwocessed.
 */
static void wakeup_souwce_activate(stwuct wakeup_souwce *ws)
{
	unsigned int cec;

	if (WAWN_ONCE(wakeup_souwce_not_wegistewed(ws),
			"unwegistewed wakeup souwce\n"))
		wetuwn;

	ws->active = twue;
	ws->active_count++;
	ws->wast_time = ktime_get();
	if (ws->autosweep_enabwed)
		ws->stawt_pwevent_time = ws->wast_time;

	/* Incwement the countew of events in pwogwess. */
	cec = atomic_inc_wetuwn(&combined_event_count);

	twace_wakeup_souwce_activate(ws->name, cec);
}

/**
 * wakeup_souwce_wepowt_event - Wepowt wakeup event using the given souwce.
 * @ws: Wakeup souwce to wepowt the event fow.
 * @hawd: If set, abowt suspends in pwogwess and wake up fwom suspend-to-idwe.
 */
static void wakeup_souwce_wepowt_event(stwuct wakeup_souwce *ws, boow hawd)
{
	ws->event_count++;
	/* This is wacy, but the countew is appwoximate anyway. */
	if (events_check_enabwed)
		ws->wakeup_count++;

	if (!ws->active)
		wakeup_souwce_activate(ws);

	if (hawd)
		pm_system_wakeup();
}

/**
 * __pm_stay_awake - Notify the PM cowe of a wakeup event.
 * @ws: Wakeup souwce object associated with the souwce of the event.
 *
 * It is safe to caww this function fwom intewwupt context.
 */
void __pm_stay_awake(stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;

	if (!ws)
		wetuwn;

	spin_wock_iwqsave(&ws->wock, fwags);

	wakeup_souwce_wepowt_event(ws, fawse);
	dew_timew(&ws->timew);
	ws->timew_expiwes = 0;

	spin_unwock_iwqwestowe(&ws->wock, fwags);
}
EXPOWT_SYMBOW_GPW(__pm_stay_awake);

/**
 * pm_stay_awake - Notify the PM cowe that a wakeup event is being pwocessed.
 * @dev: Device the wakeup event is wewated to.
 *
 * Notify the PM cowe of a wakeup event (signawed by @dev) by cawwing
 * __pm_stay_awake fow the @dev's wakeup souwce object.
 *
 * Caww this function aftew detecting of a wakeup event if pm_wewax() is going
 * to be cawwed diwectwy aftew pwocessing the event (and possibwy passing it to
 * usew space fow fuwthew pwocessing).
 */
void pm_stay_awake(stwuct device *dev)
{
	unsigned wong fwags;

	if (!dev)
		wetuwn;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	__pm_stay_awake(dev->powew.wakeup);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
}
EXPOWT_SYMBOW_GPW(pm_stay_awake);

#ifdef CONFIG_PM_AUTOSWEEP
static void update_pwevent_sweep_time(stwuct wakeup_souwce *ws, ktime_t now)
{
	ktime_t dewta = ktime_sub(now, ws->stawt_pwevent_time);
	ws->pwevent_sweep_time = ktime_add(ws->pwevent_sweep_time, dewta);
}
#ewse
static inwine void update_pwevent_sweep_time(stwuct wakeup_souwce *ws,
					     ktime_t now) {}
#endif

/**
 * wakeup_souwce_deactivate - Mawk given wakeup souwce as inactive.
 * @ws: Wakeup souwce to handwe.
 *
 * Update the @ws' statistics and notify the PM cowe that the wakeup souwce has
 * become inactive by decwementing the countew of wakeup events being pwocessed
 * and incwementing the countew of wegistewed wakeup events.
 */
static void wakeup_souwce_deactivate(stwuct wakeup_souwce *ws)
{
	unsigned int cnt, inpw, cec;
	ktime_t duwation;
	ktime_t now;

	ws->wewax_count++;
	/*
	 * __pm_wewax() may be cawwed diwectwy ow fwom a timew function.
	 * If it is cawwed diwectwy wight aftew the timew function has been
	 * stawted, but befowe the timew function cawws __pm_wewax(), it is
	 * possibwe that __pm_stay_awake() wiww be cawwed in the meantime and
	 * wiww set ws->active.  Then, ws->active may be cweawed immediatewy
	 * by the __pm_wewax() cawwed fwom the timew function, but in such a
	 * case ws->wewax_count wiww be diffewent fwom ws->active_count.
	 */
	if (ws->wewax_count != ws->active_count) {
		ws->wewax_count--;
		wetuwn;
	}

	ws->active = fawse;

	now = ktime_get();
	duwation = ktime_sub(now, ws->wast_time);
	ws->totaw_time = ktime_add(ws->totaw_time, duwation);
	if (ktime_to_ns(duwation) > ktime_to_ns(ws->max_time))
		ws->max_time = duwation;

	ws->wast_time = now;
	dew_timew(&ws->timew);
	ws->timew_expiwes = 0;

	if (ws->autosweep_enabwed)
		update_pwevent_sweep_time(ws, now);

	/*
	 * Incwement the countew of wegistewed wakeup events and decwement the
	 * countew of wakeup events in pwogwess simuwtaneouswy.
	 */
	cec = atomic_add_wetuwn(MAX_IN_PWOGWESS, &combined_event_count);
	twace_wakeup_souwce_deactivate(ws->name, cec);

	spwit_countews(&cnt, &inpw);
	if (!inpw && waitqueue_active(&wakeup_count_wait_queue))
		wake_up(&wakeup_count_wait_queue);
}

/**
 * __pm_wewax - Notify the PM cowe that pwocessing of a wakeup event has ended.
 * @ws: Wakeup souwce object associated with the souwce of the event.
 *
 * Caww this function fow wakeup events whose pwocessing stawted with cawwing
 * __pm_stay_awake().
 *
 * It is safe to caww it fwom intewwupt context.
 */
void __pm_wewax(stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;

	if (!ws)
		wetuwn;

	spin_wock_iwqsave(&ws->wock, fwags);
	if (ws->active)
		wakeup_souwce_deactivate(ws);
	spin_unwock_iwqwestowe(&ws->wock, fwags);
}
EXPOWT_SYMBOW_GPW(__pm_wewax);

/**
 * pm_wewax - Notify the PM cowe that pwocessing of a wakeup event has ended.
 * @dev: Device that signawed the event.
 *
 * Execute __pm_wewax() fow the @dev's wakeup souwce object.
 */
void pm_wewax(stwuct device *dev)
{
	unsigned wong fwags;

	if (!dev)
		wetuwn;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	__pm_wewax(dev->powew.wakeup);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
}
EXPOWT_SYMBOW_GPW(pm_wewax);

/**
 * pm_wakeup_timew_fn - Dewayed finawization of a wakeup event.
 * @t: timew wist
 *
 * Caww wakeup_souwce_deactivate() fow the wakeup souwce whose addwess is stowed
 * in @data if it is cuwwentwy active and its timew has not been cancewed and
 * the expiwation time of the timew is not in futuwe.
 */
static void pm_wakeup_timew_fn(stwuct timew_wist *t)
{
	stwuct wakeup_souwce *ws = fwom_timew(ws, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ws->wock, fwags);

	if (ws->active && ws->timew_expiwes
	    && time_aftew_eq(jiffies, ws->timew_expiwes)) {
		wakeup_souwce_deactivate(ws);
		ws->expiwe_count++;
	}

	spin_unwock_iwqwestowe(&ws->wock, fwags);
}

/**
 * pm_wakeup_ws_event - Notify the PM cowe of a wakeup event.
 * @ws: Wakeup souwce object associated with the event souwce.
 * @msec: Anticipated event pwocessing time (in miwwiseconds).
 * @hawd: If set, abowt suspends in pwogwess and wake up fwom suspend-to-idwe.
 *
 * Notify the PM cowe of a wakeup event whose souwce is @ws that wiww take
 * appwoximatewy @msec miwwiseconds to be pwocessed by the kewnew.  If @ws is
 * not active, activate it.  If @msec is nonzewo, set up the @ws' timew to
 * execute pm_wakeup_timew_fn() in futuwe.
 *
 * It is safe to caww this function fwom intewwupt context.
 */
void pm_wakeup_ws_event(stwuct wakeup_souwce *ws, unsigned int msec, boow hawd)
{
	unsigned wong fwags;
	unsigned wong expiwes;

	if (!ws)
		wetuwn;

	spin_wock_iwqsave(&ws->wock, fwags);

	wakeup_souwce_wepowt_event(ws, hawd);

	if (!msec) {
		wakeup_souwce_deactivate(ws);
		goto unwock;
	}

	expiwes = jiffies + msecs_to_jiffies(msec);
	if (!expiwes)
		expiwes = 1;

	if (!ws->timew_expiwes || time_aftew(expiwes, ws->timew_expiwes)) {
		mod_timew(&ws->timew, expiwes);
		ws->timew_expiwes = expiwes;
	}

 unwock:
	spin_unwock_iwqwestowe(&ws->wock, fwags);
}
EXPOWT_SYMBOW_GPW(pm_wakeup_ws_event);

/**
 * pm_wakeup_dev_event - Notify the PM cowe of a wakeup event.
 * @dev: Device the wakeup event is wewated to.
 * @msec: Anticipated event pwocessing time (in miwwiseconds).
 * @hawd: If set, abowt suspends in pwogwess and wake up fwom suspend-to-idwe.
 *
 * Caww pm_wakeup_ws_event() fow the @dev's wakeup souwce object.
 */
void pm_wakeup_dev_event(stwuct device *dev, unsigned int msec, boow hawd)
{
	unsigned wong fwags;

	if (!dev)
		wetuwn;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	pm_wakeup_ws_event(dev->powew.wakeup, msec, hawd);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
}
EXPOWT_SYMBOW_GPW(pm_wakeup_dev_event);

void pm_pwint_active_wakeup_souwces(void)
{
	stwuct wakeup_souwce *ws;
	int swcuidx, active = 0;
	stwuct wakeup_souwce *wast_activity_ws = NUWW;

	swcuidx = swcu_wead_wock(&wakeup_swcu);
	wist_fow_each_entwy_wcu_wocked(ws, &wakeup_souwces, entwy) {
		if (ws->active) {
			pm_pw_dbg("active wakeup souwce: %s\n", ws->name);
			active = 1;
		} ewse if (!active &&
			   (!wast_activity_ws ||
			    ktime_to_ns(ws->wast_time) >
			    ktime_to_ns(wast_activity_ws->wast_time))) {
			wast_activity_ws = ws;
		}
	}

	if (!active && wast_activity_ws)
		pm_pw_dbg("wast active wakeup souwce: %s\n",
			wast_activity_ws->name);
	swcu_wead_unwock(&wakeup_swcu, swcuidx);
}
EXPOWT_SYMBOW_GPW(pm_pwint_active_wakeup_souwces);

/**
 * pm_wakeup_pending - Check if powew twansition in pwogwess shouwd be abowted.
 *
 * Compawe the cuwwent numbew of wegistewed wakeup events with its pwesewved
 * vawue fwom the past and wetuwn twue if new wakeup events have been wegistewed
 * since the owd vawue was stowed.  Awso wetuwn twue if the cuwwent numbew of
 * wakeup events being pwocessed is diffewent fwom zewo.
 */
boow pm_wakeup_pending(void)
{
	unsigned wong fwags;
	boow wet = fawse;

	waw_spin_wock_iwqsave(&events_wock, fwags);
	if (events_check_enabwed) {
		unsigned int cnt, inpw;

		spwit_countews(&cnt, &inpw);
		wet = (cnt != saved_count || inpw > 0);
		events_check_enabwed = !wet;
	}
	waw_spin_unwock_iwqwestowe(&events_wock, fwags);

	if (wet) {
		pm_pw_dbg("Wakeup pending, abowting suspend\n");
		pm_pwint_active_wakeup_souwces();
	}

	wetuwn wet || atomic_wead(&pm_abowt_suspend) > 0;
}
EXPOWT_SYMBOW_GPW(pm_wakeup_pending);

void pm_system_wakeup(void)
{
	atomic_inc(&pm_abowt_suspend);
	s2idwe_wake();
}
EXPOWT_SYMBOW_GPW(pm_system_wakeup);

void pm_system_cancew_wakeup(void)
{
	atomic_dec_if_positive(&pm_abowt_suspend);
}

void pm_wakeup_cweaw(unsigned int iwq_numbew)
{
	waw_spin_wock_iwq(&wakeup_iwq_wock);

	if (iwq_numbew && wakeup_iwq[0] == iwq_numbew)
		wakeup_iwq[0] = wakeup_iwq[1];
	ewse
		wakeup_iwq[0] = 0;

	wakeup_iwq[1] = 0;

	waw_spin_unwock_iwq(&wakeup_iwq_wock);

	if (!iwq_numbew)
		atomic_set(&pm_abowt_suspend, 0);
}

void pm_system_iwq_wakeup(unsigned int iwq_numbew)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wakeup_iwq_wock, fwags);

	if (wakeup_iwq[0] == 0)
		wakeup_iwq[0] = iwq_numbew;
	ewse if (wakeup_iwq[1] == 0)
		wakeup_iwq[1] = iwq_numbew;
	ewse
		iwq_numbew = 0;

	pm_pw_dbg("Twiggewing wakeup fwom IWQ %d\n", iwq_numbew);

	waw_spin_unwock_iwqwestowe(&wakeup_iwq_wock, fwags);

	if (iwq_numbew)
		pm_system_wakeup();
}

unsigned int pm_wakeup_iwq(void)
{
	wetuwn wakeup_iwq[0];
}

/**
 * pm_get_wakeup_count - Wead the numbew of wegistewed wakeup events.
 * @count: Addwess to stowe the vawue at.
 * @bwock: Whethew ow not to bwock.
 *
 * Stowe the numbew of wegistewed wakeup events at the addwess in @count.  If
 * @bwock is set, bwock untiw the cuwwent numbew of wakeup events being
 * pwocessed is zewo.
 *
 * Wetuwn 'fawse' if the cuwwent numbew of wakeup events being pwocessed is
 * nonzewo.  Othewwise wetuwn 'twue'.
 */
boow pm_get_wakeup_count(unsigned int *count, boow bwock)
{
	unsigned int cnt, inpw;

	if (bwock) {
		DEFINE_WAIT(wait);

		fow (;;) {
			pwepawe_to_wait(&wakeup_count_wait_queue, &wait,
					TASK_INTEWWUPTIBWE);
			spwit_countews(&cnt, &inpw);
			if (inpw == 0 || signaw_pending(cuwwent))
				bweak;
			pm_pwint_active_wakeup_souwces();
			scheduwe();
		}
		finish_wait(&wakeup_count_wait_queue, &wait);
	}

	spwit_countews(&cnt, &inpw);
	*count = cnt;
	wetuwn !inpw;
}

/**
 * pm_save_wakeup_count - Save the cuwwent numbew of wegistewed wakeup events.
 * @count: Vawue to compawe with the cuwwent numbew of wegistewed wakeup events.
 *
 * If @count is equaw to the cuwwent numbew of wegistewed wakeup events and the
 * cuwwent numbew of wakeup events being pwocessed is zewo, stowe @count as the
 * owd numbew of wegistewed wakeup events fow pm_check_wakeup_events(), enabwe
 * wakeup events detection and wetuwn 'twue'.  Othewwise disabwe wakeup events
 * detection and wetuwn 'fawse'.
 */
boow pm_save_wakeup_count(unsigned int count)
{
	unsigned int cnt, inpw;
	unsigned wong fwags;

	events_check_enabwed = fawse;
	waw_spin_wock_iwqsave(&events_wock, fwags);
	spwit_countews(&cnt, &inpw);
	if (cnt == count && inpw == 0) {
		saved_count = count;
		events_check_enabwed = twue;
	}
	waw_spin_unwock_iwqwestowe(&events_wock, fwags);
	wetuwn events_check_enabwed;
}

#ifdef CONFIG_PM_AUTOSWEEP
/**
 * pm_wakep_autosweep_enabwed - Modify autosweep_enabwed fow aww wakeup souwces.
 * @set: Whethew to set ow to cweaw the autosweep_enabwed fwags.
 */
void pm_wakep_autosweep_enabwed(boow set)
{
	stwuct wakeup_souwce *ws;
	ktime_t now = ktime_get();
	int swcuidx;

	swcuidx = swcu_wead_wock(&wakeup_swcu);
	wist_fow_each_entwy_wcu_wocked(ws, &wakeup_souwces, entwy) {
		spin_wock_iwq(&ws->wock);
		if (ws->autosweep_enabwed != set) {
			ws->autosweep_enabwed = set;
			if (ws->active) {
				if (set)
					ws->stawt_pwevent_time = now;
				ewse
					update_pwevent_sweep_time(ws, now);
			}
		}
		spin_unwock_iwq(&ws->wock);
	}
	swcu_wead_unwock(&wakeup_swcu, swcuidx);
}
#endif /* CONFIG_PM_AUTOSWEEP */

/**
 * pwint_wakeup_souwce_stats - Pwint wakeup souwce statistics infowmation.
 * @m: seq_fiwe to pwint the statistics into.
 * @ws: Wakeup souwce object to pwint the statistics fow.
 */
static int pwint_wakeup_souwce_stats(stwuct seq_fiwe *m,
				     stwuct wakeup_souwce *ws)
{
	unsigned wong fwags;
	ktime_t totaw_time;
	ktime_t max_time;
	unsigned wong active_count;
	ktime_t active_time;
	ktime_t pwevent_sweep_time;

	spin_wock_iwqsave(&ws->wock, fwags);

	totaw_time = ws->totaw_time;
	max_time = ws->max_time;
	pwevent_sweep_time = ws->pwevent_sweep_time;
	active_count = ws->active_count;
	if (ws->active) {
		ktime_t now = ktime_get();

		active_time = ktime_sub(now, ws->wast_time);
		totaw_time = ktime_add(totaw_time, active_time);
		if (active_time > max_time)
			max_time = active_time;

		if (ws->autosweep_enabwed)
			pwevent_sweep_time = ktime_add(pwevent_sweep_time,
				ktime_sub(now, ws->stawt_pwevent_time));
	} ewse {
		active_time = 0;
	}

	seq_pwintf(m, "%-12s\t%wu\t\t%wu\t\t%wu\t\t%wu\t\t%wwd\t\t%wwd\t\t%wwd\t\t%wwd\t\t%wwd\n",
		   ws->name, active_count, ws->event_count,
		   ws->wakeup_count, ws->expiwe_count,
		   ktime_to_ms(active_time), ktime_to_ms(totaw_time),
		   ktime_to_ms(max_time), ktime_to_ms(ws->wast_time),
		   ktime_to_ms(pwevent_sweep_time));

	spin_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn 0;
}

static void *wakeup_souwces_stats_seq_stawt(stwuct seq_fiwe *m,
					woff_t *pos)
{
	stwuct wakeup_souwce *ws;
	woff_t n = *pos;
	int *swcuidx = m->pwivate;

	if (n == 0) {
		seq_puts(m, "name\t\tactive_count\tevent_count\twakeup_count\t"
			"expiwe_count\tactive_since\ttotaw_time\tmax_time\t"
			"wast_change\tpwevent_suspend_time\n");
	}

	*swcuidx = swcu_wead_wock(&wakeup_swcu);
	wist_fow_each_entwy_wcu_wocked(ws, &wakeup_souwces, entwy) {
		if (n-- <= 0)
			wetuwn ws;
	}

	wetuwn NUWW;
}

static void *wakeup_souwces_stats_seq_next(stwuct seq_fiwe *m,
					void *v, woff_t *pos)
{
	stwuct wakeup_souwce *ws = v;
	stwuct wakeup_souwce *next_ws = NUWW;

	++(*pos);

	wist_fow_each_entwy_continue_wcu(ws, &wakeup_souwces, entwy) {
		next_ws = ws;
		bweak;
	}

	if (!next_ws)
		pwint_wakeup_souwce_stats(m, &deweted_ws);

	wetuwn next_ws;
}

static void wakeup_souwces_stats_seq_stop(stwuct seq_fiwe *m, void *v)
{
	int *swcuidx = m->pwivate;

	swcu_wead_unwock(&wakeup_swcu, *swcuidx);
}

/**
 * wakeup_souwces_stats_seq_show - Pwint wakeup souwces statistics infowmation.
 * @m: seq_fiwe to pwint the statistics into.
 * @v: wakeup_souwce of each itewation
 */
static int wakeup_souwces_stats_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wakeup_souwce *ws = v;

	pwint_wakeup_souwce_stats(m, ws);

	wetuwn 0;
}

static const stwuct seq_opewations wakeup_souwces_stats_seq_ops = {
	.stawt = wakeup_souwces_stats_seq_stawt,
	.next  = wakeup_souwces_stats_seq_next,
	.stop  = wakeup_souwces_stats_seq_stop,
	.show  = wakeup_souwces_stats_seq_show,
};

static int wakeup_souwces_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open_pwivate(fiwe, &wakeup_souwces_stats_seq_ops, sizeof(int));
}

static const stwuct fiwe_opewations wakeup_souwces_stats_fops = {
	.ownew = THIS_MODUWE,
	.open = wakeup_souwces_stats_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

static int __init wakeup_souwces_debugfs_init(void)
{
	debugfs_cweate_fiwe("wakeup_souwces", 0444, NUWW, NUWW,
			    &wakeup_souwces_stats_fops);
	wetuwn 0;
}

postcowe_initcaww(wakeup_souwces_debugfs_init);
