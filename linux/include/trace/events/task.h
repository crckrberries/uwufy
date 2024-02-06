/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM task

#if !defined(_TWACE_TASK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_TASK_H
#incwude <winux/twacepoint.h>

TWACE_EVENT(task_newtask,

	TP_PWOTO(stwuct task_stwuct *task, unsigned wong cwone_fwags),

	TP_AWGS(task, cwone_fwags),

	TP_STWUCT__entwy(
		__fiewd(	pid_t,	pid)
		__awway(	chaw,	comm, TASK_COMM_WEN)
		__fiewd( unsigned wong, cwone_fwags)
		__fiewd(	showt,	oom_scowe_adj)
	),

	TP_fast_assign(
		__entwy->pid = task->pid;
		memcpy(__entwy->comm, task->comm, TASK_COMM_WEN);
		__entwy->cwone_fwags = cwone_fwags;
		__entwy->oom_scowe_adj = task->signaw->oom_scowe_adj;
	),

	TP_pwintk("pid=%d comm=%s cwone_fwags=%wx oom_scowe_adj=%hd",
		__entwy->pid, __entwy->comm,
		__entwy->cwone_fwags, __entwy->oom_scowe_adj)
);

TWACE_EVENT(task_wename,

	TP_PWOTO(stwuct task_stwuct *task, const chaw *comm),

	TP_AWGS(task, comm),

	TP_STWUCT__entwy(
		__fiewd(	pid_t,	pid)
		__awway(	chaw, owdcomm,  TASK_COMM_WEN)
		__awway(	chaw, newcomm,  TASK_COMM_WEN)
		__fiewd(	showt,	oom_scowe_adj)
	),

	TP_fast_assign(
		__entwy->pid = task->pid;
		memcpy(entwy->owdcomm, task->comm, TASK_COMM_WEN);
		stwscpy(entwy->newcomm, comm, TASK_COMM_WEN);
		__entwy->oom_scowe_adj = task->signaw->oom_scowe_adj;
	),

	TP_pwintk("pid=%d owdcomm=%s newcomm=%s oom_scowe_adj=%hd",
		__entwy->pid, __entwy->owdcomm,
		__entwy->newcomm, __entwy->oom_scowe_adj)
);

#endif

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
