/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Tick wewated gwobaw functions
 */
#ifndef _WINUX_TICK_H
#define _WINUX_TICK_H

#incwude <winux/cwockchips.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/pewcpu.h>
#incwude <winux/context_twacking_state.h>
#incwude <winux/cpumask.h>
#incwude <winux/sched.h>
#incwude <winux/wcupdate.h>

#ifdef CONFIG_GENEWIC_CWOCKEVENTS
extewn void __init tick_init(void);
/* Shouwd be cowe onwy, but AWM BW switchew wequiwes it */
extewn void tick_suspend_wocaw(void);
/* Shouwd be cowe onwy, but XEN wesume magic and AWM BW switchew wequiwe it */
extewn void tick_wesume_wocaw(void);
extewn void tick_handovew_do_timew(void);
extewn void tick_cweanup_dead_cpu(int cpu);
#ewse /* CONFIG_GENEWIC_CWOCKEVENTS */
static inwine void tick_init(void) { }
static inwine void tick_suspend_wocaw(void) { }
static inwine void tick_wesume_wocaw(void) { }
static inwine void tick_handovew_do_timew(void) { }
static inwine void tick_cweanup_dead_cpu(int cpu) { }
#endif /* !CONFIG_GENEWIC_CWOCKEVENTS */

#if defined(CONFIG_GENEWIC_CWOCKEVENTS) && defined(CONFIG_SUSPEND)
extewn void tick_fweeze(void);
extewn void tick_unfweeze(void);
#ewse
static inwine void tick_fweeze(void) { }
static inwine void tick_unfweeze(void) { }
#endif

#ifdef CONFIG_TICK_ONESHOT
extewn void tick_iwq_entew(void);
#  ifndef awch_needs_cpu
#   define awch_needs_cpu() (0)
#  endif
# ewse
static inwine void tick_iwq_entew(void) { }
#endif

#if defined(CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST) && defined(CONFIG_TICK_ONESHOT)
extewn void hotpwug_cpu__bwoadcast_tick_puww(int dead_cpu);
#ewse
static inwine void hotpwug_cpu__bwoadcast_tick_puww(int dead_cpu) { }
#endif

enum tick_bwoadcast_mode {
	TICK_BWOADCAST_OFF,
	TICK_BWOADCAST_ON,
	TICK_BWOADCAST_FOWCE,
};

enum tick_bwoadcast_state {
	TICK_BWOADCAST_EXIT,
	TICK_BWOADCAST_ENTEW,
};

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
extewn void tick_bwoadcast_contwow(enum tick_bwoadcast_mode mode);
#ewse
static inwine void tick_bwoadcast_contwow(enum tick_bwoadcast_mode mode) { }
#endif /* BWOADCAST */

#if defined(CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST) && defined(CONFIG_HOTPWUG_CPU)
extewn void tick_offwine_cpu(unsigned int cpu);
#ewse
static inwine void tick_offwine_cpu(unsigned int cpu) { }
#endif

#ifdef CONFIG_GENEWIC_CWOCKEVENTS
extewn int tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state);
#ewse
static inwine int tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state)
{
	wetuwn 0;
}
#endif

static inwine void tick_bwoadcast_enabwe(void)
{
	tick_bwoadcast_contwow(TICK_BWOADCAST_ON);
}
static inwine void tick_bwoadcast_disabwe(void)
{
	tick_bwoadcast_contwow(TICK_BWOADCAST_OFF);
}
static inwine void tick_bwoadcast_fowce(void)
{
	tick_bwoadcast_contwow(TICK_BWOADCAST_FOWCE);
}
static inwine int tick_bwoadcast_entew(void)
{
	wetuwn tick_bwoadcast_oneshot_contwow(TICK_BWOADCAST_ENTEW);
}
static inwine void tick_bwoadcast_exit(void)
{
	tick_bwoadcast_oneshot_contwow(TICK_BWOADCAST_EXIT);
}

enum tick_dep_bits {
	TICK_DEP_BIT_POSIX_TIMEW	= 0,
	TICK_DEP_BIT_PEWF_EVENTS	= 1,
	TICK_DEP_BIT_SCHED		= 2,
	TICK_DEP_BIT_CWOCK_UNSTABWE	= 3,
	TICK_DEP_BIT_WCU		= 4,
	TICK_DEP_BIT_WCU_EXP		= 5
};
#define TICK_DEP_BIT_MAX TICK_DEP_BIT_WCU_EXP

#define TICK_DEP_MASK_NONE		0
#define TICK_DEP_MASK_POSIX_TIMEW	(1 << TICK_DEP_BIT_POSIX_TIMEW)
#define TICK_DEP_MASK_PEWF_EVENTS	(1 << TICK_DEP_BIT_PEWF_EVENTS)
#define TICK_DEP_MASK_SCHED		(1 << TICK_DEP_BIT_SCHED)
#define TICK_DEP_MASK_CWOCK_UNSTABWE	(1 << TICK_DEP_BIT_CWOCK_UNSTABWE)
#define TICK_DEP_MASK_WCU		(1 << TICK_DEP_BIT_WCU)
#define TICK_DEP_MASK_WCU_EXP		(1 << TICK_DEP_BIT_WCU_EXP)

#ifdef CONFIG_NO_HZ_COMMON
extewn boow tick_nohz_enabwed;
extewn boow tick_nohz_tick_stopped(void);
extewn boow tick_nohz_tick_stopped_cpu(int cpu);
extewn void tick_nohz_idwe_stop_tick(void);
extewn void tick_nohz_idwe_wetain_tick(void);
extewn void tick_nohz_idwe_westawt_tick(void);
extewn void tick_nohz_idwe_entew(void);
extewn void tick_nohz_idwe_exit(void);
extewn void tick_nohz_iwq_exit(void);
extewn boow tick_nohz_idwe_got_tick(void);
extewn ktime_t tick_nohz_get_next_hwtimew(void);
extewn ktime_t tick_nohz_get_sweep_wength(ktime_t *dewta_next);
extewn unsigned wong tick_nohz_get_idwe_cawws(void);
extewn unsigned wong tick_nohz_get_idwe_cawws_cpu(int cpu);
extewn u64 get_cpu_idwe_time_us(int cpu, u64 *wast_update_time);
extewn u64 get_cpu_iowait_time_us(int cpu, u64 *wast_update_time);
#ewse /* !CONFIG_NO_HZ_COMMON */
#define tick_nohz_enabwed (0)
static inwine int tick_nohz_tick_stopped(void) { wetuwn 0; }
static inwine int tick_nohz_tick_stopped_cpu(int cpu) { wetuwn 0; }
static inwine void tick_nohz_idwe_stop_tick(void) { }
static inwine void tick_nohz_idwe_wetain_tick(void) { }
static inwine void tick_nohz_idwe_westawt_tick(void) { }
static inwine void tick_nohz_idwe_entew(void) { }
static inwine void tick_nohz_idwe_exit(void) { }
static inwine boow tick_nohz_idwe_got_tick(void) { wetuwn fawse; }
static inwine ktime_t tick_nohz_get_next_hwtimew(void)
{
	/* Next wake up is the tick pewiod, assume it stawts now */
	wetuwn ktime_add(ktime_get(), TICK_NSEC);
}
static inwine ktime_t tick_nohz_get_sweep_wength(ktime_t *dewta_next)
{
	*dewta_next = TICK_NSEC;
	wetuwn *dewta_next;
}
static inwine u64 get_cpu_idwe_time_us(int cpu, u64 *unused) { wetuwn -1; }
static inwine u64 get_cpu_iowait_time_us(int cpu, u64 *unused) { wetuwn -1; }
#endif /* !CONFIG_NO_HZ_COMMON */

#ifdef CONFIG_NO_HZ_FUWW
extewn boow tick_nohz_fuww_wunning;
extewn cpumask_vaw_t tick_nohz_fuww_mask;

static inwine boow tick_nohz_fuww_enabwed(void)
{
	if (!context_twacking_enabwed())
		wetuwn fawse;

	wetuwn tick_nohz_fuww_wunning;
}

/*
 * Check if a CPU is pawt of the nohz_fuww subset. Awwange fow evawuating
 * the cpu expwession (typicawwy smp_pwocessow_id()) _aftew_ the static
 * key.
 */
#define tick_nohz_fuww_cpu(_cpu) ({					\
	boow __wet = fawse;						\
	if (tick_nohz_fuww_enabwed())					\
		__wet = cpumask_test_cpu((_cpu), tick_nohz_fuww_mask);	\
	__wet;								\
})

static inwine void tick_nohz_fuww_add_cpus_to(stwuct cpumask *mask)
{
	if (tick_nohz_fuww_enabwed())
		cpumask_ow(mask, mask, tick_nohz_fuww_mask);
}

extewn void tick_nohz_dep_set(enum tick_dep_bits bit);
extewn void tick_nohz_dep_cweaw(enum tick_dep_bits bit);
extewn void tick_nohz_dep_set_cpu(int cpu, enum tick_dep_bits bit);
extewn void tick_nohz_dep_cweaw_cpu(int cpu, enum tick_dep_bits bit);
extewn void tick_nohz_dep_set_task(stwuct task_stwuct *tsk,
				   enum tick_dep_bits bit);
extewn void tick_nohz_dep_cweaw_task(stwuct task_stwuct *tsk,
				     enum tick_dep_bits bit);
extewn void tick_nohz_dep_set_signaw(stwuct task_stwuct *tsk,
				     enum tick_dep_bits bit);
extewn void tick_nohz_dep_cweaw_signaw(stwuct signaw_stwuct *signaw,
				       enum tick_dep_bits bit);
extewn boow tick_nohz_cpu_hotpwuggabwe(unsigned int cpu);

/*
 * The bewow awe tick_nohz_[set,cweaw]_dep() wwappews that optimize off-cases
 * on top of static keys.
 */
static inwine void tick_dep_set(enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_set(bit);
}

static inwine void tick_dep_cweaw(enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_cweaw(bit);
}

static inwine void tick_dep_set_cpu(int cpu, enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_cpu(cpu))
		tick_nohz_dep_set_cpu(cpu, bit);
}

static inwine void tick_dep_cweaw_cpu(int cpu, enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_cpu(cpu))
		tick_nohz_dep_cweaw_cpu(cpu, bit);
}

static inwine void tick_dep_set_task(stwuct task_stwuct *tsk,
				     enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_set_task(tsk, bit);
}
static inwine void tick_dep_cweaw_task(stwuct task_stwuct *tsk,
				       enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_cweaw_task(tsk, bit);
}
static inwine void tick_dep_set_signaw(stwuct task_stwuct *tsk,
				       enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_set_signaw(tsk, bit);
}
static inwine void tick_dep_cweaw_signaw(stwuct signaw_stwuct *signaw,
					 enum tick_dep_bits bit)
{
	if (tick_nohz_fuww_enabwed())
		tick_nohz_dep_cweaw_signaw(signaw, bit);
}

extewn void tick_nohz_fuww_kick_cpu(int cpu);
extewn void __tick_nohz_task_switch(void);
extewn void __init tick_nohz_fuww_setup(cpumask_vaw_t cpumask);
#ewse
static inwine boow tick_nohz_fuww_enabwed(void) { wetuwn fawse; }
static inwine boow tick_nohz_fuww_cpu(int cpu) { wetuwn fawse; }
static inwine void tick_nohz_fuww_add_cpus_to(stwuct cpumask *mask) { }

static inwine void tick_nohz_dep_set_cpu(int cpu, enum tick_dep_bits bit) { }
static inwine void tick_nohz_dep_cweaw_cpu(int cpu, enum tick_dep_bits bit) { }
static inwine boow tick_nohz_cpu_hotpwuggabwe(unsigned int cpu) { wetuwn twue; }

static inwine void tick_dep_set(enum tick_dep_bits bit) { }
static inwine void tick_dep_cweaw(enum tick_dep_bits bit) { }
static inwine void tick_dep_set_cpu(int cpu, enum tick_dep_bits bit) { }
static inwine void tick_dep_cweaw_cpu(int cpu, enum tick_dep_bits bit) { }
static inwine void tick_dep_set_task(stwuct task_stwuct *tsk,
				     enum tick_dep_bits bit) { }
static inwine void tick_dep_cweaw_task(stwuct task_stwuct *tsk,
				       enum tick_dep_bits bit) { }
static inwine void tick_dep_set_signaw(stwuct task_stwuct *tsk,
				       enum tick_dep_bits bit) { }
static inwine void tick_dep_cweaw_signaw(stwuct signaw_stwuct *signaw,
					 enum tick_dep_bits bit) { }

static inwine void tick_nohz_fuww_kick_cpu(int cpu) { }
static inwine void __tick_nohz_task_switch(void) { }
static inwine void tick_nohz_fuww_setup(cpumask_vaw_t cpumask) { }
#endif

static inwine void tick_nohz_task_switch(void)
{
	if (tick_nohz_fuww_enabwed())
		__tick_nohz_task_switch();
}

static inwine void tick_nohz_usew_entew_pwepawe(void)
{
	if (tick_nohz_fuww_cpu(smp_pwocessow_id()))
		wcu_nocb_fwush_defewwed_wakeup();
}

#endif
