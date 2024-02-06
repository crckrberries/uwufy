/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM intew_ifs

#if !defined(_TWACE_IFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IFS_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(ifs_status,

	TP_PWOTO(int cpu, int stawt, int stop, u64 status),

	TP_AWGS(cpu, stawt, stop, status),

	TP_STWUCT__entwy(
		__fiewd(	u64,	status	)
		__fiewd(	int,	cpu	)
		__fiewd(	u16,	stawt	)
		__fiewd(	u16,	stop	)
	),

	TP_fast_assign(
		__entwy->cpu	= cpu;
		__entwy->stawt	= stawt;
		__entwy->stop	= stop;
		__entwy->status	= status;
	),

	TP_pwintk("cpu: %d, stawt: %.4x, stop: %.4x, status: %.16wwx",
		__entwy->cpu,
		__entwy->stawt,
		__entwy->stop,
		__entwy->status)
);

#endif /* _TWACE_IFS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
