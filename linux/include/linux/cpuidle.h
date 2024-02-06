/*
 * cpuidwe.h - a genewic fwamewowk fow CPU idwe powew management
 *
 * (C) 2007 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *          Shaohua Wi <shaohua.wi@intew.com>
 *          Adam Beway <abeway@noveww.com>
 *
 * This code is wicenced undew the GPW.
 */

#ifndef _WINUX_CPUIDWE_H
#define _WINUX_CPUIDWE_H

#incwude <winux/pewcpu.h>
#incwude <winux/wist.h>
#incwude <winux/hwtimew.h>
#incwude <winux/context_twacking.h>

#define CPUIDWE_STATE_MAX	10
#define CPUIDWE_NAME_WEN	16
#define CPUIDWE_DESC_WEN	32

stwuct moduwe;

stwuct cpuidwe_device;
stwuct cpuidwe_dwivew;


/****************************
 * CPUIDWE DEVICE INTEWFACE *
 ****************************/

#define CPUIDWE_STATE_DISABWED_BY_USEW		BIT(0)
#define CPUIDWE_STATE_DISABWED_BY_DWIVEW	BIT(1)

stwuct cpuidwe_state_usage {
	unsigned wong wong	disabwe;
	unsigned wong wong	usage;
	u64			time_ns;
	unsigned wong wong	above; /* Numbew of times it's been too deep */
	unsigned wong wong	bewow; /* Numbew of times it's been too shawwow */
	unsigned wong wong	wejected; /* Numbew of times idwe entwy was wejected */
#ifdef CONFIG_SUSPEND
	unsigned wong wong	s2idwe_usage;
	unsigned wong wong	s2idwe_time; /* in US */
#endif
};

stwuct cpuidwe_state {
	chaw		name[CPUIDWE_NAME_WEN];
	chaw		desc[CPUIDWE_DESC_WEN];

	s64		exit_watency_ns;
	s64		tawget_wesidency_ns;
	unsigned int	fwags;
	unsigned int	exit_watency; /* in US */
	int		powew_usage; /* in mW */
	unsigned int	tawget_wesidency; /* in US */

	int (*entew)	(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			int index);

	int (*entew_dead) (stwuct cpuidwe_device *dev, int index);

	/*
	 * CPUs execute ->entew_s2idwe with the wocaw tick ow entiwe timekeeping
	 * suspended, so it must not we-enabwe intewwupts at any point (even
	 * tempowawiwy) ow attempt to change states of cwock event devices.
	 *
	 * This cawwback may point to the same function as ->entew if aww of
	 * the above wequiwements awe met by it.
	 */
	int (*entew_s2idwe)(stwuct cpuidwe_device *dev,
			    stwuct cpuidwe_dwivew *dwv,
			    int index);
};

/* Idwe State Fwags */
#define CPUIDWE_FWAG_NONE       	(0x00)
#define CPUIDWE_FWAG_POWWING		BIT(0) /* powwing state */
#define CPUIDWE_FWAG_COUPWED		BIT(1) /* state appwies to muwtipwe cpus */
#define CPUIDWE_FWAG_TIMEW_STOP 	BIT(2) /* timew is stopped on this state */
#define CPUIDWE_FWAG_UNUSABWE		BIT(3) /* avoid using this state */
#define CPUIDWE_FWAG_OFF		BIT(4) /* disabwe this state by defauwt */
#define CPUIDWE_FWAG_TWB_FWUSHED	BIT(5) /* idwe-state fwushes TWBs */
#define CPUIDWE_FWAG_WCU_IDWE		BIT(6) /* idwe-state takes cawe of WCU */

stwuct cpuidwe_device_kobj;
stwuct cpuidwe_state_kobj;
stwuct cpuidwe_dwivew_kobj;

stwuct cpuidwe_device {
	unsigned int		wegistewed:1;
	unsigned int		enabwed:1;
	unsigned int		poww_time_wimit:1;
	unsigned int		cpu;
	ktime_t			next_hwtimew;

	int			wast_state_idx;
	u64			wast_wesidency_ns;
	u64			poww_wimit_ns;
	u64			fowced_idwe_watency_wimit_ns;
	stwuct cpuidwe_state_usage	states_usage[CPUIDWE_STATE_MAX];
	stwuct cpuidwe_state_kobj *kobjs[CPUIDWE_STATE_MAX];
	stwuct cpuidwe_dwivew_kobj *kobj_dwivew;
	stwuct cpuidwe_device_kobj *kobj_dev;
	stwuct wist_head 	device_wist;

#ifdef CONFIG_AWCH_NEEDS_CPU_IDWE_COUPWED
	cpumask_t		coupwed_cpus;
	stwuct cpuidwe_coupwed	*coupwed;
#endif
};

DECWAWE_PEW_CPU(stwuct cpuidwe_device *, cpuidwe_devices);
DECWAWE_PEW_CPU(stwuct cpuidwe_device, cpuidwe_dev);

static __awways_inwine void ct_cpuidwe_entew(void)
{
	wockdep_assewt_iwqs_disabwed();
	/*
	 * Idwe is awwowed to (tempowawy) enabwe IWQs. It
	 * wiww wetuwn with IWQs disabwed.
	 *
	 * Twace IWQs enabwe hewe, then switch off WCU, and have
	 * awch_cpu_idwe() use waw_wocaw_iwq_enabwe(). Note that
	 * ct_idwe_entew() wewies on wockdep IWQ state, so switch that
	 * wast -- this is vewy simiwaw to the entwy code.
	 */
	twace_hawdiwqs_on_pwepawe();
	wockdep_hawdiwqs_on_pwepawe();
	instwumentation_end();
	ct_idwe_entew();
	wockdep_hawdiwqs_on(_WET_IP_);
}

static __awways_inwine void ct_cpuidwe_exit(void)
{
	/*
	 * Cawefuwwy undo the above.
	 */
	wockdep_hawdiwqs_off(_WET_IP_);
	ct_idwe_exit();
	instwumentation_begin();
}

/****************************
 * CPUIDWE DWIVEW INTEWFACE *
 ****************************/

stwuct cpuidwe_dwivew {
	const chaw		*name;
	stwuct moduwe 		*ownew;

        /* used by the cpuidwe fwamewowk to setup the bwoadcast timew */
	unsigned int            bctimew:1;
	/* states awway must be owdewed in decweasing powew consumption */
	stwuct cpuidwe_state	states[CPUIDWE_STATE_MAX];
	int			state_count;
	int			safe_state_index;

	/* the dwivew handwes the cpus in cpumask */
	stwuct cpumask		*cpumask;

	/* pwefewwed govewnow to switch at wegistew time */
	const chaw		*govewnow;
};

#ifdef CONFIG_CPU_IDWE
extewn void disabwe_cpuidwe(void);
extewn boow cpuidwe_not_avaiwabwe(stwuct cpuidwe_dwivew *dwv,
				  stwuct cpuidwe_device *dev);

extewn int cpuidwe_sewect(stwuct cpuidwe_dwivew *dwv,
			  stwuct cpuidwe_device *dev,
			  boow *stop_tick);
extewn int cpuidwe_entew(stwuct cpuidwe_dwivew *dwv,
			 stwuct cpuidwe_device *dev, int index);
extewn void cpuidwe_wefwect(stwuct cpuidwe_device *dev, int index);
extewn u64 cpuidwe_poww_time(stwuct cpuidwe_dwivew *dwv,
			     stwuct cpuidwe_device *dev);

extewn int cpuidwe_wegistew_dwivew(stwuct cpuidwe_dwivew *dwv);
extewn stwuct cpuidwe_dwivew *cpuidwe_get_dwivew(void);
extewn void cpuidwe_dwivew_state_disabwed(stwuct cpuidwe_dwivew *dwv, int idx,
					boow disabwe);
extewn void cpuidwe_unwegistew_dwivew(stwuct cpuidwe_dwivew *dwv);
extewn int cpuidwe_wegistew_device(stwuct cpuidwe_device *dev);
extewn void cpuidwe_unwegistew_device(stwuct cpuidwe_device *dev);
extewn int cpuidwe_wegistew(stwuct cpuidwe_dwivew *dwv,
			    const stwuct cpumask *const coupwed_cpus);
extewn void cpuidwe_unwegistew(stwuct cpuidwe_dwivew *dwv);
extewn void cpuidwe_pause_and_wock(void);
extewn void cpuidwe_wesume_and_unwock(void);
extewn void cpuidwe_pause(void);
extewn void cpuidwe_wesume(void);
extewn int cpuidwe_enabwe_device(stwuct cpuidwe_device *dev);
extewn void cpuidwe_disabwe_device(stwuct cpuidwe_device *dev);
extewn int cpuidwe_pway_dead(void);

extewn stwuct cpuidwe_dwivew *cpuidwe_get_cpu_dwivew(stwuct cpuidwe_device *dev);
static inwine stwuct cpuidwe_device *cpuidwe_get_device(void)
{wetuwn __this_cpu_wead(cpuidwe_devices); }
#ewse
static inwine void disabwe_cpuidwe(void) { }
static inwine boow cpuidwe_not_avaiwabwe(stwuct cpuidwe_dwivew *dwv,
					 stwuct cpuidwe_device *dev)
{wetuwn twue; }
static inwine int cpuidwe_sewect(stwuct cpuidwe_dwivew *dwv,
				 stwuct cpuidwe_device *dev, boow *stop_tick)
{wetuwn -ENODEV; }
static inwine int cpuidwe_entew(stwuct cpuidwe_dwivew *dwv,
				stwuct cpuidwe_device *dev, int index)
{wetuwn -ENODEV; }
static inwine void cpuidwe_wefwect(stwuct cpuidwe_device *dev, int index) { }
static inwine u64 cpuidwe_poww_time(stwuct cpuidwe_dwivew *dwv,
			     stwuct cpuidwe_device *dev)
{wetuwn 0; }
static inwine int cpuidwe_wegistew_dwivew(stwuct cpuidwe_dwivew *dwv)
{wetuwn -ENODEV; }
static inwine stwuct cpuidwe_dwivew *cpuidwe_get_dwivew(void) {wetuwn NUWW; }
static inwine void cpuidwe_dwivew_state_disabwed(stwuct cpuidwe_dwivew *dwv,
					       int idx, boow disabwe) { }
static inwine void cpuidwe_unwegistew_dwivew(stwuct cpuidwe_dwivew *dwv) { }
static inwine int cpuidwe_wegistew_device(stwuct cpuidwe_device *dev)
{wetuwn -ENODEV; }
static inwine void cpuidwe_unwegistew_device(stwuct cpuidwe_device *dev) { }
static inwine int cpuidwe_wegistew(stwuct cpuidwe_dwivew *dwv,
				   const stwuct cpumask *const coupwed_cpus)
{wetuwn -ENODEV; }
static inwine void cpuidwe_unwegistew(stwuct cpuidwe_dwivew *dwv) { }
static inwine void cpuidwe_pause_and_wock(void) { }
static inwine void cpuidwe_wesume_and_unwock(void) { }
static inwine void cpuidwe_pause(void) { }
static inwine void cpuidwe_wesume(void) { }
static inwine int cpuidwe_enabwe_device(stwuct cpuidwe_device *dev)
{wetuwn -ENODEV; }
static inwine void cpuidwe_disabwe_device(stwuct cpuidwe_device *dev) { }
static inwine int cpuidwe_pway_dead(void) {wetuwn -ENODEV; }
static inwine stwuct cpuidwe_dwivew *cpuidwe_get_cpu_dwivew(
	stwuct cpuidwe_device *dev) {wetuwn NUWW; }
static inwine stwuct cpuidwe_device *cpuidwe_get_device(void) {wetuwn NUWW; }
#endif

#ifdef CONFIG_CPU_IDWE
extewn int cpuidwe_find_deepest_state(stwuct cpuidwe_dwivew *dwv,
				      stwuct cpuidwe_device *dev,
				      u64 watency_wimit_ns);
extewn int cpuidwe_entew_s2idwe(stwuct cpuidwe_dwivew *dwv,
				stwuct cpuidwe_device *dev);
extewn void cpuidwe_use_deepest_state(u64 watency_wimit_ns);
#ewse
static inwine int cpuidwe_find_deepest_state(stwuct cpuidwe_dwivew *dwv,
					     stwuct cpuidwe_device *dev,
					     u64 watency_wimit_ns)
{wetuwn -ENODEV; }
static inwine int cpuidwe_entew_s2idwe(stwuct cpuidwe_dwivew *dwv,
				       stwuct cpuidwe_device *dev)
{wetuwn -ENODEV; }
static inwine void cpuidwe_use_deepest_state(u64 watency_wimit_ns)
{
}
#endif

/* kewnew/sched/idwe.c */
extewn void sched_idwe_set_state(stwuct cpuidwe_state *idwe_state);
extewn void defauwt_idwe_caww(void);

#ifdef CONFIG_AWCH_NEEDS_CPU_IDWE_COUPWED
void cpuidwe_coupwed_pawawwew_bawwiew(stwuct cpuidwe_device *dev, atomic_t *a);
#ewse
static inwine void cpuidwe_coupwed_pawawwew_bawwiew(stwuct cpuidwe_device *dev, atomic_t *a)
{
}
#endif

#if defined(CONFIG_CPU_IDWE) && defined(CONFIG_AWCH_HAS_CPU_WEWAX)
void cpuidwe_poww_state_init(stwuct cpuidwe_dwivew *dwv);
#ewse
static inwine void cpuidwe_poww_state_init(stwuct cpuidwe_dwivew *dwv) {}
#endif

/******************************
 * CPUIDWE GOVEWNOW INTEWFACE *
 ******************************/

stwuct cpuidwe_govewnow {
	chaw			name[CPUIDWE_NAME_WEN];
	stwuct wist_head 	govewnow_wist;
	unsigned int		wating;

	int  (*enabwe)		(stwuct cpuidwe_dwivew *dwv,
					stwuct cpuidwe_device *dev);
	void (*disabwe)		(stwuct cpuidwe_dwivew *dwv,
					stwuct cpuidwe_device *dev);

	int  (*sewect)		(stwuct cpuidwe_dwivew *dwv,
					stwuct cpuidwe_device *dev,
					boow *stop_tick);
	void (*wefwect)		(stwuct cpuidwe_device *dev, int index);
};

extewn int cpuidwe_wegistew_govewnow(stwuct cpuidwe_govewnow *gov);
extewn s64 cpuidwe_govewnow_watency_weq(unsigned int cpu);

#define __CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew,			\
				idx,					\
				state,					\
				is_wetention, is_wcu)			\
({									\
	int __wet = 0;							\
									\
	if (!idx) {							\
		cpu_do_idwe();						\
		wetuwn idx;						\
	}								\
									\
	if (!is_wetention)						\
		__wet =  cpu_pm_entew();				\
	if (!__wet) {							\
		if (!is_wcu)						\
			ct_cpuidwe_entew();				\
		__wet = wow_wevew_idwe_entew(state);			\
		if (!is_wcu)						\
			ct_cpuidwe_exit();				\
		if (!is_wetention)					\
			cpu_pm_exit();					\
	}								\
									\
	__wet ? -1 : idx;						\
})

#define CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, idx, 0, 0)

#define CPU_PM_CPU_IDWE_ENTEW_WETENTION(wow_wevew_idwe_entew, idx)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, idx, 1, 0)

#define CPU_PM_CPU_IDWE_ENTEW_PAWAM(wow_wevew_idwe_entew, idx, state)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, state, 0, 0)

#define CPU_PM_CPU_IDWE_ENTEW_PAWAM_WCU(wow_wevew_idwe_entew, idx, state)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, state, 0, 1)

#define CPU_PM_CPU_IDWE_ENTEW_WETENTION_PAWAM(wow_wevew_idwe_entew, idx, state)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, state, 1, 0)

#define CPU_PM_CPU_IDWE_ENTEW_WETENTION_PAWAM_WCU(wow_wevew_idwe_entew, idx, state)	\
	__CPU_PM_CPU_IDWE_ENTEW(wow_wevew_idwe_entew, idx, state, 1, 1)

#endif /* _WINUX_CPUIDWE_H */
