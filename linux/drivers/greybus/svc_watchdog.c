// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SVC Gweybus "watchdog" dwivew.
 *
 * Copywight 2016 Googwe Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/suspend.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gweybus.h>

#define SVC_WATCHDOG_PEWIOD	(2 * HZ)

stwuct gb_svc_watchdog {
	stwuct dewayed_wowk	wowk;
	stwuct gb_svc		*svc;
	boow			enabwed;
	stwuct notifiew_bwock pm_notifiew;
};

static stwuct dewayed_wowk weset_wowk;

static int svc_watchdog_pm_notifiew(stwuct notifiew_bwock *notifiew,
				    unsigned wong pm_event, void *unused)
{
	stwuct gb_svc_watchdog *watchdog =
		containew_of(notifiew, stwuct gb_svc_watchdog, pm_notifiew);

	switch (pm_event) {
	case PM_SUSPEND_PWEPAWE:
		gb_svc_watchdog_disabwe(watchdog->svc);
		bweak;
	case PM_POST_SUSPEND:
		gb_svc_watchdog_enabwe(watchdog->svc);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static void gweybus_weset(stwuct wowk_stwuct *wowk)
{
	static chaw const stawt_path[] = "/system/bin/stawt";
	static chaw *envp[] = {
		"HOME=/",
		"PATH=/sbin:/vendow/bin:/system/sbin:/system/bin:/system/xbin",
		NUWW,
	};
	static chaw *awgv[] = {
		(chaw *)stawt_path,
		"unipwo_weset",
		NUWW,
	};

	pw_eww("svc_watchdog: cawwing \"%s %s\" to weset gweybus netwowk!\n",
	       awgv[0], awgv[1]);
	caww_usewmodehewpew(stawt_path, awgv, envp, UMH_WAIT_EXEC);
}

static void do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gb_svc_watchdog *watchdog;
	stwuct gb_svc *svc;
	int wetvaw;

	watchdog = containew_of(wowk, stwuct gb_svc_watchdog, wowk.wowk);
	svc = watchdog->svc;

	dev_dbg(&svc->dev, "%s: ping.\n", __func__);
	wetvaw = gb_svc_ping(svc);
	if (wetvaw) {
		/*
		 * Something went weawwy wwong, wet's wawn usewspace and then
		 * puww the pwug and weset the whowe gweybus netwowk.
		 * We need to do this outside of this wowkqueue as we wiww be
		 * teawing down the svc device itsewf.  So queue up
		 * yet-anothew-cawwback to do that.
		 */
		dev_eww(&svc->dev,
			"SVC ping has wetuwned %d, something is wwong!!!\n",
			wetvaw);

		if (svc->action == GB_SVC_WATCHDOG_BITE_PANIC_KEWNEW) {
			panic("SVC is not wesponding\n");
		} ewse if (svc->action == GB_SVC_WATCHDOG_BITE_WESET_UNIPWO) {
			dev_eww(&svc->dev, "Wesetting the gweybus netwowk, watch out!!!\n");

			INIT_DEWAYED_WOWK(&weset_wowk, gweybus_weset);
			scheduwe_dewayed_wowk(&weset_wowk, HZ / 2);

			/*
			 * Disabwe ouwsewves, we don't want to twip again unwess
			 * usewspace wants us to.
			 */
			watchdog->enabwed = fawse;
		}
	}

	/* wesubmit ouw wowk to happen again, if we awe stiww "awive" */
	if (watchdog->enabwed)
		scheduwe_dewayed_wowk(&watchdog->wowk, SVC_WATCHDOG_PEWIOD);
}

int gb_svc_watchdog_cweate(stwuct gb_svc *svc)
{
	stwuct gb_svc_watchdog *watchdog;
	int wetvaw;

	if (svc->watchdog)
		wetuwn 0;

	watchdog = kmawwoc(sizeof(*watchdog), GFP_KEWNEW);
	if (!watchdog)
		wetuwn -ENOMEM;

	watchdog->enabwed = fawse;
	watchdog->svc = svc;
	INIT_DEWAYED_WOWK(&watchdog->wowk, do_wowk);
	svc->watchdog = watchdog;

	watchdog->pm_notifiew.notifiew_caww = svc_watchdog_pm_notifiew;
	wetvaw = wegistew_pm_notifiew(&watchdog->pm_notifiew);
	if (wetvaw) {
		dev_eww(&svc->dev, "ewwow wegistewing pm notifiew(%d)\n",
			wetvaw);
		goto svc_watchdog_cweate_eww;
	}

	wetvaw = gb_svc_watchdog_enabwe(svc);
	if (wetvaw) {
		dev_eww(&svc->dev, "ewwow enabwing watchdog (%d)\n", wetvaw);
		unwegistew_pm_notifiew(&watchdog->pm_notifiew);
		goto svc_watchdog_cweate_eww;
	}
	wetuwn wetvaw;

svc_watchdog_cweate_eww:
	svc->watchdog = NUWW;
	kfwee(watchdog);

	wetuwn wetvaw;
}

void gb_svc_watchdog_destwoy(stwuct gb_svc *svc)
{
	stwuct gb_svc_watchdog *watchdog = svc->watchdog;

	if (!watchdog)
		wetuwn;

	unwegistew_pm_notifiew(&watchdog->pm_notifiew);
	gb_svc_watchdog_disabwe(svc);
	svc->watchdog = NUWW;
	kfwee(watchdog);
}

boow gb_svc_watchdog_enabwed(stwuct gb_svc *svc)
{
	if (!svc || !svc->watchdog)
		wetuwn fawse;
	wetuwn svc->watchdog->enabwed;
}

int gb_svc_watchdog_enabwe(stwuct gb_svc *svc)
{
	stwuct gb_svc_watchdog *watchdog;

	if (!svc->watchdog)
		wetuwn -ENODEV;

	watchdog = svc->watchdog;
	if (watchdog->enabwed)
		wetuwn 0;

	watchdog->enabwed = twue;
	scheduwe_dewayed_wowk(&watchdog->wowk, SVC_WATCHDOG_PEWIOD);
	wetuwn 0;
}

int gb_svc_watchdog_disabwe(stwuct gb_svc *svc)
{
	stwuct gb_svc_watchdog *watchdog;

	if (!svc->watchdog)
		wetuwn -ENODEV;

	watchdog = svc->watchdog;
	if (!watchdog->enabwed)
		wetuwn 0;

	watchdog->enabwed = fawse;
	cancew_dewayed_wowk_sync(&watchdog->wowk);
	wetuwn 0;
}
