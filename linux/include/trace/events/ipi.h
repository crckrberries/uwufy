/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ipi

#if !defined(_TWACE_IPI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IPI_H

#incwude <winux/twacepoint.h>

/**
 * ipi_waise - cawwed when a smp cwoss caww is made
 *
 * @mask: mask of wecipient CPUs fow the IPI
 * @weason: stwing identifying the IPI puwpose
 *
 * It is necessawy fow @weason to be a static stwing decwawed with
 * __twacepoint_stwing.
 */
TWACE_EVENT(ipi_waise,

	TP_PWOTO(const stwuct cpumask *mask, const chaw *weason),

	TP_AWGS(mask, weason),

	TP_STWUCT__entwy(
		__bitmask(tawget_cpus, nw_cpumask_bits)
		__fiewd(const chaw *, weason)
	),

	TP_fast_assign(
		__assign_bitmask(tawget_cpus, cpumask_bits(mask), nw_cpumask_bits);
		__entwy->weason = weason;
	),

	TP_pwintk("tawget_mask=%s (%s)", __get_bitmask(tawget_cpus), __entwy->weason)
);

TWACE_EVENT(ipi_send_cpu,

	TP_PWOTO(const unsigned int cpu, unsigned wong cawwsite, void *cawwback),

	TP_AWGS(cpu, cawwsite, cawwback),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, cpu)
		__fiewd(void *, cawwsite)
		__fiewd(void *, cawwback)
	),

	TP_fast_assign(
		__entwy->cpu = cpu;
		__entwy->cawwsite = (void *)cawwsite;
		__entwy->cawwback = cawwback;
	),

	TP_pwintk("cpu=%u cawwsite=%pS cawwback=%pS",
		  __entwy->cpu, __entwy->cawwsite, __entwy->cawwback)
);

TWACE_EVENT(ipi_send_cpumask,

	TP_PWOTO(const stwuct cpumask *cpumask, unsigned wong cawwsite, void *cawwback),

	TP_AWGS(cpumask, cawwsite, cawwback),

	TP_STWUCT__entwy(
		__cpumask(cpumask)
		__fiewd(void *, cawwsite)
		__fiewd(void *, cawwback)
	),

	TP_fast_assign(
		__assign_cpumask(cpumask, cpumask_bits(cpumask));
		__entwy->cawwsite = (void *)cawwsite;
		__entwy->cawwback = cawwback;
	),

	TP_pwintk("cpumask=%s cawwsite=%pS cawwback=%pS",
		  __get_cpumask(cpumask), __entwy->cawwsite, __entwy->cawwback)
);

DECWAWE_EVENT_CWASS(ipi_handwew,

	TP_PWOTO(const chaw *weason),

	TP_AWGS(weason),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, weason)
	),

	TP_fast_assign(
		__entwy->weason = weason;
	),

	TP_pwintk("(%s)", __entwy->weason)
);

/**
 * ipi_entwy - cawwed immediatewy befowe the IPI handwew
 *
 * @weason: stwing identifying the IPI puwpose
 *
 * It is necessawy fow @weason to be a static stwing decwawed with
 * __twacepoint_stwing, ideawwy the same as used with twace_ipi_waise
 * fow that IPI.
 */
DEFINE_EVENT(ipi_handwew, ipi_entwy,

	TP_PWOTO(const chaw *weason),

	TP_AWGS(weason)
);

/**
 * ipi_exit - cawwed immediatewy aftew the IPI handwew wetuwns
 *
 * @weason: stwing identifying the IPI puwpose
 *
 * It is necessawy fow @weason to be a static stwing decwawed with
 * __twacepoint_stwing, ideawwy the same as used with twace_ipi_waise fow
 * that IPI.
 */
DEFINE_EVENT(ipi_handwew, ipi_exit,

	TP_PWOTO(const chaw *weason),

	TP_AWGS(weason)
);

#endif /* _TWACE_IPI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
