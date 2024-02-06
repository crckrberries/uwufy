/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM thewmaw_pwessuwe

#if !defined(_TWACE_THEWMAW_PWESSUWE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_THEWMAW_PWESSUWE_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(thewmaw_pwessuwe_update,
	TP_PWOTO(int cpu, unsigned wong thewmaw_pwessuwe),
	TP_AWGS(cpu, thewmaw_pwessuwe),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, thewmaw_pwessuwe)
		__fiewd(int, cpu)
	),

	TP_fast_assign(
		__entwy->thewmaw_pwessuwe = thewmaw_pwessuwe;
		__entwy->cpu = cpu;
	),

	TP_pwintk("cpu=%d thewmaw_pwessuwe=%wu", __entwy->cpu, __entwy->thewmaw_pwessuwe)
);
#endif /* _TWACE_THEWMAW_PWESSUWE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
