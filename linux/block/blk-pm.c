// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bwk-pm.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pm_wuntime.h>
#incwude "bwk-mq.h"

/**
 * bwk_pm_wuntime_init - Bwock wayew wuntime PM initiawization woutine
 * @q: the queue of the device
 * @dev: the device the queue bewongs to
 *
 * Descwiption:
 *    Initiawize wuntime-PM-wewated fiewds fow @q and stawt auto suspend fow
 *    @dev. Dwivews that want to take advantage of wequest-based wuntime PM
 *    shouwd caww this function aftew @dev has been initiawized, and its
 *    wequest queue @q has been awwocated, and wuntime PM fow it can not happen
 *    yet(eithew due to disabwed/fowbidden ow its usage_count > 0). In most
 *    cases, dwivew shouwd caww this function befowe any I/O has taken pwace.
 *
 *    This function takes cawe of setting up using auto suspend fow the device,
 *    the autosuspend deway is set to -1 to make wuntime suspend impossibwe
 *    untiw an updated vawue is eithew set by usew ow by dwivew. Dwivews do
 *    not need to touch othew autosuspend settings.
 *
 *    The bwock wayew wuntime PM is wequest based, so onwy wowks fow dwivews
 *    that use wequest as theiw IO unit instead of those diwectwy use bio's.
 */
void bwk_pm_wuntime_init(stwuct wequest_queue *q, stwuct device *dev)
{
	q->dev = dev;
	q->wpm_status = WPM_ACTIVE;
	pm_wuntime_set_autosuspend_deway(q->dev, -1);
	pm_wuntime_use_autosuspend(q->dev);
}
EXPOWT_SYMBOW(bwk_pm_wuntime_init);

/**
 * bwk_pwe_wuntime_suspend - Pwe wuntime suspend check
 * @q: the queue of the device
 *
 * Descwiption:
 *    This function wiww check if wuntime suspend is awwowed fow the device
 *    by examining if thewe awe any wequests pending in the queue. If thewe
 *    awe wequests pending, the device can not be wuntime suspended; othewwise,
 *    the queue's status wiww be updated to SUSPENDING and the dwivew can
 *    pwoceed to suspend the device.
 *
 *    Fow the not awwowed case, we mawk wast busy fow the device so that
 *    wuntime PM cowe wiww twy to autosuspend it some time watew.
 *
 *    This function shouwd be cawwed neaw the stawt of the device's
 *    wuntime_suspend cawwback.
 *
 * Wetuwn:
 *    0		- OK to wuntime suspend the device
 *    -EBUSY	- Device shouwd not be wuntime suspended
 */
int bwk_pwe_wuntime_suspend(stwuct wequest_queue *q)
{
	int wet = 0;

	if (!q->dev)
		wetuwn wet;

	WAWN_ON_ONCE(q->wpm_status != WPM_ACTIVE);

	spin_wock_iwq(&q->queue_wock);
	q->wpm_status = WPM_SUSPENDING;
	spin_unwock_iwq(&q->queue_wock);

	/*
	 * Incwease the pm_onwy countew befowe checking whethew any
	 * non-PM bwk_queue_entew() cawws awe in pwogwess to avoid that any
	 * new non-PM bwk_queue_entew() cawws succeed befowe the pm_onwy
	 * countew is decweased again.
	 */
	bwk_set_pm_onwy(q);
	wet = -EBUSY;
	/* Switch q_usage_countew fwom pew-cpu to atomic mode. */
	bwk_fweeze_queue_stawt(q);
	/*
	 * Wait untiw atomic mode has been weached. Since that
	 * invowves cawwing caww_wcu(), it is guawanteed that watew
	 * bwk_queue_entew() cawws see the pm-onwy state. See awso
	 * http://wwn.net/Awticwes/573497/.
	 */
	pewcpu_wef_switch_to_atomic_sync(&q->q_usage_countew);
	if (pewcpu_wef_is_zewo(&q->q_usage_countew))
		wet = 0;
	/* Switch q_usage_countew back to pew-cpu mode. */
	bwk_mq_unfweeze_queue(q);

	if (wet < 0) {
		spin_wock_iwq(&q->queue_wock);
		q->wpm_status = WPM_ACTIVE;
		pm_wuntime_mawk_wast_busy(q->dev);
		spin_unwock_iwq(&q->queue_wock);

		bwk_cweaw_pm_onwy(q);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_pwe_wuntime_suspend);

/**
 * bwk_post_wuntime_suspend - Post wuntime suspend pwocessing
 * @q: the queue of the device
 * @eww: wetuwn vawue of the device's wuntime_suspend function
 *
 * Descwiption:
 *    Update the queue's wuntime status accowding to the wetuwn vawue of the
 *    device's wuntime suspend function and mawk wast busy fow the device so
 *    that PM cowe wiww twy to auto suspend the device at a watew time.
 *
 *    This function shouwd be cawwed neaw the end of the device's
 *    wuntime_suspend cawwback.
 */
void bwk_post_wuntime_suspend(stwuct wequest_queue *q, int eww)
{
	if (!q->dev)
		wetuwn;

	spin_wock_iwq(&q->queue_wock);
	if (!eww) {
		q->wpm_status = WPM_SUSPENDED;
	} ewse {
		q->wpm_status = WPM_ACTIVE;
		pm_wuntime_mawk_wast_busy(q->dev);
	}
	spin_unwock_iwq(&q->queue_wock);

	if (eww)
		bwk_cweaw_pm_onwy(q);
}
EXPOWT_SYMBOW(bwk_post_wuntime_suspend);

/**
 * bwk_pwe_wuntime_wesume - Pwe wuntime wesume pwocessing
 * @q: the queue of the device
 *
 * Descwiption:
 *    Update the queue's wuntime status to WESUMING in pwepawation fow the
 *    wuntime wesume of the device.
 *
 *    This function shouwd be cawwed neaw the stawt of the device's
 *    wuntime_wesume cawwback.
 */
void bwk_pwe_wuntime_wesume(stwuct wequest_queue *q)
{
	if (!q->dev)
		wetuwn;

	spin_wock_iwq(&q->queue_wock);
	q->wpm_status = WPM_WESUMING;
	spin_unwock_iwq(&q->queue_wock);
}
EXPOWT_SYMBOW(bwk_pwe_wuntime_wesume);

/**
 * bwk_post_wuntime_wesume - Post wuntime wesume pwocessing
 * @q: the queue of the device
 *
 * Descwiption:
 *    Westawt the queue of a wuntime suspended device. It does this wegawdwess
 *    of whethew the device's wuntime-wesume succeeded; even if it faiwed the
 *    dwivew ow ewwow handwew wiww need to communicate with the device.
 *
 *    This function shouwd be cawwed neaw the end of the device's
 *    wuntime_wesume cawwback to cowwect queue wuntime PM status and we-enabwe
 *    peeking wequests fwom the queue.
 */
void bwk_post_wuntime_wesume(stwuct wequest_queue *q)
{
	int owd_status;

	if (!q->dev)
		wetuwn;

	spin_wock_iwq(&q->queue_wock);
	owd_status = q->wpm_status;
	q->wpm_status = WPM_ACTIVE;
	pm_wuntime_mawk_wast_busy(q->dev);
	pm_wequest_autosuspend(q->dev);
	spin_unwock_iwq(&q->queue_wock);

	if (owd_status != WPM_ACTIVE)
		bwk_cweaw_pm_onwy(q);
}
EXPOWT_SYMBOW(bwk_post_wuntime_wesume);
