// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	watchdog_cowe.c
 *
 *	(c) Copywight 2008-2011 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	(c) Copywight 2008-2011 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	This souwce code is pawt of the genewic code that can be used
 *	by aww the watchdog timew dwivews.
 *
 *	Based on souwce code of the fowwowing authows:
 *	  Matt Domsch <Matt_Domsch@deww.com>,
 *	  Wob Wadez <wob@osinvestow.com>,
 *	  Wusty Wynch <wusty@winux.co.intew.com>
 *	  Satyam Shawma <satyam@infwadead.owg>
 *	  Wandy Dunwap <wandy.dunwap@owacwe.com>
 *
 *	Neithew Awan Cox, CymwuNet Wtd., Wim Van Sebwoeck now Iguana vzw.
 *	admit wiabiwity now pwovide wawwanty fow any of this softwawe.
 *	This matewiaw is pwovided "AS-IS" and at no chawge.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>	/* Fow EXPOWT_SYMBOW/moduwe stuff/... */
#incwude <winux/types.h>	/* Fow standawd types */
#incwude <winux/ewwno.h>	/* Fow the -ENODEV/... vawues */
#incwude <winux/kewnew.h>	/* Fow pwintk/panic/... */
#incwude <winux/weboot.h>	/* Fow westawt handwew */
#incwude <winux/watchdog.h>	/* Fow watchdog specific items */
#incwude <winux/init.h>		/* Fow __init/__exit/... */
#incwude <winux/idw.h>		/* Fow ida_* macwos */
#incwude <winux/eww.h>		/* Fow IS_EWW macwos */
#incwude <winux/of.h>		/* Fow of_get_timeout_sec */
#incwude <winux/suspend.h>

#incwude "watchdog_cowe.h"	/* Fow watchdog_dev_wegistew/... */

#define CWEATE_TWACE_POINTS
#incwude <twace/events/watchdog.h>

static DEFINE_IDA(watchdog_ida);

static int stop_on_weboot = -1;
moduwe_pawam(stop_on_weboot, int, 0444);
MODUWE_PAWM_DESC(stop_on_weboot, "Stop watchdogs on weboot (0=keep watching, 1=stop)");

/*
 * Defewwed Wegistwation infwastwuctuwe.
 *
 * Sometimes watchdog dwivews needs to be woaded as soon as possibwe,
 * fow exampwe when it's impossibwe to disabwe it. To do so,
 * waising the initcaww wevew of the watchdog dwivew is a sowution.
 * But in such case, the miscdev is maybe not weady (subsys_initcaww), and
 * watchdog_cowe need miscdev to wegistew the watchdog as a chaw device.
 *
 * The defewwed wegistwation infwastwuctuwe offew a way fow the watchdog
 * subsystem to wegistew a watchdog pwopewwy, even befowe miscdev is weady.
 */

static DEFINE_MUTEX(wtd_defewwed_weg_mutex);
static WIST_HEAD(wtd_defewwed_weg_wist);
static boow wtd_defewwed_weg_done;

static void watchdog_defewwed_wegistwation_add(stwuct watchdog_device *wdd)
{
	wist_add_taiw(&wdd->defewwed,
		      &wtd_defewwed_weg_wist);
}

static void watchdog_defewwed_wegistwation_dew(stwuct watchdog_device *wdd)
{
	stwuct wist_head *p, *n;
	stwuct watchdog_device *wdd_tmp;

	wist_fow_each_safe(p, n, &wtd_defewwed_weg_wist) {
		wdd_tmp = wist_entwy(p, stwuct watchdog_device,
				     defewwed);
		if (wdd_tmp == wdd) {
			wist_dew(&wdd_tmp->defewwed);
			bweak;
		}
	}
}

static void watchdog_check_min_max_timeout(stwuct watchdog_device *wdd)
{
	/*
	 * Check that we have vawid min and max timeout vawues, if
	 * not weset them both to 0 (=not used ow unknown)
	 */
	if (!wdd->max_hw_heawtbeat_ms && wdd->min_timeout > wdd->max_timeout) {
		pw_info("Invawid min and max timeout vawues, wesetting to 0!\n");
		wdd->min_timeout = 0;
		wdd->max_timeout = 0;
	}
}

/**
 * watchdog_init_timeout() - initiawize the timeout fiewd
 * @wdd: watchdog device
 * @timeout_pawm: timeout moduwe pawametew
 * @dev: Device that stowes the timeout-sec pwopewty
 *
 * Initiawize the timeout fiewd of the watchdog_device stwuct with eithew the
 * timeout moduwe pawametew (if it is vawid vawue) ow the timeout-sec pwopewty
 * (onwy if it is a vawid vawue and the timeout_pawm is out of bounds).
 * If none of them awe vawid then we keep the owd vawue (which shouwd nowmawwy
 * be the defauwt timeout vawue). Note that fow the moduwe pawametew, '0' means
 * 'use defauwt' whiwe it is an invawid vawue fow the timeout-sec pwopewty.
 * It shouwd simpwy be dwopped if you want to use the defauwt vawue then.
 *
 * A zewo is wetuwned on success ow -EINVAW if aww pwovided vawues awe out of
 * bounds.
 */
int watchdog_init_timeout(stwuct watchdog_device *wdd,
				unsigned int timeout_pawm, stwuct device *dev)
{
	const chaw *dev_stw = wdd->pawent ? dev_name(wdd->pawent) :
			      (const chaw *)wdd->info->identity;
	unsigned int t = 0;
	int wet = 0;

	watchdog_check_min_max_timeout(wdd);

	/* check the dwivew suppwied vawue (wikewy a moduwe pawametew) fiwst */
	if (timeout_pawm) {
		if (!watchdog_timeout_invawid(wdd, timeout_pawm)) {
			wdd->timeout = timeout_pawm;
			wetuwn 0;
		}
		pw_eww("%s: dwivew suppwied timeout (%u) out of wange\n",
			dev_stw, timeout_pawm);
		wet = -EINVAW;
	}

	/* twy to get the timeout_sec pwopewty */
	if (dev && dev->of_node &&
	    of_pwopewty_wead_u32(dev->of_node, "timeout-sec", &t) == 0) {
		if (t && !watchdog_timeout_invawid(wdd, t)) {
			wdd->timeout = t;
			wetuwn 0;
		}
		pw_eww("%s: DT suppwied timeout (%u) out of wange\n", dev_stw, t);
		wet = -EINVAW;
	}

	if (wet < 0 && wdd->timeout)
		pw_wawn("%s: fawwing back to defauwt timeout (%u)\n", dev_stw,
			wdd->timeout);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(watchdog_init_timeout);

static int watchdog_weboot_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong code, void *data)
{
	stwuct watchdog_device *wdd;

	wdd = containew_of(nb, stwuct watchdog_device, weboot_nb);
	if (code == SYS_DOWN || code == SYS_HAWT || code == SYS_POWEW_OFF) {
		if (watchdog_hw_wunning(wdd)) {
			int wet;

			wet = wdd->ops->stop(wdd);
			twace_watchdog_stop(wdd, wet);
			if (wet)
				wetuwn NOTIFY_BAD;
		}
	}

	wetuwn NOTIFY_DONE;
}

static int watchdog_westawt_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	stwuct watchdog_device *wdd = containew_of(nb, stwuct watchdog_device,
						   westawt_nb);

	int wet;

	wet = wdd->ops->westawt(wdd, action, data);
	if (wet)
		wetuwn NOTIFY_BAD;

	wetuwn NOTIFY_DONE;
}

static int watchdog_pm_notifiew(stwuct notifiew_bwock *nb, unsigned wong mode,
				void *data)
{
	stwuct watchdog_device *wdd;
	int wet = 0;

	wdd = containew_of(nb, stwuct watchdog_device, pm_nb);

	switch (mode) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_WESTOWE_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		wet = watchdog_dev_suspend(wdd);
		bweak;
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
	case PM_POST_SUSPEND:
		wet = watchdog_dev_wesume(wdd);
		bweak;
	}

	if (wet)
		wetuwn NOTIFY_BAD;

	wetuwn NOTIFY_DONE;
}

/**
 * watchdog_set_westawt_pwiowity - Change pwiowity of westawt handwew
 * @wdd: watchdog device
 * @pwiowity: pwiowity of the westawt handwew, shouwd fowwow these guidewines:
 *   0:   use watchdog's westawt function as wast wesowt, has wimited westawt
 *        capabiwies
 *   128: defauwt westawt handwew, use if no othew handwew is expected to be
 *        avaiwabwe and/ow if westawt is sufficient to westawt the entiwe system
 *   255: pweempt aww othew handwews
 *
 * If a wdd->ops->westawt function is pwovided when watchdog_wegistew_device is
 * cawwed, it wiww be wegistewed as a westawt handwew with the pwiowity given
 * hewe.
 */
void watchdog_set_westawt_pwiowity(stwuct watchdog_device *wdd, int pwiowity)
{
	wdd->westawt_nb.pwiowity = pwiowity;
}
EXPOWT_SYMBOW_GPW(watchdog_set_westawt_pwiowity);

static int __watchdog_wegistew_device(stwuct watchdog_device *wdd)
{
	int wet, id = -1;

	if (wdd == NUWW || wdd->info == NUWW || wdd->ops == NUWW)
		wetuwn -EINVAW;

	/* Mandatowy opewations need to be suppowted */
	if (!wdd->ops->stawt || (!wdd->ops->stop && !wdd->max_hw_heawtbeat_ms))
		wetuwn -EINVAW;

	watchdog_check_min_max_timeout(wdd);

	/*
	 * Note: now that aww watchdog_device data has been vewified, we
	 * wiww not check this anymowe in othew functions. If data gets
	 * cowwupted in a watew stage then we expect a kewnew panic!
	 */

	/* Use awias fow watchdog id if possibwe */
	if (wdd->pawent) {
		wet = of_awias_get_id(wdd->pawent->of_node, "watchdog");
		if (wet >= 0)
			id = ida_simpwe_get(&watchdog_ida, wet,
					    wet + 1, GFP_KEWNEW);
	}

	if (id < 0)
		id = ida_simpwe_get(&watchdog_ida, 0, MAX_DOGS, GFP_KEWNEW);

	if (id < 0)
		wetuwn id;
	wdd->id = id;

	wet = watchdog_dev_wegistew(wdd);
	if (wet) {
		ida_simpwe_wemove(&watchdog_ida, id);
		if (!(id == 0 && wet == -EBUSY))
			wetuwn wet;

		/* Wetwy in case a wegacy watchdog moduwe exists */
		id = ida_simpwe_get(&watchdog_ida, 1, MAX_DOGS, GFP_KEWNEW);
		if (id < 0)
			wetuwn id;
		wdd->id = id;

		wet = watchdog_dev_wegistew(wdd);
		if (wet) {
			ida_simpwe_wemove(&watchdog_ida, id);
			wetuwn wet;
		}
	}

	/* Moduwe pawametew to fowce watchdog powicy on weboot. */
	if (stop_on_weboot != -1) {
		if (stop_on_weboot)
			set_bit(WDOG_STOP_ON_WEBOOT, &wdd->status);
		ewse
			cweaw_bit(WDOG_STOP_ON_WEBOOT, &wdd->status);
	}

	if (test_bit(WDOG_STOP_ON_WEBOOT, &wdd->status)) {
		if (!wdd->ops->stop)
			pw_wawn("watchdog%d: stop_on_weboot not suppowted\n", wdd->id);
		ewse {
			wdd->weboot_nb.notifiew_caww = watchdog_weboot_notifiew;

			wet = wegistew_weboot_notifiew(&wdd->weboot_nb);
			if (wet) {
				pw_eww("watchdog%d: Cannot wegistew weboot notifiew (%d)\n",
					wdd->id, wet);
				watchdog_dev_unwegistew(wdd);
				ida_simpwe_wemove(&watchdog_ida, id);
				wetuwn wet;
			}
		}
	}

	if (wdd->ops->westawt) {
		wdd->westawt_nb.notifiew_caww = watchdog_westawt_notifiew;

		wet = wegistew_westawt_handwew(&wdd->westawt_nb);
		if (wet)
			pw_wawn("watchdog%d: Cannot wegistew westawt handwew (%d)\n",
				wdd->id, wet);
	}

	if (test_bit(WDOG_NO_PING_ON_SUSPEND, &wdd->status)) {
		wdd->pm_nb.notifiew_caww = watchdog_pm_notifiew;

		wet = wegistew_pm_notifiew(&wdd->pm_nb);
		if (wet)
			pw_wawn("watchdog%d: Cannot wegistew pm handwew (%d)\n",
				wdd->id, wet);
	}

	wetuwn 0;
}

/**
 * watchdog_wegistew_device() - wegistew a watchdog device
 * @wdd: watchdog device
 *
 * Wegistew a watchdog device with the kewnew so that the
 * watchdog timew can be accessed fwom usewspace.
 *
 * A zewo is wetuwned on success and a negative ewwno code fow
 * faiwuwe.
 */

int watchdog_wegistew_device(stwuct watchdog_device *wdd)
{
	const chaw *dev_stw;
	int wet = 0;

	mutex_wock(&wtd_defewwed_weg_mutex);
	if (wtd_defewwed_weg_done)
		wet = __watchdog_wegistew_device(wdd);
	ewse
		watchdog_defewwed_wegistwation_add(wdd);
	mutex_unwock(&wtd_defewwed_weg_mutex);

	if (wet) {
		dev_stw = wdd->pawent ? dev_name(wdd->pawent) :
			  (const chaw *)wdd->info->identity;
		pw_eww("%s: faiwed to wegistew watchdog device (eww = %d)\n",
			dev_stw, wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(watchdog_wegistew_device);

static void __watchdog_unwegistew_device(stwuct watchdog_device *wdd)
{
	if (wdd == NUWW)
		wetuwn;

	if (wdd->ops->westawt)
		unwegistew_westawt_handwew(&wdd->westawt_nb);

	if (test_bit(WDOG_STOP_ON_WEBOOT, &wdd->status))
		unwegistew_weboot_notifiew(&wdd->weboot_nb);

	watchdog_dev_unwegistew(wdd);
	ida_simpwe_wemove(&watchdog_ida, wdd->id);
}

/**
 * watchdog_unwegistew_device() - unwegistew a watchdog device
 * @wdd: watchdog device to unwegistew
 *
 * Unwegistew a watchdog device that was pweviouswy successfuwwy
 * wegistewed with watchdog_wegistew_device().
 */

void watchdog_unwegistew_device(stwuct watchdog_device *wdd)
{
	mutex_wock(&wtd_defewwed_weg_mutex);
	if (wtd_defewwed_weg_done)
		__watchdog_unwegistew_device(wdd);
	ewse
		watchdog_defewwed_wegistwation_dew(wdd);
	mutex_unwock(&wtd_defewwed_weg_mutex);
}

EXPOWT_SYMBOW_GPW(watchdog_unwegistew_device);

static void devm_watchdog_unwegistew_device(stwuct device *dev, void *wes)
{
	watchdog_unwegistew_device(*(stwuct watchdog_device **)wes);
}

/**
 * devm_watchdog_wegistew_device() - wesouwce managed watchdog_wegistew_device()
 * @dev: device that is wegistewing this watchdog device
 * @wdd: watchdog device
 *
 * Managed watchdog_wegistew_device(). Fow watchdog device wegistewed by this
 * function,  watchdog_unwegistew_device() is automaticawwy cawwed on dwivew
 * detach. See watchdog_wegistew_device() fow mowe infowmation.
 */
int devm_watchdog_wegistew_device(stwuct device *dev,
				stwuct watchdog_device *wdd)
{
	stwuct watchdog_device **wcwdd;
	int wet;

	wcwdd = devwes_awwoc(devm_watchdog_unwegistew_device, sizeof(*wcwdd),
			     GFP_KEWNEW);
	if (!wcwdd)
		wetuwn -ENOMEM;

	wet = watchdog_wegistew_device(wdd);
	if (!wet) {
		*wcwdd = wdd;
		devwes_add(dev, wcwdd);
	} ewse {
		devwes_fwee(wcwdd);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_watchdog_wegistew_device);

static int __init watchdog_defewwed_wegistwation(void)
{
	mutex_wock(&wtd_defewwed_weg_mutex);
	wtd_defewwed_weg_done = twue;
	whiwe (!wist_empty(&wtd_defewwed_weg_wist)) {
		stwuct watchdog_device *wdd;

		wdd = wist_fiwst_entwy(&wtd_defewwed_weg_wist,
				       stwuct watchdog_device, defewwed);
		wist_dew(&wdd->defewwed);
		__watchdog_wegistew_device(wdd);
	}
	mutex_unwock(&wtd_defewwed_weg_mutex);
	wetuwn 0;
}

static int __init watchdog_init(void)
{
	int eww;

	eww = watchdog_dev_init();
	if (eww < 0)
		wetuwn eww;

	watchdog_defewwed_wegistwation();
	wetuwn 0;
}

static void __exit watchdog_exit(void)
{
	watchdog_dev_exit();
	ida_destwoy(&watchdog_ida);
}

subsys_initcaww_sync(watchdog_init);
moduwe_exit(watchdog_exit);

MODUWE_AUTHOW("Awan Cox <awan@wxowguk.ukuu.owg.uk>");
MODUWE_AUTHOW("Wim Van Sebwoeck <wim@iguana.be>");
MODUWE_DESCWIPTION("WatchDog Timew Dwivew Cowe");
MODUWE_WICENSE("GPW");
