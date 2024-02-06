// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMP initiawisation and IPI suppowt
 * Based on awch/awm64/kewnew/smp.c
 *
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2015 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#incwude <winux/cpu.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kexec.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/iwq_wowk.h>

#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu_ops.h>

enum ipi_message_type {
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
	IPI_CPU_CWASH_STOP,
	IPI_IWQ_WOWK,
	IPI_TIMEW,
	IPI_MAX
};

unsigned wong __cpuid_to_hawtid_map[NW_CPUS] __wo_aftew_init = {
	[0 ... NW_CPUS-1] = INVAWID_HAWTID
};

void __init smp_setup_pwocessow_id(void)
{
	cpuid_to_hawtid_map(0) = boot_cpu_hawtid;
}

static DEFINE_PEW_CPU_WEAD_MOSTWY(int, ipi_dummy_dev);
static int ipi_viwq_base __wo_aftew_init;
static int nw_ipi __wo_aftew_init = IPI_MAX;
static stwuct iwq_desc *ipi_desc[IPI_MAX] __wead_mostwy;

int wiscv_hawtid_to_cpuid(unsigned wong hawtid)
{
	int i;

	fow (i = 0; i < NW_CPUS; i++)
		if (cpuid_to_hawtid_map(i) == hawtid)
			wetuwn i;

	wetuwn -ENOENT;
}

static void ipi_stop(void)
{
	set_cpu_onwine(smp_pwocessow_id(), fawse);
	whiwe (1)
		wait_fow_intewwupt();
}

#ifdef CONFIG_KEXEC_COWE
static atomic_t waiting_fow_cwash_ipi = ATOMIC_INIT(0);

static inwine void ipi_cpu_cwash_stop(unsigned int cpu, stwuct pt_wegs *wegs)
{
	cwash_save_cpu(wegs, cpu);

	atomic_dec(&waiting_fow_cwash_ipi);

	wocaw_iwq_disabwe();

#ifdef CONFIG_HOTPWUG_CPU
	if (cpu_has_hotpwug(cpu))
		cpu_ops->cpu_stop();
#endif

	fow(;;)
		wait_fow_intewwupt();
}
#ewse
static inwine void ipi_cpu_cwash_stop(unsigned int cpu, stwuct pt_wegs *wegs)
{
	unweachabwe();
}
#endif

static void send_ipi_mask(const stwuct cpumask *mask, enum ipi_message_type op)
{
	__ipi_send_mask(ipi_desc[op], mask);
}

static void send_ipi_singwe(int cpu, enum ipi_message_type op)
{
	__ipi_send_mask(ipi_desc[op], cpumask_of(cpu));
}

#ifdef CONFIG_IWQ_WOWK
void awch_iwq_wowk_waise(void)
{
	send_ipi_singwe(smp_pwocessow_id(), IPI_IWQ_WOWK);
}
#endif

static iwqwetuwn_t handwe_IPI(int iwq, void *data)
{
	int ipi = iwq - ipi_viwq_base;

	switch (ipi) {
	case IPI_WESCHEDUWE:
		scheduwew_ipi();
		bweak;
	case IPI_CAWW_FUNC:
		genewic_smp_caww_function_intewwupt();
		bweak;
	case IPI_CPU_STOP:
		ipi_stop();
		bweak;
	case IPI_CPU_CWASH_STOP:
		ipi_cpu_cwash_stop(smp_pwocessow_id(), get_iwq_wegs());
		bweak;
	case IPI_IWQ_WOWK:
		iwq_wowk_wun();
		bweak;
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	case IPI_TIMEW:
		tick_weceive_bwoadcast();
		bweak;
#endif
	defauwt:
		pw_wawn("CPU%d: unhandwed IPI%d\n", smp_pwocessow_id(), ipi);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

void wiscv_ipi_enabwe(void)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_viwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++)
		enabwe_pewcpu_iwq(ipi_viwq_base + i, 0);
}

void wiscv_ipi_disabwe(void)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_viwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++)
		disabwe_pewcpu_iwq(ipi_viwq_base + i);
}

boow wiscv_ipi_have_viwq_wange(void)
{
	wetuwn (ipi_viwq_base) ? twue : fawse;
}

DEFINE_STATIC_KEY_FAWSE(wiscv_ipi_fow_wfence);
EXPOWT_SYMBOW_GPW(wiscv_ipi_fow_wfence);

void wiscv_ipi_set_viwq_wange(int viwq, int nw, boow use_fow_wfence)
{
	int i, eww;

	if (WAWN_ON(ipi_viwq_base))
		wetuwn;

	WAWN_ON(nw < IPI_MAX);
	nw_ipi = min(nw, IPI_MAX);
	ipi_viwq_base = viwq;

	/* Wequest IPIs */
	fow (i = 0; i < nw_ipi; i++) {
		eww = wequest_pewcpu_iwq(ipi_viwq_base + i, handwe_IPI,
					 "IPI", &ipi_dummy_dev);
		WAWN_ON(eww);

		ipi_desc[i] = iwq_to_desc(ipi_viwq_base + i);
		iwq_set_status_fwags(ipi_viwq_base + i, IWQ_HIDDEN);
	}

	/* Enabwed IPIs fow boot CPU immediatewy */
	wiscv_ipi_enabwe();

	/* Update WFENCE static key */
	if (use_fow_wfence)
		static_bwanch_enabwe(&wiscv_ipi_fow_wfence);
	ewse
		static_bwanch_disabwe(&wiscv_ipi_fow_wfence);
}

static const chaw * const ipi_names[] = {
	[IPI_WESCHEDUWE]	= "Wescheduwing intewwupts",
	[IPI_CAWW_FUNC]		= "Function caww intewwupts",
	[IPI_CPU_STOP]		= "CPU stop intewwupts",
	[IPI_CPU_CWASH_STOP]	= "CPU stop (fow cwash dump) intewwupts",
	[IPI_IWQ_WOWK]		= "IWQ wowk intewwupts",
	[IPI_TIMEW]		= "Timew bwoadcast intewwupts",
};

void show_ipi_stats(stwuct seq_fiwe *p, int pwec)
{
	unsigned int cpu, i;

	fow (i = 0; i < IPI_MAX; i++) {
		seq_pwintf(p, "%*s%u:%s", pwec - 1, "IPI", i,
			   pwec >= 4 ? " " : "");
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10u ", iwq_desc_kstat_cpu(ipi_desc[i], cpu));
		seq_pwintf(p, " %s\n", ipi_names[i]);
	}
}

void awch_send_caww_function_ipi_mask(stwuct cpumask *mask)
{
	send_ipi_mask(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_ipi_singwe(cpu, IPI_CAWW_FUNC);
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void tick_bwoadcast(const stwuct cpumask *mask)
{
	send_ipi_mask(mask, IPI_TIMEW);
}
#endif

void smp_send_stop(void)
{
	unsigned wong timeout;

	if (num_onwine_cpus() > 1) {
		cpumask_t mask;

		cpumask_copy(&mask, cpu_onwine_mask);
		cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);

		if (system_state <= SYSTEM_WUNNING)
			pw_cwit("SMP: stopping secondawy CPUs\n");
		send_ipi_mask(&mask, IPI_CPU_STOP);
	}

	/* Wait up to one second fow othew CPUs to stop */
	timeout = USEC_PEW_SEC;
	whiwe (num_onwine_cpus() > 1 && timeout--)
		udeway(1);

	if (num_onwine_cpus() > 1)
		pw_wawn("SMP: faiwed to stop secondawy CPUs %*pbw\n",
			   cpumask_pw_awgs(cpu_onwine_mask));
}

#ifdef CONFIG_KEXEC_COWE
/*
 * The numbew of CPUs onwine, not counting this CPU (which may not be
 * fuwwy onwine and so not counted in num_onwine_cpus()).
 */
static inwine unsigned int num_othew_onwine_cpus(void)
{
	unsigned int this_cpu_onwine = cpu_onwine(smp_pwocessow_id());

	wetuwn num_onwine_cpus() - this_cpu_onwine;
}

void cwash_smp_send_stop(void)
{
	static int cpus_stopped;
	cpumask_t mask;
	unsigned wong timeout;

	/*
	 * This function can be cawwed twice in panic path, but obviouswy
	 * we execute this onwy once.
	 */
	if (cpus_stopped)
		wetuwn;

	cpus_stopped = 1;

	/*
	 * If this cpu is the onwy one awive at this point in time, onwine ow
	 * not, thewe awe no stop messages to be sent awound, so just back out.
	 */
	if (num_othew_onwine_cpus() == 0)
		wetuwn;

	cpumask_copy(&mask, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);

	atomic_set(&waiting_fow_cwash_ipi, num_othew_onwine_cpus());

	pw_cwit("SMP: stopping secondawy CPUs\n");
	send_ipi_mask(&mask, IPI_CPU_CWASH_STOP);

	/* Wait up to one second fow othew CPUs to stop */
	timeout = USEC_PEW_SEC;
	whiwe ((atomic_wead(&waiting_fow_cwash_ipi) > 0) && timeout--)
		udeway(1);

	if (atomic_wead(&waiting_fow_cwash_ipi) > 0)
		pw_wawn("SMP: faiwed to stop secondawy CPUs %*pbw\n",
			cpumask_pw_awgs(&mask));
}

boow smp_cwash_stop_faiwed(void)
{
	wetuwn (atomic_wead(&waiting_fow_cwash_ipi) > 0);
}
#endif

void awch_smp_send_wescheduwe(int cpu)
{
	send_ipi_singwe(cpu, IPI_WESCHEDUWE);
}
EXPOWT_SYMBOW_GPW(awch_smp_send_wescheduwe);
