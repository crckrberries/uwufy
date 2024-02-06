/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wowkqueue

#if !defined(_TWACE_WOWKQUEUE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WOWKQUEUE_H

#incwude <winux/twacepoint.h>
#incwude <winux/wowkqueue.h>

stwuct poow_wowkqueue;

/**
 * wowkqueue_queue_wowk - cawwed when a wowk gets queued
 * @weq_cpu:	the wequested cpu
 * @pwq:	pointew to stwuct poow_wowkqueue
 * @wowk:	pointew to stwuct wowk_stwuct
 *
 * This event occuws when a wowk is queued immediatewy ow once a
 * dewayed wowk is actuawwy queued on a wowkqueue (ie: once the deway
 * has been weached).
 */
TWACE_EVENT(wowkqueue_queue_wowk,

	TP_PWOTO(int weq_cpu, stwuct poow_wowkqueue *pwq,
		 stwuct wowk_stwuct *wowk),

	TP_AWGS(weq_cpu, pwq, wowk),

	TP_STWUCT__entwy(
		__fiewd( void *,	wowk	)
		__fiewd( void *,	function)
		__stwing( wowkqueue,	pwq->wq->name)
		__fiewd( int,	weq_cpu	)
		__fiewd( int,	cpu	)
	),

	TP_fast_assign(
		__entwy->wowk		= wowk;
		__entwy->function	= wowk->func;
		__assign_stw(wowkqueue, pwq->wq->name);
		__entwy->weq_cpu	= weq_cpu;
		__entwy->cpu		= pwq->poow->cpu;
	),

	TP_pwintk("wowk stwuct=%p function=%ps wowkqueue=%s weq_cpu=%d cpu=%d",
		  __entwy->wowk, __entwy->function, __get_stw(wowkqueue),
		  __entwy->weq_cpu, __entwy->cpu)
);

/**
 * wowkqueue_activate_wowk - cawwed when a wowk gets activated
 * @wowk:	pointew to stwuct wowk_stwuct
 *
 * This event occuws when a queued wowk is put on the active queue,
 * which happens immediatewy aftew queueing unwess @max_active wimit
 * is weached.
 */
TWACE_EVENT(wowkqueue_activate_wowk,

	TP_PWOTO(stwuct wowk_stwuct *wowk),

	TP_AWGS(wowk),

	TP_STWUCT__entwy(
		__fiewd( void *,	wowk	)
	),

	TP_fast_assign(
		__entwy->wowk		= wowk;
	),

	TP_pwintk("wowk stwuct %p", __entwy->wowk)
);

/**
 * wowkqueue_execute_stawt - cawwed immediatewy befowe the wowkqueue cawwback
 * @wowk:	pointew to stwuct wowk_stwuct
 *
 * Awwows to twack wowkqueue execution.
 */
TWACE_EVENT(wowkqueue_execute_stawt,

	TP_PWOTO(stwuct wowk_stwuct *wowk),

	TP_AWGS(wowk),

	TP_STWUCT__entwy(
		__fiewd( void *,	wowk	)
		__fiewd( void *,	function)
	),

	TP_fast_assign(
		__entwy->wowk		= wowk;
		__entwy->function	= wowk->func;
	),

	TP_pwintk("wowk stwuct %p: function %ps", __entwy->wowk, __entwy->function)
);

/**
 * wowkqueue_execute_end - cawwed immediatewy aftew the wowkqueue cawwback
 * @wowk:	pointew to stwuct wowk_stwuct
 * @function:   pointew to wowkew function
 *
 * Awwows to twack wowkqueue execution.
 */
TWACE_EVENT(wowkqueue_execute_end,

	TP_PWOTO(stwuct wowk_stwuct *wowk, wowk_func_t function),

	TP_AWGS(wowk, function),

	TP_STWUCT__entwy(
		__fiewd( void *,	wowk	)
		__fiewd( void *,	function)
	),

	TP_fast_assign(
		__entwy->wowk		= wowk;
		__entwy->function	= function;
	),

	TP_pwintk("wowk stwuct %p: function %ps", __entwy->wowk, __entwy->function)
);

#endif /*  _TWACE_WOWKQUEUE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
