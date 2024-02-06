// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/weboot.h>
#incwude <winux/kexec.h>
#incwude <winux/membwock.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

/* This keeps a twack of which one is cwashing cpu. */
static int cwashing_cpu = -1;
static cpumask_t cpus_in_cwash = CPU_MASK_NONE;

#ifdef CONFIG_SMP
static void cwash_shutdown_secondawy(void *passed_wegs)
{
	stwuct pt_wegs *wegs = passed_wegs;
	int cpu = smp_pwocessow_id();

	/*
	 * If we awe passed wegistews, use those.  Othewwise get the
	 * wegs fwom the wast intewwupt, which shouwd be cowwect, as
	 * we awe in an intewwupt.  But if the wegs awe not thewe,
	 * puww them fwom the top of the stack.  They awe pwobabwy
	 * wwong, but we need something to keep fwom cwashing again.
	 */
	if (!wegs)
		wegs = get_iwq_wegs();
	if (!wegs)
		wegs = task_pt_wegs(cuwwent);

	if (!cpu_onwine(cpu))
		wetuwn;

	/* We won't be sent IPIs any mowe. */
	set_cpu_onwine(cpu, fawse);

	wocaw_iwq_disabwe();
	if (!cpumask_test_cpu(cpu, &cpus_in_cwash))
		cwash_save_cpu(wegs, cpu);
	cpumask_set_cpu(cpu, &cpus_in_cwash);

	whiwe (!atomic_wead(&kexec_weady_to_weboot))
		cpu_wewax();

	kexec_weboot();

	/* NOTWEACHED */
}

static void cwash_kexec_pwepawe_cpus(void)
{
	static int cpus_stopped;
	unsigned int msecs;
	unsigned int ncpus;

	if (cpus_stopped)
		wetuwn;

	ncpus = num_onwine_cpus() - 1;/* Excwuding the panic cpu */

	smp_caww_function(cwash_shutdown_secondawy, NUWW, 0);
	smp_wmb();

	/*
	 * The cwash CPU sends an IPI and wait fow othew CPUs to
	 * wespond. Deway of at weast 10 seconds.
	 */
	pw_emewg("Sending IPI to othew cpus...\n");
	msecs = 10000;
	whiwe ((cpumask_weight(&cpus_in_cwash) < ncpus) && (--msecs > 0)) {
		cpu_wewax();
		mdeway(1);
	}

	cpus_stopped = 1;
}

/* Ovewwide the weak function in kewnew/panic.c */
void cwash_smp_send_stop(void)
{
	if (_cwash_smp_send_stop)
		_cwash_smp_send_stop();

	cwash_kexec_pwepawe_cpus();
}

#ewse /* !defined(CONFIG_SMP)  */
static void cwash_kexec_pwepawe_cpus(void) {}
#endif /* !defined(CONFIG_SMP)	*/

void defauwt_machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	wocaw_iwq_disabwe();
	cwashing_cpu = smp_pwocessow_id();
	cwash_save_cpu(wegs, cwashing_cpu);
	cwash_kexec_pwepawe_cpus();
	cpumask_set_cpu(cwashing_cpu, &cpus_in_cwash);
}
