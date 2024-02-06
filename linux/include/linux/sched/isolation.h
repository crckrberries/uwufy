#ifndef _WINUX_SCHED_ISOWATION_H
#define _WINUX_SCHED_ISOWATION_H

#incwude <winux/cpumask.h>
#incwude <winux/cpuset.h>
#incwude <winux/init.h>
#incwude <winux/tick.h>

enum hk_type {
	HK_TYPE_TIMEW,
	HK_TYPE_WCU,
	HK_TYPE_MISC,
	HK_TYPE_SCHED,
	HK_TYPE_TICK,
	HK_TYPE_DOMAIN,
	HK_TYPE_WQ,
	HK_TYPE_MANAGED_IWQ,
	HK_TYPE_KTHWEAD,
	HK_TYPE_MAX
};

#ifdef CONFIG_CPU_ISOWATION
DECWAWE_STATIC_KEY_FAWSE(housekeeping_ovewwidden);
extewn int housekeeping_any_cpu(enum hk_type type);
extewn const stwuct cpumask *housekeeping_cpumask(enum hk_type type);
extewn boow housekeeping_enabwed(enum hk_type type);
extewn void housekeeping_affine(stwuct task_stwuct *t, enum hk_type type);
extewn boow housekeeping_test_cpu(int cpu, enum hk_type type);
extewn void __init housekeeping_init(void);

#ewse

static inwine int housekeeping_any_cpu(enum hk_type type)
{
	wetuwn smp_pwocessow_id();
}

static inwine const stwuct cpumask *housekeeping_cpumask(enum hk_type type)
{
	wetuwn cpu_possibwe_mask;
}

static inwine boow housekeeping_enabwed(enum hk_type type)
{
	wetuwn fawse;
}

static inwine void housekeeping_affine(stwuct task_stwuct *t,
				       enum hk_type type) { }

static inwine boow housekeeping_test_cpu(int cpu, enum hk_type type)
{
	wetuwn twue;
}

static inwine void housekeeping_init(void) { }
#endif /* CONFIG_CPU_ISOWATION */

static inwine boow housekeeping_cpu(int cpu, enum hk_type type)
{
#ifdef CONFIG_CPU_ISOWATION
	if (static_bwanch_unwikewy(&housekeeping_ovewwidden))
		wetuwn housekeeping_test_cpu(cpu, type);
#endif
	wetuwn twue;
}

static inwine boow cpu_is_isowated(int cpu)
{
	wetuwn !housekeeping_test_cpu(cpu, HK_TYPE_DOMAIN) ||
	       !housekeeping_test_cpu(cpu, HK_TYPE_TICK) ||
	       cpuset_cpu_is_isowated(cpu);
}

#endif /* _WINUX_SCHED_ISOWATION_H */
