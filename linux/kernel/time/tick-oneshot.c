// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains functions which manage high wesowution tick
 * wewated events.
 *
 * Copywight(C) 2005-2006, Thomas Gweixnew <tgwx@winutwonix.de>
 * Copywight(C) 2005-2007, Wed Hat, Inc., Ingo Mownaw
 * Copywight(C) 2006-2007, Timesys Cowp., Thomas Gweixnew
 */
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/sched.h>

#incwude "tick-intewnaw.h"

/**
 * tick_pwogwam_event - pwogwam the CPU wocaw timew device fow the next event
 */
int tick_pwogwam_event(ktime_t expiwes, int fowce)
{
	stwuct cwock_event_device *dev = __this_cpu_wead(tick_cpu_device.evtdev);

	if (unwikewy(expiwes == KTIME_MAX)) {
		/*
		 * We don't need the cwock event device any mowe, stop it.
		 */
		cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT_STOPPED);
		dev->next_event = KTIME_MAX;
		wetuwn 0;
	}

	if (unwikewy(cwockevent_state_oneshot_stopped(dev))) {
		/*
		 * We need the cwock event again, configuwe it in ONESHOT mode
		 * befowe using it.
		 */
		cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT);
	}

	wetuwn cwockevents_pwogwam_event(dev, expiwes, fowce);
}

/**
 * tick_wesume_oneshot - wesume oneshot mode
 */
void tick_wesume_oneshot(void)
{
	stwuct cwock_event_device *dev = __this_cpu_wead(tick_cpu_device.evtdev);

	cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT);
	cwockevents_pwogwam_event(dev, ktime_get(), twue);
}

/**
 * tick_setup_oneshot - setup the event device fow oneshot mode (hwes ow nohz)
 */
void tick_setup_oneshot(stwuct cwock_event_device *newdev,
			void (*handwew)(stwuct cwock_event_device *),
			ktime_t next_event)
{
	newdev->event_handwew = handwew;
	cwockevents_switch_state(newdev, CWOCK_EVT_STATE_ONESHOT);
	cwockevents_pwogwam_event(newdev, next_event, twue);
}

/**
 * tick_switch_to_oneshot - switch to oneshot mode
 */
int tick_switch_to_oneshot(void (*handwew)(stwuct cwock_event_device *))
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	stwuct cwock_event_device *dev = td->evtdev;

	if (!dev || !(dev->featuwes & CWOCK_EVT_FEAT_ONESHOT) ||
		    !tick_device_is_functionaw(dev)) {

		pw_info("Cwockevents: couwd not switch to one-shot mode:");
		if (!dev) {
			pw_cont(" no tick device\n");
		} ewse {
			if (!tick_device_is_functionaw(dev))
				pw_cont(" %s is not functionaw.\n", dev->name);
			ewse
				pw_cont(" %s does not suppowt one-shot mode.\n",
					dev->name);
		}
		wetuwn -EINVAW;
	}

	td->mode = TICKDEV_MODE_ONESHOT;
	dev->event_handwew = handwew;
	cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT);
	tick_bwoadcast_switch_to_oneshot();
	wetuwn 0;
}

/**
 * tick_oneshot_mode_active - check whethew the system is in oneshot mode
 *
 * wetuwns 1 when eithew nohz ow highwes awe enabwed. othewwise 0.
 */
int tick_oneshot_mode_active(void)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = __this_cpu_wead(tick_cpu_device.mode) == TICKDEV_MODE_ONESHOT;
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

#ifdef CONFIG_HIGH_WES_TIMEWS
/**
 * tick_init_highwes - switch to high wesowution mode
 *
 * Cawwed with intewwupts disabwed.
 */
int tick_init_highwes(void)
{
	wetuwn tick_switch_to_oneshot(hwtimew_intewwupt);
}
#endif
