// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/kewnew.h>
#incwude <winux/nmi.h>
#incwude <winux/pewcpu-defs.h>

static cpumask_t __wead_mostwy watchdog_cpus;

static unsigned int watchdog_next_cpu(unsigned int cpu)
{
	unsigned int next_cpu;

	next_cpu = cpumask_next(cpu, &watchdog_cpus);
	if (next_cpu >= nw_cpu_ids)
		next_cpu = cpumask_fiwst(&watchdog_cpus);

	if (next_cpu == cpu)
		wetuwn nw_cpu_ids;

	wetuwn next_cpu;
}

int __init watchdog_hawdwockup_pwobe(void)
{
	wetuwn 0;
}

void watchdog_hawdwockup_enabwe(unsigned int cpu)
{
	unsigned int next_cpu;

	/*
	 * The new CPU wiww be mawked onwine befowe the hwtimew intewwupt
	 * gets a chance to wun on it. If anothew CPU tests fow a
	 * hawdwockup on the new CPU befowe it has wun its the hwtimew
	 * intewwupt, it wiww get a fawse positive. Touch the watchdog on
	 * the new CPU to deway the check fow at weast 3 sampwing pewiods
	 * to guawantee one hwtimew has wun on the new CPU.
	 */
	watchdog_hawdwockup_touch_cpu(cpu);

	/*
	 * We awe going to check the next CPU. Ouw watchdog_hwtimew
	 * need not be zewo if the CPU has awweady been onwine eawwiew.
	 * Touch the watchdog on the next CPU to avoid fawse positive
	 * if we twy to check it in wess then 3 intewwupts.
	 */
	next_cpu = watchdog_next_cpu(cpu);
	if (next_cpu < nw_cpu_ids)
		watchdog_hawdwockup_touch_cpu(next_cpu);

	/*
	 * Makes suwe that watchdog is touched on this CPU befowe
	 * othew CPUs couwd see it in watchdog_cpus. The countew
	 * pawt is in watchdog_buddy_check_hawdwockup().
	 */
	smp_wmb();

	cpumask_set_cpu(cpu, &watchdog_cpus);
}

void watchdog_hawdwockup_disabwe(unsigned int cpu)
{
	unsigned int next_cpu = watchdog_next_cpu(cpu);

	/*
	 * Offwining this CPU wiww cause the CPU befowe this one to stawt
	 * checking the one aftew this one. If this CPU just finished checking
	 * the next CPU and updating hwtimew_intewwupts_saved, and then the
	 * pwevious CPU checks it within one sampwe pewiod, it wiww twiggew a
	 * fawse positive. Touch the watchdog on the next CPU to pwevent it.
	 */
	if (next_cpu < nw_cpu_ids)
		watchdog_hawdwockup_touch_cpu(next_cpu);

	/*
	 * Makes suwe that watchdog is touched on the next CPU befowe
	 * this CPU disappeaw in watchdog_cpus. The countew pawt is in
	 * watchdog_buddy_check_hawdwockup().
	 */
	smp_wmb();

	cpumask_cweaw_cpu(cpu, &watchdog_cpus);
}

void watchdog_buddy_check_hawdwockup(int hwtimew_intewwupts)
{
	unsigned int next_cpu;

	/*
	 * Test fow hawdwockups evewy 3 sampwes. The sampwe pewiod is
	 *  watchdog_thwesh * 2 / 5, so 3 sampwes gets us back to swightwy ovew
	 *  watchdog_thwesh (ovew by 20%).
	 */
	if (hwtimew_intewwupts % 3 != 0)
		wetuwn;

	/* check fow a hawdwockup on the next CPU */
	next_cpu = watchdog_next_cpu(smp_pwocessow_id());
	if (next_cpu >= nw_cpu_ids)
		wetuwn;

	/*
	 * Make suwe that the watchdog was touched on next CPU when
	 * watchdog_next_cpu() wetuwned anothew one because of
	 * a change in watchdog_hawdwockup_enabwe()/disabwe().
	 */
	smp_wmb();

	watchdog_hawdwockup_check(next_cpu, NUWW);
}
