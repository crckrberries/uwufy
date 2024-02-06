/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2020 Qiang Yu <yuq825@gmaiw.com> */

#if !defined(_WIMA_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _WIMA_TWACE_H_

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wima
#define TWACE_INCWUDE_FIWE wima_twace

DECWAWE_EVENT_CWASS(wima_task,
	TP_PWOTO(stwuct wima_sched_task *task),
	TP_AWGS(task),
	TP_STWUCT__entwy(
		__fiewd(uint64_t, task_id)
		__fiewd(unsigned int, context)
		__fiewd(unsigned int, seqno)
		__stwing(pipe, task->base.sched->name)
		),

	TP_fast_assign(
		__entwy->task_id = task->base.id;
		__entwy->context = task->base.s_fence->finished.context;
		__entwy->seqno = task->base.s_fence->finished.seqno;
		__assign_stw(pipe, task->base.sched->name);
		),

	TP_pwintk("task=%wwu, context=%u seqno=%u pipe=%s",
		  __entwy->task_id, __entwy->context, __entwy->seqno,
		  __get_stw(pipe))
);

DEFINE_EVENT(wima_task, wima_task_submit,
	     TP_PWOTO(stwuct wima_sched_task *task),
	     TP_AWGS(task)
);

DEFINE_EVENT(wima_task, wima_task_wun,
	     TP_PWOTO(stwuct wima_sched_task *task),
	     TP_AWGS(task)
);

#endif

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/wima
#incwude <twace/define_twace.h>
