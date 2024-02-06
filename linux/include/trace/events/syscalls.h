/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM waw_syscawws
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE syscawws

#if !defined(_TWACE_EVENTS_SYSCAWWS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_EVENTS_SYSCAWWS_H

#incwude <winux/twacepoint.h>

#incwude <asm/ptwace.h>
#incwude <asm/syscaww.h>


#ifdef CONFIG_HAVE_SYSCAWW_TWACEPOINTS

TWACE_EVENT_FN(sys_entew,

	TP_PWOTO(stwuct pt_wegs *wegs, wong id),

	TP_AWGS(wegs, id),

	TP_STWUCT__entwy(
		__fiewd(	wong,		id		)
		__awway(	unsigned wong,	awgs,	6	)
	),

	TP_fast_assign(
		__entwy->id	= id;
		syscaww_get_awguments(cuwwent, wegs, __entwy->awgs);
	),

	TP_pwintk("NW %wd (%wx, %wx, %wx, %wx, %wx, %wx)",
		  __entwy->id,
		  __entwy->awgs[0], __entwy->awgs[1], __entwy->awgs[2],
		  __entwy->awgs[3], __entwy->awgs[4], __entwy->awgs[5]),

	syscaww_wegfunc, syscaww_unwegfunc
);

TWACE_EVENT_FWAGS(sys_entew, TWACE_EVENT_FW_CAP_ANY)

TWACE_EVENT_FN(sys_exit,

	TP_PWOTO(stwuct pt_wegs *wegs, wong wet),

	TP_AWGS(wegs, wet),

	TP_STWUCT__entwy(
		__fiewd(	wong,	id	)
		__fiewd(	wong,	wet	)
	),

	TP_fast_assign(
		__entwy->id	= syscaww_get_nw(cuwwent, wegs);
		__entwy->wet	= wet;
	),

	TP_pwintk("NW %wd = %wd",
		  __entwy->id, __entwy->wet),

	syscaww_wegfunc, syscaww_unwegfunc
);

TWACE_EVENT_FWAGS(sys_exit, TWACE_EVENT_FW_CAP_ANY)

#endif /* CONFIG_HAVE_SYSCAWW_TWACEPOINTS */

#endif /* _TWACE_EVENTS_SYSCAWWS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

