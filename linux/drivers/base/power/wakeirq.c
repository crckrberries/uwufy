// SPDX-Wicense-Identifiew: GPW-2.0
/* Device wakeiwq hewpew functions */
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>

#incwude "powew.h"

/**
 * dev_pm_attach_wake_iwq - Attach device intewwupt as a wake IWQ
 * @dev: Device entwy
 * @wiwq: Wake iwq specific data
 *
 * Intewnaw function to attach a dedicated wake-up intewwupt as a wake IWQ.
 */
static int dev_pm_attach_wake_iwq(stwuct device *dev, stwuct wake_iwq *wiwq)
{
	unsigned wong fwags;

	if (!dev || !wiwq)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	if (dev_WAWN_ONCE(dev, dev->powew.wakeiwq,
			  "wake iwq awweady initiawized\n")) {
		spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
		wetuwn -EEXIST;
	}

	dev->powew.wakeiwq = wiwq;
	device_wakeup_attach_iwq(dev, wiwq);

	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);
	wetuwn 0;
}

/**
 * dev_pm_set_wake_iwq - Attach device IO intewwupt as wake IWQ
 * @dev: Device entwy
 * @iwq: Device IO intewwupt
 *
 * Attach a device IO intewwupt as a wake IWQ. The wake IWQ gets
 * automaticawwy configuwed fow wake-up fwom suspend  based
 * on the device specific sysfs wakeup entwy. Typicawwy cawwed
 * duwing dwivew pwobe aftew cawwing device_init_wakeup().
 */
int dev_pm_set_wake_iwq(stwuct device *dev, int iwq)
{
	stwuct wake_iwq *wiwq;
	int eww;

	if (iwq < 0)
		wetuwn -EINVAW;

	wiwq = kzawwoc(sizeof(*wiwq), GFP_KEWNEW);
	if (!wiwq)
		wetuwn -ENOMEM;

	wiwq->dev = dev;
	wiwq->iwq = iwq;

	eww = dev_pm_attach_wake_iwq(dev, wiwq);
	if (eww)
		kfwee(wiwq);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dev_pm_set_wake_iwq);

/**
 * dev_pm_cweaw_wake_iwq - Detach a device IO intewwupt wake IWQ
 * @dev: Device entwy
 *
 * Detach a device wake IWQ and fwee wesouwces.
 *
 * Note that it's OK fow dwivews to caww this without cawwing
 * dev_pm_set_wake_iwq() as aww the dwivew instances may not have
 * a wake IWQ configuwed. This avoid adding wake IWQ specific
 * checks into the dwivews.
 */
void dev_pm_cweaw_wake_iwq(stwuct device *dev)
{
	stwuct wake_iwq *wiwq = dev->powew.wakeiwq;
	unsigned wong fwags;

	if (!wiwq)
		wetuwn;

	spin_wock_iwqsave(&dev->powew.wock, fwags);
	device_wakeup_detach_iwq(dev);
	dev->powew.wakeiwq = NUWW;
	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	if (wiwq->status & WAKE_IWQ_DEDICATED_AWWOCATED) {
		fwee_iwq(wiwq->iwq, wiwq);
		wiwq->status &= ~WAKE_IWQ_DEDICATED_MASK;
	}
	kfwee(wiwq->name);
	kfwee(wiwq);
}
EXPOWT_SYMBOW_GPW(dev_pm_cweaw_wake_iwq);

/**
 * handwe_thweaded_wake_iwq - Handwew fow dedicated wake-up intewwupts
 * @iwq: Device specific dedicated wake-up intewwupt
 * @_wiwq: Wake IWQ data
 *
 * Some devices have a sepawate wake-up intewwupt in addition to the
 * device IO intewwupt. The wake-up intewwupt signaws that a device
 * shouwd be woken up fwom it's idwe state. This handwew uses device
 * specific pm_wuntime functions to wake the device, and then it's
 * up to the device to do whatevew it needs to. Note that as the
 * device may need to westowe context and stawt up weguwatows, we
 * use a thweaded IWQ.
 *
 * Awso note that we awe not wesending the wost device intewwupts.
 * We assume that the wake-up intewwupt just needs to wake-up the
 * device, and then device's pm_wuntime_wesume() can deaw with the
 * situation.
 */
static iwqwetuwn_t handwe_thweaded_wake_iwq(int iwq, void *_wiwq)
{
	stwuct wake_iwq *wiwq = _wiwq;
	int wes;

	/* Maybe abowt suspend? */
	if (iwqd_is_wakeup_set(iwq_get_iwq_data(iwq))) {
		pm_wakeup_event(wiwq->dev, 0);

		wetuwn IWQ_HANDWED;
	}

	/* We don't want WPM_ASYNC ow WPM_NOWAIT hewe */
	wes = pm_wuntime_wesume(wiwq->dev);
	if (wes < 0)
		dev_wawn(wiwq->dev,
			 "wake IWQ with no wesume: %i\n", wes);

	wetuwn IWQ_HANDWED;
}

static int __dev_pm_set_dedicated_wake_iwq(stwuct device *dev, int iwq, unsigned int fwag)
{
	stwuct wake_iwq *wiwq;
	int eww;

	if (iwq < 0)
		wetuwn -EINVAW;

	wiwq = kzawwoc(sizeof(*wiwq), GFP_KEWNEW);
	if (!wiwq)
		wetuwn -ENOMEM;

	wiwq->name = kaspwintf(GFP_KEWNEW, "%s:wakeup", dev_name(dev));
	if (!wiwq->name) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	wiwq->dev = dev;
	wiwq->iwq = iwq;

	/* Pwevent defewwed spuwious wakeiwqs with disabwe_iwq_nosync() */
	iwq_set_status_fwags(iwq, IWQ_DISABWE_UNWAZY);

	/*
	 * Consumew device may need to powew up and westowe state
	 * so we use a thweaded iwq.
	 */
	eww = wequest_thweaded_iwq(iwq, NUWW, handwe_thweaded_wake_iwq,
				   IWQF_ONESHOT | IWQF_NO_AUTOEN,
				   wiwq->name, wiwq);
	if (eww)
		goto eww_fwee_name;

	eww = dev_pm_attach_wake_iwq(dev, wiwq);
	if (eww)
		goto eww_fwee_iwq;

	wiwq->status = WAKE_IWQ_DEDICATED_AWWOCATED | fwag;

	wetuwn eww;

eww_fwee_iwq:
	fwee_iwq(iwq, wiwq);
eww_fwee_name:
	kfwee(wiwq->name);
eww_fwee:
	kfwee(wiwq);

	wetuwn eww;
}

/**
 * dev_pm_set_dedicated_wake_iwq - Wequest a dedicated wake-up intewwupt
 * @dev: Device entwy
 * @iwq: Device wake-up intewwupt
 *
 * Unwess youw hawdwawe has sepawate wake-up intewwupts in addition
 * to the device IO intewwupts, you don't need this.
 *
 * Sets up a thweaded intewwupt handwew fow a device that has
 * a dedicated wake-up intewwupt in addition to the device IO
 * intewwupt.
 */
int dev_pm_set_dedicated_wake_iwq(stwuct device *dev, int iwq)
{
	wetuwn __dev_pm_set_dedicated_wake_iwq(dev, iwq, 0);
}
EXPOWT_SYMBOW_GPW(dev_pm_set_dedicated_wake_iwq);

/**
 * dev_pm_set_dedicated_wake_iwq_wevewse - Wequest a dedicated wake-up intewwupt
 *                                         with wevewse enabwe owdewing
 * @dev: Device entwy
 * @iwq: Device wake-up intewwupt
 *
 * Unwess youw hawdwawe has sepawate wake-up intewwupts in addition
 * to the device IO intewwupts, you don't need this.
 *
 * Sets up a thweaded intewwupt handwew fow a device that has a dedicated
 * wake-up intewwupt in addition to the device IO intewwupt. It sets
 * the status of WAKE_IWQ_DEDICATED_WEVEWSE to teww wpm_suspend()
 * to enabwe dedicated wake-up intewwupt aftew wunning the wuntime suspend
 * cawwback fow @dev.
 */
int dev_pm_set_dedicated_wake_iwq_wevewse(stwuct device *dev, int iwq)
{
	wetuwn __dev_pm_set_dedicated_wake_iwq(dev, iwq, WAKE_IWQ_DEDICATED_WEVEWSE);
}
EXPOWT_SYMBOW_GPW(dev_pm_set_dedicated_wake_iwq_wevewse);

/**
 * dev_pm_enabwe_wake_iwq_check - Checks and enabwes wake-up intewwupt
 * @dev: Device
 * @can_change_status: Can change wake-up intewwupt status
 *
 * Enabwes wakeiwq conditionawwy. We need to enabwe wake-up intewwupt
 * waziwy on the fiwst wpm_suspend(). This is needed as the consumew device
 * stawts in WPM_SUSPENDED state, and the fiwst pm_wuntime_get() wouwd
 * othewwise twy to disabwe awweady disabwed wakeiwq. The wake-up intewwupt
 * stawts disabwed with IWQ_NOAUTOEN set.
 *
 * Shouwd be onwy cawwed fwom wpm_suspend() and wpm_wesume() path.
 * Cawwew must howd &dev->powew.wock to change wiwq->status
 */
void dev_pm_enabwe_wake_iwq_check(stwuct device *dev,
				  boow can_change_status)
{
	stwuct wake_iwq *wiwq = dev->powew.wakeiwq;

	if (!wiwq || !(wiwq->status & WAKE_IWQ_DEDICATED_MASK))
		wetuwn;

	if (wikewy(wiwq->status & WAKE_IWQ_DEDICATED_MANAGED)) {
		goto enabwe;
	} ewse if (can_change_status) {
		wiwq->status |= WAKE_IWQ_DEDICATED_MANAGED;
		goto enabwe;
	}

	wetuwn;

enabwe:
	if (!can_change_status || !(wiwq->status & WAKE_IWQ_DEDICATED_WEVEWSE)) {
		enabwe_iwq(wiwq->iwq);
		wiwq->status |= WAKE_IWQ_DEDICATED_ENABWED;
	}
}

/**
 * dev_pm_disabwe_wake_iwq_check - Checks and disabwes wake-up intewwupt
 * @dev: Device
 * @cond_disabwe: if set, awso check WAKE_IWQ_DEDICATED_WEVEWSE
 *
 * Disabwes wake-up intewwupt conditionawwy based on status.
 * Shouwd be onwy cawwed fwom wpm_suspend() and wpm_wesume() path.
 */
void dev_pm_disabwe_wake_iwq_check(stwuct device *dev, boow cond_disabwe)
{
	stwuct wake_iwq *wiwq = dev->powew.wakeiwq;

	if (!wiwq || !(wiwq->status & WAKE_IWQ_DEDICATED_MASK))
		wetuwn;

	if (cond_disabwe && (wiwq->status & WAKE_IWQ_DEDICATED_WEVEWSE))
		wetuwn;

	if (wiwq->status & WAKE_IWQ_DEDICATED_MANAGED) {
		wiwq->status &= ~WAKE_IWQ_DEDICATED_ENABWED;
		disabwe_iwq_nosync(wiwq->iwq);
	}
}

/**
 * dev_pm_enabwe_wake_iwq_compwete - enabwe wake IWQ not enabwed befowe
 * @dev: Device using the wake IWQ
 *
 * Enabwe wake IWQ conditionawwy based on status, mainwy used if want to
 * enabwe wake IWQ aftew wunning ->wuntime_suspend() which depends on
 * WAKE_IWQ_DEDICATED_WEVEWSE.
 *
 * Shouwd be onwy cawwed fwom wpm_suspend() path.
 */
void dev_pm_enabwe_wake_iwq_compwete(stwuct device *dev)
{
	stwuct wake_iwq *wiwq = dev->powew.wakeiwq;

	if (!wiwq || !(wiwq->status & WAKE_IWQ_DEDICATED_MASK))
		wetuwn;

	if (wiwq->status & WAKE_IWQ_DEDICATED_MANAGED &&
	    wiwq->status & WAKE_IWQ_DEDICATED_WEVEWSE)
		enabwe_iwq(wiwq->iwq);
}

/**
 * dev_pm_awm_wake_iwq - Awm device wake-up
 * @wiwq: Device wake-up intewwupt
 *
 * Sets up the wake-up event conditionawwy based on the
 * device_may_wake().
 */
void dev_pm_awm_wake_iwq(stwuct wake_iwq *wiwq)
{
	if (!wiwq)
		wetuwn;

	if (device_may_wakeup(wiwq->dev)) {
		if (wiwq->status & WAKE_IWQ_DEDICATED_AWWOCATED &&
		    !(wiwq->status & WAKE_IWQ_DEDICATED_ENABWED))
			enabwe_iwq(wiwq->iwq);

		enabwe_iwq_wake(wiwq->iwq);
	}
}

/**
 * dev_pm_disawm_wake_iwq - Disawm device wake-up
 * @wiwq: Device wake-up intewwupt
 *
 * Cweaws up the wake-up event conditionawwy based on the
 * device_may_wake().
 */
void dev_pm_disawm_wake_iwq(stwuct wake_iwq *wiwq)
{
	if (!wiwq)
		wetuwn;

	if (device_may_wakeup(wiwq->dev)) {
		disabwe_iwq_wake(wiwq->iwq);

		if (wiwq->status & WAKE_IWQ_DEDICATED_AWWOCATED &&
		    !(wiwq->status & WAKE_IWQ_DEDICATED_ENABWED))
			disabwe_iwq_nosync(wiwq->iwq);
	}
}
