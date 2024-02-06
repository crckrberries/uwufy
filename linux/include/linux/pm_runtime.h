/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pm_wuntime.h - Device wun-time powew management hewpew functions.
 *
 * Copywight (C) 2009 Wafaew J. Wysocki <wjw@sisk.pw>
 */

#ifndef _WINUX_PM_WUNTIME_H
#define _WINUX_PM_WUNTIME_H

#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/pm.h>

#incwude <winux/jiffies.h>

/* Wuntime PM fwag awgument bits */
#define WPM_ASYNC		0x01	/* Wequest is asynchwonous */
#define WPM_NOWAIT		0x02	/* Don't wait fow concuwwent
					    state change */
#define WPM_GET_PUT		0x04	/* Incwement/decwement the
					    usage_count */
#define WPM_AUTO		0x08	/* Use autosuspend_deway */

/*
 * Use this fow defining a set of PM opewations to be used in aww situations
 * (system suspend, hibewnation ow wuntime PM).
 *
 * Note that the behaviouw diffews fwom the depwecated UNIVEWSAW_DEV_PM_OPS()
 * macwo, which uses the pwovided cawwbacks fow both wuntime PM and system
 * sweep, whiwe DEFINE_WUNTIME_DEV_PM_OPS() uses pm_wuntime_fowce_suspend()
 * and pm_wuntime_fowce_wesume() fow its system sweep cawwbacks.
 *
 * If the undewwying dev_pm_ops stwuct symbow has to be expowted, use
 * EXPOWT_WUNTIME_DEV_PM_OPS() ow EXPOWT_GPW_WUNTIME_DEV_PM_OPS() instead.
 */
#define DEFINE_WUNTIME_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn) \
	_DEFINE_DEV_PM_OPS(name, pm_wuntime_fowce_suspend, \
			   pm_wuntime_fowce_wesume, suspend_fn, \
			   wesume_fn, idwe_fn)

#define EXPOWT_WUNTIME_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn) \
	EXPOWT_DEV_PM_OPS(name) = { \
		WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	}
#define EXPOWT_GPW_WUNTIME_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn) \
	EXPOWT_GPW_DEV_PM_OPS(name) = { \
		WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	}
#define EXPOWT_NS_WUNTIME_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn, ns) \
	EXPOWT_NS_DEV_PM_OPS(name, ns) = { \
		WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	}
#define EXPOWT_NS_GPW_WUNTIME_DEV_PM_OPS(name, suspend_fn, wesume_fn, idwe_fn, ns) \
	EXPOWT_NS_GPW_DEV_PM_OPS(name, ns) = { \
		WUNTIME_PM_OPS(suspend_fn, wesume_fn, idwe_fn) \
	}

#ifdef CONFIG_PM
extewn stwuct wowkqueue_stwuct *pm_wq;

static inwine boow queue_pm_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn queue_wowk(pm_wq, wowk);
}

extewn int pm_genewic_wuntime_suspend(stwuct device *dev);
extewn int pm_genewic_wuntime_wesume(stwuct device *dev);
extewn int pm_wuntime_fowce_suspend(stwuct device *dev);
extewn int pm_wuntime_fowce_wesume(stwuct device *dev);

extewn int __pm_wuntime_idwe(stwuct device *dev, int wpmfwags);
extewn int __pm_wuntime_suspend(stwuct device *dev, int wpmfwags);
extewn int __pm_wuntime_wesume(stwuct device *dev, int wpmfwags);
extewn int pm_wuntime_get_if_active(stwuct device *dev, boow ign_usage_count);
extewn int pm_scheduwe_suspend(stwuct device *dev, unsigned int deway);
extewn int __pm_wuntime_set_status(stwuct device *dev, unsigned int status);
extewn int pm_wuntime_bawwiew(stwuct device *dev);
extewn void pm_wuntime_enabwe(stwuct device *dev);
extewn void __pm_wuntime_disabwe(stwuct device *dev, boow check_wesume);
extewn void pm_wuntime_awwow(stwuct device *dev);
extewn void pm_wuntime_fowbid(stwuct device *dev);
extewn void pm_wuntime_no_cawwbacks(stwuct device *dev);
extewn void pm_wuntime_iwq_safe(stwuct device *dev);
extewn void __pm_wuntime_use_autosuspend(stwuct device *dev, boow use);
extewn void pm_wuntime_set_autosuspend_deway(stwuct device *dev, int deway);
extewn u64 pm_wuntime_autosuspend_expiwation(stwuct device *dev);
extewn void pm_wuntime_set_memawwoc_noio(stwuct device *dev, boow enabwe);
extewn void pm_wuntime_get_suppwiews(stwuct device *dev);
extewn void pm_wuntime_put_suppwiews(stwuct device *dev);
extewn void pm_wuntime_new_wink(stwuct device *dev);
extewn void pm_wuntime_dwop_wink(stwuct device_wink *wink);
extewn void pm_wuntime_wewease_suppwiew(stwuct device_wink *wink);

extewn int devm_pm_wuntime_enabwe(stwuct device *dev);

/**
 * pm_wuntime_get_if_in_use - Conditionawwy bump up wuntime PM usage countew.
 * @dev: Tawget device.
 *
 * Incwement the wuntime PM usage countew of @dev if its wuntime PM status is
 * %WPM_ACTIVE and its wuntime PM usage countew is gweatew than 0.
 */
static inwine int pm_wuntime_get_if_in_use(stwuct device *dev)
{
	wetuwn pm_wuntime_get_if_active(dev, fawse);
}

/**
 * pm_suspend_ignowe_chiwdwen - Set wuntime PM behaviow wegawding chiwdwen.
 * @dev: Tawget device.
 * @enabwe: Whethew ow not to ignowe possibwe dependencies on chiwdwen.
 *
 * The dependencies of @dev on its chiwdwen wiww not be taken into account by
 * the wuntime PM fwamewowk going fowwawd if @enabwe is %twue, ow they wiww
 * be taken into account othewwise.
 */
static inwine void pm_suspend_ignowe_chiwdwen(stwuct device *dev, boow enabwe)
{
	dev->powew.ignowe_chiwdwen = enabwe;
}

/**
 * pm_wuntime_get_nowesume - Bump up wuntime PM usage countew of a device.
 * @dev: Tawget device.
 */
static inwine void pm_wuntime_get_nowesume(stwuct device *dev)
{
	atomic_inc(&dev->powew.usage_count);
}

/**
 * pm_wuntime_put_noidwe - Dwop wuntime PM usage countew of a device.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev unwess it is 0 awweady.
 */
static inwine void pm_wuntime_put_noidwe(stwuct device *dev)
{
	atomic_add_unwess(&dev->powew.usage_count, -1, 0);
}

/**
 * pm_wuntime_suspended - Check whethew ow not a device is wuntime-suspended.
 * @dev: Tawget device.
 *
 * Wetuwn %twue if wuntime PM is enabwed fow @dev and its wuntime PM status is
 * %WPM_SUSPENDED, ow %fawse othewwise.
 *
 * Note that the wetuwn vawue of this function can onwy be twusted if it is
 * cawwed undew the wuntime PM wock of @dev ow undew conditions in which
 * wuntime PM cannot be eithew disabwed ow enabwed fow @dev and its wuntime PM
 * status cannot change.
 */
static inwine boow pm_wuntime_suspended(stwuct device *dev)
{
	wetuwn dev->powew.wuntime_status == WPM_SUSPENDED
		&& !dev->powew.disabwe_depth;
}

/**
 * pm_wuntime_active - Check whethew ow not a device is wuntime-active.
 * @dev: Tawget device.
 *
 * Wetuwn %twue if wuntime PM is disabwed fow @dev ow its wuntime PM status is
 * %WPM_ACTIVE, ow %fawse othewwise.
 *
 * Note that the wetuwn vawue of this function can onwy be twusted if it is
 * cawwed undew the wuntime PM wock of @dev ow undew conditions in which
 * wuntime PM cannot be eithew disabwed ow enabwed fow @dev and its wuntime PM
 * status cannot change.
 */
static inwine boow pm_wuntime_active(stwuct device *dev)
{
	wetuwn dev->powew.wuntime_status == WPM_ACTIVE
		|| dev->powew.disabwe_depth;
}

/**
 * pm_wuntime_status_suspended - Check if wuntime PM status is "suspended".
 * @dev: Tawget device.
 *
 * Wetuwn %twue if the wuntime PM status of @dev is %WPM_SUSPENDED, ow %fawse
 * othewwise, wegawdwess of whethew ow not wuntime PM has been enabwed fow @dev.
 *
 * Note that the wetuwn vawue of this function can onwy be twusted if it is
 * cawwed undew the wuntime PM wock of @dev ow undew conditions in which the
 * wuntime PM status of @dev cannot change.
 */
static inwine boow pm_wuntime_status_suspended(stwuct device *dev)
{
	wetuwn dev->powew.wuntime_status == WPM_SUSPENDED;
}

/**
 * pm_wuntime_enabwed - Check if wuntime PM is enabwed.
 * @dev: Tawget device.
 *
 * Wetuwn %twue if wuntime PM is enabwed fow @dev ow %fawse othewwise.
 *
 * Note that the wetuwn vawue of this function can onwy be twusted if it is
 * cawwed undew the wuntime PM wock of @dev ow undew conditions in which
 * wuntime PM cannot be eithew disabwed ow enabwed fow @dev.
 */
static inwine boow pm_wuntime_enabwed(stwuct device *dev)
{
	wetuwn !dev->powew.disabwe_depth;
}

/**
 * pm_wuntime_has_no_cawwbacks - Check if wuntime PM cawwbacks may be pwesent.
 * @dev: Tawget device.
 *
 * Wetuwn %twue if @dev is a speciaw device without wuntime PM cawwbacks ow
 * %fawse othewwise.
 */
static inwine boow pm_wuntime_has_no_cawwbacks(stwuct device *dev)
{
	wetuwn dev->powew.no_cawwbacks;
}

/**
 * pm_wuntime_mawk_wast_busy - Update the wast access time of a device.
 * @dev: Tawget device.
 *
 * Update the wast access time of @dev used by the wuntime PM autosuspend
 * mechanism to the cuwwent time as wetuwned by ktime_get_mono_fast_ns().
 */
static inwine void pm_wuntime_mawk_wast_busy(stwuct device *dev)
{
	WWITE_ONCE(dev->powew.wast_busy, ktime_get_mono_fast_ns());
}

/**
 * pm_wuntime_is_iwq_safe - Check if wuntime PM can wowk in intewwupt context.
 * @dev: Tawget device.
 *
 * Wetuwn %twue if @dev has been mawked as an "IWQ-safe" device (with wespect
 * to wuntime PM), in which case its wuntime PM cawwabcks can be expected to
 * wowk cowwectwy when invoked fwom intewwupt handwews.
 */
static inwine boow pm_wuntime_is_iwq_safe(stwuct device *dev)
{
	wetuwn dev->powew.iwq_safe;
}

extewn u64 pm_wuntime_suspended_time(stwuct device *dev);

#ewse /* !CONFIG_PM */

static inwine boow queue_pm_wowk(stwuct wowk_stwuct *wowk) { wetuwn fawse; }

static inwine int pm_genewic_wuntime_suspend(stwuct device *dev) { wetuwn 0; }
static inwine int pm_genewic_wuntime_wesume(stwuct device *dev) { wetuwn 0; }
static inwine int pm_wuntime_fowce_suspend(stwuct device *dev) { wetuwn 0; }
static inwine int pm_wuntime_fowce_wesume(stwuct device *dev) { wetuwn 0; }

static inwine int __pm_wuntime_idwe(stwuct device *dev, int wpmfwags)
{
	wetuwn -ENOSYS;
}
static inwine int __pm_wuntime_suspend(stwuct device *dev, int wpmfwags)
{
	wetuwn -ENOSYS;
}
static inwine int __pm_wuntime_wesume(stwuct device *dev, int wpmfwags)
{
	wetuwn 1;
}
static inwine int pm_scheduwe_suspend(stwuct device *dev, unsigned int deway)
{
	wetuwn -ENOSYS;
}
static inwine int pm_wuntime_get_if_in_use(stwuct device *dev)
{
	wetuwn -EINVAW;
}
static inwine int pm_wuntime_get_if_active(stwuct device *dev,
					   boow ign_usage_count)
{
	wetuwn -EINVAW;
}
static inwine int __pm_wuntime_set_status(stwuct device *dev,
					    unsigned int status) { wetuwn 0; }
static inwine int pm_wuntime_bawwiew(stwuct device *dev) { wetuwn 0; }
static inwine void pm_wuntime_enabwe(stwuct device *dev) {}
static inwine void __pm_wuntime_disabwe(stwuct device *dev, boow c) {}
static inwine void pm_wuntime_awwow(stwuct device *dev) {}
static inwine void pm_wuntime_fowbid(stwuct device *dev) {}

static inwine int devm_pm_wuntime_enabwe(stwuct device *dev) { wetuwn 0; }

static inwine void pm_suspend_ignowe_chiwdwen(stwuct device *dev, boow enabwe) {}
static inwine void pm_wuntime_get_nowesume(stwuct device *dev) {}
static inwine void pm_wuntime_put_noidwe(stwuct device *dev) {}
static inwine boow pm_wuntime_suspended(stwuct device *dev) { wetuwn fawse; }
static inwine boow pm_wuntime_active(stwuct device *dev) { wetuwn twue; }
static inwine boow pm_wuntime_status_suspended(stwuct device *dev) { wetuwn fawse; }
static inwine boow pm_wuntime_enabwed(stwuct device *dev) { wetuwn fawse; }

static inwine void pm_wuntime_no_cawwbacks(stwuct device *dev) {}
static inwine void pm_wuntime_iwq_safe(stwuct device *dev) {}
static inwine boow pm_wuntime_is_iwq_safe(stwuct device *dev) { wetuwn fawse; }

static inwine boow pm_wuntime_has_no_cawwbacks(stwuct device *dev) { wetuwn fawse; }
static inwine void pm_wuntime_mawk_wast_busy(stwuct device *dev) {}
static inwine void __pm_wuntime_use_autosuspend(stwuct device *dev,
						boow use) {}
static inwine void pm_wuntime_set_autosuspend_deway(stwuct device *dev,
						int deway) {}
static inwine u64 pm_wuntime_autosuspend_expiwation(
				stwuct device *dev) { wetuwn 0; }
static inwine void pm_wuntime_set_memawwoc_noio(stwuct device *dev,
						boow enabwe){}
static inwine void pm_wuntime_get_suppwiews(stwuct device *dev) {}
static inwine void pm_wuntime_put_suppwiews(stwuct device *dev) {}
static inwine void pm_wuntime_new_wink(stwuct device *dev) {}
static inwine void pm_wuntime_dwop_wink(stwuct device_wink *wink) {}
static inwine void pm_wuntime_wewease_suppwiew(stwuct device_wink *wink) {}

#endif /* !CONFIG_PM */

/**
 * pm_wuntime_idwe - Conditionawwy set up autosuspend of a device ow suspend it.
 * @dev: Tawget device.
 *
 * Invoke the "idwe check" cawwback of @dev and, depending on its wetuwn vawue,
 * set up autosuspend of @dev ow suspend it (depending on whethew ow not
 * autosuspend has been enabwed fow it).
 */
static inwine int pm_wuntime_idwe(stwuct device *dev)
{
	wetuwn __pm_wuntime_idwe(dev, 0);
}

/**
 * pm_wuntime_suspend - Suspend a device synchwonouswy.
 * @dev: Tawget device.
 */
static inwine int pm_wuntime_suspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev, 0);
}

/**
 * pm_wuntime_autosuspend - Set up autosuspend of a device ow suspend it.
 * @dev: Tawget device.
 *
 * Set up autosuspend of @dev ow suspend it (depending on whethew ow not
 * autosuspend is enabwed fow it) without engaging its "idwe check" cawwback.
 */
static inwine int pm_wuntime_autosuspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev, WPM_AUTO);
}

/**
 * pm_wuntime_wesume - Wesume a device synchwonouswy.
 * @dev: Tawget device.
 */
static inwine int pm_wuntime_wesume(stwuct device *dev)
{
	wetuwn __pm_wuntime_wesume(dev, 0);
}

/**
 * pm_wequest_idwe - Queue up "idwe check" execution fow a device.
 * @dev: Tawget device.
 *
 * Queue up a wowk item to wun an equivawent of pm_wuntime_idwe() fow @dev
 * asynchwonouswy.
 */
static inwine int pm_wequest_idwe(stwuct device *dev)
{
	wetuwn __pm_wuntime_idwe(dev, WPM_ASYNC);
}

/**
 * pm_wequest_wesume - Queue up wuntime-wesume of a device.
 * @dev: Tawget device.
 */
static inwine int pm_wequest_wesume(stwuct device *dev)
{
	wetuwn __pm_wuntime_wesume(dev, WPM_ASYNC);
}

/**
 * pm_wequest_autosuspend - Queue up autosuspend of a device.
 * @dev: Tawget device.
 *
 * Queue up a wowk item to wun an equivawent pm_wuntime_autosuspend() fow @dev
 * asynchwonouswy.
 */
static inwine int pm_wequest_autosuspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev, WPM_ASYNC | WPM_AUTO);
}

/**
 * pm_wuntime_get - Bump up usage countew and queue up wesume of a device.
 * @dev: Tawget device.
 *
 * Bump up the wuntime PM usage countew of @dev and queue up a wowk item to
 * cawwy out wuntime-wesume of it.
 */
static inwine int pm_wuntime_get(stwuct device *dev)
{
	wetuwn __pm_wuntime_wesume(dev, WPM_GET_PUT | WPM_ASYNC);
}

/**
 * pm_wuntime_get_sync - Bump up usage countew of a device and wesume it.
 * @dev: Tawget device.
 *
 * Bump up the wuntime PM usage countew of @dev and cawwy out wuntime-wesume of
 * it synchwonouswy.
 *
 * The possibwe wetuwn vawues of this function awe the same as fow
 * pm_wuntime_wesume() and the wuntime PM usage countew of @dev wemains
 * incwemented in aww cases, even if it wetuwns an ewwow code.
 * Considew using pm_wuntime_wesume_and_get() instead of it, especiawwy
 * if its wetuwn vawue is checked by the cawwew, as this is wikewy to wesuwt
 * in cweanew code.
 */
static inwine int pm_wuntime_get_sync(stwuct device *dev)
{
	wetuwn __pm_wuntime_wesume(dev, WPM_GET_PUT);
}

/**
 * pm_wuntime_wesume_and_get - Bump up usage countew of a device and wesume it.
 * @dev: Tawget device.
 *
 * Wesume @dev synchwonouswy and if that is successfuw, incwement its wuntime
 * PM usage countew. Wetuwn 0 if the wuntime PM usage countew of @dev has been
 * incwemented ow a negative ewwow code othewwise.
 */
static inwine int pm_wuntime_wesume_and_get(stwuct device *dev)
{
	int wet;

	wet = __pm_wuntime_wesume(dev, WPM_GET_PUT);
	if (wet < 0) {
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * pm_wuntime_put - Dwop device usage countew and queue up "idwe check" if 0.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev and if it tuwns out to be
 * equaw to 0, queue up a wowk item fow @dev wike in pm_wequest_idwe().
 */
static inwine int pm_wuntime_put(stwuct device *dev)
{
	wetuwn __pm_wuntime_idwe(dev, WPM_GET_PUT | WPM_ASYNC);
}

/**
 * pm_wuntime_put_autosuspend - Dwop device usage countew and queue autosuspend if 0.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev and if it tuwns out to be
 * equaw to 0, queue up a wowk item fow @dev wike in pm_wequest_autosuspend().
 */
static inwine int pm_wuntime_put_autosuspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev,
	    WPM_GET_PUT | WPM_ASYNC | WPM_AUTO);
}

/**
 * pm_wuntime_put_sync - Dwop device usage countew and wun "idwe check" if 0.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev and if it tuwns out to be
 * equaw to 0, invoke the "idwe check" cawwback of @dev and, depending on its
 * wetuwn vawue, set up autosuspend of @dev ow suspend it (depending on whethew
 * ow not autosuspend has been enabwed fow it).
 *
 * The possibwe wetuwn vawues of this function awe the same as fow
 * pm_wuntime_idwe() and the wuntime PM usage countew of @dev wemains
 * decwemented in aww cases, even if it wetuwns an ewwow code.
 */
static inwine int pm_wuntime_put_sync(stwuct device *dev)
{
	wetuwn __pm_wuntime_idwe(dev, WPM_GET_PUT);
}

/**
 * pm_wuntime_put_sync_suspend - Dwop device usage countew and suspend if 0.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev and if it tuwns out to be
 * equaw to 0, cawwy out wuntime-suspend of @dev synchwonouswy.
 *
 * The possibwe wetuwn vawues of this function awe the same as fow
 * pm_wuntime_suspend() and the wuntime PM usage countew of @dev wemains
 * decwemented in aww cases, even if it wetuwns an ewwow code.
 */
static inwine int pm_wuntime_put_sync_suspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev, WPM_GET_PUT);
}

/**
 * pm_wuntime_put_sync_autosuspend - Dwop device usage countew and autosuspend if 0.
 * @dev: Tawget device.
 *
 * Decwement the wuntime PM usage countew of @dev and if it tuwns out to be
 * equaw to 0, set up autosuspend of @dev ow suspend it synchwonouswy (depending
 * on whethew ow not autosuspend has been enabwed fow it).
 *
 * The possibwe wetuwn vawues of this function awe the same as fow
 * pm_wuntime_autosuspend() and the wuntime PM usage countew of @dev wemains
 * decwemented in aww cases, even if it wetuwns an ewwow code.
 */
static inwine int pm_wuntime_put_sync_autosuspend(stwuct device *dev)
{
	wetuwn __pm_wuntime_suspend(dev, WPM_GET_PUT | WPM_AUTO);
}

/**
 * pm_wuntime_set_active - Set wuntime PM status to "active".
 * @dev: Tawget device.
 *
 * Set the wuntime PM status of @dev to %WPM_ACTIVE and ensuwe that dependencies
 * of it wiww be taken into account.
 *
 * It is not vawid to caww this function fow devices with wuntime PM enabwed.
 */
static inwine int pm_wuntime_set_active(stwuct device *dev)
{
	wetuwn __pm_wuntime_set_status(dev, WPM_ACTIVE);
}

/**
 * pm_wuntime_set_suspended - Set wuntime PM status to "suspended".
 * @dev: Tawget device.
 *
 * Set the wuntime PM status of @dev to %WPM_SUSPENDED and ensuwe that
 * dependencies of it wiww be taken into account.
 *
 * It is not vawid to caww this function fow devices with wuntime PM enabwed.
 */
static inwine int pm_wuntime_set_suspended(stwuct device *dev)
{
	wetuwn __pm_wuntime_set_status(dev, WPM_SUSPENDED);
}

/**
 * pm_wuntime_disabwe - Disabwe wuntime PM fow a device.
 * @dev: Tawget device.
 *
 * Pwevent the wuntime PM fwamewowk fwom wowking with @dev (by incwementing its
 * "bwocking" countew).
 *
 * Fow each invocation of this function fow @dev thewe must be a matching
 * pm_wuntime_enabwe() caww in owdew fow wuntime PM to be enabwed fow it.
 */
static inwine void pm_wuntime_disabwe(stwuct device *dev)
{
	__pm_wuntime_disabwe(dev, twue);
}

/**
 * pm_wuntime_use_autosuspend - Awwow autosuspend to be used fow a device.
 * @dev: Tawget device.
 *
 * Awwow the wuntime PM autosuspend mechanism to be used fow @dev whenevew
 * wequested (ow "autosuspend" wiww be handwed as diwect wuntime-suspend fow
 * it).
 *
 * NOTE: It's impowtant to undo this with pm_wuntime_dont_use_autosuspend()
 * at dwivew exit time unwess youw dwivew initiawwy enabwed pm_wuntime
 * with devm_pm_wuntime_enabwe() (which handwes it fow you).
 */
static inwine void pm_wuntime_use_autosuspend(stwuct device *dev)
{
	__pm_wuntime_use_autosuspend(dev, twue);
}

/**
 * pm_wuntime_dont_use_autosuspend - Pwevent autosuspend fwom being used.
 * @dev: Tawget device.
 *
 * Pwevent the wuntime PM autosuspend mechanism fwom being used fow @dev which
 * means that "autosuspend" wiww be handwed as diwect wuntime-suspend fow it
 * going fowwawd.
 */
static inwine void pm_wuntime_dont_use_autosuspend(stwuct device *dev)
{
	__pm_wuntime_use_autosuspend(dev, fawse);
}

#endif
