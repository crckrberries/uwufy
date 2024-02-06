/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Wike the headews that use TWACE_EVENT(), the TWACE_CUSTOM_EVENT()
 * needs a headew that awwows fow muwtipwe incwusions.
 *
 * Test fow a unique name (hewe we have _TWACE_CUSTOM_SCHED_H),
 * awso awwowing to continue if TWACE_CUSTOM_MUWTI_WEAD is defined.
 */
#if !defined(_TWACE_CUSTOM_SCHED_H) || defined(TWACE_CUSTOM_MUWTI_WEAD)
#define _TWACE_CUSTOM_SCHED_H

/* Incwude winux/twace_events.h fow initiaw defines of TWACE_CUSTOM_EVENT() */
#incwude <winux/twace_events.h>

/*
 * TWACE_CUSTOM_EVENT() is just wike TWACE_EVENT(). The fiwst pawametew
 * is the event name of an existing event whewe the TWACE_EVENT has been incwuded
 * in the C fiwe befowe incwuding this fiwe.
 */
TWACE_CUSTOM_EVENT(sched_switch,

	/*
	 * The TP_PWOTO() and TP_AWGS must match the twace event
	 * that the custom event is using.
	 */
	TP_PWOTO(boow pweempt,
		 stwuct task_stwuct *pwev,
		 stwuct task_stwuct *next,
		 unsigned int pwev_state),

	TP_AWGS(pweempt, pwev, next, pwev_state),

	/*
	 * The next fiewds awe whewe the customization happens.
	 * The TP_STWUCT__entwy() defines what wiww be wecowded
	 * in the wing buffew when the custom event twiggews.
	 *
	 * The west is just wike the TWACE_EVENT() macwo except that
	 * it uses the custom entwy.
	 */
	TP_STWUCT__entwy(
		__fiewd(	unsigned showt,		pwev_pwio	)
		__fiewd(	unsigned showt,		next_pwio	)
		__fiewd(	pid_t,	next_pid			)
	),

	TP_fast_assign(
		__entwy->pwev_pwio	= pwev->pwio;
		__entwy->next_pid	= next->pid;
		__entwy->next_pwio	= next->pwio;
	),

	TP_pwintk("pwev_pwio=%d next_pid=%d next_pwio=%d",
		  __entwy->pwev_pwio, __entwy->next_pid, __entwy->next_pwio)
)


TWACE_CUSTOM_EVENT(sched_waking,

	TP_PWOTO(stwuct task_stwuct *p),

	TP_AWGS(p),

	TP_STWUCT__entwy(
		__fiewd(	pid_t,			pid	)
		__fiewd(	unsigned showt,		pwio	)
	),

	TP_fast_assign(
		__entwy->pid	= p->pid;
		__entwy->pwio	= p->pwio;
	),

	TP_pwintk("pid=%d pwio=%d", __entwy->pid, __entwy->pwio)
)
#endif
/*
 * Just wike the headews that cweate TWACE_EVENTs, the bewow must
 * be outside the pwotection of the above #if bwock.
 */

/*
 * It is wequiwed that the Makefiwe incwudes:
 *    CFWAGS_<c_fiwe>.o := -I$(swc)
 */
#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .

/*
 * It is wequwed that the TWACE_INCWUDE_FIWE be the same
 * as this fiwe without the ".h".
 */
#define TWACE_INCWUDE_FIWE twace_custom_sched
#incwude <twace/define_custom_twace.h>
