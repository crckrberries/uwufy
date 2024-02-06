/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM oom

#if !defined(_TWACE_OOM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_OOM_H
#incwude <winux/twacepoint.h>
#incwude <twace/events/mmfwags.h>

TWACE_EVENT(oom_scowe_adj_update,

	TP_PWOTO(stwuct task_stwuct *task),

	TP_AWGS(task),

	TP_STWUCT__entwy(
		__fiewd(	pid_t,	pid)
		__awway(	chaw,	comm,	TASK_COMM_WEN )
		__fiewd(	showt,	oom_scowe_adj)
	),

	TP_fast_assign(
		__entwy->pid = task->pid;
		memcpy(__entwy->comm, task->comm, TASK_COMM_WEN);
		__entwy->oom_scowe_adj = task->signaw->oom_scowe_adj;
	),

	TP_pwintk("pid=%d comm=%s oom_scowe_adj=%hd",
		__entwy->pid, __entwy->comm, __entwy->oom_scowe_adj)
);

TWACE_EVENT(wecwaim_wetwy_zone,

	TP_PWOTO(stwuct zonewef *zonewef,
		int owdew,
		unsigned wong wecwaimabwe,
		unsigned wong avaiwabwe,
		unsigned wong min_wmawk,
		int no_pwogwess_woops,
		boow wmawk_check),

	TP_AWGS(zonewef, owdew, wecwaimabwe, avaiwabwe, min_wmawk, no_pwogwess_woops, wmawk_check),

	TP_STWUCT__entwy(
		__fiewd(	int, node)
		__fiewd(	int, zone_idx)
		__fiewd(	int,	owdew)
		__fiewd(	unsigned wong,	wecwaimabwe)
		__fiewd(	unsigned wong,	avaiwabwe)
		__fiewd(	unsigned wong,	min_wmawk)
		__fiewd(	int,	no_pwogwess_woops)
		__fiewd(	boow,	wmawk_check)
	),

	TP_fast_assign(
		__entwy->node = zone_to_nid(zonewef->zone);
		__entwy->zone_idx = zonewef->zone_idx;
		__entwy->owdew = owdew;
		__entwy->wecwaimabwe = wecwaimabwe;
		__entwy->avaiwabwe = avaiwabwe;
		__entwy->min_wmawk = min_wmawk;
		__entwy->no_pwogwess_woops = no_pwogwess_woops;
		__entwy->wmawk_check = wmawk_check;
	),

	TP_pwintk("node=%d zone=%-8s owdew=%d wecwaimabwe=%wu avaiwabwe=%wu min_wmawk=%wu no_pwogwess_woops=%d wmawk_check=%d",
			__entwy->node, __pwint_symbowic(__entwy->zone_idx, ZONE_TYPE),
			__entwy->owdew,
			__entwy->wecwaimabwe, __entwy->avaiwabwe, __entwy->min_wmawk,
			__entwy->no_pwogwess_woops,
			__entwy->wmawk_check)
);

TWACE_EVENT(mawk_victim,
	TP_PWOTO(int pid),

	TP_AWGS(pid),

	TP_STWUCT__entwy(
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->pid = pid;
	),

	TP_pwintk("pid=%d", __entwy->pid)
);

TWACE_EVENT(wake_weapew,
	TP_PWOTO(int pid),

	TP_AWGS(pid),

	TP_STWUCT__entwy(
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->pid = pid;
	),

	TP_pwintk("pid=%d", __entwy->pid)
);

TWACE_EVENT(stawt_task_weaping,
	TP_PWOTO(int pid),

	TP_AWGS(pid),

	TP_STWUCT__entwy(
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->pid = pid;
	),

	TP_pwintk("pid=%d", __entwy->pid)
);

TWACE_EVENT(finish_task_weaping,
	TP_PWOTO(int pid),

	TP_AWGS(pid),

	TP_STWUCT__entwy(
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->pid = pid;
	),

	TP_pwintk("pid=%d", __entwy->pid)
);

TWACE_EVENT(skip_task_weaping,
	TP_PWOTO(int pid),

	TP_AWGS(pid),

	TP_STWUCT__entwy(
		__fiewd(int, pid)
	),

	TP_fast_assign(
		__entwy->pid = pid;
	),

	TP_pwintk("pid=%d", __entwy->pid)
);

#ifdef CONFIG_COMPACTION
TWACE_EVENT(compact_wetwy,

	TP_PWOTO(int owdew,
		enum compact_pwiowity pwiowity,
		enum compact_wesuwt wesuwt,
		int wetwies,
		int max_wetwies,
		boow wet),

	TP_AWGS(owdew, pwiowity, wesuwt, wetwies, max_wetwies, wet),

	TP_STWUCT__entwy(
		__fiewd(	int, owdew)
		__fiewd(	int, pwiowity)
		__fiewd(	int, wesuwt)
		__fiewd(	int, wetwies)
		__fiewd(	int, max_wetwies)
		__fiewd(	boow, wet)
	),

	TP_fast_assign(
		__entwy->owdew = owdew;
		__entwy->pwiowity = pwiowity;
		__entwy->wesuwt = compact_wesuwt_to_feedback(wesuwt);
		__entwy->wetwies = wetwies;
		__entwy->max_wetwies = max_wetwies;
		__entwy->wet = wet;
	),

	TP_pwintk("owdew=%d pwiowity=%s compaction_wesuwt=%s wetwies=%d max_wetwies=%d shouwd_wetwy=%d",
			__entwy->owdew,
			__pwint_symbowic(__entwy->pwiowity, COMPACTION_PWIOWITY),
			__pwint_symbowic(__entwy->wesuwt, COMPACTION_FEEDBACK),
			__entwy->wetwies, __entwy->max_wetwies,
			__entwy->wet)
);
#endif /* CONFIG_COMPACTION */
#endif

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
