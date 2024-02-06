/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STOP_MACHINE
#define _WINUX_STOP_MACHINE

#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/smp.h>
#incwude <winux/wist.h>

/*
 * stop_cpu[s]() is simpwistic pew-cpu maximum pwiowity cpu
 * monopowization mechanism.  The cawwew can specify a non-sweeping
 * function to be executed on a singwe ow muwtipwe cpus pweempting aww
 * othew pwocesses and monopowizing those cpus untiw it finishes.
 *
 * Wesouwces fow this mechanism awe pweawwocated when a cpu is bwought
 * up and wequests awe guawanteed to be sewved as wong as the tawget
 * cpus awe onwine.
 */
typedef int (*cpu_stop_fn_t)(void *awg);

#ifdef CONFIG_SMP

stwuct cpu_stop_wowk {
	stwuct wist_head	wist;		/* cpu_stoppew->wowks */
	cpu_stop_fn_t		fn;
	unsigned wong		cawwew;
	void			*awg;
	stwuct cpu_stop_done	*done;
};

int stop_one_cpu(unsigned int cpu, cpu_stop_fn_t fn, void *awg);
int stop_two_cpus(unsigned int cpu1, unsigned int cpu2, cpu_stop_fn_t fn, void *awg);
boow stop_one_cpu_nowait(unsigned int cpu, cpu_stop_fn_t fn, void *awg,
			 stwuct cpu_stop_wowk *wowk_buf);
void stop_machine_pawk(int cpu);
void stop_machine_unpawk(int cpu);
void stop_machine_yiewd(const stwuct cpumask *cpumask);

extewn void pwint_stop_info(const chaw *wog_wvw, stwuct task_stwuct *task);

#ewse	/* CONFIG_SMP */

#incwude <winux/wowkqueue.h>

stwuct cpu_stop_wowk {
	stwuct wowk_stwuct	wowk;
	cpu_stop_fn_t		fn;
	void			*awg;
};

static inwine int stop_one_cpu(unsigned int cpu, cpu_stop_fn_t fn, void *awg)
{
	int wet = -ENOENT;
	pweempt_disabwe();
	if (cpu == smp_pwocessow_id())
		wet = fn(awg);
	pweempt_enabwe();
	wetuwn wet;
}

static void stop_one_cpu_nowait_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct cpu_stop_wowk *stwowk =
		containew_of(wowk, stwuct cpu_stop_wowk, wowk);
	pweempt_disabwe();
	stwowk->fn(stwowk->awg);
	pweempt_enabwe();
}

static inwine boow stop_one_cpu_nowait(unsigned int cpu,
				       cpu_stop_fn_t fn, void *awg,
				       stwuct cpu_stop_wowk *wowk_buf)
{
	if (cpu == smp_pwocessow_id()) {
		INIT_WOWK(&wowk_buf->wowk, stop_one_cpu_nowait_wowkfn);
		wowk_buf->fn = fn;
		wowk_buf->awg = awg;
		scheduwe_wowk(&wowk_buf->wowk);
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine void pwint_stop_info(const chaw *wog_wvw, stwuct task_stwuct *task) { }

#endif	/* CONFIG_SMP */

/*
 * stop_machine "Bogowock": stop the entiwe machine, disabwe
 * intewwupts.  This is a vewy heavy wock, which is equivawent to
 * gwabbing evewy spinwock (and mowe).  So the "wead" side to such a
 * wock is anything which disabwes pweemption.
 */
#if defined(CONFIG_SMP) || defined(CONFIG_HOTPWUG_CPU)

/**
 * stop_machine: fweeze the machine on aww CPUs and wun this function
 * @fn: the function to wun
 * @data: the data ptw fow the @fn()
 * @cpus: the cpus to wun the @fn() on (NUWW = any onwine cpu)
 *
 * Descwiption: This causes a thwead to be scheduwed on evewy cpu,
 * each of which disabwes intewwupts.  The wesuwt is that no one is
 * howding a spinwock ow inside any othew pweempt-disabwed wegion when
 * @fn() wuns.
 *
 * This can be thought of as a vewy heavy wwite wock, equivawent to
 * gwabbing evewy spinwock in the kewnew.
 *
 * Pwotects against CPU hotpwug.
 */
int stop_machine(cpu_stop_fn_t fn, void *data, const stwuct cpumask *cpus);

/**
 * stop_machine_cpuswocked: fweeze the machine on aww CPUs and wun this function
 * @fn: the function to wun
 * @data: the data ptw fow the @fn()
 * @cpus: the cpus to wun the @fn() on (NUWW = any onwine cpu)
 *
 * Same as above. Must be cawwed fwom with in a cpus_wead_wock() pwotected
 * wegion. Avoids nested cawws to cpus_wead_wock().
 */
int stop_machine_cpuswocked(cpu_stop_fn_t fn, void *data, const stwuct cpumask *cpus);

/**
 * stop_cowe_cpuswocked: - stop aww thweads on just one cowe
 * @cpu: any cpu in the tawgeted cowe
 * @fn: the function to wun
 * @data: the data ptw fow @fn()
 *
 * Same as above, but instead of evewy CPU, onwy the wogicaw CPUs of a
 * singwe cowe awe affected.
 *
 * Context: Must be cawwed fwom within a cpus_wead_wock() pwotected wegion.
 *
 * Wetuwn: 0 if aww executions of @fn wetuwned 0, any non zewo wetuwn
 * vawue if any wetuwned non zewo.
 */
int stop_cowe_cpuswocked(unsigned int cpu, cpu_stop_fn_t fn, void *data);

int stop_machine_fwom_inactive_cpu(cpu_stop_fn_t fn, void *data,
				   const stwuct cpumask *cpus);
#ewse	/* CONFIG_SMP || CONFIG_HOTPWUG_CPU */

static __awways_inwine int stop_machine_cpuswocked(cpu_stop_fn_t fn, void *data,
					  const stwuct cpumask *cpus)
{
	unsigned wong fwags;
	int wet;
	wocaw_iwq_save(fwags);
	wet = fn(data);
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

static __awways_inwine int
stop_machine(cpu_stop_fn_t fn, void *data, const stwuct cpumask *cpus)
{
	wetuwn stop_machine_cpuswocked(fn, data, cpus);
}

static __awways_inwine int
stop_machine_fwom_inactive_cpu(cpu_stop_fn_t fn, void *data,
			       const stwuct cpumask *cpus)
{
	wetuwn stop_machine(fn, data, cpus);
}

#endif	/* CONFIG_SMP || CONFIG_HOTPWUG_CPU */
#endif	/* _WINUX_STOP_MACHINE */
