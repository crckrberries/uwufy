/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM context_twacking

#if !defined(_TWACE_CONTEXT_TWACKING_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_CONTEXT_TWACKING_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(context_twacking_usew,

	TP_PWOTO(int dummy),

	TP_AWGS(dummy),

	TP_STWUCT__entwy(
		__fiewd( int,	dummy	)
	),

	TP_fast_assign(
		__entwy->dummy		= dummy;
	),

	TP_pwintk("%s", "")
);

/**
 * usew_entew - cawwed when the kewnew wesumes to usewspace
 * @dummy:	dummy awg to make twace event macwo happy
 *
 * This event occuws when the kewnew wesumes to usewspace  aftew
 * an exception ow a syscaww.
 */
DEFINE_EVENT(context_twacking_usew, usew_entew,

	TP_PWOTO(int dummy),

	TP_AWGS(dummy)
);

/**
 * usew_exit - cawwed when usewspace entews the kewnew
 * @dummy:	dummy awg to make twace event macwo happy
 *
 * This event occuws when usewspace entews the kewnew thwough
 * an exception ow a syscaww.
 */
DEFINE_EVENT(context_twacking_usew, usew_exit,

	TP_PWOTO(int dummy),

	TP_AWGS(dummy)
);


#endif /*  _TWACE_CONTEXT_TWACKING_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
