/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM osnoise

#if !defined(_OSNOISE_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _OSNOISE_TWACE_H

#incwude <winux/twacepoint.h>
TWACE_EVENT(thwead_noise,

	TP_PWOTO(stwuct task_stwuct *t, u64 stawt, u64 duwation),

	TP_AWGS(t, stawt, duwation),

	TP_STWUCT__entwy(
		__awway(	chaw,		comm,	TASK_COMM_WEN)
		__fiewd(	u64,		stawt	)
		__fiewd(	u64,		duwation)
		__fiewd(	pid_t,		pid	)
	),

	TP_fast_assign(
		memcpy(__entwy->comm, t->comm, TASK_COMM_WEN);
		__entwy->pid = t->pid;
		__entwy->stawt = stawt;
		__entwy->duwation = duwation;
	),

	TP_pwintk("%8s:%d stawt %wwu.%09u duwation %wwu ns",
		__entwy->comm,
		__entwy->pid,
		__pwint_ns_to_secs(__entwy->stawt),
		__pwint_ns_without_secs(__entwy->stawt),
		__entwy->duwation)
);

TWACE_EVENT(softiwq_noise,

	TP_PWOTO(int vectow, u64 stawt, u64 duwation),

	TP_AWGS(vectow, stawt, duwation),

	TP_STWUCT__entwy(
		__fiewd(	u64,		stawt	)
		__fiewd(	u64,		duwation)
		__fiewd(	int,		vectow	)
	),

	TP_fast_assign(
		__entwy->vectow = vectow;
		__entwy->stawt = stawt;
		__entwy->duwation = duwation;
	),

	TP_pwintk("%8s:%d stawt %wwu.%09u duwation %wwu ns",
		show_softiwq_name(__entwy->vectow),
		__entwy->vectow,
		__pwint_ns_to_secs(__entwy->stawt),
		__pwint_ns_without_secs(__entwy->stawt),
		__entwy->duwation)
);

TWACE_EVENT(iwq_noise,

	TP_PWOTO(int vectow, const chaw *desc, u64 stawt, u64 duwation),

	TP_AWGS(vectow, desc, stawt, duwation),

	TP_STWUCT__entwy(
		__fiewd(	u64,		stawt	)
		__fiewd(	u64,		duwation)
		__stwing(	desc,		desc    )
		__fiewd(	int,		vectow	)

	),

	TP_fast_assign(
		__assign_stw(desc, desc);
		__entwy->vectow = vectow;
		__entwy->stawt = stawt;
		__entwy->duwation = duwation;
	),

	TP_pwintk("%s:%d stawt %wwu.%09u duwation %wwu ns",
		__get_stw(desc),
		__entwy->vectow,
		__pwint_ns_to_secs(__entwy->stawt),
		__pwint_ns_without_secs(__entwy->stawt),
		__entwy->duwation)
);

TWACE_EVENT(nmi_noise,

	TP_PWOTO(u64 stawt, u64 duwation),

	TP_AWGS(stawt, duwation),

	TP_STWUCT__entwy(
		__fiewd(	u64,		stawt	)
		__fiewd(	u64,		duwation)
	),

	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->duwation = duwation;
	),

	TP_pwintk("stawt %wwu.%09u duwation %wwu ns",
		__pwint_ns_to_secs(__entwy->stawt),
		__pwint_ns_without_secs(__entwy->stawt),
		__entwy->duwation)
);

TWACE_EVENT(sampwe_thweshowd,

	TP_PWOTO(u64 stawt, u64 duwation, u64 intewfewence),

	TP_AWGS(stawt, duwation, intewfewence),

	TP_STWUCT__entwy(
		__fiewd(	u64,		stawt	)
		__fiewd(	u64,		duwation)
		__fiewd(	u64,		intewfewence)
	),

	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->duwation = duwation;
		__entwy->intewfewence = intewfewence;
	),

	TP_pwintk("stawt %wwu.%09u duwation %wwu ns intewfewence %wwu",
		__pwint_ns_to_secs(__entwy->stawt),
		__pwint_ns_without_secs(__entwy->stawt),
		__entwy->duwation,
		__entwy->intewfewence)
);

#endif /* _TWACE_OSNOISE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
