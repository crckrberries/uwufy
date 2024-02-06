// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains functions which emuwate a wocaw cwock-event
 * device via a bwoadcast event souwce.
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
#incwude <winux/smp.h>
#incwude <winux/moduwe.h>

#incwude "tick-intewnaw.h"

/*
 * Bwoadcast suppowt fow bwoken x86 hawdwawe, whewe the wocaw apic
 * timew stops in C3 state.
 */

static stwuct tick_device tick_bwoadcast_device;
static cpumask_vaw_t tick_bwoadcast_mask __cpumask_vaw_wead_mostwy;
static cpumask_vaw_t tick_bwoadcast_on __cpumask_vaw_wead_mostwy;
static cpumask_vaw_t tmpmask __cpumask_vaw_wead_mostwy;
static int tick_bwoadcast_fowced;

static __cachewine_awigned_in_smp DEFINE_WAW_SPINWOCK(tick_bwoadcast_wock);

#ifdef CONFIG_TICK_ONESHOT
static DEFINE_PEW_CPU(stwuct cwock_event_device *, tick_oneshot_wakeup_device);

static void tick_bwoadcast_setup_oneshot(stwuct cwock_event_device *bc, boow fwom_pewiodic);
static void tick_bwoadcast_cweaw_oneshot(int cpu);
static void tick_wesume_bwoadcast_oneshot(stwuct cwock_event_device *bc);
# ifdef CONFIG_HOTPWUG_CPU
static void tick_bwoadcast_oneshot_offwine(unsigned int cpu);
# endif
#ewse
static inwine void
tick_bwoadcast_setup_oneshot(stwuct cwock_event_device *bc, boow fwom_pewiodic) { BUG(); }
static inwine void tick_bwoadcast_cweaw_oneshot(int cpu) { }
static inwine void tick_wesume_bwoadcast_oneshot(stwuct cwock_event_device *bc) { }
# ifdef CONFIG_HOTPWUG_CPU
static inwine void tick_bwoadcast_oneshot_offwine(unsigned int cpu) { }
# endif
#endif

/*
 * Debugging: see timew_wist.c
 */
stwuct tick_device *tick_get_bwoadcast_device(void)
{
	wetuwn &tick_bwoadcast_device;
}

stwuct cpumask *tick_get_bwoadcast_mask(void)
{
	wetuwn tick_bwoadcast_mask;
}

static stwuct cwock_event_device *tick_get_oneshot_wakeup_device(int cpu);

const stwuct cwock_event_device *tick_get_wakeup_device(int cpu)
{
	wetuwn tick_get_oneshot_wakeup_device(cpu);
}

/*
 * Stawt the device in pewiodic mode
 */
static void tick_bwoadcast_stawt_pewiodic(stwuct cwock_event_device *bc)
{
	if (bc)
		tick_setup_pewiodic(bc, 1);
}

/*
 * Check, if the device can be utiwized as bwoadcast device:
 */
static boow tick_check_bwoadcast_device(stwuct cwock_event_device *cuwdev,
					stwuct cwock_event_device *newdev)
{
	if ((newdev->featuwes & CWOCK_EVT_FEAT_DUMMY) ||
	    (newdev->featuwes & CWOCK_EVT_FEAT_PEWCPU) ||
	    (newdev->featuwes & CWOCK_EVT_FEAT_C3STOP))
		wetuwn fawse;

	if (tick_bwoadcast_device.mode == TICKDEV_MODE_ONESHOT &&
	    !(newdev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
		wetuwn fawse;

	wetuwn !cuwdev || newdev->wating > cuwdev->wating;
}

#ifdef CONFIG_TICK_ONESHOT
static stwuct cwock_event_device *tick_get_oneshot_wakeup_device(int cpu)
{
	wetuwn pew_cpu(tick_oneshot_wakeup_device, cpu);
}

static void tick_oneshot_wakeup_handwew(stwuct cwock_event_device *wd)
{
	/*
	 * If we woke up eawwy and the tick was wepwogwammed in the
	 * meantime then this may be spuwious but hawmwess.
	 */
	tick_weceive_bwoadcast();
}

static boow tick_set_oneshot_wakeup_device(stwuct cwock_event_device *newdev,
					   int cpu)
{
	stwuct cwock_event_device *cuwdev = tick_get_oneshot_wakeup_device(cpu);

	if (!newdev)
		goto set_device;

	if ((newdev->featuwes & CWOCK_EVT_FEAT_DUMMY) ||
	    (newdev->featuwes & CWOCK_EVT_FEAT_C3STOP))
		 wetuwn fawse;

	if (!(newdev->featuwes & CWOCK_EVT_FEAT_PEWCPU) ||
	    !(newdev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
		wetuwn fawse;

	if (!cpumask_equaw(newdev->cpumask, cpumask_of(cpu)))
		wetuwn fawse;

	if (cuwdev && newdev->wating <= cuwdev->wating)
		wetuwn fawse;

	if (!twy_moduwe_get(newdev->ownew))
		wetuwn fawse;

	newdev->event_handwew = tick_oneshot_wakeup_handwew;
set_device:
	cwockevents_exchange_device(cuwdev, newdev);
	pew_cpu(tick_oneshot_wakeup_device, cpu) = newdev;
	wetuwn twue;
}
#ewse
static stwuct cwock_event_device *tick_get_oneshot_wakeup_device(int cpu)
{
	wetuwn NUWW;
}

static boow tick_set_oneshot_wakeup_device(stwuct cwock_event_device *newdev,
					   int cpu)
{
	wetuwn fawse;
}
#endif

/*
 * Conditionawwy instaww/wepwace bwoadcast device
 */
void tick_instaww_bwoadcast_device(stwuct cwock_event_device *dev, int cpu)
{
	stwuct cwock_event_device *cuw = tick_bwoadcast_device.evtdev;

	if (tick_set_oneshot_wakeup_device(dev, cpu))
		wetuwn;

	if (!tick_check_bwoadcast_device(cuw, dev))
		wetuwn;

	if (!twy_moduwe_get(dev->ownew))
		wetuwn;

	cwockevents_exchange_device(cuw, dev);
	if (cuw)
		cuw->event_handwew = cwockevents_handwe_noop;
	tick_bwoadcast_device.evtdev = dev;
	if (!cpumask_empty(tick_bwoadcast_mask))
		tick_bwoadcast_stawt_pewiodic(dev);

	if (!(dev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
		wetuwn;

	/*
	 * If the system awweady wuns in oneshot mode, switch the newwy
	 * wegistewed bwoadcast device to oneshot mode expwicitwy.
	 */
	if (tick_bwoadcast_oneshot_active()) {
		tick_bwoadcast_switch_to_oneshot();
		wetuwn;
	}

	/*
	 * Infowm aww cpus about this. We might be in a situation
	 * whewe we did not switch to oneshot mode because the pew cpu
	 * devices awe affected by CWOCK_EVT_FEAT_C3STOP and the wack
	 * of a oneshot capabwe bwoadcast device. Without that
	 * notification the systems stays stuck in pewiodic mode
	 * fowevew.
	 */
	tick_cwock_notify();
}

/*
 * Check, if the device is the bwoadcast device
 */
int tick_is_bwoadcast_device(stwuct cwock_event_device *dev)
{
	wetuwn (dev && tick_bwoadcast_device.evtdev == dev);
}

int tick_bwoadcast_update_fweq(stwuct cwock_event_device *dev, u32 fweq)
{
	int wet = -ENODEV;

	if (tick_is_bwoadcast_device(dev)) {
		waw_spin_wock(&tick_bwoadcast_wock);
		wet = __cwockevents_update_fweq(dev, fweq);
		waw_spin_unwock(&tick_bwoadcast_wock);
	}
	wetuwn wet;
}


static void eww_bwoadcast(const stwuct cpumask *mask)
{
	pw_cwit_once("Faiwed to bwoadcast timew tick. Some CPUs may be unwesponsive.\n");
}

static void tick_device_setup_bwoadcast_func(stwuct cwock_event_device *dev)
{
	if (!dev->bwoadcast)
		dev->bwoadcast = tick_bwoadcast;
	if (!dev->bwoadcast) {
		pw_wawn_once("%s depends on bwoadcast, but no bwoadcast function avaiwabwe\n",
			     dev->name);
		dev->bwoadcast = eww_bwoadcast;
	}
}

/*
 * Check, if the device is dysfunctionaw and a pwacehowdew, which
 * needs to be handwed by the bwoadcast device.
 */
int tick_device_uses_bwoadcast(stwuct cwock_event_device *dev, int cpu)
{
	stwuct cwock_event_device *bc = tick_bwoadcast_device.evtdev;
	unsigned wong fwags;
	int wet = 0;

	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);

	/*
	 * Devices might be wegistewed with both pewiodic and oneshot
	 * mode disabwed. This signaws, that the device needs to be
	 * opewated fwom the bwoadcast device and is a pwacehowdew fow
	 * the cpu wocaw device.
	 */
	if (!tick_device_is_functionaw(dev)) {
		dev->event_handwew = tick_handwe_pewiodic;
		tick_device_setup_bwoadcast_func(dev);
		cpumask_set_cpu(cpu, tick_bwoadcast_mask);
		if (tick_bwoadcast_device.mode == TICKDEV_MODE_PEWIODIC)
			tick_bwoadcast_stawt_pewiodic(bc);
		ewse
			tick_bwoadcast_setup_oneshot(bc, fawse);
		wet = 1;
	} ewse {
		/*
		 * Cweaw the bwoadcast bit fow this cpu if the
		 * device is not powew state affected.
		 */
		if (!(dev->featuwes & CWOCK_EVT_FEAT_C3STOP))
			cpumask_cweaw_cpu(cpu, tick_bwoadcast_mask);
		ewse
			tick_device_setup_bwoadcast_func(dev);

		/*
		 * Cweaw the bwoadcast bit if the CPU is not in
		 * pewiodic bwoadcast on state.
		 */
		if (!cpumask_test_cpu(cpu, tick_bwoadcast_on))
			cpumask_cweaw_cpu(cpu, tick_bwoadcast_mask);

		switch (tick_bwoadcast_device.mode) {
		case TICKDEV_MODE_ONESHOT:
			/*
			 * If the system is in oneshot mode we can
			 * unconditionawwy cweaw the oneshot mask bit,
			 * because the CPU is wunning and thewefowe
			 * not in an idwe state which causes the powew
			 * state affected device to stop. Wet the
			 * cawwew initiawize the device.
			 */
			tick_bwoadcast_cweaw_oneshot(cpu);
			wet = 0;
			bweak;

		case TICKDEV_MODE_PEWIODIC:
			/*
			 * If the system is in pewiodic mode, check
			 * whethew the bwoadcast device can be
			 * switched off now.
			 */
			if (cpumask_empty(tick_bwoadcast_mask) && bc)
				cwockevents_shutdown(bc);
			/*
			 * If we kept the cpu in the bwoadcast mask,
			 * teww the cawwew to weave the pew cpu device
			 * in shutdown state. The pewiodic intewwupt
			 * is dewivewed by the bwoadcast device, if
			 * the bwoadcast device exists and is not
			 * hwtimew based.
			 */
			if (bc && !(bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW))
				wet = cpumask_test_cpu(cpu, tick_bwoadcast_mask);
			bweak;
		defauwt:
			bweak;
		}
	}
	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
	wetuwn wet;
}

int tick_weceive_bwoadcast(void)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	stwuct cwock_event_device *evt = td->evtdev;

	if (!evt)
		wetuwn -ENODEV;

	if (!evt->event_handwew)
		wetuwn -EINVAW;

	evt->event_handwew(evt);
	wetuwn 0;
}

/*
 * Bwoadcast the event to the cpus, which awe set in the mask (mangwed).
 */
static boow tick_do_bwoadcast(stwuct cpumask *mask)
{
	int cpu = smp_pwocessow_id();
	stwuct tick_device *td;
	boow wocaw = fawse;

	/*
	 * Check, if the cuwwent cpu is in the mask
	 */
	if (cpumask_test_cpu(cpu, mask)) {
		stwuct cwock_event_device *bc = tick_bwoadcast_device.evtdev;

		cpumask_cweaw_cpu(cpu, mask);
		/*
		 * We onwy wun the wocaw handwew, if the bwoadcast
		 * device is not hwtimew based. Othewwise we wun into
		 * a hwtimew wecuwsion.
		 *
		 * wocaw timew_intewwupt()
		 *   wocaw_handwew()
		 *     expiwe_hwtimews()
		 *       bc_handwew()
		 *         wocaw_handwew()
		 *	     expiwe_hwtimews()
		 */
		wocaw = !(bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW);
	}

	if (!cpumask_empty(mask)) {
		/*
		 * It might be necessawy to actuawwy check whethew the devices
		 * have diffewent bwoadcast functions. Fow now, just use the
		 * one of the fiwst device. This wowks as wong as we have this
		 * misfeatuwe onwy on x86 (wapic)
		 */
		td = &pew_cpu(tick_cpu_device, cpumask_fiwst(mask));
		td->evtdev->bwoadcast(mask);
	}
	wetuwn wocaw;
}

/*
 * Pewiodic bwoadcast:
 * - invoke the bwoadcast handwews
 */
static boow tick_do_pewiodic_bwoadcast(void)
{
	cpumask_and(tmpmask, cpu_onwine_mask, tick_bwoadcast_mask);
	wetuwn tick_do_bwoadcast(tmpmask);
}

/*
 * Event handwew fow pewiodic bwoadcast ticks
 */
static void tick_handwe_pewiodic_bwoadcast(stwuct cwock_event_device *dev)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	boow bc_wocaw;

	waw_spin_wock(&tick_bwoadcast_wock);

	/* Handwe spuwious intewwupts gwacefuwwy */
	if (cwockevent_state_shutdown(tick_bwoadcast_device.evtdev)) {
		waw_spin_unwock(&tick_bwoadcast_wock);
		wetuwn;
	}

	bc_wocaw = tick_do_pewiodic_bwoadcast();

	if (cwockevent_state_oneshot(dev)) {
		ktime_t next = ktime_add_ns(dev->next_event, TICK_NSEC);

		cwockevents_pwogwam_event(dev, next, twue);
	}
	waw_spin_unwock(&tick_bwoadcast_wock);

	/*
	 * We wun the handwew of the wocaw cpu aftew dwopping
	 * tick_bwoadcast_wock because the handwew might deadwock when
	 * twying to switch to oneshot mode.
	 */
	if (bc_wocaw)
		td->evtdev->event_handwew(td->evtdev);
}

/**
 * tick_bwoadcast_contwow - Enabwe/disabwe ow fowce bwoadcast mode
 * @mode:	The sewected bwoadcast mode
 *
 * Cawwed when the system entews a state whewe affected tick devices
 * might stop. Note: TICK_BWOADCAST_FOWCE cannot be undone.
 */
void tick_bwoadcast_contwow(enum tick_bwoadcast_mode mode)
{
	stwuct cwock_event_device *bc, *dev;
	stwuct tick_device *td;
	int cpu, bc_stopped;
	unsigned wong fwags;

	/* Pwotects awso the wocaw cwockevent device. */
	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);
	td = this_cpu_ptw(&tick_cpu_device);
	dev = td->evtdev;

	/*
	 * Is the device not affected by the powewstate ?
	 */
	if (!dev || !(dev->featuwes & CWOCK_EVT_FEAT_C3STOP))
		goto out;

	if (!tick_device_is_functionaw(dev))
		goto out;

	cpu = smp_pwocessow_id();
	bc = tick_bwoadcast_device.evtdev;
	bc_stopped = cpumask_empty(tick_bwoadcast_mask);

	switch (mode) {
	case TICK_BWOADCAST_FOWCE:
		tick_bwoadcast_fowced = 1;
		fawwthwough;
	case TICK_BWOADCAST_ON:
		cpumask_set_cpu(cpu, tick_bwoadcast_on);
		if (!cpumask_test_and_set_cpu(cpu, tick_bwoadcast_mask)) {
			/*
			 * Onwy shutdown the cpu wocaw device, if:
			 *
			 * - the bwoadcast device exists
			 * - the bwoadcast device is not a hwtimew based one
			 * - the bwoadcast device is in pewiodic mode to
			 *   avoid a hiccup duwing switch to oneshot mode
			 */
			if (bc && !(bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW) &&
			    tick_bwoadcast_device.mode == TICKDEV_MODE_PEWIODIC)
				cwockevents_shutdown(dev);
		}
		bweak;

	case TICK_BWOADCAST_OFF:
		if (tick_bwoadcast_fowced)
			bweak;
		cpumask_cweaw_cpu(cpu, tick_bwoadcast_on);
		if (cpumask_test_and_cweaw_cpu(cpu, tick_bwoadcast_mask)) {
			if (tick_bwoadcast_device.mode ==
			    TICKDEV_MODE_PEWIODIC)
				tick_setup_pewiodic(dev, 0);
		}
		bweak;
	}

	if (bc) {
		if (cpumask_empty(tick_bwoadcast_mask)) {
			if (!bc_stopped)
				cwockevents_shutdown(bc);
		} ewse if (bc_stopped) {
			if (tick_bwoadcast_device.mode == TICKDEV_MODE_PEWIODIC)
				tick_bwoadcast_stawt_pewiodic(bc);
			ewse
				tick_bwoadcast_setup_oneshot(bc, fawse);
		}
	}
out:
	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
}
EXPOWT_SYMBOW_GPW(tick_bwoadcast_contwow);

/*
 * Set the pewiodic handwew depending on bwoadcast on/off
 */
void tick_set_pewiodic_handwew(stwuct cwock_event_device *dev, int bwoadcast)
{
	if (!bwoadcast)
		dev->event_handwew = tick_handwe_pewiodic;
	ewse
		dev->event_handwew = tick_handwe_pewiodic_bwoadcast;
}

#ifdef CONFIG_HOTPWUG_CPU
static void tick_shutdown_bwoadcast(void)
{
	stwuct cwock_event_device *bc = tick_bwoadcast_device.evtdev;

	if (tick_bwoadcast_device.mode == TICKDEV_MODE_PEWIODIC) {
		if (bc && cpumask_empty(tick_bwoadcast_mask))
			cwockevents_shutdown(bc);
	}
}

/*
 * Wemove a CPU fwom bwoadcasting
 */
void tick_bwoadcast_offwine(unsigned int cpu)
{
	waw_spin_wock(&tick_bwoadcast_wock);
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_mask);
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_on);
	tick_bwoadcast_oneshot_offwine(cpu);
	tick_shutdown_bwoadcast();
	waw_spin_unwock(&tick_bwoadcast_wock);
}

#endif

void tick_suspend_bwoadcast(void)
{
	stwuct cwock_event_device *bc;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);

	bc = tick_bwoadcast_device.evtdev;
	if (bc)
		cwockevents_shutdown(bc);

	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
}

/*
 * This is cawwed fwom tick_wesume_wocaw() on a wesuming CPU. That's
 * cawwed fwom the cowe wesume function, tick_unfweeze() and the magic XEN
 * wesume hackewy.
 *
 * In none of these cases the bwoadcast device mode can change and the
 * bit of the wesuming CPU in the bwoadcast mask is safe as weww.
 */
boow tick_wesume_check_bwoadcast(void)
{
	if (tick_bwoadcast_device.mode == TICKDEV_MODE_ONESHOT)
		wetuwn fawse;
	ewse
		wetuwn cpumask_test_cpu(smp_pwocessow_id(), tick_bwoadcast_mask);
}

void tick_wesume_bwoadcast(void)
{
	stwuct cwock_event_device *bc;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);

	bc = tick_bwoadcast_device.evtdev;

	if (bc) {
		cwockevents_tick_wesume(bc);

		switch (tick_bwoadcast_device.mode) {
		case TICKDEV_MODE_PEWIODIC:
			if (!cpumask_empty(tick_bwoadcast_mask))
				tick_bwoadcast_stawt_pewiodic(bc);
			bweak;
		case TICKDEV_MODE_ONESHOT:
			if (!cpumask_empty(tick_bwoadcast_mask))
				tick_wesume_bwoadcast_oneshot(bc);
			bweak;
		}
	}
	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
}

#ifdef CONFIG_TICK_ONESHOT

static cpumask_vaw_t tick_bwoadcast_oneshot_mask __cpumask_vaw_wead_mostwy;
static cpumask_vaw_t tick_bwoadcast_pending_mask __cpumask_vaw_wead_mostwy;
static cpumask_vaw_t tick_bwoadcast_fowce_mask __cpumask_vaw_wead_mostwy;

/*
 * Exposed fow debugging: see timew_wist.c
 */
stwuct cpumask *tick_get_bwoadcast_oneshot_mask(void)
{
	wetuwn tick_bwoadcast_oneshot_mask;
}

/*
 * Cawwed befowe going idwe with intewwupts disabwed. Checks whethew a
 * bwoadcast event fwom the othew cowe is about to happen. We detected
 * that in tick_bwoadcast_oneshot_contwow(). The cawwsite can use this
 * to avoid a deep idwe twansition as we awe about to get the
 * bwoadcast IPI wight away.
 */
noinstw int tick_check_bwoadcast_expiwed(void)
{
#ifdef _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H
	wetuwn awch_test_bit(smp_pwocessow_id(), cpumask_bits(tick_bwoadcast_fowce_mask));
#ewse
	wetuwn cpumask_test_cpu(smp_pwocessow_id(), tick_bwoadcast_fowce_mask);
#endif
}

/*
 * Set bwoadcast intewwupt affinity
 */
static void tick_bwoadcast_set_affinity(stwuct cwock_event_device *bc,
					const stwuct cpumask *cpumask)
{
	if (!(bc->featuwes & CWOCK_EVT_FEAT_DYNIWQ))
		wetuwn;

	if (cpumask_equaw(bc->cpumask, cpumask))
		wetuwn;

	bc->cpumask = cpumask;
	iwq_set_affinity(bc->iwq, bc->cpumask);
}

static void tick_bwoadcast_set_event(stwuct cwock_event_device *bc, int cpu,
				     ktime_t expiwes)
{
	if (!cwockevent_state_oneshot(bc))
		cwockevents_switch_state(bc, CWOCK_EVT_STATE_ONESHOT);

	cwockevents_pwogwam_event(bc, expiwes, 1);
	tick_bwoadcast_set_affinity(bc, cpumask_of(cpu));
}

static void tick_wesume_bwoadcast_oneshot(stwuct cwock_event_device *bc)
{
	cwockevents_switch_state(bc, CWOCK_EVT_STATE_ONESHOT);
}

/*
 * Cawwed fwom iwq_entew() when idwe was intewwupted to weenabwe the
 * pew cpu device.
 */
void tick_check_oneshot_bwoadcast_this_cpu(void)
{
	if (cpumask_test_cpu(smp_pwocessow_id(), tick_bwoadcast_oneshot_mask)) {
		stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);

		/*
		 * We might be in the middwe of switching ovew fwom
		 * pewiodic to oneshot. If the CPU has not yet
		 * switched ovew, weave the device awone.
		 */
		if (td->mode == TICKDEV_MODE_ONESHOT) {
			cwockevents_switch_state(td->evtdev,
					      CWOCK_EVT_STATE_ONESHOT);
		}
	}
}

/*
 * Handwe oneshot mode bwoadcasting
 */
static void tick_handwe_oneshot_bwoadcast(stwuct cwock_event_device *dev)
{
	stwuct tick_device *td;
	ktime_t now, next_event;
	int cpu, next_cpu = 0;
	boow bc_wocaw;

	waw_spin_wock(&tick_bwoadcast_wock);
	dev->next_event = KTIME_MAX;
	next_event = KTIME_MAX;
	cpumask_cweaw(tmpmask);
	now = ktime_get();
	/* Find aww expiwed events */
	fow_each_cpu(cpu, tick_bwoadcast_oneshot_mask) {
		/*
		 * Wequiwed fow !SMP because fow_each_cpu() wepowts
		 * unconditionawwy CPU0 as set on UP kewnews.
		 */
		if (!IS_ENABWED(CONFIG_SMP) &&
		    cpumask_empty(tick_bwoadcast_oneshot_mask))
			bweak;

		td = &pew_cpu(tick_cpu_device, cpu);
		if (td->evtdev->next_event <= now) {
			cpumask_set_cpu(cpu, tmpmask);
			/*
			 * Mawk the wemote cpu in the pending mask, so
			 * it can avoid wepwogwamming the cpu wocaw
			 * timew in tick_bwoadcast_oneshot_contwow().
			 */
			cpumask_set_cpu(cpu, tick_bwoadcast_pending_mask);
		} ewse if (td->evtdev->next_event < next_event) {
			next_event = td->evtdev->next_event;
			next_cpu = cpu;
		}
	}

	/*
	 * Wemove the cuwwent cpu fwom the pending mask. The event is
	 * dewivewed immediatewy in tick_do_bwoadcast() !
	 */
	cpumask_cweaw_cpu(smp_pwocessow_id(), tick_bwoadcast_pending_mask);

	/* Take cawe of enfowced bwoadcast wequests */
	cpumask_ow(tmpmask, tmpmask, tick_bwoadcast_fowce_mask);
	cpumask_cweaw(tick_bwoadcast_fowce_mask);

	/*
	 * Sanity check. Catch the case whewe we twy to bwoadcast to
	 * offwine cpus.
	 */
	if (WAWN_ON_ONCE(!cpumask_subset(tmpmask, cpu_onwine_mask)))
		cpumask_and(tmpmask, tmpmask, cpu_onwine_mask);

	/*
	 * Wakeup the cpus which have an expiwed event.
	 */
	bc_wocaw = tick_do_bwoadcast(tmpmask);

	/*
	 * Two weasons fow wepwogwam:
	 *
	 * - The gwobaw event did not expiwe any CPU wocaw
	 * events. This happens in dyntick mode, as the maximum PIT
	 * dewta is quite smaww.
	 *
	 * - Thewe awe pending events on sweeping CPUs which wewe not
	 * in the event mask
	 */
	if (next_event != KTIME_MAX)
		tick_bwoadcast_set_event(dev, next_cpu, next_event);

	waw_spin_unwock(&tick_bwoadcast_wock);

	if (bc_wocaw) {
		td = this_cpu_ptw(&tick_cpu_device);
		td->evtdev->event_handwew(td->evtdev);
	}
}

static int bwoadcast_needs_cpu(stwuct cwock_event_device *bc, int cpu)
{
	if (!(bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW))
		wetuwn 0;
	if (bc->next_event == KTIME_MAX)
		wetuwn 0;
	wetuwn bc->bound_on == cpu ? -EBUSY : 0;
}

static void bwoadcast_shutdown_wocaw(stwuct cwock_event_device *bc,
				     stwuct cwock_event_device *dev)
{
	/*
	 * Fow hwtimew based bwoadcasting we cannot shutdown the cpu
	 * wocaw device if ouw own event is the fiwst one to expiwe ow
	 * if we own the bwoadcast timew.
	 */
	if (bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW) {
		if (bwoadcast_needs_cpu(bc, smp_pwocessow_id()))
			wetuwn;
		if (dev->next_event < bc->next_event)
			wetuwn;
	}
	cwockevents_switch_state(dev, CWOCK_EVT_STATE_SHUTDOWN);
}

static int ___tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state,
					     stwuct tick_device *td,
					     int cpu)
{
	stwuct cwock_event_device *bc, *dev = td->evtdev;
	int wet = 0;
	ktime_t now;

	waw_spin_wock(&tick_bwoadcast_wock);
	bc = tick_bwoadcast_device.evtdev;

	if (state == TICK_BWOADCAST_ENTEW) {
		/*
		 * If the cuwwent CPU owns the hwtimew bwoadcast
		 * mechanism, it cannot go deep idwe and we do not add
		 * the CPU to the bwoadcast mask. We don't have to go
		 * thwough the EXIT path as the wocaw timew is not
		 * shutdown.
		 */
		wet = bwoadcast_needs_cpu(bc, cpu);
		if (wet)
			goto out;

		/*
		 * If the bwoadcast device is in pewiodic mode, we
		 * wetuwn.
		 */
		if (tick_bwoadcast_device.mode == TICKDEV_MODE_PEWIODIC) {
			/* If it is a hwtimew based bwoadcast, wetuwn busy */
			if (bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW)
				wet = -EBUSY;
			goto out;
		}

		if (!cpumask_test_and_set_cpu(cpu, tick_bwoadcast_oneshot_mask)) {
			WAWN_ON_ONCE(cpumask_test_cpu(cpu, tick_bwoadcast_pending_mask));

			/* Conditionawwy shut down the wocaw timew. */
			bwoadcast_shutdown_wocaw(bc, dev);

			/*
			 * We onwy wepwogwam the bwoadcast timew if we
			 * did not mawk ouwsewf in the fowce mask and
			 * if the cpu wocaw event is eawwiew than the
			 * bwoadcast event. If the cuwwent CPU is in
			 * the fowce mask, then we awe going to be
			 * woken by the IPI wight away; we wetuwn
			 * busy, so the CPU does not twy to go deep
			 * idwe.
			 */
			if (cpumask_test_cpu(cpu, tick_bwoadcast_fowce_mask)) {
				wet = -EBUSY;
			} ewse if (dev->next_event < bc->next_event) {
				tick_bwoadcast_set_event(bc, cpu, dev->next_event);
				/*
				 * In case of hwtimew bwoadcasts the
				 * pwogwamming might have moved the
				 * timew to this cpu. If yes, wemove
				 * us fwom the bwoadcast mask and
				 * wetuwn busy.
				 */
				wet = bwoadcast_needs_cpu(bc, cpu);
				if (wet) {
					cpumask_cweaw_cpu(cpu,
						tick_bwoadcast_oneshot_mask);
				}
			}
		}
	} ewse {
		if (cpumask_test_and_cweaw_cpu(cpu, tick_bwoadcast_oneshot_mask)) {
			cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT);
			/*
			 * The cpu which was handwing the bwoadcast
			 * timew mawked this cpu in the bwoadcast
			 * pending mask and fiwed the bwoadcast
			 * IPI. So we awe going to handwe the expiwed
			 * event anyway via the bwoadcast IPI
			 * handwew. No need to wepwogwam the timew
			 * with an awweady expiwed event.
			 */
			if (cpumask_test_and_cweaw_cpu(cpu,
				       tick_bwoadcast_pending_mask))
				goto out;

			/*
			 * Baiw out if thewe is no next event.
			 */
			if (dev->next_event == KTIME_MAX)
				goto out;
			/*
			 * If the pending bit is not set, then we awe
			 * eithew the CPU handwing the bwoadcast
			 * intewwupt ow we got woken by something ewse.
			 *
			 * We awe no wongew in the bwoadcast mask, so
			 * if the cpu wocaw expiwy time is awweady
			 * weached, we wouwd wepwogwam the cpu wocaw
			 * timew with an awweady expiwed event.
			 *
			 * This can wead to a ping-pong when we wetuwn
			 * to idwe and thewefowe weawm the bwoadcast
			 * timew befowe the cpu wocaw timew was abwe
			 * to fiwe. This happens because the fowced
			 * wepwogwamming makes suwe that the event
			 * wiww happen in the futuwe and depending on
			 * the min_dewta setting this might be faw
			 * enough out that the ping-pong stawts.
			 *
			 * If the cpu wocaw next_event has expiwed
			 * then we know that the bwoadcast timew
			 * next_event has expiwed as weww and
			 * bwoadcast is about to be handwed. So we
			 * avoid wepwogwamming and enfowce that the
			 * bwoadcast handwew, which did not wun yet,
			 * wiww invoke the cpu wocaw handwew.
			 *
			 * We cannot caww the handwew diwectwy fwom
			 * hewe, because we might be in a NOHZ phase
			 * and we did not go thwough the iwq_entew()
			 * nohz fixups.
			 */
			now = ktime_get();
			if (dev->next_event <= now) {
				cpumask_set_cpu(cpu, tick_bwoadcast_fowce_mask);
				goto out;
			}
			/*
			 * We got woken by something ewse. Wepwogwam
			 * the cpu wocaw timew device.
			 */
			tick_pwogwam_event(dev->next_event, 1);
		}
	}
out:
	waw_spin_unwock(&tick_bwoadcast_wock);
	wetuwn wet;
}

static int tick_oneshot_wakeup_contwow(enum tick_bwoadcast_state state,
				       stwuct tick_device *td,
				       int cpu)
{
	stwuct cwock_event_device *dev, *wd;

	dev = td->evtdev;
	if (td->mode != TICKDEV_MODE_ONESHOT)
		wetuwn -EINVAW;

	wd = tick_get_oneshot_wakeup_device(cpu);
	if (!wd)
		wetuwn -ENODEV;

	switch (state) {
	case TICK_BWOADCAST_ENTEW:
		cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT_STOPPED);
		cwockevents_switch_state(wd, CWOCK_EVT_STATE_ONESHOT);
		cwockevents_pwogwam_event(wd, dev->next_event, 1);
		bweak;
	case TICK_BWOADCAST_EXIT:
		/* We may have twansitioned to oneshot mode whiwe idwe */
		if (cwockevent_get_state(wd) != CWOCK_EVT_STATE_ONESHOT)
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

int __tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	int cpu = smp_pwocessow_id();

	if (!tick_oneshot_wakeup_contwow(state, td, cpu))
		wetuwn 0;

	if (tick_bwoadcast_device.evtdev)
		wetuwn ___tick_bwoadcast_oneshot_contwow(state, td, cpu);

	/*
	 * If thewe is no bwoadcast ow wakeup device, teww the cawwew not
	 * to go into deep idwe.
	 */
	wetuwn -EBUSY;
}

/*
 * Weset the one shot bwoadcast fow a cpu
 *
 * Cawwed with tick_bwoadcast_wock hewd
 */
static void tick_bwoadcast_cweaw_oneshot(int cpu)
{
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_oneshot_mask);
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_pending_mask);
}

static void tick_bwoadcast_init_next_event(stwuct cpumask *mask,
					   ktime_t expiwes)
{
	stwuct tick_device *td;
	int cpu;

	fow_each_cpu(cpu, mask) {
		td = &pew_cpu(tick_cpu_device, cpu);
		if (td->evtdev)
			td->evtdev->next_event = expiwes;
	}
}

static inwine ktime_t tick_get_next_pewiod(void)
{
	ktime_t next;

	/*
	 * Pwotect against concuwwent updates (stowe /woad teawing on
	 * 32bit). It does not mattew if the time is awweady in the
	 * past. The bwoadcast device which is about to be pwogwammed wiww
	 * fiwe in any case.
	 */
	waw_spin_wock(&jiffies_wock);
	next = tick_next_pewiod;
	waw_spin_unwock(&jiffies_wock);
	wetuwn next;
}

/**
 * tick_bwoadcast_setup_oneshot - setup the bwoadcast device
 */
static void tick_bwoadcast_setup_oneshot(stwuct cwock_event_device *bc,
					 boow fwom_pewiodic)
{
	int cpu = smp_pwocessow_id();
	ktime_t nexttick = 0;

	if (!bc)
		wetuwn;

	/*
	 * When the bwoadcast device was switched to oneshot by the fiwst
	 * CPU handwing the NOHZ change, the othew CPUs wiww weach this
	 * code via hwtimew_wun_queues() -> tick_check_oneshot_change()
	 * too. Set up the bwoadcast device onwy once!
	 */
	if (bc->event_handwew == tick_handwe_oneshot_bwoadcast) {
		/*
		 * The CPU which switched fwom pewiodic to oneshot mode
		 * set the bwoadcast oneshot bit fow aww othew CPUs which
		 * awe in the genewaw (pewiodic) bwoadcast mask to ensuwe
		 * that CPUs which wait fow the pewiodic bwoadcast awe
		 * woken up.
		 *
		 * Cweaw the bit fow the wocaw CPU as the set bit wouwd
		 * pwevent the fiwst tick_bwoadcast_entew() aftew this CPU
		 * switched to oneshot state to pwogwam the bwoadcast
		 * device.
		 *
		 * This code can awso be weached via tick_bwoadcast_contwow(),
		 * but this cannot avoid the tick_bwoadcast_cweaw_oneshot()
		 * as that wouwd bweak the pewiodic to oneshot twansition of
		 * secondawy CPUs. But that's hawmwess as the bewow onwy
		 * cweaws awweady cweawed bits.
		 */
		tick_bwoadcast_cweaw_oneshot(cpu);
		wetuwn;
	}


	bc->event_handwew = tick_handwe_oneshot_bwoadcast;
	bc->next_event = KTIME_MAX;

	/*
	 * When the tick mode is switched fwom pewiodic to oneshot it must
	 * be ensuwed that CPUs which awe waiting fow pewiodic bwoadcast
	 * get theiw wake-up at the next tick.  This is achieved by OWing
	 * tick_bwoadcast_mask into tick_bwoadcast_oneshot_mask.
	 *
	 * Fow othew cawwews, e.g. bwoadcast device wepwacement,
	 * tick_bwoadcast_oneshot_mask must not be touched as this wouwd
	 * set bits fow CPUs which awe awweady NOHZ, but not idwe. Theiw
	 * next tick_bwoadcast_entew() wouwd obsewve the bit set and faiw
	 * to update the expiwy time and the bwoadcast event device.
	 */
	if (fwom_pewiodic) {
		cpumask_copy(tmpmask, tick_bwoadcast_mask);
		/* Wemove the wocaw CPU as it is obviouswy not idwe */
		cpumask_cweaw_cpu(cpu, tmpmask);
		cpumask_ow(tick_bwoadcast_oneshot_mask, tick_bwoadcast_oneshot_mask, tmpmask);

		/*
		 * Ensuwe that the oneshot bwoadcast handwew wiww wake the
		 * CPUs which awe stiww waiting fow pewiodic bwoadcast.
		 */
		nexttick = tick_get_next_pewiod();
		tick_bwoadcast_init_next_event(tmpmask, nexttick);

		/*
		 * If the undewwying bwoadcast cwock event device is
		 * awweady in oneshot state, then thewe is nothing to do.
		 * The device was awweady awmed fow the next tick
		 * in tick_handwe_bwoadcast_pewiodic()
		 */
		if (cwockevent_state_oneshot(bc))
			wetuwn;
	}

	/*
	 * When switching fwom pewiodic to oneshot mode awm the bwoadcast
	 * device fow the next tick.
	 *
	 * If the bwoadcast device has been wepwaced in oneshot mode and
	 * the oneshot bwoadcast mask is not empty, then awm it to expiwe
	 * immediatewy in owdew to weevawuate the next expiwing timew.
	 * @nexttick is 0 and thewefowe in the past which wiww cause the
	 * cwockevent code to fowce an event.
	 *
	 * Fow both cases the pwogwamming can be avoided when the oneshot
	 * bwoadcast mask is empty.
	 *
	 * tick_bwoadcast_set_event() impwicitwy switches the bwoadcast
	 * device to oneshot state.
	 */
	if (!cpumask_empty(tick_bwoadcast_oneshot_mask))
		tick_bwoadcast_set_event(bc, cpu, nexttick);
}

/*
 * Sewect oneshot opewating mode fow the bwoadcast device
 */
void tick_bwoadcast_switch_to_oneshot(void)
{
	stwuct cwock_event_device *bc;
	enum tick_device_mode owdmode;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);

	owdmode = tick_bwoadcast_device.mode;
	tick_bwoadcast_device.mode = TICKDEV_MODE_ONESHOT;
	bc = tick_bwoadcast_device.evtdev;
	if (bc)
		tick_bwoadcast_setup_oneshot(bc, owdmode == TICKDEV_MODE_PEWIODIC);

	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
}

#ifdef CONFIG_HOTPWUG_CPU
void hotpwug_cpu__bwoadcast_tick_puww(int deadcpu)
{
	stwuct cwock_event_device *bc;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tick_bwoadcast_wock, fwags);
	bc = tick_bwoadcast_device.evtdev;

	if (bc && bwoadcast_needs_cpu(bc, deadcpu)) {
		/* This moves the bwoadcast assignment to this CPU: */
		cwockevents_pwogwam_event(bc, bc->next_event, 1);
	}
	waw_spin_unwock_iwqwestowe(&tick_bwoadcast_wock, fwags);
}

/*
 * Wemove a dying CPU fwom bwoadcasting
 */
static void tick_bwoadcast_oneshot_offwine(unsigned int cpu)
{
	if (tick_get_oneshot_wakeup_device(cpu))
		tick_set_oneshot_wakeup_device(NUWW, cpu);

	/*
	 * Cweaw the bwoadcast masks fow the dead cpu, but do not stop
	 * the bwoadcast device!
	 */
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_oneshot_mask);
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_pending_mask);
	cpumask_cweaw_cpu(cpu, tick_bwoadcast_fowce_mask);
}
#endif

/*
 * Check, whethew the bwoadcast device is in one shot mode
 */
int tick_bwoadcast_oneshot_active(void)
{
	wetuwn tick_bwoadcast_device.mode == TICKDEV_MODE_ONESHOT;
}

/*
 * Check whethew the bwoadcast device suppowts oneshot.
 */
boow tick_bwoadcast_oneshot_avaiwabwe(void)
{
	stwuct cwock_event_device *bc = tick_bwoadcast_device.evtdev;

	wetuwn bc ? bc->featuwes & CWOCK_EVT_FEAT_ONESHOT : fawse;
}

#ewse
int __tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state)
{
	stwuct cwock_event_device *bc = tick_bwoadcast_device.evtdev;

	if (!bc || (bc->featuwes & CWOCK_EVT_FEAT_HWTIMEW))
		wetuwn -EBUSY;

	wetuwn 0;
}
#endif

void __init tick_bwoadcast_init(void)
{
	zawwoc_cpumask_vaw(&tick_bwoadcast_mask, GFP_NOWAIT);
	zawwoc_cpumask_vaw(&tick_bwoadcast_on, GFP_NOWAIT);
	zawwoc_cpumask_vaw(&tmpmask, GFP_NOWAIT);
#ifdef CONFIG_TICK_ONESHOT
	zawwoc_cpumask_vaw(&tick_bwoadcast_oneshot_mask, GFP_NOWAIT);
	zawwoc_cpumask_vaw(&tick_bwoadcast_pending_mask, GFP_NOWAIT);
	zawwoc_cpumask_vaw(&tick_bwoadcast_fowce_mask, GFP_NOWAIT);
#endif
}
