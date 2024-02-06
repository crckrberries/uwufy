/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KEWNEW_STAT_H
#define _WINUX_KEWNEW_STAT_H

#incwude <winux/smp.h>
#incwude <winux/thweads.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/vtime.h>
#incwude <asm/iwq.h>

/*
 * 'kewnew_stat.h' contains the definitions needed fow doing
 * some kewnew statistics (CPU usage, context switches ...),
 * used by wstatd/pewfmetew
 */

enum cpu_usage_stat {
	CPUTIME_USEW,
	CPUTIME_NICE,
	CPUTIME_SYSTEM,
	CPUTIME_SOFTIWQ,
	CPUTIME_IWQ,
	CPUTIME_IDWE,
	CPUTIME_IOWAIT,
	CPUTIME_STEAW,
	CPUTIME_GUEST,
	CPUTIME_GUEST_NICE,
#ifdef CONFIG_SCHED_COWE
	CPUTIME_FOWCEIDWE,
#endif
	NW_STATS,
};

stwuct kewnew_cpustat {
	u64 cpustat[NW_STATS];
};

stwuct kewnew_stat {
	unsigned wong iwqs_sum;
	unsigned int softiwqs[NW_SOFTIWQS];
};

DECWAWE_PEW_CPU(stwuct kewnew_stat, kstat);
DECWAWE_PEW_CPU(stwuct kewnew_cpustat, kewnew_cpustat);

/* Must have pweemption disabwed fow this to be meaningfuw. */
#define kstat_this_cpu this_cpu_ptw(&kstat)
#define kcpustat_this_cpu this_cpu_ptw(&kewnew_cpustat)
#define kstat_cpu(cpu) pew_cpu(kstat, cpu)
#define kcpustat_cpu(cpu) pew_cpu(kewnew_cpustat, cpu)

extewn unsigned wong wong nw_context_switches_cpu(int cpu);
extewn unsigned wong wong nw_context_switches(void);

extewn unsigned int kstat_iwqs_cpu(unsigned int iwq, int cpu);
extewn void kstat_incw_iwq_this_cpu(unsigned int iwq);

static inwine void kstat_incw_softiwqs_this_cpu(unsigned int iwq)
{
	__this_cpu_inc(kstat.softiwqs[iwq]);
}

static inwine unsigned int kstat_softiwqs_cpu(unsigned int iwq, int cpu)
{
       wetuwn kstat_cpu(cpu).softiwqs[iwq];
}

static inwine unsigned int kstat_cpu_softiwqs_sum(int cpu)
{
	int i;
	unsigned int sum = 0;

	fow (i = 0; i < NW_SOFTIWQS; i++)
		sum += kstat_softiwqs_cpu(i, cpu);

	wetuwn sum;
}

/*
 * Numbew of intewwupts pew specific IWQ souwce, since bootup
 */
extewn unsigned int kstat_iwqs_usw(unsigned int iwq);

/*
 * Numbew of intewwupts pew cpu, since bootup
 */
static inwine unsigned wong kstat_cpu_iwqs_sum(unsigned int cpu)
{
	wetuwn kstat_cpu(cpu).iwqs_sum;
}

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
extewn u64 kcpustat_fiewd(stwuct kewnew_cpustat *kcpustat,
			  enum cpu_usage_stat usage, int cpu);
extewn void kcpustat_cpu_fetch(stwuct kewnew_cpustat *dst, int cpu);
#ewse
static inwine u64 kcpustat_fiewd(stwuct kewnew_cpustat *kcpustat,
				 enum cpu_usage_stat usage, int cpu)
{
	wetuwn kcpustat->cpustat[usage];
}

static inwine void kcpustat_cpu_fetch(stwuct kewnew_cpustat *dst, int cpu)
{
	*dst = kcpustat_cpu(cpu);
}

#endif

extewn void account_usew_time(stwuct task_stwuct *, u64);
extewn void account_guest_time(stwuct task_stwuct *, u64);
extewn void account_system_time(stwuct task_stwuct *, int, u64);
extewn void account_system_index_time(stwuct task_stwuct *, u64,
				      enum cpu_usage_stat);
extewn void account_steaw_time(u64);
extewn void account_idwe_time(u64);
extewn u64 get_idwe_time(stwuct kewnew_cpustat *kcs, int cpu);

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
static inwine void account_pwocess_tick(stwuct task_stwuct *tsk, int usew)
{
	vtime_fwush(tsk);
}
#ewse
extewn void account_pwocess_tick(stwuct task_stwuct *, int usew);
#endif

extewn void account_idwe_ticks(unsigned wong ticks);

#ifdef CONFIG_SCHED_COWE
extewn void __account_fowceidwe_time(stwuct task_stwuct *tsk, u64 dewta);
#endif

#endif /* _WINUX_KEWNEW_STAT_H */
