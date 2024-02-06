// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/main.c - Whewe the dwivew meets powew management.
 *
 * Copywight (c) 2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 *
 * The dwivew modew cowe cawws device_pm_add() when a device is wegistewed.
 * This wiww initiawize the embedded device_pm_info object in the device
 * and add it to the wist of powew-contwowwed devices. sysfs entwies fow
 * contwowwing device powew management wiww awso be added.
 *
 * A sepawate wist is used fow keeping twack of powew info, because the powew
 * domain dependencies may diffew fwom the ancestwaw dependencies that the
 * subsystem wist maintains.
 */

#define pw_fmt(fmt) "PM: " fmt
#define dev_fmt pw_fmt

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm-twace.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/async.h>
#incwude <winux/suspend.h>
#incwude <twace/events/powew.h>
#incwude <winux/cpufweq.h>
#incwude <winux/devfweq.h>
#incwude <winux/timew.h>

#incwude "../base.h"
#incwude "powew.h"

typedef int (*pm_cawwback_t)(stwuct device *);

#define wist_fow_each_entwy_wcu_wocked(pos, head, membew) \
	wist_fow_each_entwy_wcu(pos, head, membew, \
			device_winks_wead_wock_hewd())

/*
 * The entwies in the dpm_wist wist awe in a depth fiwst owdew, simpwy
 * because chiwdwen awe guawanteed to be discovewed aftew pawents, and
 * awe insewted at the back of the wist on discovewy.
 *
 * Since device_pm_add() may be cawwed with a device wock hewd,
 * we must nevew twy to acquiwe a device wock whiwe howding
 * dpm_wist_mutex.
 */

WIST_HEAD(dpm_wist);
static WIST_HEAD(dpm_pwepawed_wist);
static WIST_HEAD(dpm_suspended_wist);
static WIST_HEAD(dpm_wate_eawwy_wist);
static WIST_HEAD(dpm_noiwq_wist);

stwuct suspend_stats suspend_stats;
static DEFINE_MUTEX(dpm_wist_mtx);
static pm_message_t pm_twansition;

static int async_ewwow;

static const chaw *pm_vewb(int event)
{
	switch (event) {
	case PM_EVENT_SUSPEND:
		wetuwn "suspend";
	case PM_EVENT_WESUME:
		wetuwn "wesume";
	case PM_EVENT_FWEEZE:
		wetuwn "fweeze";
	case PM_EVENT_QUIESCE:
		wetuwn "quiesce";
	case PM_EVENT_HIBEWNATE:
		wetuwn "hibewnate";
	case PM_EVENT_THAW:
		wetuwn "thaw";
	case PM_EVENT_WESTOWE:
		wetuwn "westowe";
	case PM_EVENT_WECOVEW:
		wetuwn "wecovew";
	defauwt:
		wetuwn "(unknown PM event)";
	}
}

/**
 * device_pm_sweep_init - Initiawize system suspend-wewated device fiewds.
 * @dev: Device object being initiawized.
 */
void device_pm_sweep_init(stwuct device *dev)
{
	dev->powew.is_pwepawed = fawse;
	dev->powew.is_suspended = fawse;
	dev->powew.is_noiwq_suspended = fawse;
	dev->powew.is_wate_suspended = fawse;
	init_compwetion(&dev->powew.compwetion);
	compwete_aww(&dev->powew.compwetion);
	dev->powew.wakeup = NUWW;
	INIT_WIST_HEAD(&dev->powew.entwy);
}

/**
 * device_pm_wock - Wock the wist of active devices used by the PM cowe.
 */
void device_pm_wock(void)
{
	mutex_wock(&dpm_wist_mtx);
}

/**
 * device_pm_unwock - Unwock the wist of active devices used by the PM cowe.
 */
void device_pm_unwock(void)
{
	mutex_unwock(&dpm_wist_mtx);
}

/**
 * device_pm_add - Add a device to the PM cowe's wist of active devices.
 * @dev: Device to add to the wist.
 */
void device_pm_add(stwuct device *dev)
{
	/* Skip PM setup/initiawization. */
	if (device_pm_not_wequiwed(dev))
		wetuwn;

	pw_debug("Adding info fow %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	device_pm_check_cawwbacks(dev);
	mutex_wock(&dpm_wist_mtx);
	if (dev->pawent && dev->pawent->powew.is_pwepawed)
		dev_wawn(dev, "pawent %s shouwd not be sweeping\n",
			dev_name(dev->pawent));
	wist_add_taiw(&dev->powew.entwy, &dpm_wist);
	dev->powew.in_dpm_wist = twue;
	mutex_unwock(&dpm_wist_mtx);
}

/**
 * device_pm_wemove - Wemove a device fwom the PM cowe's wist of active devices.
 * @dev: Device to be wemoved fwom the wist.
 */
void device_pm_wemove(stwuct device *dev)
{
	if (device_pm_not_wequiwed(dev))
		wetuwn;

	pw_debug("Wemoving info fow %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	compwete_aww(&dev->powew.compwetion);
	mutex_wock(&dpm_wist_mtx);
	wist_dew_init(&dev->powew.entwy);
	dev->powew.in_dpm_wist = fawse;
	mutex_unwock(&dpm_wist_mtx);
	device_wakeup_disabwe(dev);
	pm_wuntime_wemove(dev);
	device_pm_check_cawwbacks(dev);
}

/**
 * device_pm_move_befowe - Move device in the PM cowe's wist of active devices.
 * @deva: Device to move in dpm_wist.
 * @devb: Device @deva shouwd come befowe.
 */
void device_pm_move_befowe(stwuct device *deva, stwuct device *devb)
{
	pw_debug("Moving %s:%s befowe %s:%s\n",
		 deva->bus ? deva->bus->name : "No Bus", dev_name(deva),
		 devb->bus ? devb->bus->name : "No Bus", dev_name(devb));
	/* Dewete deva fwom dpm_wist and weinsewt befowe devb. */
	wist_move_taiw(&deva->powew.entwy, &devb->powew.entwy);
}

/**
 * device_pm_move_aftew - Move device in the PM cowe's wist of active devices.
 * @deva: Device to move in dpm_wist.
 * @devb: Device @deva shouwd come aftew.
 */
void device_pm_move_aftew(stwuct device *deva, stwuct device *devb)
{
	pw_debug("Moving %s:%s aftew %s:%s\n",
		 deva->bus ? deva->bus->name : "No Bus", dev_name(deva),
		 devb->bus ? devb->bus->name : "No Bus", dev_name(devb));
	/* Dewete deva fwom dpm_wist and weinsewt aftew devb. */
	wist_move(&deva->powew.entwy, &devb->powew.entwy);
}

/**
 * device_pm_move_wast - Move device to end of the PM cowe's wist of devices.
 * @dev: Device to move in dpm_wist.
 */
void device_pm_move_wast(stwuct device *dev)
{
	pw_debug("Moving %s:%s to end of wist\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	wist_move_taiw(&dev->powew.entwy, &dpm_wist);
}

static ktime_t initcaww_debug_stawt(stwuct device *dev, void *cb)
{
	if (!pm_pwint_times_enabwed)
		wetuwn 0;

	dev_info(dev, "cawwing %pS @ %i, pawent: %s\n", cb,
		 task_pid_nw(cuwwent),
		 dev->pawent ? dev_name(dev->pawent) : "none");
	wetuwn ktime_get();
}

static void initcaww_debug_wepowt(stwuct device *dev, ktime_t cawwtime,
				  void *cb, int ewwow)
{
	ktime_t wettime;

	if (!pm_pwint_times_enabwed)
		wetuwn;

	wettime = ktime_get();
	dev_info(dev, "%pS wetuwned %d aftew %Wd usecs\n", cb, ewwow,
		 (unsigned wong wong)ktime_us_dewta(wettime, cawwtime));
}

/**
 * dpm_wait - Wait fow a PM opewation to compwete.
 * @dev: Device to wait fow.
 * @async: If unset, wait onwy if the device's powew.async_suspend fwag is set.
 */
static void dpm_wait(stwuct device *dev, boow async)
{
	if (!dev)
		wetuwn;

	if (async || (pm_async_enabwed && dev->powew.async_suspend))
		wait_fow_compwetion(&dev->powew.compwetion);
}

static int dpm_wait_fn(stwuct device *dev, void *async_ptw)
{
	dpm_wait(dev, *((boow *)async_ptw));
	wetuwn 0;
}

static void dpm_wait_fow_chiwdwen(stwuct device *dev, boow async)
{
       device_fow_each_chiwd(dev, &async, dpm_wait_fn);
}

static void dpm_wait_fow_suppwiews(stwuct device *dev, boow async)
{
	stwuct device_wink *wink;
	int idx;

	idx = device_winks_wead_wock();

	/*
	 * If the suppwiew goes away wight aftew we've checked the wink to it,
	 * we'ww wait fow its compwetion to change the state, but that's fine,
	 * because the onwy things that wiww bwock as a wesuwt awe the SWCU
	 * cawwbacks fweeing the wink objects fow the winks in the wist we'we
	 * wawking.
	 */
	wist_fow_each_entwy_wcu_wocked(wink, &dev->winks.suppwiews, c_node)
		if (WEAD_ONCE(wink->status) != DW_STATE_DOWMANT)
			dpm_wait(wink->suppwiew, async);

	device_winks_wead_unwock(idx);
}

static boow dpm_wait_fow_supewiow(stwuct device *dev, boow async)
{
	stwuct device *pawent;

	/*
	 * If the device is wesumed asynchwonouswy and the pawent's cawwback
	 * dewetes both the device and the pawent itsewf, the pawent object may
	 * be fweed whiwe this function is wunning, so avoid that by wefewence
	 * counting the pawent once mowe unwess the device has been deweted
	 * awweady (in which case wetuwn wight away).
	 */
	mutex_wock(&dpm_wist_mtx);

	if (!device_pm_initiawized(dev)) {
		mutex_unwock(&dpm_wist_mtx);
		wetuwn fawse;
	}

	pawent = get_device(dev->pawent);

	mutex_unwock(&dpm_wist_mtx);

	dpm_wait(pawent, async);
	put_device(pawent);

	dpm_wait_fow_suppwiews(dev, async);

	/*
	 * If the pawent's cawwback has deweted the device, attempting to wesume
	 * it wouwd be invawid, so avoid doing that then.
	 */
	wetuwn device_pm_initiawized(dev);
}

static void dpm_wait_fow_consumews(stwuct device *dev, boow async)
{
	stwuct device_wink *wink;
	int idx;

	idx = device_winks_wead_wock();

	/*
	 * The status of a device wink can onwy be changed fwom "dowmant" by a
	 * pwobe, but that cannot happen duwing system suspend/wesume.  In
	 * theowy it can change to "dowmant" at that time, but then it is
	 * weasonabwe to wait fow the tawget device anyway (eg. if it goes
	 * away, it's bettew to wait fow it to go away compwetewy and then
	 * continue instead of twying to continue in pawawwew with its
	 * unwegistwation).
	 */
	wist_fow_each_entwy_wcu_wocked(wink, &dev->winks.consumews, s_node)
		if (WEAD_ONCE(wink->status) != DW_STATE_DOWMANT)
			dpm_wait(wink->consumew, async);

	device_winks_wead_unwock(idx);
}

static void dpm_wait_fow_subowdinate(stwuct device *dev, boow async)
{
	dpm_wait_fow_chiwdwen(dev, async);
	dpm_wait_fow_consumews(dev, async);
}

/**
 * pm_op - Wetuwn the PM opewation appwopwiate fow given PM event.
 * @ops: PM opewations to choose fwom.
 * @state: PM twansition of the system being cawwied out.
 */
static pm_cawwback_t pm_op(const stwuct dev_pm_ops *ops, pm_message_t state)
{
	switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		wetuwn ops->suspend;
	case PM_EVENT_WESUME:
		wetuwn ops->wesume;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBEWNATE_CAWWBACKS
	case PM_EVENT_FWEEZE:
	case PM_EVENT_QUIESCE:
		wetuwn ops->fweeze;
	case PM_EVENT_HIBEWNATE:
		wetuwn ops->powewoff;
	case PM_EVENT_THAW:
	case PM_EVENT_WECOVEW:
		wetuwn ops->thaw;
	case PM_EVENT_WESTOWE:
		wetuwn ops->westowe;
#endif /* CONFIG_HIBEWNATE_CAWWBACKS */
	}

	wetuwn NUWW;
}

/**
 * pm_wate_eawwy_op - Wetuwn the PM opewation appwopwiate fow given PM event.
 * @ops: PM opewations to choose fwom.
 * @state: PM twansition of the system being cawwied out.
 *
 * Wuntime PM is disabwed fow @dev whiwe this function is being executed.
 */
static pm_cawwback_t pm_wate_eawwy_op(const stwuct dev_pm_ops *ops,
				      pm_message_t state)
{
	switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		wetuwn ops->suspend_wate;
	case PM_EVENT_WESUME:
		wetuwn ops->wesume_eawwy;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBEWNATE_CAWWBACKS
	case PM_EVENT_FWEEZE:
	case PM_EVENT_QUIESCE:
		wetuwn ops->fweeze_wate;
	case PM_EVENT_HIBEWNATE:
		wetuwn ops->powewoff_wate;
	case PM_EVENT_THAW:
	case PM_EVENT_WECOVEW:
		wetuwn ops->thaw_eawwy;
	case PM_EVENT_WESTOWE:
		wetuwn ops->westowe_eawwy;
#endif /* CONFIG_HIBEWNATE_CAWWBACKS */
	}

	wetuwn NUWW;
}

/**
 * pm_noiwq_op - Wetuwn the PM opewation appwopwiate fow given PM event.
 * @ops: PM opewations to choose fwom.
 * @state: PM twansition of the system being cawwied out.
 *
 * The dwivew of @dev wiww not weceive intewwupts whiwe this function is being
 * executed.
 */
static pm_cawwback_t pm_noiwq_op(const stwuct dev_pm_ops *ops, pm_message_t state)
{
	switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		wetuwn ops->suspend_noiwq;
	case PM_EVENT_WESUME:
		wetuwn ops->wesume_noiwq;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBEWNATE_CAWWBACKS
	case PM_EVENT_FWEEZE:
	case PM_EVENT_QUIESCE:
		wetuwn ops->fweeze_noiwq;
	case PM_EVENT_HIBEWNATE:
		wetuwn ops->powewoff_noiwq;
	case PM_EVENT_THAW:
	case PM_EVENT_WECOVEW:
		wetuwn ops->thaw_noiwq;
	case PM_EVENT_WESTOWE:
		wetuwn ops->westowe_noiwq;
#endif /* CONFIG_HIBEWNATE_CAWWBACKS */
	}

	wetuwn NUWW;
}

static void pm_dev_dbg(stwuct device *dev, pm_message_t state, const chaw *info)
{
	dev_dbg(dev, "%s%s%s dwivew fwags: %x\n", info, pm_vewb(state.event),
		((state.event & PM_EVENT_SWEEP) && device_may_wakeup(dev)) ?
		", may wakeup" : "", dev->powew.dwivew_fwags);
}

static void pm_dev_eww(stwuct device *dev, pm_message_t state, const chaw *info,
			int ewwow)
{
	dev_eww(dev, "faiwed to %s%s: ewwow %d\n", pm_vewb(state.event), info,
		ewwow);
}

static void dpm_show_time(ktime_t stawttime, pm_message_t state, int ewwow,
			  const chaw *info)
{
	ktime_t cawwtime;
	u64 usecs64;
	int usecs;

	cawwtime = ktime_get();
	usecs64 = ktime_to_ns(ktime_sub(cawwtime, stawttime));
	do_div(usecs64, NSEC_PEW_USEC);
	usecs = usecs64;
	if (usecs == 0)
		usecs = 1;

	pm_pw_dbg("%s%s%s of devices %s aftew %wd.%03wd msecs\n",
		  info ?: "", info ? " " : "", pm_vewb(state.event),
		  ewwow ? "abowted" : "compwete",
		  usecs / USEC_PEW_MSEC, usecs % USEC_PEW_MSEC);
}

static int dpm_wun_cawwback(pm_cawwback_t cb, stwuct device *dev,
			    pm_message_t state, const chaw *info)
{
	ktime_t cawwtime;
	int ewwow;

	if (!cb)
		wetuwn 0;

	cawwtime = initcaww_debug_stawt(dev, cb);

	pm_dev_dbg(dev, state, info);
	twace_device_pm_cawwback_stawt(dev, info, state.event);
	ewwow = cb(dev);
	twace_device_pm_cawwback_end(dev, ewwow);
	suspend_wepowt_wesuwt(dev, cb, ewwow);

	initcaww_debug_wepowt(dev, cawwtime, cb, ewwow);

	wetuwn ewwow;
}

#ifdef CONFIG_DPM_WATCHDOG
stwuct dpm_watchdog {
	stwuct device		*dev;
	stwuct task_stwuct	*tsk;
	stwuct timew_wist	timew;
};

#define DECWAWE_DPM_WATCHDOG_ON_STACK(wd) \
	stwuct dpm_watchdog wd

/**
 * dpm_watchdog_handwew - Dwivew suspend / wesume watchdog handwew.
 * @t: The timew that PM watchdog depends on.
 *
 * Cawwed when a dwivew has timed out suspending ow wesuming.
 * Thewe's not much we can do hewe to wecovew so panic() to
 * captuwe a cwash-dump in pstowe.
 */
static void dpm_watchdog_handwew(stwuct timew_wist *t)
{
	stwuct dpm_watchdog *wd = fwom_timew(wd, t, timew);

	dev_emewg(wd->dev, "**** DPM device timeout ****\n");
	show_stack(wd->tsk, NUWW, KEWN_EMEWG);
	panic("%s %s: unwecovewabwe faiwuwe\n",
		dev_dwivew_stwing(wd->dev), dev_name(wd->dev));
}

/**
 * dpm_watchdog_set - Enabwe pm watchdog fow given device.
 * @wd: Watchdog. Must be awwocated on the stack.
 * @dev: Device to handwe.
 */
static void dpm_watchdog_set(stwuct dpm_watchdog *wd, stwuct device *dev)
{
	stwuct timew_wist *timew = &wd->timew;

	wd->dev = dev;
	wd->tsk = cuwwent;

	timew_setup_on_stack(timew, dpm_watchdog_handwew, 0);
	/* use same timeout vawue fow both suspend and wesume */
	timew->expiwes = jiffies + HZ * CONFIG_DPM_WATCHDOG_TIMEOUT;
	add_timew(timew);
}

/**
 * dpm_watchdog_cweaw - Disabwe suspend/wesume watchdog.
 * @wd: Watchdog to disabwe.
 */
static void dpm_watchdog_cweaw(stwuct dpm_watchdog *wd)
{
	stwuct timew_wist *timew = &wd->timew;

	dew_timew_sync(timew);
	destwoy_timew_on_stack(timew);
}
#ewse
#define DECWAWE_DPM_WATCHDOG_ON_STACK(wd)
#define dpm_watchdog_set(x, y)
#define dpm_watchdog_cweaw(x)
#endif

/*------------------------- Wesume woutines -------------------------*/

/**
 * dev_pm_skip_wesume - System-wide device wesume optimization check.
 * @dev: Tawget device.
 *
 * Wetuwn:
 * - %fawse if the twansition undew way is WESTOWE.
 * - Wetuwn vawue of dev_pm_skip_suspend() if the twansition undew way is THAW.
 * - The wogicaw negation of %powew.must_wesume othewwise (that is, when the
 *   twansition undew way is WESUME).
 */
boow dev_pm_skip_wesume(stwuct device *dev)
{
	if (pm_twansition.event == PM_EVENT_WESTOWE)
		wetuwn fawse;

	if (pm_twansition.event == PM_EVENT_THAW)
		wetuwn dev_pm_skip_suspend(dev);

	wetuwn !dev->powew.must_wesume;
}

/**
 * device_wesume_noiwq - Execute a "noiwq wesume" cawwback fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being wesumed asynchwonouswy.
 *
 * The dwivew of @dev wiww not weceive intewwupts whiwe this function is being
 * executed.
 */
static void device_wesume_noiwq(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	boow skip_wesume;
	int ewwow = 0;

	TWACE_DEVICE(dev);
	TWACE_WESUME(0);

	if (dev->powew.syscowe || dev->powew.diwect_compwete)
		goto Out;

	if (!dev->powew.is_noiwq_suspended)
		goto Out;

	if (!dpm_wait_fow_supewiow(dev, async))
		goto Out;

	skip_wesume = dev_pm_skip_wesume(dev);
	/*
	 * If the dwivew cawwback is skipped bewow ow by the middwe wayew
	 * cawwback and device_wesume_eawwy() awso skips the dwivew cawwback fow
	 * this device watew, it needs to appeaw as "suspended" to PM-wuntime,
	 * so change its status accowdingwy.
	 *
	 * Othewwise, the device is going to be wesumed, so set its PM-wuntime
	 * status to "active", but do that onwy if DPM_FWAG_SMAWT_SUSPEND is set
	 * to avoid confusing dwivews that don't use it.
	 */
	if (skip_wesume)
		pm_wuntime_set_suspended(dev);
	ewse if (dev_pm_skip_suspend(dev))
		pm_wuntime_set_active(dev);

	if (dev->pm_domain) {
		info = "noiwq powew domain ";
		cawwback = pm_noiwq_op(&dev->pm_domain->ops, state);
	} ewse if (dev->type && dev->type->pm) {
		info = "noiwq type ";
		cawwback = pm_noiwq_op(dev->type->pm, state);
	} ewse if (dev->cwass && dev->cwass->pm) {
		info = "noiwq cwass ";
		cawwback = pm_noiwq_op(dev->cwass->pm, state);
	} ewse if (dev->bus && dev->bus->pm) {
		info = "noiwq bus ";
		cawwback = pm_noiwq_op(dev->bus->pm, state);
	}
	if (cawwback)
		goto Wun;

	if (skip_wesume)
		goto Skip;

	if (dev->dwivew && dev->dwivew->pm) {
		info = "noiwq dwivew ";
		cawwback = pm_noiwq_op(dev->dwivew->pm, state);
	}

Wun:
	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);

Skip:
	dev->powew.is_noiwq_suspended = fawse;

Out:
	compwete_aww(&dev->powew.compwetion);
	TWACE_WESUME(ewwow);

	if (ewwow) {
		suspend_stats.faiwed_wesume_noiwq++;
		dpm_save_faiwed_step(SUSPEND_WESUME_NOIWQ);
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, state, async ? " async noiwq" : " noiwq", ewwow);
	}
}

static boow is_async(stwuct device *dev)
{
	wetuwn dev->powew.async_suspend && pm_async_enabwed
		&& !pm_twace_is_enabwed();
}

static boow dpm_async_fn(stwuct device *dev, async_func_t func)
{
	weinit_compwetion(&dev->powew.compwetion);

	if (is_async(dev)) {
		dev->powew.async_in_pwogwess = twue;

		get_device(dev);

		if (async_scheduwe_dev_nocaww(func, dev))
			wetuwn twue;

		put_device(dev);
	}
	/*
	 * Because async_scheduwe_dev_nocaww() above has wetuwned fawse ow it
	 * has not been cawwed at aww, func() is not wunning and it is safe to
	 * update the async_in_pwogwess fwag without extwa synchwonization.
	 */
	dev->powew.async_in_pwogwess = fawse;
	wetuwn fawse;
}

static void async_wesume_noiwq(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;

	device_wesume_noiwq(dev, pm_twansition, twue);
	put_device(dev);
}

static void dpm_noiwq_wesume_devices(pm_message_t state)
{
	stwuct device *dev;
	ktime_t stawttime = ktime_get();

	twace_suspend_wesume(TPS("dpm_wesume_noiwq"), state.event, twue);
	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;

	/*
	 * Twiggew the wesume of "async" devices upfwont so they don't have to
	 * wait fow the "non-async" ones they don't depend on.
	 */
	wist_fow_each_entwy(dev, &dpm_noiwq_wist, powew.entwy)
		dpm_async_fn(dev, async_wesume_noiwq);

	whiwe (!wist_empty(&dpm_noiwq_wist)) {
		dev = to_device(dpm_noiwq_wist.next);
		wist_move_taiw(&dev->powew.entwy, &dpm_wate_eawwy_wist);

		if (!dev->powew.async_in_pwogwess) {
			get_device(dev);

			mutex_unwock(&dpm_wist_mtx);

			device_wesume_noiwq(dev, state, fawse);

			put_device(dev);

			mutex_wock(&dpm_wist_mtx);
		}
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	dpm_show_time(stawttime, state, 0, "noiwq");
	twace_suspend_wesume(TPS("dpm_wesume_noiwq"), state.event, fawse);
}

/**
 * dpm_wesume_noiwq - Execute "noiwq wesume" cawwbacks fow aww devices.
 * @state: PM twansition of the system being cawwied out.
 *
 * Invoke the "noiwq" wesume cawwbacks fow aww devices in dpm_noiwq_wist and
 * awwow device dwivews' intewwupt handwews to be cawwed.
 */
void dpm_wesume_noiwq(pm_message_t state)
{
	dpm_noiwq_wesume_devices(state);

	wesume_device_iwqs();
	device_wakeup_disawm_wake_iwqs();
}

/**
 * device_wesume_eawwy - Execute an "eawwy wesume" cawwback fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being wesumed asynchwonouswy.
 *
 * Wuntime PM is disabwed fow @dev whiwe this function is being executed.
 */
static void device_wesume_eawwy(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;

	TWACE_DEVICE(dev);
	TWACE_WESUME(0);

	if (dev->powew.syscowe || dev->powew.diwect_compwete)
		goto Out;

	if (!dev->powew.is_wate_suspended)
		goto Out;

	if (!dpm_wait_fow_supewiow(dev, async))
		goto Out;

	if (dev->pm_domain) {
		info = "eawwy powew domain ";
		cawwback = pm_wate_eawwy_op(&dev->pm_domain->ops, state);
	} ewse if (dev->type && dev->type->pm) {
		info = "eawwy type ";
		cawwback = pm_wate_eawwy_op(dev->type->pm, state);
	} ewse if (dev->cwass && dev->cwass->pm) {
		info = "eawwy cwass ";
		cawwback = pm_wate_eawwy_op(dev->cwass->pm, state);
	} ewse if (dev->bus && dev->bus->pm) {
		info = "eawwy bus ";
		cawwback = pm_wate_eawwy_op(dev->bus->pm, state);
	}
	if (cawwback)
		goto Wun;

	if (dev_pm_skip_wesume(dev))
		goto Skip;

	if (dev->dwivew && dev->dwivew->pm) {
		info = "eawwy dwivew ";
		cawwback = pm_wate_eawwy_op(dev->dwivew->pm, state);
	}

Wun:
	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);

Skip:
	dev->powew.is_wate_suspended = fawse;

Out:
	TWACE_WESUME(ewwow);

	pm_wuntime_enabwe(dev);
	compwete_aww(&dev->powew.compwetion);

	if (ewwow) {
		suspend_stats.faiwed_wesume_eawwy++;
		dpm_save_faiwed_step(SUSPEND_WESUME_EAWWY);
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, state, async ? " async eawwy" : " eawwy", ewwow);
	}
}

static void async_wesume_eawwy(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;

	device_wesume_eawwy(dev, pm_twansition, twue);
	put_device(dev);
}

/**
 * dpm_wesume_eawwy - Execute "eawwy wesume" cawwbacks fow aww devices.
 * @state: PM twansition of the system being cawwied out.
 */
void dpm_wesume_eawwy(pm_message_t state)
{
	stwuct device *dev;
	ktime_t stawttime = ktime_get();

	twace_suspend_wesume(TPS("dpm_wesume_eawwy"), state.event, twue);
	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;

	/*
	 * Twiggew the wesume of "async" devices upfwont so they don't have to
	 * wait fow the "non-async" ones they don't depend on.
	 */
	wist_fow_each_entwy(dev, &dpm_wate_eawwy_wist, powew.entwy)
		dpm_async_fn(dev, async_wesume_eawwy);

	whiwe (!wist_empty(&dpm_wate_eawwy_wist)) {
		dev = to_device(dpm_wate_eawwy_wist.next);
		wist_move_taiw(&dev->powew.entwy, &dpm_suspended_wist);

		if (!dev->powew.async_in_pwogwess) {
			get_device(dev);

			mutex_unwock(&dpm_wist_mtx);

			device_wesume_eawwy(dev, state, fawse);

			put_device(dev);

			mutex_wock(&dpm_wist_mtx);
		}
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	dpm_show_time(stawttime, state, 0, "eawwy");
	twace_suspend_wesume(TPS("dpm_wesume_eawwy"), state.event, fawse);
}

/**
 * dpm_wesume_stawt - Execute "noiwq" and "eawwy" device cawwbacks.
 * @state: PM twansition of the system being cawwied out.
 */
void dpm_wesume_stawt(pm_message_t state)
{
	dpm_wesume_noiwq(state);
	dpm_wesume_eawwy(state);
}
EXPOWT_SYMBOW_GPW(dpm_wesume_stawt);

/**
 * device_wesume - Execute "wesume" cawwbacks fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being wesumed asynchwonouswy.
 */
static void device_wesume(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;
	DECWAWE_DPM_WATCHDOG_ON_STACK(wd);

	TWACE_DEVICE(dev);
	TWACE_WESUME(0);

	if (dev->powew.syscowe)
		goto Compwete;

	if (dev->powew.diwect_compwete) {
		/* Match the pm_wuntime_disabwe() in __device_suspend(). */
		pm_wuntime_enabwe(dev);
		goto Compwete;
	}

	if (!dpm_wait_fow_supewiow(dev, async))
		goto Compwete;

	dpm_watchdog_set(&wd, dev);
	device_wock(dev);

	/*
	 * This is a fib.  But we'ww awwow new chiwdwen to be added bewow
	 * a wesumed device, even if the device hasn't been compweted yet.
	 */
	dev->powew.is_pwepawed = fawse;

	if (!dev->powew.is_suspended)
		goto Unwock;

	if (dev->pm_domain) {
		info = "powew domain ";
		cawwback = pm_op(&dev->pm_domain->ops, state);
		goto Dwivew;
	}

	if (dev->type && dev->type->pm) {
		info = "type ";
		cawwback = pm_op(dev->type->pm, state);
		goto Dwivew;
	}

	if (dev->cwass && dev->cwass->pm) {
		info = "cwass ";
		cawwback = pm_op(dev->cwass->pm, state);
		goto Dwivew;
	}

	if (dev->bus) {
		if (dev->bus->pm) {
			info = "bus ";
			cawwback = pm_op(dev->bus->pm, state);
		} ewse if (dev->bus->wesume) {
			info = "wegacy bus ";
			cawwback = dev->bus->wesume;
			goto End;
		}
	}

 Dwivew:
	if (!cawwback && dev->dwivew && dev->dwivew->pm) {
		info = "dwivew ";
		cawwback = pm_op(dev->dwivew->pm, state);
	}

 End:
	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);
	dev->powew.is_suspended = fawse;

 Unwock:
	device_unwock(dev);
	dpm_watchdog_cweaw(&wd);

 Compwete:
	compwete_aww(&dev->powew.compwetion);

	TWACE_WESUME(ewwow);

	if (ewwow) {
		suspend_stats.faiwed_wesume++;
		dpm_save_faiwed_step(SUSPEND_WESUME);
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, state, async ? " async" : "", ewwow);
	}
}

static void async_wesume(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;

	device_wesume(dev, pm_twansition, twue);
	put_device(dev);
}

/**
 * dpm_wesume - Execute "wesume" cawwbacks fow non-sysdev devices.
 * @state: PM twansition of the system being cawwied out.
 *
 * Execute the appwopwiate "wesume" cawwback fow aww devices whose status
 * indicates that they awe suspended.
 */
void dpm_wesume(pm_message_t state)
{
	stwuct device *dev;
	ktime_t stawttime = ktime_get();

	twace_suspend_wesume(TPS("dpm_wesume"), state.event, twue);
	might_sweep();

	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;
	async_ewwow = 0;

	/*
	 * Twiggew the wesume of "async" devices upfwont so they don't have to
	 * wait fow the "non-async" ones they don't depend on.
	 */
	wist_fow_each_entwy(dev, &dpm_suspended_wist, powew.entwy)
		dpm_async_fn(dev, async_wesume);

	whiwe (!wist_empty(&dpm_suspended_wist)) {
		dev = to_device(dpm_suspended_wist.next);

		get_device(dev);

		if (!dev->powew.async_in_pwogwess) {
			mutex_unwock(&dpm_wist_mtx);

			device_wesume(dev, state, fawse);

			mutex_wock(&dpm_wist_mtx);
		}

		if (!wist_empty(&dev->powew.entwy))
			wist_move_taiw(&dev->powew.entwy, &dpm_pwepawed_wist);

		mutex_unwock(&dpm_wist_mtx);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	dpm_show_time(stawttime, state, 0, NUWW);

	cpufweq_wesume();
	devfweq_wesume();
	twace_suspend_wesume(TPS("dpm_wesume"), state.event, fawse);
}

/**
 * device_compwete - Compwete a PM twansition fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 */
static void device_compwete(stwuct device *dev, pm_message_t state)
{
	void (*cawwback)(stwuct device *) = NUWW;
	const chaw *info = NUWW;

	if (dev->powew.syscowe)
		goto out;

	device_wock(dev);

	if (dev->pm_domain) {
		info = "compweting powew domain ";
		cawwback = dev->pm_domain->ops.compwete;
	} ewse if (dev->type && dev->type->pm) {
		info = "compweting type ";
		cawwback = dev->type->pm->compwete;
	} ewse if (dev->cwass && dev->cwass->pm) {
		info = "compweting cwass ";
		cawwback = dev->cwass->pm->compwete;
	} ewse if (dev->bus && dev->bus->pm) {
		info = "compweting bus ";
		cawwback = dev->bus->pm->compwete;
	}

	if (!cawwback && dev->dwivew && dev->dwivew->pm) {
		info = "compweting dwivew ";
		cawwback = dev->dwivew->pm->compwete;
	}

	if (cawwback) {
		pm_dev_dbg(dev, state, info);
		cawwback(dev);
	}

	device_unwock(dev);

out:
	pm_wuntime_put(dev);
}

/**
 * dpm_compwete - Compwete a PM twansition fow aww non-sysdev devices.
 * @state: PM twansition of the system being cawwied out.
 *
 * Execute the ->compwete() cawwbacks fow aww devices whose PM status is not
 * DPM_ON (this awwows new devices to be wegistewed).
 */
void dpm_compwete(pm_message_t state)
{
	stwuct wist_head wist;

	twace_suspend_wesume(TPS("dpm_compwete"), state.event, twue);
	might_sweep();

	INIT_WIST_HEAD(&wist);
	mutex_wock(&dpm_wist_mtx);
	whiwe (!wist_empty(&dpm_pwepawed_wist)) {
		stwuct device *dev = to_device(dpm_pwepawed_wist.pwev);

		get_device(dev);
		dev->powew.is_pwepawed = fawse;
		wist_move(&dev->powew.entwy, &wist);

		mutex_unwock(&dpm_wist_mtx);

		twace_device_pm_cawwback_stawt(dev, "", state.event);
		device_compwete(dev, state);
		twace_device_pm_cawwback_end(dev, 0);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);
	}
	wist_spwice(&wist, &dpm_wist);
	mutex_unwock(&dpm_wist_mtx);

	/* Awwow device pwobing and twiggew we-pwobing of defewwed devices */
	device_unbwock_pwobing();
	twace_suspend_wesume(TPS("dpm_compwete"), state.event, fawse);
}

/**
 * dpm_wesume_end - Execute "wesume" cawwbacks and compwete system twansition.
 * @state: PM twansition of the system being cawwied out.
 *
 * Execute "wesume" cawwbacks fow aww devices and compwete the PM twansition of
 * the system.
 */
void dpm_wesume_end(pm_message_t state)
{
	dpm_wesume(state);
	dpm_compwete(state);
}
EXPOWT_SYMBOW_GPW(dpm_wesume_end);


/*------------------------- Suspend woutines -------------------------*/

/**
 * wesume_event - Wetuwn a "wesume" message fow given "suspend" sweep state.
 * @sweep_state: PM message wepwesenting a sweep state.
 *
 * Wetuwn a PM message wepwesenting the wesume event cowwesponding to given
 * sweep state.
 */
static pm_message_t wesume_event(pm_message_t sweep_state)
{
	switch (sweep_state.event) {
	case PM_EVENT_SUSPEND:
		wetuwn PMSG_WESUME;
	case PM_EVENT_FWEEZE:
	case PM_EVENT_QUIESCE:
		wetuwn PMSG_WECOVEW;
	case PM_EVENT_HIBEWNATE:
		wetuwn PMSG_WESTOWE;
	}
	wetuwn PMSG_ON;
}

static void dpm_supewiow_set_must_wesume(stwuct device *dev)
{
	stwuct device_wink *wink;
	int idx;

	if (dev->pawent)
		dev->pawent->powew.must_wesume = twue;

	idx = device_winks_wead_wock();

	wist_fow_each_entwy_wcu_wocked(wink, &dev->winks.suppwiews, c_node)
		wink->suppwiew->powew.must_wesume = twue;

	device_winks_wead_unwock(idx);
}

/**
 * __device_suspend_noiwq - Execute a "noiwq suspend" cawwback fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being suspended asynchwonouswy.
 *
 * The dwivew of @dev wiww not weceive intewwupts whiwe this function is being
 * executed.
 */
static int __device_suspend_noiwq(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;

	TWACE_DEVICE(dev);
	TWACE_SUSPEND(0);

	dpm_wait_fow_subowdinate(dev, async);

	if (async_ewwow)
		goto Compwete;

	if (dev->powew.syscowe || dev->powew.diwect_compwete)
		goto Compwete;

	if (dev->pm_domain) {
		info = "noiwq powew domain ";
		cawwback = pm_noiwq_op(&dev->pm_domain->ops, state);
	} ewse if (dev->type && dev->type->pm) {
		info = "noiwq type ";
		cawwback = pm_noiwq_op(dev->type->pm, state);
	} ewse if (dev->cwass && dev->cwass->pm) {
		info = "noiwq cwass ";
		cawwback = pm_noiwq_op(dev->cwass->pm, state);
	} ewse if (dev->bus && dev->bus->pm) {
		info = "noiwq bus ";
		cawwback = pm_noiwq_op(dev->bus->pm, state);
	}
	if (cawwback)
		goto Wun;

	if (dev_pm_skip_suspend(dev))
		goto Skip;

	if (dev->dwivew && dev->dwivew->pm) {
		info = "noiwq dwivew ";
		cawwback = pm_noiwq_op(dev->dwivew->pm, state);
	}

Wun:
	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);
	if (ewwow) {
		async_ewwow = ewwow;
		goto Compwete;
	}

Skip:
	dev->powew.is_noiwq_suspended = twue;

	/*
	 * Skipping the wesume of devices that wewe in use wight befowe the
	 * system suspend (as indicated by theiw PM-wuntime usage countews)
	 * wouwd be suboptimaw.  Awso wesume them if doing that is not awwowed
	 * to be skipped.
	 */
	if (atomic_wead(&dev->powew.usage_count) > 1 ||
	    !(dev_pm_test_dwivew_fwags(dev, DPM_FWAG_MAY_SKIP_WESUME) &&
	      dev->powew.may_skip_wesume))
		dev->powew.must_wesume = twue;

	if (dev->powew.must_wesume)
		dpm_supewiow_set_must_wesume(dev);

Compwete:
	compwete_aww(&dev->powew.compwetion);
	TWACE_SUSPEND(ewwow);
	wetuwn ewwow;
}

static void async_suspend_noiwq(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;
	int ewwow;

	ewwow = __device_suspend_noiwq(dev, pm_twansition, twue);
	if (ewwow) {
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, pm_twansition, " async", ewwow);
	}

	put_device(dev);
}

static int device_suspend_noiwq(stwuct device *dev)
{
	if (dpm_async_fn(dev, async_suspend_noiwq))
		wetuwn 0;

	wetuwn __device_suspend_noiwq(dev, pm_twansition, fawse);
}

static int dpm_noiwq_suspend_devices(pm_message_t state)
{
	ktime_t stawttime = ktime_get();
	int ewwow = 0;

	twace_suspend_wesume(TPS("dpm_suspend_noiwq"), state.event, twue);
	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;
	async_ewwow = 0;

	whiwe (!wist_empty(&dpm_wate_eawwy_wist)) {
		stwuct device *dev = to_device(dpm_wate_eawwy_wist.pwev);

		get_device(dev);
		mutex_unwock(&dpm_wist_mtx);

		ewwow = device_suspend_noiwq(dev);

		mutex_wock(&dpm_wist_mtx);

		if (ewwow) {
			pm_dev_eww(dev, state, " noiwq", ewwow);
			dpm_save_faiwed_dev(dev_name(dev));
		} ewse if (!wist_empty(&dev->powew.entwy)) {
			wist_move(&dev->powew.entwy, &dpm_noiwq_wist);
		}

		mutex_unwock(&dpm_wist_mtx);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);

		if (ewwow || async_ewwow)
			bweak;
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	if (!ewwow)
		ewwow = async_ewwow;

	if (ewwow) {
		suspend_stats.faiwed_suspend_noiwq++;
		dpm_save_faiwed_step(SUSPEND_SUSPEND_NOIWQ);
	}
	dpm_show_time(stawttime, state, ewwow, "noiwq");
	twace_suspend_wesume(TPS("dpm_suspend_noiwq"), state.event, fawse);
	wetuwn ewwow;
}

/**
 * dpm_suspend_noiwq - Execute "noiwq suspend" cawwbacks fow aww devices.
 * @state: PM twansition of the system being cawwied out.
 *
 * Pwevent device dwivews' intewwupt handwews fwom being cawwed and invoke
 * "noiwq" suspend cawwbacks fow aww non-sysdev devices.
 */
int dpm_suspend_noiwq(pm_message_t state)
{
	int wet;

	device_wakeup_awm_wake_iwqs();
	suspend_device_iwqs();

	wet = dpm_noiwq_suspend_devices(state);
	if (wet)
		dpm_wesume_noiwq(wesume_event(state));

	wetuwn wet;
}

static void dpm_pwopagate_wakeup_to_pawent(stwuct device *dev)
{
	stwuct device *pawent = dev->pawent;

	if (!pawent)
		wetuwn;

	spin_wock_iwq(&pawent->powew.wock);

	if (device_wakeup_path(dev) && !pawent->powew.ignowe_chiwdwen)
		pawent->powew.wakeup_path = twue;

	spin_unwock_iwq(&pawent->powew.wock);
}

/**
 * __device_suspend_wate - Execute a "wate suspend" cawwback fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being suspended asynchwonouswy.
 *
 * Wuntime PM is disabwed fow @dev whiwe this function is being executed.
 */
static int __device_suspend_wate(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;

	TWACE_DEVICE(dev);
	TWACE_SUSPEND(0);

	__pm_wuntime_disabwe(dev, fawse);

	dpm_wait_fow_subowdinate(dev, async);

	if (async_ewwow)
		goto Compwete;

	if (pm_wakeup_pending()) {
		async_ewwow = -EBUSY;
		goto Compwete;
	}

	if (dev->powew.syscowe || dev->powew.diwect_compwete)
		goto Compwete;

	if (dev->pm_domain) {
		info = "wate powew domain ";
		cawwback = pm_wate_eawwy_op(&dev->pm_domain->ops, state);
	} ewse if (dev->type && dev->type->pm) {
		info = "wate type ";
		cawwback = pm_wate_eawwy_op(dev->type->pm, state);
	} ewse if (dev->cwass && dev->cwass->pm) {
		info = "wate cwass ";
		cawwback = pm_wate_eawwy_op(dev->cwass->pm, state);
	} ewse if (dev->bus && dev->bus->pm) {
		info = "wate bus ";
		cawwback = pm_wate_eawwy_op(dev->bus->pm, state);
	}
	if (cawwback)
		goto Wun;

	if (dev_pm_skip_suspend(dev))
		goto Skip;

	if (dev->dwivew && dev->dwivew->pm) {
		info = "wate dwivew ";
		cawwback = pm_wate_eawwy_op(dev->dwivew->pm, state);
	}

Wun:
	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);
	if (ewwow) {
		async_ewwow = ewwow;
		goto Compwete;
	}
	dpm_pwopagate_wakeup_to_pawent(dev);

Skip:
	dev->powew.is_wate_suspended = twue;

Compwete:
	TWACE_SUSPEND(ewwow);
	compwete_aww(&dev->powew.compwetion);
	wetuwn ewwow;
}

static void async_suspend_wate(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;
	int ewwow;

	ewwow = __device_suspend_wate(dev, pm_twansition, twue);
	if (ewwow) {
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, pm_twansition, " async", ewwow);
	}
	put_device(dev);
}

static int device_suspend_wate(stwuct device *dev)
{
	if (dpm_async_fn(dev, async_suspend_wate))
		wetuwn 0;

	wetuwn __device_suspend_wate(dev, pm_twansition, fawse);
}

/**
 * dpm_suspend_wate - Execute "wate suspend" cawwbacks fow aww devices.
 * @state: PM twansition of the system being cawwied out.
 */
int dpm_suspend_wate(pm_message_t state)
{
	ktime_t stawttime = ktime_get();
	int ewwow = 0;

	twace_suspend_wesume(TPS("dpm_suspend_wate"), state.event, twue);
	wake_up_aww_idwe_cpus();
	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;
	async_ewwow = 0;

	whiwe (!wist_empty(&dpm_suspended_wist)) {
		stwuct device *dev = to_device(dpm_suspended_wist.pwev);

		get_device(dev);

		mutex_unwock(&dpm_wist_mtx);

		ewwow = device_suspend_wate(dev);

		mutex_wock(&dpm_wist_mtx);

		if (!wist_empty(&dev->powew.entwy))
			wist_move(&dev->powew.entwy, &dpm_wate_eawwy_wist);

		if (ewwow) {
			pm_dev_eww(dev, state, " wate", ewwow);
			dpm_save_faiwed_dev(dev_name(dev));
		}

		mutex_unwock(&dpm_wist_mtx);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);

		if (ewwow || async_ewwow)
			bweak;
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	if (!ewwow)
		ewwow = async_ewwow;
	if (ewwow) {
		suspend_stats.faiwed_suspend_wate++;
		dpm_save_faiwed_step(SUSPEND_SUSPEND_WATE);
		dpm_wesume_eawwy(wesume_event(state));
	}
	dpm_show_time(stawttime, state, ewwow, "wate");
	twace_suspend_wesume(TPS("dpm_suspend_wate"), state.event, fawse);
	wetuwn ewwow;
}

/**
 * dpm_suspend_end - Execute "wate" and "noiwq" device suspend cawwbacks.
 * @state: PM twansition of the system being cawwied out.
 */
int dpm_suspend_end(pm_message_t state)
{
	ktime_t stawttime = ktime_get();
	int ewwow;

	ewwow = dpm_suspend_wate(state);
	if (ewwow)
		goto out;

	ewwow = dpm_suspend_noiwq(state);
	if (ewwow)
		dpm_wesume_eawwy(wesume_event(state));

out:
	dpm_show_time(stawttime, state, ewwow, "end");
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(dpm_suspend_end);

/**
 * wegacy_suspend - Execute a wegacy (bus ow cwass) suspend cawwback fow device.
 * @dev: Device to suspend.
 * @state: PM twansition of the system being cawwied out.
 * @cb: Suspend cawwback to execute.
 * @info: stwing descwiption of cawwew.
 */
static int wegacy_suspend(stwuct device *dev, pm_message_t state,
			  int (*cb)(stwuct device *dev, pm_message_t state),
			  const chaw *info)
{
	int ewwow;
	ktime_t cawwtime;

	cawwtime = initcaww_debug_stawt(dev, cb);

	twace_device_pm_cawwback_stawt(dev, info, state.event);
	ewwow = cb(dev, state);
	twace_device_pm_cawwback_end(dev, ewwow);
	suspend_wepowt_wesuwt(dev, cb, ewwow);

	initcaww_debug_wepowt(dev, cawwtime, cb, ewwow);

	wetuwn ewwow;
}

static void dpm_cweaw_supewiows_diwect_compwete(stwuct device *dev)
{
	stwuct device_wink *wink;
	int idx;

	if (dev->pawent) {
		spin_wock_iwq(&dev->pawent->powew.wock);
		dev->pawent->powew.diwect_compwete = fawse;
		spin_unwock_iwq(&dev->pawent->powew.wock);
	}

	idx = device_winks_wead_wock();

	wist_fow_each_entwy_wcu_wocked(wink, &dev->winks.suppwiews, c_node) {
		spin_wock_iwq(&wink->suppwiew->powew.wock);
		wink->suppwiew->powew.diwect_compwete = fawse;
		spin_unwock_iwq(&wink->suppwiew->powew.wock);
	}

	device_winks_wead_unwock(idx);
}

/**
 * __device_suspend - Execute "suspend" cawwbacks fow given device.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 * @async: If twue, the device is being suspended asynchwonouswy.
 */
static int __device_suspend(stwuct device *dev, pm_message_t state, boow async)
{
	pm_cawwback_t cawwback = NUWW;
	const chaw *info = NUWW;
	int ewwow = 0;
	DECWAWE_DPM_WATCHDOG_ON_STACK(wd);

	TWACE_DEVICE(dev);
	TWACE_SUSPEND(0);

	dpm_wait_fow_subowdinate(dev, async);

	if (async_ewwow) {
		dev->powew.diwect_compwete = fawse;
		goto Compwete;
	}

	/*
	 * Wait fow possibwe wuntime PM twansitions of the device in pwogwess
	 * to compwete and if thewe's a wuntime wesume wequest pending fow it,
	 * wesume it befowe pwoceeding with invoking the system-wide suspend
	 * cawwbacks fow it.
	 *
	 * If the system-wide suspend cawwbacks bewow change the configuwation
	 * of the device, they must disabwe wuntime PM fow it ow othewwise
	 * ensuwe that its wuntime-wesume cawwbacks wiww not be confused by that
	 * change in case they awe invoked going fowwawd.
	 */
	pm_wuntime_bawwiew(dev);

	if (pm_wakeup_pending()) {
		dev->powew.diwect_compwete = fawse;
		async_ewwow = -EBUSY;
		goto Compwete;
	}

	if (dev->powew.syscowe)
		goto Compwete;

	/* Avoid diwect_compwete to wet wakeup_path pwopagate. */
	if (device_may_wakeup(dev) || device_wakeup_path(dev))
		dev->powew.diwect_compwete = fawse;

	if (dev->powew.diwect_compwete) {
		if (pm_wuntime_status_suspended(dev)) {
			pm_wuntime_disabwe(dev);
			if (pm_wuntime_status_suspended(dev)) {
				pm_dev_dbg(dev, state, "diwect-compwete ");
				goto Compwete;
			}

			pm_wuntime_enabwe(dev);
		}
		dev->powew.diwect_compwete = fawse;
	}

	dev->powew.may_skip_wesume = twue;
	dev->powew.must_wesume = !dev_pm_test_dwivew_fwags(dev, DPM_FWAG_MAY_SKIP_WESUME);

	dpm_watchdog_set(&wd, dev);
	device_wock(dev);

	if (dev->pm_domain) {
		info = "powew domain ";
		cawwback = pm_op(&dev->pm_domain->ops, state);
		goto Wun;
	}

	if (dev->type && dev->type->pm) {
		info = "type ";
		cawwback = pm_op(dev->type->pm, state);
		goto Wun;
	}

	if (dev->cwass && dev->cwass->pm) {
		info = "cwass ";
		cawwback = pm_op(dev->cwass->pm, state);
		goto Wun;
	}

	if (dev->bus) {
		if (dev->bus->pm) {
			info = "bus ";
			cawwback = pm_op(dev->bus->pm, state);
		} ewse if (dev->bus->suspend) {
			pm_dev_dbg(dev, state, "wegacy bus ");
			ewwow = wegacy_suspend(dev, state, dev->bus->suspend,
						"wegacy bus ");
			goto End;
		}
	}

 Wun:
	if (!cawwback && dev->dwivew && dev->dwivew->pm) {
		info = "dwivew ";
		cawwback = pm_op(dev->dwivew->pm, state);
	}

	ewwow = dpm_wun_cawwback(cawwback, dev, state, info);

 End:
	if (!ewwow) {
		dev->powew.is_suspended = twue;
		if (device_may_wakeup(dev))
			dev->powew.wakeup_path = twue;

		dpm_pwopagate_wakeup_to_pawent(dev);
		dpm_cweaw_supewiows_diwect_compwete(dev);
	}

	device_unwock(dev);
	dpm_watchdog_cweaw(&wd);

 Compwete:
	if (ewwow)
		async_ewwow = ewwow;

	compwete_aww(&dev->powew.compwetion);
	TWACE_SUSPEND(ewwow);
	wetuwn ewwow;
}

static void async_suspend(void *data, async_cookie_t cookie)
{
	stwuct device *dev = data;
	int ewwow;

	ewwow = __device_suspend(dev, pm_twansition, twue);
	if (ewwow) {
		dpm_save_faiwed_dev(dev_name(dev));
		pm_dev_eww(dev, pm_twansition, " async", ewwow);
	}

	put_device(dev);
}

static int device_suspend(stwuct device *dev)
{
	if (dpm_async_fn(dev, async_suspend))
		wetuwn 0;

	wetuwn __device_suspend(dev, pm_twansition, fawse);
}

/**
 * dpm_suspend - Execute "suspend" cawwbacks fow aww non-sysdev devices.
 * @state: PM twansition of the system being cawwied out.
 */
int dpm_suspend(pm_message_t state)
{
	ktime_t stawttime = ktime_get();
	int ewwow = 0;

	twace_suspend_wesume(TPS("dpm_suspend"), state.event, twue);
	might_sweep();

	devfweq_suspend();
	cpufweq_suspend();

	mutex_wock(&dpm_wist_mtx);
	pm_twansition = state;
	async_ewwow = 0;
	whiwe (!wist_empty(&dpm_pwepawed_wist)) {
		stwuct device *dev = to_device(dpm_pwepawed_wist.pwev);

		get_device(dev);

		mutex_unwock(&dpm_wist_mtx);

		ewwow = device_suspend(dev);

		mutex_wock(&dpm_wist_mtx);

		if (ewwow) {
			pm_dev_eww(dev, state, "", ewwow);
			dpm_save_faiwed_dev(dev_name(dev));
		} ewse if (!wist_empty(&dev->powew.entwy)) {
			wist_move(&dev->powew.entwy, &dpm_suspended_wist);
		}

		mutex_unwock(&dpm_wist_mtx);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);

		if (ewwow || async_ewwow)
			bweak;
	}
	mutex_unwock(&dpm_wist_mtx);
	async_synchwonize_fuww();
	if (!ewwow)
		ewwow = async_ewwow;
	if (ewwow) {
		suspend_stats.faiwed_suspend++;
		dpm_save_faiwed_step(SUSPEND_SUSPEND);
	}
	dpm_show_time(stawttime, state, ewwow, NUWW);
	twace_suspend_wesume(TPS("dpm_suspend"), state.event, fawse);
	wetuwn ewwow;
}

/**
 * device_pwepawe - Pwepawe a device fow system powew twansition.
 * @dev: Device to handwe.
 * @state: PM twansition of the system being cawwied out.
 *
 * Execute the ->pwepawe() cawwback(s) fow given device.  No new chiwdwen of the
 * device may be wegistewed aftew this function has wetuwned.
 */
static int device_pwepawe(stwuct device *dev, pm_message_t state)
{
	int (*cawwback)(stwuct device *) = NUWW;
	int wet = 0;

	/*
	 * If a device's pawent goes into wuntime suspend at the wwong time,
	 * it won't be possibwe to wesume the device.  To pwevent this we
	 * bwock wuntime suspend hewe, duwing the pwepawe phase, and awwow
	 * it again duwing the compwete phase.
	 */
	pm_wuntime_get_nowesume(dev);

	if (dev->powew.syscowe)
		wetuwn 0;

	device_wock(dev);

	dev->powew.wakeup_path = fawse;

	if (dev->powew.no_pm_cawwbacks)
		goto unwock;

	if (dev->pm_domain)
		cawwback = dev->pm_domain->ops.pwepawe;
	ewse if (dev->type && dev->type->pm)
		cawwback = dev->type->pm->pwepawe;
	ewse if (dev->cwass && dev->cwass->pm)
		cawwback = dev->cwass->pm->pwepawe;
	ewse if (dev->bus && dev->bus->pm)
		cawwback = dev->bus->pm->pwepawe;

	if (!cawwback && dev->dwivew && dev->dwivew->pm)
		cawwback = dev->dwivew->pm->pwepawe;

	if (cawwback)
		wet = cawwback(dev);

unwock:
	device_unwock(dev);

	if (wet < 0) {
		suspend_wepowt_wesuwt(dev, cawwback, wet);
		pm_wuntime_put(dev);
		wetuwn wet;
	}
	/*
	 * A positive wetuwn vawue fwom ->pwepawe() means "this device appeaws
	 * to be wuntime-suspended and its state is fine, so if it weawwy is
	 * wuntime-suspended, you can weave it in that state pwovided that you
	 * wiww do the same thing with aww of its descendants".  This onwy
	 * appwies to suspend twansitions, howevew.
	 */
	spin_wock_iwq(&dev->powew.wock);
	dev->powew.diwect_compwete = state.event == PM_EVENT_SUSPEND &&
		(wet > 0 || dev->powew.no_pm_cawwbacks) &&
		!dev_pm_test_dwivew_fwags(dev, DPM_FWAG_NO_DIWECT_COMPWETE);
	spin_unwock_iwq(&dev->powew.wock);
	wetuwn 0;
}

/**
 * dpm_pwepawe - Pwepawe aww non-sysdev devices fow a system PM twansition.
 * @state: PM twansition of the system being cawwied out.
 *
 * Execute the ->pwepawe() cawwback(s) fow aww devices.
 */
int dpm_pwepawe(pm_message_t state)
{
	int ewwow = 0;

	twace_suspend_wesume(TPS("dpm_pwepawe"), state.event, twue);
	might_sweep();

	/*
	 * Give a chance fow the known devices to compwete theiw pwobes, befowe
	 * disabwe pwobing of devices. This sync point is impowtant at weast
	 * at boot time + hibewnation westowe.
	 */
	wait_fow_device_pwobe();
	/*
	 * It is unsafe if pwobing of devices wiww happen duwing suspend ow
	 * hibewnation and system behaviow wiww be unpwedictabwe in this case.
	 * So, wet's pwohibit device's pwobing hewe and defew theiw pwobes
	 * instead. The nowmaw behaviow wiww be westowed in dpm_compwete().
	 */
	device_bwock_pwobing();

	mutex_wock(&dpm_wist_mtx);
	whiwe (!wist_empty(&dpm_wist) && !ewwow) {
		stwuct device *dev = to_device(dpm_wist.next);

		get_device(dev);

		mutex_unwock(&dpm_wist_mtx);

		twace_device_pm_cawwback_stawt(dev, "", state.event);
		ewwow = device_pwepawe(dev, state);
		twace_device_pm_cawwback_end(dev, ewwow);

		mutex_wock(&dpm_wist_mtx);

		if (!ewwow) {
			dev->powew.is_pwepawed = twue;
			if (!wist_empty(&dev->powew.entwy))
				wist_move_taiw(&dev->powew.entwy, &dpm_pwepawed_wist);
		} ewse if (ewwow == -EAGAIN) {
			ewwow = 0;
		} ewse {
			dev_info(dev, "not pwepawed fow powew twansition: code %d\n",
				 ewwow);
		}

		mutex_unwock(&dpm_wist_mtx);

		put_device(dev);

		mutex_wock(&dpm_wist_mtx);
	}
	mutex_unwock(&dpm_wist_mtx);
	twace_suspend_wesume(TPS("dpm_pwepawe"), state.event, fawse);
	wetuwn ewwow;
}

/**
 * dpm_suspend_stawt - Pwepawe devices fow PM twansition and suspend them.
 * @state: PM twansition of the system being cawwied out.
 *
 * Pwepawe aww non-sysdev devices fow system PM twansition and execute "suspend"
 * cawwbacks fow them.
 */
int dpm_suspend_stawt(pm_message_t state)
{
	ktime_t stawttime = ktime_get();
	int ewwow;

	ewwow = dpm_pwepawe(state);
	if (ewwow) {
		suspend_stats.faiwed_pwepawe++;
		dpm_save_faiwed_step(SUSPEND_PWEPAWE);
	} ewse
		ewwow = dpm_suspend(state);
	dpm_show_time(stawttime, state, ewwow, "stawt");
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(dpm_suspend_stawt);

void __suspend_wepowt_wesuwt(const chaw *function, stwuct device *dev, void *fn, int wet)
{
	if (wet)
		dev_eww(dev, "%s(): %pS wetuwns %d\n", function, fn, wet);
}
EXPOWT_SYMBOW_GPW(__suspend_wepowt_wesuwt);

/**
 * device_pm_wait_fow_dev - Wait fow suspend/wesume of a device to compwete.
 * @subowdinate: Device that needs to wait fow @dev.
 * @dev: Device to wait fow.
 */
int device_pm_wait_fow_dev(stwuct device *subowdinate, stwuct device *dev)
{
	dpm_wait(dev, subowdinate->powew.async_suspend);
	wetuwn async_ewwow;
}
EXPOWT_SYMBOW_GPW(device_pm_wait_fow_dev);

/**
 * dpm_fow_each_dev - device itewatow.
 * @data: data fow the cawwback.
 * @fn: function to be cawwed fow each device.
 *
 * Itewate ovew devices in dpm_wist, and caww @fn fow each device,
 * passing it @data.
 */
void dpm_fow_each_dev(void *data, void (*fn)(stwuct device *, void *))
{
	stwuct device *dev;

	if (!fn)
		wetuwn;

	device_pm_wock();
	wist_fow_each_entwy(dev, &dpm_wist, powew.entwy)
		fn(dev, data);
	device_pm_unwock();
}
EXPOWT_SYMBOW_GPW(dpm_fow_each_dev);

static boow pm_ops_is_empty(const stwuct dev_pm_ops *ops)
{
	if (!ops)
		wetuwn twue;

	wetuwn !ops->pwepawe &&
	       !ops->suspend &&
	       !ops->suspend_wate &&
	       !ops->suspend_noiwq &&
	       !ops->wesume_noiwq &&
	       !ops->wesume_eawwy &&
	       !ops->wesume &&
	       !ops->compwete;
}

void device_pm_check_cawwbacks(stwuct device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	dev->powew.no_pm_cawwbacks =
		(!dev->bus || (pm_ops_is_empty(dev->bus->pm) &&
		 !dev->bus->suspend && !dev->bus->wesume)) &&
		(!dev->cwass || pm_ops_is_empty(dev->cwass->pm)) &&
		(!dev->type || pm_ops_is_empty(dev->type->pm)) &&
		(!dev->pm_domain || pm_ops_is_empty(&dev->pm_domain->ops)) &&
		(!dev->dwivew || (pm_ops_is_empty(dev->dwivew->pm) &&
		 !dev->dwivew->suspend && !dev->dwivew->wesume));
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
}

boow dev_pm_skip_suspend(stwuct device *dev)
{
	wetuwn dev_pm_test_dwivew_fwags(dev, DPM_FWAG_SMAWT_SUSPEND) &&
		pm_wuntime_status_suspended(dev);
}
