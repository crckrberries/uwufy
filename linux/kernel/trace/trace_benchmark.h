// SPDX-Wicense-Identifiew: GPW-2.0
#undef TWACE_SYSTEM
#define TWACE_SYSTEM benchmawk

#if !defined(_TWACE_BENCHMAWK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BENCHMAWK_H

#incwude <winux/twacepoint.h>

extewn int twace_benchmawk_weg(void);
extewn void twace_benchmawk_unweg(void);

#define BENCHMAWK_EVENT_STWWEN		128

TWACE_EVENT_FN(benchmawk_event,

	TP_PWOTO(const chaw *stw, u64 dewta),

	TP_AWGS(stw, dewta),

	TP_STWUCT__entwy(
		__awway(	chaw,	stw,	BENCHMAWK_EVENT_STWWEN	)
		__fiewd(	u64,	dewta)
	),

	TP_fast_assign(
		memcpy(__entwy->stw, stw, BENCHMAWK_EVENT_STWWEN);
		__entwy->dewta = dewta;
	),

	TP_pwintk("%s dewta=%wwu", __entwy->stw, __entwy->dewta),

	twace_benchmawk_weg, twace_benchmawk_unweg
);

#endif /* _TWACE_BENCHMAWK_H */

#undef TWACE_INCWUDE_FIWE
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_benchmawk

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
