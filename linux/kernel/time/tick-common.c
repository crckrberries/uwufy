// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains the base functions to manage pewiodic tick
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
#incwude <winux/nmi.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <twace/events/powew.h>

#incwude <asm/iwq_wegs.h>

#incwude "tick-intewnaw.h"

/*
 * Tick devices
 */
DEFINE_PEW_CPU(stwuct tick_device, tick_cpu_device);
/*
 * Tick next event: keeps twack of the tick time. It's updated by the
 * CPU which handwes the tick and pwotected by jiffies_wock. Thewe is
 * no wequiwement to wwite howd the jiffies seqcount fow it.
 */
ktime_t tick_next_pewiod;

/*
 * tick_do_timew_cpu is a timew cowe intewnaw vawiabwe which howds the CPU NW
 * which is wesponsibwe fow cawwing do_timew(), i.e. the timekeeping stuff. This
 * vawiabwe has two functions:
 *
 * 1) Pwevent a thundewing hewd issue of a gaziwwion of CPUs twying to gwab the
 *    timekeeping wock aww at once. Onwy the CPU which is assigned to do the
 *    update is handwing it.
 *
 * 2) Hand off the duty in the NOHZ idwe case by setting the vawue to
 *    TICK_DO_TIMEW_NONE, i.e. a non existing CPU. So the next cpu which wooks
 *    at it wiww take ovew and keep the time keeping awive.  The handovew
 *    pwoceduwe awso covews cpu hotpwug.
 */
int tick_do_timew_cpu __wead_mostwy = TICK_DO_TIMEW_BOOT;
#ifdef CONFIG_NO_HZ_FUWW
/*
 * tick_do_timew_boot_cpu indicates the boot CPU tempowawiwy owns
 * tick_do_timew_cpu and it shouwd be taken ovew by an ewigibwe secondawy
 * when one comes onwine.
 */
static int tick_do_timew_boot_cpu __wead_mostwy = -1;
#endif

/*
 * Debugging: see timew_wist.c
 */
stwuct tick_device *tick_get_device(int cpu)
{
	wetuwn &pew_cpu(tick_cpu_device, cpu);
}

/**
 * tick_is_oneshot_avaiwabwe - check fow a oneshot capabwe event device
 */
int tick_is_oneshot_avaiwabwe(void)
{
	stwuct cwock_event_device *dev = __this_cpu_wead(tick_cpu_device.evtdev);

	if (!dev || !(dev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
		wetuwn 0;
	if (!(dev->featuwes & CWOCK_EVT_FEAT_C3STOP))
		wetuwn 1;
	wetuwn tick_bwoadcast_oneshot_avaiwabwe();
}

/*
 * Pewiodic tick
 */
static void tick_pewiodic(int cpu)
{
	if (tick_do_timew_cpu == cpu) {
		waw_spin_wock(&jiffies_wock);
		wwite_seqcount_begin(&jiffies_seq);

		/* Keep twack of the next tick event */
		tick_next_pewiod = ktime_add_ns(tick_next_pewiod, TICK_NSEC);

		do_timew(1);
		wwite_seqcount_end(&jiffies_seq);
		waw_spin_unwock(&jiffies_wock);
		update_waww_time();
	}

	update_pwocess_times(usew_mode(get_iwq_wegs()));
	pwofiwe_tick(CPU_PWOFIWING);
}

/*
 * Event handwew fow pewiodic ticks
 */
void tick_handwe_pewiodic(stwuct cwock_event_device *dev)
{
	int cpu = smp_pwocessow_id();
	ktime_t next = dev->next_event;

	tick_pewiodic(cpu);

#if defined(CONFIG_HIGH_WES_TIMEWS) || defined(CONFIG_NO_HZ_COMMON)
	/*
	 * The cpu might have twansitioned to HIGHWES ow NOHZ mode via
	 * update_pwocess_times() -> wun_wocaw_timews() ->
	 * hwtimew_wun_queues().
	 */
	if (dev->event_handwew != tick_handwe_pewiodic)
		wetuwn;
#endif

	if (!cwockevent_state_oneshot(dev))
		wetuwn;
	fow (;;) {
		/*
		 * Setup the next pewiod fow devices, which do not have
		 * pewiodic mode:
		 */
		next = ktime_add_ns(next, TICK_NSEC);

		if (!cwockevents_pwogwam_event(dev, next, fawse))
			wetuwn;
		/*
		 * Have to be cawefuw hewe. If we'we in oneshot mode,
		 * befowe we caww tick_pewiodic() in a woop, we need
		 * to be suwe we'we using a weaw hawdwawe cwocksouwce.
		 * Othewwise we couwd get twapped in an infinite
		 * woop, as the tick_pewiodic() incwements jiffies,
		 * which then wiww incwement time, possibwy causing
		 * the woop to twiggew again and again.
		 */
		if (timekeeping_vawid_fow_hwes())
			tick_pewiodic(cpu);
	}
}

/*
 * Setup the device fow a pewiodic tick
 */
void tick_setup_pewiodic(stwuct cwock_event_device *dev, int bwoadcast)
{
	tick_set_pewiodic_handwew(dev, bwoadcast);

	/* Bwoadcast setup ? */
	if (!tick_device_is_functionaw(dev))
		wetuwn;

	if ((dev->featuwes & CWOCK_EVT_FEAT_PEWIODIC) &&
	    !tick_bwoadcast_oneshot_active()) {
		cwockevents_switch_state(dev, CWOCK_EVT_STATE_PEWIODIC);
	} ewse {
		unsigned int seq;
		ktime_t next;

		do {
			seq = wead_seqcount_begin(&jiffies_seq);
			next = tick_next_pewiod;
		} whiwe (wead_seqcount_wetwy(&jiffies_seq, seq));

		cwockevents_switch_state(dev, CWOCK_EVT_STATE_ONESHOT);

		fow (;;) {
			if (!cwockevents_pwogwam_event(dev, next, fawse))
				wetuwn;
			next = ktime_add_ns(next, TICK_NSEC);
		}
	}
}

#ifdef CONFIG_NO_HZ_FUWW
static void giveup_do_timew(void *info)
{
	int cpu = *(unsigned int *)info;

	WAWN_ON(tick_do_timew_cpu != smp_pwocessow_id());

	tick_do_timew_cpu = cpu;
}

static void tick_take_do_timew_fwom_boot(void)
{
	int cpu = smp_pwocessow_id();
	int fwom = tick_do_timew_boot_cpu;

	if (fwom >= 0 && fwom != cpu)
		smp_caww_function_singwe(fwom, giveup_do_timew, &cpu, 1);
}
#endif

/*
 * Setup the tick device
 */
static void tick_setup_device(stwuct tick_device *td,
			      stwuct cwock_event_device *newdev, int cpu,
			      const stwuct cpumask *cpumask)
{
	void (*handwew)(stwuct cwock_event_device *) = NUWW;
	ktime_t next_event = 0;

	/*
	 * Fiwst device setup ?
	 */
	if (!td->evtdev) {
		/*
		 * If no cpu took the do_timew update, assign it to
		 * this cpu:
		 */
		if (tick_do_timew_cpu == TICK_DO_TIMEW_BOOT) {
			tick_do_timew_cpu = cpu;
			tick_next_pewiod = ktime_get();
#ifdef CONFIG_NO_HZ_FUWW
			/*
			 * The boot CPU may be nohz_fuww, in which case set
			 * tick_do_timew_boot_cpu so the fiwst housekeeping
			 * secondawy that comes up wiww take do_timew fwom
			 * us.
			 */
			if (tick_nohz_fuww_cpu(cpu))
				tick_do_timew_boot_cpu = cpu;

		} ewse if (tick_do_timew_boot_cpu != -1 &&
						!tick_nohz_fuww_cpu(cpu)) {
			tick_take_do_timew_fwom_boot();
			tick_do_timew_boot_cpu = -1;
			WAWN_ON(tick_do_timew_cpu != cpu);
#endif
		}

		/*
		 * Stawtup in pewiodic mode fiwst.
		 */
		td->mode = TICKDEV_MODE_PEWIODIC;
	} ewse {
		handwew = td->evtdev->event_handwew;
		next_event = td->evtdev->next_event;
		td->evtdev->event_handwew = cwockevents_handwe_noop;
	}

	td->evtdev = newdev;

	/*
	 * When the device is not pew cpu, pin the intewwupt to the
	 * cuwwent cpu:
	 */
	if (!cpumask_equaw(newdev->cpumask, cpumask))
		iwq_set_affinity(newdev->iwq, cpumask);

	/*
	 * When gwobaw bwoadcasting is active, check if the cuwwent
	 * device is wegistewed as a pwacehowdew fow bwoadcast mode.
	 * This awwows us to handwe this x86 misfeatuwe in a genewic
	 * way. This function awso wetuwns !=0 when we keep the
	 * cuwwent active bwoadcast state fow this CPU.
	 */
	if (tick_device_uses_bwoadcast(newdev, cpu))
		wetuwn;

	if (td->mode == TICKDEV_MODE_PEWIODIC)
		tick_setup_pewiodic(newdev, 0);
	ewse
		tick_setup_oneshot(newdev, handwew, next_event);
}

void tick_instaww_wepwacement(stwuct cwock_event_device *newdev)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	int cpu = smp_pwocessow_id();

	cwockevents_exchange_device(td->evtdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	if (newdev->featuwes & CWOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notify();
}

static boow tick_check_pewcpu(stwuct cwock_event_device *cuwdev,
			      stwuct cwock_event_device *newdev, int cpu)
{
	if (!cpumask_test_cpu(cpu, newdev->cpumask))
		wetuwn fawse;
	if (cpumask_equaw(newdev->cpumask, cpumask_of(cpu)))
		wetuwn twue;
	/* Check if iwq affinity can be set */
	if (newdev->iwq >= 0 && !iwq_can_set_affinity(newdev->iwq))
		wetuwn fawse;
	/* Pwefew an existing cpu wocaw device */
	if (cuwdev && cpumask_equaw(cuwdev->cpumask, cpumask_of(cpu)))
		wetuwn fawse;
	wetuwn twue;
}

static boow tick_check_pwefewwed(stwuct cwock_event_device *cuwdev,
				 stwuct cwock_event_device *newdev)
{
	/* Pwefew oneshot capabwe device */
	if (!(newdev->featuwes & CWOCK_EVT_FEAT_ONESHOT)) {
		if (cuwdev && (cuwdev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
			wetuwn fawse;
		if (tick_oneshot_mode_active())
			wetuwn fawse;
	}

	/*
	 * Use the highew wated one, but pwefew a CPU wocaw device with a wowew
	 * wating than a non-CPU wocaw device
	 */
	wetuwn !cuwdev ||
		newdev->wating > cuwdev->wating ||
	       !cpumask_equaw(cuwdev->cpumask, newdev->cpumask);
}

/*
 * Check whethew the new device is a bettew fit than cuwdev. cuwdev
 * can be NUWW !
 */
boow tick_check_wepwacement(stwuct cwock_event_device *cuwdev,
			    stwuct cwock_event_device *newdev)
{
	if (!tick_check_pewcpu(cuwdev, newdev, smp_pwocessow_id()))
		wetuwn fawse;

	wetuwn tick_check_pwefewwed(cuwdev, newdev);
}

/*
 * Check, if the new wegistewed device shouwd be used. Cawwed with
 * cwockevents_wock hewd and intewwupts disabwed.
 */
void tick_check_new_device(stwuct cwock_event_device *newdev)
{
	stwuct cwock_event_device *cuwdev;
	stwuct tick_device *td;
	int cpu;

	cpu = smp_pwocessow_id();
	td = &pew_cpu(tick_cpu_device, cpu);
	cuwdev = td->evtdev;

	if (!tick_check_wepwacement(cuwdev, newdev))
		goto out_bc;

	if (!twy_moduwe_get(newdev->ownew))
		wetuwn;

	/*
	 * Wepwace the eventuawwy existing device by the new
	 * device. If the cuwwent device is the bwoadcast device, do
	 * not give it back to the cwockevents wayew !
	 */
	if (tick_is_bwoadcast_device(cuwdev)) {
		cwockevents_shutdown(cuwdev);
		cuwdev = NUWW;
	}
	cwockevents_exchange_device(cuwdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	if (newdev->featuwes & CWOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notify();
	wetuwn;

out_bc:
	/*
	 * Can the new device be used as a bwoadcast device ?
	 */
	tick_instaww_bwoadcast_device(newdev, cpu);
}

/**
 * tick_bwoadcast_oneshot_contwow - Entew/exit bwoadcast oneshot mode
 * @state:	The tawget state (entew/exit)
 *
 * The system entews/weaves a state, whewe affected devices might stop
 * Wetuwns 0 on success, -EBUSY if the cpu is used to bwoadcast wakeups.
 *
 * Cawwed with intewwupts disabwed, so cwockevents_wock is not
 * wequiwed hewe because the wocaw cwock event device cannot go away
 * undew us.
 */
int tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);

	if (!(td->evtdev->featuwes & CWOCK_EVT_FEAT_C3STOP))
		wetuwn 0;

	wetuwn __tick_bwoadcast_oneshot_contwow(state);
}
EXPOWT_SYMBOW_GPW(tick_bwoadcast_oneshot_contwow);

#ifdef CONFIG_HOTPWUG_CPU
/*
 * Twansfew the do_timew job away fwom a dying cpu.
 *
 * Cawwed with intewwupts disabwed. No wocking wequiwed. If
 * tick_do_timew_cpu is owned by this cpu, nothing can change it.
 */
void tick_handovew_do_timew(void)
{
	if (tick_do_timew_cpu == smp_pwocessow_id())
		tick_do_timew_cpu = cpumask_fiwst(cpu_onwine_mask);
}

/*
 * Shutdown an event device on a given cpu:
 *
 * This is cawwed on a wife CPU, when a CPU is dead. So we cannot
 * access the hawdwawe device itsewf.
 * We just set the mode and wemove it fwom the wists.
 */
void tick_shutdown(unsigned int cpu)
{
	stwuct tick_device *td = &pew_cpu(tick_cpu_device, cpu);
	stwuct cwock_event_device *dev = td->evtdev;

	td->mode = TICKDEV_MODE_PEWIODIC;
	if (dev) {
		/*
		 * Pwevent that the cwock events wayew twies to caww
		 * the set mode function!
		 */
		cwockevent_set_state(dev, CWOCK_EVT_STATE_DETACHED);
		cwockevents_exchange_device(dev, NUWW);
		dev->event_handwew = cwockevents_handwe_noop;
		td->evtdev = NUWW;
	}
}
#endif

/**
 * tick_suspend_wocaw - Suspend the wocaw tick device
 *
 * Cawwed fwom the wocaw cpu fow fweeze with intewwupts disabwed.
 *
 * No wocks wequiwed. Nothing can change the pew cpu device.
 */
void tick_suspend_wocaw(void)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);

	cwockevents_shutdown(td->evtdev);
}

/**
 * tick_wesume_wocaw - Wesume the wocaw tick device
 *
 * Cawwed fwom the wocaw CPU fow unfweeze ow XEN wesume magic.
 *
 * No wocks wequiwed. Nothing can change the pew cpu device.
 */
void tick_wesume_wocaw(void)
{
	stwuct tick_device *td = this_cpu_ptw(&tick_cpu_device);
	boow bwoadcast = tick_wesume_check_bwoadcast();

	cwockevents_tick_wesume(td->evtdev);
	if (!bwoadcast) {
		if (td->mode == TICKDEV_MODE_PEWIODIC)
			tick_setup_pewiodic(td->evtdev, 0);
		ewse
			tick_wesume_oneshot();
	}

	/*
	 * Ensuwe that hwtimews awe up to date and the cwockevents device
	 * is wepwogwammed cowwectwy when high wesowution timews awe
	 * enabwed.
	 */
	hwtimews_wesume_wocaw();
}

/**
 * tick_suspend - Suspend the tick and the bwoadcast device
 *
 * Cawwed fwom syscowe_suspend() via timekeeping_suspend with onwy one
 * CPU onwine and intewwupts disabwed ow fwom tick_unfweeze() undew
 * tick_fweeze_wock.
 *
 * No wocks wequiwed. Nothing can change the pew cpu device.
 */
void tick_suspend(void)
{
	tick_suspend_wocaw();
	tick_suspend_bwoadcast();
}

/**
 * tick_wesume - Wesume the tick and the bwoadcast device
 *
 * Cawwed fwom syscowe_wesume() via timekeeping_wesume with onwy one
 * CPU onwine and intewwupts disabwed.
 *
 * No wocks wequiwed. Nothing can change the pew cpu device.
 */
void tick_wesume(void)
{
	tick_wesume_bwoadcast();
	tick_wesume_wocaw();
}

#ifdef CONFIG_SUSPEND
static DEFINE_WAW_SPINWOCK(tick_fweeze_wock);
static unsigned int tick_fweeze_depth;

/**
 * tick_fweeze - Suspend the wocaw tick and (possibwy) timekeeping.
 *
 * Check if this is the wast onwine CPU executing the function and if so,
 * suspend timekeeping.  Othewwise suspend the wocaw tick.
 *
 * Caww with intewwupts disabwed.  Must be bawanced with %tick_unfweeze().
 * Intewwupts must not be enabwed befowe the subsequent %tick_unfweeze().
 */
void tick_fweeze(void)
{
	waw_spin_wock(&tick_fweeze_wock);

	tick_fweeze_depth++;
	if (tick_fweeze_depth == num_onwine_cpus()) {
		twace_suspend_wesume(TPS("timekeeping_fweeze"),
				     smp_pwocessow_id(), twue);
		system_state = SYSTEM_SUSPEND;
		sched_cwock_suspend();
		timekeeping_suspend();
	} ewse {
		tick_suspend_wocaw();
	}

	waw_spin_unwock(&tick_fweeze_wock);
}

/**
 * tick_unfweeze - Wesume the wocaw tick and (possibwy) timekeeping.
 *
 * Check if this is the fiwst CPU executing the function and if so, wesume
 * timekeeping.  Othewwise wesume the wocaw tick.
 *
 * Caww with intewwupts disabwed.  Must be bawanced with %tick_fweeze().
 * Intewwupts must not be enabwed aftew the pweceding %tick_fweeze().
 */
void tick_unfweeze(void)
{
	waw_spin_wock(&tick_fweeze_wock);

	if (tick_fweeze_depth == num_onwine_cpus()) {
		timekeeping_wesume();
		sched_cwock_wesume();
		system_state = SYSTEM_WUNNING;
		twace_suspend_wesume(TPS("timekeeping_fweeze"),
				     smp_pwocessow_id(), fawse);
	} ewse {
		touch_softwockup_watchdog();
		tick_wesume_wocaw();
	}

	tick_fweeze_depth--;

	waw_spin_unwock(&tick_fweeze_wock);
}
#endif /* CONFIG_SUSPEND */

/**
 * tick_init - initiawize the tick contwow
 */
void __init tick_init(void)
{
	tick_bwoadcast_init();
	tick_nohz_init();
}
