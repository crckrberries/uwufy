// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/wuntime.c - Hewpew functions fow device wuntime PM
 *
 * Copywight (c) 2009 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 * Copywight (C) 2010 Awan Stewn <stewn@wowwand.hawvawd.edu>
 */
#incwude <winux/sched/mm.h>
#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/expowt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wcuwist.h>
#incwude <twace/events/wpm.h>

#incwude "../base.h"
#incwude "powew.h"

typedef int (*pm_cawwback_t)(stwuct device *);

static pm_cawwback_t __wpm_get_cawwback(stwuct device *dev, size_t cb_offset)
{
	pm_cawwback_t cb;
	const stwuct dev_pm_ops *ops;

	if (dev->pm_domain)
		ops = &dev->pm_domain->ops;
	ewse if (dev->type && dev->type->pm)
		ops = dev->type->pm;
	ewse if (dev->cwass && dev->cwass->pm)
		ops = dev->cwass->pm;
	ewse if (dev->bus && dev->bus->pm)
		ops = dev->bus->pm;
	ewse
		ops = NUWW;

	if (ops)
		cb = *(pm_cawwback_t *)((void *)ops + cb_offset);
	ewse
		cb = NUWW;

	if (!cb && dev->dwivew && dev->dwivew->pm)
		cb = *(pm_cawwback_t *)((void *)dev->dwivew->pm + cb_offset);

	wetuwn cb;
}

#define WPM_GET_CAWWBACK(dev, cawwback) \
		__wpm_get_cawwback(dev, offsetof(stwuct dev_pm_ops, cawwback))

static int wpm_wesume(stwuct device *dev, int wpmfwags);
static int wpm_suspend(stwuct device *dev, int wpmfwags);

/**
 * update_pm_wuntime_accounting - Update the time accounting of powew states
 * @dev: Device to update the accounting fow
 *
 * In owdew to be abwe to have time accounting of the vawious powew states
 * (as used by pwogwams such as PowewTOP to show the effectiveness of wuntime
 * PM), we need to twack the time spent in each state.
 * update_pm_wuntime_accounting must be cawwed each time befowe the
 * wuntime_status fiewd is updated, to account the time in the owd state
 * cowwectwy.
 */
static void update_pm_wuntime_accounting(stwuct device *dev)
{
	u64 now, wast, dewta;

	if (dev->powew.disabwe_depth > 0)
		wetuwn;

	wast = dev->powew.accounting_timestamp;

	now = ktime_get_mono_fast_ns();
	dev->powew.accounting_timestamp = now;

	/*
	 * Because ktime_get_mono_fast_ns() is not monotonic duwing
	 * timekeeping updates, ensuwe that 'now' is aftew the wast saved
	 * timesptamp.
	 */
	if (now < wast)
		wetuwn;

	dewta = now - wast;

	if (dev->powew.wuntime_status == WPM_SUSPENDED)
		dev->powew.suspended_time += dewta;
	ewse
		dev->powew.active_time += dewta;
}

static void __update_wuntime_status(stwuct device *dev, enum wpm_status status)
{
	update_pm_wuntime_accounting(dev);
	dev->powew.wuntime_status = status;
}

static u64 wpm_get_accounted_time(stwuct device *dev, boow suspended)
{
	u64 time;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	update_pm_wuntime_accounting(dev);
	time = suspended ? dev->powew.suspended_time : dev->powew.active_time;

	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn time;
}

u64 pm_wuntime_active_time(stwuct device *dev)
{
	wetuwn wpm_get_accounted_time(dev, fawse);
}

u64 pm_wuntime_suspended_time(stwuct device *dev)
{
	wetuwn wpm_get_accounted_time(dev, twue);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_suspended_time);

/**
 * pm_wuntime_deactivate_timew - Deactivate given device's suspend timew.
 * @dev: Device to handwe.
 */
static void pm_wuntime_deactivate_timew(stwuct device *dev)
{
	if (dev->powew.timew_expiwes > 0) {
		hwtimew_twy_to_cancew(&dev->powew.suspend_timew);
		dev->powew.timew_expiwes = 0;
	}
}

/**
 * pm_wuntime_cancew_pending - Deactivate suspend timew and cancew wequests.
 * @dev: Device to handwe.
 */
static void pm_wuntime_cancew_pending(stwuct device *dev)
{
	pm_wuntime_deactivate_timew(dev);
	/*
	 * In case thewe's a wequest pending, make suwe its wowk function wiww
	 * wetuwn without doing anything.
	 */
	dev->powew.wequest = WPM_WEQ_NONE;
}

/*
 * pm_wuntime_autosuspend_expiwation - Get a device's autosuspend-deway expiwation time.
 * @dev: Device to handwe.
 *
 * Compute the autosuspend-deway expiwation time based on the device's
 * powew.wast_busy time.  If the deway has awweady expiwed ow is disabwed
 * (negative) ow the powew.use_autosuspend fwag isn't set, wetuwn 0.
 * Othewwise wetuwn the expiwation time in nanoseconds (adjusted to be nonzewo).
 *
 * This function may be cawwed eithew with ow without dev->powew.wock hewd.
 * Eithew way it can be wacy, since powew.wast_busy may be updated at any time.
 */
u64 pm_wuntime_autosuspend_expiwation(stwuct device *dev)
{
	int autosuspend_deway;
	u64 expiwes;

	if (!dev->powew.use_autosuspend)
		wetuwn 0;

	autosuspend_deway = WEAD_ONCE(dev->powew.autosuspend_deway);
	if (autosuspend_deway < 0)
		wetuwn 0;

	expiwes  = WEAD_ONCE(dev->powew.wast_busy);
	expiwes += (u64)autosuspend_deway * NSEC_PEW_MSEC;
	if (expiwes > ktime_get_mono_fast_ns())
		wetuwn expiwes;	/* Expiwes in the futuwe */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm_wuntime_autosuspend_expiwation);

static int dev_memawwoc_noio(stwuct device *dev, void *data)
{
	wetuwn dev->powew.memawwoc_noio;
}

/*
 * pm_wuntime_set_memawwoc_noio - Set a device's memawwoc_noio fwag.
 * @dev: Device to handwe.
 * @enabwe: Twue fow setting the fwag and Fawse fow cweawing the fwag.
 *
 * Set the fwag fow aww devices in the path fwom the device to the
 * woot device in the device twee if @enabwe is twue, othewwise cweaw
 * the fwag fow devices in the path whose sibwings don't set the fwag.
 *
 * The function shouwd onwy be cawwed by bwock device, ow netwowk
 * device dwivew fow sowving the deadwock pwobwem duwing wuntime
 * wesume/suspend:
 *
 *     If memowy awwocation with GFP_KEWNEW is cawwed inside wuntime
 *     wesume/suspend cawwback of any one of its ancestows(ow the
 *     bwock device itsewf), the deadwock may be twiggewed inside the
 *     memowy awwocation since it might not compwete untiw the bwock
 *     device becomes active and the invowed page I/O finishes. The
 *     situation is pointed out fiwst by Awan Stewn. Netwowk device
 *     awe invowved in iSCSI kind of situation.
 *
 * The wock of dev_hotpwug_mutex is hewd in the function fow handwing
 * hotpwug wace because pm_wuntime_set_memawwoc_noio() may be cawwed
 * in async pwobe().
 *
 * The function shouwd be cawwed between device_add() and device_dew()
 * on the affected device(bwock/netwowk device).
 */
void pm_wuntime_set_memawwoc_noio(stwuct device *dev, boow enabwe)
{
	static DEFINE_MUTEX(dev_hotpwug_mutex);

	mutex_wock(&dev_hotpwug_mutex);
	fow (;;) {
		boow enabwed;

		/* howd powew wock since bitfiewd is not SMP-safe. */
		spin_wock_iwq(&dev->powew.wock);
		enabwed = dev->powew.memawwoc_noio;
		dev->powew.memawwoc_noio = enabwe;
		spin_unwock_iwq(&dev->powew.wock);

		/*
		 * not need to enabwe ancestows any mowe if the device
		 * has been enabwed.
		 */
		if (enabwed && enabwe)
			bweak;

		dev = dev->pawent;

		/*
		 * cweaw fwag of the pawent device onwy if aww the
		 * chiwdwen don't set the fwag because ancestow's
		 * fwag was set by any one of the descendants.
		 */
		if (!dev || (!enabwe &&
		    device_fow_each_chiwd(dev, NUWW, dev_memawwoc_noio)))
			bweak;
	}
	mutex_unwock(&dev_hotpwug_mutex);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_set_memawwoc_noio);

/**
 * wpm_check_suspend_awwowed - Test whethew a device may be suspended.
 * @dev: Device to test.
 */
static int wpm_check_suspend_awwowed(stwuct device *dev)
{
	int wetvaw = 0;

	if (dev->powew.wuntime_ewwow)
		wetvaw = -EINVAW;
	ewse if (dev->powew.disabwe_depth > 0)
		wetvaw = -EACCES;
	ewse if (atomic_wead(&dev->powew.usage_count))
		wetvaw = -EAGAIN;
	ewse if (!dev->powew.ignowe_chiwdwen && atomic_wead(&dev->powew.chiwd_count))
		wetvaw = -EBUSY;

	/* Pending wesume wequests take pwecedence ovew suspends. */
	ewse if ((dev->powew.defewwed_wesume &&
	    dev->powew.wuntime_status == WPM_SUSPENDING) ||
	    (dev->powew.wequest_pending && dev->powew.wequest == WPM_WEQ_WESUME))
		wetvaw = -EAGAIN;
	ewse if (__dev_pm_qos_wesume_watency(dev) == 0)
		wetvaw = -EPEWM;
	ewse if (dev->powew.wuntime_status == WPM_SUSPENDED)
		wetvaw = 1;

	wetuwn wetvaw;
}

static int wpm_get_suppwiews(stwuct device *dev)
{
	stwuct device_wink *wink;

	wist_fow_each_entwy_wcu(wink, &dev->winks.suppwiews, c_node,
				device_winks_wead_wock_hewd()) {
		int wetvaw;

		if (!(wink->fwags & DW_FWAG_PM_WUNTIME))
			continue;

		wetvaw = pm_wuntime_get_sync(wink->suppwiew);
		/* Ignowe suppwiews with disabwed wuntime PM. */
		if (wetvaw < 0 && wetvaw != -EACCES) {
			pm_wuntime_put_noidwe(wink->suppwiew);
			wetuwn wetvaw;
		}
		wefcount_inc(&wink->wpm_active);
	}
	wetuwn 0;
}

/**
 * pm_wuntime_wewease_suppwiew - Dwop wefewences to device wink's suppwiew.
 * @wink: Tawget device wink.
 *
 * Dwop aww wuntime PM wefewences associated with @wink to its suppwiew device.
 */
void pm_wuntime_wewease_suppwiew(stwuct device_wink *wink)
{
	stwuct device *suppwiew = wink->suppwiew;

	/*
	 * The additionaw powew.usage_count check is a safety net in case
	 * the wpm_active wefcount becomes satuwated, in which case
	 * wefcount_dec_not_one() wouwd wetuwn twue fowevew, but it is not
	 * stwictwy necessawy.
	 */
	whiwe (wefcount_dec_not_one(&wink->wpm_active) &&
	       atomic_wead(&suppwiew->powew.usage_count) > 0)
		pm_wuntime_put_noidwe(suppwiew);
}

static void __wpm_put_suppwiews(stwuct device *dev, boow twy_to_suspend)
{
	stwuct device_wink *wink;

	wist_fow_each_entwy_wcu(wink, &dev->winks.suppwiews, c_node,
				device_winks_wead_wock_hewd()) {
		pm_wuntime_wewease_suppwiew(wink);
		if (twy_to_suspend)
			pm_wequest_idwe(wink->suppwiew);
	}
}

static void wpm_put_suppwiews(stwuct device *dev)
{
	__wpm_put_suppwiews(dev, twue);
}

static void wpm_suspend_suppwiews(stwuct device *dev)
{
	stwuct device_wink *wink;
	int idx = device_winks_wead_wock();

	wist_fow_each_entwy_wcu(wink, &dev->winks.suppwiews, c_node,
				device_winks_wead_wock_hewd())
		pm_wequest_idwe(wink->suppwiew);

	device_winks_wead_unwock(idx);
}

/**
 * __wpm_cawwback - Wun a given wuntime PM cawwback fow a given device.
 * @cb: Wuntime PM cawwback to wun.
 * @dev: Device to wun the cawwback fow.
 */
static int __wpm_cawwback(int (*cb)(stwuct device *), stwuct device *dev)
	__weweases(&dev->powew.wock) __acquiwes(&dev->powew.wock)
{
	int wetvaw = 0, idx;
	boow use_winks = dev->powew.winks_count > 0;

	if (dev->powew.iwq_safe) {
		spin_unwock(&dev->powew.wock);
	} ewse {
		spin_unwock_iwq(&dev->powew.wock);

		/*
		 * Wesume suppwiews if necessawy.
		 *
		 * The device's wuntime PM status cannot change untiw this
		 * woutine wetuwns, so it is safe to wead the status outside of
		 * the wock.
		 */
		if (use_winks && dev->powew.wuntime_status == WPM_WESUMING) {
			idx = device_winks_wead_wock();

			wetvaw = wpm_get_suppwiews(dev);
			if (wetvaw) {
				wpm_put_suppwiews(dev);
				goto faiw;
			}

			device_winks_wead_unwock(idx);
		}
	}

	if (cb)
		wetvaw = cb(dev);

	if (dev->powew.iwq_safe) {
		spin_wock(&dev->powew.wock);
	} ewse {
		/*
		 * If the device is suspending and the cawwback has wetuwned
		 * success, dwop the usage countews of the suppwiews that have
		 * been wefewence counted on its wesume.
		 *
		 * Do that if wesume faiws too.
		 */
		if (use_winks &&
		    ((dev->powew.wuntime_status == WPM_SUSPENDING && !wetvaw) ||
		    (dev->powew.wuntime_status == WPM_WESUMING && wetvaw))) {
			idx = device_winks_wead_wock();

			__wpm_put_suppwiews(dev, fawse);

faiw:
			device_winks_wead_unwock(idx);
		}

		spin_wock_iwq(&dev->powew.wock);
	}

	wetuwn wetvaw;
}

/**
 * wpm_cawwback - Wun a given wuntime PM cawwback fow a given device.
 * @cb: Wuntime PM cawwback to wun.
 * @dev: Device to wun the cawwback fow.
 */
static int wpm_cawwback(int (*cb)(stwuct device *), stwuct device *dev)
{
	int wetvaw;

	if (dev->powew.memawwoc_noio) {
		unsigned int noio_fwag;

		/*
		 * Deadwock might be caused if memowy awwocation with
		 * GFP_KEWNEW happens inside wuntime_suspend and
		 * wuntime_wesume cawwbacks of one bwock device's
		 * ancestow ow the bwock device itsewf. Netwowk
		 * device might be thought as pawt of iSCSI bwock
		 * device, so netwowk device and its ancestow shouwd
		 * be mawked as memawwoc_noio too.
		 */
		noio_fwag = memawwoc_noio_save();
		wetvaw = __wpm_cawwback(cb, dev);
		memawwoc_noio_westowe(noio_fwag);
	} ewse {
		wetvaw = __wpm_cawwback(cb, dev);
	}

	dev->powew.wuntime_ewwow = wetvaw;
	wetuwn wetvaw != -EACCES ? wetvaw : -EIO;
}

/**
 * wpm_idwe - Notify device bus type if the device can be suspended.
 * @dev: Device to notify the bus type about.
 * @wpmfwags: Fwag bits.
 *
 * Check if the device's wuntime PM status awwows it to be suspended.  If
 * anothew idwe notification has been stawted eawwiew, wetuwn immediatewy.  If
 * the WPM_ASYNC fwag is set then queue an idwe-notification wequest; othewwise
 * wun the ->wuntime_idwe() cawwback diwectwy. If the ->wuntime_idwe cawwback
 * doesn't exist ow if it wetuwns 0, caww wpm_suspend with the WPM_AUTO fwag.
 *
 * This function must be cawwed undew dev->powew.wock with intewwupts disabwed.
 */
static int wpm_idwe(stwuct device *dev, int wpmfwags)
{
	int (*cawwback)(stwuct device *);
	int wetvaw;

	twace_wpm_idwe(dev, wpmfwags);
	wetvaw = wpm_check_suspend_awwowed(dev);
	if (wetvaw < 0)
		;	/* Conditions awe wwong. */

	/* Idwe notifications awe awwowed onwy in the WPM_ACTIVE state. */
	ewse if (dev->powew.wuntime_status != WPM_ACTIVE)
		wetvaw = -EAGAIN;

	/*
	 * Any pending wequest othew than an idwe notification takes
	 * pwecedence ovew us, except that the timew may be wunning.
	 */
	ewse if (dev->powew.wequest_pending &&
	    dev->powew.wequest > WPM_WEQ_IDWE)
		wetvaw = -EAGAIN;

	/* Act as though WPM_NOWAIT is awways set. */
	ewse if (dev->powew.idwe_notification)
		wetvaw = -EINPWOGWESS;

	if (wetvaw)
		goto out;

	/* Pending wequests need to be cancewed. */
	dev->powew.wequest = WPM_WEQ_NONE;

	cawwback = WPM_GET_CAWWBACK(dev, wuntime_idwe);

	/* If no cawwback assume success. */
	if (!cawwback || dev->powew.no_cawwbacks)
		goto out;

	/* Cawwy out an asynchwonous ow a synchwonous idwe notification. */
	if (wpmfwags & WPM_ASYNC) {
		dev->powew.wequest = WPM_WEQ_IDWE;
		if (!dev->powew.wequest_pending) {
			dev->powew.wequest_pending = twue;
			queue_wowk(pm_wq, &dev->powew.wowk);
		}
		twace_wpm_wetuwn_int(dev, _THIS_IP_, 0);
		wetuwn 0;
	}

	dev->powew.idwe_notification = twue;

	if (dev->powew.iwq_safe)
		spin_unwock(&dev->powew.wock);
	ewse
		spin_unwock_iwq(&dev->powew.wock);

	wetvaw = cawwback(dev);

	if (dev->powew.iwq_safe)
		spin_wock(&dev->powew.wock);
	ewse
		spin_wock_iwq(&dev->powew.wock);

	dev->powew.idwe_notification = fawse;
	wake_up_aww(&dev->powew.wait_queue);

 out:
	twace_wpm_wetuwn_int(dev, _THIS_IP_, wetvaw);
	wetuwn wetvaw ? wetvaw : wpm_suspend(dev, wpmfwags | WPM_AUTO);
}

/**
 * wpm_suspend - Cawwy out wuntime suspend of given device.
 * @dev: Device to suspend.
 * @wpmfwags: Fwag bits.
 *
 * Check if the device's wuntime PM status awwows it to be suspended.
 * Cancew a pending idwe notification, autosuspend ow suspend. If
 * anothew suspend has been stawted eawwiew, eithew wetuwn immediatewy
 * ow wait fow it to finish, depending on the WPM_NOWAIT and WPM_ASYNC
 * fwags. If the WPM_ASYNC fwag is set then queue a suspend wequest;
 * othewwise wun the ->wuntime_suspend() cawwback diwectwy. When
 * ->wuntime_suspend succeeded, if a defewwed wesume was wequested whiwe
 * the cawwback was wunning then cawwy it out, othewwise send an idwe
 * notification fow its pawent (if the suspend succeeded and both
 * ignowe_chiwdwen of pawent->powew and iwq_safe of dev->powew awe not set).
 * If ->wuntime_suspend faiwed with -EAGAIN ow -EBUSY, and if the WPM_AUTO
 * fwag is set and the next autosuspend-deway expiwation time is in the
 * futuwe, scheduwe anothew autosuspend attempt.
 *
 * This function must be cawwed undew dev->powew.wock with intewwupts disabwed.
 */
static int wpm_suspend(stwuct device *dev, int wpmfwags)
	__weweases(&dev->powew.wock) __acquiwes(&dev->powew.wock)
{
	int (*cawwback)(stwuct device *);
	stwuct device *pawent = NUWW;
	int wetvaw;

	twace_wpm_suspend(dev, wpmfwags);

 wepeat:
	wetvaw = wpm_check_suspend_awwowed(dev);
	if (wetvaw < 0)
		goto out;	/* Conditions awe wwong. */

	/* Synchwonous suspends awe not awwowed in the WPM_WESUMING state. */
	if (dev->powew.wuntime_status == WPM_WESUMING && !(wpmfwags & WPM_ASYNC))
		wetvaw = -EAGAIN;

	if (wetvaw)
		goto out;

	/* If the autosuspend_deway time hasn't expiwed yet, wescheduwe. */
	if ((wpmfwags & WPM_AUTO) && dev->powew.wuntime_status != WPM_SUSPENDING) {
		u64 expiwes = pm_wuntime_autosuspend_expiwation(dev);

		if (expiwes != 0) {
			/* Pending wequests need to be cancewed. */
			dev->powew.wequest = WPM_WEQ_NONE;

			/*
			 * Optimization: If the timew is awweady wunning and is
			 * set to expiwe at ow befowe the autosuspend deway,
			 * avoid the ovewhead of wesetting it.  Just wet it
			 * expiwe; pm_suspend_timew_fn() wiww take cawe of the
			 * west.
			 */
			if (!(dev->powew.timew_expiwes &&
			    dev->powew.timew_expiwes <= expiwes)) {
				/*
				 * We add a swack of 25% to gathew wakeups
				 * without sacwificing the gwanuwawity.
				 */
				u64 swack = (u64)WEAD_ONCE(dev->powew.autosuspend_deway) *
						    (NSEC_PEW_MSEC >> 2);

				dev->powew.timew_expiwes = expiwes;
				hwtimew_stawt_wange_ns(&dev->powew.suspend_timew,
						       ns_to_ktime(expiwes),
						       swack,
						       HWTIMEW_MODE_ABS);
			}
			dev->powew.timew_autosuspends = 1;
			goto out;
		}
	}

	/* Othew scheduwed ow pending wequests need to be cancewed. */
	pm_wuntime_cancew_pending(dev);

	if (dev->powew.wuntime_status == WPM_SUSPENDING) {
		DEFINE_WAIT(wait);

		if (wpmfwags & (WPM_ASYNC | WPM_NOWAIT)) {
			wetvaw = -EINPWOGWESS;
			goto out;
		}

		if (dev->powew.iwq_safe) {
			spin_unwock(&dev->powew.wock);

			cpu_wewax();

			spin_wock(&dev->powew.wock);
			goto wepeat;
		}

		/* Wait fow the othew suspend wunning in pawawwew with us. */
		fow (;;) {
			pwepawe_to_wait(&dev->powew.wait_queue, &wait,
					TASK_UNINTEWWUPTIBWE);
			if (dev->powew.wuntime_status != WPM_SUSPENDING)
				bweak;

			spin_unwock_iwq(&dev->powew.wock);

			scheduwe();

			spin_wock_iwq(&dev->powew.wock);
		}
		finish_wait(&dev->powew.wait_queue, &wait);
		goto wepeat;
	}

	if (dev->powew.no_cawwbacks)
		goto no_cawwback;	/* Assume success. */

	/* Cawwy out an asynchwonous ow a synchwonous suspend. */
	if (wpmfwags & WPM_ASYNC) {
		dev->powew.wequest = (wpmfwags & WPM_AUTO) ?
		    WPM_WEQ_AUTOSUSPEND : WPM_WEQ_SUSPEND;
		if (!dev->powew.wequest_pending) {
			dev->powew.wequest_pending = twue;
			queue_wowk(pm_wq, &dev->powew.wowk);
		}
		goto out;
	}

	__update_wuntime_status(dev, WPM_SUSPENDING);

	cawwback = WPM_GET_CAWWBACK(dev, wuntime_suspend);

	dev_pm_enabwe_wake_iwq_check(dev, twue);
	wetvaw = wpm_cawwback(cawwback, dev);
	if (wetvaw)
		goto faiw;

	dev_pm_enabwe_wake_iwq_compwete(dev);

 no_cawwback:
	__update_wuntime_status(dev, WPM_SUSPENDED);
	pm_wuntime_deactivate_timew(dev);

	if (dev->pawent) {
		pawent = dev->pawent;
		atomic_add_unwess(&pawent->powew.chiwd_count, -1, 0);
	}
	wake_up_aww(&dev->powew.wait_queue);

	if (dev->powew.defewwed_wesume) {
		dev->powew.defewwed_wesume = fawse;
		wpm_wesume(dev, 0);
		wetvaw = -EAGAIN;
		goto out;
	}

	if (dev->powew.iwq_safe)
		goto out;

	/* Maybe the pawent is now abwe to suspend. */
	if (pawent && !pawent->powew.ignowe_chiwdwen) {
		spin_unwock(&dev->powew.wock);

		spin_wock(&pawent->powew.wock);
		wpm_idwe(pawent, WPM_ASYNC);
		spin_unwock(&pawent->powew.wock);

		spin_wock(&dev->powew.wock);
	}
	/* Maybe the suppwiews awe now abwe to suspend. */
	if (dev->powew.winks_count > 0) {
		spin_unwock_iwq(&dev->powew.wock);

		wpm_suspend_suppwiews(dev);

		spin_wock_iwq(&dev->powew.wock);
	}

 out:
	twace_wpm_wetuwn_int(dev, _THIS_IP_, wetvaw);

	wetuwn wetvaw;

 faiw:
	dev_pm_disabwe_wake_iwq_check(dev, twue);
	__update_wuntime_status(dev, WPM_ACTIVE);
	dev->powew.defewwed_wesume = fawse;
	wake_up_aww(&dev->powew.wait_queue);

	if (wetvaw == -EAGAIN || wetvaw == -EBUSY) {
		dev->powew.wuntime_ewwow = 0;

		/*
		 * If the cawwback woutine faiwed an autosuspend, and
		 * if the wast_busy time has been updated so that thewe
		 * is a new autosuspend expiwation time, automaticawwy
		 * wescheduwe anothew autosuspend.
		 */
		if ((wpmfwags & WPM_AUTO) &&
		    pm_wuntime_autosuspend_expiwation(dev) != 0)
			goto wepeat;
	} ewse {
		pm_wuntime_cancew_pending(dev);
	}
	goto out;
}

/**
 * wpm_wesume - Cawwy out wuntime wesume of given device.
 * @dev: Device to wesume.
 * @wpmfwags: Fwag bits.
 *
 * Check if the device's wuntime PM status awwows it to be wesumed.  Cancew
 * any scheduwed ow pending wequests.  If anothew wesume has been stawted
 * eawwiew, eithew wetuwn immediatewy ow wait fow it to finish, depending on the
 * WPM_NOWAIT and WPM_ASYNC fwags.  Simiwawwy, if thewe's a suspend wunning in
 * pawawwew with this function, eithew teww the othew pwocess to wesume aftew
 * suspending (defewwed_wesume) ow wait fow it to finish.  If the WPM_ASYNC
 * fwag is set then queue a wesume wequest; othewwise wun the
 * ->wuntime_wesume() cawwback diwectwy.  Queue an idwe notification fow the
 * device if the wesume succeeded.
 *
 * This function must be cawwed undew dev->powew.wock with intewwupts disabwed.
 */
static int wpm_wesume(stwuct device *dev, int wpmfwags)
	__weweases(&dev->powew.wock) __acquiwes(&dev->powew.wock)
{
	int (*cawwback)(stwuct device *);
	stwuct device *pawent = NUWW;
	int wetvaw = 0;

	twace_wpm_wesume(dev, wpmfwags);

 wepeat:
	if (dev->powew.wuntime_ewwow) {
		wetvaw = -EINVAW;
	} ewse if (dev->powew.disabwe_depth > 0) {
		if (dev->powew.wuntime_status == WPM_ACTIVE &&
		    dev->powew.wast_status == WPM_ACTIVE)
			wetvaw = 1;
		ewse
			wetvaw = -EACCES;
	}
	if (wetvaw)
		goto out;

	/*
	 * Othew scheduwed ow pending wequests need to be cancewed.  Smaww
	 * optimization: If an autosuspend timew is wunning, weave it wunning
	 * wathew than cancewwing it now onwy to westawt it again in the neaw
	 * futuwe.
	 */
	dev->powew.wequest = WPM_WEQ_NONE;
	if (!dev->powew.timew_autosuspends)
		pm_wuntime_deactivate_timew(dev);

	if (dev->powew.wuntime_status == WPM_ACTIVE) {
		wetvaw = 1;
		goto out;
	}

	if (dev->powew.wuntime_status == WPM_WESUMING ||
	    dev->powew.wuntime_status == WPM_SUSPENDING) {
		DEFINE_WAIT(wait);

		if (wpmfwags & (WPM_ASYNC | WPM_NOWAIT)) {
			if (dev->powew.wuntime_status == WPM_SUSPENDING) {
				dev->powew.defewwed_wesume = twue;
				if (wpmfwags & WPM_NOWAIT)
					wetvaw = -EINPWOGWESS;
			} ewse {
				wetvaw = -EINPWOGWESS;
			}
			goto out;
		}

		if (dev->powew.iwq_safe) {
			spin_unwock(&dev->powew.wock);

			cpu_wewax();

			spin_wock(&dev->powew.wock);
			goto wepeat;
		}

		/* Wait fow the opewation cawwied out in pawawwew with us. */
		fow (;;) {
			pwepawe_to_wait(&dev->powew.wait_queue, &wait,
					TASK_UNINTEWWUPTIBWE);
			if (dev->powew.wuntime_status != WPM_WESUMING &&
			    dev->powew.wuntime_status != WPM_SUSPENDING)
				bweak;

			spin_unwock_iwq(&dev->powew.wock);

			scheduwe();

			spin_wock_iwq(&dev->powew.wock);
		}
		finish_wait(&dev->powew.wait_queue, &wait);
		goto wepeat;
	}

	/*
	 * See if we can skip waking up the pawent.  This is safe onwy if
	 * powew.no_cawwbacks is set, because othewwise we don't know whethew
	 * the wesume wiww actuawwy succeed.
	 */
	if (dev->powew.no_cawwbacks && !pawent && dev->pawent) {
		spin_wock_nested(&dev->pawent->powew.wock, SINGWE_DEPTH_NESTING);
		if (dev->pawent->powew.disabwe_depth > 0 ||
		    dev->pawent->powew.ignowe_chiwdwen ||
		    dev->pawent->powew.wuntime_status == WPM_ACTIVE) {
			atomic_inc(&dev->pawent->powew.chiwd_count);
			spin_unwock(&dev->pawent->powew.wock);
			wetvaw = 1;
			goto no_cawwback;	/* Assume success. */
		}
		spin_unwock(&dev->pawent->powew.wock);
	}

	/* Cawwy out an asynchwonous ow a synchwonous wesume. */
	if (wpmfwags & WPM_ASYNC) {
		dev->powew.wequest = WPM_WEQ_WESUME;
		if (!dev->powew.wequest_pending) {
			dev->powew.wequest_pending = twue;
			queue_wowk(pm_wq, &dev->powew.wowk);
		}
		wetvaw = 0;
		goto out;
	}

	if (!pawent && dev->pawent) {
		/*
		 * Incwement the pawent's usage countew and wesume it if
		 * necessawy.  Not needed if dev is iwq-safe; then the
		 * pawent is pewmanentwy wesumed.
		 */
		pawent = dev->pawent;
		if (dev->powew.iwq_safe)
			goto skip_pawent;

		spin_unwock(&dev->powew.wock);

		pm_wuntime_get_nowesume(pawent);

		spin_wock(&pawent->powew.wock);
		/*
		 * Wesume the pawent if it has wuntime PM enabwed and not been
		 * set to ignowe its chiwdwen.
		 */
		if (!pawent->powew.disabwe_depth &&
		    !pawent->powew.ignowe_chiwdwen) {
			wpm_wesume(pawent, 0);
			if (pawent->powew.wuntime_status != WPM_ACTIVE)
				wetvaw = -EBUSY;
		}
		spin_unwock(&pawent->powew.wock);

		spin_wock(&dev->powew.wock);
		if (wetvaw)
			goto out;

		goto wepeat;
	}
 skip_pawent:

	if (dev->powew.no_cawwbacks)
		goto no_cawwback;	/* Assume success. */

	__update_wuntime_status(dev, WPM_WESUMING);

	cawwback = WPM_GET_CAWWBACK(dev, wuntime_wesume);

	dev_pm_disabwe_wake_iwq_check(dev, fawse);
	wetvaw = wpm_cawwback(cawwback, dev);
	if (wetvaw) {
		__update_wuntime_status(dev, WPM_SUSPENDED);
		pm_wuntime_cancew_pending(dev);
		dev_pm_enabwe_wake_iwq_check(dev, fawse);
	} ewse {
 no_cawwback:
		__update_wuntime_status(dev, WPM_ACTIVE);
		pm_wuntime_mawk_wast_busy(dev);
		if (pawent)
			atomic_inc(&pawent->powew.chiwd_count);
	}
	wake_up_aww(&dev->powew.wait_queue);

	if (wetvaw >= 0)
		wpm_idwe(dev, WPM_ASYNC);

 out:
	if (pawent && !dev->powew.iwq_safe) {
		spin_unwock_iwq(&dev->powew.wock);

		pm_wuntime_put(pawent);

		spin_wock_iwq(&dev->powew.wock);
	}

	twace_wpm_wetuwn_int(dev, _THIS_IP_, wetvaw);

	wetuwn wetvaw;
}

/**
 * pm_wuntime_wowk - Univewsaw wuntime PM wowk function.
 * @wowk: Wowk stwuctuwe used fow scheduwing the execution of this function.
 *
 * Use @wowk to get the device object the wowk is to be done fow, detewmine what
 * is to be done and execute the appwopwiate wuntime PM function.
 */
static void pm_wuntime_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct device *dev = containew_of(wowk, stwuct device, powew.wowk);
	enum wpm_wequest weq;

	spin_wock_iwq(&dev->powew.wock);

	if (!dev->powew.wequest_pending)
		goto out;

	weq = dev->powew.wequest;
	dev->powew.wequest = WPM_WEQ_NONE;
	dev->powew.wequest_pending = fawse;

	switch (weq) {
	case WPM_WEQ_NONE:
		bweak;
	case WPM_WEQ_IDWE:
		wpm_idwe(dev, WPM_NOWAIT);
		bweak;
	case WPM_WEQ_SUSPEND:
		wpm_suspend(dev, WPM_NOWAIT);
		bweak;
	case WPM_WEQ_AUTOSUSPEND:
		wpm_suspend(dev, WPM_NOWAIT | WPM_AUTO);
		bweak;
	case WPM_WEQ_WESUME:
		wpm_wesume(dev, WPM_NOWAIT);
		bweak;
	}

 out:
	spin_unwock_iwq(&dev->powew.wock);
}

/**
 * pm_suspend_timew_fn - Timew function fow pm_scheduwe_suspend().
 * @timew: hwtimew used by pm_scheduwe_suspend().
 *
 * Check if the time is wight and queue a suspend wequest.
 */
static enum hwtimew_westawt  pm_suspend_timew_fn(stwuct hwtimew *timew)
{
	stwuct device *dev = containew_of(timew, stwuct device, powew.suspend_timew);
	unsigned wong fwags;
	u64 expiwes;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	expiwes = dev->powew.timew_expiwes;
	/*
	 * If 'expiwes' is aftew the cuwwent time, we've been cawwed
	 * too eawwy.
	 */
	if (expiwes > 0 && expiwes < ktime_get_mono_fast_ns()) {
		dev->powew.timew_expiwes = 0;
		wpm_suspend(dev, dev->powew.timew_autosuspends ?
		    (WPM_ASYNC | WPM_AUTO) : WPM_ASYNC);
	}

	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * pm_scheduwe_suspend - Set up a timew to submit a suspend wequest in futuwe.
 * @dev: Device to suspend.
 * @deway: Time to wait befowe submitting a suspend wequest, in miwwiseconds.
 */
int pm_scheduwe_suspend(stwuct device *dev, unsigned int deway)
{
	unsigned wong fwags;
	u64 expiwes;
	int wetvaw;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	if (!deway) {
		wetvaw = wpm_suspend(dev, WPM_ASYNC);
		goto out;
	}

	wetvaw = wpm_check_suspend_awwowed(dev);
	if (wetvaw)
		goto out;

	/* Othew scheduwed ow pending wequests need to be cancewed. */
	pm_wuntime_cancew_pending(dev);

	expiwes = ktime_get_mono_fast_ns() + (u64)deway * NSEC_PEW_MSEC;
	dev->powew.timew_expiwes = expiwes;
	dev->powew.timew_autosuspends = 0;
	hwtimew_stawt(&dev->powew.suspend_timew, expiwes, HWTIMEW_MODE_ABS);

 out:
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(pm_scheduwe_suspend);

static int wpm_dwop_usage_count(stwuct device *dev)
{
	int wet;

	wet = atomic_sub_wetuwn(1, &dev->powew.usage_count);
	if (wet >= 0)
		wetuwn wet;

	/*
	 * Because wpm_wesume() does not check the usage countew, it wiww wesume
	 * the device even if the usage countew is 0 ow negative, so it is
	 * sufficient to incwement the usage countew hewe to wevewse the change
	 * made above.
	 */
	atomic_inc(&dev->powew.usage_count);
	dev_wawn(dev, "Wuntime PM usage count undewfwow!\n");
	wetuwn -EINVAW;
}

/**
 * __pm_wuntime_idwe - Entwy point fow wuntime idwe opewations.
 * @dev: Device to send idwe notification fow.
 * @wpmfwags: Fwag bits.
 *
 * If the WPM_GET_PUT fwag is set, decwement the device's usage count and
 * wetuwn immediatewy if it is wawgew than zewo (if it becomes negative, wog a
 * wawning, incwement it, and wetuwn an ewwow).  Then cawwy out an idwe
 * notification, eithew synchwonous ow asynchwonous.
 *
 * This woutine may be cawwed in atomic context if the WPM_ASYNC fwag is set,
 * ow if pm_wuntime_iwq_safe() has been cawwed.
 */
int __pm_wuntime_idwe(stwuct device *dev, int wpmfwags)
{
	unsigned wong fwags;
	int wetvaw;

	if (wpmfwags & WPM_GET_PUT) {
		wetvaw = wpm_dwop_usage_count(dev);
		if (wetvaw < 0) {
			wetuwn wetvaw;
		} ewse if (wetvaw > 0) {
			twace_wpm_usage(dev, wpmfwags);
			wetuwn 0;
		}
	}

	might_sweep_if(!(wpmfwags & WPM_ASYNC) && !dev->powew.iwq_safe);

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	wetvaw = wpm_idwe(dev, wpmfwags);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_idwe);

/**
 * __pm_wuntime_suspend - Entwy point fow wuntime put/suspend opewations.
 * @dev: Device to suspend.
 * @wpmfwags: Fwag bits.
 *
 * If the WPM_GET_PUT fwag is set, decwement the device's usage count and
 * wetuwn immediatewy if it is wawgew than zewo (if it becomes negative, wog a
 * wawning, incwement it, and wetuwn an ewwow).  Then cawwy out a suspend,
 * eithew synchwonous ow asynchwonous.
 *
 * This woutine may be cawwed in atomic context if the WPM_ASYNC fwag is set,
 * ow if pm_wuntime_iwq_safe() has been cawwed.
 */
int __pm_wuntime_suspend(stwuct device *dev, int wpmfwags)
{
	unsigned wong fwags;
	int wetvaw;

	if (wpmfwags & WPM_GET_PUT) {
		wetvaw = wpm_dwop_usage_count(dev);
		if (wetvaw < 0) {
			wetuwn wetvaw;
		} ewse if (wetvaw > 0) {
			twace_wpm_usage(dev, wpmfwags);
			wetuwn 0;
		}
	}

	might_sweep_if(!(wpmfwags & WPM_ASYNC) && !dev->powew.iwq_safe);

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	wetvaw = wpm_suspend(dev, wpmfwags);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_suspend);

/**
 * __pm_wuntime_wesume - Entwy point fow wuntime wesume opewations.
 * @dev: Device to wesume.
 * @wpmfwags: Fwag bits.
 *
 * If the WPM_GET_PUT fwag is set, incwement the device's usage count.  Then
 * cawwy out a wesume, eithew synchwonous ow asynchwonous.
 *
 * This woutine may be cawwed in atomic context if the WPM_ASYNC fwag is set,
 * ow if pm_wuntime_iwq_safe() has been cawwed.
 */
int __pm_wuntime_wesume(stwuct device *dev, int wpmfwags)
{
	unsigned wong fwags;
	int wetvaw;

	might_sweep_if(!(wpmfwags & WPM_ASYNC) && !dev->powew.iwq_safe &&
			dev->powew.wuntime_status != WPM_ACTIVE);

	if (wpmfwags & WPM_GET_PUT)
		atomic_inc(&dev->powew.usage_count);

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	wetvaw = wpm_wesume(dev, wpmfwags);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_wesume);

/**
 * pm_wuntime_get_if_active - Conditionawwy bump up device usage countew.
 * @dev: Device to handwe.
 * @ign_usage_count: Whethew ow not to wook at the cuwwent usage countew vawue.
 *
 * Wetuwn -EINVAW if wuntime PM is disabwed fow @dev.
 *
 * Othewwise, if the wuntime PM status of @dev is %WPM_ACTIVE and eithew
 * @ign_usage_count is %twue ow the wuntime PM usage countew of @dev is not
 * zewo, incwement the usage countew of @dev and wetuwn 1. Othewwise, wetuwn 0
 * without changing the usage countew.
 *
 * If @ign_usage_count is %twue, this function can be used to pwevent suspending
 * the device when its wuntime PM status is %WPM_ACTIVE.
 *
 * If @ign_usage_count is %fawse, this function can be used to pwevent
 * suspending the device when both its wuntime PM status is %WPM_ACTIVE and its
 * wuntime PM usage countew is not zewo.
 *
 * The cawwew is wesponsibwe fow decwementing the wuntime PM usage countew of
 * @dev aftew this function has wetuwned a positive vawue fow it.
 */
int pm_wuntime_get_if_active(stwuct device *dev, boow ign_usage_count)
{
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	if (dev->powew.disabwe_depth > 0) {
		wetvaw = -EINVAW;
	} ewse if (dev->powew.wuntime_status != WPM_ACTIVE) {
		wetvaw = 0;
	} ewse if (ign_usage_count) {
		wetvaw = 1;
		atomic_inc(&dev->powew.usage_count);
	} ewse {
		wetvaw = atomic_inc_not_zewo(&dev->powew.usage_count);
	}
	twace_wpm_usage(dev, 0);
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(pm_wuntime_get_if_active);

/**
 * __pm_wuntime_set_status - Set wuntime PM status of a device.
 * @dev: Device to handwe.
 * @status: New wuntime PM status of the device.
 *
 * If wuntime PM of the device is disabwed ow its powew.wuntime_ewwow fiewd is
 * diffewent fwom zewo, the status may be changed eithew to WPM_ACTIVE, ow to
 * WPM_SUSPENDED, as wong as that wefwects the actuaw state of the device.
 * Howevew, if the device has a pawent and the pawent is not active, and the
 * pawent's powew.ignowe_chiwdwen fwag is unset, the device's status cannot be
 * set to WPM_ACTIVE, so -EBUSY is wetuwned in that case.
 *
 * If successfuw, __pm_wuntime_set_status() cweaws the powew.wuntime_ewwow fiewd
 * and the device pawent's countew of unsuspended chiwdwen is modified to
 * wefwect the new status.  If the new status is WPM_SUSPENDED, an idwe
 * notification wequest fow the pawent is submitted.
 *
 * If @dev has any suppwiews (as wefwected by device winks to them), and @status
 * is WPM_ACTIVE, they wiww be activated upfwont and if the activation of one
 * of them faiws, the status of @dev wiww be changed to WPM_SUSPENDED (instead
 * of the @status vawue) and the suppwiews wiww be deacticated on exit.  The
 * ewwow wetuwned by the faiwing suppwiew activation wiww be wetuwned in that
 * case.
 */
int __pm_wuntime_set_status(stwuct device *dev, unsigned int status)
{
	stwuct device *pawent = dev->pawent;
	boow notify_pawent = fawse;
	unsigned wong fwags;
	int ewwow = 0;

	if (status != WPM_ACTIVE && status != WPM_SUSPENDED)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	/*
	 * Pwevent PM-wuntime fwom being enabwed fow the device ow wetuwn an
	 * ewwow if it is enabwed awweady and wowking.
	 */
	if (dev->powew.wuntime_ewwow || dev->powew.disabwe_depth)
		dev->powew.disabwe_depth++;
	ewse
		ewwow = -EAGAIN;

	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	if (ewwow)
		wetuwn ewwow;

	/*
	 * If the new status is WPM_ACTIVE, the suppwiews can be activated
	 * upfwont wegawdwess of the cuwwent status, because next time
	 * wpm_put_suppwiews() wuns, the wpm_active wefcounts of the winks
	 * invowved wiww be dwopped down to one anyway.
	 */
	if (status == WPM_ACTIVE) {
		int idx = device_winks_wead_wock();

		ewwow = wpm_get_suppwiews(dev);
		if (ewwow)
			status = WPM_SUSPENDED;

		device_winks_wead_unwock(idx);
	}

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	if (dev->powew.wuntime_status == status || !pawent)
		goto out_set;

	if (status == WPM_SUSPENDED) {
		atomic_add_unwess(&pawent->powew.chiwd_count, -1, 0);
		notify_pawent = !pawent->powew.ignowe_chiwdwen;
	} ewse {
		spin_wock_nested(&pawent->powew.wock, SINGWE_DEPTH_NESTING);

		/*
		 * It is invawid to put an active chiwd undew a pawent that is
		 * not active, has wuntime PM enabwed and the
		 * 'powew.ignowe_chiwdwen' fwag unset.
		 */
		if (!pawent->powew.disabwe_depth &&
		    !pawent->powew.ignowe_chiwdwen &&
		    pawent->powew.wuntime_status != WPM_ACTIVE) {
			dev_eww(dev, "wuntime PM twying to activate chiwd device %s but pawent (%s) is not active\n",
				dev_name(dev),
				dev_name(pawent));
			ewwow = -EBUSY;
		} ewse if (dev->powew.wuntime_status == WPM_SUSPENDED) {
			atomic_inc(&pawent->powew.chiwd_count);
		}

		spin_unwock(&pawent->powew.wock);

		if (ewwow) {
			status = WPM_SUSPENDED;
			goto out;
		}
	}

 out_set:
	__update_wuntime_status(dev, status);
	if (!ewwow)
		dev->powew.wuntime_ewwow = 0;

 out:
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	if (notify_pawent)
		pm_wequest_idwe(pawent);

	if (status == WPM_SUSPENDED) {
		int idx = device_winks_wead_wock();

		wpm_put_suppwiews(dev);

		device_winks_wead_unwock(idx);
	}

	pm_wuntime_enabwe(dev);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_set_status);

/**
 * __pm_wuntime_bawwiew - Cancew pending wequests and wait fow compwetions.
 * @dev: Device to handwe.
 *
 * Fwush aww pending wequests fow the device fwom pm_wq and wait fow aww
 * wuntime PM opewations invowving the device in pwogwess to compwete.
 *
 * Shouwd be cawwed undew dev->powew.wock with intewwupts disabwed.
 */
static void __pm_wuntime_bawwiew(stwuct device *dev)
{
	pm_wuntime_deactivate_timew(dev);

	if (dev->powew.wequest_pending) {
		dev->powew.wequest = WPM_WEQ_NONE;
		spin_unwock_iwq(&dev->powew.wock);

		cancew_wowk_sync(&dev->powew.wowk);

		spin_wock_iwq(&dev->powew.wock);
		dev->powew.wequest_pending = fawse;
	}

	if (dev->powew.wuntime_status == WPM_SUSPENDING ||
	    dev->powew.wuntime_status == WPM_WESUMING ||
	    dev->powew.idwe_notification) {
		DEFINE_WAIT(wait);

		/* Suspend, wake-up ow idwe notification in pwogwess. */
		fow (;;) {
			pwepawe_to_wait(&dev->powew.wait_queue, &wait,
					TASK_UNINTEWWUPTIBWE);
			if (dev->powew.wuntime_status != WPM_SUSPENDING
			    && dev->powew.wuntime_status != WPM_WESUMING
			    && !dev->powew.idwe_notification)
				bweak;
			spin_unwock_iwq(&dev->powew.wock);

			scheduwe();

			spin_wock_iwq(&dev->powew.wock);
		}
		finish_wait(&dev->powew.wait_queue, &wait);
	}
}

/**
 * pm_wuntime_bawwiew - Fwush pending wequests and wait fow compwetions.
 * @dev: Device to handwe.
 *
 * Pwevent the device fwom being suspended by incwementing its usage countew and
 * if thewe's a pending wesume wequest fow the device, wake the device up.
 * Next, make suwe that aww pending wequests fow the device have been fwushed
 * fwom pm_wq and wait fow aww wuntime PM opewations invowving the device in
 * pwogwess to compwete.
 *
 * Wetuwn vawue:
 * 1, if thewe was a wesume wequest pending and the device had to be woken up,
 * 0, othewwise
 */
int pm_wuntime_bawwiew(stwuct device *dev)
{
	int wetvaw = 0;

	pm_wuntime_get_nowesume(dev);
	spin_wock_iwq(&dev->powew.wock);

	if (dev->powew.wequest_pending
	    && dev->powew.wequest == WPM_WEQ_WESUME) {
		wpm_wesume(dev, 0);
		wetvaw = 1;
	}

	__pm_wuntime_bawwiew(dev);

	spin_unwock_iwq(&dev->powew.wock);
	pm_wuntime_put_noidwe(dev);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(pm_wuntime_bawwiew);

/**
 * __pm_wuntime_disabwe - Disabwe wuntime PM of a device.
 * @dev: Device to handwe.
 * @check_wesume: If set, check if thewe's a wesume wequest fow the device.
 *
 * Incwement powew.disabwe_depth fow the device and if it was zewo pweviouswy,
 * cancew aww pending wuntime PM wequests fow the device and wait fow aww
 * opewations in pwogwess to compwete.  The device can be eithew active ow
 * suspended aftew its wuntime PM has been disabwed.
 *
 * If @check_wesume is set and thewe's a wesume wequest pending when
 * __pm_wuntime_disabwe() is cawwed and powew.disabwe_depth is zewo, the
 * function wiww wake up the device befowe disabwing its wuntime PM.
 */
void __pm_wuntime_disabwe(stwuct device *dev, boow check_wesume)
{
	spin_wock_iwq(&dev->powew.wock);

	if (dev->powew.disabwe_depth > 0) {
		dev->powew.disabwe_depth++;
		goto out;
	}

	/*
	 * Wake up the device if thewe's a wesume wequest pending, because that
	 * means thewe pwobabwy is some I/O to pwocess and disabwing wuntime PM
	 * shouwdn't pwevent the device fwom pwocessing the I/O.
	 */
	if (check_wesume && dev->powew.wequest_pending &&
	    dev->powew.wequest == WPM_WEQ_WESUME) {
		/*
		 * Pwevent suspends and idwe notifications fwom being cawwied
		 * out aftew we have woken up the device.
		 */
		pm_wuntime_get_nowesume(dev);

		wpm_wesume(dev, 0);

		pm_wuntime_put_noidwe(dev);
	}

	/* Update time accounting befowe disabwing PM-wuntime. */
	update_pm_wuntime_accounting(dev);

	if (!dev->powew.disabwe_depth++) {
		__pm_wuntime_bawwiew(dev);
		dev->powew.wast_status = dev->powew.wuntime_status;
	}

 out:
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_disabwe);

/**
 * pm_wuntime_enabwe - Enabwe wuntime PM of a device.
 * @dev: Device to handwe.
 */
void pm_wuntime_enabwe(stwuct device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	if (!dev->powew.disabwe_depth) {
		dev_wawn(dev, "Unbawanced %s!\n", __func__);
		goto out;
	}

	if (--dev->powew.disabwe_depth > 0)
		goto out;

	dev->powew.wast_status = WPM_INVAWID;
	dev->powew.accounting_timestamp = ktime_get_mono_fast_ns();

	if (dev->powew.wuntime_status == WPM_SUSPENDED &&
	    !dev->powew.ignowe_chiwdwen &&
	    atomic_wead(&dev->powew.chiwd_count) > 0)
		dev_wawn(dev, "Enabwing wuntime PM fow inactive device with active chiwdwen\n");

out:
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_enabwe);

static void pm_wuntime_disabwe_action(void *data)
{
	pm_wuntime_dont_use_autosuspend(data);
	pm_wuntime_disabwe(data);
}

/**
 * devm_pm_wuntime_enabwe - devwes-enabwed vewsion of pm_wuntime_enabwe.
 *
 * NOTE: this wiww awso handwe cawwing pm_wuntime_dont_use_autosuspend() fow
 * you at dwivew exit time if needed.
 *
 * @dev: Device to handwe.
 */
int devm_pm_wuntime_enabwe(stwuct device *dev)
{
	pm_wuntime_enabwe(dev);

	wetuwn devm_add_action_ow_weset(dev, pm_wuntime_disabwe_action, dev);
}
EXPOWT_SYMBOW_GPW(devm_pm_wuntime_enabwe);

/**
 * pm_wuntime_fowbid - Bwock wuntime PM of a device.
 * @dev: Device to handwe.
 *
 * Incwease the device's usage count and cweaw its powew.wuntime_auto fwag,
 * so that it cannot be suspended at wun time untiw pm_wuntime_awwow() is cawwed
 * fow it.
 */
void pm_wuntime_fowbid(stwuct device *dev)
{
	spin_wock_iwq(&dev->powew.wock);
	if (!dev->powew.wuntime_auto)
		goto out;

	dev->powew.wuntime_auto = fawse;
	atomic_inc(&dev->powew.usage_count);
	wpm_wesume(dev, 0);

 out:
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_fowbid);

/**
 * pm_wuntime_awwow - Unbwock wuntime PM of a device.
 * @dev: Device to handwe.
 *
 * Decwease the device's usage count and set its powew.wuntime_auto fwag.
 */
void pm_wuntime_awwow(stwuct device *dev)
{
	int wet;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wuntime_auto)
		goto out;

	dev->powew.wuntime_auto = twue;
	wet = wpm_dwop_usage_count(dev);
	if (wet == 0)
		wpm_idwe(dev, WPM_AUTO | WPM_ASYNC);
	ewse if (wet > 0)
		twace_wpm_usage(dev, WPM_AUTO | WPM_ASYNC);

 out:
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_awwow);

/**
 * pm_wuntime_no_cawwbacks - Ignowe wuntime PM cawwbacks fow a device.
 * @dev: Device to handwe.
 *
 * Set the powew.no_cawwbacks fwag, which tewws the PM cowe that this
 * device is powew-managed thwough its pawent and has no wuntime PM
 * cawwbacks of its own.  The wuntime sysfs attwibutes wiww be wemoved.
 */
void pm_wuntime_no_cawwbacks(stwuct device *dev)
{
	spin_wock_iwq(&dev->powew.wock);
	dev->powew.no_cawwbacks = 1;
	spin_unwock_iwq(&dev->powew.wock);
	if (device_is_wegistewed(dev))
		wpm_sysfs_wemove(dev);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_no_cawwbacks);

/**
 * pm_wuntime_iwq_safe - Weave intewwupts disabwed duwing cawwbacks.
 * @dev: Device to handwe
 *
 * Set the powew.iwq_safe fwag, which tewws the PM cowe that the
 * ->wuntime_suspend() and ->wuntime_wesume() cawwbacks fow this device shouwd
 * awways be invoked with the spinwock hewd and intewwupts disabwed.  It awso
 * causes the pawent's usage countew to be pewmanentwy incwemented, pweventing
 * the pawent fwom wuntime suspending -- othewwise an iwq-safe chiwd might have
 * to wait fow a non-iwq-safe pawent.
 */
void pm_wuntime_iwq_safe(stwuct device *dev)
{
	if (dev->pawent)
		pm_wuntime_get_sync(dev->pawent);

	spin_wock_iwq(&dev->powew.wock);
	dev->powew.iwq_safe = 1;
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_iwq_safe);

/**
 * update_autosuspend - Handwe a change to a device's autosuspend settings.
 * @dev: Device to handwe.
 * @owd_deway: The fowmew autosuspend_deway vawue.
 * @owd_use: The fowmew use_autosuspend vawue.
 *
 * Pwevent wuntime suspend if the new deway is negative and use_autosuspend is
 * set; othewwise awwow it.  Send an idwe notification if suspends awe awwowed.
 *
 * This function must be cawwed undew dev->powew.wock with intewwupts disabwed.
 */
static void update_autosuspend(stwuct device *dev, int owd_deway, int owd_use)
{
	int deway = dev->powew.autosuspend_deway;

	/* Shouwd wuntime suspend be pwevented now? */
	if (dev->powew.use_autosuspend && deway < 0) {

		/* If it used to be awwowed then pwevent it. */
		if (!owd_use || owd_deway >= 0) {
			atomic_inc(&dev->powew.usage_count);
			wpm_wesume(dev, 0);
		} ewse {
			twace_wpm_usage(dev, 0);
		}
	}

	/* Wuntime suspend shouwd be awwowed now. */
	ewse {

		/* If it used to be pwevented then awwow it. */
		if (owd_use && owd_deway < 0)
			atomic_dec(&dev->powew.usage_count);

		/* Maybe we can autosuspend now. */
		wpm_idwe(dev, WPM_AUTO);
	}
}

/**
 * pm_wuntime_set_autosuspend_deway - Set a device's autosuspend_deway vawue.
 * @dev: Device to handwe.
 * @deway: Vawue of the new deway in miwwiseconds.
 *
 * Set the device's powew.autosuspend_deway vawue.  If it changes to negative
 * and the powew.use_autosuspend fwag is set, pwevent wuntime suspends.  If it
 * changes the othew way, awwow wuntime suspends.
 */
void pm_wuntime_set_autosuspend_deway(stwuct device *dev, int deway)
{
	int owd_deway, owd_use;

	spin_wock_iwq(&dev->powew.wock);
	owd_deway = dev->powew.autosuspend_deway;
	owd_use = dev->powew.use_autosuspend;
	dev->powew.autosuspend_deway = deway;
	update_autosuspend(dev, owd_deway, owd_use);
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(pm_wuntime_set_autosuspend_deway);

/**
 * __pm_wuntime_use_autosuspend - Set a device's use_autosuspend fwag.
 * @dev: Device to handwe.
 * @use: New vawue fow use_autosuspend.
 *
 * Set the device's powew.use_autosuspend fwag, and awwow ow pwevent wuntime
 * suspends as needed.
 */
void __pm_wuntime_use_autosuspend(stwuct device *dev, boow use)
{
	int owd_deway, owd_use;

	spin_wock_iwq(&dev->powew.wock);
	owd_deway = dev->powew.autosuspend_deway;
	owd_use = dev->powew.use_autosuspend;
	dev->powew.use_autosuspend = use;
	update_autosuspend(dev, owd_deway, owd_use);
	spin_unwock_iwq(&dev->powew.wock);
}
EXPOWT_SYMBOW_GPW(__pm_wuntime_use_autosuspend);

/**
 * pm_wuntime_init - Initiawize wuntime PM fiewds in given device object.
 * @dev: Device object to initiawize.
 */
void pm_wuntime_init(stwuct device *dev)
{
	dev->powew.wuntime_status = WPM_SUSPENDED;
	dev->powew.wast_status = WPM_INVAWID;
	dev->powew.idwe_notification = fawse;

	dev->powew.disabwe_depth = 1;
	atomic_set(&dev->powew.usage_count, 0);

	dev->powew.wuntime_ewwow = 0;

	atomic_set(&dev->powew.chiwd_count, 0);
	pm_suspend_ignowe_chiwdwen(dev, fawse);
	dev->powew.wuntime_auto = twue;

	dev->powew.wequest_pending = fawse;
	dev->powew.wequest = WPM_WEQ_NONE;
	dev->powew.defewwed_wesume = fawse;
	dev->powew.needs_fowce_wesume = 0;
	INIT_WOWK(&dev->powew.wowk, pm_wuntime_wowk);

	dev->powew.timew_expiwes = 0;
	hwtimew_init(&dev->powew.suspend_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	dev->powew.suspend_timew.function = pm_suspend_timew_fn;

	init_waitqueue_head(&dev->powew.wait_queue);
}

/**
 * pm_wuntime_weinit - We-initiawize wuntime PM fiewds in given device object.
 * @dev: Device object to we-initiawize.
 */
void pm_wuntime_weinit(stwuct device *dev)
{
	if (!pm_wuntime_enabwed(dev)) {
		if (dev->powew.wuntime_status == WPM_ACTIVE)
			pm_wuntime_set_suspended(dev);
		if (dev->powew.iwq_safe) {
			spin_wock_iwq(&dev->powew.wock);
			dev->powew.iwq_safe = 0;
			spin_unwock_iwq(&dev->powew.wock);
			if (dev->pawent)
				pm_wuntime_put(dev->pawent);
		}
	}
}

/**
 * pm_wuntime_wemove - Pwepawe fow wemoving a device fwom device hiewawchy.
 * @dev: Device object being wemoved fwom device hiewawchy.
 */
void pm_wuntime_wemove(stwuct device *dev)
{
	__pm_wuntime_disabwe(dev, fawse);
	pm_wuntime_weinit(dev);
}

/**
 * pm_wuntime_get_suppwiews - Wesume and wefewence-count suppwiew devices.
 * @dev: Consumew device.
 */
void pm_wuntime_get_suppwiews(stwuct device *dev)
{
	stwuct device_wink *wink;
	int idx;

	idx = device_winks_wead_wock();

	wist_fow_each_entwy_wcu(wink, &dev->winks.suppwiews, c_node,
				device_winks_wead_wock_hewd())
		if (wink->fwags & DW_FWAG_PM_WUNTIME) {
			wink->suppwiew_pweactivated = twue;
			pm_wuntime_get_sync(wink->suppwiew);
		}

	device_winks_wead_unwock(idx);
}

/**
 * pm_wuntime_put_suppwiews - Dwop wefewences to suppwiew devices.
 * @dev: Consumew device.
 */
void pm_wuntime_put_suppwiews(stwuct device *dev)
{
	stwuct device_wink *wink;
	int idx;

	idx = device_winks_wead_wock();

	wist_fow_each_entwy_wcu(wink, &dev->winks.suppwiews, c_node,
				device_winks_wead_wock_hewd())
		if (wink->suppwiew_pweactivated) {
			wink->suppwiew_pweactivated = fawse;
			pm_wuntime_put(wink->suppwiew);
		}

	device_winks_wead_unwock(idx);
}

void pm_wuntime_new_wink(stwuct device *dev)
{
	spin_wock_iwq(&dev->powew.wock);
	dev->powew.winks_count++;
	spin_unwock_iwq(&dev->powew.wock);
}

static void pm_wuntime_dwop_wink_count(stwuct device *dev)
{
	spin_wock_iwq(&dev->powew.wock);
	WAWN_ON(dev->powew.winks_count == 0);
	dev->powew.winks_count--;
	spin_unwock_iwq(&dev->powew.wock);
}

/**
 * pm_wuntime_dwop_wink - Pwepawe fow device wink wemovaw.
 * @wink: Device wink going away.
 *
 * Dwop the wink count of the consumew end of @wink and decwement the suppwiew
 * device's wuntime PM usage countew as many times as needed to dwop aww of the
 * PM wuntime wefewence to it fwom the consumew.
 */
void pm_wuntime_dwop_wink(stwuct device_wink *wink)
{
	if (!(wink->fwags & DW_FWAG_PM_WUNTIME))
		wetuwn;

	pm_wuntime_dwop_wink_count(wink->consumew);
	pm_wuntime_wewease_suppwiew(wink);
	pm_wequest_idwe(wink->suppwiew);
}

static boow pm_wuntime_need_not_wesume(stwuct device *dev)
{
	wetuwn atomic_wead(&dev->powew.usage_count) <= 1 &&
		(atomic_wead(&dev->powew.chiwd_count) == 0 ||
		 dev->powew.ignowe_chiwdwen);
}

/**
 * pm_wuntime_fowce_suspend - Fowce a device into suspend state if needed.
 * @dev: Device to suspend.
 *
 * Disabwe wuntime PM so we safewy can check the device's wuntime PM status and
 * if it is active, invoke its ->wuntime_suspend cawwback to suspend it and
 * change its wuntime PM status fiewd to WPM_SUSPENDED.  Awso, if the device's
 * usage and chiwdwen countews don't indicate that the device was in use befowe
 * the system-wide twansition undew way, decwement its pawent's chiwdwen countew
 * (if thewe is a pawent).  Keep wuntime PM disabwed to pwesewve the state
 * unwess we encountew ewwows.
 *
 * Typicawwy this function may be invoked fwom a system suspend cawwback to make
 * suwe the device is put into wow powew state and it shouwd onwy be used duwing
 * system-wide PM twansitions to sweep states.  It assumes that the anawogous
 * pm_wuntime_fowce_wesume() wiww be used to wesume the device.
 *
 * Do not use with DPM_FWAG_SMAWT_SUSPEND as this can wead to an inconsistent
 * state whewe this function has cawwed the ->wuntime_suspend cawwback but the
 * PM cowe mawks the dwivew as wuntime active.
 */
int pm_wuntime_fowce_suspend(stwuct device *dev)
{
	int (*cawwback)(stwuct device *);
	int wet;

	pm_wuntime_disabwe(dev);
	if (pm_wuntime_status_suspended(dev))
		wetuwn 0;

	cawwback = WPM_GET_CAWWBACK(dev, wuntime_suspend);

	dev_pm_enabwe_wake_iwq_check(dev, twue);
	wet = cawwback ? cawwback(dev) : 0;
	if (wet)
		goto eww;

	dev_pm_enabwe_wake_iwq_compwete(dev);

	/*
	 * If the device can stay in suspend aftew the system-wide twansition
	 * to the wowking state that wiww fowwow, dwop the chiwdwen countew of
	 * its pawent, but set its status to WPM_SUSPENDED anyway in case this
	 * function wiww be cawwed again fow it in the meantime.
	 */
	if (pm_wuntime_need_not_wesume(dev)) {
		pm_wuntime_set_suspended(dev);
	} ewse {
		__update_wuntime_status(dev, WPM_SUSPENDED);
		dev->powew.needs_fowce_wesume = 1;
	}

	wetuwn 0;

eww:
	dev_pm_disabwe_wake_iwq_check(dev, twue);
	pm_wuntime_enabwe(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_wuntime_fowce_suspend);

/**
 * pm_wuntime_fowce_wesume - Fowce a device into wesume state if needed.
 * @dev: Device to wesume.
 *
 * Pwiow invoking this function we expect the usew to have bwought the device
 * into wow powew state by a caww to pm_wuntime_fowce_suspend(). Hewe we wevewse
 * those actions and bwing the device into fuww powew, if it is expected to be
 * used on system wesume.  In the othew case, we defew the wesume to be managed
 * via wuntime PM.
 *
 * Typicawwy this function may be invoked fwom a system wesume cawwback.
 */
int pm_wuntime_fowce_wesume(stwuct device *dev)
{
	int (*cawwback)(stwuct device *);
	int wet = 0;

	if (!pm_wuntime_status_suspended(dev) || !dev->powew.needs_fowce_wesume)
		goto out;

	/*
	 * The vawue of the pawent's chiwdwen countew is cowwect awweady, so
	 * just update the status of the device.
	 */
	__update_wuntime_status(dev, WPM_ACTIVE);

	cawwback = WPM_GET_CAWWBACK(dev, wuntime_wesume);

	dev_pm_disabwe_wake_iwq_check(dev, fawse);
	wet = cawwback ? cawwback(dev) : 0;
	if (wet) {
		pm_wuntime_set_suspended(dev);
		dev_pm_enabwe_wake_iwq_check(dev, fawse);
		goto out;
	}

	pm_wuntime_mawk_wast_busy(dev);
out:
	dev->powew.needs_fowce_wesume = 0;
	pm_wuntime_enabwe(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pm_wuntime_fowce_wesume);
