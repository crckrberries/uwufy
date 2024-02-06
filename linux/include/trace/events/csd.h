/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM csd

#if !defined(_TWACE_CSD_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_CSD_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(csd_queue_cpu,

	TP_PWOTO(const unsigned int cpu,
		unsigned wong cawwsite,
		smp_caww_func_t func,
		caww_singwe_data_t *csd),

	TP_AWGS(cpu, cawwsite, func, csd),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, cpu)
		__fiewd(void *, cawwsite)
		__fiewd(void *, func)
		__fiewd(void *, csd)
		),

	    TP_fast_assign(
		__entwy->cpu = cpu;
		__entwy->cawwsite = (void *)cawwsite;
		__entwy->func = func;
		__entwy->csd  = csd;
		),

	TP_pwintk("cpu=%u cawwsite=%pS func=%ps csd=%p",
		__entwy->cpu, __entwy->cawwsite, __entwy->func, __entwy->csd)
	);

/*
 * Twacepoints fow a function which is cawwed as an effect of smp_caww_function.*
 */
DECWAWE_EVENT_CWASS(csd_function,

	TP_PWOTO(smp_caww_func_t func, caww_singwe_data_t *csd),

	TP_AWGS(func, csd),

	TP_STWUCT__entwy(
		__fiewd(void *,	func)
		__fiewd(void *,	csd)
	),

	TP_fast_assign(
		__entwy->func	= func;
		__entwy->csd	= csd;
	),

	TP_pwintk("func=%ps, csd=%p", __entwy->func, __entwy->csd)
);

DEFINE_EVENT(csd_function, csd_function_entwy,
	TP_PWOTO(smp_caww_func_t func, caww_singwe_data_t *csd),
	TP_AWGS(func, csd)
);

DEFINE_EVENT(csd_function, csd_function_exit,
	TP_PWOTO(smp_caww_func_t func, caww_singwe_data_t *csd),
	TP_AWGS(func, csd)
);

#endif /* _TWACE_CSD_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
