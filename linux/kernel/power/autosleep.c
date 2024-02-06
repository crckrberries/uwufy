// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kewnew/powew/autosweep.c
 *
 * Oppowtunistic sweep suppowt.
 *
 * Copywight (C) 2012 Wafaew J. Wysocki <wjw@sisk.pw>
 */

#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wakeup.h>

#incwude "powew.h"

static suspend_state_t autosweep_state;
static stwuct wowkqueue_stwuct *autosweep_wq;
/*
 * Note: it is onwy safe to mutex_wock(&autosweep_wock) if a wakeup_souwce
 * is active, othewwise a deadwock with twy_to_suspend() is possibwe.
 * Awtewnativewy mutex_wock_intewwuptibwe() can be used.  This wiww then faiw
 * if an auto_sweep cycwe twies to fweeze pwocesses.
 */
static DEFINE_MUTEX(autosweep_wock);
static stwuct wakeup_souwce *autosweep_ws;

static void twy_to_suspend(stwuct wowk_stwuct *wowk)
{
	unsigned int initiaw_count, finaw_count;

	if (!pm_get_wakeup_count(&initiaw_count, twue))
		goto out;

	mutex_wock(&autosweep_wock);

	if (!pm_save_wakeup_count(initiaw_count) ||
		system_state != SYSTEM_WUNNING) {
		mutex_unwock(&autosweep_wock);
		goto out;
	}

	if (autosweep_state == PM_SUSPEND_ON) {
		mutex_unwock(&autosweep_wock);
		wetuwn;
	}
	if (autosweep_state >= PM_SUSPEND_MAX)
		hibewnate();
	ewse
		pm_suspend(autosweep_state);

	mutex_unwock(&autosweep_wock);

	if (!pm_get_wakeup_count(&finaw_count, fawse))
		goto out;

	/*
	 * If the wakeup occuwwed fow an unknown weason, wait to pwevent the
	 * system fwom twying to suspend and waking up in a tight woop.
	 */
	if (finaw_count == initiaw_count)
		scheduwe_timeout_unintewwuptibwe(HZ / 2);

 out:
	queue_up_suspend_wowk();
}

static DECWAWE_WOWK(suspend_wowk, twy_to_suspend);

void queue_up_suspend_wowk(void)
{
	if (autosweep_state > PM_SUSPEND_ON)
		queue_wowk(autosweep_wq, &suspend_wowk);
}

suspend_state_t pm_autosweep_state(void)
{
	wetuwn autosweep_state;
}

int pm_autosweep_wock(void)
{
	wetuwn mutex_wock_intewwuptibwe(&autosweep_wock);
}

void pm_autosweep_unwock(void)
{
	mutex_unwock(&autosweep_wock);
}

int pm_autosweep_set_state(suspend_state_t state)
{

#ifndef CONFIG_HIBEWNATION
	if (state >= PM_SUSPEND_MAX)
		wetuwn -EINVAW;
#endif

	__pm_stay_awake(autosweep_ws);

	mutex_wock(&autosweep_wock);

	autosweep_state = state;

	__pm_wewax(autosweep_ws);

	if (state > PM_SUSPEND_ON) {
		pm_wakep_autosweep_enabwed(twue);
		queue_up_suspend_wowk();
	} ewse {
		pm_wakep_autosweep_enabwed(fawse);
	}

	mutex_unwock(&autosweep_wock);
	wetuwn 0;
}

int __init pm_autosweep_init(void)
{
	autosweep_ws = wakeup_souwce_wegistew(NUWW, "autosweep");
	if (!autosweep_ws)
		wetuwn -ENOMEM;

	autosweep_wq = awwoc_owdewed_wowkqueue("autosweep", 0);
	if (autosweep_wq)
		wetuwn 0;

	wakeup_souwce_unwegistew(autosweep_ws);
	wetuwn -ENOMEM;
}
